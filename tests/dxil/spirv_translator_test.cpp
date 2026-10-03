/**
 * @file        spirv_translator_test.cpp
 * @brief       Guest microcode through the SPIR-V translator to signed DXIL
 *
 * The xenia-edge SPIR-V translator (RG-GDK-032 stage 2) on the GPU fixture's
 * hand-assembled guest shaders, configured as Edge's D3D12 pipeline cache
 * configures it, then Mesa spirv_to_dxil with bindless lowering and signing by
 * the pinned dxil.dll, whose validation must accept the result.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <bit>
#include <cstdint>
#include <cstring>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <rex/cvar.h>
#include <rex/graphics/pipeline/shader/spirv.h>
#include <rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h>
#include <rex/graphics/pipeline/shader/spirv_translator.h>
#include <rex/string/buffer.h>

#include "../gpu/guest_draw.h"

// Defined in plugin sources the test doesn't compile (command processor, DXBC
// translator), with their defaults.
REXCVAR_DEFINE_BOOL(occlusion_query_viz, false, "GPU", "");
REXCVAR_DEFINE_BOOL(occlusion_query_full_counters, false, "GPU", "");
REXCVAR_DEFINE_BOOL(draw_resolution_scaled_texture_offsets, true, "GPU/Shader", "");

namespace {

using namespace rex::graphics;  // NOLINT

std::unique_ptr<SpirvShaderTranslator> CreateTranslator(bool rov) {
  SpirvShaderTranslator::Features features(/*all=*/true);
  features.fragment_shader_sample_interlock = false;
  features.fragment_shader_barycentric = true;
  features.signed_zero_inf_nan_preserve_float32 = false;
  features.denorm_flush_to_zero_float32 = true;
  features.rounding_mode_rte_float32 = false;
  return std::make_unique<SpirvShaderTranslator>(features, true, false, rov, false, 1, 1);
}

// Guest ucode to SPIR-V; empty on failure.
std::vector<uint8_t> ToSpirv(SpirvShaderTranslator& translator, SpirvShader& shader) {
  rex::string::StringBuffer disassembly;
  shader.AnalyzeUcode(disassembly);
  const uint64_t modification =
      shader.type() == xenos::ShaderType::kVertex
          ? translator.GetDefaultVertexShaderModification(64, Shader::HostVertexShaderType::kVertex)
          : translator.GetDefaultPixelShaderModification(64);
  Shader::Translation* translation = shader.GetOrCreateTranslation(modification);
  if (!translator.TranslateAnalyzedShader(*translation) || !translation->is_valid()) {
    return {};
  }
  return translation->translated_binary();
}

}  // namespace

TEST_CASE("The SPIR-V translator turns guest shaders into signed DXIL", "[dxil][spirv]") {
  REQUIRE(SpirvToDxilCompiler::IsSignerAvailable());
  const bool rov = GENERATE(false, true);
  const bool vertex = GENERATE(true, false);
  INFO((vertex ? "vertex" : "pixel") << " shader, " << (rov ? "ROV" : "RTV"));
  namespace gd = rex::testing::guest_draw;
  const std::vector<uint32_t>& ucode = vertex ? gd::kVertexShader : gd::kPixelShader;
  SpirvShader shader(vertex ? xenos::ShaderType::kVertex : xenos::ShaderType::kPixel,
                     vertex ? 0x1111 : 0x2222, ucode.data(), ucode.size(), std::endian::native);

  auto translator = CreateTranslator(rov);
  std::vector<uint8_t> spirv = ToSpirv(*translator, shader);
  REQUIRE(spirv.size() >= 20);
  uint32_t magic;
  std::memcpy(&magic, spirv.data(), sizeof(magic));
  CHECK(magic == 0x07230203);

  // Translate signs the DXIL; dxil.dll validation rejecting it returns empty.
  std::vector<uint8_t> dxil = SpirvToDxilCompiler::Translate(
      reinterpret_cast<const uint32_t*>(spirv.data()), spirv.size() / sizeof(uint32_t),
      vertex ? SpirvToDxilCompiler::Stage::kVertex : SpirvToDxilCompiler::Stage::kPixel,
      /*lower_to_bindless=*/true);
  REQUIRE(dxil.size() > 32);
  CHECK(std::memcmp(dxil.data(), "DXBC", 4) == 0);
}
