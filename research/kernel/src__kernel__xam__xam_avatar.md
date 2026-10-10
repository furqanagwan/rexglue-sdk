# Xam avatar: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xam/xam_avatar.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_avatar.cpp#L23)

```text
// 1, 4, etc
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_avatar.cpp#L24)

```text
// 0 or 1
```

## Source note 3, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_avatar.cpp#L25)

```text
// for thread creation?
```

## Source note 4, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_avatar.cpp#L26)

```text
// 20b, 5 pointers
```

## Source note 5, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_avatar.cpp#L27)

```text
// ptr in data segment
```

## Source note 6, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_avatar.cpp#L28)

```text
// flags - 0x00300000, 0x30, etc
```

## Source note 7, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_avatar.cpp#L30)

```text
// Negative to fail. Game should immediately call XamAvatarShutdown.
```

## Source note 8, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_avatar.cpp#L35)

```text
// No-op.
```
