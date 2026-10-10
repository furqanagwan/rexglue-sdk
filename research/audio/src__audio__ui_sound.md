# Ui sound: audio source notes

This record preserves technical and API notes moved from `src/audio/ui_sound.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/ui_sound.cpp#L74)

```text
// XMAWAVEFORMAT, then one XMASTREAMFORMAT per stream.
```

## Source note 2, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/ui_sound.cpp#L101)

```text
// One stream: the packets' payloads join into one bitstream.
```

## Source note 3, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/ui_sound.cpp#L107)

```text
// room for the bit reader's lookahead
```

## Source note 4, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/ui_sound.cpp#L137)

```text
// First byte: leading and trailing padding bit counts, as the decoder
```

## Source note 5, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/ui_sound.cpp#L138)

```text
// takes a bit-aligned frame in whole bytes.
```

## Source note 6, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/ui_sound.cpp#L142)

```text
// The frame's last bit says whether another frame follows.
```
