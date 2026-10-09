// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#pragma once

#include <compare>
#include <cstdint>
#include <filesystem>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rex::system::update {

struct ReleaseVersion {
  uint32_t major = 0;
  uint32_t minor = 0;
  uint32_t patch = 0;
  std::string prerelease;

  static std::optional<ReleaseVersion> Parse(std::string_view text);
  std::string ToString() const;

  friend std::strong_ordering operator<=>(const ReleaseVersion& a, const ReleaseVersion& b);
  friend bool operator==(const ReleaseVersion& a, const ReleaseVersion& b) {
    return (a <=> b) == std::strong_ordering::equal;
  }
};

struct ReleaseAsset {
  std::string name;
  std::string download_url;
  uint64_t size = 0;
};

struct Release {
  ReleaseVersion version;
  std::string tag;
  std::string notes;
  bool prerelease = false;
  std::vector<ReleaseAsset> assets;
};

struct AvailableUpdate {
  Release release;
  ReleaseAsset package;
  std::optional<ReleaseAsset> checksums;
};

inline constexpr std::string_view kChecksumsAssetName = "SHA256SUMS.txt";

std::vector<Release> ParseGitHubReleases(std::string_view json);
bool MatchesAssetPattern(std::string_view name, std::string_view pattern);
std::optional<AvailableUpdate> FindUpdate(const std::vector<Release>& releases,
                                          const ReleaseVersion& current,
                                          std::string_view asset_pattern, bool include_prereleases);

std::map<std::string, std::string> ParseChecksums(std::string_view text);
std::string Sha256OfFile(const std::filesystem::path& file);
bool MatchesChecksum(const std::filesystem::path& file,
                     const std::map<std::string, std::string>& checksums);

std::filesystem::path FindPackageRoot(const std::filesystem::path& unpacked);
bool InstallStagedUpdate(const std::filesystem::path& install_folder,
                         const std::filesystem::path& package_root,
                         const std::filesystem::path& previous_folder, std::string* error);
bool RestorePreviousVersion(const std::filesystem::path& install_folder,
                            const std::filesystem::path& previous_folder, std::string* error);

bool UnpackZip(const std::filesystem::path& zip, const std::filesystem::path& destination,
               std::string* error);

struct UpdateHelperLaunch {
  std::filesystem::path helper;
  std::filesystem::path install_folder;
  std::filesystem::path package_root;
  std::filesystem::path previous_folder;
  std::filesystem::path relaunch;
  bool rollback = false;
};

std::wstring BuildUpdateHelperCommandLine(const UpdateHelperLaunch& launch,
                                          uint32_t wait_process_id);
bool StartUpdateHelper(const UpdateHelperLaunch& launch, const std::filesystem::path& helper_copy,
                       std::string* error);

}  // namespace rex::system::update
