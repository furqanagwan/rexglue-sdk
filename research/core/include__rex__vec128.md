# Vec128: core source notes

This record preserves technical and API notes moved from `include/rex/vec128.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L22)

```text
// The first rule of vector programming is to only rely on exact positions
```

## Source note 2, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L23)

```text
// when absolutely required - prefer dumb loops to exact offsets.
```

## Source note 3, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L24)

```text
// Vectors in memory are laid out as in AVX registers on little endian
```

## Source note 4, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L25)

```text
// machines. Note that little endian is dumb, so the byte at index 0 in
```

## Source note 5, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L26)

```text
// the vector is is really byte 15 (or the high byte of short 7 or int 3).
```

## Source note 6, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L27)

```text
// Because of this, all byte access should be via the accessors instead of
```

## Source note 7, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L28)

```text
// the direct array.
```

## Source note 8, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L30)

```text
// Altivec big endian layout:         AVX little endian layout:
```

## Source note 9, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L32)

```text
// | int32 0 | int16 0 | int8  0 |    | int32 3 | int16 7 | int8 15 |
```

## Source note 10, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L34)

```text
// |         |         | int8  1 |    |         |         | int8 14 |
```

## Source note 11, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L36)

```text
// |         | int16 1 | int8  2 |    |         | int16 6 | int8 13 |
```

## Source note 12, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L38)

```text
// |         |         | int8  3 |    |         |         | int8 12 |
```

## Source note 13, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L40)

```text
// | int32 1 | int16 2 | int8  4 |    | int32 2 | int16 5 | int8 11 |
```

## Source note 14, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L42)

```text
// |         |         | int8  5 |    |         |         | int8 10 |
```

## Source note 15, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L44)

```text
// |         | int16 3 | int8  6 |    |         | int16 4 | int8  9 |
```

## Source note 16, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L46)

```text
// |         |         | int8  7 |    |         |         | int8  8 |
```

## Source note 17, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L48)

```text
// | int32 2 | int16 4 | int8  8 |    | int32 1 | int16 3 | int8  7 |
```

## Source note 18, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L50)

```text
// |         |         | int8  9 |    |         |         | int8  6 |
```

## Source note 19, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L52)

```text
// |         | int16 5 | int8 10 |    |         | int16 2 | int8  5 |
```

## Source note 20, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L54)

```text
// |         |         | int8 11 |    |         |         | int8  4 |
```

## Source note 21, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L56)

```text
// | int32 3 | int16 6 | int8 12 |    | int32 0 | int16 1 | int8  3 |
```

## Source note 22, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L58)

```text
// |         |         | int8 13 |    |         |         | int8  2 |
```

## Source note 23, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L60)

```text
// |         | int16 7 | int8 14 |    |         | int16 0 | int8  1 |
```

## Source note 24, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L62)

```text
// |         |         | int8 15 |    |         |         | int8  0 |
```

## Source note 25, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L65)

```text
// Logical order:
```

## Source note 26, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L67)

```text
// |  X  |  Y  |  Z  |  W  |          |  W  |  Z  |  Y  |  X  |
```

## Source note 27, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L70)

```text
// Mapping indices is easy:
```

## Source note 28, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L71)

```text
// int32[i ^ 0x3]
```

## Source note 29, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L72)

```text
// int16[i ^ 0x7]
```

## Source note 30, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/vec128.h#L73)

```text
//  int8[i ^ 0xF]
```
