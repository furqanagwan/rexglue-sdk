/**
 * @file        log_file_open_test.cpp
 * @brief       A log file that cannot be opened falls back instead of ending the process
 *
 * @copyright   Copyright (c) 2026 ReXGlue contributors
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <fstream>
#include <string>

#include <rex/logging.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

namespace fs = std::filesystem;

namespace {

struct TempDir {
  explicit TempDir(const std::string& name)
      : path(fs::temp_directory_path() /
             ("rexglue_log_file_open_" + name + "_" + std::to_string(GetCurrentProcessId()))) {
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

TEST_CASE("A log file that can be opened is used as given", "[logging]") {
  TempDir dir("used");
  auto preferred = dir.path / "title_001.log";
  auto opened = rex::OpenLogFile(preferred, "title");
  REQUIRE(opened.sink);
  CHECK(opened.path == preferred);
}

TEST_CASE("A log file that cannot be opened falls back to the temporary folder", "[logging]") {
  TempDir dir("fallback");
  auto blocker = dir.path / "not_a_folder";
  std::ofstream(blocker) << "x";
  auto opened = rex::OpenLogFile(blocker / "title_001.log", "log_file_open_test");
  REQUIRE(opened.sink);
  CHECK(opened.path.parent_path() == fs::temp_directory_path() / "rexglue-logs");
  CHECK(opened.path.filename().string().starts_with("log_file_open_test_"));
  opened.sink.reset();
  std::error_code ec;
  fs::remove(opened.path, ec);
}
