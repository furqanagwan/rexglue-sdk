/**
 * @file        frame_stats_test.cpp
 * @brief       Frame pacing summaries for frame_stats_interval
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/frame_stats.h>

using Catch::Approx;
using rex::graphics::FrameStats;

TEST_CASE("Frame stats summarize steady 60 fps", "[graphics][frame-stats]") {
  FrameStats stats;
  for (int i = 0; i < 600; ++i) {
    stats.Add(1000.0 / 60.0);
  }
  CHECK(stats.window_seconds() == Approx(10.0));
  auto s = stats.Take();
  CHECK(s.frames == 600);
  CHECK(s.fps == Approx(60.0));
  CHECK(s.average_ms == Approx(16.667).epsilon(0.001));
  CHECK(s.p99_ms == Approx(16.667).epsilon(0.001));
  // Jitter within a millisecond of a refresh is not a late frame.
  CHECK(s.over_16_7_ms == 0);
  CHECK(s.over_33_3_ms == 0);
  CHECK(stats.empty());
  CHECK(stats.Take().frames == 0);
}

TEST_CASE("Frame stats count late frames and tail percentiles", "[graphics][frame-stats]") {
  FrameStats stats;
  for (int i = 0; i < 90; ++i) {
    stats.Add(16.7);
  }
  for (int i = 0; i < 9; ++i) {
    stats.Add(33.3);  // missed one refresh
  }
  stats.Add(100.0);  // a hitch
  auto s = stats.Take();
  CHECK(s.frames == 100);
  CHECK(s.over_16_7_ms == 10);
  CHECK(s.over_33_3_ms == 1);
  CHECK(s.max_ms == 100.0);
  CHECK(s.p95_ms == Approx(33.3));
  CHECK(s.p99_ms == Approx(33.3));
  CHECK(FrameStats::Format(s).find("100 frames") == 0);
}
