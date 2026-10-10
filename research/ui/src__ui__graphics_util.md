# Graphics util: ui source notes

This record preserves technical and API notes moved from `src/ui/graphics_util.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L20)

```text
// https://microsoft.github.io/DirectX-Specs/d3d/archive/D3D11_3_FunctionalSpec.htm#3.2.4.1%20FLOAT%20-%3E%20Fixed%20Point%20Integer
```

## Source note 2, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L21)

```text
// Early exit tests.
```

## Source note 3, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L22)

```text
// n == NaN || n.unbiasedExponent < -f-1 -> 0 . 0
```

## Source note 4, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L26)

```text
// n >= (2^(i-1)-2^-f) -> 2^(i-1)-1 . 2^f-1
```

## Source note 5, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L30)

```text
// n <= -2^(i-1) -> -2^(i-1) . 0
```

## Source note 6, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L35)

```text
// Copy float32 mantissa bits [22:0] into corresponding bits [22:0] of a
```

## Source note 7, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L36)

```text
// result buffer that has at least 24 bits total storage (before reaching
```

## Source note 8, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L37)

```text
// rounding step further below). This includes one bit for the hidden 1.
```

## Source note 9, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L38)

```text
// Set bit [23] (float32 hidden bit).
```

## Source note 10, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L39)

```text
// Clear bits [31:24].
```

## Source note 11, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L45)

```text
// If the sign bit is set in the float32 number (negative), then take the 2's
```

## Source note 12, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L46)

```text
// component of the entire set of bits.
```

## Source note 13, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L50)

```text
// Final calculation: extraBits = (mantissa - f) - n.unbiasedExponent
```

## Source note 14, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L51)

```text
// (guaranteed to be >= 0).
```

## Source note 15, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L55)

```text
// Round the 32-bit value to a decimal that is extraBits to the left of
```

## Source note 16, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L56)

```text
// the LSB end, using nearest-even.
```

## Source note 17, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_util.cpp#L58)

```text
// Shift right by extraBits (sign extending).
```
