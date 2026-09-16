/**
 * @file        audio/ui_sound_test.cpp
 * @brief       Tests for decoding console XMA files to PCM
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <chrono>
#include <thread>
#include <vector>

#include <rex/audio/ui_sound.h>

TEST_CASE("DecodeXmaFile turns away what is not an XMA file", "[audio]") {
  const std::vector<uint8_t> empty;
  CHECK_FALSE(rex::audio::DecodeXmaFile(empty).has_value());

  const std::vector<uint8_t> text = {'n', 'o', 't', ' ', 'a', ' ', 'w', 'a', 'v', 'e', '!', '!'};
  CHECK_FALSE(rex::audio::DecodeXmaFile(text).has_value());

  // A PCM WAVE: the right container, not a format this decodes.
  std::vector<uint8_t> pcm = {'R', 'I', 'F', 'F', 36, 0, 0, 0, 'W', 'A', 'V', 'E',
                              'f', 'm', 't', ' ', 16, 0, 0, 0, 1, 0, 1, 0,
                              0x44, 0xAC, 0, 0, 0x88, 0x58, 1, 0, 2, 0, 16, 0,
                              'd', 'a', 't', 'a', 0, 0, 0, 0};
  CHECK_FALSE(rex::audio::DecodeXmaFile(pcm).has_value());
}

// Console sound files are Microsoft's and never ship with the SDK. Point
// REX_TEST_XMA_FILE at one from a system update you own to run this.
TEST_CASE("DecodeXmaFile decodes a console sound", "[audio][assets]") {
  const char* path = std::getenv("REX_TEST_XMA_FILE");
  if (!path) {
    SKIP("REX_TEST_XMA_FILE is not set");
  }
  std::ifstream file(path, std::ios::binary);
  REQUIRE(file);
  const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(file)),
                                   std::istreambuf_iterator<char>());

  const auto sound = rex::audio::DecodeXmaFile(bytes);
  REQUIRE(sound.has_value());
  CHECK(sound->channels >= 1);
  CHECK(sound->sample_rate >= 8000);
  REQUIRE(sound->samples.size() % sound->channels == 0);

  float peak = 0.0f;
  for (float sample : sound->samples) {
    peak = std::max(peak, std::abs(sample));
  }
  CHECK(peak > 0.01f);  // audible, not silence
  CHECK(peak <= 1.0f);
}

TEST_CASE("UiSoundPlayer plays a decoded console sound", "[audio][assets]") {
  const char* path = std::getenv("REX_TEST_XMA_FILE");
  if (!path) {
    SKIP("REX_TEST_XMA_FILE is not set");
  }
  std::ifstream file(path, std::ios::binary);
  REQUIRE(file);
  const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(file)),
                                   std::istreambuf_iterator<char>());
  const auto sound = rex::audio::DecodeXmaFile(bytes);
  REQUIRE(sound.has_value());

  rex::audio::UiSoundPlayer player;
  // Overlapping plays exercise the voice pool, as quick menu presses do.
  for (int i = 0; i < 6; ++i) {
    player.Play(*sound, 0.2f);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
}
