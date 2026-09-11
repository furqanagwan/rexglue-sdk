/**
 * @file        ui/window_factory.cpp
 * @brief       Window::Create: startup size resolution and platform selection
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <algorithm>

#include <rex/cvar.h>
#include <rex/graphics/video_mode_util.h>
#include <rex/ui/flags.h>
#include <rex/ui/window.h>
#include <rex/ui/window_sdl.h>
#include <rex/ui/window_win.h>
#include <rex/ui/windowed_app_context_win.h>

namespace rex::ui {

namespace {

void ResolveWindowSize(uint32_t& width, uint32_t& height) {
  int32_t configured_width = REXCVAR_GET(window_width);
  int32_t configured_height = REXCVAR_GET(window_height);
  if (configured_width <= 0 || configured_height <= 0) {
    rex::graphics::video_mode_util::ResolveConfiguredSize(configured_width, configured_height);
  }
  width = uint32_t(std::clamp(configured_width, 1, 8192));
  height = uint32_t(std::clamp(configured_height, 1, 8192));
}

}  // namespace

std::unique_ptr<Window> Window::Create(WindowedAppContext& app_context,
                                       const std::string_view title) {
  uint32_t width = 0;
  uint32_t height = 0;
  ResolveWindowSize(width, height);
  return Create(app_context, title, width, height);
}

std::unique_ptr<Window> Window::Create(WindowedAppContext& app_context,
                                       const std::string_view title, uint32_t desired_logical_width,
                                       uint32_t desired_logical_height) {
  // The app context decides the platform: the entry point creates a
  // Win32WindowedAppContext for ui_backend = "win32" (RG-GDK-021).
  if (dynamic_cast<Win32WindowedAppContext*>(&app_context)) {
    return std::make_unique<Win32Window>(app_context, title, desired_logical_width,
                                         desired_logical_height);
  }
  return std::make_unique<WindowSDL>(app_context, title, desired_logical_width,
                                     desired_logical_height);
}

}  // namespace rex::ui
