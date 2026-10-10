/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <cstring>

#include <rex/input/flags.h>
#include <rex/input/nop/nop_input_driver.h>
#include <rex/logging.h>

namespace rex::input::nop {

namespace {

constexpr rex::input::DeviceId kNopDevice = static_cast<rex::input::DeviceId>(0x4E4F5000);

}

NopInputDriver::NopInputDriver(rex::ui::Window* window, size_t window_z_order)
    : InputDriver(window, window_z_order) {}

NopInputDriver::~NopInputDriver() = default;

X_STATUS NopInputDriver::Setup() {
  return X_STATUS_SUCCESS;
}

void NopInputDriver::EnumerateDevices(std::vector<DeviceInfo>& out) {
  DeviceInfo info;
  info.id = kNopDevice;
  info.name = "None";
  info.synthetic = true;
  out.push_back(info);
}

X_RESULT NopInputDriver::GetDeviceCapabilities(DeviceId id, uint32_t flags,
                                               X_INPUT_CAPABILITIES* out_caps) {
  if (id != kNopDevice) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }
  if (out_caps) {
    std::memset(out_caps, 0, sizeof(*out_caps));
    out_caps->type = 0x01;
    out_caps->sub_type = 0x01;
    out_caps->flags = 0;

    out_caps->gamepad.buttons = 0xFFFF;
    out_caps->gamepad.left_trigger = 0xFF;
    out_caps->gamepad.right_trigger = 0xFF;
    out_caps->gamepad.thumb_lx = static_cast<int16_t>(0x7FFF);
    out_caps->gamepad.thumb_ly = static_cast<int16_t>(0x7FFF);
    out_caps->gamepad.thumb_rx = static_cast<int16_t>(0x7FFF);
    out_caps->gamepad.thumb_ry = static_cast<int16_t>(0x7FFF);
    out_caps->vibration.left_motor_speed = 0xFFFF;
    out_caps->vibration.right_motor_speed = 0xFFFF;
  }
  return X_ERROR_SUCCESS;
}

X_RESULT NopInputDriver::GetDeviceState(DeviceId id, X_INPUT_STATE* out_state) {
  if (id != kNopDevice) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }
  if (out_state) {
    std::memset(out_state, 0, sizeof(*out_state));
  }
  return X_ERROR_SUCCESS;
}

X_RESULT NopInputDriver::SetDeviceVibration(DeviceId id, X_INPUT_VIBRATION* vibration) {
  if (id != kNopDevice) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }

  return X_ERROR_SUCCESS;
}

X_RESULT NopInputDriver::GetDeviceKeystroke(DeviceId id, uint32_t flags,
                                            X_INPUT_KEYSTROKE* out_keystroke) {
  if (id != kNopDevice) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }

  return X_ERROR_EMPTY;
}

}
