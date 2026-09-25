/**
 * @file        win32_window_test.cpp
 * @brief       Native Win32 window lifecycle through the Window API (RG-GDK-021)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <memory>
#include <thread>
#include <vector>

#include <rex/ui/ui_event.h>
#include <rex/ui/virtual_key.h>
#include <rex/ui/window.h>
#include <rex/ui/window_listener.h>
#include <rex/ui/window_win.h>
#include <rex/ui/windowed_app_context_win.h>

using namespace rex::ui;  // NOLINT

namespace {

// Records what the window reports to its listeners.
struct Recorder : WindowListener, WindowInputListener {
  bool allow_close = true;
  int close_requests = 0;
  int closing = 0;
  int resizes = 0;
  int minimized = 0;
  int restored = 0;
  std::vector<VirtualKey> keys_down;
  std::vector<uint32_t> chars;

  bool OnCloseRequested(UIEvent&) override {
    ++close_requests;
    return allow_close;
  }
  void OnClosing(UIEvent&) override { ++closing; }
  void OnResize(UISetupEvent&) override { ++resizes; }
  void OnMinimized(UIEvent&) override { ++minimized; }
  void OnRestored(UIEvent&) override { ++restored; }
  void OnKeyDown(KeyEvent& e) override { keys_down.push_back(e.virtual_key()); }
  void OnKeyChar(KeyEvent& e) override { chars.push_back(uint32_t(e.virtual_key())); }
};

// Dispatches everything queued for this thread, as the main loop would.
void Pump() {
  MSG message;
  while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
    TranslateMessage(&message);
    DispatchMessageW(&message);
  }
}

struct Harness {
  Harness() : context(GetModuleHandleW(nullptr), SW_SHOWNOACTIVATE) {
    REQUIRE(context.Initialize());
    window = Window::Create(context, "ReXGlue Win32 window test", 640, 360);
    REQUIRE(window);
    window->SetFullscreen(false);
    window->AddListener(&recorder);
    window->AddInputListener(&recorder, 0);
    REQUIRE(window->Open());
    Pump();
  }
  ~Harness() {
    if (window) {
      window->RemoveListener(&recorder);
      window.reset();
    }
    Pump();
  }
  HWND hwnd() const { return static_cast<HWND>(window->GetNativeWindowHandle()); }

  Win32WindowedAppContext context;
  std::unique_ptr<Window> window;
  Recorder recorder;
};

}  // namespace

TEST_CASE("A Win32 app context creates a native Win32 window", "[ui][win32]") {
  Harness h;
  CHECK(dynamic_cast<Win32Window*>(h.window.get()) != nullptr);
  REQUIRE(h.hwnd() != nullptr);
  CHECK(IsWindow(h.hwnd()));
  CHECK(h.window->GetDpi() >= 96);
  RECT client;
  REQUIRE(GetClientRect(h.hwnd(), &client));
  CHECK(h.window->GetActualPhysicalWidth() == uint32_t(client.right));
  CHECK(h.window->GetActualPhysicalHeight() == uint32_t(client.bottom));
  // The requested logical size, scaled to the window's DPI.
  CHECK(h.window->GetActualPhysicalWidth() == h.window->SizeToPhysical(640));
}

TEST_CASE("Win32 window resize, minimize and restore reach the listeners", "[ui][win32]") {
  Harness h;
  int resizes = h.recorder.resizes;
  RECT rect = {0, 0, 800, 500};
  AdjustWindowRectEx(&rect, DWORD(GetWindowLongW(h.hwnd(), GWL_STYLE)), FALSE,
                     DWORD(GetWindowLongW(h.hwnd(), GWL_EXSTYLE)));
  SetWindowPos(h.hwnd(), nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top,
               SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
  Pump();
  RECT client;
  REQUIRE(GetClientRect(h.hwnd(), &client));
  CHECK(h.recorder.resizes > resizes);
  CHECK(h.window->GetActualPhysicalWidth() == uint32_t(client.right));
  CHECK(h.window->GetActualPhysicalHeight() == uint32_t(client.bottom));

  ShowWindow(h.hwnd(), SW_MINIMIZE);
  Pump();
  CHECK(h.recorder.minimized == 1);
  ShowWindow(h.hwnd(), SW_RESTORE);
  Pump();
  CHECK(h.recorder.restored == 1);
  CHECK(h.window->GetActualPhysicalWidth() == uint32_t(client.right));
}

TEST_CASE("Win32 fullscreen covers the monitor and restores the window", "[ui][win32]") {
  Harness h;
  RECT before;
  REQUIRE(GetWindowRect(h.hwnd(), &before));
  h.window->SetFullscreen(true);
  Pump();
  MONITORINFO monitor = {};
  monitor.cbSize = sizeof(monitor);
  REQUIRE(GetMonitorInfoW(MonitorFromWindow(h.hwnd(), MONITOR_DEFAULTTONEAREST), &monitor));
  CHECK(h.window->GetActualPhysicalWidth() ==
        uint32_t(monitor.rcMonitor.right - monitor.rcMonitor.left));
  CHECK(h.window->GetActualPhysicalHeight() ==
        uint32_t(monitor.rcMonitor.bottom - monitor.rcMonitor.top));
  CHECK((GetWindowLongW(h.hwnd(), GWL_STYLE) & WS_CAPTION) == 0);

  h.window->SetFullscreen(false);
  Pump();
  RECT after;
  REQUIRE(GetWindowRect(h.hwnd(), &after));
  CHECK((GetWindowLongW(h.hwnd(), GWL_STYLE) & WS_CAPTION) == WS_CAPTION);
  CHECK(after.right - after.left == before.right - before.left);
  CHECK(after.bottom - after.top == before.bottom - before.top);
}

TEST_CASE("A listener can veto a user close of the Win32 window", "[ui][win32]") {
  Harness h;
  HWND hwnd = h.hwnd();
  h.recorder.allow_close = false;
  SendMessageW(hwnd, WM_CLOSE, 0, 0);
  CHECK(h.recorder.close_requests == 1);
  CHECK(h.recorder.closing == 0);
  CHECK(IsWindow(hwnd));
  CHECK(h.window->GetNativeWindowHandle() == hwnd);

  h.recorder.allow_close = true;
  SendMessageW(hwnd, WM_CLOSE, 0, 0);
  CHECK(h.recorder.closing == 1);
  CHECK_FALSE(IsWindow(hwnd));
  CHECK(h.window->GetNativeWindowHandle() == nullptr);
}

TEST_CASE("Programmatic close of the Win32 window skips the veto", "[ui][win32]") {
  Harness h;
  HWND hwnd = h.hwnd();
  h.recorder.allow_close = false;
  h.window->RequestClose();
  CHECK(h.recorder.close_requests == 0);
  CHECK(h.recorder.closing == 1);
  CHECK_FALSE(IsWindow(hwnd));
}

TEST_CASE("Win32 keys reach input listeners; characters only while text input is active",
          "[ui][win32]") {
  Harness h;
  SendMessageW(h.hwnd(), WM_KEYDOWN, 'A', 1);
  REQUIRE(h.recorder.keys_down.size() == 1);
  CHECK(h.recorder.keys_down[0] == VirtualKey::kA);

  SendMessageW(h.hwnd(), WM_CHAR, 'a', 1);
  CHECK(h.recorder.chars.empty());
  h.window->SetTextInputActive(true);
  SendMessageW(h.hwnd(), WM_CHAR, 'a', 1);
  REQUIRE(h.recorder.chars.size() == 1);
  CHECK(h.recorder.chars[0] == 'a');
}

TEST_CASE("Functions queued from another thread run on the Win32 UI thread", "[ui][win32]") {
  Harness h;
  std::atomic<bool> ran = false;
  std::atomic<bool> on_ui_thread = false;
  std::thread worker([&] {
    h.context.CallInUIThread([&] {
      on_ui_thread = h.context.IsInUIThread();
      ran = true;
    });
  });
  worker.join();
  for (int i = 0; i < 100 && !ran; ++i) {
    Pump();
    Sleep(1);
  }
  CHECK(ran);
  CHECK(on_ui_thread);
}
