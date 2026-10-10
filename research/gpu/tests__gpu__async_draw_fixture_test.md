# Async draw fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/async_draw_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/async_draw_fixture_test.cpp#L36)

```text
// In samples: 32 is a 1-tile render target (small, generated-data sized);
```

## Source note 2, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/async_draw_fixture_test.cpp#L37)

```text
// 320 is 4 tiles wide. Both are drawn once, never before.
```

## Source note 3, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/async_draw_fixture_test.cpp#L50)

```text
// A pixel shader this fixture hasn't seen, so its pipeline is created
```

## Source note 4, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/async_draw_fixture_test.cpp#L51)

```text
// asynchronously when the draw needs it.
```
