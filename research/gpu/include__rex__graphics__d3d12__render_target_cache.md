# Render target cache: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/d3d12/render_target_cache.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L75)

```text
// Performs the resolve to a shared memory area according to the current
```

## Source note 2, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L76)

```text
// register values, and also clears the render targets if needed. Must be in a
```

## Source note 3, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L77)

```text
// frame for calling. copy_dest_info_out receives the destination info with
```

## Source note 4, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L78)

```text
// the format normalized by GetResolveInfo, as used for the written extent.
```

## Source note 5, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L83)

```text
// For host render targets.
```

## Source note 6, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L87)

```text
// Using R16G16[B16A16]_SNORM, which are -1...1, not the needed -32...32.
```

## Source note 7, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L88)

```text
// Persistent data doesn't depend on this, so can be overriden by per-game
```

## Source note 8, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L89)

```text
// configuration.
```

## Source note 9, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L124)

```text
// The values are ordered by how strong the barrier conditions are.
```

## Source note 10, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L125)

```text
// No uncommitted ROV/UAV writes.
```

## Source note 11, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L127)

```text
// Need to commit before the next ROV usage with overlap.
```

## Source note 12, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L129)

```text
// Need to commit before any next ROV usage.
```

## Source note 13, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L143)

```text
// For host render targets, an EDRAM-sized scratch buffer for:
```

## Source note 14, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L144)

```text
// - Guest render target data copied from host render targets during copying
```

## Source note 15, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L145)

```text
//   in resolves.
```

## Source note 16, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L146)

```text
// - Host float32 depth in ownership transfers when the host depth texture and
```

## Source note 17, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L147)

```text
//   the destination are the same.
```

## Source note 18, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L148)

```text
// For rasterizer-ordered view, the buffer containing the EDRAM data.
```

## Source note 19, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L149)

```text
// (Note that if a hybrid RTV / DSV + ROV approach to color render targets is
```

## Source note 20, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L150)

```text
//  added, which is, however, unlikely as it would have very complicated
```

## Source note 21, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L151)

```text
//  interaction with depth / stencil testing, host depth will need to be
```

## Source note 22, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L152)

```text
//  copied to a different buffer - the same range may have ROV-owned color and
```

## Source note 23, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L153)

```text
//  host float32 depth at the same time).
```

## Source note 24, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L159)

```text
// Non-shader-visible descriptor heap containing pre-created SRV and UAV
```

## Source note 25, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L160)

```text
// descriptors of the EDRAM buffer, for faster binding (by copying rather
```

## Source note 26, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L161)

```text
// than creation).
```

## Source note 27, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L177)

```text
// Resolve copying root signature and pipelines.
```

## Source note 28, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L178)

```text
// Parameter 0 - draw_util::ResolveCopyShaderConstants or its ::DestRelative.
```

## Source note 29, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L179)

```text
// Parameter 1 - destination (shared memory or a part of it).
```

## Source note 30, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L180)

```text
// Parameter 2 - source (EDRAM).
```

## Source note 31, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L193)

```text
// For host render targets.
```

## Source note 32, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L197)

```text
// descriptor_load_separate is present when the DXGI formats are different
```

## Source note 33, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L198)

```text
// for drawing and bit-exact loading (for NaN pattern preservation across
```

## Source note 34, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L199)

```text
// EDRAM tile ownership transfers in floating-point formats, and to
```

## Source note 35, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L200)

```text
// distinguish between two -1 representations in snorm formats).
```

## Source note 36, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L250)

```text
// Texture SRV non-shader-visible descriptors, to prepare shader-visible
```

## Source note 37, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L251)

```text
// descriptors faster, by copying rather than by creating every time.
```

## Source note 38, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L256)

```text
// Temporary storage for indices in operations like transfers and dumps.
```

## Source note 39, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L275)

```text
// Changed 8 times per transfer.
```

## Source note 40, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L278)

```text
// Mutually exclusive with ColorSRV.
```

## Source note 41, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L280)

```text
// Mutually exclusive with ColorSRV.
```

## Source note 42, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L282)

```text
// May happen to be the same for different sources.
```

## Source note 43, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L317)

```text
// 1 SRV (color texture), source constant.
```

## Source note 44, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L319)

```text
// 1 SRV (color texture), source constant.
```

## Source note 45, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L322)

```text
// 1 or 2 SRVs (depth texture, stencil texture if SV_StencilRef is
```

## Source note 46, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L323)

```text
// supported), source constant.
```

## Source note 47, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L325)

```text
// 2 SRVs (depth texture, stencil texture), source constant.
```

