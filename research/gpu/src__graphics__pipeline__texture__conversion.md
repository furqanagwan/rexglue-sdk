# Conversion: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/texture/conversion.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/conversion.cpp#L36)

```text
// Swap high and low 16 bits within a 32 bit
```

## Source note 2, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/conversion.cpp#L48)

```text
// https://fileadmin.cs.lth.se/cs/Personal/Michael_Doggett/talks/unc-xenos-doggett.pdf
```

## Source note 3, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/conversion.cpp#L49)

```text
// (R is in the higher bits, according to how this format is used in
```

## Source note 4, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/conversion.cpp#L50)

```text
//  4D5307E6).
```

## Source note 5, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/conversion.cpp#L87)

```text
// https://github.com/BinomialLLC/crunch/blob/ea9b8d8c00c8329791256adafa8cf11e4e7942a2/inc/crn_decomp.h#L4108
```

## Source note 6, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/conversion.cpp#L114)

```text
// Bytes per pixel
```

## Source note 7, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/conversion.cpp#L118)

```text
// Offset to the current row, in bytes.
```

## Source note 8, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/conversion.cpp#L124)

```text
// Go block-by-block on this row.
```
