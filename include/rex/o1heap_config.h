/**
 * @file        o1heap_config.h
 * @brief       o1heap build configuration -- provides correct 64-bit CLZ.
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 * @license     BSD 3-Clause License
 */

#pragma once

#if defined(__clang__) || defined(__GNUC__)
#define O1HEAP_CLZ(x) ((uint8_t)__builtin_clzll((unsigned long long)(x)))
#elif defined(_MSC_VER)
#include <intrin.h>
static __inline uint8_t o1heap_clz_(size_t x) {
  unsigned long index;
  _BitScanReverse64(&index, (unsigned __int64)x);
  return (uint8_t)(63U - index);
}
#define O1HEAP_CLZ(x) o1heap_clz_(x)
#endif
