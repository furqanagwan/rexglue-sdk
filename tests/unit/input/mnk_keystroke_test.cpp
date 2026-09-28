/**
 * @file        mnk_keystroke_test.cpp
 * @brief       Keyboard keystrokes: bound pad keys and raw passthrough
 *              (upstream ReXGlue 3f34ffc). Key events arrive the same way from
 *              the Win32 and SDL windows, so these hold for both.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <string>
#include <vector>

#include <rex/cvar.h>
#include <rex/input/mnk/mnk_input_driver.h>
#include <rex/ui/ui_event.h>
#include <rex/ui/virtual_key.h>

REXCVAR_DECLARE(bool, mnk_mode);
REXCVAR_DECLARE(bool, mnk_passthrough);
REXCVAR_DECLARE(std::string, keybind_a);

using rex::X_RESULT;
using rex::X_STATUS;

using namespace rex::input;  // NOLINT
using rex::input::mnk::MnkInputDriver;
using rex::ui::KeyEvent;
using rex::ui::VirtualKey;

namespace {

class ScopedMnk {
 public:
  ScopedMnk(bool mode, bool passthrough)
      : mode_(REXCVAR_GET(mnk_mode)),
        passthrough_(REXCVAR_GET(mnk_passthrough)),
        keybind_a_(REXCVAR_GET(keybind_a)) {
    REXCVAR_SET(mnk_mode, mode);
    REXCVAR_SET(mnk_passthrough, passthrough);
    REXCVAR_SET(keybind_a, std::string("Space"));
  }
  ~ScopedMnk() {
    REXCVAR_SET(mnk_mode, mode_);
    REXCVAR_SET(mnk_passthrough, passthrough_);
    REXCVAR_SET(keybind_a, keybind_a_);
  }

 private:
  bool mode_;
  bool passthrough_;
  std::string keybind_a_;
};

KeyEvent Key(VirtualKey vk, bool repeat = false, bool shift = false) {
  return KeyEvent(nullptr, vk, 1, repeat, shift, false, false, false);
}

DeviceId Device(MnkInputDriver& driver) {
  std::vector<DeviceInfo> devices;
  driver.EnumerateDevices(devices);
  REQUIRE(devices.size() == 1);
  return devices[0].id;
}

std::vector<X_INPUT_KEYSTROKE> Drain(MnkInputDriver& driver, DeviceId id) {
  std::vector<X_INPUT_KEYSTROKE> out;
  X_INPUT_KEYSTROKE ks = {};
  while (driver.GetDeviceKeystroke(id, 0, &ks) == X_ERROR_SUCCESS) {
    out.push_back(ks);
  }
  return out;
}

}  // namespace

TEST_CASE("A bound key produces its pad button's keystrokes", "[input][mnk]") {
  ScopedMnk cvars(/*mode=*/true, /*passthrough=*/false);
  MnkInputDriver driver(nullptr, 0);
  DeviceId id = Device(driver);

  auto down = Key(VirtualKey::kSpace);
  driver.OnKeyDown(down);
  // OS auto-repeat of a held key is not a second press.
  auto repeat = Key(VirtualKey::kSpace, /*repeat=*/true);
  driver.OnKeyDown(repeat);
  auto up = Key(VirtualKey::kSpace);
  driver.OnKeyUp(up);

  auto keystrokes = Drain(driver, id);
  REQUIRE(keystrokes.size() == 2);
  CHECK(uint16_t(keystrokes[0].virtual_key) == uint16_t(VirtualKey::kXInputPadA));
  CHECK(uint16_t(keystrokes[0].flags) == X_INPUT_KEYSTROKE_KEYDOWN);
  CHECK(uint16_t(keystrokes[1].virtual_key) == uint16_t(VirtualKey::kXInputPadA));
  CHECK(uint16_t(keystrokes[1].flags) == X_INPUT_KEYSTROKE_KEYUP);

  // An unbound key says nothing.
  auto other = Key(VirtualKey::kF7);
  driver.OnKeyDown(other);
  CHECK(Drain(driver, id).empty());
}

TEST_CASE("Passthrough hands the guest a USB keyboard", "[input][mnk]") {
  ScopedMnk cvars(/*mode=*/false, /*passthrough=*/true);
  MnkInputDriver driver(nullptr, 0);
  DeviceId id = Device(driver);

  X_INPUT_CAPABILITIES caps = {};
  REQUIRE(driver.GetDeviceCapabilities(id, 0, &caps) == X_ERROR_SUCCESS);
  CHECK(caps.type == XINPUT_DEVTYPE_KEYBOARD);
  CHECK(caps.sub_type == XINPUT_DEVSUBTYPE_USB_KEYBOARD);
  // Not a pad, so a real controller keeps the guest user.
  X_INPUT_STATE state = {};
  CHECK(driver.GetDeviceState(id, &state) == X_ERROR_DEVICE_NOT_CONNECTED);

  auto down = Key(VirtualKey::kA, false, /*shift=*/true);
  driver.OnKeyDown(down);
  // The character follows its key-down, as WM_CHAR does.
  auto chr = Key(VirtualKey('A'));
  driver.OnKeyChar(chr);
  auto repeat = Key(VirtualKey::kA, /*repeat=*/true);
  driver.OnKeyDown(repeat);
  auto up = Key(VirtualKey::kA);
  driver.OnKeyUp(up);

  auto keystrokes = Drain(driver, id);
  REQUIRE(keystrokes.size() == 3);
  CHECK(uint16_t(keystrokes[0].virtual_key) == uint16_t(VirtualKey::kA));
  CHECK(keystrokes[0].hid_code == 0x04);  // USB HID usage for A
  CHECK(uint16_t(keystrokes[0].flags) ==
        (X_INPUT_KEYSTROKE_KEYDOWN | X_INPUT_KEYSTROKE_SHIFT | X_INPUT_KEYSTROKE_VALIDUNICODE));
  CHECK(uint16_t(keystrokes[0].unicode) == 'A');
  CHECK(uint16_t(keystrokes[1].flags) == (X_INPUT_KEYSTROKE_KEYDOWN | X_INPUT_KEYSTROKE_REPEAT));
  CHECK(uint16_t(keystrokes[2].flags) == X_INPUT_KEYSTROKE_KEYUP);
}

TEST_CASE("Unread keystrokes cannot grow without bound", "[input][mnk]") {
  ScopedMnk cvars(/*mode=*/false, /*passthrough=*/true);
  MnkInputDriver driver(nullptr, 0);
  DeviceId id = Device(driver);
  for (int i = 0; i < 1000; i++) {
    auto down = Key(VirtualKey::kB);
    driver.OnKeyDown(down);
  }
  CHECK(Drain(driver, id).size() == 256);
}
