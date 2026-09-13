/**
 * @file        audio/xaudio2/xaudio2_audio_driver.h
 * @brief       XAudio2 output driver for Universal Windows Platform builds
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include <rex/audio/audio_driver.h>
#include <rex/thread.h>

struct IXAudio2;
struct IXAudio2MasteringVoice;
struct IXAudio2SourceVoice;

namespace rex::audio::xaudio2 {

class XAudio2AudioDriver : public AudioDriver {
 public:
  XAudio2AudioDriver(memory::Memory* memory, rex::thread::Semaphore* semaphore);
  ~XAudio2AudioDriver() override;

  bool Initialize();
  void SubmitFrame(uint32_t frame_ptr) override;
  void Shutdown();

 private:
  class VoiceCallback;

  float* AcquireBuffer();
  void ReleaseBuffer(float* buffer);
  void OnBufferPlayed(float* buffer);

  static constexpr uint32_t kFrameFrequency = 48000;
  static constexpr uint32_t kGuestChannels = 6;
  static constexpr uint32_t kChannelSamples = 256;
  static constexpr uint32_t kGuestFrameSamples = kGuestChannels * kChannelSamples;

  rex::thread::Semaphore* semaphore_ = nullptr;
  std::unique_ptr<VoiceCallback> voice_callback_;
  IXAudio2* xaudio2_ = nullptr;
  IXAudio2MasteringVoice* mastering_voice_ = nullptr;
  IXAudio2SourceVoice* source_voice_ = nullptr;
  uint32_t output_channels_ = 2;

  std::mutex buffers_mutex_;
  std::vector<float*> unused_buffers_;
};

}  // namespace rex::audio::xaudio2
