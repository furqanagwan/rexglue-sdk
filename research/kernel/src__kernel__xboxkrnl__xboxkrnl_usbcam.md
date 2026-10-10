# Xboxkrnl usbcam: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_usbcam.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_usbcam.cpp#L22)

```text
// 0x4B000 640x480?
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_usbcam.cpp#L24)

```text
// This function should return success.
```

## Source note 3, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_usbcam.cpp#L25)

```text
// It looks like it only allocates space for usbcam support.
```

## Source note 4, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_usbcam.cpp#L26)

```text
// returning error code might cause games to initialize incorrectly.
```

## Source note 5, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_usbcam.cpp#L27)

```text
// "Carcassonne" initalization function checks for result from this
```

## Source note 6, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_usbcam.cpp#L28)

```text
// function. If value is different than 0 instead of loading
```

## Source note 7, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_usbcam.cpp#L29)

```text
// rest of the game it returns from initalization function and tries
```

## Source note 8, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_usbcam.cpp#L30)

```text
// to run game normally which causes crash, due to uninitialized data.
```

## Source note 9, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_usbcam.cpp#L35)

```text
// 0 = not connected.
```
