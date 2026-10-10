/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    ReXGlue, 2026 - Ported from xenia-edge 213dcc267 (RG-GDK-021).
 *              See window_win.h for what differs.
 */

#include <rex/ui/window_win.h>

#include <algorithm>
#include <climits>
#include <optional>
#include <cstdlib>
#include <string>
#include <vector>

#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/filesystem.h>
#include <rex/graphics/video_mode_util.h>
#include <rex/logging.h>
#include <rex/string/utf8.h>
#include <rex/ui/flags.h>
#include <rex/ui/surface_win.h>
#include <rex/ui/virtual_key.h>
#include <rex/ui/windowed_app_context_win.h>

#include <ShellScalingApi.h>
#include <dwmapi.h>
#include <imm.h>
#include <shellapi.h>
#include <windowsx.h>

#include "display_mode.h"

namespace rex::ui {

namespace {

constexpr wchar_t kWindowClassName[] = L"ReXGlueWindowClass";

std::wstring ToWide(const std::string& text) {
  std::u16string utf16 = rex::string::to_utf16(text);
  return std::wstring(utf16.begin(), utf16.end());
}

std::string FromWide(const std::wstring& text) {
  return rex::string::to_utf8(std::u16string(text.begin(), text.end()));
}

const Win32WindowedAppContext& Win32Context(const WindowedAppContext& app_context) {
  return static_cast<const Win32WindowedAppContext&>(app_context);
}

}

Win32Window::Win32Window(WindowedAppContext& app_context, const std::string_view title,
                         uint32_t desired_logical_width, uint32_t desired_logical_height)
    : Window(app_context, title, desired_logical_width, desired_logical_height),
      arrow_cursor_(LoadCursor(nullptr, IDC_ARROW)) {
  dpi_ = GetCurrentSystemDpi();
}

Win32Window::~Win32Window() {
  EnterDestructor();
  if (cursor_auto_hide_timer_) {
    DeleteTimerQueueTimer(nullptr, cursor_auto_hide_timer_, nullptr);
    cursor_auto_hide_timer_ = nullptr;
  }
  if (hwnd_) {
    HWND hwnd = hwnd_;
    hwnd_ = nullptr;
    relative_mouse_mode_ = false;
    UpdateCursorClip();
    RestoreDisplayMode();
    SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
    DestroyWindow(hwnd);
  }
  if (icon_) {
    DestroyIcon(icon_);
  }
}

uint32_t Win32Window::GetMediumDpi() const {
  return USER_DEFAULT_SCREEN_DPI;
}

bool Win32Window::OpenImpl() {
  const Win32WindowedAppContext& win32_app_context = Win32Context(app_context());
  HINSTANCE hinstance = win32_app_context.hinstance();

  static bool has_registered_class = false;
  if (!has_registered_class) {
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(wcex);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = Win32Window::WndProcThunk;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hinstance;
    wcex.hIcon = LoadIconW(hinstance, L"MAINICON");
    wcex.hIconSm = nullptr;
    wcex.hCursor = arrow_cursor_;

    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = kWindowClassName;
    if (!RegisterClassExW(&wcex)) {
      REXLOG_ERROR("RegisterClassEx failed");
      return false;
    }
    has_registered_class = true;
  }

  uint32_t initial_desired_logical_width = GetDesiredLogicalWidth();
  uint32_t initial_desired_logical_height = GetDesiredLogicalHeight();
  const Win32WindowedAppContext::PerMonitorDpiV2Api* per_monitor_dpi_v2_api =
      win32_app_context.per_monitor_dpi_v2_api();
  const Win32WindowedAppContext::PerMonitorDpiV1Api* per_monitor_dpi_v1_api =
      win32_app_context.per_monitor_dpi_v1_api();

  dpi_ = GetCurrentSystemDpi();
  DWORD window_style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
  DWORD window_ex_style = WS_EX_APPWINDOW | WS_EX_CONTROLPARENT;
  RECT window_size_rect;
  window_size_rect.left = 0;
  window_size_rect.top = 0;
  window_size_rect.right =
      LONG(ConvertSizeDpi(initial_desired_logical_width, dpi_, USER_DEFAULT_SCREEN_DPI));
  window_size_rect.bottom =
      LONG(ConvertSizeDpi(initial_desired_logical_height, dpi_, USER_DEFAULT_SCREEN_DPI));
  AdjustWindowRectangle(window_size_rect, window_style, FALSE, window_ex_style, dpi_);

  std::wstring title = ToWide(GetTitle());
  hwnd_ = CreateWindowExW(
      window_ex_style, kWindowClassName, title.c_str(), window_style, CW_USEDEFAULT, CW_USEDEFAULT,
      window_size_rect.right - window_size_rect.left,
      window_size_rect.bottom - window_size_rect.top, nullptr, nullptr, hinstance, this);
  if (!hwnd_) {
    REXLOG_ERROR("CreateWindowExW failed ({})", GetLastError());
    return false;
  }

  uint32_t initial_monitor_dpi = dpi_;
  if (per_monitor_dpi_v2_api) {
    initial_monitor_dpi = per_monitor_dpi_v2_api->get_dpi_for_window(hwnd_);
  } else if (per_monitor_dpi_v1_api) {
    HMONITOR monitor = MonitorFromWindow(hwnd_, MONITOR_DEFAULTTONEAREST);
    UINT monitor_dpi_x, monitor_dpi_y;
    if (monitor && SUCCEEDED(per_monitor_dpi_v1_api->get_dpi_for_monitor(
                       monitor, MDT_DEFAULT, &monitor_dpi_x, &monitor_dpi_y))) {
      initial_monitor_dpi = monitor_dpi_x;
    }
  }
  if (dpi_ != initial_monitor_dpi) {
    dpi_ = initial_monitor_dpi;
    WINDOWPLACEMENT initial_dpi_placement;

    initial_dpi_placement.length = sizeof(initial_dpi_placement);
    if (GetWindowPlacement(hwnd_, &initial_dpi_placement)) {
      window_size_rect.left = 0;
      window_size_rect.top = 0;
      window_size_rect.right =
          LONG(ConvertSizeDpi(initial_desired_logical_width, dpi_, USER_DEFAULT_SCREEN_DPI));
      window_size_rect.bottom =
          LONG(ConvertSizeDpi(initial_desired_logical_height, dpi_, USER_DEFAULT_SCREEN_DPI));
      AdjustWindowRectangle(window_size_rect, window_style, FALSE, window_ex_style, dpi_);
      initial_dpi_placement.rcNormalPosition.right =
          initial_dpi_placement.rcNormalPosition.left +
          (window_size_rect.right - window_size_rect.left);
      initial_dpi_placement.rcNormalPosition.bottom =
          initial_dpi_placement.rcNormalPosition.top +
          (window_size_rect.bottom - window_size_rect.top);
      SetWindowPlacement(hwnd_, &initial_dpi_placement);
    }
  }

  ApplyMonitorSelection();

  DWM_WINDOW_CORNER_PREFERENCE window_corner_preference = DWMWCP_DONOTROUND;
  DwmSetWindowAttribute(hwnd_, DWMWA_WINDOW_CORNER_PREFERENCE, &window_corner_preference,
                        sizeof(window_corner_preference));

  constexpr DWORD kTabletDisable = 0x00000001 | 0x00000008 | 0x00000010 | 0x00010000 | 0x00100000 |
                                   0x00200000 | 0x00400000 | 0x00800000;
  ATOM atom = GlobalAddAtomW(L"MicrosoftTabletPenServiceProperty");
  SetPropW(hwnd_, L"MicrosoftTabletPenServiceProperty",
           reinterpret_cast<HANDLE>(DWORD_PTR(kTabletDisable)));
  GlobalDeleteAtom(atom);

  DragAcceptFiles(hwnd_, true);

  if (icon_) {
    SendMessageW(hwnd_, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(icon_));
    SendMessageW(hwnd_, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(icon_));
  }

  ApplyNewTextInputActive();

  if (IsFullscreen()) {
    WindowDestructionReceiver destruction_receiver(this);
    ApplyFullscreenEntry(destruction_receiver);
    if (destruction_receiver.IsWindowDestroyed()) {
      return true;
    }
  }

  ShowWindow(hwnd_, SW_SHOWNORMAL);

  {
    WindowDestructionReceiver destruction_receiver(this);

    WINDOWPLACEMENT shown_placement;
    shown_placement.length = sizeof(shown_placement);
    if (GetWindowPlacement(hwnd_, &shown_placement)) {
      RECT non_client_area_rect = {};
      AdjustWindowRectangle(non_client_area_rect);
      OnDesiredLogicalSizeUpdate(
          SizeToLogical(uint32_t(std::max(
              (shown_placement.rcNormalPosition.right - shown_placement.rcNormalPosition.left) -
                  (non_client_area_rect.right - non_client_area_rect.left),
              LONG(0)))),
          SizeToLogical(uint32_t(std::max(
              (shown_placement.rcNormalPosition.bottom - shown_placement.rcNormalPosition.top) -
                  (non_client_area_rect.bottom - non_client_area_rect.top),
              LONG(0)))));
    }

    RECT shown_client_rect;
    if (GetClientRect(hwnd_, &shown_client_rect)) {
      OnActualSizeUpdate(uint32_t(shown_client_rect.right), uint32_t(shown_client_rect.bottom),
                         destruction_receiver);
      if (destruction_receiver.IsWindowDestroyedOrClosed()) {
        return true;
      }
    }

    OnFocusUpdate(GetFocus() == hwnd_, destruction_receiver);
    if (destruction_receiver.IsWindowDestroyedOrClosed()) {
      return true;
    }
  }

  if (IsMouseCaptureRequested()) {
    SetCapture(hwnd_);
  }

  cursor_currently_auto_hidden_ = false;
  CursorVisibility cursor_visibility = GetCursorVisibility();
  if (cursor_visibility != CursorVisibility::kVisible) {
    if (cursor_visibility == CursorVisibility::kAutoHidden) {
      if (!GetCursorPos(&cursor_auto_hide_last_screen_pos_)) {
        cursor_auto_hide_last_screen_pos_.x = LONG_MAX;
        cursor_auto_hide_last_screen_pos_.y = LONG_MAX;
      }
      cursor_currently_auto_hidden_ = true;
    }

    SetCursorIfFocusedOnClientArea(nullptr);
  }

  return true;
}

HMONITOR Win32Window::MonitorForIndex(int32_t monitor_index) {
  if (monitor_index <= 0) {
    return nullptr;
  }

  std::vector<HMONITOR> monitors;
  EnumDisplayMonitors(
      nullptr, nullptr,
      [](HMONITOR monitor, HDC, LPRECT, LPARAM data) -> BOOL {
        reinterpret_cast<std::vector<HMONITOR>*>(data)->push_back(monitor);
        return TRUE;
      },
      reinterpret_cast<LPARAM>(&monitors));
  std::stable_partition(monitors.begin(), monitors.end(), [](HMONITOR monitor) {
    MONITORINFO info = {};
    info.cbSize = sizeof(info);
    return GetMonitorInfoW(monitor, &info) && (info.dwFlags & MONITORINFOF_PRIMARY);
  });
  if (size_t(monitor_index) > monitors.size()) {
    REXLOG_WARN("monitor cvar is {} but only {} display(s) present; using default", monitor_index,
                monitors.size());
    return nullptr;
  }
  return monitors[monitor_index - 1];
}

void Win32Window::ApplyMonitorSelection() {
  HMONITOR monitor = MonitorForIndex(GetMonitor());
  if (!monitor) {
    return;
  }
  MONITORINFO monitor_info = {};
  monitor_info.cbSize = sizeof(monitor_info);
  RECT window_rect;
  if (!GetMonitorInfoW(monitor, &monitor_info) || !GetWindowRect(hwnd_, &window_rect)) {
    return;
  }
  const RECT& work = monitor_info.rcWork;
  int width = window_rect.right - window_rect.left;
  int height = window_rect.bottom - window_rect.top;
  SetWindowPos(hwnd_, nullptr, work.left + ((work.right - work.left) - width) / 2,
               work.top + ((work.bottom - work.top) - height) / 2, 0, 0,
               SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void Win32Window::ApplyNewMonitor() {
  if (!hwnd_) {
    return;
  }
  if (!fullscreen_applied_) {
    ApplyMonitorSelection();
    return;
  }
  HMONITOR monitor = MonitorForIndex(GetMonitor());
  if (!monitor) {
    return;
  }

  RestoreDisplayMode();
  MONITORINFO monitor_info = {};
  monitor_info.cbSize = sizeof(monitor_info);
  if (GetMonitorInfoW(monitor, &monitor_info)) {
    RECT& normal = pre_fullscreen_placement_.rcNormalPosition;
    const RECT& work = monitor_info.rcWork;
    const LONG width = normal.right - normal.left;
    const LONG height = normal.bottom - normal.top;
    normal.left = work.left + ((work.right - work.left) - width) / 2;
    normal.top = work.top + ((work.bottom - work.top) - height) / 2;
    normal.right = normal.left + width;
    normal.bottom = normal.top + height;
  }
  WindowDestructionReceiver destruction_receiver(this);
  CoverMonitor(monitor, destruction_receiver);
}

void Win32Window::ApplyNewDesiredLogicalSize() {
  if (!hwnd_) {
    return;
  }
  if (fullscreen_applied_) {
    pre_fullscreen_normal_client_width_ =
        ConvertSizeDpi(GetDesiredLogicalWidth(), pre_fullscreen_dpi_, GetMediumDpi());
    pre_fullscreen_normal_client_height_ =
        ConvertSizeDpi(GetDesiredLogicalHeight(), pre_fullscreen_dpi_, GetMediumDpi());
    RECT rect = {0, 0, LONG(pre_fullscreen_normal_client_width_),
                 LONG(pre_fullscreen_normal_client_height_)};
    AdjustWindowRectangle(rect, GetWindowLong(hwnd_, GWL_STYLE) | WS_OVERLAPPEDWINDOW, FALSE,
                          GetWindowLong(hwnd_, GWL_EXSTYLE), pre_fullscreen_dpi_);
    RECT& normal = pre_fullscreen_placement_.rcNormalPosition;
    normal.right = normal.left + (rect.right - rect.left);
    normal.bottom = normal.top + (rect.bottom - rect.top);
    return;
  }

  if (IsZoomed(hwnd_) || IsIconic(hwnd_)) {
    return;
  }
  RECT rect = {0, 0, LONG(SizeToPhysical(GetDesiredLogicalWidth())),
               LONG(SizeToPhysical(GetDesiredLogicalHeight()))};
  AdjustWindowRectangle(rect);
  SetWindowPos(hwnd_, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top,
               SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

bool Win32Window::GetDisplayPixelSize(uint32_t& width, uint32_t& height) const {
  if (!hwnd_) {
    return false;
  }
  MONITORINFOEXW monitor_info = {};
  monitor_info.cbSize = sizeof(monitor_info);
  if (!GetMonitorInfoW(MonitorFromWindow(hwnd_, MONITOR_DEFAULTTONEAREST), &monitor_info)) {
    return false;
  }

  DEVMODEW desktop = {};
  desktop.dmSize = sizeof(desktop);
  if (!EnumDisplaySettingsExW(monitor_info.szDevice, ENUM_REGISTRY_SETTINGS, &desktop, 0)) {
    return false;
  }
  width = desktop.dmPelsWidth;
  height = desktop.dmPelsHeight;
  return width > 0 && height > 0;
}

bool Win32Window::SwitchDisplayMode(HMONITOR monitor) {
  MONITORINFOEXW monitor_info = {};
  monitor_info.cbSize = sizeof(monitor_info);
  if (!GetMonitorInfoW(monitor, &monitor_info)) {
    return false;
  }
  const std::wstring device = monitor_info.szDevice;
  const std::string device_name = FromWide(device);
  DEVMODEW desktop = {};
  desktop.dmSize = sizeof(desktop);
  if (!EnumDisplaySettingsExW(device.c_str(), ENUM_REGISTRY_SETTINGS, &desktop, 0)) {
    REXLOG_WARN("No desktop mode for display {}: staying borderless", device_name);
    return false;
  }
  int32_t width = 0;
  int32_t height = 0;
  if (!rex::graphics::video_mode_util::TryGetResolutionPresetFromCVar(width, height) ||
      width <= 0 || height <= 0) {
    width = int32_t(desktop.dmPelsWidth);
    height = int32_t(desktop.dmPelsHeight);
  }

  std::vector<DisplayMode> modes;
  std::vector<DEVMODEW> devmodes;
  for (DWORD i = 0;; i++) {
    DEVMODEW devmode = {};
    devmode.dmSize = sizeof(devmode);
    if (!EnumDisplaySettingsExW(device.c_str(), i, &devmode, 0)) {
      break;
    }
    modes.push_back({devmode.dmPelsWidth, devmode.dmPelsHeight, devmode.dmDisplayFrequency,
                     devmode.dmBitsPerPel});
    devmodes.push_back(devmode);
  }
  std::optional<DisplayMode> chosen =
      ChooseFullscreenMode(modes, uint32_t(width), uint32_t(height), desktop.dmDisplayFrequency);
  if (!chosen) {
    REXLOG_WARN("Display {} has no mode near {}x{}: staying borderless", device_name, width,
                height);
    return false;
  }
  if (switched_display_ != device) {
    RestoreDisplayMode();
  }
  if (chosen->width == desktop.dmPelsWidth && chosen->height == desktop.dmPelsHeight &&
      chosen->refresh_hz == desktop.dmDisplayFrequency) {
    RestoreDisplayMode();
    return true;
  }
  size_t chosen_index = 0;
  while (!(modes[chosen_index] == *chosen)) {
    chosen_index++;
  }
  DEVMODEW devmode = devmodes[chosen_index];
  devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_BITSPERPEL;

  LONG result =
      ChangeDisplaySettingsExW(device.c_str(), &devmode, nullptr, CDS_FULLSCREEN, nullptr);
  if (result != DISP_CHANGE_SUCCESSFUL) {
    REXLOG_WARN("ChangeDisplaySettingsEx({}x{} @ {} Hz) on {} failed ({}): staying borderless",
                chosen->width, chosen->height, chosen->refresh_hz, device_name, result);
    return false;
  }
  switched_display_ = device;
  REXLOG_INFO("Exclusive fullscreen mode {}x{} @ {} Hz on display {}", chosen->width,
              chosen->height, chosen->refresh_hz, device_name);
  return true;
}

void Win32Window::RestoreDisplayMode() {
  if (switched_display_.empty()) {
    return;
  }
  ChangeDisplaySettingsExW(switched_display_.c_str(), nullptr, nullptr, 0, nullptr);
  switched_display_.clear();
}

void Win32Window::CoverMonitor(HMONITOR monitor, WindowDestructionReceiver& destruction_receiver) {
  if (REXCVAR_GET(fullscreen_exclusive)) {
    SwitchDisplayMode(monitor);
  } else {
    RestoreDisplayMode();
  }

  MONITORINFO monitor_info = {};
  monitor_info.cbSize = sizeof(monitor_info);
  if (!GetMonitorInfoW(monitor, &monitor_info)) {
    return;
  }
  BeginBatchedSizeUpdate();

  SetWindowPos(hwnd_, HWND_TOP, monitor_info.rcMonitor.left, monitor_info.rcMonitor.top,
               monitor_info.rcMonitor.right - monitor_info.rcMonitor.left,
               monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top,
               SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
  if (destruction_receiver.IsWindowDestroyed()) {
    return;
  }
  EndBatchedSizeUpdate(destruction_receiver);
}

void Win32Window::RequestCloseImpl() {
  if (hwnd_) {
    PerformClose(hwnd_, true);
  }
}

void Win32Window::PerformClose(HWND hwnd, bool destroy_window) {
  if (cursor_auto_hide_timer_) {
    DeleteTimerQueueTimer(nullptr, cursor_auto_hide_timer_, nullptr);
    cursor_auto_hide_timer_ = nullptr;
  }
  {
    WindowDestructionReceiver destruction_receiver(this);
    OnBeforeClose(destruction_receiver);
    if (destruction_receiver.IsWindowDestroyed()) {
      return;
    }
  }
  relative_mouse_mode_ = false;
  UpdateCursorClip();
  RestoreDisplayMode();

  hwnd_ = nullptr;
  SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
  if (destroy_window) {
    DestroyWindow(hwnd);
  }
  OnAfterClose();
}

uint32_t Win32Window::GetLatestDpiImpl() const {
  return dpi_;
}

void Win32Window::ApplyNewFullscreen() {
  WindowDestructionReceiver destruction_receiver(this);
  if (IsFullscreen()) {
    ApplyFullscreenEntry(destruction_receiver);
    return;
  }
  if (!fullscreen_applied_) {
    return;
  }
  fullscreen_applied_ = false;
  RestoreDisplayMode();

  BeginBatchedSizeUpdate();
  auto bail = [&]() {
    if (destruction_receiver.IsWindowDestroyedOrClosed()) {
      if (!destruction_receiver.IsWindowDestroyed()) {
        EndBatchedSizeUpdate(destruction_receiver);
      }
      return true;
    }
    return false;
  };

  SetWindowLong(hwnd_, GWL_STYLE, GetWindowLong(hwnd_, GWL_STYLE) | WS_OVERLAPPEDWINDOW);
  if (bail()) {
    return;
  }

  dpi_ = GetCurrentDpi();
  if (dpi_ != pre_fullscreen_dpi_) {
    RECT new_dpi_rect;
    new_dpi_rect.left = 0;
    new_dpi_rect.top = 0;
    new_dpi_rect.right =
        LONG(ConvertSizeDpi(pre_fullscreen_normal_client_width_, dpi_, pre_fullscreen_dpi_));
    new_dpi_rect.bottom =
        LONG(ConvertSizeDpi(pre_fullscreen_normal_client_height_, dpi_, pre_fullscreen_dpi_));
    AdjustWindowRectangle(new_dpi_rect);
    pre_fullscreen_placement_.rcNormalPosition.right =
        pre_fullscreen_placement_.rcNormalPosition.left + (new_dpi_rect.right - new_dpi_rect.left);
    pre_fullscreen_placement_.rcNormalPosition.bottom =
        pre_fullscreen_placement_.rcNormalPosition.top + (new_dpi_rect.bottom - new_dpi_rect.top);
  }
  SetWindowPlacement(hwnd_, &pre_fullscreen_placement_);
  if (bail()) {
    return;
  }

  SetWindowPos(hwnd_, nullptr, 0, 0, 0, 0,
               SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
  if (bail()) {
    return;
  }

  EndBatchedSizeUpdate(destruction_receiver);
}

void Win32Window::ApplyNewTitle() {
  SetWindowTextW(hwnd_, ToWide(GetTitle()).c_str());
}

void Win32Window::LoadAndApplyIcon(const void* buffer, size_t size,
                                   bool can_apply_state_in_current_phase) {
  (void)can_apply_state_in_current_phase;
  bool reset = !buffer || !size;

  HICON new_icon, new_icon_small;
  if (reset) {
    if (!icon_) {
      return;
    }
    if (!hwnd_) {
      DestroyIcon(icon_);
      icon_ = nullptr;
      return;
    }
    new_icon = reinterpret_cast<HICON>(GetClassLongPtrW(hwnd_, GCLP_HICON));
    new_icon_small = reinterpret_cast<HICON>(GetClassLongPtrW(hwnd_, GCLP_HICONSM));

  } else {
    new_icon = CreateIconFromResourceEx(static_cast<PBYTE>(const_cast<void*>(buffer)), DWORD(size),
                                        true, 0x00030000, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
    if (!new_icon) {
      return;
    }
    new_icon_small = new_icon;
  }

  if (hwnd_) {
    SendMessageW(hwnd_, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(new_icon));
    SendMessageW(hwnd_, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(new_icon_small));
  }

  if (icon_) {
    DestroyIcon(icon_);
    icon_ = nullptr;
  }

  if (!reset) {
    assert_true(new_icon_small == new_icon);
    icon_ = new_icon;
  }
}

void Win32Window::ApplyNewMouseCapture() {
  SetCapture(hwnd_);
}

void Win32Window::ApplyNewMouseRelease() {
  if (GetCapture() != hwnd_) {
    return;
  }
  ReleaseCapture();
}

void Win32Window::ApplyNewCursorVisibility(CursorVisibility old_cursor_visibility) {
  CursorVisibility new_cursor_visibility = GetCursorVisibility();
  cursor_currently_auto_hidden_ = false;
  if (new_cursor_visibility == CursorVisibility::kAutoHidden) {
    if (!GetCursorPos(&cursor_auto_hide_last_screen_pos_)) {
      cursor_auto_hide_last_screen_pos_.x = LONG_MAX;
      cursor_auto_hide_last_screen_pos_.y = LONG_MAX;
    }
    cursor_currently_auto_hidden_ = true;
  } else if (old_cursor_visibility == CursorVisibility::kAutoHidden) {
    if (cursor_auto_hide_timer_) {
      DeleteTimerQueueTimer(nullptr, cursor_auto_hide_timer_, nullptr);
      cursor_auto_hide_timer_ = nullptr;
    }
  }
  SetCursorIfFocusedOnClientArea(new_cursor_visibility == CursorVisibility::kVisible ? arrow_cursor_
                                                                                     : nullptr);
}

void Win32Window::ApplyNewTextInputActive() {
  if (!hwnd_) {
    return;
  }

  ImmAssociateContextEx(hwnd_, nullptr, IsTextInputActive() ? IACE_DEFAULT : 0);
}

bool Win32Window::SetRelativeMouseMode(bool enable) {
  if (!hwnd_) {
    return false;
  }
  RAWINPUTDEVICE device = {};
  device.usUsagePage = 0x01;
  device.usUsage = 0x02;
  device.dwFlags = enable ? 0 : RIDEV_REMOVE;
  device.hwndTarget = enable ? hwnd_ : nullptr;
  if (!RegisterRawInputDevices(&device, 1, sizeof(device))) {
    REXLOG_WARN("RegisterRawInputDevices({}) failed ({})", enable, GetLastError());
    if (enable) {
      return false;
    }
  }
  relative_mouse_mode_ = enable;
  UpdateCursorClip();
  return enable;
}

void Win32Window::UpdateCursorClip() const {
  if (!relative_mouse_mode_ || !hwnd_ || GetFocus() != hwnd_) {
    ClipCursor(nullptr);
    return;
  }
  RECT client_rect;
  if (!GetClientRect(hwnd_, &client_rect)) {
    return;
  }
  POINT top_left = {client_rect.left, client_rect.top};
  POINT bottom_right = {client_rect.right, client_rect.bottom};
  ClientToScreen(hwnd_, &top_left);
  ClientToScreen(hwnd_, &bottom_right);
  RECT clip = {top_left.x, top_left.y, bottom_right.x, bottom_right.y};
  ClipCursor(&clip);
}

bool Win32Window::WarpMouseToCenter(int32_t& x_out, int32_t& y_out) {
  if (!hwnd_) {
    return false;
  }
  RECT client_rect;
  if (!GetClientRect(hwnd_, &client_rect) || client_rect.right <= 0 || client_rect.bottom <= 0) {
    return false;
  }
  POINT center = {client_rect.right / 2, client_rect.bottom / 2};
  POINT screen_center = center;
  if (!ClientToScreen(hwnd_, &screen_center) || !SetCursorPos(screen_center.x, screen_center.y)) {
    return false;
  }

  POINT actual;
  if (!GetCursorPos(&actual) || std::abs(actual.x - screen_center.x) > 1 ||
      std::abs(actual.y - screen_center.y) > 1) {
    return false;
  }
  x_out = center.x;
  y_out = center.y;
  return true;
}

void Win32Window::FocusImpl() {
  SetFocus(hwnd_);
}

std::unique_ptr<Surface> Win32Window::CreateSurfaceImpl(Surface::TypeFlags allowed_types) {
  HINSTANCE hinstance = Win32Context(app_context()).hinstance();
  if (allowed_types & Surface::kTypeFlag_Win32Hwnd) {
    return std::make_unique<Win32HwndSurface>(hinstance, hwnd_);
  }
  return nullptr;
}

void Win32Window::RequestPaintImpl() {
  InvalidateRect(hwnd_, nullptr, false);
}

BOOL Win32Window::AdjustWindowRectangle(RECT& rect, DWORD style, BOOL menu, DWORD ex_style,
                                        UINT dpi) const {
  const Win32WindowedAppContext::PerMonitorDpiV2Api* per_monitor_dpi_v2_api =
      Win32Context(app_context()).per_monitor_dpi_v2_api();
  if (per_monitor_dpi_v2_api) {
    return per_monitor_dpi_v2_api->adjust_window_rect_ex_for_dpi(&rect, style, menu, ex_style, dpi);
  }

  return AdjustWindowRectEx(&rect, style, menu, ex_style);
}

BOOL Win32Window::AdjustWindowRectangle(RECT& rect) const {
  if (!hwnd_) {
    return false;
  }
  return AdjustWindowRectangle(rect, GetWindowLong(hwnd_, GWL_STYLE), FALSE,
                               GetWindowLong(hwnd_, GWL_EXSTYLE), dpi_);
}

uint32_t Win32Window::GetCurrentSystemDpi() const {
  const Win32WindowedAppContext::PerMonitorDpiV2Api* per_monitor_dpi_v2_api =
      Win32Context(app_context()).per_monitor_dpi_v2_api();
  if (per_monitor_dpi_v2_api) {
    return per_monitor_dpi_v2_api->get_dpi_for_system();
  }

  HDC screen_hdc = GetDC(nullptr);
  if (!screen_hdc) {
    return USER_DEFAULT_SCREEN_DPI;
  }

  int logical_pixels_x = GetDeviceCaps(screen_hdc, LOGPIXELSX);
  ReleaseDC(nullptr, screen_hdc);
  return uint32_t(logical_pixels_x);
}

uint32_t Win32Window::GetCurrentDpi() const {
  if (hwnd_) {
    const Win32WindowedAppContext& win32_app_context = Win32Context(app_context());

    const Win32WindowedAppContext::PerMonitorDpiV2Api* per_monitor_dpi_v2_api =
        win32_app_context.per_monitor_dpi_v2_api();
    if (per_monitor_dpi_v2_api) {
      return per_monitor_dpi_v2_api->get_dpi_for_window(hwnd_);
    }

    const Win32WindowedAppContext::PerMonitorDpiV1Api* per_monitor_dpi_v1_api =
        win32_app_context.per_monitor_dpi_v1_api();
    if (per_monitor_dpi_v1_api) {
      HMONITOR monitor = MonitorFromWindow(hwnd_, MONITOR_DEFAULTTONEAREST);
      UINT monitor_dpi_x, monitor_dpi_y;
      if (monitor && SUCCEEDED(per_monitor_dpi_v1_api->get_dpi_for_monitor(
                         monitor, MDT_DEFAULT, &monitor_dpi_x, &monitor_dpi_y))) {
        return monitor_dpi_x;
      }
    }
  }

  return GetCurrentSystemDpi();
}

void Win32Window::ApplyFullscreenEntry(WindowDestructionReceiver& destruction_receiver) {
  if (!IsFullscreen()) {
    return;
  }
  if (fullscreen_applied_) {
    HMONITOR monitor = MonitorFromWindow(hwnd_, MONITOR_DEFAULTTONEAREST);
    if (monitor) {
      CoverMonitor(monitor, destruction_receiver);
    }
    return;
  }

  pre_fullscreen_dpi_ = dpi_;
  pre_fullscreen_placement_.length = sizeof(pre_fullscreen_placement_);
  HMONITOR monitor;
  MONITORINFO monitor_info;
  monitor_info.cbSize = sizeof(monitor_info);
  if (!GetWindowPlacement(hwnd_, &pre_fullscreen_placement_) ||
      !(monitor = MonitorFromWindow(hwnd_, MONITOR_DEFAULTTONEAREST)) ||
      !GetMonitorInfo(monitor, &monitor_info)) {
    OnDesiredFullscreenUpdate(false);
    return;
  }

  RECT non_client_area_rect = {};
  AdjustWindowRectangle(non_client_area_rect);
  pre_fullscreen_normal_client_width_ =
      uint32_t(std::max((pre_fullscreen_placement_.rcNormalPosition.right -
                         pre_fullscreen_placement_.rcNormalPosition.left) -
                            (non_client_area_rect.right - non_client_area_rect.left),
                        LONG(0)));
  pre_fullscreen_normal_client_height_ =
      uint32_t(std::max((pre_fullscreen_placement_.rcNormalPosition.bottom -
                         pre_fullscreen_placement_.rcNormalPosition.top) -
                            (non_client_area_rect.bottom - non_client_area_rect.top),
                        LONG(0)));

  BeginBatchedSizeUpdate();

  SetWindowLong(hwnd_, GWL_STYLE, GetWindowLong(hwnd_, GWL_STYLE) & ~DWORD(WS_OVERLAPPEDWINDOW));
  if (destruction_receiver.IsWindowDestroyedOrClosed()) {
    if (!destruction_receiver.IsWindowDestroyed()) {
      EndBatchedSizeUpdate(destruction_receiver);
    }
    return;
  }

  fullscreen_applied_ = true;
  CoverMonitor(monitor, destruction_receiver);
  if (destruction_receiver.IsWindowDestroyed()) {
    return;
  }

  EndBatchedSizeUpdate(destruction_receiver);
}

void Win32Window::HandleSizeUpdate(WindowDestructionReceiver& destruction_receiver) {
  if (!hwnd_) {
    return;
  }

  {
    MonitorUpdateEvent e(this, false);
    OnMonitorUpdate(e);
  }

  if (!IsFullscreen()) {
    WINDOWPLACEMENT window_placement;
    window_placement.length = sizeof(window_placement);
    if (GetWindowPlacement(hwnd_, &window_placement)) {
      RECT non_client_area_rect = {};
      if (AdjustWindowRectangle(non_client_area_rect)) {
        OnDesiredLogicalSizeUpdate(
            SizeToLogical(uint32_t(std::max(
                (window_placement.rcNormalPosition.right - window_placement.rcNormalPosition.left) -
                    (non_client_area_rect.right - non_client_area_rect.left),
                LONG(0)))),
            SizeToLogical(uint32_t(std::max(
                (window_placement.rcNormalPosition.bottom - window_placement.rcNormalPosition.top) -
                    (non_client_area_rect.bottom - non_client_area_rect.top),
                LONG(0)))));
      }
    }
  }

  RECT client_rect;
  if (GetClientRect(hwnd_, &client_rect)) {
    OnActualSizeUpdate(uint32_t(client_rect.right), uint32_t(client_rect.bottom),
                       destruction_receiver);
    if (destruction_receiver.IsWindowDestroyedOrClosed()) {
      return;
    }
  }
  UpdateCursorClip();
}

void Win32Window::BeginBatchedSizeUpdate() {
  ++batched_size_update_depth_;
}

void Win32Window::EndBatchedSizeUpdate(WindowDestructionReceiver& destruction_receiver) {
  assert_not_zero(batched_size_update_depth_);
  if (--batched_size_update_depth_) {
    return;
  }

  if (batched_size_update_contained_wm_size_) {
    batched_size_update_contained_wm_size_ = false;
    HandleSizeUpdate(destruction_receiver);
    if (destruction_receiver.IsWindowDestroyed()) {
      return;
    }
  }
  if (batched_size_update_contained_wm_paint_) {
    batched_size_update_contained_wm_paint_ = false;
    RequestPaint();
  }
}

bool Win32Window::HandleMouse(UINT message, WPARAM wParam, LPARAM lParam,
                              WindowDestructionReceiver& destruction_receiver) {
  int32_t message_x = GET_X_LPARAM(lParam);
  int32_t message_y = GET_Y_LPARAM(lParam);
  bool message_pos_is_screen = message == WM_MOUSEWHEEL || message == WM_MOUSEHWHEEL;

  POINT client_pos = {message_x, message_y};
  if (message_pos_is_screen) {
    ScreenToClient(hwnd_, &client_pos);
  }

  if (GetCursorVisibility() == CursorVisibility::kAutoHidden) {
    POINT screen_pos = {message_x, message_y};
    if (message_pos_is_screen || ClientToScreen(hwnd_, &screen_pos)) {
      if (screen_pos.x != cursor_auto_hide_last_screen_pos_.x ||
          screen_pos.y != cursor_auto_hide_last_screen_pos_.y) {
        cursor_currently_auto_hidden_ = false;
        SetCursorAutoHideTimer();
        cursor_auto_hide_last_screen_pos_ = screen_pos;
      }
    }
  }

  MouseEvent::Button button = MouseEvent::Button::kNone;
  int32_t scroll_x = 0;
  int32_t scroll_y = 0;
  switch (message) {
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
      button = MouseEvent::Button::kLeft;
      break;
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
      button = MouseEvent::Button::kRight;
      break;
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
      button = MouseEvent::Button::kMiddle;
      break;
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP:
      switch (GET_XBUTTON_WPARAM(wParam)) {
        case XBUTTON1:
          button = MouseEvent::Button::kX1;
          break;
        case XBUTTON2:
          button = MouseEvent::Button::kX2;
          break;
        default:

          break;
      }
      break;
    case WM_MOUSEMOVE:
      button = MouseEvent::Button::kNone;
      break;
    case WM_MOUSEWHEEL:
      static_assert(MouseEvent::kScrollPerDetent == WHEEL_DELTA,
                    "Assuming the Windows scroll amount can be passed directly to MouseEvent");
      scroll_y = GET_WHEEL_DELTA_WPARAM(wParam);
      break;
    case WM_MOUSEHWHEEL:
      scroll_x = GET_WHEEL_DELTA_WPARAM(wParam);
      break;
    default:
      return false;
  }

  MouseEvent e(this, button, client_pos.x, client_pos.y, scroll_x, scroll_y);
  switch (message) {
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_XBUTTONDOWN:
      OnMouseDown(e, destruction_receiver);
      break;
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_XBUTTONUP:
      OnMouseUp(e, destruction_receiver);
      break;
    case WM_MOUSEMOVE:
      OnMouseMove(e, destruction_receiver);
      break;
    case WM_MOUSEWHEEL:
    case WM_MOUSEHWHEEL:
      OnMouseWheel(e, destruction_receiver);
      break;
    default:
      break;
  }

  return e.is_handled();
}

void Win32Window::HandleRawInput(LPARAM lParam, WindowDestructionReceiver& destruction_receiver) {
  RAWINPUT raw;
  UINT size = sizeof(raw);
  if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, &raw, &size,
                      sizeof(RAWINPUTHEADER)) == UINT(-1) ||
      raw.header.dwType != RIM_TYPEMOUSE) {
    return;
  }
  const RAWMOUSE& mouse = raw.data.mouse;

  if ((mouse.usFlags & MOUSE_MOVE_ABSOLUTE) || (!mouse.lLastX && !mouse.lLastY)) {
    return;
  }
  POINT client_pos = {};
  GetCursorPos(&client_pos);
  ScreenToClient(hwnd_, &client_pos);
  MouseEvent e(this, MouseEvent::Button::kNone, client_pos.x, client_pos.y, 0, 0,
               float(mouse.lLastX), float(mouse.lLastY));
  OnMouseMove(e, destruction_receiver);
}

bool Win32Window::HandleKeyboard(UINT message, WPARAM wParam, LPARAM lParam,
                                 WindowDestructionReceiver& destruction_receiver) {
  if (message == WM_CHAR && !IsTextInputActive()) {
    return false;
  }
  KeyEvent e(this, VirtualKey(wParam), lParam & 0xFFFF, !!(lParam & (LPARAM(1) << 30)),
             !!(GetKeyState(VK_SHIFT) & 0x80), !!(GetKeyState(VK_CONTROL) & 0x80),
             !!(GetKeyState(VK_MENU) & 0x80),
             !!((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & 0x80));
  switch (message) {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
      OnKeyDown(e, destruction_receiver);
      break;
    case WM_KEYUP:
    case WM_SYSKEYUP:
      OnKeyUp(e, destruction_receiver);
      break;
    case WM_CHAR:
      OnKeyChar(e, destruction_receiver);
      break;
    default:
      break;
  }

  return e.is_handled();
}

void Win32Window::SetCursorIfFocusedOnClientArea(HCURSOR cursor) const {
  if (!HasFocus()) {
    return;
  }
  POINT cursor_pos;
  if (!GetCursorPos(&cursor_pos)) {
    return;
  }
  if (WindowFromPoint(cursor_pos) == hwnd_ &&
      SendMessage(hwnd_, WM_NCHITTEST, 0, MAKELONG(cursor_pos.x, cursor_pos.y)) == HTCLIENT) {
    SetCursor(cursor);
  }
}

void Win32Window::SetCursorAutoHideTimer() {
  if (cursor_auto_hide_timer_) {
    DeleteTimerQueueTimer(nullptr, cursor_auto_hide_timer_, nullptr);
    cursor_auto_hide_timer_ = nullptr;
  }

  last_cursor_auto_hide_queued_ = last_cursor_auto_hide_signaled_ + 1;
  CreateTimerQueueTimer(&cursor_auto_hide_timer_, nullptr, AutoHideCursorTimerCallback, this,
                        GetCursorAutoHideDelayMs(), 0,
                        WT_EXECUTEINTIMERTHREAD | WT_EXECUTEONLYONCE);
}

void Win32Window::AutoHideCursorTimerCallback(void* parameter, BOOLEAN timer_or_wait_fired) {
  if (!timer_or_wait_fired) {
    return;
  }
  Win32Window& window = *static_cast<Win32Window*>(parameter);
  window.last_cursor_auto_hide_signaled_ = window.last_cursor_auto_hide_queued_;
  SendMessage(window.hwnd_, kUserMessageAutoHideCursor, window.last_cursor_auto_hide_signaled_, 0);
}

LRESULT Win32Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message >= WM_MOUSEFIRST && message <= WM_MOUSELAST) {
    WindowDestructionReceiver destruction_receiver(this);
    return HandleMouse(message, wParam, lParam, destruction_receiver)
               ? 0
               : DefWindowProcW(hWnd, message, wParam, lParam);
  }
  if (message >= WM_KEYFIRST && message <= WM_KEYLAST) {
    WindowDestructionReceiver destruction_receiver(this);
    bool handled = HandleKeyboard(message, wParam, lParam, destruction_receiver);

    if (handled && message != WM_SYSKEYDOWN && message != WM_SYSKEYUP) {
      return 0;
    }
    return DefWindowProcW(hWnd, message, wParam, lParam);
  }

  switch (message) {
    case WM_CLOSE: {
      WindowDestructionReceiver destruction_receiver(this);
      if (!SendCloseRequestToListeners(destruction_receiver)) {
        return 0;
      }
      if (destruction_receiver.IsWindowDestroyed() || !hwnd_) {
        return 0;
      }
      PerformClose(hWnd, true);
      return 0;
    }

    case WM_DESTROY:

      PerformClose(hWnd, false);
      break;

    case WM_DROPFILES: {
      HDROP drop_handle = reinterpret_cast<HDROP>(wParam);
      auto drop_count = DragQueryFileW(drop_handle, 0xFFFFFFFFu, nullptr, 0);
      if (drop_count > 0) {
        UINT path_size = DragQueryFileW(drop_handle, 0, nullptr, 0);
        if (path_size > 0 && path_size < 0xFFFFFFFFu) {
          std::wstring path;
          ++path_size;
          path.resize(path_size);

          path_size = DragQueryFileW(drop_handle, 0, path.data(), path_size);
          if (path_size > 0) {
            path.resize(path_size);
            FileDropEvent e(this, std::filesystem::path(path));
            WindowDestructionReceiver destruction_receiver(this);
            OnFileDrop(e, destruction_receiver);
            if (destruction_receiver.IsWindowDestroyedOrClosed()) {
              DragFinish(drop_handle);
              break;
            }
          }
        }
      }
      DragFinish(drop_handle);
    } break;

    case WM_MOVE: {
      MonitorUpdateEvent update_event{this, false};
      OnMonitorUpdate(update_event);
      UpdateCursorClip();
    } break;

    case WM_SIZE: {
      WindowDestructionReceiver destruction_receiver(this);
      if (wParam == SIZE_MINIMIZED) {
        if (!minimized_) {
          minimized_ = true;
          OnMinimized(destruction_receiver);
          if (destruction_receiver.IsWindowDestroyedOrClosed()) {
            break;
          }
        }
      } else if (minimized_ && (wParam == SIZE_RESTORED || wParam == SIZE_MAXIMIZED)) {
        minimized_ = false;
        OnRestored(destruction_receiver);
        if (destruction_receiver.IsWindowDestroyedOrClosed()) {
          break;
        }
      }
      if (batched_size_update_depth_) {
        batched_size_update_contained_wm_size_ = true;
      } else {
        HandleSizeUpdate(destruction_receiver);
      }
    } break;

    case WM_PAINT: {
      if (batched_size_update_depth_) {
        batched_size_update_contained_wm_paint_ = true;
      } else {
        ValidateRect(hwnd_, nullptr);
        OnPaint();
      }

      return 0;
    }

    case WM_ERASEBKGND: {
      if (HasSurface()) {
        return 0;
      }
    } break;

    case WM_DISPLAYCHANGE: {
      MonitorUpdateEvent update_event{this, true};
      OnMonitorUpdate(update_event);
    } break;

    case WM_DPICHANGED: {
      dpi_ = GetCurrentDpi();

      WindowDestructionReceiver destruction_receiver(this);

      {
        UISetupEvent e(this);
        OnDpiChanged(e, destruction_receiver);

        if (destruction_receiver.IsWindowDestroyedOrClosed()) {
          break;
        }
      }

      auto rect = reinterpret_cast<const RECT*>(lParam);
      if (rect) {
        SetWindowPos(hwnd_, nullptr, int(rect->left), int(rect->top), int(rect->right - rect->left),
                     int(rect->bottom - rect->top), SWP_NOZORDER | SWP_NOACTIVATE);
        if (destruction_receiver.IsWindowDestroyedOrClosed()) {
          break;
        }
      }
    } break;

    case WM_ACTIVATEAPP: {
      if (!wParam && !switched_display_.empty()) {
        RestoreDisplayMode();
        ShowWindow(hwnd_, SW_MINIMIZE);
      } else if (wParam && fullscreen_applied_ && REXCVAR_GET(fullscreen_exclusive) &&
                 switched_display_.empty()) {
        WindowDestructionReceiver destruction_receiver(this);
        HMONITOR monitor = MonitorFromWindow(hwnd_, MONITOR_DEFAULTTONEAREST);
        if (monitor) {
          CoverMonitor(monitor, destruction_receiver);
        }
        if (destruction_receiver.IsWindowDestroyedOrClosed()) {
          break;
        }
      }
    } break;

    case WM_KILLFOCUS: {
      ClipCursor(nullptr);
      WindowDestructionReceiver destruction_receiver(this);
      OnFocusUpdate(false, destruction_receiver);
      if (destruction_receiver.IsWindowDestroyedOrClosed()) {
        break;
      }
    } break;

    case WM_SETFOCUS: {
      WindowDestructionReceiver destruction_receiver(this);
      OnFocusUpdate(true, destruction_receiver);
      if (destruction_receiver.IsWindowDestroyedOrClosed()) {
        break;
      }
      UpdateCursorClip();
    } break;

    case WM_INPUT: {
      if (relative_mouse_mode_) {
        WindowDestructionReceiver destruction_receiver(this);
        HandleRawInput(lParam, destruction_receiver);
        if (destruction_receiver.IsWindowDestroyedOrClosed()) {
          return 0;
        }
      }
    } break;

    case WM_SETCURSOR: {
      if (reinterpret_cast<HWND>(wParam) == hwnd_ && HasFocus() && LOWORD(lParam) == HTCLIENT) {
        switch (GetCursorVisibility()) {
          case CursorVisibility::kAutoHidden: {
            if (HIWORD(lParam) != WM_MOUSEMOVE) {
              cursor_currently_auto_hidden_ = false;
              SetCursorAutoHideTimer();
            }
            if (cursor_currently_auto_hidden_) {
              SetCursor(nullptr);
              return true;
            }
          } break;
          case CursorVisibility::kHidden:
            SetCursor(nullptr);
            return true;
          default:
            break;
        }
      }

    } break;

    case kUserMessageAutoHideCursor: {
      if (GetCursorVisibility() == CursorVisibility::kAutoHidden &&
          wParam == last_cursor_auto_hide_queued_) {
        if (cursor_auto_hide_timer_) {
          DeleteTimerQueueTimer(nullptr, cursor_auto_hide_timer_, nullptr);
          cursor_auto_hide_timer_ = nullptr;
        }
        cursor_currently_auto_hidden_ = true;
        SetCursorIfFocusedOnClientArea(nullptr);
      }
      return 0;
    }

    case 0x02CC:

      return 0x00000001 | 0x00000008 | 0x00000010 | 0x00010000 | 0x00100000 | 0x00200000 |
             0x00400000 | 0x00800000;
  }

  return DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK Win32Window::WndProcThunk(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (hWnd) {
    Win32Window* window = nullptr;
    if (message == WM_NCCREATE) {
      auto create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
      window = reinterpret_cast<Win32Window*>(create_struct->lpCreateParams);
      SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));

      if (window->phase() == Phase::kOpening) {
        assert_true(!window->hwnd_ || window->hwnd_ == hWnd);
        window->hwnd_ = hWnd;
      }

      const Win32WindowedAppContext::PerMonitorDpiV2Api* per_monitor_dpi_v2_api =
          Win32Context(window->app_context()).per_monitor_dpi_v2_api();
      if (per_monitor_dpi_v2_api) {
        per_monitor_dpi_v2_api->enable_non_client_dpi_scaling(hWnd);
      }

    } else {
      window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
      if (window && window->hwnd_ == hWnd) {
        return window->WndProc(hWnd, message, wParam, lParam);
      }
    }
  }
  return DefWindowProcW(hWnd, message, wParam, lParam);
}

}
