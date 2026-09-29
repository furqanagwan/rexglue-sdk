/**
 * @file        rex/graphics/frame_stats.h
 * @brief       Frame pacing statistics between guest swaps, for the log
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include <fmt/format.h>

namespace rex::graphics {

// Collects the time between guest frame swaps and summarizes a window of them.
// Not thread-safe: the command processor thread owns it.
class FrameStats {
 public:
  struct Summary {
    size_t frames = 0;
    double seconds = 0;
    double fps = 0;
    double average_ms = 0;
    double p95_ms = 0;
    double p99_ms = 0;
    double max_ms = 0;
    // Frames that took longer than one or two 60 Hz refreshes.
    size_t over_16_7_ms = 0;
    size_t over_33_3_ms = 0;
  };

  void Add(double frame_ms) {
    frame_ms_.push_back(frame_ms);
    total_ms_ += frame_ms;
  }

  double window_seconds() const { return total_ms_ / 1000.0; }
  bool empty() const { return frame_ms_.empty(); }

  // Summarizes the frames since the last call and starts a new window.
  Summary Take() {
    Summary summary;
    summary.frames = frame_ms_.size();
    if (!summary.frames) {
      return summary;
    }
    summary.seconds = total_ms_ / 1000.0;
    summary.average_ms = total_ms_ / double(summary.frames);
    summary.fps = summary.seconds > 0 ? double(summary.frames) / summary.seconds : 0;
    for (double ms : frame_ms_) {
      summary.over_16_7_ms += ms > 1000.0 / 60.0 + kSlackMs;
      summary.over_33_3_ms += ms > 2000.0 / 60.0 + kSlackMs;
    }
    std::sort(frame_ms_.begin(), frame_ms_.end());
    auto percentile = [this](double p) {
      size_t index = size_t(p * double(frame_ms_.size() - 1) + 0.5);
      return frame_ms_[std::min(index, frame_ms_.size() - 1)];
    };
    summary.p95_ms = percentile(0.95);
    summary.p99_ms = percentile(0.99);
    summary.max_ms = frame_ms_.back();
    frame_ms_.clear();
    total_ms_ = 0;
    return summary;
  }

  static std::string Format(const Summary& s) {
    return fmt::format(
        "{} frames in {:.1f} s, {:.1f} fps; frame time avg {:.2f} ms, p95 {:.2f}, p99 {:.2f}, "
        "max {:.2f}; {} over 16.7 ms, {} over 33.3 ms",
        s.frames, s.seconds, s.fps, s.average_ms, s.p95_ms, s.p99_ms, s.max_ms, s.over_16_7_ms,
        s.over_33_3_ms);
  }

 private:
  // Swap timing jitters by a fraction of a millisecond; a frame is only late
  // when it clearly misses a refresh.
  static constexpr double kSlackMs = 1.0;

  std::vector<double> frame_ms_;
  double total_ms_ = 0;
};

}  // namespace rex::graphics
