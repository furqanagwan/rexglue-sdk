/**
 * @file        input_system_test.cpp
 * @brief       Vibration switch, stick deadzones, dialog input blocking and
 *              connected users in the shared input layer (upstream ReXGlue
 *              3cd7243), which every backend, GameInput first, goes through.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <deque>
#include <map>
#include <memory>

#include <rex/cvar.h>
#include <rex/input/flags.h>
#include <rex/input/input_system.h>
#include <rex/input/state_merge.h>

using rex::X_RESULT;
using rex::X_STATUS;

using rex::input::ApplyStickDeadzone;
using rex::input::DeviceId;
using rex::input::DeviceInfo;
using rex::input::InputDriver;
using rex::input::InputSystem;
using rex::input::PadBattery;
using rex::input::SlotAssignment;
using rex::input::StickRange;
using rex::input::X_INPUT_CAPABILITIES;
using rex::input::X_INPUT_GAMEPAD_A;
using rex::input::X_INPUT_GAMEPAD_B;
using rex::input::X_INPUT_KEYSTROKE;
using rex::input::X_INPUT_STATE;
using rex::input::X_INPUT_VIBRATION;

TEST_CASE("Host menu input never spoofs a pad when no physical backend is available",
          "[input][launch_settings]") {
  const auto original = REXCVAR_GET(input_backend);
  struct Restore {
    std::string value;
    ~Restore() { REXCVAR_SET(input_backend, value); }
  } restore{original};
  // Exercise the no-driver branch without depending on attached hardware.
  REXCVAR_SET(input_backend, "none");
  auto physical = rex::input::CreatePhysicalInputSystem();
  auto guest = rex::input::CreateDefaultInputSystem(true);
  REQUIRE(physical->Setup() == 0);
  REQUIRE(guest->Setup() == 0);
  X_INPUT_STATE state = {};
  CHECK(physical->GetStateForUI(0, &state) != 0);
  CHECK(guest->GetStateForUI(0, &state) == 0);
  physical->Shutdown();
  guest->Shutdown();
}

namespace {

constexpr StickRange kFullRange = {0xFFFF, 0xFFFF};

/// One pad per id, reporting a standard pad's capabilities and recording the
/// last vibration it was sent.
class PadDriver : public InputDriver {
 public:
  PadDriver() : InputDriver(nullptr, 0) {}

  X_STATUS Setup() override { return X_STATUS_SUCCESS; }

  void Add(uint64_t id) {
    DeviceInfo info;
    info.id = static_cast<DeviceId>(id);
    devices_.push_back(info);
    states_[info.id] = {};
  }
  void Remove(uint64_t id) {
    std::erase_if(devices_, [&](const DeviceInfo& d) { return d.id == static_cast<DeviceId>(id); });
    states_.erase(static_cast<DeviceId>(id));
  }
  X_INPUT_STATE& State(uint64_t id) { return states_[static_cast<DeviceId>(id)]; }
  void QueueKeystroke(uint64_t id, uint16_t vk) {
    X_INPUT_KEYSTROKE ks = {};
    ks.virtual_key = vk;
    keystrokes_[static_cast<DeviceId>(id)].push_back(ks);
  }
  size_t PendingKeystrokes(uint64_t id) { return keystrokes_[static_cast<DeviceId>(id)].size(); }

  void EnumerateDevices(std::vector<DeviceInfo>& out) override {
    out.insert(out.end(), devices_.begin(), devices_.end());
  }
  X_RESULT GetDeviceState(DeviceId id, X_INPUT_STATE* out) override {
    auto it = states_.find(id);
    if (it == states_.end()) {
      return X_ERROR_DEVICE_NOT_CONNECTED;
    }
    *out = it->second;
    return X_ERROR_SUCCESS;
  }
  X_RESULT GetDeviceCapabilities(DeviceId id, uint32_t, X_INPUT_CAPABILITIES* out) override {
    if (!states_.count(id)) {
      return X_ERROR_DEVICE_NOT_CONNECTED;
    }
    *out = {};
    out->gamepad.thumb_lx = static_cast<int16_t>(0xFFFFu);
    out->gamepad.thumb_ly = static_cast<int16_t>(0xFFFFu);
    out->gamepad.thumb_rx = static_cast<int16_t>(0xFFFFu);
    out->gamepad.thumb_ry = static_cast<int16_t>(0xFFFFu);
    return X_ERROR_SUCCESS;
  }
  X_RESULT SetDeviceVibration(DeviceId id, X_INPUT_VIBRATION* vibration) override {
    if (!states_.count(id)) {
      return X_ERROR_DEVICE_NOT_CONNECTED;
    }
    last_vibration = *vibration;
    return X_ERROR_SUCCESS;
  }
  X_RESULT GetDeviceKeystroke(DeviceId id, uint32_t, X_INPUT_KEYSTROKE* out) override {
    if (!states_.count(id)) {
      return X_ERROR_DEVICE_NOT_CONNECTED;
    }
    auto& queue = keystrokes_[id];
    if (queue.empty()) {
      return X_ERROR_EMPTY;
    }
    *out = queue.front();
    queue.pop_front();
    return X_ERROR_SUCCESS;
  }

  bool GetDeviceBattery(DeviceId id, PadBattery* out) override {
    auto it = batteries.find(id);
    if (it == batteries.end()) {
      return false;
    }
    *out = it->second;
    return true;
  }

  X_INPUT_VIBRATION last_vibration = {};
  std::map<DeviceId, PadBattery> batteries;

 private:
  std::vector<DeviceInfo> devices_;
  std::map<DeviceId, X_INPUT_STATE> states_;
  std::map<DeviceId, std::deque<X_INPUT_KEYSTROKE>> keystrokes_;
};

struct Harness {
  Harness() {
    auto owned = std::make_unique<PadDriver>();
    driver = owned.get();
    driver->Add(1);
    system = std::make_unique<InputSystem>(nullptr);
    system->AddDriver(std::move(owned));
    system->SetDeviceAssignment(std::make_unique<SlotAssignment>());
  }
  X_INPUT_STATE Read() {
    X_INPUT_STATE state = {};
    REQUIRE(system->GetState(0, &state) == X_ERROR_SUCCESS);
    return state;
  }

  PadDriver* driver = nullptr;
  std::unique_ptr<InputSystem> system;
};

/// Restores a double cvar when the test ends.
class ScopedDeadzones {
 public:
  ScopedDeadzones(double left, double right)
      : left_(REXCVAR_GET(left_stick_deadzone_percentage)),
        right_(REXCVAR_GET(right_stick_deadzone_percentage)) {
    REXCVAR_SET(left_stick_deadzone_percentage, left);
    REXCVAR_SET(right_stick_deadzone_percentage, right);
  }
  ~ScopedDeadzones() {
    REXCVAR_SET(left_stick_deadzone_percentage, left_);
    REXCVAR_SET(right_stick_deadzone_percentage, right_);
  }

 private:
  double left_;
  double right_;
};

}  // namespace

TEST_CASE("Stick deadzones cut every direction, not only up and right", "[input][deadzone]") {
  using Axes = std::pair<int16_t, int16_t>;
  // 0.12 of a standard pad's range is about XInput's own 7849.
  CHECK(ApplyStickDeadzone(0.12, kFullRange, 5000, 0) == Axes{0, 0});
  // Upstream compared against the signed projection and let these through.
  CHECK(ApplyStickDeadzone(0.12, kFullRange, -5000, 0) == Axes{0, 0});
  CHECK(ApplyStickDeadzone(0.12, kFullRange, 0, -5000) == Axes{0, 0});
  CHECK(ApplyStickDeadzone(0.12, kFullRange, -5000, -5000) == Axes{0, 0});
  // Past it, the stick is untouched.
  CHECK(ApplyStickDeadzone(0.12, kFullRange, -30000, 0) == Axes{-30000, 0});
  CHECK(ApplyStickDeadzone(0.12, kFullRange, 0, 32767) == Axes{0, 32767});
  // Off, or out of range: leave the stick alone.
  CHECK(ApplyStickDeadzone(0.0, kFullRange, -5000, 100) == Axes{-5000, 100});
  CHECK(ApplyStickDeadzone(1.0, kFullRange, -5000, 100) == Axes{-5000, 100});
  // A device reporting no range gets no deadzone.
  CHECK(ApplyStickDeadzone(0.12, StickRange{0, 0}, -5000, 100) == Axes{-5000, 100});
}

TEST_CASE("Each stick uses its own deadzone setting", "[input][deadzone]") {
  ScopedDeadzones deadzones(0.12, 0.0);
  Harness h;
  h.driver->State(1).gamepad.thumb_lx = -3000;
  h.driver->State(1).gamepad.thumb_rx = -3000;
  X_INPUT_STATE state = h.Read();
  CHECK(int16_t(state.gamepad.thumb_lx) == 0);
  CHECK(int16_t(state.gamepad.thumb_rx) == -3000);
}

TEST_CASE("Turning vibration off stops the motors the guest asks for", "[input][vibration]") {
  const bool saved = REXCVAR_GET(vibration);
  Harness h;
  X_INPUT_VIBRATION request = {};
  request.left_motor_speed = 40000;
  request.right_motor_speed = 20000;

  REXCVAR_SET(vibration, true);
  REQUIRE(h.system->SetState(0, &request) == X_ERROR_SUCCESS);
  CHECK(uint16_t(h.driver->last_vibration.left_motor_speed) == 40000);
  CHECK(uint16_t(h.driver->last_vibration.right_motor_speed) == 20000);

  REXCVAR_SET(vibration, false);
  // Still a success: the pad is there, it just does not buzz.
  REQUIRE(h.system->SetState(0, &request) == X_ERROR_SUCCESS);
  CHECK(uint16_t(h.driver->last_vibration.left_motor_speed) == 0);
  CHECK(uint16_t(h.driver->last_vibration.right_motor_speed) == 0);
  // The guest's own request is not rewritten.
  CHECK(uint16_t(request.left_motor_speed) == 40000);

  // Toggling silences a running motor at once.
  REXCVAR_SET(vibration, true);
  REQUIRE(h.system->SetState(0, &request) == X_ERROR_SUCCESS);
  h.system->ToggleVibration();
  CHECK_FALSE(h.system->GetVibrationEnabled());
  CHECK(uint16_t(h.driver->last_vibration.left_motor_speed) == 0);
  REXCVAR_SET(vibration, saved);
}

TEST_CASE("A dialog holds the pad and the press that closes it", "[input][ui_block]") {
  Harness h;
  h.driver->State(1).gamepad.buttons = X_INPUT_GAMEPAD_B;
  CHECK(uint16_t(h.Read().gamepad.buttons) == X_INPUT_GAMEPAD_B);

  h.system->AddUIInputBlocker();
  // The guest sees an untouched pad; the dialog still reads the real one.
  CHECK(uint16_t(h.Read().gamepad.buttons) == 0);
  X_INPUT_STATE ui = {};
  REQUIRE(h.system->GetStateForUI(0, &ui) == X_ERROR_SUCCESS);
  CHECK(uint16_t(ui.gamepad.buttons) == X_INPUT_GAMEPAD_B);

  // A is pressed to dismiss, and still held as the dialog closes.
  h.driver->State(1).gamepad.buttons = X_INPUT_GAMEPAD_A;
  h.system->RemoveUIInputBlocker();
  CHECK(uint16_t(h.Read().gamepad.buttons) == 0);
  // Other buttons pressed meanwhile get through.
  h.driver->State(1).gamepad.buttons = X_INPUT_GAMEPAD_A | X_INPUT_GAMEPAD_B;
  CHECK(uint16_t(h.Read().gamepad.buttons) == X_INPUT_GAMEPAD_B);
  // A counts again once released and pressed anew.
  h.driver->State(1).gamepad.buttons = 0;
  CHECK(uint16_t(h.Read().gamepad.buttons) == 0);
  h.driver->State(1).gamepad.buttons = X_INPUT_GAMEPAD_A;
  CHECK(uint16_t(h.Read().gamepad.buttons) == X_INPUT_GAMEPAD_A);
}

TEST_CASE("Nested dialogs hold input until the last one closes", "[input][ui_block]") {
  Harness h;
  h.driver->State(1).gamepad.thumb_lx = 20000;
  h.system->AddUIInputBlocker();
  h.system->AddUIInputBlocker();
  h.system->RemoveUIInputBlocker();
  CHECK(int16_t(h.Read().gamepad.thumb_lx) == 0);
  h.system->RemoveUIInputBlocker();
  CHECK(int16_t(h.Read().gamepad.thumb_lx) == 20000);
  // An unmatched remove does not unbalance the count.
  h.system->RemoveUIInputBlocker();
  h.system->AddUIInputBlocker();
  CHECK(int16_t(h.Read().gamepad.thumb_lx) == 0);
  h.system->RemoveUIInputBlocker();
}

TEST_CASE("Keystrokes made during a dialog stay with the dialog", "[input][ui_block]") {
  Harness h;
  X_INPUT_KEYSTROKE keystroke = {};
  h.system->AddUIInputBlocker();
  h.driver->QueueKeystroke(1, 0x5800);  // VK_PAD_A
  CHECK(h.system->GetKeystroke(0, 0, &keystroke) == X_ERROR_EMPTY);
  // Ones the guest never polled for are spent when the dialog closes.
  h.driver->QueueKeystroke(1, 0x5800);
  h.system->RemoveUIInputBlocker();
  CHECK(h.driver->PendingKeystrokes(1) == 0);
  CHECK(h.system->GetKeystroke(0, 0, &keystroke) == X_ERROR_EMPTY);
  h.driver->QueueKeystroke(1, 0x5801);  // VK_PAD_B
  REQUIRE(h.system->GetKeystroke(0, 0, &keystroke) == X_ERROR_SUCCESS);
  CHECK(uint16_t(keystroke.virtual_key) == 0x5801);
}

TEST_CASE("Connected users follow pads coming and going", "[input][hotplug]") {
  Harness h;
  CHECK(h.system->GetConnectedUsers().none());
  h.Read();
  CHECK(h.system->GetConnectedUsers().to_ulong() == 0b1);

  h.driver->Add(2);
  X_INPUT_STATE state = {};
  state.gamepad.buttons = 0;
  h.driver->State(2).gamepad.buttons = X_INPUT_GAMEPAD_A;
  REQUIRE(h.system->GetState(1, &state) == X_ERROR_SUCCESS);
  CHECK(h.system->GetConnectedUsers().to_ulong() == 0b11);
  CHECK(h.system->GetLastUsedUser() == 1);

  h.driver->Remove(1);
  CHECK(h.system->GetState(0, &state) == X_ERROR_DEVICE_NOT_CONNECTED);
  CHECK(h.system->GetConnectedUsers().to_ulong() == 0b10);
}

TEST_CASE("GetBattery reports the power of the user's pad", "[input]") {
  Harness h;
  PadBattery battery;
  // The driver cannot tell.
  CHECK_FALSE(h.system->GetBattery(0, &battery));

  h.driver->batteries[static_cast<DeviceId>(1)] = {.wireless = true, .percent = 83};
  REQUIRE(h.system->GetBattery(0, &battery));
  CHECK(battery.wireless);
  CHECK(battery.percent == 83);
  CHECK_FALSE(battery.charging);

  // No pad for user 1, and none for user 0 once it is unplugged.
  CHECK_FALSE(h.system->GetBattery(1, &battery));
  h.driver->Remove(1);
  CHECK_FALSE(h.system->GetBattery(0, &battery));
  CHECK_FALSE(h.system->GetBattery(0, nullptr));
}
