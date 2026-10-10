/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2026 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Ported from has207/xenia-edge 0788c561e3
 *              (RG-GDK-032) for the ReXGlue runtime
 */

#ifndef REX_GRAPHICS_PIPELINE_SHADER_SPIRV_BUILTIN_GEOMETRY_SHADER_H_
#define REX_GRAPHICS_PIPELINE_SHADER_SPIRV_BUILTIN_GEOMETRY_SHADER_H_

#include <cstdint>
#include <vector>

namespace rex::graphics {

enum class BuiltinGeometryShaderType : uint32_t {
  kNone,
  kPointList,
  kRectangleList,
  kQuadList,

  kLineList,
};

std::vector<unsigned int> BuildGuestPrimitiveGeometryShaderSpirv(
    BuiltinGeometryShaderType type, uint32_t interpolator_count, uint32_t user_clip_plane_count,
    bool user_clip_plane_cull, bool has_vertex_kill_and, bool has_point_size,
    bool has_point_coordinates, unsigned int spirv_version, bool denorm_flush_to_zero_float32,
    bool signed_zero_inf_nan_preserve_float32, bool rounding_mode_rte_float32);

}

#endif
