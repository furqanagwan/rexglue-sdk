/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2026 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    ReXGlue, 2026 - Ported from xenia-canary 3a44f20c7 (PR #1190)
 */

#pragma once

#include <cstdint>
#include <cstring>

namespace rex::graphics {

inline float ReduceFloatPrecision(float value, uint32_t mantissa_bits) {
  uint32_t value_bits;
  std::memcpy(&value_bits, &value, sizeof(value_bits));
  if ((value_bits & UINT32_C(0x7F800000)) == UINT32_C(0x7F800000)) {
    return value;
  }
  uint32_t truncate_bits = 23 - mantissa_bits;
  uint32_t discarded_mask = (uint32_t(1) << truncate_bits) - 1;
  uint32_t truncated_bits = value_bits & ~discarded_mask;
  uint32_t rounded_bits = truncated_bits + (uint32_t(1) << truncate_bits);
  if ((rounded_bits & UINT32_C(0x7F800000)) == UINT32_C(0x7F800000)) {
    rounded_bits = truncated_bits;
  }
  uint32_t round_bit = uint32_t(1) << (truncate_bits - 1);
  uint32_t result_bits = (value_bits & discarded_mask) >= round_bit ? rounded_bits : truncated_bits;
  float result;
  std::memcpy(&result, &result_bits, sizeof(result));
  return result;
}

}
