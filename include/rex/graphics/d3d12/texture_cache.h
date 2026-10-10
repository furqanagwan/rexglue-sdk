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

#pragma once

#include <array>
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include <rex/assert.h>
#include <rex/graphics/d3d12/shader.h>
#include <rex/graphics/d3d12/shared_memory.h>
#include <rex/graphics/pipeline/texture/cache.h>
#include <rex/graphics/pipeline/texture/util.h>
#include <rex/graphics/register_file.h>
#include <rex/graphics/xenos.h>
#include <rex/ui/d3d12/d3d12_api.h>
#include <rex/ui/d3d12/d3d12_provider.h>

namespace rex::graphics::d3d12 {

class D3D12CommandProcessor;

class D3D12TextureCache final : public TextureCache {
 public:
  struct TextureSRVKey {
    TextureKey key;
    uint32_t host_swizzle;
    uint8_t swizzled_signs;
  };

  union SamplerParameters {
    uint32_t value;
    struct {
      xenos::ClampMode clamp_x : 3;
      xenos::ClampMode clamp_y : 3;
      xenos::ClampMode clamp_z : 3;
      xenos::BorderColor border_color : 2;

      uint32_t mag_linear : 1;
      uint32_t min_linear : 1;
      uint32_t mip_linear : 1;
      xenos::AnisoFilter aniso_filter : 3;
      uint32_t mip_min_level : 4;
      uint32_t mip_base_map : 1;
    };

    SamplerParameters() : value(0) { static_assert_size(*this, sizeof(value)); }
    bool operator==(const SamplerParameters& parameters) const { return value == parameters.value; }
    bool operator!=(const SamplerParameters& parameters) const { return value != parameters.value; }
  };

  static std::unique_ptr<D3D12TextureCache> Create(const RegisterFile& register_file,
                                                   D3D12SharedMemory& shared_memory,
                                                   uint32_t draw_resolution_scale_x,
                                                   uint32_t draw_resolution_scale_y,
                                                   D3D12CommandProcessor& command_processor,
                                                   bool bindless_resources_used) {
    std::unique_ptr<D3D12TextureCache> texture_cache(
        new D3D12TextureCache(register_file, shared_memory, draw_resolution_scale_x,
                              draw_resolution_scale_y, command_processor, bindless_resources_used));
    if (!texture_cache->Initialize()) {
      return nullptr;
    }
    return std::move(texture_cache);
  }

  ~D3D12TextureCache();

  void ClearCache() override;

  void BeginSubmission(uint64_t new_submission_index) override;
  void BeginFrame() override;
  void EndFrame();

  void RequestTextures(uint32_t used_texture_mask) override;

  bool AreActiveTextureSRVKeysUpToDate(const TextureSRVKey* keys,
                                       const D3D12Shader::TextureBinding* host_shader_bindings,
                                       size_t host_shader_binding_count) const;

  void WriteActiveTextureSRVKeys(TextureSRVKey* keys,
                                 const D3D12Shader::TextureBinding* host_shader_bindings,
                                 size_t host_shader_binding_count) const;
  void WriteActiveTextureBindfulSRV(const D3D12Shader::TextureBinding& host_shader_binding,
                                    D3D12_CPU_DESCRIPTOR_HANDLE handle);
  uint32_t GetActiveTextureBindlessSRVIndex(const D3D12Shader::TextureBinding& host_shader_binding);

  SamplerParameters GetSamplerParameters(const D3D12Shader::SamplerBinding& binding) const;
  void WriteSampler(SamplerParameters parameters, D3D12_CPU_DESCRIPTOR_HANDLE handle) const;

  static bool ClampDrawResolutionScaleToMaxSupported(uint32_t& scale_x, uint32_t& scale_y,
                                                     const ui::d3d12::D3D12Provider& provider);

  bool EnsureScaledResolveMemoryCommitted(uint32_t start_unscaled, uint32_t length_unscaled,
                                          uint32_t length_scaled_alignment_log2 = 0) override;

