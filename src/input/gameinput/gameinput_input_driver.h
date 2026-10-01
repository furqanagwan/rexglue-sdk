/**
 * @file        input/gameinput/gameinput_input_driver.h
 * @brief       Native GameInput gamepad driver, GDK builds only (RG-GDK-020)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>

#include <rex/input/gameinput/gamepad_devices.h>
#include <rex/input/input_driver.h>

#include "../ble_battery.h"

// The GDK headers need the Windows headers first.
#include <windows.h>

#include <GameInput.h>

namespace rex::input::gameinput {

// Gamepads through GameInput (GameInputKindGamepad). The runtime DLL is loaded
// at Setup, so a machine without GameInput gets a logged diagnostic and the
// caller falls back to another driver instead of failing to start.
class GameInputDriver final : public InputDriver {
 public:
  explicit GameInputDriver(rex::ui::Window* window, size_t window_z_order);
  ~GameInputDriver() override;

  X_STATUS Setup() override;

  void EnumerateDevices(std::vector<DeviceInfo>& out) override;
  X_RESULT GetDeviceState(DeviceId id, X_INPUT_STATE* out_state) override;
  X_RESULT GetDeviceCapabilities(DeviceId id, uint32_t flags,
                                 X_INPUT_CAPABILITIES* out_caps) override;
  X_RESULT SetDeviceVibration(DeviceId id, X_INPUT_VIBRATION* vibration) override;
  X_RESULT GetDeviceKeystroke(DeviceId id, uint32_t flags,
                              X_INPUT_KEYSTROKE* out_keystroke) override;
  bool GetDeviceBattery(DeviceId id, PadBattery* out) override;

  /// Connected pads with this USB vendor and product ID, for the XInput
  /// supplement to skip.
  size_t CountDevices(uint16_t vendor_id, uint16_t product_id);

 private:
  static void CALLBACK OnDeviceStatus(GameInputCallbackToken token, void* context,
                                      IGameInputDevice* device, uint64_t timestamp,
                                      GameInputDeviceStatus current,
                                      GameInputDeviceStatus previous);

  // All require mutex_. ActiveLocked reads is_active() and applies a focus
  // change to the motors; PollLocked stores the device's current reading.
  bool ActiveLocked();
  void PollLocked(DeviceId id);
  void ApplyRumbleLocked(const void* host_device, const Rumble& rumble);

  std::mutex mutex_;
  HMODULE module_ = nullptr;
  IGameInput* game_input_ = nullptr;
  GameInputCallbackToken device_token_ = 0;
  GamepadDevices devices_;
  // Connected devices, each holding one reference; keyed like devices_.
  std::unordered_map<const void*, IGameInputDevice*> host_devices_;
  BleBatteryMonitor ble_battery_;
};

}  // namespace rex::input::gameinput
