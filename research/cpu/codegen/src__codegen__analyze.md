# Analyze: codegen source notes

This record preserves technical and API notes moved from `src/codegen/analyze.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/analyze.cpp#L30)

```text
// Guest code patches go in before anything reads the instructions.
```

## Source note 2, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/analyze.cpp#L47)

```text
// 1. Register entry points (imports, helpers, config, pdata)
```

## Source note 3, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/analyze.cpp#L55)

```text
// 2. Scan binary into code/data regions
```

## Source note 4, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/analyze.cpp#L63)

```text
// 3. Discover function blocks iteratively (includes vtable scan)
```

## Source note 5, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/analyze.cpp#L71)

```text
// 3.5. Function pointer scan: find lis/addi pairs loading code addresses
```

## Source note 6, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/analyze.cpp#L72)

```text
// TODO(tomc): disabled for now, causes too many false positives
```

## Source note 7, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/analyze.cpp#L73)

```text
// functionPointerScan(ctx);
```

## Source note 8, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/analyze.cpp#L75)

```text
// 4. Gap fill uncovered regions + discover blocks for gap-filled functions + cleanup
```

## Source note 9, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/analyze.cpp#L83)

```text
// 5. Merge: resolve jumps and seal functions
```

## Source note 10, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/analyze.cpp#L91)

```text
// 6. Validate
```

## Source note 11, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/analyze.cpp#L106)

```text
// AnalysisErrors implementation
```

## Source note 12, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/analyze.cpp#L146)

```text
// Group by category
```
