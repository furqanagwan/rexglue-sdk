# Video: kernel source notes

This record preserves technical and API notes moved from `include/rex/kernel/xboxkrnl/video.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/video.h#L29)

```text
// Register video variable exports (VdGlobalDevice, VdHSIOCalibrationLock, etc.)
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/video.h#L30)

```text
// Must be called during kernel initialization before XEX modules are loaded.
```
