/**
 * @file        resolve_gamma_fixture_test.cpp
 * @brief       8_8_8_8_GAMMA and copy_dest_number in full resolves (RG-GDK-073)
 *
 * Resolves of 8_8_8_8_GAMMA render targets decode the PWL curve to linear
 * before MSAA averaging, and every destination gets the linear values; full
 * resolves pack fixed destinations by copy_dest_number (xenia-canary
 * d119505289, 2ddc5ef737, fc48d37cdc).
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <cstdint>
#include <cstdlib>
#include <string>

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

struct RestoreCvars {
  ~RestoreCvars() {
    for (const char* name : {"render_target_path_d3d12", "readback_resolve"}) {
      rex::cvar::ResetToDefault(name);
    }
  }
};

// Draws color into a kSize square render target of source_format and
// resolves it with format. Returns the center texel.
bool DrawAndResolve(const char* path, xenos::MsaaSamples msaa, xenos::CopySampleSelect sample,
                    uint32_t color, const ResolveFormat& format, uint32_t& texel,
                    std::string& error) {
  auto fixture = GpuFixture::Create(&error, {{"render_target_path_d3d12", path}});
  if (!fixture) {
    return false;
  }
  if (std::string(path) == "rov" && (fixture->provider().IsAdapterSoftware() ||
                                     !fixture->provider().AreRasterizerOrderedViewsSupported())) {
    error = "no hardware ROV support";
    return false;
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  const Surface surface{msaa, kSize};
  DrawOptions options;
  options.color_format = format.source;
  SetupDraw(*fixture, surface, kSize, kSize, options);
  DrawRect(*fixture, 0, 0, kSize, kSize, color);
  const uint32_t dest = fixture->AllocPhysical(kSize * kSize * 4);
  Resolve(*fixture, surface, kSize, kSize, sample, dest, kSize, 0, format);
  REQUIRE(fixture->Flush());
  texel = ReadTexel(*fixture, dest, kSize / 2, kSize / 2);
  return true;
}

bool Near(uint32_t value, uint32_t expected, uint32_t tolerance) {
  return uint32_t(std::abs(int32_t(value) - int32_t(expected))) <= tolerance;
}

}  // namespace

TEST_CASE("Gamma render targets resolve to linear", "[gpu][resolve-gamma]") {
  const char* path = GENERATE("rtv", "rov");
  const bool msaa = GENERATE(false, true);
  INFO("render_target_path_d3d12 " << path << ", 4x MSAA averaged " << msaa);
  RestoreCvars restore;
  std::string error;
  ResolveFormat format;
  format.source = xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA;
  const xenos::MsaaSamples samples = msaa ? xenos::MsaaSamples::k4X : xenos::MsaaSamples::k1X;
  const xenos::CopySampleSelect select =
      msaa ? xenos::CopySampleSelect::k0123 : xenos::CopySampleSelect::k0;
  // Linear 0x80 (0.502) is 192 on the PWL curve, which decodes to 516/1023
  // (8-bit 129, 10-bit 516). Raw copies of the encoded bytes give 192.
  uint32_t texel = 0;
  if (!DrawAndResolve(path, samples, select, 0xFF808080, format, texel, error)) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  INFO(std::hex << "8_8_8_8 texel 0x" << texel);
  CHECK(Near(texel & 0xFF, 129, 2));
  CHECK(Near((texel >> 8) & 0xFF, 129, 2));
  CHECK(Near((texel >> 16) & 0xFF, 129, 2));
  // Alpha isn't gamma encoded.
  CHECK((texel >> 24) == 0xFF);

  // A destination that isn't 8_8_8_8 gets the same linear values.
  format.dest = xenos::ColorFormat::k_2_10_10_10;
  REQUIRE(DrawAndResolve(path, samples, select, 0xFF808080, format, texel, error));
  INFO(std::hex << "2_10_10_10 texel 0x" << texel);
  CHECK(Near(texel & 0x3FF, 516, 6));
  CHECK((texel >> 30) == 3);
}

TEST_CASE("Full resolves pack fixed destinations by copy_dest_number", "[gpu][resolve-gamma]") {
  RestoreCvars restore;
  std::string error;
  ResolveFormat format;
  uint32_t unsigned_texel = 0;
  if (!DrawAndResolve("rtv", xenos::MsaaSamples::k1X, xenos::CopySampleSelect::k0, 0xFFFFFFFF,
                      format, unsigned_texel, error)) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  CHECK(unsigned_texel == 0xFFFFFFFF);
  // 1.0 as a signed repeating fraction is 127; a raw copy would keep 255.
  format.dest_number = xenos::SurfaceNumberFormat::kSignedRepeatingFraction;
  uint32_t signed_texel = 0;
  REQUIRE(DrawAndResolve("rtv", xenos::MsaaSamples::k1X, xenos::CopySampleSelect::k0, 0xFFFFFFFF,
                         format, signed_texel, error));
  CHECK(signed_texel == 0x7F7F7F7F);
  // An unsigned integer destination takes the value itself, clamped: 1.
  format.dest_number = xenos::SurfaceNumberFormat::kUnsignedInteger;
  uint32_t integer_texel = 0;
  REQUIRE(DrawAndResolve("rtv", xenos::MsaaSamples::k1X, xenos::CopySampleSelect::k0, 0xFFFFFFFF,
                         format, integer_texel, error));
  CHECK(integer_texel == 0x01010101);
}
