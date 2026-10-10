# Project recompiler: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/project_recompiler.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/project_recompiler.h#L24)

```text
// empty = all
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/project_recompiler.h#L29)

```text
/// Bypass the stamp gate and regenerate every targeted module.
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/project_recompiler.h#L32)

```text
/// Folded into the input fingerprint. Must be stable across commits
```

## Source note 4, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/project_recompiler.h#L33)

```text
/// ("0.10.0-dev") or every SDK rebuild forces a full re-analysis.
```

## Source note 5, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/project_recompiler.h#L42)

```text
/**
   * Aggregated basenames of files removed across all modules during the most
   * recent Run() call. Empty until Run() completes successfully.
   */
```

## Source note 6, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/project_recompiler.h#L48)

```text
/**
   * Aggregated basenames of files written across all modules during the most
   * recent Run() call. Empty until Run() completes successfully.
   */
```

## Source note 7, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/project_recompiler.h#L54)

```text
/// Basenames already up to date across all modules in the last Run().
```

## Source note 8, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/project_recompiler.h#L57)

```text
/// Targets skipped in the last Run() because their stamp still matched.
```

## Source note 9, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/project_recompiler.h#L61)

```text
/// One executable's codegen: the original (with any DLL modules), or one
```

## Source note 10, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/project_recompiler.h#L62)

```text
/// title update ([[title_update]]) with its package mounted as update:.
```

## Source note 11, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/project_recompiler.h#L66)

```text
///< empty for the original
```
