#pragma once
/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2021 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <cstdint>
#include <deque>
#include <functional>
#include <mutex>
#include <thread>

#include <rex/assert.h>

namespace rex {
namespace ui {

class WindowedAppContext {
 public:
  WindowedAppContext(const WindowedAppContext& context) = delete;
  WindowedAppContext& operator=(const WindowedAppContext& context) = delete;
  virtual ~WindowedAppContext();

  bool IsInUIThread() const { return std::this_thread::get_id() == ui_thread_id_; }

  bool CallInUIThreadDeferred(std::function<void()> function);

  bool CallInUIThread(std::function<void()> function);
  bool CallInUIThreadSynchronous(std::function<void()> function);

  void ExecutePendingFunctionsFromUIThread() { ExecutePendingFunctionsFromUIThread(false); }

  bool HasQuitFromUIThread() const {
    assert_true(IsInUIThread());
    return has_quit_;
  }

  void QuitFromUIThread();

  void RequestDeferredQuit() {
    CallInUIThreadDeferred([this] { QuitFromUIThread(); });
  }

 protected:
  WindowedAppContext() : ui_thread_id_(std::this_thread::get_id()) {}

  virtual void NotifyUILoopOfPendingFunctions() = 0;

  virtual void PlatformQuitFromUIThread() = 0;

  std::thread::id ui_thread_id_;

 private:
  void ExecutePendingFunctionsFromUIThread(bool is_final);

  bool has_quit_ = false;
  bool is_in_destructor_ = false;

  std::mutex pending_functions_mutex_;
  std::deque<std::function<void()>> pending_functions_;

  bool pending_functions_accepted_ = true;
};

}
}
