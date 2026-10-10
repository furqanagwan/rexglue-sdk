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

enum class LaunchKind {

  kDashboard,

  kRelaunchSelf,

  kOtherModule,
};

struct LaunchRequest {
  LaunchKind kind;

  std::string path;
};

LaunchRequest ClassifyLaunch(std::string_view running_module_path,
                             std::optional<std::string_view> requested);

}
