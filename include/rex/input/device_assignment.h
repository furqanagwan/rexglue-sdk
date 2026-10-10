#pragma once
/**
 * @file        rex/input/device_assignment.h
 * @brief       Policy assigning physical input devices to guest user indices.
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <cstdint>
#include <vector>

#include <rex/input/device.h>

namespace rex::input {

class DeviceAssignment {
 public:
  virtual ~DeviceAssignment() = default;

  virtual void OnDevicesChanged(const std::vector<DeviceInfo>& devices) = 0;

  virtual void DevicesForUser(uint32_t user_index, std::vector<DeviceId>& out) const = 0;
};

class SlotAssignment final : public DeviceAssignment {
 public:
  void OnDevicesChanged(const std::vector<DeviceInfo>& devices) override;
  void DevicesForUser(uint32_t user_index, std::vector<DeviceId>& out) const override;

 private:
  std::vector<std::vector<DeviceId>> users_ = std::vector<std::vector<DeviceId>>(kMaxGuestUsers);
};

class SharedAssignment final : public DeviceAssignment {
 public:
  void OnDevicesChanged(const std::vector<DeviceInfo>& devices) override;
  void DevicesForUser(uint32_t user_index, std::vector<DeviceId>& out) const override;

 private:
  std::vector<DeviceId> user0_;
};

}