## Source note 48, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L328)

```text
// 1 SRV (color texture), mask constant (most frequently changed, 8 times
```

## Source note 49, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L329)

```text
// per transfer), source constant.
```

## Source note 50, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L331)

```text
// 1 SRV (stencil texture), mask constant, source constant.
```

## Source note 51, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L334)

```text
// Two-source modes, using the host depth if it, when converted to the guest
```

## Source note 52, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L335)

```text
// format, matches what's in the owner source (not modified, keep host
```

## Source note 53, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L336)

```text
// precision), or the guest data otherwise (significantly modified, possibly
```

## Source note 54, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L337)

```text
// cleared). Stencil for SV_StencilRef is always taken from the guest
```

## Source note 55, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L338)

```text
// source.
```

## Source note 56, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L340)

```text
// 2 SRVs (color texture, host depth texture or buffer), source constant,
```

## Source note 57, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L341)

```text
// host depth source constant.
```

## Source note 58, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L343)

```text
// When using different source and destination depth formats. 2 or 3 SRVs
```

## Source note 59, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L344)

```text
// (depth texture, stencil texture if SV_StencilRef is supported, host depth
```

## Source note 60, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L345)

```text
// texture or buffer), source constant, host depth source constant.
```

## Source note 61, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L353)

```text
// With this output, kTransferCBVRegisterStencilMask is used.
```

## Source note 62, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L369)

```text
// Always 1x when host_depth_source_is_copy is true not to create the same
```

## Source note 63, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L370)

```text
// pipeline for different MSAA sample counts as it doesn't matter in this
```

## Source note 64, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L371)

```text
// case.
```

## Source note 65, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L374)

```text
// If host depth is also fetched, whether it's pre-copied to the EDRAM
```

## Source note 66, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L375)

```text
// buffer (but since it's just a scratch buffer, with tiles laid out
```

## Source note 67, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L376)

```text
// linearly with the same pitch as in the original render target; also no
```

## Source note 68, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L377)

```text
// swapping of 40-sample columns as opposed to the host render target -
```

## Source note 69, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L378)

```text
// this is done only for the color source).
```

## Source note 70, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L381)

```text
// Last bits because this affects the root signature - after sorting, only
```

## Source note 71, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L382)

```text
// change it as fewer times as possible. Depth buffers have an additional
```

## Source note 72, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L383)

```text
// stencil SRV.
```

## Source note 73, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L403)

```text
// All in tiles.
```

## Source note 74, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L406)

```text
// Destination base in tiles minus source base in tiles (not vice versa
```

## Source note 75, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L407)

```text
// because this is a transform of the coordinate system, not addresses
```

## Source note 76, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L408)

```text
// themselves).
```

## Source note 77, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L409)

```text
// + 1 bit because this is a signed difference between two EDRAM bases.
```

## Source note 78, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L410)

```text
// 0 for host_depth_source_is_copy (ignored in this case anyway as
```

## Source note 79, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L411)

```text
// destination == source anyway).
```

## Source note 80, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L432)

```text
// Host depth render targets are changed rarely if they exist, won't save
```

## Source note 81, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L433)

```text
// many binding changes, ignore them for simplicity (their existence is
```

## Source note 82, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L434)

```text
// caught by the shader key change).
```

## Source note 83, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L465)

```text
// Last bit because this affects the root signature - after sorting, only
```

## Source note 84, line 466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L466)

```text
// change it at most once. Depth buffers have an additional stencil SRV.
```

## Source note 85, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L492)

```text
// May be beyond the EDRAM tile count in case of EDRAM addressing
```

## Source note 86, line 493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L493)

```text
// wrapping, thus + 1 bit.
```

## Source note 87, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L507)

```text
// Both in tiles.
```

## Source note 88, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L525)

```text
// May be changed multiple times for the same source.
```

## Source note 89, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L527)

```text
// One resolve may need multiple sources.
```

## Source note 90, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L530)

```text
// May be different for different sources.
```

## Source note 91, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L532)

```text
// Only changed between 32bpp and 64bpp.
```

## Source note 92, line 537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L537)

```text
// Same change frequency than the source (though currently the command
```

## Source note 93, line 538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L538)

```text
// processor can't contiguously allocate multiple descriptors with bindless,
```

## Source note 94, line 539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L539)

```text
// when such functionality is added, switch to one root signature).
```

## Source note 95, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L553)

```text
// Sort by the pipeline key primarily to reduce pipeline state (context)
```

## Source note 96, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L554)

```text
// switches.
```

