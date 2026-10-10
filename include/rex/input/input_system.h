#pragma once
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

#include <array>
#include <atomic>
#include <bitset>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

#include <rex/input/device_assignment.h>
#include <rex/input/input.h>
#include <rex/input/input_driver.h>
#include <rex/input/state_merge.h>
#include <rex/system/interfaces/input.h>

namespace rex::ui {
class Window;
}

namespace rex::input {

class InputSystem : public system::IInputSystem {
 public:
  explicit InputSystem(rex::ui::Window* window);
  ~InputSystem() override;

  rex::ui::Window* window() const { return window_; }

  X_STATUS Setup() override;
  void Shutdown() override;

  void AddDriver(std::unique_ptr<InputDriver> driver);
  void AttachWindow(rex::ui::Window* window);
  void SetActiveCallback(std::function<bool()> callback);

  void SetDeviceAssignment(std::unique_ptr<DeviceAssignment> assignment);

  X_RESULT GetCapabilities(uint32_t user_index, uint32_t flags, X_INPUT_CAPABILITIES* out_caps);
  X_RESULT GetState(uint32_t user_index, X_INPUT_STATE* out_state);

  X_RESULT GetStateForUI(uint32_t user_index, X_INPUT_STATE* out_state);
  X_RESULT SetState(uint32_t user_index, X_INPUT_VIBRATION* vibration);
  X_RESULT GetKeystroke(uint32_t user_index, uint32_t flags, X_INPUT_KEYSTROKE* out_keystroke);

  bool GetBattery(uint32_t user_index, PadBattery* out_battery);

  void AddUIInputBlocker();
  void RemoveUIInputBlocker();

  bool GetVibrationEnabled() const;
  void ToggleVibration();

  std::bitset<kMaxGuestUsers> GetConnectedUsers() const {
    return std::bitset<kMaxGuestUsers>(connected_users_.load());
  }

  uint32_t GetLastUsedUser() const { return last_used_user_.load(); }

 private:
  std::mutex mutex_;

  void RefreshDevices();
  InputDriver* DriverForDevice(DeviceId id);
  const DeviceInfo* DeviceInfoFor(DeviceId id) const;

  DeviceId ChooseDeviceForUser(uint32_t user_index) const;

  X_RESULT GetStateLocked(uint32_t user_index, X_INPUT_STATE* out_state, bool* out_devices_changed);
  X_RESULT GetKeystrokeLocked(uint32_t user_index, uint32_t flags,
                              X_INPUT_KEYSTROKE* out_keystroke);

  X_RESULT DrainKeystrokesLocked(uint32_t user_index, uint32_t flags);
  bool UpdateConnectedUserLocked(uint32_t user_index, bool connected);
  static void NotifyDevicesChanged();
  X_INPUT_VIBRATION ModifyVibrationLevel(const X_INPUT_VIBRATION* vibration) const;

  rex::ui::Window* window_ = nullptr;

  std::vector<std::unique_ptr<InputDriver>> drivers_;

  std::unique_ptr<DeviceAssignment> assignment_;
  ActiveDeviceTracker active_devices_;

  std::vector<DeviceInfo> devices_;
  std::vector<InputDriver*> device_owners_;

  std::atomic<uint32_t> connected_users_{0};
  std::atomic<uint32_t> last_used_user_{0};

  std::array<std::pair<StickRange, StickRange>, kMaxGuestUsers> user_stick_ranges_ = {};

  int ui_input_blockers_ = 0;

  std::array<uint16_t, kMaxGuestUsers> consumed_buttons_ = {};
};

std::unique_ptr<InputSystem> CreateDefaultInputSystem(bool tool_mode);

std::unique_ptr<InputSystem> CreatePhysicalInputSystem();

}
