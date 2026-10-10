# Command processor: graphics source notes

This record preserves technical and API notes moved from `src/graphics/d3d12/command_processor.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L75)

```text
// Adds the host ticks of its lifetime to a frame timing counter.
```

## Source note 2, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L91)

```text
// Generated with `xb buildshaders`.
```

## Source note 3, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L103)

```text
// PIX event colors by phase.
```

## Source note 4, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L202)

```text
// Strict ZPD just needs the completed submission updated and any ready query
```

## Source note 5, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L203)

```text
// resolves drained here.
```

## Source note 6, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L271)

```text
// Better put the pixel texture/sampler in the lower bits probably because it
```

## Source note 7, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L272)

```text
// changes often.
```

## Source note 8, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L287)

```text
// Try an existing root signature.
```

## Source note 9, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L293)

```text
// Create a new one.
```

## Source note 10, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L302)

```text
// Base parameters.
```

## Source note 11, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L304)

```text
// Fetch constants.
```

## Source note 12, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L314)

```text
// Vertex float constants.
```

## Source note 13, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L324)

```text
// Pixel float constants.
```

## Source note 14, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L334)

```text
// System constants.
```

## Source note 15, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L344)

```text
// Bool and loop constants.
```

## Source note 16, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L354)

```text
// Shared memory and, if ROVs are used, EDRAM.
```

## Source note 17, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L383)

```text
// ROV occlusion query counter slots.
```

## Source note 18, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L392)

```text
// Hybrid occlusion query counter slots (RTV, full counters).
```

## Source note 19, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L403)

```text
// Extra parameters.
```

## Source note 20, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L405)

```text
// Pixel textures.
```

## Source note 21, line 422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L422)

```text
// Pixel samplers.
```

## Source note 22, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L438)

```text
// Vertex textures.
```

## Source note 23, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L455)

```text
// Vertex samplers.
```

## Source note 24, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L521)

```text
// There was an error.
```

## Source note 25, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L565)

```text
// Request separate bindless descriptors that will be freed when this
```

## Source note 26, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L566)

```text
// submission is completed by the GPU.
```

## Source note 27, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L586)

```text
// Request a range within the current heap for bindful resources path.
```

## Source note 28, line 705

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L705)

```text
// There was an error.
```

## Source note 29, line 784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L784)

```text
// Force-invalidate because setting a non-guest root signature.
```

## Source note 30, line 834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L834)

```text
// Rasterizer-ordered views are a feature very rarely used as of 2020 and
```

## Source note 31, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L835)

```text
// that faces adoption complications (outside of Direct3D - on Vulkan - at
```

## Source note 32, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L836)

```text
// least), but crucial to Xenia - raise awareness of its usage.
```

## Source note 33, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L837)

```text
// https://github.com/KhronosGroup/Vulkan-Ecosystem/issues/27#issuecomment-455712319
```

## Source note 34, line 838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L838)

```text
// "In Xenia's title bar "D3D12 ROV" can be seen, which was a surprise, as I
```

## Source note 35, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L839)

```text
//  wasn't aware that Xenia D3D12 backend was using Raster Order Views
```

## Source note 36, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L840)

```text
//  feature" - oscarbg in that issue.
```

## Source note 37, line 891

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L891)

```text
// Create the command list and one allocator because it's needed for a command
```

## Source note 38, line 892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L892)

```text
// list.
```

## Source note 39, line 909

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L909)

```text
// Initially in open state, wait until a deferred command list submission.
```

## Source note 40, line 911

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L911)

```text
// Optional - added in Creators Update (SDK 10.0.15063.0).
```

## Source note 41, line 917

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L917)

```text
// Get the draw resolution scale for the render target cache and the texture
```

## Source note 42, line 918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L918)

```text
// cache.
```

## Source note 43, line 939

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L939)

```text
// Initialize the render target cache before configuring binding - need to
```

## Source note 44, line 940

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L940)

```text
// know if using rasterizer-ordered views for the bindless root signature.
```

## Source note 45, line 949

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L949)

```text
// Hybrid RTV queries count pre-test coverage in the pixel shader, so the
```

## Source note 46, line 950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L950)

```text
// root signatures below need the counter UAV. The counter slots are cleared
```

## Source note 47, line 951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L951)

```text
// with copies, so any command list works.
```

## Source note 48, line 956

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L956)

```text
// Initialize resource binding.
```

## Source note 49, line 998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L998)

```text
// Global bindless resource root signatures.
```

## Source note 50, line 999

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L999)

```text
// No CBV or UAV descriptor ranges with any descriptors to be allocated
```

## Source note 51, line 1000

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1000)

```text
// dynamically (via RequestPersistentViewBindlessDescriptor or
```

## Source note 52, line 1001

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1001)

```text
// RequestOneUseSingleViewDescriptors) should be here, because they would
```

## Source note 53, line 1002

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1002)

```text
// overlap the unbounded SRV range, which is not allowed on Nvidia Fermi!
```

## Source note 54, line 1011

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1011)

```text
// Fetch constants.
```

## Source note 55, line 1020

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1020)

```text
// Vertex float constants.
```

## Source note 56, line 1029

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1029)

```text
// Pixel float constants.
```

## Source note 57, line 1038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1038)

```text
// Pixel shader descriptor indices.
```

## Source note 58, line 1047

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1047)

```text
// Vertex shader descriptor indices.
```

## Source note 59, line 1056

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1056)

```text
// System constants.
```

## Source note 60, line 1065

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1065)

```text
// Bool and loop constants.
```

## Source note 61, line 1074

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1074)

```text
// Shared memory SRV and UAV.
```

## Source note 62, line 1100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1100)

```text
// Sampler heap.
```

## Source note 63, line 1105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1105)

```text
// Will be appending.
```

## Source note 64, line 1115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1115)

```text
// View heap.
```

## Source note 65, line 1120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1120)

```text
// Will be appending.
```

## Source note 66, line 1124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1124)

```text
// EDRAM.
```

## Source note 67, line 1135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1135)

```text
// ROV (and hybrid RTV) occlusion query counter slots.
```

## Source note 68, line 1147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1147)

```text
// Used UAV and SRV ranges must not overlap on Nvidia Fermi, so textures
```

## Source note 69, line 1148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1148)

```text
// have OffsetInDescriptorsFromTableStart after all static descriptors of
```

## Source note 70, line 1149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1149)

```text
// other types.
```

## Source note 71, line 1150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1150)

```text
// 2D array textures.
```

## Source note 72, line 1161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1161)

```text
// 3D textures.
```

## Source note 73, line 1172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1172)

```text
// Cube textures.
```

## Source note 74, line 1209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1209)

```text
// xenia-edge's fixed root signature for Mesa spirv_to_dxil output.
```

## Source note 75, line 1233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1233)

```text
// Unbounded ranges for the texture / sampler declarations the bindless
```

## Source note 76, line 1234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1234)

```text
// lowering leaves behind (never dereferenced).
```

## Source note 77, line 1257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1257)

```text
// Shared memory t0 + u0, then the ZPD counter u1 and EDRAM u2.
```

## Source note 78, line 1287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1287)

```text
// The bindless lowering indexes ResourceDescriptorHeap and
```

## Source note 79, line 1288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1288)

```text
// SamplerDescriptorHeap directly.
```

## Source note 80, line 1324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1324)

```text
// Create gamma ramp resources.
```

## Source note 81, line 1330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1330)

```text
// The first action will be uploading.
```

## Source note 82, line 1339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1339)

```text
// The upload buffer is frame-buffered.
```

## Source note 83, line 1355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1355)

```text
// Initialize compute pipelines for output with gamma ramp.
```

## Source note 84, line 1463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1463)

```text
// Initialize compute pipelines for post-processing anti-aliasing.
```

## Source note 85, line 1544

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1544)

```text
// Resolve downscale compute pipeline for scaled readback resolve.
```

## Source note 86, line 1606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1606)

```text
// Create the system bindless descriptors once all resources are
```

## Source note 87, line 1607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1607)

```text
// initialized.
```

## Source note 88, line 1608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1608)

```text
// kNullRawSRV.
```

## Source note 89, line 1614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1614)

```text
// kNullRawUAV.
```

## Source note 90, line 1620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1620)

```text
// kNullTexture2DArray.
```

## Source note 91, line 1637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1637)

```text
// kNullTexture3D.
```

## Source note 92, line 1646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1646)

```text
// kNullTextureCube.
```

## Source note 93, line 1655

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1655)

```text
// kSharedMemoryRawSRV.
```

## Source note 94, line 1658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1658)

```text
// kSharedMemoryR32UintSRV.
```

## Source note 95, line 1663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1663)

```text
// kSharedMemoryR32G32UintSRV.
```

## Source note 96, line 1668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1668)

```text
// kSharedMemoryR32G32B32A32UintSRV.
```

## Source note 97, line 1674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1674)

```text
// kSharedMemoryRawUAV.
```

## Source note 98, line 1677

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1677)

```text
// kSharedMemoryRawSRVForUAV and kSharedMemoryRawUAVWithSRV.
```

## Source note 99, line 1682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1682)

```text
// kSharedMemoryR32UintUAV.
```

## Source note 100, line 1687

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1687)

```text
// kSharedMemoryR32G32UintUAV.
```

## Source note 101, line 1692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1692)

```text
// kSharedMemoryR32G32B32A32UintUAV.
```

## Source note 102, line 1698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1698)

```text
// kEdramRawSRV.
```

## Source note 103, line 1701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1701)

```text
// kEdramR32UintSRV.
```

## Source note 104, line 1706

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1706)

```text
// kEdramR32G32UintSRV.
```

## Source note 105, line 1711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1711)

```text
// kEdramR32G32B32A32UintSRV.
```

## Source note 106, line 1716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1716)

```text
// kEdramRawUAV.
```

## Source note 107, line 1719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1719)

```text
// kEdramR32UintUAV.
```

## Source note 108, line 1724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1724)

```text
// kEdramR32G32UintUAV.
```

## Source note 109, line 1729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1729)

```text
// kEdramR32G32B32A32UintUAV.
```

## Source note 110, line 1734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1734)

```text
// kGammaRampTableSRV.
```

## Source note 111, line 1738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1738)

```text
// kGammaRampPWLSRV.
```

## Source note 112, line 1744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1744)

```text
// Null until EnsureZPDQueryResources creates the ROV counter slots.
```

## Source note 113, line 1753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1753)

```text
// ZPD occlusion query pool. Its resources aren't created in the fake mode.
```

## Source note 114, line 1759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1759)

```text
// Just not to expose uninitialized memory.
```

## Source note 115, line 1765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1765)

```text
// Guest frame 1 starts now.
```

## Source note 116, line 1777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1777)

```text
// Frame N is the work between swap N - 1 and the end of swap N.
```

## Source note 117, line 1792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1792)

```text
// The title stopped inside the captured frame: keep what was recorded.
```

## Source note 118, line 1867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1867)

```text
// Unmapping will be done implicitly by the destruction.
```

## Source note 119, line 1878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1878)

```text
// Shut down binding - bindless descriptors may be owned by subsystems like
```

## Source note 120, line 1879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1879)

```text
// the texture cache.
```

## Source note 121, line 1881

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1881)

```text
// Root signatures are used by pipelines, thus freed after the pipelines.
```

## Source note 122, line 1921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L1921)

```text
// First release the fences since they may reference fence_completion_event_.
```

## Source note 123, line 2089

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2089)

```text
// Counts the swap for d3d12_capture_frame on every return path, after the
```

## Source note 124, line 2090

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2090)

```text
// frame's last submission.
```

## Source note 125, line 2110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2110)

```text
// In case the swap command is the only one in the frame.
```

## Source note 126, line 2118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2118)

```text
// Obtain the actual swap source texture size (resolution-scaled if it's a
```

## Source note 127, line 2119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2119)

```text
// resolve destination, or not otherwise).
```

## Source note 128, line 2127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2127)

```text
// Dump texture fetch constant 0 for debugging
```

## Source note 129, line 2136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2136)

```text
// The swap gamma / FXAA pass samples source texels by pixel index, but swap
```

## Source note 130, line 2137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2137)

```text
// textures may be allocation-padded. Prefer the active frontbuffer region
```

## Source note 131, line 2138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2138)

```text
// from the swap packet, scaled proportionally to the actual source texture.
```

## Source note 132, line 2203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2203)

```text
// Make sure the texture of the correct size is available for FXAA.
```

## Source note 133, line 2241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2241)

```text
// This is according to D3D::InitializePresentationParameters from a
```

## Source note 134, line 2242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2242)

```text
// game executable, which initializes the 256-entry table gamma ramp for
```

## Source note 135, line 2243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2243)

```text
// 8_8_8_8 output and the PWL gamma ramp for 2_10_10_10.
```

## Source note 136, line 2251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2251)

```text
// Upload the new gamma ramp, using the upload buffer for the current
```

## Source note 137, line 2252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2252)

```text
// frame (will close the frame after this anyway, so can't write
```

## Source note 138, line 2253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2253)

```text
// multiple times per frame).
```

## Source note 139, line 2262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2262)

```text
// R16G16 is first R16, where the shader expects the base, and
```

## Source note 140, line 2263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2263)

```text
// second G16, where the delta should be, but gamma_ramp_pwl_rgb()
```

## Source note 141, line 2264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2264)

```text
// is an array of 32-bit DC_LUT_PWL_DATA registers - swap 16 bits in
```

## Source note 142, line 2265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2265)

```text
// each 32.
```

## Source note 143, line 2293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2293)

```text
// Destination, source, and if bindful, gamma ramp.
```

## Source note 144, line 2300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2300)

```text
// Must not call anything that can change the descriptor heap from now
```

## Source note 145, line 2301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2301)

```text
// on!
```

## Source note 146, line 2328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2328)

```text
// From now on, even in case of failure, apply_gamma_dest must be
```

## Source note 147, line 2329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2329)

```text
// transitioned back to apply_gamma_dest_initial_state!
```

## Source note 148, line 2373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2373)

```text
// Apply FXAA.
```

## Source note 149, line 2375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2375)

```text
// Destination and source.
```

## Source note 150, line 2379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2379)

```text
// Failed to obtain descriptors for FXAA - just copy after gamma
```

## Source note 151, line 2380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2380)

```text
// ramp application without applying FXAA.
```

## Source note 152, line 2401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2401)

```text
// From now on, even in case of failure, guest_output_resource must
```

## Source note 153, line 2402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2402)

```text
// be transitioned back to kGuestOutputInternalState!
```

## Source note 154, line 2448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2448)

```text
// Need to submit all the commands before giving the image back to the
```

## Source note 155, line 2449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2449)

```text
// presenter so it can submit its own commands for displaying it to the
```

## Source note 156, line 2450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2450)

```text
// queue.
```

## Source note 157, line 2456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2456)

```text
// End the frame even if did not present for any reason (the image refresher
```

## Source note 158, line 2457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2457)

```text
// was not called), to prevent leaking per-frame resources.
```

## Source note 159, line 2462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2462)

```text
// Pump any completed resolves now since the guest is likely about to poll.
```

## Source note 160, line 2488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2488)

```text
// VIZ survey geometry for one of the 64 IDs. draw_util keeps it normalized,
```

## Source note 161, line 2489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2489)

```text
// so it only counts coverage here (xenia-canary #1111).
```

## Source note 162, line 2494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2494)

```text
// Special copy handling.
```

## Source note 163, line 2504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2504)

```text
// Vertex shader analysis.
```

## Source note 164, line 2507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2507)

```text
// Always need a vertex shader.
```

## Source note 165, line 2513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2513)

```text
// Pixel shader analysis.
```

## Source note 166, line 2517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2517)

```text
// Doesn't actually draw.
```

## Source note 167, line 2518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2518)

```text
// Unlikely that zero would even really be legal though.
```

## Source note 168, line 2523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2523)

```text
// See xenos::EdramMode for explanation why the pixel shader is only used
```

## Source note 169, line 2524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2524)

```text
// when it's kColorDepth here.
```

## Source note 170, line 2535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2535)

```text
// Disabling pixel shader for this case is also required by the pipeline
```

## Source note 171, line 2536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2536)

```text
// cache.
```

## Source note 172, line 2538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2538)

```text
// This draw has no effect.
```

## Source note 173, line 2545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2545)

```text
// A draw contributing to its VIZ ID without the kill bit counts at hi-Z,
```

## Source note 174, line 2546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2546)

```text
// before the pixel shader can reject anything, which isn't measured here.
```

## Source note 175, line 2561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2561)

```text
// Process primitives.
```

## Source note 176, line 2567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2567)

```text
// Nothing to draw.
```

## Source note 177, line 2573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2573)

```text
// Shader modifications.
```

## Source note 178, line 2589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2589)

```text
// Hybrid occlusion query draw, counting coverage into the Total counter.
```

## Source note 179, line 2590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2590)

```text
// Only depth or stencil tested draws without depth writes: scene geometry
```

## Source note 180, line 2591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2591)

```text
// keeps early depth rejection, and nothing can fail without a test.
```

## Source note 181, line 2592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2592)

```text
// Surveys never count for a report.
```

## Source note 182, line 2596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2596)

```text
// For drawing without the counting while the pipeline is being created.
```

## Source note 183, line 2601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2601)

```text
// The counter UAV write disables early depth / stencil.
```

## Source note 184, line 2609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2609)

```text
// Set up the render targets - this may perform dispatches and draws.
```

## Source note 185, line 2621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2621)

```text
// Create the pipeline (for this, need the actually used render target formats
```

## Source note 186, line 2622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2622)

```text
// from the render target cache), translating the shaders - doing this now to
```

## Source note 187, line 2623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2623)

```text
// obtain the used textures.
```

## Source note 188, line 2647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2647)

```text
// SPIR-V -> DXIL (gpu_shader_path=dxil, RG-GDK-032) when this draw can take
```

## Source note 189, line 2648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2648)

```text
// it; the DXBC path otherwise.
```

## Source note 190, line 2682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2682)

```text
// Skipping a draw while its pipeline compiles is only harmless for a pass
```

## Source note 191, line 2683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2683)

```text
// redrawn every frame (has207/xenia-edge de8e60601). Wait for the real
```

## Source note 192, line 2684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2684)

```text
// pipeline instead for a render target not drawn recently (a one-off
```

## Source note 193, line 2685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2685)

```text
// render to a texture), a small one (generated data such as impostors or
```

## Source note 194, line 2686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2686)

```text
// lookup tables) or memexport, whose output isn't redone.
```

## Source note 195, line 2708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2708)

```text
// Draw without the Total counting rather than skip the draw while the
```

## Source note 196, line 2709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2709)

```text
// counting pipeline is created; the segment splits for it.
```

## Source note 197, line 2737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2737)

```text
// Update the textures - this may bind pipelines.
```

## Source note 198, line 2753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2753)

```text
// Bind the pipeline after configuring it and doing everything that may bind
```

## Source note 199, line 2754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2754)

```text
// other pipelines.
```

## Source note 200, line 2761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2761)

```text
// Get dynamic rasterizer state.
```

## Source note 201, line 2764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2764)

```text
// ZPD segments can't mix scales or hybrid Total counting. The resolved
```

## Source note 202, line 2765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2765)

```text
// sample count is divided by one scale area per segment. Split before the
```

## Source note 203, line 2766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2766)

```text
// counter index goes into the system constants.
```

## Source note 204, line 2773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2773)

```text
// Build a cache key from all viewport-affecting state to skip redundant
```

## Source note 205, line 2774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2774)

```text
// recalculation when the viewport registers haven't changed between draws.
```

## Source note 206, line 2807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2807)

```text
// Update viewport, scissor, blend factor and stencil reference.
```

## Source note 207, line 2820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2820)

```text
// Update system constants before uploading them.
```

## Source note 208, line 2827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2827)

```text
// Update constant buffers, descriptors and root parameters.
```

## Source note 209, line 2832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2832)

```text
// Must not call anything that can change the descriptor heap from now on!
```

## Source note 210, line 2834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2834)

```text
// Ensure vertex buffers are resident.
```

## Source note 211, line 2861

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2861)

```text
// A texture type (xenia-canary b083312b8): some titles draw with
```

## Source note 212, line 2862

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2862)

```text
// these, and dropping the draw loses whole models.
```

## Source note 213, line 2892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2892)

```text
// Gather memexport ranges and ensure the heaps for them are resident, and
```

## Source note 214, line 2893

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2893)

```text
// also load the data surrounding the export and to fill the regions that
```

## Source note 215, line 2894

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2894)

```text
// won't be modified by the shaders.
```

## Source note 216, line 2921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2921)

```text
// Primitive topology.
```

## Source note 217, line 2982

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2982)

```text
// Must not call anything that may change the primitive topology from now on!
```

## Source note 218, line 2984

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2984)

```text
// Consumer VIZ draws run under SetPredication instead of blocking.
```

## Source note 219, line 2985

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2985)

```text
// EQUAL_ZERO skips the draw only when the survey saw nothing.
```

## Source note 220, line 2996

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L2996)

```text
// Draw.
```

## Source note 221, line 3031

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3031)

```text
// If the shared memory is a UAV, it can't be used as an index buffer
```

## Source note 222, line 3032

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3032)

```text
// (UAV is a read/write state, index buffer is a read-only state).
```

## Source note 223, line 3033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3033)

```text
// Need to copy the indices to a buffer in the index buffer state.
```

## Source note 224, line 3089

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3089)

```text
// Make sure this memexporting draw is ordered with other work using shared
```

## Source note 225, line 3090

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3090)

```text
// memory as a UAV.
```

## Source note 226, line 3093

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3093)

```text
// Invalidate textures in memexported memory and watch for changes.
```

## Source note 227, line 3100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3100)

```text
// Stream constants can be invalid or dynamic, so exact destinations may
```

## Source note 228, line 3101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3101)

```text
// be unknown. Keep invalidation conservative in this case.
```

## Source note 229, line 3299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3299)

```text
// Downscales the scaled resolve of [address, address + length) - already
```

## Source note 230, line 3300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3300)

```text
// aligned to whole scaled addressing groups - into `dest` at `dest_offset`,
```

## Source note 231, line 3301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3301)

```text
// keeping each guest texel's top-left host sample, or its center with
```

## Source note 232, line 3302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3302)

```text
// `center`. Leaves a UAV barrier on `dest` pending.
```

## Source note 233, line 3396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3396)

```text
// A native resolve (ADR-012) left its data in shared memory.
```

## Source note 234, line 3399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3399)

```text
// Scaled readback covers whole scaled addressing groups only (see below).
```

## Source note 235, line 3445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3445)

```text
// As in xenia-canary a635ac64f, the texel size comes from the normalized
```

## Source note 236, line 3446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3446)

```text
// destination info the extent was calculated with, and the source window
```

## Source note 237, line 3447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3447)

```text
// starts at the written extent's scaled address. The shader reads the
```

## Source note 238, line 3448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3448)

```text
// scaled layout of this repository's resolve shaders (see
```

## Source note 239, line 3449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3449)

```text
// resolve_downscale.cs.hlsl).
```

## Source note 240, line 3457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3457)

```text
// Keep the start aligned to whole scaled units (Canary's 128-byte groups
```

## Source note 241, line 3458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3458)

```text
// are a multiple of them).
```

## Source note 242, line 3467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3467)

```text
// Units map independently, so any whole number of groups can be read back
```

## Source note 243, line 3468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3468)

```text
// (Canary truncates to whole 32x32 tiles instead).
```

## Source note 244, line 3564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3564)

```text
// Ending an open submission should result in queue operations done directly
```

## Source note 245, line 3565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3565)

```text
// (like UpdateTileMappings) to be tracked within the scope of that
```

## Source note 246, line 3566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3566)

```text
// submission, but just in case of a failure, or queue operations being done
```

## Source note 247, line 3567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3567)

```text
// outside of a submission, await explicitly.
```

## Source note 248, line 3584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3584)

```text
// A submission won't be ended if it hasn't been started, or if ending
```

## Source note 249, line 3585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3585)

```text
// has failed - clamp the index.
```

## Source note 250, line 3604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3604)

```text
// Not updated - no need to reclaim or download things.
```

## Source note 251, line 3608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3608)

```text
// Reclaim command allocators.
```

## Source note 252, line 3626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3626)

```text
// Release single-use bindless descriptors.
```

## Source note 253, line 3635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3635)

```text
// Delete transient resources marked for deletion.
```

## Source note 254, line 3652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3652)

```text
// Pull completed query resolves so ZPD reports can retire.
```

## Source note 255, line 3724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3724)

```text
// Check if the device is still available.
```

## Source note 256, line 3737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3737)

```text
// Check the fence - needed for all kinds of submissions (to reclaim transient
```

## Source note 257, line 3738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3738)

```text
// resources early) and specifically for frames (not to queue too many), and
```

## Source note 258, line 3739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3739)

```text
// await the availability of the current frame.
```

## Source note 259, line 3744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3744)

```text
// Update the completed frame index, also obtaining the actual completed
```

## Source note 260, line 3745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3745)

```text
// frame number (since the CPU may be actually less than 3 frames behind)
```

## Source note 261, line 3746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3746)

```text
// before reclaiming resources tracked with the frame number.
```

## Source note 262, line 3759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3759)

```text
// Start a new deferred command list - will submit it to the real one in the
```

## Source note 263, line 3760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3760)

```text
// end of the submission (when async pipeline creation requests are
```

## Source note 264, line 3761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3761)

```text
// fulfilled).
```

## Source note 265, line 3763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3763)

```text
// Regions recorded outside a submission were dropped with the list.
```

## Source note 266, line 3766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3766)

```text
// Resume the active query segment.
```

## Source note 267, line 3769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3769)

```text
// Reset cached state of the command list.
```

## Source note 268, line 3798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3798)

```text
// Reset bindings that depend on the data stored in the pools.
```

## Source note 269, line 3828

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3828)

```text
// Reclaim pool pages - no need to do this every small submission since some
```

## Source note 270, line 3829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3829)

```text
// may be reused.
```

## Source note 271, line 3850

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3850)

```text
// Make sure there is a command allocator to write commands to.
```

## Source note 272, line 3856

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3856)

```text
// Try to submit later. Completely dropping the submission is not
```

## Source note 273, line 3857

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3857)

```text
// permitted because resources would be left in an undefined state.
```

## Source note 274, line 3878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3878)

```text
// We can't close the command list with an active query - D3D12 requirement.
```

## Source note 275, line 3879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3879)

```text
// Close the active segment and emit ResolveQueryData before executing.
```

## Source note 276, line 3880

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3880)

```text
// VIZ segments open even when ZPD is faked; both are no-ops without any.
```

## Source note 277, line 3888

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3888)

```text
// Submit barriers now because resources with the queued barriers may be
```

## Source note 278, line 3889

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3889)

```text
// destroyed between frames.
```

## Source note 279, line 3894

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3894)

```text
// Submit the deferred command list.
```

## Source note 280, line 3895

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3895)

```text
// Only one deferred command list must be executed in the same
```

## Source note 281, line 3896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3896)

```text
// ExecuteCommandLists - the boundaries of ExecuteCommandLists are a full
```

## Source note 282, line 3897

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3897)

```text
// UAV and aliasing barrier, and subsystems of the emulator assume it
```

## Source note 283, line 3898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3898)

```text
// happens between Xenia submissions.
```

## Source note 284, line 3903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3903)

```text
// A draw or swap region may still be open: end it with its command list.
```

## Source note 285, line 3910

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3910)

```text
// Queue events show each submission and its frame in PIX timing captures.
```

## Source note 286, line 3942

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3942)

```text
// Pump ZPD query process. This drains any resolves that became readable
```

## Source note 287, line 3943

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3943)

```text
// from completed work and retires reports unblocked by those resolves.
```

## Source note 288, line 3947

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3947)

```text
// Queue operations done directly (like UpdateTileMappings) will be awaited
```

## Source note 289, line 3948

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3948)

```text
// alongside the last submission if needed.
```

## Source note 290, line 3957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3957)

```text
// Submission already closed now, so minus 1.
```

## Source note 291, line 3983

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3983)

```text
// Not clearing the root signatures as they're referenced by pipelines,
```

## Source note 292, line 3984

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L3984)

```text
// which are not destroyed.
```

## Source note 293, line 4025

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4025)

```text
// Viewport.
```

## Source note 294, line 4035

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4035)

```text
// Scissor.
```

## Source note 295, line 4046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4046)

```text
// Blend factor.
```

## Source note 296, line 4053

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4053)

```text
// std::memcmp instead of != so in case of NaN, every draw won't be
```

## Source note 297, line 4054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4054)

```text
// invalidating it.
```

## Source note 298, line 4063

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4063)

```text
// Stencil reference value. Per-face reference not supported by Direct3D 12,
```

## Source note 299, line 4064

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4064)

```text
// choose the back face one only if drawing only back faces.
```

## Source note 300, line 4114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4114)

```text
// Get the color info register values for each render target. Also, for ROV,
```

## Source note 301, line 4115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4115)

```text
// exclude components that don't exist in the format from the write mask.
```

## Source note 302, line 4116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4116)

```text
// Don't exclude fully overlapping render targets, however - two render
```

## Source note 303, line 4117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4117)

```text
// targets with the same base address are used in the lighting pass of
```

## Source note 304, line 4118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4118)

```text
// 4D5307E6, for example, with the needed one picked with dynamic control
```

## Source note 305, line 4119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4119)

```text
// flow.
```

## Source note 306, line 4122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4122)

```text
// Two UINT32_MAX if no components actually existing in the RT are written.
```

## Source note 307, line 4134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4134)

```text
// Disable depth and stencil only if an aliased color target writes bits used
```

## Source note 308, line 4135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4135)

```text
// by either test. Otherwise its keep-masked store preserves them.
```

## Source note 309, line 4152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4152)

```text
// Flags.
```

## Source note 310, line 4154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4154)

```text
// Whether shared memory is an SRV or a UAV. Because a resource can't be in a
```

## Source note 311, line 4155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4155)

```text
// read-write (UAV) and a read-only (SRV, IBV) state at once, if any shader in
```

## Source note 312, line 4156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4156)

```text
// the pipeline uses memexport, the shared memory buffer must be a UAV.
```

## Source note 313, line 4160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4160)

```text
// W0 division control.
```

## Source note 314, line 4161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4161)

```text
// http://www.x.org/docs/AMD/old/evergreen_3D_registers_v2.pdf
```

## Source note 315, line 4162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4162)

```text
// 8: VTX_XY_FMT = true: the incoming XY have already been multiplied by 1/W0.
```

## Source note 316, line 4163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4163)

```text
//               = false: multiply the X, Y coordinates by 1/W0.
```

## Source note 317, line 4164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4164)

```text
// 9: VTX_Z_FMT = true: the incoming Z has already been multiplied by 1/W0.
```

## Source note 318, line 4165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4165)

```text
//              = false: multiply the Z coordinate by 1/W0.
```

## Source note 319, line 4166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4166)

```text
// 10: VTX_W0_FMT = true: the incoming W0 is not 1/W0. Perform the reciprocal
```

## Source note 320, line 4167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4167)

```text
//                        to get 1/W0.
```

## Source note 321, line 4177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4177)

```text
// Whether the primitive is polygonal and SV_IsFrontFace matters.
```

## Source note 322, line 4181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4181)

```text
// Primitive type.
```

## Source note 323, line 4185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4185)

```text
// Depth format.
```

## Source note 324, line 4189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4189)

```text
// Alpha test.
```

## Source note 325, line 4194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4194)

```text
// Gamma writing.
```

## Source note 326, line 4211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4211)

```text
// In case stencil is used without depth testing - always pass, and
```

## Source note 327, line 4212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4212)

```text
// don't modify the stored depth.
```

## Source note 328, line 4220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4220)

```text
// Hint - if not applicable to the shader, will not have effect.
```

## Source note 329, line 4229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4229)

```text
// Tessellation factor range, plus 1.0 according to the images in
```

## Source note 330, line 4230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4230)

```text
// https://www.slideshare.net/blackdevilvikas/next-generation-graphics-programming-on-xbox-360
```

## Source note 331, line 4238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4238)

```text
// Line loop closing index (or 0 when drawing other primitives or using an
```

## Source note 332, line 4239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4239)

```text
// index buffer).
```

## Source note 333, line 4243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4243)

```text
// Index or tessellation edge factor buffer endianness.
```

## Source note 334, line 4247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4247)

```text
// Vertex index offset.
```

## Source note 335, line 4251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4251)

```text
// Vertex index range.
```

## Source note 336, line 4257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4257)

```text
// User clip planes (UCP_ENA_#), when not CLIP_DISABLE.
```

## Source note 337, line 4258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4258)

```text
// The shader knows only the total count - tightly packing the user clip
```

## Source note 338, line 4259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4259)

```text
// planes that are actually used.
```

## Source note 339, line 4276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4276)

```text
// Conversion to Direct3D 12 normalized device coordinates.
```

## Source note 340, line 4284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4284)

```text
// Point size, and the NDC size of a guest pixel, which the line geometry
```

## Source note 341, line 4285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4285)

```text
// shader also uses to widen resolution-scaled lines.
```

## Source note 342, line 4304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4304)

```text
// 2 because 1 in the NDC is half of the viewport's axis, 0.5 for diameter
```

## Source note 343, line 4305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4305)

```text
// to radius conversion to avoid multiplying the per-vertex diameter by an
```

## Source note 344, line 4306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4306)

```text
// additional constant in the shader.
```

## Source note 345, line 4308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4308)

```text
/* 0.5f * 2.0f * */
```

## Source note 346, line 4311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4311)

```text
/* 0.5f * 2.0f * */
```

## Source note 347, line 4323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4323)

```text
// Texture signedness / gamma.
```

## Source note 348, line 4346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4346)

```text
// Log2 of sample count, for alpha to mask and with ROV, for EDRAM address
```

## Source note 349, line 4347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4347)

```text
// calculation with MSAA.
```

## Source note 350, line 4355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4355)

```text
// Alpha test and alpha to coverage.
```

## Source note 351, line 4367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4367)

```text
// EDRAM pitch for ROV writing.
```

## Source note 352, line 4369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4369)

```text
// Align, then multiply by 32bpp tile size in dwords.
```

## Source note 353, line 4380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4380)

```text
// Color exponent bias and ROV render target writing.
```

## Source note 354, line 4383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4383)

```text
// Exponent bias is in bits 20:25 of RB_COLOR_INFO.
```

## Source note 355, line 4389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4389)

```text
// Remap from -32...32 to -1...1 by dividing the output values by 32,
```

## Source note 356, line 4390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4390)

```text
// losing blending correctness, but getting the full range.
```

## Source note 357, line 4410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4410)

```text
// Can't do float comparisons here because NaNs would result in always
```

## Source note 358, line 4411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4411)

```text
// setting the dirty flag.
```

## Source note 359, line 4423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4423)

```text
// The open occlusion query's counter slot (ROV, or a hybrid RTV query), or
```

## Source note 360, line 4424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4424)

```text
// UINT32_MAX for none.
```

## Source note 361, line 4438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4438)

```text
// For non-polygons, front polygon offset is used, and it's enabled if
```

## Source note 362, line 4439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4439)

```text
// POLY_OFFSET_PARA_ENABLED is set, for polygons, separate front and back
```

## Source note 363, line 4440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4440)

```text
// are used.
```

## Source note 364, line 4460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4460)

```text
// With non-square resolution scaling, make sure the worst-case impact is
```

## Source note 365, line 4461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4461)

```text
// reverted (slope only along the scaled axis), thus max. More bias is
```

## Source note 366, line 4462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4462)

```text
// better than less bias, because less bias means Z fighting with the
```

## Source note 367, line 4463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4463)

```text
// background is more likely.
```

## Source note 368, line 4535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4535)

```text
// Set the new root signature.
```

## Source note 369, line 4542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4542)

```text
// Changing the root signature invalidates all bindings.
```

## Source note 370, line 4547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4547)

```text
// Select the root parameter indices depending on the used binding model.
```

## Source note 371, line 4568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4568)

```text
// Update root constant buffers that are common for bindful and bindless.
```

## Source note 372, line 4571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4571)

```text
// These are the constant base addresses/ranges for shaders.
```

## Source note 373, line 4572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4572)

```text
// We have these hardcoded right now cause nothing seems to differ on the Xbox
```

## Source note 374, line 4573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4573)

```text
// 360 (however, OpenGL ES on Adreno 200 on Android has different ranges).
```

## Source note 375, line 4578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4578)

```text
// Check if the float constant layout is still the same and get the counts.
```

## Source note 376, line 4585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4585)

```text
// If no float constants at all, we can reuse any buffer for them, so not
```

## Source note 377, line 4586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4586)

```text
// invalidating.
```

## Source note 378, line 4609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4609)

```text
// Write the constant buffer data.
```

## Source note 379, line 4622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4622)

```text
// Even if the shader doesn't need any float constants, a valid binding must
```

## Source note 380, line 4623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4623)

```text
// still be provided, so if the first draw in the frame with the current
```

## Source note 381, line 4624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4624)

```text
// root signature doesn't have float constants at all, still allocate an
```

## Source note 382, line 4625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4625)

```text
// empty buffer.
```

## Source note 383, line 4702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4702)

```text
// Update descriptors.
```

## Source note 384, line 4711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4711)

```text
// Get textures and samplers used by the vertex shader, check if the last used
```

## Source note 385, line 4712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4712)

```text
// samplers are compatible and update them.
```

## Source note 386, line 4740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4740)

```text
// Get textures and samplers used by the pixel shader, check if the last used
```

## Source note 387, line 4741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4741)

```text
// samplers are compatible and update them.
```

## Source note 388, line 4784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4784)

```text
// Bindless descriptors path.
```

## Source note 389, line 4787

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4787)

```text
// Check if need to write new descriptor indices.
```

## Source note 390, line 4788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4788)

```text
// Samplers have already been checked.
```

## Source note 391, line 4804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4804)

```text
// Get sampler descriptor indices, write new samplers, and handle sampler
```

## Source note 392, line 4805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4805)

```text
// heap overflow if it happens.
```

## Source note 393, line 4810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4810)

```text
// Overflow happened - invalidate sampler bindings because their
```

## Source note 394, line 4811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4811)

```text
// descriptor indices can't be used anymore (and even if heap creation
```

## Source note 395, line 4812

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4812)

```text
// fails, because current_sampler_bindless_indices_#_ are in an
```

## Source note 396, line 4813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4813)

```text
// undefined state now) and switch to a new sampler heap.
```

## Source note 397, line 4835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4835)

```text
// Only change the heap if a new heap was created successfully, not to
```

## Source note 398, line 4836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4836)

```text
// leave the values in an undefined state in case CreateDescriptorHeap
```

## Source note 399, line 4837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4837)

```text
// has failed.
```

## Source note 400, line 4846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4846)

```text
// The only thing the heap is used for now is texture cache samplers -
```

## Source note 401, line 4847

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4847)

```text
// invalidate all of them.
```

## Source note 402, line 4931

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4931)

```text
// Current samplers have already been updated.
```

## Source note 403, line 4962

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4962)

```text
// Current samplers have already been updated.
```

## Source note 404, line 4972

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4972)

```text
// Bindful descriptors path.
```

## Source note 405, line 4975

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4975)

```text
// See what descriptors need to be updated.
```

## Source note 406, line 4976

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4976)

```text
// Samplers have already been checked.
```

## Source note 407, line 4994

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L4994)

```text
// Allocate the descriptors.
```

## Source note 408, line 5002

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5002)

```text
// Shared memory SRV and null UAV + null SRV and shared memory UAV +
```

## Source note 409, line 5003

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5003)

```text
// textures.
```

## Source note 410, line 5006

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5006)

```text
// + EDRAM UAV and ZPD counter UAV in two tables (with the shared memory
```

## Source note 411, line 5007

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5007)

```text
// SRV and with the shared memory UAV).
```

## Source note 412, line 5010

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5010)

```text
// + ZPD counter UAV in both tables.
```

## Source note 413, line 5045

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5045)

```text
// Need to update all view descriptors.
```

## Source note 414, line 5050

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5050)

```text
// If updating fully, write the shared memory SRV and UAV descriptors and,
```

## Source note 415, line 5051

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5051)

```text
// if needed, the EDRAM descriptor.
```

## Source note 416, line 5052

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5052)

```text
// SRV + null UAV + EDRAM.
```

## Source note 417, line 5072

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5072)

```text
// Null SRV + UAV + EDRAM.
```

## Source note 418, line 5102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5102)

```text
// Write the descriptors.
```

## Source note 419, line 5148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5148)

```text
// Current samplers have already been updated.
```

## Source note 420, line 5162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5162)

```text
// Current samplers have already been updated.
```

## Source note 421, line 5168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5168)

```text
// Wrote new descriptors on the current page.
```

## Source note 422, line 5175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5175)

```text
// Update the root parameters.
```

## Source note 423, line 5340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5340)

```text
// VIZ surveys need the pool even when ZPD reports are faked.
```

## Source note 424, line 5345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5345)

```text
// Host queries count samples passing the host depth/stencil test. With ROV,
```

## Source note 425, line 5346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5346)

```text
// depth and stencil are tested in the pixel shader, so the shaders count
```

## Source note 426, line 5347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5347)

```text
// into the pool's counter slots instead (RG-GDK-010a).
```

## Source note 427, line 5357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5357)

```text
// Bindful descriptor pages written before the slots existed hold a null UAV.
```

## Source note 428, line 5381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5381)

```text
// Strict mode can't guess, so wait for the oldest in-flight resolve to
```

## Source note 429, line 5382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5382)

```text
// hand a slot back. If it's still in the open submission, close that when
```

## Source note 430, line 5383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5383)

```text
// allowed and let the next draw retry.
```

## Source note 431, line 5419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5419)

```text
// The pixel shaders count Total into the slot; the query counts ZPass.
```

## Source note 432, line 5424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5424)

```text
// The ROV shaders count into the slot the system constants name. A
```

## Source note 433, line 5425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5425)

```text
// recycled slot must not carry the previous query's counts.
```

## Source note 434, line 5444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5444)

```text
// SetPredication can't read the query heap or the counter, so the count is
```

## Source note 435, line 5445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5445)

```text
// also staged into the ID's predicate for draws still waiting on an answer.
```

## Source note 436, line 5454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5454)

```text
// The ZPass lane of the counter slot, written by pixel shader atomics.
```

## Source note 437, line 5455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5455)

```text
// Only the low dword is copied; the high one reads zero from the
```

## Source note 438, line 5456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5456)

```text
// buffer's zeroed creation or an earlier full resolve.
```

## Source note 439, line 5521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5521)

```text
// Resolve is still pending. Wait for async pipeline creation to finish.
```

## Source note 440, line 5549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5549)

```text
// Don't retry and relog on every close.
```

## Source note 441, line 5555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5555)

```text
// Created zeroed, not with the usual not-zeroed flag: the counter staging
```

## Source note 442, line 5556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5556)

```text
// only writes the low dword of a predicate, and predication compares all 64
```

## Source note 443, line 5557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5557)

```text
// bits.
```

## Source note 444, line 5614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5614)

```text
// xenia-edge's UpdateBindingsMesa.
```

## Source note 445, line 5660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5660)

```text
// On the ROV path the EDRAM store encodes gamma.
```

## Source note 446, line 5673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5673)

```text
// The shader endian-swaps SV_VertexID and adds the base index.
```

## Source note 447, line 5698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5698)

```text
// Read by the host tessellation shaders.
```

## Source note 448, line 5707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5707)

```text
// Point size, and the NDC size of a guest pixel for the line expansion.
```

## Source note 449, line 5734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5734)

```text
// Remap from -32...32 to -1...1, getting the full range. The ROV EDRAM
```

## Source note 450, line 5735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5735)

```text
// store handles the format itself.
```

## Source note 451, line 5742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5742)

```text
// Texture signedness, integer scaling and resolution-scaled resolves.
```

## Source note 452, line 5760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5760)

```text
// The ROV path's EDRAM render backend constants, counting samples into the
```

## Source note 453, line 5761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5761)

```text
// active occlusion query's counter slot as the DXBC ROV shaders do.
```

## Source note 454, line 5770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5770)

```text
// Constant buffers, skipping unchanged ones.
```

## Source note 455, line 5797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5797)

```text
// Packed float constants, as in the shaders' used constant maps.
```

## Source note 456, line 5847

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5847)

```text
// Mesa's runtime data CBV (b0 space31), unused but bound.
```

## Source note 457, line 5866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5866)

```text
// Shared memory t0 + u0: memexport draws also read vertices through t0.
```

## Source note 458, line 5873

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5873)

```text
// The ZPD counter is a null UAV while no counter exists; EDRAM is only used
```

## Source note 459, line 5874

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5874)

```text
// on the ROV path.
```

## Source note 460, line 5884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5884)

```text
// Per-stage {texture heap index, sampler heap index} buffers in the order of
```

## Source note 461, line 5885

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5885)

```text
// the SPIR-V bindings, read by the bindless lowering.
```

## Source note 462, line 5909

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5909)

```text
// ResourceDescriptorHeap is the whole view heap: absolute indices.
```

## Source note 463, line 5942

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5942)

```text
// A single draw's samplers always fit a fresh heap.
```

## Source note 464, line 5975

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L5975)

```text
// Reuse the oldest retired heap once the GPU is done with it.
```

## Source note 465, line 6002

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L6002)

```text
// The DXBC path's descriptor indices point into the old heap.
```

## Source note 466, line 6010

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/command_processor.cpp#L6010)

```text
// namespace rex::graphics::d3d12
```
