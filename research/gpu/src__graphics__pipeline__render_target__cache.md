# Cache: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/render_target/cache.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L111)

```text
// Alpha clamping affects blending source, so it's non-zero for alpha for
```

## Source note 2, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L112)

```text
// k_16_16 (the render target is fixed-point). There's one deviation from
```

## Source note 3, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L113)

```text
// how Direct3D 11.3 functional specification defines SNorm conversion
```

## Source note 4, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L114)

```text
// (NaN should be 0, not the lowest negative number), and that needs to be
```

## Source note 5, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L115)

```text
// handled separately.
```

## Source note 6, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L137)

```text
// No NaNs on the Xbox 360 GPU, though can't use the extended range with
```

## Source note 7, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L138)

```text
// Direct3D and Vulkan conversions.
```

## Source note 8, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L160)

```text
// No clamping - let min/max always pick the original value.
```

## Source note 9, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L168)

```text
// No clamping - let min/max always pick the original value.
```

## Source note 10, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L180)

```text
// Disable invalid render targets.
```

## Source note 11, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L184)

```text
// Special case handled in the shaders for empty write mask to completely skip
```

## Source note 12, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L185)

```text
// a disabled render target: all keep bits are set.
```

## Source note 13, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L204)

```text
// Conservatively treat either half as overlapping a 32bpp depth sample.
```

## Source note 14, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L215)

```text
// EDRAM addressing wrapping must be handled by doing GetRangeRectangles for
```

## Source note 15, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L216)

```text
// two clamped ranges, in this case start_tiles == end_tiles will also
```

## Source note 16, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L217)

```text
// unambiguously mean an empty range rather than the entire EDRAM.
```

## Source note 17, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L221)

```text
// If start_tiles < base_tiles, this is the tail after EDRAM addressing
```

## Source note 18, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L222)

```text
// wrapping.
```

## Source note 19, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L232)

```text
// If the first and / or the last rows have the same X spans as the middle
```

## Source note 20, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L233)

```text
// part, merge them with it.
```

## Source note 21, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L235)

```text
// If start_tiles < base_tiles, this is the tail after EDRAM addressing
```

## Source note 22, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L236)

```text
// wrapping.
```

## Source note 23, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L240)

```text
// Inclusive.
```

## Source note 24, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L242)

```text
// Exclusive.
```

## Source note 25, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L296)

```text
// If nothing to cut out (no region specified, or no intersection - if the
```

## Source note 26, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L297)

```text
// cutout region is in the middle on Y, but completely to the left / right on
```

## Source note 27, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L298)

```text
// X, don't split), add the whole rectangle.
```

## Source note 28, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L312)

```text
// Upper part after cutout.
```

## Source note 29, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L314)

```text
// The completely outside case has already been checked.
```

## Source note 30, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L321)

```text
// cutout->y_pixels is already known to be < rectangle_bottom, no need for
```

## Source note 31, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L322)

```text
// min(cutout->y_pixels - rectangle.y_pixels, rectangle.height_pixels).
```

## Source note 32, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L327)

```text
// Middle part after cutout.
```

## Source note 33, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L330)

```text
// Middle left.
```

## Source note 34, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L342)

```text
// Middle right.
```

## Source note 35, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L354)

```text
// Lower part after cutout.
```

## Source note 36, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L408)

```text
// Keep only render targets currently owning any EDRAM data.
```

## Source note 37, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L456)

```text
// A pass drawn every frame may still miss one, hence a window of frames.
```

## Source note 38, line 539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L539)

```text
// Safety check because a lot of code assumes up to 4x.
```

## Source note 39, line 547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L547)

```text
// surface_pitch 0 should be handled in disabling rasterization (hopefully
```

## Source note 40, line 548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L548)

```text
// it's safe to assume that).
```

## Source note 41, line 576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L576)

```text
// Get used render targets.
```

## Source note 42, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L577)

```text
// [0] is depth / stencil where relevant, [1...4] is color.
```

## Source note 43, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L578)

```text
// Depth / stencil testing / writing is before color in the pipeline.
```

## Source note 44, line 580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L580)

```text
// depth_and_color_rts_used_bits -> EDRAM base.
```

## Source note 45, line 584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L584)

```text
// Color targets that leave the depth bits untouched.
```

