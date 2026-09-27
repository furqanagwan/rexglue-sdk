/**
 * @file        async_draw_fixture_test.cpp
 * @brief       Draws that can't be skipped while their pipeline compiles
 *
 * With async_shader_compilation, a draw whose pipeline is still being created
 * used to be skipped. That only self-heals for a pass redrawn every frame; a
 * one-off render to a texture lost its output for good (the PIX fixture's
 * single draw read back 0 until async compilation was turned off). Such draws
 * now wait for the real pipeline (has207/xenia-edge de8e60601).
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <rex/cvar.h>

#include "gpu_fixture.h"
#include "guest_draw.h"

namespace {

using rex::testing::GpuFixture;
using namespace rex::testing::guest_draw;  // NOLINT
namespace xenos = rex::graphics::xenos;

constexpr uint32_t kSize = 32;
constexpr uint32_t kColor = 0xFF5599CC;

}  // namespace

TEST_CASE("A one-off draw under async compilation waits for its pipeline",
          "[gpu][async-pipeline]") {
  // In samples: 32 is a 1-tile render target (small, generated-data sized);
  // 320 is 4 tiles wide. Both are drawn once, never before.
  auto pitch = GENERATE(uint32_t(32), uint32_t(320));
  INFO("render target pitch " << pitch << " samples");
  std::string error;
  auto fixture = GpuFixture::Create(&error, {{"async_shader_compilation", "true"}});
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));

  const Surface surface{xenos::MsaaSamples::k1X, pitch};
  uint32_t dest = fixture->AllocPhysical(kSize * kSize * 4);
  SetupDraw(*fixture, surface, kSize, kSize);
  // A pixel shader this fixture hasn't seen, so its pipeline is created
  // asynchronously when the draw needs it.
  DrawRect(*fixture, 0, 0, kSize, kSize, kColor);
  Resolve(*fixture, surface, kSize, kSize, xenos::CopySampleSelect::k0, dest);
  REQUIRE(fixture->Flush());
  CHECK(ReadTexel(*fixture, dest, kSize / 2, kSize / 2) == kColor);
}
