/**
 * @file        system/achievements.cpp
 * @brief       Convenience facade over the live AchievementManager.
 *
 * @copyright   Copyright (c) 2026 Rien Gupta <rgupta9@scu.edu>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <rex/system/achievements.h>

#include <cstdlib>
#include <string>
#include <string_view>
#include <utility>

#include <rex/cvar.h>
#include <rex/logging.h>

#include <rex/system/achievement_manager.h>
#include <rex/system/kernel_state.h>

namespace rex::system {

bool RegisterAchievement(AchievementInfo info) {
  auto* ks = kernel_state();
  if (!ks) {
    return false;
  }
  return ks->achievements().RegisterAchievement(std::move(info));
}

bool UnlockAchievement(uint32_t id, bool show_toast) {
  auto* ks = kernel_state();
  if (!ks) {
    return false;
  }
  auto result = ks->achievements().UnlockAchievement(
      id, show_toast ? AchievementNotification::kShow : AchievementNotification::kSuppress);
  return result == AchievementUnlockResult::kUnlocked;
}

bool IsAchievementUnlocked(uint32_t id) {
  auto* ks = kernel_state();
  if (!ks) {
    return false;
  }
  return ks->achievements().IsUnlocked(id);
}

}

namespace {

void ConsoleAchievementNotify(std::string_view args) {
  auto* ks = rex::system::kernel_state();
  if (!ks) {
    return;
  }
  auto& achievements = ks->achievements();
  const auto list = achievements.ListAchievements();

  uint32_t id = list.empty() ? 0 : list.front().id;
  if (args.find_first_not_of(' ') != std::string_view::npos) {
    id = uint32_t(std::strtoul(std::string(args).c_str(), nullptr, 10));
  }
  if (!achievements.ShowAchievementNotification(id)) {
    std::string ids;
    for (size_t i = 0; i < list.size() && i < 16; ++i) {
      ids += std::to_string(list[i].id) + " ";
    }
    REXLOG_INFO("achievement_notify: no achievement {}; this title has: {}", id, ids);
  }
}

}

REXCVAR_DEFINE_COMMAND_ARGS(achievement_notify, ConsoleAchievementNotify, "Console",
                            "Show achievement <id>'s unlock notification without unlocking it");
