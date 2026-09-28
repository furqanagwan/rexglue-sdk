# Native Win32 window (RG-GDK-021) and the SDL3 removal (RG-GDK-033)

The SDK has one window and message loop: the native Win32 window. SDL3 was the
default until 2026-09-28 and was removed by RG-GDK-033. `ui_backend = "sdl"` in
an old config starts the Win32 window with a warning.

The entry point (`src/ui/windowed_app_main.cpp`, installed for title projects)
parses cvars, creates the `Win32WindowedAppContext` and runs the app.
`Window::Create` (`src/ui/window_factory.cpp`) returns the `Win32Window`. Titles
need no code change; rebuilding against the new SDK is enough.

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

| Behavior | Removed SDL window | Win32 window |
| --- | --- | --- |
| DPI awareness | SDL sets it | The context calls `SetProcessDpiAwarenessContext(PER_MONITOR_AWARE_V2)`, since titles carry no manifest |
| User close | `OnCloseRequested` veto | Same: `WM_CLOSE` asks listeners first; `RequestClose()` skips the veto |
| Minimize / restore | `OnMinimized` / `OnRestored` | Same, from `WM_SIZE` transitions |
| Text input | Characters only while `SetTextInputActive(true)` | Same: `WM_CHAR` gated, and the IME context is detached while inactive |
| Relative mouse (MnK mouse look) | SDL relative mode | Raw input (`WM_INPUT`) deltas as `MouseEvent::dx/dy`, cursor clipped to the client area while focused |
| Warp to center | `SDL_WarpMouseInWindow` | `SetCursorPos`, verified with `GetCursorPos` |
| `monitor` cvar | Display index, 1 = primary | Same (primary first, then enumeration order), centered on that monitor's work area |
| Window size | `window_width`/`window_height`, then `resolution`, then `video_mode_*` (upstream ReXGlue `289f518`) | Same order; both windows size through `Window::Create` in `window_factory.cpp` |
| Live changes (`monitor`, `window_width`/`height`, `resolution`, `fullscreen`, `fullscreen_exclusive`) | Applied without a restart (upstream `923c1a5`) | Same. While fullscreen, a new monitor moves the fullscreen window and the saved window; a new size is kept for when fullscreen is left. A maximized or minimized window keeps its size |
| `fullscreen_exclusive` (default off) | `SDL_SetWindowFullscreenMode` with the closest mode (upstream `1406e1b`) | `ChangeDisplaySettingsExW(CDS_FULLSCREEN)` on the window's display, with the same mode choice (`src/ui/display_mode.h`): the `resolution` size or the desktop's, exact or else the smallest covering mode, at the desktop refresh rate or the fastest. The desktop mode comes back on leaving fullscreen, on close, and on switching away, which minimizes the window as SDL does; switching back applies the mode again. Windows also restores it if the process dies |
| Display size (`GetDisplayPixelSize`) | Desktop mode of the window's display | Same, from the registry mode, so it stays the desktop's while a mode is switched |
| Input while unfocused | Neutral (upstream `1406e1b`, in `ReXApp`) | Same, for every input backend |
| Native menus | none | none (Xenia's Win32 menus not ported, to keep parity) |
| `video_driver` cvar | SDL video driver | Removed with SDL |
| Horizontal wheel | yes | yes (`WM_MOUSEHWHEEL`) |
| Title and icon | Project name plus the SDK build stamp | The project name until launch. Once the executable is loaded, `ReXApp` shows the title's own name from its XDBF string table (in the `user_language` language when the title has it, else its default language) and its XDBF dashboard icon. Nothing else is added to the name: Quantum of Solace shows `Quantum of Solace`. A title without an XDBF resource keeps the project name. The build stamp is in the log's first line and the debug overlay |
| Unicode text | not applicable | The class and window are Unicode, so unhandled messages go to `DefWindowProcW`. The ANSI `DefWindowProc` cut the title to its first letter |

The D3D12 presenter is unchanged: both windows give it the same `Win32HwndSurface` (HWND plus HINSTANCE).

## SDL consumers (all removed)

| SDL consumer | Files | Replacement | Status |
| --- | --- | --- | --- |
| Window, message loop, entry point | `window_sdl.cpp`, `windowed_app_context_sdl.cpp`, `windowed_app_main_sdl.cpp` | `Win32Window`, `Win32WindowedAppContext`, `windowed_app_main.cpp` (RG-GDK-021) | Removed (RG-GDK-033) |
| Scancode to virtual key | `sdl_virtual_key.cpp` | Win32 messages carry virtual keys natively | Removed |
| Gamepads | `sdl_input_driver.cpp`, `hid_mappings_file` cvar | GameInput in GDK builds ([GameInput](gameinput.md), RG-GDK-020), XInput otherwise | Removed |
| Audio output | `sdl_audio_driver.cpp` | XAudio2 ([Audio output](audio-output.md), RG-GDK-019); `audio_mute` moved to `audio_backend.cpp` | Removed |
| Build and package | the `sdl3` submodule (static SDL3), `find_dependency(SDL3)` in the package config, `SDL3::SDL3` on `rexui`, `rexaudio`, `rexinput`, `rexruntime` | None needed | Removed |

Dialogs are ImGui overlays drawn by the presenter; nothing else used SDL.

## Tests

- `unit_tests [ui][win32]`:
  - the Win32 context creates a `Win32Window` with a live HWND and a DPI-scaled client size
  - resize, minimize and restore reach listeners
  - fullscreen covers the monitor and restores the frame and size
  - a new size applies at once when windowed, and after leaving fullscreen when set during it
  - refreshing fullscreen (a `resolution` or `fullscreen_exclusive` change) neither moves a windowed window nor loses the saved one
  - `monitor` moves the window live; an index past the displays leaves it
  - the display size is the monitor's desktop mode
- `unit_tests [ui][display_mode]`: exact size, refresh preference, smallest covering mode, largest fallback, colour depth, no modes.
  - user close can be vetoed; programmatic close cannot
  - keys reach input listeners; characters arrive only with text input active
  - functions queued from another thread run on the UI thread
- `gpu_tests [gpu][win32]`: D3D12 presents through the Win32 window on WARP and the hardware adapter. The first frame matches the client size; after a resize to 640×400 frames follow; frames resume after minimize and restore; and the window closes cleanly with the presenter still attached and a paint requested.

## Not established

- In-title checks of overlays, fullscreen toggling during gameplay and mouse look on the Win32 window.
- Multi-monitor moves across different DPIs (one monitor here), DPI change at runtime, and WM_DPICHANGED while fullscreen.
- `fullscreen_exclusive` switching is not in the automated tests, which would change the developer's display. The mode choice is unit-tested, and the switch was checked by hand in Quantum of Solace (see the port's PR).
- AMD and Intel presentation; hardware results are NVIDIA only, with WARP as a supplement.
- A GDK-packaged title using the Win32 window (RG-GDK-022).
