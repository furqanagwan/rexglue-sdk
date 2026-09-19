/**
 * @file        input/gameinput/gameinput_input_driver.cpp
 * @brief       GameInput driver, the input API a GDK title is expected to use
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <rex/input/gameinput/gameinput_input_driver.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

#include <GameInput.h>

#include <algorithm>
#include <cmath>
#include <iterator>

#include <rex/cvar.h>
#include <rex/input/flags.h>
#include <rex/logging.h>

namespace rex::input::gameinput {

namespace {

// The high half marks these as GameInput's, the low byte is the slot, so an id
// says which driver owns it without a lookup. 'GI' in the top bytes.
constexpr uint64_t kDeviceTag = 0x47490000ull;

DeviceId DeviceIdForSlot(size_t slot) {
  return static_cast<DeviceId>(kDeviceTag | static_cast<uint64_t>(slot));
}

bool SlotForDevice(DeviceId id, size_t* out_slot) {
  const uint64_t raw = static_cast<uint64_t>(id);
  if ((raw & ~0xFFull) != kDeviceTag || (raw & 0xFF) >= 4) {
    return false;
  }
  *out_slot = static_cast<size_t>(raw & 0xFF);
  return true;
}

struct ButtonMapping {
  GameInputGamepadButtons from;
  uint16_t to;
};

constexpr ButtonMapping kButtons[] = {
    {GameInputGamepadDPadUp, X_INPUT_GAMEPAD_DPAD_UP},
    {GameInputGamepadDPadDown, X_INPUT_GAMEPAD_DPAD_DOWN},
    {GameInputGamepadDPadLeft, X_INPUT_GAMEPAD_DPAD_LEFT},
    {GameInputGamepadDPadRight, X_INPUT_GAMEPAD_DPAD_RIGHT},
    {GameInputGamepadMenu, X_INPUT_GAMEPAD_START},
    {GameInputGamepadView, X_INPUT_GAMEPAD_BACK},
    {GameInputGamepadLeftThumbstick, X_INPUT_GAMEPAD_LEFT_THUMB},
    {GameInputGamepadRightThumbstick, X_INPUT_GAMEPAD_RIGHT_THUMB},
    {GameInputGamepadLeftShoulder, X_INPUT_GAMEPAD_LEFT_SHOULDER},
    {GameInputGamepadRightShoulder, X_INPUT_GAMEPAD_RIGHT_SHOULDER},
    {GameInputGamepadA, X_INPUT_GAMEPAD_A},
    {GameInputGamepadB, X_INPUT_GAMEPAD_B},
    {GameInputGamepadX, X_INPUT_GAMEPAD_X},
    {GameInputGamepadY, X_INPUT_GAMEPAD_Y},
};

// GameInput reports sticks and triggers as floats; the guest expects the
// console's integers.
int16_t ToThumb(float value) {
  const float clamped = std::clamp(value, -1.0f, 1.0f);
  return static_cast<int16_t>(std::lround(clamped * (clamped < 0.0f ? 32768.0f : 32767.0f)));
}

uint8_t ToTrigger(float value) {
  return static_cast<uint8_t>(std::lround(std::clamp(value, 0.0f, 1.0f) * 255.0f));
}

}  // namespace

GameInputInputDriver::GameInputInputDriver(rex::ui::Window* window, size_t window_z_order)
    : InputDriver(window, window_z_order) {}

GameInputInputDriver::~GameInputInputDriver() {
  {
    std::lock_guard<std::mutex> guard(lock_);
    ReleaseSlotsLocked();
    if (game_input_) {
      game_input_->Release();
      game_input_ = nullptr;
    }
  }
  if (module_) {
    FreeLibrary(static_cast<HMODULE>(module_));
    module_ = nullptr;
  }
}

X_STATUS GameInputInputDriver::Setup() {
  // Linking GameInput.lib would stop a GDK build starting at all on a machine
  // without the runtime, which is most of them outside a packaged install.
  HMODULE module = LoadLibraryW(L"GameInput.dll");
  if (!module) {
    REXLOG_INFO("GameInput: GameInput.dll is not present; another backend will be used");
    return X_STATUS_DLL_NOT_FOUND;
  }
  auto create = reinterpret_cast<decltype(&GameInputCreate)>(
      GetProcAddress(module, "GameInputCreate"));
  if (!create) {
    FreeLibrary(module);
    return X_STATUS_PROCEDURE_NOT_FOUND;
  }
  IGameInput* game_input = nullptr;
  const HRESULT result = create(&game_input);
  if (FAILED(result) || !game_input) {
    REXLOG_WARN("GameInput: GameInputCreate failed: {:08X}", static_cast<uint32_t>(result));
    FreeLibrary(module);
    return X_STATUS_UNSUCCESSFUL;
  }
  module_ = module;
  game_input_ = game_input;
  REXLOG_INFO("GameInput: ready");
  return X_STATUS_SUCCESS;
}

void GameInputInputDriver::ReleaseSlotsLocked() {
  for (Slot& slot : slots_) {
    if (slot.device) {
      slot.device->Release();
      slot.device = nullptr;
    }
    slot.buttons = 0;
  }
}

// GameInput hands out a device with each reading rather than a slot number, so
// the console's four slots are kept here. A device holds its slot for as long
// as it keeps producing readings; when it stops, the slot is freed for the
// next one, which is what unplugging a pad looks like to the guest.
//
// A pad can arrive as more than one GameInput device - a wireless controller
// with its own dongle reports both, and only one of them ever carries input.
// Taking them in the order they turn up puts the silent one in slot 0 as often
// as not, and then player one has a pad that reads as all zeros. So a device
// only takes a slot once it has produced a gamepad reading of its own.
void GameInputInputDriver::RefreshSlotsLocked() {
  if (!game_input_) {
    return;
  }
  std::array<bool, kSlotCount> seen{};

  // Collect the devices with a reading this moment. GetNextReading walks
  // forward in time rather than across devices, so several passes are needed
  // to see a second pad; each pass starts from whatever is current.
  IGameInputDevice* candidates[kSlotCount * 2] = {};
  size_t candidate_count = 0;
  IGameInputReading* reading = nullptr;
  if (SUCCEEDED(game_input_->GetCurrentReading(GameInputKindGamepad, nullptr, &reading)) &&
      reading) {
    IGameInputReading* current = reading;
    current->AddRef();
    while (current && candidate_count < std::size(candidates)) {
      IGameInputDevice* device = nullptr;
      current->GetDevice(&device);
      if (device) {
        // A device that cannot hand over a gamepad state is not a pad as far
        // as the guest is concerned, whatever it enumerated as.
        GameInputGamepadState ignored{};
        bool already = false;
        for (size_t i = 0; i < candidate_count; ++i) {
          already = already || candidates[i] == device;
        }
        if (!already && current->GetGamepadState(&ignored)) {
          candidates[candidate_count++] = device;  // reference passes to the array
        } else {
          device->Release();
        }
      }
      IGameInputReading* next = nullptr;
      const HRESULT more =
          game_input_->GetNextReading(current, GameInputKindGamepad, nullptr, &next);
      current->Release();
      current = SUCCEEDED(more) ? next : nullptr;
    }
    if (current) {
      current->Release();
    }
    reading->Release();
  }

  for (size_t c = 0; c < candidate_count; ++c) {
    IGameInputDevice* device = candidates[c];
    size_t slot = kSlotCount;
    for (size_t i = 0; i < kSlotCount; ++i) {
      if (slots_[i].device == device) {
        slot = i;
        break;
      }
    }
    if (slot == kSlotCount) {
      for (size_t i = 0; i < kSlotCount; ++i) {
        if (!slots_[i].device) {
          device->AddRef();
          slots_[i].device = device;
          slot = i;
          break;
        }
      }
    }
    if (slot < kSlotCount) {
      seen[slot] = true;
    }
    device->Release();
  }

  for (size_t i = 0; i < kSlotCount; ++i) {
    if (slots_[i].device && !seen[i] &&
        slots_[i].device->GetDeviceStatus() == GameInputDeviceNoStatus) {
      slots_[i].device->Release();
      slots_[i].device = nullptr;
      slots_[i].buttons = 0;
    }
  }
}

IGameInputDevice* GameInputInputDriver::DeviceForLocked(DeviceId id, size_t* out_slot) {
  size_t slot = 0;
  if (!SlotForDevice(id, &slot)) {
    return nullptr;
  }
  *out_slot = slot;
  return slots_[slot].device;
}

void GameInputInputDriver::EnumerateDevices(std::vector<DeviceInfo>& out) {
  std::lock_guard<std::mutex> guard(lock_);
  RefreshSlotsLocked();
  for (size_t i = 0; i < kSlotCount; ++i) {
    if (!slots_[i].device) {
      continue;
    }
    DeviceInfo info;
    info.id = DeviceIdForSlot(i);
    info.name = "GameInput gamepad " + std::to_string(i + 1);
    info.subtype = XINPUT_DEVSUBTYPE_GAMEPAD;
    info.synthetic = false;
    out.push_back(std::move(info));
  }
}

X_RESULT GameInputInputDriver::GetDeviceState(DeviceId id, X_INPUT_STATE* out_state) {
  if (!out_state) {
    return X_ERROR_BAD_ARGUMENTS;
  }
  std::lock_guard<std::mutex> guard(lock_);
  size_t slot = 0;
  IGameInputDevice* device = DeviceForLocked(id, &slot);
  if (!device || !game_input_) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }
  IGameInputReading* reading = nullptr;
  const HRESULT read_hr = game_input_->GetCurrentReading(GameInputKindGamepad, device, &reading);
  if (FAILED(read_hr) || !reading) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }
  GameInputGamepadState state{};
  const bool have_state = reading->GetGamepadState(&state);
  // The packet number has to change when the state does, or a title that polls
  // on it will never see an input.
  const uint32_t timestamp = static_cast<uint32_t>(reading->GetTimestamp());
  reading->Release();
  if (!have_state) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }

  uint16_t buttons = 0;
  for (const ButtonMapping& mapping : kButtons) {
    if ((state.buttons & mapping.from) != 0) {
      buttons |= mapping.to;
    }
  }
  slots_[slot].buttons = buttons;

  out_state->packet_number = timestamp;
  out_state->gamepad.buttons = buttons;
  out_state->gamepad.left_trigger = ToTrigger(state.leftTrigger);
  out_state->gamepad.right_trigger = ToTrigger(state.rightTrigger);
  out_state->gamepad.thumb_lx = ToThumb(state.leftThumbstickX);
  out_state->gamepad.thumb_ly = ToThumb(state.leftThumbstickY);
  out_state->gamepad.thumb_rx = ToThumb(state.rightThumbstickX);
  out_state->gamepad.thumb_ry = ToThumb(state.rightThumbstickY);
  return X_ERROR_SUCCESS;
}

X_RESULT GameInputInputDriver::GetDeviceCapabilities(DeviceId id, uint32_t /*flags*/,
                                                     X_INPUT_CAPABILITIES* out_caps) {
  if (!out_caps) {
    return X_ERROR_BAD_ARGUMENTS;
  }
  std::lock_guard<std::mutex> guard(lock_);
  size_t slot = 0;
  IGameInputDevice* device = DeviceForLocked(id, &slot);
  if (!device) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }
  const GameInputDeviceInfo* info = device->GetDeviceInfo();

  uint16_t flags = 0;
  if (info && info->supportedRumbleMotors != GameInputRumbleNone) {
    flags |= X_INPUT_CAPS_FFB_SUPPORTED;
  }
  GameInputBatteryState battery{};
  device->GetBatteryState(&battery);
  if (battery.status != GameInputBatteryNotPresent &&
      battery.status != GameInputBatteryUnknown) {
    flags |= X_INPUT_CAPS_WIRELESS;
  }

  out_caps->type = XINPUT_DEVTYPE_GAMEPAD;
  out_caps->sub_type = XINPUT_DEVSUBTYPE_GAMEPAD;
  out_caps->flags = flags;
  // The console reported which inputs exist by setting every bit a full pad
  // has, not by reporting the current reading.
  out_caps->gamepad.buttons = 0xF3FF | (REXCVAR_GET(guide_button) ? X_INPUT_GAMEPAD_GUIDE : 0);
  out_caps->gamepad.left_trigger = 0xFF;
  out_caps->gamepad.right_trigger = 0xFF;
  out_caps->gamepad.thumb_lx = static_cast<int16_t>(0xFFFFu);
  out_caps->gamepad.thumb_ly = static_cast<int16_t>(0xFFFFu);
  out_caps->gamepad.thumb_rx = static_cast<int16_t>(0xFFFFu);
  out_caps->gamepad.thumb_ry = static_cast<int16_t>(0xFFFFu);
  out_caps->vibration.left_motor_speed = 0xFFFF;
  out_caps->vibration.right_motor_speed = 0xFFFF;
  return X_ERROR_SUCCESS;
}

