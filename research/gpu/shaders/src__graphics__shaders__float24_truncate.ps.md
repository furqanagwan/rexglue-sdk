# Float24 truncate.ps: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/float24_truncate.ps.hlsl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 10

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L10)

```text
// Simplified conversion, always less than or equal to the original value -
```

## Source note 2, line 11

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L11)

```text
// just drop the lower bits.
```

## Source note 3, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L12)

```text
// The float32 exponent bias is 127.
```

## Source note 4, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L13)

```text
// After saturating, the exponent range is -127...0.
```

## Source note 5, line 14

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L14)

```text
// The smallest normalized 20e4 exponent is -14 - should drop 3 mantissa bits
```

## Source note 6, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L15)

```text
// at -14 or above.
```

## Source note 7, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L16)

```text
// The smallest denormalized 20e4 number is -34 - should drop 23 mantissa bits
```

## Source note 8, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L17)

```text
// at -34.
```

## Source note 9, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L18)

```text
// Anything smaller than 2^-34 becomes 0.
```

## Source note 10, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L19)

```text
// Input Z may be outside the viewport range (it's clamped after the shader).
```

## Source note 11, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L20)

```text
// Assuming that 0...0.5 on the host corresponds to 0...1 on the guest, to
```

## Source note 12, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L21)

```text
// allow for safe reinterpretation of any 24-bit value to and from float24
```

## Source note 13, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L22)

```text
// depth using depth output without unrestricted depth range.
```

## Source note 14, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L24)

```text
// Check if the number is representable as a float24 after truncation - the
```

## Source note 15, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L25)

```text
// exponent is at least -34.
```

## Source note 16, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L27)

```text
// Extract the biased float32 exponent:
```

## Source note 17, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L28)

```text
// 113+ at exponent -14+.
```

## Source note 18, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L29)

```text
// 93 at exponent -34.
```

## Source note 19, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L31)

```text
// Convert exponent to the shift amount.
```

## Source note 20, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L32)

```text
// 116 - 113 = 3.
```

## Source note 21, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L33)

```text
// 116 - 93 = 23.
```

## Source note 22, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_truncate.ps.hlsl#L37)

```text
// The number is not representable as float24 after truncation - zero.
```
