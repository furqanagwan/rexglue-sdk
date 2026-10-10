# Xecrypt md5 test: kernel source notes

This record preserves technical and API notes moved from `tests/unit/kernel/xecrypt_md5_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/xecrypt_md5_test.cpp#L66)

```text
// Block edges, the 56-byte padding edge and odd sizes.
```

## Source note 2, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/xecrypt_md5_test.cpp#L74)

```text
// Guest memory: the state as a title's stack holds it.
```

## Source note 3, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/xecrypt_md5_test.cpp#L76)

```text
// Just past the state.
```

## Source note 4, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/xecrypt_md5_test.cpp#L80)

```text
// Big-endian byte count at 0.
```

## Source note 5, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/xecrypt_md5_test.cpp#L81)

```text
// Quantum of Solace passes no output buffer and reads the words at 4-16.
```

## Source note 6, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/xecrypt_md5_test.cpp#L83)

```text
// A = 0x98500190 for "abc" (digest bytes 90 01 50 98), stored big-endian.
```
