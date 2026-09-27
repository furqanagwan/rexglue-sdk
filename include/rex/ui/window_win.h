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

  // Null if the window hasn't been opened yet, or has been closed.
  HWND hwnd() const { return hwnd_; }

  uint32_t GetMediumDpi() const override;
  void* GetNativeWindowHandle() const override { return hwnd_; }
  bool SetRelativeMouseMode(bool enable) override;
  bool WarpMouseToCenter(int32_t& x_out, int32_t& y_out) override;

 protected:
  bool OpenImpl() override;
  void RequestCloseImpl() override;

  uint32_t GetLatestDpiImpl() const override;

  void ApplyNewFullscreen() override;
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

  // Centers the window on the `monitor` cvar's display (1-based, 0 = leave).
  void ApplyMonitorSelection();

  void ApplyFullscreenEntry(WindowDestructionReceiver& destruction_receiver);

  void HandleSizeUpdate(WindowDestructionReceiver& destruction_receiver);
  // For updating multiple factors that may influence the window size at once,
  // without handling WM_SIZE multiple times (that may not only result in wasted
  // handling, but also in the state potentially changed to an inconsistent one
  // in the middle of a size update by the listeners).
  void BeginBatchedSizeUpdate();
  void EndBatchedSizeUpdate(WindowDestructionReceiver& destruction_receiver);

  // The close choreography shared by WM_CLOSE (after the listeners' veto),
  // RequestCloseImpl (no veto) and a forced WM_DESTROY.
  void PerformClose(HWND hwnd, bool destroy_window);

  bool HandleMouse(UINT message, WPARAM wParam, LPARAM lParam,
                   WindowDestructionReceiver& destruction_receiver);
  bool HandleKeyboard(UINT message, WPARAM wParam, LPARAM lParam,
                      WindowDestructionReceiver& destruction_receiver);
  void HandleRawInput(LPARAM lParam, WindowDestructionReceiver& destruction_receiver);

  // Confines the cursor to the client area while relative mouse mode is on
  // and the window has focus; releases it otherwise.
  void UpdateCursorClip() const;

  void SetCursorIfFocusedOnClientArea(HCURSOR cursor) const;
  void SetCursorAutoHideTimer();
  static void NTAPI AutoHideCursorTimerCallback(void* parameter, BOOLEAN timer_or_wait_fired);

  static LRESULT CALLBACK WndProcThunk(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
  // This can't handle messages sent during CreateWindow (hwnd_ still not
  // assigned to) or after nulling hwnd_ in closing / deleting.
  LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

  HCURSOR arrow_cursor_ = nullptr;

  HICON icon_ = nullptr;

  uint32_t dpi_ = USER_DEFAULT_SCREEN_DPI;

  // hwnd_ may be accessed by the cursor hiding timer callback from a separate
  // thread, but the timer can be active only with a valid window anyway.
  HWND hwnd_ = nullptr;

  uint32_t batched_size_update_depth_ = 0;
  bool batched_size_update_contained_wm_size_ = false;
  bool batched_size_update_contained_wm_paint_ = false;

  bool minimized_ = false;
  bool relative_mouse_mode_ = false;

  uint32_t pre_fullscreen_dpi_ = USER_DEFAULT_SCREEN_DPI;
  WINDOWPLACEMENT pre_fullscreen_placement_ = {};
  // The client area part of pre_fullscreen_placement_.rcNormalPosition, saved
  // in case something affecting AdjustWindowRectEx for the non-fullscreen
  // state changes mid-fullscreen.
  uint32_t pre_fullscreen_normal_client_width_ = 0;
  uint32_t pre_fullscreen_normal_client_height_ = 0;

  // Must be the screen position, not the client position, so it's possible to
  // immediately hide the cursor, for instance, when switching to fullscreen
  // (and thus changing the client area top-left corner, resulting in
  // WM_MOUSEMOVE being sent, which would instantly reveal the cursor because of
  // that relative position change).
  POINT cursor_auto_hide_last_screen_pos_ = {LONG_MAX, LONG_MAX};
  // A timer queue timer rather than WM_TIMER, which is never received while
  // WM_PAINT is sent continuously.
  HANDLE cursor_auto_hide_timer_ = nullptr;
  // Last hiding case numbers for skipping obsolete cursor hiding messages. The
  // queued index is read, and the signaled index is written, by the timer
  // callback outside the message thread, so delete the timer (which cancels or
  // awaits the callback) before touching them here. Compared for equality for
  // safe rollover.
  WPARAM last_cursor_auto_hide_queued_ = 0;
  WPARAM last_cursor_auto_hide_signaled_ = 0;
  // Whether the cursor has been hidden after the expiration of the timer, and
  // hasn't been revealed yet.
  bool cursor_currently_auto_hidden_ = false;
};

}  // namespace rex::ui
