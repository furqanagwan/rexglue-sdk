# Game media recovery: system source notes

This record preserves technical and API notes moved from `include/rex/system/game_media_recovery.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 9

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/game_media_recovery.h#L9)

```text
// DiscImageDevice serializes Recover calls. Only the failing guest I/O waits;
```

## Source note 2, line 10

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/game_media_recovery.h#L10)

```text
// validation/reopening runs on that worker, never on the UI thread.
```
