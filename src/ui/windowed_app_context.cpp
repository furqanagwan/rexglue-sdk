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

#include <utility>

#include <rex/assert.h>
#include <rex/thread.h>
#include <rex/ui/windowed_app_context.h>

namespace rex {
namespace ui {

WindowedAppContext::~WindowedAppContext() {
  assert_true(IsInUIThread());

  is_in_destructor_ = true;

  has_quit_ = true;

  ExecutePendingFunctionsFromUIThread(true);
}

bool WindowedAppContext::CallInUIThreadDeferred(std::function<void()> function) {
  {
    std::unique_lock<std::mutex> pending_functions_lock(pending_functions_mutex_);
    if (!pending_functions_accepted_) {
      return false;
    }
    pending_functions_.emplace_back(std::move(function));
  }

  if (!is_in_destructor_) {
    NotifyUILoopOfPendingFunctions();
  }
  return true;
}

bool WindowedAppContext::CallInUIThread(std::function<void()> function) {
  if (IsInUIThread()) {
    function();
    return true;
  }
  return CallInUIThreadDeferred(std::move(function));
}

bool WindowedAppContext::CallInUIThreadSynchronous(std::function<void()> function) {
  if (IsInUIThread()) {
    function();
    return true;
  }
  rex::thread::Fence fence;
  if (!CallInUIThreadDeferred([&function, &fence]() {
        function();
        fence.Signal();
      })) {
    return false;
  }
  fence.Wait();
  return true;
}

void WindowedAppContext::QuitFromUIThread() {
  assert_true(IsInUIThread());
  bool has_quit_previously = has_quit_;

  has_quit_ = true;

  ExecutePendingFunctionsFromUIThread(true);
  if (has_quit_previously) {
    return;
  }

  PlatformQuitFromUIThread();
}

void WindowedAppContext::ExecutePendingFunctionsFromUIThread(bool is_final) {
  assert_true(IsInUIThread());
  std::unique_lock<std::mutex> pending_functions_lock(pending_functions_mutex_);
  while (!pending_functions_.empty()) {
    std::function<void()> function = std::move(pending_functions_.front());
    pending_functions_.pop_front();

    pending_functions_lock.unlock();
    function();
    pending_functions_lock.lock();
  }
  if (is_final) {
    pending_functions_accepted_ = false;
  }
}

}
}
