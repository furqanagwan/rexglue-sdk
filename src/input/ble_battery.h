/**
 * @file        input/ble_battery.h
 * @brief       Bluetooth LE Battery Service levels for host pads (RG-GDK-047)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <condition_variable>
#include <cstdint>
#include <map>
#include <memory>
#include <mutex>

namespace rex::input {

class BleBatteryMonitor {
 public:
  BleBatteryMonitor() = default;
  ~BleBatteryMonitor();

  BleBatteryMonitor(const BleBatteryMonitor&) = delete;
  BleBatteryMonitor& operator=(const BleBatteryMonitor&) = delete;

  int Percent(uint16_t vendor_id, uint16_t product_id);

 private:
  struct State {
    std::mutex mutex;
    std::condition_variable wake;
    bool stop = false;
    bool started = false;

    std::map<uint32_t, int> levels;
  };
  static void Run(std::shared_ptr<State> state);

  std::shared_ptr<State> state_ = std::make_shared<State>();
};

}
