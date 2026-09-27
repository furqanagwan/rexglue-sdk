/**
 * @file        xaudio2_driver_test.cpp
 * @brief       XAudio2 output pacing, device loss and teardown (RG-GDK-019)
 *
 * Runs against the machine's real XAudio2 and default endpoint. Cases that need
 * a device skip when there is none; the no-device cases simulate absence.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <chrono>
#include <cstring>
#include <string>
#include <memory>
#include <thread>
#include <vector>

#include <rex/audio/audio_backend.h>
#include <rex/audio/flags.h>
#include <rex/audio/nop/nop_audio_system.h>
#include <rex/audio/sdl/sdl_audio_system.h>
#include <rex/audio/xaudio2/xaudio2_audio_driver.h>
#include <rex/audio/xaudio2/xaudio2_audio_system.h>
#include <rex/cvar.h>
#include <rex/system/export_resolver.h>
#include <rex/system/function_dispatcher.h>
#include <rex/thread.h>

#include "test_memory.h"

using namespace std::chrono_literals;
using rex::X_STATUS;
using rex::audio::xaudio2::XAudio2AudioDriver;
using rex::testing::GetTestMemory;
using Clock = std::chrono::steady_clock;

namespace {

// Room for more releases than AudioSystem's 64 so over-release would show.
constexpr int kSemaphoreMax = 256;

// Heap-allocated: a driver's frame slots are too large for the test stack.
struct Rig {
  explicit Rig(XAudio2AudioDriver::Options options = {})
      : semaphore(rex::thread::Semaphore::Create(0, kSemaphoreMax)),
        owned(std::make_unique<XAudio2AudioDriver>(&GetTestMemory(), semaphore.get(), options)),
        driver(*owned) {
    REQUIRE(driver.Initialize());
  }

  void Submit(int count) {
    for (int i = 0; i < count; ++i) {
      driver.SubmitGuestFrame(silence.data());
    }
  }

  // Waits until the driver has released `count` frames in total.
  bool WaitReleased(uint64_t count, std::chrono::milliseconds timeout = 5s) {
    const auto deadline = Clock::now() + timeout;
    while (driver.frames_released() < count) {
      if (Clock::now() > deadline) {
        return false;
      }
      std::this_thread::sleep_for(1ms);
    }
    return true;
  }

  // Takes every pending release off the semaphore.
  int DrainSemaphore() {
    int count = 0;
    while (rex::thread::Wait(semaphore.get(), false, 0ms) == rex::thread::WaitResult::kSuccess) {
      ++count;
    }
    return count;
  }

  bool WaitForDevice(bool present, std::chrono::milliseconds timeout = 5s) {
    const auto deadline = Clock::now() + timeout;
    while (driver.has_device() != present) {
      if (Clock::now() > deadline) {
        return false;
      }
      std::this_thread::sleep_for(5ms);
    }
    return true;
  }

  std::unique_ptr<rex::thread::Semaphore> semaphore;
  std::unique_ptr<XAudio2AudioDriver> owned;
  XAudio2AudioDriver& driver;
  std::vector<float> silence = std::vector<float>(XAudio2AudioDriver::kFrameSamples, 0.0f);
};

constexpr auto kFramePeriod = XAudio2AudioDriver::kFramePeriod;

}  // namespace

TEST_CASE("XAudio2 plays frames and releases the client once per frame", "[audio][xaudio2]") {
  Rig rig;
  if (!rig.driver.has_device()) {
    SKIP("No audio endpoint on this machine");
  }
  const uint32_t channels = rig.driver.output_channels();
  CHECK((channels == 2 || channels == 6));

  const auto start = Clock::now();
  rig.Submit(48);
  // Playback paces the releases: they arrive over the frames' duration, not
  // at submission.
  CHECK(rig.driver.frames_released() < 48);
  REQUIRE(rig.WaitReleased(48));
  const auto elapsed = Clock::now() - start;
  CHECK(elapsed >= 48 * kFramePeriod / 2);
  std::this_thread::sleep_for(50ms);
  CHECK(rig.driver.frames_released() == 48);
  CHECK(rig.DrainSemaphore() == 48);
  CHECK(rig.driver.device_losses() == 0);
}

TEST_CASE("XAudio2 without a device releases frames on the clock", "[audio][xaudio2]") {
  XAudio2AudioDriver::Options options;
  options.simulate_no_device = true;
  Rig rig(options);
  CHECK_FALSE(rig.driver.has_device());

  const auto start = Clock::now();
  rig.Submit(64);
  REQUIRE(rig.WaitReleased(64));
  const auto elapsed = Clock::now() - start;
  // 64 frames of 5.33 ms: paced, not released at once, and not stalled.
  CHECK(elapsed >= 64 * kFramePeriod * 8 / 10);
  CHECK(elapsed < 64 * kFramePeriod * 4);
  std::this_thread::sleep_for(50ms);
  CHECK(rig.DrainSemaphore() == 64);
}

TEST_CASE("XAudio2 device loss releases queued frames and reopens the device", "[audio][xaudio2]") {
  Rig rig;
  if (!rig.driver.has_device()) {
    SKIP("No audio endpoint on this machine");
  }
  rig.Submit(40);
  std::this_thread::sleep_for(20ms);
  rig.driver.SimulateDeviceLoss();
  // Frames the dead voice held are released on the clock instead.
  REQUIRE(rig.WaitReleased(40));
  CHECK(rig.driver.device_losses() == 1);
  // The engine is recreated straight away on the default device.
  REQUIRE(rig.WaitForDevice(true));
  rig.Submit(10);
  REQUIRE(rig.WaitReleased(50));
  std::this_thread::sleep_for(50ms);
  CHECK(rig.driver.frames_released() == 50);
  CHECK(rig.DrainSemaphore() == 50);
}

TEST_CASE("XAudio2 stall watchdog frees frames a silent voice holds", "[audio][xaudio2]") {
  XAudio2AudioDriver::Options options;
  options.stall_timeout = 200ms;
  Rig rig(options);
  if (!rig.driver.has_device()) {
    SKIP("No audio endpoint on this machine");
  }
  rig.driver.SimulateStall();
  rig.Submit(20);
  REQUIRE(rig.WaitReleased(20, 3s));
  CHECK(rig.driver.device_losses() == 1);
  REQUIRE(rig.WaitForDevice(true));
  std::this_thread::sleep_for(50ms);
  CHECK(rig.DrainSemaphore() == 20);
}

TEST_CASE("XAudio2 picks up a device that appears later", "[audio][xaudio2]") {
  XAudio2AudioDriver::Options options;
  options.simulate_no_device = true;
  options.retry_interval = 100ms;
  Rig rig(options);
  CHECK_FALSE(rig.driver.has_device());
  rig.Submit(8);
  rig.driver.SetSimulateNoDevice(false);
  if (!rig.WaitForDevice(true, 3s)) {
    // Either no endpoint exists, or the retry did not happen.
    Rig probe;
    REQUIRE_FALSE(probe.driver.has_device());
    SKIP("No audio endpoint on this machine");
  }
  rig.Submit(8);
  REQUIRE(rig.WaitReleased(16));
  std::this_thread::sleep_for(50ms);
  CHECK(rig.DrainSemaphore() == 16);
}

TEST_CASE("XAudio2 keeps one release per frame past its slot count", "[audio][xaudio2]") {
  XAudio2AudioDriver::Options options;
  options.simulate_no_device = true;
  Rig rig(options);
  rig.Submit(XAudio2AudioDriver::kFrameSlots + 6);
  REQUIRE(rig.WaitReleased(XAudio2AudioDriver::kFrameSlots + 6));
  std::this_thread::sleep_for(50ms);
  CHECK(rig.DrainSemaphore() == int(XAudio2AudioDriver::kFrameSlots + 6));
}

TEST_CASE("XAudio2 drivers survive repeated create, submit and teardown", "[audio][xaudio2]") {
  for (int i = 0; i < 25; ++i) {
    Rig rig;
    rig.Submit(i % 7);
    if (i % 5 == 4) {
      rig.driver.SimulateDeviceLoss();
    }
    rig.driver.Shutdown();
    rig.driver.Shutdown();  // idempotent
  }
  // Two clients at once, as two guest render clients would have.
  Rig a;
  Rig b;
  a.Submit(10);
  b.Submit(10);
  REQUIRE(a.WaitReleased(10));
  REQUIRE(b.WaitReleased(10));
}

TEST_CASE("audio_backend selects the XAudio2 system and it serves a guest client",
          "[audio][xaudio2]") {
  auto& memory = GetTestMemory();
  rex::runtime::ExportResolver resolver;
  rex::runtime::FunctionDispatcher dispatcher(&memory, &resolver);

  REXCVAR_SET(audio_backend, std::string("nop"));
  CHECK(dynamic_cast<rex::audio::nop::NopAudioSystem*>(
      rex::audio::CreateDefaultAudioSystem(&dispatcher).get()));
  REXCVAR_SET(audio_backend, std::string("sdl"));
  CHECK(dynamic_cast<rex::audio::sdl::SDLAudioSystem*>(
      rex::audio::CreateDefaultAudioSystem(&dispatcher).get()));
  REXCVAR_SET(audio_backend, std::string("xaudio2"));
  auto audio = rex::audio::CreateDefaultAudioSystem(&dispatcher);
  REXCVAR_SET(audio_backend, std::string("sdl"));
  auto* xaudio2_system = dynamic_cast<rex::audio::xaudio2::XAudio2AudioSystem*>(audio.get());
  REQUIRE(xaudio2_system);

  // Register a client, submit a frame from guest memory, unregister: the
  // driver is created, takes the frame and is torn down with it in flight.
  size_t index = SIZE_MAX;
  REQUIRE(xaudio2_system->RegisterClient(0x82000000, 0, &index) == X_STATUS_SUCCESS);
  const uint32_t frame = memory.SystemHeapAlloc(XAudio2AudioDriver::kFrameSamples * 4);
  REQUIRE(frame);
  std::memset(memory.TranslateVirtual(frame), 0, XAudio2AudioDriver::kFrameSamples * 4);
  for (int i = 0; i < 4; ++i) {
    xaudio2_system->SubmitFrame(index, frame);
  }
  xaudio2_system->UnregisterClient(index);
  memory.SystemHeapFree(frame);
}
