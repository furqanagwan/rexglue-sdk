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

// Draws one pixel at a time with its own constant color, so every pixel of the
// region (0, 0)-(width, height) holds a distinct value regardless of how the
// rasterizer treats the edges.
void DrawPixels(GpuFixture& fixture, const Surface& surface, uint32_t width, uint32_t height,
                const std::function<uint32_t(uint32_t, uint32_t)>& color) {
  SetupDraw(fixture, surface, width, height);
  for (uint32_t y = 0; y < height; ++y) {
    for (uint32_t x = 0; x < width; ++x) {
      DrawRect(fixture, x, y, x + 1, y + 1, color(x, y));
    }
  }
}

// Resolves (0, 0)-(width, height) of the 32bpp color target at EDRAM base 0,
// one sample of it with MSAA, to a 32-high k_8_8_8_8 tiled texture.
void Resolve(GpuFixture& fixture, const Surface& surface, uint32_t width, uint32_t height,
             xenos::CopySampleSelect sample, uint32_t dest, uint32_t dest_pitch = 32,
             uint32_t color_base_tiles = 0) {
  uint32_t vertices = fixture.AllocPhysical(0x100);
  fixture.WriteDwords(
      vertices, {0, 0, std::bit_cast<uint32_t>(float(width)), 0,
                 std::bit_cast<uint32_t>(float(width)), std::bit_cast<uint32_t>(float(height))});
  reg::RB_SURFACE_INFO surface_info = {};
  surface_info.surface_pitch = surface.pitch;
  surface_info.msaa_samples = surface.msaa;
  reg::RB_COLOR_INFO color_info = {};
  color_info.color_format = xenos::ColorRenderTargetFormat::k_8_8_8_8;
  color_info.color_base = color_base_tiles;
  reg::PA_SC_WINDOW_SCISSOR_TL window_tl = {};
  window_tl.window_offset_disable = 1;
  reg::RB_MODECONTROL mode_control = {};
  mode_control.edram_mode = xenos::EdramMode::kCopy;
  reg::RB_COPY_CONTROL copy_control = {};
  copy_control.copy_sample_select = sample;
  copy_control.copy_command = xenos::CopyCommand::kRaw;
  reg::RB_COPY_DEST_PITCH copy_dest_pitch = {};
  copy_dest_pitch.copy_dest_pitch = dest_pitch;
  copy_dest_pitch.copy_dest_height = 32;
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
                                          {PackXY(0, 0), PackXY(width, height)}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SC_WINDOW_OFFSET,
                                          {0, window_tl.value, PackXY(width, height)}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_MODECONTROL, {mode_control.value}));
  fixture.Submit(
      GpuFixture::SetRegisters(XE_GPU_REG_RB_COPY_CONTROL,
                               {copy_control.value, dest, copy_dest_pitch.value, dest_info.value}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_FETCH_00_0,
                                          {fetch.dword_0, fetch.dword_1}));
  reg::VGT_DRAW_INITIATOR initiator = {};
  initiator.prim_type = xenos::PrimitiveType::kRectangleList;
  initiator.source_select = xenos::SourceSelect::kAutoIndex;
  initiator.num_indices = 3;
  fixture.Submit({xenos::MakePacketType3(xenos::PM4_DRAW_INDX_2, 1), initiator.value});
}

uint32_t ReadTexel(const GpuFixture& fixture, uint32_t texture, uint32_t x, uint32_t y,
                   uint32_t pitch = 32) {
  return fixture.ReadDword(
      texture + uint32_t(texture_util::GetTiledOffset2D(int32_t(x), int32_t(y), pitch, 2)));
}

// A distinct 32bpp value per 1x pixel of a 16x16 region.
uint32_t PixelColor(uint32_t x, uint32_t y) {
  return x | (y << 8) | 0x80400000;
}

struct Coord {
  uint32_t x, y;
};

