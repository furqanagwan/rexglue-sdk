/**
 * @file        native_resolve_fixture_test.cpp
 * @brief       Resolves outside resolution_scale_targets are written at the guest's size (ADR-012)
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
#include <rex/graphics/pipeline/texture/util.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/xenos.h>

#include "gpu_fixture.h"
#include "guest_draw.h"

namespace {

using namespace rex::graphics;  // NOLINT: XE_GPU_REG_* register indices.
namespace xenos = rex::graphics::xenos;
using rex::testing::GpuFixture;
using namespace rex::testing::guest_draw;  // NOLINT

constexpr uint32_t kSize = 32;
constexpr uint32_t kBackground = 0xFF0000FF, kForeground = 0xFF00FF00;
constexpr uint32_t kUnwritten = 0xDEADBEEF;
// The foreground's right edge, in guest pixels: a quarter into a guest pixel
// whichever way the half-pixel convention shifts it, so at 2x the pixel's
// top-left host sample is covered and its center sample isn't.
constexpr float kEdge = 8.125f;

// The fixtures' cvars outlive them: put back what these runs set, so later
// tests in the process run at the default scale.
struct RestoreCvars {
  ~RestoreCvars() {
    for (const char* name :
         {"draw_resolution_scale_x", "draw_resolution_scale_y", "resolution_scale_targets",
          "render_target_path_d3d12", "readback_resolve_half_pixel_offset"}) {
      rex::cvar::ResetToDefault(name);
    }
  }
};

// Draws the background over 32x32, then the foreground from the left up to
// kEdge, resolves 32x32 at 2x2 resolution scale with `list` as
// resolution_scale_targets, and reads the texels back (row by row).
bool DrawAndResolve(const char* path, const char* list, std::vector<uint32_t>& texels_out,
                    std::string& error) {
  auto fixture = GpuFixture::Create(&error, {{"draw_resolution_scale_x", "2"},
                                             {"draw_resolution_scale_y", "2"},
                                             {"resolution_scale_targets", list},
                                             {"render_target_path_d3d12", path}});
  if (!fixture) {
    return false;
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve_half_pixel_offset", "false"));
  // Otherwise draws are dropped while their pipelines compile.
  REQUIRE(rex::cvar::SetFlagByName("async_shader_compilation", "false"));

  const Surface surface = {xenos::MsaaSamples::k1X, 64};
  SetupDraw(*fixture, surface, kSize, kSize);
  DrawRect(*fixture, 0, 0, kSize, kSize, kBackground);

  // The foreground's own geometry, ending inside a guest pixel.
  const uint32_t vertices = fixture->AllocPhysical(0x100);
  std::vector<uint32_t> vertex_data;
  for (float v : {-8.0f, -8.0f, 0.0f, 1.0f, kEdge, -8.0f, 0.0f, 1.0f, -8.0f, 40.0f, 0.0f, 1.0f,
                  kEdge, 40.0f, 0.0f, 1.0f}) {
    vertex_data.push_back(std::bit_cast<uint32_t>(v));
  }
  fixture->WriteDwords(vertices, vertex_data);
  xenos::xe_gpu_vertex_fetch_t fetch = {};
  fetch.type = xenos::FetchConstantType::kVertex;
  fetch.address = vertices >> 2;
  fetch.endian = xenos::Endian::k8in32;
  fetch.size = 4 * 4;
  fixture->Submit(GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_FETCH_00_0,
                                           {fetch.dword_0, fetch.dword_1}));
  DrawRect(*fixture, 0, 0, kSize, kSize, kForeground);

  const uint32_t dest = fixture->AllocPhysical(kSize * kSize * 4);
  fixture->WriteDwords(dest, std::vector<uint32_t>(kSize * kSize, kUnwritten));
  Resolve(*fixture, surface, kSize, kSize, xenos::CopySampleSelect::k0, dest);
  REQUIRE(fixture->Flush());

  texels_out.resize(kSize * kSize);
  for (uint32_t y = 0; y < kSize; ++y) {
    for (uint32_t x = 0; x < kSize; ++x) {
      const int32_t offset = texture_util::GetTiledOffset2D(int32_t(x), int32_t(y), kSize, 2);
      texels_out[y * kSize + x] = fixture->ReadDword(dest + uint32_t(offset));
    }
  }
  return true;
}

}  // namespace

TEST_CASE("A resolve the list doesn't name is written at the guest's size",
          "[gpu][resolve][native]") {
  // Both render target paths resolve from the scaled EDRAM copy.
  const char* path = GENERATE("rtv", "rov");
  INFO("render_target_path_d3d12 " << path);
  RestoreCvars restore;
  std::vector<uint32_t> scaled, native;
  std::string error;
  // 32 wide is listed: the resolve stays scaled, read back from the top-left
  // host sample of each texel.
  if (!DrawAndResolve(path, "32x0", scaled, error)) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  // Not listed: written at the guest's size from each texel's center sample.
  REQUIRE(DrawAndResolve(path, "999x0", native, error));

  uint32_t unwritten = 0, differing_columns = 0, other_differences = 0;
  for (uint32_t x = 0; x < kSize; ++x) {
    uint32_t column_differences = 0;
    for (uint32_t y = 0; y < kSize; ++y) {
      const uint32_t s = scaled[y * kSize + x], n = native[y * kSize + x];
      unwritten += n == kUnwritten;
      if (s != n) {
        ++column_differences;
        // The edge pixel: covered at its top-left sample, not at its center.
        if (!(s == kForeground && n == kBackground)) {
          ++other_differences;
        }
      }
    }
    differing_columns += column_differences == kSize;
    if (column_differences != 0 && column_differences != kSize) {
      ++other_differences;
    }
  }
  INFO("row 0 scaled/native at columns 6..10: "
       << std::hex << scaled[6] << "/" << native[6] << " " << scaled[7] << "/" << native[7] << " "
       << scaled[8] << "/" << native[8] << " " << scaled[9] << "/" << native[9]);
  CHECK(unwritten == 0);
  CHECK(native[0] == kForeground);
  CHECK(native[kSize - 1] == kBackground);
  CHECK(differing_columns == 1);
  CHECK(other_differences == 0);
}
