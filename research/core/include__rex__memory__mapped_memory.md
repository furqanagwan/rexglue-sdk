# Mapped memory: core source notes

This record preserves technical and API notes moved from `include/rex/memory/mapped_memory.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/mapped_memory.h#L40)

```text
// The mapping is still backed by the object the slice was created from, a
```

## Source note 2, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/mapped_memory.h#L41)

```text
// slice is not owning.
```

## Source note 3, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/mapped_memory.h#L49)

```text
// Close, and optionally truncate file to size
```

## Source note 4, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/mapped_memory.h#L53)

```text
// Changes the offset inside the file. This will update data() and size()!
```
