# Xmp app: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xam/apps/xmp_app.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L40)

```text
// Some stupid games will hammer this on a thread - induce a delay
```

## Source note 2, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L41)

```text
// here to keep from starving real threads.
```

## Source note 3, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L137)

```text
// Start playlist?
```

## Source note 4, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L207)

```text
// NOTE: buffer_length may be zero or valid.
```

## Source note 5, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L214)

```text
// 0?
```

## Source note 6, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L273)

```text
// out ptr to 4b - expect 0
```

## Source note 7, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L328)

```text
// dummy_alloc_ptr is the result of a XamAlloc of storage_size.
```

## Source note 8, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L338)

```text
// 0
```

## Source note 9, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L412)

```text
// Atrain spawns a thread 82437FD0 to call this in a tight loop forever.
```

## Source note 10, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L448)

```text
// Query of size for XamAlloc - the result of the alloc is passed to
```

## Source note 11, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L449)

```text
// 0x0007000D.
```

## Source note 12, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L458)

```text
// We don't use the storage, so just fudge the number.
```

## Source note 13, line 464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xmp_app.cpp#L464)

```text
// XMPCaptureOutput - not sure how this works :/
```
