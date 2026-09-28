/**
 * @file        tests/unit/system/title_display_name_test.cpp
 * @brief       Window title names from XDBF title strings
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <rex/system/util/xdbf_utils.h>

using rex::system::util::TitleDisplayName;

TEST_CASE("Title display names drop trademark signs", "[system][xdbf]") {
  // The XDBF names of the 007 titles.
  CHECK(TitleDisplayName("Quantum of Solace") == "Quantum of Solace");
  CHECK(TitleDisplayName("007: Blood Stone") == "007: Blood Stone");
  CHECK(TitleDisplayName("007\xE2\x84\xA2 Legends") == "007 Legends");
  CHECK(TitleDisplayName("Game\xC2\xAE Name\xC2\xA9") == "Game Name");
  CHECK(TitleDisplayName("A \xE2\x84\xA2 B") == "A B");
}

TEST_CASE("Title display names collapse whitespace and keep other text", "[system][xdbf]") {
  CHECK(TitleDisplayName("  Name \t with\r\nspaces  ") == "Name with spaces");
  CHECK(TitleDisplayName("L\xC3\xA9gendes") == "L\xC3\xA9gendes");
  CHECK(TitleDisplayName("\xE2\x84\xA2") == "");
  CHECK(TitleDisplayName("") == "");
}
