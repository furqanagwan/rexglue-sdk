/**
 * @file        object_header_test.cpp
 * @brief       Guest dispatch headers agree with host object state (RG-GDK-014)
 *
 * Events and semaphores keep the signal state in their guest dispatch header
 * in step with the host object (Canary #1227), pick up direct guest writes to
 * the header, and a signature left by a dead object never resolves to the
 * object that reuses its handle (Canary #1225, synthetic reproducer).
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <atomic>
#include <thread>
#include <vector>

#include <catch2/generators/catch_generators.hpp>

#include "kernel_fixture.h"

#include <rex/system/xevent.h>
#include <rex/system/xsemaphore.h>

namespace {

using rex::X_STATUS;
using rex::system::object_ref;
using rex::system::X_DISPATCH_HEADER;
using rex::system::X_KEVENT;
using rex::system::X_KSEMAPHORE;
using rex::system::XEvent;
using rex::system::XObject;
using rex::system::XSemaphore;
using rex::testing::Kernel;

constexpr X_STATUS kSuccess = 0;
constexpr X_STATUS kTimeout = 0x00000102;

X_STATUS Poll(XObject* object) {
  uint64_t timeout = 0;
  return object->Wait(3, 1, 0, &timeout);
}

object_ref<XEvent> CreateEvent(bool manual_reset, bool initial_state) {
  auto event = object_ref<XEvent>(new XEvent(Kernel()));
  event->Initialize(manual_reset, initial_state);
  return event;
}

object_ref<XSemaphore> CreateSemaphore(int32_t count, int32_t limit) {
  auto semaphore = object_ref<XSemaphore>(new XSemaphore(Kernel()));
  REQUIRE(semaphore->Initialize(count, limit));
  return semaphore;
}

uint32_t SignalState(XObject* object) {
  return object->guest_object<X_DISPATCH_HEADER>()->signal_state;
}

struct GuestObject {
  explicit GuestObject(uint32_t size) {
    address = Kernel()->memory()->SystemHeapAlloc(size);
    REQUIRE(address);
    Kernel()->memory()->Zero(address, size);
  }
  ~GuestObject() { Kernel()->memory()->SystemHeapFree(address); }
  template <typename T>
  T* get() const {
    return Kernel()->memory()->TranslateVirtual<T*>(address);
  }
  uint32_t address = 0;
};

}

TEST_CASE("A created notification event keeps its type and state in the header",
          "[kernel][object_header]") {
  auto event = CreateEvent(true, false);
  auto* header = &event->guest_object<X_KEVENT>()->header;
  CHECK(header->type == 0);
  CHECK(header->signal_state == 0);

  uint32_t type = 99, state = 99;
  event->Query(&type, &state);

  CHECK(type == 0);
  CHECK(state == 0);

  event->Set(0, false);
  CHECK(header->signal_state == 1);

  CHECK(Poll(event.get()) == kSuccess);
  CHECK(Poll(event.get()) == kSuccess);
  CHECK(header->signal_state == 1);
  event->Reset();
  CHECK(header->signal_state == 0);
  CHECK(Poll(event.get()) == kTimeout);
  event->ReleaseHandle();
}

TEST_CASE("A synchronization event clears its header when a wait takes it",
          "[kernel][object_header]") {
  auto event = CreateEvent(false, true);
  CHECK(event->guest_object<X_KEVENT>()->header.type == 1);
  CHECK(SignalState(event.get()) == 1);
  CHECK(Poll(event.get()) == kSuccess);
  CHECK(SignalState(event.get()) == 0);
  CHECK(Poll(event.get()) == kTimeout);

  event->Set(0, false);

  CHECK(event->Pulse(0, false) == 1);
  CHECK(SignalState(event.get()) == 0);
  CHECK(event->Pulse(0, false) == 0);
  CHECK(Poll(event.get()) == kTimeout);
  event->ReleaseHandle();
}

TEST_CASE("A semaphore header holds the count and limit", "[kernel][object_header]") {
  auto semaphore = CreateSemaphore(2, 5);
  auto* guest = semaphore->guest_object<X_KSEMAPHORE>();
  CHECK(guest->header.type == 5);
  CHECK(guest->header.signal_state == 2);
  CHECK(guest->limit == 5);

  CHECK(Poll(semaphore.get()) == kSuccess);
  CHECK(guest->header.signal_state == 1);
  int32_t previous = -1;
  CHECK(semaphore->ReleaseSemaphore(3, &previous));
  CHECK(previous == 1);
  CHECK(guest->header.signal_state == 4);

  CHECK_FALSE(semaphore->ReleaseSemaphore(2, nullptr));
  CHECK(guest->header.signal_state == 4);
  semaphore->ReleaseHandle();
}

TEST_CASE("A guest write to an event header is picked up on the next lookup",
          "[kernel][object_header]") {
  GuestObject memory(sizeof(X_KEVENT));
  auto* header = &memory.get<X_KEVENT>()->header;
  header->type = 1;

  auto event = XObject::GetNativeObject<XEvent>(Kernel(), header);
  REQUIRE(event);
  CHECK(event->guest_object() == memory.address);
  CHECK(Poll(event.get()) == kTimeout);

  header->signal_state = 1;
  auto again = XObject::GetNativeObject<XEvent>(Kernel(), header);
  CHECK(again.get() == event.get());
  CHECK(Poll(event.get()) == kSuccess);
  CHECK(header->signal_state == 0);

  event->Set(0, false);
  header->signal_state = 0;
  XObject::GetNativeObject<XEvent>(Kernel(), header);
  CHECK(Poll(event.get()) == kTimeout);
  event->ReleaseHandle();
}

TEST_CASE("An in-place semaphore re-initialize moves the host count both ways",
          "[kernel][object_header]") {
  GuestObject memory(sizeof(X_KSEMAPHORE));
  auto* guest = memory.get<X_KSEMAPHORE>();
  guest->header.type = 5;
  guest->header.signal_state = 1;
  guest->limit = 4;

  auto semaphore = XObject::GetNativeObject<XSemaphore>(Kernel(), guest);
  REQUIRE(semaphore);
  guest->header.signal_state = 3;
  XObject::GetNativeObject<XSemaphore>(Kernel(), guest);
  CHECK(Poll(semaphore.get()) == kSuccess);
  CHECK(Poll(semaphore.get()) == kSuccess);
  CHECK(guest->header.signal_state == 1);

  guest->header.signal_state = 0;
  XObject::GetNativeObject<XSemaphore>(Kernel(), guest);
  CHECK(Poll(semaphore.get()) == kTimeout);
  CHECK(guest->header.signal_state == 0);

  guest->header.signal_state = 9;
  XObject::GetNativeObject<XSemaphore>(Kernel(), guest);
  CHECK(guest->header.signal_state == 0);
  semaphore->ReleaseHandle();
}

TEST_CASE("A signature left by a dead object never resolves to the handle's next owner",
          "[kernel][object_header]") {
  GuestObject memory(sizeof(X_KEVENT));
  auto* header = &memory.get<X_KEVENT>()->header;
  header->type = 1;

  uint32_t dead_handle;
  {
    auto first = XObject::GetNativeObject<XEvent>(Kernel(), header);
    REQUIRE(first);
    dead_handle = first->handle();

    first->ReleaseHandle();
  }
  CHECK(header->wait_list_blink == dead_handle);

  auto next_owner = CreateSemaphore(0, 1);
  INFO("handle reused: " << (next_owner->handle() == dead_handle));

  auto looked_up = XObject::GetNativeObject<XObject>(Kernel(), header);
  REQUIRE(looked_up);
  CHECK(looked_up.get() != next_owner.get());
  CHECK(looked_up->type() == XObject::Type::Event);
  CHECK(looked_up->guest_object() == memory.address);
  CHECK(header->wait_list_blink == looked_up->handle());

  looked_up->ReleaseHandle();
  CHECK(Kernel()->object_table()->LookupObject<XSemaphore>(next_owner->handle()));
  next_owner->ReleaseHandle();
}

TEST_CASE("SignalAndWait updates the signaled object's header", "[kernel][object_header]") {
  auto signal = CreateEvent(false, false);
  auto wait = CreateEvent(true, true);
  uint64_t timeout = 0;
  CHECK(XObject::SignalAndWait(signal.get(), wait.get(), 3, 1, 0, &timeout) == kSuccess);
  CHECK(SignalState(signal.get()) == 1);
  CHECK(Poll(signal.get()) == kSuccess);
  CHECK(SignalState(signal.get()) == 0);

  auto full = CreateSemaphore(1, 1);
  XObject::SignalAndWait(full.get(), wait.get(), 3, 1, 0, &timeout);
  CHECK(SignalState(full.get()) == 1);
  signal->ReleaseHandle();
  wait->ReleaseHandle();
  full->ReleaseHandle();
}

TEST_CASE("Concurrent releases and waits leave the semaphore header equal to the count",
          "[kernel][object_header]") {
  constexpr int kThreads = 4;
  constexpr int kReleasesPerThread = 2000;
  auto semaphore = CreateSemaphore(0, kThreads * kReleasesPerThread);
  std::atomic<int> taken{0};
  std::vector<std::thread> threads;
  for (int t = 0; t < kThreads; ++t) {
    threads.emplace_back([&] {
      for (int i = 0; i < kReleasesPerThread; ++i) {
        REQUIRE(semaphore->ReleaseSemaphore(1, nullptr));
      }
    });
    threads.emplace_back([&] {
      for (int i = 0; i < kReleasesPerThread / 2; ++i) {
        if (Poll(semaphore.get()) == kSuccess) {
          ++taken;
        }
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
  int32_t expected = kThreads * kReleasesPerThread - taken;
  CHECK(static_cast<int32_t>(SignalState(semaphore.get())) == expected);

  int32_t drained = 0;
  while (Poll(semaphore.get()) == kSuccess) {
    ++drained;
  }
  CHECK(drained == expected);
  CHECK(SignalState(semaphore.get()) == 0);
  semaphore->ReleaseHandle();
}

TEST_CASE("Concurrent set, reset, pulse and wait end with header and event in agreement",
          "[kernel][object_header]") {
  auto manual = GENERATE(true, false);
  INFO((manual ? "notification" : "synchronization"));
  auto event = CreateEvent(manual, false);
  std::atomic<bool> stop{false};
  std::vector<std::thread> threads;
  threads.emplace_back([&] {
    for (int i = 0; i < 20000; ++i) {
      switch (i % 3) {
        case 0:
          event->Set(0, false);
          break;
        case 1:
          event->Reset();
          break;
        default:
          event->Pulse(0, false);
      }
    }

    event->Set(0, false);
    stop = true;
  });
  for (int t = 0; t < 3; ++t) {
    threads.emplace_back([&] {
      while (!stop) {
        Poll(event.get());
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }

  bool header_signaled = SignalState(event.get()) != 0;
  bool host_signaled = Poll(event.get()) == kSuccess;
  CHECK(header_signaled == host_signaled);
  event->ReleaseHandle();
}
