# Draw: graphics source notes

This record preserves technical and API notes moved from `src/graphics/util/draw.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L34)

```text
// Very prominent in 545407F2.
```

## Source note 2, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L35)

```text
// DEFINE_bool(
```

## Source note 3, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L36)

```text
//     resolve_resolution_scale_fill_half_pixel_offset, true,
```

## Source note 4, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L37)

```text
//     "When using resolution scaling, apply the hack that stretches the first "
```

## Source note 5, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L38)

```text
//     "surely covered host pixel in the left and top sides of render target "
```

## Source note 6, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L39)

```text
//     "resolve areas to eliminate the gap caused by the half-pixel offset (this "
```

## Source note 7, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L40)

```text
//     "is necessary for certain games to display the scene graphics).",
```

## Source note 8, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L41)

```text
//     "GPU");
```

## Source note 9, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L46)

```text
// The sample counters live in the RB with depth/stencil testing.
```

## Source note 10, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L47)

```text
// kNoOperation and kCopy don't count. D3D sits in kCopy during
```

## Source note 11, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L48)

```text
// EVENT_WRITE_ZPD, which only snapshots the running counters.
```

## Source note 12, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L58)

```text
// Geometry killed after hi-Z only feeds the VIZ survey. Without an ID,
```

## Source note 13, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L59)

```text
// nothing consumes it (screen-extent queries are not emulated).
```

## Source note 14, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L66)

```text
// Both faces are culled.
```

## Source note 15, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L82)

```text
// Both depth and stencil disabled (EDRAM depth and stencil ignored).
```

## Source note 16, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L89)

```text
// VIZ surveys just test, never write. Nothing rejects them with hi-Z off.
```

## Source note 17, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L92)

```text
// Surveys use per-sample depth tests when hi-Z is on.
```

## Source note 18, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L97)

```text
// For more reliable skipping of depth render target management for draws not
```

## Source note 19, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L98)

```text
// requiring depth.
```

## Source note 20, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L103)

```text
// Stencil is more complex and is expected to be usually enabled explicitly
```

## Source note 21, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L104)

```text
// when needed.
```

## Source note 22, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L108)

```text
// https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_standard_multisample_quality_levels
```

## Source note 23, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L117)

```text
// Prefer the front polygon offset because in general, front faces are the
```

## Source note 24, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L118)

```text
// ones that are rendered (except for shadow volumes).
```

## Source note 25, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L129)

```text
// Non-triangle primitives use the front offset, but it's toggled via
```

## Source note 26, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L130)

```text
// poly_offset_para_enable.
```

## Source note 27, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L145)

```text
// See xenos::EdramMode for explanation why the pixel shader is only used when
```

## Source note 28, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L146)

```text
// it's kColorDepth here.
```

## Source note 29, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L151)

```text
// Surveys just count coverage; hardware kills them before the shader.
```

## Source note 30, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L156)

```text
// Discarding (explicitly or through alphatest or alpha to coverage) has side
```

## Source note 31, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L157)

```text
// effects on pixel counting.
```

## Source note 32, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L159)

```text
// Depth output only really matters if depth test is active, but it's used
```

## Source note 33, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L160)

```text
// extremely rarely, and pretty much always intentionally - for simplicity,
```

## Source note 34, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L161)

```text
// consider it as always mattering.
```

## Source note 35, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L163)

```text
// Memory export is an obvious intentional side effect.
```

## Source note 36, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L171)

```text
// Check if a color target is actually written.
```

## Source note 37, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L185)

```text
// Only depth / stencil passthrough potentially.
```

## Source note 38, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L198)

```text
// A vertex position goes the following path:
```

## Source note 39, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L200)

```text
// = Vertex shader output in clip space, (-w, -w, 0) ... (w, w, w) for
```

## Source note 40, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L201)

```text
//   Direct3D or (-w, -w, -w) ... (w, w, w) for OpenGL.
```

## Source note 41, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L202)

```text
// > Clipping to the boundaries of the clip space if enabled.
```

## Source note 42, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L203)

```text
// > Division by W if not pre-divided.
```

## Source note 43, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L204)

```text
// = Normalized device coordinates, (-1, -1, 0) ... (1, 1, 1) for Direct3D or
```

## Source note 44, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L205)

```text
//   (-1, -1, -1) ... (1, 1, 1) for OpenGL.
```

## Source note 45, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L206)

```text
// > Viewport scaling.
```

## Source note 46, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L207)

```text
// > Viewport, window and half-pixel offsetting.
```

## Source note 47, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L208)

```text
// = Actual position in render target pixels used for rasterization and depth
```

## Source note 48, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L209)

```text
//   buffer coordinates.
```

## Source note 49, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L211)

```text
// On modern PC graphics APIs, all drawing is done with clipping enabled (only
```

## Source note 50, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L212)

```text
// Z clipping can be replaced with viewport depth range clamping).
```

## Source note 51, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L214)

```text
// On the Xbox 360, however, there are two cases:
```

## Source note 52, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L216)

```text
// - Clipping is enabled:
```

## Source note 53, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L218)

```text
//   Drawing "as normal", primarily for the game world. Draws are clipped to
```

## Source note 54, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L219)

```text
//   the (-w, -w, 0) ... (w, w, w) or (-w, -w, -w) ... (w, w, w) clip space.
```

## Source note 55, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L221)

```text
//   Ideally all offsets in pixels (window offset, half-pixel offset) are
```

## Source note 56, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L222)

```text
//   post-clip, and thus they would need to be applied via the host viewport
```

## Source note 57, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L223)

```text
//   (also the Direct3D 11.3 specification defines this as the correct way of
```

## Source note 58, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L224)

```text
//   reproducing the original Direct3D 9 half-pixel offset behavior).
```

## Source note 59, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L226)

```text
//   However, in reality, only WARP actually truly clips to -W...W, with the
```

## Source note 60, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L227)

```text
//   viewport fractional offset actually accurately making samples outside the
```

## Source note 61, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L228)

```text
//   fractional rectangle unable to be covered. AMD, Intel and Nvidia, in
```

## Source note 62, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L229)

```text
//   Direct3D 12, all don't truly clip even a really huge primitive to -W...W.
```

## Source note 63, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L230)

```text
//   Instead, primitives still overflow the fractional rectangle and cover
```

## Source note 64, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L231)

```text
//   samples outside of it. The actual viewport scissor is floor(TopLeftX,
```

## Source note 65, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L232)

```text
//   TopLeftY) ... floor(TopLeftX + Width, TopLeftY + Height), with flooring
```

## Source note 66, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L233)

```text
//   and addition in float32 (with 0x3F7FFFFF TopLeftXY, or 1.0f - ULP, all
```

## Source note 67, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L234)

```text
//   the samples in the top row / left column can be covered, while with
```

## Source note 68, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L235)

```text
//   0x3F800000, or 1.0f, none of them can be).
```

## Source note 69, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L237)

```text
//   We are reproducing the same behavior here - what would happen if we'd be
```

## Source note 70, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L238)

```text
//   passing the guest values directly to Direct3D 12. Also, for consistency
```

## Source note 71, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L239)

```text
//   across hardware and APIs (especially Vulkan with viewportSubPixelBits
```

## Source note 72, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L240)

```text
//   being 0 rather than at least 8 on some devices - Arm Mali, Imagination
```

## Source note 73, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L241)

```text
//   PowerVR), and for simplicity of math, and also for exact calculations in
```

## Source note 74, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L242)

```text
//   bounds checking in validation layers of the host APIs, we are returning
```

## Source note 75, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L243)

```text
//   integer viewport coordinates, handling the fractional offset in the
```

## Source note 76, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L244)

```text
//   vertex shaders instead, via ndc_scale and ndc_offset - it shouldn't
```

## Source note 77, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L245)

```text
//   significantly affect precision that we will be doing the offsetting in
```

## Source note 78, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L246)

```text
//   W-scaled rather than W-divided units, the ratios of exponents involved in
```

## Source note 79, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L247)

```text
//   the calculations stay the same, and everything ends up being 16.8 anyway
```

## Source note 80, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L248)

```text
//   on most hardware, so small precision differences are very unlikely to
```

## Source note 81, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L249)

```text
//   affect coverage.
```

## Source note 82, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L257)

```text
// Obtain the original viewport values in a normalized way.
```

## Source note 83, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L270)

```text
// Calculate all the integer.0 or integer.5 offsetting exactly at full
```

## Source note 84, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L271)

```text
// precision, separately so it can be used in other integer calculations
```

## Source note 85, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L272)

```text
// without double rounding if needed.
```

## Source note 86, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L284)

```text
// The maximum value is at least the maximum host render target size anyway -
```

## Source note 87, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L285)

```text
// and a guest pixel is always treated as a whole with resolution scaling.
```

## Source note 88, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L296)

```text
// Clipping is disabled - use a huge host viewport, perform pixel and depth
```

## Source note 89, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L297)

```text
// offsetting in the vertex shader.
```

## Source note 90, line 299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L299)

```text
// XY.
```

## Source note 91, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L313)

```text
// Z.
```

## Source note 92, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L319)

```text
// Clipping is enabled - perform pixel and depth offsetting via the host
```

## Source note 93, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L320)

```text
// viewport.
```

## Source note 94, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L322)

```text
// XY.
```

## Source note 95, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L324)

```text
// With resolution scaling, do all viewport XY scissoring in guest pixels
```

## Source note 96, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L325)

```text
// if fractional and for the half-pixel offset - we treat guest pixels as
```

## Source note 97, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L326)

```text
// a whole, and also the half-pixel offset would be irreversible in guest
```

## Source note 98, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L327)

```text
// vertices if we did flooring in host pixels. Instead of flooring, also
```

## Source note 99, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L328)

```text
// doing truncation for simplicity - since maxing with 0 is done anyway
```

## Source note 100, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L329)

```text
// (we only return viewports in the positive quarter-plane).
```

## Source note 101, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L345)

```text
// Rescale from the old bounds to the new ones, and also apply the sign.
```

## Source note 102, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L346)

```text
// If the new bounds are smaller than the old, for instance, we're
```

## Source note 103, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L347)

```text
// cropping - the new -W...W clip space is a subregion of the old one -
```

## Source note 104, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L348)

```text
// the scale should be > 1 so the area being cut off ends up outside
```

## Source note 105, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L349)

```text
// -W...W. If the new region should include more than the original clip
```

## Source note 106, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L350)

```text
// space, a region previously outside -W...W should end up within it, so
```

## Source note 107, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L351)

```text
// the scale should be < 1.
```

## Source note 108, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L354)

```text
// Move the origin of the snapped coordinates back to the original one.
```

## Source note 109, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L358)

```text
// Empty viewport (everything outside the viewport scissor).
```

## Source note 110, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L366)

```text
// Z.
```

## Source note 111, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L375)

```text
// Normalizing both Direct3D / Vulkan 0...W and OpenGL -W...W clip spaces
```

## Source note 112, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L376)

```text
// to 0...W. We are not targeting OpenGL, but there we could accept the
```

## Source note 113, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L377)

```text
// wanted clip space (Direct3D, OpenGL, or any) and return the actual one
```

## Source note 114, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L378)

```text
// (Direct3D or OpenGL).
```

## Source note 115, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L380)

```text
// If the guest wants to use -W...W clip space (-1...1 NDC) and a 0...1
```

## Source note 116, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L381)

```text
// depth range in the end, it's expected to use ZSCALE of 0.5 and ZOFFSET
```

## Source note 117, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L382)

```text
// of 0.5.
```

## Source note 118, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L384)

```text
// We are providing the near and the far (or offset and offset + scale)
```

## Source note 119, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L385)

```text
// plane distances to the host API in a way that the near maps to Z = 0
```

## Source note 120, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L386)

```text
// and the far maps to Z = W in clip space (or Z = 1 in NDC).
```

## Source note 121, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L388)

```text
// With D3D offset and scale that we want, assuming D3D clip space input,
```

## Source note 122, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L389)

```text
// the formula for the depth would be:
```

## Source note 123, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L391)

```text
// depth = offset_d3d + scale_d3d * ndc_z_d3d
```

## Source note 124, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L393)

```text
// We are remapping the incoming OpenGL Z from -W...W to 0...W by scaling
```

## Source note 125, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L394)

```text
// it by 0.5 and adding 0.5 * W to the result. So, our depth formula would
```

## Source note 126, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L397)

```text
// depth = offset_d3d + scale_d3d * (ndc_z_gl * 0.5 + 0.5)
```

## Source note 127, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L399)

```text
// The guest registers, however, contain the offset and the scale for
```

## Source note 128, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L400)

```text
// remapping not from 0...W to near...far, but from -W...W to near...far,
```

## Source note 129, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L403)

```text
// depth = offset_gl + scale_gl * ndc_z_gl
```

## Source note 130, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L405)

```text
// Knowing offset_gl, scale_gl and how ndc_z_d3d can be obtained from
```

## Source note 131, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L406)

```text
// ndc_z_gl, we need to derive the formulas for the needed offset_d3d and
```

## Source note 132, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L407)

```text
// scale_d3d to apply them to the incoming ndc_z_d3d.
```

## Source note 133, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L409)

```text
// depth = offset_gl + scale_gl * (ndc_z_d3d * 2 - 1)
```

## Source note 134, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L413)

```text
// depth = offset_gl + (scale_gl * ndc_z_d3d * 2 - scale_gl)
```

## Source note 135, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L417)

```text
// depth = (offset_gl - scale_gl) + (scale_gl * 2) * ndc_z_d3d
```

## Source note 136, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L418)

```text
// offset_d3d = offset_gl - scale_gl
```

## Source note 137, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L419)

```text
// scale_d3d = scale_gl * 2
```

## Source note 138, line 422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L422)

```text
// Need to remap -W...W clip space to 0...W via ndc_scale and ndc_offset -
```

## Source note 139, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L423)

```text
// by scaling Z by 0.5 and adding 0.5 * W to it.
```

## Source note 140, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L428)

```text
// Allow the pixel shader to write any depth value since
```

## Source note 141, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L429)

```text
// PA_SC_VPORT_ZMIN/ZMAX isn't present on the Adreno 200; guest pixel
```

## Source note 142, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L430)

```text
// shaders don't have access to the original Z in the viewport space
```

## Source note 143, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L431)

```text
// anyway and likely must write the depth on all execution paths.
```

## Source note 144, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L435)

```text
// This clamping is not very correct, but just for safety. Direct3D
```

## Source note 145, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L436)

```text
// doesn't allow an unrestricted depth range. Vulkan does, as an
```

## Source note 146, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L437)

```text
// extension. But cases when this really matters are yet to be found -
```

## Source note 147, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L438)

```text
// trying to fix this will result in more correct depth values, but
```

## Source note 148, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L439)

```text
// incorrect clipping.
```

## Source note 149, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L442)

```text
// Direct3D 12 doesn't allow reverse depth range - on some drivers it
```

## Source note 150, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L443)

```text
// works, on some drivers it doesn't, actually, but it was never
```

## Source note 151, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L444)

```text
// explicitly allowed by the specification.
```

## Source note 152, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L456)

```text
// Need to adjust the bounds that the resulting depth values will be
```

## Source note 153, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L457)

```text
// clamped to after the pixel shader. Preferring adding some error to
```

## Source note 154, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L458)

```text
// interpolated Z instead if conversion can't be done exactly, without
```

## Source note 155, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L459)

```text
// modifying clipping bounds by adjusting Z in vertex shaders, as that
```

## Source note 156, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L460)

```text
// may cause polygons placed explicitly at Z = 0 or Z = W to be clipped.
```

## Source note 157, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L461)

```text
// Rounding the bounds to the nearest even regardless of the depth
```

## Source note 158, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L462)

```text
// rounding mode not to add even more error by truncating twice.
```

## Source note 159, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L467)

```text
// Remap the full [0...2) float24 range to [0...1) support data round-trip
```

## Source note 160, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L468)

```text
// during render target ownership transfer of EDRAM tiles through depth
```

## Source note 161, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L469)

```text
// input without unrestricted depth range.
```

## Source note 162, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L501)

```text
// Screen scissor is not used by Direct3D 9 (always 0, 0 to 8192, 8192), but
```

## Source note 163, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L502)

```text
// still handled here for completeness.
```

## Source note 164, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L510)

```text
// Clamp the horizontal scissor to surface_pitch for safety, in case that's
```

## Source note 165, line 511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L511)

```text
// not done by the guest for some reason (it's not when doing draws without
```

## Source note 166, line 512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L512)

```text
// clipping in Direct3D 9, for instance), to prevent overflow - this is
```

## Source note 167, line 513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L513)

```text
// important for host implementations, both based on target-indepedent
```

## Source note 168, line 514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L514)

```text
// rasterization without render target width at all (pixel shader
```

## Source note 169, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L515)

```text
// interlock-based custom RB implementations) and using conventional render
```

## Source note 170, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L516)

```text
// targets, but padded to EDRAM tiles.
```

## Source note 171, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L521)

```text
// Ensure the rectangle is non-negative, by collapsing it into a 0-sized one
```

## Source note 172, line 522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L522)

```text
// (not by reordering the bounds preserving the width / height, which would
```

## Source note 173, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L523)

```text
// reveal samples not meant to be covered, unless TL > BR does that on a real
```

## Source note 174, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L524)

```text
// console, but no evidence of such has ever been seen), and also drop
```

## Source note 175, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L525)

```text
// negative offsets.
```

## Source note 176, line 545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L545)

```text
// Exclude the render targets not statically written to by the pixel shader.
```

## Source note 177, line 546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L546)

```text
// If the shader doesn't write to a render target, it shouldn't be written
```

## Source note 178, line 547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L547)

```text
// to, and no ownership transfers should happen to it on the host even -
```

## Source note 179, line 548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L548)

```text
// otherwise, in 4D5307E6, one render target is being destroyed by a shader
```

## Source note 180, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L549)

```text
// not writing anything, and in 58410955, the result of clearing the top
```

## Source note 181, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L550)

```text
// tile is being ignored because there are 4 render targets bound with the
```

## Source note 182, line 551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L551)

```text
// same EDRAM base (clearly not correct usage), but the shader only clears
```

## Source note 183, line 552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L552)

```text
// 1, and then ownership of EDRAM portions by host render targets is
```

## Source note 184, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L553)

```text
// conflicting.
```

## Source note 185, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L557)

```text
// Check if any existing component is written to.
```

## Source note 186, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L567)

```text
// Mark the non-existent components as written so in the host driver, no
```

## Source note 187, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L568)

```text
// slow path (involving reading and merging components) is taken if the
```

## Source note 188, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L569)

```text
// driver doesn't perform this check internally, and some components are not
```

## Source note 189, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L570)

```text
// included in the mask even though they actually don't exist in the format.
```

## Source note 190, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L572)

```text
// Add to the normalized mask.
```

## Source note 191, line 581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L581)

```text
// The shader has eA writes, but no real exports.
```

## Source note 192, line 590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L590)

```text
// Safety checks for stream constants potentially not set up if the export
```

## Source note 193, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L591)

```text
// isn't done on the control flow path taken by the shader (not checking the
```

## Source note 194, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L592)

```text
// Y component because the index is more likely to be constructed
```

## Source note 195, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L593)

```text
// arbitrarily).
```

## Source note 196, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L594)

```text
// The hardware validates the upper bits of eA according to the
```

## Source note 197, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L595)

```text
// IPR2015-00325 sequencer specification.
```

## Source note 198, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L603)

```text
// Translated shaders shouldn't be performing exports with an unknown
```

## Source note 199, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L604)

```text
// format, the draw can still be performed.
```

## Source note 200, line 621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L621)

```text
// Try to reduce the number of shared memory operations when writing
```

## Source note 201, line 622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L622)

```text
// different elements into the same buffer through different exports
```

## Source note 202, line 623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L623)

```text
// (happens in 4D5307E6).
```

## Source note 203, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L632)

```text
// Add a new range if haven't expanded an existing one.
```

## Source note 204, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L641)

```text
// Depth can't be averaged.
```

## Source note 205, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L684)

```text
// Due to 64bpp, and also not to make an assumption that the offsets are
```

## Source note 206, line 685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L685)

```text
// limited to (80 - 8, 8 - 8) with 2x MSAA, and (40 - 8, 8 - 8) with 4x MSAA,
```

## Source note 207, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L686)

```text
// still taking the offset into account.
```

## Source note 208, line 722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L722)

```text
// Don't pass uninitialized values to shaders, not to leak data to frame
```

## Source note 209, line 723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L723)

```text
// captures. Also initialize an invalid resolve to empty.
```

## Source note 210, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L740)

```text
// Get the extent of pixels covered by the resolve rectangle, according to the
```

## Source note 211, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L741)

```text
// top-left rasterization rule.
```

## Source note 212, line 751

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L751)

```text
// Most vertices have a negative half-pixel offset applied, which we reverse.
```

## Source note 213, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L759)

```text
// Inclusive.
```

## Source note 214, line 762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L762)

```text
// Exclusive.
```

## Source note 215, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L765)

```text
// Top-left - include .5 (0.128 treated as 0 covered, 0.129 as 0 not covered).
```

## Source note 216, line 768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L768)

```text
// Bottom-right - exclude .5.
```

## Source note 217, line 774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L774)

```text
// Apply the window offset to the vertices.
```

## Source note 218, line 782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L782)

```text
// Apply the scissor and prevent negative origin (behind the EDRAM base).
```

## Source note 219, line 784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L784)

```text
// False because clamping to the surface pitch will be done later (it will be
```

## Source note 220, line 785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L785)

```text
// aligned to the resolve alignment here, for resolving from render targets
```

## Source note 221, line 786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L786)

```text
// with a pitch that is not a multiple of 8).
```

## Source note 222, line 797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L797)

```text
// Direct3D 9's D3DDevice_Resolve internally rounds the right/bottom of the
```

## Source note 223, line 798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L798)

```text
// rectangle internally to 8. While all the alignment should have already been
```

## Source note 224, line 799

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L799)

```text
// done by Direct3D 9, just for safety of host implementation of resolve,
```

## Source note 225, line 800

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L800)

```text
// force-align the rectangle by expanding (D3D9 expands to the right/bottom
```

## Source note 226, line 801

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L801)

```text
// for some reason and takes the left/top as given, only requiring them to be
```

## Source note 227, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L802)

```text
// aligned, but logically it would make sense to expand to the left/top too).
```

## Source note 228, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L810)

```text
// Safety check because a lot of code assumes up to 4x.
```

## Source note 229, line 819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L819)

```text
// Clamp to the EDRAM surface pitch (maximum possible surface pitch is also
```

## Source note 230, line 820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L820)

```text
// assumed to be the largest resolvable size).
```

## Source note 231, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L831)

```text
// Clamp the height to a sane value (to make sure it can fit in the packed
```

## Source note 232, line 832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L832)

```text
// shader constant).
```

## Source note 233, line 846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L846)

```text
// 3 bits for each.
```

## Source note 234, line 852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L852)

```text
// Handle the destination.
```

## Source note 235, line 854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L854)

```text
// Get the sample selection to safely pass to the shader.
```

## Source note 236, line 866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L866)

```text
// Get the format to pass to the shader in a unified way - for depth (for
```

## Source note 237, line 867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L867)

```text
// which Direct3D 9 specifies the k_8_8_8_8 uint destination format), make
```

## Source note 238, line 868

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L868)

```text
// sure the shader won't try to do conversion - pass proper k_24_8 or
```

## Source note 239, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L869)

```text
// k_24_8_FLOAT.
```

## Source note 240, line 877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L877)

```text
// For development feedback - not much known about these formats currently.
```

## Source note 241, line 898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L898)

```text
// Calculate the destination memory extent.
```

## Source note 242, line 907

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L907)

```text
// For volume resolves, D3D writes pitch * level height in blocks to
```

## Source note 243, line 908

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L908)

```text
// RB_COPY_SURFACE_SLICE; copy_dest_height may include the top of the source
```

## Source note 244, line 909

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L909)

```text
// rectangle, so it is only the fallback for slice spacing.
```

## Source note 245, line 910

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L910)

```text
// Source: xenia-canary #1248 (d8731edc99ecc438eb4cd1a8754341d7396a061e).
```

## Source note 246, line 930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L930)

```text
// D3D advances RB_COPY_DEST_BASE in 32x32 macro tiles based on the
```

## Source note 247, line 931

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L931)

```text
// destination point. 8bpp/16bpp macro tiles are smaller than 4KB, so part
```

## Source note 248, line 932

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L932)

```text
// of the x offset can be left in the base's low bits. Move that part back
```

## Source note 249, line 933

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L933)

```text
// into dest_addr_x0 before the usual tiled calculation. 534307D5's water
```

## Source note 250, line 934

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L934)

```text
// refraction texture's middle 5_6_5 strip hits this at x=480.
```

## Source note 251, line 935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L935)

```text
// Source: xenia-canary #1240 (89609297c7ae25dc5ba404c6a977260b806bb725).
```

## Source note 252, line 957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L957)

```text
// The base pointer is already adjusted to the Z / 8 (copy_dest_slice is
```

## Source note 253, line 958

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L958)

```text
// 3-bit).
```

## Source note 254, line 993

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L993)

```text
// Offset relative to the beginning of the tile to put it in fewer bits.
```

## Source note 255, line 1009

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1009)

```text
// Write the color/depth EDRAM info.
```

## Source note 256, line 1022

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1022)

```text
// If wrapping happens, it's fine, it doesn't matter how many times and
```

## Source note 257, line 1023

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1023)

```text
// where modulo xenos::kEdramTileCount is applied in this context.
```

## Source note 258, line 1036

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1036)

```text
// Color.
```

## Source note 259, line 1043

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1043)

```text
// If wrapping happens, it's fine, it doesn't matter how many times and
```

## Source note 260, line 1044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1044)

```text
// where modulo xenos::kEdramTileCount is applied in this context.
```

## Source note 261, line 1053

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1053)

```text
// The texture expects 0x8001 = -32, 0x7FFF = 32, but the hack making
```

## Source note 262, line 1054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1054)

```text
// 0x8001 = -1, 0x7FFF = 1 is used - revert (this won't be correct if the
```

## Source note 263, line 1055

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1055)

```text
// requested exponent bias is 27 or above, but it's a hack anyway, no need
```

## Source note 264, line 1056

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1056)

```text
// to create a new copy info structure with one more bit just for this).
```

## Source note 265, line 1065

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1065)

```text
// Patch and write RB_COPY_DEST_INFO.
```

## Source note 266, line 1067

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1067)

```text
// Override with the depth format to make sure the shader doesn't have any
```

## Source note 267, line 1068

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1068)

```text
// reason to try to do k_8_8_8_8 packing.
```

## Source note 268, line 1070

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1070)

```text
// Handle k_16_16 and k_16_16_16_16 range.
```

## Source note 269, line 1073

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1073)

```text
// Single component, nothing to swap.
```

## Source note 270, line 1094

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1094)

```text
// The fast resolves are only right when the destination reads the bits the
```

## Source note 271, line 1095

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1095)

```text
// EDRAM view stores: fixed colors as unsigned fractions, float colors as
```

## Source note 272, line 1096

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1096)

```text
// floats. Signed and integer destinations need the full resolve to repack.
```

## Source note 273, line 1121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1121)

```text
// The fast resolves copy the EDRAM bits. Hardware decodes 8_8_8_8_GAMMA to
```

## Source note 274, line 1122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1122)

```text
// linear (a title keeping the encoding re-aliases the surface as 8_8_8_8
```

## Source note 275, line 1123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1123)

```text
// first), and a copy_dest_number other than the EDRAM's own interpretation
```

## Source note 276, line 1124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1124)

```text
// needs repacking, so both take the full shader (xenia-canary d119505289,
```

## Source note 277, line 1125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1125)

```text
// 2ddc5ef737, fc48d37cdc).
```

## Source note 278, line 1194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw.cpp#L1194)

```text
// Source: xenia-canary a635ac64f5ca37c0b789e8b4166b53dc673b213f.
```
