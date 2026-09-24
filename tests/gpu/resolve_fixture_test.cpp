/**
 * @file        resolve_fixture_test.cpp
 * @brief       EDRAM clear and resolve readback through the GPU plugin (RG-GDK-006)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <bit>
#include <cstdio>

#include <wrl/client.h>

#include <catch2/catch_test_macros.hpp>

#include <rex/cvar.h>
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

// Direct3D 9 resolves by drawing a 3-vertex rectangle list with RB_MODECONTROL
// in copy mode. The rectangle comes from vertex fetch constant 0.
void SubmitResolve(GpuFixture& fixture, uint32_t vertices, uint32_t dest, uint32_t clear_color) {
  reg::RB_SURFACE_INFO surface_info = {};
  surface_info.surface_pitch = kSize;
  surface_info.msaa_samples = xenos::MsaaSamples::k1X;
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
  dest_pitch.copy_dest_pitch = kSize;
  dest_pitch.copy_dest_height = kSize;
  reg::RB_COPY_DEST_INFO dest_info = {};
  dest_info.copy_dest_endian = xenos::Endian128::k8in32;
  dest_info.copy_dest_format = xenos::ColorFormat::k_8_8_8_8;
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
      XE_GPU_REG_RB_COPY_CONTROL, {copy_control.value, dest, dest_pitch.value, dest_info.value}));
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
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  std::printf("GPU fixture: %s\n", fixture->Metadata().c_str());
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));

  uint32_t vertices = fixture->AllocPhysical(0x100);
  fixture->WriteDwords(
      vertices, {std::bit_cast<uint32_t>(0.0f), std::bit_cast<uint32_t>(0.0f),
                 std::bit_cast<uint32_t>(float(kSize)), std::bit_cast<uint32_t>(0.0f),
                 std::bit_cast<uint32_t>(float(kSize)), std::bit_cast<uint32_t>(float(kSize))});
  uint32_t dest = fixture->AllocPhysical(kSize * kSize * 4);
  constexpr uint32_t kClearColor = 0x11223344;

  // The clear happens after the copy, so the first resolve clears EDRAM and
  // the second one copies the cleared color out.
  SubmitResolve(*fixture, vertices, dest, kClearColor);
  SubmitResolve(*fixture, vertices, dest, kClearColor);
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

// Hidden: the backend treats device loss as fatal, so this case ends the
// process. CTest runs it on its own and requires the fatal-error report.
TEST_CASE("Device removal before a submission is reported", "[.device-removal]") {
  REXCVAR_SET(d3d12_dred, true);
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  uint32_t vertices = fixture->AllocPhysical(0x100);
  fixture->WriteDwords(
      vertices, {0, 0, std::bit_cast<uint32_t>(float(kSize)), 0,
                 std::bit_cast<uint32_t>(float(kSize)), std::bit_cast<uint32_t>(float(kSize))});
  uint32_t dest = fixture->AllocPhysical(kSize * kSize * 4);

  Microsoft::WRL::ComPtr<ID3D12Device5> device;
  REQUIRE(SUCCEEDED(fixture->provider().GetDevice()->QueryInterface(IID_PPV_ARGS(&device))));
  device->RemoveDevice();

  // The resolve opens a submission, which checks the device first.
  SubmitResolve(*fixture, vertices, dest, 0);
  fixture->Flush(std::chrono::seconds(10));
  FAIL("device loss was not reported");
}
