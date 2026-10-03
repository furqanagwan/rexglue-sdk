/**
 * @file        scaling_list_test.cpp
 * @brief       Matching render target sizes against a title's list (ADR-012)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <string>

#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/pipeline/render_target/scaling_list.h>

using rex::graphics::ScalingResolutionList;

TEST_CASE("A width, a height or both pick the render targets to scale", "[graphics][scaling]") {
  ScalingResolutionList list;
  // Fuzion Frenzy's list from its PC backward compatibility package.
  REQUIRE(list.Parse("720x0 844x0 1280x0 0x240 0x480 0x256"));
  CHECK(list.entries().size() == 6);
  CHECK(list.Matches(720, 123));   // 720x0: width 720, any height
  CHECK(list.Matches(1280, 720));  // 1280x0
  CHECK(list.Matches(512, 240));   // 0x240: height 240, any width
  CHECK(list.Matches(320, 256));   // 0x256
  CHECK_FALSE(list.Matches(640, 360));
  CHECK_FALSE(list.Matches(256, 720));

  REQUIRE(list.Parse("1280x720"));  // exact
  CHECK(list.Matches(1280, 720));
  CHECK_FALSE(list.Matches(1280, 704));
  CHECK_FALSE(list.Matches(640, 720));
}

TEST_CASE("No list scales everything; a bad entry rejects the list", "[graphics][scaling]") {
  ScalingResolutionList list;
  REQUIRE(list.Parse(""));
  CHECK(list.empty());
  CHECK(list.Matches(640, 360));

  std::string bad;
  CHECK_FALSE(list.Parse("720x0 0x0", &bad));
  CHECK(bad == "0x0");
  CHECK(list.empty());
  CHECK_FALSE(list.Parse("720", &bad));
  CHECK(bad == "720");
  CHECK_FALSE(list.Parse("720xabc", &bad));
  // Commas and tabs separate entries too.
  REQUIRE(list.Parse("720x0,\t0x240"));
  CHECK(list.entries().size() == 2);
}
