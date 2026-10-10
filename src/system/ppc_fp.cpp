/**
 * @file        system/ppc_fp.cpp
 * @brief       Tables for the PowerPC estimate instructions (rex/ppc/fp.h)
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 *
 * @remarks     The vrsqrtefp coefficients and interpolation are from
 *              has207/xenia-edge src/xenia/cpu/backend/vrsqrte_table.cc
 *              (b5cc59e854, Xenia BSD licence), matched there to Xbox 360
 *              hardware captures.
 */

#include <array>
#include <bit>

#include <rex/ppc/fp.h>

namespace rex::ppc::fp {

namespace {

constexpr uint32_t kVRsqrteCoefficients[32] = {
    0x0568B4FD, 0x04F3AF97, 0x048DAAA5, 0x0435A618, 0x03E7A1E4, 0x03A29DFE, 0x03659A5C, 0x032E96F8,
    0x02FC93CA, 0x02D090CE, 0x02A88DFE, 0x02838B57, 0x026188D4, 0x02438673, 0x02268431, 0x020B820B,
    0x03D27FFA, 0x03807C29, 0x033878AA, 0x02F97572, 0x02C27279, 0x02926FB7, 0x02666D26, 0x023F6AC0,
    0x021D6881, 0x01FD6665, 0x01E16468, 0x01C76287, 0x01AF60C1, 0x01995F12, 0x01855D79, 0x01735BF4,
};

uint32_t NormalVRsqrte(uint32_t input) {
  const uint32_t mantissa = input & 0x7FFFFF;
  const uint32_t index = (((input >> 23) & 1) << 4) | (mantissa >> 19);
  const uint32_t coefficient = kVRsqrteCoefficients[index];
  uint32_t estimate =
      ((coefficient << 10) & 0x3FFFC00) - (((mantissa >> 9) & 1023) * (coefficient >> 16));
  int32_t exponent_adjustment = 0;
  if (!(estimate & 0x02000000)) {
    const uint32_t leading_zeros = std::countl_zero(estimate & 0x1FFFFFF);
    exponent_adjustment += 6 - int32_t(leading_zeros);
    estimate <<= leading_zeros - 6;
  }
  if ((estimate & 5) && (estimate & 2)) {
    estimate += 4;
  }
  return (0x3F800000 + uint32_t(exponent_adjustment) * 0x00800000) | ((estimate >> 2) & 0x7FFFFF);
}

}

const uint32_t* VRsqrteTable() {
  alignas(64) static const std::array<uint32_t, 1 << 15> table = [] {
    std::array<uint32_t, 1 << 15> values{};
    for (uint32_t index = 0; index < values.size(); ++index) {
      const uint32_t exponent = 126 + (index >> 14);
      values[index] = NormalVRsqrte((exponent << 23) | ((index & 0x3FFF) << 9));
    }
    return values;
  }();
  return table.data();
}

}
