/**
 * @file        ui/display_info.h
 * @brief       The displays a player can choose to play on, and what each supports
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace rex::ui {

struct DisplayResolution {
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t max_refresh_hz = 0;
  bool operator==(const DisplayResolution&) const = default;
};

struct DisplayInfo {
  int32_t monitor_index = 0;
  std::string name;
  bool primary = false;
  bool shows_game = false;
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t refresh_hz = 0;
  uint32_t native_width = 0;
  uint32_t native_height = 0;
  std::vector<DisplayResolution> resolutions;
  bool hdr_supported = false;
  bool hdr_on = false;
  uint32_t bits_per_color = 0;
  float peak_nits = 0.0f;
};

std::vector<DisplayInfo> ListDisplays(void* game_window);

std::vector<DisplayResolution> NotableResolutions(const std::vector<DisplayResolution>& modes,
                                                  uint32_t native_width, uint32_t native_height);
std::string ResolutionName(uint32_t width, uint32_t height);

}
