# Xenos: graphics source notes

This record preserves technical and API notes moved from `src/graphics/xenos.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L21)

```text
// Based on X360GammaToLinear and X360LinearToGamma from the Source Engine, with
```

## Source note 2, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L22)

```text
// additional logic from Direct3D 9 code in game executable disassembly, located
```

## Source note 3, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L23)

```text
// via the floating-point constants involved.
```

## Source note 4, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L24)

```text
// https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/mathlib/color_conversion.cpp#L329
```

## Source note 5, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L25)

```text
// These are provided here in part as a reference for shader translators.
```

## Source note 6, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L28)

```text
// Not found in game executables, so just using the logic similar to that in
```

## Source note 7, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L29)

```text
// the Source Engine.
```

## Source note 8, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L32)

```text
// While the compiled code for linear to gamma conversion uses `vcmpgtfp
```

## Source note 9, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L33)

```text
// constant, value` comparison (constant > value, or value < constant), it's
```

## Source note 10, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L34)

```text
// preferable to use `value >= constant` condition for the higher pieces, as
```

## Source note 11, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L35)

```text
// it will never pass for NaN, and in case of NaN, the 0...64/255 case will be
```

## Source note 12, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L36)

```text
// selected regardless of whether it's saturated before or after the
```

## Source note 13, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L37)

```text
// comparisons (always pre-saturating here, but shader translators may choose
```

## Source note 14, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L38)

```text
// to saturate later for convenience), as saturation will flush NaN to 0.
```

## Source note 15, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L54)

```text
// No `floor` term in this case in the Source Engine, but for the largest
```

## Source note 16, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L55)

```text
// value, 1.0, `floor(255.0f * (1.0f / 1024.0f))` is 0 anyway.
```

## Source note 17, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L58)

```text
// Though in the Source Engine, the 1/1024 multiplication is done for the
```

## Source note 18, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L59)

```text
// truncated part specifically, pre-baking it into the scale is lossless -
```

## Source note 19, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L60)

```text
// both 1024 and `scale` are powers of 2.
```

## Source note 20, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L62)

```text
// For consistency with linear to gamma, and because it's more logical here
```

## Source note 21, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L63)

```text
// (0 rather than 1 at -epsilon), using `trunc` instead of `floor`.
```

## Source note 22, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L66)

```text
// Clamping is not necessary (1 * (255 * 8) - 1024 + 7 is exactly 1023).
```

## Source note 23, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L73)

```text
// While the compiled code uses `vcmpgtfp constant, value` comparison
```

## Source note 24, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L74)

```text
// (constant > value, or value < constant), it's preferable to use `value >=
```

## Source note 25, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L75)

```text
// constant` condition for the higher pieces, as it will never pass for NaN,
```

## Source note 26, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L76)

```text
// and in case of NaN, the 0...64/1023 case will be selected regardless of
```

## Source note 27, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L77)

```text
// whether it's saturated before or after the comparisons (always
```

## Source note 28, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L78)

```text
// pre-saturating here, but shader translators may choose to saturate later
```

## Source note 29, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L79)

```text
// for convenience), as saturation will flush NaN to 0.
```

## Source note 30, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L97)

```text
// The truncation isn't in X360LinearToGamma in the Source Engine, but is
```

## Source note 31, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L98)

```text
// there in Direct3D 9 disassembly (the `vrfiz` instructions).
```

## Source note 32, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L99)

```text
// It also prevents conversion of 1.0 to 1.0034313725490196078431372549016
```

## Source note 33, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L100)

```text
// that's handled via clamping in the Source Engine.
```

## Source note 34, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L101)

```text
// 127.875 (1023 / 8) is truncated to 127, which, after scaling, becomes
```

## Source note 35, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L102)

```text
// 127 / 255, and when 128 / 255 is added, the result is 1.
```

## Source note 36, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L106)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 37, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L116)

```text
// Normalize the value in the resulting float.
```

## Source note 38, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L117)

```text
// do { Exponent--; Mantissa <<= 1; } while ((Mantissa & 0x80) == 0)
```

## Source note 39, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L125)

```text
// Based on CFloat24 from d3dref9.dll and the 6e4 code from:
```

## Source note 40, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L126)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 41, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L127)

```text
// 6e4 has a different exponent bias allowing [0,512) values, 20e4 allows [0,2).
```

## Source note 42, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L131)

```text
// Positive only, and not -0 or NaN.
```

## Source note 43, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L136)

```text
// Saturate.
```

## Source note 44, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L140)

```text
// The number is too small to be represented as a normalized 20e4.
```

## Source note 45, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L141)

```text
// Convert it to a denormalized value.
```

## Source note 46, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L145)

```text
// Rebias the exponent to represent the value as a normalized 20e4.
```

## Source note 47, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L162)

```text
// Normalize the value in the resulting float.
```

## Source note 48, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/xenos.cpp#L163)

```text
// do { Exponent--; Mantissa <<= 1; } while ((Mantissa & 0x100000) == 0)
```
