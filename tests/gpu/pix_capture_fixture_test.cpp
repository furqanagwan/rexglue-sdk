/**
 * @file        pix_capture_fixture_test.cpp
 * @brief       PIX captures of a labeled draw and resolve (RG-GDK-028)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <cstdio>
#include <functional>

#include <catch2/catch_test_macros.hpp>

#include <rex/cvar.h>

#include "gpu_fixture.h"
#include "guest_draw.h"

namespace {

using rex::testing::GpuFixture;
using namespace rex::testing::guest_draw;  // NOLINT

constexpr uint32_t kSize = 32;
constexpr uint32_t kColor = 0xFF336699;

uint32_t DrawAndResolve(GpuFixture& fixture, const std::function<void()>& begin,
                        const std::function<void()>& end) {
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));

  REQUIRE(rex::cvar::SetFlagByName("async_shader_compilation", "false"));

  const Surface surface{rex::graphics::xenos::MsaaSamples::k1X, kSize};
  uint32_t dest = fixture.AllocPhysical(kSize * kSize * 4);
  SetupDraw(fixture, surface, kSize, kSize);
  REQUIRE(fixture.Flush());

  begin();
  DrawRect(fixture, 0, 0, kSize, kSize, kColor);
  Resolve(fixture, surface, kSize, kSize, rex::graphics::xenos::CopySampleSelect::k0, dest);
  REQUIRE(fixture.Flush());
  end();
  return ReadTexel(fixture, dest, kSize / 2, kSize / 2);
}

}

TEST_CASE("PIX captures a labeled draw and resolve", "[.pix-capture]") {
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }

  IDXGraphicsAnalysis* analysis = fixture->provider().GetGraphicsAnalysis();
  if (!analysis) {
    SKIP("Not running under PIX; use scripts/pix_capture_fixture.ps1");
  }
  std::printf("GPU fixture: %s\n", fixture->Metadata().c_str());

  CHECK(DrawAndResolve(
            *fixture, [&] { analysis->BeginCapture(); }, [&] { analysis->EndCapture(); }) ==
        kColor);
}
