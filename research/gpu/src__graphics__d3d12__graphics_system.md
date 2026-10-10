# Graphics system: graphics source notes

This record preserves technical and API notes moved from `src/graphics/d3d12/graphics_system.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/graphics_system.cpp#L40)

```text
/*with_presentation*/
```

## Source note 2, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/graphics_system.cpp#L41)

```text
// D3D12 doesn't differentiate headless vs. swapchain-capable providers;
```

## Source note 3, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/graphics_system.cpp#L42)

```text
// swapchains are created lazily per-window by the presenter.
```

## Source note 4, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/graphics_system.cpp#L50)

```text
// namespace rex::graphics::d3d12
```
