/**
 * @file        vblank_pacer_test.cpp
 * @brief       Guest vblank cadence: one per interval, no bursts
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/vblank_pacer.h>

using rex::graphics::VblankPacer;

TEST_CASE("Vblanks fire once per interval on a steady clock", "[graphics][vblank]") {
  VblankPacer pacer(1000, 0);
  CHECK_FALSE(pacer.Due(999));
  CHECK(pacer.TicksUntilDue(999) == 1);
  CHECK(pacer.Due(1000));
  CHECK_FALSE(pacer.Due(1000));
  CHECK(pacer.TicksUntilDue(1000) == 1000);
  CHECK(pacer.Due(2000));
}

TEST_CASE("A late wake fires once and keeps the cadence", "[graphics][vblank]") {
  VblankPacer pacer(1000, 0);

  CHECK(pacer.Due(1600));
  CHECK_FALSE(pacer.Due(1600));
  CHECK(pacer.TicksUntilDue(1600) == 400);
  CHECK(pacer.Due(2000));
}

TEST_CASE("Falling far behind restarts the cadence instead of a burst", "[graphics][vblank]") {
  VblankPacer pacer(1000, 0);
  CHECK(pacer.Due(5000));
  CHECK_FALSE(pacer.Due(5000));
  CHECK(pacer.TicksUntilDue(5000) == 1000);

  VblankPacer close(1000, 0);
  CHECK(close.Due(2900));
  CHECK(close.Due(2900));
  CHECK_FALSE(close.Due(2900));
}
