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

// Pads paired over Bluetooth LE (Xbox Wireless over BLE, ROG Raikiri II and
// the like) reach XInput through xinputhid, which reports no battery, and
// GameInput, which reports them wired. Their GATT Battery Service (0x180F,
// Battery Level 0x2A19) has the level. A device read can
// take a 15 s timeout when the pad sleeps, so reads run on a worker thread and
// callers get the last level read. The worker is detached at destruction, so
// exit never waits on a read.
class BleBatteryMonitor {
 public:
  BleBatteryMonitor() = default;
  ~BleBatteryMonitor();

  BleBatteryMonitor(const BleBatteryMonitor&) = delete;
  BleBatteryMonitor& operator=(const BleBatteryMonitor&) = delete;

  /// The last level read for the connected BLE device with this USB vendor
  /// and product ID, or -1 while none is known. The first call for an ID
  /// starts reading it.
  int Percent(uint16_t vendor_id, uint16_t product_id);

 private:
  struct State {
    std::mutex mutex;
    std::condition_variable wake;
    bool stop = false;
    bool started = false;
    // (vendor << 16 | product) to percent, -1 until read.
    std::map<uint32_t, int> levels;
  };
  static void Run(std::shared_ptr<State> state);

  std::shared_ptr<State> state_ = std::make_shared<State>();
};

}  // namespace rex::input
