/**
 * @file        notify_test.cpp
 * @brief       XAM notification filtering, order, lifetime and title launches (RG-GDK-017)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <utility>
#include <vector>

#include <rex/system/xam/title_launch.h>
#include <rex/system/xnotifylistener.h>

#include "kernel_fixture.h"

using rex::X_STATUS;
using rex::system::XNotificationID;
using rex::system::XNotifyListener;
using rex::system::xam::ClassifyLaunch;
using rex::system::xam::LaunchKind;

namespace {

// Notification ids pack mask_index:6, version:9 and local_id:16.
XNotificationID Id(uint32_t mask_index, uint32_t version, uint32_t local_id) {
  return XNotificationID((mask_index << 25) | (version << 16) | local_id);
}

// Mask bit 0 is left out: the kernel sends its startup notifications to the
// first listener with that bit, which only the dedicated case below creates.
rex::system::object_ref<XNotifyListener> Listen(uint64_t mask, uint32_t max_version = 10) {
  auto listener =
      rex::system::object_ref<XNotifyListener>(new XNotifyListener(rex::testing::Kernel()));
  listener->Initialize(mask, max_version);
  return listener;
}

std::vector<std::pair<uint32_t, uint32_t>> Drain(XNotifyListener* listener) {
  std::vector<std::pair<uint32_t, uint32_t>> out;
  XNotificationID id;
  uint32_t data;
  while (listener->DequeueNotification(&id, &data)) {
    out.emplace_back(uint32_t(id), data);
  }
  return out;
}

}  // namespace

TEST_CASE("Notify listeners receive only their mask and version", "[kernel][notify]") {
  auto listener = Listen(1ull << 2, /*max_version=*/3);
  auto* kernel = rex::testing::Kernel();
  kernel->BroadcastNotification(Id(2, 1, 0x10), 1);  // matching
  kernel->BroadcastNotification(Id(3, 1, 0x11), 2);  // other mask bit
  kernel->BroadcastNotification(Id(2, 4, 0x12), 3);  // newer than max_version
  kernel->BroadcastNotification(Id(2, 3, 0x13), 4);  // exactly max_version
  CHECK(Drain(listener.get()) == std::vector<std::pair<uint32_t, uint32_t>>{
                                     {uint32_t(Id(2, 1, 0x10)), 1}, {uint32_t(Id(2, 3, 0x13)), 4}});
  listener->ReleaseHandle();
}

TEST_CASE("Notifications arrive in broadcast order; a matched dequeue keeps the rest in order",
          "[kernel][notify]") {
  auto listener = Listen(1ull << 5);
  auto* kernel = rex::testing::Kernel();
  const auto a = Id(5, 0, 1), b = Id(5, 0, 2), c = Id(5, 0, 3);
  kernel->BroadcastNotification(a, 10);
  kernel->BroadcastNotification(b, 20);
  kernel->BroadcastNotification(c, 30);
  kernel->BroadcastNotification(b, 21);

  uint32_t data = 0;
  REQUIRE(listener->DequeueNotification(b, &data));
  CHECK(data == 20);  // the first b
  CHECK(Drain(listener.get()) == std::vector<std::pair<uint32_t, uint32_t>>{
                                     {uint32_t(a), 10}, {uint32_t(c), 30}, {uint32_t(b), 21}});
  CHECK_FALSE(listener->DequeueNotification(b, &data));
  listener->ReleaseHandle();
}

TEST_CASE("A listener the guest closed stops receiving broadcasts", "[kernel][notify]") {
  auto listener = Listen(1ull << 7);
  auto* kernel = rex::testing::Kernel();
  kernel->BroadcastNotification(Id(7, 0, 1), 1);
  CHECK(Drain(listener.get()).size() == 1);

  // XCloseHandle on the listener: the kernel stops holding and feeding it.
  REQUIRE(kernel->object_table()->ReleaseHandle(listener->handle()) == X_STATUS_SUCCESS);
  kernel->BroadcastNotification(Id(7, 0, 2), 2);
  CHECK(Drain(listener.get()).empty());
}

TEST_CASE("Only the first listener for system notifications gets the startup set",
          "[kernel][notify]") {
  auto first = Listen(1ull << 0);
  auto second = Listen(1ull << 0);
  const auto startup = Drain(first.get());
  // XN_SYS_UI on/off, XN_SYS_SIGNINCHANGED x2, input device changed/config x2 each.
  REQUIRE(startup.size() == 8);
  CHECK(startup[0] == std::pair<uint32_t, uint32_t>{0x9, 1});
  CHECK(startup[1] == std::pair<uint32_t, uint32_t>{0x9, 0});
  CHECK(startup[2] == std::pair<uint32_t, uint32_t>{0xA, 1});
  CHECK(Drain(second.get()).empty());
  first->ReleaseHandle();
  second->ReleaseHandle();
}

TEST_CASE("Title launch requests are classified against the compiled module", "[kernel][launch]") {
  const std::string running = "game:\\default.xex";
  auto dashboard = ClassifyLaunch(running, std::nullopt);
  CHECK(dashboard.kind == LaunchKind::kDashboard);
  CHECK(dashboard.path.empty());

  auto self_empty = ClassifyLaunch(running, std::string_view(""));
  CHECK(self_empty.kind == LaunchKind::kRelaunchSelf);
  CHECK(self_empty.path == "game:\\default.xex");

  auto self_case = ClassifyLaunch(running, std::string_view("GAME:\\Default.XEX"));
  CHECK(self_case.kind == LaunchKind::kRelaunchSelf);

  auto bare = ClassifyLaunch(running, std::string_view("mp.xex"));
  CHECK(bare.kind == LaunchKind::kOtherModule);
  CHECK(bare.path == "game:\\mp.xex");

  auto other = ClassifyLaunch(running, std::string_view("game:\\bin\\mp.xex"));
  CHECK(other.kind == LaunchKind::kOtherModule);
  CHECK(other.path == "game:\\bin\\mp.xex");
}
