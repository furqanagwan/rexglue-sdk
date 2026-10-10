# Manifest: codegen source notes

This record preserves technical and API notes moved from `src/codegen/manifest.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/manifest.cpp#L56)

```text
/**
 * Pull file_path / out_directory_path / project_name onto the recompiler
 * config so downstream consumers can rely on them. Other fields (codegen
 * flags, sub-tables, includes) come from RecompilerConfig::LoadFromTable.
 */
```

## Source note 2, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/manifest.cpp#L150)

```text
// [[title_update]]: the entrypoint again, patched by that update's XEX
```

## Source note 3, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/manifest.cpp#L151)

```text
// patches, with its own output directory and includes (its own function
```

## Source note 4, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/manifest.cpp#L152)

```text
// entries, patches and mods: addresses differ between versions).
```

## Source note 5, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/manifest.cpp#L180)

```text
// The entrypoint's settings, with this version's output and includes.
```
