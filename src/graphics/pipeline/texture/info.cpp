/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2014 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <algorithm>
#include <cmath>
#include <cstring>

#include <rex/graphics/pipeline/texture/info.h>
#include <rex/hash.h>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/memory.h>

namespace rex::graphics {

using namespace rex::graphics::xenos;

bool TextureInfo::Prepare(const xe_gpu_texture_fetch_t& fetch, TextureInfo* out_info) {
  std::memset(out_info, 0, sizeof(TextureInfo));

  auto& info = *out_info;

  info.format = fetch.format;
  info.endianness = fetch.endianness;

  info.dimension = fetch.dimension;
  info.width = info.height = info.depth = 0;
  info.is_stacked = false;
  switch (info.dimension) {
    case xenos::DataDimension::k1D:

      info.dimension = DataDimension::k2DOrStacked;
      info.width = fetch.size_1d.width;
      assert_true(!fetch.stacked);
      break;
    case xenos::DataDimension::k2DOrStacked:
      info.width = fetch.size_2d.width;
      info.height = fetch.size_2d.height;
      if (fetch.stacked) {
        info.depth = fetch.size_2d.stack_depth;
        info.is_stacked = true;
      }
      break;
    case xenos::DataDimension::k3D:
      info.width = fetch.size_3d.width;
      info.height = fetch.size_3d.height;
      info.depth = fetch.size_3d.depth;
      assert_true(!fetch.stacked);
      break;
    case xenos::DataDimension::kCube:
      info.width = fetch.size_2d.width;
      info.height = fetch.size_2d.height;
      assert_true(fetch.size_2d.stack_depth == 5);
      info.depth = fetch.size_2d.stack_depth;
      assert_true(!fetch.stacked);
      break;
    default:
      assert_unhandled_case(info.dimension);
      break;
  }
  info.pitch = fetch.pitch << 5;

  info.mip_min_level = fetch.mip_min_level;
  info.mip_max_level = std::max(uint32_t(fetch.mip_min_level), uint32_t(fetch.mip_max_level));

  info.is_tiled = fetch.tiled;
  info.has_packed_mips = fetch.packed_mips;

  info.extent = TextureExtent::Calculate(out_info, true);
  info.SetupMemoryInfo(fetch.base_address << 12, fetch.mip_address << 12);

  if (info.mip_max_level > 0 && !info.memory.mip_address) {
    info.mip_max_level = 0;
  }

  assert_true(info.mip_min_level <= info.mip_max_level);

  return true;
}

bool TextureInfo::PrepareResolve(uint32_t physical_address, xenos::TextureFormat format,
                                 xenos::Endian endian, uint32_t pitch, uint32_t width,
                                 uint32_t height, uint32_t depth, TextureInfo* out_info) {
  assert_true(width > 0);
  assert_true(height > 0);

  std::memset(out_info, 0, sizeof(TextureInfo));

  auto& info = *out_info;
  info.format = format;
  info.endianness = endian;

  info.dimension = xenos::DataDimension::k2DOrStacked;
  info.width = width - 1;
  info.height = height - 1;
  info.depth = depth - 1;

  info.pitch = pitch;
  info.mip_min_level = 0;
  info.mip_max_level = 0;

  info.is_tiled = true;
  info.has_packed_mips = false;

  info.extent = TextureExtent::Calculate(out_info, true);
  info.SetupMemoryInfo(physical_address, 0);
  return true;
}

uint32_t TextureInfo::GetMaxMipLevels() const {
  return 1 + rex::log2_floor(std::max({width + 1, height + 1, depth + 1}));
}

const TextureExtent TextureInfo::GetMipExtent(uint32_t mip, bool is_guest) const {
  if (mip == 0) {
    return extent;
  }
  uint32_t mip_width, mip_height;
  if (is_guest) {
    mip_width = rex::next_pow2(width + 1) >> mip;
    mip_height = rex::next_pow2(height + 1) >> mip;
  } else {
    mip_width = std::max(1u, (width + 1) >> mip);
    mip_height = std::max(1u, (height + 1) >> mip);
  }
  return TextureExtent::Calculate(format_info(), mip_width, mip_height, depth + 1, is_tiled,
                                  is_guest);
}

void TextureInfo::GetMipSize(uint32_t mip, uint32_t* out_width, uint32_t* out_height) const {
  assert_not_null(out_width);
  assert_not_null(out_height);
  if (mip == 0) {
    *out_width = width + 1;
    *out_height = height + 1;
    return;
  }
  uint32_t width_pow2 = rex::next_pow2(width + 1);
  uint32_t height_pow2 = rex::next_pow2(height + 1);
  *out_width = std::max(width_pow2 >> mip, 1u);
  *out_height = std::max(height_pow2 >> mip, 1u);
}

uint32_t TextureInfo::GetMipLocation(uint32_t mip, uint32_t* offset_x, uint32_t* offset_y,
                                     bool is_guest) const {
  if (mip == 0) {
    if (!has_packed_mips) {
      *offset_x = 0;
      *offset_y = 0;
    } else {
      GetPackedTileOffset(0, offset_x, offset_y);
    }
    return memory.base_address;
  }

  if (!memory.mip_address) {
    *offset_x = 0;
    *offset_y = 0;
    return 0;
  }

  uint32_t address_base, address_offset;
  address_base = memory.mip_address;
  address_offset = 0;

  auto bytes_per_block = format_info()->bytes_per_block();

  if (!has_packed_mips) {
    for (uint32_t i = 1; i < mip; i++) {
      address_offset += GetMipExtent(i, is_guest).all_blocks() * bytes_per_block;
    }
    *offset_x = 0;
    *offset_y = 0;
    return address_base + address_offset;
  }

  uint32_t width_pow2 = rex::next_pow2(width + 1);
  uint32_t height_pow2 = rex::next_pow2(height + 1);

  uint32_t packed_mip_base = 1;
  for (uint32_t i = packed_mip_base; i < mip; i++, packed_mip_base++) {
    uint32_t mip_width = std::max(width_pow2 >> i, 1u);
    uint32_t mip_height = std::max(height_pow2 >> i, 1u);
    if (std::min(mip_width, mip_height) <= 16) {
      break;
    }
    address_offset += GetMipExtent(i, is_guest).all_blocks() * bytes_per_block;
  }

  GetPackedTileOffset(width_pow2 >> mip, height_pow2 >> mip, format_info(), mip - packed_mip_base,
                      offset_x, offset_y);
  return address_base + address_offset;
}

bool TextureInfo::GetPackedTileOffset(uint32_t width, uint32_t height,
                                      const FormatInfo* format_info, int packed_tile,
                                      uint32_t* offset_x, uint32_t* offset_y) {
  uint32_t log2_width = rex::log2_ceil(width);
  uint32_t log2_height = rex::log2_ceil(height);
  if (std::min(log2_width, log2_height) > 4) {
    *offset_x = 0;
    *offset_y = 0;
    return false;
  }

  if (packed_tile < 3) {
    if (log2_width > log2_height) {
      *offset_x = 0;
      *offset_y = 16 >> packed_tile;
    } else {
      *offset_x = 16 >> packed_tile;
      *offset_y = 0;
    }
  } else {
    if (log2_width > log2_height) {
      *offset_x = 16 >> (packed_tile - 2);
      *offset_y = 0;
    } else {
      *offset_x = 0;
      *offset_y = 16 >> (packed_tile - 2);
    }
  }

  *offset_x /= format_info->block_width;
  *offset_y /= format_info->block_height;
  return true;
}

bool TextureInfo::GetPackedTileOffset(int packed_tile, uint32_t* offset_x,
                                      uint32_t* offset_y) const {
  if (!has_packed_mips) {
    *offset_x = 0;
    *offset_y = 0;
    return false;
  }
  return GetPackedTileOffset(rex::next_pow2(width + 1), rex::next_pow2(height + 1), format_info(),
                             packed_tile, offset_x, offset_y);
}

uint64_t TextureInfo::hash() const {
  return XXH3_64bits(this, sizeof(TextureInfo));
}

void TextureInfo::SetupMemoryInfo(uint32_t base_address, uint32_t mip_address) {
  uint32_t bytes_per_block = format_info()->bytes_per_block();

  memory.base_address = 0;
  memory.base_size = 0;
  memory.mip_address = 0;
  memory.mip_size = 0;

  if (mip_min_level == 0 && base_address) {
    memory.base_address = base_address;
    memory.base_size = GetMipExtent(0, true).visible_blocks() * bytes_per_block;
  }

  if (mip_min_level == 0 && mip_max_level == 0) {
    return;
  }

  if (mip_min_level == 0 && base_address == mip_address) {
    return;
  }

  if (mip_min_level > 0) {
    if ((base_address && !mip_address) || (base_address == mip_address)) {
      mip_address = base_address;
      base_address = 0;
    } else if (!base_address && mip_address) {
    } else {
      assert_always();
    }
  }

  memory.mip_address = mip_address;

  if (!has_packed_mips) {
    for (uint32_t mip = std::max(1u, mip_min_level); mip < mip_max_level; mip++) {
      memory.mip_size += GetMipExtent(mip, true).all_blocks() * bytes_per_block;
    }
    memory.mip_size += GetMipExtent(mip_max_level, true).visible_blocks() * bytes_per_block;
    return;
  }

  uint32_t width_pow2 = rex::next_pow2(width + 1);
  uint32_t height_pow2 = rex::next_pow2(height + 1);

  uint32_t packed_mip_base = std::max(1u, mip_min_level);
  for (uint32_t mip = packed_mip_base; mip < mip_max_level; mip++, packed_mip_base++) {
    uint32_t mip_width = std::max(width_pow2 >> mip, 1u);
    uint32_t mip_height = std::max(height_pow2 >> mip, 1u);
    if (std::min(mip_width, mip_height) <= 16) {
      break;
    }
    memory.mip_size += GetMipExtent(mip, true).all_blocks() * bytes_per_block;
  }
}

}
