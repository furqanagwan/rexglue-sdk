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
#include <rex/logging.h>
#include <rex/ui/flags.h>
#include <rex/ui/window.h>
#include <rex/ui/window_sdl.h>
#include <rex/ui/window_win.h>
#include <rex/ui/windowed_app_context_win.h>

namespace rex::ui {

std::unique_ptr<Window> Window::Create(WindowedAppContext& app_context,
                                       const std::string_view title) {
  uint32_t width = 0;
  uint32_t height = 0;
  ResolveConfiguredLogicalSize(width, height);
  return Create(app_context, title, width, height);
}

std::unique_ptr<Window> Window::Create(WindowedAppContext& app_context,
                                       const std::string_view title, uint32_t desired_logical_width,
                                       uint32_t desired_logical_height) {
  // The app context decides the platform: the entry point creates a
  // Win32WindowedAppContext for ui_backend = "win32" (RG-GDK-021).
  if (dynamic_cast<Win32WindowedAppContext*>(&app_context)) {
    REXLOG_INFO("Window: native Win32");
    return std::make_unique<Win32Window>(app_context, title, desired_logical_width,
                                         desired_logical_height);
  }
  REXLOG_INFO("Window: SDL");
  return std::make_unique<WindowSDL>(app_context, title, desired_logical_width,
                                     desired_logical_height);
}

}  // namespace rex::ui
