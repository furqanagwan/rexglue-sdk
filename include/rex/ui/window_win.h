/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    ReXGlue, 2026 - Ported from xenia-edge 213dcc267 (last native
 *              Win32 window before its Qt conversion) for RG-GDK-021: no native
 *              menus (parity with the SDL window), close veto, minimize/restore,
 *              relative mouse mode, warp, text input gating, native handle.
 */

#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

#include <rex/ui/window.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

namespace rex::ui {

class Win32Window final : public Window {
 public:
  Win32Window(WindowedAppContext& app_context, const std::string_view title,
              uint32_t desired_logical_width, uint32_t desired_logical_height);
  ~Win32Window() override;

  HWND hwnd() const { return hwnd_; }

  uint32_t GetMediumDpi() const override;
  void* GetNativeWindowHandle() const override { return hwnd_; }
  bool SetRelativeMouseMode(bool enable) override;
  bool WarpMouseToCenter(int32_t& x_out, int32_t& y_out) override;

  bool GetDisplayPixelSize(uint32_t& width, uint32_t& height) const override;

 protected:
  bool OpenImpl() override;
  void RequestCloseImpl() override;

  uint32_t GetLatestDpiImpl() const override;

  void ApplyNewFullscreen() override;
  void ApplyNewMonitor() override;
  void ApplyNewDesiredLogicalSize() override;
  void ApplyNewTitle() override;
  void LoadAndApplyIcon(const void* buffer, size_t size,
                        bool can_apply_state_in_current_phase) override;
  void ApplyNewMouseCapture() override;
  void ApplyNewMouseRelease() override;
  void ApplyNewCursorVisibility(CursorVisibility old_cursor_visibility) override;
  void ApplyNewTextInputActive() override;

  void FocusImpl() override;

  std::unique_ptr<Surface> CreateSurfaceImpl(Surface::TypeFlags allowed_types) override;
  void RequestPaintImpl() override;

 private:
  enum : UINT {
    kUserMessageAutoHideCursor = WM_USER,
  };

  BOOL AdjustWindowRectangle(RECT& rect, DWORD style, BOOL menu, DWORD ex_style, UINT dpi) const;
  BOOL AdjustWindowRectangle(RECT& rect) const;

  uint32_t GetCurrentSystemDpi() const;
  uint32_t GetCurrentDpi() const;

  static HMONITOR MonitorForIndex(int32_t monitor_index);

  void ApplyMonitorSelection();

  void ApplyFullscreenEntry(WindowDestructionReceiver& destruction_receiver);

  void CoverMonitor(HMONITOR monitor, WindowDestructionReceiver& destruction_receiver);

  bool SwitchDisplayMode(HMONITOR monitor);

  void RestoreDisplayMode();

  void HandleSizeUpdate(WindowDestructionReceiver& destruction_receiver);

  void BeginBatchedSizeUpdate();
  void EndBatchedSizeUpdate(WindowDestructionReceiver& destruction_receiver);

  void PerformClose(HWND hwnd, bool destroy_window);

  bool HandleMouse(UINT message, WPARAM wParam, LPARAM lParam,
                   WindowDestructionReceiver& destruction_receiver);
  bool HandleKeyboard(UINT message, WPARAM wParam, LPARAM lParam,
                      WindowDestructionReceiver& destruction_receiver);
  void HandleRawInput(LPARAM lParam, WindowDestructionReceiver& destruction_receiver);

  void UpdateCursorClip() const;

  void SetCursorIfFocusedOnClientArea(HCURSOR cursor) const;
  void SetCursorAutoHideTimer();
  static void NTAPI AutoHideCursorTimerCallback(void* parameter, BOOLEAN timer_or_wait_fired);

  static LRESULT CALLBACK WndProcThunk(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

  LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

  HCURSOR arrow_cursor_ = nullptr;

  HICON icon_ = nullptr;

  uint32_t dpi_ = USER_DEFAULT_SCREEN_DPI;

  HWND hwnd_ = nullptr;

  uint32_t batched_size_update_depth_ = 0;
  bool batched_size_update_contained_wm_size_ = false;
  bool batched_size_update_contained_wm_paint_ = false;

  bool minimized_ = false;
  bool relative_mouse_mode_ = false;

  bool fullscreen_applied_ = false;

  std::wstring switched_display_;

  uint32_t pre_fullscreen_dpi_ = USER_DEFAULT_SCREEN_DPI;
  WINDOWPLACEMENT pre_fullscreen_placement_ = {};

  uint32_t pre_fullscreen_normal_client_width_ = 0;
  uint32_t pre_fullscreen_normal_client_height_ = 0;

  POINT cursor_auto_hide_last_screen_pos_ = {LONG_MAX, LONG_MAX};

  HANDLE cursor_auto_hide_timer_ = nullptr;

  WPARAM last_cursor_auto_hide_queued_ = 0;
  WPARAM last_cursor_auto_hide_signaled_ = 0;

  bool cursor_currently_auto_hidden_ = false;
};

}
