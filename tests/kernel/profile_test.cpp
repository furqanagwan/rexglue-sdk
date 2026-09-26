/**
 * @file        profile_test.cpp
 * @brief       Profile setting lifetime, title isolation and durable saves (RG-GDK-017)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <filesystem>
#include <fstream>
#include <memory>
#include <thread>
#include <vector>

#include <rex/system/kernel_state.h>
#include <rex/system/xam/content_manager.h>
#include <rex/system/xam/user_profile.h>

#include "kernel_fixture.h"

using rex::X_RESULT;
using rex::system::xam::UserProfile;

namespace {

// Title-specific binary setting ids (XPROFILE_TITLE_SPECIFIC1-3).
constexpr uint32_t kTitleSpecific1 = 0x63E83FFF;
constexpr uint32_t kTitleSpecific2 = 0x63E83FFE;

// A setting that reports when it is destroyed.
struct TrackedSetting : UserProfile::BinarySetting {
  TrackedSetting(uint32_t id, std::vector<uint8_t> bytes, std::atomic<bool>* destroyed)
      : BinarySetting(id, bytes), destroyed(destroyed) {}
  ~TrackedSetting() override { *destroyed = true; }
  std::atomic<bool>* destroyed;
};

std::vector<uint8_t> Bytes(std::initializer_list<uint8_t> list) {
  return std::vector<uint8_t>(list);
}

std::vector<uint8_t> ValueOf(const std::shared_ptr<UserProfile::Setting>& setting) {
  return static_cast<UserProfile::BinarySetting*>(setting.get())->value;
}

std::filesystem::path SettingPath(uint32_t id) {
  return rex::testing::Kernel()->content_manager()->ResolveGameUserContentPath() /
         fmt::format("{:08X}", id);
}

}  // namespace

TEST_CASE("A setting a reader holds outlives its replacement", "[kernel][profile]") {
  UserProfile profile;
  profile.set_kernel_state(rex::testing::Kernel());
  std::atomic<bool> destroyed = false;
  profile.AddSetting(std::make_unique<TrackedSetting>(0x10040002, Bytes({1}), &destroyed));

  auto held = profile.GetSetting(0x10040002);
  REQUIRE(held);
  // Another thread writes the same setting while the reader still uses it.
  profile.AddSetting(std::make_unique<UserProfile::BinarySetting>(0x10040002, Bytes({2})));
  CHECK_FALSE(destroyed);
  CHECK(ValueOf(held) == Bytes({1}));
  CHECK(ValueOf(profile.GetSetting(0x10040002)) == Bytes({2}));
  held.reset();
  CHECK(destroyed);
}

TEST_CASE("Concurrent profile setting reads and writes stay consistent", "[kernel][profile]") {
  UserProfile profile;
  profile.set_kernel_state(rex::testing::Kernel());
  std::atomic<bool> stop = false;
  std::atomic<int> bad = 0;
  std::vector<std::thread> readers;
  for (int r = 0; r < 4; ++r) {
    readers.emplace_back([&] {
      while (!stop) {
        auto setting = profile.GetSetting(0x10040003);
        auto* binary = dynamic_cast<UserProfile::BinarySetting*>(setting.get());
        if (binary && binary->value.size() != 64) {
          ++bad;
        }
      }
    });
  }
  for (int i = 0; i < 2000; ++i) {
    profile.AddSetting(std::make_unique<UserProfile::BinarySetting>(
        0x10040003, std::vector<uint8_t>(64, uint8_t(i))));
  }
  stop = true;
  for (auto& t : readers) {
    t.join();
  }
  CHECK(bad == 0);
}

TEST_CASE("Title-specific settings are saved whole and read back", "[kernel][profile]") {
  UserProfile profile;
  profile.set_kernel_state(rex::testing::Kernel());
  const auto path = SettingPath(kTitleSpecific1);
  std::error_code ec;
  std::filesystem::remove(path, ec);

  CHECK(profile.AddSetting(
      std::make_unique<UserProfile::BinarySetting>(kTitleSpecific1, Bytes({9, 8, 7}))));
  CHECK(std::filesystem::file_size(path) == 3);
  CHECK_FALSE(std::filesystem::exists(path.string() + ".tmp"));

  // A fresh profile (a relaunch) reads it back for the same title.
  UserProfile relaunched;
  relaunched.set_kernel_state(rex::testing::Kernel());
  auto setting = relaunched.GetSetting(kTitleSpecific1);
  REQUIRE(setting);
  CHECK(setting->is_set);
  CHECK(ValueOf(setting) == Bytes({9, 8, 7}));
  std::filesystem::remove(path, ec);
}

TEST_CASE("A title-specific setting does not leak into a title without one", "[kernel][profile]") {
  UserProfile profile;
  profile.set_kernel_state(rex::testing::Kernel());
  const auto path = SettingPath(kTitleSpecific2);
  std::error_code ec;
  std::filesystem::remove(path, ec);

  // Loaded for another title (as after a title switch); the running title
  // has no saved copy.
  profile.AddSetting(std::make_unique<UserProfile::BinarySetting>(kTitleSpecific2, Bytes({5})));
  std::filesystem::remove(path, ec);
  profile.GetSetting(kTitleSpecific2)->loaded_title_id = 0x4D5307E6;

  auto setting = profile.GetSetting(kTitleSpecific2);
  REQUIRE(setting);
  CHECK_FALSE(setting->is_set);
  CHECK(ValueOf(setting).empty());
}

TEST_CASE("Closing content flushes it and reports a failed flush", "[kernel][content]") {
  auto* kernel = rex::testing::Kernel();
  rex::testing::TempDir root("rex_content_close");
  rex::system::xam::ContentManager content(kernel, root.path);
  const auto data = rex::testing::SaveData("CLOSE1");
  REQUIRE(content.CreateContent("close1", rex::testing::kXuid, data) == X_ERROR_SUCCESS);

  // No explicit flush: the header is still made durable on close.
  auto file = rex::testing::OpenGuestFile(kernel, "close1", "a.dat");
  rex::testing::WriteGuest(file.get(), "saved");
  file->ReleaseHandle();
  file.reset();
  CHECK(content.CloseContent("close1") == X_ERROR_SUCCESS);
  CHECK(std::filesystem::exists(rex::testing::HeaderPath(root.path, "CLOSE1")));
  CHECK(content.CloseContent("close1") == X_ERROR_FILE_NOT_FOUND);

  uint32_t license = 0;
  REQUIRE(content.OpenContent("close1", rex::testing::kXuid, data, license) == X_ERROR_SUCCESS);
  auto real = rex::testing::OpenGuestFile(kernel, "close1", "b.dat");
  rex::system::object_ref<rex::system::XFile> failing(
      new rex::system::XFile(kernel, new rex::testing::FailingFlushFile(real->entry()), true));
  // The failure is reported and the package is still closed.
  CHECK(content.CloseContent("close1") == X_ERROR_WRITE_FAULT);
  CHECK(content.FlushContent("close1") == X_ERROR_FILE_NOT_FOUND);
  failing.reset();
  real.reset();
}
