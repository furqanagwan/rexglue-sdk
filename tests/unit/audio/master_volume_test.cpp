/**
 * @file        master_volume_test.cpp
 * @brief       audio_volume scales the output stage's gain and a minimised title is silenced
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <rex/audio/downmix.h>
#include <rex/cvar.h>

TEST_CASE("audio_volume scales the master output gain", "[audio][volume]") {
  const float previous = rex::audio::GetOutputGain();
  rex::audio::SetOutputGain(1.0f);

  REQUIRE(rex::cvar::SetFlagByName("audio_volume", "100"));
  CHECK(rex::audio::MasterOutputGain() == 1.0f);
  REQUIRE(rex::cvar::SetFlagByName("audio_volume", "50"));
  CHECK(rex::audio::MasterOutputGain() == 0.5f);
  REQUIRE(rex::cvar::SetFlagByName("audio_volume", "0"));
  CHECK(rex::audio::MasterOutputGain() == 0.0f);

  // A title's own gain is kept and scaled.
  rex::audio::SetOutputGain(2.0f);
  REQUIRE(rex::cvar::SetFlagByName("audio_volume", "25"));
  CHECK(rex::audio::MasterOutputGain() == 0.5f);

  // Out-of-range values are refused and leave the volume unchanged.
  CHECK_FALSE(rex::cvar::SetFlagByName("audio_volume", "150"));
  CHECK(rex::audio::MasterOutputGain() == 0.5f);

  REQUIRE(rex::cvar::SetFlagByName("audio_volume", "100"));
  rex::audio::SetOutputGain(previous);
}

TEST_CASE("A minimised title is silent unless the player keeps it playing", "[audio][volume]") {
  REQUIRE(rex::cvar::SetFlagByName("audio_mute", "false"));
  REQUIRE(rex::cvar::SetFlagByName("audio_mute_minimized", "true"));
  rex::audio::SetAppConstrained(false);
  CHECK_FALSE(rex::audio::OutputSilenced());

  rex::audio::SetAppConstrained(true);
  CHECK(rex::audio::OutputSilenced());
  REQUIRE(rex::cvar::SetFlagByName("audio_mute_minimized", "false"));
  CHECK_FALSE(rex::audio::OutputSilenced());

  // audio_mute silences regardless.
  REQUIRE(rex::cvar::SetFlagByName("audio_mute", "true"));
  rex::audio::SetAppConstrained(false);
  CHECK(rex::audio::OutputSilenced());

  REQUIRE(rex::cvar::SetFlagByName("audio_mute", "false"));
  REQUIRE(rex::cvar::SetFlagByName("audio_mute_minimized", "true"));
}
