# Input system: input source notes

This record preserves technical and API notes moved from `src/input/input_system.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L32)

```text
// GameInput in GDK builds, XInput otherwise. "sdl" is still accepted so an
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L33)

```text
// old config starts: SDL was removed (RG-GDK-033), and it now means the
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L34)

```text
// default, with a warning.
```

## Source note 4, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L59)

```text
// Synthetic devices are parked past every physical ordinal so they cannot push
```

## Source note 5, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L60)

```text
// a real pad off guest user 0. SlotAssignment routes them by their synthetic
```

## Source note 6, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L61)

```text
// flag and never reads this value.
```

## Source note 7, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L79)

```text
// device_owners_ holds raw driver pointers.
```

## Source note 8, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L126)

```text
// Carry forward ordinals already handed out, so a device keeps its guest user
```

## Source note 9, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L127)

```text
// when another pad is unplugged.
```

## Source note 10, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L141)

```text
// Runs after the carry-forward pass so a new device cannot take an ordinal a
```

## Source note 11, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L142)

```text
// live one is still holding. Lowest free rather than a growing counter,
```

## Source note 12, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L143)

```text
// because a reconnected pad arrives as a new device and would otherwise walk
```

## Source note 13, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L144)

```text
// off the end of the guest users.
```

## Source note 14, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L149)

```text
// Only physical devices consume an ordinal, so the first pad to connect is
```

## Source note 15, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L150)

```text
// guest user 0 however many synthetic devices enumerated ahead of it.
```

## Source note 16, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L184)

```text
// Stable: synthetic devices share one ordinal, and their relative order
```

## Source note 17, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L185)

```text
// decides which answers GetCapabilities when no pad is attached.
```

## Source note 18, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L228)

```text
// Prefer the pad in hand, so button glyphs follow it rather than whichever
```

## Source note 19, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L229)

```text
// device enumerated first.
```

## Source note 20, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L287)

```text
// Deadzone percentages scale against the device's own range.
```

## Source note 21, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L303)

```text
// Titles poll capabilities off this rather than every frame, so without it
```

## Source note 22, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L304)

```text
// a pad plugged in mid-game is never noticed. Sent outside mutex_: listeners
```

## Source note 23, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L305)

```text
// are guest objects with their own locks.
```

## Source note 24, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L317)

```text
// A dialog owns the controller.
```

## Source note 25, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L330)

```text
// Each button leaves the mask once the player lets go of it.
```

## Source note 26, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L424)

```text
// Whatever is held right now stays masked until released, so the press
```

## Source note 27, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L425)

```text
// that dismissed the dialog is not also read as a press in the game.
```

## Source note 28, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L433)

```text
// Keystroke synthesizers see the held buttons now, so their key-downs
```

## Source note 29, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L434)

```text
// are spent here rather than reaching the game.
```

## Source note 30, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L450)

```text
// The guest's next SetState may never come while a motor is running.
```

## Source note 31, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L479)

```text
// Every pad on this user belongs to the same player, so all of them buzz.
```

## Source note 32, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L480)

```text
// Only pads decide the result: synthetic devices accept any vibration and
```

## Source note 33, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L481)

```text
// would otherwise report success for a pad that never rumbled.
```

## Source note 34, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L516)

```text
// Keystrokes made while a dialog is up belong to the dialog.
```

## Source note 35, line 552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L552)

```text
// Bounded: a driver synthesizing repeats never runs dry while a key is held.
```

## Source note 36, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L578)

```text
// GameInput does not list Bluetooth LE pads (xinputhid), so XInput
```

## Source note 37, line 579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L579)

```text
// adds the pads it does not serve. Both drivers live as long as input.
```

## Source note 38, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L604)

```text
// Keyboard and mouse still work through MnK.
```

## Source note 39, line 612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L612)

```text
// MnK driver (keyboard/mouse -> controller emulation)
```

## Source note 40, line 621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/input_system.cpp#L621)

```text
// NOP driver (primary in tool mode, fallback otherwise)
```
