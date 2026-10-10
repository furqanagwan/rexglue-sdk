# Device: input source notes

This record preserves technical and API notes moved from `include/rex/input/device.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device.h#L20)

```text
/// Driver-scoped device handle. Never reused within a process run, so a handle
```

## Source note 2, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device.h#L21)

```text
/// that outlives its device resolves to nothing rather than aliasing whichever
```

## Source note 3, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device.h#L22)

```text
/// device took the freed slot.
```

## Source note 4, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device.h#L27)

```text
// connection order, assigned by InputSystem
```

## Source note 5, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device.h#L30)

```text
// XINPUT_DEVSUBTYPE_*
```

## Source note 6, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device.h#L31)

```text
// keyboard/mouse emulation or the NOP stand-in
```

## Source note 7, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device.h#L34)

```text
/// How a host pad is powered, as far as the host APIs say. The guide shows a
```

## Source note 8, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device.h#L35)

```text
/// battery only for wireless pads with a known level, as the console does.
```

## Source note 9, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device.h#L38)

```text
// 0 to 100, or -1 when the level is not reported
```
