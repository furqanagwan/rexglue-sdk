# Xnotifylistener: system source notes

This record preserves technical and API notes moved from `include/rex/system/xnotifylistener.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xnotifylistener.h#L58)

```text
// The guest closed the listener: stop broadcasting to it, so the kernel's
```

## Source note 2, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xnotifylistener.h#L59)

```text
// reference no longer keeps it (and its queue) alive.
```
