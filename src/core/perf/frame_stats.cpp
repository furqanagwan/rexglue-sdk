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
std::atomic<uint64_t> g_gpu_wait_us{0};
std::atomic<uint64_t> g_upload_bytes{0};

// Per kind of work: how many, time on the command thread, time elsewhere.
struct WorkCounters {
  std::atomic<uint32_t> count{0};
  std::atomic<uint64_t> command_us{0};
  std::atomic<uint64_t> background_us{0};
};
WorkCounters g_work[size_t(Work::kCount)];
thread_local bool t_command_thread = false;

uint64_t NowMicroseconds() {
  return uint64_t(std::chrono::duration_cast<std::chrono::microseconds>(
                      Clock::now().time_since_epoch())
                      .count());
}

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
  std::fputs("frame,frame_ms,gpu_wait_ms,draws,resolves,textures,texture_ms,shaders,shader_ms,"
             "shader_bg_ms,pipelines,pipeline_ms,pipeline_bg_ms,draw_ms,resolve_ms,swap_ms,"
             "submit_ms,draw_setup_ms,draw_primitives_ms,draw_render_targets_ms,"
             "draw_pipeline_ms,draw_textures_ms,draw_state_ms,draw_bindings_ms,"
             "draw_vertices_ms,upload_mb,upload_ms,watch_ms\n",
             g_file);
  return true;
}

}  // namespace

void RecordDraw() {
  g_draws.fetch_add(1, std::memory_order_relaxed);
}

void RecordResolve() {
  g_resolves.fetch_add(1, std::memory_order_relaxed);
}

void RecordGpuWait(uint64_t microseconds) {
  g_gpu_wait_us.fetch_add(microseconds, std::memory_order_relaxed);
}

void RecordUpload(uint64_t bytes) {
  g_upload_bytes.fetch_add(bytes, std::memory_order_relaxed);
}

void MarkCommandThread() {
  t_command_thread = true;
}

namespace {

void Credit(Work work, uint64_t elapsed_us) {
  WorkCounters& counters = g_work[static_cast<size_t>(work)];
  counters.count.fetch_add(1, std::memory_order_relaxed);
  (t_command_thread ? counters.command_us : counters.background_us)
      .fetch_add(elapsed_us, std::memory_order_relaxed);
}

}  // namespace

ScopedWork::ScopedWork(Work work) : work_(work), start_us_(NowMicroseconds()) {}

ScopedWork::~ScopedWork() {
  Credit(work_, NowMicroseconds() - start_us_);
}

StageTimer::StageTimer(Work final_stage) : final_stage_(final_stage), last_us_(NowMicroseconds()) {}

StageTimer::~StageTimer() {
  Credit(final_stage_, NowMicroseconds() - last_us_);
}

void StageTimer::Mark(Work finished_stage) {
  const uint64_t now = NowMicroseconds();
  Credit(finished_stage, now - last_us_);
  last_us_ = now;
}

void RecordFrame() {
  const uint64_t gpu_wait_us = g_gpu_wait_us.exchange(0, std::memory_order_relaxed);
  const uint32_t draws = g_draws.exchange(0, std::memory_order_relaxed);
  const uint32_t resolves = g_resolves.exchange(0, std::memory_order_relaxed);
  const uint64_t upload_bytes = g_upload_bytes.exchange(0, std::memory_order_relaxed);
  struct Taken {
    uint32_t count;
    double command_ms;
    double background_ms;
  } work[size_t(Work::kCount)];
  for (size_t i = 0; i < size_t(Work::kCount); ++i) {
    work[i] = {g_work[i].count.exchange(0, std::memory_order_relaxed),
               double(g_work[i].command_us.exchange(0, std::memory_order_relaxed)) / 1000.0,
               double(g_work[i].background_us.exchange(0, std::memory_order_relaxed)) / 1000.0};
  }
  const Taken& textures = work[size_t(Work::kTextureLoad)];
  const Taken& shaders = work[size_t(Work::kShaderTranslation)];
  const Taken& pipelines = work[size_t(Work::kPipelineCreation)];
  const auto phase_ms = [&](Work kind) {
    return work[size_t(kind)].command_ms + work[size_t(kind)].background_ms;
  };
  std::lock_guard lock(g_mutex);
  if (!EnsureOpen()) {
    return;
  }
  const auto now = Clock::now();
  if (g_frame > 0) {
    const float frame_ms = std::chrono::duration<float, std::milli>(now - g_last_frame).count();
    g_frame_ms.push_back(frame_ms);
    // Texture loads only happen on the command thread; their background time
    // is always zero, so it is folded in rather than given a column.
    std::fprintf(g_file, "%llu,%.3f,%.3f,%u,%u,%u,%.3f,%u,%.3f,%.3f,%u,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n",
                 static_cast<unsigned long long>(g_frame), frame_ms,
                 static_cast<double>(gpu_wait_us) / 1000.0, draws, resolves, textures.count,
                 textures.command_ms + textures.background_ms, shaders.count, shaders.command_ms,
                 shaders.background_ms, pipelines.count, pipelines.command_ms,
                 pipelines.background_ms, phase_ms(Work::kDraw), phase_ms(Work::kResolve),
                 phase_ms(Work::kSwap), phase_ms(Work::kSubmission),
                 phase_ms(Work::kDrawSetup), phase_ms(Work::kDrawPrimitives),
                 phase_ms(Work::kDrawRenderTargets), phase_ms(Work::kDrawPipeline),
                 phase_ms(Work::kDrawTextures), phase_ms(Work::kDrawState),
                 phase_ms(Work::kDrawBindings), phase_ms(Work::kDrawVertices),
                 double(upload_bytes) / (1024.0 * 1024.0), phase_ms(Work::kMemoryUpload),
                 phase_ms(Work::kMemoryWatch));
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
