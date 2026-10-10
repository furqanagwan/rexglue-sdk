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

#include <rex/graphics/pipeline/shader/spirv.h>

#include <cstring>

namespace rex::graphics {

SpirvShader::SpirvShader(xenos::ShaderType shader_type, uint64_t ucode_data_hash,
                         const uint32_t* ucode_dwords, size_t ucode_dword_count,
                         std::endian ucode_source_endian)
    : Shader(shader_type, ucode_data_hash, ucode_dwords, ucode_dword_count, ucode_source_endian) {}

Shader::Translation* SpirvShader::CreateTranslationInstance(uint64_t modification) {
  return new SpirvTranslation(*this, modification);
}

}
