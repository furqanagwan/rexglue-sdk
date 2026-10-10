# Binary view: codegen source notes

This record preserves technical and API notes moved from `src/codegen/binary_view.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/binary_view.cpp#L25)

```text
// Copy metadata
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/binary_view.cpp#L33)

```text
// Copy import symbols and calculate import thunk table start
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/binary_view.cpp#L34)

```text
// The import thunk table (and export table after it) extends to end of .text
```

## Source note 4, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/binary_view.cpp#L38)

```text
// Copy symbol for Register phase to use
```

## Source note 5, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/binary_view.cpp#L41)

```text
// Track minimum address for thunk table range
```

## Source note 6, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/binary_view.cpp#L51)

```text
// Find section containing the import thunk table to determine end of import/export range
```

## Source note 7, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/binary_view.cpp#L64)

```text
// Copy section data
```

## Source note 8, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/binary_view.cpp#L72)

```text
// Skip sections not mapped into memory
```

## Source note 9, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/binary_view.cpp#L77)

```text
// Skip sections that extend beyond the loaded image
```

## Source note 10, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/binary_view.cpp#L84)

```text
// Copy name
```

## Source note 11, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/binary_view.cpp#L87)

```text
// Copy bytes
```

## Source note 12, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/binary_view.cpp#L90)

```text
// Create view pointing into our owned data
```
