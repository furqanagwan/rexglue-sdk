/**
 * @file        input/gameinput/gameinput_input_driver.h
 * @brief       GameInput driver, the input API a GDK title is expected to use
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <array>
#include <cstdint>
#include <mutex>
#include <vector>

#include <rex/input/input_driver.h>

struct IGameInput;
struct IGameInputDevice;

namespace rex::input::gameinput {

// The current Microsoft input API, and the only supported one on Xbox. It is
// preferred over XInput and SDL inside a GDK package: it reports the device
// behind a reading, its battery in real units rather than four steps, and it
// does not pay XInput's cost for polling a slot nobody is using.
//
// GameInput.dll is loaded at runtime rather than linked, so a build made with
// the GDK still starts on a machine without the runtime; Setup fails there and
// the caller falls back to another driver.
class GameInputInputDriver final : public InputDriver {
 public:
  explicit GameInputInputDriver(rex::ui::Window* window, size_t window_z_order);
  ~GameInputInputDriver() override;

  X_STATUS Setup() override;

  void EnumerateDevices(std::vector<DeviceInfo>& out) override;
  X_RESULT GetDeviceState(DeviceId id, X_INPUT_STATE* out_state) override;
  X_RESULT GetDeviceCapabilities(DeviceId id, uint32_t flags,
                                 X_INPUT_CAPABILITIES* out_caps) override;
  X_RESULT SetDeviceVibration(DeviceId id, X_INPUT_VIBRATION* vibration) override;
  X_RESULT GetDeviceKeystroke(DeviceId id, uint32_t flags,
                              X_INPUT_KEYSTROKE* out_keystroke) override;
  X_RESULT GetDeviceBatteryInformation(DeviceId id, uint32_t type,
                                       X_INPUT_BATTERY_INFORMATION* out_battery) override;

 private:
  // GameInput identifies a device by pointer, which says nothing about which
  // player it is. The console's four slots are kept here in the order devices
  // first produced a reading, so slot 0 stays slot 0 while it is connected.
  static constexpr size_t kSlotCount = 4;

  struct Slot {
    IGameInputDevice* device = nullptr;
    // What the guest last saw, so a keystroke can be reported on a change.
    uint16_t buttons = 0;
  };

  // Refreshes the slot table from the current reading. Callers hold lock_.
  void RefreshSlotsLocked();
  // The device in a slot, addrefed by the table. Null when the slot is empty.
  IGameInputDevice* DeviceForLocked(DeviceId id, size_t* out_slot);
  void ReleaseSlotsLocked();

  void* module_ = nullptr;
  IGameInput* game_input_ = nullptr;
  std::mutex lock_;
  std::array<Slot, kSlotCount> slots_{};
};

}  // namespace rex::input::gameinput
