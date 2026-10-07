/**
 * @file        tessellation_fixture_test.cpp
 * @brief       Tessellated quad patches cover the domain the guest maps
 *
 * A guest vertex shader drawn with tessellation enabled is a domain shader:
 * r0.yz holds the domain location. The one here places the patch's domain at
 * (0, 0)-(16, 16), so a tessellated patch fills exactly that corner of the
 * target, on both render target paths and on both the DXBC and the SPIR-V ->
 * DXIL shader paths (gpu.dxil_parity, RG-GDK-032).
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <bit>
#include <cstdint>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <rex/cvar.h>
#include <rex/graphics/format/ucode.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/xenos.h>

#include "gpu_fixture.h"
#include "guest_draw.h"

namespace {

using namespace rex::graphics;  // NOLINT: XE_GPU_REG_* register indices.
namespace reg = rex::graphics::reg;
namespace xenos = rex::graphics::xenos;
using rex::testing::GpuFixture;
using namespace rex::testing::guest_draw;  // NOLINT

constexpr uint32_t kSize = 32;
constexpr uint32_t kPatchSize = 16;

struct RestoreCvars {
  ~RestoreCvars() {
    for (const char* name : {"render_target_path_d3d12", "async_shader_compilation"}) {
      rex::cvar::ResetToDefault(name);
    }
  }
};

// alloc position; exec_end (mad oPos, r0.yzxx, c0, c1): the domain location
// (u, v) in r0.yz scaled by c0 and offset by c1, w from c1.w. The patch index
// in r0.x is 0 here, so it zeroes z and w before the offset.
std::vector<uint32_t> DomainShader() {
  std::vector<uint32_t> ucode;
  PackCf(ucode, Alloc(rex::graphics::ucode::AllocType::kVsPosition), Exec(1, 1, 0, true));
  // Component-relative: x from y, y from z, z and w from x.
  constexpr uint32_t kSwizzleYZXX = 1 | (1 << 2) | (2 << 4) | (1 << 6);
  const std::vector<uint32_t> mad =
      AluExport(62, kAluMad, 0, 0, 1, kSwizzleYZXX, true, false, false);
  ucode.insert(ucode.end(), mad.begin(), mad.end());
  return ucode;
}

// Fills the target black, then draws one tessellated quad patch in white and
// returns the resolved texels.
bool DrawPatch(const char* path, xenos::TessellationMode mode, std::vector<uint32_t>& texels_out,
               std::string& error) {
  auto fixture = GpuFixture::Create(
      &error, {{"render_target_path_d3d12", path}, {"async_shader_compilation", "false"}});
  if (!fixture) {
    return false;
  }
  if (std::string(path) == "rov" && (fixture->provider().IsAdapterSoftware() ||
                                     !fixture->provider().AreRasterizerOrderedViewsSupported())) {
    error = "no hardware ROV support";
    return false;
  }
  const Surface surface = {xenos::MsaaSamples::k1X, 64};
  SetupDraw(*fixture, surface, kSize, kSize);
  DrawRect(*fixture, 0, 0, kSize, kSize, 0xFF000000);

  fixture->Submit(LoadShader(xenos::ShaderType::kVertex, DomainShader()));
  fixture->Submit(GpuFixture::SetRegisters(
      XE_GPU_REG_SHADER_CONSTANT_000_X,
      {std::bit_cast<uint32_t>(float(kPatchSize)), std::bit_cast<uint32_t>(float(kPatchSize)), 0, 0,
       0, 0, 0, std::bit_cast<uint32_t>(1.0f)}));
  fixture->Submit(
      GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_256_X,
                               {std::bit_cast<uint32_t>(1.0f), std::bit_cast<uint32_t>(1.0f),
                                std::bit_cast<uint32_t>(1.0f), std::bit_cast<uint32_t>(1.0f)}));
  reg::VGT_OUTPUT_PATH_CNTL output_path = {};
  output_path.path_select = xenos::VGTOutputPath::kTessellationEnable;
  reg::VGT_HOS_CNTL hos_cntl = {};
  hos_cntl.tess_mode = mode;
  // Factors of 1 (the guest adds 1): one quad over the whole domain.
  fixture->Submit(GpuFixture::SetRegisters(XE_GPU_REG_VGT_OUTPUT_PATH_CNTL,
                                           {output_path.value, hos_cntl.value, 0, 0}));
  reg::PA_SC_WINDOW_SCISSOR_TL window_tl = {};
  window_tl.window_offset_disable = 1;
  fixture->Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SC_WINDOW_SCISSOR_TL,
                                           {window_tl.value, PackXY(kSize, kSize)}));
  reg::VGT_DRAW_INITIATOR initiator = {};
  initiator.prim_type = xenos::PrimitiveType::kQuadPatch;
  initiator.source_select = xenos::SourceSelect::kAutoIndex;
  initiator.num_indices = 1;
  fixture->Submit({xenos::MakePacketType3(xenos::PM4_DRAW_INDX_2, 1), initiator.value});
  fixture->Submit(GpuFixture::SetRegisters(XE_GPU_REG_VGT_OUTPUT_PATH_CNTL, {0}));

  const uint32_t dest = fixture->AllocPhysical(kSize * kSize * 4);
  Resolve(*fixture, surface, kSize, kSize, xenos::CopySampleSelect::k0, dest);
  REQUIRE(fixture->Flush());
  texels_out.clear();
  for (uint32_t y = 0; y < kSize; ++y) {
    for (uint32_t x = 0; x < kSize; ++x) {
      texels_out.push_back(ReadTexel(*fixture, dest, x, y));
    }
  }
  return true;
}

}  // namespace

TEST_CASE("A tessellated quad patch covers the domain the shader maps", "[gpu][tessellation]") {
  const char* path = GENERATE("rtv", "rov");
  const xenos::TessellationMode mode =
      GENERATE(xenos::TessellationMode::kDiscrete, xenos::TessellationMode::kContinuous);
  INFO("render_target_path_d3d12 " << path << ", tessellation mode " << uint32_t(mode));
  RestoreCvars restore;
  std::string error;
  std::vector<uint32_t> texels;
  if (!DrawPatch(path, mode, texels, error)) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  // White inside the patch, the black fill outside, away from the edges.
  for (uint32_t y = 0; y < kSize; ++y) {
    for (uint32_t x = 0; x < kSize; ++x) {
      if (x == kPatchSize - 1 || x == kPatchSize || y == kPatchSize - 1 || y == kPatchSize) {
        continue;
      }
      bool inside = x < kPatchSize && y < kPatchSize;
      INFO("texel (" << x << ", " << y << ")");
      CHECK(texels[y * kSize + x] == (inside ? 0xFFFFFFFFu : 0xFF000000u));
    }
  }
}