X_RESULT GameInputInputDriver::SetDeviceVibration(DeviceId id, X_INPUT_VIBRATION* vibration) {
  if (!vibration) {
    return X_ERROR_BAD_ARGUMENTS;
  }
  std::lock_guard<std::mutex> guard(lock_);
  size_t slot = 0;
  IGameInputDevice* device = DeviceForLocked(id, &slot);
  if (!device) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }
  GameInputRumbleParams params{};
  if (REXCVAR_GET(vibration)) {
    // The console had two motors; GameInput also drives the trigger motors on
    // pads that have them, which the guest knows nothing about, so they stay
    // at rest rather than being given a share of the guest's two values.
    params.lowFrequency = static_cast<uint16_t>(vibration->left_motor_speed) / 65535.0f;
    params.highFrequency = static_cast<uint16_t>(vibration->right_motor_speed) / 65535.0f;
  }
  device->SetRumbleState(&params);
  return X_ERROR_SUCCESS;
}

X_RESULT GameInputInputDriver::GetDeviceKeystroke(DeviceId id, uint32_t /*flags*/,
                                                  X_INPUT_KEYSTROKE* out_keystroke) {
  if (!out_keystroke) {
    return X_ERROR_BAD_ARGUMENTS;
  }
  std::lock_guard<std::mutex> guard(lock_);
  size_t slot = 0;
  if (!DeviceForLocked(id, &slot)) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }
  // GameInput has no keystroke queue of its own. Titles that use this API read
  // buttons from GetState; reporting nothing is what an empty queue looks like.
  return X_ERROR_EMPTY;
}

