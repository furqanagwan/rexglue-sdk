/**
 * @file        gamepad_devices_test.cpp
 * @brief       GameInput driver semantics without devices (RG-GDK-020)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <vector>

#include <rex/input/device_assignment.h>
#include <rex/input/gameinput/gamepad_devices.h>
#include <rex/input/input_system.h>
#include <rex/ui/virtual_key.h>

using rex::X_RESULT;
using rex::X_STATUS;

using namespace rex::input;  // NOLINT
using rex::input::gameinput::GamepadDevices;
using rex::input::gameinput::Rumble;

namespace {

// The GameInput driver with GameInput replaced by test calls: host devices
// are addresses of HostPad objects, and rumble sent to them is recorded.
struct HostPad {
  X_INPUT_GAMEPAD gamepad = {};
  std::vector<Rumble> rumble;
};

class TableDriver : public InputDriver {
 public:
  TableDriver() : InputDriver(nullptr, 0) {}
  X_STATUS Setup() override { return X_STATUS_SUCCESS; }

  DeviceId Plug(HostPad* host) { return devices_.Connect(host, "test pad", false); }
  void Unplug(HostPad* host) { devices_.Disconnect(host); }

  void EnumerateDevices(std::vector<DeviceInfo>& out) override { devices_.Enumerate(out); }

  X_RESULT GetDeviceState(DeviceId id, X_INPUT_STATE* out) override {
    bool active = Active();
    if (active) {
      Poll(id);
    }
    return devices_.GetState(id, active, out);
  }
  X_RESULT GetDeviceCapabilities(DeviceId id, uint32_t, X_INPUT_CAPABILITIES* out) override {
    return devices_.GetCapabilities(id, false, out);
  }
  X_RESULT SetDeviceVibration(DeviceId id, X_INPUT_VIBRATION* vibration) override {
    std::optional<Rumble> apply;
    X_RESULT result = devices_.SetVibration(id, *vibration, Active(), &apply);
    if (apply) {
      Host(devices_.HostDevice(id))->rumble.push_back(*apply);
    }
    return result;
  }
  X_RESULT GetDeviceKeystroke(DeviceId id, uint32_t, X_INPUT_KEYSTROKE* out) override {
    bool active = Active();
    if (active) {
      Poll(id);
    }
    return devices_.GetKeystroke(id, active, now_ms, out);
  }

  uint64_t now_ms = 1000;

 private:
  static HostPad* Host(const void* key) {
    return const_cast<HostPad*>(static_cast<const HostPad*>(key));
  }
  bool Active() {
    bool active = is_active();
    for (const auto& [key, rumble] : devices_.SetActive(active)) {
      Host(key)->rumble.push_back(rumble);
    }
    return active;
  }
  void Poll(DeviceId id) {
    if (const void* key = devices_.HostDevice(id)) {
      devices_.Update(id, Host(key)->gamepad);
    }
  }

  GamepadDevices devices_;
};

struct Harness {
  Harness() {
    auto owned = std::make_unique<TableDriver>();
    driver = owned.get();
    system = std::make_unique<InputSystem>(nullptr);
    system->AddDriver(std::move(owned));
    system->SetDeviceAssignment(std::make_unique<SlotAssignment>());
    system->SetActiveCallback([this] { return active; });
  }

  // Buttons user `user` sees, or nullopt when nothing is connected there.
  std::optional<uint16_t> Buttons(uint32_t user) {
    X_INPUT_STATE state = {};
    if (system->GetState(user, &state) != X_ERROR_SUCCESS) {
      return std::nullopt;
    }
    return uint16_t(state.gamepad.buttons);
  }
  uint32_t Packet(uint32_t user) {
    X_INPUT_STATE state = {};
    REQUIRE(system->GetState(user, &state) == X_ERROR_SUCCESS);
    return state.packet_number;
  }

  TableDriver* driver = nullptr;
  std::unique_ptr<InputSystem> system;
  bool active = true;
};

}  // namespace

TEST_CASE("Four GameInput pads map to four guest users in connection order", "[input][gameinput]") {
  Harness h;
  HostPad pads[4];
  for (HostPad& pad : pads) {
    h.driver->Plug(&pad);
  }
  pads[0].gamepad.buttons = X_INPUT_GAMEPAD_A;
  pads[1].gamepad.buttons = X_INPUT_GAMEPAD_B;
  pads[2].gamepad.buttons = X_INPUT_GAMEPAD_X;
  pads[3].gamepad.buttons = X_INPUT_GAMEPAD_Y;
  CHECK(h.Buttons(0) == X_INPUT_GAMEPAD_A);
  CHECK(h.Buttons(1) == X_INPUT_GAMEPAD_B);
  CHECK(h.Buttons(2) == X_INPUT_GAMEPAD_X);
  CHECK(h.Buttons(3) == X_INPUT_GAMEPAD_Y);
}

TEST_CASE("Unplugging a GameInput pad keeps the others on their users", "[input][gameinput]") {
  Harness h;
  HostPad pads[4];
  uint16_t buttons[4] = {X_INPUT_GAMEPAD_A, X_INPUT_GAMEPAD_B, X_INPUT_GAMEPAD_X,
                         X_INPUT_GAMEPAD_Y};
  for (int i = 0; i < 4; i++) {
    h.driver->Plug(&pads[i]);
    pads[i].gamepad.buttons = buttons[i];
  }
  REQUIRE(h.Buttons(1) == X_INPUT_GAMEPAD_B);

  h.driver->Unplug(&pads[1]);
  CHECK(h.Buttons(0) == X_INPUT_GAMEPAD_A);
  CHECK(h.Buttons(1) == std::nullopt);  // no phantom input from the removed pad
  CHECK(h.Buttons(2) == X_INPUT_GAMEPAD_X);
  CHECK(h.Buttons(3) == X_INPUT_GAMEPAD_Y);

  SECTION("the same pad reconnects to the freed user, with a fresh state") {
    pads[1].gamepad.buttons = 0;
    h.driver->Plug(&pads[1]);
    CHECK(h.Buttons(1) == 0);
    CHECK(h.Packet(1) == 1);
  }
  SECTION("a different pad takes the freed user") {
    HostPad other;
    other.gamepad.buttons = X_INPUT_GAMEPAD_START;
    h.driver->Plug(&other);
    CHECK(h.Buttons(1) == X_INPUT_GAMEPAD_START);
    CHECK(h.Buttons(2) == X_INPUT_GAMEPAD_X);
  }
}

TEST_CASE("GameInput packet numbers advance once per change the guest can see",
          "[input][gameinput]") {
  Harness h;
  HostPad pad;
  h.driver->Plug(&pad);
  CHECK(h.Packet(0) == 1);
  CHECK(h.Packet(0) == 1);  // unchanged reading
  pad.gamepad.thumb_lx = 1000;
  pad.gamepad.thumb_lx = 2000;  // two host updates between polls count once
  CHECK(h.Packet(0) == 2);
  h.active = false;
  CHECK(h.Packet(0) == 3);  // focus loss is a change
  pad.gamepad.buttons = X_INPUT_GAMEPAD_A;
  CHECK(h.Packet(0) == 3);  // input while unfocused is not seen
  h.active = true;
  CHECK(h.Packet(0) == 4);
}

TEST_CASE("An unfocused GameInput pad reads untouched and keeps held buttons",
          "[input][gameinput]") {
  Harness h;
  HostPad pad;
  h.driver->Plug(&pad);
  pad.gamepad.buttons = X_INPUT_GAMEPAD_A;
  pad.gamepad.right_trigger = 200;
  REQUIRE(h.Buttons(0) == X_INPUT_GAMEPAD_A);
  h.active = false;
  X_INPUT_STATE state = {};
  REQUIRE(h.system->GetState(0, &state) == X_ERROR_SUCCESS);
  CHECK(uint16_t(state.gamepad.buttons) == 0);
  CHECK(state.gamepad.right_trigger == 0);
  h.active = true;
  CHECK(h.Buttons(0) == X_INPUT_GAMEPAD_A);
}

TEST_CASE("GameInput rumble holds, stops on focus loss and resumes on focus",
          "[input][gameinput]") {
  Harness h;
  HostPad pad;
  h.driver->Plug(&pad);
  X_INPUT_VIBRATION vibration = {};
  vibration.left_motor_speed = 0x8000;
  vibration.right_motor_speed = 0x1000;
  REQUIRE(h.system->SetState(0, &vibration) == X_ERROR_SUCCESS);
  REQUIRE(pad.rumble.size() == 1);
  CHECK(pad.rumble.back() == Rumble{0x8000, 0x1000});

  h.active = false;
  REQUIRE(h.Buttons(0).has_value());
  REQUIRE(pad.rumble.size() == 2);
  CHECK(pad.rumble.back() == Rumble{});

  // A request while unfocused is remembered, not played.
  vibration.left_motor_speed = 0x4000;
  REQUIRE(h.system->SetState(0, &vibration) == X_ERROR_SUCCESS);
  CHECK(pad.rumble.size() == 2);

  h.active = true;
  REQUIRE(h.Buttons(0).has_value());
  REQUIRE(pad.rumble.size() == 3);
  CHECK(pad.rumble.back() == Rumble{0x4000, 0x1000});
}

TEST_CASE("GameInput rumble does not survive a disconnect", "[input][gameinput]") {
  Harness h;
  HostPad pad;
  h.driver->Plug(&pad);
  X_INPUT_VIBRATION vibration = {};
  vibration.left_motor_speed = 0xFFFF;
  REQUIRE(h.system->SetState(0, &vibration) == X_ERROR_SUCCESS);
  h.driver->Unplug(&pad);
  CHECK(h.system->SetState(0, &vibration) == X_ERROR_DEVICE_NOT_CONNECTED);

  h.driver->Plug(&pad);
  pad.rumble.clear();
  // A focus cycle replays only what the guest asked of the new connection.
  h.active = false;
  REQUIRE(h.Buttons(0).has_value());
  h.active = true;
  REQUIRE(h.Buttons(0).has_value());
  CHECK(pad.rumble.empty());
}

TEST_CASE("GameInput keystrokes release on focus loss", "[input][gameinput]") {
  Harness h;
  HostPad pad;
  h.driver->Plug(&pad);
  pad.gamepad.buttons = X_INPUT_GAMEPAD_A;
  X_INPUT_KEYSTROKE keystroke = {};
  REQUIRE(h.system->GetKeystroke(0, 0, &keystroke) == X_ERROR_SUCCESS);
  CHECK(uint16_t(keystroke.virtual_key) == uint16_t(rex::ui::VirtualKey::kXInputPadA));
  CHECK(uint16_t(keystroke.flags) == X_INPUT_KEYSTROKE_KEYDOWN);
  h.active = false;
  REQUIRE(h.system->GetKeystroke(0, 0, &keystroke) == X_ERROR_SUCCESS);
  CHECK(uint16_t(keystroke.flags) == X_INPUT_KEYSTROKE_KEYUP);
  CHECK(h.system->GetKeystroke(0, 0, &keystroke) == X_ERROR_EMPTY);
}

TEST_CASE("GameInput pads report a wired or wireless standard gamepad", "[input][gameinput]") {
  GamepadDevices devices;
  int a = 0, b = 0;
  DeviceId wired = devices.Connect(&a, "wired", false);
  DeviceId wireless = devices.Connect(&b, "wireless", true);
  X_INPUT_CAPABILITIES caps = {};
  REQUIRE(devices.GetCapabilities(wired, false, &caps) == X_ERROR_SUCCESS);
  CHECK(caps.type == 1);
  CHECK(caps.sub_type == 1);
  CHECK(uint16_t(caps.flags) == 0);
  CHECK(uint16_t(caps.gamepad.buttons) == 0xF3FF);
  REQUIRE(devices.GetCapabilities(wireless, true, &caps) == X_ERROR_SUCCESS);
  CHECK(uint16_t(caps.flags) == X_INPUT_CAPS_WIRELESS);
  CHECK(uint16_t(caps.gamepad.buttons) == (0xF3FF | X_INPUT_GAMEPAD_GUIDE));
  CHECK((static_cast<uint64_t>(wired) >> 48) == 0x4749);
  CHECK(wired != wireless);
}
