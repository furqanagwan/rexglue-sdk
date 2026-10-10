/**
 * @file        audio/downmix.h
 * @brief       Output-stage mix parameters: 5.1 fold, 5.1 matrix and master gain
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once

namespace rex::audio {

struct StereoFold {
  float center = 0.70710678f;
  float surround = 0.70710678f;
  float lfe = 0.0f;
  float scale = 0.58578644f;
};

struct SurroundMix {
  float center = 1.0f;
  float surround = 1.0f;
  float lfe = 1.0f;
};

void SetStereoFold(const StereoFold& fold);
StereoFold GetStereoFold();

void SetSurroundMix(const SurroundMix& mix);
SurroundMix GetSurroundMix();

void SetOutputGain(float linear);
float GetOutputGain();

float MasterOutputGain();

void SetAppConstrained(bool constrained);
bool AppConstrained();

bool OutputSilenced();

}
