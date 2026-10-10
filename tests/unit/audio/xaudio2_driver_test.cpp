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
#include <rex/audio/audio_outputs.h>
#include <rex/audio/flags.h>
#include <rex/audio/nop/nop_audio_system.h>
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

constexpr int kSemaphoreMax = 256;

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

}

TEST_CASE("XAudio2 plays frames and releases the client once per frame", "[audio][xaudio2]") {
  Rig rig;
  if (!rig.driver.has_device()) {
    SKIP("No audio endpoint on this machine");
  }
  const uint32_t channels = rig.driver.output_channels();
  CHECK((channels == 2 || channels == 6));

  const auto start = Clock::now();
  rig.Submit(48);

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

  REQUIRE(rig.WaitReleased(40));
  CHECK(rig.driver.device_losses() == 1);

  REQUIRE(rig.WaitForDevice(true));
  rig.Submit(10);
  REQUIRE(rig.WaitReleased(50));
  std::this_thread::sleep_for(50ms);
  CHECK(rig.driver.frames_released() == 50);
  CHECK(rig.DrainSemaphore() == 50);
}

TEST_CASE("Windows lists its active audio outputs", "[audio][xaudio2]") {
  const auto outputs = rex::audio::ListAudioOutputs();
  if (outputs.empty()) {
    SKIP("No audio endpoint on this machine");
  }
  size_t defaults = 0;
  for (const auto& output : outputs) {
    INFO(output.id);
    CHECK_FALSE(output.id.empty());
    CHECK_FALSE(output.name.empty());
    CHECK(output.channels > 0);
    CHECK(output.sample_rate > 0);
    CHECK_FALSE(rex::audio::SpeakerLayoutName(output.channels, output.channel_mask).empty());
    defaults += output.is_default ? 1 : 0;
  }
  CHECK(defaults <= 1);
}

TEST_CASE("Speaker layouts are named from the channel mask, then the count", "[audio]") {
  using rex::audio::SpeakerLayoutName;
  CHECK(SpeakerLayoutName(2, 0x3) == "Stereo");
  CHECK(SpeakerLayoutName(6, 0x3F) == "5.1 surround");
  CHECK(SpeakerLayoutName(6, 0x60F) == "5.1 surround");
  CHECK(SpeakerLayoutName(8, 0x63F) == "7.1 surround");
  CHECK(SpeakerLayoutName(8, 0) == "7.1 surround");
  CHECK(SpeakerLayoutName(12, 0) == "12 channels");
  CHECK(SpeakerLayoutName(0, 0).empty());
}

TEST_CASE("XAudio2 moves to a chosen output and back to the default", "[audio][xaudio2]") {
  Rig rig;
  const auto outputs = rex::audio::ListAudioOutputs();
  if (!rig.driver.has_device() || outputs.empty()) {
    SKIP("No audio endpoint on this machine");
  }
  CHECK(rig.driver.opened_device().empty());
  auto reopened = [&](uint32_t opens) {
    const auto deadline = Clock::now() + 5s;
    while (rig.driver.engine_opens() <= opens || !rig.driver.has_device()) {
      if (Clock::now() > deadline) {
        return false;
      }
      std::this_thread::sleep_for(5ms);
    }
    return true;
  };

  rig.Submit(20);
  uint32_t opens = rig.driver.engine_opens();
  rig.driver.SetOutputDevice(outputs.back().id);
  REQUIRE(reopened(opens));
  CHECK(rig.driver.opened_device() == outputs.back().id);
  rig.Submit(10);
  REQUIRE(rig.WaitReleased(30));

  opens = rig.driver.engine_opens();
  rig.driver.SetOutputDevice("");
  REQUIRE(reopened(opens));
  CHECK(rig.driver.opened_device().empty());
  std::this_thread::sleep_for(50ms);
  CHECK(rig.driver.frames_released() == 30);
  CHECK(rig.DrainSemaphore() == 30);
  CHECK(rig.driver.device_losses() == 0);
}

TEST_CASE("XAudio2 plays through the default when the chosen output is gone", "[audio][xaudio2]") {
  XAudio2AudioDriver::Options options;
  options.output_device = "{0.0.0.00000000}.{00000000-0000-0000-0000-000000000000}";
  Rig rig(options);
  if (!rig.driver.has_device()) {
    SKIP("No audio endpoint on this machine");
  }
  CHECK(rig.driver.opened_device().empty());
  rig.Submit(8);
  REQUIRE(rig.WaitReleased(8));
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
    rig.driver.Shutdown();
  }

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

  CHECK(REXCVAR_GET(audio_backend) == "xaudio2");
  const std::string saved = REXCVAR_GET(audio_backend);
  REXCVAR_SET(audio_backend, std::string("nop"));
  CHECK(dynamic_cast<rex::audio::nop::NopAudioSystem*>(
      rex::audio::CreateDefaultAudioSystem(&dispatcher).get()));

  REXCVAR_SET(audio_backend, std::string("sdl"));
  CHECK(dynamic_cast<rex::audio::xaudio2::XAudio2AudioSystem*>(
      rex::audio::CreateDefaultAudioSystem(&dispatcher).get()));
  REXCVAR_SET(audio_backend, std::string("xaudio2"));
  auto audio = rex::audio::CreateDefaultAudioSystem(&dispatcher);
  REXCVAR_SET(audio_backend, saved);
  auto* xaudio2_system = dynamic_cast<rex::audio::xaudio2::XAudio2AudioSystem*>(audio.get());
  REQUIRE(xaudio2_system);

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