## Source note 46, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L591)

```text
// With pixel shader interlock, always the same addressing disregarding
```

## Source note 47, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L592)

```text
// the format.
```

## Source note 48, line 611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L611)

```text
// Only changes in mapping between coordinates and addresses are
```

## Source note 49, line 612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L612)

```text
// interesting (along with access overlap between draw calls), thus only
```

## Source note 50, line 613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L613)

```text
// pixel size is relevant.
```

## Source note 51, line 634

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L634)

```text
// A shared EDRAM base address doesn't necessarily mean the targets conflict
```

## Source note 52, line 635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L635)

```text
// with each other. 4D530A26 writes post-process data into the stencil byte
```

## Source note 53, line 636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L636)

```text
// of a 8_8_8_8 color target while simultaneously reading depth. Other MRT
```

## Source note 54, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L637)

```text
// setups probably use similar aliasing tricks.
```

## Source note 55, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L639)

```text
// To handle this, color target is given ownership of the range, but the
```

## Source note 56, line 640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L640)

```text
// current depth target is kept bound as read-only as long as the write ranges
```

## Source note 57, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L641)

```text
// don't overlap.
```

## Source note 58, line 659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L659)

```text
// The color owner can't preserve depth if this draw also writes it.
```

## Source note 59, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L670)

```text
// Eliminate other bound render targets if their EDRAM base conflicts with
```

## Source note 60, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L671)

```text
// another render target - it's an error in most host implementations to bind
```

## Source note 61, line 672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L672)

```text
// the same render target into multiple slots, also the behavior would be
```

## Source note 62, line 673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L673)

```text
// unpredictable if that happens.
```

## Source note 63, line 674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L674)

```text
// Depth is considered the least important as it's earlier in the pipeline
```

## Source note 64, line 675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L675)

```text
// (issues caused by color and depth render target collisions haven't been
```

## Source note 65, line 676

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L676)

```text
// found yet), but render targets with smaller index are considered more
```

## Source note 66, line 677

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L677)

```text
// important - specifically, because of the usage in the lighting pass of
```

## Source note 67, line 678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L678)

```text
// 4D5307E6, which can be checked in the vertical look calibration sequence in
```

## Source note 68, line 679

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L679)

```text
// the beginning of the game: if render target 0 is removed in favor of 1, the
```

## Source note 69, line 680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L680)

```text
// characters and the world will be too dark, like fully in shadow -
```

## Source note 70, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L681)

```text
// especially prominent on the helmet. This happens because the shader picks
```

## Source note 71, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L682)

```text
// between two render targets to write dynamically (though with a static, bool
```

## Source note 72, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L683)

```text
// constant condition), but all other state is set up in a way that implies
```

## Source note 73, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L684)

```text
// the same render target being bound twice. On Direct3D 9, if you don't write
```

## Source note 74, line 685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L685)

```text
// to a color pixel shader output on the control flow that was taken, the
```

## Source note 75, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L686)

```text
// render target will not be written to. However, this has been relaxed in
```

## Source note 76, line 687

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L687)

```text
// Direct3D 10, where if the shader declares an output, it's assumed to be
```

## Source note 77, line 688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L688)

```text
// always written (or with an undefined value otherwise).
```

## Source note 78, line 707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L707)

```text
// Clear ownership transfers before adding any.
```

## Source note 79, line 715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L715)

```text
// Nothing to bind, don't waste time on things like memexport-only draws -
```

## Source note 80, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L716)

```text
// just check if old bindings can still be used.
```

## Source note 81, line 739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L739)

```text
// Estimate height used by render targets (for color for writes, for depth /
```

## Source note 82, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L740)

```text
// stencil for both reads and writes) from various sources.
```

## Source note 83, line 752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L752)

```text
// Read-only aliased depth doesn't participate in the ownership layout.
```

## Source note 84, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L764)

```text
// Sorted by EDRAM base and then by index in the pipeline - for simplicity,
```

## Source note 85, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L765)

```text
// treat render targets placed closer to the end of the EDRAM as truncating
```

## Source note 86, line 766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L766)

```text
// the previous one (and in case multiple render targets are placed at the
```

## Source note 87, line 767

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L767)

```text
// same EDRAM base, though normally this shouldn't happen, treat the color
```

