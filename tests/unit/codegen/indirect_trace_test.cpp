/**
 * @file        indirect_trace_test.cpp
 * @brief       The runtime's indirect call trace feeds codegen (RG-GDK-066)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <fstream>
#include <string>

#include <rex/codegen/config.h>
#include <rex/system/function_dispatcher.h>

#include "rexglue/commands/project_scan.h"

namespace {

bool Contains(const std::string& text, const std::string& part) {
  return text.find(part) != std::string::npos;
}

}

TEST_CASE("Targets a run records become function entries for codegen", "[codegen][indirect]") {
  const std::filesystem::path folder =
      std::filesystem::temp_directory_path() / "rexglue_indirect_trace_test";
  std::filesystem::remove_all(folder);
  std::filesystem::create_directories(folder);
  const std::filesystem::path trace = folder / "indirect_trace.toml";

  REQUIRE(rex::runtime::AppendIndirectTrace(trace, 0x82462590));
  REQUIRE(rex::runtime::AppendIndirectTrace(trace, 0x8211E798));
  REQUIRE(rex::runtime::AppendIndirectTrace(trace, 0x82462590));

  std::ofstream(folder / "title.toml")
      << "file_path = \"default.xex\"\nincludes = [\"indirect_trace.toml\"]\n";
  rex::codegen::RecompilerConfig config;
  REQUIRE(config.Load((folder / "title.toml").string()));
  CHECK(config.functions.size() == 2);
  CHECK(config.functions.contains(0x82462590));
  CHECK(config.functions.contains(0x8211E798));
  std::filesystem::remove_all(folder);
}

TEST_CASE("Generated CMake offers the unoptimised fallback build", "[codegen][indirect]") {
  const std::string cmake = rexglue::cli::RenderRexglueCmake("demo", "0.10.0", "generated/default",
                                                             {{2, "generated/tu2"}});
  CHECK(Contains(cmake, "set(REXGLUE_RECOMP_FALLBACK \"\" CACHE STRING"));
  CHECK(Contains(cmake, "_name MATCHES \"${REXGLUE_RECOMP_FALLBACK}\""));
  CHECK(Contains(cmake, "SKIP_PRECOMPILE_HEADERS ON"));

  CHECK(Contains(cmake, "_rexglue_apply_recomp_fallback(${REXGLUE_ENTRYPOINT_GENERATED_SOURCES})"));
  CHECK(Contains(cmake, "_rexglue_apply_recomp_fallback(${REXGLUE_TU2_GENERATED_SOURCES})"));
}
