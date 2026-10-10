/**
 * @file        memexport_fixture_test.cpp
 * @brief       Memexport ownership: GPU write, CPU read, GPU reuse and invalid
 *              stream ranges (RG-GDK-011)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <bit>
#include <chrono>
#include <cstdint>
#include <string>
#include <thread>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/format/ucode.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/xenos.h>

#include "gpu_fixture.h"
#include "guest_draw.h"

namespace {

using namespace rex::graphics;  // NOLINT: XE_GPU_REG_* register indices.
namespace reg = rex::graphics::reg;
namespace xenos = rex::graphics::xenos;
using rex::testing::GpuFixture;
using namespace rex::testing::guest_draw;  // NOLINT

std::vector<uint32_t> MemexportVertexShader() {
  std::vector<uint32_t> ucode;
  PackCf(ucode, Exec(3, 1, 1, false), Alloc(ucode::AllocType::kVsPosition));
  PackCf(ucode, Exec(4, 1, 0, false), Alloc(ucode::AllocType::kMemory));
  PackCf(ucode, Exec(5, 2, 0, true), Cf{0, 0});

  ucode.insert(ucode.end(), {0x00081000, 0x00260688, 0x00000004});

  auto pos = AluExport(62, kAluMax, 1, 1, 0, 0, true, true, false);
  ucode.insert(ucode.end(), pos.begin(), pos.end());

  auto address = AluExport(32, kAluMad, 0, 1, 2, kSwizzleXXXX, true, false, false);
  ucode.insert(ucode.end(), address.begin(), address.end());

  auto data = AluExport(33, kAluMax, 3, 3, 0, 0, false, false, false);
  ucode.insert(ucode.end(), data.begin(), data.end());
  return ucode;
}

constexpr uint32_t kVertexCount = 4;
constexpr uint32_t kStreamBytes = kVertexCount * 16;

xenos::xe_gpu_memexport_stream_t Stream(uint32_t address, uint32_t index_count) {
  xenos::xe_gpu_memexport_stream_t stream = {};
  stream.base_address = address >> 2;
  stream.const_0x1 = 0x1;
  stream.const_0x4b000000 = 0x4B000000;
  stream.endianness = xenos::Endian128::k8in32;
  stream.format = xenos::ColorFormat::k_32_32_32_32_FLOAT;
  stream.num_format = xenos::SurfaceNumberFormat::kFloat;
  stream.const_0x4b0 = 0x4B0;
  stream.index_count = index_count;
  stream.const_0x96 = 0x96;
  return stream;
}

std::unique_ptr<GpuFixture> CreateFixture(std::string* error) {
  return GpuFixture::Create(error, {{"async_shader_compilation", "false"},
                                    {"occlusion_query", "strict"},
                                    {"readback_memexport", "true"},

                                    {"readback_memexport_fast", "false"}});
}

void DrawExporting(GpuFixture& fixture, const xenos::xe_gpu_memexport_stream_t& stream,
                   const uint32_t (&value)[4]) {
  DrawOptions options;
  options.color_mask = 0;
  SetupDraw(fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32, options);
  fixture.Submit(LoadShader(xenos::ShaderType::kVertex, MemexportVertexShader()));
  fixture.Submit(GpuFixture::SetRegisters(
      XE_GPU_REG_SHADER_CONSTANT_000_X + 4,
      {std::bit_cast<uint32_t>(0.0f), std::bit_cast<uint32_t>(1.0f), std::bit_cast<uint32_t>(0.0f),
       std::bit_cast<uint32_t>(0.0f), stream.dword_0, stream.dword_1, stream.dword_2,
       stream.dword_3, value[0], value[1], value[2], value[3]}));
  DrawRect(fixture, 0, 0, 16, 8, 0);
}

uint32_t CountSamplesFrom(GpuFixture& fixture, uint32_t vertices) {
  DrawOptions options;
  options.color_mask = 0;
  SetupDraw(fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32, options);
  xenos::xe_gpu_vertex_fetch_t fetch = {};
  fetch.type = xenos::FetchConstantType::kVertex;
  fetch.address = vertices >> 2;
  fetch.endian = xenos::Endian::k8in32;
  fetch.size = 4 * 4;
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_FETCH_00_0,
                                          {fetch.dword_0, fetch.dword_1}));
  uint32_t begin = fixture.AllocPhysical(0x100, 0x100);
  uint32_t end = fixture.AllocPhysical(0x100, 0x100);
  fixture.WriteDwords(begin, std::vector<uint32_t>(8, 0));
  fixture.WriteDwords(end, std::vector<uint32_t>(8, 0));
  fixture.WriteDwords(end + 16, {0xFFFFFEED});
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_SAMPLE_COUNT_ADDR, {begin}));
  fixture.Submit({xenos::MakePacketType3(xenos::PM4_EVENT_WRITE_ZPD, 1), xenos::ZPASS_DONE});
  DrawRect(fixture, 0, 0, 32, 32, 0);
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_SAMPLE_COUNT_ADDR, {end}));
  fixture.Submit({xenos::MakePacketType3(xenos::PM4_EVENT_WRITE_ZPD, 1), xenos::ZPASS_DONE});
  if (!fixture.Flush()) {
    return UINT32_MAX;
  }
  for (int i = 0; i < 10000 && fixture.ReadDword(end + 16) == 0xFFFFFEED; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  const auto& b = *fixture.memory()->TranslatePhysical<xenos::xe_gpu_depth_sample_counts*>(begin);
  const auto& e = *fixture.memory()->TranslatePhysical<xenos::xe_gpu_depth_sample_counts*>(end);
  return (uint32_t(e.ZPass_A) + uint32_t(e.ZPass_B)) - (uint32_t(b.ZPass_A) + uint32_t(b.ZPass_B));
}

std::vector<uint32_t> RectVertices(float l, float t, float r, float b) {
  std::vector<uint32_t> dwords;
  for (float v : {l, t, 0.0f, 1.0f, r, t, 0.0f, 1.0f, l, b, 0.0f, 1.0f, r, b, 0.0f, 1.0f}) {
    dwords.push_back(std::bit_cast<uint32_t>(v));
  }
  return dwords;
}

}

TEST_CASE("Memexport data reaches the CPU and CPU writes over it reach the GPU",
          "[gpu][memexport]") {
  std::string error;
  auto fixture = CreateFixture(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  uint32_t buffer = fixture->AllocPhysical(0x1000);
  fixture->WriteDwords(buffer, std::vector<uint32_t>(kStreamBytes / 4, 0xCDCDCDCD));
  const uint32_t value[4] = {std::bit_cast<uint32_t>(1.5f), std::bit_cast<uint32_t>(-2.0f),
                             std::bit_cast<uint32_t>(0.25f), std::bit_cast<uint32_t>(8.0f)};

  DrawExporting(*fixture, Stream(buffer, kVertexCount), value);
  REQUIRE(fixture->Flush());
  INFO(fixture->Metadata());
  for (uint32_t i = 0; i < kVertexCount; ++i) {
    for (uint32_t c = 0; c < 4; ++c) {
      INFO("element " << i << ", component " << c);
      CHECK(fixture->ReadDword(buffer + i * 16 + c * 4) == value[c]);
    }
  }

  uint32_t fresh = fixture->AllocPhysical(0x1000);
  fixture->WriteDwords(fresh, RectVertices(-8.0f, -8.0f, 8.0f, 12.0f));
  CHECK(CountSamplesFrom(*fixture, fresh) == 8u * 12u);
  fixture->WriteDwordsAsGuest(buffer, RectVertices(-8.0f, -8.0f, 8.0f, 12.0f));
  CHECK(CountSamplesFrom(*fixture, buffer) == 8u * 12u);
}

TEST_CASE("A memexport stream past the end of physical memory drops only that draw",
          "[gpu][memexport]") {
  std::string error;
  auto fixture = CreateFixture(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  const uint32_t value[4] = {1, 2, 3, 4};

  DrawExporting(*fixture, Stream(0x1FFFFF00, 1024), value);
  REQUIRE(fixture->Flush());

  uint32_t buffer = fixture->AllocPhysical(0x1000);
  fixture->WriteDwords(buffer, std::vector<uint32_t>(kStreamBytes / 4, 0));
  DrawExporting(*fixture, Stream(buffer, kVertexCount), value);
  REQUIRE(fixture->Flush());
  CHECK(fixture->ReadDword(buffer) == 1u);
  CHECK(fixture->ReadDword(buffer + (kVertexCount - 1) * 16 + 12) == 4u);
}

TEST_CASE("A memexport stream running off its allocation keeps the command processor alive",
          "[gpu][memexport]") {
  std::string error;
  auto fixture = CreateFixture(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }

  uint32_t buffer = fixture->AllocPhysical(0x1000);
  const uint32_t value[4] = {5, 6, 7, 8};
  DrawExporting(*fixture, Stream(buffer, 64 * 1024), value);
  REQUIRE(fixture->Flush());
  INFO(fixture->Metadata());

  CHECK(fixture->ReadDword(buffer) == 5u);
  uint32_t after = fixture->AllocPhysical(0x1000);
  fixture->WriteDwords(after, std::vector<uint32_t>(kStreamBytes / 4, 0));
  DrawExporting(*fixture, Stream(after, kVertexCount), value);
  REQUIRE(fixture->Flush());
  CHECK(fixture->ReadDword(after) == 5u);
}

TEST_CASE("Async pipeline creation survives first use, cache hits and teardown",
          "[gpu][async-pipeline]") {
  for (uint32_t round = 0; round < 4; ++round) {
    std::string error;
    auto fixture = GpuFixture::Create(&error, {{"async_shader_compilation", "true"}});
    if (!fixture) {
      SKIP("GPU fixture host unavailable: " << error);
    }
    INFO("round " << round);
    SetupDraw(*fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32);
    for (uint32_t constant = 0; constant < 48; ++constant) {
      uint32_t source = (round * 48 + constant) & 0xFF;
      fixture->Submit(LoadShader(xenos::ShaderType::kPixel,
                                 {0x00000000, 0x1001C400, 0x20000000, 0xC80F8000, 0x00000000,
                                  0x02000000 | (source << 16) | (source << 8)}));
      fixture->Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_COLOR_MASK, {0xF}));
      DrawRect(*fixture, 0, 0, 8, 8, 0xFFFFFFFF);

      fixture->Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_COLOR_MASK, {0}));
      DrawRect(*fixture, 0, 0, 8, 8, 0);
    }

    if (round < 3) {
      REQUIRE(fixture->Flush());
    }
  }
}
