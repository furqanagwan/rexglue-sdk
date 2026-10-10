# Math: core source notes

This record preserves technical and API notes moved from `include/rex/math.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L41)

```text
// Rounds up the given value to the given alignment.
```

## Source note 2, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L47)

```text
// Rounds the given number up to the next highest multiple.
```

## Source note 3, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L56)

```text
// For NaN, returns min_value (or, if it's NaN too, max_value).
```

## Source note 4, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L57)

```text
// If either of the boundaries is zero, and if the value is at that boundary or
```

## Source note 5, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L58)

```text
// exceeds it, the result will have the sign of that boundary. If both
```

## Source note 6, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L59)

```text
// boundaries are zero, which sign is selected among the argument signs is not
```

## Source note 7, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L60)

```text
// explicitly defined.
```

## Source note 8, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L67)

```text
// Using the same conventions as in shading languages, returning 0 for NaN.
```

## Source note 9, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L68)

```text
// 0 is always returned as positive.
```

## Source note 10, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L74)

```text
// Gets the next power of two value that is greater than or equal to the given
```

## Source note 11, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L75)

```text
// value.
```

## Source note 12, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L96)

```text
// Use the Euclid algorithm to calculate the greatest common divisor
```

## Source note 13, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L129)

```text
// lzcnt - count leading zeros.
```

## Source note 14, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L130)

```text
// Returns the size of the input operand if value is zero.
```

## Source note 15, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L136)

```text
// tzcnt - count trailing zeros.
```

## Source note 16, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L166)

```text
// BitScanForward (bsf).
```

## Source note 17, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L167)

```text
// Search the value from least significant bit (LSB) to the most significant bit
```

## Source note 18, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L168)

```text
// (MSB) for a set bit (1).
```

## Source note 19, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L169)

```text
// Returns false if no bits are set and the output index is invalid.
```

## Source note 20, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L194)

```text
// Utilities for SSE values.
```

## Source note 21, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L229)

```text
// Similar to the C++ implementation of XMConvertFloatToHalf and
```

## Source note 22, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L230)

```text
// XMConvertHalfToFloat from DirectXMath 3.00 (pre-3.04, which switched from the
```

## Source note 23, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L231)

```text
// Xenos encoding to IEEE 754), with the extended range instead of infinity and
```

## Source note 24, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L232)

```text
// NaN, and optionally with denormalized numbers - as used in vpkd3d128 (no
```

## Source note 25, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L233)

```text
// denormals, rounding towards zero) and on the Xenos (GL_OES_texture_float
```

## Source note 26, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L234)

```text
// alternative encoding).
```

## Source note 27, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L242)

```text
// Saturate.
```

## Source note 28, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L246)

```text
// The number is too small to be represented as a normalized half.
```

## Source note 29, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L254)

```text
// Rebias the exponent to represent the value as a normalized half.
```

## Source note 30, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L272)

```text
// Normalize the value in the resulting float.
```

## Source note 31, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L273)

```text
// do { Exponent--; Mantissa <<= 1; } while ((Mantissa & 0x0400) == 0)
```

## Source note 32, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/math.h#L287)

```text
// https://locklessinc.com/articles/sat_arithmetic/
```
