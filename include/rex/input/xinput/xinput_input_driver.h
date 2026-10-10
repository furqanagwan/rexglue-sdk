/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Sanjay Govind, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <array>
#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>

#include <rex/input/input_driver.h>

namespace rex::input {
class BleBatteryMonitor;
}

namespace rex::input::xinput {

class XinputInputDriver final : public InputDriver {
 public:
  using ClaimedCount = std::function<size_t(uint16_t vendor_id, uint16_t product_id)>;

  explicit XinputInputDriver(rex::ui::Window* window, size_t window_z_order);

  XinputInputDriver(rex::ui::Window* window, size_t window_z_order, ClaimedCount claimed);
  ~XinputInputDriver() override;

  X_STATUS Setup() override;

  void EnumerateDevices(std::vector<DeviceInfo>& out) override;
  X_RESULT GetDeviceState(DeviceId id, X_INPUT_STATE* out_state) override;
  X_RESULT GetDeviceCapabilities(DeviceId id, uint32_t flags,
                                 X_INPUT_CAPABILITIES* out_caps) override;
  X_RESULT SetDeviceVibration(DeviceId id, X_INPUT_VIBRATION* vibration) override;
  X_RESULT GetDeviceKeystroke(DeviceId id, uint32_t flags,
                              X_INPUT_KEYSTROKE* out_keystroke) override;
  bool GetDeviceBattery(DeviceId id, PadBattery* out) override;

 private:
  bool SlotIds(uint32_t slot, uint16_t* vendor_id, uint16_t* product_id);

  ClaimedCount claimed_;
  std::unique_ptr<BleBatteryMonitor> ble_battery_;
  void* module_;
  void* XInputGetCapabilities_;
  void* XInputGetState_;
  void* XInputGetStateEx_;
  void* XInputGetKeystroke_;
  void* XInputSetState_;
  void* XInputEnable_;
  void* XInputGetBatteryInformation_ = nullptr;
  void* XInputGetCapabilitiesEx_ = nullptr;
};

}
