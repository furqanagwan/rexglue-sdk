#pragma once
/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include <rex/platform.h>
#include <rex/ui/menu_item.h>
#include <rex/ui/presenter.h>
#include <rex/ui/surface.h>
#include <rex/ui/ui_event.h>
#include <rex/ui/virtual_key.h>
#include <rex/ui/window_listener.h>
#include <rex/ui/windowed_app_context.h>

namespace rex {
namespace ui {

class Window {
 public:
  enum class Phase {

    kClosedOpenable,

    kOpening,

    kOpen,

    kOpenBeforeClosing,

    kClosing,

    kClosedLeavingListeners,

    kDeleting,
  };

  enum class CursorVisibility {
    kVisible,

    kAutoHidden,
    kHidden,
  };

  static std::unique_ptr<Window> Create(WindowedAppContext& app_context,
                                        const std::string_view title);

  static std::unique_ptr<Window> Create(WindowedAppContext& app_context,
                                        const std::string_view title,
                                        uint32_t desired_logical_width,
                                        uint32_t desired_logical_height);

  virtual ~Window();

  WindowedAppContext& app_context() const { return app_context_; }

  Phase phase() const { return phase_; }
  bool HasActualState() const { return phase_ >= Phase::kOpening && phase_ <= Phase::kClosing; }

  void AddListener(WindowListener* listener);
  void RemoveListener(WindowListener* listener);
  void AddInputListener(WindowInputListener* listener, size_t z_order);
  void RemoveInputListener(WindowInputListener* listener);

  bool Open();

  void RequestClose() {
    if (phase_ != Phase::kOpen) {
      return;
    }
    RequestCloseImpl();
  }

  virtual uint32_t GetMediumDpi() const { return 96; }
  uint32_t GetDpi() const {
    uint32_t dpi = GetLatestDpiImpl();
    return dpi ? dpi : GetMediumDpi();
  }

  static constexpr uint32_t ConvertSizeDpi(uint32_t size, uint32_t new_dpi, uint32_t old_dpi) {
    return uint32_t((uint64_t(size) * new_dpi + (old_dpi - 1)) / old_dpi);
  }
  uint32_t SizeToLogical(uint32_t size) const {
    return ConvertSizeDpi(size, GetMediumDpi(), GetDpi());
  }
  uint32_t SizeToPhysical(uint32_t size) const {
    return ConvertSizeDpi(size, GetDpi(), GetMediumDpi());
  }
  static constexpr int32_t ConvertPositionDpi(int32_t position, uint32_t new_dpi,
                                              uint32_t old_dpi) {
    return int32_t((int64_t(position) * new_dpi + int32_t(old_dpi >> 1) * (position < 0 ? -1 : 1)) /
                   old_dpi);
  }
  int32_t PositionToLogical(int32_t position) const {
    return ConvertPositionDpi(position, GetMediumDpi(), GetDpi());
  }
  int32_t PositionToPhysical(int32_t position) const {
    return ConvertPositionDpi(position, GetDpi(), GetMediumDpi());
  }

  uint32_t GetDesiredLogicalWidth() const { return desired_logical_width_; }
  uint32_t GetDesiredLogicalHeight() const { return desired_logical_height_; }
  void SetDesiredLogicalSize(uint32_t new_desired_logical_width,
                             uint32_t new_desired_logical_height);
  static void ResolveConfiguredLogicalSize(uint32_t& width_out, uint32_t& height_out);

  uint32_t GetActualPhysicalWidth() const { return HasActualState() ? actual_physical_width_ : 0; }
  uint32_t GetActualPhysicalHeight() const {
    return HasActualState() ? actual_physical_height_ : 0;
  }
  uint32_t GetActualLogicalWidth() const { return SizeToLogical(GetActualPhysicalWidth()); }
  uint32_t GetActualLogicalHeight() const { return SizeToLogical(GetActualPhysicalHeight()); }

  virtual bool GetDisplayPixelSize(uint32_t& width, uint32_t& height) const {
    (void)width;
    (void)height;
    return false;
  }

  bool IsFullscreen() const { return fullscreen_; }
  void SetFullscreen(bool new_fullscreen);
  void RefreshFullscreen();

  int32_t GetMonitor() const { return monitor_; }
  void SetMonitor(int32_t new_monitor);

  const std::string& GetTitle() const { return title_; }
  void SetTitle(const std::string_view new_title);

  void SetIcon(const void* buffer, size_t size);
  void ResetIcon() { SetIcon(nullptr, 0); }

  virtual void* GetNativeWindowHandle() const { return nullptr; }

  void SetMainMenu(std::unique_ptr<MenuItem> new_main_menu);
  void CompleteMainMenuItemsUpdate();
  void SetMainMenuEnabled(bool enabled);

