/**
 * @file        audio/sdl/ui_sound_player.cpp
 * @brief       Plays interface sounds through SDL, beside the title's audio
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <rex/audio/ui_sound.h>

#include <array>
#include <mutex>

#include <rex/logging.h>

#include <SDL3/SDL.h>

namespace rex::audio {

namespace {

// Enough for a highlight click over a tab sound over a notification chime.
constexpr size_t kVoices = 4;

}  // namespace

struct UiSoundPlayer::Impl {
  struct Voice {
    SDL_AudioStream* stream = nullptr;
    uint32_t sample_rate = 0;
    uint16_t channels = 0;
  };

  bool audio_ready = false;
  std::mutex mutex;
  std::array<Voice, kVoices> voices{};
  size_t next_voice = 0;
};

UiSoundPlayer::UiSoundPlayer() : impl_(std::make_unique<Impl>()) {
  // Counted by SDL, so this sits alongside the title's own audio driver.
  impl_->audio_ready = SDL_InitSubSystem(SDL_INIT_AUDIO);
  if (!impl_->audio_ready) {
    REXAPU_WARN("UI sound: no audio output ({})", SDL_GetError());
  }
}

UiSoundPlayer::~UiSoundPlayer() {
  for (auto& voice : impl_->voices) {
    if (voice.stream) {
      SDL_DestroyAudioStream(voice.stream);
    }
  }
  if (impl_->audio_ready) {
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
  }
}

void UiSoundPlayer::Play(const PcmSound& sound, float volume) {
  if (!impl_->audio_ready || sound.samples.empty() || sound.channels == 0) {
    return;
  }
  std::lock_guard lock(impl_->mutex);

  // A voice that has finished, else the one started longest ago.
  Impl::Voice* voice = nullptr;
  for (auto& candidate : impl_->voices) {
    if (!candidate.stream || SDL_GetAudioStreamQueued(candidate.stream) == 0) {
      voice = &candidate;
      break;
    }
  }
  if (!voice) {
    voice = &impl_->voices[impl_->next_voice];
    impl_->next_voice = (impl_->next_voice + 1) % kVoices;
  }

  if (voice->stream &&
      (voice->sample_rate != sound.sample_rate || voice->channels != sound.channels)) {
    SDL_DestroyAudioStream(voice->stream);
    voice->stream = nullptr;
  }
  if (!voice->stream) {
    const SDL_AudioSpec spec{SDL_AUDIO_F32, int(sound.channels), int(sound.sample_rate)};
    voice->stream =
        SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);
    if (!voice->stream) {
      REXAPU_WARN("UI sound: could not open an output stream ({})", SDL_GetError());
      return;
    }
    voice->sample_rate = sound.sample_rate;
    voice->channels = sound.channels;
    SDL_ResumeAudioStreamDevice(voice->stream);
  }

  SDL_ClearAudioStream(voice->stream);
  SDL_SetAudioStreamGain(voice->stream, volume);
  SDL_PutAudioStreamData(voice->stream, sound.samples.data(),
                         int(sound.samples.size() * sizeof(float)));
}

}  // namespace rex::audio