  bool MakeScaledResolveRangeCurrent(uint32_t start_unscaled, uint32_t length_unscaled,
                                     uint32_t length_scaled_alignment_log2 = 0);

  void CreateCurrentScaledResolveRangeUintPow2SRV(D3D12_CPU_DESCRIPTOR_HANDLE handle,
                                                  uint32_t element_size_bytes_pow2);
  void CreateCurrentScaledResolveRangeUintPow2UAV(D3D12_CPU_DESCRIPTOR_HANDLE handle,
                                                  uint32_t element_size_bytes_pow2);
  void TransitionCurrentScaledResolveRange(D3D12_RESOURCE_STATES new_state);
  uint64_t GetCurrentScaledResolveRangeStartScaled() const {
    return scaled_resolve_current_range_start_scaled_;
  }
  uint64_t GetCurrentScaledResolveRangeLengthScaled() const {
    return scaled_resolve_current_range_length_scaled_;
  }
  ID3D12Resource* GetCurrentScaledResolveBufferResource() {
    return GetCurrentScaledResolveBuffer().resource();
  }
  size_t GetCurrentScaledResolveBufferIndexPublic() const {
    return GetCurrentScaledResolveBufferIndex();
  }
  void MarkCurrentScaledResolveRangeUAVWritesCommitNeeded() {
    assert_true(IsDrawResolutionScaled());
    GetCurrentScaledResolveBuffer().SetUAVBarrierPending();
  }

  ID3D12Resource* RequestSwapTexture(D3D12_SHADER_RESOURCE_VIEW_DESC& srv_desc_out,
                                     xenos::TextureFormat& format_out,
                                     uint32_t* width_unscaled_out = nullptr,
                                     uint32_t* height_unscaled_out = nullptr);

 protected:
  bool IsSignedVersionSeparateForFormat(TextureKey key) const override;
  bool IsScaledResolveSupportedForFormat(TextureKey key) const override;
  uint32_t GetHostFormatSwizzle(TextureKey key) const override;

  uint32_t GetMaxHostTextureWidthHeight(xenos::DataDimension dimension) const override;
  uint32_t GetMaxHostTextureDepthOrArraySize(xenos::DataDimension dimension) const override;

  std::unique_ptr<Texture> CreateTexture(TextureKey key) override;

  bool LoadTextureDataFromResidentMemoryImpl(Texture& texture, bool load_base,
                                             bool load_mips) override;

  void UpdateTextureBindingsImpl(uint32_t fetch_constant_mask) override;

 private:
  static constexpr uint32_t kLoadGuestXThreadsPerGroupLog2 = 2;
  static constexpr uint32_t kLoadGuestYBlocksPerGroupLog2 = 5;

  struct HostFormat {
    DXGI_FORMAT dxgi_format_resource;

    DXGI_FORMAT dxgi_format_unsigned;

    LoadShaderIndex load_shader;

    DXGI_FORMAT dxgi_format_signed;

    LoadShaderIndex load_shader_signed;

    bool is_block_compressed;

    DXGI_FORMAT dxgi_format_uncompressed;
    LoadShaderIndex load_shader_decompress;

    uint32_t swizzle;
  };

  class D3D12Texture final : public Texture {
   public:
    union SRVDescriptorKey {
      uint32_t key;
      struct {
        uint32_t is_signed : 1;
        uint32_t host_swizzle : 12;
        uint32_t dimension : 2;
      };

      SRVDescriptorKey() : key(0) { static_assert_size(*this, sizeof(key)); }

      struct Hasher {
        size_t operator()(const SRVDescriptorKey& key) const {
          return std::hash<decltype(key.key)>{}(key.key);
        }
      };
      bool operator==(const SRVDescriptorKey& other_key) const { return key == other_key.key; }
      bool operator!=(const SRVDescriptorKey& other_key) const { return !(*this == other_key); }
    };

