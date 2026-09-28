/**
 * @file        data_locations_test.cpp
 * @brief       Default title data locations and the one-time move out of
 *              Documents
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <fstream>
#include <string>

#include <rex/data_locations.h>

namespace fs = std::filesystem;
using namespace rex::filesystem;  // NOLINT

namespace {

struct TempRoot {
  fs::path path;
  explicit TempRoot(const char* name) {
    path = fs::temp_directory_path() / name;
    fs::remove_all(path);
    fs::create_directories(path);
  }
  ~TempRoot() {
    std::error_code ec;
    fs::remove_all(path, ec);
  }
};

void WriteFile(const fs::path& path, const std::string& text) {
  fs::create_directories(path.parent_path());
  std::ofstream(path, std::ios::binary) << text;
}

std::string ReadFile(const fs::path& path) {
  std::ifstream in(path, std::ios::binary);
  return std::string(std::istreambuf_iterator<char>(in), {});
}

}  // namespace

TEST_CASE("Default title data locations follow Xbox PC conventions", "[core][data_locations]") {
  const auto locations = DefaultTitleDataLocations("C:/Users/A/Saved Games",
                                                   "C:/Users/A/AppData/Local", "quantumofsolace");
  CHECK(locations.user_data == fs::path("C:/Users/A/Saved Games/quantumofsolace"));
  CHECK(locations.local == fs::path("C:/Users/A/AppData/Local/quantumofsolace"));
  CHECK(locations.cache == locations.local / "cache");
  CHECK(locations.logs == locations.local / "logs");
  CHECK(locations.config == locations.local / "quantumofsolace.toml");
}

TEST_CASE("Known folders resolve on this machine", "[core][data_locations]") {
  CHECK(fs::is_directory(GetSavedGamesFolder()));
  CHECK(fs::is_directory(GetLocalAppDataFolder()));
}

TEST_CASE("Game files are found beside the executable", "[core][data_locations]") {
  TempRoot root("rexglue_data_locations_game");
  CHECK(FindGameDataRoot(root.path).empty());

  WriteFile(root.path / "default.xex", "x");
  CHECK(FindGameDataRoot(root.path) == root.path);

  // A game folder wins over the executable's own folder.
  WriteFile(root.path / "game" / "default.xex", "x");
  CHECK(FindGameDataRoot(root.path) == root.path / "game");
}

TEST_CASE("Legacy user data moves once, cache separately", "[core][data_locations]") {
  TempRoot root("rexglue_data_locations_move");
  const auto legacy = root.path / "Documents" / "title";
  const auto user = root.path / "Saved Games" / "title";
  const auto cache = root.path / "Local" / "title" / "cache";
  WriteFile(legacy / "B13EBABEBABEBABE" / "save.bin", "save");
  WriteFile(legacy / "cache" / "shaders.bin", "cache");

  const auto first = MoveLegacyUserData(legacy, user, cache);
  CHECK(first.moved);
  CHECK_FALSE(first.copied);
  CHECK(first.moved_cache);
  CHECK(first.error.empty());
  CHECK_FALSE(fs::exists(legacy));
  CHECK(ReadFile(user / "B13EBABEBABEBABE" / "save.bin") == "save");
  CHECK_FALSE(fs::exists(user / "cache"));
  CHECK(ReadFile(cache / "shaders.bin") == "cache");

  // Nothing happens again, even if an old folder reappears.
  WriteFile(legacy / "other.bin", "old");
  const auto second = MoveLegacyUserData(legacy, user, cache);
  CHECK_FALSE(second.moved);
  CHECK_FALSE(second.copied);
  CHECK(fs::exists(legacy / "other.bin"));
  CHECK_FALSE(fs::exists(user / "other.bin"));
}

TEST_CASE("Legacy user data is left alone when there is nothing to move",
          "[core][data_locations]") {
  TempRoot root("rexglue_data_locations_none");
  const auto user = root.path / "Saved Games" / "title";
  const auto result = MoveLegacyUserData(root.path / "missing", user, root.path / "cache");
  CHECK_FALSE(result.moved);
  CHECK_FALSE(result.copied);
  CHECK(result.error.empty());
  CHECK_FALSE(fs::exists(user));

  CHECK_FALSE(MoveLegacyUserData({}, user, root.path / "cache").moved);
}

TEST_CASE("An existing cache is not replaced by the legacy one", "[core][data_locations]") {
  TempRoot root("rexglue_data_locations_cache");
  const auto legacy = root.path / "Documents" / "title";
  const auto user = root.path / "Saved Games" / "title";
  const auto cache = root.path / "Local" / "title" / "cache";
  WriteFile(legacy / "save.bin", "save");
  WriteFile(legacy / "cache" / "shaders.bin", "old");
  WriteFile(cache / "shaders.bin", "new");

  const auto result = MoveLegacyUserData(legacy, user, cache);
  CHECK(result.moved);
  CHECK_FALSE(result.moved_cache);
  CHECK(ReadFile(cache / "shaders.bin") == "new");
  CHECK(ReadFile(user / "save.bin") == "save");
}

TEST_CASE("Legacy user data is copied when it cannot be renamed", "[core][data_locations]") {
  TempRoot root("rexglue_data_locations_copy");
  const auto legacy = root.path / "Documents" / "title";
  const auto user = root.path / "Saved Games" / "title";
  const auto cache = root.path / "Local" / "title" / "cache";
  WriteFile(legacy / "profile" / "settings.bin", "profile");
  WriteFile(legacy / "save.bin", "save");

  LegacyDataMove result;
  {
    // An open file inside the folder stops Windows renaming it, as a move to
    // another volume would.
    std::ifstream held(legacy / "save.bin", std::ios::binary);
    REQUIRE(held);
    result = MoveLegacyUserData(legacy, user, cache);
  }
  CHECK_FALSE(result.moved);
  CHECK(result.copied);
  CHECK(result.error.empty());
  CHECK(ReadFile(user / "save.bin") == "save");
  CHECK(ReadFile(user / "profile" / "settings.bin") == "profile");
  CHECK(ReadFile(legacy / "save.bin") == "save");  // the old copy stays
}
