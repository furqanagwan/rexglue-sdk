/**
 * @file        shader_replacement_fixture_test.cpp
 * @brief       A title's replacement shader reaches the GPU (RG-GDK-067)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

#include <rex/cvar.h>
#include <rex/filesystem.h>
#include <rex/hash.h>
#include <rex/graphics/xenos.h>

#include "gpu_fixture.h"
#include "guest_draw.h"

namespace {

namespace xenos = rex::graphics::xenos;
using rex::testing::GpuFixture;
using namespace rex::testing::guest_draw;  // NOLINT

uint64_t PixelShaderHash() {
  std::vector<uint8_t> bytes;
  for (uint32_t dword : kPixelShader) {
    for (int shift = 24; shift >= 0; shift -= 8) {
      bytes.push_back(uint8_t(dword >> shift));
    }
  }
  return XXH3_64bits(bytes.data(), bytes.size());
}

bool DrawAndRead(bool replacements, uint32_t color, uint32_t& texel_out, std::string& error) {
  auto fixture =
      GpuFixture::Create(&error, {{"shader_replacements", replacements ? "true" : "false"},
                                  {"render_target_path_d3d12", "rtv"}});
  if (!fixture) {
    return false;
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));

  REQUIRE(rex::cvar::SetFlagByName("async_shader_compilation", "false"));
  const Surface surface = {xenos::MsaaSamples::k1X, 64};
  SetupDraw(*fixture, surface, 8, 8);
  DrawRect(*fixture, 0, 0, 8, 8, color);
  const uint32_t dest = fixture->AllocPhysical(0x1000);
  Resolve(*fixture, surface, 8, 8, xenos::CopySampleSelect::k0, dest);
  REQUIRE(fixture->Flush());
  texel_out = fixture->ReadDword(dest);
  return true;
}

}

TEST_CASE("A title's replacement pixel shader stands in for the translated one",
          "[gpu][replacements]") {
  const std::filesystem::path folder =
      rex::filesystem::GetExecutableFolder() / "shader_replacements";
  std::filesystem::remove_all(folder);
  std::filesystem::create_directories(folder);
  std::filesystem::copy_file(REXGLUE_TEST_REPLACEMENT_DXBC,
                             folder / fmt::format("{:016X}.ps_rtv.dxbc", PixelShaderHash()));

  constexpr uint32_t kMagenta = 0xFFFF00FF, kGreen = 0xFF00FF00;
  std::string error;
  uint32_t magenta = 0, green = 0, replaced = 0;
  if (!DrawAndRead(false, kMagenta, magenta, error)) {
    std::filesystem::remove_all(folder);
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(DrawAndRead(false, kGreen, green, error));

  REQUIRE(DrawAndRead(true, kGreen, replaced, error));
  std::filesystem::remove_all(folder);

  rex::cvar::ResetToDefault("shader_replacements");
  rex::cvar::ResetToDefault("render_target_path_d3d12");

  INFO("magenta 0x" << std::hex << magenta << ", green 0x" << green << ", replaced 0x" << replaced);
  CHECK(magenta != green);
  CHECK(replaced == magenta);
}
