/**
 * @file        rex/thread/fiber.h
 * @brief       Host OS fiber primitive for cooperative context switching
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <rex/platform.h>
#include <cstddef>

namespace rex::thread {

struct Fiber {
  static Fiber* ConvertCurrentThread();

  static Fiber* Create(size_t stack_size, void (*entry)(void*), void* arg);

  static void SwitchTo(Fiber* target);

  void Destroy();

  static Fiber* Current() { return tls_current_; }

 private:
  static thread_local Fiber* tls_current_;

  void* handle_ = nullptr;
  bool is_thread_fiber_ = false;
};

}
