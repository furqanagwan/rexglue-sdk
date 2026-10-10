# Ui sound: audio source notes

This record preserves technical and API notes moved from `include/rex/audio/ui_sound.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/ui_sound.h#L26)

```text
/// Decodes a single-stream RIFF XMA file (XMA1 format tag 0x165 or XMA2
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/ui_sound.h#L27)

```text
/// 0x166), as the dashboard's UI sounds are, frame by frame through the
```

## Source note 3, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/ui_sound.h#L28)

```text
/// SDK's XMA frame decoder.
```

## Source note 4, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/ui_sound.h#L31)

```text
/// Plays UI sounds on their own XAudio2 engine, so they are heard whatever
```

## Source note 5, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/ui_sound.h#L32)

```text
/// the guest's audio is doing.
```

## Source note 6, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/ui_sound.h#L35)

```text
/// Null when XAudio2 or an output device is unavailable.
```
