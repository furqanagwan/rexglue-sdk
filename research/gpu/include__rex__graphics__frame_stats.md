# Frame stats: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/frame_stats.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/frame_stats.h#L21)

```text
// Collects the time between guest frame swaps and summarizes a window of them.
```

## Source note 2, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/frame_stats.h#L22)

```text
// Not thread-safe: the command processor thread owns it.
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/frame_stats.h#L33)

```text
// Frames that took longer than one or two 60 Hz refreshes.
```

## Source note 4, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/frame_stats.h#L46)

```text
// Summarizes the frames since the last call and starts a new window.
```

## Source note 5, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/frame_stats.h#L82)

```text
// Swap timing jitters by a fraction of a millisecond; a frame is only late
```

## Source note 6, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/frame_stats.h#L83)

```text
// when it clearly misses a refresh.
```
