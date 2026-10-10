# Bit stream: core source notes

This record preserves technical and API notes moved from `src/core/bit_stream.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L36)

```text
// FYI: The reason we can't copy more than 57 bits is:
```

## Source note 2, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L37)

```text
// 57 = 7 * 8 + 1 - that can only span a maximum of 8 bytes.
```

## Source note 3, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L38)

```text
// We can't read in 9 bytes (easily), so we limit it.
```

## Source note 4, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L45)

```text
// offset -->
```

## Source note 5, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L46)

```text
// ..[junk]..| target bits |....[junk].............
```

## Source note 6, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L49)

```text
// We need the data in little endian.
```

## Source note 7, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L53)

```text
// Shift right
```

## Source note 8, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L54)

```text
// .....[junk]........| target bits |
```

## Source note 9, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L57)

```text
// AND with mask
```

## Source note 10, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L58)

```text
// ...................| target bits |
```

## Source note 11, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L78)

```text
// Construct a mask
```

## Source note 12, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L83)

```text
// Shift the value left into position.
```

## Source note 13, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L86)

```text
// offset ----->
```

## Source note 14, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L87)

```text
// ....[junk]...| target bits w/ junk |....[junk]......
```

## Source note 15, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L90)

```text
// AND with mask
```

## Source note 16, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L91)

```text
// ....[junk]...| target bits (0) |........[junk]......
```

## Source note 17, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L94)

```text
// OR with val
```

## Source note 18, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L95)

```text
// ....[junk]...| target bits (val) |......[junk]......
```

## Source note 19, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L98)

```text
// Store into the bitstream.
```

## Source note 20, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L101)

```text
// Advance the bitstream forward.
```

## Source note 21, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L113)

```text
// First: Copy the first few bits up to a byte boundary.
```

## Source note 22, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L125)

```text
// Second: Use memcpy for the bytes left.
```

## Source note 23, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L134)

```text
// Third: Copy the last few bits.
```

## Source note 24, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/bit_stream.cpp#L145)

```text
// Return the bit offset to the copied bits.
```
