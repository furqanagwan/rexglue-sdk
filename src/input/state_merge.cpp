/**
 * @file        input/state_merge.cpp
 * @brief       Combining several devices into one guest controller state.
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <rex/input/state_merge.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>

namespace rex::input {

namespace {

int16_t LargerMagnitude(int16_t a, int16_t b) {
  return std::abs(static_cast<int>(a)) >= std::abs(static_cast<int>(b)) ? a : b;
}

bool PastDeadzone(int16_t axis) {
  return std::abs(static_cast<int>(axis)) >= kThumbDeadzone;
}

}  // namespace

std::pair<int16_t, int16_t> ApplyStickDeadzone(double percentage, StickRange range, int16_t x,
                                               int16_t y) {
  if (!(percentage > 0.0 && percentage < 1.0)) {
    return {x, y};
  }
  const double theta = std::atan2(static_cast<double>(y), static_cast<double>(x));
  // Magnitudes: upstream compared against the signed projection, so a stick
  // pushed left or down never reached the deadzone.
  const double cutoff_x = std::abs(std::cos(theta)) * range.first * percentage;
  const double cutoff_y = std::abs(std::sin(theta)) * range.second * percentage;
  if (std::abs(static_cast<double>(x)) < cutoff_x) {
    x = 0;
  }
  if (std::abs(static_cast<double>(y)) < cutoff_y) {
    y = 0;
  }
  return {x, y};
}

void MergeInto(X_INPUT_STATE& dst, const X_INPUT_STATE& src) {
  dst.gamepad.buttons =
      static_cast<uint16_t>(dst.gamepad.buttons) | static_cast<uint16_t>(src.gamepad.buttons);
  dst.gamepad.left_trigger = std::max(dst.gamepad.left_trigger, src.gamepad.left_trigger);
  dst.gamepad.right_trigger = std::max(dst.gamepad.right_trigger, src.gamepad.right_trigger);
  dst.gamepad.thumb_lx = LargerMagnitude(dst.gamepad.thumb_lx, src.gamepad.thumb_lx);
  dst.gamepad.thumb_ly = LargerMagnitude(dst.gamepad.thumb_ly, src.gamepad.thumb_ly);
  dst.gamepad.thumb_rx = LargerMagnitude(dst.gamepad.thumb_rx, src.gamepad.thumb_rx);
  dst.gamepad.thumb_ry = LargerMagnitude(dst.gamepad.thumb_ry, src.gamepad.thumb_ry);

  if (static_cast<uint32_t>(src.packet_number) > static_cast<uint32_t>(dst.packet_number)) {
    dst.packet_number = src.packet_number;
  }
}

bool IsNeutral(const X_INPUT_GAMEPAD& gamepad) {
  if (static_cast<uint16_t>(gamepad.buttons) != 0) {
    return false;
  }
  if (gamepad.left_trigger >= kTriggerThreshold || gamepad.right_trigger >= kTriggerThreshold) {
    return false;
  }
  return !PastDeadzone(gamepad.thumb_lx) && !PastDeadzone(gamepad.thumb_ly) &&
         !PastDeadzone(gamepad.thumb_rx) && !PastDeadzone(gamepad.thumb_ry);
}

void ActiveDeviceTracker::Observe(uint32_t user_index, DeviceId id,
                                  const X_INPUT_GAMEPAD& gamepad) {
  if (user_index >= kMaxGuestUsers || IsNeutral(gamepad)) {
    return;
  }
  active_[user_index] = id;
}

DeviceId ActiveDeviceTracker::Active(uint32_t user_index) const {
  if (user_index >= kMaxGuestUsers) {
    return DeviceId::kInvalid;
  }
  return active_[user_index];
}

void ActiveDeviceTracker::Forget(DeviceId id) {
  for (auto& active : active_) {
    if (active == id) {
      active = DeviceId::kInvalid;
    }
  }
}

}  // namespace rex::input
