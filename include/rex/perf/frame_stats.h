/**
 * @file        perf/frame_stats.h
 * @brief       Per-frame timing log for automated performance runs
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once

#include <cstdint>
#include <cstddef>

namespace rex::perf::frame_stats {

// Unlike the perf counter registry, these are compiled into release builds:
// they cost two atomic increments per draw and nothing else unless the
// frame_stats_csv cvar names a file. Each guest frame (VdSwap) then appends
//   frame,frame_ms,gpu_wait_ms,draws,resolves
// (a resolve is issued as a draw, so draws include resolves). gpu_wait_ms is
// the time the GPU command thread spent waiting for the guest: a frame with
// little wait was limited by emulating the GPU, one with a lot by the guest.
// and shutdown logs a one-line summary (average and 1% low frame rate).

void RecordDraw();
void RecordResolve();
// Time the GPU command thread spent blocked waiting for guest commands.
void RecordGpuWait(uint64_t microseconds);
// Bytes of guest memory uploaded to the GPU.
void RecordUpload(uint64_t bytes);
// True when a CSV path was supplied. GPU backends use this to avoid allocating
// timestamp resources or recording queries during ordinary runs.
bool IsEnabled();

// Publishes asynchronously resolved GPU stage durations. The frame number is
// included in the CSV because these values normally become readable several
// frames after the CPU counters for the same frame were written.
inline constexpr size_t kGpuStageCount = 11;
void RecordGpuStages(uint64_t frame, const double (&milliseconds)[kGpuStageCount]);
// Called once per guest swap, before the frame is issued.
void RecordFrame();

// GPU emulation work that can make a frame late, timed wherever it runs. Work
// on the GPU command thread holds up the frame; the same work on a background
// thread (asynchronous shader and pipeline creation) does not, so the CSV
// keeps the two apart:
//   textures,texture_ms,shaders,shader_ms,shader_bg_ms,pipelines,pipeline_ms,pipeline_bg_ms,
//   draw_ms,resolve_ms,swap_ms,submit_ms,
//   draw_setup_ms,draw_primitives_ms,draw_render_targets_ms,draw_pipeline_ms,
//   draw_textures_ms,draw_state_ms,draw_bindings_ms,draw_vertices_ms,
//   upload_mb,upload_ms,watch_ms
// draw_ms through submit_ms are the command thread's own phases. They nest (a
// draw or a swap can end a submission, a draw can load a texture), so they do
// not sum to the frame. The draw_* columns split draw_ms into its stages, in
// order, and do sum to it. upload_ms is guest memory copied to the GPU's
// shared memory buffer (upload_mb of it), watch_ms the page protection that
// re-arms the write watch on it; both happen inside draws.
enum class Work : uint8_t {
  kTextureLoad,
  kShaderTranslation,
  kPipelineCreation,
  kDraw,
  kResolve,
  kSwap,
  kSubmission,
  kDrawSetup,          // shader analysis, beginning the submission
  kDrawPrimitives,     // index and primitive processing
  kDrawRenderTargets,  // render target cache update
  kDrawPipeline,       // pipeline description and lookup
  kDrawTextures,       // texture requests
  kDrawState,          // viewport, scissor and system constants
  kDrawBindings,       // constant buffers, descriptors, root parameters
  kDrawVertices,       // vertex and memexport data, then the draw call
  kMemoryUpload,       // guest memory copied to the shared memory buffer
  kMemoryWatch,        // write watches re-armed on uploaded memory
  kCount,
};

// Marks the calling thread as the GPU command thread.
void MarkCommandThread();

// Times one piece of work from construction to destruction. Costs a clock
// read at each end whether or not frame_stats_csv is set.
class ScopedWork {
 public:
  explicit ScopedWork(Work work);
  ~ScopedWork();
  ScopedWork(const ScopedWork&) = delete;
  ScopedWork& operator=(const ScopedWork&) = delete;

 private:
  Work work_;
  uint64_t start_us_;
};

// Times consecutive stages of one piece of work: each Mark ends the stage in
// progress and credits it with the time since the previous mark. Whatever runs
// after the last mark, to any return, goes to the final stage.
class StageTimer {
 public:
  explicit StageTimer(Work final_stage);
  ~StageTimer();
  StageTimer(const StageTimer&) = delete;
  StageTimer& operator=(const StageTimer&) = delete;

  void Mark(Work finished_stage);

 private:
  Work final_stage_;
  uint64_t last_us_;
};
// Writes the summary and closes the file.
void Shutdown();

}  // namespace rex::perf::frame_stats