## Source note 97, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L602)

```text
// - A pointer to 1 pipeline for writing color or depth (or stencil via
```

## Source note 98, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L603)

```text
//   SV_StencilRef).
```

## Source note 99, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L604)

```text
// - A pointer to 8 pipelines for writing stencil by discarding samples
```

## Source note 100, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L605)

```text
//   depending on whether they have one bit set, from 1 << 0 to 1 << 7.
```

## Source note 101, line 606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L606)

```text
// - Null if failed to create.
```

## Source note 102, line 626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L626)

```text
// Do ownership transfers for render targets - each render target / vector may
```

## Source note 103, line 627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L627)

```text
// be null / empty in case there's nothing to do for them.
```

## Source note 104, line 628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L628)

```text
// resolve_clear_rectangle is expected to be provided by
```

## Source note 105, line 629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L629)

```text
// PrepareHostRenderTargetsResolveClear which should do all the needed size
```

## Source note 106, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L630)

```text
// bound checks.
```

## Source note 107, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L637)

```text
// Accepts an array of (1 + xenos::kMaxColorRenderTargets) render targets,
```

## Source note 108, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L638)

```text
// first depth, then color.
```

## Source note 109, line 647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L647)

```text
// Writes contents of host render targets within rectangles from
```

## Source note 110, line 648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L648)

```text
// ResolveInfo::GetCopyEdramTileSpan to edram_buffer_.
```

## Source note 111, line 667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L667)

```text
// Possible tile ownership transfer paths:
```

## Source note 112, line 668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L668)

```text
// - To color:
```

## Source note 113, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L669)

```text
//   - From color: 1 SRV (color).
```

## Source note 114, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L670)

```text
//   - From depth: 2 SRVs (depth, stencil).
```

## Source note 115, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L671)

```text
// - To depth / stencil (with SV_StencilRef):
```

## Source note 116, line 672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L672)

```text
//   - From color: 1 SRV (color).
```

## Source note 117, line 673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L673)

```text
//   - From depth: 2 SRVs (depth, stencil).
```

## Source note 118, line 674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L674)

```text
//   - From color and float32 depth: 2 SRVs (color with stencil, depth).
```

## Source note 119, line 675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L675)

```text
//     - Different depth buffer: depth SRV is a texture.
```

## Source note 120, line 676

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L676)

```text
//     - Same depth buffer: depth SRV is a buffer (pre-copied).
```

## Source note 121, line 677

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L677)

```text
// - To depth (no SV_StencilRef):
```

## Source note 122, line 678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L678)

```text
//   - From color: 1 SRV (color).
```

## Source note 123, line 679

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L679)

```text
//   - From depth: 1 SRV (depth).
```

## Source note 124, line 680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L680)

```text
//   - From color and float32 depth: 2 SRVs (color, depth).
```

## Source note 125, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L681)

```text
//     - Different depth buffer: depth SRV is a texture.
```

## Source note 126, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L682)

```text
//     - Same depth buffer: depth SRV is a buffer (pre-copied).
```

## Source note 127, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L683)

```text
// - To stencil (no SV_StencilRef):
```

## Source note 128, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L684)

```text
//   - From color: 1 SRV (color).
```

## Source note 129, line 685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L685)

```text
//   - From depth: 1 SRV (stencil).
```

## Source note 130, line 691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L691)

```text
// Temporary storage for descriptors used in PerformTransfersAndResolveClears
```

## Source note 131, line 692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L692)

```text
// and DumpRenderTargets.
```

## Source note 132, line 708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L708)

```text
// Temporary storage for PerformTransfersAndResolveClears.
```

## Source note 133, line 711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L711)

```text
// Temporary storage for DumpRenderTargets.
```

## Source note 134, line 718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L718)

```text
// Compute pipelines for copying host render target contents to the EDRAM
```

## Source note 135, line 719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L719)

```text
// buffer. May be null if failed to create.
```

## Source note 136, line 731

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L731)

```text
// Parameter 0 - 2 root constants (red, green).
```

## Source note 137, line 733

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L733)

```text
// [32 or 32_32][MSAA samples].
```

## Source note 138, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L738)

```text
// Temporary storage for DXBC building.
```

## Source note 139, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L741)

```text
// For rasterizer-ordered view (pixel shader interlock).
```

## Source note 140, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L744)

```text
// Clearing 32bpp color or depth.
```

## Source note 141, line 746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L746)

```text
// Clearing 64bpp color.
```

## Source note 142, line 750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/render_target_cache.h#L750)

```text
// namespace rex::graphics::d3d12
```
