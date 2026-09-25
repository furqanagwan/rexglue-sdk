/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    ReXGlue, 2026 - Split out of the SDL driver so every gamepad
 *              driver reports XInputGetKeystroke events the same way (RG-GDK-020)
 */

#pragma once

#include <cstdint>

#include <rex/input/input.h>
#include <rex/kernel.h>

namespace rex::input {

// Turns successive gamepad states into XInputGetKeystroke events: one event
// per call, key-ups before key-downs, analog triggers and stick directions as
// virtual buttons, and key repeat for the last button pressed. Keep one per
// physical pad so it survives guest user reassignment.
class KeystrokeSynthesizer {
 public:
  static constexpr int16_t kThumbThreshold = 0x4E00;
  static constexpr uint8_t kTriggerThreshold = 0x1F;
  static constexpr uint32_t kRepeatDelayMs = 400;
  static constexpr uint32_t kRepeatRateMs = 100;

  // `active` false reports every button released, so focus loss produces
  // key-ups and regaining focus produces key-downs. `now_ms` is guest uptime.
  // Returns X_ERROR_SUCCESS with an event, or X_ERROR_EMPTY. user_index is
  // left zero; InputSystem stamps the guest user.
  X_RESULT Next(const X_INPUT_GAMEPAD& gamepad, bool active, uint64_t now_ms,
                X_INPUT_KEYSTROKE* out_keystroke);

  // Analog inputs past their thresholds as virtual buttons 16-33.
  static uint64_t AnalogToKeyfield(const X_INPUT_GAMEPAD& gamepad);

 private:
  enum class RepeatState {
    kIdle,       // no buttons pressed or repeating has ended
    kWaiting,    // a button is held and the delay is awaited
    kRepeating,  // actively repeating at a rate
  };

  uint64_t buttons_ = 0;
  RepeatState repeat_state_ = RepeatState::kIdle;
  // The button pressed last, and when its down or repeat event was sent.
  uint8_t repeat_button_index_ = 0;
  uint64_t repeat_time_ = 0;
};

}  // namespace rex::input
