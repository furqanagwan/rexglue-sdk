/**
 * @file        audio/xaudio2/xaudio2_audio_system.cpp
 * @brief       Audio system with XAudio2 output (RG-GDK-019)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/audio/xaudio2/xaudio2_audio_system.h>

#include <algorithm>

#include <rex/assert.h>
#include <rex/audio/flags.h>
#include <rex/audio/xaudio2/xaudio2_audio_driver.h>
#include <rex/cvar.h>

namespace rex::audio::xaudio2 {

namespace {

constexpr std::string_view kOutputDeviceFlag = "audio_output_device";

}  // namespace

std::unique_ptr<AudioSystem> XAudio2AudioSystem::Create(
    runtime::FunctionDispatcher* function_dispatcher) {
  return std::make_unique<XAudio2AudioSystem>(function_dispatcher);
}

XAudio2AudioSystem::XAudio2AudioSystem(runtime::FunctionDispatcher* function_dispatcher)
    : AudioSystem(function_dispatcher), output_device_(REXCVAR_GET(audio_output_device)) {
  rex::cvar::RegisterChangeCallback(
      kOutputDeviceFlag,
      [this](std::string_view, std::string_view value) { SetOutputDevice(std::string(value)); });
}

XAudio2AudioSystem::~XAudio2AudioSystem() {
  rex::cvar::UnregisterChangeCallbacks(kOutputDeviceFlag);
}

void XAudio2AudioSystem::SetOutputDevice(std::string device_id) {
  std::lock_guard<std::mutex> lock(drivers_mutex_);
  output_device_ = std::move(device_id);
  for (XAudio2AudioDriver* driver : drivers_) {
    driver->SetOutputDevice(output_device_);
  }
}

X_STATUS XAudio2AudioSystem::CreateDriver([[maybe_unused]] size_t index,
                                          rex::thread::Semaphore* semaphore,
                                          AudioDriver** out_driver) {
  assert_not_null(out_driver);
  std::lock_guard<std::mutex> lock(drivers_mutex_);
  XAudio2AudioDriver::Options options;
  options.output_device = output_device_;
  auto driver = new XAudio2AudioDriver(memory_, semaphore, options);
  if (!driver->Initialize()) {
    driver->Shutdown();
    delete driver;
    return X_STATUS_UNSUCCESSFUL;
  }
  drivers_.push_back(driver);
  *out_driver = driver;
  return X_STATUS_SUCCESS;
}

void XAudio2AudioSystem::DestroyDriver(AudioDriver* driver) {
  assert_not_null(driver);
  auto xaudio2_driver = static_cast<XAudio2AudioDriver*>(driver);
  {
    std::lock_guard<std::mutex> lock(drivers_mutex_);
    drivers_.erase(std::remove(drivers_.begin(), drivers_.end(), xaudio2_driver), drivers_.end());
  }
  xaudio2_driver->Shutdown();
  delete xaudio2_driver;
}

}  // namespace rex::audio::xaudio2
