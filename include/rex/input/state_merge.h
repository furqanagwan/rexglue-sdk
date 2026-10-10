#pragma once
/**
 * @file        rex/input/state_merge.h
 * @brief       Combining several devices into one guest controller state.
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <array>
#include <utility>

#include <rex/input/device.h>
#include <rex/input/input.h>

namespace rex::input {

constexpr int32_t kThumbDeadzone = X_INPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
constexpr uint8_t kTriggerThreshold = X_INPUT_GAMEPAD_TRIGGER_THRESHOLD;

void MergeInto(X_INPUT_STATE& dst, const X_INPUT_STATE& src);

bool IsNeutral(const X_INPUT_GAMEPAD& gamepad);

using StickRange = std::pair<uint16_t, uint16_t>;

std::pair<int16_t, int16_t> ApplyStickDeadzone(double percentage, StickRange range, int16_t x,
                                               int16_t y);

class ActiveDeviceTracker {
 public:
  void Observe(uint32_t user_index, DeviceId id, const X_INPUT_GAMEPAD& gamepad);

  DeviceId Active(uint32_t user_index) const;
  void Forget(DeviceId id);

 private:
  std::array<DeviceId, kMaxGuestUsers> active_ = {};
};

}
