// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <rex/system/release_update.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <charconv>
#include <fstream>
#include <ranges>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

// clang-format off
#include <windows.h>
#include <bcrypt.h>
// clang-format on

namespace rex::system::update {
namespace {

namespace fs = std::filesystem;

constexpr std::string_view kAddedFilesList = "added-files.txt";

std::optional<uint32_t> ParseNumber(std::string_view text) {
  uint32_t value = 0;
  if (text.empty() || (text.size() > 1 && text.front() == '0')) {
    return std::nullopt;
  }
  auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), value);
  if (error != std::errc() || end != text.data() + text.size()) {
    return std::nullopt;
  }
  return value;
}

bool IsNumericIdentifier(std::string_view identifier) {
  return !identifier.empty() && std::ranges::all_of(identifier, [](char c) {
    return std::isdigit(static_cast<unsigned char>(c)) != 0;
  });
}

std::strong_ordering ComparePrerelease(std::string_view a, std::string_view b) {
  if (a.empty() || b.empty()) {
    return a.empty() <=> b.empty();
  }
  auto a_parts = std::views::split(a, '.');
  auto b_parts = std::views::split(b, '.');
  auto a_it = a_parts.begin();
  auto b_it = b_parts.begin();
  for (; a_it != a_parts.end() && b_it != b_parts.end(); ++a_it, ++b_it) {
    const std::string_view a_id((*a_it).begin(), (*a_it).end());
    const std::string_view b_id((*b_it).begin(), (*b_it).end());
    const bool a_numeric = IsNumericIdentifier(a_id);
    const bool b_numeric = IsNumericIdentifier(b_id);
    if (a_numeric && b_numeric) {
      if (auto order = a_id.size() <=> b_id.size(); order != 0) {
        return order;
      }
    } else if (a_numeric != b_numeric) {
      return a_numeric ? std::strong_ordering::less : std::strong_ordering::greater;
    }
    if (auto order = a_id <=> b_id; order != 0) {
      return order;
    }
  }
  return (a_it == a_parts.end()) == (b_it == b_parts.end())
             ? std::strong_ordering::equal
             : (a_it == a_parts.end() ? std::strong_ordering::less : std::strong_ordering::greater);
}

std::string ToLowerHex(std::string_view text) {
  std::string lower(text);
  std::ranges::transform(lower, lower.begin(),
                         [](char c) { return char(std::tolower(static_cast<unsigned char>(c))); });
  return lower;
}

bool RelocateFile(const fs::path& from, const fs::path& to, std::string* error) {
  std::error_code code;
  fs::create_directories(to.parent_path(), code);
  fs::rename(from, to, code);
  if (code) {
    code.clear();
    fs::copy_file(from, to, fs::copy_options::overwrite_existing, code);
    if (!code) {
      fs::remove(from, code);
      code.clear();
    }
  }
  if (code && error) {
    *error = fmt::format("moving {} to {}: {}", from.string(), to.string(), code.message());
  }
  return !code;
}

std::vector<fs::path> RelativeFiles(const fs::path& root) {
  std::vector<fs::path> files;
  std::error_code code;
  for (const auto& entry : fs::recursive_directory_iterator(root, code)) {
    if (entry.is_regular_file()) {
      files.push_back(fs::relative(entry.path(), root));
    }
  }
  return files;
}

void WriteAddedFilesList(const fs::path& previous_folder, const std::vector<fs::path>& added) {
  std::ofstream list(previous_folder / kAddedFilesList);
  for (const fs::path& path : added) {
    list << path.generic_string() << "\n";
  }
}

}  // namespace

