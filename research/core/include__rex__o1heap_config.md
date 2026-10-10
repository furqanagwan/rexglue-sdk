# O1heap config: core source notes

This record preserves technical and API notes moved from `include/rex/o1heap_config.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 9

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/o1heap_config.h#L9)

```text
// On Windows, unsigned long is 32 bits even on x64.  o1heap.c auto-selects
```

## Source note 2, line 10

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/o1heap_config.h#L10)

```text
// __builtin_clzl under clang-cl (because __clang__ is defined), but that
```

## Source note 3, line 11

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/o1heap_config.h#L11)

```text
// gives a 32-bit CLZ while o1heap needs 64-bit (size_t-width).  This causes
```

## Source note 4, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/o1heap_config.h#L12)

```text
// roundUpToPowerOf2() to produce astronomically large values, corrupting the
```

## Source note 5, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/o1heap_config.h#L13)

```text
// heap bin structure on first allocation.
```
