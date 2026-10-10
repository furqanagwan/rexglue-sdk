# Zpd report test: graphics source notes

This record preserves technical and API notes moved from `tests/unit/graphics/zpd_report_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/zpd_report_test.cpp#L36)

```text
// A gets the odd sample; D3D sums the two.
```

## Source note 2, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/zpd_report_test.cpp#L44)

```text
// 425307EC masks each lane to 24 bits before summing, so neither lane may
```

## Source note 3, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/zpd_report_test.cpp#L45)

```text
// carry the whole count.
```

## Source note 4, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/zpd_report_test.cpp#L53)

```text
// The hardware counters are 32-bit and free-running; D3D subtracts the BEGIN
```

## Source note 5, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/zpd_report_test.cpp#L54)

```text
// snapshot from the END one, so a wrap in between still gives the delta.
```

## Source note 6, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/zpd_report_test.cpp#L70)

```text
// Rounded to nearest.
```

## Source note 7, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/zpd_report_test.cpp#L73)

```text
// A visible sliver never normalizes to occluded.
```

## Source note 8, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/zpd_report_test.cpp#L79)

```text
// GetData polls ZPass and QueryBatch Lock polls ZPass_A or StencilFail_B, so
```

## Source note 9, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/zpd_report_test.cpp#L80)

```text
// they're the tail of the structure and written after Total and ZFail.
```

## Source note 10, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/zpd_report_test.cpp#L93)

```text
// Lane order is the shader's: Total (unused), ZFail, ZPass, StencilFail.
```

## Source note 11, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/zpd_report_test.cpp#L100)

```text
// Total is always the sum, never the stored lane.
```
