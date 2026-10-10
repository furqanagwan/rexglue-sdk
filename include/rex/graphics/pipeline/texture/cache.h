#pragma once
/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <array>
#include <atomic>
#include <cstdint>
#include <cstring>
#include <memory>
#include <unordered_map>
#include <vector>

#include <rex/assert.h>
#include <rex/graphics/pipeline/texture/util.h>
#include <rex/graphics/register_file.h>
#include <rex/graphics/shared_memory.h>
#include <rex/graphics/xenos.h>
#include <rex/hash.h>
#include <rex/thread/mutex.h>

namespace rex::graphics {

class TextureCache {
 public:
  static constexpr uint32_t kMaxDrawResolutionScaleAlongAxis = 7;

  TextureCache(const TextureCache& texture_cache) = delete;
  TextureCache& operator=(const TextureCache& texture_cache) = delete;
  virtual ~TextureCache();

  static bool GetConfigDrawResolutionScale(uint32_t& x_out, uint32_t& y_out);
  uint32_t draw_resolution_scale_x() const { return draw_resolution_scale_x_; }
  uint32_t draw_resolution_scale_y() const { return draw_resolution_scale_y_; }
  bool IsDrawResolutionScaled() const {
    return draw_resolution_scale_x_ > 1 || draw_resolution_scale_y_ > 1;
  }

  virtual void ClearCache();

  virtual void CompletedSubmissionUpdated(uint64_t completed_submission_index);
  virtual void BeginSubmission(uint64_t new_submission_index);
  virtual void BeginFrame();

  void MarkRangeAsResolved(uint32_t start_unscaled, uint32_t length_unscaled);

  void MarkRangeAsNativeResolved(uint32_t start_unscaled, uint32_t length_unscaled);

  bool IsRangeResolvedScaled(uint32_t start_unscaled, uint32_t length_unscaled) {
    return IsRangeScaledResolved(start_unscaled, length_unscaled);
  }

  virtual bool EnsureScaledResolveMemoryCommitted(uint32_t, uint32_t, uint32_t = 0) {
    return false;
  }

  static uint32_t GuestToHostSwizzle(uint32_t guest_swizzle, uint32_t host_format_swizzle);

  void TextureFetchConstantWritten(uint32_t index) { TextureFetchConstantsWritten(index, index); }
  void TextureFetchConstantsWritten(uint32_t first_index, uint32_t last_index) {
    if (first_index > last_index) {
      uint32_t swap_index = first_index;
      first_index = last_index;
      last_index = swap_index;
    }
    if (first_index > 31) {
      return;
    }
    if (last_index > 31) {
      last_index = 31;
    }
    uint32_t bit_count = last_index - first_index + 1;
    uint32_t mask = bit_count == 32 ? UINT32_MAX : ((UINT32_C(1) << bit_count) - 1) << first_index;
    texture_bindings_in_sync_ &= ~mask;
  }

  virtual void RequestTextures(uint32_t used_texture_mask);

  uint32_t GetActiveTextureHostSwizzle(uint32_t fetch_constant_index) const {
    const TextureBinding* binding = GetValidTextureBinding(fetch_constant_index);
    return binding ? binding->host_swizzle : xenos::XE_GPU_TEXTURE_SWIZZLE_0000;
  }
  uint8_t GetActiveTextureSwizzledSigns(uint32_t fetch_constant_index) const {
    const TextureBinding* binding = GetValidTextureBinding(fetch_constant_index);
    return binding ? binding->swizzled_signs : kSwizzledSignsUnsigned;
  }
  uint32_t GetActiveIntegerScaleBits(uint32_t fetch_constant_index) const {
    const TextureBinding* binding = GetValidTextureBinding(fetch_constant_index);
    return binding ? binding->integer_scale_bits : 0;
  }
  bool IsActiveTextureResolutionScaled(uint32_t fetch_constant_index) const {
    const TextureBinding* binding = GetValidTextureBinding(fetch_constant_index);
    if (!binding) {
      return false;
    }
    return (binding->texture && binding->texture->key().scaled_resolve) ||
           (binding->texture_signed && binding->texture_signed->key().scaled_resolve);
  }

 protected:
  struct TextureKey {
    uint32_t base_page : 17;
    xenos::DataDimension dimension : 2;
    uint32_t width_minus_1 : 13;

    uint32_t height_minus_1 : 13;
    uint32_t tiled : 1;
    uint32_t packed_mips : 1;

