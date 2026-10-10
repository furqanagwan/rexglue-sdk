# Float precision: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/float_precision.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/float_precision.h#L19)

```text
// Reduces a finite float to mantissa_bits (1-22) mantissa bits, rounding to
```

## Source note 2, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/float_precision.h#L20)

```text
// nearest with halfway values away from zero, for the scalar approximations
```

## Source note 3, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/float_precision.h#L21)

```text
// (EXP, LOG, LOGC, RCP*, RSQ*, SQRT) when gpu_scalar_approximation_rounding is
```

## Source note 4, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/float_precision.h#L22)

```text
// enabled. The console's actual precision and midpoint behavior are unknown;
```

## Source note 5, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/float_precision.h#L23)

```text
// this is what 4E4D07D1 needs. Inf and NaN are returned unchanged, signed
```

## Source note 6, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/float_precision.h#L24)

```text
// zero stays signed, and a finite value is never rounded up to infinity (the
```

## Source note 7, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/float_precision.h#L25)

```text
// truncated value is kept instead). The DXBC translator emits the same
```

## Source note 8, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/float_precision.h#L26)

```text
// operations (DxbcShaderTranslator::ReduceFloatPrecision).
```