    ID3D12Resource* GetOrCreate3DAs2DResource(D3D12_RESOURCE_STATES end_state);

    explicit D3D12Texture(D3D12TextureCache& texture_cache, const TextureKey& key,
                          ID3D12Resource* resource, D3D12_RESOURCE_STATES resource_state,
                          bool track_usage = true);
    ~D3D12Texture();

    ID3D12Resource* resource() const { return resource_.Get(); }

    D3D12_RESOURCE_STATES SetResourceState(D3D12_RESOURCE_STATES new_state) {
      D3D12_RESOURCE_STATES old_state = resource_state_;
      resource_state_ = new_state;
      return old_state;
    }

    uint32_t GetSRVDescriptorIndex(SRVDescriptorKey descriptor_key) const {
      auto it = srv_descriptors_.find(descriptor_key);
      return it != srv_descriptors_.cend() ? it->second : UINT32_MAX;
    }

    void AddSRVDescriptorIndex(SRVDescriptorKey descriptor_key, uint32_t descriptor_index) {
      srv_descriptors_.emplace(descriptor_key, descriptor_index);
    }

   private:
    Microsoft::WRL::ComPtr<ID3D12Resource> resource_;
    D3D12_RESOURCE_STATES resource_state_;
    std::unique_ptr<D3D12Texture> texture_3d_as_2d_;

    std::unordered_map<SRVDescriptorKey, uint32_t, SRVDescriptorKey::Hasher> srv_descriptors_;
  };

  static constexpr uint32_t kSRVDescriptorCachePageSize = 65536;

  struct SRVDescriptorCachePage {
   public:
    explicit SRVDescriptorCachePage(ID3D12DescriptorHeap* heap)
        : heap_(heap), heap_start_(heap->GetCPUDescriptorHandleForHeapStart()) {}
    SRVDescriptorCachePage(const SRVDescriptorCachePage& page) = delete;
    SRVDescriptorCachePage& operator=(const SRVDescriptorCachePage& page) = delete;
    SRVDescriptorCachePage(SRVDescriptorCachePage&& page) {
      std::swap(heap_, page.heap_);
      std::swap(heap_start_, page.heap_start_);
    }
    SRVDescriptorCachePage& operator=(SRVDescriptorCachePage&& page) {
      std::swap(heap_, page.heap_);
      std::swap(heap_start_, page.heap_start_);
      return *this;
    }

    ID3D12DescriptorHeap* heap() const { return heap_.Get(); }
    D3D12_CPU_DESCRIPTOR_HANDLE heap_start() const { return heap_start_; }

   private:
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap_;
    D3D12_CPU_DESCRIPTOR_HANDLE heap_start_;
  };

  struct D3D12TextureBinding {
    uint32_t descriptor_index;
    uint32_t descriptor_index_signed;

    D3D12TextureBinding() { Reset(); }

    void Reset() {
      descriptor_index = UINT32_MAX;
      descriptor_index_signed = UINT32_MAX;
    }
  };

  class ScaledResolveVirtualBuffer {
   public:
    explicit ScaledResolveVirtualBuffer(ID3D12Resource* resource,
                                        D3D12_RESOURCE_STATES resource_state)
        : resource_(resource), resource_state_(resource_state) {}
    ID3D12Resource* resource() const { return resource_.Get(); }
    D3D12_RESOURCE_STATES SetResourceState(D3D12_RESOURCE_STATES new_state) {
      D3D12_RESOURCE_STATES old_state = resource_state_;
      if (old_state == D3D12_RESOURCE_STATE_UNORDERED_ACCESS) {
        uav_barrier_pending_ = false;
      }
      resource_state_ = new_state;
      return old_state;
    }

    void SetUAVBarrierPending() {
      if (resource_state_ == D3D12_RESOURCE_STATE_UNORDERED_ACCESS) {
        uav_barrier_pending_ = true;
      }
    }

