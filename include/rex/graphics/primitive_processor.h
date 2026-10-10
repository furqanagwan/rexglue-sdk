#pragma once
/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2021 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <deque>
#include <functional>
#include <mutex>
#include <unordered_map>
#include <utility>

#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/graphics/pipeline/shader/shader.h>
#include <rex/graphics/register_file.h>
#include <rex/graphics/shared_memory.h>
#include <rex/graphics/xenos.h>
#include <rex/math.h>
#include <rex/memory.h>
#include <rex/platform.h>

#if REX_ARCH_AMD64

#include <tmmintrin.h>
#define XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE 16
#elif REX_ARCH_ARM64
#include <arm_neon.h>
#define XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE 16
#else
#define XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE 0
#endif

REXCVAR_DECLARE(bool, ignore_32bit_vertex_index_support);

namespace rex::graphics {

class PrimitiveProcessor {
 public:
  enum ProcessedIndexBufferType {

    kNone,

    kGuestDMA,

    kHostConverted,

    kHostBuiltinForAuto,

    kHostBuiltinForDMA,
  };

  struct ProcessingResult {
    xenos::PrimitiveType guest_primitive_type;
    xenos::PrimitiveType host_primitive_type;

    Shader::HostVertexShaderType host_vertex_shader_type;

    xenos::TessellationMode tessellation_mode;

    uint32_t guest_draw_vertex_count;
    uint32_t host_draw_vertex_count;
    uint32_t line_loop_closing_index;
    ProcessedIndexBufferType index_buffer_type;
    uint32_t guest_index_base;
    xenos::IndexFormat host_index_format;
    xenos::Endian host_shader_index_endian;

    bool host_primitive_reset_enabled;

    size_t host_index_buffer_handle;
    bool IsTessellated() const {
      return Shader::IsHostVertexShaderTypeDomain(host_vertex_shader_type);
    }
  };

  virtual ~PrimitiveProcessor();

  bool AreFull32BitVertexIndicesUsed() const { return full_32bit_vertex_indices_used_; }
  bool IsConvertingTriangleFansToLists() const { return convert_triangle_fans_to_lists_; }
  bool IsConvertingLineLoopsToStrips() const { return convert_line_loops_to_strips_; }

  bool IsConvertingQuadListsToTriangleLists() const {
    return convert_quad_lists_to_triangle_lists_;
  }
  bool IsExpandingPointSpritesInVS() const { return expand_point_sprites_in_vs_; }
  bool IsExpandingRectangleListsInVS() const { return expand_rectangle_lists_in_vs_; }

  bool Process(ProcessingResult& result_out);

  std::pair<uint32_t, uint32_t> MemoryInvalidationCallback(uint32_t physical_address_start,
                                                           uint32_t length, bool exact_range);

 protected:
  static constexpr uint32_t kMinRequiredConvertedIndexBufferSize =
      sizeof(uint32_t) * (UINT16_MAX - 2) * 3 * +XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE;

  PrimitiveProcessor(const RegisterFile& register_file, memory::Memory& memory,
                     SharedMemory& shared_memory)
      : register_file_(register_file), memory_(memory), shared_memory_(shared_memory) {}

  bool InitializeCommon(bool full_32bit_vertex_indices_supported, bool triangle_fans_supported,
                        bool line_loops_supported, bool quad_lists_supported,
                        bool point_sprites_supported_without_vs_expansion,
                        bool rectangle_lists_supported_without_vs_expansion);

  virtual bool InitializeBuiltinIndexBuffer(size_t size_bytes,
                                            std::function<void(void*)> fill_callback) = 0;

  void ShutdownCommon();

  void ClearPerFrameCache();

  static constexpr size_t GetBuiltinIndexBufferOffsetBytes(size_t handle) { return handle; }

  static ptrdiff_t GetSimdCoalignmentOffset(const void* host_index_ptr, uint32_t guest_index_base) {
#if XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE

    return ptrdiff_t((guest_index_base - reinterpret_cast<uintptr_t>(host_index_ptr)) &
                     (XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE - 1));
#else
    return 0;
#endif
  }