## Source note 88, line 768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L768)

```text
// ones as more important than the depth one, which may be not needed and just
```

## Source note 89, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L769)

```text
// a leftover if the draw, for instance, has depth / stencil happening to be
```

## Source note 90, line 770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L770)

```text
// always passing and never writing with the current state, and also because
```

## Source note 91, line 771

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L771)

```text
// depth testing has to happen before the color is written). Overall it's
```

## Source note 92, line 772

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L772)

```text
// normal for estimated EDRAM ranges of render targets to intersect if drawing
```

## Source note 93, line 773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L773)

```text
// without a viewport (as there's nothing to clamp the estimated height) and
```

## Source note 94, line 774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L774)

```text
// multiple render targets are bound.
```

## Source note 95, line 784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L784)

```text
// "As if it was 64bpp" (contribution of 32bpp render targets multiplied by 2,
```

## Source note 96, line 785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L785)

```text
// and clamping for 32bpp render targets divides this by 2) because 32bpp
```

## Source note 97, line 786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L786)

```text
// render targets can be combined with twice as long 64bpp render targets. An
```

## Source note 98, line 787

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L787)

```text
// example is the 4541099D menu background (1-sample 1152x720, or 1200x720
```

## Source note 99, line 788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L788)

```text
// after rounding to tiles, with a 32bpp depth buffer at 0 requiring 675
```

## Source note 100, line 789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L789)

```text
// tiles, and a 64bpp color buffer at 675 requiring 1350 tiles, but the
```

## Source note 101, line 790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L790)

```text
// smallest distance between two render target bases is 675 tiles).
```

## Source note 102, line 800

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L800)

```text
// Clamp to the distance from the last render target to the first with
```

## Source note 103, line 801

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L801)

```text
// EDRAM addressing wrapping.
```

## Source note 104, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L810)

```text
// Make sure all the needed render targets are created, and gather lengths of
```

## Source note 105, line 811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L811)

```text
// ranges used by each render target.
```

## Source note 106, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L835)

```text
// The last render target can occupy the EDRAM until the base of the first
```

## Source note 107, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L836)

```text
// render target (itself in case of 1 render target) with EDRAM addressing
```

## Source note 108, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L837)

```text
// wrapping.
```

## Source note 109, line 853

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L853)

```text
// The host depth must be current for the color owner's whole range.
```

## Source note 110, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L869)

```text
// Don't leave stale accumulated depth bound.
```

## Source note 111, line 875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L875)

```text
// Because a full pixel shader interlock barrier may clear the ownership map
```

## Source note 112, line 876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L876)

```text
// (since it flushes all previous writes, and there's no need for another
```

## Source note 113, line 877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L877)

```text
// barrier if an overlap is encountered later between pre-barrier and
```

## Source note 114, line 878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L878)

```text
// post-barrier usages), check if any overlap requiring a barrier happens,
```

## Source note 115, line 879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L879)

```text
// and then insert the barrier if needed.
```

## Source note 116, line 894

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L894)

```text
// From now on ownership transfers should succeed for simplicity and
```

## Source note 117, line 895

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L895)

```text
// consistency, even if they fail in the implementation (just ignore that and
```

## Source note 118, line 896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L896)

```text
// draw with whatever contents currently are in the render target in this
```

## Source note 119, line 897

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L897)

```text
// case).
```

## Source note 120, line 908

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L908)

```text
// No copying transfers or render target bindings - only needed the barrier.
```

## Source note 121, line 912

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L912)

```text
// If everything succeeded, update the used render targets.
```

## Source note 122, line 918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L918)

```text
// Check if the only re-enabling a previously bound render target.
```

## Source note 123, line 925

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L925)

```text
// Binding a totally new render target - won't keep the existing
```

## Source note 124, line 926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L926)

```text
// render pass anyway, no much need to try to re-enable previously
```

## Source note 125, line 927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L927)

```text
// disabled render targets in other slots as well, even though that
```

## Source note 126, line 928

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L928)

```text
// would be valid.
```

## Source note 127, line 932

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L932)

```text
// Append the new render target.
```

## Source note 128, line 938

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L938)

```text
// Changing a render target in a slot.
```

## Source note 129, line 946

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L946)

```text
// The previously bound render target is incompatible with the
```

## Source note 130, line 947

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L947)

