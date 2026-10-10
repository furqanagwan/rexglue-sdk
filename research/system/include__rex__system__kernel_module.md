# Kernel module: system source notes

This record preserves technical and API notes moved from `include/rex/system/kernel_module.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_module.h#L36)

```text
/**
   * Erase any cached thunks whose guest address falls in [lo, hi).
   */
```

## Source note 2, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_module.h#L51)

```text
// Cache of (caller_module_base, ordinal) -> thunk guest address.
```
