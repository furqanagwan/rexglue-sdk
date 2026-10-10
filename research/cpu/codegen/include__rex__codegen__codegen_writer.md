# Codegen writer: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/codegen_writer.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_writer.h#L28)

```text
/// True for output files this writer owns and may delete.
```

## Source note 2, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_writer.h#L35)

```text
/// Run the full output pipeline: validate, generate, flush, sweep.
```

## Source note 3, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_writer.h#L38)

```text
/**
   * Basenames of stale outputs removed by the sweep that follows the flush.
   * Populated only after write() completes. Empty otherwise.
   */
```

## Source note 4, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_writer.h#L44)

```text
/**
   * Basenames of files written to disk during write() (via FlushPendingWrites).
   * Populated only after write() completes. Empty otherwise.
   */
```

## Source note 5, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_writer.h#L50)

```text
/// Basenames whose on-disk content already matched, so nothing was written.
```

## Source note 6, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_writer.h#L77)

```text
// Convenience accessors
```