  virtual void* RequestHostConvertedIndexBufferForCurrentFrame(
      xenos::IndexFormat format, uint32_t index_count, bool coalign_for_simd,
      uint32_t coalignment_original_address, size_t& backend_handle_out) = 0;

 private:
#if XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE
#if REX_ARCH_AMD64

  using SimdVectorU16 = __m128i;
  using SimdVectorU32 = __m128i;
  static SimdVectorU16 ReplicateU16(uint16_t value) { return _mm_set1_epi16(int16_t(value)); }
  static SimdVectorU32 ReplicateU32(uint32_t value) { return _mm_set1_epi32(int32_t(value)); }
  static SimdVectorU16 LoadAlignedVectorU16(const uint16_t* source) {
    return _mm_load_si128(reinterpret_cast<const __m128i*>(source));
  }
  static SimdVectorU32 LoadAlignedVectorU32(const uint32_t* source) {
    return _mm_load_si128(reinterpret_cast<const __m128i*>(source));
  }
  static void StoreUnalignedVectorU16(uint16_t* dest, SimdVectorU16 source) {
    _mm_storeu_si128(reinterpret_cast<__m128i*>(dest), source);
  }
  static void StoreUnalignedVectorU32(uint32_t* dest, SimdVectorU32 source) {
    _mm_storeu_si128(reinterpret_cast<__m128i*>(dest), source);
  }
#elif REX_ARCH_ARM64

  using SimdVectorU16 = uint16x8_t;
  using SimdVectorU32 = uint32x4_t;
  static SimdVectorU16 ReplicateU16(uint16_t value) { return vdupq_n_u16(value); }
  static SimdVectorU32 ReplicateU32(uint32_t value) { return vdupq_n_u32(value); }
  static SimdVectorU16 LoadAlignedVectorU16(const uint16_t* source) {
#if REX_COMPILER_MSVC
    return vld1q_u16_ex(source, sizeof(uint16x8_t) * CHAR_BIT);
#else
    return vld1q_u16(
        reinterpret_cast<const uint16_t*>(__builtin_assume_aligned(source, sizeof(uint16x8_t))));
#endif
  }
  static SimdVectorU32 LoadAlignedVectorU32(const uint32_t* source) {
#if REX_COMPILER_MSVC
    return vld1q_u32_ex(source, sizeof(uint16x8_t) * CHAR_BIT);
#else
    return vld1q_u32(
        reinterpret_cast<const uint32_t*>(__builtin_assume_aligned(source, sizeof(uint32x4_t))));
#endif
  }
  static void StoreUnalignedVectorU16(uint16_t* dest, SimdVectorU16 source) {
    vst1q_u16(dest, source);
  }
  static void StoreUnalignedVectorU32(uint32_t* dest, SimdVectorU32 source) {
    vst1q_u32(dest, source);
  }
#else
#error SIMD vector types and constant loads not specified.
#endif
  static_assert(sizeof(SimdVectorU16) == XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE,
                "XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE must reflect the vector size "
                "actually used");
  static_assert(sizeof(SimdVectorU32) == XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE,
                "XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE must reflect the vector size "
                "actually used");
  static constexpr uint32_t kSimdVectorU16Elements = sizeof(SimdVectorU16) / sizeof(uint16_t);
  static constexpr uint32_t kSimdVectorU32Elements = sizeof(SimdVectorU32) / sizeof(uint32_t);
#endif

  static bool IsResetUsed(const uint16_t* source, uint32_t count,
                          uint16_t reset_index_guest_endian);
  static void Get16BitResetIndexUsage(const uint16_t* source, uint32_t count,
                                      uint16_t reset_index_guest_endian,
                                      bool& is_reset_index_used_out,
                                      bool& is_ffff_used_as_vertex_index_out);
  static bool IsResetUsed(const uint32_t* source, uint32_t count, uint32_t reset_index_guest_endian,
                          uint32_t low_bits_mask_guest_endian);
  static void ReplaceResetIndex16To16(uint16_t* dest, const uint16_t* source, uint32_t count,
                                      uint16_t reset_index_guest_endian);

  static void ReplaceResetIndex16To24(uint32_t* dest, const uint16_t* source, uint32_t count,
                                      uint16_t reset_index_guest_endian);

