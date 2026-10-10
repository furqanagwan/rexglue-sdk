# Downmix: audio source notes

This record preserves technical and API notes moved from `src/audio/downmix.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/downmix.cpp#L21)

```text
// One output device exists, so the mix parameters are process state. The
```

## Source note 2, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/downmix.cpp#L22)

```text
// reader is the SDL device callback, which runs every 5.33 ms, so a plain
```

## Source note 3, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/downmix.cpp#L23)

```text
// mutex costs nothing and avoids a torn read across the four weights.
```
