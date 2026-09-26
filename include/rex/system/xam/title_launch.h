/**
 * @file        system/xam/title_launch.h
 * @brief       What XamLoaderLaunchTitle can do in a statically compiled title
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace rex::system::xam {

// The outcome of a title asking XAM to launch an executable.
enum class LaunchKind {
  // No name: return to the dashboard. There is none, so the title ends.
  kDashboard,
  // The executable this binary was compiled from, launched again.
  kRelaunchSelf,
  // Another executable. Only the compiled module exists in this binary.
  kOtherModule,
};

struct LaunchRequest {
  LaunchKind kind;
  // Full guest path of the requested executable (empty for the dashboard).
  std::string path;
};

// Resolves a launch name the way XamLoaderLaunchTitle does: empty means the
// title's own default.xex, a bare file name is taken relative to the running
// executable's directory. Comparison with the running module ignores case.
LaunchRequest ClassifyLaunch(std::string_view running_module_path,
                             std::optional<std::string_view> requested);

}  // namespace rex::system::xam
