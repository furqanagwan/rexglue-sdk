/**
 * @file        audio/downmix.cpp
 * @brief       Output-stage mix parameters: 5.1 fold, 5.1 matrix and master gain
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#include <algorithm>
#include <atomic>
#include <mutex>

#include <rex/audio/downmix.h>
#include <rex/audio/flags.h>

namespace rex::audio {
namespace {

// One output device exists, so the mix parameters are process state. The
// reader is the SDL device callback, which runs every 5.33 ms, so a plain
// mutex costs nothing and avoids a torn read across the four weights.
std::mutex g_mutex;
StereoFold g_fold = {};
SurroundMix g_mix = {};
float g_gain = 1.0f;

}  // namespace

void SetStereoFold(const StereoFold& fold) {
  std::lock_guard<std::mutex> lock(g_mutex);
  g_fold = fold;
}

StereoFold GetStereoFold() {
  std::lock_guard<std::mutex> lock(g_mutex);
  return g_fold;
}

void SetSurroundMix(const SurroundMix& mix) {
  std::lock_guard<std::mutex> lock(g_mutex);
  g_mix = mix;
}

SurroundMix GetSurroundMix() {
  std::lock_guard<std::mutex> lock(g_mutex);
  return g_mix;
}

void SetOutputGain(float linear) {
  std::lock_guard<std::mutex> lock(g_mutex);
  g_gain = linear;
}

float GetOutputGain() {
  std::lock_guard<std::mutex> lock(g_mutex);
  return g_gain;
}

float MasterOutputGain() {
  const int32_t volume = std::clamp<int32_t>(REXCVAR_GET(audio_volume), 0, 100);
  return GetOutputGain() * (float(volume) / 100.0f);
}

namespace {
std::atomic<bool> g_constrained = false;
}  // namespace

void SetAppConstrained(bool constrained) {
  g_constrained.store(constrained, std::memory_order_relaxed);
}

bool AppConstrained() {
  return g_constrained.load(std::memory_order_relaxed);
}

bool OutputSilenced() {
  return REXCVAR_GET(audio_mute) || (AppConstrained() && REXCVAR_GET(audio_mute_minimized));
}

}  // namespace rex::audio
