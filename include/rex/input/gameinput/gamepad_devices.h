/**
 * @file        input/gameinput/gamepad_devices.h
 * @brief       Guest-facing state of the GameInput driver's pads (RG-GDK-020)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <rex/input/device.h>
#include <rex/input/input.h>
#include <rex/input/keystroke_synthesizer.h>
#include <rex/kernel.h>

namespace rex::input::gameinput {

struct Rumble {
  uint16_t left = 0;
  uint16_t right = 0;
  bool operator==(const Rumble&) const = default;
};

struct PadTraits {
  bool wireless = false;
  uint8_t subtype = XINPUT_DEVSUBTYPE_GAMEPAD;

  bool rumble = true;
};

class GamepadDevices {
 public:
  DeviceId Connect(const void* host_device, std::string name, PadTraits traits = {});

  bool Disconnect(const void* host_device);

  const void* HostDevice(DeviceId id) const;
  std::vector<const void*> HostDevices() const;
  void Enumerate(std::vector<DeviceInfo>& out) const;

  void Update(DeviceId id, const X_INPUT_GAMEPAD& gamepad);

  X_RESULT GetState(DeviceId id, bool active, X_INPUT_STATE* out_state);
  X_RESULT GetCapabilities(DeviceId id, bool guide_button, X_INPUT_CAPABILITIES* out_caps) const;
  X_RESULT GetKeystroke(DeviceId id, bool active, uint64_t now_ms,
                        X_INPUT_KEYSTROKE* out_keystroke);

  X_RESULT SetVibration(DeviceId id, const X_INPUT_VIBRATION& vibration, bool active,
                        std::optional<Rumble>* out_apply);

  std::vector<std::pair<const void*, Rumble>> SetActive(bool active);

  static constexpr uint64_t kDeviceIdBase = 0x4749000000000000ull;

 private:
  struct Pad {
    const void* host_device = nullptr;
    DeviceId id = DeviceId::kInvalid;
    std::string name;
    PadTraits traits;
    X_INPUT_STATE state = {};
    bool changed = true;
    bool active = true;
    Rumble requested;
    KeystrokeSynthesizer keystroke;
  };

  Pad* Find(DeviceId id);
  const Pad* Find(DeviceId id) const;

  std::vector<Pad> pads_;
  uint64_t next_id_ = kDeviceIdBase + 1;
  bool active_ = true;
};

}
