/**
 * @file        input/gameinput/gameinput_mapping.h
 * @brief       GameInput gamepad readings to XInput values (RG-GDK-020)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cmath>
#include <cstdint>

#include <rex/input/gameinput/gamepad_devices.h>
#include <rex/input/input.h>

// The GDK headers need the Windows headers first.
#include <windows.h>

#include <GameInput.h>

namespace rex::input::gameinput {

// GameInput sticks are -1..1 with up positive, as in XInput. The negative
// half spans 32768 and the positive 32767, so both extremes of the XInput
// range are reachable. GameInput applies no dead zone to gamepad readings
// and neither does this; titles apply their own, as they do with XInput.
inline int16_t StickToXInput(float value) {
  if (!(value == value)) {  // NaN
    return 0;
  }
  value = std::fmax(-1.0f, std::fmin(1.0f, value));
  return static_cast<int16_t>(std::lround(value < 0.0f ? value * 32768.0f : value * 32767.0f));
}

inline uint8_t TriggerToXInput(float value) {
  if (!(value == value)) {
    return 0;
  }
  value = std::fmax(0.0f, std::fmin(1.0f, value));
  return static_cast<uint8_t>(std::lround(value * 255.0f));
}

inline X_INPUT_GAMEPAD GamepadToXInput(const GameInputGamepadState& state, bool guide) {
  struct ButtonMap {
    GameInputGamepadButtons from;
    uint16_t to;
  };
  static constexpr ButtonMap kButtons[] = {
      {GameInputGamepadDPadUp, X_INPUT_GAMEPAD_DPAD_UP},
      {GameInputGamepadDPadDown, X_INPUT_GAMEPAD_DPAD_DOWN},
      {GameInputGamepadDPadLeft, X_INPUT_GAMEPAD_DPAD_LEFT},
      {GameInputGamepadDPadRight, X_INPUT_GAMEPAD_DPAD_RIGHT},
      {GameInputGamepadMenu, X_INPUT_GAMEPAD_START},
      {GameInputGamepadView, X_INPUT_GAMEPAD_BACK},
      {GameInputGamepadLeftThumbstick, X_INPUT_GAMEPAD_LEFT_THUMB},
      {GameInputGamepadRightThumbstick, X_INPUT_GAMEPAD_RIGHT_THUMB},
      {GameInputGamepadLeftShoulder, X_INPUT_GAMEPAD_LEFT_SHOULDER},
      {GameInputGamepadRightShoulder, X_INPUT_GAMEPAD_RIGHT_SHOULDER},
      {GameInputGamepadA, X_INPUT_GAMEPAD_A},
      {GameInputGamepadB, X_INPUT_GAMEPAD_B},
      {GameInputGamepadX, X_INPUT_GAMEPAD_X},
      {GameInputGamepadY, X_INPUT_GAMEPAD_Y},
  };
  uint16_t buttons = 0;
  for (const ButtonMap& map : kButtons) {
    if (state.buttons & map.from) {
      buttons |= map.to;
    }
  }
  if (guide) {
    buttons |= X_INPUT_GAMEPAD_GUIDE;
  }
  X_INPUT_GAMEPAD gamepad = {};
  gamepad.buttons = buttons;
  gamepad.left_trigger = TriggerToXInput(state.leftTrigger);
  gamepad.right_trigger = TriggerToXInput(state.rightTrigger);
  gamepad.thumb_lx = StickToXInput(state.leftThumbstickX);
  gamepad.thumb_ly = StickToXInput(state.leftThumbstickY);
  gamepad.thumb_rx = StickToXInput(state.rightThumbstickX);
  gamepad.thumb_ry = StickToXInput(state.rightThumbstickY);
  return gamepad;
}

// XInput's left motor is the low-frequency (heavy) one, the right the
// high-frequency one. Trigger motors have no XInput equivalent and stay off.
inline GameInputRumbleParams RumbleToGameInput(const Rumble& rumble) {
  GameInputRumbleParams params = {};
  params.lowFrequency = rumble.left / 65535.0f;
  params.highFrequency = rumble.right / 65535.0f;
  return params;
}

}  // namespace rex::input::gameinput
