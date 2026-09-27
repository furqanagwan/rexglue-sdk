/**
 * @file        input/gameinput/gamepad_devices.cpp
 * @brief       Guest-facing state of the GameInput driver's pads (RG-GDK-020)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/input/gameinput/gamepad_devices.h>

#include <algorithm>
#include <cstring>

namespace rex::input::gameinput {

DeviceId GamepadDevices::Connect(const void* host_device, std::string name, bool wireless) {
  Disconnect(host_device);
  Pad pad;
  pad.host_device = host_device;
  pad.id = static_cast<DeviceId>(next_id_++);
  pad.name = std::move(name);
  pad.wireless = wireless;
  pad.active = active_;
  pads_.push_back(std::move(pad));
  return pads_.back().id;
}

bool GamepadDevices::Disconnect(const void* host_device) {
  auto it = std::find_if(pads_.begin(), pads_.end(),
                         [&](const Pad& pad) { return pad.host_device == host_device; });
  if (it == pads_.end()) {
    return false;
  }
  pads_.erase(it);
  return true;
}

const void* GamepadDevices::HostDevice(DeviceId id) const {
  const Pad* pad = Find(id);
  return pad ? pad->host_device : nullptr;
}

std::vector<const void*> GamepadDevices::HostDevices() const {
  std::vector<const void*> out;
  for (const Pad& pad : pads_) {
    out.push_back(pad.host_device);
  }
  return out;
}

void GamepadDevices::Enumerate(std::vector<DeviceInfo>& out) const {
  for (const Pad& pad : pads_) {
    DeviceInfo info;
    info.id = pad.id;
    info.name = pad.name;
    info.synthetic = false;
    out.push_back(info);
  }
}

void GamepadDevices::Update(DeviceId id, const X_INPUT_GAMEPAD& gamepad) {
  Pad* pad = Find(id);
  if (!pad) {
    return;
  }
  if (std::memcmp(&pad->state.gamepad, &gamepad, sizeof(gamepad)) != 0) {
    pad->state.gamepad = gamepad;
    pad->changed = true;
  }
}

X_RESULT GamepadDevices::GetState(DeviceId id, bool active, X_INPUT_STATE* out_state) {
  Pad* pad = Find(id);
  if (!pad) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }
  if (active != pad->active || (active && pad->changed)) {
    pad->state.packet_number = pad->state.packet_number + 1;
    pad->active = active;
    pad->changed = false;
  }
  *out_state = pad->state;
  if (!active) {
    // Held buttons are kept and show again once active.
    std::memset(&out_state->gamepad, 0, sizeof(out_state->gamepad));
  }
  return X_ERROR_SUCCESS;
}

X_RESULT GamepadDevices::GetCapabilities(DeviceId id, bool guide_button,
                                         X_INPUT_CAPABILITIES* out_caps) const {
  const Pad* pad = Find(id);
  if (!pad) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }
  // Same report as the SDL driver: a standard gamepad with every input.
  // GameInput exposes no XInput subtype, so instruments are not identified.
  X_INPUT_CAPABILITIES caps = {};
  caps.type = 0x01;      // XINPUT_DEVTYPE_GAMEPAD
  caps.sub_type = 0x01;  // XINPUT_DEVSUBTYPE_GAMEPAD
  caps.flags = pad->wireless ? uint16_t(X_INPUT_CAPS_WIRELESS) : uint16_t(0);
  caps.gamepad.buttons = uint16_t(0xF3FF | (guide_button ? X_INPUT_GAMEPAD_GUIDE : 0));
  caps.gamepad.left_trigger = 0xFF;
  caps.gamepad.right_trigger = 0xFF;
  caps.gamepad.thumb_lx = static_cast<int16_t>(0xFFFFu);
  caps.gamepad.thumb_ly = static_cast<int16_t>(0xFFFFu);
  caps.gamepad.thumb_rx = static_cast<int16_t>(0xFFFFu);
  caps.gamepad.thumb_ry = static_cast<int16_t>(0xFFFFu);
  caps.vibration.left_motor_speed = 0xFFFFu;
  caps.vibration.right_motor_speed = 0xFFFFu;
  *out_caps = caps;
  return X_ERROR_SUCCESS;
}

X_RESULT GamepadDevices::GetKeystroke(DeviceId id, bool active, uint64_t now_ms,
                                      X_INPUT_KEYSTROKE* out_keystroke) {
  Pad* pad = Find(id);
  if (!pad) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }
  return pad->keystroke.Next(pad->state.gamepad, active, now_ms, out_keystroke);
}

X_RESULT GamepadDevices::SetVibration(DeviceId id, const X_INPUT_VIBRATION& vibration, bool active,
                                      std::optional<Rumble>* out_apply) {
  out_apply->reset();
  Pad* pad = Find(id);
  if (!pad) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }
  pad->requested = {vibration.left_motor_speed, vibration.right_motor_speed};
  if (active) {
    *out_apply = pad->requested;
  }
  return X_ERROR_SUCCESS;
}

std::vector<std::pair<const void*, Rumble>> GamepadDevices::SetActive(bool active) {
  std::vector<std::pair<const void*, Rumble>> out;
  if (active == active_) {
    return out;
  }
  active_ = active;
  for (const Pad& pad : pads_) {
    if (pad.requested != Rumble{}) {
      out.emplace_back(pad.host_device, active ? pad.requested : Rumble{});
    }
  }
  return out;
}

GamepadDevices::Pad* GamepadDevices::Find(DeviceId id) {
  for (Pad& pad : pads_) {
    if (pad.id == id) {
      return &pad;
    }
  }
  return nullptr;
}

const GamepadDevices::Pad* GamepadDevices::Find(DeviceId id) const {
  for (const Pad& pad : pads_) {
    if (pad.id == id) {
      return &pad;
    }
  }
  return nullptr;
}

}  // namespace rex::input::gameinput
