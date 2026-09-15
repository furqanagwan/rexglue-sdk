/**
 * @file        core/perf/frame_stats.cpp
 * @brief       Per-frame timing log for automated performance runs
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#include <rex/perf/frame_stats.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <mutex>
#include <string>
#include <vector>

#include <rex/cvar.h>
#include <rex/filesystem.h>
#include <rex/logging.h>

REXCVAR_DEFINE_STRING(frame_stats_csv, "", "Perf",
                      "Write one line per guest frame (frame time, draws, resolves) to this "
                      "CSV file and log an FPS summary on exit. Empty disables it.");

namespace rex::perf::frame_stats {
namespace {

using Clock = std::chrono::steady_clock;

std::atomic<uint32_t> g_draws{0};
std::atomic<uint32_t> g_resolves{0};

std::mutex g_mutex;
FILE* g_file = nullptr;
bool g_opened = false;
uint64_t g_frame = 0;
Clock::time_point g_last_frame;
std::vector<float> g_frame_ms;

bool EnsureOpen() {
  if (g_opened) {
    return g_file != nullptr;
  }
  g_opened = true;
  const std::string path = REXCVAR_GET(frame_stats_csv);
  if (path.empty()) {
    return false;
  }
  g_file = rex::filesystem::OpenFile(rex::to_path(path), "w");
  if (!g_file) {
    REXLOG_WARN("frame_stats: cannot open {}", path);
    return false;
  }
  std::fputs("frame,frame_ms,draws,resolves\n", g_file);
  return true;
}

}  // namespace

void RecordDraw() {
  g_draws.fetch_add(1, std::memory_order_relaxed);
}

void RecordResolve() {
  g_resolves.fetch_add(1, std::memory_order_relaxed);
}

void RecordFrame() {
  const uint32_t draws = g_draws.exchange(0, std::memory_order_relaxed);
  const uint32_t resolves = g_resolves.exchange(0, std::memory_order_relaxed);
  std::lock_guard lock(g_mutex);
  if (!EnsureOpen()) {
    return;
  }
  const auto now = Clock::now();
  if (g_frame > 0) {
    const float frame_ms = std::chrono::duration<float, std::milli>(now - g_last_frame).count();
    g_frame_ms.push_back(frame_ms);
    std::fprintf(g_file, "%llu,%.3f,%u,%u\n", static_cast<unsigned long long>(g_frame), frame_ms,
                 draws, resolves);
    // Runs are often ended by killing the process, so keep the file current.
    if (g_frame % 30 == 0) {
      std::fflush(g_file);
    }
  }
  g_last_frame = now;
  ++g_frame;
}

void Shutdown() {
  std::lock_guard lock(g_mutex);
  if (!g_file) {
    return;
  }
  if (!g_frame_ms.empty()) {
    double total = 0.0;
    for (float ms : g_frame_ms) {
      total += ms;
    }
    std::vector<float> sorted = g_frame_ms;
    std::sort(sorted.begin(), sorted.end());
    // 1% low: the frame rate of the slowest 1% of frames.
    const size_t slow_count = std::max<size_t>(1, sorted.size() / 100);
    double slow_total = 0.0;
    for (size_t i = sorted.size() - slow_count; i < sorted.size(); ++i) {
      slow_total += sorted[i];
    }
    REXLOG_INFO("frame_stats: {} frames, average {:.1f} fps, 1% low {:.1f} fps, worst {:.1f} ms",
                g_frame_ms.size(), 1000.0 * g_frame_ms.size() / total,
                1000.0 * slow_count / slow_total, sorted.back());
  }
  std::fclose(g_file);
  g_file = nullptr;
}

}  // namespace rex::perf::frame_stats
