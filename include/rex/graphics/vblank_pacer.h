/**
 * @file        rex/graphics/vblank_pacer.h
 * @brief       When the guest vblank interrupt is due
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>

namespace rex::graphics {

class VblankPacer {
 public:
  VblankPacer(uint64_t interval_ticks, uint64_t now)
      : interval_(interval_ticks), next_(now + interval_ticks) {}

  bool Due(uint64_t now) {
    if (now < next_) {
      return false;
    }
    if (now - next_ > interval_ * 2) {
      next_ = now + interval_;
    } else {
      next_ += interval_;
    }
    return true;
  }

  uint64_t TicksUntilDue(uint64_t now) const { return now < next_ ? next_ - now : 0; }

  uint64_t interval() const { return interval_; }

 private:
  uint64_t interval_;
  uint64_t next_;
};

}
