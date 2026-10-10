/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <memory>

namespace rex::thread {

class TimerQueue;

struct TimerQueueWaitItem {
  using clock = std::chrono::steady_clock;

  TimerQueueWaitItem(std::function<void(void*)> callback, void* userdata, TimerQueue* parent_queue,
                     clock::time_point due, clock::duration interval)
      : callback_(std::move(callback)),
        userdata_(userdata),
        parent_queue_(parent_queue),
        due_(due),
        interval_(interval),
        state_(State::kIdle) {}

  void Disarm();

  friend TimerQueue;

 private:
  enum class State : uint_least8_t { kIdle = 0, kInCallback, kInCallbackSelfDisarmed, kDisarmed };
  static_assert(std::atomic<State>::is_always_lock_free);

  std::function<void(void*)> callback_;
  void* userdata_;
  TimerQueue* parent_queue_;
  clock::time_point due_;
  clock::duration interval_;
  std::atomic<State> state_;
};

std::weak_ptr<TimerQueueWaitItem> QueueTimerOnce(std::function<void(void*)> callback,
                                                 void* userdata,
                                                 TimerQueueWaitItem::clock::time_point due);

std::weak_ptr<TimerQueueWaitItem> QueueTimerRecurring(std::function<void(void*)> callback,
                                                      void* userdata,
                                                      TimerQueueWaitItem::clock::time_point due,
                                                      TimerQueueWaitItem::clock::duration interval);

}
