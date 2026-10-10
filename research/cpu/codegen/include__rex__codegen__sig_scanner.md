# Sig scanner: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/sig_scanner.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L25)

```text
// Signature - Pattern definition for matching
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L27)

```text
// Dword-based patterns follow PPC's per-instruction size.
```

## Source note 3, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L28)

```text
// Each pattern word is matched against memory using the corresponding mask.
```

## Source note 4, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L29)

```text
// A mask of 0xFFFFFFFF means exact match; partial masks allow wildcards.
```

## Source note 5, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L32)

```text
// e.g., "__savegprlr_14"
```

## Source note 6, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L33)

```text
// Instruction words to match
```

## Source note 7, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L34)

```text
// Bits that must match (0xFFFFFFFF = exact)
```

## Source note 8, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L35)

```text
// Offset from pattern start to entry point
```

## Source note 9, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L36)

```text
// Known size, or nullopt to compute from pattern
```

## Source note 10, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L40)

```text
// SigScanner - Pattern-based signature matcher
```

## Source note 11, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L47)

```text
// Scan for a single signature, return all match entry points
```

## Source note 12, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L50)

```text
// Scan for multiple signatures at once (more efficient - single pass)
```

## Source note 13, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L54)

```text
// Built-in signature sets
```

## Source note 14, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L55)

```text
// __save/__restore helpers
```

## Source note 15, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L56)

```text
// memset, memmove, etc. (future)
```

## Source note 16, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/sig_scanner.h#L61)

```text
// Scan a single range for a pattern
```
