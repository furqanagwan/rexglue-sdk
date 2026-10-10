# String: kernel source notes

This record preserves technical and API notes moved from `src/kernel/crt/string.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/string.cpp#L20)

```text
// C string operations
```

## Source note 2, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/string.cpp#L45)

```text
// Non-reentrant per guest libc contract; concurrent guest threads will trample.
```

## Source note 3, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/string.cpp#L59)

```text
// Win32 string functions (lstr*)
```

## Source note 4, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/string.cpp#L67)

```text
// Unbounded by guest contract.
```

## Source note 5, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/string.cpp#L82)

```text
// Unbounded by guest contract.
```

## Source note 6, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/string.cpp#L92)

```text
// C UTF-16 Widestring functions (int16_t*)
```
