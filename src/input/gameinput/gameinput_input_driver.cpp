/**
 * @file        input/gameinput/gameinput_input_driver.cpp
 * @brief       Native GameInput gamepad driver, GDK builds only (RG-GDK-020)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include "gameinput_input_driver.h"

#include <fmt/format.h>

#include <rex/chrono/clock.h>
#include <rex/input/flags.h>
#include <rex/logging.h>

#include "gameinput_mapping.h"

namespace rex::input::gameinput {

namespace {

// How long teardown waits for a callback that is already running.
constexpr uint64_t kUnregisterTimeoutUs = 5'000'000;

// Zeroed parameters rather than nullptr: the header allows null, but the
// installed runtime (inbox GameInput.dll 0.2309, GameInputRedist 3.5.270)
// dereferences it and crashes.
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

}  // namespace

GameInputDriver::GameInputDriver(rex::ui::Window* window, size_t window_z_order)
    : InputDriver(window, window_z_order) {}

GameInputDriver::~GameInputDriver() {
  if (game_input_) {
    // Unregister first: a callback in flight must finish before the state it
    // touches goes away. UnregisterCallback waits for it.
    if (guide_token_) {
      game_input_->UnregisterCallback(guide_token_, kUnregisterTimeoutUs);
    }
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
  // GameInput.dll stays loaded: its worker threads outlive the last release,
  // and unloading it under them crashes the process.
}

X_STATUS GameInputDriver::Setup() {
  // GameInput.dll ships with Windows and forwards to the GameInput runtime
  // (GameInputRedist). Loaded here, not linked, so its absence is reported.
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

  // Blocking enumeration reports every already-connected pad before this
  // returns, so the first EnumerateDevices sees them.
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
  // The guide button is not part of GameInputGamepadState. Optional: some
  // runtimes reserve it for the system.
  hr = game_input_->RegisterGuideButtonCallback(nullptr, this, OnGuideButton, &guide_token_);
  if (FAILED(hr)) {
    REXLOG_INFO("GameInput: guide button unavailable (0x{:08X})", uint32_t(hr));
    guide_token_ = 0;
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
    const bool wireless = (current & GameInputDeviceWireless) != 0;
    DeviceId id = self->devices_.Connect(key, DeviceName(device), wireless);
    if (!self->host_devices_.count(key)) {
      device->AddRef();
      self->host_devices_[key] = device;
    }
    self->guide_pressed_[key] = false;
    REXLOG_INFO("GameInput: connected {} as device {:X}", DeviceName(device),
                static_cast<uint64_t>(id));
  } else {
    self->devices_.Disconnect(key);
    self->guide_pressed_.erase(key);
    auto it = self->host_devices_.find(key);
    if (it != self->host_devices_.end()) {
      // A reconnect must not resume the old rumble.
      StopRumble(it->second);
      it->second->Release();
      self->host_devices_.erase(it);
    }
    REXLOG_INFO("GameInput: disconnected {}", DeviceName(device));
  }
}

void CALLBACK GameInputDriver::OnGuideButton(GameInputCallbackToken, void* context,
                                             IGameInputDevice* device, uint64_t, bool is_pressed) {
  auto* self = static_cast<GameInputDriver*>(context);
  std::lock_guard lock(self->mutex_);
  auto it = self->guide_pressed_.find(device);
  if (it != self->guide_pressed_.end()) {
    it->second = is_pressed;
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
    // No reading yet: keep the last state (initially an untouched pad).
    return;
  }
  GameInputGamepadState state = {};
  if (reading->GetGamepadState(&state)) {
    const bool guide = REXCVAR_GET(guide_button) && guide_pressed_[key];
    devices_.Update(id, GamepadToXInput(state, guide));
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
  return devices_.GetCapabilities(id, REXCVAR_GET(guide_button), out_caps);
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

}  // namespace rex::input::gameinput
