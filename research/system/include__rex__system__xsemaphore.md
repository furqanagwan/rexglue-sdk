# Xsemaphore: system source notes

This record preserves technical and API notes moved from `include/rex/system/xsemaphore.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsemaphore.h#L52)

```text
// Writes host_count_ to the guest header; count_lock_ held.
```

## Source note 2, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsemaphore.h#L58)

```text
// The guest header's signal state mirrors the host count (Canary #1227).
```
