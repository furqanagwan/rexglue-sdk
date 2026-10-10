# Mnk input driver: input source notes

This record preserves technical and API notes moved from `src/input/mnk/mnk_input_driver.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L71)

```text
// A single device, so its handle is a constant.
```

## Source note 2, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L74)

```text
// Bounds the queue for titles that never call XamInputGetKeystroke.
```

## Source note 3, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L77)

```text
// Bind values are a comma-separated list of alternatives, each optionally
```

## Source note 4, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L78)

```text
// carrying modifier prefixes: "Q,I" or "Shift+W". Modifier matching is exact,
```

## Source note 5, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L79)

```text
// so "Up" stays silent while Shift is held and "Shift+Up" stays silent without
```

## Source note 6, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L80)

```text
// it. That is what lets the D-pad share the arrow keys. A consequence is
```

## Source note 7, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L81)

```text
// that binding a bare modifier name ("Shift") can never fire, since holding it
```

## Source note 8, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L82)

```text
// makes the live mask non-zero while the bind wants zero.
```

## Source note 9, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L98)

```text
// Strips leading modifier prefixes off 'token', advancing it to the bare key
```

## Source note 10, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L99)

```text
// name and returning the mask they require.
```

## Source note 11, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L149)

```text
// ui::VirtualKey follows Windows VK_ numbering; the guest wants USB HID usage
```

## Source note 12, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L150)

```text
// page 0x07.
```

## Source note 13, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L154)

```text
// The runs below are contiguous in both numbering schemes.
```

## Source note 14, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L158)

```text
// 0 is irregular in both digit runs; handled in the switch.
```

## Source note 15, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L263)

```text
// Sticks and triggers are included: XInput reports those as directional pad
```

## Source note 16, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L264)

```text
// keys, which is what menu navigation reads.
```

## Source note 17, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L270)

```text
// Rebuilt per call because the cvars are live-editable.
```

## Source note 18, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L314)

```text
// Detach handled by OnClosing; if window outlives the driver, clean up here.
```

## Source note 19, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L343)

```text
// Detach first so nothing new is queued, then run out what already was.
```

## Source note 20, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L358)

```text
// Passthrough enables the device on its own.
```

## Source note 21, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L386)

```text
// Disabled means no device at all, so it never occupies a guest user slot.
```

## Source note 22, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L432)

```text
// Keys reach the guest through GetDeviceKeystroke only, leaving the guest
```

## Source note 23, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L433)

```text
// user free for a real controller.
```

## Source note 24, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L438)

```text
// Mouse look is opt in. Without this gate, keyboard input alone would hide
```

## Source note 25, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L439)

```text
// and lock the cursor, breaking the ImGui overlays.
```

## Source note 26, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L516)

```text
// Drained unconditionally: deltas keep accumulating in OnMouseMove while the
```

## Source note 27, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L517)

```text
// mouse is off, and toggling it on would otherwise dump the whole backlog
```

## Source note 28, line 518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L518)

```text
// into one frame as a camera snap.
```

## Source note 29, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L569)

```text
// InputSystem stamps the guest user this device is assigned to.
```

## Source note 30, line 590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L590)

```text
// Already down, so this is the OS auto-repeat.
```

## Source note 31, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L616)

```text
// The whole table is diffed rather than the key that moved: binds carry
```

## Source note 32, line 617

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L617)

```text
// modifiers, so Shift alone can flip several of them at once.
```

## Source note 33, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L642)

```text
// Deferred, not CallInUIThread: running inline would re-enter state_mutex_.
```

## Source note 34, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L670)

```text
// Reset deltas to avoid a spike on capture start
```

## Source note 35, line 697

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L697)

```text
// Only once the pointer has drifted well off the middle, to keep warps rare.
```

## Source note 36, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L744)

```text
// WM_CHAR convention: the codepoint arrives after its key-down, so it is
```

## Source note 37, line 745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L745)

```text
// attached to the keystroke already queued for that key.
```

## Source note 38, line 807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L807)

```text
// The pointer is locked, so the absolute position no longer moves.
```

## Source note 39, line 817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L817)

```text
// Without a pointer lock the cursor still has to be kept off the edges.
```

## Source note 40, line 825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L825)

```text
// Withdraw the request too, or an update queued before the focus loss grabs
```

## Source note 41, line 826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L826)

```text
// the cursor straight back.
```

## Source note 42, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/mnk/mnk_input_driver.cpp#L831)

```text
// Releases landing on another window never arrive here as key-ups.
```
