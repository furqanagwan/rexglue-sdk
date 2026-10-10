# Hook: core source notes

This record preserves technical and API notes moved from `include/rex/hook.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L28)

```text
// Hook Macros
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L31)

```text
// Hook a recompiled function with an auto-marshaled native C++ function.
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L32)

```text
// The native function uses plain types (u32, mapped_u32, etc.) and
```

## Source note 4, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L33)

```text
// HostToGuestFunction handles register translation automatically.
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L48)

```text
// Define a raw hook with direct ctx/base access.
```

## Source note 6, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L51)

```text
// Stub: logs a warning when called.
```

## Source note 7, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L71)

```text
// Export: hook + register in global registry for kernel ordinal lookup.
```

## Source note 8, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L87)

```text
// CallFrame - Lightweight isolated calling context
```

## Source note 9, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L89)

```text
// For side calls that must not disturb the outer hook's register state.
```

## Source note 10, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L90)

```text
// Stack-allocated, NOT zero-initialized. Only copies the registers a callee
```

## Source note 11, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L91)

```text
// actually needs from the parent context.
```

## Source note 12, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L116)

```text
// ImportFunction - Zero-overhead typed callable for recompiled functions
```

## Source note 13, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L146)

```text
/// Auto-isolating call: retrieves ctx/base internally, creates isolated
```

## Source note 14, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L147)

```text
/// context with 0x70 frame, calls function, returns result.
```

## Source note 15, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L185)

```text
// StackFrame - RAII guest stack allocation
```

## Source note 16, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L223)

```text
// REX_IMPORT - Typed callable import of a recompiled function
```

## Source note 17, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L225)

```text
// Three explicit arguments, no hidden prefix transformations:
```

## Source note 18, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L226)

```text
//   symbol:   the exact linker symbol to reference
```

## Source note 19, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L227)

```text
//   callable: the name of the typed callable variable
```

## Source note 20, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L228)

```text
//   sig:      the function signature (e.g. u32(u32, u32))
```

## Source note 21, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L230)

```text
// The callable is internal-linkage on purpose: on ELF, a namespace-scope C++
```

## Source note 22, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L231)

```text
// variable is not name-mangled, so an external-linkage callable named after a
```

## Source note 23, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L232)

```text
// guest function would collide with the generated weak function alias and
```

## Source note 24, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L233)

```text
// hijack its function table entry (MSVC decorates variables, hiding the bug).
```

## Source note 25, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hook.h#L242)

```text
// Legacy Compat Aliases
```
