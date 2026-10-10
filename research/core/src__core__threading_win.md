# Threading win: core source notes

This record preserves technical and API notes moved from `src/core/threading_win.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L38)

```text
// "Minimum" and "maximum" name the coarsest and finest periods.
```

## Source note 2, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L59)

```text
// https://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx
```

## Source note 3, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L62)

```text
// Must be 0x1000.
```

## Source note 4, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L63)

```text
// Pointer to name (in user addr space).
```

## Source note 5, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L64)

```text
// Thread ID (-1=caller thread).
```

## Source note 6, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L65)

```text
// Reserved for future use, must be zero.
```

## Source note 7, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L90)

```text
// Convert UTF-8 name to UTF-16 using Windows API
```

## Source note 8, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L132)

```text
// The calling thread's high-resolution timer (Windows 10 1803+), created on
```

## Source note 9, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L133)

```text
// first use and closed when the thread exits. A synchronization timer:
```

## Source note 10, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L134)

```text
// setting it clears any earlier expiry.
```

## Source note 11, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L151)

```text
// Relative, 100 ns units.
```

## Source note 12, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L284)

```text
// The timer goes last: when an object and the timer are both signaled, the
```

## Source note 13, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L285)

```text
// lowest index wins, so the object is reported.
```

## Source note 14, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L317)

```text
// NtQueryEvent (EventBasicInformation) reads the state; a zero-timeout
```

## Source note 15, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L318)

```text
// wait would consume an auto-reset event's signal.
```

## Source note 16, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L328)

```text
// ntdll always exports it; the handle is our own event.
```

## Source note 17, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L443)

```text
// Reset the callback immediately so that any completions don't call it.
```

## Source note 18, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/threading_win.cpp#L451)

```text
// As the callback may reset the timer, store local.
```
