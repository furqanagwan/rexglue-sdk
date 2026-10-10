# Function table layout: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/function_table_layout.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_table_layout.h#L22)

```text
/// The guest address of each module's function dispatch table. A table holds
```

## Source note 2, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_table_layout.h#L23)

```text
/// a host pointer per 4 bytes of code: (code size + thunk reserve) * 2 bytes,
```

## Source note 3, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_table_layout.h#L24)

```text
/// bounded here by the image size. It goes right after its image, as it
```

## Source note 4, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_table_layout.h#L25)

```text
/// always has, unless that would overlap another module's image or table;
```

## Source note 5, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_table_layout.h#L26)

```text
/// then it goes after the highest image or table, on a 64 KiB boundary. FIFA Street's launcher
```

## Source note 6, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_table_layout.h#L27)

```text
/// (82000000, 1.75 MiB) would put its table across its game DLL's image at 82300000.
```

## Source note 7, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_table_layout.h#L42)

```text
// First every table that fits right after its own image, then the rest
```

## Source note 8, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_table_layout.h#L43)

```text
// after everything placed so far.
```
