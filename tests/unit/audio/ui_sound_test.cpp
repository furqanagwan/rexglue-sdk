/**
 * @file        tests/unit/audio/ui_sound_test.cpp
 * @brief       RIFF XMA UI sound decoding (RG-GDK-041)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include <rex/audio/ui_sound.h>
#include <rex/ui/xui/system_update.h>

#include "xma_synth.h"

using namespace xma_synth;

namespace {

void Le16(std::vector<uint8_t>& out, uint16_t v) {
  out.push_back(uint8_t(v));
  out.push_back(uint8_t(v >> 8));
}

void Le32(std::vector<uint8_t>& out, uint32_t v) {
  for (int shift = 0; shift < 32; shift += 8) {
    out.push_back(uint8_t(v >> shift));
  }
}

void Chunk(std::vector<uint8_t>& out, const char* id, const std::vector<uint8_t>& body) {
  out.insert(out.end(), id, id + 4);
  Le32(out, uint32_t(body.size()));
  out.insert(out.end(), body.begin(), body.end());
  if (body.size() & 1) {
    out.push_back(0);
  }
}

std::vector<uint8_t> XmaFile(const std::vector<uint8_t>& packets, uint8_t channels,
                             uint16_t streams = 1) {
  std::vector<uint8_t> fmt;
  Le16(fmt, 0x0165);
  Le16(fmt, 16);
  Le16(fmt, 0x10D6);
  Le16(fmt, 0);
  Le16(fmt, streams);
  fmt.push_back(0);
  fmt.push_back(2);
  for (uint16_t s = 0; s < streams; ++s) {
    Le32(fmt, 0);
    Le32(fmt, 44100);
    Le32(fmt, 0);
    Le32(fmt, 0);
    fmt.push_back(0);
    fmt.push_back(channels);
    Le16(fmt, channels == 2 ? 3 : 4);
  }
  std::vector<uint8_t> body = {'W', 'A', 'V', 'E'};
  Chunk(body, "fmt ", fmt);
  Chunk(body, "data", packets);
  std::vector<uint8_t> out = {'R', 'I', 'F', 'F'};
  Le32(out, uint32_t(body.size()));
  out.insert(out.end(), body.begin(), body.end());
  return out;
}

}

TEST_CASE("XMA UI sounds decode every frame across packets", "[audio][ui_sound]") {
  const Stream stream = BuildStream(SilentFrames({3000, 3000, 3000, 3000, 3000, 3000}), 2, false);
  std::string error;
  auto sound = rex::audio::DecodeXmaFile(XmaFile(stream.bytes, 1), &error);
  INFO(error);
  REQUIRE(sound);
  CHECK(sound->sample_rate == 44100);
  CHECK(sound->channels == 1);
  CHECK(sound->samples.size() == 6 * 512);
  for (int16_t s : sound->samples) {
    REQUIRE(s == 0);
  }
}

TEST_CASE("XMA UI sounds decode stereo frames interleaved", "[audio][ui_sound]") {
  const Stream stream = BuildStream(SilentFrames({1500, 1500}, true), 1, false);
  std::string error;
  auto sound = rex::audio::DecodeXmaFile(XmaFile(stream.bytes, 2), &error);
  INFO(error);
  REQUIRE(sound);
  CHECK(sound->channels == 2);
  CHECK(sound->samples.size() == 2 * 512 * 2);
}

TEST_CASE("XMA UI sound decoding stops at the frame that ends the stream", "[audio][ui_sound]") {
  std::vector<Bits> frames = {SilentFrame(1000, false, true), SilentFrame(1000, false, false),
                              SilentFrame(1000, false, false)};
  const Stream stream = BuildStream(frames, 1, false);
  std::string error;
  auto sound = rex::audio::DecodeXmaFile(XmaFile(stream.bytes, 1), &error);
  REQUIRE(sound);
  CHECK(sound->samples.size() == 2 * 512);
}

TEST_CASE("XMA UI sound decoding rejects what it cannot play", "[audio][ui_sound]") {
  std::string error;
  CHECK_FALSE(rex::audio::DecodeXmaFile(std::vector<uint8_t>{'R', 'I', 'F', 'F'}, &error));
  const Stream stream = BuildStream(SilentFrames({1000}), 1, false);
  CHECK_FALSE(rex::audio::DecodeXmaFile(XmaFile(stream.bytes, 1, 2), &error));
  CHECK(error.find("single-stream") != std::string::npos);

  CHECK_FALSE(rex::audio::DecodeXmaFile(
      XmaFile(std::vector<uint8_t>(stream.bytes.begin(), stream.bytes.begin() + 100), 1), &error));
}

TEST_CASE("The console's guide sounds decode", "[audio][ui_sound][local]") {
  const char* path = std::getenv("REXGLUE_SYSTEM_UPDATE");
  if (!path || !*path) {
    SKIP("REXGLUE_SYSTEM_UPDATE is not set");
  }
  std::string error;
  auto update = rex::ui::xui::SystemUpdate::Load(path, &error);
  INFO(error);
  REQUIRE(update);
  int decoded = 0;
  for (const char* name : {"hud/hud", "xam/xam", "xam/skin", "xam/shrdres"}) {
    for (const auto& entry : update->Find(name)->entries()) {
      if (!entry.name.ends_with(".xma")) {
        continue;
      }
      CAPTURE(name, entry.name);
      auto sound = rex::audio::DecodeXmaFile(update->Find(name)->Find(entry.name), &error);
      INFO(error);
      REQUIRE(sound);
      CHECK(sound->samples.size() >= 512);

      int peak = 0;
      for (int16_t sample : sound->samples) {
        peak = std::max(peak, std::abs(int(sample)));
      }
      CHECK(peak > 1000);
      ++decoded;
    }
  }
  CHECK(decoded >= 15);
}
