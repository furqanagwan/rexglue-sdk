# Crt jump scanner: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/crt_jump_scanner.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 11

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/crt_jump_scanner.h#L11)

```text
// Candidates only: recognizing the CRT does not establish that every caller
```

## Source note 2, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/crt_jump_scanner.h#L12)

```text
// can safely use the native non-local-jump implementation.
```

## Source note 3, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/crt_jump_scanner.h#L20)

```text
// Fill missing addresses only for a unique pair consistent with explicit hints.
```
