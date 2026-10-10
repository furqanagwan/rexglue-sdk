# Gpu plugin: system source notes

This record preserves technical and API notes moved from `include/rex/system/gpu_plugin.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gpu_plugin.h#L32)

```text
// Bump on any change to GpuCreateInfo or to the IGraphicsSystem interface.
```

## Source note 2, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gpu_plugin.h#L39)

```text
// sizeof(GpuCreateInfo), set by the host
```

## Source note 3, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gpu_plugin.h#L40)

```text
// "d3d12" or "any"
```

## Source note 4, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gpu_plugin.h#L43)

```text
// extern "C" exports every GPU plugin must provide:
```

## Source note 5, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gpu_plugin.h#L44)

```text
//   uint32_t rex_gpu_abi_version(void);
```

## Source note 6, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gpu_plugin.h#L45)

```text
//   rex::system::IGraphicsSystem* rex_gpu_create(uint32_t abi_version,
```

## Source note 7, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gpu_plugin.h#L46)

```text
//                                                const GpuCreateInfo* info);
```

## Source note 8, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gpu_plugin.h#L50)

```text
// Loads rexgpu-<name> from the executable's directory and constructs its
```

## Source note 9, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gpu_plugin.h#L51)

```text
// graphics system. Returns nullptr after logging a detailed error (missing
```

## Source note 10, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gpu_plugin.h#L52)

```text
// file, missing exports, ABI mismatch, or factory failure). The library
```

## Source note 11, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gpu_plugin.h#L53)

```text
// handle is retained for process lifetime; plugins are never unloaded.
```
