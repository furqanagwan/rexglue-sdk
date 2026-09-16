/**
 * @file        rex/audio/ui_sound.h
 * @brief       Short host-side interface sounds, decoded from console audio files
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <span>
#include <vector>

namespace rex::audio {

// Interleaved 32-bit float samples.
struct PcmSound {
  uint32_t sample_rate = 0;
  uint16_t channels = 0;
  std::vector<float> samples;
};

// Decodes a console audio file: a RIFF WAVE holding XMA1 or XMA2, as the
// dashboard's XUI packages carry for button and notification sounds. Returns
// nothing for anything else, or data that does not decode.
std::optional<PcmSound> DecodeXmaFile(std::span<const uint8_t> file);

// Plays interface sounds on the default output device, separately from the
// title's own audio, so a menu drawn over a game can click and chime without
// going through the emulated audio hardware. Overlapping sounds mix.
//
// Where the platform has no host audio output (UWP) playing is a no-op.
class UiSoundPlayer {
 public:
  UiSoundPlayer();
  ~UiSoundPlayer();
  UiSoundPlayer(const UiSoundPlayer&) = delete;
  UiSoundPlayer& operator=(const UiSoundPlayer&) = delete;

  // Queues the sound to start now; volume scales it, 0 to 1.
  void Play(const PcmSound& sound, float volume = 1.0f);

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace rex::audio
