# Window win: ui source notes

This record preserves technical and API notes moved from `src/ui/window_win.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L76)

```text
// Set hwnd_ to null to ignore events from now on since this Win32Window is
```

## Source note 2, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L77)

```text
// entering an indeterminate state.
```

## Source note 3, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L111)

```text
// Matches the black background color of the presenter's painting.
```

## Source note 4, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L122)

```text
// Setup the initial size for the non-fullscreen window. With per-monitor DPI,
```

## Source note 5, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L123)

```text
// this is also done to be able to obtain the initial window rectangle (with
```

## Source note 6, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L124)

```text
// CW_USEDEFAULT) to get the monitor for the window position, and then to
```

## Source note 7, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L125)

```text
// adjust the normal window size to the new DPI.
```

## Source note 8, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L126)

```text
// Save the initial desired size since it may be modified by the handler of
```

## Source note 9, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L127)

```text
// the WM_SIZE sent during window creation - it's needed for the initial
```

## Source note 10, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L128)

```text
// per-monitor DPI scaling.
```

## Source note 11, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L135)

```text
// Even with per-monitor DPI, take the closest approximation (system DPI) to
```

## Source note 12, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L136)

```text
// potentially more accurately determine the initial monitor.
```

## Source note 13, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L148)

```text
// Create the window. Though WM_NCCREATE will assign to `hwnd_` too, still do
```

## Source note 14, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L149)

```text
// the assignment here to handle the case of a failure after WM_NCCREATE, for
```

## Source note 15, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L150)

```text
// instance.
```

## Source note 16, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L160)

```text
// For per-monitor DPI, obtain the DPI of the monitor the window was created
```

## Source note 17, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L161)

```text
// on, and adjust the initial normal size for it. If as a result of this
```

## Source note 18, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L162)

```text
// resizing, the window is moved to a different monitor, the WM_DPICHANGED
```

## Source note 19, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L163)

```text
// handler will do the needed correction.
```

## Source note 20, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L178)

```text
// WINDOWPLACEMENT contains workspace coordinates, which exclude toolbars
```

## Source note 21, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L179)

```text
// such as the taskbar - they can't be mixed with virtual screen
```

## Source note 22, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L180)

```text
// coordinates such as those from GetWindowRect.
```

## Source note 23, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L200)

```text
// Center on the requested display before fullscreen so fullscreen resolves
```

## Source note 24, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L201)

```text
// against it.
```

## Source note 25, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L204)

```text
// Disable rounded corners starting with Windows 11 (or silently receive and
```

## Source note 26, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L205)

```text
// ignore E_INVALIDARG on Windows versions before 10.0.22000.0), primarily to
```

## Source note 27, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L206)

```text
// preserve all pixels of the guest output.
```

## Source note 28, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L210)

```text
// Disable pen and touch gestures (press and hold, flicks, feedback).
```

## Source note 29, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L218)

```text
// Enable file dragging from external sources
```

## Source note 30, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L221)

```text
// Apply the initial state from the Window that the window shouldn't be
```

## Source note 31, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L222)

```text
// visibly transitioned to.
```

## Source note 32, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L232)

```text
// Go fullscreen after setting up everything related to the placement of the
```

## Source note 33, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L233)

```text
// non-fullscreen window.
```

## Source note 34, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L241)

```text
// Finally show the window.
```

## Source note 35, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L244)

```text
// Report the initial actual state after opening, messages for which might
```

## Source note 36, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L245)

```text
// have missed if they were processed during CreateWindowExW when the HWND was
```

## Source note 37, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L246)

```text
// not yet attached to the Win32Window.
```

## Source note 38, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L250)

```text
// Report the desired logical size of the client area in the non-maximized
```

## Source note 39, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L251)

```text
// state after the initial layout setup in Windows.
```

## Source note 40, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L255)

```text
// Subtract the non-client area from the non-maximized window size, and
```

## Source note 41, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L256)

```text
// clamp to 0 in case AdjustWindowRect is inexact.
```

## Source note 42, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L270)

```text
// Report the actual physical size in the current state.
```

## Source note 43, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L271)

```text
// GetClientRect returns a rectangle with 0 origin.
```

## Source note 44, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L287)

```text
// Apply the initial state from the Window that involves interaction with the
```

## Source note 45, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L288)

```text
// user.
```

## Source note 46, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L304)

```text
// OnFocusUpdate needs to be done before this.
```

## Source note 47, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L315)

```text
// 1 is the primary display, then the others in enumeration order.
```

## Source note 48, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L354)

```text
// A monitor with another DPI sends WM_DPICHANGED, which resizes as usual.
```

## Source note 49, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L369)

```text
// Leaving fullscreen later returns to the new display: move the saved
```

## Source note 50, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L370)

```text
// window there, keeping its size.
```

## Source note 51, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L393)

```text
// Applied when fullscreen is left: the saved window takes the new size,
```

## Source note 52, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L394)

```text
// at the DPI it was saved at.
```

## Source note 53, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L408)

```text
// As the SDL window: a maximized or minimized window keeps its size.
```

## Source note 54, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L428)

```text
// The registry mode is the desktop's, whatever mode is current.
```

## Source note 55, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L485)

```text
// The desktop mode already: borderless is the same picture.
```

## Source note 56, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L495)

```text
// CDS_FULLSCREEN: temporary, so Windows restores the desktop mode if the
```

## Source note 57, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L496)

```text
// process ends without doing it.
```

## Source note 58, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L524)

```text
// After the switch: the monitor rectangle follows the mode.
```

## Source note 59, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L531)

```text
// Resize the window to fullscreen _after_ removing the decorations, so the
```

## Source note 60, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L532)

```text
// new size never needs composition and independent low-latency presentation
```

## Source note 61, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L533)

```text
// is possible immediately (a composed window may otherwise stay composed).
```

## Source note 62, line 545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L545)

```text
// Programmatic close skips the listeners' veto, like the SDL window. The
```

## Source note 63, line 546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L546)

```text
// window might be deleted by the close handlers, don't touch *this after.
```

## Source note 64, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L567)

```text
// Set hwnd_ to null to ignore events from now on since this Win32Window is
```

## Source note 65, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L568)

```text
// entering an indeterminate state - this should be done at some point in
```

## Source note 66, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L569)

```text
// closing anyway.
```

## Source note 67, line 579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L579)

```text
// hwnd_ may be null in this function, but the latest DPI is stored in a
```

## Source note 68, line 580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L580)

```text
// variable anyway.
```

## Source note 69, line 585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L585)

```text
// Various functions here may send messages that may result in the
```

## Source note 70, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L586)

```text
// listeners being invoked, and potentially cause the destruction of the
```

## Source note 71, line 587

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L587)

```text
// window or fullscreen being toggled from inside this function.
```

## Source note 72, line 598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L598)

```text
// Changing the style may change the size too, don't handle the resize
```

## Source note 73, line 599

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L599)

```text
// multiple times (also potentially with the listeners changing the desired
```

## Source note 74, line 600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L600)

```text
// fullscreen if called from the handling of some message like WM_SIZE).
```

## Source note 75, line 612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L612)

```text
// Reinstate the non-client area.
```

## Source note 76, line 618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L618)

```text
// For some reason, WM_DPICHANGED is not sent when the window is borderless
```

## Source note 77, line 619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L619)

```text
// fullscreen with per-monitor DPI awareness v1 (on Windows versions since
```

## Source note 78, line 620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L620)

```text
// Windows 8.1 before Windows 10 1703) - refresh the current DPI explicitly.
```

## Source note 79, line 623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L623)

```text
// Rescale the pre-fullscreen non-maximized window size to the new DPI,
```

## Source note 80, line 624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L624)

```text
// keeping the physical top-left origin like Windows does when the scale
```

## Source note 81, line 625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L625)

```text
// is changed in the settings.
```

## Source note 82, line 644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L644)

```text
// https://devblogs.microsoft.com/oldnewthing/20131017-00/?p=2903
```

## Source note 83, line 666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L666)

```text
// The icon is already the default one.
```

## Source note 84, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L670)

```text
// Don't need to get the actual icon from the class if there's nothing to
```

## Source note 85, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L671)

```text
// set it for yet.
```

## Source note 86, line 678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L678)

```text
// Not caring if it's null in the class, accepting anything the class
```

## Source note 87, line 679

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L679)

```text
// specifies.
```

## Source note 88, line 694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L694)

```text
// The old icon is not in use anymore, safe to destroy it now.
```

## Source note 89, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L740)

```text
// Like SDL_StartTextInput / SDL_StopTextInput: the IME is attached only
```

## Source note 90, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L741)

```text
// while text input is active, so button-only gameplay gets no candidate
```

## Source note 91, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L742)

```text
// windows. WM_CHAR is gated on the same state in HandleKeyboard.
```

## Source note 92, line 796

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L796)

```text
// Something else may have moved the pointer, so confirm.
```

## Source note 93, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L830)

```text
// Before per-monitor DPI v2, there was no rescaling of the non-client
```

## Source note 94, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L831)

```text
// area at runtime at all, so throughout the execution of the process it will
```

## Source note 95, line 832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L832)

```text
// behave the same regardless of the DPI.
```

## Source note 96, line 855

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L855)

```text
// According to MSDN, x and y are identical.
```

## Source note 97, line 878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L878)

```text
// According to MSDN, x and y are identical.
```

## Source note 98, line 892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L892)

```text
// Already borderless: only the display mode may need to follow the cvars.
```

## Source note 99, line 900

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L900)

```text
// https://blogs.msdn.com/b/oldnewthing/archive/2010/04/12/9994016.aspx
```

## Source note 100, line 912

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L912)

```text
// Preserve values for DPI rescaling of the window in the non-maximized state
```

## Source note 101, line 913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L913)

```text
// if DPI is changed mid-fullscreen, clamped to 0 in case AdjustWindowRect is
```

## Source note 102, line 914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L914)

```text
// inexact.
```

## Source note 103, line 930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L930)

```text
// Remove the non-client area.
```

## Source note 104, line 950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L950)

```text
// Batched size update ended when the window has already been closed, for
```

## Source note 105, line 951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L951)

```text
// instance.
```

## Source note 106, line 960

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L960)

```text
// For the desired size in the normal, not maximized and not fullscreen state.
```

## Source note 107, line 965

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L965)

```text
// rcNormalPosition is the entire window's rectangle - convert to client,
```

## Source note 108, line 966

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L966)

```text
// clamped to 0 in case AdjustWindowRect is inexact.
```

## Source note 109, line 967

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L967)

```text
// https://devblogs.microsoft.com/oldnewthing/20131017-00/?p=2903
```

## Source note 110, line 983

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L983)

```text
// For the actual state.
```

## Source note 111, line 984

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L984)

```text
// GetClientRect returns a rectangle with 0 origin.
```

## Source note 112, line 997

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L997)

```text
// It's okay if batched_size_update_contained_* are not false when beginning
```

## Source note 113, line 998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L998)

```text
// a batched update, in case the new batched update was started by a window
```

## Source note 114, line 999

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L999)

```text
// listener called from within EndBatchedSizeUpdate.
```

## Source note 115, line 1008

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1008)

```text
// Resetting batched_size_update_contained_* in closing, not opening, because
```

## Source note 116, line 1009

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1009)

```text
// a listener may start a new batch, and finish it, and there won't be need to
```

## Source note 117, line 1010

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1010)

```text
// handle the deferred messages twice.
```

## Source note 118, line 1026

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1026)

```text
// Mouse messages usually contain the position in the client area in lParam,
```

## Source note 119, line 1027

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1027)

```text
// but WM_MOUSEWHEEL is an exception, it passes the screen position.
```

## Source note 120, line 1042

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1042)

```text
// WM_MOUSEMOVE and WM_SETCURSOR also come from window management
```

## Source note 121, line 1043

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1043)

```text
// without the user moving the mouse; only actual movement reveals the
```

## Source note 122, line 1044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1044)

```text
// cursor. WM_SETCURSOR follows, so no SetCursor here.
```

## Source note 123, line 1078

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1078)

```text
// Still handle the movement.
```

## Source note 124, line 1121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1121)

```text
// Returning immediately anyway - no need to check
```

## Source note 125, line 1122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1122)

```text
// destruction_receiver.IsWindowDestroyed().
```

## Source note 126, line 1135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1135)

```text
// Absolute devices (tablets, remote desktop) have no relative motion.
```

## Source note 127, line 1150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1150)

```text
// Same as SDL: characters are only delivered while text input is active.
```

## Source note 128, line 1172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1172)

```text
// Returning immediately anyway - no need to check
```

## Source note 129, line 1173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1173)

```text
// destruction_receiver.IsWindowDestroyed().
```

## Source note 130, line 1192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1192)

```text
// Reset the timer by deleting the old timer and creating the new one.
```

## Source note 131, line 1193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1193)

```text
// ChangeTimerQueueTimer doesn't work if the timer has already expired.
```

## Source note 132, line 1198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1198)

```text
// After making sure that the callback is not callable anymore
```

## Source note 133, line 1199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1199)

```text
// (DeleteTimerQueueTimer waits for the completion of the callback if it has
```

## Source note 134, line 1200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1200)

```text
// been called already, or cancels it if it's hasn't), update the most recent
```

## Source note 135, line 1201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1201)

```text
// message revision.
```

## Source note 136, line 1210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1210)

```text
// Not a timer callback.
```

## Source note 137, line 1228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1228)

```text
// System keys (Alt combinations, F10) still reach DefWindowProc so Alt+F4
```

## Source note 138, line 1229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1229)

```text
// and the window menu keep working.
```

## Source note 139, line 1238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1238)

```text
// User-initiated: listeners may veto, as with the SDL window.
```

## Source note 140, line 1251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1251)

```text
// In case the Windows window was somehow forcibly destroyed without
```

## Source note 141, line 1252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1252)

```text
// WM_CLOSE.
```

## Source note 142, line 1260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1260)

```text
// Get required buffer size
```

## Source note 143, line 1264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1264)

```text
// Ensure space for the null terminator
```

## Source note 144, line 1266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1266)

```text
// Only getting first file dropped (other files ignored)
```

## Source note 145, line 1269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1269)

```text
// Will drop the null terminator
```

## Source note 146, line 1315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1315)

```text
// Avoid painting an outdated surface during a batched size update when
```

## Source note 147, line 1316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1316)

```text
// WM_SIZE handling is deferred.
```

## Source note 148, line 1322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1322)

```text
// Custom painting via OnPaint - don't pass to DefWindowProc.
```

## Source note 149, line 1328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1328)

```text
// Don't erase between paints because painting may be dropped if nothing
```

## Source note 150, line 1329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1329)

```text
// has changed since the last one.
```

## Source note 151, line 1340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1340)

```text
// Note that for some reason, WM_DPICHANGED is not sent when the window is
```

## Source note 152, line 1341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1341)

```text
// borderless fullscreen with per-monitor DPI awareness v1.
```

## Source note 153, line 1350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1350)

```text
// The window might have been closed by the handler, check hwnd_ too
```

## Source note 154, line 1351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1351)

```text
// since it's needed below.
```

## Source note 155, line 1359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1359)

```text
// SetWindowPos arguments according to WM_DPICHANGED MSDN documentation.
```

## Source note 156, line 1360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1360)

```text
// https://docs.microsoft.com/en-us/windows/win32/hidpi/wm-dpichanged
```

## Source note 157, line 1361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1361)

```text
// Windows restores a maximized window when changing the DPI, so no
```

## Source note 158, line 1362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1362)

```text
// special maximized handling is needed.
```

## Source note 159, line 1420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1420)

```text
// Always revealing the cursor in case of events like clicking, but
```

## Source note 160, line 1421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1421)

```text
// WM_MOUSEMOVE messages may be sent for reasons not always
```

## Source note 161, line 1422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1422)

```text
// involving actual mouse movement performed by the user. Revealing
```

## Source note 162, line 1423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1423)

```text
// the cursor in case of movement is done in HandleMouse instead.
```

## Source note 163, line 1440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1440)

```text
// For the non-client area, and for visible cursor, letting normal
```

## Source note 164, line 1441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1441)

```text
// processing happen, setting the cursor to an arrow or to something
```

## Source note 165, line 1442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1442)

```text
// specific to non-client parts of the window.
```

## Source note 166, line 1446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1446)

```text
// Recheck the cursor visibility - the callback might have been called
```

## Source note 167, line 1447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1447)

```text
// before or while the timer is deleted. Also ignore messages from
```

## Source note 168, line 1448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1448)

```text
// outdated mouse interactions.
```

## Source note 169, line 1451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1451)

```text
// The timer object is not needed anymore.
```

## Source note 170, line 1463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1463)

```text
// Disable press and hold, pen feedback, flicks, touch switch, smooth
```

## Source note 171, line 1464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1464)

```text
// scrolling and forced touch UI; enable multitouch data.
```

## Source note 172, line 1469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1469)

```text
// The window might have been destroyed by the handlers, don't interact with
```

## Source note 173, line 1470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1470)

```text
// *this in this function from now on.
```

## Source note 174, line 1472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1472)

```text
// Passing the original hWnd argument rather than hwnd_ as the window might
```

## Source note 175, line 1473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1473)

```text
// have been closed or destroyed by a handler, making hwnd_ null even though
```

## Source note 176, line 1474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1474)

```text
// DefWindowProc still needs to be called to propagate the closing-related
```

## Source note 177, line 1475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1475)

```text
// messages needed by Windows, or inaccessible (due to use-after-free) at all.
```

## Source note 178, line 1486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1486)

```text
// Don't miss any messages sent before CreateWindowExW returns (but don't
```

## Source note 179, line 1487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1487)

```text
// reattach a closed window if WM_NCCREATE was somehow sent while closing).
```

## Source note 180, line 1492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1492)

```text
// Enable non-client area DPI scaling for AdjustWindowRectExForDpi to work
```

## Source note 181, line 1493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1493)

```text
// correctly between Windows 10 1607 and 1703.
```

## Source note 182, line 1499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window_win.cpp#L1499)

```text
// Already fully handled, no need to call Win32Window::WndProc.
```
