/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    ReXGlue, 2026 - Ported from xenia-edge 213dcc267 (RG-GDK-021)
 */

#include <rex/ui/windowed_app_context_win.h>

#include <cstdlib>

namespace rex::ui {

bool Win32WindowedAppContext::pending_functions_window_class_registered_;

Win32WindowedAppContext::~Win32WindowedAppContext() {
  if (pending_functions_hwnd_) {
    DestroyWindow(pending_functions_hwnd_);
  }
  if (user32_module_) {
    FreeLibrary(user32_module_);
  }
  if (shcore_module_) {
    FreeLibrary(shcore_module_);
  }
}

bool Win32WindowedAppContext::Initialize() {
  user32_module_ = LoadLibraryW(L"user32.dll");

  if (user32_module_) {
    using SetProcessDpiAwarenessContextFn = BOOL(WINAPI*)(DPI_AWARENESS_CONTEXT);
    auto set_awareness = reinterpret_cast<SetProcessDpiAwarenessContextFn>(
        GetProcAddress(user32_module_, "SetProcessDpiAwarenessContext"));
    if (set_awareness) {
      set_awareness(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    }
  }

  shcore_module_ = LoadLibraryW(L"SHCore.dll");
  if (shcore_module_) {
    per_monitor_dpi_v1_api_available_ = true;
    per_monitor_dpi_v1_api_available_ &=
        (*reinterpret_cast<void**>(&per_monitor_dpi_v1_api_.get_dpi_for_monitor) =
             reinterpret_cast<void*>(GetProcAddress(shcore_module_, "GetDpiForMonitor"))) !=
        nullptr;
  }
  if (user32_module_) {
    per_monitor_dpi_v2_api_available_ = true;
    auto load = [&](void* target, const char* name) {
      void* proc = reinterpret_cast<void*>(GetProcAddress(user32_module_, name));
      *static_cast<void**>(target) = proc;
      per_monitor_dpi_v2_api_available_ &= proc != nullptr;
    };
    load(&per_monitor_dpi_v2_api_.adjust_window_rect_ex_for_dpi, "AdjustWindowRectExForDpi");
    load(&per_monitor_dpi_v2_api_.enable_non_client_dpi_scaling, "EnableNonClientDpiScaling");
    load(&per_monitor_dpi_v2_api_.get_dpi_for_system, "GetDpiForSystem");
    load(&per_monitor_dpi_v2_api_.get_dpi_for_window, "GetDpiForWindow");
  }

  static constexpr WCHAR kPendingFunctionsWindowClassName[] = L"ReXGluePendingFunctionsWindowClass";
  if (!pending_functions_window_class_registered_) {
    WNDCLASSEXW pending_functions_window_class = {};
    pending_functions_window_class.cbSize = sizeof(pending_functions_window_class);
    pending_functions_window_class.lpfnWndProc = PendingFunctionsWndProc;
    pending_functions_window_class.hInstance = hinstance_;
    pending_functions_window_class.lpszClassName = kPendingFunctionsWindowClassName;
    if (!RegisterClassExW(&pending_functions_window_class)) {
      return false;
    }
    pending_functions_window_class_registered_ = true;
  }
  pending_functions_hwnd_ =
      CreateWindowExW(0, kPendingFunctionsWindowClassName, L"ReXGlue Pending Functions",
                      WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                      HWND_MESSAGE, nullptr, hinstance_, this);
  if (!pending_functions_hwnd_) {
    return false;
  }

  return true;
}

void Win32WindowedAppContext::NotifyUILoopOfPendingFunctions() {
  while (!PostMessageW(pending_functions_hwnd_, kPendingFunctionsWindowClassMessageExecute, 0, 0)) {
    Sleep(1);
  }
}

void Win32WindowedAppContext::PlatformQuitFromUIThread() {
  PostQuitMessage(EXIT_SUCCESS);
}

int Win32WindowedAppContext::RunMainMessageLoop() {
  int result = EXIT_SUCCESS;
  MSG message;

  while (!HasQuitFromUIThread()) {
    BOOL message_result = GetMessageW(&message, nullptr, 0, 0);
    if (message_result == 0 || message_result == -1) {
      QuitFromUIThread();
      result = message_result ? EXIT_FAILURE : int(message.wParam);
      break;
    }
    TranslateMessage(&message);
    DispatchMessageW(&message);
  }
  return result;
}

LRESULT CALLBACK Win32WindowedAppContext::PendingFunctionsWndProc(HWND hwnd, UINT message,
                                                                  WPARAM wparam, LPARAM lparam) {
  if (message == WM_CLOSE) {
    return 0;
  }
  if (message == WM_NCCREATE) {
    SetWindowLongPtrW(
        hwnd, GWLP_USERDATA,
        reinterpret_cast<LONG_PTR>(reinterpret_cast<const CREATESTRUCTW*>(lparam)->lpCreateParams));
  } else {
    auto app_context =
        reinterpret_cast<Win32WindowedAppContext*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    if (app_context) {
      switch (message) {
        case WM_DESTROY:

          app_context->QuitFromUIThread();
          break;
        case kPendingFunctionsWindowClassMessageExecute:
          app_context->ExecutePendingFunctionsFromUIThread();
          return 0;
        default:
          break;
      }
    }
  }
  return DefWindowProcW(hwnd, message, wparam, lparam);
}

}
