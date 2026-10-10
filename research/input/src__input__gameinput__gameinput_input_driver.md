# Gameinput input driver: input source notes

This record preserves technical and API notes moved from `src/input/gameinput/gameinput_input_driver.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_input_driver.h#L20)

```text
// The GDK headers need the Windows headers first.
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_input_driver.h#L27)

```text
// Gamepads through GameInput (GameInputKindGamepad). The runtime DLL is loaded
```

## Source note 3, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_input_driver.h#L28)

```text
// at Setup, so a machine without GameInput gets a logged diagnostic and the
```

## Source note 4, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_input_driver.h#L29)

```text
// caller falls back to another driver instead of failing to start.
```

## Source note 5, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_input_driver.h#L46)

```text
/// Connected pads with this USB vendor and product ID, for the XInput
```

## Source note 6, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_input_driver.h#L47)

```text
/// supplement to skip.
```

## Source note 7, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_input_driver.h#L56)

```text
// All require mutex_. ActiveLocked reads is_active() and applies a focus
```

## Source note 8, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_input_driver.h#L57)

```text
// change to the motors; PollLocked stores the device's current reading.
```

## Source note 9, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_input_driver.h#L67)

```text
// Connected devices, each holding one reference; keyed like devices_.
```