  bool IsMouseCaptureRequested() const { return mouse_capture_request_count_ != 0; }
  void CaptureMouse();
  void ReleaseMouse();

  virtual bool SetRelativeMouseMode(bool enable) {
    (void)enable;
    return false;
  }

  virtual bool WarpMouseToCenter(int32_t& x_out, int32_t& y_out) {
    (void)x_out;
    (void)y_out;
    return false;
  }

  bool IsTextInputActive() const { return text_input_active_; }
  void SetTextInputActive(bool active);

  CursorVisibility GetCursorVisibility() const { return cursor_visibility_; }

  void SetCursorVisibility(CursorVisibility new_cursor_visibility);

  uint32_t GetCursorAutoHideDelayMs() const { return cursor_auto_hide_delay_ms_; }

  void SetCursorAutoHideDelayMs(uint32_t delay_ms) { cursor_auto_hide_delay_ms_ = delay_ms; }

  bool HasFocus() const { return HasActualState() ? has_focus_ : false; }

  void Focus();

  void SetPresenter(Presenter* presenter);

  void RequestPaint() {
    if (presenter_surface_) {
      RequestPaintImpl();
    }
  }
  void RequestPresenterUIPaintFromUIThread() {
    if (presenter_) {
      presenter_->RequestUIPaintFromUIThread();
    }
  }

 protected:
  class WindowDestructionReceiver {
   public:
    explicit WindowDestructionReceiver(Window* window) : window_(window) {
      if (window_) {
        outer_receiver_ = window_->innermost_destruction_receiver_;
        window_->innermost_destruction_receiver_ = this;
      }
    }

    ~WindowDestructionReceiver() {
      if (window_) {
        assert_true(window_->innermost_destruction_receiver_ == this);
        window_->innermost_destruction_receiver_ = outer_receiver_;
      }
    }

    bool IsWindowDestroyed() const { return window_ == nullptr; }

    bool IsWindowDestroyedOrClosed() const { return IsWindowDestroyed() || window_->IsClosed(); }

    bool IsWindowDestroyedOrStateInapplicable() const {
      return IsWindowDestroyed() || !window_->CanApplyState();
    }
    bool IsWindowDestroyedOrListenersUncallable() const {
      return IsWindowDestroyed() || !window_->CanSendEventsToListeners();
    }

   private:
    friend Window;
    Window* window_;
    WindowDestructionReceiver* outer_receiver_ = nullptr;
  };

  static constexpr uint32_t kDefaultCursorAutoHideMilliseconds = 3333;

  Window(WindowedAppContext& app_context, const std::string_view title,
         uint32_t desired_logical_width, uint32_t desired_logical_height);

  void EnterDestructor() {
    phase_ = Phase::kDeleting;

    OnSurfaceChanged(false);
  }

  virtual uint32_t GetLatestDpiImpl() const { return GetMediumDpi(); }

  virtual bool OpenImpl() = 0;
  virtual void RequestCloseImpl() = 0;

  virtual void ApplyNewFullscreen() {}
  virtual void ApplyNewMonitor() {}
  virtual void ApplyNewDesiredLogicalSize() {}
  virtual void ApplyNewTitle() {}

  virtual void LoadAndApplyIcon(const void* buffer, size_t size,
                                bool can_apply_state_in_current_phase) {
    (void)buffer;
    (void)size;
    (void)can_apply_state_in_current_phase;
  }
  MenuItem* GetMainMenu() const { return main_menu_.get(); }

  virtual void ApplyNewMainMenu(MenuItem* old_main_menu) { (void)old_main_menu; }

  virtual void CompleteMainMenuItemsUpdateImpl() {}

  virtual void ApplyNewMouseCapture() {}
  virtual void ApplyNewMouseRelease() {}
  virtual void ApplyNewTextInputActive() {}
  virtual void ApplyNewCursorVisibility(CursorVisibility old_cursor_visibility) {
    (void)old_cursor_visibility;
  }

  virtual void FocusImpl() {}

  Presenter* presenter() const { return presenter_; }
  bool HasSurface() const { return presenter_surface_ != nullptr; }

  void OnSurfaceChanged(bool new_surface_potentially_exists);

  virtual std::unique_ptr<Surface> CreateSurfaceImpl(Surface::TypeFlags allowed_types) = 0;

  virtual void RequestPaintImpl() = 0;

  void OnBeforeClose(WindowDestructionReceiver& destruction_receiver);
  void OnAfterClose();

  bool SendCloseRequestToListeners(WindowDestructionReceiver& destruction_receiver);

  void OnMinimized(WindowDestructionReceiver& destruction_receiver);
  void OnRestored(WindowDestructionReceiver& destruction_receiver);

  void OnDpiChanged(UISetupEvent& e, WindowDestructionReceiver& destruction_receiver);
  void OnMonitorUpdate(MonitorUpdateEvent& e);

