/**
 * @file        gdk_runtime_test.cpp
 * @brief       GDK toolchain proof inside the SDK build (RG-GDK-002)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

// SDK headers first, then the GDK, as a title would: both must coexist with
// the SDK's NOMINMAX/WIN32_LEAN_AND_MEAN Windows configuration.
#include <rex/codegen/game_config.h>
#include <rex/cvar.h>
#include <rex/platform.h>
#include <rex/system/gaming_runtime.h>
#include <rex/system/gpu_plugin.h>

// The GDK headers need the Windows headers first; the SDK headers above do
// not include them.
#include <windows.h>

#include <XGameRuntime.h>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

#include <catch2/catch_test_macros.hpp>

static_assert(_GRDK_EDITION == REXGLUE_GDK_EDITION,
              "GDK headers differ from the edition selected at configure time");

REXCVAR_DEFINE_COMMAND_ARGS(
    gdk_test_throw, [](std::string_view args) { throw std::runtime_error(std::string(args)); },
    "Testing", "Throws its argument (RG-GDK-002 exception ABI test)");

TEST_CASE("The pinned GDK edition is selected", "[gdk]") {
  CHECK(REXGLUE_GDK_EDITION == 260404);
}

TEST_CASE("Gaming Runtime initializes in an unpackaged SDK process", "[gdk]") {
  HRESULT hr = XGameRuntimeInitialize();
  INFO("XGameRuntimeInitialize: 0x" << std::hex << uint32_t(hr));
  REQUIRE(SUCCEEDED(hr));
  XGameRuntimeUninitialize();
}

TEST_CASE("C++ exceptions unwind through rexruntime under the GDK toolchain", "[gdk]") {
  // The command runs inside rexruntime's cvar dispatch, so the exception
  // crosses the DLL boundary on its way back to the test.
  try {
    rex::cvar::InvokeCommand("gdk_test_throw", "crossed rexruntime");
    FAIL("no exception");
  } catch (const std::runtime_error& e) {
    CHECK(std::string(e.what()) == "crossed rexruntime");
  }
}

TEST_CASE("GamingRuntime drives the installed Gaming Runtime", "[gdk][gaming_runtime]") {
  rex::system::GamingRuntime runtime;
  auto result = runtime.Initialize();
  INFO(result.message);
  REQUIRE(result.ok());
  runtime.Uninitialize();
  CHECK(runtime.state() == rex::system::GamingRuntimeState::kNotInitialized);
}

TEST_CASE("The installed runtime rejects a malformed or missing MicrosoftGame.config",
          "[gdk][gaming_runtime]") {
  const auto dir = std::filesystem::temp_directory_path() /
                   ("rexglue_gameconfig_" + std::to_string(GetCurrentProcessId()));
  std::filesystem::create_directories(dir);
  const auto config = dir / "MicrosoftGame.config";
  {
    std::ofstream out(config);
    out << "<Game configVersion=\"1\"><Identity Name=\"x\"/></Game";
  }
  rex::system::GamingRuntime runtime;
  auto bad = runtime.Initialize(rex::system::GamingRuntime::kDefaultTimeout, config.string());
  INFO(bad.message);
  CHECK(bad.state == rex::system::GamingRuntimeState::kConfigError);

  auto missing = runtime.Initialize(rex::system::GamingRuntime::kDefaultTimeout,
                                    (dir / "absent" / "MicrosoftGame.config").string());
  INFO(missing.message);
  CHECK(missing.state == rex::system::GamingRuntimeState::kConfigError);
  runtime.Uninitialize();
  std::error_code ec;
  std::filesystem::remove_all(dir, ec);
}

TEST_CASE("The installed runtime accepts a generated MicrosoftGame.config",
          "[gdk][gaming_runtime][gameconfig]") {
  rex::codegen::GameConfigIdentity id;
  id.name = "ReXGlue.GdkRuntimeTest";
  id.publisher = "CN=ReXGlue Tests";
  id.display_name = "ReXGlue runtime test";
  id.publisher_display_name = "ReXGlue";
  id.executable = "unit_tests.exe";
  auto xml = rex::codegen::RenderGameConfig(id);
  REQUIRE(xml);

  const auto dir = std::filesystem::temp_directory_path() /
                   ("rexglue_gameconfig_ok_" + std::to_string(GetCurrentProcessId()));
  std::filesystem::create_directories(dir);
  const auto config = dir / "MicrosoftGame.config";
  {
    std::ofstream out(config, std::ios::binary);
    out << *xml;
  }
  rex::system::GamingRuntime runtime;
  auto result = runtime.Initialize(rex::system::GamingRuntime::kDefaultTimeout, config.string());
  INFO(result.message);
  CHECK(result.ok());
  runtime.Uninitialize();
  std::error_code ec;
  std::filesystem::remove_all(dir, ec);
}
