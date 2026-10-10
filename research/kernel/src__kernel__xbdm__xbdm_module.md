# Xbdm module: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xbdm/xbdm_module.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xbdm/xbdm_module.cpp#L29)

```text
// Register all exported functions.
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xbdm/xbdm_module.cpp#L30)

```text
// #define XE_MODULE_EXPORT_GROUP(m, n) \
//  Register##n##Exports(export_resolver_, kernel_state_);
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xbdm/xbdm_module.cpp#L32)

```text
// #include <rex/kernel/xbdm/module_export_groups.inc>
```

## Source note 4, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xbdm/xbdm_module.cpp#L33)

```text
// #undef XE_MODULE_EXPORT_GROUP
```

## Source note 5, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xbdm/xbdm_module.cpp#L47)

```text
// Build the export table used for resolution.
```