    uint32_t mip_page : 17;

    uint32_t depth_or_array_size_minus_1 : 10;
    uint32_t pitch : 9;
    uint32_t mip_max_level : 4;
    xenos::TextureFormat format : 6;
    xenos::Endian endianness : 2;

    uint32_t signed_separate : 1;

    uint32_t scaled_resolve : 1;

    uint32_t is_valid : 1;

    TextureKey() { MakeInvalid(); }
    TextureKey(const TextureKey& key) { std::memcpy(this, &key, sizeof(*this)); }
    TextureKey& operator=(const TextureKey& key) {
      std::memcpy(this, &key, sizeof(*this));
      return *this;
    }
    void MakeInvalid() { std::memset(this, 0, sizeof(*this)); }

    using Hasher = rex::XXHasher<TextureKey>;
    bool operator==(const TextureKey& key) const { return !std::memcmp(this, &key, sizeof(*this)); }
    bool operator!=(const TextureKey& key) const { return !(*this == key); }

    uint32_t GetWidth() const { return width_minus_1 + 1; }
    uint32_t GetHeight() const { return height_minus_1 + 1; }
    uint32_t GetDepthOrArraySize() const { return depth_or_array_size_minus_1 + 1; }

    texture_util::TextureGuestLayout GetGuestLayout() const {
      return texture_util::GetGuestTextureLayout(dimension, pitch, GetWidth(), GetHeight(),
                                                 GetDepthOrArraySize(), tiled, format, packed_mips,
                                                 base_page != 0, mip_max_level);
    }

    static const char* GetLogDimensionName(xenos::DataDimension dimension);
    const char* GetLogDimensionName() const { return GetLogDimensionName(dimension); }
    void LogAction(const char* action) const;
  };

  class Texture {
   public:
    Texture(const Texture& texture) = delete;
    Texture& operator=(const Texture& texture) = delete;
    virtual ~Texture();

    TextureCache& texture_cache() const { return texture_cache_; }

    const TextureKey& key() const { return key_; }

    const texture_util::TextureGuestLayout& guest_layout() const { return guest_layout_; }
    uint32_t GetGuestBaseSize() const { return guest_layout().base.level_data_extent_bytes; }
    uint32_t GetGuestMipsSize() const { return guest_layout().mips_total_extent_bytes; }

    bool force_load_3d_tiling() const { return force_load_3d_tiling_; }
    void SetForceLoad3DTiling(bool force) { force_load_3d_tiling_ = force; }

    uint64_t GetHostMemoryUsage() const { return host_memory_usage_; }

    uint64_t last_usage_submission_index() const { return last_usage_submission_index_; }
    uint64_t last_usage_time() const { return last_usage_time_; }
    static constexpr uint32_t kOutdatedBitBase = UINT32_C(1) << 0;
    static constexpr uint32_t kOutdatedBitMips = UINT32_C(1) << 1;
    uint32_t outdated_mask() const { return outdated_mask_.load(std::memory_order_acquire); }

    bool base_outdated(const std::unique_lock<std::recursive_mutex>& global_lock) const {
      return base_outdated_;
    }
    bool mips_outdated(const std::unique_lock<std::recursive_mutex>& global_lock) const {
      return mips_outdated_;
    }
    void MakeUpToDateAndWatch(const std::unique_lock<std::recursive_mutex>& global_lock);

    void WatchCallback(const std::unique_lock<std::recursive_mutex>& global_lock, bool is_mip);

    void MarkAsUsed();

    void LogAction(const char* action) const;

   protected:
    explicit Texture(TextureCache& texture_cache, const TextureKey& key, bool track_usage = true);

    void SetHostMemoryUsage(uint64_t new_host_memory_usage) {
      texture_cache_.UpdateTexturesTotalHostMemoryUsage(new_host_memory_usage, host_memory_usage_);
      host_memory_usage_ = new_host_memory_usage;
    }

   private:
    TextureCache& texture_cache_;

    TextureKey key_;

    texture_util::TextureGuestLayout guest_layout_;

    uint64_t host_memory_usage_ = 0;

    uint64_t last_usage_submission_index_;
    uint64_t last_usage_time_;
    Texture* used_previous_;
    Texture* used_next_;
    bool in_usage_list_;
    bool force_load_3d_tiling_ = false;

    bool base_outdated_ = false;

