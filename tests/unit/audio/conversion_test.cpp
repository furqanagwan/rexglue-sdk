/**
 * @file        conversion_test.cpp
 * @brief       Guest 5.1 frame to host layouts: channel impulses, fold, clipping
 *
 * Shared by the SDL and XAudio2 outputs (RG-GDK-019).
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cstring>
#include <vector>

#include <rex/audio/conversion.h>
#include <rex/audio/downmix.h>
#include <rex/memory.h>

using Catch::Approx;
using rex::audio::StereoFold;
using rex::audio::SurroundMix;

namespace {

constexpr size_t kSamples = 256;
constexpr size_t kChannels = 6;
enum Channel { kFL, kFR, kFC, kLFE, kBL, kBR };

float BigEndian(float value) {
  uint32_t bits;
  std::memcpy(&bits, &value, 4);
  bits = rex::byte_swap(bits);
  float out;
  std::memcpy(&out, &bits, 4);
  return out;
}

// A guest frame: six channels one after another, big endian, with `value` at
// `sample` of `channel` and silence elsewhere.
std::vector<float> Impulse(int channel, size_t sample, float value) {
  std::vector<float> frame(kChannels * kSamples, 0.0f);
  frame[channel * kSamples + sample] = BigEndian(value);
  return frame;
}

}  // namespace

TEST_CASE("5.1 passthrough puts each guest channel in its interleaved slot",
          "[audio][conversion]") {
  const SurroundMix unity;
  for (int channel = 0; channel < 6; ++channel) {
    INFO("channel " << channel);
    const size_t sample = 37;
    auto frame = Impulse(channel, sample, 0.5f);
    std::vector<float> out(kChannels * kSamples, -9.0f);
    rex::audio::conversion::sequential_6_BE_to_interleaved_6_LE(out.data(), frame.data(), kSamples,
                                                                unity, 1.0f);
    for (size_t i = 0; i < out.size(); ++i) {
      const float expected = i == sample * kChannels + channel ? 0.5f : 0.0f;
      REQUIRE(out[i] == Approx(expected));
    }
  }
}

TEST_CASE("5.1 passthrough applies the mix weights and gain per channel", "[audio][conversion]") {
  SurroundMix mix;
  mix.center = 0.5f;
  mix.surround = 0.25f;
  mix.lfe = 0.0f;
  const float gain = 0.8f;
  const float weight[6] = {gain, gain, 0.5f * gain, 0.0f, 0.25f * gain, 0.25f * gain};
  for (int channel = 0; channel < 6; ++channel) {
    INFO("channel " << channel);
    auto frame = Impulse(channel, 10, 0.5f);
    std::vector<float> out(kChannels * kSamples);
    rex::audio::conversion::sequential_6_BE_to_interleaved_6_LE(out.data(), frame.data(), kSamples,
                                                                mix, gain);
    CHECK(out[10 * kChannels + channel] == Approx(0.5f * weight[channel]));
  }
}

TEST_CASE("Stereo fold sends each guest channel to the right side", "[audio][conversion]") {
  const StereoFold fold;  // ITU-R BS.775 defaults
  struct Case {
    int channel;
    float left;
    float right;
  };
  const Case cases[] = {
      {kFL, 1.0f, 0.0f},          {kFR, 0.0f, 1.0f},          {kFC, fold.center, fold.center},
      {kLFE, fold.lfe, fold.lfe}, {kBL, fold.surround, 0.0f}, {kBR, 0.0f, fold.surround},
  };
  for (const Case& c : cases) {
    INFO("channel " << c.channel);
    const size_t sample = 100;
    auto frame = Impulse(c.channel, sample, 0.5f);
    std::vector<float> out(2 * kSamples, -9.0f);
    rex::audio::conversion::sequential_6_BE_to_interleaved_2_LE(out.data(), frame.data(), kSamples,
                                                                fold, 1.0f);
    CHECK(out[sample * 2 + 0] == Approx(0.5f * c.left * fold.scale));
    CHECK(out[sample * 2 + 1] == Approx(0.5f * c.right * fold.scale));
    for (size_t i = 0; i < out.size(); ++i) {
      if (i / 2 != sample) {
        REQUIRE(out[i] == 0.0f);
      }
    }
  }
}

TEST_CASE("Output clamps to [-1, 1] after gain", "[audio][conversion]") {
  auto hot = Impulse(kFL, 0, 0.9f);
  hot[kFR * kSamples] = BigEndian(-0.9f);
  std::vector<float> out6(kChannels * kSamples);
  rex::audio::conversion::sequential_6_BE_to_interleaved_6_LE(out6.data(), hot.data(), kSamples,
                                                              SurroundMix{}, 4.0f);
  CHECK(out6[0] == 1.0f);
  CHECK(out6[1] == -1.0f);

  std::vector<float> out2(2 * kSamples);
  StereoFold fold;
  fold.scale = 4.0f;
  rex::audio::conversion::sequential_6_BE_to_interleaved_2_LE(out2.data(), hot.data(), kSamples,
                                                              fold, 1.0f);
  CHECK(out2[0] == 1.0f);
  CHECK(out2[1] == -1.0f);
}