std::optional<ReleaseVersion> ReleaseVersion::Parse(std::string_view text) {
  if (!text.empty() && (text.front() == 'v' || text.front() == 'V')) {
    text.remove_prefix(1);
  }
  ReleaseVersion version;
  const size_t dash = text.find('-');
  std::string_view core = text.substr(0, dash);
  if (dash != std::string_view::npos) {
    version.prerelease = std::string(text.substr(dash + 1));
    if (version.prerelease.empty()) {
      return std::nullopt;
    }
  }
  std::array<uint32_t*, 3> fields = {&version.major, &version.minor, &version.patch};
  for (size_t i = 0; i < fields.size(); ++i) {
    const size_t dot = core.find('.');
    if ((i < 2) == (dot == std::string_view::npos)) {
      return std::nullopt;
    }
    auto number = ParseNumber(core.substr(0, dot));
    if (!number) {
      return std::nullopt;
    }
    *fields[i] = *number;
    core = dot == std::string_view::npos ? std::string_view() : core.substr(dot + 1);
  }
  return version;
}

std::string ReleaseVersion::ToString() const {
  return prerelease.empty() ? fmt::format("{}.{}.{}", major, minor, patch)
                            : fmt::format("{}.{}.{}-{}", major, minor, patch, prerelease);
}

std::strong_ordering operator<=>(const ReleaseVersion& a, const ReleaseVersion& b) {
  if (auto order = std::tie(a.major, a.minor, a.patch) <=> std::tie(b.major, b.minor, b.patch);
      order != 0) {
    return order;
  }
  return ComparePrerelease(a.prerelease, b.prerelease);
}

std::vector<Release> ParseGitHubReleases(std::string_view json) {
  std::vector<Release> releases;
  const auto document = nlohmann::json::parse(json, nullptr, false);
  if (!document.is_array()) {
    return releases;
  }
  for (const auto& entry : document) {
    if (!entry.is_object() || entry.value("draft", false)) {
      continue;
    }
    const std::string tag = entry.value("tag_name", "");
    auto version = ReleaseVersion::Parse(tag);
    if (!version) {
      continue;
    }
    Release release;
    release.version = *version;
    release.tag = tag;
    release.notes = entry.value("body", "");
    release.prerelease = entry.value("prerelease", false);
    if (auto assets = entry.find("assets"); assets != entry.end() && assets->is_array()) {
      for (const auto& asset : *assets) {
        release.assets.push_back({asset.value("name", ""), asset.value("browser_download_url", ""),
                                  asset.value("size", uint64_t(0))});
      }
    }
    releases.push_back(std::move(release));
  }
  return releases;
}

bool MatchesAssetPattern(std::string_view name, std::string_view pattern) {
  size_t name_index = 0;
  size_t pattern_index = 0;
  size_t star = std::string_view::npos;
  size_t star_name_index = 0;
  while (name_index < name.size()) {
    if (pattern_index < pattern.size() && pattern[pattern_index] == '*') {
      star = pattern_index++;
      star_name_index = name_index;
    } else if (pattern_index < pattern.size() && pattern[pattern_index] == name[name_index]) {
      ++pattern_index;
      ++name_index;
    } else if (star != std::string_view::npos) {
      pattern_index = star + 1;
      name_index = ++star_name_index;
    } else {
      return false;
    }
  }
  while (pattern_index < pattern.size() && pattern[pattern_index] == '*') {
    ++pattern_index;
  }
  return pattern_index == pattern.size();
}

std::optional<AvailableUpdate> FindUpdate(const std::vector<Release>& releases,
                                          const ReleaseVersion& current,
                                          std::string_view asset_pattern,
                                          bool include_prereleases) {
  std::optional<AvailableUpdate> best;
  for (const Release& release : releases) {
    if ((release.prerelease && !include_prereleases) || release.version <= current ||
        (best && release.version <= best->release.version)) {
      continue;
    }
    auto package = std::ranges::find_if(release.assets, [&](const ReleaseAsset& asset) {
      return MatchesAssetPattern(asset.name, asset_pattern);
    });
    if (package == release.assets.end()) {
      continue;
    }
    AvailableUpdate update{release, *package, std::nullopt};
    auto checksums = std::ranges::find_if(release.assets, [](const ReleaseAsset& asset) {
      return asset.name == kChecksumsAssetName;
    });
    if (checksums != release.assets.end()) {
      update.checksums = *checksums;
    }
    best = std::move(update);
  }
  return best;
}

