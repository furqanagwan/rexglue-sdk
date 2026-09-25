/**
 * @file        gdk_runtime_test.cpp
 * @brief       GDK toolchain proof inside the SDK build (RG-GDK-002)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

// SDK headers first, then the GDK, as a title would: both must coexist with
// the SDK's NOMINMAX/WIN32_LEAN_AND_MEAN Windows configuration.
#include <rex/cvar.h>
#include <rex/platform.h>
#include <rex/system/gpu_plugin.h>

// The GDK headers need the Windows headers first; the SDK headers above do
// not include them.
#include <windows.h>

#include <XGameRuntime.h>

#include <cstdint>
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
