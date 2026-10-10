# Audio backend: audio source notes

This record preserves technical and API notes moved from `src/audio/audio_backend.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_backend.cpp#L16)

```text
// "sdl" is still accepted so an old config starts: SDL was removed
```

## Source note 2, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_backend.cpp#L17)

```text
// (RG-GDK-033), and it now means XAudio2, with a warning.
```

## Source note 3, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_backend.cpp#L22)

```text
// Applied by every output driver; defined here since the SDL driver that
```

## Source note 4, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_backend.cpp#L23)

```text
// held it was removed.
```
