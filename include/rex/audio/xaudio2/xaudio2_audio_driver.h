/**
 * @file        audio/xaudio2/xaudio2_audio_driver.h
 * @brief       XAudio2 2.9 output for one guest audio client (RG-GDK-019)
 *
 * Structure follows Xenia's XAudio2 driver (xenia-edge src/xenia/apu/xaudio2,
 * last changed 71dcd5004): a COM MTA thread owns the engine, the source voice
 * takes one buffer per guest frame and OnBufferEnd paces the guest. Added here:
 * the Windows SDK's XAudio2 2.9 instead of hand-declared 2.7/2.8 interfaces,
 * and device loss handling. Every submitted frame releases the client
 * semaphore exactly once, played by the device or, with no usable device,
 * released on a wall clock at the frame rate, so a title never waits on audio
 * hardware that went away. The service thread recreates the engine when a
 * device returns.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <rex/audio/audio_driver.h>
#include <rex/thread.h>

struct IXAudio2;
struct IXAudio2MasteringVoice;
struct IXAudio2SourceVoice;

namespace rex::audio::xaudio2 {

class XAudio2AudioDriver : public AudioDriver {
 public:
  static constexpr uint32_t kFrameFrequency = 48000;
  static constexpr uint32_t kFrameChannels = 6;
  static constexpr uint32_t kChannelSamples = 256;
  static constexpr uint32_t kFrameSamples = kFrameChannels * kChannelSamples;

  static constexpr uint32_t kFrameSlots = 64;
  static constexpr std::chrono::nanoseconds kFramePeriod{
      std::chrono::nanoseconds(std::chrono::seconds(1)) * kChannelSamples / kFrameFrequency};

  struct Options {
    bool simulate_no_device = false;

    std::chrono::milliseconds retry_interval{2000};

    std::chrono::milliseconds stall_timeout{1000};

    std::string output_device;
  };

  XAudio2AudioDriver(memory::Memory* memory, rex::thread::Semaphore* semaphore);
  XAudio2AudioDriver(memory::Memory* memory, rex::thread::Semaphore* semaphore, Options options);
  ~XAudio2AudioDriver() override;

  bool Initialize();
  void SubmitFrame(uint32_t frame_ptr) override;

  void SubmitGuestFrame(const float* frame);

  void Shutdown();

  bool has_device() const;

  uint32_t output_channels() const;

  void SetOutputDevice(std::string device_id);

  std::string opened_device() const;

  uint32_t engine_opens() const { return engine_opens_.load(); }

  uint32_t device_losses() const { return device_losses_.load(); }

  uint64_t frames_released() const { return frames_released_.load(); }

  void SimulateDeviceLoss();
  void SetSimulateNoDevice(bool no_device);

  void SimulateStall();

 private:
  class EngineCallback;
  class VoiceCallback;

  enum class SlotState : uint8_t { kFree, kFilling, kEngine, kPaced };
  struct Slot {
    std::array<float, kFrameSamples> samples;
    SlotState state = SlotState::kFree;
    uint32_t generation = 0;
  };
  using Clock = std::chrono::steady_clock;

  void ServiceThread();
  bool CreateEngine();
  void DestroyEngine();
  void OnBufferEnd(uint32_t slot, uint32_t generation);
  void OnCriticalError(long hr);

  void PaceLocked(uint32_t slot, Clock::time_point now);
  void ReleaseSlotLocked(uint32_t slot);

  void MarkEngineLostLocked(const char* reason);

  rex::thread::Semaphore* semaphore_;
  Options options_;

  mutable std::mutex mutex_;
  std::condition_variable wake_;
  std::array<Slot, kFrameSlots> slots_;
  std::vector<uint32_t> free_slots_;
  std::deque<std::pair<uint32_t, Clock::time_point>> paced_;
  Clock::time_point last_paced_deadline_{};
  uint32_t engine_frames_ = 0;
  Clock::time_point engine_progress_{};
  bool engine_live_ = false;
  bool engine_lost_ = false;
  uint32_t generation_ = 0;
  uint32_t output_channels_ = 2;
  bool shutdown_requested_ = false;
  bool simulate_no_device_ = false;
  std::string output_device_;
  std::string opened_device_;
  bool device_switch_requested_ = false;

  IXAudio2* xaudio2_ = nullptr;
  IXAudio2MasteringVoice* mastering_voice_ = nullptr;
  IXAudio2SourceVoice* source_voice_ = nullptr;
  EngineCallback* engine_callback_ = nullptr;
  VoiceCallback* voice_callback_ = nullptr;

  std::thread service_thread_;
  bool service_started_ = false;
  bool service_ok_ = false;
  bool create_failure_logged_ = false;

  std::atomic<uint32_t> device_losses_ = 0;
  std::atomic<uint32_t> engine_opens_ = 0;
  std::atomic<uint64_t> frames_released_ = 0;
};

}