std::map<std::string, std::string> ParseChecksums(std::string_view text) {
  std::map<std::string, std::string> checksums;
  for (auto line_range : std::views::split(text, '\n')) {
    std::string_view line(line_range.begin(), line_range.end());
    while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) {
      line.remove_suffix(1);
    }
    const size_t space = line.find(' ');
    if (space != 64 || line.size() <= space + 1) {
      continue;
    }
    std::string_view name = line.substr(space + 1);
    while (!name.empty() && (name.front() == ' ' || name.front() == '*')) {
      name.remove_prefix(1);
    }
    if (!name.empty()) {
      checksums[std::string(name)] = ToLowerHex(line.substr(0, space));
    }
  }
  return checksums;
}

std::string Sha256OfFile(const fs::path& file) {
  std::ifstream stream(file, std::ios::binary);
  if (!stream) {
    return {};
  }
  BCRYPT_ALG_HANDLE algorithm = nullptr;
  if (!BCRYPT_SUCCESS(
          BCryptOpenAlgorithmProvider(&algorithm, BCRYPT_SHA256_ALGORITHM, nullptr, 0))) {
    return {};
  }
  BCRYPT_HASH_HANDLE hash = nullptr;
  std::string result;
  if (BCRYPT_SUCCESS(BCryptCreateHash(algorithm, &hash, nullptr, 0, nullptr, 0, 0))) {
    std::vector<char> buffer(1 << 20);
    bool ok = true;
    while (ok && stream) {
      stream.read(buffer.data(), std::streamsize(buffer.size()));
      const ULONG read = ULONG(stream.gcount());
      ok = read == 0 ||
           BCRYPT_SUCCESS(BCryptHashData(hash, reinterpret_cast<PUCHAR>(buffer.data()), read, 0));
    }
    std::array<UCHAR, 32> digest{};
    if (ok && BCRYPT_SUCCESS(BCryptFinishHash(hash, digest.data(), ULONG(digest.size()), 0))) {
      for (UCHAR byte : digest) {
        result += fmt::format("{:02x}", byte);
      }
    }
    BCryptDestroyHash(hash);
  }
  BCryptCloseAlgorithmProvider(algorithm, 0);
  return result;
}

bool MatchesChecksum(const fs::path& file, const std::map<std::string, std::string>& checksums) {
  auto expected = checksums.find(file.filename().string());
  return expected != checksums.end() && Sha256OfFile(file) == expected->second;
}

fs::path FindPackageRoot(const fs::path& unpacked) {
  std::error_code code;
  std::vector<fs::directory_entry> entries;
  for (const auto& entry : fs::directory_iterator(unpacked, code)) {
    entries.push_back(entry);
  }
  return entries.size() == 1 && entries.front().is_directory() ? entries.front().path() : unpacked;
}

bool InstallStagedUpdate(const fs::path& install_folder, const fs::path& package_root,
                         const fs::path& previous_folder, std::string* error) {
  std::error_code code;
  fs::remove_all(previous_folder, code);
  fs::create_directories(previous_folder, code);
  if (code) {
    if (error) {
      *error = fmt::format("creating {}: {}", previous_folder.string(), code.message());
    }
    return false;
  }
  std::vector<fs::path> added;
  for (const fs::path& relative : RelativeFiles(package_root)) {
    const fs::path installed = install_folder / relative;
    const bool replaces = fs::exists(installed);
    bool ok = !replaces || RelocateFile(installed, previous_folder / relative, error);
    ok = ok && RelocateFile(package_root / relative, installed, error);
    if (!ok) {
      WriteAddedFilesList(previous_folder, added);
      std::string restore_error;
      RestorePreviousVersion(install_folder, previous_folder, &restore_error);
      return false;
    }
    if (!replaces) {
      added.push_back(relative);
    }
  }
  WriteAddedFilesList(previous_folder, added);
  return true;
}

