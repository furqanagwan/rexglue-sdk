# Binary view: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/binary_view.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L26)

```text
/// Lightweight view of a binary section (points into BinaryView's owned data)
```

## Source note 2, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L45)

```text
/// Import symbol from binary (thunk address + name in "libname@ordinal" format)
```

## Source note 3, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L47)

```text
///< Thunk address (bl target)
```

## Source note 4, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L48)

```text
///< "libname@ordinal" format
```

## Source note 5, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L51)

```text
/// Self-contained binary view that owns all section data
```

## Source note 6, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L54)

```text
/// Factory - copies all data from Module
```

## Source note 7, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L57)

```text
// Move-only (owns large buffers)
```

## Source note 8, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L63)

```text
// Section access
```

## Source note 9, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L69)

```text
/// Overwrites `bytes` at `addr` in this view's copy of the image. Only a
```

## Source note 10, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L70)

```text
/// range inside one executable section can be written; returns false (and
```

## Source note 11, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L71)

```text
/// changes nothing) otherwise. Used for codegen-time guest code patches.
```

## Source note 12, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L75)

```text
// Metadata access
```

## Source note 13, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L83)

```text
/// Start of import thunk table (0 if not available)
```

## Source note 14, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L84)

```text
/// Everything from this address to end of .text is import/export tables, not code
```

## Source note 15, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L87)

```text
/// Check if address is in the import thunk/export table range (not real code)
```

## Source note 16, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L88)

```text
/// This range is specifically within .text section, not other executable sections
```

## Source note 17, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L94)

```text
/// Import symbols (thunk addresses + names)
```

## Source note 18, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L101)

```text
// Owned section data
```

## Source note 19, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L113)

```text
///< Start of import thunk table
```

## Source note 20, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L114)

```text
///< End of import/export range (end of .text)
```

## Source note 21, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/binary_view.h#L116)

```text
// Import symbols
```
