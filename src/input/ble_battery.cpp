/**
 * @file        input/ble_battery.cpp
 * @brief       Bluetooth LE Battery Service levels for host pads (RG-GDK-047)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include "ble_battery.h"

#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include <fmt/format.h>
#include <fmt/xchar.h>

#include <rex/logging.h>

// clang-format off
#include <windows.h>
#include <setupapi.h>
#include <bluetoothleapis.h>
// clang-format on

namespace rex::input {

namespace {

constexpr GUID kBatteryService = {
    0x0000180F, 0x0000, 0x1000, {0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB}};
constexpr USHORT kBatteryLevel = 0x2A19;

constexpr auto kRefreshInterval = std::chrono::seconds(60);

std::wstring FindBatteryService(uint16_t vendor_id, uint16_t product_id) {
  const std::wstring needle = fmt::format(L"{:04x}_pid&{:04x}_", vendor_id, product_id);
  HDEVINFO set = SetupDiGetClassDevsW(&kBatteryService, nullptr, nullptr,
                                      DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
  if (set == INVALID_HANDLE_VALUE) {
    return {};
  }
  std::wstring found;
  SP_DEVICE_INTERFACE_DATA iface = {sizeof(iface)};
  for (DWORD i = 0;
       found.empty() && SetupDiEnumDeviceInterfaces(set, nullptr, &kBatteryService, i, &iface);
       ++i) {
    DWORD size = 0;
    SetupDiGetDeviceInterfaceDetailW(set, &iface, nullptr, 0, &size, nullptr);
    std::vector<uint8_t> buffer(size);
    auto* detail = reinterpret_cast<SP_DEVICE_INTERFACE_DETAIL_DATA_W*>(buffer.data());
    detail->cbSize = sizeof(*detail);
    if (!SetupDiGetDeviceInterfaceDetailW(set, &iface, detail, size, nullptr, nullptr)) {
      continue;
    }
    std::wstring path = detail->DevicePath;
    std::wstring lower = path;
    for (wchar_t& c : lower) {
      c = towlower(c);
    }
    if (lower.find(needle) != std::wstring::npos) {
      found = std::move(path);
    }
  }
  SetupDiDestroyDeviceInfoList(set);
  return found;
}

int ReadLevel(HANDLE service, BTH_LE_GATT_CHARACTERISTIC& level, ULONG flags) {
  USHORT size = 0;
  BluetoothGATTGetCharacteristicValue(service, &level, 0, nullptr, &size, flags);
  if (size < sizeof(BTH_LE_GATT_CHARACTERISTIC_VALUE)) {
    return -1;
  }
  std::vector<uint8_t> buffer(size);
  auto* value = reinterpret_cast<BTH_LE_GATT_CHARACTERISTIC_VALUE*>(buffer.data());
  if (FAILED(BluetoothGATTGetCharacteristicValue(service, &level, size, value, nullptr, flags)) ||
      value->DataSize < 1 || value->Data[0] > 100) {
    return -1;
  }
  return value->Data[0];
}

int ReadPercent(uint16_t vendor_id, uint16_t product_id) {
  const std::wstring path = FindBatteryService(vendor_id, product_id);
  if (path.empty()) {
    return -1;
  }
  HANDLE service = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                               nullptr, OPEN_EXISTING, 0, nullptr);
  if (service == INVALID_HANDLE_VALUE) {
    return -1;
  }
  int percent = -1;
  USHORT count = 0;
  BluetoothGATTGetCharacteristics(service, nullptr, 0, nullptr, &count, BLUETOOTH_GATT_FLAG_NONE);
  std::vector<BTH_LE_GATT_CHARACTERISTIC> characteristics(count);
  if (count &&
      SUCCEEDED(BluetoothGATTGetCharacteristics(service, nullptr, count, characteristics.data(),
                                                &count, BLUETOOTH_GATT_FLAG_NONE))) {
    for (auto& characteristic : characteristics) {
      if (!characteristic.CharacteristicUuid.IsShortUuid ||
          characteristic.CharacteristicUuid.Value.ShortUuid != kBatteryLevel) {
        continue;
      }
      percent = ReadLevel(service, characteristic, BLUETOOTH_GATT_FLAG_FORCE_READ_FROM_DEVICE);
      if (percent < 0) {
        percent = ReadLevel(service, characteristic, BLUETOOTH_GATT_FLAG_NONE);
      }
      break;
    }
  }
  CloseHandle(service);
  return percent;
}

}

BleBatteryMonitor::~BleBatteryMonitor() {
  {
    std::lock_guard lock(state_->mutex);
    state_->stop = true;
  }
  state_->wake.notify_all();
}

int BleBatteryMonitor::Percent(uint16_t vendor_id, uint16_t product_id) {
  const uint32_t key = (uint32_t(vendor_id) << 16) | product_id;
  std::lock_guard lock(state_->mutex);
  auto [it, inserted] = state_->levels.try_emplace(key, -1);
  if (inserted) {
    if (!state_->started) {
      state_->started = true;
      std::thread(Run, state_).detach();
    }
    state_->wake.notify_all();
  }
  return it->second;
}

void BleBatteryMonitor::Run(std::shared_ptr<State> state) {
  std::unique_lock lock(state->mutex);
  while (!state->stop) {
    std::vector<uint32_t> keys;
    for (const auto& [key, percent] : state->levels) {
      keys.push_back(key);
    }
    lock.unlock();
    for (uint32_t key : keys) {
      const int percent = ReadPercent(uint16_t(key >> 16), uint16_t(key));
      lock.lock();
      const int previous = state->levels[key];
      state->levels[key] = percent;
      lock.unlock();
      if (percent != previous) {
        REXLOG_INFO("Input: Bluetooth battery of {:04X}:{:04X} is {}", key >> 16, key & 0xFFFF,
                    percent < 0 ? std::string("unknown") : fmt::format("{}%", percent));
      }
    }
    lock.lock();

    const size_t known = state->levels.size();
    state->wake.wait_for(lock, kRefreshInterval,
                         [&] { return state->stop || state->levels.size() != known; });
  }
}

}