  template <xenos::Endian HostSwap>
  static void ReplaceResetIndex32To24(uint32_t* dest, const uint32_t* source, uint32_t count,
                                      uint32_t reset_index_guest_endian,
                                      uint32_t low_bits_mask_guest_endian) {
#if XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE
    while (count &&
           (reinterpret_cast<uintptr_t>(source) & (XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE - 1))) {
      --count;
      uint32_t index = *(source++) & low_bits_mask_guest_endian;
      *(dest++) = index != reset_index_guest_endian ? xenos::GpuSwap(index, HostSwap) : UINT32_MAX;
    }
    if (count >= kSimdVectorU32Elements) {
      SimdVectorU32 reset_index_guest_endian_simd = ReplicateU32(reset_index_guest_endian);
      SimdVectorU32 low_bits_mask_guest_endian_simd = ReplicateU32(low_bits_mask_guest_endian);
#if REX_ARCH_AMD64
      __m128i host_swap_shuffle;
      if constexpr (HostSwap != xenos::Endian::kNone) {
        host_swap_shuffle = _mm_set_epi32(int32_t(xenos::GpuSwap(uint32_t(0x0F0E0D0C), HostSwap)),
                                          int32_t(xenos::GpuSwap(uint32_t(0x0B0A0908), HostSwap)),
                                          int32_t(xenos::GpuSwap(uint32_t(0x07060504), HostSwap)),
                                          int32_t(xenos::GpuSwap(uint32_t(0x03020100), HostSwap)));
      }
#endif
      while (count >= kSimdVectorU32Elements) {
        count -= kSimdVectorU32Elements;

        SimdVectorU32 source_simd = LoadAlignedVectorU32(source);
        source += kSimdVectorU32Elements;
        SimdVectorU32 result_simd;
#if REX_ARCH_AMD64
        source_simd = _mm_and_si128(source_simd, low_bits_mask_guest_endian_simd);
        result_simd =
            _mm_or_si128(source_simd, _mm_cmpeq_epi32(source_simd, reset_index_guest_endian_simd));
        if constexpr (HostSwap != xenos::Endian::kNone) {
          result_simd = _mm_shuffle_epi8(result_simd, host_swap_shuffle);
        }
#elif REX_ARCH_ARM64
        source_simd = vandq_u32(source_simd, low_bits_mask_guest_endian_simd);
        result_simd = vorrq_u32(source_simd, vceqq_u32(source_simd, reset_index_guest_endian_simd));
        if constexpr (HostSwap == xenos::Endian::k8in16) {
          result_simd = vreinterpretq_u32_u8(vrev16q_u8(vreinterpretq_u8_u32(result_simd)));
        } else if constexpr (HostSwap == xenos::Endian::k8in32) {
          result_simd = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(result_simd)));
        } else if constexpr (HostSwap == xenos::Endian::k16in32) {
          result_simd = vreinterpretq_u32_u16(vrev32q_u16(vreinterpretq_u16_u32(result_simd)));
        }
#else
#error SIMD ReplaceResetIndex32To24 not implemented.
#endif
        StoreUnalignedVectorU32(dest, result_simd);
        dest += kSimdVectorU32Elements;
      }
    }
#endif
    while (count--) {
      uint32_t index = *(source++) & low_bits_mask_guest_endian;
      *(dest++) = index != reset_index_guest_endian ? xenos::GpuSwap(index, HostSwap) : UINT32_MAX;
    }
  }

  struct PassthroughIndexTransform {
    uint16_t operator()(uint16_t index) const { return index; }
    uint32_t operator()(uint32_t index) const { return index; }
  };
  struct To24NonSwappingIndexTransform {
    uint32_t operator()(uint32_t index) const { return index & xenos::kVertexIndexMask; }
  };
  struct To24Swapping8In16IndexTransform {
    uint32_t operator()(uint32_t index) const {
      return xenos::GpuSwap(index, xenos::Endian::k8in16) & xenos::kVertexIndexMask;
    }
  };
  struct To24Swapping8In32IndexTransform {
    uint32_t operator()(uint32_t index) const {
      return xenos::GpuSwap(index, xenos::Endian::k8in32) & xenos::kVertexIndexMask;
    }
  };
  struct To24Swapping16In32IndexTransform {
    uint32_t operator()(uint32_t index) const {
      return xenos::GpuSwap(index, xenos::Endian::k16in32) & xenos::kVertexIndexMask;
    }
  };

  static constexpr uint32_t GetTwoTriangleStripIndexCount(uint32_t strip_count) {
    return 4 * strip_count + (std::max(strip_count, UINT32_C(1)) - 1);
  }

  static constexpr uint32_t GetTriangleFanListIndexCount(uint32_t fan_index_count) {
    return fan_index_count > 2 ? (fan_index_count - 2) * 3 : 0;
  }
  template <typename Index, typename IndexTransform>
  static void TriangleFanToList(Index* dest, const Index* source, uint32_t source_index_count,
                                const IndexTransform& index_transform) {
    if (source_index_count <= 2) {
      return;
    }
    Index index_first = index_transform(source[0]);
    Index index_previous = index_transform(source[1]);
    for (uint32_t i = 2; i < source_index_count; ++i) {
      Index index_current = index_transform(source[i]);
      *(dest++) = index_previous;
      *(dest++) = index_current;
      *(dest++) = index_first;
      index_previous = index_current;
    }
  }

  static constexpr uint32_t GetLineLoopStripIndexCount(uint32_t loop_index_count) {
    return loop_index_count > 1 ? loop_index_count + 1 : 0;
  }
  template <typename Index, typename IndexTransform>
  static void LineLoopToStrip(Index* dest, const Index* source, uint32_t source_index_count,
                              const IndexTransform& index_transform) {
    if (source_index_count <= 1) {
      return;
    }
    Index index_first = index_transform(source[0]);
    dest[0] = index_first;
    for (uint32_t i = 1; i < source_index_count; ++i) {
      dest[i] = index_transform(source[i]);
    }
    dest[source_index_count] = index_first;
  }
  static void LineLoopToStrip(uint16_t* dest, const uint16_t* source, uint32_t source_index_count,
                              const PassthroughIndexTransform& index_transform);
  static void LineLoopToStrip(uint32_t* dest, const uint32_t* source, uint32_t source_index_count,
                              const PassthroughIndexTransform& index_transform);

  static constexpr uint32_t GetQuadListTriangleListIndexCount(uint32_t quad_list_index_count) {
    return (quad_list_index_count / 4) * 6;
  }
  template <typename Index, typename IndexTransform>
  static void QuadListToTriangleList(Index* dest, const Index* source, uint32_t source_index_count,
                                     const IndexTransform& index_transform) {
    uint32_t quad_count = source_index_count / 4;
    for (uint32_t i = 0; i < quad_count; ++i) {
      Index common_index_0 = index_transform(*(source++));
      *(dest++) = common_index_0;
      *(dest++) = index_transform(*(source++));
      Index common_index_2 = index_transform(*(source++));
      *(dest++) = common_index_2;

      *(dest++) = common_index_0;
      *(dest++) = common_index_2;
      *(dest++) = index_transform(*(source++));
    }
  }

  struct SinglePrimitiveRange {
    SinglePrimitiveRange(uint32_t guest_offset, uint32_t guest_index_count,
                         uint32_t host_index_count)
        : guest_offset(guest_offset),
          guest_index_count(guest_index_count),
          host_index_count(host_index_count) {}
    uint32_t guest_offset;
    uint32_t guest_index_count;
    uint32_t host_index_count;
  };
  static uint32_t GetMultiPrimitiveHostIndexCountAndRanges(
      std::function<uint32_t(uint32_t)> single_primitive_guest_to_host_count,
      const uint16_t* source, uint32_t source_index_count, uint16_t reset_index_guest_endian,
      std::deque<SinglePrimitiveRange>& ranges_append_out);
  static uint32_t GetMultiPrimitiveHostIndexCountAndRanges(
      std::function<uint32_t(uint32_t)> single_primitive_guest_to_host_count,
      const uint32_t* source, uint32_t source_index_count, uint32_t reset_index_guest_endian,
      uint32_t low_bits_mask_guest_endian, std::deque<SinglePrimitiveRange>& ranges_append_out);

  template <typename Index, typename IndexTransform, typename PrimitiveRangeIterator>
  static void ConvertSinglePrimitiveRanges(Index* dest, const Index* source,
                                           xenos::PrimitiveType source_primitive_type,
                                           const IndexTransform& index_transform,
                                           PrimitiveRangeIterator ranges_beginning,
                                           PrimitiveRangeIterator ranges_end) {
    Index* dest_write_ptr = dest;
    switch (source_primitive_type) {
      case xenos::PrimitiveType::kTriangleFan:
        for (PrimitiveRangeIterator range_it = ranges_beginning; range_it != ranges_end;
             ++range_it) {
          TriangleFanToList(dest_write_ptr, source + range_it->guest_offset,
                            range_it->guest_index_count, index_transform);
          dest_write_ptr += range_it->host_index_count;
        }
        break;
      case xenos::PrimitiveType::kLineLoop:
        for (PrimitiveRangeIterator range_it = ranges_beginning; range_it != ranges_end;
             ++range_it) {
          LineLoopToStrip(dest_write_ptr, source + range_it->guest_offset,
                          range_it->guest_index_count, index_transform);
          dest_write_ptr += range_it->host_index_count;
        }
        break;
      case xenos::PrimitiveType::kQuadList:
        for (PrimitiveRangeIterator range_it = ranges_beginning; range_it != ranges_end;
             ++range_it) {
          QuadListToTriangleList(dest_write_ptr, source + range_it->guest_offset,
                                 range_it->guest_index_count, index_transform);
          dest_write_ptr += range_it->host_index_count;
        }
        break;
      default:
        assert_unhandled_case(source_primitive_type);
    }
  }

  const RegisterFile& register_file_;
  memory::Memory& memory_;
  SharedMemory& shared_memory_;

  bool full_32bit_vertex_indices_used_ = false;
  bool convert_triangle_fans_to_lists_ = false;
  bool convert_line_loops_to_strips_ = false;
  bool convert_quad_lists_to_triangle_lists_ = false;
  bool expand_point_sprites_in_vs_ = false;
  bool expand_rectangle_lists_in_vs_ = false;

  size_t builtin_ib_offset_two_triangle_strips_ = SIZE_MAX;
  size_t builtin_ib_offset_triangle_fans_to_lists_ = SIZE_MAX;
  size_t builtin_ib_offset_quad_lists_to_triangle_lists_ = SIZE_MAX;

  std::deque<SinglePrimitiveRange> single_primitive_ranges_;

  static constexpr uint32_t kCacheBucketSizeBytesLog2 = 18;
  static constexpr uint32_t kCacheBucketSizeBytes = uint32_t(1) << kCacheBucketSizeBytesLog2;
  static constexpr uint32_t kCacheBucketCount =
      rex::align(SharedMemory::kBufferSize, kCacheBucketSizeBytes) / kCacheBucketSizeBytes;

  union CacheKey {
    uint64_t key;
    struct {
      uint32_t base;
      uint32_t count : 16;
      xenos::IndexFormat format : 1;
      xenos::Endian endian : 2;
      uint32_t is_reset_enabled : 1;

      xenos::PrimitiveType conversion_guest_primitive_type : 6;

      uint32_t non_vertex_32bit_dma_to_24bit : 1;
    };

    CacheKey() : key(0) { static_assert_size(*this, sizeof(key)); }
    CacheKey(uint32_t base, uint32_t count, xenos::IndexFormat format, xenos::Endian endian,
             bool is_reset_enabled,
             xenos::PrimitiveType conversion_guest_primitive_type = xenos::PrimitiveType::kNone,
             bool non_vertex_32bit_dma_to_24bit = false) {
      key = 0;
      this->base = base;
      this->count = count;
      this->format = format;
      this->endian = endian;
      this->is_reset_enabled = is_reset_enabled;
      this->conversion_guest_primitive_type = conversion_guest_primitive_type;
      this->non_vertex_32bit_dma_to_24bit = non_vertex_32bit_dma_to_24bit;
    }

    struct Hasher {
      size_t operator()(const CacheKey& key) const { return std::hash<uint64_t>{}(key.key); }
    };
    bool operator==(const CacheKey& other_key) const { return key == other_key.key; }

    uint32_t GetSizeBytes() const {
      return count * (format == xenos::IndexFormat::kInt16 ? sizeof(uint16_t) : sizeof(uint32_t));
    }
  };

  struct CachedResult {
    uint32_t host_draw_vertex_count;
    ProcessedIndexBufferType index_buffer_type;
    xenos::IndexFormat host_index_format;
    xenos::Endian host_shader_index_endian;
    bool host_primitive_reset_enabled;
    size_t host_index_buffer_handle;
  };

  struct CacheEntry {
    static_assert(UINT16_MAX * sizeof(uint32_t) <= (size_t(1) << kCacheBucketSizeBytesLog2),
                  "Assuming that primitive processor cache entries need to store to the "
                  "previous and to the next entries only within up to 2 buckets, so the "
                  "size of the cache buckets must be not smaller than the maximum guest "
                  "index buffer size");
    union {
      size_t free_next;
      size_t buckets_prev[2];
    };
    size_t buckets_next[2];
    CacheKey key;
    CachedResult result;
    static uint32_t GetBucketCount(CacheKey key) {
      uint32_t count = ((key.base + (key.GetSizeBytes() - 1)) >> kCacheBucketSizeBytesLog2) -
                       (key.base >> kCacheBucketSizeBytesLog2) + 1;
      assert_true(count <= 2, "Cache entries only store list links within two buckets");
      return count;
    }
    uint32_t GetBucketCount() const { return GetBucketCount(key); }
  };

  class CacheTransaction final {
   public:
    CacheTransaction(PrimitiveProcessor& processor, CacheKey key);
    const CachedResult* GetFoundResult() const {
      return result_type_ == ResultType::kExisting ? &result_ : nullptr;
    }
    void SetNewResult(const CachedResult& new_result) {
      assert_true(result_type_ != ResultType::kExisting);
      result_ = new_result;
      result_type_ = ResultType::kNewSet;
    }
    ~CacheTransaction();

   private:
    PrimitiveProcessor& processor_;

    CacheKey key_;
    CachedResult result_;
    enum class ResultType {
      kNewUnset,
      kNewSet,
      kExisting,
    };
    ResultType result_type_ = ResultType::kNewUnset;
  };

  std::deque<CacheEntry> cache_entry_pool_;

  void* memory_invalidation_callback_handle_ = nullptr;

  std::mutex cache_mutex_;

  std::unordered_map<CacheKey, size_t, CacheKey::Hasher> cache_map_;

  uint32_t cache_currently_processing_base_ = 0;

  uint32_t cache_currently_processing_size_bytes_ = 0;

  size_t cache_bucket_free_first_entry_ = SIZE_MAX;

  uint64_t cache_buckets_non_empty_l1_[(kCacheBucketCount + 63) / 64] = {};

  uint64_t cache_buckets_non_empty_l2_[(kCacheBucketCount + (64 * 64 - 1)) / (64 * 64)] = {};

  void UpdateCacheBucketsNonEmptyL2(
      uint32_t bucket_index_div_64,
      [[maybe_unused]] const std::lock_guard<std::mutex>& cache_lock) {
    uint64_t& cache_buckets_non_empty_l2_ref =
        cache_buckets_non_empty_l2_[bucket_index_div_64 >> 6];
    uint64_t cache_buckets_non_empty_l2_bit = uint64_t(1) << (bucket_index_div_64 & 63);
    if (cache_buckets_non_empty_l1_[bucket_index_div_64]) {
      cache_buckets_non_empty_l2_ref |= cache_buckets_non_empty_l2_bit;
    } else {
      cache_buckets_non_empty_l2_ref &= ~cache_buckets_non_empty_l2_bit;
    }
  }

  size_t cache_bucket_first_entries_[kCacheBucketCount];
  static std::pair<uint32_t, uint32_t> MemoryInvalidationCallbackThunk(
      void* context_ptr, uint32_t physical_address_start, uint32_t length, bool exact_range);
};

}
