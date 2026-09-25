/**
 * @file        gameinput_test.cpp
 * @brief       GameInput reading mapping and runtime setup (RG-GDK-020)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <vector>

#include "input/gameinput/gameinput_input_driver.h"
#include "input/gameinput/gameinput_mapping.h"

using rex::X_RESULT;
using rex::X_STATUS;

using namespace rex::input;             // NOLINT
using namespace rex::input::gameinput;  // NOLINT

TEST_CASE("GameInput sticks cover the whole XInput range", "[gdk][gameinput]") {
  CHECK(StickToXInput(0.0f) == 0);
  CHECK(StickToXInput(1.0f) == 32767);
  CHECK(StickToXInput(-1.0f) == -32768);
  CHECK(StickToXInput(0.5f) == 16384);
  CHECK(StickToXInput(-0.5f) == -16384);
  CHECK(StickToXInput(2.0f) == 32767);  // out of range clamps
  CHECK(StickToXInput(-2.0f) == -32768);
  CHECK(StickToXInput(NAN) == 0);
  CHECK(TriggerToXInput(0.0f) == 0);
  CHECK(TriggerToXInput(1.0f) == 255);
  CHECK(TriggerToXInput(-0.1f) == 0);
  CHECK(TriggerToXInput(NAN) == 0);
}

TEST_CASE("GameInput gamepad buttons map to XInput buttons", "[gdk][gameinput]") {
  GameInputGamepadState state = {};
  state.buttons = GameInputGamepadA | GameInputGamepadMenu | GameInputGamepadView |
                  GameInputGamepadDPadLeft | GameInputGamepadRightShoulder |
                  GameInputGamepadLeftThumbstick;
  state.leftThumbstickY = 1.0f;  // up is positive in both
  state.rightTrigger = 1.0f;
  X_INPUT_GAMEPAD pad = GamepadToXInput(state, false);
  CHECK(uint16_t(pad.buttons) ==
        (X_INPUT_GAMEPAD_A | X_INPUT_GAMEPAD_START | X_INPUT_GAMEPAD_BACK |
         X_INPUT_GAMEPAD_DPAD_LEFT | X_INPUT_GAMEPAD_RIGHT_SHOULDER | X_INPUT_GAMEPAD_LEFT_THUMB));
  CHECK(int16_t(pad.thumb_ly) == 32767);
  CHECK(pad.right_trigger == 255);
  CHECK(pad.left_trigger == 0);
  CHECK(uint16_t(GamepadToXInput({}, true).buttons) == X_INPUT_GAMEPAD_GUIDE);

  // Every GameInput button maps to a distinct XInput button.
  uint16_t all = 0;
  for (uint32_t bit = 1; bit <= GameInputGamepadRightThumbstick; bit <<= 1) {
    GameInputGamepadState one = {};
    one.buttons = GameInputGamepadButtons(bit);
    uint16_t mapped = GamepadToXInput(one, false).buttons;
    CHECK(mapped != 0);
    CHECK((all & mapped) == 0);
    all |= mapped;
  }
  CHECK(all == 0xF3FF);
}

TEST_CASE("XInput motor speeds become GameInput rumble", "[gdk][gameinput]") {
  GameInputRumbleParams params = RumbleToGameInput({0xFFFF, 0x8000});
  CHECK(params.lowFrequency == 1.0f);
  CHECK(std::abs(params.highFrequency - 0.5f) < 1e-4f);
  CHECK(params.leftTrigger == 0.0f);
  CHECK(params.rightTrigger == 0.0f);
}

TEST_CASE("The GameInput driver starts against the installed runtime", "[gdk][gameinput]") {
  GameInputDriver driver(nullptr, 0);
  REQUIRE(driver.Setup() == X_STATUS_SUCCESS);
  std::vector<DeviceInfo> devices;
  driver.EnumerateDevices(devices);
  INFO(devices.size() << " gamepad(s) connected");
  for (const DeviceInfo& device : devices) {
    X_INPUT_STATE state = {};
    CHECK(driver.GetDeviceState(device.id, &state) == X_ERROR_SUCCESS);
    CHECK(state.packet_number >= 1);
  }
  X_INPUT_STATE state = {};
  CHECK(driver.GetDeviceState(DeviceId::kInvalid, &state) == X_ERROR_DEVICE_NOT_CONNECTED);
}
