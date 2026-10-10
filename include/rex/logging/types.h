/**
 * @file        rex/logging/types.h
 * @brief       Log category types, constants, and configuration
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <spdlog/spdlog.h>

namespace rex {

struct LogCategoryId {
  uint16_t id;
  constexpr explicit LogCategoryId(uint16_t id) : id(id) {}
  constexpr bool operator==(const LogCategoryId&) const = default;
};

struct LogCategoryEntry {
  std::string name;
  std::shared_ptr<spdlog::logger> logger;
  std::optional<LogCategoryId> parent;
  bool has_explicit_level = false;
};

#if defined(NDEBUG)
inline constexpr auto kDefaultLogLevel = spdlog::level::info;
inline constexpr auto kVerboseLogLevel = spdlog::level::trace;
#else
inline constexpr auto kDefaultLogLevel = spdlog::level::debug;
inline constexpr auto kVerboseLogLevel = spdlog::level::trace;
#endif

struct LogConfig {
  spdlog::level::level_enum default_level = spdlog::level::info;

  bool log_to_console = false;

  std::filesystem::path log_file;

  std::string console_pattern = "[%^%l%$] [%n] [t%t] %v";

  std::string file_pattern = "[%Y-%m-%d %H:%M:%S.%e] [%l] [%n] [t%t] %v";

  spdlog::level::level_enum flush_level = spdlog::level::info;

  std::map<std::string, spdlog::level::level_enum> category_levels;

  std::vector<spdlog::sink_ptr> extra_sinks;

  std::map<std::string, std::vector<spdlog::sink_ptr>> category_sinks;

  bool category_sinks_exclusive = false;

  std::string app_name;
  std::filesystem::path log_dir;
  uint64_t dir_budget_bytes = 0;
  std::chrono::seconds flush_interval{0};
};

}
