# Renderdoc api: ui source notes

This record preserves technical and API notes moved from `src/ui/renderdoc_api.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/renderdoc_api.cpp#L23)

```text
// Try to load the RenderDoc library. If RenderDoc is attached, the library
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/renderdoc_api.cpp#L24)

```text
// should already be loaded into the process and this will increment the
```

## Source note 3, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/renderdoc_api.cpp#L25)

```text
// reference count. If not attached, the load will fail and we return nullptr.
```

## Source note 4, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/renderdoc_api.cpp#L31)

```text
// get_api will be null if RenderDoc is not connected, or the API isn't
```

## Source note 5, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/renderdoc_api.cpp#L32)

```text
// available on this platform, or there was an error.
```
