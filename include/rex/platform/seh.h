/**
 * @file        platform/seh.h
 * @brief       Platform-specific SEH implementation details
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 * @license     BSD 3-Clause License
 */

#pragma once

#include <atomic>
#include <cstdint>

#include <rex/types.h>

namespace rex {
class SehException;
}

namespace rex::platform {

inline std::atomic<bool> g_seh_initialized{false};

struct SehThreadState {
  u32 code = 0;
  uintptr_t info[2] = {0, 0};
};

SehThreadState& seh_thread_state();

int seh_filter(u32 code, void* exception_pointers);

[[noreturn]] void seh_rethrow();

void seh_initialize();

bool& seh_active();

}
