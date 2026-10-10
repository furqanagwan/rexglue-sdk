/**
 * @file        viz_fixture_test.cpp
 * @brief       VIZ_QUERY predication through the GPU plugin (RG-GDK-010b, xenia-canary #1111)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <bit>
#include <cstdint>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <rex/cvar.h>
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

constexpr uint32_t kVizId = 5;
constexpr uint32_t kBackground = 0xFF0000FF, kConsumer = 0xFF00FF00;

struct RestoreCvars {
  ~RestoreCvars() {
    for (const char* name : {"occlusion_query_viz", "render_target_path_d3d12",
                             "async_shader_compilation", "readback_resolve"}) {
      rex::cvar::ResetToDefault(name);
    }
  }
};

void VizQuery(GpuFixture& fixture, uint32_t dword) {
  fixture.Submit({xenos::MakePacketType3(xenos::PM4_VIZ_QUERY, 1), dword});
}

void SetVizRegister(GpuFixture& fixture, bool enable) {
  reg::PA_SC_VIZ_QUERY viz = {};
  viz.viz_query_ena = enable;
  viz.viz_query_id = kVizId;
  viz.kill_pix_post_hi_z = enable;
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SC_VIZ_QUERY, {viz.value}));
}

void DrawRectWithToken(GpuFixture& fixture, uint32_t token, uint32_t color) {
  reg::PA_SC_WINDOW_SCISSOR_TL window_tl = {};
  window_tl.window_offset_disable = 1;
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SC_WINDOW_SCISSOR_TL,
                                          {window_tl.value | PackXY(0, 0), PackXY(32, 32)}));
  auto channel = [color](uint32_t i) {
    return std::bit_cast<uint32_t>(float((color >> (i * 8)) & 0xFF) / 255.0f);
  };
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_256_X,
                                          {channel(0), channel(1), channel(2), channel(3)}));
  reg::VGT_DRAW_INITIATOR initiator = {};
  initiator.prim_type = xenos::PrimitiveType::kTriangleStrip;
  initiator.source_select = xenos::SourceSelect::kAutoIndex;
  initiator.num_indices = 4;
  fixture.Submit({xenos::MakePacketType3(xenos::PM4_DRAW_INDX, 2), token, initiator.value});
}

struct RunOptions {
  bool viz_enabled = true;

  float survey_z = 0.75f;

  bool hiz = true;

  bool flush_before_consumer = false;
};

bool Run(const char* path, const RunOptions& run, uint32_t& texel_out, std::string& error) {
  auto fixture =
      GpuFixture::Create(&error, {{"occlusion_query_viz", run.viz_enabled ? "true" : "false"},
                                  {"async_shader_compilation", "false"},
                                  {"render_target_path_d3d12", path}});
  if (!fixture) {
    return false;
  }
  if (std::string(path) == "rov" && (fixture->provider().IsAdapterSoftware() ||
                                     !fixture->provider().AreRasterizerOrderedViewsSupported())) {
    error = "no hardware ROV support";
    return false;
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));

  const Surface surface = {xenos::MsaaSamples::k1X, 64};
  DrawOptions options;

  options.color_base_tiles = 16;
  options.depth_control.z_enable = 1;
  options.depth_control.z_write_enable = 1;
  options.depth_control.zfunc = xenos::CompareFunction::kAlways;
  options.z = 0.5f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 32, 32, kBackground);

  options.depth_control.z_write_enable = 0;
  options.depth_control.zfunc = xenos::CompareFunction::kLess;
  options.z = run.survey_z;
  SetupDraw(*fixture, surface, 32, 32, options);
  reg::RB_HIZCONTROL hiz = {};
  hiz.hiz_enable = run.hiz;
  fixture->Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_HIZCONTROL, {hiz.value}));
  VizQuery(*fixture, kVizId);
  SetVizRegister(*fixture, true);
  DrawRect(*fixture, 0, 0, 32, 32, 0xFFFFFFFF);
  SetVizRegister(*fixture, false);
  VizQuery(*fixture, 0x100 | kVizId);
  if (run.flush_before_consumer) {
    REQUIRE(fixture->Flush());
  }

  options.depth_control.zfunc = xenos::CompareFunction::kAlways;
  options.z = 0.1f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRectWithToken(*fixture, 0x100 | kVizId, kConsumer);

  const uint32_t dest = fixture->AllocPhysical(0x1000);
  Resolve(*fixture, surface, 32, 32, xenos::CopySampleSelect::k0, dest, 32, 16);
  REQUIRE(fixture->Flush());
  texel_out = fixture->ReadDword(dest);
  return true;
}

}

TEST_CASE("A VIZ survey hidden behind depth skips its consumer draw", "[gpu][viz]") {
  const char* path = GENERATE("rtv", "rov");
  const bool flush = GENERATE(false, true);
  INFO("render_target_path_d3d12 " << path << ", flush before the consumer " << flush);
  RestoreCvars restore;
  std::string error;
  RunOptions run;
  run.flush_before_consumer = flush;
  uint32_t hidden = 0, visible = 0, disabled = 0;
  run.viz_enabled = false;
  if (!Run(path, run, disabled, error)) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  run.viz_enabled = true;
  REQUIRE(Run(path, run, hidden, error));
  run.survey_z = 0.25f;
  REQUIRE(Run(path, run, visible, error));
  INFO(std::hex << "hidden 0x" << hidden << ", visible 0x" << visible << ", VIZ off 0x"
                << disabled);

  CHECK(disabled == kConsumer);
  CHECK(visible == kConsumer);

  CHECK(hidden == kBackground);
}

TEST_CASE("A VIZ survey with nothing rejecting it keeps its consumer draw", "[gpu][viz]") {
  const char* path = GENERATE("rtv", "rov");
  INFO("render_target_path_d3d12 " << path);
  RestoreCvars restore;
  std::string error;
  RunOptions run;

  run.hiz = false;
  uint32_t texel = 0;
  if (!Run(path, run, texel, error)) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  CHECK(texel == kConsumer);
}
