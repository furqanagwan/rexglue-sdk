# Gamepad devices: input source notes

This record preserves technical and API notes moved from `include/rex/input/gameinput/gamepad_devices.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L24)

```text
// Motor speeds to send to a host device, in XInput's 0-65535 range.
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L31)

```text
// What the host says about a pad, reported to the guest in its capabilities.
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L35)

```text
// Whether the pad has XInput's two motors; without them the capabilities
```

## Source note 4, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L36)

```text
// report no vibration, as XInput does.
```

## Source note 5, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L40)

```text
// Everything the GameInput driver tells the guest, kept apart from GameInput
```

## Source note 6, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L41)

```text
// itself so the XInput semantics are testable without devices or the GDK:
```

## Source note 7, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L42)

```text
// device identity across connect/disconnect, packet numbers, the untouched
```

## Source note 8, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L43)

```text
// pad while unfocused, keystrokes, and rumble that holds until the guest
```

## Source note 9, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L44)

```text
// changes it but stops while unfocused and never outlives a disconnect.
```

## Source note 10, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L45)

```text
// Host devices are opaque keys (the driver uses IGameInputDevice pointers).
```

## Source note 11, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L46)

```text
// Not thread-safe; the driver serializes access.
```

## Source note 12, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L49)

```text
// A newly connected host device gets a new DeviceId, even when the same
```

## Source note 13, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L50)

```text
// device reconnects, so no state from before the disconnect reaches the
```

## Source note 14, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L51)

```text
// guest. InputSystem decides which guest user the new id becomes.
```

## Source note 15, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L53)

```text
// Returns false for an unknown device. The id is gone afterwards: every
```

## Source note 16, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L54)

```text
// query for it reports X_ERROR_DEVICE_NOT_CONNECTED.
```

## Source note 17, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L61)

```text
// Stores the host's latest reading.
```

## Source note 18, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L64)

```text
// `active` false (window unfocused, overlay open) reports an untouched pad.
```

## Source note 19, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L65)

```text
// The packet number advances once per change seen by the guest, including
```

## Source note 20, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L66)

```text
// focus changes, and starts at 1 for a new device.
```

## Source note 21, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L72)

```text
// Records the guest's request. Returns the rumble to apply to the host
```

## Source note 22, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L73)

```text
// device now: the request while active, nothing while inactive (the
```

## Source note 23, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L74)

```text
// motors are already stopped and resume on SetActive(true)).
```

## Source note 24, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L78)

```text
// Focus transitions. Returns the host devices whose motors must change:
```

## Source note 25, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L79)

```text
// stopped on losing focus, back to the guest's request on regaining it.
```

## Source note 26, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L82)

```text
// "GI"
```

## Source note 27, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/gameinput/gamepad_devices.h#L91)

```text
// XInput starts with packet_number = 1
```