bool RestorePreviousVersion(const fs::path& install_folder, const fs::path& previous_folder,
                            std::string* error) {
  std::error_code code;
  if (!fs::is_directory(previous_folder, code)) {
    if (error) {
      *error = fmt::format("no previous version in {}", previous_folder.string());
    }
    return false;
  }
  bool ok = true;
  std::ifstream added_list(previous_folder / kAddedFilesList);
  for (std::string line; std::getline(added_list, line);) {
    if (!line.empty()) {
      fs::remove(install_folder / fs::path(line), code);
    }
  }
  added_list.close();
  for (const fs::path& relative : RelativeFiles(previous_folder)) {
    if (relative == fs::path(kAddedFilesList)) {
      continue;
    }
    ok = RelocateFile(previous_folder / relative, install_folder / relative, error) && ok;
  }
  if (ok) {
    fs::remove_all(previous_folder, code);
  }
  return ok;
}

bool UnpackZip(const fs::path& zip, const fs::path& destination, std::string* error) {
  std::error_code code;
  fs::create_directories(destination, code);
  wchar_t system_folder[MAX_PATH] = {};
  GetSystemDirectoryW(system_folder, MAX_PATH);
  const fs::path tar = fs::path(system_folder) / L"tar.exe";
  std::wstring command_line = L"\"" + tar.wstring() + L"\" -xf \"" + zip.wstring() + L"\" -C \"" +
                              destination.wstring() + L"\"";
  STARTUPINFOW startup{};
  startup.cb = sizeof(startup);
  PROCESS_INFORMATION process = {};
  if (!CreateProcessW(tar.c_str(), command_line.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW,
                      nullptr, nullptr, &startup, &process)) {
    if (error) {
      *error = fmt::format("starting {} failed (error {})", tar.string(), GetLastError());
    }
    return false;
  }
  WaitForSingleObject(process.hProcess, INFINITE);
  DWORD exit_code = 1;
  GetExitCodeProcess(process.hProcess, &exit_code);
  CloseHandle(process.hThread);
  CloseHandle(process.hProcess);
  if (exit_code != 0 && error) {
    *error = fmt::format("unpacking {} failed (tar exit code {})", zip.string(), exit_code);
  }
  return exit_code == 0;
}

std::wstring BuildUpdateHelperCommandLine(const UpdateHelperLaunch& launch,
                                          uint32_t wait_process_id) {
  auto quoted = [](const fs::path& path) { return L"\"" + path.wstring() + L"\""; };
  std::wstring command_line =
      quoted(launch.helper) + L" --wait " + std::to_wstring(wait_process_id) + L" --install " +
      quoted(launch.install_folder) + L" --previous " + quoted(launch.previous_folder);
  if (launch.rollback) {
    command_line += L" --rollback";
  } else {
    command_line += L" --package " + quoted(launch.package_root);
  }
  if (!launch.relaunch.empty()) {
    command_line += L" --launch " + quoted(launch.relaunch);
  }
  return command_line;
}

bool StartUpdateHelper(const UpdateHelperLaunch& launch, const fs::path& helper_copy,
                       std::string* error) {
  std::error_code code;
  fs::create_directories(helper_copy.parent_path(), code);
  fs::copy_file(launch.helper, helper_copy, fs::copy_options::overwrite_existing, code);
  if (code) {
    if (error) {
      *error = fmt::format("copying {}: {}", launch.helper.string(), code.message());
    }
    return false;
  }
  UpdateHelperLaunch copied = launch;
  copied.helper = helper_copy;
  std::wstring command_line = BuildUpdateHelperCommandLine(copied, GetCurrentProcessId());
  STARTUPINFOW startup{};
  startup.cb = sizeof(startup);
  PROCESS_INFORMATION process = {};
  if (!CreateProcessW(helper_copy.c_str(), command_line.data(), nullptr, nullptr, FALSE, 0, nullptr,
                      helper_copy.parent_path().c_str(), &startup, &process)) {
    if (error) {
      *error = fmt::format("starting {} failed (error {})", helper_copy.string(), GetLastError());
    }
    return false;
  }
  CloseHandle(process.hThread);
  CloseHandle(process.hProcess);
  return true;
}

}  // namespace rex::system::update
