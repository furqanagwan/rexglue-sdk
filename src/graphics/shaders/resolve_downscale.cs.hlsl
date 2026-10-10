/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2025 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */






















cbuffer XeResolveDownscaleConstants : register(b0) {
  uint xe_downscale_scale_x;
  uint xe_downscale_scale_y;
  uint xe_downscale_pixel_size_log2;

  uint xe_downscale_length_dwords;


  uint xe_downscale_mode;
};

ByteAddressBuffer xe_resolve_source : register(t0);
RWByteAddressBuffer xe_resolve_dest : register(u0);



uint XeDownscaleScaledBlockByte(uint rel_bytes, uint pixel_size_log2,
                                uint scale_x, uint scale_y, uint sample_x,
                                uint sample_y) {
  uint unit_width_log2 = min(4u - pixel_size_log2, 3u);
  uint unit_bytes_log2 = unit_width_log2 + pixel_size_log2;
  uint unit_rel_bytes = rel_bytes & ~((1u << unit_bytes_log2) - 1u);


  uint block_in_unit =
      (rel_bytes >> pixel_size_log2) & ((1u << unit_width_log2) - 1u);
  uint host_x_in_unit = block_in_unit * scale_x + sample_x;
  uint subunit_x = host_x_in_unit >> unit_width_log2;
  uint block_in_subunit = host_x_in_unit & ((1u << unit_width_log2) - 1u);
  return unit_rel_bytes * (scale_x * scale_y) +
         ((((subunit_x * scale_y + sample_y) << unit_width_log2) +
           block_in_subunit) << pixel_size_log2);
}



[numthreads(128, 1, 1)]
void main(uint3 xe_group_id : SV_GroupID,
          uint xe_group_thread_index : SV_GroupIndex) {
  uint pixel_size_log2 = xe_downscale_pixel_size_log2;
  uint scale_x = xe_downscale_scale_x;
  uint scale_y = xe_downscale_scale_y;

  uint tile_dwords = ((32u * 32u) << pixel_size_log2) >> 2u;
  uint tile_first_dword = xe_group_id.x * tile_dwords;
  [branch] if (tile_first_dword >= xe_downscale_length_dwords) {
    return;
  }
  tile_dwords = min(tile_dwords, xe_downscale_length_dwords - tile_first_dword);


  uint sample_x = 0u;
  uint sample_y = 0u;
  [branch] if (xe_downscale_mode == 1u && scale_x * scale_y > 1u) {
    sample_x = scale_x >> 1u;
    sample_y = scale_y >> 1u;
  }

  [branch] if (xe_downscale_mode == 2u) {


    uint sample_count = scale_x * scale_y;
    for (uint dword_index = xe_group_thread_index; dword_index < tile_dwords;
         dword_index += 128u) {
      uint rel_bytes = (tile_first_dword + dword_index) << 2u;
      uint packed = 0u;
      for (uint byte_index = 0u; byte_index < 4u; ++byte_index) {
        uint byte_rel = rel_bytes + byte_index;
        uint texel_rel = byte_rel & ~((1u << pixel_size_log2) - 1u);
        uint byte_in_texel = byte_rel & ((1u << pixel_size_log2) - 1u);
        uint sum = 0u;
        for (uint y = 0u; y < scale_y; ++y) {
          for (uint x = 0u; x < scale_x; ++x) {
            uint src_bytes = XeDownscaleScaledBlockByte(
                                 texel_rel, pixel_size_log2, scale_x, scale_y, x,
                                 y) +
                             byte_in_texel;
            sum += (xe_resolve_source.Load(src_bytes & ~3u) >>
                    ((src_bytes & 3u) << 3u)) &
                   0xFFu;
          }
        }
        packed |= ((sum + (sample_count >> 1u)) / sample_count)
                  << (byte_index << 3u);
      }
      xe_resolve_dest.Store(rel_bytes, packed);
    }
    return;
  }

  for (uint dword_index = xe_group_thread_index; dword_index < tile_dwords;
       dword_index += 128u) {
    uint rel_bytes = (tile_first_dword + dword_index) << 2u;
    [branch] if (pixel_size_log2 >= 2u) {


      uint src_bytes =
          XeDownscaleScaledBlockByte(rel_bytes, pixel_size_log2, scale_x,
                                     scale_y, sample_x, sample_y) +
          (rel_bytes & ((1u << pixel_size_log2) - 4u));
      xe_resolve_dest.Store(rel_bytes, xe_resolve_source.Load(src_bytes));
    } else {

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
