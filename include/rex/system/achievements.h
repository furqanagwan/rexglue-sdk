/**
 * @file        rex/system/achievements.h
 * @brief       Convenience facade over the live AchievementManager for hooks.
 *
 * @copyright   Copyright (c) 2026 Rien Gupta <rgupta9@scu.edu>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once

#include <cstdint>

#include <rex/system/achievement_store.h>

namespace rex::system {

bool RegisterAchievement(AchievementInfo info);

bool UnlockAchievement(uint32_t id, bool show_toast = true);

bool IsAchievementUnlocked(uint32_t id);

}
