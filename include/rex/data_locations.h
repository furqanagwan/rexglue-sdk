/**
 * @file        rex/data_locations.h
 * @brief       Where a title keeps its files on a Windows PC, as an Xbox PC
 *              game does
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <filesystem>
#include <string>
#include <string_view>

namespace rex::filesystem {

std::filesystem::path GetSavedGamesFolder();

std::filesystem::path GetLocalAppDataFolder();

struct TitleDataLocations {
  std::filesystem::path user_data;
  std::filesystem::path local;
  std::filesystem::path cache;
  std::filesystem::path logs;
  std::filesystem::path config;
};

TitleDataLocations DefaultTitleDataLocations(const std::filesystem::path& saved_games,
                                             const std::filesystem::path& local_app_data,
                                             std::string_view name);

std::filesystem::path FindGameDataRoot(const std::filesystem::path& exe_dir);

struct LegacyDataMove {
  bool moved = false;
  bool copied = false;
  bool moved_cache = false;
  std::string error;
};

LegacyDataMove MoveLegacyUserData(const std::filesystem::path& legacy_user,
                                  const std::filesystem::path& user_data,
                                  const std::filesystem::path& cache);

}
