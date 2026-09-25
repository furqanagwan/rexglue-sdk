/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    ReXGlue, 2026 - Ported from xenia-edge 213dcc267 for RG-GDK-021;
 *              sets per-monitor DPI awareness v2 itself (no manifest needed).
 */

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

// For per-monitor DPI awareness v1.
#include <ShellScalingApi.h>

#include <rex/ui/windowed_app_context.h>

namespace rex::ui {

class Win32WindowedAppContext final : public WindowedAppContext {
 public:
  // clang-format off
  struct PerMonitorDpiV1Api {
    HRESULT (STDAPICALLTYPE* get_dpi_for_monitor)(
        HMONITOR hmonitor, MONITOR_DPI_TYPE dpi_type, UINT* dpi_x, UINT* dpi_y);
  };

  struct PerMonitorDpiV2Api {
    // Added in Windows 10 1607, before per-monitor awareness v2 (1703). Make
    // sure EnableNonClientDpiScaling is called in WM_NCCREATE so
    // AdjustWindowRectExForDpi matches the actual non-client area on 1607.
    BOOL (WINAPI* adjust_window_rect_ex_for_dpi)(
        LPRECT rect, DWORD style, BOOL menu, DWORD ex_style, UINT dpi);
    BOOL (WINAPI* enable_non_client_dpi_scaling)(HWND hwnd);
    UINT (WINAPI* get_dpi_for_system)();
    UINT (WINAPI* get_dpi_for_window)(HWND hwnd);
  };
  // clang-format on

  // Must call Initialize and check its result after creating to be able to
  // perform pending function calls.
  explicit Win32WindowedAppContext(HINSTANCE hinstance, int show_cmd)
      : hinstance_(hinstance), show_cmd_(show_cmd) {}
  ~Win32WindowedAppContext() override;

  bool Initialize();

  HINSTANCE hinstance() const { return hinstance_; }
  int show_cmd() const { return show_cmd_; }

  void NotifyUILoopOfPendingFunctions() override;
  void PlatformQuitFromUIThread() override;

  int RunMainMessageLoop();

  // Windows 8.1 per-monitor DPI awareness version 1.
  const PerMonitorDpiV1Api* per_monitor_dpi_v1_api() const {
    return per_monitor_dpi_v1_api_available_ ? &per_monitor_dpi_v1_api_ : nullptr;
  }
  // Windows 10 1607 per-monitor DPI awareness API, also used for per-monitor
  // DPI awareness version 2 functionality added in Windows 10 1703.
  const PerMonitorDpiV2Api* per_monitor_dpi_v2_api() const {
    return per_monitor_dpi_v2_api_available_ ? &per_monitor_dpi_v2_api_ : nullptr;
  }

 private:
  enum : UINT {
    kPendingFunctionsWindowClassMessageExecute = WM_USER,
  };

  static LRESULT CALLBACK PendingFunctionsWndProc(HWND hwnd, UINT message, WPARAM wparam,
                                                  LPARAM lparam);

  HINSTANCE hinstance_;
  int show_cmd_;

  HMODULE shcore_module_ = nullptr;
  HMODULE user32_module_ = nullptr;
  PerMonitorDpiV1Api per_monitor_dpi_v1_api_ = {};
  PerMonitorDpiV2Api per_monitor_dpi_v2_api_ = {};
  bool per_monitor_dpi_v1_api_available_ = false;
  bool per_monitor_dpi_v2_api_available_ = false;

  static bool pending_functions_window_class_registered_;
  HWND pending_functions_hwnd_ = nullptr;
};

}  // namespace rex::ui
