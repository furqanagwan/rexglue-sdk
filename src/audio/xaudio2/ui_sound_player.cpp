/**
 * @file        audio/xaudio2/ui_sound_player.cpp
 * @brief       UI sounds on their own XAudio2 engine (RG-GDK-041)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/audio/ui_sound.h>

#include <mutex>
#include <vector>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <xaudio2.h>

#include <rex/logging.h>

namespace rex::audio {
namespace {

// Enough for a guide's overlapping focus, select and blade sounds.
constexpr size_t kMaxVoices = 16;

class XAudio2UiSoundPlayer final : public UiSoundPlayer {
 public:
  XAudio2UiSoundPlayer(IXAudio2* xaudio2, IXAudio2MasteringVoice* mastering)
      : xaudio2_(xaudio2), mastering_(mastering) {}

  ~XAudio2UiSoundPlayer() override {
    std::lock_guard<std::mutex> lock(mutex_);
    for (Active& active : active_) {
      active.voice->DestroyVoice();
    }
    active_.clear();
    mastering_->DestroyVoice();
    xaudio2_->Release();
  }

  void Play(std::shared_ptr<const PcmSound> sound, float volume) override {
    if (!sound || sound->samples.empty()) {
      return;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    ReapFinished();
    if (active_.size() >= kMaxVoices) {
      active_.front().voice->DestroyVoice();
      active_.erase(active_.begin());
    }
    WAVEFORMATEX format = {};
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = WORD(sound->channels);
    format.nSamplesPerSec = sound->sample_rate;
    format.wBitsPerSample = 16;
    format.nBlockAlign = WORD(sound->channels * sizeof(int16_t));
    format.nAvgBytesPerSec = sound->sample_rate * format.nBlockAlign;
    IXAudio2SourceVoice* voice = nullptr;
    if (FAILED(xaudio2_->CreateSourceVoice(&voice, &format))) {
      return;
    }
    XAUDIO2_BUFFER buffer = {};
    buffer.AudioBytes = UINT32(sound->samples.size() * sizeof(int16_t));
    buffer.pAudioData = reinterpret_cast<const BYTE*>(sound->samples.data());
    buffer.Flags = XAUDIO2_END_OF_STREAM;
    if (FAILED(voice->SubmitSourceBuffer(&buffer)) || FAILED(voice->SetVolume(volume)) ||
        FAILED(voice->Start())) {
      voice->DestroyVoice();
      return;
    }
    active_.push_back({voice, std::move(sound)});
  }

 private:
  struct Active {
    IXAudio2SourceVoice* voice;
    std::shared_ptr<const PcmSound> sound;  // the voice reads these samples
  };

  void ReapFinished() {
    for (size_t i = 0; i < active_.size();) {
      XAUDIO2_VOICE_STATE state = {};
      active_[i].voice->GetState(&state, XAUDIO2_VOICE_NOSAMPLESPLAYED);
      if (state.BuffersQueued == 0) {
        active_[i].voice->DestroyVoice();
        active_.erase(active_.begin() + ptrdiff_t(i));
      } else {
        ++i;
      }
    }
  }

  IXAudio2* xaudio2_;
  IXAudio2MasteringVoice* mastering_;
  std::mutex mutex_;
  std::vector<Active> active_;
};

}  // namespace

std::unique_ptr<UiSoundPlayer> UiSoundPlayer::Create() {
  IXAudio2* xaudio2 = nullptr;
  if (FAILED(XAudio2Create(&xaudio2, 0, XAUDIO2_DEFAULT_PROCESSOR))) {
    REXAPU_WARN("UI sounds: XAudio2 is not available");
    return nullptr;
  }
  IXAudio2MasteringVoice* mastering = nullptr;
  if (FAILED(xaudio2->CreateMasteringVoice(&mastering))) {
    REXAPU_WARN("UI sounds: no audio output device");
    xaudio2->Release();
    return nullptr;
  }
  return std::make_unique<XAudio2UiSoundPlayer>(xaudio2, mastering);
}

}  // namespace rex::audio
