# Win32 window test: ui source notes

This record preserves technical and API notes moved from `tests/unit/ui/win32_window_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L30)

```text
// Records what the window reports to its listeners.
```

## Source note 2, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L53)

```text
// Dispatches everything queued for this thread, as the main loop would.
```

## Source note 3, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L99)

```text
// The requested logical size, scaled to the window's DPI.
```

## Source note 4, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L105)

```text
// A title's XDBF name is UTF-8 and may leave ASCII ("Légendes").
```

## Source note 5, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L113)

```text
// XDBF title icons are PNG; a 4x4 red one.
```

## Source note 6, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L244)

```text
// While fullscreen the monitor keeps the window; the size applies on leaving.
```

## Source note 7, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L264)

```text
// Windowed: nothing to refresh, and the saved placement is not reapplied.
```

## Source note 8, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L272)

```text
// Fullscreen, refreshed (a resolution or fullscreen_exclusive change), then
```

## Source note 9, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L273)

```text
// left: the window comes back as it was, not at the fullscreen rectangle.
```

## Source note 10, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L288)

```text
// The primary display.
```

## Source note 11, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L292)

```text
// Past the displays present: logged, and the window stays.
```

## Source note 12, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L308)

```text
// The process is per-monitor DPI aware, so the monitor rectangle is in
```

## Source note 13, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L309)

```text
// physical pixels, as the desktop mode is.
```

## Source note 14, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ui/win32_window_test.cpp#L318)

```text
// Owner decision, 2026-09-28: native backends by default.
```
