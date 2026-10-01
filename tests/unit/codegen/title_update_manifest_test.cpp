/**
 * @file        title_update_manifest_test.cpp
 * @brief       Manifest [[title_update]] builds and their CMake targets (RG-GDK-057)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <fstream>
#include <string>

#include <rex/codegen/manifest.h>

#include "rexglue/commands/project_scan.h"

namespace fs = std::filesystem;
using rex::codegen::ManifestConfig;

namespace {

// A project folder with a manifest and the configs it includes.
struct Project {
  fs::path dir;
  explicit Project(const std::string& manifest) {
    static int counter = 0;
    dir = fs::temp_directory_path() / ("rex_tu_manifest_" + std::to_string(++counter));
    fs::remove_all(dir);
    fs::create_directories(dir);
    Write("demo_manifest.toml", manifest);
    Write("base.toml", "[functions.\"0x82000100\"]\n");
    Write("tu2.toml", "[functions.\"0x82000200\"]\n");
  }
  ~Project() {
    std::error_code ec;
    fs::remove_all(dir, ec);
  }
  void Write(const std::string& name, const std::string& text) const {
    std::ofstream(dir / name) << text;
  }
  fs::path Manifest() const { return dir / "demo_manifest.toml"; }
};

constexpr const char* kHead = R"(
[project]
name = "demo"
game_root = "game"

[entrypoint]
file_path = "game/default.xex"
out_directory_path = "generated/default"
includes = ["base.toml"]
)";

bool Contains(const std::string& text, const std::string& part) {
  return text.find(part) != std::string::npos;
}

}  // namespace

TEST_CASE("A title update builds the entrypoint again with its own output and includes",
          "[codegen][title_update]") {
  Project project(std::string(kHead) + R"(
[[title_update]]
version = 2
package = "title_updates/TU_2"
out_directory_path = "generated/tu2"
includes = ["tu2.toml"]
)");
  auto manifest = ManifestConfig::Load(project.Manifest());
  REQUIRE(manifest);
  REQUIRE(manifest->titleUpdates.size() == 1);
  const auto& tu = manifest->titleUpdates[0];
  CHECK(tu.version == 2);
  CHECK(tu.package == project.dir / "title_updates/TU_2");
  const auto& cfg = tu.binary.recompiler;
  CHECK(cfg.titleUpdateVersion == 2);
  CHECK(cfg.outDirectoryPath == "generated/tu2");
  CHECK(cfg.filePath == manifest->entrypoint.recompiler.filePath);
  // Its own includes replace the original's: addresses differ between versions.
  CHECK(cfg.functions.contains(0x82000200));
  CHECK_FALSE(cfg.functions.contains(0x82000100));
  // The original is untouched.
  CHECK(manifest->entrypoint.recompiler.titleUpdateVersion == 0);
  CHECK(manifest->entrypoint.recompiler.functions.contains(0x82000100));
}

TEST_CASE("A title update entry missing a field, or listed twice, is refused",
          "[codegen][title_update]") {
  SECTION("no includes") {
    Project project(std::string(kHead) + R"(
[[title_update]]
version = 2
package = "tu"
out_directory_path = "generated/tu2"
)");
    CHECK_FALSE(ManifestConfig::Load(project.Manifest()));
  }
  SECTION("version 0") {
    Project project(std::string(kHead) + R"(
[[title_update]]
version = 0
package = "tu"
out_directory_path = "generated/tu0"
includes = []
)");
    CHECK_FALSE(ManifestConfig::Load(project.Manifest()));
  }
  SECTION("the same version twice") {
    Project project(std::string(kHead) + R"(
[[title_update]]
version = 2
package = "a"
out_directory_path = "generated/a"
includes = []
[[title_update]]
version = 2
package = "b"
out_directory_path = "generated/b"
includes = []
)");
    CHECK_FALSE(ManifestConfig::Load(project.Manifest()));
  }
}

TEST_CASE("Generated CMake adds an executable per title update", "[codegen][title_update]") {
  const std::string none = rexglue::cli::RenderRexglueCmake("demo", "0.10.0", "generated/default");
  CHECK_FALSE(Contains(none, "add_executable(${target_name}_tu"));
  CHECK_FALSE(Contains(none, "REXGLUE_TU"));

  const std::string cmake = rexglue::cli::RenderRexglueCmake("demo", "0.10.0", "generated/default",
                                                             {{2, "generated/tu2"}});
  CHECK(Contains(cmake, "include(generated/tu2/sources.cmake)"));
  CHECK(Contains(cmake, "set(REXGLUE_TU2_GENERATED_SOURCES ${GENERATED_SOURCES})"));
  CHECK(Contains(cmake, "add_executable(${target_name}_tu2 ${_rexglue_host_sources})"));
  CHECK(Contains(cmake, "\"${CMAKE_CURRENT_SOURCE_DIR}/generated/tu2\")"));
  // Codegen's rule produces the update's sources too, so the build orders after it.
  const auto command = cmake.find("add_custom_command(");
  REQUIRE(command != std::string::npos);
  CHECK(cmake.find("${REXGLUE_TU2_GENERATED_SOURCES}", command) <
        cmake.find("COMMAND $<TARGET_FILE:rex::rexglue> codegen", command));
}
