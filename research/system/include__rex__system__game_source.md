# Game source: system source notes

This record preserves technical and API notes moved from `include/rex/system/game_source.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/game_source.h#L13)

```text
// XXH3-128 of the original XEX file, not an entitlement.
```

## Source note 2, line 14

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/game_source.h#L14)

```text
// The XDBF display name, for messages; empty when unknown.
```

## Source note 3, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/game_source.h#L23)

```text
// Header-only inspection; encrypted/compressed payloads are not decoded.
```

## Source note 4, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/game_source.h#L25)

```text
// The display name in a whole XEX file's XDBF resource (decrypting and
```

## Source note 5, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/game_source.h#L26)

```text
// decompressing its image), or empty. Safe on arbitrary bytes.
```

## Source note 6, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/game_source.h#L38)

```text
// Copy a validated image to a new folder. Existing destinations are preserved;
```

## Source note 7, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/game_source.h#L39)

```text
// only an owned staging directory is cleaned up on cancellation or failure.
```
