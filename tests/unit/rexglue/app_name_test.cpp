/**
 * @file        app_name_test.cpp
 * @brief       Project names for `rexglue init` (upstream ReXGlue 5cf287f)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include "rexglue/commands/template_utils.h"

using rexglue::cli::parse_app_name;

TEST_CASE("Project names keep their case", "[rexglue][init]") {
  auto names = parse_app_name("QuantumOfSolace");
  CHECK(names.original == "QuantumOfSolace");
  CHECK(names.upper_case == "QUANTUMOFSOLACE");
  CHECK(names.pascal_case == "Quantumofsolace");
}

TEST_CASE("Names from earlier versions regenerate unchanged", "[rexglue][init]") {
  CHECK(parse_app_name("my_game").original == "my_game");
  CHECK(parse_app_name("quantumofsolace").original == "quantumofsolace");
  CHECK(parse_app_name("my_game").upper_case == "MYGAME");
  CHECK(parse_app_name("my_game").pascal_case == "MyGame");
}

TEST_CASE("Spaces and dashes become one underscore", "[rexglue][init]") {
  CHECK(parse_app_name("Blood Stone").original == "Blood_Stone");
  CHECK(parse_app_name("Bond-Legends").original == "Bond_Legends");
  CHECK(parse_app_name("my  -_game ").original == "my_game");
  CHECK(parse_app_name("Blood Stone").pascal_case == "BloodStone");
}
