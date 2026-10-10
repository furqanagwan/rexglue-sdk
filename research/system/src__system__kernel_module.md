# Kernel module: system source notes

This record preserves technical and API notes moved from `src/system/kernel_module.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_module.cpp#L31)

```text
// Persist this object through reloads.
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_module.cpp#L40)

```text
// Look up the export in the resolver
```

## Source note 3, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_module.cpp#L48)

```text
// Variables have guest addresses we can return directly
```

## Source note 4, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_module.cpp#L58)

```text
// Check thunk cache first (already allocated for this caller's module)
```

## Source note 5, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_module.cpp#L66)

```text
// Look up native implementation by name from the auto-registry
```

## Source note 6, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_module.cpp#L80)

```text
// No native implementation available
```