```text
// current surface info.
```

## Source note 131, line 953

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L953)

```text
// Make sure the same render target isn't bound into two different slots
```

## Source note 132, line 954

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L954)

```text
// over time.
```

## Source note 133, line 1009

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1009)

```text
// Down to the beginning of the render target in the next 11-bit EDRAM
```

## Source note 134, line 1010

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1010)

```text
// addressing period.
```

## Source note 135, line 1012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1012)

```text
// Clamp to the guest limit (tile padding should exceed it) and to the host
```

## Source note 136, line 1013

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1013)

```text
// limit (tile padding mustn't exceed it).
```

## Source note 137, line 1031

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1031)

```text
// Initialize to all bits zeroed.
```

## Source note 138, line 1033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1033)

```text
// 8 pixels is the resolve granularity, both clearing and tile size are
```

## Source note 139, line 1034

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1034)

```text
// aligned to 8.
```

## Source note 140, line 1044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1044)

```text
// 1 thread group = 64x8 host samples.
```

## Source note 141, line 1064

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1064)

```text
// Collect render targets owning ranges within the specified rectangle. The
```

## Source note 142, line 1065

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1065)

```text
// first render target in the range may be before the lower_bound, only
```

## Source note 143, line 1066

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1066)

```text
// being in the range with its tail.
```

## Source note 144, line 1083

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1083)

```text
// Merge with other render target ranges with the same current ownership,
```

## Source note 145, line 1084

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1084)

```text
// but different depth ownership, since it's not relevant to resolving.
```

## Source note 146, line 1104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1104)

```text
// The first row starts within the pitch padding.
```

## Source note 147, line 1106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1106)

```text
// Multiple rows - start at the second.
```

## Source note 148, line 1110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1110)

```text
// Single row - nothing to dump.
```

## Source note 149, line 1118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1118)

```text
// Don't include pitch padding in the last row.
```

## Source note 150, line 1127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1127)

```text
// The resolve area goes to the next EDRAM addressing period.
```

## Source note 151, line 1224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1224)

```text
// Outside the pitch / height (or initially specified as 0).
```

## Source note 152, line 1228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1228)

```text
// Change ownership of the tiles containing the area to be cleared, so the
```

## Source note 153, line 1229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1229)

```text
// up-to-date host render target for the cleared range will be the cleared
```

## Source note 154, line 1230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1230)

```text
// one.
```

## Source note 155, line 1242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1242)

```text
// Up to the range from the base in the current 11 tile index bits to the base
```

## Source note 156, line 1243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1243)

```text
// in the next 11 tile index bits after wrapping can be cleared.
```

## Source note 157, line 1265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1265)

```text
// Prevent overlap - clear the depth only until the color, the color only
```

## Source note 158, line 1266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1266)

```text
// until the depth, in the current or the next 11 bits of the tile index.
```

## Source note 159, line 1297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1297)

```text
// Failed to create the depth render target, don't clear it.
```

## Source note 160, line 1313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1313)

```text
// Failed to create the color render target, don't clear it.
```

## Source note 161, line 1319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1319)

```text
// Complete overlap, or failed to create all the render targets.
```

## Source note 162, line 1341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1341)

```text
// Clear ownership - any overlap of data written before the barrier is safe.
```

## Source note 163, line 1345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1345)

```text
// Do not reallocate map elements if not needed (either nothing drawn since
```

## Source note 164, line 1346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1346)

```text
// the last barrier, or all of the EDRAM is owned by one render target).
```

## Source note 165, line 1347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1347)

```text
// The ownership map contains no gaps - the first element should always be
```

## Source note 166, line 1348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1348)

```text
// at 0.
```

## Source note 167, line 1384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1384)

```text
// Insert even if failed to create, not to try to create again.
```

## Source note 168, line 1393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1393)

```text
// xenos::kEdramTileCount with length 0 is fine if both the start and the end
```

## Source note 169, line 1394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1394)

```text
// are clamped to xenos::kEdramTileCount.
```

## Source note 170, line 1403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1403)

```text
// The map contains consecutive ranges, merged if the adjacent ones are the
```

## Source note 171, line 1404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1404)

```text
// same. Find the range starting at >= the start. A portion of the range
```

## Source note 172, line 1405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1405)

