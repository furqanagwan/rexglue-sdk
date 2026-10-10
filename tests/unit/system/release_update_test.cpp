// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <random>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include <rex/system/release_update.h>

namespace {

namespace fs = std::filesystem;
using namespace rex::system::update;

ReleaseVersion Version(std::string_view text) {
  auto version = ReleaseVersion::Parse(text);
  REQUIRE(version);
  return *version;
}

void WriteText(const fs::path& path, std::string_view text) {
  fs::create_directories(path.parent_path());
  std::ofstream(path, std::ios::binary) << text;
}

std::string ReadText(const fs::path& path) {
  std::ifstream stream(path, std::ios::binary);
  return {std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
}

struct TemporaryFolder {
  fs::path path =
      fs::temp_directory_path() / ("rex_release_update_" + std::to_string(std::random_device()()));
  TemporaryFolder() { fs::create_directories(path); }
  ~TemporaryFolder() {
    std::error_code code;
    fs::remove_all(path, code);
  }
};

constexpr std::string_view kReleasesJson = R"([
  {"tag_name": "v0.2.0-alpha.1", "prerelease": true, "draft": true, "body": "draft",
   "assets": [{"name": "007-QuantumOfSolace-0.2.0-alpha.1-win-x64.zip",
               "browser_download_url": "https://example/draft.zip", "size": 1}]},
  {"tag_name": "v0.1.0-alpha.2", "prerelease": true, "draft": false, "body": "Second alpha",
   "assets": [{"name": "007-QuantumOfSolace-0.1.0-alpha.2-win-x64.zip",
               "browser_download_url": "https://example/qos2.zip", "size": 200},
              {"name": "007-Legends-0.1.0-alpha.2-win-x64.zip",
               "browser_download_url": "https://example/legends2.zip", "size": 300},
              {"name": "SHA256SUMS.txt",
               "browser_download_url": "https://example/sums2.txt", "size": 10}]},
  {"tag_name": "v0.1.0-alpha.1", "prerelease": true, "draft": false, "body": "First alpha",
   "assets": [{"name": "007-QuantumOfSolace-0.1.0-alpha.1-win-x64.zip",
               "browser_download_url": "https://example/qos1.zip", "size": 100}]},
  {"tag_name": "not-a-version", "prerelease": false, "draft": false, "assets": []}
])";

}

TEST_CASE("Release versions order as Semantic Versioning", "[system][update]") {
  CHECK(Version("0.1.0-alpha.1") < Version("0.1.0-alpha.2"));
  CHECK(Version("0.1.0-alpha.2") < Version("0.1.0-alpha.10"));
  CHECK(Version("0.1.0-alpha.10") < Version("0.1.0-beta.1"));
  CHECK(Version("0.1.0-beta.1") < Version("0.1.0"));
  CHECK(Version("0.1.0") < Version("0.2.0-alpha.1"));
  CHECK(Version("0.9.0") < Version("0.10.0"));
  CHECK(Version("1.0.0-alpha") < Version("1.0.0-alpha.1"));
  CHECK(Version("v0.1.0-alpha.1") == Version("0.1.0-alpha.1"));
  CHECK(Version("v0.1.0-alpha.1").ToString() == "0.1.0-alpha.1");
}

TEST_CASE("Malformed versions are rejected", "[system][update]") {
  for (std::string_view text : {"", "1", "1.2", "1.2.3.4", "01.2.3", "1.2.3-", "a.b.c", "1.2.x"}) {
    INFO(text);
    CHECK_FALSE(ReleaseVersion::Parse(text));
  }
}

TEST_CASE("GitHub releases are read without drafts or unversioned tags", "[system][update]") {
  const auto releases = ParseGitHubReleases(kReleasesJson);
  REQUIRE(releases.size() == 2);
  CHECK(releases[0].tag == "v0.1.0-alpha.2");
  CHECK(releases[0].notes == "Second alpha");
  CHECK(releases[0].prerelease);
  CHECK(releases[0].assets.size() == 3);
  CHECK(ParseGitHubReleases("not json").empty());
}

TEST_CASE("The newest matching release newer than the running one is offered", "[system][update]") {
  const auto releases = ParseGitHubReleases(kReleasesJson);
  const auto update =
      FindUpdate(releases, Version("0.1.0-alpha.1"), "007-QuantumOfSolace-*-win-x64.zip", true);
  REQUIRE(update);
  CHECK(update->release.tag == "v0.1.0-alpha.2");
  CHECK(update->package.download_url == "https://example/qos2.zip");
  REQUIRE(update->checksums);
  CHECK(update->checksums->download_url == "https://example/sums2.txt");

  CHECK_FALSE(FindUpdate(releases, Version("0.1.0-alpha.2"), "007-QuantumOfSolace-*", true));
  CHECK_FALSE(FindUpdate(releases, Version("0.1.0-alpha.1"), "007-BloodStone-*", true));
  CHECK_FALSE(FindUpdate(releases, Version("0.1.0-alpha.1"), "007-QuantumOfSolace-*", false));
}

TEST_CASE("Asset patterns match with wildcards", "[system][update]") {
  CHECK(MatchesAssetPattern("007-Legends-0.1.0-alpha.1-win-x64.zip", "007-Legends-*-win-x64.zip"));
  CHECK(MatchesAssetPattern("abc", "*"));
  CHECK(MatchesAssetPattern("abc", "a*c"));
  CHECK(MatchesAssetPattern("abc", "abc"));
  CHECK_FALSE(MatchesAssetPattern("abc", "abd"));
  CHECK_FALSE(MatchesAssetPattern("007-Legends-1-win-x64.zip.part", "007-Legends-*-win-x64.zip"));
}