// Canary #1163's canonical layout: the 1x pixel holding sample `s` of the
// MSAA pixel (x, y) at the same EDRAM address (XeEdramOffsetBytes).
Coord CanonicalSampleTo1x(xenos::MsaaSamples msaa, uint32_t x, uint32_t y, uint32_t s) {
  if (msaa == xenos::MsaaSamples::k4X) {
    return {((x & ~1u) << 1) | (x & 1) | ((s & 1) << 1), ((y & ~1u) << 1) | (y & 1) | (s & 2)};
  }
  return {(x & ~2u) | (s << 1), ((y & ~1u) << 1) | (y & 1) | (x & 2)};
}

}  // namespace

// Canary #1163: MSAA samples of a pixel are spread over 4x4 blocks of the 1x
// view of the same EDRAM, so a 1x target re-aliased as MSAA (and back) sees the
// console's arrangement. 8x8-aligned clears can't show this; one draw per
// pixel gives every 1x pixel a distinct value.
TEST_CASE("1x EDRAM re-aliased as MSAA uses the canonical sample layout", "[gpu][edram]") {
  auto msaa = GENERATE(xenos::MsaaSamples::k2X, xenos::MsaaSamples::k4X);
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  // Otherwise draws are dropped while their pipelines compile.
  REQUIRE(rex::cvar::SetFlagByName("async_shader_compilation", "false"));
  bool is_4x = msaa == xenos::MsaaSamples::k4X;
  INFO((is_4x ? "4x" : "2x"));

  constexpr uint32_t k1xSize = 16;
  Surface surface_1x = {xenos::MsaaSamples::k1X, 64};
  DrawPixels(*fixture, surface_1x, k1xSize, k1xSize, PixelColor);
  uint32_t reference = fixture->AllocPhysical(0x1000);
  Resolve(*fixture, surface_1x, k1xSize, k1xSize, xenos::CopySampleSelect::k0, reference);

  // The MSAA alias of the same EDRAM rows: 2x halves the height, 4x also the
  // width (the pitch is in samples either way).
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
  // Otherwise draws are dropped while their pipelines compile.
  REQUIRE(rex::cvar::SetFlagByName("async_shader_compilation", "false"));
  bool is_4x = msaa == xenos::MsaaSamples::k4X;
  INFO((is_4x ? "4x" : "2x"));

  // Every sample of an MSAA pixel gets the pixel's color.
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

// Canary #1222 (title 4D530A26): a color target aliasing the depth buffer's
// EDRAM base that writes only the stencil byte (red of k_8_8_8_8 over D24S8)
// must not disable a read-only depth test, and the depth bits must survive.
TEST_CASE("Color aliasing depth keeps a read-only depth test", "[gpu][edram]") {
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  REQUIRE(rex::cvar::SetFlagByName("async_shader_compilation", "false"));

  // Depth tiles store their 40-sample halves swapped relative to color, so a
  // whole 80-sample tile row covers both the color and the depth bits.
  constexpr uint32_t kWidth = 80, kHeight = 16, kPitch = 96;
  Surface surface = {xenos::MsaaSamples::k1X, kWidth};
  // Depth 0.5 everywhere, no color writes.
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

  // Red only, depth test less without writes: the left half (z 0.25) passes,
  // the right half (z 0.75) fails.
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

// Canary #1238: when a float24 depth target is transferred back into after an
// alias, the host depth store saves its float32 depth per sample in the layout
// the transfer shader reads it with. A wrong layout loses the host precision,
// so redrawing the same geometry with an equal depth test fails.
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
  // 80 samples, a whole tile row, for both halves of the depth tile.
  Surface surface = {msaa, 80};
  // A color target far from the depth one to record the equal test.
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

  // A color draw over the depth range makes the color target its owner. It
  // writes only the stencil byte, so the EDRAM depth bits still match the
  // host depth when the range goes back to the depth target.
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

// Canary #1163: a 64bpp sample is two horizontally adjacent 32bpp sample
// columns, u = 2 * u_64bpp + half, for any sample count of the 64bpp view.
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

  // 40 64bpp samples (a tile row), 80 32bpp ones in the 1x alias.
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
