/**
 * @file        core/data_locations.cpp
 * @brief       Where a title keeps its files on a Windows PC
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <system_error>

#include <rex/data_locations.h>

namespace rex::filesystem {

namespace fs = std::filesystem;

TitleDataLocations DefaultTitleDataLocations(const fs::path& saved_games,
                                             const fs::path& local_app_data,
                                             std::string_view name) {
  TitleDataLocations locations;
  locations.user_data = saved_games / name;
  locations.local = local_app_data / name;
  locations.cache = locations.local / "cache";
  locations.logs = locations.local / "logs";
  locations.config = locations.local / (std::string(name) + ".toml");
  return locations;
}

fs::path FindGameDataRoot(const fs::path& exe_dir) {
  std::error_code ec;
  for (const auto& candidate : {exe_dir / "game", exe_dir}) {
    if (fs::is_regular_file(candidate / "default.xex", ec)) {
      return candidate;
    }
  }
  return {};
}

LegacyDataMove MoveLegacyUserData(const fs::path& legacy_user, const fs::path& user_data,
                                  const fs::path& cache) {
  LegacyDataMove result;
  std::error_code ec;
  if (legacy_user.empty() || !fs::is_directory(legacy_user, ec) || fs::exists(user_data, ec)) {
    return result;
  }
  fs::create_directories(user_data.parent_path(), ec);

  const fs::path legacy_cache = legacy_user / "cache";
  if (fs::is_directory(legacy_cache, ec) && !fs::exists(cache, ec)) {
    fs::create_directories(cache.parent_path(), ec);
    fs::rename(legacy_cache, cache, ec);
    result.moved_cache = !ec;
  }

  fs::rename(legacy_user, user_data, ec);
  if (!ec) {
    result.moved = true;
    return result;
  }

  fs::create_directories(user_data, ec);
  for (const auto& entry : fs::directory_iterator(legacy_user, ec)) {
    if (entry.path().filename() == "cache") {
      continue;
    }
    fs::copy(entry.path(), user_data / entry.path().filename(),
             fs::copy_options::recursive | fs::copy_options::copy_symlinks, ec);
    if (ec) {
      break;
    }
  }
  if (ec) {
    result.error = ec.message();
    std::error_code cleanup;
    fs::remove_all(user_data, cleanup);
    return result;
  }
  result.copied = true;
  return result;
}

}