TEST_CASE("Checksum lists are read and files are verified", "[system][update]") {
  TemporaryFolder folder;
  const fs::path file = folder.path / "package.zip";
  WriteText(file, "abc");
  CHECK(Sha256OfFile(file) == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");

  const auto checksums = ParseChecksums(
      "BA7816BF8F01CFEA414140DE5DAE2223B00361A396177A9CB410FF61F20015AD  package.zip\r\n"
      "0000000000000000000000000000000000000000000000000000000000000000 *other.zip\n"
      "not a checksum line\n");
  REQUIRE(checksums.size() == 2);
  CHECK(checksums.at("other.zip") == std::string(64, '0'));
  CHECK(MatchesChecksum(file, checksums));
  WriteText(file, "abd");
  CHECK_FALSE(MatchesChecksum(file, checksums));
  CHECK_FALSE(MatchesChecksum(folder.path / "missing.zip", checksums));
}

TEST_CASE("A staged update replaces files and can be rolled back", "[system][update]") {
  TemporaryFolder folder;
  const fs::path install = folder.path / "install";
  const fs::path unpacked = folder.path / "staging";
  const fs::path previous = install / "previous";
  WriteText(install / "game.exe", "old game");
  WriteText(install / "rexruntime.dll", "old runtime");
  WriteText(install / "keep.toml", "settings");
  WriteText(unpacked / "007-Game-0.1.0-alpha.2-win-x64" / "game.exe", "new game");
  WriteText(unpacked / "007-Game-0.1.0-alpha.2-win-x64" / "rexruntime.dll", "new runtime");
  WriteText(unpacked / "007-Game-0.1.0-alpha.2-win-x64" / "shader_cache" / "new.xsh", "cache");

  const fs::path package_root = FindPackageRoot(unpacked);
  CHECK(package_root.filename() == "007-Game-0.1.0-alpha.2-win-x64");

  std::string error;
  REQUIRE(InstallStagedUpdate(install, package_root, previous, &error));
  CHECK(error.empty());
  CHECK(ReadText(install / "game.exe") == "new game");
  CHECK(ReadText(install / "rexruntime.dll") == "new runtime");
  CHECK(ReadText(install / "shader_cache" / "new.xsh") == "cache");
  CHECK(ReadText(install / "keep.toml") == "settings");
  CHECK(ReadText(previous / "game.exe") == "old game");

  REQUIRE(RestorePreviousVersion(install, previous, &error));
  CHECK(ReadText(install / "game.exe") == "old game");
  CHECK(ReadText(install / "rexruntime.dll") == "old runtime");
  CHECK_FALSE(fs::exists(install / "shader_cache" / "new.xsh"));
  CHECK(ReadText(install / "keep.toml") == "settings");
  CHECK_FALSE(fs::exists(previous));
}

TEST_CASE("Rolling back without a previous version fails", "[system][update]") {
  TemporaryFolder folder;
  std::string error;
  CHECK_FALSE(RestorePreviousVersion(folder.path, folder.path / "previous", &error));
  CHECK_FALSE(error.empty());
}

TEST_CASE("A release zip unpacks with Windows' tar", "[system][update]") {
  TemporaryFolder folder;
  const fs::path source = folder.path / "source";
  WriteText(source / "007-Game-0.1.0-alpha.2-win-x64" / "game.exe", "new game");
  WriteText(source / "007-Game-0.1.0-alpha.2-win-x64" / "shader_cache" / "a.xsh", "cache");
  const fs::path zip = folder.path / "package.zip";
  const fs::path windows_tar = fs::path(std::getenv("SystemRoot")) / "System32" / "tar.exe";
  const std::string create = "\"\"" + windows_tar.string() + "\" -a -c -f \"" + zip.string() +
                             "\" -C \"" + source.string() + "\" 007-Game-0.1.0-alpha.2-win-x64\"";
  REQUIRE(std::system(create.c_str()) == 0);

  std::string error;
  const fs::path unpacked = folder.path / "unpacked";
  REQUIRE(UnpackZip(zip, unpacked, &error));
  const fs::path root = FindPackageRoot(unpacked);
  CHECK(root.filename() == "007-Game-0.1.0-alpha.2-win-x64");
  CHECK(ReadText(root / "game.exe") == "new game");
  CHECK(ReadText(root / "shader_cache" / "a.xsh") == "cache");

  CHECK_FALSE(UnpackZip(folder.path / "missing.zip", folder.path / "nothing", &error));
  CHECK_FALSE(error.empty());
}

TEST_CASE("The helper command line names every folder and the game to restart",
          "[system][update]") {
  UpdateHelperLaunch launch;
  launch.helper = LR"(C:\cache\rexglue-updater.exe)";
  launch.install_folder = LR"(C:\Games\007 QoS)";
  launch.package_root = LR"(C:\cache\updates\0.1.0-alpha.2\pkg)";
  launch.previous_folder = LR"(C:\Games\007 QoS\previous)";
  launch.relaunch = LR"(C:\Games\007 QoS\quantumofsolace.exe)";
  CHECK(BuildUpdateHelperCommandLine(launch, 42) ==
        LR"("C:\cache\rexglue-updater.exe" --wait 42 --install "C:\Games\007 QoS" )"
        LR"(--previous "C:\Games\007 QoS\previous" --package )"
        LR"("C:\cache\updates\0.1.0-alpha.2\pkg" --launch )"
        LR"("C:\Games\007 QoS\quantumofsolace.exe")");
  launch.rollback = true;
  CHECK(BuildUpdateHelperCommandLine(launch, 7) ==
        LR"("C:\cache\rexglue-updater.exe" --wait 7 --install "C:\Games\007 QoS" )"
        LR"(--previous "C:\Games\007 QoS\previous" --rollback --launch )"
        LR"("C:\Games\007 QoS\quantumofsolace.exe")");
}
