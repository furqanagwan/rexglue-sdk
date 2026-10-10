// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <rex/cvar.h>

#include "gpu_fixture.h"
#include "guest_draw.h"

namespace {
using namespace rex::graphics;             // NOLINT
using namespace rex::testing::guest_draw;  // NOLINT
using rex::testing::GpuFixture;
constexpr uint32_t kSize = 32;
constexpr uint32_t kSwizzleXXX = 0x00;
constexpr uint32_t kSwizzleXYZ = 0x24;

struct RestoreCvars {
  ~RestoreCvars() {
    for (const char* name : {"readback_resolve", "async_shader_compilation"}) {
      rex::cvar::ResetToDefault(name);
    }
  }
};

std::vector<uint32_t> FetchPixelShader(uint32_t source_swizzle) {
  std::vector<uint32_t> code;
  PackCf(code, Alloc(ucode::AllocType::kPsColors), Exec(1, 3, 4, true));
  auto coordinates = AluExport(1, kAluMax, 0, 0, 0, 0, false, false, false);
  coordinates[0] &= ~(1u << 15);
  code.insert(code.end(), coordinates.begin(), coordinates.end());
  const uint32_t point = uint32_t(xenos::TextureFilter::kPoint);
  code.insert(code.end(), {uint32_t(ucode::FetchOpcode::kTextureFetch) | (1u << 5) | (2u << 12) |
                               (1u << 20) | (source_swizzle << 26),
                           0x688u | (point << 12) | (point << 14) | (point << 16),
                           uint32_t(xenos::FetchOpDimension::k1D) << 14});
  auto output = AluExport(0, kAluMax, 2, 2, 0, 0, true, true, false);
  code.insert(code.end(), output.begin(), output.end());
  return code;
}

uint32_t RowValue(uint32_t texel) {
  constexpr uint32_t kRowValues[] = {0x10, 0x80, 0xF0};
  const uint32_t value = kRowValues[texel / xenos::kTexture2DCubeMaxWidthHeight];
  return value | (value << 8) | (value << 16) | (value << 24);
}

void Texture1D(GpuFixture& fixture, uint32_t width) {
  const uint32_t address = fixture.AllocPhysical((width * 4 + 0xFFF) & ~0xFFFu);
  std::vector<uint32_t> texels(width);
  for (uint32_t i = 0; i < width; ++i) {
    texels[i] = RowValue(i);
  }
  fixture.WriteDwords(address, texels);
  xenos::xe_gpu_texture_fetch_t fetch = {};
  fetch.type = xenos::FetchConstantType::kTexture;
  fetch.format = xenos::TextureFormat::k_8_8_8_8;
  fetch.endianness = xenos::Endian::k8in32;
  fetch.base_address = address >> 12;
  fetch.pitch = std::min((width + 31) / 32, 511u);
  fetch.dimension = xenos::DataDimension::k1D;
  fetch.size_1d.width = width - 1;
  fetch.swizzle = 0 | (1 << 3) | (2 << 6) | (3 << 9);
  fetch.clamp_x = fetch.clamp_y = fetch.clamp_z = xenos::ClampMode::kClampToEdge;
  fetch.mag_filter = fetch.min_filter = xenos::TextureFilter::kPoint;
  fetch.mip_filter = xenos::TextureFilter::kPoint;
  REQUIRE(fixture.Submit(GpuFixture::SetRegisters(
      XE_GPU_REG_SHADER_CONSTANT_FETCH_01_0,
      {fetch.dword_0, fetch.dword_1, fetch.dword_2, fetch.dword_3, fetch.dword_4, fetch.dword_5})));
}

uint32_t Sample(GpuFixture& fixture, uint32_t source_swizzle, uint32_t width, uint32_t texel) {
  const Surface surface{xenos::MsaaSamples::k1X, kSize};
  SetupDraw(fixture, surface, kSize, kSize);
  REQUIRE(fixture.Submit(LoadShader(xenos::ShaderType::kPixel, FetchPixelShader(source_swizzle))));
  reg::SQ_PROGRAM_CNTL program = {};
  program.vs_num_reg = 1;
  program.ps_num_reg = 3;
  REQUIRE(fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_SQ_PROGRAM_CNTL, {program.value})));
  const float u = (float(texel) + 0.5f) / float(width);
  DrawRectFloat(fixture, 0, 0, kSize, kSize, u, 0.5f, 0.5f, 1.0f);
  const uint32_t dest = fixture.AllocPhysical(kSize * kSize * 4);
  Resolve(fixture, surface, kSize, kSize, xenos::CopySampleSelect::k0, dest);
  REQUIRE(fixture.Flush());
  return ReadTexel(fixture, dest, kSize / 2, kSize / 2);
}
}

TEST_CASE("Wide 1D textures are fetched from their 8192-texel rows", "[gpu][wide-1d]") {
  const uint32_t source_swizzle = GENERATE(kSwizzleXXX, kSwizzleXYZ);
  RestoreCvars restore;
  std::string error;
  auto fixture = GpuFixture::Create(&error, {{"async_shader_compilation", "false"}});
  if (!fixture)
    SKIP(error);
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  INFO(fixture->Metadata() << ", source swizzle 0x" << std::hex << source_swizzle);
  constexpr uint32_t kWidth = 20000;
  Texture1D(*fixture, kWidth);
  for (uint32_t texel : {100u, 8191u, 8192u, 9000u, 16383u, 16384u, 19999u}) {
    const uint32_t color = Sample(*fixture, source_swizzle, kWidth, texel);
    INFO("texel " << std::dec << texel << ", read 0x" << std::hex << color << ", expected 0x"
                  << RowValue(texel));
    CHECK(color == RowValue(texel));
  }
}

TEST_CASE("A 1D texture within one row is fetched as before", "[gpu][wide-1d]") {
  RestoreCvars restore;
  std::string error;
  auto fixture = GpuFixture::Create(&error, {{"async_shader_compilation", "false"}});
  if (!fixture)
    SKIP(error);
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  constexpr uint32_t kWidth = 8192;
  Texture1D(*fixture, kWidth);
  for (uint32_t texel : {0u, 4096u, 8191u}) {
    INFO("texel " << texel);
    CHECK(Sample(*fixture, kSwizzleXXX, kWidth, texel) == RowValue(texel));
  }
}
