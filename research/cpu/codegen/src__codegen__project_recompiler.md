# Project recompiler: codegen source notes

This record preserves technical and API notes moved from `src/codegen/project_recompiler.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/project_recompiler.cpp#L152)

```text
// The build's codegen rule tracks one stamp and depfile, in the original's
```

## Source note 2, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/project_recompiler.cpp#L153)

```text
// output, so every pass's inputs and fingerprints go into them.
```

## Source note 3, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/project_recompiler.cpp#L181)

```text
// Never WriteIfChanged: the build rule re-runs until this mtime passes its inputs.
```

## Source note 4, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/project_recompiler.cpp#L254)

```text
// Two binaries sharing an out_directory_path would clobber each other's
```

## Source note 5, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/project_recompiler.cpp#L255)

```text
// sources.cmake on emit (the writer's cleanup sweep is unprefixed for
```

## Source note 6, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/project_recompiler.cpp#L256)

```text
// that file).
```

## Source note 7, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/project_recompiler.cpp#L281)

```text
// gameRoot anchors VFS root and DLL guest_path derivation. Honor the
```

## Source note 8, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/project_recompiler.cpp#L282)

```text
// manifest override if set; otherwise default to the entrypoint's parent.
```

## Source note 9, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/project_recompiler.cpp#L317)

```text
// A title update build loads the executable patched by that update.
```

## Source note 10, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/project_recompiler.cpp#L437)

```text
// a changed update regenerates
```

## Source note 11, line 491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/project_recompiler.cpp#L491)

```text
// Each module's dispatch table, clear of every module's image (RG-GDK-070).
```
