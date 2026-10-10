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

#include <algorithm>

#include <rex/graphics/pipeline/texture/info.h>
#include <rex/graphics/xenos.h>
#include <rex/math.h>

namespace rex::graphics::texture_util {

void GetSubresourcesFromFetchConstant(const xenos::xe_gpu_texture_fetch_t& fetch,
                                      uint32_t* width_minus_1_out, uint32_t* height_minus_1_out,
                                      uint32_t* depth_or_array_size_minus_1_out,
                                      uint32_t* base_page_out, uint32_t* mip_page_out,
                                      uint32_t* mip_min_level_out, uint32_t* mip_max_level_out);

inline uint32_t GetPackedMipLevel(uint32_t width, uint32_t height) {
  uint32_t log2_size = rex::log2_ceil(std::min(width, height));
  return log2_size > 4 ? log2_size - 4 : 0;
}

bool GetPackedMipOffset(uint32_t width, uint32_t height, uint32_t depth,
                        xenos::TextureFormat format, uint32_t mip, uint32_t& x_blocks,
                        uint32_t& y_blocks, uint32_t& z_blocks);

struct TextureGuestLayout {
  struct Level {
    uint32_t row_pitch_bytes;

    uint32_t z_slice_stride_block_rows;

    uint32_t array_slice_stride_bytes;

    uint32_t x_extent_blocks;
    uint32_t y_extent_blocks;
    uint32_t z_extent;

    uint32_t array_slice_data_extent_bytes;

    uint32_t level_data_extent_bytes;
  };

  Level base;

  Level mips[xenos::kTextureMaxMips];
  uint32_t mip_offsets_bytes[xenos::kTextureMaxMips];
  uint32_t mips_total_extent_bytes;
  uint32_t max_level;

  uint32_t packed_level;
  uint32_t array_size;
};

TextureGuestLayout GetGuestTextureLayout(xenos::DataDimension dimension,
                                         uint32_t base_pitch_texels_div_32, uint32_t width_texels,
                                         uint32_t height_texels, uint32_t depth_or_array_size,
                                         bool is_tiled, xenos::TextureFormat format,
                                         bool has_packed_levels, bool has_base, uint32_t max_level);

void GetTextureTotalSize(xenos::DataDimension dimension, uint32_t base_pitch_texels_div_32,
                         uint32_t width_texels, uint32_t height_texels,
                         uint32_t depth_or_array_size, bool is_tiled, xenos::TextureFormat format,
                         uint32_t mip_max_level, bool has_packed_mips, uint32_t* base_size_out,
                         uint32_t* mip_size_out);

int32_t GetTiledOffset2D(int32_t x, int32_t y, uint32_t pitch, uint32_t bytes_per_block_log2);
int32_t GetTiledOffset3D(int32_t x, int32_t y, int32_t z, uint32_t pitch, uint32_t height,
                         uint32_t bytes_per_block_log2);

inline uint32_t GetTiledAddressLowerBound2D(uint32_t left, uint32_t top, uint32_t pitch,
                                            uint32_t bytes_per_block_log2) {
  return uint32_t(GetTiledOffset2D(int32_t(left & ~(xenos::kTextureTileWidthHeight - 1)),
                                   int32_t(top & ~(xenos::kTextureTileWidthHeight - 1)), pitch,
                                   bytes_per_block_log2));
}
inline uint32_t GetTiledAddressLowerBound3D(uint32_t left, uint32_t top, uint32_t front,
                                            uint32_t pitch, uint32_t height,
                                            uint32_t bytes_per_block_log2) {
  uint32_t front_aligned = front & ~(xenos::kTextureTileDepth - 1);
  uint32_t top_aligned = top & ~(xenos::kTextureTileWidthHeight - 1);
  if (front_aligned & xenos::kTextureTileDepth) {
    top_aligned += 8;
  }
  return uint32_t(GetTiledOffset3D(int32_t(left & ~(xenos::kTextureTileWidthHeight - 1)),
                                   int32_t(top_aligned), int32_t(front_aligned), pitch, height,
                                   bytes_per_block_log2));
}

uint32_t GetTiledAddressUpperBound2D(uint32_t right, uint32_t bottom, uint32_t pitch,
                                     uint32_t bytes_per_block_log2);
uint32_t GetTiledAddressUpperBound3D(uint32_t right, uint32_t bottom, uint32_t back, uint32_t pitch,
                                     uint32_t height, uint32_t bytes_per_block_log2);

uint8_t SwizzleSigns(const xenos::xe_gpu_texture_fetch_t& fetch);
constexpr bool IsAnySignNotSigned(uint8_t packed_signs) {
  return packed_signs != uint32_t(xenos::TextureSign::kSigned) * 0b01010101;
}
constexpr bool IsAnySignSigned(uint8_t packed_signs) {
  uint32_t xor_signed = packed_signs ^ (uint32_t(xenos::TextureSign::kSigned) * 0b01010101);
  return ((xor_signed | (xor_signed >> 1)) & 0b01010101) != 0b01010101;
}

constexpr bool IsSignedViewBound(uint8_t packed_signs, bool is_signed) {
  return is_signed || !IsAnySignNotSigned(packed_signs);
}

void GetClampModesForDimension(const xenos::xe_gpu_texture_fetch_t& fetch,
                               xenos::ClampMode& clamp_x_out, xenos::ClampMode& clamp_y_out,
                               xenos::ClampMode& clamp_z_out);

uint32_t GetIntegerScaleBits(const xenos::xe_gpu_texture_fetch_t& fetch, uint8_t swizzled_signs);

struct Wide1DTextureLayout {
  uint32_t row_width;
  uint32_t row_count;
};

constexpr Wide1DTextureLayout GetWide1DTextureLayout(uint32_t width) {
  const uint32_t row_width = xenos::kTexture2DCubeMaxWidthHeight;
  return {row_width, std::min((width + row_width - 1) / row_width, xenos::kTexture1DWideMaxRows)};
}

}
