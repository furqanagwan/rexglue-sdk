/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2015 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <mutex>

namespace rex::thread {

class global_critical_region {
 public:
  static std::recursive_mutex& mutex();

  static std::unique_lock<std::recursive_mutex> AcquireDirect() {
    return std::unique_lock<std::recursive_mutex>(mutex());
  }

  inline std::unique_lock<std::recursive_mutex> Acquire() {
    return std::unique_lock<std::recursive_mutex>(mutex());
  }

  inline std::unique_lock<std::recursive_mutex> AcquireDeferred() {
    return std::unique_lock<std::recursive_mutex>(mutex(), std::defer_lock);
  }

  inline std::unique_lock<std::recursive_mutex> TryAcquire() {
    return std::unique_lock<std::recursive_mutex>(mutex(), std::try_to_lock);
  }
};

}
