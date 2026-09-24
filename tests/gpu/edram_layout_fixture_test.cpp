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

namespace {

using namespace rex::graphics;  // NOLINT: XE_GPU_REG_* register indices.
namespace reg = rex::graphics::reg;
namespace xenos = rex::graphics::xenos;
using rex::testing::GpuFixture;

uint32_t PackXY(uint32_t x, uint32_t y) {
  return x | (y << 16);
}

// Guest microcode, hand-assembled (see include/rex/graphics/format/ucode.h).
// Control flow instructions are 48 bits, two per three dwords; ALU and fetch
// instructions follow as three dwords each, addressed in three-dword units.

// exec (vfetch r1, r0.x, vf0 as float4, stride 4); alloc position;
// exec_end (max oPos, r1, r1). The vertex index is in r0.x.
const std::vector<uint32_t> kVertexShader = {
    0x00011002, 0x00001000, 0xC2000000,  // exec 2 fetch; alloc position
    0x00001003, 0x00002000, 0x00000000,  // exec_end 3 ALU; nop
    0x00081000, 0x00260688, 0x00000004,  // vfetch r1.xyzw, r0.x, vf0
    0xC80F803E, 0x00000000, 0xC2010100,  // max oPos.xyzw, r1, r1
};

// alloc colors; exec_end (max oC0, c0, c0).
const std::vector<uint32_t> kPixelShader = {
    0x00000000, 0x1001C400, 0x20000000,  // alloc colors; exec_end 1 ALU
    0xC80F8000, 0x00000000, 0x02000000,  // max oC0.xyzw, c0, c0
};

std::vector<uint32_t> LoadShader(xenos::ShaderType type, const std::vector<uint32_t>& ucode) {
  std::vector<uint32_t> packet = {
      xenos::MakePacketType3(xenos::PM4_IM_LOAD_IMMEDIATE, uint32_t(2 + ucode.size())),
      uint32_t(type), uint32_t(ucode.size())};
  packet.insert(packet.end(), ucode.begin(), ucode.end());
  return packet;
}

struct Surface {
  xenos::MsaaSamples msaa;
  // In samples, as in RB_SURFACE_INFO.
  uint32_t pitch;
};

// Draws one pixel at a time with its own constant color, so every pixel of the
// region (0, 0)-(width, height) holds a distinct value regardless of how the
// rasterizer treats the edges, into a 32bpp color target at EDRAM base 0.
void DrawPixels(GpuFixture& fixture, const Surface& surface, uint32_t width, uint32_t height,
                const std::function<uint32_t(uint32_t, uint32_t)>& color) {
  uint32_t vertices = fixture.AllocPhysical(0x100);
  // Past the region on every side: with the Direct3D 9 pixel center
  // convention, the geometry is shifted by half a pixel, which would leave
  // MSAA samples of the first row and column uncovered. The scissor clips.
  float l = -8.0f, r = float(width + 8), t = -8.0f, b = float(height + 8);
  std::vector<uint32_t> vertex_data;
  for (float v : {l, t, 0.0f, 1.0f, r, t, 0.0f, 1.0f, l, b, 0.0f, 1.0f, r, b, 0.0f, 1.0f}) {
    vertex_data.push_back(std::bit_cast<uint32_t>(v));
  }
  fixture.WriteDwords(vertices, vertex_data);

  reg::SQ_PROGRAM_CNTL program_cntl = {};
  program_cntl.vs_num_reg = 1;
  program_cntl.ps_num_reg = 0;
  reg::RB_SURFACE_INFO surface_info = {};
  surface_info.surface_pitch = surface.pitch;
  surface_info.msaa_samples = surface.msaa;
  reg::RB_COLOR_INFO color_info = {};
  color_info.color_format = xenos::ColorRenderTargetFormat::k_8_8_8_8;
  reg::RB_MODECONTROL mode_control = {};
  mode_control.edram_mode = xenos::EdramMode::kColorDepth;
  reg::PA_CL_CLIP_CNTL clip_cntl = {};
  clip_cntl.clip_disable = 1;
  reg::PA_SC_WINDOW_SCISSOR_TL window_tl = {};
  window_tl.window_offset_disable = 1;
  xenos::xe_gpu_vertex_fetch_t fetch = {};
  fetch.type = xenos::FetchConstantType::kVertex;
  fetch.address = vertices >> 2;
  fetch.endian = xenos::Endian::k8in32;
  fetch.size = 4 * 4;

  fixture.Submit(LoadShader(xenos::ShaderType::kVertex, kVertexShader));
  fixture.Submit(LoadShader(xenos::ShaderType::kPixel, kPixelShader));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_SQ_PROGRAM_CNTL, {program_cntl.value, 0}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_SURFACE_INFO,
                                          {surface_info.value, color_info.value, 0}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_MODECONTROL, {mode_control.value}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_COLOR_MASK, {0xF}));
  // One * source + zero * destination for color and alpha.
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_BLENDCONTROL0, {0x00010001}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_DEPTHCONTROL, {0}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_CL_CLIP_CNTL, {clip_cntl.value}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_CL_VTE_CNTL, {0}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SU_SC_MODE_CNTL, {0}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SU_VTX_CNTL, {0}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SC_AA_MASK, {0xFFFF}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SC_SCREEN_SCISSOR_TL,
                                          {PackXY(0, 0), PackXY(width, height)}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SC_WINDOW_OFFSET, {0}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_VGT_MAX_VTX_INDX, {0xFFFFFF, 0, 0}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_FETCH_00_0,
                                          {fetch.dword_0, fetch.dword_1}));

  reg::VGT_DRAW_INITIATOR initiator = {};
  initiator.prim_type = xenos::PrimitiveType::kTriangleStrip;
  initiator.source_select = xenos::SourceSelect::kAutoIndex;
  initiator.num_indices = 4;
  for (uint32_t y = 0; y < height; ++y) {
    for (uint32_t x = 0; x < width; ++x) {
      uint32_t c = color(x, y);
      fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SC_WINDOW_SCISSOR_TL,
                                              {window_tl.value | PackXY(x, y),
                                               PackXY(x + 1, y + 1)}));
      fixture.Submit(GpuFixture::SetRegisters(
          XE_GPU_REG_SHADER_CONSTANT_256_X,
          {std::bit_cast<uint32_t>(float(c & 0xFF) / 255.0f),
           std::bit_cast<uint32_t>(float((c >> 8) & 0xFF) / 255.0f),
           std::bit_cast<uint32_t>(float((c >> 16) & 0xFF) / 255.0f),
           std::bit_cast<uint32_t>(float(c >> 24) / 255.0f)}));
      fixture.Submit({xenos::MakePacketType3(xenos::PM4_DRAW_INDX_2, 1), initiator.value});
    }
  }
}

