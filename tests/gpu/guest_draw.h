/**
 * @file        guest_draw.h
 * @brief       Guest draw helpers for GPU fixtures: hand-assembled shaders and
 *              constant-color rectangles (RG-GDK-009, RG-GDK-010)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <bit>
#include <cstdint>
#include <vector>

#include <rex/graphics/format/ucode.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/xenos.h>

#include "gpu_fixture.h"

namespace rex::testing::guest_draw {

using namespace rex::graphics;  // NOLINT: XE_GPU_REG_* register indices.
namespace reg = rex::graphics::reg;
namespace xenos = rex::graphics::xenos;
namespace ucode = rex::graphics::ucode;

inline uint32_t PackXY(uint32_t x, uint32_t y) {
  return x | (y << 16);
}

// Guest microcode, hand-assembled (see include/rex/graphics/format/ucode.h).
// Control flow instructions are 48 bits, two per three dwords; ALU and fetch
// instructions follow as three dwords each, addressed in three-dword units.

// exec (vfetch r1, r0.x, vf0 as float4, stride 4); alloc position;
// exec_end (max oPos, r1, r1). The vertex index is in r0.x.
inline const std::vector<uint32_t> kVertexShader = {
    0x00011002, 0x00001000, 0xC2000000,  // exec 2 fetch; alloc position
    0x00001003, 0x00002000, 0x00000000,  // exec_end 3 ALU; nop
    0x00081000, 0x00260688, 0x00000004,  // vfetch r1.xyzw, r0.x, vf0
    0xC80F803E, 0x00000000, 0xC2010100,  // max oPos.xyzw, r1, r1
};

// alloc colors; exec_end (max oC0, c0, c0).
inline const std::vector<uint32_t> kPixelShader = {
    0x00000000, 0x1001C400, 0x20000000,  // alloc colors; exec_end 1 ALU
    0xC80F8000, 0x00000000, 0x02000000,  // max oC0.xyzw, c0, c0
};

inline std::vector<uint32_t> LoadShader(xenos::ShaderType type,
                                        const std::vector<uint32_t>& ucode) {
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

struct DrawOptions {
  // Depth at the left and the right edges of the region, 0 to 1 (right is
  // the left one if negative).
  float z = 0.0f;
  float z_right = -1.0f;
  uint32_t color_base_tiles = 0;
  xenos::ColorRenderTargetFormat color_format = xenos::ColorRenderTargetFormat::k_8_8_8_8;
  xenos::DepthRenderTargetFormat depth_format = xenos::DepthRenderTargetFormat::kD24S8;
  reg::RB_DEPTHCONTROL depth_control = {};
  // RB_COLOR_MASK bits of color target 0.
  uint32_t color_mask = 0xF;
};

// Sets up drawing constant-color rectangles into a color target and a depth
// target at EDRAM base 0, within (0, 0)-(width, height).
inline void SetupDraw(GpuFixture& fixture, const Surface& surface, uint32_t width, uint32_t height,
                      const DrawOptions& options = {}) {
  uint32_t vertices = fixture.AllocPhysical(0x100);
  // Past the region on every side: with the Direct3D 9 pixel center
  // convention, the geometry is shifted by half a pixel, which would leave
  // MSAA samples of the first row and column uncovered. The scissor clips.
  float l = -8.0f, r = float(width + 8), t = -8.0f, b = float(height + 8);
  // Extrapolated to the extended edges.
  float z_right = options.z_right < 0.0f ? options.z : options.z_right;
  float dz = (z_right - options.z) / float(width);
  float zl = options.z + dz * l, zr = options.z + dz * r;
  std::vector<uint32_t> vertex_data;
  for (float v : {l, t, zl, 1.0f, r, t, zr, 1.0f, l, b, zl, 1.0f, r, b, zr, 1.0f}) {
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
  color_info.color_format = options.color_format;
  color_info.color_base = options.color_base_tiles;
  reg::RB_DEPTH_INFO depth_info = {};
  depth_info.depth_format = options.depth_format;
  reg::RB_MODECONTROL mode_control = {};
  mode_control.edram_mode = xenos::EdramMode::kColorDepth;
  reg::PA_CL_CLIP_CNTL clip_cntl = {};
  clip_cntl.clip_disable = 1;
  xenos::xe_gpu_vertex_fetch_t fetch = {};
  fetch.type = xenos::FetchConstantType::kVertex;
  fetch.address = vertices >> 2;
  fetch.endian = xenos::Endian::k8in32;
  fetch.size = 4 * 4;

  fixture.Submit(LoadShader(xenos::ShaderType::kVertex, kVertexShader));
  fixture.Submit(LoadShader(xenos::ShaderType::kPixel, kPixelShader));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_SQ_PROGRAM_CNTL, {program_cntl.value, 0}));
  fixture.Submit(GpuFixture::SetRegisters(
      XE_GPU_REG_RB_SURFACE_INFO, {surface_info.value, color_info.value, depth_info.value}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_MODECONTROL, {mode_control.value}));
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_COLOR_MASK, {options.color_mask}));
  // One * source + zero * destination for color and alpha.
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_BLENDCONTROL0, {0x00010001}));
  fixture.Submit(
      GpuFixture::SetRegisters(XE_GPU_REG_RB_DEPTHCONTROL, {options.depth_control.value}));
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
}

// Draws (x0, y0)-(x1, y1) with the constant pixel shader output c0, clipped by
// the window scissor, with the state from SetupDraw.
inline void DrawRectFloat(GpuFixture& fixture, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1,
                          float r, float g, float b, float a) {
  reg::PA_SC_WINDOW_SCISSOR_TL window_tl = {};
  window_tl.window_offset_disable = 1;
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_PA_SC_WINDOW_SCISSOR_TL,
                                          {window_tl.value | PackXY(x0, y0), PackXY(x1, y1)}));
  fixture.Submit(GpuFixture::SetRegisters(
      XE_GPU_REG_SHADER_CONSTANT_256_X, {std::bit_cast<uint32_t>(r), std::bit_cast<uint32_t>(g),
                                         std::bit_cast<uint32_t>(b), std::bit_cast<uint32_t>(a)}));
  reg::VGT_DRAW_INITIATOR initiator = {};
  initiator.prim_type = xenos::PrimitiveType::kTriangleStrip;
  initiator.source_select = xenos::SourceSelect::kAutoIndex;
  initiator.num_indices = 4;
  fixture.Submit({xenos::MakePacketType3(xenos::PM4_DRAW_INDX_2, 1), initiator.value});
}

// DrawRectFloat with an 8-bit normalized RGBA color (red in the low byte).
inline void DrawRect(GpuFixture& fixture, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1,
                     uint32_t color) {
  DrawRectFloat(fixture, x0, y0, x1, y1, float(color & 0xFF) / 255.0f,
                float((color >> 8) & 0xFF) / 255.0f, float((color >> 16) & 0xFF) / 255.0f,
                float(color >> 24) / 255.0f);
}

// Microcode encoders for hand-assembled shaders.

// Control flow instructions, packed two per three dwords.
struct Cf {
  uint32_t dword_0, dword_1;  // dword_1 has 16 bits.
};
inline Cf Exec(uint32_t address, uint32_t count, uint32_t fetch_sequence, bool end) {
  return {address | (count << 12) | (fetch_sequence << 16), end ? 0x2000u : 0x1000u};
}
inline Cf Alloc(ucode::AllocType type) {
  return {0, 0xC000u | (uint32_t(type) << 9)};
}
inline void PackCf(std::vector<uint32_t>& out, Cf a, Cf b) {
  out.insert(out.end(), {a.dword_0, (a.dword_1 & 0xFFFF) | (b.dword_0 << 16),
                         (b.dword_0 >> 16) | (b.dword_1 << 16)});
}

// ALU vector operation exporting all four components to export register
// `dest` (32 is eA, 33 is eM0, 62 is the position), with the scalar operation
// retaining the previous value. `sel` bits select temporary registers (1) or
// float constants (0) for sources 1..3.
inline std::vector<uint32_t> AluExport(uint32_t dest, uint32_t opcode, uint32_t src1, uint32_t src2,
                                       uint32_t src3, uint32_t src1_swizzle, bool src1_temp,
                                       bool src2_temp, bool src3_temp) {
  return {0xC80F8000u | dest, src1_swizzle << 16,
          src3 | (src2 << 8) | (src1 << 16) | (opcode << 24) | (uint32_t(src3_temp) << 29) |
              (uint32_t(src2_temp) << 30) | (uint32_t(src1_temp) << 31)};
}

constexpr uint32_t kAluMax = 2;
constexpr uint32_t kAluMad = 11;
// Component-relative swizzle replicating X.
constexpr uint32_t kSwizzleXXXX = 0 | (3 << 2) | (2 << 4) | (1 << 6);

}  // namespace rex::testing::guest_draw
