# Storage seed test: graphics source notes

This record preserves technical and API notes moved from `tests/unit/graphics/storage_seed_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/storage_seed_test.cpp#L33)

```text
// A shader record: hash, dword count and type, ucode.
```

## Source note 2, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/storage_seed_test.cpp#L42)

```text
// the type bit
```

## Source note 3, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/storage_seed_test.cpp#L48)

```text
// A fixed-size pipeline record: hash, then 24 bytes it covers.
```

## Source note 4, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/storage_seed_test.cpp#L96)

```text
// Nothing new the second time.
```

## Source note 5, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/storage_seed_test.cpp#L101)

```text
// Nothing shipped.
```

## Source note 6, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/storage_seed_test.cpp#L110)

```text
// The player has shader 2 and their own 9, then a cut-off record.
```

## Source note 7, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/storage_seed_test.cpp#L131)

```text
// The player's from an older SDK: the pipeline cache would throw it away.
```

## Source note 8, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/storage_seed_test.cpp#L151)

```text
// Reading stops at the damaged record, as the pipeline cache's does.
```