    void ClearUAVBarrierPending() { uav_barrier_pending_ = false; }

   private:
    Microsoft::WRL::ComPtr<ID3D12Resource> resource_;
    D3D12_RESOURCE_STATES resource_state_;
    bool uav_barrier_pending_ = false;
  };

  explicit D3D12TextureCache(const RegisterFile& register_file, D3D12SharedMemory& shared_memory,
                             uint32_t draw_resolution_scale_x, uint32_t draw_resolution_scale_y,
                             D3D12CommandProcessor& command_processor,
                             bool bindless_resources_used);

  bool Initialize();

  bool IsDecompressionNeeded(xenos::TextureFormat format, uint32_t width, uint32_t height) const;
  DXGI_FORMAT GetDXGIResourceFormat(xenos::TextureFormat format, uint32_t width,
                                    uint32_t height) const {
    const HostFormat& host_format = host_formats_[uint32_t(format)];
    return IsDecompressionNeeded(format, width, height) ? host_format.dxgi_format_uncompressed
                                                        : host_format.dxgi_format_resource;
  }
  DXGI_FORMAT GetDXGIResourceFormat(TextureKey key) const {
    return GetDXGIResourceFormat(key.format, key.GetWidth(), key.GetHeight());
  }
  DXGI_FORMAT GetDXGIUnormFormat(xenos::TextureFormat format, uint32_t width,
                                 uint32_t height) const {
    const HostFormat& host_format = host_formats_[uint32_t(format)];
    return IsDecompressionNeeded(format, width, height) ? host_format.dxgi_format_uncompressed
                                                        : host_format.dxgi_format_unsigned;
  }
  DXGI_FORMAT GetDXGIUnormFormat(TextureKey key) const {
    return GetDXGIUnormFormat(key.format, key.GetWidth(), key.GetHeight());
  }

  LoadShaderIndex GetLoadShaderIndex(TextureKey key) const;

  static constexpr bool AreDimensionsCompatible(xenos::FetchOpDimension binding_dimension,
                                                xenos::DataDimension resource_dimension) {
    switch (binding_dimension) {
      case xenos::FetchOpDimension::k1D:
      case xenos::FetchOpDimension::k2D:
        return resource_dimension == xenos::DataDimension::k1D ||
               resource_dimension == xenos::DataDimension::k2DOrStacked ||
               resource_dimension == xenos::DataDimension::k3D;
      case xenos::FetchOpDimension::k3DOrStacked:
        return resource_dimension == xenos::DataDimension::k3D;
      case xenos::FetchOpDimension::kCube:
        return resource_dimension == xenos::DataDimension::kCube;
      default:
        return false;
    }
  }

  uint32_t FindOrCreateTextureDescriptor(D3D12Texture& texture, xenos::DataDimension dimension,
                                         bool is_signed, uint32_t host_swizzle);
  void ReleaseTextureDescriptor(uint32_t descriptor_index);
  D3D12_CPU_DESCRIPTOR_HANDLE GetTextureDescriptorCPUHandle(uint32_t descriptor_index) const;

  size_t GetScaledResolveBufferCount() const {
    assert_true(IsDrawResolutionScaled());

    uint64_t address_space_size = uint64_t(SharedMemory::kBufferSize) *
                                  (draw_resolution_scale_x() * draw_resolution_scale_y());
    return size_t((address_space_size - 1) >> 30);
  }

  std::array<size_t, 2> GetPossibleScaledResolveBufferIndices(uint64_t address_scaled) const {
    assert_true(IsDrawResolutionScaled());
    size_t address_gb = size_t(address_scaled >> 30);
    size_t max_index = GetScaledResolveBufferCount() - 1;

    return std::array<size_t, 2>{std::min(address_gb, max_index),
                                 std::min(std::max(address_gb, size_t(1)) - size_t(1), max_index)};
  }

