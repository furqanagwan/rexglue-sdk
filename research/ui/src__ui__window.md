# Window: ui source notes

This record preserves technical and API notes moved from `src/ui/window.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L33)

```text
// kHotReload (default): Window::SetFullscreen can be applied live, so the
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L34)

```text
// change callback registered in ReXApp::SetupPresentation keeps the window
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L35)

```text
// in sync whenever this cvar is changed at runtime.
```

## Source note 4, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L47)

```text
// "sdl" is still accepted so an old config starts: SDL was removed
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L48)

```text
// (RG-GDK-033), and Window::Create warns and makes the Win32 window.
```

## Source note 6, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L82)

```text
// In case the implementation didn't need to call EnterDestructor. Though
```

## Source note 7, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L83)

```text
// that was likely a mistake, so placing an assertion.
```

## Source note 8, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L89)

```text
// Null the pointer to prevent an infinite loop between
```

## Source note 9, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L90)

```text
// SetWindowSurfaceFromUIThread and SetPresenter calling each other.
```

## Source note 10, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L96)

```text
// Right before destruction has finished, after which no interaction with
```

## Source note 11, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L97)

```text
// *this can be done, notify the destruction receivers that the window is
```

## Source note 12, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L98)

```text
// being destroyed and that *this is not accessible anymore.
```

## Source note 13, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L107)

```text
// Check if already added.
```

## Source note 14, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L120)

```text
// Actualize the next listener indices after the erasure from the vector.
```

## Source note 15, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L136)

```text
// Check if already added.
```

## Source note 16, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L145)

```text
// If removing the listener that is the next in a current listener loop,
```

## Source note 17, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L146)

```text
// skip it (in a multimap, only one element iterator is invalidated).
```

## Source note 18, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L157)

```text
// If adding to layers in between the currently being processed ones (from
```

## Source note 19, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L158)

```text
// highest to lowest) and the previously next, make sure the new listener is
```

## Source note 20, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L159)

```text
// executed too. Execution within one layer, however, happens in the reverse
```

## Source note 21, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L160)

```text
// order of addition, so if adding to the Z layer currently being processed,
```

## Source note 22, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L161)

```text
// the new listener must not be executed within the loop. But, if adding to
```

## Source note 23, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L162)

```text
// the next Z layer after the current one, it must be executed immediately.
```

## Source note 24, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L183)

```text
// If removing the listener that is the next in a current listener loop,
```

## Source note 25, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L184)

```text
// skip it (in a multimap, only one element iterator is invalidated).
```

## Source note 26, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L202)

```text
// For consistency of the behavior of OpenImpl and the initial On*Update
```

## Source note 27, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L203)

```text
// that should be called as a result of it, reset the actual state to its
```

## Source note 28, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L204)

```text
// defaults for a closed window.
```

## Source note 29, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L205)

```text
// Note that this is performed in Open, not after closing, because there's
```

## Source note 30, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L206)

```text
// only one entry point for opening a window, while closing may be done
```

## Source note 31, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L207)

```text
// different ways - by actually closing, by destroying, or by failing to call
```

## Source note 32, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L208)

```text
// OpenImpl - instead of performing this reset in every possible close case,
```

## Source note 33, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L209)

```text
// just returning these defaults from the actual state getters if
```

## Source note 34, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L210)

```text
// HasActualState is false.
```

## Source note 35, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L221)

```text
// The window was closed mid-opening.
```

## Source note 36, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L226)

```text
// Call the listeners (OnOpened with all the new state so the listeners are
```

## Source note 37, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L227)

```text
// aware that they can start interacting with the open Window, and after that,
```

## Source note 38, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L228)

```text
// in case certain listeners don't handle OnOpened, but rather, only need the
```

## Source note 39, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L229)

```text
// more granular callbacks, make sure those callbacks receive the new state
```

## Source note 40, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L230)

```text
// too) for the actual state of the new window (that may be different than the
```

## Source note 41, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L231)

```text
// desired, depending on how the platform has interpreted the desired state).
```

## Source note 42, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L259)

```text
// May now try to create a valid surface (though the window may be in a
```

## Source note 43, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L260)

```text
// minimized state without the possibility of creating a surface, but that
```

## Source note 44, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L261)

```text
// will be resolved by the implementation), after OnDpiChanged and OnResize so
```

## Source note 45, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L262)

```text
// nothing related to painting will be making wrong assumptions about the
```

## Source note 46, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L263)

```text
// size.
```

## Source note 47, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L363)

```text
// The primary reason for this comparison (of two unique pointers) is
```

## Source note 48, line 364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L364)