X_RESULT GameInputInputDriver::GetDeviceBatteryInformation(
    DeviceId id, uint32_t /*type*/, X_INPUT_BATTERY_INFORMATION* out_battery) {
  if (!out_battery) {
    return X_ERROR_BAD_ARGUMENTS;
  }
  out_battery->type = X_INPUT_BATTERY_TYPE_DISCONNECTED;
  out_battery->level = X_INPUT_BATTERY_LEVEL_EMPTY;

  std::lock_guard<std::mutex> guard(lock_);
  size_t slot = 0;
  IGameInputDevice* device = DeviceForLocked(id, &slot);
  if (!device) {
    return X_ERROR_DEVICE_NOT_CONNECTED;
  }
  GameInputBatteryState battery{};
  device->GetBatteryState(&battery);
  switch (battery.status) {
    case GameInputBatteryNotPresent:
      out_battery->type = X_INPUT_BATTERY_TYPE_WIRED;
      return X_ERROR_SUCCESS;
    case GameInputBatteryDischarging:
    case GameInputBatteryIdle:
    case GameInputBatteryCharging:
      // GameInput does not say what chemistry the cells are either, and the
      // guest does nothing with the distinction.
      out_battery->type = X_INPUT_BATTERY_TYPE_NIMH;
      break;
    default:
      return X_ERROR_DEVICE_NOT_CONNECTED;
  }

  // Real capacities rather than XInput's four steps, so the level is worked
  // out here. A pack that does not report its capacity reads as full, because
  // claiming empty would be a warning the device never gave.
  float fraction = 1.0f;
  if (battery.fullChargeCapacity > 0.0f && battery.remainingCapacity >= 0.0f) {
    fraction = std::clamp(battery.remainingCapacity / battery.fullChargeCapacity, 0.0f, 1.0f);
  }
  if (battery.status == GameInputBatteryCharging) {
    fraction = std::max(fraction, 0.7f);
  }
  out_battery->level = fraction >= 0.7f   ? X_INPUT_BATTERY_LEVEL_FULL
                       : fraction >= 0.4f ? X_INPUT_BATTERY_LEVEL_MEDIUM
                       : fraction >= 0.1f ? X_INPUT_BATTERY_LEVEL_LOW
                                          : X_INPUT_BATTERY_LEVEL_EMPTY;
  return X_ERROR_SUCCESS;
}

}  // namespace rex::input::gameinput
