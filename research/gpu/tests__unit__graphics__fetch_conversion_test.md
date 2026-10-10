# Fetch conversion test: graphics source notes

This record preserves technical and API notes moved from `tests/unit/graphics/fetch_conversion_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 1

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/fetch_conversion_test.cpp#L1)

```text
/**
 * @file        fetch_conversion_test.cpp
 * @brief       Packing of the fixed-format fetch conversion (RG-GDK-045)
 *
 * texture_util::GetIntegerScaleBits tells the translated fetch how to give the
 * guest its own result from a host sample: the integer range for num_format 1,
 * 16 fractional bits and the 4 to 7 bit point-sample conversion for num_format
 * 0, and the point sampled flag that snaps coordinates (xenia-canary #1072,
 * #1137, #1177, #1250).
 */
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/fetch_conversion_test.cpp#L27)

```text
// X, Y, Z, W from components 0, 1, 2, 3.
```

## Source note 3, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/fetch_conversion_test.cpp#L60)

```text
// 4_4_4_4 read as integers [0, 15]; linear filtering, so no point flag.
```

## Source note 4, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/fetch_conversion_test.cpp#L64)

```text
// 1_5_5_5 (components 5, 5, 5, 1) with a signed X.
```

## Source note 5, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/fetch_conversion_test.cpp#L72)

```text
// Filtered 4_4_4_4: rounding only.
```

## Source note 6, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/fetch_conversion_test.cpp#L75)

```text
// Point sampled 4_4_4_4: the guest's n * (2^w + 1) / 2^(2w) needs the width.
```

## Source note 7, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/fetch_conversion_test.cpp#L80)

```text
// Point sampled 8_8_8_8: 8 bits is outside 4 to 7, so no widths.
```

## Source note 8, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/fetch_conversion_test.cpp#L86)

```text
// 8 has one component; Y, Z and W read past it and take the last stored
```

## Source note 9, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/fetch_conversion_test.cpp#L87)

```text
// one. Constant 0 and 1 outputs carry nothing.
```

## Source note 10, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/fetch_conversion_test.cpp#L94)

```text
// Gamma with integer num_format: nothing for that component.
```

## Source note 11, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/fetch_conversion_test.cpp#L98)

```text
// Gamma with normalized num_format: the sign without a width.
```

## Source note 12, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/fetch_conversion_test.cpp#L101)

```text
// A float format is not sampled normalized; only the point flag remains.
```
