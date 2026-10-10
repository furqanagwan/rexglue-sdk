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

#ifndef REX_GRAPHICS_PIPELINE_SHADER_SPIRV_FSI_SYSTEM_CONSTANTS_H_
#define REX_GRAPHICS_PIPELINE_SHADER_SPIRV_FSI_SYSTEM_CONSTANTS_H_

#include <cstdint>

#include <rex/graphics/register_file.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/pipeline/shader/spirv_translator.h>

namespace rex::graphics {

void WriteFragmentShaderInterlockSystemConstants(
    SpirvShaderTranslator::SystemConstants& system_constants, uint32_t& flags, bool& dirty,
    const RegisterFile& regs, bool primitive_polygonal,
    reg::RB_DEPTHCONTROL normalized_depth_control, uint32_t normalized_color_mask,
    uint32_t draw_resolution_scale_x, uint32_t draw_resolution_scale_y,
    uint32_t zpd_fsi_counter_index);

}

#endif
