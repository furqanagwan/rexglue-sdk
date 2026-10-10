# Map parser: system source notes

This record preserves technical and API notes moved from `src/system/map_parser.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L22)

```text
/**
 * Determine symbol type from nm symbol type character.
 */
```

## Source note 2, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L44)

```text
/**
 * Check if nm symbol type indicates a function.
 */
```

## Source note 3, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L57)

```text
// Parse line by line
```

## Source note 4, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L60)

```text
// Find end of line
```

## Source note 5, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L69)

```text
// Skip empty lines
```

## Source note 6, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L73)

```text
// Remove trailing \r if present
```

## Source note 7, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L78)

```text
// nm format: "address type name" (space-separated)
```

## Source note 8, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L79)

```text
// Example: "00000000 t test_add1"
```

## Source note 9, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L81)

```text
// Find first space (after address)
```

## Source note 10, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L86)

```text
// Parse address
```

## Source note 11, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L94)

```text
// Skip whitespace to find type
```

## Source note 12, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L104)

```text
// Skip to name
```

## Source note 13, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L114)

```text
// Apply filters
```

## Source note 14, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L125)

```text
// Create symbol
```

## Source note 15, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L129)

```text
// nm doesn't provide size
```

## Source note 16, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L144)

```text
// Check if file exists
```

## Source note 17, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/map_parser.cpp#L149)

```text
// Read file contents
```
