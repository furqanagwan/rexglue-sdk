/**
 * @file        input/gameinput/gameinput_input_driver.cpp
 * @brief       Native GameInput gamepad driver, GDK builds only (RG-GDK-020)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include "gameinput_input_driver.h"

#include <algorithm>

#include <fmt/format.h>

#include <rex/chrono/clock.h>
#include <rex/input/flags.h>
#include <rex/logging.h>

#include "gameinput_mapping.h"

namespace rex::input::gameinput {

namespace {

constexpr uint64_t kUnregisterTimeoutUs = 5'000'000;

void StopRumble(IGameInputDevice* device) {
  GameInputRumbleParams stop = {};
  device->SetRumbleState(&stop);
}

std::string DeviceName(IGameInputDevice* device) {
  const GameInputDeviceInfo* info = device->GetDeviceInfo();
  const char* family = "HID";
  switch (info->deviceFamily) {
    case GameInputFamilyXboxOne:
      family = "Xbox One";
      break;
    case GameInputFamilyXbox360:
      family = "Xbox 360";
      break;
    case GameInputFamilyVirtual:
      family = "Virtual";
      break;
    default:
      break;
  }
  return fmt::format("GameInput {} gamepad {:04X}:{:04X}", family, info->vendorId, info->productId);
}

}

GameInputDriver::GameInputDriver(rex::ui::Window* window, size_t window_z_order)
    : InputDriver(window, window_z_order) {}

GameInputDriver::~GameInputDriver() {
  if (game_input_) {
    if (device_token_) {
      game_input_->UnregisterCallback(device_token_, kUnregisterTimeoutUs);
    }
    std::lock_guard lock(mutex_);
    for (auto& [key, device] : host_devices_) {
      StopRumble(device);
      device->Release();
    }
    host_devices_.clear();
    game_input_->Release();
    game_input_ = nullptr;
  }
}

X_STATUS GameInputDriver::Setup() {
  module_ = LoadLibraryW(L"GameInput.dll");
  if (!module_) {
    REXLOG_ERROR(
        "GameInput: GameInput.dll not found (error {}). Install the GameInput runtime "
        "(GameInputRedist.msi from the Microsoft GDK or the Microsoft.GameInput package).",
        GetLastError());
    return X_STATUS_DLL_NOT_FOUND;
  }
  using GameInputCreateFn = HRESULT(WINAPI*)(IGameInput**);
  auto create = reinterpret_cast<GameInputCreateFn>(GetProcAddress(module_, "GameInputCreate"));
  if (!create) {
    REXLOG_ERROR("GameInput: GameInput.dll has no GameInputCreate export");
    FreeLibrary(module_);
    module_ = nullptr;
    return X_STATUS_PROCEDURE_NOT_FOUND;
  }
  HRESULT hr = create(&game_input_);
  if (FAILED(hr) || !game_input_) {
    REXLOG_ERROR(
        "GameInput: GameInputCreate failed (0x{:08X}). The GameInput runtime is missing or "
        "older than this SDK's GDK headers; install the current GameInput redistributable.",
        uint32_t(hr));
    game_input_ = nullptr;
    FreeLibrary(module_);
    module_ = nullptr;
    return X_STATUS_UNSUCCESSFUL;
  }

  hr = game_input_->RegisterDeviceCallback(nullptr, GameInputKindGamepad, GameInputDeviceConnected,
                                           GameInputBlockingEnumeration, this, OnDeviceStatus,
                                           &device_token_);
  if (FAILED(hr)) {
    REXLOG_ERROR("GameInput: RegisterDeviceCallback failed (0x{:08X})", uint32_t(hr));
    game_input_->Release();
    game_input_ = nullptr;
    FreeLibrary(module_);
    module_ = nullptr;
    return X_STATUS_UNSUCCESSFUL;
  }

  REXLOG_INFO("GameInput: driver ready");
  return X_STATUS_SUCCESS;
}

void CALLBACK GameInputDriver::OnDeviceStatus(GameInputCallbackToken, void* context,
                                              IGameInputDevice* device, uint64_t,
                                              GameInputDeviceStatus current,
                                              GameInputDeviceStatus previous) {
  auto* self = static_cast<GameInputDriver*>(context);
  const bool connected = (current & GameInputDeviceConnected) != 0;
  const bool was_connected = (previous & GameInputDeviceConnected) != 0;
  if (connected == was_connected) {
    return;
  }
  std::lock_guard lock(self->mutex_);
  const void* key = device;
  if (connected) {
    const GameInputDeviceInfo* info = device->GetDeviceInfo();
    PadTraits traits;
    traits.wireless = (current & GameInputDeviceWireless) != 0;
    traits.subtype = SubtypeFromGameInput(info->supportedInput);
    traits.rumble = HasXInputRumble(info->supportedRumbleMotors);
    DeviceId id = self->devices_.Connect(key, DeviceName(device), traits);
    if (!self->host_devices_.count(key)) {
      device->AddRef();
      self->host_devices_[key] = device;
    }
    REXLOG_INFO(
        "GameInput: connected {} as device {:X}: kinds 0x{:08X}, XInput subtype 0x{:02X}, "
        "rumble motors 0x{:X}, {}",
        DeviceName(device), static_cast<uint64_t>(id), uint32_t(info->supportedInput),
        traits.subtype, uint32_t(info->supportedRumbleMotors),
        traits.wireless ? "wireless" : "wired");
  } else {
    self->devices_.Disconnect(key);
    auto it = self->host_devices_.find(key);
    if (it != self->host_devices_.end()) {
      StopRumble(it->second);
      it->second->Release();
      self->host_devices_.erase(it);
    }
    REXLOG_INFO("GameInput: disconnected {}", DeviceName(device));
  }
}

bool GameInputDriver::ActiveLocked() {
  const bool active = is_active();
  for (const auto& [key, rumble] : devices_.SetActive(active)) {
    ApplyRumbleLocked(key, rumble);
  }
  return active;
}

void GameInputDriver::PollLocked(DeviceId id) {
  const void* key = devices_.HostDevice(id);
  auto it = host_devices_.find(key);
  if (it == host_devices_.end()) {
    return;
  }
  IGameInputReading* reading = nullptr;
  if (FAILED(game_input_->GetCurrentReading(GameInputKindGamepad, it->second, &reading))) {
    return;
  }
  GameInputGamepadState state = {};
  if (reading->GetGamepadState(&state)) {
    devices_.Update(id, GamepadToXInput(state, false));
  }
  reading->Release();
}

void GameInputDriver::ApplyRumbleLocked(const void* host_device, const Rumble& rumble) {
  auto it = host_devices_.find(host_device);
  if (it == host_devices_.end()) {
    return;
  }
  GameInputRumbleParams params = RumbleToGameInput(rumble);
  it->second->SetRumbleState(&params);
}

void GameInputDriver::EnumerateDevices(std::vector<DeviceInfo>& out) {
  std::lock_guard lock(mutex_);
  devices_.Enumerate(out);
}

X_RESULT GameInputDriver::GetDeviceState(DeviceId id, X_INPUT_STATE* out_state) {
  std::lock_guard lock(mutex_);
  const bool active = ActiveLocked();
  if (active) {
    PollLocked(id);
  }
  return devices_.GetState(id, active, out_state);
}

X_RESULT GameInputDriver::GetDeviceCapabilities(DeviceId id, uint32_t,
                                                X_INPUT_CAPABILITIES* out_caps) {
  if (!out_caps) {
    return X_ERROR_BAD_ARGUMENTS;
  }
  std::lock_guard lock(mutex_);

  return devices_.GetCapabilities(id, false, out_caps);
}

X_RESULT GameInputDriver::SetDeviceVibration(DeviceId id, X_INPUT_VIBRATION* vibration) {
  std::lock_guard lock(mutex_);
  const bool active = ActiveLocked();
  std::optional<Rumble> apply;
  X_RESULT result = devices_.SetVibration(id, *vibration, active, &apply);
  if (apply) {
    ApplyRumbleLocked(devices_.HostDevice(id), *apply);
  }
  return result;
}

X_RESULT GameInputDriver::GetDeviceKeystroke(DeviceId id, uint32_t,
                                             X_INPUT_KEYSTROKE* out_keystroke) {
  if (!out_keystroke) {
    return X_ERROR_BAD_ARGUMENTS;
  }
  std::lock_guard lock(mutex_);
  const bool active = ActiveLocked();
  if (active) {
    PollLocked(id);
  }
  return devices_.GetKeystroke(id, active, rex::chrono::Clock::QueryGuestUptimeMillis(),
                               out_keystroke);
}

bool GameInputDriver::GetDeviceBattery(DeviceId id, PadBattery* out) {
  if (!out) {
    return false;
  }
  std::lock_guard lock(mutex_);
  auto it = host_devices_.find(devices_.HostDevice(id));
  if (it == host_devices_.end()) {
    return false;
  }
  GameInputBatteryState battery = {};
  battery.status = GameInputBatteryUnknown;
  it->second->GetBatteryState(&battery);
  *out = {};
  out->wireless = (it->second->GetDeviceStatus() & GameInputDeviceWireless) != 0;
  out->charging = battery.status == GameInputBatteryCharging;
  if (battery.status != GameInputBatteryUnknown && battery.status != GameInputBatteryNotPresent &&
      battery.fullChargeCapacity > 0.0f) {
    out->percent = std::clamp(
        int(battery.remainingCapacity / battery.fullChargeCapacity * 100.0f + 0.5f), 0, 100);
  }
  if (out->percent < 0) {
    const GameInputDeviceInfo* info = it->second->GetDeviceInfo();
    const int percent = ble_battery_.Percent(info->vendorId, info->productId);
    if (percent >= 0) {
      out->wireless = true;
      out->percent = percent;
    }
  }
  return true;
}

size_t GameInputDriver::CountDevices(uint16_t vendor_id, uint16_t product_id) {
  std::lock_guard lock(mutex_);
  size_t count = 0;
  for (const auto& [key, device] : host_devices_) {
    const GameInputDeviceInfo* info = device->GetDeviceInfo();
    if (info->vendorId == vendor_id && info->productId == product_id) {
      ++count;
    }
  }
  return count;
}

}
