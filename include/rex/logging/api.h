/**
 * @file        rex/logging/api.h
 * @brief       Logging system function declarations and CVAR declarations
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <rex/logging/types.h>

#include <cstdint>
#include <filesystem>
#include <span>
#include <string_view>

#include <rex/cvar.h>

REXCVAR_DECLARE(std::string, log_level);
REXCVAR_DECLARE(std::string, log_file);
REXCVAR_DECLARE(bool, log_verbose);
REXCVAR_DECLARE(bool, log_noisy);
REXCVAR_DECLARE(int32_t, log_flush_interval);

namespace rex {

void InitLogging(const LogConfig& config);

void InitLogging(std::filesystem::path log_file = {},
                 spdlog::level::level_enum level = spdlog::level::info);

void InitLogging(const char* log_file, spdlog::level::level_enum level = spdlog::level::info);

void InitLoggingEarly();

void ShutdownLogging();

void FlushLogging();

LogCategoryId RegisterLogCategory(const char* name);

LogCategoryId RegisterLogSubcategory(const char* name, LogCategoryId parent);
void SetRootLevel(LogCategoryId root, spdlog::level::level_enum level);

std::optional<LogCategoryId> FindCategory(const std::string& name);

std::span<const LogCategoryEntry> GetAllCategories();

spdlog::logger* GetLoggerRaw(LogCategoryId category);

std::shared_ptr<spdlog::logger> GetLogger(LogCategoryId category);

std::shared_ptr<spdlog::logger> GetLogger();

void SetCategoryLevel(LogCategoryId category, spdlog::level::level_enum level);

void SetAllLevels(spdlog::level::level_enum level);

void RegisterLogLevelCallback();

void AddSink(spdlog::sink_ptr sink);

void AddSink(LogCategoryId category, spdlog::sink_ptr sink);

void RemoveSink(spdlog::sink_ptr sink);

void RemoveSink(LogCategoryId category, spdlog::sink_ptr sink);

void ReplaceConsoleSink(spdlog::sink_ptr sink);

void SetConsolePattern(const std::string& pattern);

void SetFilePattern(const std::string& pattern);

std::optional<spdlog::level::level_enum> ParseLogLevel(const std::string& level_str);

spdlog::level::level_enum ParseLogLevelOr(const std::string& level_str,
                                          spdlog::level::level_enum default_level);

LogConfig BuildLogConfig(const std::string& cli_level,
                         const std::map<std::string, std::string>& category_levels);

void ApplyLogCvarOverrides(LogConfig& config);

void PruneLogDirectory(const std::filesystem::path& logs_dir, std::string_view app_name,
                       uint64_t budget_bytes);

const LogConfig& LoggingConfig();

std::map<std::string, std::string> ParseCategoryLevelsFromConfig(
    const std::filesystem::path& config_path);

}