    bool mips_outdated_ = false;
    std::atomic<uint32_t> outdated_mask_{0};

    SharedMemory::WatchHandle base_watch_handle_ = nullptr;
    SharedMemory::WatchHandle mips_watch_handle_ = nullptr;
  };

  struct LoadConstants {
    uint32_t is_tiled_3d_endian_scale;

    uint32_t guest_offset;

    uint32_t guest_pitch_aligned;

    uint32_t guest_z_stride_block_rows_aligned;

    uint32_t size_blocks[3];

    uint32_t host_offset;

    uint32_t host_pitch;
    uint32_t height_texels;
  };

  static constexpr uint32_t kLoadGuestXThreadsPerGroupLog2 = 2;
  static constexpr uint32_t kLoadGuestYBlocksPerGroupLog2 = 5;

  enum LoadShaderIndex {
    kLoadShaderIndex8bpb,
    kLoadShaderIndex16bpb,
    kLoadShaderIndex32bpb,
    kLoadShaderIndex64bpb,
    kLoadShaderIndex128bpb,
    kLoadShaderIndexR5G5B5A1ToB5G5R5A1,
    kLoadShaderIndexR5G6B5ToB5G6R5,
    kLoadShaderIndexR5G6B5ToRGBA8,
    kLoadShaderIndexR5G5B6ToB5G6R5WithRBGASwizzle,
    kLoadShaderIndexRGBA4ToBGRA4,
    kLoadShaderIndexRGBA4ToARGB4,
    kLoadShaderIndexRGBA4ToRGBA8,
    kLoadShaderIndexGBGR8ToGRGB8,
    kLoadShaderIndexGBGR8ToRGB8,
    kLoadShaderIndexBGRG8ToRGBG8,
    kLoadShaderIndexBGRG8ToRGB8,
    kLoadShaderIndexR10G11B11ToRGBA16,
    kLoadShaderIndexR10G11B11ToRGBA16SNorm,
    kLoadShaderIndexR11G11B10ToRGBA16,
    kLoadShaderIndexR11G11B10ToRGBA16SNorm,
    kLoadShaderIndexR16UNormToFloat,
    kLoadShaderIndexR16SNormToFloat,
    kLoadShaderIndexRG16UNormToFloat,
    kLoadShaderIndexRG16SNormToFloat,
    kLoadShaderIndexRGBA16UNormToFloat,
    kLoadShaderIndexRGBA16SNormToFloat,
    kLoadShaderIndexDXT1ToRGBA8,
    kLoadShaderIndexDXT3ToRGBA8,
    kLoadShaderIndexDXT5ToRGBA8,
    kLoadShaderIndexDXNToRG8,
    kLoadShaderIndexDXT3A,
    kLoadShaderIndexDXT3AAs1111ToBGRA4,
    kLoadShaderIndexDXT3AAs1111ToARGB4,
    kLoadShaderIndexDXT5AToR8,
    kLoadShaderIndexCTX1,
    kLoadShaderIndexDepthUnorm,
    kLoadShaderIndexDepthFloat,

    kLoadShaderCount,
    kLoadShaderIndexUnknown = kLoadShaderCount,
  };

  struct LoadShaderInfo {
    uint32_t source_bpe_log2;
    uint32_t dest_bpe_log2;

    uint32_t bytes_per_host_block;

    uint32_t guest_x_blocks_per_thread_log2;

    uint32_t GetGuestXBlocksPerGroupLog2() const {
      return kLoadGuestXThreadsPerGroupLog2 + guest_x_blocks_per_thread_log2;
    }
  };

  static constexpr uint8_t kSwizzledSignsUnsigned =
      uint8_t(xenos::TextureSign::kUnsigned) * uint8_t(0b01010101);

  struct TextureBinding {
    TextureKey key;

    uint32_t integer_scale_bits;

    uint32_t host_swizzle;

    uint8_t swizzled_signs;

    Texture* texture;

    Texture* texture_signed;

    TextureBinding() { Reset(); }

    void Reset() {
      std::memset(this, 0, sizeof(*this));
      host_swizzle = xenos::XE_GPU_TEXTURE_SWIZZLE_0000;
      swizzled_signs = kSwizzledSignsUnsigned;
    }
  };

  explicit TextureCache(const RegisterFile& register_file, SharedMemory& shared_memory,
                        uint32_t draw_resolution_scale_x, uint32_t draw_resolution_scale_y);