// Resolves (0, 0)-(width, height) of the 32bpp color target at EDRAM base 0,
// one sample of it with MSAA, to a 32x32-aligned k_8_8_8_8 tiled texture.
void Resolve(GpuFixture& fixture, const Surface& surface, uint32_t width, uint32_t height,
             xenos::CopySampleSelect sample, uint32_t dest) {
  uint32_t vertices = fixture.AllocPhysical(0x100);
  fixture.WriteDwords(vertices, {0, 0, std::bit_cast<uint32_t>(float(width)), 0,
                                 std::bit_cast<uint32_t>(float(width)),
                                 std::bit_cast<uint32_t>(float(height))});
  reg::RB_SURFACE_INFO surface_info = {};
  surface_info.surface_pitch = surface.pitch;
  surface_info.msaa_samples = surface.msaa;
  reg::RB_COLOR_INFO color_info = {};
  color_info.color_format = xenos::ColorRenderTargetFormat::k_8_8_8_8;
  reg::PA_SC_WINDOW_SCISSOR_TL window_tl = {};
  window_tl.window_offset_disable = 1;
  reg::RB_MODECONTROL mode_control = {};
  mode_control.edram_mode = xenos::EdramMode::kCopy;
  reg::RB_COPY_CONTROL copy_control = {};
  copy_control.copy_sample_select = sample;
  copy_control.copy_command = xenos::CopyCommand::kRaw;
  reg::RB_COPY_DEST_PITCH dest_pitch = {};
  dest_pitch.copy_dest_pitch = 32;
  dest_pitch.copy_dest_height = 32;
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
  fixture.Submit(GpuFixture::SetRegisters(
      XE_GPU_REG_RB_COPY_CONTROL, {copy_control.value, dest, dest_pitch.value, dest_info.value}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_FETCH_00_0,
                                          {fetch.dword_0, fetch.dword_1}));
  reg::VGT_DRAW_INITIATOR initiator = {};
  initiator.prim_type = xenos::PrimitiveType::kRectangleList;
  initiator.source_select = xenos::SourceSelect::kAutoIndex;
  initiator.num_indices = 3;
  fixture.Submit({xenos::MakePacketType3(xenos::PM4_DRAW_INDX_2, 1), initiator.value});
}

uint32_t ReadTexel(const GpuFixture& fixture, uint32_t texture, uint32_t x, uint32_t y) {
  return fixture.ReadDword(
      texture + uint32_t(texture_util::GetTiledOffset2D(int32_t(x), int32_t(y), 32, 2)));
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
            UNSCOPED_INFO("sample " << s << " (" << x << ", " << y << "): 0x" << std::hex
                                    << actual << ", expected 0x" << expected << std::dec);
          }
        }
      }
    }
  }
  std::printf("1x as %s: %u samples off the canonical layout\n", is_4x ? "4x" : "2x",
              mismatches);
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
  Resolve(*fixture, surface_msaa, msaa_width, msaa_height, xenos::CopySampleSelect::k0,
          reference);
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
                                 << ", " << y << "): 0x" << std::hex << actual
                                 << ", expected 0x" << expected << std::dec);
          }
        }
      }
    }
  }
  std::printf("%s as 1x: %u pixels off the canonical layout\n", is_4x ? "4x" : "2x", mismatches);
  CHECK(mismatches == 0);
}


