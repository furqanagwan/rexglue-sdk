# Input system: input source notes

This record preserves technical and API notes moved from `include/rex/input/input_system.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L47)

```text
/// Replaces any previous assignment. Call before the guest starts polling.
```

## Source note 2, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L52)

```text
/// GetState for the emulator's own UI, which reads while the guest is blocked.
```

## Source note 3, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L56)

```text
/// The power of the pad that speaks for the user. False when no pad is
```

## Source note 4, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L57)

```text
/// connected or its driver cannot tell.
```

## Source note 5, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L60)

```text
/// While any blocker is held the guest reads a neutral pad and no
```

## Source note 6, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L61)

```text
/// keystrokes. Buttons still held when a blocker drops stay masked until
```

## Source note 7, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L62)

```text
/// released, so the press that dismissed the dialog does not also reach the
```

## Source note 8, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L63)

```text
/// game.
```

## Source note 9, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L73)

```text
/// Guest user whose device most recently produced a button press.
```

## Source note 10, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L77)

```text
// Guest threads may poll input concurrently. Hold this across refresh,
```

## Source note 11, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L78)

```text
// assignment, and driver lookup so one poll cannot invalidate another.
```

## Source note 12, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L81)

```text
/// Re-enumerates every driver and notifies the assignment when the set
```

## Source note 13, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L82)

```text
/// changed.
```

## Source note 14, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L86)

```text
/// The device that speaks for a user, preferring the one most recently in
```

## Source note 15, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L87)

```text
/// the player's hands.
```

## Source note 16, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L90)

```text
/// Merged state of a user's devices with the deadzones applied. Sets
```

## Source note 17, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L91)

```text
/// `out_devices_changed` when the user connected or disconnected, for the
```

## Source note 18, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L92)

```text
/// caller to send XN_SYS_INPUTDEVICESCHANGED once mutex_ is released.
```

## Source note 19, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L96)

```text
/// Reads and discards pending keystrokes. Returns the last read's result.
```

## Source note 20, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L109)

```text
// Ordered by ordinal. Ordinals are never recycled, so unplugging pad one
```

## Source note 21, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L110)

```text
// does not renumber pad two.
```

## Source note 22, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L114)

```text
// Written under mutex_; atomic so the getters can read without it.
```

## Source note 23, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L117)

```text
// {left, right} stick ranges, scaling the deadzone percentages.
```

## Source note 24, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L120)

```text
// The rest are guarded by mutex_.
```

## Source note 25, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L122)

```text
// Masked out per user until the guest sees them released.
```

## Source note 26, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L126)

```text
/// Create a default InputSystem: GameInput or XInput by input_backend,
```

## Source note 27, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L127)

```text
/// then MnK and NOP.
```

## Source note 28, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L128)

```text
/// In tool mode, only the NOP driver is added.
```

## Source note 29, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/input_system.h#L130)

```text
/// Host menus: physical pads only, without guest MnK/NOP synthetic devices.
```
