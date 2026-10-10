# Bit: core source notes

This record preserves technical and API notes moved from `include/rex/bit.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L29)

```text
// BitMap - Efficient lookup of free/used entries
```

## Source note 2, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L36)

```text
// Size is the number of entries, must be a multiple of 64.
```

## Source note 3, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L39)

```text
// Data does not have to be aligned to a 4-byte boundary, but it is
```

## Source note 4, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L40)

```text
// preferable.
```

## Source note 5, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L41)

```text
// Size is the number of entries, must be a multiple of 64.
```

## Source note 6, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L44)

```text
// (threadsafe) Acquires an entry and returns its index. Returns -1 if there
```

## Source note 7, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L45)

```text
// are no more free entries.
```

## Source note 8, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L48)

```text
// (threadsafe) Releases an entry by an index.
```

## Source note 9, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L51)

```text
// Resize the bitmap. Size is the number of entries, must be a multiple of 64.
```

## Source note 10, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L54)

```text
// Sets all entries to free.
```

## Source note 11, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L67)

```text
// Bit Range Utilities
```

## Source note 12, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L70)

```text
// Provided length is in bits since the first. Returns <first, length> of the
```

## Source note 13, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L71)

```text
// range in bits, with length == 0 if not found.
```

## Source note 14, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L84)

```text
// Ignore bits in the block outside the specified range by considering them
```

## Source note 15, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L85)

```text
// set.
```

## Source note 16, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L95)

```text
// Check if need to open a new range.
```

## Source note 17, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L101)

```text
// Check if need to close the range.
```

## Source note 18, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/bit.h#L102)

```text
// Ignore the set bits before the beginning of the range.
```
