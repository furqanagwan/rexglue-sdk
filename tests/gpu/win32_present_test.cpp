/**
 * @file        win32_present_test.cpp
 * @brief       D3D12 presentation through the native Win32 window (RG-GDK-021)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <chrono>
#include <memory>
#include <utility>
#include <vector>

#include <rex/cvar.h>
#include <rex/logging.h>
#include <rex/ui/d3d12/d3d12_provider.h>
#include <rex/ui/presenter.h>
#include <rex/ui/ui_drawer.h>
#include <rex/ui/window.h>
#include <rex/ui/window_win.h>
#include <rex/ui/windowed_app_context_win.h>

REXCVAR_DECLARE(int32_t, d3d12_adapter);

namespace {

using namespace rex::ui;  // NOLINT
using rex::ui::d3d12::D3D12Provider;

// UI drawers run only for frames that are presented, so this records every
// presented frame's render target size.
struct FrameRecorder : UIDrawer {
  std::vector<std::pair<uint32_t, uint32_t>> frames;
  void Draw(UIDrawContext& context) override {
    frames.emplace_back(context.render_target_width(), context.render_target_height());
  }
};

// Pumps the UI thread's messages until `done` or the timeout.
template <typename Done>
bool PumpUntil(Done done, std::chrono::milliseconds timeout = std::chrono::seconds(10)) {
  auto deadline = std::chrono::steady_clock::now() + timeout;
  while (!done()) {
    if (std::chrono::steady_clock::now() > deadline) {
      return false;
    }
    MSG message;
    while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&message);
      DispatchMessageW(&message);
    }
    MsgWaitForMultipleObjects(0, nullptr, FALSE, 1, QS_ALLINPUT);
  }
  return true;
}

}  // namespace

TEST_CASE("D3D12 presents through the Win32 window across resize and close", "[gpu][win32]") {
  static bool logging_initialized = [] {
    rex::InitLogging();
    return true;
  }();
  (void)logging_initialized;
  if (!D3D12Provider::IsD3D12APIAvailable()) {
    SKIP("Direct3D 12 is not available");
  }
  const int32_t adapter = GENERATE(-2, -1);  // WARP, then the hardware adapter
  REXCVAR_SET(d3d12_adapter, adapter);
  auto provider = D3D12Provider::Create();
  REXCVAR_SET(d3d12_adapter, -1);
  if (!provider) {
    SKIP("No Direct3D 12 adapter for d3d12_adapter " << adapter);
  }
  INFO("adapter " << (provider->IsAdapterSoftware() ? "WARP" : "hardware"));

  Win32WindowedAppContext context(GetModuleHandleW(nullptr), SW_SHOWNOACTIVATE);
  REQUIRE(context.Initialize());
  auto window = Window::Create(context, "ReXGlue Win32 present test", 480, 270);
  REQUIRE(dynamic_cast<Win32Window*>(window.get()));
  window->SetFullscreen(false);
  REQUIRE(window->Open());

  auto presenter = provider->CreatePresenter();
  REQUIRE(presenter);
  FrameRecorder recorder;
  presenter->AddUIDrawerFromUIThread(&recorder, 0);
  window->SetPresenter(presenter.get());

  // First frame at the window's size.
  REQUIRE(PumpUntil([&] { return !recorder.frames.empty(); }));
  CHECK(recorder.frames.back().first == window->GetActualPhysicalWidth());
  CHECK(recorder.frames.back().second == window->GetActualPhysicalHeight());

  // Resize: the swap chain follows the client area.
  HWND hwnd = static_cast<HWND>(window->GetNativeWindowHandle());
  RECT rect = {0, 0, 640, 400};
  AdjustWindowRectEx(&rect, DWORD(GetWindowLongW(hwnd, GWL_STYLE)), FALSE,
                     DWORD(GetWindowLongW(hwnd, GWL_EXSTYLE)));
  SetWindowPos(hwnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top,
               SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
  REQUIRE(PumpUntil([&] {
    presenter->RequestUIPaintFromUIThread();
    return recorder.frames.back().first == 640 && recorder.frames.back().second == 400;
  }));

  // Minimize and restore keep presenting afterwards.
  ShowWindow(hwnd, SW_MINIMIZE);
  PumpUntil([] { return false; }, std::chrono::milliseconds(100));
  ShowWindow(hwnd, SW_RESTORE);
  size_t frames_before = recorder.frames.size();
  REQUIRE(PumpUntil([&] {
    presenter->RequestUIPaintFromUIThread();
    return recorder.frames.size() > frames_before;
  }));

  // Close with the presenter still attached, while frames are being requested:
  // the window detaches the surface, and the presenter outlives it cleanly.
  presenter->RequestUIPaintFromUIThread();
  window->RequestClose();
  CHECK(window->GetNativeWindowHandle() == nullptr);
  PumpUntil([] { return false; }, std::chrono::milliseconds(100));
  presenter->RemoveUIDrawerFromUIThread(&recorder);
  window->SetPresenter(nullptr);
  presenter.reset();
  window.reset();
  provider.reset();
}
