/**
 * @file        audio_client_lifetime_test.cpp
 * @brief       Audio client callback vs. unregister/driver lifetime (RG-GDK-018)
 *
 * Drives AudioSystem's client dispatch directly, with a host function standing
 * in for the guest render callback, so the worker thread and kernel state are
 * not needed.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include <rex/audio/audio_driver.h>
#include <rex/audio/audio_system.h>
#include <rex/system/export_resolver.h>
#include <rex/system/function_dispatcher.h>

#include "test_memory.h"

using namespace std::chrono_literals;
using rex::X_STATUS;
using rex::testing::GetTestMemory;

namespace {

struct FakeDriver : rex::audio::AudioDriver {
  explicit FakeDriver(rex::memory::Memory* memory) : AudioDriver(memory) {}
  void SubmitFrame(uint32_t) override {
    if (destroyed) {
      ++use_after_destroy;
    }
    ++frames;
  }
  std::atomic<bool> destroyed = false;
  std::atomic<int> frames = 0;
  std::atomic<int> use_after_destroy = 0;
};

class TestAudioSystem : public rex::audio::AudioSystem {
 public:
  explicit TestAudioSystem(rex::runtime::FunctionDispatcher* dispatcher)
      : AudioSystem(dispatcher) {}
  ~TestAudioSystem() override {
    for (auto* driver : drivers_) {
      delete driver;
    }
  }

  using AudioSystem::DispatchClientCallback;

  // Runs in place of the guest callback.
  std::function<void(uint32_t callback_arg)> callback;

  FakeDriver* driver(size_t i) { return drivers_.at(i); }
  size_t driver_count() const { return drivers_.size(); }

 protected:
  X_STATUS CreateDriver(size_t, rex::thread::Semaphore*,
                        rex::audio::AudioDriver** out_driver) override {
    // Drivers are kept (marked destroyed) so late use is observable rather
    // than a crash.
    auto* driver = new FakeDriver(memory());
    drivers_.push_back(driver);
    *out_driver = driver;
    return X_STATUS_SUCCESS;
  }
  void DestroyDriver(rex::audio::AudioDriver* driver) override {
    static_cast<FakeDriver*>(driver)->destroyed = true;
  }
  void ExecuteClientCallback(uint32_t, uint32_t callback_arg) override {
    if (callback) {
      callback(callback_arg);
    }
  }

 private:
  std::vector<FakeDriver*> drivers_;
};

struct Fixture {
  Fixture() : dispatcher(&GetTestMemory(), &resolver), audio(&dispatcher) {}
  rex::runtime::ExportResolver resolver;
  rex::runtime::FunctionDispatcher dispatcher;
  TestAudioSystem audio;
};

constexpr uint32_t kCallback = 0x82000000;

size_t Register(TestAudioSystem& audio, uint32_t callback_arg = 0x1234) {
  size_t index = SIZE_MAX;
  REQUIRE(audio.RegisterClient(kCallback, callback_arg, &index) == X_STATUS_SUCCESS);
  REQUIRE(index < 8);
  return index;
}

}  // namespace

TEST_CASE("Unregister waits for an in-flight client callback before destroying its driver",
          "[audio][lifetime]") {
  Fixture f;
  const size_t index = Register(f.audio);
  FakeDriver* driver = f.audio.driver(0);

  std::promise<void> entered;
  std::promise<void> release;
  std::shared_future<void> released = release.get_future().share();
  f.audio.callback = [&](uint32_t) {
    entered.set_value();
    released.wait();
    // The callback re-enters through SubmitFrame, which takes the global lock
    // UnregisterClient held while clearing the slot (xenia-canary#1214).
    f.audio.SubmitFrame(index, 0);
  };

  auto worker =
      std::async(std::launch::async, [&] { return f.audio.DispatchClientCallback(index); });
  entered.get_future().wait();

  auto unregister = std::async(std::launch::async, [&] { f.audio.UnregisterClient(index); });
  CHECK(unregister.wait_for(100ms) == std::future_status::timeout);
  CHECK_FALSE(driver->destroyed);

  release.set_value();
  REQUIRE(worker.wait_for(10s) == std::future_status::ready);
  REQUIRE(unregister.wait_for(10s) == std::future_status::ready);
  CHECK(worker.get());
  CHECK(driver->destroyed);
  CHECK(driver->use_after_destroy == 0);
}

TEST_CASE("A cleared audio client is not dispatched and drops late frames", "[audio][lifetime]") {
  Fixture f;
  const size_t index = Register(f.audio);
  FakeDriver* driver = f.audio.driver(0);
  int calls = 0;
  f.audio.callback = [&](uint32_t) { ++calls; };

  CHECK(f.audio.DispatchClientCallback(index));
  f.audio.SubmitFrame(index, 0);
  CHECK(driver->frames == 1);

  f.audio.UnregisterClient(index);
  CHECK_FALSE(f.audio.DispatchClientCallback(index));
  CHECK(calls == 1);
  f.audio.SubmitFrame(index, 0);  // no driver: dropped, not dereferenced
  CHECK(driver->frames == 1);
  CHECK(driver->use_after_destroy == 0);

  // A second unregister and an out-of-range one are rejected.
  f.audio.UnregisterClient(index);
  f.audio.UnregisterClient(99);
  f.audio.SubmitFrame(99, 0);
}

TEST_CASE("A client can unregister itself from inside its callback", "[audio][lifetime]") {
  Fixture f;
  const size_t index = Register(f.audio);
  FakeDriver* driver = f.audio.driver(0);
  f.audio.callback = [&](uint32_t) {
    f.audio.UnregisterClient(index);
    f.audio.SubmitFrame(index, 0);
  };
  auto worker =
      std::async(std::launch::async, [&] { return f.audio.DispatchClientCallback(index); });
  REQUIRE(worker.wait_for(10s) == std::future_status::ready);
  CHECK(worker.get());
  CHECK(driver->destroyed);
  CHECK(driver->use_after_destroy == 0);

  // The slot is free again.
  CHECK(Register(f.audio) == index);
  f.audio.UnregisterClient(index);
}

TEST_CASE("Repeated register, dispatch and unregister never reach a destroyed driver",
          "[audio][lifetime]") {
  Fixture f;
  std::atomic<size_t> live_index = SIZE_MAX;
  std::atomic<bool> stop = false;
  std::atomic<int> callbacks = 0;
  f.audio.callback = [&](uint32_t) {
    ++callbacks;
    size_t index = live_index;
    if (index != SIZE_MAX) {
      f.audio.SubmitFrame(index, 0);
    }
  };

  // Stands in for the worker, pumping whatever slot is current.
  std::thread worker([&] {
    while (!stop) {
      size_t index = live_index;
      if (index != SIZE_MAX) {
        f.audio.DispatchClientCallback(index);
      }
      std::this_thread::yield();
    }
  });

  for (int i = 0; i < 300; ++i) {
    const size_t index = Register(f.audio, 0x1000 + i);
    live_index = index;
    std::this_thread::yield();
    f.audio.UnregisterClient(index);
    live_index = SIZE_MAX;
  }
  stop = true;
  worker.join();

  REQUIRE(f.audio.driver_count() == 300);
  int late = 0;
  for (size_t i = 0; i < f.audio.driver_count(); ++i) {
    CHECK(f.audio.driver(i)->destroyed);
    late += f.audio.driver(i)->use_after_destroy;
  }
  CHECK(late == 0);
  CHECK(callbacks > 0);
}
