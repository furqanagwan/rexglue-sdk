/**
 * @file        zpd_fixture_test.cpp
 * @brief       EVENT_WRITE_ZPD occlusion query reports through the GPU plugin (RG-GDK-010,
 *              and the ROV path, RG-GDK-010a)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <chrono>
#include <cstdint>
#include <thread>
#include <vector>

#include <catch2/catch_test_macros.hpp>

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

constexpr uint32_t kPendingSentinel = 0xFFFFFEED;
constexpr uint32_t kZPassAOffset = 16;

std::unique_ptr<GpuFixture> CreateFixture(std::string* error, const char* mode) {
  return GpuFixture::Create(error,
                            {{"occlusion_query", mode}, {"async_shader_compilation", "false"}});
}

uint32_t AllocReport(GpuFixture& fixture) {
  uint32_t report = fixture.AllocPhysical(0x100, 0x100);
  fixture.WriteDwords(report, std::vector<uint32_t>(8, 0));
  return report;
}

void WriteZPD(GpuFixture& fixture, uint32_t report, bool awaited) {
  if (awaited) {
    fixture.WriteDwords(report + kZPassAOffset, {kPendingSentinel});
  }
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_RB_SAMPLE_COUNT_ADDR, {report}));
  fixture.Submit({xenos::MakePacketType3(xenos::PM4_EVENT_WRITE_ZPD, 1), xenos::ZPASS_DONE});
}

const xenos::xe_gpu_depth_sample_counts& Counts(GpuFixture& fixture, uint32_t report) {
  return *fixture.memory()->TranslatePhysical<xenos::xe_gpu_depth_sample_counts*>(report);
}

uint32_t ZPass(GpuFixture& fixture, uint32_t report) {
  const auto& counts = Counts(fixture, report);
  return uint32_t(counts.ZPass_A) + uint32_t(counts.ZPass_B);
}

uint32_t Total(GpuFixture& fixture, uint32_t report) {
  const auto& counts = Counts(fixture, report);
  return uint32_t(counts.Total_A) + uint32_t(counts.Total_B);
}

uint32_t ZFail(GpuFixture& fixture, uint32_t report) {
  const auto& counts = Counts(fixture, report);
  return uint32_t(counts.ZFail_A) + uint32_t(counts.ZFail_B);
}

uint32_t StencilFail(GpuFixture& fixture, uint32_t report) {
  const auto& counts = Counts(fixture, report);
  return uint32_t(counts.StencilFail_A) + uint32_t(counts.StencilFail_B);
}

std::unique_ptr<GpuFixture> CreateRovFixture(std::string* error, bool full_counters) {
  auto fixture = GpuFixture::Create(
      error, {{"occlusion_query", "strict"},
              {"async_shader_compilation", "false"},
              {"render_target_path_d3d12", "rov"},
              {"occlusion_query_full_counters", full_counters ? "true" : "false"}});
  if (fixture && (fixture->provider().IsAdapterSoftware() ||
                  !fixture->provider().AreRasterizerOrderedViewsSupported())) {
    *error = "no hardware ROV support: " + fixture->Metadata();
    return nullptr;
  }
  return fixture;
}

bool AwaitReport(GpuFixture& fixture, uint32_t report) {
  if (!fixture.Flush()) {
    return false;
  }
  auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(10);
  while (fixture.ReadDword(report + kZPassAOffset) == kPendingSentinel) {
    if (std::chrono::steady_clock::now() > deadline) {
      return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  return true;
}

uint32_t Delta(uint32_t end, uint32_t begin) {
  return end - begin;
}

}

TEST_CASE("Conventional BEGIN/END query counts the samples drawn in between", "[gpu][zpd]") {
  std::string error;
  auto fixture = CreateFixture(&error, "strict");
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  SetupDraw(*fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32);

  DrawRect(*fixture, 0, 0, 32, 32, 0xFF0000FF);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  WriteZPD(*fixture, begin, false);
  DrawRect(*fixture, 0, 0, 16, 8, 0xFF00FF00);
  WriteZPD(*fixture, end, true);
  REQUIRE(AwaitReport(*fixture, end));
  INFO(fixture->Metadata());

  CHECK(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) == 16u * 8u);

  CHECK(Delta(Total(*fixture, end), Total(*fixture, begin)) == 16u * 8u);
  CHECK(Delta(ZFail(*fixture, end), ZFail(*fixture, begin)) == 0u);
}

TEST_CASE("QueryBatch snapshots give per-interval counts, including empty intervals",
          "[gpu][zpd]") {
  std::string error;
  auto fixture = CreateFixture(&error, "strict");
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  SetupDraw(*fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32);
  uint32_t slots[4];
  for (uint32_t& slot : slots) {
    slot = AllocReport(*fixture);
  }

  WriteZPD(*fixture, slots[0], false);
  DrawRect(*fixture, 0, 0, 16, 16, 0xFFFFFFFF);
  WriteZPD(*fixture, slots[1], false);
  WriteZPD(*fixture, slots[2], false);
  DrawRect(*fixture, 0, 0, 4, 4, 0xFFFFFFFF);
  DrawRect(*fixture, 8, 8, 10, 10, 0xFFFFFFFF);
  WriteZPD(*fixture, slots[3], true);
  REQUIRE(AwaitReport(*fixture, slots[3]));

  CHECK(Delta(ZPass(*fixture, slots[1]), ZPass(*fixture, slots[0])) == 256u);
  CHECK(Delta(ZPass(*fixture, slots[2]), ZPass(*fixture, slots[1])) == 0u);
  CHECK(Delta(ZPass(*fixture, slots[3]), ZPass(*fixture, slots[2])) == 16u + 4u);
}

TEST_CASE("Depth-tested draws count only the samples that pass", "[gpu][zpd]") {
  std::string error;
  auto fixture = CreateFixture(&error, "strict");
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  Surface surface = {xenos::MsaaSamples::k1X, 64};
  DrawOptions options;

  options.color_base_tiles = 16;
  options.depth_control.z_enable = 1;
  options.depth_control.z_write_enable = 1;
  options.depth_control.zfunc = xenos::CompareFunction::kAlways;
  options.z = 0.5f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 32, 32, 0xFF000000);

  uint32_t reports[3];
  for (uint32_t& report : reports) {
    report = AllocReport(*fixture);
  }
  options.depth_control.zfunc = xenos::CompareFunction::kLess;
  WriteZPD(*fixture, reports[0], false);

  options.z = 0.75f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 32, 32, 0xFF0000FF);
  WriteZPD(*fixture, reports[1], false);

  options.z = 0.25f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 8, 32, 0xFF00FF00);
  WriteZPD(*fixture, reports[2], true);
  REQUIRE(AwaitReport(*fixture, reports[2]));
  INFO(fixture->Metadata());

  CHECK(Delta(ZPass(*fixture, reports[1]), ZPass(*fixture, reports[0])) == 0u);
  CHECK(Delta(ZPass(*fixture, reports[2]), ZPass(*fixture, reports[1])) == 8u * 32u);
}

TEST_CASE("A query spanning command list submissions accumulates every segment", "[gpu][zpd]") {
  std::string error;
  auto fixture = CreateFixture(&error, "strict");
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  SetupDraw(*fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  WriteZPD(*fixture, begin, false);
  DrawRect(*fixture, 0, 0, 8, 8, 0xFFFFFFFF);

  REQUIRE(fixture->Flush());
  DrawRect(*fixture, 16, 16, 24, 24, 0xFFFFFFFF);
  REQUIRE(fixture->Flush());
  DrawRect(*fixture, 0, 16, 4, 20, 0xFFFFFFFF);
  WriteZPD(*fixture, end, true);
  REQUIRE(AwaitReport(*fixture, end));

  CHECK(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) == 64u + 64u + 16u);
}

TEST_CASE("Reused report memory and recycled host queries stay exact", "[gpu][zpd]") {
  std::string error;
  auto fixture = CreateFixture(&error, "strict");
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  SetupDraw(*fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32);

  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  for (uint32_t round = 0; round < 3; ++round) {
    for (uint32_t width = 1; width <= 32; ++width) {
      WriteZPD(*fixture, begin, false);
      DrawRect(*fixture, 0, 0, width, 2, 0xFFFFFFFF);
      WriteZPD(*fixture, end, true);
      REQUIRE(AwaitReport(*fixture, end));
      INFO("round " << round << ", width " << width);
      REQUIRE(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) == width * 2);
    }
  }
}

TEST_CASE("A draw without a pixel shader or writes is still counted", "[gpu][zpd]") {
  std::string error;
  auto fixture = CreateFixture(&error, "strict");
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }

  DrawOptions options;
  options.color_mask = 0;
  SetupDraw(*fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32, options);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  WriteZPD(*fixture, begin, false);
  DrawRect(*fixture, 0, 0, 16, 16, 0);
  WriteZPD(*fixture, end, true);
  REQUIRE(AwaitReport(*fixture, end));
  INFO(fixture->Metadata());

  CHECK(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) == 256u);
}

TEST_CASE("MSAA queries count covered samples", "[gpu][zpd]") {
  std::string error;
  auto fixture = CreateFixture(&error, "strict");
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  SetupDraw(*fixture, {xenos::MsaaSamples::k4X, 64}, 16, 16);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  WriteZPD(*fixture, begin, false);
  DrawRect(*fixture, 0, 0, 8, 4, 0xFFFFFFFF);
  WriteZPD(*fixture, end, true);
  REQUIRE(AwaitReport(*fixture, end));
  INFO(fixture->Metadata());

  CHECK(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) == 8u * 4u * 4u);
}

TEST_CASE("Fast mode writes a visible guess, then the real count", "[gpu][zpd]") {
  std::string error;
  auto fixture = CreateFixture(&error, "fast");
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  SetupDraw(*fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  WriteZPD(*fixture, begin, false);
  DrawRect(*fixture, 0, 0, 16, 8, 0xFFFFFFFF);
  WriteZPD(*fixture, end, true);
  REQUIRE(fixture->Flush());

  CHECK(fixture->ReadDword(end + kZPassAOffset) != kPendingSentinel);
  CHECK(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) >= 1u);

  auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(10);
  while (Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) != 16u * 8u &&
         std::chrono::steady_clock::now() < deadline) {
    DrawRect(*fixture, 0, 0, 1, 1, 0xFFFFFFFF);
    REQUIRE(fixture->Flush());
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  CHECK(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) == 16u * 8u);
}

TEST_CASE("Fake mode reports the configured count for every interval", "[gpu][zpd]") {
  std::string error;
  auto fixture = CreateFixture(&error, "fake");
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  SetupDraw(*fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  WriteZPD(*fixture, begin, false);
  DrawRect(*fixture, 0, 0, 16, 8, 0xFFFFFFFF);
  WriteZPD(*fixture, end, true);
  REQUIRE(AwaitReport(*fixture, end));

  CHECK(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) == 1000u);
}

TEST_CASE("ROV BEGIN/END query counts the samples drawn in between", "[gpu][zpd][rov]") {
  std::string error;
  auto fixture = CreateRovFixture(&error, false);
  if (!fixture) {
    SKIP("ROV fixture unavailable: " << error);
  }
  SetupDraw(*fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32);
  DrawRect(*fixture, 0, 0, 32, 32, 0xFF0000FF);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  WriteZPD(*fixture, begin, false);
  DrawRect(*fixture, 0, 0, 16, 8, 0xFF00FF00);
  WriteZPD(*fixture, end, true);
  REQUIRE(AwaitReport(*fixture, end));
  INFO(fixture->Metadata());

  CHECK(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) == 16u * 8u);
  CHECK(Delta(Total(*fixture, end), Total(*fixture, begin)) == 16u * 8u);
  CHECK(Delta(ZFail(*fixture, end), ZFail(*fixture, begin)) == 0u);
}

TEST_CASE("ROV depth-tested draws count only the samples that pass", "[gpu][zpd][rov]") {
  std::string error;
  auto fixture = CreateRovFixture(&error, false);
  if (!fixture) {
    SKIP("ROV fixture unavailable: " << error);
  }
  Surface surface = {xenos::MsaaSamples::k1X, 64};
  DrawOptions options;
  options.color_base_tiles = 16;
  options.depth_control.z_enable = 1;
  options.depth_control.z_write_enable = 1;
  options.depth_control.zfunc = xenos::CompareFunction::kAlways;
  options.z = 0.5f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 32, 32, 0xFF000000);

  uint32_t reports[3];
  for (uint32_t& report : reports) {
    report = AllocReport(*fixture);
  }
  options.depth_control.zfunc = xenos::CompareFunction::kLess;
  WriteZPD(*fixture, reports[0], false);
  options.z = 0.75f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 32, 32, 0xFF0000FF);
  WriteZPD(*fixture, reports[1], false);
  options.z = 0.25f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 8, 32, 0xFF00FF00);
  WriteZPD(*fixture, reports[2], true);
  REQUIRE(AwaitReport(*fixture, reports[2]));
  INFO(fixture->Metadata());

  CHECK(Delta(ZPass(*fixture, reports[1]), ZPass(*fixture, reports[0])) == 0u);
  CHECK(Delta(ZPass(*fixture, reports[2]), ZPass(*fixture, reports[1])) == 8u * 32u);

  CHECK(Delta(ZFail(*fixture, reports[1]), ZFail(*fixture, reports[0])) == 0u);
}

TEST_CASE("ROV full counters split depth and stencil failures", "[gpu][zpd][rov]") {
  std::string error;
  auto fixture = CreateRovFixture(&error, true);
  if (!fixture) {
    SKIP("ROV fixture unavailable: " << error);
  }
  Surface surface = {xenos::MsaaSamples::k1X, 64};
  DrawOptions options;
  options.color_base_tiles = 16;
  options.depth_control.z_enable = 1;
  options.depth_control.z_write_enable = 1;
  options.depth_control.zfunc = xenos::CompareFunction::kAlways;
  options.z = 0.5f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 32, 32, 0xFF000000);

  uint32_t reports[4];
  for (uint32_t& report : reports) {
    report = AllocReport(*fixture);
  }
  options.depth_control.z_write_enable = 0;
  options.depth_control.zfunc = xenos::CompareFunction::kLess;
  WriteZPD(*fixture, reports[0], false);

  options.z = 0.75f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 32, 32, 0xFF0000FF);
  WriteZPD(*fixture, reports[1], false);

  DrawOptions stencil = options;
  stencil.z = 0.75f;
  stencil.depth_control.stencil_enable = 1;
  stencil.depth_control.stencilfunc = xenos::CompareFunction::kNever;
  SetupDraw(*fixture, surface, 32, 32, stencil);
  DrawRect(*fixture, 0, 0, 8, 32, 0xFF00FF00);
  WriteZPD(*fixture, reports[2], false);

  options.z = 0.25f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 4, 32, 0xFFFF0000);
  WriteZPD(*fixture, reports[3], true);
  REQUIRE(AwaitReport(*fixture, reports[3]));
  INFO(fixture->Metadata());

  struct Counters {
    uint32_t zpass, zfail, stencil_fail, total;
  };
  auto interval = [&](uint32_t i) {
    return Counters{Delta(ZPass(*fixture, reports[i + 1]), ZPass(*fixture, reports[i])),
                    Delta(ZFail(*fixture, reports[i + 1]), ZFail(*fixture, reports[i])),
                    Delta(StencilFail(*fixture, reports[i + 1]), StencilFail(*fixture, reports[i])),
                    Delta(Total(*fixture, reports[i + 1]), Total(*fixture, reports[i]))};
  };
  Counters depth = interval(0);
  CHECK(depth.zfail == 32u * 32u);
  CHECK(depth.zpass == 0u);
  CHECK(depth.stencil_fail == 0u);
  CHECK(depth.total == 32u * 32u);
  Counters stencil_failed = interval(1);
  CHECK(stencil_failed.stencil_fail == 8u * 32u);
  CHECK(stencil_failed.zfail == 0u);
  CHECK(stencil_failed.zpass == 0u);
  CHECK(stencil_failed.total == 8u * 32u);
  Counters passed = interval(2);
  CHECK(passed.zpass == 4u * 32u);
  CHECK(passed.zfail + passed.stencil_fail == 0u);
  CHECK(passed.total == 4u * 32u);
}

TEST_CASE("ROV counter slots are cleared when a query reuses them", "[gpu][zpd][rov]") {
  std::string error;
  auto fixture = CreateRovFixture(&error, false);
  if (!fixture) {
    SKIP("ROV fixture unavailable: " << error);
  }
  SetupDraw(*fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);

  for (uint32_t width = 1; width <= 32; ++width) {
    WriteZPD(*fixture, begin, false);
    DrawRect(*fixture, 0, 0, width, 2, 0xFFFFFFFF);
    WriteZPD(*fixture, end, true);
    REQUIRE(AwaitReport(*fixture, end));
    INFO("width " << width);
    REQUIRE(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) == width * 2);
  }
}

TEST_CASE("ROV MSAA queries count covered samples", "[gpu][zpd][rov]") {
  std::string error;
  auto fixture = CreateRovFixture(&error, false);
  if (!fixture) {
    SKIP("ROV fixture unavailable: " << error);
  }
  SetupDraw(*fixture, {xenos::MsaaSamples::k4X, 64}, 16, 16);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  WriteZPD(*fixture, begin, false);
  DrawRect(*fixture, 0, 0, 8, 4, 0xFFFFFFFF);
  WriteZPD(*fixture, end, true);
  REQUIRE(AwaitReport(*fixture, end));
  INFO(fixture->Metadata());

  CHECK(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) == 8u * 4u * 4u);
}

namespace {

std::unique_ptr<GpuFixture> CreateHybridFixture(std::string* error) {
  return GpuFixture::Create(error, {{"occlusion_query", "strict"},
                                    {"async_shader_compilation", "false"},
                                    {"render_target_path_d3d12", "rtv"},
                                    {"occlusion_query_full_counters", "true"}});
}

struct Interval {
  uint32_t zpass, zfail, stencil_fail, total;
};

Interval Between(GpuFixture& fixture, uint32_t begin, uint32_t end) {
  return {Delta(ZPass(fixture, end), ZPass(fixture, begin)),
          Delta(ZFail(fixture, end), ZFail(fixture, begin)),
          Delta(StencilFail(fixture, end), StencilFail(fixture, begin)),
          Delta(Total(fixture, end), Total(fixture, begin))};
}

DrawOptions PrimeDepth(GpuFixture& fixture, const Surface& surface) {
  DrawOptions options;
  options.color_base_tiles = 16;
  options.depth_control.z_enable = 1;
  options.depth_control.z_write_enable = 1;
  options.depth_control.zfunc = xenos::CompareFunction::kAlways;
  options.z = 0.5f;
  SetupDraw(fixture, surface, 32, 32, options);
  DrawRect(fixture, 0, 0, 32, 32, 0xFF000000);
  options.depth_control.z_write_enable = 0;
  options.depth_control.zfunc = xenos::CompareFunction::kLess;
  return options;
}

}

TEST_CASE("RTV full counters count rejected samples in Total", "[gpu][zpd][hybrid]") {
  std::string error;
  auto fixture = CreateHybridFixture(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  Surface surface = {xenos::MsaaSamples::k1X, 64};
  DrawOptions options = PrimeDepth(*fixture, surface);

  uint32_t reports[4];
  for (uint32_t& report : reports) {
    report = AllocReport(*fixture);
  }
  WriteZPD(*fixture, reports[0], false);

  options.z = 0.75f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 32, 32, 0xFF0000FF);
  WriteZPD(*fixture, reports[1], false);

  DrawOptions stencil = options;
  stencil.depth_control.stencil_enable = 1;
  stencil.depth_control.stencilfunc = xenos::CompareFunction::kNever;
  SetupDraw(*fixture, surface, 32, 32, stencil);
  DrawRect(*fixture, 0, 0, 8, 32, 0xFF00FF00);
  WriteZPD(*fixture, reports[2], false);

  options.z = 0.25f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 4, 32, 0xFFFF0000);
  WriteZPD(*fixture, reports[3], true);
  REQUIRE(AwaitReport(*fixture, reports[3]));
  INFO(fixture->Metadata());

  Interval depth = Between(*fixture, reports[0], reports[1]);
  CHECK(depth.zpass == 0u);
  CHECK(depth.zfail == 32u * 32u);
  CHECK(depth.stencil_fail == 0u);
  CHECK(depth.total == 32u * 32u);
  Interval stencil_failed = Between(*fixture, reports[1], reports[2]);
  CHECK(stencil_failed.zpass == 0u);
  CHECK(stencil_failed.zfail == 8u * 32u);
  CHECK(stencil_failed.stencil_fail == 0u);
  CHECK(stencil_failed.total == 8u * 32u);
  Interval passed = Between(*fixture, reports[2], reports[3]);
  CHECK(passed.zpass == 4u * 32u);
  CHECK(passed.zfail == 0u);
  CHECK(passed.total == 4u * 32u);
}

TEST_CASE("RTV full counters count a draw without a pixel shader", "[gpu][zpd][hybrid]") {
  std::string error;
  auto fixture = CreateHybridFixture(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  Surface surface = {xenos::MsaaSamples::k1X, 64};
  DrawOptions options = PrimeDepth(*fixture, surface);

  options.color_mask = 0;
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  WriteZPD(*fixture, begin, false);
  options.z = 0.75f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 16, 16, 0);
  options.z = 0.25f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 16, 16, 24, 24, 0);
  WriteZPD(*fixture, end, true);
  REQUIRE(AwaitReport(*fixture, end));
  INFO(fixture->Metadata());

  Interval counts = Between(*fixture, begin, end);
  CHECK(counts.zpass == 8u * 8u);
  CHECK(counts.zfail == 16u * 16u);
  CHECK(counts.total == 16u * 16u + 8u * 8u);
}

TEST_CASE("RTV full counters leave depth-writing draws to the native query", "[gpu][zpd][hybrid]") {
  std::string error;
  auto fixture = CreateHybridFixture(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  Surface surface = {xenos::MsaaSamples::k1X, 64};
  DrawOptions options = PrimeDepth(*fixture, surface);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  WriteZPD(*fixture, begin, false);

  DrawOptions writing = options;
  writing.depth_control.z_write_enable = 1;
  writing.z = 0.25f;
  SetupDraw(*fixture, surface, 32, 32, writing);
  DrawRect(*fixture, 0, 0, 16, 32, 0xFF00FF00);

  options.z = 0.75f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 16, 0, 32, 32, 0xFF0000FF);
  WriteZPD(*fixture, end, true);
  REQUIRE(AwaitReport(*fixture, end));
  INFO(fixture->Metadata());

  Interval counts = Between(*fixture, begin, end);
  CHECK(counts.zpass == 16u * 32u);
  CHECK(counts.zfail == 16u * 32u);
  CHECK(counts.total == 32u * 32u);
}

TEST_CASE("RTV hybrid counter slots are cleared when a query reuses them", "[gpu][zpd][hybrid]") {
  std::string error;
  auto fixture = CreateHybridFixture(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  Surface surface = {xenos::MsaaSamples::k1X, 64};
  DrawOptions options = PrimeDepth(*fixture, surface);
  options.z = 0.75f;
  SetupDraw(*fixture, surface, 32, 32, options);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  for (uint32_t width = 1; width <= 16; ++width) {
    WriteZPD(*fixture, begin, false);
    DrawRect(*fixture, 0, 0, width, 2, 0xFFFFFFFF);
    WriteZPD(*fixture, end, true);
    REQUIRE(AwaitReport(*fixture, end));
    INFO("width " << width);
    REQUIRE(Between(*fixture, begin, end).zfail == width * 2);
  }
}

TEST_CASE("RTV hybrid MSAA queries count covered samples", "[gpu][zpd][hybrid]") {
  std::string error;
  auto fixture = CreateHybridFixture(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  Surface surface = {xenos::MsaaSamples::k4X, 64};
  DrawOptions options = PrimeDepth(*fixture, surface);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  WriteZPD(*fixture, begin, false);
  options.z = 0.75f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 8, 4, 0xFFFFFFFF);
  WriteZPD(*fixture, end, true);
  REQUIRE(AwaitReport(*fixture, end));
  INFO(fixture->Metadata());

  Interval counts = Between(*fixture, begin, end);
  CHECK(counts.zpass == 0u);
  CHECK(counts.zfail == 8u * 4u * 4u);
  CHECK(counts.total == 8u * 4u * 4u);
}