```text
// preceding it may be intersecting the render target's range (or even fully
```

## Source note 173, line 1406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1406)

```text
// contain it).
```

## Source note 174, line 1416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1416)

```text
// Outside the touched extent already.
```

## Source note 175, line 1420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1420)

```text
// Already owned by the needed render target - no need to transfer
```

## Source note 176, line 1421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1421)

```text
// anything.
```

## Source note 177, line 1425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1425)

```text
// Only perform the transfer when actually changing the latest owner, not
```

## Source note 178, line 1426

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1426)

```text
// just the latest host depth owner - the transfer source is expected to
```

## Source note 179, line 1427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1427)

```text
// be different than the destination.
```

## Source note 180, line 1434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1434)

```text
// start_tiles_base_relative may already be in the next 11 bits - wrap the
```

## Source note 181, line 1435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1435)

```text
// start tile index to use the same code as if that was not the case.
```

## Source note 182, line 1443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1443)

```text
// The check extent goes to the next EDRAM addressing period.
```

## Source note 183, line 1470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1470)

```text
// Empty and invalidated ranges are stale too.
```

## Source note 184, line 1492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1492)

```text
// xenos::kEdramTileCount with length 0 is fine if both the start and the end
```

## Source note 185, line 1493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1493)

```text
// are clamped to xenos::kEdramTileCount.
```

## Source note 186, line 1503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1503)

```text
// Depth targets and ordinary color writes replace the tracked depth bits.
```

## Source note 187, line 1506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1506)

```text
// Split even an already-owned range if its depth bits must be refreshed.
```

## Source note 188, line 1514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1514)

```text
// The map contains consecutive ranges, merged if the adjacent ones are the
```

## Source note 189, line 1515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1515)

```text
// same. Find the range starting at >= the start. A portion of the range
```

## Source note 190, line 1516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1516)

```text
// preceding it may be intersecting the render target's range (or even fully
```

## Source note 191, line 1517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1517)

```text
// contain it) - split it into the untouched head and the claimed tail if
```

## Source note 192, line 1518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1518)

```text
// needed.
```

## Source note 193, line 1523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1523)

```text
// Different render target overlapping the range - split the head.
```

## Source note 194, line 1526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1526)

```text
// Let the next loop do the transfer and needed merging and splitting
```

## Source note 195, line 1527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1527)

```text
// starting from the added tail.
```

## Source note 196, line 1533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1533)

```text
// Outside the touched extent already.
```

## Source note 197, line 1537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1537)

```text
// Already owned by the needed render target - no need to transfer
```

## Source note 198, line 1538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1538)

```text
// anything.
```

## Source note 199, line 1542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1542)

```text
// Take over the current range. Handle the tail - may be outside the range
```

## Source note 200, line 1543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1543)

```text
// (split in this case) or within it.
```

## Source note 201, line 1545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1545)

```text
// Split the tail.
```

## Source note 202, line 1551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1551)

```text
// Only perform the copying when actually changing the latest owner, not
```

## Source note 203, line 1552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1552)

```text
// just the latest host depth owner - the transfer source is expected to
```

## Source note 204, line 1553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1553)

```text
// be different than the destination.
```

## Source note 205, line 1565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1565)

```text
// Same render target, don't provide a separate host depth source.
```

## Source note 206, line 1576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1576)

```text
// Extend the last transfer if, for example, transferring color,
```

## Source note 207, line 1577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1577)

```text
// but host depth is different.
```

## Source note 208, line 1602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1602)

```text
// Claim the current range.
```

## Source note 209, line 1610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1610)

```text
// Check if can merge with the next range after claiming.
```

## Source note 210, line 1615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1615)

```text
// Merge with the next range.
```

## Source note 211, line 1624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1624)

```text
// Check if can merge with the previous range after claiming and merging
```

## Source note 212, line 1625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1625)

```text
// with the next (thus obtaining the correct end pointer).
```

## Source note 213, line 1636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1636)

```text
// start_tiles_base_relative may already be in the next 11 bits - wrap the
```

## Source note 214, line 1637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1637)

```text
// start tile index to use the same code as if that was not the case.
```

## Source note 215, line 1643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/render_target/cache.cpp#L1643)

```text
// The ownership change extent goes to the next EDRAM addressing period.
```
