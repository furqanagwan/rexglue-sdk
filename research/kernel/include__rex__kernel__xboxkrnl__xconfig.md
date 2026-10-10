# Xconfig: kernel source notes

This record preserves technical and API notes moved from `include/rex/kernel/xboxkrnl/xconfig.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xconfig.h#L15)

```text
// XCONFIG_USER_VIDEO_FLAGS as the console reports it.
```

## Source note 2, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xconfig.h#L18)

```text
// XCONFIG_USER_AUDIO_FLAGS: analog stereo (0x00010001), the value Xenia
```

## Source note 3, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xconfig.h#L19)

```text
// Canary and Edge report by default. XGetAudioFlags returns the same value.
```
