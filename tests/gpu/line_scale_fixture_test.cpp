/**
 * @file        line_scale_fixture_test.cpp
 * @brief       Resolution-scaled lines stay 1 guest pixel wide
 *
 * Host lines are rasterized 1 host pixel wide; at a draw resolution scale of 2
 * a guest line covered only half its guest pixels. The line geometry shader
 * expands each segment to a quad 1 guest pixel wide (has207/xenia-edge
 * 7d0a45263).
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

struct RestoreCvars {
  ~RestoreCvars() {
    for (const char* name :
         {"draw_resolution_scale_x", "draw_resolution_scale_y", "resolution_scale_targets",
          "resolve_downscale_average", "render_target_path_d3d12", "readback_resolve",
          "async_shader_compilation"}) {
      rex::cvar::ResetToDefault(name);
    }
  }
};

// Draws a white horizontal line at guest y over black, resolves it at the
// guest's size (each texel the average of its host pixels) and returns the
// red coverage summed down column 16, in 255ths of a guest pixel.
bool LineCoverage(const char* path, uint32_t scale, float y, uint32_t& coverage_out,
                  std::string& error) {
  const std::string scale_text = std::to_string(scale);
  auto fixture = GpuFixture::Create(&error, {{"draw_resolution_scale_x", scale_text.c_str()},
                                             {"draw_resolution_scale_y", scale_text.c_str()},
                                             {"resolution_scale_targets", "none"},
                                             {"resolve_downscale_average", "true"},
                                             {"render_target_path_d3d12", path},
                                             {"async_shader_compilation", "false"}});
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
  SetupDraw(*fixture, surface, kSize, kSize);
  DrawRect(*fixture, 0, 0, kSize, kSize, 0xFF000000);

  const uint32_t vertices = fixture->AllocPhysical(0x100);
  std::vector<uint32_t> vertex_data;
  for (float v : {-8.0f, y, 0.0f, 1.0f, 40.0f, y, 0.0f, 1.0f}) {
    vertex_data.push_back(std::bit_cast<uint32_t>(v));
  }
  fixture->WriteDwords(vertices, vertex_data);
  xenos::xe_gpu_vertex_fetch_t fetch = {};
  fetch.type = xenos::FetchConstantType::kVertex;
  fetch.address = vertices >> 2;
  fetch.endian = xenos::Endian::k8in32;
  fetch.size = 2 * 4;
  fixture->Submit(GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_FETCH_00_0,
                                           {fetch.dword_0, fetch.dword_1}));
  fixture->Submit(
      GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_256_X,
                               {std::bit_cast<uint32_t>(1.0f), std::bit_cast<uint32_t>(1.0f),
                                std::bit_cast<uint32_t>(1.0f), std::bit_cast<uint32_t>(1.0f)}));
  reg::VGT_DRAW_INITIATOR initiator = {};
  initiator.prim_type = xenos::PrimitiveType::kLineList;
  initiator.source_select = xenos::SourceSelect::kAutoIndex;
  initiator.num_indices = 2;
  fixture->Submit({xenos::MakePacketType3(xenos::PM4_DRAW_INDX_2, 1), initiator.value});

  const uint32_t dest = fixture->AllocPhysical(kSize * kSize * 4);
  Resolve(*fixture, surface, kSize, kSize, xenos::CopySampleSelect::k0, dest);
  REQUIRE(fixture->Flush());
  coverage_out = 0;
  for (uint32_t row = 0; row < kSize; ++row) {
    coverage_out += ReadTexel(*fixture, dest, 16, row) & 0xFF;
  }
  return true;
}

}  // namespace

TEST_CASE("Resolution-scaled lines cover one guest pixel", "[gpu][line-scale]") {
  const char* path = GENERATE("rtv", "rov");
  // On a guest pixel's center and across a guest pixel boundary.
  const float y = GENERATE(16.5f, 16.0f, 16.3f);
  INFO("render_target_path_d3d12 " << path << ", line at y " << y);
  RestoreCvars restore;
  std::string error;
  uint32_t native = 0, scaled = 0;
  if (!LineCoverage(path, 1, y, native, error)) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(LineCoverage(path, 2, y, scaled, error));
  INFO("coverage down a column: 1x " << native << ", 2x " << scaled);
  // One guest pixel of white either way; a 1-host-pixel line at 2x gives half
  // (128).
  CHECK(native == 255);
  CHECK(scaled >= 250);
  CHECK(scaled <= 260);
}
