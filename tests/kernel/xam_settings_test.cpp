/**
 * @file        xam_settings_test.cpp
 * @brief       Console settings XAM reports: audio flags and granted licenses
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cstdint>

#include <rex/cvar.h>
#include <rex/kernel/xboxkrnl/xconfig.h>

#include "kernel_fixture.h"

namespace rex::kernel::xam {
uint32_t XGetAudioFlags_entry();
}  // namespace rex::kernel::xam

using rex::system::xam::ContentManager;

TEST_CASE("XGetAudioFlags reports the console's XConfig audio flags", "[kernel][xam]") {
  CHECK(rex::kernel::xam::XGetAudioFlags_entry() == rex::kernel::xboxkrnl::kXConfigUserAudioFlags);
  CHECK(rex::kernel::xboxkrnl::kXConfigUserAudioFlags == 0x00010001);  // analog stereo
}

TEST_CASE("license_mask grants licenses to opened content", "[kernel][content]") {
  using namespace rex::testing;  // NOLINT
  auto* kernel = Kernel();
  TempDir root("rex_content_license");
  ContentManager content(kernel, root.path);
  const auto data = SaveData("LICENSED");
  REQUIRE(content.CreateContent("lic", kXuid, data) == X_ERROR_SUCCESS);
  REQUIRE(content.CloseContent("lic") == X_ERROR_SUCCESS);

  uint32_t license = 0xFFFFFFFF;
  REQUIRE(content.OpenContent("lic", kXuid, data, license) == X_ERROR_SUCCESS);
  CHECK(license == 0);  // no header licenses and no mask
  REQUIRE(content.CloseContent("lic") == X_ERROR_SUCCESS);

  // A mask of 1 applies too (Edge aac25ad0c; it used to need > 1).
  REQUIRE(rex::cvar::SetFlagByName("license_mask", "1"));
  REQUIRE(content.OpenContent("lic", kXuid, data, license) == X_ERROR_SUCCESS);
  CHECK(license == 1);
  REQUIRE(content.CloseContent("lic") == X_ERROR_SUCCESS);
  REQUIRE(rex::cvar::SetFlagByName("license_mask", "0"));
}
