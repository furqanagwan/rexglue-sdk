# User language: system source notes

This record preserves technical and API notes moved from `include/rex/system/user_language.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 10

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/user_language.h#L10)

```text
// Map a Windows/BCP-47 locale to a language the guest understands. Unsupported
```

## Source note 2, line 11

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/user_language.h#L11)

```text
// locales fall back to English; Chinese script takes priority over region.
```

## Source note 3, line 14

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/user_language.h#L14)

```text
// user_language=0 follows Windows; 1..12 selects an explicit guest language.
```

## Source note 4, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/user_language.h#L15)

```text
// All guest APIs and title metadata must use the same resolved value.
```
