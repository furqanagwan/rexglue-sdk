/**
 * @file        invalid_fetch_fixture_test.cpp
 * @brief       Draws whose vertex fetch constant has a texture type
 *
 * Some titles draw with a vertex fetch constant typed as a texture (character
 * models in 5454086C and 425607FE). With gpu_allow_invalid_fetch_constants
 * (the default) such draws now run instead of being dropped (xenia-canary
 * b083312b8).
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

}

TEST_CASE("A vertex fetch constant with a texture type draws only when allowed",
          "[gpu][invalid-fetch]") {
  const bool allow = GENERATE(true, false);
  INFO("gpu_allow_invalid_fetch_constants " << allow);
  std::string error;
  auto fixture = GpuFixture::Create(&error, {{"async_shader_compilation", "false"}});
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  REQUIRE(rex::cvar::SetFlagByName("gpu_allow_invalid_fetch_constants", allow ? "true" : "false"));

  const Surface surface{xenos::MsaaSamples::k1X, kSize};
  uint32_t dest = fixture->AllocPhysical(kSize * kSize * 4);
  DrawOptions options;
  options.fetch_type = xenos::FetchConstantType::kTexture;
  SetupDraw(*fixture, surface, kSize, kSize, options);
  DrawRect(*fixture, 0, 0, kSize, kSize, kColor);
  Resolve(*fixture, surface, kSize, kSize, xenos::CopySampleSelect::k0, dest);
  REQUIRE(fixture->Flush());
  const uint32_t texel = ReadTexel(*fixture, dest, kSize / 2, kSize / 2);
  rex::cvar::ResetToDefault("gpu_allow_invalid_fetch_constants");
  rex::cvar::ResetToDefault("readback_resolve");
  rex::cvar::ResetToDefault("async_shader_compilation");
  if (allow) {
    CHECK(texel == kColor);
  } else {
    CHECK(texel != kColor);
  }
}
