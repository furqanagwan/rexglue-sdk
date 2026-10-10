# Float precision test: graphics source notes

This record preserves technical and API notes moved from `tests/unit/graphics/float_precision_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/float_precision_test.cpp#L33)

```text
// The two discarded bits: below half truncates, half and above rounds up.
```

## Source note 2, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/float_precision_test.cpp#L38)

```text
// Away from zero for negative values too (magnitude bits round the same).
```

## Source note 3, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/float_precision_test.cpp#L41)

```text
// A carry into the exponent is still a correctly rounded value.
```

## Source note 4, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/float_precision_test.cpp#L43)

```text
// Results always have the low two mantissa bits clear.
```

## Source note 5, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/float_precision_test.cpp#L57)

```text
// FLT_MAX would round up into infinity; the truncated value is kept.
```
