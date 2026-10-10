# Vblank pacer test: graphics source notes

This record preserves technical and API notes moved from `tests/unit/graphics/vblank_pacer_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/vblank_pacer_test.cpp#L20)

```text
// one per interval
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/vblank_pacer_test.cpp#L27)

```text
// Woke 600 ticks late: fires now, and the next one is still due at 2000.
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/vblank_pacer_test.cpp#L35)

```text
// A coarse 15.6 ms sleep against a 16.7 ms vblank used to deliver several
```

## Source note 4, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/vblank_pacer_test.cpp#L36)

```text
// vblanks at once after a long wake. More than two intervals late now fires
```

## Source note 5, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/vblank_pacer_test.cpp#L37)

```text
// one and starts over.
```

## Source note 6, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/vblank_pacer_test.cpp#L42)

```text
// Up to two intervals late still catches up, one vblank per call.
```
