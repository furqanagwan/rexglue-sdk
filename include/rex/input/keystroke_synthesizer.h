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

class KeystrokeSynthesizer {
 public:
  static constexpr int16_t kThumbThreshold = 0x4E00;
  static constexpr uint8_t kTriggerThreshold = 0x1F;
  static constexpr uint32_t kRepeatDelayMs = 400;
  static constexpr uint32_t kRepeatRateMs = 100;

  X_RESULT Next(const X_INPUT_GAMEPAD& gamepad, bool active, uint64_t now_ms,
                X_INPUT_KEYSTROKE* out_keystroke);

  static uint64_t AnalogToKeyfield(const X_INPUT_GAMEPAD& gamepad);

 private:
  enum class RepeatState {
    kIdle,
    kWaiting,
    kRepeating,
  };

  uint64_t buttons_ = 0;
  RepeatState repeat_state_ = RepeatState::kIdle;

  uint8_t repeat_button_index_ = 0;
  uint64_t repeat_time_ = 0;
};

}
