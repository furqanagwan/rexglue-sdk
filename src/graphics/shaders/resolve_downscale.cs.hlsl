/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2025 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

// Downscales scaled resolve buffer data back to 1x resolution for CPU readback.
// One thread group processes one 32x32 tile of the written extent; each thread
// produces output dwords. Keeps the top-left host texel of each scale_x *
// scale_y block, or its (scale/2, scale/2) center when
// xe_downscale_half_pixel_offset is set.
//
// The source is not a flat scale_x * scale_y expansion of each guest texel.
// The resolve shaders in this repository are xenia-canary's from 04d5c40d0
// (2025-08-19), which scale Nx1 units of horizontally consecutive guest blocks
// (XeTextureScaledTiledOffset in that revision's texture_address.xesli):
// - 1bpp and 2bpp - 8 blocks, 4bpp - 4, 8bpp - 2, 16bpp - 1.
// A guest unit at guest address A occupies scale_x * scale_y host sub-units of
// the same size at A * scale_x * scale_y, ordered column-major. This shader
// reverses that per guest unit. Canary a635ac64f reads the group layout that
// Canary introduced in 0f23f0568 instead, which doesn't match these shaders.
//
// The source view starts at the written extent's scaled address, and the
// extent is limited in dwords, so extents ending inside a tile are complete.

cbuffer XeResolveDownscaleConstants : register(b0) {
  uint xe_downscale_scale_x;         // 1 to kMaxDrawResolutionScaleAlongAxis
  uint xe_downscale_scale_y;         // 1 to kMaxDrawResolutionScaleAlongAxis
  uint xe_downscale_pixel_size_log2; // 0=8bit, 1=16bit, 2=32bit, 3=64bit
  // Number of 1x dwords to write; the last 32x32 tile may be partial.
  uint xe_downscale_length_dwords;
  // When non-zero, sample from (scale/2, scale/2) within each scaled block
  // instead of (0, 0).
  uint xe_downscale_half_pixel_offset;
};

ByteAddressBuffer xe_resolve_source : register(t0);
RWByteAddressBuffer xe_resolve_dest : register(u0);

// Scaled-buffer byte of the chosen host sample of the guest block at byte
// offset rel_bytes from the start of the written extent.
uint XeDownscaleScaledBlockByte(uint rel_bytes, uint pixel_size_log2,
                                uint scale_x, uint scale_y, uint sample_x,
                                uint sample_y) {
  uint unit_width_log2 = min(4u - pixel_size_log2, 3u);
  uint unit_bytes_log2 = unit_width_log2 + pixel_size_log2;
  uint unit_rel_bytes = rel_bytes & ~((1u << unit_bytes_log2) - 1u);
  // Shift first, then mask: fxc compiles the mask-then-shift form into a ubfe
  // whose width wrongly includes the shift for non-zero pixel_size_log2.
  uint block_in_unit =
      (rel_bytes >> pixel_size_log2) & ((1u << unit_width_log2) - 1u);
  uint host_x_in_unit = block_in_unit * scale_x + sample_x;
  uint subunit_x = host_x_in_unit >> unit_width_log2;
  uint block_in_subunit = host_x_in_unit & ((1u << unit_width_log2) - 1u);
  return unit_rel_bytes * (scale_x * scale_y) +
         ((((subunit_x * scale_y + sample_y) << unit_width_log2) +
           block_in_subunit) << pixel_size_log2);
}

// 128 threads per group; a tile has 256..2048 output dwords depending on the
// pixel size, so each thread strides over several of them.
[numthreads(128, 1, 1)]
void main(uint3 xe_group_id : SV_GroupID,
          uint xe_group_thread_index : SV_GroupIndex) {
  uint pixel_size_log2 = xe_downscale_pixel_size_log2;
  uint scale_x = xe_downscale_scale_x;
  uint scale_y = xe_downscale_scale_y;
  // Number of output dwords in a 1x tile (256, 512, 1024 or 2048).
  uint tile_dwords = ((32u * 32u) << pixel_size_log2) >> 2u;
  uint tile_first_dword = xe_group_id.x * tile_dwords;
  [branch] if (tile_first_dword >= xe_downscale_length_dwords) {
    return;
  }
  tile_dwords = min(tile_dwords, xe_downscale_length_dwords - tile_first_dword);

  // Host sample to keep within each block: top-left, or center when requested.
  uint sample_x = 0u;
  uint sample_y = 0u;
  [branch] if (xe_downscale_half_pixel_offset != 0u &&
               scale_x * scale_y > 1u) {
    sample_x = scale_x >> 1u;
    sample_y = scale_y >> 1u;
  }

  for (uint dword_index = xe_group_thread_index; dword_index < tile_dwords;
       dword_index += 128u) {
    uint rel_bytes = (tile_first_dword + dword_index) << 2u;
    [branch] if (pixel_size_log2 >= 2u) {
      // 32bpp: one texel per output dword. 64bpp: a texel's two dwords are
      // consecutive in its host sub-unit too.
      uint src_bytes =
          XeDownscaleScaledBlockByte(rel_bytes, pixel_size_log2, scale_x,
                                     scale_y, sample_x, sample_y) +
          (rel_bytes & ((1u << pixel_size_log2) - 4u));
      xe_resolve_dest.Store(rel_bytes, xe_resolve_source.Load(src_bytes));
    } else {
      // 8bpp/16bpp: consecutive texels packed into one output dword.
      uint texels_per_dword = 4u >> pixel_size_log2;
      uint component_bits = 8u << pixel_size_log2;
      uint component_mask = (1u << component_bits) - 1u;
      uint packed = 0u;
      for (uint i = 0u; i < texels_per_dword; ++i) {
        uint src_bytes = XeDownscaleScaledBlockByte(
            rel_bytes + (i << pixel_size_log2), pixel_size_log2, scale_x,
            scale_y, sample_x, sample_y);
        uint src_word = xe_resolve_source.Load(src_bytes & ~3u);
        packed |= ((src_word >> ((src_bytes & 3u) << 3u)) & component_mask)
                  << (i * component_bits);
      }
      xe_resolve_dest.Store(rel_bytes, packed);
    }
  }
}
