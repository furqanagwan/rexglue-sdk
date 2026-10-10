/**
 * @file        timing_test.cpp
 * @brief       Guest delays and wait timeouts, measured on the host (RG-GDK-015)
 *
 * Guest intervals are in 100 ns ticks: negative is relative, positive is an
 * absolute guest system time. The report case prints what each interval
 * actually takes so the contract in docs/threading-contracts.md is measured,
 * not assumed.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <thread>
#include <vector>

#include <catch2/generators/catch_generators.hpp>

#include "kernel_fixture.h"

#include <rex/chrono/clock.h>
#include <rex/cvar.h>
#include <rex/system/xevent.h>
#include <rex/system/xthread.h>

namespace {

using rex::X_STATUS;
using rex::system::object_ref;
using rex::system::XEvent;
using rex::system::XThread;
using rex::testing::Kernel;
using Clock = std::chrono::steady_clock;

struct Stats {
  double median_us;
  double max_us;
};

template <typename F>
Stats Measure(int iterations, F&& operation) {
  std::vector<double> samples;
  samples.reserve(iterations);
  for (int i = 0; i < iterations; ++i) {
    auto start = Clock::now();
    operation();
    samples.push_back(std::chrono::duration<double, std::micro>(Clock::now() - start).count());
  }
  std::sort(samples.begin(), samples.end());
  return {samples[samples.size() / 2], samples.back()};
}

XThread& DelayThread() {
  static object_ref<XThread> thread(new XThread(Kernel()));
  return *thread;
}

Stats MeasureDelay(int64_t ticks, int iterations = 40) {
  return Measure(iterations, [&] { DelayThread().Delay(0, 0, uint64_t(ticks)); });
}

Stats MeasureWait(int64_t ticks, int iterations = 40) {
  static object_ref<XEvent> event = [] {
    auto e = object_ref<XEvent>(new XEvent(Kernel()));
    e->Initialize(true, false);
    return e;
  }();
  return Measure(iterations, [&] {
    uint64_t timeout = uint64_t(ticks);
    event->Wait(3, 1, 0, &timeout);
  });
}

struct PreciseTimers {
  explicit PreciseTimers(bool enabled) {
    REQUIRE(rex::cvar::SetFlagByName("guest_precise_timers", enabled ? "true" : "false"));
  }
  ~PreciseTimers() { rex::cvar::SetFlagByName("guest_precise_timers", "true"); }
};

Stats MeasureAbsoluteDelay(int64_t us, int iterations = 20) {
  return Measure(iterations, [&] {
    DelayThread().Delay(0, 0, rex::chrono::Clock::QueryGuestSystemTime() + uint64_t(us) * 10);
  });
}

}

TEST_CASE("Guest delay and wait timing report", "[.timing-report]") {
  for (bool precise : {true, false}) {
    PreciseTimers mode(precise);
    std::printf("guest_precise_timers = %s\n", precise ? "true" : "false");
    std::printf("%-22s %14s %14s %14s %14s\n", "interval", "delay median", "delay max",
                "wait median", "wait max");
    for (int64_t us : {0, 100, 500, 1000, 2000, 5000, 10000, 16000}) {
      Stats delay = MeasureDelay(-us * 10);
      Stats wait = MeasureWait(-us * 10);
      std::printf("relative %8lld us   %11.0f us %11.0f us %11.0f us %11.0f us\n",
                  static_cast<long long>(us), delay.median_us, delay.max_us, wait.median_us,
                  wait.max_us);
    }
    for (int64_t us : {1000, 10000}) {
      Stats delay = MeasureAbsoluteDelay(us);
      std::printf("absolute +%7lld us   %11.0f us %11.0f us\n", static_cast<long long>(us),
                  delay.median_us, delay.max_us);
    }
  }
}

TEST_CASE("Precise guest delays and waits are neither early nor a timer tick late",
          "[kernel][timing]") {
  PreciseTimers mode(true);
  for (int64_t us : {1000, 2000, 10000}) {
    INFO("requested " << us << " us");
    Stats delay = MeasureDelay(-us * 10, 15);
    Stats wait = MeasureWait(-us * 10, 15);
    CHECK(delay.median_us >= us);
    CHECK(delay.median_us < us + 5000);
    CHECK(wait.median_us >= us);
    CHECK(wait.median_us < us + 5000);
  }

  CHECK(MeasureDelay(-5000, 15).median_us >= 500);
}

TEST_CASE("An absolute-time delay waits until that guest time", "[kernel][timing]") {
  auto precise = GENERATE(true, false);
  PreciseTimers mode(precise);
  INFO("guest_precise_timers " << precise);

  Stats delay = MeasureAbsoluteDelay(10000, 10);
  CHECK(delay.median_us >= 9000);
  CHECK(delay.median_us < 40000);

  auto past = Measure(
      10, [] { DelayThread().Delay(0, 0, rex::chrono::Clock::QueryGuestSystemTime() - 10000); });
  CHECK(past.median_us < 5000);
}

TEST_CASE("guest_precise_timers off keeps the system-timer behaviour", "[kernel][timing]") {
  PreciseTimers mode(false);

  CHECK(MeasureDelay(-5000, 15).median_us < 500);

  CHECK(MeasureDelay(-10000, 5).median_us >= 1000);
}

TEST_CASE("A signaled object ends a precise timed wait at once", "[kernel][timing]") {
  PreciseTimers mode(true);
  auto event = object_ref<XEvent>(new XEvent(Kernel()));
  event->Initialize(true, true);
  uint64_t timeout = uint64_t(-10000000);
  auto start = Clock::now();
  CHECK(event->Wait(3, 1, 0, &timeout) == X_STATUS_SUCCESS);
  CHECK(Clock::now() - start < std::chrono::milliseconds(100));
  event->ReleaseHandle();
}

TEST_CASE("A user APC ends an alertable delay or wait early", "[kernel][timing]") {
  auto precise = GENERATE(true, false);
  PreciseTimers mode(precise);
  INFO("guest_precise_timers " << precise);
  auto event = object_ref<XEvent>(new XEvent(Kernel()));
  event->Initialize(true, false);
  for (bool delay : {true, false}) {
    INFO((delay ? "delay" : "wait"));
    std::atomic<bool> apc_ran{false};
    X_STATUS status = 0;
    std::chrono::steady_clock::duration elapsed{};
    std::thread thread([&] {
      auto start = Clock::now();
      uint64_t timeout = uint64_t(-20000000);
      status = delay ? DelayThread().Delay(0, 1, timeout) : event->Wait(3, 1, 1, &timeout);
      elapsed = Clock::now() - start;
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    QueueUserAPC([](ULONG_PTR flag) { reinterpret_cast<std::atomic<bool>*>(flag)->store(true); },
                 thread.native_handle(), reinterpret_cast<ULONG_PTR>(&apc_ran));
    thread.join();
    CHECK(apc_ran);
    CHECK(status == X_STATUS_USER_APC);
    CHECK(elapsed < std::chrono::milliseconds(1000));
  }
  event->ReleaseHandle();
}
