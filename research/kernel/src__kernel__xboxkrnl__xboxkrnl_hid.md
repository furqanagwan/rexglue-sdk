# Xboxkrnl hid: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_hid.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_hid.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_hid.cpp#L29)

```text
// HidGetCapabilities - ordinal 0x01EA
```

## Source note 3, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_hid.cpp#L30)

```text
// Returns capabilities for HID device (keyboard/mouse)
```

## Source note 4, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_hid.cpp#L31)

```text
// Not supported in rexglue - return unsuccessful
```

## Source note 5, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_hid.cpp#L36)

```text
// HidGetLastInputTime - ordinal 0x01F1
```

## Source note 6, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_hid.cpp#L37)

```text
// Returns the last time any HID input was received
```

## Source note 7, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_hid.cpp#L45)

```text
// HidReadMouseChanges - ordinal 0x0273
```

## Source note 8, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_hid.cpp#L46)

```text
// Reads mouse input changes - not supported in rexglue
```

## Source note 9, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_hid.cpp#L57)

```text
// XInputd stubs
```

## Source note 10, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_hid.cpp#L91)

```text
// Drv stubs
```
