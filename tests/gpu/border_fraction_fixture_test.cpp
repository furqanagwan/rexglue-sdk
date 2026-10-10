
#include <bit>
#include <cmath>
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

struct RestoreCvars {
  ~RestoreCvars() {
    for (const char* name :
         {"render_target_path_d3d12", "readback_resolve", "async_shader_compilation",
          "draw_resolution_scale_x", "draw_resolution_scale_y", "resolution_scale_targets"}) {
      rex::cvar::ResetToDefault(name);
    }
  }
};

std::vector<uint32_t> PixelShader(xenos::FetchOpDimension dimension, bool linear,
                                  bool ordinary_fetch = false, uint32_t lod = 0) {
  std::vector<uint32_t> code;
  PackCf(code, Alloc(ucode::AllocType::kPsColors), Exec(1, 3, 4, true));
  auto coordinates = AluExport(1, kAluMax, 0, 0, 0, 0, false, false, false);
  coordinates[0] &= ~(1u << 15);
  code.insert(code.end(), coordinates.begin(), coordinates.end());
  const uint32_t filter =
      uint32_t(linear ? xenos::TextureFilter::kLinear : xenos::TextureFilter::kPoint);
  const auto opcode = ordinary_fetch ? ucode::FetchOpcode::kTextureFetch
                                     : ucode::FetchOpcode::kGetTextureBorderColorFrac;

  code.insert(code.end(), {uint32_t(opcode) | (1u << 5) | (2u << 12) | (1u << 20) | (0x24u << 26),
                           0x688u | (filter << 12) | (filter << 14) |
                               (uint32_t(xenos::TextureFilter::kPoint) << 16),
                           (lod * 16u << 2) | (uint32_t(dimension) << 14)});
  auto output = AluExport(0, kAluMax, 2, 2, 0, 0, true, true, false);
  code.insert(code.end(), output.begin(), output.end());
  return code;
}

xenos::xe_gpu_texture_fetch_t Texture(
    GpuFixture& fixture, bool linear, bool is_signed, xenos::ClampMode clamp,
    xenos::DataDimension dimension = xenos::DataDimension::k2DOrStacked, bool stacked = false,
    bool mip = false) {
  const uint32_t address = fixture.AllocPhysical(0x20000);
  fixture.WriteDwords(address, std::vector<uint32_t>(0x20000 / 4, 0x40404040));
  xenos::xe_gpu_texture_fetch_t fetch = {};
  fetch.type = xenos::FetchConstantType::kTexture;
  fetch.format = xenos::TextureFormat::k_8_8_8_8;
  fetch.endianness = xenos::Endian::k8in32;
  fetch.base_address = address >> 12;
  fetch.pitch = 1;
  fetch.tiled = 1;
  fetch.dimension = dimension;
  fetch.stacked = stacked;
  fetch.size_2d.width = kSize - 1;
  fetch.size_2d.height = kSize - 1;
  if (dimension == xenos::DataDimension::k3D) {
    fetch.size_3d.width = kSize - 1;
    fetch.size_3d.height = kSize - 1;
    fetch.size_3d.depth = 3;
  } else if (stacked) {
    fetch.size_2d.stack_depth = 3;
  }
  fetch.swizzle = 0 | (1 << 3) | (2 << 6) | (3 << 9);
  fetch.sign_x = fetch.sign_y = fetch.sign_z = fetch.sign_w =
      is_signed ? xenos::TextureSign::kSigned : xenos::TextureSign::kUnsigned;
  fetch.clamp_x = fetch.clamp_y = fetch.clamp_z = clamp;
  fetch.mag_filter = fetch.min_filter =
      linear ? xenos::TextureFilter::kLinear : xenos::TextureFilter::kPoint;
  fetch.mip_filter = xenos::TextureFilter::kPoint;

  fetch.border_color = xenos::BorderColor::k_ACBYCR_Black;
  if (mip) {
    fetch.mip_address = address >> 12;
    fetch.mip_min_level = fetch.mip_max_level = 1;
  }
  REQUIRE(fixture.Submit(GpuFixture::SetRegisters(
      XE_GPU_REG_SHADER_CONSTANT_FETCH_01_0,
      {fetch.dword_0, fetch.dword_1, fetch.dword_2, fetch.dword_3, fetch.dword_4, fetch.dword_5})));
  return fetch;
}

