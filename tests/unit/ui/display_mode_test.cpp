/**
 * @file        display_mode_test.cpp
 * @brief       Exclusive fullscreen mode choice (upstream ReXGlue 1406e1b)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "ui/display_mode.h"

using rex::ui::ChooseFullscreenMode;
using rex::ui::DisplayMode;

namespace {

const std::vector<DisplayMode> kModes = {
    {1280, 720, 60, 32},   {1280, 720, 144, 32},  {1920, 1080, 60, 32}, {1920, 1080, 120, 32},
    {1920, 1080, 144, 32}, {2560, 1440, 144, 32}, {1920, 1080, 60, 16}, {640, 480, 60, 32},
};

}

TEST_CASE("Fullscreen takes the exact size at the desktop refresh rate", "[ui][display_mode]") {
  CHECK(ChooseFullscreenMode(kModes, 1920, 1080, 120) == DisplayMode{1920, 1080, 120, 32});

  CHECK(ChooseFullscreenMode(kModes, 1280, 720, 120) == DisplayMode{1280, 720, 144, 32});
}

TEST_CASE("Fullscreen falls back to the smallest mode covering the size", "[ui][display_mode]") {
  CHECK(ChooseFullscreenMode(kModes, 1600, 900, 60) == DisplayMode{1920, 1080, 60, 32});

  CHECK(ChooseFullscreenMode(kModes, 3840, 2160, 60) == DisplayMode{2560, 1440, 144, 32});
}

TEST_CASE("Fullscreen ignores shallow colour modes and empty lists", "[ui][display_mode]") {
  const std::vector<DisplayMode> modes = {{1920, 1080, 60, 16}, {1920, 1080, 50, 32}};
  CHECK(ChooseFullscreenMode(modes, 1920, 1080, 60) == DisplayMode{1920, 1080, 50, 32});
  CHECK_FALSE(ChooseFullscreenMode({}, 1920, 1080, 60).has_value());
}
