/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    ReXGlue, 2026 - Split out of the SDL driver (RG-GDK-020)
 */

#include <array>
#include <iterator>

#include <rex/assert.h>
#include <rex/input/keystroke_synthesizer.h>
#include <rex/ui/virtual_key.h>

namespace rex::input {

namespace {

// The order of this list is also the order in which events are sent if
// multiple buttons change at once.
constexpr std::array<rex::ui::VirtualKey, 34> kVkLookup = {
    // 00 - True buttons from xinput button field
    rex::ui::VirtualKey::kXInputPadDpadUp,
    rex::ui::VirtualKey::kXInputPadDpadDown,
    rex::ui::VirtualKey::kXInputPadDpadLeft,
    rex::ui::VirtualKey::kXInputPadDpadRight,
    rex::ui::VirtualKey::kXInputPadStart,
    rex::ui::VirtualKey::kXInputPadBack,
    rex::ui::VirtualKey::kXInputPadLThumbPress,
    rex::ui::VirtualKey::kXInputPadRThumbPress,
    rex::ui::VirtualKey::kXInputPadLShoulder,
    rex::ui::VirtualKey::kXInputPadRShoulder,
    rex::ui::VirtualKey::kNone, /* Guide has no VK */
    rex::ui::VirtualKey::kNone, /* Unknown */
    rex::ui::VirtualKey::kXInputPadA,
    rex::ui::VirtualKey::kXInputPadB,
    rex::ui::VirtualKey::kXInputPadX,
    rex::ui::VirtualKey::kXInputPadY,
    // 16 - Fake buttons generated from analog inputs
    rex::ui::VirtualKey::kXInputPadLTrigger,
    rex::ui::VirtualKey::kXInputPadRTrigger,
    // 18
    rex::ui::VirtualKey::kXInputPadLThumbUp,
    rex::ui::VirtualKey::kXInputPadLThumbDown,
    rex::ui::VirtualKey::kXInputPadLThumbRight,
    rex::ui::VirtualKey::kXInputPadLThumbLeft,
    rex::ui::VirtualKey::kXInputPadLThumbUpLeft,
    rex::ui::VirtualKey::kXInputPadLThumbUpRight,
    rex::ui::VirtualKey::kXInputPadLThumbDownRight,
    rex::ui::VirtualKey::kXInputPadLThumbDownLeft,
    // 26
    rex::ui::VirtualKey::kXInputPadRThumbUp,
    rex::ui::VirtualKey::kXInputPadRThumbDown,
    rex::ui::VirtualKey::kXInputPadRThumbRight,
    rex::ui::VirtualKey::kXInputPadRThumbLeft,
    rex::ui::VirtualKey::kXInputPadRThumbUpLeft,
    rex::ui::VirtualKey::kXInputPadRThumbUpRight,
    rex::ui::VirtualKey::kXInputPadRThumbDownRight,
    rex::ui::VirtualKey::kXInputPadRThumbDownLeft,
};

void FillKeystroke(rex::ui::VirtualKey vk, uint16_t flags, X_INPUT_KEYSTROKE* out_keystroke) {
  out_keystroke->virtual_key = uint16_t(vk);
  out_keystroke->unicode = 0;
  out_keystroke->user_index = 0;
  out_keystroke->hid_code = 0;
  out_keystroke->flags = flags;
}

}  // namespace

X_RESULT KeystrokeSynthesizer::Next(const X_INPUT_GAMEPAD& gamepad, bool active, uint64_t now_ms,
                                    X_INPUT_KEYSTROKE* out_keystroke) {
  static_assert(sizeof(X_INPUT_GAMEPAD::buttons) == 2);
  static_assert(kRepeatDelayMs >= kRepeatRateMs);
  const uint64_t current =
      active ? (uint64_t(uint16_t(gamepad.buttons)) | AnalogToKeyfield(gamepad)) : uint64_t(0);

  if (repeat_state_ == RepeatState::kWaiting && repeat_time_ + kRepeatDelayMs < now_ms) {
    repeat_state_ = RepeatState::kRepeating;
  }
  if (repeat_state_ == RepeatState::kRepeating && repeat_time_ + kRepeatRateMs < now_ms) {
    repeat_time_ = now_ms;
    rex::ui::VirtualKey vk = kVkLookup.at(repeat_button_index_);
    assert_true(vk != rex::ui::VirtualKey::kNone);
    FillKeystroke(vk, X_INPUT_KEYSTROKE_KEYDOWN | X_INPUT_KEYSTROKE_REPEAT, out_keystroke);
    return X_ERROR_SUCCESS;
  }

  const uint64_t changed = current ^ buttons_;
  if (!changed) {
    return X_ERROR_EMPTY;
  }

  // First clear buttons with up events, to match XInput when a stick moves
  // between directions: THUMB_UPLEFT goes up before THUMB_LEFT goes down.
  for (int pass = 0; pass < 2; pass++) {
    const bool clear_pass = pass == 0;
    for (uint8_t i = 0; i < uint8_t(std::size(kVkLookup)); i++) {
      const uint64_t bit = uint64_t(1) << i;
      if (!(changed & bit)) {
        continue;
      }
      rex::ui::VirtualKey vk = kVkLookup.at(i);
      if (vk == rex::ui::VirtualKey::kNone) {
        continue;
      }
      const bool pressed = current & bit;
      if (clear_pass && !pressed) {
        FillKeystroke(vk, X_INPUT_KEYSTROKE_KEYUP, out_keystroke);
        buttons_ &= ~bit;
        repeat_state_ = RepeatState::kIdle;
        return X_ERROR_SUCCESS;
      }
      if (!clear_pass && pressed) {
        FillKeystroke(vk, X_INPUT_KEYSTROKE_KEYDOWN, out_keystroke);
        buttons_ |= bit;
        repeat_state_ = RepeatState::kWaiting;
        repeat_button_index_ = i;
        repeat_time_ = now_ms;
        return X_ERROR_SUCCESS;
      }
    }
  }
  return X_ERROR_EMPTY;
}

uint64_t KeystrokeSynthesizer::AnalogToKeyfield(const X_INPUT_GAMEPAD& gamepad) {
  uint64_t f = 0;

  f |= uint64_t(gamepad.left_trigger > kTriggerThreshold) << 16;
  f |= uint64_t(gamepad.right_trigger > kTriggerThreshold) << 17;

  auto thumb_x = static_cast<int16_t>(gamepad.thumb_lx);
  auto thumb_y = static_cast<int16_t>(gamepad.thumb_ly);
  for (size_t i = 0; i <= 8; i = i + 8) {
    uint64_t u = thumb_y > kThumbThreshold;
    uint64_t d = thumb_y < ~kThumbThreshold;
    uint64_t r = thumb_x > kThumbThreshold;
    uint64_t l = thumb_x < ~kThumbThreshold;
    if (u && l) {
      u = l = 0;
      f |= uint64_t(1) << (22 + i);
    }
    if (u && r) {
      u = r = 0;
      f |= uint64_t(1) << (23 + i);
    }
    if (d && r) {
      d = r = 0;
      f |= uint64_t(1) << (24 + i);
    }
    if (d && l) {
      d = l = 0;
      f |= uint64_t(1) << (25 + i);
    }
    f |= u << (18 + i);
    f |= d << (19 + i);
    f |= r << (20 + i);
    f |= l << (21 + i);

    thumb_x = static_cast<int16_t>(gamepad.thumb_rx);
    thumb_y = static_cast<int16_t>(gamepad.thumb_ry);
  }
  return f;
}

}  // namespace rex::input
