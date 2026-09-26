/**
 * @file        audio/xaudio2/xaudio2_audio_system.cpp
 * @brief       Audio system with XAudio2 output (RG-GDK-019)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/audio/xaudio2/xaudio2_audio_system.h>

#include <rex/assert.h>
#include <rex/audio/xaudio2/xaudio2_audio_driver.h>

namespace rex::audio::xaudio2 {

std::unique_ptr<AudioSystem> XAudio2AudioSystem::Create(
    runtime::FunctionDispatcher* function_dispatcher) {
  return std::make_unique<XAudio2AudioSystem>(function_dispatcher);
}

XAudio2AudioSystem::XAudio2AudioSystem(runtime::FunctionDispatcher* function_dispatcher)
    : AudioSystem(function_dispatcher) {}

XAudio2AudioSystem::~XAudio2AudioSystem() = default;

X_STATUS XAudio2AudioSystem::CreateDriver([[maybe_unused]] size_t index,
                                          rex::thread::Semaphore* semaphore,
                                          AudioDriver** out_driver) {
  assert_not_null(out_driver);
  auto driver = new XAudio2AudioDriver(memory_, semaphore);
  if (!driver->Initialize()) {
    driver->Shutdown();
    delete driver;
    return X_STATUS_UNSUCCESSFUL;
  }
  *out_driver = driver;
  return X_STATUS_SUCCESS;
}

void XAudio2AudioSystem::DestroyDriver(AudioDriver* driver) {
  assert_not_null(driver);
  auto xaudio2_driver = static_cast<XAudio2AudioDriver*>(driver);
  xaudio2_driver->Shutdown();
  delete xaudio2_driver;
}

}  // namespace rex::audio::xaudio2
