# Gameinput mapping: input source notes

This record preserves technical and API notes moved from `src/input/gameinput/gameinput_mapping.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_mapping.h#L17)

```text
// The GDK headers need the Windows headers first.
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_mapping.h#L24)

```text
// GameInput sticks are -1..1 with up positive, as in XInput. The negative
```

## Source note 3, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_mapping.h#L25)

```text
// half spans 32768 and the positive 32767, so both extremes of the XInput
```

## Source note 4, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_mapping.h#L26)

```text
// range are reachable. GameInput applies no dead zone to gamepad readings
```

## Source note 5, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_mapping.h#L27)

```text
// and neither does this; titles apply their own, as they do with XInput.
```

## Source note 6, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_mapping.h#L85)

```text
// GameInput names a device's kind rather than an XInput subtype. A wheel or
```

## Source note 7, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_mapping.h#L86)

```text
// stick usually also offers GameInputKindGamepad, so the specific kind wins.
```

## Source note 8, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_mapping.h#L100)

```text
// XInput vibration needs both body motors; trigger motors alone do not count.
```

## Source note 9, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_mapping.h#L105)

```text
// XInput's left motor is the low-frequency (heavy) one, the right the
```

## Source note 10, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/gameinput/gameinput_mapping.h#L106)

```text
// high-frequency one. Trigger motors have no XInput equivalent and stay off.
```
