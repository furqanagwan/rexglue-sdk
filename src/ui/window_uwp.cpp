/**
 * @file        ui/window_uwp.cpp
 * @brief       CoreWindow implementation of the Window abstraction
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <rex/ui/window_uwp.h>

#include <cmath>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.h>
#include <winrt/Windows.UI.ViewManagement.h>

#include <rex/cvar.h>
#include <rex/logging.h>
#include <rex/ui/flags.h>
#include <rex/ui/surface_win.h>

namespace rex::ui {

namespace {

using winrt::Windows::Graphics::Display::DisplayInformation;
using SystemVirtualKey = winrt::Windows::System::VirtualKey;
using winrt::Windows::UI::Core::CoreCursor;
using winrt::Windows::UI::Core::CoreCursorType;
using winrt::Windows::UI::Core::CoreVirtualKeyStates;
using winrt::Windows::UI::Core::CoreWindowActivationState;
using winrt::Windows::UI::Core::PointerEventArgs;
using winrt::Windows::UI::Input::PointerUpdateKind;
using winrt::Windows::UI::ViewManagement::ApplicationView;
using winrt::Windows::UI::ViewManagement::ApplicationViewBoundsMode;

constexpr int32_t kFirstGamepadVirtualKey = 0xC3;
constexpr int32_t kLastGamepadVirtualKey = 0xDA;

bool IsGamepadVirtualKey(SystemVirtualKey key) {
  int32_t code = static_cast<int32_t>(key);
  return code >= kFirstGamepadVirtualKey && code <= kLastGamepadVirtualKey;
}

MouseEvent::Button TranslatePointerUpdateKind(PointerUpdateKind kind) {
  switch (kind) {
    case PointerUpdateKind::LeftButtonPressed:
    case PointerUpdateKind::LeftButtonReleased:
      return MouseEvent::Button::kLeft;
    case PointerUpdateKind::RightButtonPressed:
    case PointerUpdateKind::RightButtonReleased:
      return MouseEvent::Button::kRight;
    case PointerUpdateKind::MiddleButtonPressed:
    case PointerUpdateKind::MiddleButtonReleased:
      return MouseEvent::Button::kMiddle;
    case PointerUpdateKind::XButton1Pressed:
    case PointerUpdateKind::XButton1Released:
      return MouseEvent::Button::kX1;
    case PointerUpdateKind::XButton2Pressed:
    case PointerUpdateKind::XButton2Released:
      return MouseEvent::Button::kX2;
    default:
      return MouseEvent::Button::kNone;
  }
}

bool IsPointerButtonPress(PointerUpdateKind kind) {
  switch (kind) {
    case PointerUpdateKind::LeftButtonPressed:
    case PointerUpdateKind::RightButtonPressed:
    case PointerUpdateKind::MiddleButtonPressed:
    case PointerUpdateKind::XButton1Pressed:
    case PointerUpdateKind::XButton2Pressed:
      return true;
    default:
      return false;
  }
}

}  // namespace

std::unique_ptr<Window> Window::Create(WindowedAppContext& app_context,
                                       const std::string_view title, uint32_t desired_logical_width,
                                       uint32_t desired_logical_height) {
  return std::make_unique<WindowUWP>(app_context, title, desired_logical_width,
                                     desired_logical_height);
}

WindowUWP::WindowUWP(WindowedAppContext& app_context, const std::string_view title,
                     uint32_t desired_logical_width, uint32_t desired_logical_height)
    : Window(app_context, title, desired_logical_width, desired_logical_height),
      alive_(std::make_shared<std::atomic<bool>>(true)) {}

WindowUWP::~WindowUWP() {
  EnterDestructor();
  alive_->store(false);
  RevokeEventHandlers();
}

bool WindowUWP::OpenImpl() {
  core_window_ = uwp_app_context().core_window();
  display_information_ = DisplayInformation::GetForCurrentView();

  ApplicationView view = ApplicationView::GetForCurrentView();
  view.SetDesiredBoundsMode(ApplicationViewBoundsMode::UseCoreWindow);
  view.Title(winrt::to_hstring(GetTitle()));
  if (IsFullscreen()) {
    view.TryEnterFullScreenMode();
  }

  RegisterEventHandlers();
  ApplyNewCursorVisibility(GetCursorVisibility());

  WindowDestructionReceiver destruction_receiver(this);
  auto bounds = core_window_.Bounds();
  double scale = GetRawPixelsPerViewPixel();
  OnActualSizeUpdate(uint32_t(std::lround(bounds.Width * scale)),
                     uint32_t(std::lround(bounds.Height * scale)), destruction_receiver);
  if (destruction_receiver.IsWindowDestroyed()) {
    return true;
  }
  OnFocusUpdate(true, destruction_receiver);
  return true;
}

void WindowUWP::RegisterEventHandlers() {
  if (handlers_registered_) {
    return;
  }
  handlers_registered_ = true;

  size_changed_token_ = core_window_.SizeChanged([this](auto&&, auto&&) { UpdateActualSize(); });

  visibility_changed_token_ = core_window_.VisibilityChanged([this](auto&&, auto&& args) {
    WindowDestructionReceiver destruction_receiver(this);
    if (args.Visible()) {
      OnRestored(destruction_receiver);
      if (!destruction_receiver.IsWindowDestroyedOrClosed()) {
        OnPaint(true);
      }
    } else {
      OnMinimized(destruction_receiver);
    }
  });

  activated_token_ = core_window_.Activated([this](auto&&, auto&& args) {
    WindowDestructionReceiver destruction_receiver(this);
    OnFocusUpdate(args.WindowActivationState() != CoreWindowActivationState::Deactivated,
                  destruction_receiver);
  });

  closed_token_ = core_window_.Closed([this](auto&&, auto&&) {
    WindowDestructionReceiver destruction_receiver(this);
    if (SendCloseRequestToListeners(destruction_receiver) &&
        !destruction_receiver.IsWindowDestroyed()) {
      PerformClose();
    }
  });

  key_down_token_ =
      core_window_.KeyDown([this](auto&&, auto&& args) { HandleKey(args, true); });
  key_up_token_ = core_window_.KeyUp([this](auto&&, auto&& args) { HandleKey(args, false); });
  character_received_token_ =
      core_window_.CharacterReceived([this](auto&&, auto&& args) { HandleCharacter(args); });

  pointer_moved_token_ =
      core_window_.PointerMoved([this](auto&&, auto&& args) { HandlePointerMoved(args); });
  pointer_pressed_token_ =
      core_window_.PointerPressed([this](auto&&, auto&& args) { HandlePointerButton(args); });
  pointer_released_token_ =
      core_window_.PointerReleased([this](auto&&, auto&& args) { HandlePointerButton(args); });
  pointer_wheel_token_ =
      core_window_.PointerWheelChanged([this](auto&&, auto&& args) { HandlePointerWheel(args); });

  dpi_changed_token_ = display_information_.DpiChanged([this](auto&&, auto&&) {
    WindowDestructionReceiver destruction_receiver(this);
    UISetupEvent e(this);
    OnDpiChanged(e, destruction_receiver);
    if (!destruction_receiver.IsWindowDestroyedOrClosed()) {
      UpdateActualSize();
    }
  });

  back_requested_token_ =
      winrt::Windows::UI::Core::SystemNavigationManager::GetForCurrentView().BackRequested(
          [](auto&&, auto&& args) { args.Handled(true); });
}

void WindowUWP::RevokeEventHandlers() {
  if (!handlers_registered_) {
    return;
  }
  handlers_registered_ = false;
  core_window_.SizeChanged(size_changed_token_);
  core_window_.VisibilityChanged(visibility_changed_token_);
  core_window_.Activated(activated_token_);
  core_window_.Closed(closed_token_);
  core_window_.KeyDown(key_down_token_);
  core_window_.KeyUp(key_up_token_);
  core_window_.CharacterReceived(character_received_token_);
  core_window_.PointerMoved(pointer_moved_token_);
  core_window_.PointerPressed(pointer_pressed_token_);
  core_window_.PointerReleased(pointer_released_token_);
  core_window_.PointerWheelChanged(pointer_wheel_token_);
  display_information_.DpiChanged(dpi_changed_token_);
  winrt::Windows::UI::Core::SystemNavigationManager::GetForCurrentView().BackRequested(
      back_requested_token_);
}

void WindowUWP::RequestCloseImpl() {
  PerformClose();
}

void WindowUWP::PerformClose() {
  WindowDestructionReceiver destruction_receiver(this);
  OnBeforeClose(destruction_receiver);
  if (destruction_receiver.IsWindowDestroyed()) {
    return;
  }
  RevokeEventHandlers();
  OnAfterClose();
}

double WindowUWP::GetRawPixelsPerViewPixel() const {
  if (!display_information_) {
    return 1.0;
  }
  double scale = display_information_.RawPixelsPerViewPixel();
  return scale > 0.0 ? scale : 1.0;
}

void WindowUWP::UpdateActualSize() {
  if (!core_window_) {
    return;
  }
  auto bounds = core_window_.Bounds();
  double scale = GetRawPixelsPerViewPixel();
  WindowDestructionReceiver destruction_receiver(this);
  OnActualSizeUpdate(uint32_t(std::lround(bounds.Width * scale)),
                     uint32_t(std::lround(bounds.Height * scale)), destruction_receiver);
}

uint32_t WindowUWP::GetLatestDpiImpl() const {
  if (!display_information_) {
    return GetMediumDpi();
  }
  return uint32_t(std::lround(display_information_.LogicalDpi()));
}

void WindowUWP::ApplyNewFullscreen() {
  ApplicationView view = ApplicationView::GetForCurrentView();
  if (IsFullscreen()) {
    view.TryEnterFullScreenMode();
  } else {
    view.ExitFullScreenMode();
  }
}

void WindowUWP::ApplyNewTitle() {
  ApplicationView::GetForCurrentView().Title(winrt::to_hstring(GetTitle()));
}

void WindowUWP::ApplyNewCursorVisibility(CursorVisibility old_cursor_visibility) {
  (void)old_cursor_visibility;
  if (!core_window_) {
    return;
  }
  if (GetCursorVisibility() == CursorVisibility::kVisible) {
    core_window_.PointerCursor(CoreCursor(CoreCursorType::Arrow, 0));
  } else {
    core_window_.PointerCursor(nullptr);
  }
}

std::unique_ptr<Surface> WindowUWP::CreateSurfaceImpl(Surface::TypeFlags allowed_types) {
  if (!core_window_ || !(allowed_types & Surface::kTypeFlag_CoreWindow)) {
    return nullptr;
  }
  return std::make_unique<CoreWindowSurface>(static_cast<::IUnknown*>(winrt::get_abi(core_window_)));
}

void WindowUWP::RequestPaintImpl() {
  if (paint_pending_.exchange(true)) {
    return;
  }
  auto alive = alive_;
  uwp_app_context().RunOnDispatcher([this, alive]() {
    if (!alive->load()) {
      return;
    }
    paint_pending_.store(false);
    OnPaint();
  });
}

bool WindowUWP::AreModifiersDown(SystemVirtualKey key) const {
  return (core_window_.GetKeyState(key) & CoreVirtualKeyStates::Down) == CoreVirtualKeyStates::Down;
}

void WindowUWP::HandleKey(const winrt::Windows::UI::Core::KeyEventArgs& args, bool is_down) {
  SystemVirtualKey key = args.VirtualKey();
  if (IsGamepadVirtualKey(key)) {
    return;
  }
  args.Handled(true);
  auto status = args.KeyStatus();
  KeyEvent e(this, VirtualKey(static_cast<uint16_t>(key)),
             int(status.RepeatCount ? status.RepeatCount : 1), status.WasKeyDown,
             AreModifiersDown(SystemVirtualKey::Shift), AreModifiersDown(SystemVirtualKey::Control),
             AreModifiersDown(SystemVirtualKey::Menu),
             AreModifiersDown(SystemVirtualKey::LeftWindows) || AreModifiersDown(SystemVirtualKey::RightWindows));
  WindowDestructionReceiver destruction_receiver(this);
  if (is_down) {
    OnKeyDown(e, destruction_receiver);
  } else {
    OnKeyUp(e, destruction_receiver);
  }
}

void WindowUWP::HandleCharacter(
    const winrt::Windows::UI::Core::CharacterReceivedEventArgs& args) {
  args.Handled(true);
  KeyEvent e(this, VirtualKey(args.KeyCode()), 1, false, false, false, false, false);
  WindowDestructionReceiver destruction_receiver(this);
  OnKeyChar(e, destruction_receiver);
}

bool WindowUWP::GetPointerPosition(const PointerEventArgs& args, int32_t& x_out,
                                   int32_t& y_out) const {
  auto position = args.CurrentPoint().Position();
  double scale = GetRawPixelsPerViewPixel();
  x_out = int32_t(std::lround(position.X * scale));
  y_out = int32_t(std::lround(position.Y * scale));
  return true;
}

void WindowUWP::HandlePointerMoved(const PointerEventArgs& args) {
  int32_t x = 0;
  int32_t y = 0;
  GetPointerPosition(args, x, y);
  MouseEvent e(this, MouseEvent::Button::kNone, x, y);
  WindowDestructionReceiver destruction_receiver(this);
  OnMouseMove(e, destruction_receiver);
}

void WindowUWP::HandlePointerButton(const PointerEventArgs& args) {
  int32_t x = 0;
  int32_t y = 0;
  GetPointerPosition(args, x, y);
  PointerUpdateKind kind = args.CurrentPoint().Properties().PointerUpdateKind();
  MouseEvent e(this, TranslatePointerUpdateKind(kind), x, y);
  WindowDestructionReceiver destruction_receiver(this);
  if (IsPointerButtonPress(kind)) {
    OnMouseDown(e, destruction_receiver);
  } else {
    OnMouseUp(e, destruction_receiver);
  }
}

void WindowUWP::HandlePointerWheel(const PointerEventArgs& args) {
  int32_t x = 0;
  int32_t y = 0;
  GetPointerPosition(args, x, y);
  auto properties = args.CurrentPoint().Properties();
  int32_t delta = properties.MouseWheelDelta();
  MouseEvent e(this, MouseEvent::Button::kNone, x, y,
               properties.IsHorizontalMouseWheel() ? delta : 0,
               properties.IsHorizontalMouseWheel() ? 0 : delta);
  WindowDestructionReceiver destruction_receiver(this);
  OnMouseWheel(e, destruction_receiver);
}

}  // namespace rex::ui
