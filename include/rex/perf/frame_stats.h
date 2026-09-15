/**
 * @file        perf/frame_stats.h
 * @brief       Per-frame timing log for automated performance runs
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once

#include <cstdint>

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
// Called once per guest swap, before the frame is issued.
void RecordFrame();
// Writes the summary and closes the file.
void Shutdown();

}  // namespace rex::perf::frame_stats
