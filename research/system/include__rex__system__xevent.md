# Xevent: system source notes

This record preserves technical and API notes moved from `include/rex/system/xevent.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xevent.h#L21)

```text
// https://www.nirsoft.net/kernel_struct/vista/KEVENT.html
```

## Source note 2, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xevent.h#L55)

```text
// Writes the guest header's signal state and host_signaled_; state_lock_
```

## Source note 3, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xevent.h#L56)

```text
// held.
```

## Source note 4, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xevent.h#L62)

```text
// The guest dispatch header mirrors the host event (Canary #1227): what the
```

## Source note 5, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xevent.h#L63)

```text
// kernel last wrote there, so a different value was written by the guest.
```
