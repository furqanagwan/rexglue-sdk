# Output partition: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/output_partition.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_partition.h#L32)

```text
/// Pins each guest function to a recomp file across runs.
```

## Source note 2, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_partition.h#L37)

```text
/// One bucket per output file, holding indices into `entries`. The file count
```

## Source note 3, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_partition.h#L38)

```text
/// is derived from `maxFileBytes` and persisted, so growth alone does not
```

## Source note 4, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_partition.h#L39)

```text
/// reshuffle the emitted set; a new `maxFileBytes` repartitions from scratch.
```

## Source note 5, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_partition.h#L40)

```text
/// Call Serialize() after.
```
