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

// Motor speeds to send to a host device, in XInput's 0-65535 range.
struct Rumble {
  uint16_t left = 0;
  uint16_t right = 0;
  bool operator==(const Rumble&) const = default;
};

// Everything the GameInput driver tells the guest, kept apart from GameInput
// itself so the XInput semantics are testable without devices or the GDK:
// device identity across connect/disconnect, packet numbers, the untouched
// pad while unfocused, keystrokes, and rumble that holds until the guest
// changes it but stops while unfocused and never outlives a disconnect.
// Host devices are opaque keys (the driver uses IGameInputDevice pointers).
// Not thread-safe; the driver serializes access.
class GamepadDevices {
 public:
  // A newly connected host device gets a new DeviceId, even when the same
  // device reconnects, so no state from before the disconnect reaches the
  // guest. InputSystem decides which guest user the new id becomes.
  DeviceId Connect(const void* host_device, std::string name, bool wireless);
  // Returns false for an unknown device. The id is gone afterwards: every
  // query for it reports X_ERROR_DEVICE_NOT_CONNECTED.
  bool Disconnect(const void* host_device);

  const void* HostDevice(DeviceId id) const;
  std::vector<const void*> HostDevices() const;
  void Enumerate(std::vector<DeviceInfo>& out) const;

  // Stores the host's latest reading.
  void Update(DeviceId id, const X_INPUT_GAMEPAD& gamepad);

  // `active` false (window unfocused, overlay open) reports an untouched pad.
  // The packet number advances once per change seen by the guest, including
  // focus changes, and starts at 1 for a new device.
  X_RESULT GetState(DeviceId id, bool active, X_INPUT_STATE* out_state);
  X_RESULT GetCapabilities(DeviceId id, bool guide_button, X_INPUT_CAPABILITIES* out_caps) const;
  X_RESULT GetKeystroke(DeviceId id, bool active, uint64_t now_ms,
                        X_INPUT_KEYSTROKE* out_keystroke);

  // Records the guest's request. Returns the rumble to apply to the host
  // device now: the request while active, nothing while inactive (the
  // motors are already stopped and resume on SetActive(true)).
  X_RESULT SetVibration(DeviceId id, const X_INPUT_VIBRATION& vibration, bool active,
                        std::optional<Rumble>* out_apply);

  // Focus transitions. Returns the host devices whose motors must change:
  // stopped on losing focus, back to the guest's request on regaining it.
  std::vector<std::pair<const void*, Rumble>> SetActive(bool active);

  static constexpr uint64_t kDeviceIdBase = 0x4749000000000000ull;  // "GI"

 private:
  struct Pad {
    const void* host_device = nullptr;
    DeviceId id = DeviceId::kInvalid;
    std::string name;
    bool wireless = false;
    X_INPUT_STATE state = {};
    bool changed = true;  // XInput starts with packet_number = 1
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

}  // namespace rex::input::gameinput