  const RegisterFile& register_file() const { return register_file_; }
  SharedMemory& shared_memory() const { return shared_memory_; }

  void DestroyAllTextures(bool from_destructor = false);

  virtual bool IsSignedVersionSeparateForFormat(TextureKey) const { return false; }

  virtual bool IsScaledResolveSupportedForFormat(TextureKey) const { return false; }

  virtual uint32_t GetHostFormatSwizzle(TextureKey key) const = 0;

  virtual uint32_t GetMaxHostTextureWidthHeight(xenos::DataDimension dimension) const = 0;
  virtual uint32_t GetMaxHostTextureDepthOrArraySize(xenos::DataDimension dimension) const = 0;

  virtual std::unique_ptr<Texture> CreateTexture(TextureKey key) = 0;

  Texture* FindOrCreateTexture(TextureKey key);

  static const LoadShaderInfo& GetLoadShaderInfo(LoadShaderIndex load_shader_index) {
    assert_true(load_shader_index < kLoadShaderCount);
    return load_shader_info_[load_shader_index];
  }
  bool LoadTextureData(Texture& texture);

  virtual bool LoadTextureDataFromResidentMemoryImpl(Texture& texture, bool load_base,
                                                     bool load_mips) = 0;

  static void BindingInfoFromFetchConstant(const xenos::xe_gpu_texture_fetch_t& fetch,
                                           TextureKey& key_out, uint8_t* swizzled_signs_out);

  void ResetTextureBindings(bool from_destructor = false);

  const TextureBinding* GetValidTextureBinding(uint32_t fetch_constant_index) const {
    const TextureBinding& binding = texture_bindings_[fetch_constant_index];
    return binding.key.is_valid ? &binding : nullptr;
  }

  virtual void UpdateTextureBindingsImpl(uint32_t) {}

 private:
  struct PendingTextureLoad {
    Texture* texture = nullptr;
    bool load_base = false;
    bool load_mips = false;
  };
  struct PendingSharedMemoryRange {
    uint32_t start = 0;
    uint32_t length = 0;
  };
  bool PrepareTextureLoad(Texture& texture, PendingTextureLoad& pending_load_out,
                          PendingSharedMemoryRange* pending_ranges_out,
                          size_t& pending_range_count_out);
  bool CommitPreparedTextureLoad(const PendingTextureLoad& pending_load);

  void UpdateTexturesTotalHostMemoryUsage(uint64_t add, uint64_t subtract);

  static void WatchCallback(const std::unique_lock<std::recursive_mutex>& global_lock,
                            void* context, void* data, uint64_t argument, bool invalidated_by_gpu);

  bool IsRangeScaledResolved(uint32_t start_unscaled, uint32_t length_unscaled);

  static void ScaledResolveGlobalWatchCallbackThunk(
      const std::unique_lock<std::recursive_mutex>& global_lock, void* context,
      uint32_t address_first, uint32_t address_last, bool invalidated_by_gpu);
  void ScaledResolveGlobalWatchCallback(const std::unique_lock<std::recursive_mutex>& global_lock,
                                        uint32_t address_first, uint32_t address_last,
                                        bool invalidated_by_gpu);

  const RegisterFile& register_file_;
  SharedMemory& shared_memory_;
  uint32_t draw_resolution_scale_x_;
  uint32_t draw_resolution_scale_y_;

  static const LoadShaderInfo load_shader_info_[kLoadShaderCount];

  rex::thread::global_critical_region global_critical_region_;

  std::unique_ptr<uint32_t[]> scaled_resolve_pages_;

  uint64_t scaled_resolve_pages_l2_[SharedMemory::kBufferSize >> (12 + 5 + 6)];

  SharedMemory::GlobalWatchHandle scaled_resolve_global_watch_handle_ = nullptr;

  uint64_t current_submission_index_ = 0;
  uint64_t current_submission_time_ = 0;

  std::unordered_map<TextureKey, std::unique_ptr<Texture>, TextureKey::Hasher> textures_;

  uint64_t textures_total_host_memory_usage_ = 0;

  Texture* texture_used_first_ = nullptr;
  Texture* texture_used_last_ = nullptr;

  std::atomic<bool> texture_became_outdated_{false};

  std::array<TextureBinding, xenos::kTextureFetchConstantCount> texture_bindings_;

  uint32_t texture_bindings_in_sync_ = 0;
};

}
