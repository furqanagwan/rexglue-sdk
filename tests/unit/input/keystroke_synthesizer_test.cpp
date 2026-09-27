/**
 * @file        keystroke_synthesizer_test.cpp
 * @brief       Gamepad keystroke events shared by the SDL and GameInput drivers
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <rex/input/keystroke_synthesizer.h>
#include <rex/ui/virtual_key.h>

using rex::X_RESULT;

using namespace rex::input;  // NOLINT
using rex::ui::VirtualKey;

namespace {

struct Event {
  X_RESULT result;
  uint16_t vk;
  uint16_t flags;
};

Event Next(KeystrokeSynthesizer& s, const X_INPUT_GAMEPAD& pad, uint64_t now, bool active = true) {
  X_INPUT_KEYSTROKE k = {};
  X_RESULT result = s.Next(pad, active, now, &k);
  return {result, uint16_t(k.virtual_key), uint16_t(k.flags)};
}

}  // namespace

TEST_CASE("Keystrokes report one edge per call, key-ups first", "[input][keystroke]") {
  KeystrokeSynthesizer s;
  X_INPUT_GAMEPAD pad = {};
  CHECK(Next(s, pad, 0).result == X_ERROR_EMPTY);

  pad.buttons = X_INPUT_GAMEPAD_A;
  Event e = Next(s, pad, 0);
  CHECK(e.result == X_ERROR_SUCCESS);
  CHECK(e.vk == uint16_t(VirtualKey::kXInputPadA));
  CHECK(e.flags == X_INPUT_KEYSTROKE_KEYDOWN);
  CHECK(Next(s, pad, 10).result == X_ERROR_EMPTY);

  // Release A and press B together: the release comes first.
  pad.buttons = X_INPUT_GAMEPAD_B;
  e = Next(s, pad, 20);
  CHECK(e.vk == uint16_t(VirtualKey::kXInputPadA));
  CHECK(e.flags == X_INPUT_KEYSTROKE_KEYUP);
  e = Next(s, pad, 20);
  CHECK(e.vk == uint16_t(VirtualKey::kXInputPadB));
  CHECK(e.flags == X_INPUT_KEYSTROKE_KEYDOWN);
}

TEST_CASE("Held buttons repeat after the delay, at the repeat rate", "[input][keystroke]") {
  KeystrokeSynthesizer s;
  X_INPUT_GAMEPAD pad = {};
  pad.buttons = X_INPUT_GAMEPAD_DPAD_DOWN;
  REQUIRE(Next(s, pad, 1000).flags == X_INPUT_KEYSTROKE_KEYDOWN);
  CHECK(Next(s, pad, 1000 + KeystrokeSynthesizer::kRepeatDelayMs).result == X_ERROR_EMPTY);
  Event e = Next(s, pad, 1000 + KeystrokeSynthesizer::kRepeatDelayMs + 1);
  CHECK(e.vk == uint16_t(VirtualKey::kXInputPadDpadDown));
  CHECK(e.flags == (X_INPUT_KEYSTROKE_KEYDOWN | X_INPUT_KEYSTROKE_REPEAT));
  uint64_t t = 1000 + KeystrokeSynthesizer::kRepeatDelayMs + 1;
  CHECK(Next(s, pad, t + KeystrokeSynthesizer::kRepeatRateMs).result == X_ERROR_EMPTY);
  CHECK(Next(s, pad, t + KeystrokeSynthesizer::kRepeatRateMs + 1).flags ==
        (X_INPUT_KEYSTROKE_KEYDOWN | X_INPUT_KEYSTROKE_REPEAT));
}

TEST_CASE("Analog inputs become virtual keys past their thresholds", "[input][keystroke]") {
  X_INPUT_GAMEPAD pad = {};
  pad.left_trigger = KeystrokeSynthesizer::kTriggerThreshold;
  CHECK(KeystrokeSynthesizer::AnalogToKeyfield(pad) == 0);
  pad.left_trigger = KeystrokeSynthesizer::kTriggerThreshold + 1;
  CHECK(KeystrokeSynthesizer::AnalogToKeyfield(pad) == (uint64_t(1) << 16));

  pad = {};
  pad.thumb_lx = -32768;
  pad.thumb_ly = 32767;  // up-left is its own key, not up plus left
  CHECK(KeystrokeSynthesizer::AnalogToKeyfield(pad) == (uint64_t(1) << 22));
  pad = {};
  pad.thumb_ry = -32768;
  CHECK(KeystrokeSynthesizer::AnalogToKeyfield(pad) == (uint64_t(1) << 27));
}

TEST_CASE("Inactive input releases every held key", "[input][keystroke]") {
  KeystrokeSynthesizer s;
  X_INPUT_GAMEPAD pad = {};
  pad.buttons = X_INPUT_GAMEPAD_A;
  pad.right_trigger = 255;
  REQUIRE(Next(s, pad, 0).result == X_ERROR_SUCCESS);
  REQUIRE(Next(s, pad, 0).result == X_ERROR_SUCCESS);
  CHECK(Next(s, pad, 0, false).flags == X_INPUT_KEYSTROKE_KEYUP);
  CHECK(Next(s, pad, 0, false).flags == X_INPUT_KEYSTROKE_KEYUP);
  CHECK(Next(s, pad, 0, false).result == X_ERROR_EMPTY);
  // Back in focus, still held: key-downs again.
  CHECK(Next(s, pad, 10).flags == X_INPUT_KEYSTROKE_KEYDOWN);
}