  void OnDesiredLogicalSizeUpdate(uint32_t new_desired_logical_width,
                                  uint32_t new_desired_logical_height) {
    desired_logical_width_ = new_desired_logical_width;
    desired_logical_height_ = new_desired_logical_height;
  }

  bool OnActualSizeUpdate(uint32_t new_physical_width, uint32_t new_physical_height,
                          WindowDestructionReceiver& destruction_receiver);
  void OnDesiredFullscreenUpdate(bool new_fullscreen) { fullscreen_ = new_fullscreen; }
  void OnFocusUpdate(bool new_has_focus, WindowDestructionReceiver& destruction_receiver);

  void OnPaint(bool force_paint = false);

  void OnFileDrop(FileDropEvent& e, WindowDestructionReceiver& destruction_receiver);

  void OnKeyDown(KeyEvent& e, WindowDestructionReceiver& destruction_receiver);
  void OnKeyUp(KeyEvent& e, WindowDestructionReceiver& destruction_receiver);
  void OnKeyChar(KeyEvent& e, WindowDestructionReceiver& destruction_receiver);

  void OnMouseDown(MouseEvent& e, WindowDestructionReceiver& destruction_receiver);
  void OnMouseMove(MouseEvent& e, WindowDestructionReceiver& destruction_receiver);
  void OnMouseUp(MouseEvent& e, WindowDestructionReceiver& destruction_receiver);
  void OnMouseWheel(MouseEvent& e, WindowDestructionReceiver& destruction_receiver);

  void OnTouchEvent(TouchEvent& e, WindowDestructionReceiver& destruction_receiver);

 private:
  struct ListenerIterationContext {
    explicit ListenerIterationContext(ListenerIterationContext* outer_context,
                                      size_t first_index = 0)
        : outer_context(outer_context), next_index(first_index) {}

    ListenerIterationContext* outer_context;

    size_t next_index;
  };

  struct InputListenerIterationContext {
    explicit InputListenerIterationContext(
        InputListenerIterationContext* outer_context,
        std::multimap<size_t, WindowInputListener*>::const_reverse_iterator first_iterator,
        size_t first_z_order = SIZE_MAX)
        : outer_context(outer_context),
          next_iterator(first_iterator),
          current_z_order(first_z_order) {}

    InputListenerIterationContext* outer_context;

    std::multimap<size_t, WindowInputListener*>::const_reverse_iterator next_iterator;
    size_t current_z_order;
  };

  bool IsClosed() const { return phase_ < Phase::kOpening || phase_ > Phase::kOpenBeforeClosing; }

  bool CanApplyState() const {
    return phase_ >= Phase::kOpen && phase_ <= Phase::kOpenBeforeClosing;
  }

  bool CanSendEventsToListeners() const {
    return phase_ >= Phase::kOpen && phase_ <= Phase::kOpenBeforeClosing;
  }

  void SendEventToListeners(std::function<void(WindowListener*)> fn,
                            WindowDestructionReceiver& destruction_receiver);
  void PropagateEventThroughInputListeners(std::function<bool(WindowInputListener*)> fn,
                                           WindowDestructionReceiver& destruction_receiver);

  std::unique_ptr<Surface> CreateSurface(Surface::TypeFlags allowed_types) {
    if (phase_ != Phase::kOpen) {
      return nullptr;
    }
    return CreateSurfaceImpl(allowed_types);
  }

  WindowedAppContext& app_context_;

  Phase phase_ = Phase::kClosedOpenable;
  WindowDestructionReceiver* innermost_destruction_receiver_ = nullptr;

  std::vector<WindowListener*> listeners_;

  std::multimap<size_t, WindowInputListener*> input_listeners_;

  ListenerIterationContext* innermost_listener_iteration_context_ = nullptr;
  InputListenerIterationContext* innermost_input_listener_iteration_context_ = nullptr;

  uint32_t desired_logical_width_ = 0;
  uint32_t desired_logical_height_ = 0;

  uint32_t actual_physical_width_ = 0;
  uint32_t actual_physical_height_ = 0;

  bool fullscreen_ = false;
  int32_t monitor_ = 0;

  std::string title_;

  std::unique_ptr<MenuItem> main_menu_;

  uint32_t mouse_capture_request_count_ = 0;

  bool text_input_active_ = false;

  CursorVisibility cursor_visibility_ = CursorVisibility::kVisible;

  uint32_t cursor_auto_hide_delay_ms_ = kDefaultCursorAutoHideMilliseconds;

  bool has_focus_ = false;

  Presenter* presenter_ = nullptr;
  std::unique_ptr<Surface> presenter_surface_;

  bool is_painting_ = false;

  bool paint_requested_while_painting_ = false;
};

}
}