```text
// nullptr == nullptr.
```

## Source note 49, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L368)

```text
// Keep the old menu object existing while it's still being detached from
```

## Source note 50, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L369)

```text
// the platform window.
```

## Source note 51, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L397)

```text
// Not comparing to the actual enabled state, it's a part of the MenuItem, not
```

## Source note 52, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L398)

```text
// the Window.
```

## Source note 53, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L399)

```text
// In case enabling (or even disabling) causes menu-related events (like
```

## Source note 54, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L400)

```text
// pressing) that may execute callbacks potentially destroying the Window via
```

## Source note 55, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L401)

```text
// the outer architecture.
```

## Source note 56, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L407)

```text
// Modifying the state of the items, notify the implementation so it makes the
```

## Source note 57, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L408)

```text
// displaying of the main menu consistent.
```

## Source note 58, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L421)

```text
// Call even if capturing while the mouse is already assumed to be captured,
```

## Source note 59, line 422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L422)

```text
// in case something has released it in the OS.
```

## Source note 60, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L509)

```text
// Detach the presenter from the old surface before attaching to the new one.
```

## Source note 61, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L524)

```text
// Usually a session whose native surface extension the driver lacks.
```

## Source note 62, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L533)

```text
// Because events are not sent from closed windows, and to make sure the
```

## Source note 63, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L534)

```text
// window isn't closed while its surface is still attached to the presenter,
```

## Source note 64, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L535)

```text
// this must be called before doing what constitutes closing in the platform
```

## Source note 65, line 536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L536)

```text
// implementation, not after.
```

## Source note 66, line 548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L548)

```text
// If the window was focused, notify the listeners that focus is being lost
```

## Source note 67, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L549)

```text
// because the window is being closed (the implementation usually wouldn't
```

## Source note 68, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L550)

```text
// be sending any events to the listeners after OnClosing even if the OS
```

## Source note 69, line 551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L551)

```text
// actually sends the focus loss event as part of the closing process).
```

## Source note 70, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L565)

```text
// Disconnect from the surface without connecting to the new one (after the
```

## Source note 71, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L566)

```text
// listeners so they don't try to reconnect afterwards).
```

## Source note 72, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L604)

```text
// The listeners may reference the presenter, update the presenter first.
```

## Source note 73, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L637)

```text
// Snapshot: listeners may add/remove listeners or destroy the window from
```

## Source note 74, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L638)

```text
// within the callback, and a veto must stop iteration immediately.
```

## Source note 75, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L670)

```text
// Something inside the paint pumped messages (XAudio2 or COM setup can).
```

## Source note 76, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L671)

```text
// The Presenter only asks for a paint while none is pending, so dropping
```

## Source note 77, line 672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L672)

```text
// this one would stop painting for good; repeat it after this paint.
```

## Source note 78, line 797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L797)

```text
// iteration_context.next_index may be changed during the execution of the
```

## Source note 79, line 798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L798)

```text
// listener if the list of the listeners is modified by it - don't assume
```

## Source note 80, line 799

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L799)

```text
// that after the call iteration_context.next_index will be the same as
```

## Source note 81, line 800

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L800)

```text
// iteration_context.next_index + 1 before it.
```

## Source note 82, line 803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L803)

```text
// The window was destroyed by the listener, can't access anything in
```

## Source note 83, line 804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L804)

```text
// *this anymore, including innermost_listener_iteration_context_ which
```

## Source note 84, line 805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L805)

```text
// has to be left in an indeterminate state.
```

## Source note 85, line 809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L809)

```text
// The listener has put the window in a state in which the window can't
```

## Source note 86, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L810)

```text
// send events anymore.
```

## Source note 87, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L831)

```text
// The current iterator may be invalidated, and
```

## Source note 88, line 832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L832)

```text
// iteration_context.next_iterator may be changed, during the execution of
```

## Source note 89, line 833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L833)

```text
// the listener if the list of the listeners is modified by it - don't
```

## Source note 90, line 834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L834)

```text
// assume that after the call iteration_context.next_iterator will be the
```

## Source note 91, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L835)

```text
// same as std::next(iteration_context.next_iterator) before it.
```

## Source note 92, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L839)

```text
// The window was destroyed by the listener, can't access anything in
```

## Source note 93, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L840)

```text
// *this anymore, including innermost_listener_iteration_context_ which
```

## Source note 94, line 841

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L841)

```text
// has to be left in an indeterminate state.
```

## Source note 95, line 848

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L848)

```text
// The listener has put the window in a state in which the window can't
```

## Source note 96, line 849

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/window.cpp#L849)

```text
// send events anymore.
```
