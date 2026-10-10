/**
 * @file        audio/xaudio2/xaudio2_audio_system.h
 * @brief       Audio system with XAudio2 output (RG-GDK-019)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <mutex>
#include <string>
#include <vector>

#include <rex/audio/audio_system.h>

namespace rex::audio::xaudio2 {

class XAudio2AudioDriver;

class XAudio2AudioSystem : public AudioSystem {
 public:
  explicit XAudio2AudioSystem(runtime::FunctionDispatcher* function_dispatcher);
  ~XAudio2AudioSystem() override;

  static std::unique_ptr<AudioSystem> Create(runtime::FunctionDispatcher* function_dispatcher);

  X_STATUS CreateDriver(size_t index, rex::thread::Semaphore* semaphore,
                        AudioDriver** out_driver) override;
  void DestroyDriver(AudioDriver* driver) override;

 private:
  void SetOutputDevice(std::string device_id);

  std::mutex drivers_mutex_;
  std::vector<XAudio2AudioDriver*> drivers_;
  std::string output_device_;
};

}  // namespace rex::audio::xaudio2
