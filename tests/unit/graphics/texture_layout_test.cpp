/**
 * @file        graphics/texture_layout_test.cpp
 * @brief       Guest texture layout and tiled address bound checks (RG-GDK-008)
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cstdint>

#include <rex/graphics/pipeline/texture/util.h>

namespace {

namespace xenos = rex::graphics::xenos;
namespace texture_util = rex::graphics::texture_util;

texture_util::TextureGuestLayout Layout(xenos::DataDimension dimension, uint32_t width,
                                        uint32_t height, uint32_t depth_or_array_size,
                                        bool is_tiled, xenos::TextureFormat format) {
  return texture_util::GetGuestTextureLayout(dimension, (width + 31) / 32, width, height,
                                             depth_or_array_size, is_tiled, format, false, true, 3);
}

}  // namespace

// Expected offsets follow D3D's FindTextureSize: a mip level of an N-slice 2D
// array is padded to align(N, 4) slices, and a 3D mip's slice count comes from
// the level's own depth, not the base depth. Source: xenia-canary #1243.
TEST_CASE("2D array mips are padded to four slices", "[graphics][texture_layout]") {
  auto layout =
      Layout(xenos::DataDimension::k2DOrStacked, 64, 64, 3, true, xenos::TextureFormat::k_8_8_8_8);
  // Level 1 and 2 are both one 32x32 k_8_8_8_8 tile (4 KB) per slice.
  CHECK(layout.mips[1].array_slice_stride_bytes == 0x1000);
  CHECK(layout.mip_offsets_bytes[1] == 0);
  CHECK(layout.mip_offsets_bytes[2] == 4 * 0x1000);
  CHECK(layout.mip_offsets_bytes[3] == 8 * 0x1000);

  // A single slice isn't an array and a cube keeps its six faces.
  auto single =
      Layout(xenos::DataDimension::k2DOrStacked, 64, 64, 1, true, xenos::TextureFormat::k_8_8_8_8);
  CHECK(single.mip_offsets_bytes[2] == 0x1000);
  auto cube = Layout(xenos::DataDimension::kCube, 64, 64, 6, true, xenos::TextureFormat::k_8_8_8_8);
  CHECK(cube.mip_offsets_bytes[2] == 6 * 0x1000);
}

TEST_CASE("3D mips use their own depth for the slice stride", "[graphics][texture_layout]") {
  auto layout =
      Layout(xenos::DataDimension::k3D, 64, 64, 16, true, xenos::TextureFormat::k_8_8_8_8);
  // Level 1 is 32x32x8, level 2 is 16x16x4 padded to 32x32x4.
  CHECK(layout.mips[1].array_slice_stride_bytes == 8 * 0x1000);
  CHECK(layout.mips[2].array_slice_stride_bytes == 4 * 0x1000);
  CHECK(layout.mip_offsets_bytes[2] == 8 * 0x1000);
  CHECK(layout.mip_offsets_bytes[3] == 12 * 0x1000);
}

TEST_CASE("Linear mip rows align to max(256 / block size, 32) blocks",
          "[graphics][texture_layout]") {
  // 96bpp: 256 / 12 < 32, so a 32 texel row is 32 * 12 bytes, not 512.
  auto rgb32f = Layout(xenos::DataDimension::k2DOrStacked, 64, 64, 1, false,
                       xenos::TextureFormat::k_32_32_32_FLOAT);
  CHECK(rgb32f.mips[1].row_pitch_bytes == 32 * 12);
  CHECK(rgb32f.mips[2].row_pitch_bytes == 32 * 12);
  // 8bpp and 32bpp still pad to 256 bytes, 128bpp to 32 blocks.
  auto r8 = Layout(xenos::DataDimension::k2DOrStacked, 64, 64, 1, false, xenos::TextureFormat::k_8);
  CHECK(r8.mips[1].row_pitch_bytes == 256);
  auto rgba8 =
      Layout(xenos::DataDimension::k2DOrStacked, 64, 64, 1, false, xenos::TextureFormat::k_8_8_8_8);
  CHECK(rgba8.mips[1].row_pitch_bytes == 256);
  auto rgba32f = Layout(xenos::DataDimension::k2DOrStacked, 64, 64, 1, false,
                        xenos::TextureFormat::k_32_32_32_32_FLOAT);
  CHECK(rgba32f.mips[1].row_pitch_bytes == 32 * 16);
}

TEST_CASE("Packed 3D 1x1 mips stack along Z from the level", "[graphics][texture_layout]") {
  // 32x32x256: level 6 is 1x1x4 in the packed tail. D3D places it at
  // Z = (log2(depth) - level) * 4 = 8.
  uint32_t x, y, z;
  REQUIRE(
      texture_util::GetPackedMipOffset(32, 32, 256, xenos::TextureFormat::k_8_8_8_8, 6, x, y, z));
  CHECK(z == 8);
}

// Independent oracle: every texel's address comes from the per-texel tiling
// function, and the bounds must contain all of them.
TEST_CASE("Tiled address bounds contain every texel", "[graphics][texture_layout]") {
  uint32_t failures = 0;
  for (uint32_t bpp_log2 = 0; bpp_log2 <= 2; ++bpp_log2) {
    for (uint32_t pitch : {32u, 64u, 96u}) {
      constexpr uint32_t kHeight = 64;
      for (uint32_t left : {0u, 32u}) {
        for (uint32_t width : {1u, 32u}) {
          if (left + width > pitch) {
            continue;
          }
          for (uint32_t top : {0u, 8u, 32u}) {
            for (uint32_t height : {1u, 32u}) {
              uint32_t right = left + width, bottom = top + height;
              // 2D.
              int64_t min2d = INT64_MAX, max2d = INT64_MIN;
              for (uint32_t y = top; y < bottom; ++y) {
                for (uint32_t x = left; x < right; ++x) {
                  int64_t offset =
                      texture_util::GetTiledOffset2D(int32_t(x), int32_t(y), pitch, bpp_log2);
                  min2d = std::min(min2d, offset);
                  max2d = std::max(max2d, offset);
                }
              }
              if (texture_util::GetTiledAddressLowerBound2D(left, top, pitch, bpp_log2) > min2d ||
                  texture_util::GetTiledAddressUpperBound2D(right, bottom, pitch, bpp_log2) <
                      max2d + (int64_t(1) << bpp_log2)) {
                UNSCOPED_INFO("2D bpp_log2 " << bpp_log2 << " pitch " << pitch << " [" << left
                                             << "," << top << ")-(" << right << "," << bottom
                                             << ")");
                ++failures;
              }
              // 3D, including the odd Z/4 groups.
              for (uint32_t front : {0u, 1u, 4u, 5u, 8u}) {
                for (uint32_t depth : {1u, 4u}) {
                  uint32_t back = front + depth;
                  int64_t min3d = INT64_MAX, max3d = INT64_MIN;
                  for (uint32_t z = front; z < back; ++z) {
                    for (uint32_t y = top; y < bottom; ++y) {
                      for (uint32_t x = left; x < right; ++x) {
                        int64_t offset = texture_util::GetTiledOffset3D(
                            int32_t(x), int32_t(y), int32_t(z), pitch, kHeight, bpp_log2);
                        min3d = std::min(min3d, offset);
                        max3d = std::max(max3d, offset);
                      }
                    }
                  }
                  uint64_t lower3d = texture_util::GetTiledAddressLowerBound3D(
                      left, top, front, pitch, kHeight, bpp_log2);
                  // For a whole 32x32x4 tile the lower bound is also tight.
                  bool whole_tile =
                      !(top & 31) && width == 32 && height == 32 && !(front & 3) && depth == 4;
                  if (lower3d > uint64_t(min3d) || (whole_tile && lower3d != uint64_t(min3d)) ||
                      texture_util::GetTiledAddressUpperBound3D(right, bottom, back, pitch, kHeight,
                                                                bpp_log2) <
                          max3d + (int64_t(1) << bpp_log2)) {
                    UNSCOPED_INFO("3D bpp_log2 " << bpp_log2 << " pitch " << pitch << " [" << left
                                                 << "," << top << "," << front << ")-(" << right
                                                 << "," << bottom << "," << back << ")");
                    ++failures;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  CHECK(failures == 0);
}
