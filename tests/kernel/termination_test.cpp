/**
 * @file        termination_test.cpp
 * @brief       Title termination with guest threads blocked in the kernel (RG-GDK-015)
 *
 * Guest threads run a registered function (as generated code does) that
 * loops in kernel waits and delays. TerminateTitle must bring every one of
 * them to its termination point and return, under contention, repeatedly,
 * within a watchdog: no indefinite wait.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <atomic>
#include <chrono>
#include <future>
#include <thread>
#include <vector>

#include "kernel_fixture.h"

#include <catch2/generators/catch_generators.hpp>

#include <rex/cvar.h>

#include <rex/ppc/context.h>
#include <rex/system/function_dispatcher.h>
#include <rex/system/xevent.h>
#include <rex/system/xthread.h>

namespace {

using rex::X_STATUS;
using rex::system::object_ref;
using rex::system::XEvent;
using rex::system::XThread;
using rex::testing::Kernel;

// A code range for the test's guest functions.
constexpr uint32_t kCodeBase = 0x82F00000;
constexpr uint32_t kCodeSize = 0x1000;
constexpr uint32_t kImageSize = 0x10000;
constexpr uint32_t kWaiterAddress = kCodeBase + 0x100;

std::atomic<int> g_started{0};
std::atomic<int> g_returned{0};
XEvent* g_event = nullptr;

// The guest thread body: block in the kernel until termination stops it.
// start_context picks how: 0 infinite wait, 1 alertable infinite wait,
// 2 1 ms delay, 3 alertable 5 ms delay, 4 alertable 60 s delay (only a user
// APC can end it), 5 60 s delay (only the termination event can end it, like
// a guest Sleep(INFINITE)).
void Waiter(PPCContext& ctx, uint8_t* base) {
  (void)base;
  const uint32_t mode = ctx.r3.u32 % 6;
  ++g_started;
  XThread* self = XThread::GetCurrentThread();
  for (;;) {
    switch (mode) {
      case 0:
        g_event->Wait(3, 1, 0, nullptr);
        break;
      case 1:
        g_event->Wait(3, 1, 1, nullptr);
        break;
      case 2:
        self->Delay(1, 0, uint64_t(-10000));
        break;
      case 3:
        self->Delay(1, 1, uint64_t(-50000));
        break;
      case 4:
        self->Delay(1, 1, uint64_t(-600000000));
        break;
      default:
        self->Delay(1, 0, uint64_t(-600000000));
        break;
    }
    // Waits also wake for the contention thread; loop until terminated.
    // Termination exits the thread inside the kernel call, so this function
    // never returns; g_returned counts any that do.
    if (g_event == nullptr) {
      ++g_returned;
      return;
    }
  }
}

void RegisterWaiter() {
  static bool registered = [] {
    auto* dispatcher = Kernel()->function_dispatcher();
    REQUIRE(dispatcher->InitializeFunctionTable(kCodeBase, kCodeSize, kCodeBase, kImageSize));
    REQUIRE(dispatcher->SetFunction(kWaiterAddress, &Waiter));
    return true;
  }();
  (void)registered;
}

}  // namespace

TEST_CASE("TerminateTitle stops guest threads blocked in waits and delays, repeatedly",
          "[kernel][termination]") {
  RegisterWaiter();
  // With precise timers every kind of block ends at termination. Without
  // them a non-alertable 60 s delay (mode 5) sleeps on and is left running,
  // a documented limitation, so that mode is left out.
  auto precise = GENERATE(true, false);
  INFO("guest_precise_timers " << precise);
  REQUIRE(rex::cvar::SetFlagByName("guest_precise_timers", precise ? "true" : "false"));
  constexpr int kRounds = 10;
  constexpr int kThreads = 16;
  for (int round = 0; round < kRounds; ++round) {
    INFO("round " << round);
    g_started = 0;
    auto event = object_ref<XEvent>(new XEvent(Kernel()));
    event->Initialize(false, false);
    g_event = event.get();

    std::vector<object_ref<XThread>> threads;
    for (int i = 0; i < kThreads; ++i) {
      auto thread = object_ref<XThread>(new XThread(Kernel(), 64 * 1024, 0, kWaiterAddress,
                                                    uint32_t(precise ? i : i % 5), 0, true));
      REQUIRE(thread->Create() == X_STATUS_SUCCESS);
      threads.push_back(thread);
    }
    auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    while (g_started < kThreads && std::chrono::steady_clock::now() < deadline) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    REQUIRE(g_started == kThreads);

    // Contention: the event keeps flipping while termination runs.
    std::atomic<bool> stop{false};
    std::thread flipper([&] {
      while (!stop) {
        event->Set(0, false);
        event->Reset();
      }
    });

    // Watchdog: TerminateTitle must return, not wait forever.
    auto terminated = std::async(std::launch::async, [] { Kernel()->TerminateTitle(); });
    bool returned = terminated.wait_for(std::chrono::seconds(5)) == std::future_status::ready;
    stop = true;
    flipper.join();
    REQUIRE(returned);

    // Every guest thread reached a termination point and exited.
    deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    auto running = [&] {
      int count = 0;
      for (auto& thread : threads) {
        count += thread->is_running() ? 1 : 0;
      }
      return count;
    };
    while (running() && std::chrono::steady_clock::now() < deadline) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    CHECK(running() == 0);
    CHECK(g_returned == 0);
    CHECK_FALSE(Kernel()->is_terminating_title());
    g_event = nullptr;
    event->ReleaseHandle();
  }
  rex::cvar::SetFlagByName("guest_precise_timers", "true");
}
