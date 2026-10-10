# Window win: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/window_win.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L40)

```text
// Null if the window hasn't been opened yet, or has been closed.
```

## Source note 2, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L47)

```text
// The desktop mode of the window's display, even while fullscreen_exclusive
```

## Source note 3, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L48)

```text
// has switched it.
```

## Source note 4, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L84)

```text
// The display for a 1-based monitor index, primary first; null for 0 or an
```

## Source note 5, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L85)

```text
// index past the displays present (logged).
```

## Source note 6, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L87)

```text
// Centers the window on GetMonitor()'s display (0 = leave it).
```

## Source note 7, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L91)

```text
// Sizes the borderless window over `monitor`, first switching its display
```

## Source note 8, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L92)

```text
// mode when fullscreen_exclusive is on (and back to the desktop mode when
```

## Source note 9, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L93)

```text
// it is off).
```

## Source note 10, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L95)

```text
// Switches `monitor` to the mode for the resolution cvar (or its desktop
```

## Source note 11, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L96)

```text
// size). Returns false, staying borderless, when the display refuses.
```

## Source note 12, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L98)

```text
// Back to the desktop mode of the display switched, if any.
```

## Source note 13, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L102)

```text
// For updating multiple factors that may influence the window size at once,
```

## Source note 14, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L103)

```text
// without handling WM_SIZE multiple times (that may not only result in wasted
```

## Source note 15, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L104)

```text
// handling, but also in the state potentially changed to an inconsistent one
```

## Source note 16, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L105)

```text
// in the middle of a size update by the listeners).
```

## Source note 17, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L109)

```text
// The close choreography shared by WM_CLOSE (after the listeners' veto),
```

## Source note 18, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L110)

```text
// RequestCloseImpl (no veto) and a forced WM_DESTROY.
```

## Source note 19, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L119)

```text
// Confines the cursor to the client area while relative mouse mode is on
```

## Source note 20, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L120)

```text
// and the window has focus; releases it otherwise.
```

## Source note 21, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L128)

```text
// This can't handle messages sent during CreateWindow (hwnd_ still not
```

## Source note 22, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L129)

```text
// assigned to) or after nulling hwnd_ in closing / deleting.
```

## Source note 23, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L138)

```text
// hwnd_ may be accessed by the cursor hiding timer callback from a separate
```

## Source note 24, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L139)

```text
// thread, but the timer can be active only with a valid window anyway.
```

## Source note 25, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L149)

```text
// Whether the window currently is borderless over a monitor, as opposed to
```

## Source note 26, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L150)

```text
// IsFullscreen, the desired state.
```

## Source note 27, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L152)

```text
// The display whose mode fullscreen_exclusive changed, empty when none.
```

## Source note 28, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L157)

```text
// The client area part of pre_fullscreen_placement_.rcNormalPosition, saved
```

## Source note 29, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L158)

```text
// in case something affecting AdjustWindowRectEx for the non-fullscreen
```

## Source note 30, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L159)

```text
// state changes mid-fullscreen.
```

## Source note 31, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L163)

```text
// Must be the screen position, not the client position, so it's possible to
```

## Source note 32, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L164)

```text
// immediately hide the cursor, for instance, when switching to fullscreen
```

## Source note 33, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L165)

```text
// (and thus changing the client area top-left corner, resulting in
```

## Source note 34, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L166)

```text
// WM_MOUSEMOVE being sent, which would instantly reveal the cursor because of
```

## Source note 35, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L167)

```text
// that relative position change).
```

## Source note 36, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L169)

```text
// A timer queue timer rather than WM_TIMER, which is never received while
```

## Source note 37, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L170)

```text
// WM_PAINT is sent continuously.
```

## Source note 38, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L172)

```text
// Last hiding case numbers for skipping obsolete cursor hiding messages. The
```

## Source note 39, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L173)

```text
// queued index is read, and the signaled index is written, by the timer
```

## Source note 40, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L174)

```text
// callback outside the message thread, so delete the timer (which cancels or
```

## Source note 41, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L175)

```text
// awaits the callback) before touching them here. Compared for equality for
```

## Source note 42, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L176)

```text
// safe rollover.
```

## Source note 43, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L179)

```text
// Whether the cursor has been hidden after the expiration of the timer, and
```

## Source note 44, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_win.h#L180)

```text
// hasn't been revealed yet.
```
