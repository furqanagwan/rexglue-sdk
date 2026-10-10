# D3d12 provider: ui source notes

This record preserves technical and API notes moved from `src/ui/d3d12/d3d12_provider.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L136)

```text
// PIX's capturer must be in the process before D3D12.dll is.
```

## Source note 2, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L156)

```text
// Load the core libraries.
```

## Source note 3, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L180)

```text
// Load optional D3DCompiler_47.dll.
```

## Source note 4, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L196)

```text
// Load optional dxilconv.dll.
```

## Source note 5, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L213)

```text
// Load optional dxcompiler.dll.
```

## Source note 6, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L233)

```text
// Configure the DXGI debug info queue.
```

## Source note 7, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L251)

```text
// Enable the debug layer.
```

## Source note 8, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L264)

```text
// Enable DRED (Device Removed Extended Data) for diagnosing GPU crashes. It
```

## Source note 9, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L265)

```text
// doesn't need the debug layer, so it can be enabled on its own for runs that
```

## Source note 10, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L266)

```text
// shouldn't pay the debug layer's cost.
```

## Source note 11, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L281)

```text
// Create the DXGI factory.
```

## Source note 12, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L289)

```text
// Choose the adapter.
```

## Source note 13, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L350)

```text
// Record enough to reproduce a GPU result: the exact adapter and user-mode
```

## Source note 14, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L351)

```text
// driver, not only the vendor.
```

## Source note 15, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L367)

```text
// Create the Direct3D 12 device.
```

## Source note 16, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L377)

```text
// Configure the Direct3D 12 debug info queue.
```

## Source note 17, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L384)

```text
// Xbox 360 vertex fetch is explicit in shaders.
```

## Source note 18, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L386)

```text
// Bug in the debug layer (fixed in some version of Windows) - gaps in
```

## Source note 19, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L387)

```text
// render target bindings must be represented with a fully typed RTV
```

## Source note 20, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L388)

```text
// descriptor and DXGI_FORMAT_UNKNOWN in the pipeline state, but older
```

## Source note 21, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L389)

```text
// debug layer versions give a format mismatch error in this case.
```

## Source note 22, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L391)

```text
// Render targets and shader exports don't have to match on the Xbox
```

## Source note 23, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L392)

```text
// 360.
```

## Source note 24, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L394)

```text
// Arbitrary scissor can be specified by the guest, also it can be
```

## Source note 25, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L395)

```text
// explicitly used to disable drawing.
```

## Source note 26, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L397)

```text
// Arbitrary clear values can be specified by the guest.
```

## Source note 27, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L418)

```text
// Create the command queue for graphics.
```

## Source note 28, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L461)

```text
// Get descriptor sizes for each type.
```

## Source note 29, line 466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L466)

```text
// Check if optional features are supported.
```

## Source note 30, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L467)

```text
// D3D12_HEAP_FLAG_CREATE_NOT_ZEROED requires Windows 10 2004 (indicated by
```

## Source note 31, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L468)

```text
// the availability of ID3D12Device8 or D3D12_FEATURE_D3D12_OPTIONS7).
```

## Source note 32, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L510)

```text
// The runtime rejects a shader model newer than it knows with E_INVALIDARG,
```

## Source note 33, line 511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L511)

```text
// so step down until the query succeeds.
```

## Source note 34, line 556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L556)

```text
// Get the graphics analysis interface, will silently fail if PIX is not
```

## Source note 35, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L557)

```text
// attached.
```

## Source note 36, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_provider.cpp#L572)

```text
// namespace rex::ui::d3d12
```
