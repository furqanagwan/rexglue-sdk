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

  /// Replaces any previous assignment. Call before the guest starts polling.
  void SetDeviceAssignment(std::unique_ptr<DeviceAssignment> assignment);

  X_RESULT GetCapabilities(uint32_t user_index, uint32_t flags, X_INPUT_CAPABILITIES* out_caps);
  X_RESULT GetState(uint32_t user_index, X_INPUT_STATE* out_state);
  /// GetState for the emulator's own UI, which reads while the guest is blocked.
  X_RESULT GetStateForUI(uint32_t user_index, X_INPUT_STATE* out_state);
  X_RESULT SetState(uint32_t user_index, X_INPUT_VIBRATION* vibration);
  X_RESULT GetKeystroke(uint32_t user_index, uint32_t flags, X_INPUT_KEYSTROKE* out_keystroke);

  /// While any blocker is held the guest reads a neutral pad and no
  /// keystrokes. Buttons still held when a blocker drops stay masked until
  /// released, so the press that dismissed the dialog does not also reach the
  /// game.
  void AddUIInputBlocker();
  void RemoveUIInputBlocker();

  bool GetVibrationEnabled() const;
  void ToggleVibration();

  std::bitset<kMaxGuestUsers> GetConnectedUsers() const {
    return std::bitset<kMaxGuestUsers>(connected_users_.load());
  }
  /// Guest user whose device most recently produced a button press.
  uint32_t GetLastUsedUser() const { return last_used_user_.load(); }

 private:
  // Guest threads may poll input concurrently. Hold this across refresh,
  // assignment, and driver lookup so one poll cannot invalidate another.
  std::mutex mutex_;

  /// Re-enumerates every driver and notifies the assignment when the set
  /// changed.
  void RefreshDevices();
  InputDriver* DriverForDevice(DeviceId id);
  const DeviceInfo* DeviceInfoFor(DeviceId id) const;
  /// The device that speaks for a user, preferring the one most recently in
  /// the player's hands.
  DeviceId ChooseDeviceForUser(uint32_t user_index) const;

  /// Merged state of a user's devices with the deadzones applied. Sets
  /// `out_devices_changed` when the user connected or disconnected, for the
  /// caller to send XN_SYS_INPUTDEVICESCHANGED once mutex_ is released.
  X_RESULT GetStateLocked(uint32_t user_index, X_INPUT_STATE* out_state, bool* out_devices_changed);
  X_RESULT GetKeystrokeLocked(uint32_t user_index, uint32_t flags,
                              X_INPUT_KEYSTROKE* out_keystroke);
  /// Reads and discards pending keystrokes. Returns the last read's result.
  X_RESULT DrainKeystrokesLocked(uint32_t user_index, uint32_t flags);
  bool UpdateConnectedUserLocked(uint32_t user_index, bool connected);
  static void NotifyDevicesChanged();
  X_INPUT_VIBRATION ModifyVibrationLevel(const X_INPUT_VIBRATION* vibration) const;

  rex::ui::Window* window_ = nullptr;

  std::vector<std::unique_ptr<InputDriver>> drivers_;

  std::unique_ptr<DeviceAssignment> assignment_;
  ActiveDeviceTracker active_devices_;

  // Ordered by ordinal. Ordinals are never recycled, so unplugging pad one
  // does not renumber pad two.
  std::vector<DeviceInfo> devices_;
  std::vector<InputDriver*> device_owners_;

  // Written under mutex_; atomic so the getters can read without it.
  std::atomic<uint32_t> connected_users_{0};
  std::atomic<uint32_t> last_used_user_{0};
  // {left, right} stick ranges, scaling the deadzone percentages.
  std::array<std::pair<StickRange, StickRange>, kMaxGuestUsers> user_stick_ranges_ = {};

  // The rest are guarded by mutex_.
  int ui_input_blockers_ = 0;
  // Masked out per user until the guest sees them released.
  std::array<uint16_t, kMaxGuestUsers> consumed_buttons_ = {};
};

/// Create a default InputSystem: GameInput, XInput or SDL by input_backend,
/// then MnK and NOP.
/// In tool mode, only the NOP driver is added.
std::unique_ptr<InputSystem> CreateDefaultInputSystem(bool tool_mode);

}  // namespace rex::input
