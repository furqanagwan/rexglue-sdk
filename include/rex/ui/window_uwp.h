/**
 * @file        ui/window_uwp.h
 * @brief       CoreWindow implementation of the Window abstraction
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <atomic>
#include <memory>
#include <string_view>

#include <winrt/Windows.Graphics.Display.h>
#include <winrt/Windows.UI.Core.h>

#include <rex/ui/window.h>
#include <rex/ui/windowed_app_context_uwp.h>

namespace rex::ui {

class WindowUWP final : public Window {
 public:
  WindowUWP(WindowedAppContext& app_context, const std::string_view title,
            uint32_t desired_logical_width, uint32_t desired_logical_height);
  ~WindowUWP() override;

 protected:
  uint32_t GetLatestDpiImpl() const override;

  bool OpenImpl() override;
  void RequestCloseImpl() override;

  void ApplyNewFullscreen() override;
  void ApplyNewTitle() override;
  void ApplyNewCursorVisibility(CursorVisibility old_cursor_visibility) override;

  std::unique_ptr<Surface> CreateSurfaceImpl(Surface::TypeFlags allowed_types) override;
  void RequestPaintImpl() override;

 private:
  UWPWindowedAppContext& uwp_app_context() const {
    return static_cast<UWPWindowedAppContext&>(app_context());
  }

  void RegisterEventHandlers();
  void RevokeEventHandlers();
  void PerformClose();
  void UpdateActualSize();
  double GetRawPixelsPerViewPixel() const;
  bool GetPointerPosition(const winrt::Windows::UI::Core::PointerEventArgs& args, int32_t& x_out,
                          int32_t& y_out) const;
  bool AreModifiersDown(winrt::Windows::System::VirtualKey key) const;

  void HandleKey(const winrt::Windows::UI::Core::KeyEventArgs& args, bool is_down);
  void HandleCharacter(const winrt::Windows::UI::Core::CharacterReceivedEventArgs& args);
  void HandlePointerMoved(const winrt::Windows::UI::Core::PointerEventArgs& args);
  void HandlePointerButton(const winrt::Windows::UI::Core::PointerEventArgs& args);
  void HandlePointerWheel(const winrt::Windows::UI::Core::PointerEventArgs& args);

  winrt::Windows::UI::Core::CoreWindow core_window_{nullptr};
  winrt::Windows::Graphics::Display::DisplayInformation display_information_{nullptr};
  std::shared_ptr<std::atomic<bool>> alive_;
  std::atomic<bool> paint_pending_{false};

  winrt::event_token size_changed_token_{};
  winrt::event_token visibility_changed_token_{};
  winrt::event_token activated_token_{};
  winrt::event_token closed_token_{};
  winrt::event_token key_down_token_{};
  winrt::event_token key_up_token_{};
  winrt::event_token character_received_token_{};
  winrt::event_token pointer_moved_token_{};
  winrt::event_token pointer_pressed_token_{};
  winrt::event_token pointer_released_token_{};
  winrt::event_token pointer_wheel_token_{};
  winrt::event_token dpi_changed_token_{};
  winrt::event_token back_requested_token_{};
  bool handlers_registered_ = false;
};

}  // namespace rex::ui
