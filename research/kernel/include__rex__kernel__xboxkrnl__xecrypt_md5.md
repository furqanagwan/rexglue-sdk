# Xecrypt md5: kernel source notes

This record preserves technical and API notes moved from `include/rex/kernel/xboxkrnl/xecrypt_md5.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L20)

```text
// XECRYPT_MD5_STATE as titles allocate and read it: a 32-bit byte count, the
```

## Source note 2, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L21)

```text
// four MD5 words and the partial block, 0x54 bytes like XECRYPT_SHA_STATE.
```

## Source note 3, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L22)

```text
// Quantum of Solace calls XeCryptMd5Final with no output buffer and reads the
```

## Source note 4, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L23)

```text
// digest from the words at offsets 4-16 (its code at 0x8255B7xx), which fixes
```

## Source note 5, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L24)

```text
// the 32-bit count; Xenia Edge's 64-bit count would move them. The words hold
```

## Source note 6, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L25)

```text
// A, B, C and D as big-endian values, as the SHA state holds its words; what
```

## Source note 7, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L26)

```text
// hardware leaves there after Final is not verified.
```

## Source note 8, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L28)

```text
// 0x0, bytes hashed
```

## Source note 9, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L29)

```text
// 0x4, A B C D
```

## Source note 10, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L30)

```text
// 0x14, count % 64 bytes pending
```

## Source note 11, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L37)

```text
// RFC 1321.
```

## Source note 12, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L117)

```text
// Pads, leaves the final words in the state and writes up to 16 digest bytes
```

## Source note 13, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L118)

```text
// (A to D, each little-endian) to `out`.
```

## Source note 14, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L120)

```text
// The 32-bit count limits messages to 4 GB, like XECRYPT_SHA_STATE.
```

## Source note 15, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xboxkrnl/xecrypt_md5.h#L142)

```text
// namespace md5
```
