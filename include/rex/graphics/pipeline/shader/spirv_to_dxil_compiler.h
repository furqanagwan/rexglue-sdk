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

#ifndef REX_GRAPHICS_PIPELINE_SHADER_SPIRV_TO_DXIL_COMPILER_H_
#define REX_GRAPHICS_PIPELINE_SHADER_SPIRV_TO_DXIL_COMPILER_H_

#include <cstddef>
#include <cstdint>
#include <vector>

namespace rex::graphics {

class SpirvToDxilCompiler {
 public:
  static uint64_t version();

  static bool IsSignerAvailable();

  static constexpr uint32_t kPushConstantRegisterSpace = 31;
  static constexpr uint32_t kPushConstantShaderRegister = 1;

  enum class Stage {
    kVertex,
    kTessellationControl,
    kTessellationEvaluation,
    kGeometry,
    kPixel,
    kCompute,
  };

  static std::vector<uint8_t> Translate(const uint32_t* spirv_words, size_t spirv_word_count,
                                        Stage stage, bool lower_to_bindless = false,
                                        uint32_t input_clip_size = 0);

  struct LinkedStage {
    const uint32_t* spirv_words;
    size_t spirv_word_count;
    Stage stage;
  };

  static std::vector<std::vector<uint8_t>> TranslateLinked(const std::vector<LinkedStage>& stages,
                                                           bool lower_to_bindless = false);
};

}

#endif
