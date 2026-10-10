/**
 * @file        display_info_test.cpp
 * @brief       The displays a player can choose and what each supports
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <rex/ui/display_info.h>

using rex::ui::DisplayResolution;

TEST_CASE("A display's notable resolutions start at native and keep their fastest refresh",
          "[ui][display_info]") {
  const std::vector<DisplayResolution> modes = {
      {3840, 2160, 60}, {3840, 2160, 144}, {2560, 1440, 120}, {1920, 1080, 144},
      {1920, 1080, 60}, {1280, 720, 60},   {1024, 768, 60},   {3440, 1440, 100},
  };
  CHECK(rex::ui::NotableResolutions(modes, 3440, 1440) ==
        std::vector<DisplayResolution>{
            {3440, 1440, 100}, {3840, 2160, 144}, {2560, 1440, 120}, {1920, 1080, 144}});
  CHECK(rex::ui::NotableResolutions(modes, 1024, 768).front() == DisplayResolution{1024, 768, 60});
  CHECK(rex::ui::NotableResolutions({{1920, 1080, 60}}, 3840, 2160) ==
        std::vector<DisplayResolution>{{1920, 1080, 60}});
  CHECK(rex::ui::NotableResolutions({}, 1920, 1080).empty());
}

TEST_CASE("Common resolutions have their everyday names", "[ui][display_info]") {
  CHECK(rex::ui::ResolutionName(3840, 2160) == "4K UHD");
  CHECK(rex::ui::ResolutionName(2560, 1440) == "1440p QHD");
  CHECK(rex::ui::ResolutionName(1920, 1080) == "1080p Full HD");
  CHECK(rex::ui::ResolutionName(1600, 900).empty());
}

TEST_CASE("Windows lists its displays in the monitor setting's order", "[ui][display_info]") {
  const auto displays = rex::ui::ListDisplays(nullptr);
  if (displays.empty()) {
    SKIP("No display on this machine");
  }
  CHECK(displays.front().primary);
  for (size_t i = 0; i < displays.size(); ++i) {
    INFO(displays[i].name);
    CHECK(displays[i].monitor_index == int32_t(i + 1));
    CHECK_FALSE(displays[i].name.empty());
    CHECK(displays[i].name.back() != ' ');
    CHECK(displays[i].width > 0);
    CHECK(displays[i].height > 0);
    CHECK(displays[i].refresh_hz > 0);
    CHECK_FALSE(displays[i].shows_game);
    CHECK_FALSE(displays[i].resolutions.empty());
  }
}
