# Xgi app: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xam/apps/xgi_app.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L26)

```text
// http://mb.mirage.org/bugzilla/xliveless/main.c
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L30)

```text
// NOTE: buffer_length may be zero or valid.
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L35)

```text
// dword r3 user index
```

## Source note 4, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L36)

```text
// dword (unwritten?)
```

## Source note 5, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L37)

```text
// qword 0
```

## Source note 6, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L38)

```text
// dword r4 context enum
```

## Source note 7, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L39)

```text
// dword r5 value
```

## Source note 8, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L57)

```text
// Raw dump so we can confirm the actual buffer layout the game sends.
```

## Source note 9, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L67)

```text
// Empirically confirmed from log: each entry is {u32 padding/user_index, u32 id, ...}.
```

## Source note 10, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L68)

```text
// The achievement ID sits at offset 4, not 0. Stride 8 covers the observed fields.
```

## Source note 11, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L99)

```text
// - XamSessionCreateHandle
```

## Source note 12, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L100)

```text
// - XamSessionRefObjByHandle
```

## Source note 13, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L101)

```text
// - [this]
```

## Source note 14, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L102)

```text
// - CloseHandle
```

## Source note 15, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L155)

```text
// send high scores?
```

## Source note 16, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L266)

```text
// 300
```

## Source note 17, line 362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L362)

```text
// Called after opening xbox live arcade and clicking on xbox live v5759
```

## Source note 18, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L363)

```text
// to 5787 and called after clicking xbox live in the game library from
```

## Source note 19, line 364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L364)

```text
// v6683 to v6717
```

## Source note 20, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L365)

```text
// Does not get sent a buffer
```

## Source note 21, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xgi_app.cpp#L384)

```text
// 00000000 2789fecc 00000000 00000000 200491e0 00000000 200491f0 20049340
```
