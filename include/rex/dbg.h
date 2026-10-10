/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2014 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <cstdint>

#include <fmt/format.h>

#include <cstring>

namespace rex::debug {

bool IsDebuggerAttached();

void Break();

namespace detail {
void DebugPrint(const char* s);
}

template <typename... Args>
void DebugPrint(fmt::string_view format, const Args&... args) {
  detail::DebugPrint(fmt::vformat(format, fmt::make_format_args(args...)).c_str());
}

}

#ifdef REXGLUE_ENABLE_PROFILING

#include <tracy/Tracy.hpp>

#define SCOPE_profile_cpu_f(name) ZoneNamedN(___tracy_cpu_zone, name, TracyIsStarted)
#define SCOPE_profile_cpu_i(name, detail)                \
  ZoneNamedN(___tracy_cpu_zone_i, name, TracyIsStarted); \
  ZoneTextV(___tracy_cpu_zone_i, detail, std::strlen(detail))

#define SCOPE_profile_gpu_f(name)
#define SCOPE_profile_gpu_i(name, detail)

#define PROFILE_THREAD_ENTER(name) \
  do {                             \
    if (TracyIsStarted)            \
      tracy::SetThreadName(name);  \
  } while (0)
#define PROFILE_THREAD_EXIT()

#ifdef TRACY_FIBERS
#define PROFILE_FIBER_ENTER(name) \
  do {                            \
    if (TracyIsStarted)           \
      TracyFiberEnter(name);      \
  } while (0)
#define PROFILE_FIBER_LEAVE \
  do {                      \
    if (TracyIsStarted)     \
      TracyFiberLeave;      \
  } while (0)
#else
#define PROFILE_FIBER_ENTER(name)
#define PROFILE_FIBER_LEAVE
#endif

#define COUNT_profile_set(name, value)              \
  do {                                              \
    if (TracyIsStarted)                             \
      TracyPlot(name, static_cast<int64_t>(value)); \
  } while (0)

#else

#define SCOPE_profile_cpu_f(name)
#define SCOPE_profile_cpu_i(name, detail)

#define SCOPE_profile_gpu_f(name)
#define SCOPE_profile_gpu_i(name, detail)

#define PROFILE_THREAD_ENTER(name)
#define PROFILE_THREAD_EXIT()

#define PROFILE_FIBER_ENTER(name)
#define PROFILE_FIBER_LEAVE

#define COUNT_profile_set(name, value)

#endif