uint32_t Sample(GpuFixture& fixture, xenos::FetchOpDimension dimension, bool linear, float u,
                float v, float w = 0.5f, bool ordinary_fetch = false, uint32_t lod = 0) {
  const Surface surface{xenos::MsaaSamples::k1X, kSize};
  SetupDraw(fixture, surface, kSize, kSize);
  REQUIRE(fixture.Submit(
      LoadShader(xenos::ShaderType::kPixel, PixelShader(dimension, linear, ordinary_fetch, lod))));
  reg::SQ_PROGRAM_CNTL program = {};
  program.vs_num_reg = 1;
  program.ps_num_reg = 3;
  REQUIRE(fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_SQ_PROGRAM_CNTL, {program.value})));
  DrawRectFloat(fixture, 0, 0, kSize, kSize, u, v, w, 1.0f);
  const uint32_t dest = fixture.AllocPhysical(kSize * kSize * 4);
  Resolve(fixture, surface, kSize, kSize, xenos::CopySampleSelect::k0, dest);
  REQUIRE(fixture.Flush());
  return ReadTexel(fixture, dest, kSize / 2, kSize / 2);
}

void CheckFraction(uint32_t color, float expected) {
  INFO("readback 0x" << std::hex << color << ", expected fraction " << expected);
  CHECK(std::abs(int(color & 255) - int(std::lround(expected * 255.0f))) <= 2);
  CHECK((color & 0xFFFFFF00) == 0);
}
}

TEST_CASE("getBCF measures point and linear borders without changing ordinary fetches",
          "[gpu][border-fraction]") {
  const char* path = GENERATE("rtv", "rov");
  const bool linear = GENERATE(false, true);
  const bool is_signed = GENERATE(false, true);
  RestoreCvars restore;
  std::string error;
  auto fixture = GpuFixture::Create(
      &error, {{"render_target_path_d3d12", path}, {"async_shader_compilation", "false"}});
  if (!fixture)
    SKIP(error);
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  INFO(fixture->Metadata() << ", path " << path << ", linear " << linear << ", signed "
                           << is_signed);
  SetupDraw(*fixture, {xenos::MsaaSamples::k1X, kSize}, kSize, kSize);
  const auto fetch = Texture(*fixture, linear, is_signed, xenos::ClampMode::kClampToBorder);
  INFO("fetch type " << uint32_t(fetch.type) << ", format " << uint32_t(fetch.format)
                     << ", base page 0x" << std::hex << fetch.base_address << ", source dword 0x"
                     << fixture->ReadDword(fetch.base_address << 12));
  CheckFraction(Sample(*fixture, xenos::FetchOpDimension::k2D, linear, 0.5f, 0.5f), 0.0f);
  CheckFraction(Sample(*fixture, xenos::FetchOpDimension::k2D, linear, -1.0f, 0.5f), 1.0f);
  CheckFraction(Sample(*fixture, xenos::FetchOpDimension::k2D, linear, 0.0f, 0.5f),
                linear ? 0.5f : 0.0f);
  CheckFraction(Sample(*fixture, xenos::FetchOpDimension::k2D, linear, 0.0f, 0.0f),
                linear ? 0.75f : 0.0f);
  const uint32_t interior =
      Sample(*fixture, xenos::FetchOpDimension::k2D, linear, 0.5f, 0.5f, 0.5f, true);
  CHECK((interior & 255) > 32);
  Texture(*fixture, linear, is_signed, xenos::ClampMode::kClampToEdge);
  CheckFraction(Sample(*fixture, xenos::FetchOpDimension::k2D, linear, -1.0f, 0.5f), 0.0f);
}

TEST_CASE("getBCF handles mips volumes stacked textures and cube controls",
          "[gpu][border-fraction]") {
  RestoreCvars restore;
  std::string error;
  auto fixture = GpuFixture::Create(&error, {{"async_shader_compilation", "false"}});
  if (!fixture)
    SKIP(error);
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  SetupDraw(*fixture, {xenos::MsaaSamples::k1X, kSize}, kSize, kSize);
  Texture(*fixture, true, false, xenos::ClampMode::kClampToBorder,
          xenos::DataDimension::k2DOrStacked, false, true);
  CheckFraction(Sample(*fixture, xenos::FetchOpDimension::k2D, true, 0.0f, 0.5f, 0.5f, false, 1),
                0.5f);
  for (bool stacked : {false, true}) {
    Texture(*fixture, true, false, xenos::ClampMode::kClampToBorder,
            stacked ? xenos::DataDimension::k2DOrStacked : xenos::DataDimension::k3D, stacked);
    CheckFraction(Sample(*fixture, xenos::FetchOpDimension::k3DOrStacked, true, 0.0f, 0.5f), 0.5f);
    CheckFraction(Sample(*fixture, xenos::FetchOpDimension::k3DOrStacked, true, -1.0f, 0.5f), 1.0f);
  }
  CheckFraction(Sample(*fixture, xenos::FetchOpDimension::kCube, true, -1.0f, 0.5f), 0.0f);
}
