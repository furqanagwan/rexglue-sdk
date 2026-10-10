# Gamepad devices: input source notes

This record preserves technical and API notes moved from `src/input/gameinput/gamepad_devices.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gamepad_devices.cpp#L85)

```text
// Held buttons are kept and show again once active.
```

## Source note 2, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gamepad_devices.cpp#L97)

```text
// Every input, as the SDL driver reports. The subtype is what the host
```

## Source note 3, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gamepad_devices.cpp#L98)

```text
// identified: GameInput knows wheels and arcade and flight sticks, but not
```

## Source note 4, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gamepad_devices.cpp#L99)

```text
// Xbox 360 instruments, which report as gamepads.
```
