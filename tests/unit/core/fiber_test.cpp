/**
 * @file        tests/unit/core/fiber_test.cpp
 * @brief       Unit tests for rex::thread::Fiber
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <catch2/catch_test_macros.hpp>
#include <rex/thread/fiber.h>

using rex::thread::Fiber;

static Fiber* s_main = nullptr;
static int s_count = 0;

static void counting_fiber(void*) {
  ++s_count;
  Fiber::SwitchTo(s_main);
  ++s_count;
  Fiber::SwitchTo(s_main);
}

TEST_CASE("rex::thread::Fiber - basic context switch", "[fiber]") {
  s_count = 0;
  s_main = Fiber::ConvertCurrentThread();
  auto* f = Fiber::Create(256 * 1024, counting_fiber, nullptr);

  REQUIRE(s_count == 0);
  Fiber::SwitchTo(f);
  REQUIRE(s_count == 1);
  Fiber::SwitchTo(f);
  REQUIRE(s_count == 2);

  f->Destroy();
  s_main->Destroy();
  s_main = nullptr;
}
