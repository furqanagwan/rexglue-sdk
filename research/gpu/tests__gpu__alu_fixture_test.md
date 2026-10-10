# Alu fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/alu_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L34)

```text
// Scalar opcodes (ucode::AluScalarOpcode).
```

## Source note 2, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L74)

```text
// Scalar operation on r1.x exported to eM0.x, the vector operation writing
```

## Source note 3, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L75)

```text
// nothing. For one-operand scalar operations the operand is src3's W, so the
```

## Source note 4, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L76)

```text
// swizzle selects X there.
```

## Source note 5, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L83)

```text
// mulsc (MUL_CONST_1, so the temporary register's low bit is 1: r1) exported
```

## Source note 6, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L84)

```text
// to eM0.x: c3.w * r1.x. The constant operand is src3's W and the temporary
```

## Source note 7, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L85)

```text
// its X, so a zero swizzle selects both; src3 is the constant (sel 0).
```

## Source note 8, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L86)

```text
// Source of the rounding under test: xenia-canary #1245.
```

## Source note 9, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L93)

```text
// vfetch r1 (the input in X); oPos = r1; eA from c2 by the vertex index; eM0.x
```

## Source note 10, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L94)

```text
// = the scalar operation `data` on r1.x. One exported float per vertex.
```

## Source note 11, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L113)

```text
// Inputs: signed zeros, infinities, a NaN, negatives, and finite values across
```

## Source note 12, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L114)

```text
// the exponent range (no denormals - the host flushes them).
```

## Source note 13, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L121)

```text
// Runs the scalar operation `data` on every input through a translated vertex
```

## Source note 14, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L122)

```text
// shader, with c3.w = `c3_w`, and returns the exported results, or an empty
```

## Source note 15, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L123)

```text
// vector if the draw didn't complete.
```

## Source note 16, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L127)

```text
// Triangle lists need a multiple of three vertices; pad with 1.0.
```

## Source note 17, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L184)

```text
// The documented special cases, and the double-precision value for finite
```

## Source note 18, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L185)

```text
// results. Clamped variants (C) turn infinite results into +-FLT_MAX, flushed
```

## Source note 19, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L186)

```text
// ones (F) into signed zero; LOGC turns -Inf into -FLT_MAX.
```

## Source note 20, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L212)

```text
// Single precision range.
```

## Source note 21, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L241)

```text
// Mismatch description, or empty if `result` meets the reference: bit-exact
```

## Source note 22, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L242)

```text
// for special values, within 2^-20 relative (or 2^-20 absolute near zero) for
```

## Source note 23, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L243)

```text
// finite ones, which covers the host's documented approximation error and the
```

## Source note 24, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L244)

```text
// optional 21-bit reduction.
```

## Source note 25, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L258)

```text
// A denormal result may be flushed to zero by the host float controls.
```

## Source note 26, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L294)

```text
// The opt-in reduction leaves 21 mantissa bits. The clamped variants
```

## Source note 27, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L295)

```text
// turn infinity into exactly +-FLT_MAX after it.
```

## Source note 28, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L302)

```text
// xenia-canary #1245: MULSC rounds to nearest even by default; the opt-in
```

## Source note 29, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L303)

```text
// mulsc_round_toward_zero steps a product that rounded away from zero back by
```

## Source note 30, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L304)

```text
// one ulp.
```

## Source note 31, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L318)

```text
// Batch indices times 1/3 as the Volition titles split them, and other
```

## Source note 32, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L319)

```text
// products whose float result rounds up, down or is exact.
```

## Source note 33, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L320)

```text
// 1/3 rounded up
```

## Source note 34, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/alu_fixture_test.cpp#L337)

```text
// The inputs must exercise the case the option changes.
```
