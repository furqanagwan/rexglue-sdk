/**
 * @file        gaming_runtime_test.cpp
 * @brief       Gaming Runtime lifecycle, diagnostics and timeout (RG-GDK-022)
 *
 * Fake hooks stand in for XGameRuntime so the missing-runtime, version and
 * stall cases run on a machine where the real runtime works. The real calls
 * are covered by the [gdk] cases in tests/unit/gdk.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include <rex/system/gaming_runtime.h>

using rex::system::ClassifyGamingRuntimeResult;
using rex::system::GamingRuntime;
using rex::system::GamingRuntimeHooks;
using rex::system::GamingRuntimeState;

namespace {

using namespace std::chrono_literals;

struct FakeRuntime {
  std::atomic<int32_t> result{0};
  std::atomic<int> initialize_calls{0};
  std::atomic<int> uninitialize_calls{0};
  std::string last_config;

  std::mutex mutex;
  std::condition_variable cv;
  bool blocked = false;

  void Release() {
    {
      std::lock_guard lock(mutex);
      blocked = false;
    }
    cv.notify_all();
  }

  static GamingRuntimeHooks Hooks(const std::shared_ptr<FakeRuntime>& fake) {
    return {
        [fake](const std::string& config_path) {
          std::unique_lock lock(fake->mutex);
          fake->cv.wait(lock, [&] { return !fake->blocked; });
          fake->last_config = config_path;
          fake->initialize_calls++;
          return fake->result.load();
        },
        [fake] { fake->uninitialize_calls++; },
    };
  }
};

bool WaitFor(const std::function<bool()>& condition) {
  const auto deadline = std::chrono::steady_clock::now() + 10s;
  while (!condition()) {
    if (std::chrono::steady_clock::now() > deadline) {
      return false;
    }
    std::this_thread::sleep_for(1ms);
  }
  return true;
}

int32_t Hr(uint32_t code) {
  return int32_t(code);
}

}

TEST_CASE("A ready runtime is uninitialized exactly once", "[gaming_runtime]") {
  auto fake = std::make_shared<FakeRuntime>();
  {
    GamingRuntime runtime(FakeRuntime::Hooks(fake));
    auto result = runtime.Initialize(5s);
    CHECK(result.ok());
    CHECK(result.hresult == 0);

    CHECK(runtime.Initialize(5s).ok());
    CHECK(fake->initialize_calls == 1);

    runtime.Uninitialize();
    CHECK(fake->uninitialize_calls == 1);
    runtime.Uninitialize();
    CHECK(fake->uninitialize_calls == 1);
    CHECK(runtime.state() == GamingRuntimeState::kNotInitialized);

    REQUIRE(runtime.Initialize(5s).ok());
  }

  CHECK(fake->initialize_calls == 2);
  CHECK(fake->uninitialize_calls == 2);
}

TEST_CASE("A missing Gaming Runtime is reported and never uninitialized", "[gaming_runtime]") {
  auto fake = std::make_shared<FakeRuntime>();
  fake->result = Hr(0x89240101);
  {
    GamingRuntime runtime(FakeRuntime::Hooks(fake));
    auto result = runtime.Initialize(5s);
    CHECK(result.state == GamingRuntimeState::kMissing);
    CHECK(result.hresult == Hr(0x89240101));
    CHECK(result.message.find("Gaming Services") != std::string::npos);
    CHECK(result.message.find("0x89240101") != std::string::npos);
    runtime.Uninitialize();
  }
  CHECK(fake->uninitialize_calls == 0);
}

TEST_CASE("Initialize results are classified", "[gaming_runtime]") {
  CHECK(ClassifyGamingRuntimeResult(0) == GamingRuntimeState::kReady);
  CHECK(ClassifyGamingRuntimeResult(1) == GamingRuntimeState::kReady);
  CHECK(ClassifyGamingRuntimeResult(Hr(0x89240107)) == GamingRuntimeState::kMissing);
  CHECK(ClassifyGamingRuntimeResult(Hr(0x8007007E)) == GamingRuntimeState::kMissing);
  CHECK(ClassifyGamingRuntimeResult(Hr(0x89240102)) == GamingRuntimeState::kVersionMismatch);
  CHECK(ClassifyGamingRuntimeResult(Hr(0x8924010B)) == GamingRuntimeState::kConfigError);
  CHECK(ClassifyGamingRuntimeResult(Hr(0x89240109)) == GamingRuntimeState::kConfigError);
  CHECK(ClassifyGamingRuntimeResult(Hr(0x8924010A)) == GamingRuntimeState::kConfigError);
  CHECK(ClassifyGamingRuntimeResult(Hr(0x89245209)) == GamingRuntimeState::kConfigError);
  CHECK(ClassifyGamingRuntimeResult(Hr(0x89245212)) == GamingRuntimeState::kConfigError);
  CHECK(ClassifyGamingRuntimeResult(Hr(0x89245213)) == GamingRuntimeState::kFailed);
  CHECK(ClassifyGamingRuntimeResult(Hr(0x89245200)) == GamingRuntimeState::kFailed);
  CHECK(ClassifyGamingRuntimeResult(Hr(0x80004005)) == GamingRuntimeState::kFailed);
}

TEST_CASE("A version mismatch names the GDK edition", "[gaming_runtime]") {
  auto fake = std::make_shared<FakeRuntime>();
  fake->result = Hr(0x89240102);
  GamingRuntime runtime(FakeRuntime::Hooks(fake));
  auto result = runtime.Initialize(5s);
  CHECK(result.state == GamingRuntimeState::kVersionMismatch);
  CHECK(result.message.find("Update Gaming Services") != std::string::npos);
}

TEST_CASE("A config path selects the options call; a missing file is a config error",
          "[gaming_runtime]") {
  auto fake = std::make_shared<FakeRuntime>();
  GamingRuntime runtime(FakeRuntime::Hooks(fake));
  REQUIRE(runtime.Initialize(5s, "C:\\title\\MicrosoftGame.config").ok());
  CHECK(fake->last_config == "C:\\title\\MicrosoftGame.config");
  runtime.Uninitialize();

  fake->result = Hr(0x80070002);
  auto missing = runtime.Initialize(5s, "C:\\nowhere\\MicrosoftGame.config");
  CHECK(missing.state == GamingRuntimeState::kConfigError);
  CHECK(missing.message.find("C:\\nowhere\\MicrosoftGame.config") != std::string::npos);

  CHECK(runtime.Initialize(5s).state == GamingRuntimeState::kFailed);
}

TEST_CASE("A stalled runtime times out and a late success is balanced", "[gaming_runtime]") {
  auto fake = std::make_shared<FakeRuntime>();
  fake->blocked = true;
  GamingRuntime runtime(FakeRuntime::Hooks(fake));

  const auto start = std::chrono::steady_clock::now();
  auto result = runtime.Initialize(50ms);
  CHECK(result.state == GamingRuntimeState::kTimedOut);
  CHECK(result.message.find("50 ms") != std::string::npos);
  CHECK(std::chrono::steady_clock::now() - start < 5s);

  CHECK(runtime.Initialize(50ms).state == GamingRuntimeState::kTimedOut);

  fake->Release();
  REQUIRE(WaitFor([&] { return fake->uninitialize_calls == 1; }));
  CHECK(fake->initialize_calls == 1);

  REQUIRE(runtime.Initialize(5s).ok());
  CHECK(fake->initialize_calls == 2);
  runtime.Uninitialize();
  CHECK(fake->uninitialize_calls == 2);
}

TEST_CASE("A late failure after a timeout is not uninitialized", "[gaming_runtime]") {
  auto fake = std::make_shared<FakeRuntime>();
  fake->blocked = true;
  fake->result = Hr(0x89240101);
  {
    GamingRuntime runtime(FakeRuntime::Hooks(fake));
    CHECK(runtime.Initialize(20ms).state == GamingRuntimeState::kTimedOut);
  }

  fake->Release();
  REQUIRE(WaitFor([&] { return fake->initialize_calls == 1; }));
  std::this_thread::sleep_for(20ms);
  CHECK(fake->uninitialize_calls == 0);
}

TEST_CASE("Without GDK hooks the runtime is unavailable", "[gaming_runtime]") {
  GamingRuntime runtime(GamingRuntimeHooks{});
  auto result = runtime.Initialize(5s);
  CHECK(result.state == GamingRuntimeState::kUnavailable);
  CHECK(result.message.find("REXGLUE_USE_GDK") != std::string::npos);
  CHECK(GamingRuntime::built_with_gdk() ==
        bool(rex::system::SystemGamingRuntimeHooks().initialize));
}

TEST_CASE("The startup policy decides whether a failed runtime stops the title",
          "[gaming_runtime]") {
  using rex::system::GamingRuntimeAllowsLaunch;
  using rex::system::GamingRuntimePolicy;
  using rex::system::GamingRuntimeResult;
  using rex::system::ParseGamingRuntimePolicy;

  CHECK(ParseGamingRuntimePolicy("off") == GamingRuntimePolicy::kOff);
  CHECK(ParseGamingRuntimePolicy("auto") == GamingRuntimePolicy::kAuto);
  CHECK(ParseGamingRuntimePolicy("required") == GamingRuntimePolicy::kRequired);
  CHECK_FALSE(ParseGamingRuntimePolicy("Required").has_value());
  CHECK_FALSE(ParseGamingRuntimePolicy("").has_value());

  const GamingRuntimeResult ready{GamingRuntimeState::kReady, 0, {}};
  const GamingRuntimeResult timed_out{GamingRuntimeState::kTimedOut, 0, {}};
  const GamingRuntimeResult unavailable{GamingRuntimeState::kUnavailable, 0, {}};
  CHECK(GamingRuntimeAllowsLaunch(GamingRuntimePolicy::kAuto, timed_out));
  CHECK(GamingRuntimeAllowsLaunch(GamingRuntimePolicy::kAuto, unavailable));
  CHECK(GamingRuntimeAllowsLaunch(GamingRuntimePolicy::kRequired, ready));
  CHECK_FALSE(GamingRuntimeAllowsLaunch(GamingRuntimePolicy::kRequired, timed_out));
  CHECK_FALSE(GamingRuntimeAllowsLaunch(GamingRuntimePolicy::kRequired, unavailable));
  CHECK(GamingRuntimeAllowsLaunch(GamingRuntimePolicy::kOff, timed_out));
}
