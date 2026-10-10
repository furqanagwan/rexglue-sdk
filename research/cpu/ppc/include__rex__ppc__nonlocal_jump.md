# Nonlocal jump: ppc source notes

This record preserves technical and API notes moved from `include/rex/ppc/nonlocal_jump.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/nonlocal_jump.h#L13)

```text
// Windows native non-local jumps only. setjmp MUST execute in the generated
```

## Source note 2, line 14

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/nonlocal_jump.h#L14)

```text
// caller, never inside a helper that returns. Generated callers keep all guest
```

## Source note 3, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/nonlocal_jump.h#L15)

```text
// registers in ctx: native automatic locals are not restored by longjmp.
```

## Source note 4, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/nonlocal_jump.h#L60)

```text
// Restore AFTER the native unwind: skipped frame destructors may modify ctx.
```

## Source note 5, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/nonlocal_jump.h#L73)

```text
// Generated callers restore from heap state after resuming, so setjmp is
```

## Source note 6, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/nonlocal_jump.h#L74)

```text
// a controlling expression, with no modified native local result.
```

## Source note 7, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/nonlocal_jump.h#L79)

```text
// Keep mutable snapshots off the native stack. Multiple buffers saved by the
```

## Source note 8, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/nonlocal_jump.h#L80)

```text
// same generated function must not overwrite a shared automatic PPCContext.
```
