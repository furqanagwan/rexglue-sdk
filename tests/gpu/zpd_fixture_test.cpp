/**
 * @file        zpd_fixture_test.cpp
 * @brief       EVENT_WRITE_ZPD occlusion query reports through the GPU plugin (RG-GDK-010)
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

// D3D's pending marker, written big-endian to ZPass_A of the END report
// before the event and polled until the GPU overwrites it.
constexpr uint32_t kPendingSentinel = 0xFFFFFEED;
constexpr uint32_t kZPassAOffset = 16;

std::unique_ptr<GpuFixture> CreateFixture(std::string* error, const char* mode) {
  // Otherwise draws are dropped while their pipelines compile.
  return GpuFixture::Create(error,
                            {{"occlusion_query", mode}, {"async_shader_compilation", "false"}});
}

// One sample counter report, as D3D reserves it.
uint32_t AllocReport(GpuFixture& fixture) {
  uint32_t report = fixture.AllocPhysical(0x100, 0x100);
  fixture.WriteDwords(report, std::vector<uint32_t>(8, 0));
  return report;
}

// EVENT_WRITE_ZPD at report. D3D marks the report it will wait on (the END of
// a conventional query) with the pending sentinel first.
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

// Waits for the command processor to write the awaited report back. Reports
// retire in stream order, so every earlier one is final too.
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

// The guest's END - BEGIN, in 32-bit arithmetic as D3D does it.
uint32_t Delta(uint32_t end, uint32_t begin) {
  return end - begin;
}

}  // namespace

TEST_CASE("Conventional BEGIN/END query counts the samples drawn in between", "[gpu][zpd]") {
  std::string error;
  auto fixture = CreateFixture(&error, "strict");
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  SetupDraw(*fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32);
  // Drawn outside any query; must not be counted.
  DrawRect(*fixture, 0, 0, 32, 32, 0xFF0000FF);
  uint32_t begin = AllocReport(*fixture);
  uint32_t end = AllocReport(*fixture);
  WriteZPD(*fixture, begin, false);
  DrawRect(*fixture, 0, 0, 16, 8, 0xFF00FF00);
  WriteZPD(*fixture, end, true);
  REQUIRE(AwaitReport(*fixture, end));
  INFO(fixture->Metadata());

  CHECK(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) == 16u * 8u);
  // Host queries count ZPass only: Total is ZPass and nothing fails.
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
  // Issue, draw, Issue, Issue, draw, draw, Issue: N intervals from N + 1
  // snapshots of one running counter.
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
  // Color after the depth buffer in EDRAM rather than aliasing it.
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
  // Behind the depth buffer everywhere: fully occluded.
  options.z = 0.75f;
  SetupDraw(*fixture, surface, 32, 32, options);
  DrawRect(*fixture, 0, 0, 32, 32, 0xFF0000FF);
  WriteZPD(*fixture, reports[1], false);
  // In front, over a quarter of the target.
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
  // The command processor goes idle and submits, closing the host query; the
  // next draw opens a new segment for the same report.
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
  // The same two reports for every query, as titles reuse query objects; the
  // host slots of each round are released and handed out again in the next.
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
  // No color writes and no depth/stencil writes: the draw has no pixel shader
  // and writes nothing, as occlusion-only proxies do (4541096E, 5553083B).
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

  // Host samples, as Canary reports them; not verified against a console.
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
  // Written at the event without waiting: never the sentinel, never occluded.
  CHECK(fixture->ReadDword(end + kZPassAOffset) != kPendingSentinel);
  CHECK(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) >= 1u);

  // Later submissions retire the report and write the real count over the
  // guess. Draws after the last event don't belong to the measured interval.
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

  // query_occlusion_fake_sample_count, whatever was drawn.
  CHECK(Delta(ZPass(*fixture, end), ZPass(*fixture, begin)) == 1000u);
}
