# Map parser: system source notes

This record preserves technical and API notes moved from `include/rex/system/map_parser.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/map_parser.h#L25)

```text
/**
 * Options for parsing map files.
 */
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/map_parser.h#L29)

```text
/// Base address to add to all symbol addresses (for relative maps)
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/map_parser.h#L32)

```text
/// If true, only parse symbols that look like functions
```

## Source note 4, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/map_parser.h#L35)

```text
/// If non-empty, only include symbols whose names start with this prefix
```

## Source note 5, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/map_parser.h#L39)

```text
/**
 * Error types for map parsing operations.
 */
```

## Source note 6, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/map_parser.h#L44)

```text
/**
 * Get a human-readable string for a MapParseError.
 */
```

## Source note 7, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/map_parser.h#L61)

```text
/**
 * Parse an nm-style map file (format: "address type name").
 *
 * This is the format produced by `nm` on Unix systems:
 *   00000000 t test_add1
 *   00000010 T test_sub1
 *
 * Symbol types:
 *   T/t = text (code)
 *   D/d = data
 *   B/b = bss
 *   U   = undefined
 *
 * @param map_path    Path to the .map file
 * @param options     Parsing options (base address, filters)
 * @return            Vector of parsed symbols or error
 */
```

## Source note 8, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/map_parser.h#L81)

```text
/**
 * Parse nm-style map data from a string.
 *
 * @param map_data    Map file contents as a string
 * @param options     Parsing options
 * @return            Vector of parsed symbols or error
 */
```
