# Xboxkrnl modules: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_modules.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L29)

```text
// DWORD Privilege
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L31)

```text
// Privilege is bit position in xe_xex2_system_flags enum - so:
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L32)

```text
// Privilege=6 -> 0x00000040 -> XEX_SYSTEM_INSECURE_SOCKETS
```

## Source note 4, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L60)

```text
// NOTE: we don't retain the handle for return.
```

## Source note 5, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L92)

```text
// Lookup + load_count++ must be atomic vs XexUnloadImage to prevent
```

## Source note 6, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L93)

```text
// resurrecting a module between the read of hmodule and the increment.
```

## Source note 7, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L94)

```text
// The fresh-load path can't share this lock: LoadUserModule runs
```

## Source note 8, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L95)

```text
// DllMain ATTACH outside the global lock by design.
```

## Source note 9, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L109)

```text
// Released by the last XexUnloadImage call.
```

## Source note 10, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L133)

```text
// Decrement-and-check under the global lock so concurrent unloads can't both
```

## Source note 11, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L134)

```text
// observe zero and double-free.
```

## Source note 12, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L152)

```text
// May be entry point?
```

## Source note 13, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L203)

```text
// Adding.
```

## Source note 14, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_modules.cpp#L207)

```text
// Removing.
```
