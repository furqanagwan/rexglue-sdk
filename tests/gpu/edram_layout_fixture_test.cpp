/**
 * @file        edram_layout_fixture_test.cpp
 * @brief       EDRAM sample layout across MSAA aliases through the GPU plugin (RG-GDK-009)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <bit>
#include <cstdio>
#include <functional>
#include <set>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <rex/cvar.h>
#include <rex/graphics/pipeline/texture/util.h>
#include <rex/graphics/registers.h>

#include "gpu_fixture.h"
#include "guest_draw.h"

namespace {

using namespace rex::graphics;  // NOLINT: XE_GPU_REG_* register indices.
namespace reg = rex::graphics::reg;
namespace xenos = rex::graphics::xenos;
using rex::testing::GpuFixture;
using namespace rex::testing::guest_draw;  // NOLINT

void DrawPixels(GpuFixture& fixture, const Surface& surface, uint32_t width, uint32_t height,
                const std::function<uint32_t(uint32_t, uint32_t)>& color) {
  SetupDraw(fixture, surface, width, height);
  for (uint32_t y = 0; y < height; ++y) {
    for (uint32_t x = 0; x < width; ++x) {
      DrawRect(fixture, x, y, x + 1, y + 1, color(x, y));
    }
  }
}

uint32_t PixelColor(uint32_t x, uint32_t y) {
  return x | (y << 8) | 0x80400000;
}

struct Coord {
  uint32_t x, y;
};

Coord CanonicalSampleTo1x(xenos::MsaaSamples msaa, uint32_t x, uint32_t y, uint32_t s) {
  if (msaa == xenos::MsaaSamples::k4X) {
    return {((x & ~1u) << 1) | (x & 1) | ((s & 1) << 1), ((y & ~1u) << 1) | (y & 1) | (s & 2)};
  }
  return {(x & ~2u) | (s << 1), ((y & ~1u) << 1) | (y & 1) | (x & 2)};
}

}

TEST_CASE("1x EDRAM re-aliased as MSAA uses the canonical sample layout", "[gpu][edram]") {
  auto msaa = GENERATE(xenos::MsaaSamples::k2X, xenos::MsaaSamples::k4X);
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));

  REQUIRE(rex::cvar::SetFlagByName("async_shader_compilation", "false"));
  bool is_4x = msaa == xenos::MsaaSamples::k4X;
  INFO((is_4x ? "4x" : "2x"));

  constexpr uint32_t k1xSize = 16;
  Surface surface_1x = {xenos::MsaaSamples::k1X, 64};
  DrawPixels(*fixture, surface_1x, k1xSize, k1xSize, PixelColor);
  uint32_t reference = fixture->AllocPhysical(0x1000);
  Resolve(*fixture, surface_1x, k1xSize, k1xSize, xenos::CopySampleSelect::k0, reference);

  Surface surface_msaa = {msaa, 64};
  uint32_t msaa_width = is_4x ? k1xSize / 2 : k1xSize;
  uint32_t msaa_height = k1xSize / 2;
  uint32_t sample_count = is_4x ? 4 : 2;
  std::vector<uint32_t> samples(sample_count);
  for (uint32_t s = 0; s < sample_count; ++s) {
    samples[s] = fixture->AllocPhysical(0x1000);
    Resolve(*fixture, surface_msaa, msaa_width, msaa_height, xenos::CopySampleSelect(s),
            samples[s]);
  }
  REQUIRE(fixture->Flush(std::chrono::seconds(30)));

  std::set<uint32_t> distinct;
  for (uint32_t y = 0; y < k1xSize; ++y) {
    for (uint32_t x = 0; x < k1xSize; ++x) {
      distinct.insert(ReadTexel(*fixture, reference, x, y));
    }
  }
  REQUIRE(distinct.size() == k1xSize * k1xSize);

  uint32_t mismatches = 0;
  for (uint32_t s = 0; s < sample_count; ++s) {
    for (uint32_t y = 0; y < msaa_height; ++y) {
      for (uint32_t x = 0; x < msaa_width; ++x) {
        Coord c = CanonicalSampleTo1x(msaa, x, y, s);
        uint32_t expected = ReadTexel(*fixture, reference, c.x, c.y);
        uint32_t actual = ReadTexel(*fixture, samples[s], x, y);
        if (actual != expected) {
          if (++mismatches <= 4) {
            UNSCOPED_INFO("sample " << s << " (" << x << ", " << y << "): 0x" << std::hex << actual
                                    << ", expected 0x" << expected << std::dec);
          }
        }
      }
    }
  }
  std::printf("1x as %s: %u samples off the canonical layout\n", is_4x ? "4x" : "2x", mismatches);
  CHECK(mismatches == 0);
}

TEST_CASE("MSAA EDRAM re-aliased as 1x uses the canonical sample layout", "[gpu][edram]") {
  auto msaa = GENERATE(xenos::MsaaSamples::k2X, xenos::MsaaSamples::k4X);
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));

  REQUIRE(rex::cvar::SetFlagByName("async_shader_compilation", "false"));
  bool is_4x = msaa == xenos::MsaaSamples::k4X;
  INFO((is_4x ? "4x" : "2x"));

  Surface surface_msaa = {msaa, 64};
  uint32_t msaa_width = is_4x ? 8 : 16, msaa_height = 8;
  DrawPixels(*fixture, surface_msaa, msaa_width, msaa_height, PixelColor);
  Surface surface_1x = {xenos::MsaaSamples::k1X, 64};
  uint32_t aliased = fixture->AllocPhysical(0x1000);
  Resolve(*fixture, surface_1x, 16, 16, xenos::CopySampleSelect::k0, aliased);
  uint32_t reference = fixture->AllocPhysical(0x1000);
  Resolve(*fixture, surface_msaa, msaa_width, msaa_height, xenos::CopySampleSelect::k0, reference);
  REQUIRE(fixture->Flush(std::chrono::seconds(30)));

  std::set<uint32_t> distinct;
  for (uint32_t y = 0; y < msaa_height; ++y) {
    for (uint32_t x = 0; x < msaa_width; ++x) {
      distinct.insert(ReadTexel(*fixture, reference, x, y));
    }
  }
  REQUIRE(distinct.size() == msaa_width * msaa_height);

  uint32_t mismatches = 0;
  uint32_t sample_count = is_4x ? 4 : 2;
  for (uint32_t s = 0; s < sample_count; ++s) {
    for (uint32_t y = 0; y < msaa_height; ++y) {
      for (uint32_t x = 0; x < msaa_width; ++x) {
        Coord c = CanonicalSampleTo1x(msaa, x, y, s);
        uint32_t expected = ReadTexel(*fixture, reference, x, y);
        uint32_t actual = ReadTexel(*fixture, aliased, c.x, c.y);
        if (actual != expected) {
          if (++mismatches <= 4) {
            UNSCOPED_INFO("1x (" << c.x << ", " << c.y << ") from sample " << s << " of (" << x
                                 << ", " << y << "): 0x" << std::hex << actual << ", expected 0x"
                                 << expected << std::dec);
          }
        }
      }
    }
  }
  std::printf("%s as 1x: %u pixels off the canonical layout\n", is_4x ? "4x" : "2x", mismatches);
  CHECK(mismatches == 0);
}

TEST_CASE("Color aliasing depth keeps a read-only depth test", "[gpu][edram]") {
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  REQUIRE(rex::cvar::SetFlagByName("async_shader_compilation", "false"));

  constexpr uint32_t kWidth = 80, kHeight = 16, kPitch = 96;
  Surface surface = {xenos::MsaaSamples::k1X, kWidth};

  DrawOptions depth_fill;
  depth_fill.z = 0.5f;
  depth_fill.depth_control.z_enable = 1;
  depth_fill.depth_control.z_write_enable = 1;
  depth_fill.depth_control.zfunc = xenos::CompareFunction::kAlways;
  depth_fill.color_mask = 0;
  SetupDraw(*fixture, surface, kWidth, kHeight, depth_fill);
  DrawRect(*fixture, 0, 0, kWidth, kHeight, 0);
  uint32_t before = fixture->AllocPhysical(0x4000);
  Resolve(*fixture, surface, kWidth, kHeight, xenos::CopySampleSelect::k0, before, kPitch);

  for (uint32_t half = 0; half < 2; ++half) {
    DrawOptions stencil_byte;
    stencil_byte.z = half ? 0.75f : 0.25f;
    stencil_byte.depth_control.z_enable = 1;
    stencil_byte.depth_control.zfunc = xenos::CompareFunction::kLess;
    stencil_byte.color_mask = 0b0001;
    SetupDraw(*fixture, surface, kWidth, kHeight, stencil_byte);
    DrawRect(*fixture, half * (kWidth / 2), 0, (half + 1) * (kWidth / 2), kHeight, 0x55);
  }
  uint32_t after = fixture->AllocPhysical(0x4000);
  Resolve(*fixture, surface, kWidth, kHeight, xenos::CopySampleSelect::k0, after, kPitch);
  REQUIRE(fixture->Flush(std::chrono::seconds(30)));

  uint32_t depth_lost = 0, test_ignored = 0, not_written = 0;
  for (uint32_t y = 0; y < kHeight; ++y) {
    for (uint32_t x = 0; x < kWidth; ++x) {
      uint32_t b = ReadTexel(*fixture, before, x, y, kPitch);
      uint32_t a = ReadTexel(*fixture, after, x, y, kPitch);
      depth_lost += (a & ~0xFFu) != (b & ~0xFFu);
      if (x < kWidth / 2) {
        not_written += (a & 0xFF) != 0x55;
      } else {
        test_ignored += (a & 0xFF) != (b & 0xFF);
      }
    }
  }
  uint32_t sample = ReadTexel(*fixture, before, 0, 0, kPitch);
  std::printf(
      "depth alias: before 0x%08X, %u pixels lost depth bits, %u failing pixels written, %u "
      "passing pixels not written\n",
      sample, depth_lost, test_ignored, not_written);
  CHECK((sample & ~0xFFu) != 0);
  CHECK(depth_lost == 0);
  CHECK(test_ignored == 0);
  CHECK(not_written == 0);
}

TEST_CASE("MSAA float24 depth keeps host precision through an alias", "[gpu][edram]") {
  auto msaa = GENERATE(xenos::MsaaSamples::k2X, xenos::MsaaSamples::k4X);
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  REQUIRE(rex::cvar::SetFlagByName("async_shader_compilation", "false"));
  bool is_4x = msaa == xenos::MsaaSamples::k4X;
  INFO((is_4x ? "4x" : "2x"));

  constexpr uint32_t kWidth = 32, kHeight = 16;

  Surface surface = {msaa, 80};

  constexpr uint32_t kColorBaseTiles = 1024;
  DrawOptions gradient;
  gradient.z = 0.1f;
  gradient.z_right = 0.9f;
  gradient.depth_format = xenos::DepthRenderTargetFormat::kD24FS8;
  gradient.color_base_tiles = kColorBaseTiles;
  gradient.depth_control.z_enable = 1;
  gradient.depth_control.z_write_enable = 1;
  gradient.depth_control.zfunc = xenos::CompareFunction::kAlways;
  gradient.color_mask = 0;
  SetupDraw(*fixture, surface, kWidth, kHeight, gradient);
  DrawRect(*fixture, 0, 0, kWidth, kHeight, 0);

  DrawOptions alias;
  alias.color_mask = 0b0001;
  SetupDraw(*fixture, surface, kWidth, kHeight, alias);
  DrawRect(*fixture, 0, 0, kWidth, kHeight, 0x55);

  DrawOptions equal = gradient;
  equal.depth_control.z_write_enable = 0;
  equal.depth_control.zfunc = xenos::CompareFunction::kEqual;
  equal.color_mask = 0xF;
  SetupDraw(*fixture, surface, kWidth, kHeight, equal);
  DrawRect(*fixture, 0, 0, kWidth, kHeight, 0xFFFFFFFF);
  uint32_t result = fixture->AllocPhysical(0x1000);
  Resolve(*fixture, surface, kWidth, kHeight, xenos::CopySampleSelect::k0123, result, 32,
          kColorBaseTiles);
  REQUIRE(fixture->Flush(std::chrono::seconds(30)));

  uint32_t failed = 0;
  for (uint32_t y = 0; y < kHeight; ++y) {
    for (uint32_t x = 0; x < kWidth; ++x) {
      failed += ReadTexel(*fixture, result, x, y) != 0xFFFFFFFF;
    }
  }
  std::printf("%s float24 depth alias: %u of %u pixels failed the equal test\n",
              is_4x ? "4x" : "2x", failed, kWidth * kHeight);
  CHECK(failed == 0);
}

TEST_CASE("64bpp EDRAM re-aliased as 32bpp uses the canonical sample layout", "[gpu][edram]") {
  auto msaa = GENERATE(xenos::MsaaSamples::k1X, xenos::MsaaSamples::k4X);
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  REQUIRE(rex::cvar::SetFlagByName("async_shader_compilation", "false"));
  bool is_4x = msaa == xenos::MsaaSamples::k4X;
  INFO((is_4x ? "4x" : "1x"));

  Surface surface_64bpp = {msaa, 40};
  uint32_t width = is_4x ? 8 : 16, height = is_4x ? 8 : 16;
  DrawOptions options;
  options.color_format = xenos::ColorRenderTargetFormat::k_32_32_FLOAT;
  SetupDraw(*fixture, surface_64bpp, width, height, options);
  auto value = [](uint32_t x, uint32_t y, uint32_t half) {
    return 1.0f + float(x) + 64.0f * float(y) + (half ? 0.5f : 0.25f);
  };
  for (uint32_t y = 0; y < height; ++y) {
    for (uint32_t x = 0; x < width; ++x) {
      DrawRectFloat(*fixture, x, y, x + 1, y + 1, value(x, y, 0), value(x, y, 1), 0.0f, 0.0f);
    }
  }
  constexpr uint32_t k32bppWidth = 32, k32bppHeight = 16;
  uint32_t aliased = fixture->AllocPhysical(0x1000);
  Resolve(*fixture, {xenos::MsaaSamples::k1X, 80}, k32bppWidth, k32bppHeight,
          xenos::CopySampleSelect::k0, aliased);
  REQUIRE(fixture->Flush(std::chrono::seconds(30)));

  uint32_t mismatches = 0;
  uint32_t sample_count = is_4x ? 4 : 1;
  for (uint32_t s = 0; s < sample_count; ++s) {
    for (uint32_t y = 0; y < height; ++y) {
      for (uint32_t x = 0; x < width; ++x) {
        Coord c = is_4x ? CanonicalSampleTo1x(msaa, x, y, s) : Coord{x, y};
        for (uint32_t half = 0; half < 2; ++half) {
          uint32_t expected = std::bit_cast<uint32_t>(value(x, y, half));
          uint32_t actual = ReadTexel(*fixture, aliased, 2 * c.x + half, c.y);
          if (actual != expected && ++mismatches <= 4) {
            UNSCOPED_INFO("sample " << s << " (" << x << ", " << y << ") half " << half << ": 0x"
                                    << std::hex << actual << ", expected 0x" << expected
                                    << std::dec);
          }
        }
      }
    }
  }
  std::printf("%s 64bpp as 32bpp: %u dwords off the canonical layout\n", is_4x ? "4x" : "1x",
              mismatches);
  CHECK(mismatches == 0);
}
