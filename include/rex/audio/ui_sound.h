/**
 * @file        rex/audio/ui_sound.h
 * @brief       Host UI sounds: XMA files decoded to PCM, played apart from the guest (RG-GDK-041)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace rex::audio {

struct PcmSound {
  uint32_t sample_rate = 0;
  uint32_t channels = 0;
  std::vector<int16_t> samples;
};

std::optional<PcmSound> DecodeXmaFile(std::span<const uint8_t> riff, std::string* error);

class UiSoundPlayer {
 public:
  static std::unique_ptr<UiSoundPlayer> Create();
  virtual ~UiSoundPlayer() = default;
  virtual void Play(std::shared_ptr<const PcmSound> sound, float volume = 1.0f) = 0;
};

}
