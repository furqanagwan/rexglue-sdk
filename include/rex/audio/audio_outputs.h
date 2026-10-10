/**
 * @file        audio/audio_outputs.h
 * @brief       The Windows audio outputs a player can choose to play the game through
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <string>
#include <vector>

namespace rex::audio {

struct AudioOutput {
  std::string id;
  std::string name;
  bool is_default = false;
};

std::vector<AudioOutput> ListAudioOutputs();

}  // namespace rex::audio
