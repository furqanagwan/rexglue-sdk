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
  // Guest frames: 6 channels (fl fr fc lf bl br) of 256 big-endian float
  // samples each, one channel after another, at 48 kHz.
  static constexpr uint32_t kFrameFrequency = 48000;
  static constexpr uint32_t kFrameChannels = 6;
  static constexpr uint32_t kChannelSamples = 256;
  static constexpr uint32_t kFrameSamples = kFrameChannels * kChannelSamples;
  // AudioSystem queues at most this many frames per client.
  static constexpr uint32_t kFrameSlots = 64;
  static constexpr std::chrono::nanoseconds kFramePeriod{
      std::chrono::nanoseconds(std::chrono::seconds(1)) * kChannelSamples / kFrameFrequency};

  struct Options {
    // Every engine creation fails, as on a machine with no audio endpoint.
    bool simulate_no_device = false;
    // How often to try again for a device while there is none.
    std::chrono::milliseconds retry_interval{2000};
    // Buffers queued with no OnBufferEnd for this long mean the device is gone
    // even if XAudio2 never reported it.
    std::chrono::milliseconds stall_timeout{1000};
  };

  XAudio2AudioDriver(memory::Memory* memory, rex::thread::Semaphore* semaphore);
  XAudio2AudioDriver(memory::Memory* memory, rex::thread::Semaphore* semaphore, Options options);
  ~XAudio2AudioDriver() override;

  // Starts the service thread and tries for a device. Succeeds without one
  // (frames are then paced by the clock); fails only if COM cannot start.
  bool Initialize();
  void SubmitFrame(uint32_t frame_ptr) override;
  // SubmitFrame on a host pointer to a guest-format frame.
  void SubmitGuestFrame(const float* frame);
  // Stops the service thread and releases the engine. Frames still queued are
  // not released: the client is going away.
  void Shutdown();

  // A device is open and taking frames.
  bool has_device() const;
  // Channels submitted to the device: 2 (stereo fold) or 6 (5.1).
  uint32_t output_channels() const;
  // Device losses handled so far (critical errors and stalls).
  uint32_t device_losses() const { return device_losses_.load(); }
  // Semaphore releases so far.
  uint64_t frames_released() const { return frames_released_.load(); }

  // Test hooks: take the device-loss path as if XAudio2 reported a critical
  // error, and switch simulated device absence on or off.
  void SimulateDeviceLoss();
  void SetSimulateNoDevice(bool no_device);
  // Stops the source voice without telling the driver, so buffers stop
  // finishing and only the stall watchdog notices.
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
  // With mutex_ held.
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

  // Owned by the service thread; used by SubmitGuestFrame only while
  // engine_live_ is set, under mutex_.
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
  std::atomic<uint64_t> frames_released_ = 0;
};

}  // namespace rex::audio::xaudio2
