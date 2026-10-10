/**
 * @file        log_prune_test.cpp
 * @brief       The log directory budget (upstream ReXGlue b971840)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <fstream>
#include <string>

#include <rex/cvar.h>
#include <rex/logging.h>

namespace fs = std::filesystem;

namespace {

void WriteFile(const fs::path& path, size_t bytes) {
  std::ofstream(path, std::ios::binary) << std::string(bytes, 'x');
}

struct TempDir {
  TempDir() : path(fs::temp_directory_path() / "rexglue_log_prune_test") {
    fs::remove_all(path);
    fs::create_directories(path);
  }
  ~TempDir() {
    std::error_code ec;
    fs::remove_all(path, ec);
  }
  fs::path path;
};

}

TEST_CASE("The log budget removes whole runs, oldest first", "[logging]") {
  TempDir dir;
  for (int run = 1; run <= 5; run++) {
    WriteFile(dir.path / ("game_00" + std::to_string(run) + ".log"), 1000);
  }

  WriteFile(dir.path / "game_002.1.log", 1000);

  WriteFile(dir.path / "other_001.log", 5000);
  WriteFile(dir.path / "game_notes.txt", 5000);

  rex::PruneLogDirectory(dir.path, "game", 3000);

  CHECK_FALSE(fs::exists(dir.path / "game_001.log"));
  CHECK_FALSE(fs::exists(dir.path / "game_002.log"));
  CHECK_FALSE(fs::exists(dir.path / "game_002.1.log"));
  CHECK(fs::exists(dir.path / "game_003.log"));
  CHECK(fs::exists(dir.path / "game_004.log"));
  CHECK(fs::exists(dir.path / "game_005.log"));
  CHECK(fs::exists(dir.path / "other_001.log"));
  CHECK(fs::exists(dir.path / "game_notes.txt"));
}

TEST_CASE("Runs within the log budget are kept", "[logging]") {
  TempDir dir;
  WriteFile(dir.path / "game_001.log", 1000);
  WriteFile(dir.path / "game_002.log", 1000);
  rex::PruneLogDirectory(dir.path, "game", 2000);
  CHECK(fs::exists(dir.path / "game_001.log"));
  CHECK(fs::exists(dir.path / "game_002.log"));
}

TEST_CASE("The log_dir flag moves sequential logs out of the default folder", "[core][log]") {
  rex::LogConfig config;
  config.log_dir = "C:/default/logs";
  REQUIRE(rex::cvar::SetFlagByName("log_dir", "C:/chosen/logs"));
  rex::ApplyLogCvarOverrides(config);
  CHECK(config.log_dir == fs::path("C:/chosen/logs"));

  REQUIRE(rex::cvar::SetFlagByName("log_dir", ""));
  rex::LogConfig untouched;
  untouched.log_dir = "C:/default/logs";
  rex::ApplyLogCvarOverrides(untouched);
  CHECK(untouched.log_dir == fs::path("C:/default/logs"));
}
