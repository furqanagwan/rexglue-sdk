/**
 * @file        timer_resolution_test.cpp
 * @brief       Millisecond sleeps after raising the timer resolution
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <chrono>

#include <rex/thread.h>

TEST_CASE("A 1 ms sleep lasts about 1 ms with the high timer resolution", "[core][timer]") {
  const uint32_t resolution = rex::thread::RequestHighTimerResolution();
  INFO("timer resolution " << resolution << " x 100 ns");
  REQUIRE(resolution != 0);
  CHECK(resolution <= 10000);

  constexpr int kSleeps = 20;
  auto start = std::chrono::steady_clock::now();
  for (int i = 0; i < kSleeps; ++i) {
    rex::thread::Sleep(std::chrono::milliseconds(1));
  }
  auto average = (std::chrono::steady_clock::now() - start) / kSleeps;
  const double average_ms = std::chrono::duration<double, std::milli>(average).count();
  INFO("average 1 ms sleep " << average_ms << " ms");
  CHECK(average < std::chrono::milliseconds(5));
}
