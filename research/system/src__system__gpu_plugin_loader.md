# Gpu plugin loader: system source notes

This record preserves technical and API notes moved from `src/system/gpu_plugin_loader.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/gpu_plugin_loader.cpp#L29)

```text
// Plugin binaries follow the SDK's per-config postfix convention; this TU is
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/gpu_plugin_loader.cpp#L30)

```text
// part of rexruntime, so REXGLUE_BUILD_CONFIG matches the plugin's config.
```

## Source note 3, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/gpu_plugin_loader.cpp#L42)

```text
// Plugins stay loaded for process lifetime: guest threads may still be in
```

## Source note 4, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/gpu_plugin_loader.cpp#L43)

```text
// plugin code pages at shutdown.
```
