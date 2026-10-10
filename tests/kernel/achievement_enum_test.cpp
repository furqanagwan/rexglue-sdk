/**
 * @file        achievement_enum_test.cpp
 * @brief       Achievement enumerators start at the title's offset
 *
 * 007 Legends pages through its achievements with one enumerator per page
 * (offset 0, 25, 50, ...) until a page comes back short. With the offset
 * ignored every page was the first, so the title never stopped and grew a list
 * until its heap ran out (2026-10-01).
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <string>
#include <vector>

#include <rex/system/achievement_store.h>
#include <rex/types.h>

#include "kernel_fixture.h"

namespace rex::kernel::xam {
u32 XamUserCreateAchievementEnumerator_entry(u32 title_id, u32 user_index, u32 xuid, u32 flags,
                                             u32 offset, u32 count, mapped_u32 buffer_size_ptr,
                                             mapped_u32 handle_ptr);
uint32_t xeXamEnumerate(uint32_t handle, uint32_t flags, mapped_void buffer_ptr,
                        uint32_t buffer_size, uint32_t* items_returned, uint32_t overlapped_ptr);
}

namespace {

using rex::X_RESULT;
using rex::system::AchievementInfo;
using rex::testing::Kernel;

constexpr uint32_t kAchievementCount = 60;
constexpr uint32_t kPageSize = 25;

constexpr uint32_t kDetailsSize = 36;

struct Page {
  X_RESULT result = 0;
  uint32_t items = 0;
  uint32_t first_id = 0;
};

Page ReadPage(uint32_t offset) {
  auto* memory = Kernel()->memory();
  const uint32_t out = memory->SystemHeapAlloc(8);
  const uint32_t buffer = memory->SystemHeapAlloc(kDetailsSize * kPageSize);
  REQUIRE(rex::kernel::xam::XamUserCreateAchievementEnumerator_entry(
              0, 0, 0, 0, offset, kPageSize,
              mapped_u32(memory->TranslateVirtual<rex::be<uint32_t>*>(out), out),
              mapped_u32(memory->TranslateVirtual<rex::be<uint32_t>*>(out + 4), out + 4)) ==
          X_ERROR_SUCCESS);
  const uint32_t handle = *memory->TranslateVirtual<rex::be<uint32_t>*>(out + 4);
  Page page;
  page.result = rex::kernel::xam::xeXamEnumerate(
      handle, 0, mapped_void(memory->TranslateVirtual(buffer), buffer), kDetailsSize * kPageSize,
      &page.items, 0);
  page.first_id = *memory->TranslateVirtual<rex::be<uint32_t>*>(buffer);
  Kernel()->object_table()->ReleaseHandle(handle);
  memory->SystemHeapFree(buffer);
  memory->SystemHeapFree(out);
  return page;
}

}

TEST_CASE("Achievement enumerators page from the title's offset", "[kernel][xam]") {
  std::vector<AchievementInfo> achievements;
  for (uint32_t id = 1; id <= kAchievementCount; ++id) {
    AchievementInfo info;
    info.id = id;
    info.label = "Achievement " + std::to_string(id);
    achievements.push_back(info);
  }
  Kernel()->SetLoadedAchievements(achievements);

  const Page first = ReadPage(0);
  CHECK(first.result == X_ERROR_SUCCESS);
  CHECK(first.items == kPageSize);
  CHECK(first.first_id == 1);

  const Page second = ReadPage(25);
  CHECK(second.result == X_ERROR_SUCCESS);
  CHECK(second.items == kPageSize);
  CHECK(second.first_id == 26);

  const Page last = ReadPage(50);
  CHECK(last.result == X_ERROR_SUCCESS);
  CHECK(last.items == kAchievementCount - 50);
  CHECK(last.first_id == 51);

  CHECK(ReadPage(60).result == X_ERROR_NO_MORE_FILES);

  CHECK(ReadPage(1000).result == X_ERROR_NO_MORE_FILES);

  Kernel()->SetLoadedAchievements({});
}
