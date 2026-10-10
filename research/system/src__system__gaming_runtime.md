# Gaming runtime: system source notes

This record preserves technical and API notes moved from `src/system/gaming_runtime.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/gaming_runtime.cpp#L28)

```text
// XGameErr.h, restated so this file needs no GDK header in standard builds.
```

## Source note 2, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/gaming_runtime.cpp#L36)

```text
// E_GAMEPACKAGE_CONFIG_NO_ROOT_NODE .. E_GAMEPACKAGE_CONFIG_x64_EXECUTABLE_REQUIRED
```

## Source note 3, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/gaming_runtime.cpp#L39)

```text
// HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND)
```

## Source note 4, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/gaming_runtime.cpp#L226)

```text
// Nobody will uninitialize a success the caller already gave up on.
```

## Source note 5, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/gaming_runtime.cpp#L250)

```text
// File errors are reported unchanged, so a missing config file surfaces here.
```
