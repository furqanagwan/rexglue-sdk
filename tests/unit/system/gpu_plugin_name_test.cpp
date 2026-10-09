// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>

#include <rex/system/gpu_plugin.h>

using rex::system::ResolveGpuPluginName;

TEST_CASE("An unset GPU plugin loads xenos when it is next to the executable",
          "[system][gpu_plugin]") {
  CHECK(ResolveGpuPluginName("", true) == "xenos");
  CHECK(ResolveGpuPluginName("", false).empty());
}

TEST_CASE("A named GPU plugin is used as given", "[system][gpu_plugin]") {
  CHECK(ResolveGpuPluginName("xenos", false) == "xenos");
  CHECK(ResolveGpuPluginName("other", true) == "other");
}

TEST_CASE("The none GPU plugin turns GPU emulation off", "[system][gpu_plugin]") {
  CHECK(ResolveGpuPluginName("none", true).empty());
}
