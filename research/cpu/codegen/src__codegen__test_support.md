# Test support: codegen source notes

This record preserves technical and API notes moved from `src/codegen/test_support.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L32)

```text
// --- TestModule ---
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L40)

```text
// Populate binary section for FunctionScanner to read instructions
```

## Source note 3, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L53)

```text
// --- AnalyzeTestBinary ---
```

## Source note 4, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L58)

```text
// Extract only test_ prefixed symbols as function entry points
```

## Source note 5, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L61)

```text
// Synthetic non-local-jump fixtures exercise the production call emitter
```

## Source note 6, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L62)

```text
// without embedding a proprietary CRT in the instruction test corpus.
```

## Source note 7, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L72)

```text
// Sort by address
```

## Source note 8, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L75)

```text
// First pass: add all functions and transition through state machine
```

## Source note 9, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L79)

```text
// Size extends to next test_ function or end of binary
```

## Source note 10, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L89)

```text
// kRegistered -> kDiscovered -> kSealed
```

## Source note 11, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L96)

```text
// Second pass: scan for bl instructions and register resolved call edges
```

## Source note 12, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L105)

```text
// Scan each instruction in this function
```

## Source note 13, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/test_support.cpp#L111)

```text
// Check for bl (branch with link = function call)
```
