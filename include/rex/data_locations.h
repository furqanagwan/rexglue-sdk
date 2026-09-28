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

// %USERPROFILE%\Saved Games (FOLDERID_SavedGames). The GDK's advice for saves
// a title keeps itself: OneDrive does not sync it by default.
std::filesystem::path GetSavedGamesFolder();

// %LOCALAPPDATA% (FOLDERID_LocalAppData): per-user, per-machine data such as
// caches, logs and settings.
std::filesystem::path GetLocalAppDataFolder();

// Default per-title locations. Saves go under Saved Games; everything the
// title can rebuild or that belongs to this machine goes under local app data.
struct TitleDataLocations {
  std::filesystem::path user_data;  // Saved Games\<name>
  std::filesystem::path local;      // %LOCALAPPDATA%\<name>
  std::filesystem::path cache;      // %LOCALAPPDATA%\<name>\cache
  std::filesystem::path logs;       // %LOCALAPPDATA%\<name>\logs
  std::filesystem::path config;     // %LOCALAPPDATA%\<name>\<name>.toml
};

TitleDataLocations DefaultTitleDataLocations(const std::filesystem::path& saved_games,
                                             const std::filesystem::path& local_app_data,
                                             std::string_view name);

// The game files beside the executable: `<exe_dir>\game` or `<exe_dir>`
// itself, whichever holds `default.xex` first. Empty when neither does.
std::filesystem::path FindGameDataRoot(const std::filesystem::path& exe_dir);

// Result of moving a title's user data out of its old default location.
struct LegacyDataMove {
  bool moved = false;        // renamed into place; the old folder is gone
  bool copied = false;       // copied (another volume); the old folder stays
  bool moved_cache = false;  // its cache went to the new cache location
  std::string error;         // why nothing was moved, if something failed
};

// Moves `legacy_user` (the old Documents\<name>) to `user_data` once, when the
// old folder exists and the new one does not. A rename is tried first; across
// volumes (for example Documents redirected to OneDrive on another drive) the
// data is copied and the old folder left in place. A cache folder inside it
// moves to `cache` first; it is never copied, and goes along only with a
// rename when it could not be moved on its own. A failed copy is removed, so the next start tries
// again.
LegacyDataMove MoveLegacyUserData(const std::filesystem::path& legacy_user,
                                  const std::filesystem::path& user_data,
                                  const std::filesystem::path& cache);

}  // namespace rex::filesystem
