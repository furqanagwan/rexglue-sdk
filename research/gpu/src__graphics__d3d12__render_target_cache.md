# Render target cache: graphics source notes

This record preserves technical and API notes moved from `src/graphics/d3d12/render_target_cache.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L52)

```text
// Generated with `xb buildshaders`.
```

## Source note 2, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L183)

```text
// As of April 2021 (driver version 27.20.0100.9316), on Intel (tested on
```

## Source note 3, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L184)

```text
// UHD Graphics 630), the "always" stencil comparison function isn't working
```

## Source note 4, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L185)

```text
// properly, so clears in the Xbox 360's Direct3D 9 don't work. Forcing ROV
```

## Source note 5, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L186)

```text
// there.
```

## Source note 6, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L188)

```text
// The ROV path is currently much slower generally.
```

## Source note 7, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L194)

```text
// The AMD shader compiler crashes very often with Xenia's custom
```

## Source note 8, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L195)

```text
// output-merger code as of March 2021.
```

## Source note 9, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L208)

```text
// Create the buffer for reinterpreting EDRAM contents.
```

## Source note 10, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L214)

```text
// The first operation will likely be depth self-comparison with host render
```

## Source note 11, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L215)

```text
// targets or drawing with ROV.
```

## Source note 12, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L217)

```text
// Creating zeroed for stable initial value with ROV (though on a real
```

## Source note 13, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L218)

```text
// console it has to be cleared anyway probably) and not to leak irrelevant
```

## Source note 14, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L219)

```text
// data when not covered by host render targets entirely.
```

## Source note 15, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L230)

```text
// Create non-shader-visible descriptors of the EDRAM buffer for copying.
```

## Source note 16, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L289)

```text
// Create the resolve copying root signature.
```

## Source note 17, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L291)

```text
// Parameter 0 is constants.
```

## Source note 18, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L295)

```text
// Binding all of the shared memory at 1x resolution, portions with scaled
```

## Source note 19, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L296)

```text
// resolution.
```

## Source note 20, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L302)

```text
// Parameter 1 is the destination (shared memory).
```

## Source note 21, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L313)

```text
// Parameter 2 is the source (EDRAM).
```

## Source note 22, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L339)

```text
// Direct resolve currently shares the root signature shape with the resolve
```

## Source note 23, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L340)

```text
// copy pass (constants + destination UAV + source SRV) and may diverge later.
```

## Source note 24, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L346)

```text
// Create the resolve copying pipelines.
```

## Source note 25, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L351)

```text
// Somewhat verification whether resolve_copy_shaders_ is up to date.
```

## Source note 26, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L373)

```text
// Using the cvar on emulator initialization so used pipelines are consistent
```

## Source note 27, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L374)

```text
// across different titles launched in one emulator instance.
```

## Source note 28, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L384)

```text
// Host render targets.
```

## Source note 29, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L391)

```text
// Check if 2x MSAA is supported or needs to be emulated with 4x MSAA
```

## Source note 30, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L392)

```text
// instead.
```

## Source note 31, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L406)

```text
// For ownership transfer.
```

## Source note 32, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L455)

```text
// Create null render target descriptors for gaps, must be fully typed
```

## Source note 33, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L456)

```text
// (though in pipeline states, DXGI_FORMAT_UNKNOWN must be used instead -
```

## Source note 34, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L457)

```text
// this would also cause a mismatching format error in the debug layer, but
```

## Source note 35, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L458)

```text
// it's a bug in the debug layer itself - needs to be suppressed, and
```

## Source note 36, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L459)

```text
// already fixed in some version of Windows).
```

## Source note 37, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L467)

```text
// The format doesn't matter, but it must be bindable as a render target,
```

## Source note 38, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L468)

```text
// not DXGI_FORMAT_UNKNOWN.
```

## Source note 39, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L477)

```text
// For host depth -> same depth transfers, host depth storing root signature
```

## Source note 40, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L478)

```text
// and pipelines.
```

## Source note 41, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L481)

```text
// Constants.
```

## Source note 42, line 490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L490)

```text
// Source.
```

## Source note 43, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L504)

```text
// Destination.
```

## Source note 44, line 518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L518)

```text
// Root signature.
```

## Source note 45, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L534)

```text
// Pipelines.
```

## Source note 46, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L535)

```text
// 1 sample.
```

## Source note 47, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L549)

```text
// 2 samples.
```

## Source note 48, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L563)

```text
// 4 samples.
```

## Source note 49, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L578)

```text
// Transfer and clear vertex buffer, for quads of up to tile granularity.
```

## Source note 50, line 584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L584)

```text
// Transfer root signatures.
```

## Source note 51, line 618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L618)

```text
// Stencil mask constant.
```

## Source note 52, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L631)

```text
// Color SRV.
```

## Source note 53, line 640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L640)

```text
// Depth SRV.
```

## Source note 54, line 649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L649)

```text
// Stencil SRV.
```

## Source note 55, line 659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L659)

```text
// Address constant.
```

## Source note 56, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L671)

```text
// Host depth SRV.
```

## Source note 57, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L682)

```text
// Host depth address constant.
```

## Source note 58, line 710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L710)

```text
// Dumping root signatures.
```

## Source note 59, line 734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L734)

```text
// Offsets.
```

## Source note 60, line 743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L743)

```text
// Source.
```

## Source note 61, line 751

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L751)

```text
// Stencil.
```

## Source note 62, line 760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L760)

```text
// Pitches.
```

## Source note 63, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L769)

```text
// EDRAM.
```

## Source note 64, line 803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L803)

```text
// k_32_FLOAT and k_32_32_FLOAT clear root signature and pipelines.
```

## Source note 65, line 844

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L844)

```text
// Using sample 0 as 0 and 3 as 1 for 2x instead.
```

## Source note 66, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L869)

```text
// FXC-compiled depth / stencil dumping shader is ~2 KB, reserve 4 KB for
```

## Source note 67, line 870

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L870)

```text
// some additional space.
```

## Source note 68, line 873

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L873)

```text
// Pixel shader interlock (rasterizer-ordered view).
```

## Source note 69, line 875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L875)

```text
// Blending is done in linear space directly in shaders.
```

## Source note 70, line 878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L878)

```text
// Always true float24 depth rounded to the nearest even.
```

## Source note 71, line 882

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L882)

```text
// Only ForcedSampleCount, which doesn't support 2x.
```

## Source note 72, line 885

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L885)

```text
// Create the resolve EDRAM buffer clearing root signature.
```

## Source note 73, line 887

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L887)

```text
// Parameter 0 is constants.
```

## Source note 74, line 891

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L891)

```text
// Binding all of the shared memory at 1x resolution, portions with scaled
```

## Source note 75, line 892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L892)

```text
// resolution.
```

## Source note 76, line 896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L896)

```text
// Parameter 1 is the destination (EDRAM).
```

## Source note 77, line 925

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L925)

```text
// Create the resolve EDRAM buffer clearing pipelines.
```

## Source note 78, line 1054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1054)

```text
// New command list - render targets not bound.
```

## Source note 79, line 1056

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1056)

```text
// ExecuteCommandLists is a full UAV barrier.
```

## Source note 80, line 1080

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1080)

```text
// For ROV, only the barrier is needed - already scheduled if required.
```

## Source note 81, line 1081

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1081)

```text
// But the buffer will be used for ROV drawing now.
```

## Source note 82, line 1083

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1083)

```text
// Commit preceding UAV (but not ROV) writes like clears as they aren't
```

## Source note 83, line 1084

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1084)

```text
// synchronized with ROV accesses.
```

## Source note 84, line 1183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1183)

```text
// The format is normalized to the xenos::TextureFormat used for the copy
```

## Source note 85, line 1184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1184)

```text
// (the depth format for depth copies, where the register may hold k_8).
```

## Source note 86, line 1188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1188)

```text
// Nothing to copy/clear.
```

## Source note 87, line 1195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1195)

```text
// Copying.
```

## Source note 88, line 1208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1208)

```text
// Written at the guest's size after the scaled copy (ADR-012); the
```

## Source note 89, line 1209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1209)

```text
// direct path writes textures, not the scaled copy it downscales.
```

## Source note 90, line 1222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1222)

```text
// Dump the current contents of the render targets owning the affected
```

## Source note 91, line 1223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1223)

```text
// range to edram_buffer_.
```

## Source note 92, line 1236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1236)

```text
// Make sure there is memory to write to.
```

## Source note 93, line 1239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1239)

```text
// Committing starting with the beginning of the potentially written
```

## Source note 94, line 1240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1240)

```text
// extent, but making the buffer containing the base current as the
```

## Source note 95, line 1241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1241)

```text
// beginning of the bound buffer is the base.
```

## Source note 96, line 1254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1254)

```text
// Write the descriptors and transition the resources.
```

## Source note 97, line 1255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1255)

```text
// Full shared memory without resolution scaling, range of the scaled
```

## Source note 98, line 1256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1256)

```text
// resolve buffer with scaling because only at least 128 * 2^20 R32
```

## Source note 99, line 1257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1257)

```text
// elements must be addressable
```

## Source note 100, line 1258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1258)

```text
// (D3D12_REQ_BUFFER_RESOURCE_TEXEL_COUNT_2_TO_EXP).
```

## Source note 101, line 1302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1302)

```text
// Submit the resolve.
```

## Source note 102, line 1318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1318)

```text
// Order the resolve with other work using the destination as a UAV.
```

## Source note 103, line 1325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1325)

```text
// Invalidate textures and mark the range as scaled if needed.
```

## Source note 104, line 1328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1328)

```text
// A native resolve also gets the guest-size copy: the center host
```

## Source note 105, line 1329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1329)

```text
// sample of each texel into shared memory, which textures of the
```

## Source note 106, line 1330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1330)

```text
// pages it covers then read.
```

## Source note 107, line 1360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1360)

```text
// Clearing.
```

## Source note 108, line 1369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1369)

```text
// If PrepareHostRenderTargetsResolveClear returns false, may be just an
```

## Source note 109, line 1370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1370)

```text
// empty region (success) or an error - don't care.
```

## Source note 110, line 1399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1399)

```text
// Should be safe to only commit once (if was UAV / ROV previously -
```

## Source note 111, line 1400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1400)

```text
// if there was nothing to copy, only to clear, for some reason, for
```

## Source note 112, line 1401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1401)

```text
// instance), overlap of the depth and the color ranges is highly
```

## Source note 113, line 1402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1402)

```text
// unlikely.
```

## Source note 114, line 1422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1422)

```text
// Non-RT-specific constants have already been set.
```

## Source note 115, line 1453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1453)

```text
// Typed should be preferred over typeless so there are more opportunities for
```

## Source note 116, line 1454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1454)

```text
// compression.
```

## Source note 117, line 1467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1467)

```text
// SNORM has two representations of -1.
```

## Source note 118, line 1472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1472)

```text
// Floating-point - ensure NaN propagation during ownership transfer for
```

## Source note 119, line 1473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1473)

```text
// unmodified data.
```

## Source note 120, line 1615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1615)

```text
// The first access will be ownership transfer into this render target or
```

## Source note 121, line 1616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1616)

```text
// starting to draw directly.
```

## Source note 122, line 1622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1622)

```text
// Fixed-point depth is generally direct (1 being the farthest),
```

## Source note 123, line 1623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1623)

```text
// floating-point is used for more uniform precision across the range (0
```

## Source note 124, line 1624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1624)

```text
// being the farthest).
```

## Source note 125, line 1635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1635)

```text
// Create zeroed for more determinism, primarily with respect to compression
```

## Source note 126, line 1636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1636)

```text
// and depth float24 / float32 mirroring.
```

## Source note 127, line 1672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1672)

```text
// DSV and stencil SRV.
```

## Source note 128, line 1698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1698)

```text
// Depth SRV.
```

## Source note 129, line 1701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1701)

```text
// Drawing RTV.
```

## Source note 130, line 1712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1712)

```text
// Ownership transfer RTV.
```

## Source note 131, line 1723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1723)

```text
// SRV for ownership transfer and dumping.
```

## Source note 132, line 1751

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1751)

```text
// Resetting edram_buffer_modification_status_ only if the barrier has been
```

## Source note 133, line 1752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1752)

```text
// truly inserted - in particular, not resetting it for UAV > UAV as
```

## Source note 134, line 1753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1753)

```text
// barriers are dropped if the state hasn't been changed.
```

## Source note 135, line 1766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1766)

```text
// max because being modified as a UAV requires stricter synchronization than
```

## Source note 136, line 1767

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1767)

```text
// as ROV.
```

## Source note 137, line 1786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1786)

```text
// Indices of host samples that transfer sample remap helpers use:
```

## Source note 138, line 1787

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1787)

```text
// - First sample bit of 4x in Direct3D 10.1+ - horizontal sample.
```

## Source note 139, line 1788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1788)

```text
// - Second sample bit of 4x in Direct3D 10.1+ - vertical sample.
```

## Source note 140, line 1789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1789)

```text
// - 2x:
```

## Source note 141, line 1790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1790)

```text
//   - Native 2x - top sample is 1 in Direct3D 10.1+, bottom sample is 0.
```

## Source note 142, line 1791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1791)

```text
//   - 2x as 4x - top sample is 0, bottom sample is 3.
```

## Source note 143, line 1793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1793)

```text
// Converts the view pixel coordinates in r0.xy and host sample index to
```

## Source note 144, line 1794

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1794)

```text
// canonical guest sample coordinates, u into r1.x and v into r1.y for a
```

## Source note 145, line 1795

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1795)

```text
// multisampled or resolution scaled view. The guest pixel goes through r1.xy
```

## Source note 146, line 1796

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1796)

```text
// and the subpixel offset via r2.xy in case of scaling, with r2.zw being
```

## Source note 147, line 1797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1797)

```text
// scratch. r0.w and r1.zw remain untouched.
```

## Source note 148, line 1807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1807)

```text
// r1.xy = guest pixel, r2.xy = host subpixel offset
```

## Source note 149, line 1816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1816)

```text
// The guest sample index is the host sample index, bit 0 horizontal
```

## Source note 150, line 1817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1817)

```text
// and bit 1 vertical for both.
```

## Source note 151, line 1818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1818)

```text
// r2.z = x with bit 1 = sample bit 0
```

## Source note 152, line 1820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1820)

```text
// r2.w = x >> 1
```

## Source note 153, line 1822

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1822)

```text
// r1.x = u = ((x >> 1) << 2) | ((sample & 1) << 1) | (x & 1)
```

## Source note 154, line 1825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1825)

```text
// r2.z = sample >> 1
```

## Source note 155, line 1827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1827)

```text
// r2.z = y with bit 1 = sample bit 1
```

## Source note 156, line 1830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1830)

```text
// r2.w = y >> 1
```

## Source note 157, line 1832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1832)

```text
// r1.y = v = ((y >> 1) << 2) | ((sample >> 1) << 1) | (y & 1)
```

## Source note 158, line 1838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1838)

```text
// r2.z = guest sample index (0 = top, 1 = bottom)
```

## Source note 159, line 1844

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1844)

```text
// r2.w = x >> 1
```

## Source note 160, line 1846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1846)

```text
// r2.w = y with bit 1 = x bit 1
```

## Source note 161, line 1849

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1849)

```text
// r1.x = u = (x & ~2) | (sample << 1)
```

## Source note 162, line 1852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1852)

```text
// r2.z = y >> 1
```

## Source note 163, line 1854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1854)

```text
// r1.y = v = ((y >> 1) << 2) | (x & 2) | (y & 1)
```

## Source note 164, line 1862

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1862)

```text
// Converts the canonical guest sample coordinates back to view pixels,
```

## Source note 165, line 1863

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1863)

```text
// r1.xy for a multisampled or resolution scaled view and scaled by the subpixel
```

## Source note 166, line 1864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1864)

```text
// offset in r2.xy, along with host sample index in r1.z. sample_out is
```

## Source note 167, line 1865

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1865)

```text
// unaffected for a single sampled view.
```

## Source note 168, line 1866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1866)

```text
// Uses r2.zw as scratch and leaves r0.w and r1.w unchanged.
```

## Source note 169, line 1874

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1874)

```text
// The host sample index is the guest sample index.
```

## Source note 170, line 1875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1875)

```text
// r2.z = (u >> 1) & 1
```

## Source note 171, line 1877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1877)

```text
// r2.w = v & 2
```

## Source note 172, line 1879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1879)

```text
// r1.z = sample = ((u >> 1) & 1) | (v & 2)
```

## Source note 173, line 1883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1883)

```text
// r2.z = u >> 2
```

## Source note 174, line 1885

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1885)

```text
// r1.x = x = ((u >> 2) << 1) | (u & 1)
```

## Source note 175, line 1888

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1888)

```text
// r2.w = v >> 2
```

## Source note 176, line 1890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1890)

```text
// r1.y = y = ((v >> 2) << 1) | (v & 1)
```

## Source note 177, line 1896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1896)

```text
// r2.z = guest sample = (u >> 1) & 1 (0 = top, 1 = bottom)
```

## Source note 178, line 1898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1898)

```text
// r1.z = host sample index
```

## Source note 179, line 1902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1902)

```text
// The guest sample 1 is the host sample 3 when 2x is emulated as
```

## Source note 180, line 1903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1903)

```text
// 4x.
```

## Source note 181, line 1908

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1908)

```text
// r2.w = v >> 1
```

## Source note 182, line 1910

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1910)

```text
// r1.x = x = (u & ~3) | (v & 2) | (u & 1)
```

## Source note 183, line 1913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1913)

```text
// r2.w = v >> 2
```

## Source note 184, line 1915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1915)

```text
// r1.y = y = ((v >> 2) << 1) | (v & 1)
```

## Source note 185, line 1922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1922)

```text
// Every scaled composition has the guest pixel in r1.xy at this point.
```

## Source note 186, line 1923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1923)

```text
// Restore the host pixel from it and the subpixel offset.
```

## Source note 187, line 1952

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1952)

```text
// If not dest_is_color, it's depth, or stencil bit - 40-sample columns are
```

## Source note 188, line 1953

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1953)

```text
// swapped as opposed to color source.
```

## Source note 189, line 1966

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1966)

```text
// If not source_is_color, it's depth / stencil - 40-sample columns are
```

## Source note 190, line 1967

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1967)

```text
// swapped as opposed to color destination.
```

## Source note 191, line 1981

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1981)

```text
// Need one component, but choosing from the two 32bpp halves of the
```

## Source note 192, line 1982

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1982)

```text
// 64bpp sample.
```

## Source note 193, line 1985

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L1985)

```text
// Red is at least 8 bits per component in all formats.
```

## Source note 194, line 2002

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2002)

```text
// Because of built_shader_.resize(), pointers can't be kept persistently
```

## Source note 195, line 2003

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2003)

```text
// here! Resizing also zeroes the memory.
```

## Source note 196, line 2007

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2007)

```text
// RDEF, ISGN, OSGN, SHEX, optionally SFI0, STAT.
```

## Source note 197, line 2010

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2010)

```text
// Allocate space for the container header and the blob offsets.
```

## Source note 198, line 2019

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2019)

```text
// Resource definition
```

## Source note 199, line 2024

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2024)

```text
// Not needed, as the next operation done is resize, to allocate the space for
```

## Source note 200, line 2025

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2025)

```text
// both the blob header and the resource definition header.
```

## Source note 201, line 2026

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2026)

```text
// built_shader_.resize(rdef_position_dwords);
```

## Source note 202, line 2028

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2028)

```text
// Allocate space for the RDEF header.
```

## Source note 203, line 2030

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2030)

```text
// Generator name.
```

## Source note 204, line 2033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2033)

```text
// Constant types - uint (aka "dword" when it's scalar) only.
```

## Source note 205, line 2034

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2034)

```text
// Names.
```

## Source note 206, line 2038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2038)

```text
// Types.
```

## Source note 207, line 2053

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2053)

```text
// Constants, if needed:
```

## Source note 208, line 2054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2054)

```text
// - uint xe_transfer_stencil_mask
```

## Source note 209, line 2055

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2055)

```text
// - uint xe_transfer_address
```

## Source note 210, line 2056

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2056)

```text
// - uint xe_transfer_host_depth_address
```

## Source note 211, line 2067

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2067)

```text
// Names.
```

## Source note 212, line 2081

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2081)

```text
// Constants.
```

## Source note 213, line 2090

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2090)

```text
// uint xe_transfer_stencil_mask
```

## Source note 214, line 2101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2101)

```text
// uint xe_transfer_address
```

## Source note 215, line 2111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2111)

```text
// uint xe_transfer_host_depth_address
```

## Source note 216, line 2124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2124)

```text
// Constant buffers, if needed:
```

## Source note 217, line 2125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2125)

```text
// - xe_transfer_stencil_mask { uint xe_transfer_stencil_mask; }
```

## Source note 218, line 2126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2126)

```text
// - xe_transfer_address { uint xe_transfer_address; }
```

## Source note 219, line 2127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2127)

```text
// - xe_transfer_host_depth_address { uint xe_transfer_host_depth_address; }
```

## Source note 220, line 2128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2128)

```text
// Reusing the constant names for constant buffers.
```

## Source note 221, line 2172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2172)

```text
// Bindings.
```

## Source note 222, line 2173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2173)

```text
// - Texture2D/Texture2DMS<floatN/uintN> xe_transfer_color
```

## Source note 223, line 2174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2174)

```text
// - Texture2D/Texture2DMS<float> xe_transfer_depth
```

## Source note 224, line 2175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2175)

```text
// - Texture2D/Texture2DMS<uint2> xe_transfer_stencil
```

## Source note 225, line 2176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2176)

```text
// - Texture2D<float>/Texture2DMS<float>/Buffer<uint> xe_transfer_host_depth
```

## Source note 226, line 2177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2177)

```text
// - Constant buffers
```

## Source note 227, line 2188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2188)

```text
// Names.
```

## Source note 228, line 2206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2206)

```text
// Bindings.
```

## Source note 229, line 2273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2273)

```text
// Float as uint.
```

## Source note 230, line 2322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2322)

```text
// Header.
```

## Source note 231, line 2336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2336)

```text
// Generator name is right after the header.
```

## Source note 232, line 2352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2352)

```text
// Input signature
```

## Source note 233, line 2355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2355)

```text
// Registers for accessing in the shader code - multiple inputs may be packed
```

## Source note 234, line 2356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2356)

```text
// into the same register.
```

## Source note 235, line 2363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2363)

```text
// Position, and for multisampled, sample index.
```

## Source note 236, line 2366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2366)

```text
// Reserve space for the header and the parameters.
```

## Source note 237, line 2372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2372)

```text
// Names (after the parameters).
```

## Source note 238, line 2381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2381)

```text
// Header and parameters.
```

## Source note 239, line 2383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2383)

```text
// Header.
```

## Source note 240, line 2388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2388)

```text
// Parameters.
```

## Source note 241, line 2392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2392)

```text
// SV_Position.xy
```

## Source note 242, line 2422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2422)

```text
// Output signature
```

## Source note 243, line 2425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2425)

```text
// Color or depth.
```

## Source note 244, line 2434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2434)

```text
// Reserve space for the header and the parameters.
```

## Source note 245, line 2440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2440)

```text
// Names (after the parameters).
```

## Source note 246, line 2462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2462)

```text
// Header and parameters.
```

## Source note 247, line 2464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2464)

```text
// Header.
```

## Source note 248, line 2469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2469)

```text
// Parameters.
```

## Source note 249, line 2496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2496)

```text
// Older versions of FXC incorrectly expect SV_StencilRef to be float,
```

## Source note 250, line 2497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2497)

```text
// it's always uint in DXC and also in the latest versions of FXC.
```

## Source note 251, line 2515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2515)

```text
// Shader program
```

## Source note 252, line 2523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2523)

```text
// Reserve space for the length token.
```

## Source note 253, line 2597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2597)

```text
// r0:r2 are involved at least in common addressing code. Texture loads
```

## Source note 254, line 2598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2598)

```text
// usually can overwrite some of the addressing temps as they are only needed
```

## Source note 255, line 2599

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2599)

```text
// for the coordinates for that load. Currently 3 temps are enough.
```

## Source note 256, line 2608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2608)

```text
// Split the destination pixel index into 32bpp tile in r0.zw and
```

## Source note 257, line 2609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2609)

```text
// 32bpp-tile-relative pixel index in r0.xy.
```

## Source note 258, line 2610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2610)

```text
// r0.xy = pixel XY as uint
```

## Source note 259, line 2617

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2617)

```text
// r0.xy = destination pixel XY index within the 32bpp tile
```

## Source note 260, line 2618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2618)

```text
// r0.zw = 32bpp tile XY index
```

## Source note 261, line 2623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2623)

```text
// r1.x = destination pitch in 32bpp tiles
```

## Source note 262, line 2626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2626)

```text
// r0.z = 32bpp tile index relative to the destination base
```

## Source note 263, line 2627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2627)

```text
// r0.w = free
```

## Source note 264, line 2628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2628)

```text
// r1.x = free
```

## Source note 265, line 2632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2632)

```text
// Now the tile index doesn't have any dependencies on the destination. The
```

## Source note 266, line 2633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2633)

```text
// dword index within the source tile, however, is calculated from both the
```

## Source note 267, line 2634

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2634)

```text
// source and the destination pixel size, sample count and color vs. depth.
```

## Source note 268, line 2636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2636)

```text
// Source can be 64bpp or 32bpp - depth if only depth is available, color in
```

## Source note 269, line 2637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2637)

```text
// all other cases.
```

## Source note 270, line 2639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2639)

```text
// Load the source to r1 (or low to r0, high to r1 if need 64bpp color as the
```

## Source note 271, line 2640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2640)

```text
// result, as the address is loaded to r1).
```

## Source note 272, line 2642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2642)

```text
// Source pixel and sample index within the 32bpp tile.
```

## Source note 273, line 2643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2643)

```text
// X to r1.x (or keep r0.x if not modifying).
```

## Source note 274, line 2644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2644)

```text
// Y to r1.y (or keep r0.y if not modifying).
```

## Source note 275, line 2645

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2645)

```text
// Sample index to r1.z (or use v# if not modifying); r1.z will also be set
```

## Source note 276, line 2646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2646)

```text
// to 0 before sampling for the LOD of the single-sampled source (needs to
```

## Source note 277, line 2647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2647)

```text
// be in the register).
```

## Source note 278, line 2648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2648)

```text
// If 64bpp -> 32bpp, also the needed half in r0.w.
```

## Source note 279, line 2654

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2654)

```text
// The transfer remaps the destination sample to the source sample through
```

## Source note 280, line 2655

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2655)

```text
// the canonical sample coordinates, the layout is described in
```

## Source note 281, line 2656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2656)

```text
// XeEdramOffsetBytes in edram.xesli.
```

## Source note 282, line 2658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2658)

```text
// Remap the destination view sample to the source view using the canonical
```

## Source note 283, line 2659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2659)

```text
// coordinates (both views are in the source scale space here).
```

## Source note 284, line 2667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2667)

```text
// The low 32bpp half of the 64bpp destination sample is obtained from the
```

## Source note 285, line 2668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2668)

```text
// source pixel at u = 2 * u_64bpp, and the high half comes from the
```

## Source note 286, line 2669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2669)

```text
// horizontally adjacent source pixel later.
```

## Source note 287, line 2673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2673)

```text
// The 32bpp destination sample is one half (r0.w) of the 64bpp
```

## Source note 288, line 2674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2674)

```text
// source sample at u = u_32bpp >> 1.
```

## Source note 289, line 2684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2684)

```text
// Each of the compositions routes u (and along with that the X result)
```

## Source note 290, line 2685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2685)

```text
// through r1.x. The Y result lands in r1.y, except when there is a single
```

## Source note 291, line 2686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2686)

```text
// sampled unscaled transfer between bit depths. In that case, v goes into
```

## Source note 292, line 2687

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2687)

```text
// r0.y.
```

## Source note 293, line 2700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2700)

```text
// Copying between color and depth / stencil - swap 40-32bpp-sample columns
```

## Source note 294, line 2701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2701)

```text
// in the pixel index within the source 32bpp tile using r1.w as temporary.
```

## Source note 295, line 2712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2712)

```text
// r1.w = free
```

## Source note 296, line 2715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2715)

```text
// Current register allocation:
```

## Source note 297, line 2716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2716)

```text
// r0.xy = pixel index within the destination 32bpp tile
```

## Source note 298, line 2717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2717)

```text
// r0.z = 32bpp tile index relative to the destination base
```

## Source note 299, line 2718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2718)

```text
// r0.w for 64bpp -> 32bpp - needed 32bpp half index of 64bpp data
```

## Source note 300, line 2719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2719)

```text
// r1.xy = pixel index within the source 32bpp tile
```

## Source note 301, line 2720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2720)

```text
// r1.z for 2x/4x -> = sample index within the source pixel
```

## Source note 302, line 2722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2722)

```text
// Apply the source 32bpp tile index.
```

## Source note 303, line 2723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2723)

```text
// r1.w = destination to source EDRAM tile adjustment
```

## Source note 304, line 2727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2727)

```text
// r1.w = 32bpp tile index within the source, or the tile index within the
```

## Source note 305, line 2728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2728)

```text
//        source minus the EDRAM tile count if transferring across addressing
```

## Source note 306, line 2729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2729)

```text
//        wrapping (if negative)
```

## Source note 307, line 2732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2732)

```text
// r1.w = 32bpp tile index within the source
```

## Source note 308, line 2735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2735)

```text
// r2.x = source pitch in 32bpp tiles
```

## Source note 309, line 2739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2739)

```text
// r1.w = source tile row
```

## Source note 310, line 2740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2740)

```text
// r2.x = source 32bpp tile within the row
```

## Source note 311, line 2743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2743)

```text
// r1.x = pixel X within the source texture
```

## Source note 312, line 2744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2744)

```text
// r2.x = free
```

## Source note 313, line 2748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2748)

```text
// r1.y = pixel Y within the source texture
```

## Source note 314, line 2749

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2749)

```text
// r1.w = free
```

## Source note 315, line 2756

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2756)

```text
// Load the source to r1, or, for 32bpp | 32bpp -> 64bpp, the first dword to
```

## Source note 316, line 2757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2757)

```text
// r0 since addressing will not be needed anymore for color, and the second
```

## Source note 317, line 2758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2758)

```text
// dword to r1.
```

## Source note 318, line 2759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2759)

```text
// Depth will be loaded to w before loading stencil (so it doesn't overwrite
```

## Source note 319, line 2760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2760)

```text
// the coordinates needed for stencil loading).
```

## Source note 320, line 2761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2761)

```text
// Stencil will be loaded to x.
```

## Source note 321, line 2762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2762)

```text
// Color will be loaded to x...w.
```

## Source note 322, line 2782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2782)

```text
// The high 32bpp half of a 64bpp destination sample is identical to the
```

## Source note 323, line 2783

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2783)

```text
// sample of the horizontally adjacent source pixel since each canonical
```

## Source note 324, line 2784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2784)

```text
// sample column of a single 64bpp value decodes to the same sample of
```

## Source note 325, line 2785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2785)

```text
// two horizontally adjacent pixels, regardless of sample count.
```

## Source note 326, line 2791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2791)

```text
// Write zero to the LOD index in r1.z.
```

## Source note 327, line 2809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2809)

```text
// The high half, same as in the multisampled case above.
```

## Source note 328, line 2815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2815)

```text
// Pick the needed 32bpp half of the 64bpp color based on r0.w.
```

## Source note 329, line 2836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2836)

```text
// For the depth -> depth case, write the stencil loaded to r1.x directly to
```

## Source note 330, line 2837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2837)

```text
// the output.
```

## Source note 331, line 2843

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2843)

```text
// Handle construction of 64bpp color, either from two 32-bit samples in r0
```

## Source note 332, line 2844

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2844)

```text
// and r1, or from one 64bpp sample in r1. Using r2.x as temporary when
```

## Source note 333, line 2845

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2845)

```text
// needed.
```

## Source note 334, line 2846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2846)

```text
// If color_packed_in_r0x_and_r1x, use the generic path for combining two
```

## Source note 335, line 2847

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2847)

```text
// 32-bit samples - as raw in r0.x and r1.x - into the destination.
```

## Source note 336, line 2852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2852)

```text
// 8_8_8_8_GAMMA is represented by linear stored in
```

## Source note 337, line 2853

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2853)

```text
// R16G16B16A16_UNORM.
```

## Source note 338, line 2890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2890)

```text
// Float16 has a wider range for both color and alpha, also NaNs -
```

## Source note 339, line 2891

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2891)

```text
// clamp and convert.
```

## Source note 340, line 2899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2899)

```text
// Saturate and convert the alpha.
```

## Source note 341, line 2908

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2908)

```text
// All 64bpp formats, and all 16 bits per component formats, are
```

## Source note 342, line 2909

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2909)

```text
// represented as integers in ownership transfer for safe handling of
```

## Source note 343, line 2910

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2910)

```text
// NaNs and -32768 / -32767.
```

## Source note 344, line 2950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2950)

```text
// Round to the nearest even integer. This seems to be the correct
```

## Source note 345, line 2951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2951)

```text
// conversion, adding +0.5 and rounding towards zero results in red
```

## Source note 346, line 2952

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2952)

```text
// instead of black in the 4D5307E6 clear shader.
```

## Source note 347, line 2959

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2959)

```text
// Convert using r1.y as temporary.
```

## Source note 348, line 2960

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2960)

```text
// When converting the depth in pixel shaders, it's always exact,
```

## Source note 349, line 2961

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2961)

```text
// truncating not to insert additional rounding instructions.
```

## Source note 350, line 2967

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2967)

```text
// Merge depth and stencil into r0/r1.x.
```

## Source note 351, line 2984

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2984)

```text
// Handle a 32bpp destination (32bpp color, or depth / stencil). If
```

## Source note 352, line 2985

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2985)

```text
// color_packed_in_r1x is true, a raw 32bpp color value was written, and
```

## Source note 353, line 2986

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L2986)

```text
// common handling will be done.
```

## Source note 354, line 3004

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3004)

```text
// Color space conversion between k_8_8_8_8 and
```

## Source note 355, line 3005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3005)

```text
// k_8_8_8_8_GAMMA.
```

## Source note 356, line 3016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3016)

```text
// Same or converted format - passthrough.
```

## Source note 357, line 3025

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3025)

```text
// When need only depth, not stencil, skip the red component.
```

## Source note 358, line 3031

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3031)

```text
// Write the red component to the stencil reference.
```

## Source note 359, line 3034

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3034)

```text
// Put depth in 0:23 of r1.w.
```

## Source note 360, line 3035

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3035)

```text
// r1.y = 0xGGBB0000.
```

## Source note 361, line 3038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3038)

```text
// r1.w = 0xGGBBAA00.
```

## Source note 362, line 3090

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3090)

```text
// Float16 has a wider range for both color and alpha, also NaNs -
```

## Source note 363, line 3091

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3091)

```text
// clamp and convert.
```

## Source note 364, line 3099

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3099)

```text
// Saturate and convert the alpha.
```

## Source note 365, line 3112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3112)

```text
// All 16 bits per component formats are represented as integers in
```

## Source note 366, line 3113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3113)

```text
// ownership transfer for safe handling of NaNs and -32768 / -32767.
```

## Source note 367, line 3115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3115)

```text
// High bits are not important for discarding, as only one bit is
```

## Source note 368, line 3116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3116)

```text
// checked - already loaded to red.
```

## Source note 369, line 3134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3134)

```text
// Need to reinterpret the depth value as color or as a different depth
```

## Source note 370, line 3135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3135)

```text
// format. Convert the depth within r1.w.
```

## Source note 371, line 3139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3139)

```text
// Round to the nearest even integer. This seems to be the correct
```

## Source note 372, line 3140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3140)

```text
// conversion, adding +0.5 and rounding towards zero results in red
```

## Source note 373, line 3141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3141)

```text
// instead of black in the 4D5307E6 clear shader.
```

## Source note 374, line 3148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3148)

```text
// Convert using r1.y as temporary.
```

## Source note 375, line 3149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3149)

```text
// When converting the depth in pixel shaders, it's always exact,
```

## Source note 376, line 3150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3150)

```text
// truncating not to insert additional rounding instructions.
```

## Source note 377, line 3157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3157)

```text
// Merge depth and stencil into r1.x for reinterpretation as color.
```

## Source note 378, line 3166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3166)

```text
// Unless a special path was taken, unpack the raw 32bpp value into the
```

## Source note 379, line 3167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3167)

```text
// 32bpp color output. Any register can be used as temporary if needed -
```

## Source note 380, line 3168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3168)

```text
// this is the end of the shader.
```

## Source note 381, line 3178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3178)

```text
// 8_8_8_8_GAMMA is represented by linear stored in
```

## Source note 382, line 3179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3179)

```text
// R16G16B16A16_UNORM.
```

## Source note 383, line 3200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3200)

```text
// Color using r1.yz as temporary.
```

## Source note 384, line 3205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3205)

```text
// Alpha.
```

## Source note 385, line 3214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3214)

```text
// All 16 bits per component formats are represented as integers
```

## Source note 386, line 3215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3215)

```text
// in ownership transfer for safe handling of NaNs and
```

## Source note 387, line 3216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3216)

```text
// -32768 / -32767.
```

## Source note 388, line 3221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3221)

```text
// Already as a 32-bit value.
```

## Source note 389, line 3225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3225)

```text
// A 64bpp format (handled separately) or an invalid one.
```

## Source note 390, line 3233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3233)

```text
// Extract the depth bits to r1.w.
```

## Source note 391, line 3237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3237)

```text
// Extract the stencil bits to the stencil reference.
```

## Source note 392, line 3238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3238)

```text
// The depth -> depth case is handled earlier, not long after
```

## Source note 393, line 3239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3239)

```text
// loading the stencil, for simplicity.
```

## Source note 394, line 3244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3244)

```text
// r1.w contains the depth in the guest format. If a host depth source
```

## Source note 395, line 3245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3245)

```text
// is available, need to check if it's up to date - if it is, the host
```

## Source note 396, line 3246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3246)

```text
// precision value needs to be written. Otherwise, the new guest value
```

## Source note 397, line 3247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3247)

```text
// needs to be converted to the host format. Using `if` here because
```

## Source note 398, line 3248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3248)

```text
// it's likely that the values will either be the same - if not
```

## Source note 399, line 3249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3249)

```text
// modified - or different - if cleared or totally overwritten - in
```

## Source note 400, line 3250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3250)

```text
// large amounts of samples, usually whole waves, at once.
```

## Source note 401, line 3252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3252)

```text
// Load the host float32 depth to r0.x, check if, when converted to
```

## Source note 402, line 3253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3253)

```text
// the guest format, it's the same as the guest source, thus up to
```

## Source note 403, line 3254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3254)

```text
// date, and if it is, write host float32 depth to r1.w, otherwise
```

## Source note 404, line 3255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3255)

```text
// do the guest -> host conversion on the `else` path.
```

## Source note 405, line 3257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3257)

```text
// Current register allocation:
```

## Source note 406, line 3258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3258)

```text
// r0.xy = pixel index within the destination 32bpp tile
```

## Source note 407, line 3259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3259)

```text
// r0.z = 32bpp tile index relative to the destination base
```

## Source note 408, line 3260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3260)

```text
// r1.w = depth in guest format
```

## Source note 409, line 3263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3263)

```text
// Get the address in the EDRAM scratch buffer and load from
```

## Source note 410, line 3264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3264)

```text
// there.
```

## Source note 411, line 3265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3265)

```text
// The beginning of the buffer is (0, 0) of the destination.
```

## Source note 412, line 3266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3266)

```text
// 40-sample columns are not swapped for addressing simplicity
```

## Source note 413, line 3267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3267)

```text
// (because this is used for depth -> depth transfers, where
```

## Source note 414, line 3268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3268)

```text
// swapping isn't needed).
```

## Source note 415, line 3269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3269)

```text
// Convert samples to pixels.
```

## Source note 416, line 3273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3273)

```text
// Horizontal sample index in bit 0.
```

## Source note 417, line 3277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3277)

```text
// Vertical sample index as 1 or 0 in bit 0 for true 2x or as 0
```

## Source note 418, line 3278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3278)

```text
// or 1 in bit 1 for 4x or for 2x emulated as 4x.
```

## Source note 419, line 3285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3285)

```text
// Using r0.w as a temporary.
```

## Source note 420, line 3291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3291)

```text
// Combine the tile sample index and the tile index into buffer
```

## Source note 421, line 3292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3292)

```text
// address to r0.x.
```

## Source note 422, line 3293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3293)

```text
// The tile index doesn't need to be wrapped, as the host depth is
```

## Source note 423, line 3294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3294)

```text
// written to the beginning of the buffer, without the base
```

## Source note 424, line 3295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3295)

```text
// offset.
```

## Source note 425, line 3301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3301)

```text
// Load from the buffer.
```

## Source note 426, line 3306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3306)

```text
// Adjust the tile index from the destination to the host depth
```

## Source note 427, line 3307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3307)

```text
// source.
```

## Source note 428, line 3308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3308)

```text
// r0.w = destination to host depth source EDRAM tile adjustment
```

## Source note 429, line 3313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3313)

```text
// r0.z = tile index relative to the host depth source base, or
```

## Source note 430, line 3314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3314)

```text
//        the tile index within the host depth source minus the
```

## Source note 431, line 3315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3315)

```text
//        EDRAM tile count if transferring across addressing
```

## Source note 432, line 3316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3316)

```text
//        wrapping (if negative)
```

## Source note 433, line 3317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3317)

```text
// r0.w = free
```

## Source note 434, line 3320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3320)

```text
// r0.z = tile index relative to the host depth source base
```

## Source note 435, line 3323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3323)

```text
// Convert position and sample index from within the destination
```

## Source note 436, line 3324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3324)

```text
// tile to within the host depth source tile by remapping
```

## Source note 437, line 3325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3325)

```text
// through the canonical coordinates. Both views are 32bpp and
```

## Source note 438, line 3326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3326)

```text
// use the destination scale.
```

## Source note 439, line 3341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3341)

```text
// With varying sample counts, the remapped coordinates will
```

## Source note 440, line 3342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3342)

```text
// always be stored in r1.xy here. The remapping helpers keep
```

## Source note 441, line 3343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3343)

```text
// the value of r1.w as the guest depth value, while r1.z, the
```

## Source note 442, line 3344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3344)

```text
// host sample index, is read before the pitch takes up r1.x.
```

## Source note 443, line 3345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3345)

```text
// Move the coordinates to r0.xy for the common host depth
```

## Source note 444, line 3346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3346)

```text
// source addressing.
```

## Source note 445, line 3349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3349)

```text
// r1.x = host depth source pitch in tiles
```

## Source note 446, line 3354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3354)

```text
// r0.z = host depth source tile row
```

## Source note 447, line 3355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3355)

```text
// r1.x = host depth source tile within the row
```

## Source note 448, line 3358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3358)

```text
// r0.x = pixel X within the host depth source texture
```

## Source note 449, line 3359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3359)

```text
// r1.x = free
```

## Source note 450, line 3365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3365)

```text
// r0.y = pixel Y within the host depth source texture
```

## Source note 451, line 3366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3366)

```text
// r0.z = free
```

## Source note 452, line 3372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3372)

```text
// Load from the host depth texture.
```

## Source note 453, line 3379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3379)

```text
// Write zero to the LOD index in r0.z.
```

## Source note 454, line 3386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3386)

```text
// Convert the host depth value in r0.x to the guest format in r0.y
```

## Source note 455, line 3387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3387)

```text
// using r0.z as a temporary and check if it matches the value in
```

## Source note 456, line 3388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3388)

```text
// the currently owning guest render target.
```

## Source note 457, line 3391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3391)

```text
// Round to the nearest even integer. This seems to be the
```

## Source note 458, line 3392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3392)

```text
// correct, adding +0.5 and rounding towards zero results in red
```

## Source note 459, line 3393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3393)

```text
// instead of black in the 4D5307E6 clear shader.
```

## Source note 460, line 3400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3400)

```text
// When converting the depth in pixel shaders, it's always
```

## Source note 461, line 3401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3401)

```text
// exact, truncating not to insert additional rounding
```

## Source note 462, line 3402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3402)

```text
// instructions.
```

## Source note 463, line 3411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3411)

```text
// If the host depth is up to date, write it to oDepth at the host
```

## Source note 464, line 3412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3412)

```text
// precision instead of converting the guest depth.
```

## Source note 465, line 3416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3416)

```text
// Convert using r0.x as a temporary.
```

## Source note 466, line 3419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3419)

```text
// Multiplying by 1.0 / 0xFFFFFF produces an incorrect result (for
```

## Source note 467, line 3420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3420)

```text
// 0xC00000, for instance - which is 2_10_10_10 clear to 0001) -
```

## Source note 468, line 3421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3421)

```text
// rescale from 0...0xFFFFFF to 0...0x1000000 doing what true
```

## Source note 469, line 3422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3422)

```text
// float division followed by multiplication does (on x86-64 MSVC
```

## Source note 470, line 3423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3423)

```text
// with default SSE rounding) - values starting from 0x800000
```

## Source note 471, line 3424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3424)

```text
// become bigger by 1; then accurately bias the result's exponent.
```

## Source note 472, line 3438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3438)

```text
// Host depth is different, or not available - convert the guest depth
```

## Source note 473, line 3439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3439)

```text
// to the destination format.
```

## Source note 474, line 3441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3441)

```text
// Close the conditional for the host / guest depth.
```

## Source note 475, line 3448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3448)

```text
// Discard the sample if the needed stencil bit is not set.
```

## Source note 476, line 3459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3459)

```text
// Fill the unused components of the color result.
```

## Source note 477, line 3470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3470)

```text
// Write the shader program length in dwords.
```

## Source note 478, line 3483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3483)

```text
// Shader feature info
```

## Source note 479, line 3521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3521)

```text
// Container header
```

## Source note 480, line 3558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3558)

```text
// Using sample 0 as 0 and 3 as 1 for 2x instead.
```

## Source note 481, line 3579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3579)

```text
// Even if creation fails, still store the null pointers not to try to
```

## Source note 482, line 3580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3580)

```text
// create again.
```

## Source note 483, line 3619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3619)

```text
// Using ALWAYS, not NOT_EQUAL, so depth writing is unaffected by
```

## Source note 484, line 3620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3620)

```text
// stencil being different.
```

## Source note 485, line 3630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3630)

```text
// Even if creation fails, still store the null pointer not to try to create
```

## Source note 486, line 3631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3631)

```text
// again.
```

## Source note 487, line 3632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3632)

```text
// Return a pointer to the persistent location.
```

## Source note 488, line 3639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3639)

```text
// Stencil bit copying uses only the stencil SRV for depth / stencil source,
```

## Source note 489, line 3640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3640)

```text
// can't use srv_index_depth for checking.
```

## Source note 490, line 3683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3683)

```text
// Assuming the rectangle is already clamped by the setup function from the
```

## Source note 491, line 3684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3684)

```text
// common render target cache.
```

## Source note 492, line 3695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3695)

```text
// Do host depth storing for the depth destination (assuming there can be only
```

## Source note 493, line 3696

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3696)

```text
// one depth destination) where depth destination == host depth source.
```

## Source note 494, line 3714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3714)

```text
// Bindings.
```

## Source note 495, line 3715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3715)

```text
// 0 - source.
```

## Source note 496, line 3716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3716)

```text
// 1 - EDRAM if bindful.
```

## Source note 497, line 3723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3723)

```text
// Destination (EDRAM uint4 buffer).
```

## Source note 498, line 3735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3735)

```text
// Depth source texture.
```

## Source note 499, line 3743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3743)

```text
// Render target constant.
```

## Source note 500, line 3752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3752)

```text
// Barriers - don't need to try to combine them with the rest of
```

## Source note 501, line 3753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3753)

```text
// render target transfer barriers now - if this happens, after host
```

## Source note 502, line 3754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3754)

```text
// depth storing, NON_PIXEL_SHADER_RESOURCE -> DEPTH_WRITE will be done
```

## Source note 503, line 3755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3755)

```text
// anyway even in the best case, so it's not possible to have all the
```

## Source note 504, line 3756

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3756)

```text
// barriers in one place here.
```

## Source note 505, line 3762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3762)

```text
// Pipeline.
```

## Source note 506, line 3791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3791)

```text
// Try to insert as many barriers as possible in one place, hoping that in the
```

## Source note 507, line 3792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3792)

```text
// best case (no cross-copying between current render targets), barriers will
```

## Source note 508, line 3793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3793)

```text
// need to be only inserted here, not between transfers. In case of
```

## Source note 509, line 3794

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3794)

```text
// cross-copying, if the destination use is going to happen before the source
```

## Source note 510, line 3795

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3795)

```text
// use, choose the destination state, otherwise the source state - to match
```

## Source note 511, line 3796

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3796)

```text
// the order in which transfers will actually happen (otherwise there will be
```

## Source note 512, line 3797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3797)

```text
// just a useless switch back and forth).
```

## Source note 513, line 3808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3808)

```text
// Transition the sources, only if not going to be used as destinations
```

## Source note 514, line 3809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3809)

```text
// earlier.
```

## Source note 515, line 3832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3832)

```text
// transfer.host_depth_source == dest_rt means the EDRAM buffer will be
```

## Source note 516, line 3833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3833)

```text
// used instead, no need to transition.
```

## Source note 517, line 3844

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3844)

```text
// Transition the destination, only if not going to be used as a source
```

## Source note 518, line 3845

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3845)

```text
// earlier.
```

## Source note 519, line 3864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3864)

```text
// Will be reading copied host depth from the EDRAM buffer.
```

## Source note 520, line 3868

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3868)

```text
// Copy source descriptors to the shader-visible heap.
```

## Source note 521, line 3869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3869)

```text
// Clear previously set shader-visible descriptor indices.
```

## Source note 522, line 3921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3921)

```text
// The host_depth_source_d3d12_rt == dest_rt case would use the EDRAM
```

## Source note 523, line 3922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3922)

```text
// buffer instead.
```

## Source note 524, line 3944

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3944)

```text
// Perform the transfers and clears.
```

## Source note 525, line 3976

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3976)

```text
// Late barrier in case there was cross-copying that prevented merging of
```

## Source note 526, line 3977

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L3977)

```text
// barriers.
```

## Source note 527, line 4002

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4002)

```text
// Gather shader keys and sort to reduce pipeline state and binding
```

## Source note 528, line 4003

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4003)

```text
// switches. Also gather stencil rectangles to clear if needed.
```

## Source note 529, line 4014

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4014)

```text
// j == 0 - color or depth.
```

## Source note 530, line 4015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4015)

```text
// j == 1 - stencil bits.
```

## Source note 531, line 4016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4016)

```text
// Stencil bit writing always requires a different root signature,
```

## Source note 532, line 4017

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4017)

```text
// handle these separately. Stencil never has a host depth source.
```

## Source note 533, line 4018

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4018)

```text
// Clear previously set sort indices.
```

## Source note 534, line 4046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4046)

```text
// The host depth copy buffer has only raw samples.
```

## Source note 535, line 4081

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4081)

```text
// Clear the stencil to 0 where it will be loaded - will be setting the
```

## Source note 536, line 4082

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4082)

```text
// bits that need to be 1 by discarding samples. Clearing everything here
```

## Source note 537, line 4083

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4083)

```text
// to reduce context switches internally in the driver if clear causes
```

## Source note 538, line 4084

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4084)

```text
// them.
```

## Source note 539, line 4114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4114)

```text
// Perform the transfers for the render target.
```

## Source note 540, line 4118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4118)

```text
// Will be passing NDC directly, set the viewport to the maximum host
```

## Source note 541, line 4119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4119)

```text
// render target size for simplicity. Using a power-of-two scale for
```

## Source note 542, line 4120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4120)

```text
// exact pixel coordinates.
```

## Source note 543, line 4141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4141)

```text
// Will be merging transfers from the same source into one mesh.
```

## Source note 544, line 4157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4157)

```text
// Skip the merged transfers in the subsequent iterations.
```

## Source note 545, line 4175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4175)

```text
// Late barriers in case there was cross-copying that prevented merging
```

## Source note 546, line 4176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4176)

```text
// of barriers.
```

## Source note 547, line 4183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4183)

```text
// Reading copied host depth from the EDRAM buffer.
```

## Source note 548, line 4186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4186)

```text
// Reading host depth from the texture.
```

## Source note 549, line 4221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4221)

```text
// O-*
```

## Source note 550, line 4226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4226)

```text
// *-O
```

## Source note 551, line 4238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4238)

```text
// O-*
```

## Source note 552, line 4248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4248)

```text
// *-O
```

## Source note 553, line 4268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4268)

```text
// Invalidate outdated bindings.
```

## Source note 554, line 4339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4339)

```text
// Apply the new bindings.
```

## Source note 555, line 4409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4409)

```text
// Draw the transfer rectangles.
```

## Source note 556, line 4425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4425)

```text
// Perform the clear.
```

## Source note 557, line 4436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4436)

```text
// Taking [0, 2) -> [0, 1) remapping into account.
```

## Source note 558, line 4459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4459)

```text
// 8_8_8_8_GAMMA is represented by linear stored in
```

## Source note 559, line 4460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4460)

```text
// R16G16B16A16_UNORM.
```

## Source note 560, line 4484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4484)

```text
// Using uint for loading both. Disregarding the current -32...32
```

## Source note 561, line 4485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4485)

```text
// vs. -1...1 settings for consistency with color clear via depth
```

## Source note 562, line 4486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4486)

```text
// aliasing.
```

## Source note 563, line 4493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4493)

```text
// Using uint for loading both. Disregarding the current -32...32
```

## Source note 564, line 4494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4494)

```text
// vs. -1...1 settings for consistency with color clear via depth
```

## Source note 565, line 4495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4495)

```text
// aliasing.
```

## Source note 566, line 4501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4501)

```text
// Using uint for proper denormal and NaN handling.
```

## Source note 567, line 4503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4503)

```text
// Numbers > 2^24 can't be represented with a step of 1 as floats,
```

## Source note 568, line 4504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4504)

```text
// need to clear by drawing a uint rectangle.
```

## Source note 569, line 4510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4510)

```text
// Using uint for proper denormal and NaN handling.
```

## Source note 570, line 4513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4513)

```text
// Numbers > 2^24 can't be represented with a step of 1 as floats,
```

## Source note 571, line 4514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4514)

```text
// need to clear by drawing a uint rectangle.
```

## Source note 572, line 4567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4567)

```text
// Ensure the render targets are in the needed resource state.
```

## Source note 573, line 4585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4585)

```text
// Bind the render targets.
```

## Source note 574, line 4607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4607)

```text
// Fill the gaps with a null descriptor.
```

## Source note 575, line 4628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4628)

```text
// Because of built_shader_.resize(), pointers can't be kept persistently
```

## Source note 576, line 4629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4629)

```text
// here! Resizing also zeroes the memory.
```

## Source note 577, line 4633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4633)

```text
// RDEF, ISGN, OSGN, SHEX, STAT.
```

## Source note 578, line 4636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4636)

```text
// Allocate space for the container header and the blob offsets.
```

## Source note 579, line 4645

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4645)

```text
// Resource definition
```

## Source note 580, line 4650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4650)

```text
// Not needed, as the next operation done is resize, to allocate the space for
```

## Source note 581, line 4651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4651)

```text
// both the blob header and the resource definition header.
```

## Source note 582, line 4652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4652)

```text
// built_shader_.resize(rdef_position_dwords);
```

## Source note 583, line 4654

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4654)

```text
// Allocate space for the RDEF header.
```

## Source note 584, line 4656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4656)

```text
// Generator name.
```

## Source note 585, line 4659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4659)

```text
// Constant types - uint (aka "dword" when it's scalar) only.
```

## Source note 586, line 4660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4660)

```text
// Names.
```

## Source note 587, line 4664

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4664)

```text
// Types.
```

## Source note 588, line 4680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4680)

```text
// - uint xe_edram_dump_offsets
```

## Source note 589, line 4681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4681)

```text
// - uint xe_edram_dump_pitches
```

## Source note 590, line 4687

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4687)

```text
// Names.
```

## Source note 591, line 4693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4693)

```text
// Constants.
```

## Source note 592, line 4702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4702)

```text
// uint xe_edram_dump_offsets
```

## Source note 593, line 4710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4710)

```text
// uint xe_edram_dump_pitches
```

## Source note 594, line 4720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4720)

```text
// Constant buffers:
```

## Source note 595, line 4721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4721)

```text
// - xe_edram_dump_offsets : b0 { uint xe_edram_dump_offsets; }
```

## Source note 596, line 4722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4722)

```text
// - xe_edram_dump_pitches : b1 { uint xe_edram_dump_pitches; }
```

## Source note 597, line 4723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4723)

```text
// Reusing the constant names for constant buffers.
```

## Source note 598, line 4746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4746)

```text
// Bindings.
```

## Source note 599, line 4747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4747)

```text
// - Texture2D/Texture2DMS<float4/uint4> xe_edram_dump_source : t0
```

## Source note 600, line 4748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4748)

```text
// - Optionally, Texture2D/Texture2DMS<uint2> xe_edram_dump_stencil : t1
```

## Source note 601, line 4749

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4749)

```text
// - RWBuffer<uint/uint2> xe_edram : u0
```

## Source note 602, line 4750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4750)

```text
// - Constant buffers
```

## Source note 603, line 4752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4752)

```text
// Names.
```

## Source note 604, line 4762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4762)

```text
// Bindings.
```

## Source note 605, line 4789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4789)

```text
// Sample count is dynamic on Shader Model 5.
```

## Source note 606, line 4837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4837)

```text
// Header.
```

## Source note 607, line 4851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4851)

```text
// Generator name is right after the header.
```

## Source note 608, line 4867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4867)

```text
// Input and output signatures (empty)
```

## Source note 609, line 4877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4877)

```text
// Empty - just set parameter pointer to the end.
```

## Source note 610, line 4892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4892)

```text
// Shader program
```

## Source note 611, line 4900

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4900)

```text
// Reserve space for the length token.
```

## Source note 612, line 4914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4914)

```text
// Source texture.
```

## Source note 613, line 4923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4923)

```text
// Source stencil texture.
```

## Source note 614, line 4929

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4929)

```text
// EDRAM buffer.
```

## Source note 615, line 4934

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4934)

```text
// r0 - addressing before the load, then addressing and conversion scratch
```

## Source note 616, line 4935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4935)

```text
// r1 - addressing scratch before the load, then data
```

## Source note 617, line 4938

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4938)

```text
// There's no strict dependency on the group size here, for simplicity of
```

## Source note 618, line 4939

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4939)

```text
// calculations especially with resolution scaling, dividing manually (as the
```

## Source note 619, line 4940

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4940)

```text
// group size is not unlimited). The only restriction is that an integer
```

## Source note 620, line 4941

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4941)

```text
// multiple of it must be 80x16 samples (and no larger than that) for 32bpp,
```

## Source note 621, line 4942

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4942)

```text
// or 40x16 samples for 64bpp (because only a half of the pair of tiles may
```

## Source note 622, line 4943

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4943)

```text
// need to be dumped). The group size limit in Direct3D 11 is 1024, and 40x16
```

## Source note 623, line 4944

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4944)

```text
// fits in it, while 80x16 doesn't.
```

## Source note 624, line 4950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4950)

```text
// For now, as the exact addressing in 64bpp render targets relatively to
```

## Source note 625, line 4951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4951)

```text
// 32bpp is unknown, treating 64bpp tiles as storing 40x16 samples rather than
```

## Source note 626, line 4952

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4952)

```text
// 80x16 for simplicity of addressing into the texture.
```

## Source note 627, line 4958

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4958)

```text
// Get the parts of the address - tile row index within the dispatch to r0.zw,
```

## Source note 628, line 4959

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4959)

```text
// sample Y within the tile to r0.xy.
```

## Source note 629, line 4960

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4960)

```text
// r0.x = X sample position within the tile
```

## Source note 630, line 4961

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4961)

```text
// r0.y = Y sample position within the tile
```

## Source note 631, line 4962

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4962)

```text
// r0.z = X tile position
```

## Source note 632, line 4963

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4963)

```text
// r0.w = Y tile position
```

## Source note 633, line 4967

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4967)

```text
// Extract the dump rectangle tile row pitch to r1.x.
```

## Source note 634, line 4968

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4968)

```text
// r0.x = X sample position within the tile
```

## Source note 635, line 4969

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4969)

```text
// r0.y = Y sample position within the tile
```

## Source note 636, line 4970

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4970)

```text
// r0.z = X tile position
```

## Source note 637, line 4971

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4971)

```text
// r0.w = Y tile position
```

## Source note 638, line 4972

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4972)

```text
// r1.x = dump rectangle pitch in tiles
```

## Source note 639, line 4975

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4975)

```text
// Get the tile index in the EDRAM relative to the dump rectangle base tile to
```

## Source note 640, line 4976

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4976)

```text
// r0.w.
```

## Source note 641, line 4977

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4977)

```text
// r0.x = X sample position within the tile
```

## Source note 642, line 4978

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4978)

```text
// r0.y = Y sample position within the tile
```

## Source note 643, line 4979

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4979)

```text
// r0.z = free
```

## Source note 644, line 4980

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4980)

```text
// r0.w = tile index relative to the dump rectangle base
```

## Source note 645, line 4981

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4981)

```text
// r1.x = free
```

## Source note 646, line 4985

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4985)

```text
// Extract the index of the first tile (taking EDRAM addressing wrapping into
```

## Source note 647, line 4986

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4986)

```text
// account) of the dispatch in the EDRAM to r0.z.
```

## Source note 648, line 4987

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4987)

```text
// r0.x = X sample position within the tile
```

## Source note 649, line 4988

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4988)

```text
// r0.y = Y sample position within the tile
```

## Source note 650, line 4989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4989)

```text
// r0.z = first EDRAM tile index in the dispatch
```

## Source note 651, line 4990

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4990)

```text
// r0.w = tile index relative to the dump rectangle base
```

## Source note 652, line 4994

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4994)

```text
// Add the base tile in the dispatch to the dispatch-local tile index to r0.w,
```

## Source note 653, line 4995

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4995)

```text
// not wrapping yet so in case of a wraparound, the address relative to the
```

## Source note 654, line 4996

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4996)

```text
// base in the texture after subtraction of the base won't be negative.
```

## Source note 655, line 4997

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4997)

```text
// r0.x = X sample position within the tile
```

## Source note 656, line 4998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4998)

```text
// r0.y = Y sample position within the tile
```

## Source note 657, line 4999

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L4999)

```text
// r0.z = free
```

## Source note 658, line 5000

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5000)

```text
// r0.w = non-wrapped tile index in the EDRAM
```

## Source note 659, line 5003

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5003)

```text
// Wrap the address of the tile in the EDRAM to r0.z.
```

## Source note 660, line 5004

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5004)

```text
// r0.x = X sample position within the tile
```

## Source note 661, line 5005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5005)

```text
// r0.y = Y sample position within the tile
```

## Source note 662, line 5006

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5006)

```text
// r0.z = wrapped tile index in the EDRAM
```

## Source note 663, line 5007

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5007)

```text
// r0.w = non-wrapped tile index in the EDRAM
```

## Source note 664, line 5010

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5010)

```text
// Convert the tile index to samples and add the X sample index to it to r0.z.
```

## Source note 665, line 5011

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5011)

```text
// r0.x = X sample position within the tile
```

## Source note 666, line 5012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5012)

```text
// r0.y = Y sample position within the tile
```

## Source note 667, line 5013

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5013)

```text
// r0.z = tile sample offset in the EDRAM plus X sample offset
```

## Source note 668, line 5014

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5014)

```text
// r0.w = non-wrapped tile index in the EDRAM
```

## Source note 669, line 5020

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5020)

```text
// Add the contribution of the Y sample position within the tile to the sample
```

## Source note 670, line 5021

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5021)

```text
// address in the EDRAM to r0.z.
```

## Source note 671, line 5022

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5022)

```text
// r0.x = X sample position within the tile
```

## Source note 672, line 5023

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5023)

```text
// r0.y = Y sample position within the tile
```

## Source note 673, line 5024

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5024)

```text
// r0.z = sample offset in the EDRAM without the depth column swapping
```

## Source note 674, line 5025

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5025)

```text
// r0.w = non-wrapped tile index in the EDRAM
```

## Source note 675, line 5030

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5030)

```text
// Get which 40-sample half within the tile is being processed to r1.x.
```

## Source note 676, line 5031

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5031)

```text
// r0.x = X sample position within the tile
```

## Source note 677, line 5032

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5032)

```text
// r0.y = Y sample position within the tile
```

## Source note 678, line 5033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5033)

```text
// r0.z = sample offset in the EDRAM without the depth column swapping
```

## Source note 679, line 5034

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5034)

```text
// r0.w = non-wrapped tile index in the EDRAM
```

## Source note 680, line 5035

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5035)

```text
// r1.x = 0xFFFFFFFF if in the right 40-sample half, 0 otherwise
```

## Source note 681, line 5038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5038)

```text
// Get the offset needed to swap 40-sample halves for depth.
```

## Source note 682, line 5039

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5039)

```text
// r0.x = X sample position within the tile
```

## Source note 683, line 5040

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5040)

```text
// r0.y = Y sample position within the tile
```

## Source note 684, line 5041

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5041)

```text
// r0.z = sample offset in the EDRAM without the depth column swapping
```

## Source note 685, line 5042

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5042)

```text
// r0.w = non-wrapped tile index in the EDRAM
```

## Source note 686, line 5043

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5043)

```text
// r1.x = depth half-tile flipping offset
```

## Source note 687, line 5046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5046)

```text
// Swap 40-sample columns in the depth buffer in the destination address in
```

## Source note 688, line 5047

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5047)

```text
// r0.w to get the final address of the sample in EDRAM.
```

## Source note 689, line 5048

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5048)

```text
// r0.x = X sample position within the tile
```

## Source note 690, line 5049

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5049)

```text
// r0.y = Y sample position within the tile
```

## Source note 691, line 5050

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5050)

```text
// r0.z = sample offset in the EDRAM
```

## Source note 692, line 5051

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5051)

```text
// r0.w = non-wrapped tile index in the EDRAM
```

## Source note 693, line 5052

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5052)

```text
// r1.x = free
```

## Source note 694, line 5057

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5057)

```text
// Extract the source texture base tile index to r1.x.
```

## Source note 695, line 5058

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5058)

```text
// r0.x = X sample position within the tile
```

## Source note 696, line 5059

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5059)

```text
// r0.y = Y sample position within the tile
```

## Source note 697, line 5060

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5060)

```text
// r0.z = sample offset in the EDRAM
```

## Source note 698, line 5061

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5061)

```text
// r0.w = non-wrapped tile index in the EDRAM
```

## Source note 699, line 5062

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5062)

```text
// r1.x = source texture base tile index
```

## Source note 700, line 5066

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5066)

```text
// Get the linear tile index within the source texture to r0.w.
```

## Source note 701, line 5067

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5067)

```text
// r0.x = X sample position within the tile
```

## Source note 702, line 5068

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5068)

```text
// r0.y = Y sample position within the tile
```

## Source note 703, line 5069

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5069)

```text
// r0.z = sample offset in the EDRAM
```

## Source note 704, line 5070

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5070)

```text
// r0.w = linear tile index in the source texture
```

## Source note 705, line 5071

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5071)

```text
// r1.x = free
```

## Source note 706, line 5074

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5074)

```text
// Get the source texture pitch in tiles to r1.x.
```

## Source note 707, line 5075

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5075)

```text
// r0.x = X sample position within the tile
```

## Source note 708, line 5076

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5076)

```text
// r0.y = Y sample position within the tile
```

## Source note 709, line 5077

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5077)

```text
// r0.z = sample offset in the EDRAM
```

## Source note 710, line 5078

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5078)

```text
// r0.w = linear tile index in the source texture
```

## Source note 711, line 5079

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5079)

```text
// r1.x = source texture pitch in tiles
```

## Source note 712, line 5083

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5083)

```text
// Split the linear tile index in the source texture into X and Y in tiles.
```

## Source note 713, line 5084

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5084)

```text
// r0.x = X sample position within the tile
```

## Source note 714, line 5085

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5085)

```text
// r0.y = Y sample position within the tile
```

## Source note 715, line 5086

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5086)

```text
// r0.z = sample offset in the EDRAM
```

## Source note 716, line 5087

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5087)

```text
// r0.w = X tile index within the tile row in the source texture
```

## Source note 717, line 5088

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5088)

```text
// r1.x = Y tile row index within the source texture
```

## Source note 718, line 5091

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5091)

```text
// Add the source texture tile X offset to the source texture sample X
```

## Source note 719, line 5092

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5092)

```text
// coordinate.
```

## Source note 720, line 5093

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5093)

```text
// r0.x = X sample position within the source texture
```

## Source note 721, line 5094

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5094)

```text
// r0.y = Y sample position within the tile
```

## Source note 722, line 5095

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5095)

```text
// r0.z = sample offset in the EDRAM
```

## Source note 723, line 5096

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5096)

```text
// r0.w = free
```

## Source note 724, line 5097

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5097)

```text
// r1.x = Y tile row index within the source texture
```

## Source note 725, line 5100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5100)

```text
// Add the source texture tile Y offset to the source texture sample Y
```

## Source note 726, line 5101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5101)

```text
// coordinate.
```

## Source note 727, line 5102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5102)

```text
// r0.x = X sample position within the source texture
```

## Source note 728, line 5103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5103)

```text
// r0.y = Y sample position within the source texture
```

## Source note 729, line 5104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5104)

```text
// r0.z = sample offset in the EDRAM
```

## Source note 730, line 5105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5105)

```text
// r1.x = free
```

## Source note 731, line 5109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5109)

```text
// Will be using the source texture coordinates from r0.xy, and for
```

## Source note 732, line 5110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5110)

```text
// single-sampled source, LOD from r0.w.
```

## Source note 733, line 5113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5113)

```text
// r0.xy holds the canonical sample coordinates within the EDRAM layout.
```

## Source note 734, line 5114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5114)

```text
// Convert them into the pixel and the sample of the multisampled view
```

## Source note 735, line 5115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5115)

```text
// using the canonical layout formulas (xenia-canary #1163), at guest pixel
```

## Source note 736, line 5116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5116)

```text
// granularity when the layout is scaled.
```

## Source note 737, line 5121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5121)

```text
// r0.xy = guest canonical sample coordinates
```

## Source note 738, line 5122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5122)

```text
// r1.xy = subpixel within the guest sample
```

## Source note 739, line 5127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5127)

```text
// The 4x sample index has bit 0 horizontal and bit 1 vertical, same as
```

## Source note 740, line 5128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5128)

```text
// the canonical layout.
```

## Source note 741, line 5129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5129)

```text
// r0.w = horizontal sample index = (u >> 1) & 1
```

## Source note 742, line 5132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5132)

```text
// r1.z = vertical sample index = (v >> 1) & 1
```

## Source note 743, line 5135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5135)

```text
// r0.w = sample index within the source pixel
```

## Source note 744, line 5138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5138)

```text
// Guest pixel per axis = ((c >> 2) << 1) | (c & 1).
```

## Source note 745, line 5139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5139)

```text
// r1.z = u >> 2
```

## Source note 746, line 5141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5141)

```text
// r0.x = X guest pixel position
```

## Source note 747, line 5144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5144)

```text
// r1.z = v >> 2
```

## Source note 748, line 5146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5146)

```text
// r0.y = Y guest pixel position
```

## Source note 749, line 5150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5150)

```text
// 2x MSAA source texture sample index.
```

## Source note 750, line 5151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5151)

```text
// r0.w = guest vertical sample index = (u >> 1) & 1
```

## Source note 751, line 5154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5154)

```text
// Guest pixel X = (u & ~2) | (v & 2).
```

## Source note 752, line 5155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5155)

```text
// r1.z = v & 2
```

## Source note 753, line 5157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5157)

```text
// r0.x = (u & ~2)
```

## Source note 754, line 5160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5160)

```text
// r0.x = X guest pixel position
```

## Source note 755, line 5163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5163)

```text
// Guest pixel Y = ((v & ~3) >> 1) | (v & 1).
```

## Source note 756, line 5164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5164)

```text
// r1.z = v & 1
```

## Source note 757, line 5166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5166)

```text
// r0.y = v & ~3
```

## Source note 758, line 5169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5169)

```text
// r0.y = (v & ~3) >> 1
```

## Source note 759, line 5171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5171)

```text
// r0.y = Y guest pixel position
```

## Source note 760, line 5174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5174)

```text
// Convert the 2x MSAA sample index from the guest to Direct3D 10.1+.
```

## Source note 761, line 5175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5175)

```text
// r0.w = sample index within the source pixel
```

## Source note 762, line 5181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5181)

```text
// Restore the subpixel position.
```

## Source note 763, line 5182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5182)

```text
// r0.xy = XY pixel position within the source texture
```

## Source note 764, line 5186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5186)

```text
// Load the source to r1.
```

## Source note 765, line 5187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5187)

```text
// r0.x = X pixel position within the source texture if stencil is needed
```

## Source note 766, line 5188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5188)

```text
// r0.y = Y pixel position within the source texture if stencil is needed
```

## Source note 767, line 5189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5189)

```text
// r0.z = sample offset in the EDRAM
```

## Source note 768, line 5190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5190)

```text
// r0.w = sample index within the source pixel if stencil is needed
```

## Source note 769, line 5191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5191)

```text
// r1 = source texel value
```

## Source note 770, line 5195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5195)

```text
// Load the source stencil to r1.y.
```

## Source note 771, line 5196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5196)

```text
// r0.x = free
```

## Source note 772, line 5197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5197)

```text
// r0.y = free
```

## Source note 773, line 5198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5198)

```text
// r0.z = sample offset in the EDRAM
```

## Source note 774, line 5199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5199)

```text
// r0.w = free
```

## Source note 775, line 5200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5200)

```text
// r1.x = source depth value
```

## Source note 776, line 5201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5201)

```text
// r1.y = source stencil value
```

## Source note 777, line 5206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5206)

```text
// Write the LOD index (0) to the register with texture coordinates for
```

## Source note 778, line 5207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5207)

```text
// loading from the single-sampled source texture.
```

## Source note 779, line 5208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5208)

```text
// r0.x = X pixel position within the source texture
```

## Source note 780, line 5209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5209)

```text
// r0.y = Y pixel position within the source texture
```

## Source note 781, line 5210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5210)

```text
// r0.z = sample offset in the EDRAM
```

## Source note 782, line 5211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5211)

```text
// r0.w = LOD for the texture load (zero)
```

## Source note 783, line 5213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5213)

```text
// Load the source to r1.
```

## Source note 784, line 5214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5214)

```text
// r0.x = X pixel position within the source texture if stencil is needed
```

## Source note 785, line 5215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5215)

```text
// r0.y = Y pixel position within the source texture if stencil is needed
```

## Source note 786, line 5216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5216)

```text
// r0.z = sample offset in the EDRAM
```

## Source note 787, line 5217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5217)

```text
// r0.w = LOD for the texture load (zero)
```

## Source note 788, line 5218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5218)

```text
// r1 = source texel value
```

## Source note 789, line 5222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5222)

```text
// Load the source stencil to r1.y.
```

## Source note 790, line 5223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5223)

```text
// r0.x = free
```

## Source note 791, line 5224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5224)

```text
// r0.y = free
```

## Source note 792, line 5225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5225)

```text
// r0.z = sample offset in the EDRAM
```

## Source note 793, line 5226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5226)

```text
// r0.w = free
```

## Source note 794, line 5227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5227)

```text
// r1.x = source depth value
```

## Source note 795, line 5228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5228)

```text
// r1.y = source stencil value
```

## Source note 796, line 5233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5233)

```text
// Pack in the needed format, writing the result to r1.x for 32bpp or r1.xy
```

## Source note 797, line 5234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5234)

```text
// for 64bpp.
```

## Source note 798, line 5235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5235)

```text
// r0.xyw are usable as temporary storage.
```

## Source note 799, line 5239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5239)

```text
// Round to the nearest even integer. This seems to be the correct
```

## Source note 800, line 5240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5240)

```text
// conversion, adding +0.5 and rounding towards zero results in red
```

## Source note 801, line 5241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5241)

```text
// instead of black in the 4D5307E6 clear shader.
```

## Source note 802, line 5248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5248)

```text
// Convert to [0, 2) float24 from [0, 1) float32, using r0.x as
```

## Source note 803, line 5249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5249)

```text
// temporary.
```

## Source note 804, line 5250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5250)

```text
// When converting the depth in pixel shaders, it's always exact,
```

## Source note 805, line 5251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5251)

```text
// truncating not to insert additional rounding instructions.
```

## Source note 806, line 5257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5257)

```text
// Combine 24-bit depth and stencil into r1.x.
```

## Source note 807, line 5263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5263)

```text
// 8_8_8_8_GAMMA is represented by linear stored in
```

## Source note 808, line 5264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5264)

```text
// R16G16B16A16_UNORM.
```

## Source note 809, line 5300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5300)

```text
// Float16 has a wider range for both color and alpha, also NaNs.
```

## Source note 810, line 5301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5301)

```text
// Color - clamp and convert.
```

## Source note 811, line 5302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5302)

```text
// Convert red in r1.x to the result register r1.x - the same, but
```

## Source note 812, line 5303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5303)

```text
// UnclampedFloat32To7e3 allows that - using r0.x as a temporary.
```

## Source note 813, line 5306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5306)

```text
// Convert green and blue to a temporary register r0.x using r0.y
```

## Source note 814, line 5307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5307)

```text
// as an internal temporary, then insert them into the result in
```

## Source note 815, line 5308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5308)

```text
// r1.x.
```

## Source note 816, line 5313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5313)

```text
// Alpha - saturate and convert.
```

## Source note 817, line 5336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5336)

```text
// Already has the needed representation.
```

## Source note 818, line 5341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5341)

```text
// Write the sample to the destination address stored in r0.z.
```

## Source note 819, line 5347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5347)

```text
// Write the shader program length in dwords.
```

## Source note 820, line 5377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5377)

```text
// Container header
```

## Source note 821, line 5411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5411)

```text
// Even if creation fails, still store the null pointer not to try to create
```

## Source note 822, line 5412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5412)

```text
// again.
```

## Source note 823, line 5424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5424)

```text
// Until dedicated direct host RT -> shared memory shaders are added, reuse
```

## Source note 824, line 5425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5425)

```text
// the resolve copy pipelines to keep all resolve shader modes wired for the
```

## Source note 825, line 5426

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5426)

```text
// direct preflight path.
```

## Source note 826, line 5477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5477)

```text
// Dedicated direct resolve dispatches are staged behind the same preflight;
```

## Source note 827, line 5478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5478)

```text
// keep using the existing dump path until source-image direct shaders land.
```

## Source note 828, line 5492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5492)

```text
// Clear previously set temporary indices.
```

## Source note 829, line 5499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5499)

```text
// Gather all needed barriers and info needed to create descriptors and to
```

## Source note 830, line 5500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5500)

```text
// sort the invocations.
```

## Source note 831, line 5533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5533)

```text
// 32bpp and 64bpp.
```

## Source note 832, line 5550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5550)

```text
// Copy source descriptors to a shader-visible heap.
```

## Source note 833, line 5564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5564)

```text
// Sort the invocations to reduce context and binding switches.
```

## Source note 834, line 5567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5567)

```text
// Dump the render targets.
```

## Source note 835, line 5687

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5687)

```text
// Processing 40 x 16 x scale samples per dispatch (a 32bpp tile in two
```

## Source note 836, line 5688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5688)

```text
// dispatches at 1x1 scale, 64bpp in one dispatch).
```

## Source note 837, line 5698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/render_target_cache.cpp#L5698)

```text
// namespace rex::graphics::d3d12
```
