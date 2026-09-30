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
  std::vector<int16_t> samples;  // interleaved
};

/// Decodes a single-stream RIFF XMA file (XMA1 format tag 0x165 or XMA2
/// 0x166), as the dashboard's UI sounds are, frame by frame through the
/// SDK's XMA frame decoder.
std::optional<PcmSound> DecodeXmaFile(std::span<const uint8_t> riff, std::string* error);

/// Plays UI sounds on their own XAudio2 engine, so they are heard whatever
/// the guest's audio is doing.
class UiSoundPlayer {
 public:
  /// Null when XAudio2 or an output device is unavailable.
  static std::unique_ptr<UiSoundPlayer> Create();
  virtual ~UiSoundPlayer() = default;
  virtual void Play(std::shared_ptr<const PcmSound> sound, float volume = 1.0f) = 0;
};

}  // namespace rex::audio
