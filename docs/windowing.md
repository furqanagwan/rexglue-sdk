# Native Win32 window and SDL ownership (RG-GDK-021)

The SDK has two window and message-loop backends. SDL3 remains the default; the native Win32 window is opt-in until it has been compared with SDL on titles and the vendor hardware matrix:

```toml
[UI/Window]
ui_backend = "win32"   # default "sdl"
```

The entry point (`src/ui/windowed_app_main_sdl.cpp`, installed for title projects) reads `ui_backend` after parsing cvars and creates either `Win32WindowedAppContext` or `SDLWindowedAppContext`. `Window::Create` (`src/ui/window_factory.cpp`) then returns the matching window. Titles need no code change.

## Win32 window

Ported from the last native Win32 window in Xenia before Edge moved to Qt: `has207/xenia-edge` `213dcc2675806bf1e61291dd6ed0bb897c8d2fff` (`window_win.cc`, `windowed_app_context_win.cc`). Pending UI-thread functions run through a message-only window, so they also run inside modal loops.

Kept as in the source:
- per-monitor DPI v2 (with v1 and system-DPI fallbacks) and `WM_DPICHANGED` resizing
- batched size updates
- borderless fullscreen on the window's monitor, restoring the pre-fullscreen placement, rescaled if the DPI changed meanwhile
- cursor auto-hide on a timer-queue timer
- file drop
- no rounded corners on Windows 11
- disabled pen gestures

Adapted for this SDK:

| Behavior | SDL window | Win32 window |
| --- | --- | --- |
| DPI awareness | SDL sets it | The context calls `SetProcessDpiAwarenessContext(PER_MONITOR_AWARE_V2)`, since titles carry no manifest |
| User close | `OnCloseRequested` veto | Same: `WM_CLOSE` asks listeners first; `RequestClose()` skips the veto |
| Minimize / restore | `OnMinimized` / `OnRestored` | Same, from `WM_SIZE` transitions |
| Text input | Characters only while `SetTextInputActive(true)` | Same: `WM_CHAR` gated, and the IME context is detached while inactive |
| Relative mouse (MnK mouse look) | SDL relative mode | Raw input (`WM_INPUT`) deltas as `MouseEvent::dx/dy`, cursor clipped to the client area while focused |
| Warp to center | `SDL_WarpMouseInWindow` | `SetCursorPos`, verified with `GetCursorPos` |
| `monitor` cvar | Display index, 1 = primary | Same (primary first, then enumeration order), centered on that monitor's work area |
| Native menus | none | none (Xenia's Win32 menus not ported, to keep parity) |
| `video_driver` cvar | SDL video driver | ignored |
| Horizontal wheel | yes | yes (`WM_MOUSEHWHEEL`) |

The D3D12 presenter is unchanged: both windows give it the same `Win32HwndSurface` (HWND plus HINSTANCE).

## SDL consumers and owners

| SDL consumer | Files | Owner | Native replacement | Status |
| --- | --- | --- | --- | --- |
| Window, message loop, entry point | `window_sdl.cpp`, `windowed_app_context_sdl.cpp`, `windowed_app_main_sdl.cpp` | RG-GDK-021 | `Win32Window`, `Win32WindowedAppContext` | Opt-in (`ui_backend = "win32"`); SDL stays default |
| Scancode to virtual key | `sdl_virtual_key.cpp` | RG-GDK-021 | Win32 messages carry virtual keys natively | Used only by the SDL window |
| Gamepads | `src/input/sdl/sdl_input_driver.cpp` | RG-GDK-020 | GameInput driver ([GameInput](gameinput.md)) | Opt-in (`input_backend = "gameinput"`, GDK builds) |
| Audio output | `src/audio/sdl/sdl_audio_driver.cpp` | RG-GDK-019 | XAudio2 driver ([Audio output](audio-output.md)) | Opt-in (`audio_backend = "xaudio2"`); SDL stays default |
| Build and package | `thirdparty/CMakeLists.txt` (static SDL3), `find_dependency(SDL3)` in the package config, `SDL3::SDL3` on `rexui`, `rexinput`, `rexruntime` | RG-GDK-022 | Drop once the three rows above have validated replacements | Retained |

The SDL gamepad and audio drivers initialize their own SDL subsystems (events, gamepad, audio) and do not need SDL video. They keep working under the Win32 window: the gamepad driver pumps SDL events through `CallInUIThread`, which the Win32 context runs.

No other code uses SDL. Dialogs are ImGui overlays drawn by the presenter, and there are no SDL message boxes or file pickers.

## Tests

- `unit_tests [ui][win32]`:
  - the Win32 context creates a `Win32Window` with a live HWND and a DPI-scaled client size
  - resize, minimize and restore reach listeners
  - fullscreen covers the monitor and restores the frame and size
  - user close can be vetoed; programmatic close cannot
  - keys reach input listeners; characters arrive only with text input active
  - functions queued from another thread run on the UI thread
- `gpu_tests [gpu][win32]`: D3D12 presents through the Win32 window on WARP and the hardware adapter. The first frame matches the client size; after a resize to 640×400 frames follow; frames resume after minimize and restore; and the window closes cleanly with the presenter still attached and a paint requested.

## Not established

- Title-level parity with the SDL window (no title content): input feel, overlays, fullscreen toggling during gameplay, mouse look.
- Multi-monitor moves across different DPIs (one monitor here), DPI change at runtime, and WM_DPICHANGED while fullscreen.
- AMD and Intel presentation; hardware results are NVIDIA only, with WARP as a supplement.
- A GDK-packaged title using the Win32 window (RG-GDK-022).
