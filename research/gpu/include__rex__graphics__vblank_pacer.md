# Vblank pacer: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/vblank_pacer.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/vblank_pacer.h#L15)

```text
// Guest vblanks at a fixed cadence, one per interval. Adapted from the
```

## Source note 2, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/vblank_pacer.h#L16)

```text
// xenia-edge frame limiter (src/xenia/gpu/graphics_system.cc): a waiter that
```

## Source note 3, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/vblank_pacer.h#L17)

```text
// wakes late fires once and keeps the cadence; one more than two intervals
```

## Source note 4, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/vblank_pacer.h#L18)

```text
// late starts a new cadence instead of firing a burst of vblanks.
```

## Source note 5, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/vblank_pacer.h#L24)

```text
// True when a vblank is due at `now`; it is then counted.
```

## Source note 6, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/vblank_pacer.h#L37)

```text
// Ticks until the next vblank (0 when one is due).
```