  size_t GetCurrentScaledResolveBufferIndex() const {
    return scaled_resolve_1gb_buffer_indices_[scaled_resolve_current_range_start_scaled_ >> 30];
  }
  ScaledResolveVirtualBuffer& GetCurrentScaledResolveBuffer() {
    ScaledResolveVirtualBuffer* scaled_resolve_buffer =
        scaled_resolve_2gb_buffers_[GetCurrentScaledResolveBufferIndex()].get();
    assert_not_null(scaled_resolve_buffer);
    return *scaled_resolve_buffer;
  }

  xenos::ClampMode NormalizeClampMode(xenos::ClampMode clamp_mode) const;

  static const HostFormat host_formats_[64];

  D3D12CommandProcessor& command_processor_;
  bool bindless_resources_used_;

  Microsoft::WRL::ComPtr<ID3D12RootSignature> load_root_signature_;
  std::array<Microsoft::WRL::ComPtr<ID3D12PipelineState>, kLoadShaderCount> load_pipelines_;

  std::array<Microsoft::WRL::ComPtr<ID3D12PipelineState>, kLoadShaderCount> load_pipelines_scaled_;

  std::vector<SRVDescriptorCachePage> srv_descriptor_cache_;
  uint32_t srv_descriptor_cache_allocated_;

  std::vector<uint32_t> srv_descriptor_cache_free_;

  enum class NullSRVDescriptorIndex {
    k2DArray,
    k3D,
    kCube,

    kCount,
  };

  Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> null_srv_descriptor_heap_;
  D3D12_CPU_DESCRIPTOR_HANDLE null_srv_descriptor_heap_start_;

  std::array<D3D12TextureBinding, xenos::kTextureFetchConstantCount> d3d12_texture_bindings_;

  enum : uint8_t {
    kUnsupportedResourceBit = 1,
    kUnsupportedUnormBit = kUnsupportedResourceBit << 1,
    kUnsupportedSnormBit = kUnsupportedUnormBit << 1,
  };
  uint8_t unsupported_format_features_used_[64];

  std::array<std::unique_ptr<ScaledResolveVirtualBuffer>,
             (uint64_t(SharedMemory::kBufferSize) *
                  (kMaxDrawResolutionScaleAlongAxis * kMaxDrawResolutionScaleAlongAxis) -
              1) /
                 (UINT32_C(1) << 30)>
      scaled_resolve_2gb_buffers_;

  static constexpr uint32_t kScaledResolveHeapSizeLog2 = 24;
  static constexpr uint32_t kScaledResolveHeapSize = uint32_t(1) << kScaledResolveHeapSizeLog2;
  static_assert((kScaledResolveHeapSize % D3D12_TILED_RESOURCE_TILE_SIZE_IN_BYTES) == 0,
                "Scaled resolve heap size must be a multiple of Direct3D tile size");
  static_assert(kScaledResolveHeapSizeLog2 <= SharedMemory::kBufferSizeLog2,
                "Scaled resolve heaps are assumed to be wholly mappable irrespective of "
                "resolution scale, never truncated, for example, if the scaled resolve "
                "address space is 4.5 GB, but the heap size is 1 GB");
  static_assert(kScaledResolveHeapSizeLog2 <= 30,
                "Scaled resolve heaps are assumed to only be wholly mappable to up to "
                "two 2 GB buffers");

  std::vector<Microsoft::WRL::ComPtr<ID3D12Heap>> scaled_resolve_heaps_;

  uint32_t scaled_resolve_heap_count_ = 0;

  size_t scaled_resolve_1gb_buffer_indices_[(uint64_t(SharedMemory::kBufferSize) *
                                                 kMaxDrawResolutionScaleAlongAxis *
                                                 kMaxDrawResolutionScaleAlongAxis +
                                             ((uint32_t(1) << 30) - 1)) >>
                                            30];

  uint64_t scaled_resolve_current_range_start_scaled_;
  uint64_t scaled_resolve_current_range_length_scaled_;
};

}
