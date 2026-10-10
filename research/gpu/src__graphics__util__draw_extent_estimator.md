# Draw extent estimator: graphics source notes

This record preserves technical and API notes moved from `src/graphics/util/draw_extent_estimator.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L33)

```text
// DEFINE_bool(
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L34)

```text
//     execute_unclipped_draw_vs_on_cpu, true,
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L35)

```text
//     "Execute the vertex shader for draws with clipping disabled, primarily "
```

## Source note 4, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L36)

```text
//     "screen-space draws (such as clears), on the CPU when possible to estimate "
```

## Source note 5, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L37)

```text
//     "the extent of the EDRAM involved in the draw.\n"
```

## Source note 6, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L38)

```text
//     "Enabling this may significantly improve GPU performance as otherwise up "
```

## Source note 7, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L39)

```text
//     "to the entire EDRAM may be considered used in draws without clipping, "
```

## Source note 8, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L40)

```text
//     "potentially resulting in spurious EDRAM range ownership transfer round "
```

## Source note 9, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L41)

```text
//     "trips between host render targets.\n"
```

## Source note 10, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L42)

```text
//     "Also, on hosts where certain render target formats have to be emulated in "
```

## Source note 11, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L43)

```text
//     "a lossy way (for instance, 16-bit fixed-point via 16-bit floating-point), "
```

## Source note 12, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L44)

```text
//     "this prevents corruption of other render targets located after the "
```

## Source note 13, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L45)

```text
//     "current ones in the EDRAM by lossy range ownership transfers done for "
```

## Source note 14, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L46)

```text
//     "those draws.",
```

## Source note 15, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L47)

```text
//     "GPU");
```

## Source note 16, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L48)

```text
// DEFINE_bool(
```

## Source note 17, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L49)

```text
//     execute_unclipped_draw_vs_on_cpu_with_scissor, false,
```

## Source note 18, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L50)

```text
//     "Don't restrict the usage of execute_unclipped_draw_vs_on_cpu to only "
```

## Source note 19, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L51)

```text
//     "non-scissored draws (with the right and the bottom sides of the scissor "
```

## Source note 20, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L52)

```text
//     "rectangle at 8192 or beyond) even though if the scissor rectangle is "
```

## Source note 21, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L53)

```text
//     "present, it's usually sufficient for esimating the height of the render "
```

## Source note 22, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L54)

```text
//     "target.\n"
```

## Source note 23, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L55)

```text
//     "Enabling this may cause excessive processing of vertices on the CPU, as "
```

## Source note 24, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L56)

```text
//     "some games draw rectangles (for their UI, for instance) without clipping, "
```

## Source note 25, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L57)

```text
//     "but with a proper scissor rectangle.",
```

## Source note 26, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L58)

```text
//     "GPU");
```

## Source note 27, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L95)

```text
// Not reproducing tessellation.
```

## Source note 28, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L119)

```text
// Handle the index endianness to same way as the PrimitiveProcessor.
```

## Source note 29, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L171)

```text
// The Xenos only uses 24 bits of the index (reset_indx is 24-bit).
```

## Source note 30, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L211)

```text
// Vertex-specified diameter. Clamped effectively as a signed integer in
```

## Source note 31, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L212)

```text
// the hardware, -NaN, -Infinity ... -0 to the minimum, +Infinity, +NaN
```

## Source note 32, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L213)

```text
// to the maximum.
```

## Source note 33, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L220)

```text
// Constant radius.
```

## Source note 34, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L226)

```text
// std::max is `a < b ? b : a`, thus in case of NaN, the first argument is
```

## Source note 35, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L227)

```text
// always returned - max_y, which is initialized to a normalized value.
```

## Source note 36, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L233)

```text
// 16p8 range is -32768 to 32767+255/256, but it's stored as uint32_t here,
```

## Source note 37, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L234)

```text
// as 24p8, so overflowing up to -8388608 to 8388608+255/256 is safe. The
```

## Source note 38, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L235)

```text
// range of the window offset plus the half-pixel offset is -16384 to 16384.5,
```

## Source note 39, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L236)

```text
// so it's safe to add both - adding it will neither move the 16p8 clamping
```

## Source note 40, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L237)

```text
// bounds -32768 and 32767+255/256 into the 0...8192 screen space range, nor
```

## Source note 41, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L238)

```text
// cause 24p8 overflow.
```

## Source note 42, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L245)

```text
// Top-left rule - .5 exclusive without MSAA, 1. exclusive with MSAA.
```

## Source note 43, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L261)

```text
// Scissor.
```

## Source note 44, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L273)

```text
// Actual extent from the vertices.
```

## Source note 45, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L281)

```text
// Handle just the usual special 8192x8192 case in Direct3D 9 - 8192
```

## Source note 46, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L282)

```text
// may be a normal render target height (80x8192 is well within the
```

## Source note 47, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L283)

```text
// EDRAM size, for instance), no need to process the vertices on the
```

## Source note 48, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L284)

```text
// CPU in this case.
```

## Source note 49, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L300)

```text
// Viewport. Though the Xenos itself doesn't have an implicit viewport
```

## Source note 50, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L301)

```text
// scissor (it's set by Direct3D 9 when a viewport is used), on hosts, it
```

## Source note 51, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L302)

```text
// usually exists and can't be disabled.
```

## Source note 52, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L305)

```text
// First calculate all the integer.0 or integer.5 offsetting exactly at full
```

## Source note 53, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L306)

```text
// precision.
```

## Source note 54, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L313)

```text
// Then apply the floating-point viewport offset.
```

## Source note 55, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L320)

```text
// Using floor, or, rather, truncation (because maxing with zero anyway)
```

## Source note 56, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L321)

```text
// similar to how viewport scissoring behaves on real AMD, Intel and Nvidia
```

## Source note 57, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L322)

```text
// GPUs on Direct3D 12 (but not WARP), also like in
```

## Source note 58, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L323)

```text
// draw_util::GetHostViewportInfo.
```

## Source note 59, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L324)

```text
// max(0.0f, viewport_bottom) to drop NaN and < 0 - max picks the first
```

## Source note 60, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L325)

```text
// argument in the !(a < b) case (always for NaN), min as float (max_y is
```

## Source note 61, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/util/draw_extent_estimator.cpp#L326)

```text
// well below 2^24) to safely drop very large values.
```
