/**
 * @file        ui/display_mode.h
 * @brief       Picking a display mode for exclusive fullscreen
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>
#include <optional>
#include <vector>

namespace rex::ui {

struct DisplayMode {
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t refresh_hz = 0;
  uint32_t bits_per_pixel = 0;
  bool operator==(const DisplayMode&) const = default;
};

// The mode to switch to for a requested size, following SDL's
// SDL_GetClosestFullscreenDisplayMode so both windows agree: the exact size
// if the display has it, otherwise the smallest mode covering it, otherwise
// the largest mode. Among modes of that size, the preferred refresh rate (the
// desktop's), or the highest one. Only the deepest colour modes are
// considered. Empty when there are no modes.
inline std::optional<DisplayMode> ChooseFullscreenMode(const std::vector<DisplayMode>& modes,
                                                       uint32_t width, uint32_t height,
                                                       uint32_t preferred_refresh_hz) {
  uint32_t bits = 0;
  for (const DisplayMode& mode : modes) {
    if (mode.width && mode.height) {
      bits = mode.bits_per_pixel > bits ? mode.bits_per_pixel : bits;
    }
  }
  auto usable = [&](const DisplayMode& mode) {
    return mode.width && mode.height && mode.bits_per_pixel == bits;
  };
  auto area = [](const DisplayMode& mode) { return uint64_t(mode.width) * mode.height; };

  const DisplayMode* size = nullptr;
  for (const DisplayMode& mode : modes) {
    if (usable(mode) && mode.width == width && mode.height == height) {
      size = &mode;
      break;
    }
  }
  if (!size) {
    for (const DisplayMode& mode : modes) {
      if (usable(mode) && mode.width >= width && mode.height >= height &&
          (!size || area(mode) < area(*size))) {
        size = &mode;
      }
    }
  }
  if (!size) {
    for (const DisplayMode& mode : modes) {
      if (usable(mode) && (!size || area(mode) > area(*size))) {
        size = &mode;
      }
    }
  }
  if (!size) {
    return std::nullopt;
  }

  const DisplayMode* best = nullptr;
  for (const DisplayMode& mode : modes) {
    if (!usable(mode) || mode.width != size->width || mode.height != size->height) {
      continue;
    }
    if (mode.refresh_hz == preferred_refresh_hz) {
      return mode;
    }
    if (!best || mode.refresh_hz > best->refresh_hz) {
      best = &mode;
    }
  }
  return *best;
}

}  // namespace rex::ui
