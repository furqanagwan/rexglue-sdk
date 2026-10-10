# String: core source notes

This record preserves technical and API notes moved from `include/rex/string.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string.h#L54)

```text
// Caller must free() the returned pointer.
```

## Source note 2, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string.h#L91)

```text
// No in-buffer NUL terminator. Caller must zero the buffer (or rely on
```

## Source note 3, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string.h#L92)

```text
// adjacent padding bytes) to terminate.
```
