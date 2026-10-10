# Mnk input driver: input source notes

This record preserves technical and API notes moved from `include/rex/input/mnk/mnk_input_driver.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L64)

```text
/// Appends to the keystroke queue, evicting the oldest entry once it is full.
```

## Source note 2, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L66)

```text
/// Queues one raw key for the guest, with its unicode and modifier state.
```

## Source note 3, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L67)

```text
/// Passthrough only.
```

## Source note 4, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L69)

```text
/// Re-evaluates every bind against the current key state and queues a
```

## Source note 5, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L70)

```text
/// keystroke for each pad button that changed. Call with state_mutex_ held
```

## Source note 6, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L71)

```text
/// after any key or mouse button moves.
```

## Source note 7, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L74)

```text
// Called from the guest thread. The rest of the capture path stays on the UI
```

## Source note 8, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L75)

```text
// thread, since every Window call in it is a UI-thread call.
```

## Source note 9, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L80)

```text
// Safe to call from any thread.
```

## Source note 10, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L83)

```text
// Only the UI thread writes it, so only guest thread access needs the lock.
```

## Source note 11, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L89)

```text
// Mouse delta tracking. Fractional because relative motion arrives in
```

## Source note 12, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L90)

```text
// fractions of a pixel, and truncating each event drops slow movement.
```

## Source note 13, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L91)

```text
// Filled on the UI thread, drained on the guest thread, hence the lock.
```

## Source note 14, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L95)

```text
// UI thread only.
```

## Source note 15, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L99)

```text
// Whether the window has the pointer locked and is reporting relative motion.
```

## Source note 16, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L101)

```text
// Cursor visibility to restore on capture release - the window owner may run
```

## Source note 17, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L102)

```text
// an auto-hide policy that capture must not permanently override.
```

## Source note 18, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L106)

```text
// Guest thread to UI thread. The queued flag coalesces the posts.
```

## Source note 19, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L112)

```text
// Keystroke queue. In passthrough it carries raw keys; otherwise the
```

## Source note 20, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L113)

```text
// VK_PAD_* codes of the bound buttons.
```

## Source note 21, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L115)

```text
// Which binds were pressed at the last evaluation, to diff against. One bit
```

## Source note 22, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L116)

```text
// per entry of the bind table.
```

## Source note 23, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/mnk/mnk_input_driver.h#L119)

```text
// Packet number incremented on state change
```
