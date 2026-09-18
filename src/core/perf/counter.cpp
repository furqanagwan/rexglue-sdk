/**
 * @file        core/perf/counter.cpp
 * @brief       Performance counter registry implementation
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#include <rex/perf/counter.h>

#include <rex/cvar.h>
#include <rex/filesystem.h>
#include <rex/logging.h>

#include <array>
#include <algorithm>
#include <atomic>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <mutex>
#include <vector>

REXCVAR_DEFINE_STRING(perf_log_csv, "", "Perf",
                      "Path to write per-frame CSV log (empty = disabled)");
REXCVAR_DEFINE_INT32(perf_capture_frames, 120, "Perf",
                     "Number of frames collected by a programmatic performance capture");

namespace rex::perf {

namespace {

constexpr size_t kNumCounters = static_cast<size_t>(CounterId::kCount);

std::array<std::atomic<int64_t>, kNumCounters> g_counters{};
std::array<std::atomic<int64_t>, kNumCounters> g_snapshot{};

constexpr const char* kCounterNames[] = {
    "frame_time_us",
    "fps",
    "draw_calls",
    "command_buffer_stalls",
    "vertices_processed",
    "xma_frames_decoded",
    "audio_frame_latency_us",
    "buffer_queue_depth",
    "functions_dispatched",
    "interrupt_dispatches",
    "active_threads",
    "apc_queue_depth",
    "critical_region_contentions",
    "texture_cache_hits",
    "texture_cache_misses",
    "pipeline_cache_hits",
    "pipeline_cache_misses",
};
static_assert(std::size(kCounterNames) == kNumCounters, "kCounterNames must match CounterId enum");

// Gauge counters are snapshotted but NOT zeroed each frame.
// Accumulators (everything else) are zeroed after snapshot.
constexpr bool kIsGauge[] = {
    false,  // kFrameTimeUs       (set each frame)
    false,  // kFps               (set each frame)
    false,  // kDrawCalls
    false,  // kCommandBufferStalls
    false,  // kVerticesProcessed
    false,  // kXmaFramesDecoded
    false,  // kAudioFrameLatencyUs
    false,  // kBufferQueueDepth  (set each frame)
    false,  // kFunctionsDispatched
    false,  // kInterruptDispatches
    true,   // kActiveThreads     (inc/dec over lifetime)
    false,  // kApcQueueDepth
    true,   // kCriticalRegionContentions (running total)
    false,  // kTextureCacheHits
    false,  // kTextureCacheMisses
    false,  // kPipelineCacheHits
    false,  // kPipelineCacheMisses
};
static_assert(std::size(kIsGauge) == kNumCounters, "kIsGauge must match CounterId enum");

// CSV state
std::FILE* g_csv_file = nullptr;
std::string g_csv_path;
int g_csv_frame_count = 0;

using CounterValues = std::array<int64_t, kNumCounters>;

struct CaptureState {
  bool active = false;
  uint32_t frames_remaining = 0;
  std::filesystem::path counters_path;
  std::filesystem::path frame_samples_path;
  CounterValues totals{};
  std::vector<CounterValues> frames;
};

std::mutex g_capture_mutex;
CaptureState g_capture;
std::atomic<bool> g_capture_recording{false};

bool SaveCapture(const CaptureState& capture) {
  std::ofstream counters(capture.counters_path, std::ios::out | std::ios::trunc);
  std::ofstream frames(capture.frame_samples_path, std::ios::out | std::ios::trunc);
  if (!counters || !frames) {
    return false;
  }

  const size_t frame_count = std::max<size_t>(capture.frames.size(), 1);
  counters << "counter,total,avg_per_frame\n";
  for (size_t i = 0; i < kNumCounters; ++i) {
    counters << kCounterNames[i] << ',' << capture.totals[i] << ','
             << static_cast<double>(capture.totals[i]) / static_cast<double>(frame_count) << '\n';
  }

  frames << "frame";
  for (const char* name : kCounterNames) {
    frames << ',' << name;
  }
  frames << '\n';
  for (size_t frame_index = 0; frame_index < capture.frames.size(); ++frame_index) {
    frames << frame_index;
    for (int64_t value : capture.frames[frame_index]) {
      frames << ',' << value;
    }
    frames << '\n';
  }
  return true;
}

}  // anonymous namespace

const char* CounterName(CounterId id) {
  auto idx = static_cast<size_t>(id);
  if (idx < kNumCounters)
    return kCounterNames[idx];
  return "unknown";
}

void SetCounter(CounterId id, int64_t value) {
  g_counters[static_cast<size_t>(id)].store(value, std::memory_order_relaxed);
}

void IncrementCounter(CounterId id, int64_t delta) {
  g_counters[static_cast<size_t>(id)].fetch_add(delta, std::memory_order_relaxed);
}

int64_t GetCounter(CounterId id) {
  return g_counters[static_cast<size_t>(id)].load(std::memory_order_relaxed);
}

void ResetFrameCounters() {
  CounterValues frame{};
  for (size_t i = 0; i < kNumCounters; ++i) {
    if (kIsGauge[i]) {
      // Gauges: snapshot the current value, don't zero
      g_snapshot[i].store(g_counters[i].load(std::memory_order_relaxed), std::memory_order_relaxed);
    } else {
      // Accumulators: snapshot and zero for next frame
      g_snapshot[i].store(g_counters[i].exchange(0, std::memory_order_relaxed),
                          std::memory_order_relaxed);
    }
    frame[i] = g_snapshot[i].load(std::memory_order_relaxed);
  }

  CaptureState completed_capture;
  bool capture_completed = false;
  {
    std::lock_guard lock(g_capture_mutex);
    if (g_capture.active) {
      g_capture.frames.push_back(frame);
      for (size_t i = 0; i < kNumCounters; ++i) {
        g_capture.totals[i] += frame[i];
      }
      if (--g_capture.frames_remaining == 0) {
        completed_capture = std::move(g_capture);
        g_capture = {};
        g_capture_recording.store(false, std::memory_order_release);
        capture_completed = true;
      }
    }
  }

  if (capture_completed) {
    if (SaveCapture(completed_capture)) {
      REXLOG_INFO("Saved performance capture to {} and {}",
                  completed_capture.counters_path.string(),
                  completed_capture.frame_samples_path.string());
    } else {
      REXLOG_WARN("Failed to save performance capture to {} and {}",
                  completed_capture.counters_path.string(),
                  completed_capture.frame_samples_path.string());
    }
  }
}

int64_t GetSnapshotCounter(CounterId id) {
  return g_snapshot[static_cast<size_t>(id)].load(std::memory_order_relaxed);
}

void Init() {
  for (auto& c : g_counters)
    c.store(0, std::memory_order_relaxed);
  for (auto& s : g_snapshot)
    s.store(0, std::memory_order_relaxed);
  std::lock_guard lock(g_capture_mutex);
  g_capture = {};
  g_capture_recording.store(false, std::memory_order_release);
}

bool StartCapture(const std::filesystem::path& counters_path,
                  const std::filesystem::path& frame_samples_path) {
  if (counters_path.empty() || frame_samples_path.empty()) {
    return false;
  }
  std::lock_guard lock(g_capture_mutex);
  if (g_capture.active) {
    return false;
  }

  g_capture = {};
  g_capture.active = true;
  g_capture.frames_remaining =
      static_cast<uint32_t>(std::max(INT32_C(1), REXCVAR_GET(perf_capture_frames)));
  g_capture.counters_path = counters_path;
  g_capture.frame_samples_path = frame_samples_path;
  g_capture.frames.reserve(g_capture.frames_remaining);
  g_capture_recording.store(true, std::memory_order_release);
  return true;
}

bool IsCaptureRecording() {
  return g_capture_recording.load(std::memory_order_acquire);
}

void SetCsvLogPath(const std::string& path) {
  if (g_csv_file) {
    std::fflush(g_csv_file);
    std::fclose(g_csv_file);
    g_csv_file = nullptr;
  }
  g_csv_path = path;
  g_csv_frame_count = 0;

  if (path.empty())
    return;

  g_csv_file = rex::filesystem::OpenFile(rex::to_path(path), "w");
  if (!g_csv_file) {
    REXLOG_WARN("perf: failed to open CSV log: {}", path);
    g_csv_path.clear();
    return;
  }

  // Write header
  for (size_t i = 0; i < kNumCounters; ++i) {
    if (i > 0)
      std::fputc(',', g_csv_file);
    std::fputs(kCounterNames[i], g_csv_file);
  }
  std::fputc('\n', g_csv_file);
}

void WriteCsvFrame() {
  if (!g_csv_file)
    return;

  for (size_t i = 0; i < kNumCounters; ++i) {
    if (i > 0)
      std::fputc(',', g_csv_file);
    std::fprintf(g_csv_file, "%lld",
                 static_cast<long long>(g_snapshot[i].load(std::memory_order_relaxed)));
  }
  std::fputc('\n', g_csv_file);

  if (++g_csv_frame_count % 60 == 0) {
    std::fflush(g_csv_file);
  }
}

void FlushCsv() {
  if (g_csv_file) {
    std::fflush(g_csv_file);
    std::fclose(g_csv_file);
    g_csv_file = nullptr;
  }
  g_csv_path.clear();
}

}  // namespace rex::perf
