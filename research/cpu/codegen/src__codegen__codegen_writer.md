# Codegen writer: codegen source notes

This record preserves technical and API notes moved from `src/codegen/codegen_writer.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L43)

```text
// The text between the quotes of a C string literal holding `text`.
```

## Source note 2, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L76)

```text
// Compute code_base and code_size from binary sections
```

## Source note 3, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L88)

```text
// Build functions JSON array
```

## Source note 4, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L115)

```text
// Build config flags
```

## Source note 5, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L222)

```text
// 32 MB
```

## Source note 6, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L227)

```text
// Convenience accessors
```

## Source note 7, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L255)

```text
// --- Validation gate (from recompile.cpp) ---
```

## Source note 8, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L262)

```text
// --- Output directory setup (from recompile.cpp) ---
```

## Source note 9, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L267)

```text
// --- Everything below from recompiler.cpp recompile() ---
```

## Source note 10, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L271)

```text
// Build sorted function list from graph
```

## Source note 11, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L280)

```text
// Build rexcrt reverse map and rename graph nodes
```

## Source note 12, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L298)

```text
// Generate {project}_pch.h (config + macros, stable enough to precompile)
```

## Source note 13, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L303)

```text
// Generate {project}_funcs.h (every guest function declaration)
```

## Source note 14, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L308)

```text
// Generate {project}_init.h (the full surface, for init.cpp and consumers)
```

## Source note 15, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L313)

```text
// Generate {project}_init.cpp (PPCImageConfig + PPCFuncMappings)
```

## Source note 16, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L318)

```text
// Generate {project}_register.cpp (registration function for hash-based dispatch)
```

## Source note 17, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L324)

```text
// Filter out imports and rexcrt functions before recompilation
```

## Source note 18, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L332)

```text
// Build EmitContext -- resolver is now properly connected
```

## Source note 19, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L369)

```text
// Buckets are address-ordered, so a call can precede its definition.
```

## Source note 20, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L396)

```text
// Generate sources.cmake
```

## Source note 21, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L408)

```text
// Write all buffered files to disk
```

## Source note 22, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/codegen_writer.cpp#L425)

```text
// A swallowed failure would be stamped as success and skipped on the next run.
```
