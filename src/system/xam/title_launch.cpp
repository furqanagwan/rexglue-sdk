/**
 * @file        system/xam/title_launch.cpp
 * @brief       What XamLoaderLaunchTitle can do in a statically compiled title
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/system/xam/title_launch.h>

#include <rex/string.h>

namespace rex::system::xam {

LaunchRequest ClassifyLaunch(std::string_view running_module_path,
                             std::optional<std::string_view> requested) {
  if (!requested) {
    return {LaunchKind::kDashboard, {}};
  }
  std::string path(*requested);
  if (path.empty()) {
    path = "game:\\default.xex";
  } else if (rex::string::utf8_find_name_from_guest_path(path) == path) {
    path = rex::string::utf8_join_guest_paths(
        rex::string::utf8_find_base_guest_path(running_module_path), path);
  }
  const bool same = rex::string::utf8_equal_case(path, running_module_path);
  return {same ? LaunchKind::kRelaunchSelf : LaunchKind::kOtherModule, std::move(path)};
}

}  // namespace rex::system::xam
