# Viz fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/viz_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L34)

```text
// The fixtures' cvars outlive them.
```

## Source note 2, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L56)

```text
// DrawRect, through PM4_DRAW_INDX with a VIZ token: drawn only if the token's
```

## Source note 3, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L57)

```text
// ID was visible.
```

## Source note 4, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L77)

```text
// Behind the background's 0.5 or in front of it.
```

## Source note 5, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L79)

```text
// Surveys only depth test with hi-Z on.
```

## Source note 6, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L81)

```text
// Finishes the submission between the survey and its consumer, so the
```

## Source note 7, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L82)

```text
// consumer uses the resolved answer instead of the predicate.
```

## Source note 8, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L86)

```text
// The background writes depth 0.5; the survey for kVizId is at survey_z; the
```

## Source note 9, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L87)

```text
// consumer carries the ID's token. Returns the first texel of the color target.
```

## Source note 10, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L105)

```text
// Color after the depth buffer in EDRAM rather than aliasing it.
```

## Source note 11, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L114)

```text
// The survey: tested against the background's depth, never drawn.
```

## Source note 12, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L131)

```text
// The consumer, in front of everything.
```

## Source note 13, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L165)

```text
// With VIZ off every consumer draws, as before.
```

## Source note 14, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L168)

```text
// Hidden: the consumer was skipped, leaving the background.
```

## Source note 15, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/viz_fixture_test.cpp#L178)

```text
// Behind the background, but without hi-Z nothing rejects the survey.
```
