/**
 * @file        audio/audio_outputs.h
 * @brief       The Windows audio outputs a player can choose to play the game through
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace rex::audio {

enum class Support { kUnknown, kNo, kYes };

struct AudioFormats {
  Support dolby_digital = Support::kUnknown;
  Support dolby_digital_plus = Support::kUnknown;
  Support dolby_truehd = Support::kUnknown;
  Support dts = Support::kUnknown;
  Support dts_hd = Support::kUnknown;
};

struct AudioOutput {
  std::string id;
  std::string name;
  bool is_default = false;
  uint32_t channels = 0;
  uint32_t channel_mask = 0;
  uint32_t sample_rate = 0;
  uint32_t bits_per_sample = 0;
  AudioFormats formats;
  bool spatial_sound = false;
};

std::vector<AudioOutput> ListAudioOutputs();

std::string SpeakerLayoutName(uint32_t channels, uint32_t channel_mask);

}
