/**
 * @file        resolve_fixture_test.cpp
 * @brief       EDRAM clear and resolve readback through the GPU plugin (RG-GDK-006)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <algorithm>
#include <bit>
#include <cstdio>
#include <vector>

#include <wrl/client.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <rex/cvar.h>
#include <rex/graphics/pipeline/texture/util.h>
#include <rex/graphics/registers.h>

#include "gpu_fixture.h"

REXCVAR_DECLARE(bool, d3d12_dred);

namespace {

using namespace rex::graphics;  // NOLINT: XE_GPU_REG_* register indices.
namespace reg = rex::graphics::reg;
namespace xenos = rex::graphics::xenos;
using rex::testing::GpuFixture;

constexpr uint32_t kSize = 64;

uint32_t PackXY(uint32_t x, uint32_t y) {
  return x | (y << 16);
}

struct ResolveTarget {
  uint32_t dest;
  uint32_t pitch = kSize;
  uint32_t height = kSize;
  xenos::ColorFormat format = xenos::ColorFormat::k_8_8_8_8;
  xenos::MsaaSamples msaa = xenos::MsaaSamples::k1X;
};

// Writes the resolve rectangle (x0, y0)-(x1, y1) for vertex fetch 0.
uint32_t AllocRectangle(GpuFixture& fixture, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
  uint32_t vertices = fixture.AllocPhysical(0x100);
  fixture.WriteDwords(vertices,
                      {std::bit_cast<uint32_t>(float(x0)), std::bit_cast<uint32_t>(float(y0)),
                       std::bit_cast<uint32_t>(float(x1)), std::bit_cast<uint32_t>(float(y0)),
                       std::bit_cast<uint32_t>(float(x1)), std::bit_cast<uint32_t>(float(y1))});
  return vertices;
}
uint32_t AllocRectangle(GpuFixture& fixture, uint32_t width, uint32_t height) {
  return AllocRectangle(fixture, 0, 0, width, height);
}

// Direct3D 9 resolves by drawing a 3-vertex rectangle list with RB_MODECONTROL
// in copy mode. The rectangle comes from vertex fetch constant 0.
void SubmitResolve(GpuFixture& fixture, uint32_t vertices, const ResolveTarget& target,
                   uint32_t clear_color) {
  reg::RB_SURFACE_INFO surface_info = {};
  // The EDRAM pitch is in samples, two per pixel horizontally with 4x MSAA.
  surface_info.surface_pitch = kSize * (target.msaa == xenos::MsaaSamples::k4X ? 2 : 1);
  surface_info.msaa_samples = target.msaa;
  reg::RB_COLOR_INFO color_info = {};
  color_info.color_format = xenos::ColorRenderTargetFormat::k_8_8_8_8;
  reg::PA_SC_WINDOW_SCISSOR_TL window_tl = {};
  window_tl.window_offset_disable = 1;
  reg::RB_MODECONTROL mode_control = {};
  mode_control.edram_mode = xenos::EdramMode::kCopy;
  reg::RB_COPY_CONTROL copy_control = {};
  copy_control.color_clear_enable = 1;
  copy_control.copy_command = xenos::CopyCommand::kRaw;
  reg::RB_COPY_DEST_PITCH dest_pitch = {};
  dest_pitch.copy_dest_pitch = target.pitch;
  dest_pitch.copy_dest_height = target.height;
  reg::RB_COPY_DEST_INFO dest_info = {};
  dest_info.copy_dest_endian = xenos::Endian128::k8in32;
  dest_info.copy_dest_format = target.format;
  xenos::xe_gpu_vertex_fetch_t fetch = {};
  fetch.type = xenos::FetchConstantType::kVertex;
  fetch.address = vertices >> 2;
  fetch.endian = xenos::Endian::k8in32;
  fetch.size = 3 * 2;

  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_SURFACE_INFO,
                                          {surface_info.value, color_info.value, 0}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SC_SCREEN_SCISSOR_TL,
                                          {PackXY(0, 0), PackXY(kSize, kSize)}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SC_WINDOW_OFFSET,
                                          {0, window_tl.value, PackXY(kSize, kSize)}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SU_SC_MODE_CNTL, {0}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SU_VTX_CNTL, {0}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_MODECONTROL, {mode_control.value}));
  fixture.Submit(GpuFixture::SetRegisters(
      XE_GPU_REG_RB_COPY_CONTROL,
      {copy_control.value, target.dest, dest_pitch.value, dest_info.value}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_COLOR_CLEAR, {clear_color, clear_color}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_FETCH_00_0,
                                          {fetch.dword_0, fetch.dword_1}));

  reg::VGT_DRAW_INITIATOR initiator = {};
  initiator.prim_type = xenos::PrimitiveType::kRectangleList;
  initiator.source_select = xenos::SourceSelect::kAutoIndex;
  initiator.num_indices = 3;
  fixture.Submit({xenos::MakePacketType3(xenos::PM4_DRAW_INDX_2, 1), initiator.value});
}

}  // namespace

TEST_CASE("EDRAM clear resolves to guest memory with full readback", "[gpu][resolve]") {
  auto msaa = GENERATE(xenos::MsaaSamples::k1X, xenos::MsaaSamples::k2X, xenos::MsaaSamples::k4X);
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  std::printf("GPU fixture: %s\n", fixture->Metadata().c_str());
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));

  uint32_t vertices = AllocRectangle(*fixture, kSize, kSize);
  uint32_t dest = fixture->AllocPhysical(kSize * kSize * 4);
  constexpr uint32_t kClearColor = 0x11223344;
  ResolveTarget target{dest};
  target.msaa = msaa;
  INFO("MSAA samples log2 " << uint32_t(msaa));

  // The clear happens after the copy, so the first resolve clears EDRAM and
  // the second one copies the cleared color out.
  SubmitResolve(*fixture, vertices, target, kClearColor);
  SubmitResolve(*fixture, vertices, target, kClearColor);
  REQUIRE(fixture->Flush());

  uint32_t mismatches = 0;
  for (uint32_t i = 0; i < kSize * kSize; ++i) {
    if (fixture->ReadDword(dest + i * 4) != kClearColor) {
      ++mismatches;
    }
  }
  std::printf("First resolved texel 0x%08X, %u of %u texels differ\n", fixture->ReadDword(dest),
              mismatches, kSize * kSize);
  CHECK(mismatches == 0);
}

// D3D advances RB_COPY_DEST_BASE by whole 32x32 macro tiles, which are 1 KB at
// 8bpp and 2 KB at 16bpp, so the base can sit inside a 4 KB tiled subresource.
// The texel at (x, y) then belongs at (x + 32 * phase, y) of the surface that
// starts at the 4 KB boundary. Source: xenia-canary #1240.
TEST_CASE("Sub-32bpp resolve keeps the macro tile phase of the base", "[gpu][resolve]") {
  struct Case {
    xenos::ColorFormat format;
    uint32_t bpp_log2;
    uint32_t phase;
  };
  auto test = GENERATE(Case{xenos::ColorFormat::k_8, 0, 0}, Case{xenos::ColorFormat::k_5_6_5, 1, 0},
                       Case{xenos::ColorFormat::k_8, 0, 3}, Case{xenos::ColorFormat::k_8, 0, 1},
                       Case{xenos::ColorFormat::k_5_6_5, 1, 1});
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  INFO("bpp_log2 " << test.bpp_log2 << ", phase " << test.phase);

  constexpr uint32_t kRect = 32;
  constexpr uint32_t kPitch = 128;
  constexpr uint32_t kHeight = 32;
  constexpr uint32_t kBytes = 0x4000;
  uint32_t vertices = AllocRectangle(*fixture, kRect, kRect);
  uint32_t surface = fixture->AllocPhysical(kBytes);
  uint32_t macro_tile_bytes = uint32_t(1)
                              << (2 * xenos::kTextureTileWidthHeightLog2 + test.bpp_log2);
  ResolveTarget target{surface + test.phase * macro_tile_bytes, kPitch, kHeight, test.format};
  SubmitResolve(*fixture, vertices, target, 0xFFFFFFFF);
  SubmitResolve(*fixture, vertices, target, 0xFFFFFFFF);
  REQUIRE(fixture->Flush());

  // Every byte of the allocation must be written exactly where the oracle
  // places the rectangle's texels, and nowhere else.
  std::vector<uint8_t> expected(kBytes, 0);
  uint32_t bytes_per_texel = uint32_t(1) << test.bpp_log2;
  for (uint32_t y = 0; y < kRect; ++y) {
    for (uint32_t x = 0; x < kRect; ++x) {
      int32_t offset = rex::graphics::texture_util::GetTiledOffset2D(
          int32_t(x + test.phase * xenos::kTextureTileWidthHeight), int32_t(y), kPitch,
          test.bpp_log2);
      REQUIRE(uint32_t(offset) + bytes_per_texel <= kBytes);
      std::fill_n(expected.begin() + offset, bytes_per_texel, uint8_t(0xFF));
    }
  }
  const uint8_t* actual = fixture->memory()->TranslatePhysical<const uint8_t*>(surface);
  uint32_t missing = 0, stray = 0;
  for (uint32_t i = 0; i < kBytes; ++i) {
    if (expected[i] && actual[i] != 0xFF) {
      ++missing;
    } else if (!expected[i] && actual[i]) {
      ++stray;
    }
  }
  std::printf("bpp_log2 %u phase %u: %u missing, %u stray bytes\n", test.bpp_log2, test.phase,
              missing, stray);
  CHECK(missing == 0);
  CHECK(stray == 0);
}

// A uniform clear can't show texels read back from the wrong place, so this
// resolves a 4x4 grid of 8x8 cells, each with its own color, into the same
// destination. Each cell's texels must hold one value, distinct per cell, at
// the addresses the tiling oracle gives. Run with draw_resolution_scale_* to
// cover the scaled readback (#58).
TEST_CASE("Resolve readback keeps texel positions", "[gpu][resolve]") {
  struct Case {
    xenos::ColorFormat format;
    uint32_t bpp_log2;
    uint32_t phase;
  };
  auto test =
      GENERATE(Case{xenos::ColorFormat::k_8, 0, 0}, Case{xenos::ColorFormat::k_8, 0, 1},
               Case{xenos::ColorFormat::k_5_6_5, 1, 0}, Case{xenos::ColorFormat::k_5_6_5, 1, 1},
               Case{xenos::ColorFormat::k_8_8_8_8, 2, 0});
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  INFO("bpp_log2 " << test.bpp_log2 << ", phase " << test.phase);

  constexpr uint32_t kCells = 4;
  constexpr uint32_t kCellSize = 8;
  constexpr uint32_t kHeight = kCells * kCellSize;
  constexpr uint32_t kPitch = 128;
  constexpr uint32_t kBytes = 0x8000;
  uint32_t surface = fixture->AllocPhysical(kBytes);
  uint32_t macro_tile_bytes = uint32_t(1)
                              << (2 * xenos::kTextureTileWidthHeightLog2 + test.bpp_log2);
  ResolveTarget target{surface + test.phase * macro_tile_bytes, kPitch, kHeight, test.format};
  for (uint32_t cell = 0; cell < kCells * kCells; ++cell) {
    uint32_t x = (cell % kCells) * kCellSize, y = (cell / kCells) * kCellSize;
    uint32_t vertices = AllocRectangle(*fixture, x, y, x + kCellSize, y + kCellSize);
    // Channels of 15 * (cell + 1) stay distinct even when packed to 5 bits.
    uint32_t color = 0x01010101 * (15 * (cell + 1));
    SubmitResolve(*fixture, vertices, target, color);
    SubmitResolve(*fixture, vertices, target, color);
  }
  REQUIRE(fixture->Flush());

  const uint8_t* actual = fixture->memory()->TranslatePhysical<const uint8_t*>(surface);
  uint32_t bytes_per_texel = uint32_t(1) << test.bpp_log2;
  std::vector<bool> covered(kBytes, false);
  std::vector<std::vector<uint8_t>> cell_values(kCells * kCells);
  uint32_t mismatches = 0;
  for (uint32_t y = 0; y < kHeight; ++y) {
    for (uint32_t x = 0; x < kCells * kCellSize; ++x) {
      int32_t offset = rex::graphics::texture_util::GetTiledOffset2D(
          int32_t(x + test.phase * xenos::kTextureTileWidthHeight), int32_t(y), kPitch,
          test.bpp_log2);
      REQUIRE(uint32_t(offset) + bytes_per_texel <= kBytes);
      std::vector<uint8_t> texel(actual + offset, actual + offset + bytes_per_texel);
      std::fill_n(covered.begin() + offset, bytes_per_texel, true);
      std::vector<uint8_t>& expected = cell_values[(y / kCellSize) * kCells + x / kCellSize];
      if (expected.empty()) {
        expected = texel;
      } else if (texel != expected) {
        ++mismatches;
      }
    }
  }
  uint32_t stray = 0;
  for (uint32_t i = 0; i < kBytes; ++i) {
    if (!covered[i] && actual[i]) {
      ++stray;
    }
  }
  uint32_t duplicates = 0;
  for (uint32_t a = 0; a < cell_values.size(); ++a) {
    CHECK(std::any_of(cell_values[a].begin(), cell_values[a].end(),
                      [](uint8_t v) { return v != 0; }));
    for (uint32_t b = a + 1; b < cell_values.size(); ++b) {
      duplicates += cell_values[a] == cell_values[b];
    }
  }
  std::printf(
      "positions bpp_log2 %u phase %u: %u texels off their cell, %u duplicate cells, %u stray "
      "bytes\n",
      test.bpp_log2, test.phase, mismatches, duplicates, stray);
  CHECK(mismatches == 0);
  CHECK(duplicates == 0);
  CHECK(stray == 0);
}

// Hidden: the backend treats device loss as fatal, so this case ends the
// process. CTest runs it on its own and requires the fatal-error report.
TEST_CASE("Device removal before a submission is reported", "[.device-removal]") {
  REXCVAR_SET(d3d12_dred, true);
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  uint32_t vertices = AllocRectangle(*fixture, kSize, kSize);
  ResolveTarget target{fixture->AllocPhysical(kSize * kSize * 4)};

  Microsoft::WRL::ComPtr<ID3D12Device5> device;
  REQUIRE(SUCCEEDED(fixture->provider().GetDevice()->QueryInterface(IID_PPV_ARGS(&device))));
  device->RemoveDevice();

  // The resolve opens a submission, which checks the device first.
  SubmitResolve(*fixture, vertices, target, 0);
  fixture->Flush(std::chrono::seconds(10));
  FAIL("device loss was not reported");
}
