# Primitive cache test: graphics source notes

This record preserves technical and API notes moved from `tests/unit/graphics/primitive_cache_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 2

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/primitive_cache_test.cpp#L2)

```text
// CPU-only coverage of the real primitive converter and memory watch contract.
```

## Source note 2, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/primitive_cache_test.cpp#L86)

```text
// Borrowed allocator; this guard owns the region.
```

## Source note 3, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/primitive_cache_test.cpp#L89)

```text
// Declared first so watches unregister before the region is released, also
```

## Source note 4, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/primitive_cache_test.cpp#L90)

```text
// if the rest of fixture initialization fails.
```

## Source note 5, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/primitive_cache_test.cpp#L231)

```text
// Exercise the actual physical-memory watch dispatch, not only the converter callback.
```
