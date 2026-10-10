/**
 * @file        rex/codegen/manifest.h
 * @brief       Manifest TOML parser for multi-binary projects
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <rex/codegen/config.h>

namespace rex::codegen {

struct BinaryConfig {
  RecompilerConfig recompiler;
  std::string guestPath;
};

struct TitleUpdateBuild {
  uint32_t version = 0;
  std::filesystem::path package;
  BinaryConfig binary;
};

std::string CanonicalizeModuleGuestPath(std::string_view path, std::string_view project_name = {});

struct ManifestConfig {
  std::string projectName;
  std::optional<std::string> sdkVersion;
  std::filesystem::path manifestPath;
  std::optional<std::string> gameRoot;

  std::filesystem::path manifestDir;
  BinaryConfig entrypoint;
  std::vector<BinaryConfig> modules;
  std::vector<TitleUpdateBuild> titleUpdates;

  static std::optional<ManifestConfig> Load(const std::filesystem::path& path);

  static bool IsManifest(const std::filesystem::path& path);

  static bool WriteSdkVersionStamp(const std::filesystem::path& path, std::string_view version);
};

}
