# Stack: ppc source notes

This record preserves technical and API notes moved from `include/rex/ppc/stack.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L27)

```text
// Stack bounds helper
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L30)

```text
/// Read stack_end_ptr from KPCR at r13 + 0x74.
```

## Source note 3, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L31)

```text
/// Returns 0 if r13 is not set (e.g. in unit tests without a live thread).
```

## Source note 4, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L48)

```text
// note(tomc): PPC64 ABI requires 16-byte frame alignment, but r1 is already frame-aligned
```

## Source note 5, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L49)

```text
// on entry; individual pushes round to 8 bytes to maintain doubleword alignment.
```

## Source note 6, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L55)

```text
// Core push/pop (explicit ctx/base)
```

## Source note 7, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L58)

```text
/// Push a byte-swapped scalar onto the guest stack.
```

## Source note 8, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L67)

```text
// Byte-swap and write
```

## Source note 9, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L91)

```text
/// Push a NUL-terminated string onto the guest stack (no byte-swap, raw bytes).
```

## Source note 10, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L102)

```text
/// Push raw bytes onto the guest stack (no byte-swap).
```

## Source note 11, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L112)

```text
/// Pop bytes from the guest stack.
```

## Source note 12, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L118)

```text
// Scope guard
```

## Source note 13, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L121)

```text
/// RAII guard that saves r1 on construction and restores on destruction.
```

## Source note 14, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/stack.h#L136)

```text
// Implicit ctx/base overloads (use current thread context)
```
