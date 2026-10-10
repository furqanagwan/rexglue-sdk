# Cache: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/render_target/cache.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L37)

```text
// High-level emulation logic implementation path.
```

## Source note 2, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L39)

```text
// Approximate method using conventional host render targets and copying
```

## Source note 3, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L40)

```text
// ("transferring ownership" of tiles) between render targets to support
```

## Source note 4, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L41)

```text
// aliasing.
```

## Source note 5, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L43)

```text
// May be irreparably inaccurate, completely at the mercy of the host API's
```

## Source note 6, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L44)

```text
// fixed-function output-merger, primarily because it has to perform
```

## Source note 7, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L45)

```text
// blending - and when using a different pixel format, it will behave
```

## Source note 8, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L46)

```text
// differently (the most important factor here is the range - it's clamped
```

## Source note 9, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L47)

```text
// for normalized formats, but not for floating-point ones).
```

## Source note 10, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L49)

```text
// On a Direct3D 11-level device, formats which can be mapped directly
```

## Source note 11, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L50)

```text
// (disregarding things like blending internal precision details):
```

## Source note 12, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L51)

```text
// - 8_8_8_8
```

## Source note 13, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L52)

```text
// - 2_10_10_10
```

## Source note 14, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L53)

```text
// - 32_FLOAT
```

## Source note 15, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L54)

```text
// - 32_32_FLOAT
```

## Source note 16, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L55)

```text
// - D24S8
```

## Source note 17, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L56)

```text
// Can be mapped directly, but require handling in shaders:
```

## Source note 18, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L57)

```text
// - D24FS8 with truncated SV_DepthLessEqual output (or SV_Depth, which is
```

## Source note 19, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L58)

```text
//   suboptimal, as it prevents early depth / stencil from working). To
```

## Source note 20, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L59)

```text
//   support bit-exact reinterpretation to and from D24F for unmodified
```

## Source note 21, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L60)

```text
//   areas using pixel shader depth output without unrestricted depth range,
```

## Source note 22, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L61)

```text
//   0...1 of the guest depth should be mapped to 0...0.5 on the host in the
```

## Source note 23, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L62)

```text
//   viewport and conversion.
```

## Source note 24, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L63)

```text
// Can be mapped directly, but not supporting rare edge cases:
```

## Source note 25, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L64)

```text
// - 16_16_FLOAT, k_16_16_16_16_FLOAT - the Xenos float16 doesn't have
```

## Source note 26, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L65)

```text
//   special values.
```

## Source note 27, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L66)

```text
// Significant differences:
```

## Source note 28, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L67)

```text
// - 8_8_8_8_GAMMA - the piecewise linear gamma curve is very different than
```

## Source note 29, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L68)

```text
//   sRGB, one possible path is conversion in shaders (resulting in
```

## Source note 30, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L69)

```text
//   incorrect blending, especially visible on decals in 4D5307E6), another
```

## Source note 31, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L70)

```text
//   is using sRGB render targets and either conversion on resolve or
```

## Source note 32, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L71)

```text
//   reading the resolved data as a true sRGB texture (incorrect when the
```

## Source note 33, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L72)

```text
//   game accesses the data directly, like 4541080F).
```

## Source note 34, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L73)

```text
// - 2_10_10_10_FLOAT - ranges significantly different than in float16, much
```

## Source note 35, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L74)

```text
//   smaller RGB range, and alpha is fixed-point and has only 2 bits.
```

## Source note 36, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L75)

```text
// - 16_16, 16_16_16_16 - has -32 to 32 range, not -1 to 1 - need either to
```

## Source note 37, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L76)

```text
//   truncate the range for blending to work correctly, or divide by 32 in
```

## Source note 38, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L77)

```text
//   shaders breaking multiplication in blending.
```

## Source note 39, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L80)

```text
// Custom output-merger implementation, with full per-pixel and per-sample
```

## Source note 40, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L81)

```text
// control, however, only available on hosts with raster-ordered writes from
```

## Source note 41, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L82)

```text
// pixel shaders.
```

## Source note 42, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L86)

```text
// Pixel shader interlock implementation helpers.
```

## Source note 43, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L88)

```text
// Appended to the format in the format constant via bitwise OR.
```

## Source note 44, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L91)

```text
// Requires clamping of blending sources and factors.
```

## Source note 45, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L125)

```text
// Whether an aliased color write touches enabled depth or stencil bits.
```

## Source note 46, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L134)

```text
// Resolution scaling on the EDRAM side is performed by multiplying the EDRAM
```

## Source note 47, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L135)

```text
// tile size by the resolution scale.
```

## Source note 48, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L136)

```text
// Note: Only integer scaling factors are provided because fractional ones,
```

## Source note 49, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L137)

```text
// even with 0.5 granularity, cause significant issues in addition to the ones
```

## Source note 50, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L138)

```text
// already present with integer scaling. 1.5 (from 1280x720 to 1920x1080) may
```

## Source note 51, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L139)

```text
// be useful, but it would cause pixel coverage issues with odd dimensions of
```

## Source note 52, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L140)

```text
// screen-space geometry, most importantly 1x1 that is often the final step in
```

## Source note 53, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L141)

```text
// reduction algorithms such as average luminance computation in HDR. A
```

## Source note 54, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L142)

```text
// single-pixel quad, either 0...1 without half-pixel offset or 0.5...1.5 with
```

## Source note 55, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L143)

```text
// it (covers only the first pixel according the top-left rule), with 1.5x
```

## Source note 56, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L144)

```text
// resolution scaling, would become 0...1.5 (only the first pixel covered) or
```

## Source note 57, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L145)

```text
// 0.75...2.25 (only the second). The workaround used in Xenia for 2x and 3x
```

## Source note 58, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L146)

```text
// resolution scaling for filling the gap caused by the half-pixel offset
```

## Source note 59, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L147)

```text
// becoming whole-pixel - stretching the second column / row of pixels into
```

## Source note 60, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L148)

```text
// the first - will not work in this case, as for one-pixel primitives without
```

## Source note 61, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L149)

```text
// half-pixel offset (covering only the first pixel, but not the second, with
```

## Source note 62, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L150)

```text
// 1.5x), it will actually cause the pixel to be erased with 1.5x scaling. As
```

## Source note 63, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L151)

```text
// within one pass there can be geometry both with and without the half-pixel
```

## Source note 64, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L152)

```text
// offset (not only depending on PA_SU_VTX_CNTL::PIX_CENTER, but also with the
```

## Source note 65, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L153)

```text
// half-pixel offset possibly reverted manually), the emulator can't decide
```

## Source note 66, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L154)

```text
// whether the stretching workaround actually needs to be used. So, with 1.5x,
```

## Source note 67, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L155)

```text
// depending on how the game draws its screen-space effects and on whether the
```

## Source note 68, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L156)

```text
// workaround is used, in some cases, nothing will just be drawn to the first
```

## Source note 69, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L157)

```text
// pixel, while in other cases, the effect will be drawn to it, but the
```

## Source note 70, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L158)

```text
// stretching workaround will replace it with the undefined value in the
```

## Source note 71, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L159)

```text
// second pixel. Also, with 1.5x, rounding of integer coordinates becomes
```

## Source note 72, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L160)

```text
// complicated, also in part due to the half-pixel offset. Odd texture sizes
```

## Source note 73, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L161)

```text
// would need to be rounded down, as according to the top-left rule, a 1.5x1.5
```

## Source note 74, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L162)

```text
// quad at the 0 or 0.75 origin (after the scaling) will cover only 1 pixel -
```

## Source note 75, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L163)

```text
// so, if the resulting texture was 2x2 rather than 1x1, undefined pixels
```

## Source note 76, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L164)

```text
// would participate in filtering. However, 1x1 scissor rounded to 1x1, with
```

## Source note 77, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L165)

```text
// the half-pixel offset of vertices, would cause the entire 0.75...2.25 quad
```

## Source note 78, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L166)

```text
// to be discarded.
```

## Source note 79, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L169)

```text
// Whether this resolve is written at the guest's size (ADR-012): the
```

## Source note 80, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L170)

```text
// resolution is scaled, resolution_scale_targets doesn't list the resolved
```

## Source note 81, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L171)

```text
// size, and the copy can be downscaled whole (a 2D destination of up to
```

## Source note 82, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L172)

```text
// 64bpp that the resolved rectangle covers, so no texel beside it changes).
```

## Source note 83, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L173)

```text
// Logs each resolved size once with log_resolution_scale_targets.
```

## Source note 84, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L175)

```text
// Whether a native resolve averages each texel's host block
```

## Source note 85, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L176)

```text
// (resolve_downscale_average, supersampling) rather than taking its center:
```

## Source note 86, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L177)

```text
// only for formats of 8-bit channels, where a per-byte mean is exact.
```

## Source note 87, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L184)

```text
// Virtual (both the common code and the implementation may do something
```

## Source note 88, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L185)

```text
// here), don't call from destructors (does work not needed for shutdown
```

## Source note 89, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L186)

```text
// also).
```

## Source note 90, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L194)

```text
// Returns bits where 0 is whether a depth render target is currently bound on
```

## Source note 91, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L195)

```text
// the host and 1... are whether the same applies to color render targets, and
```

## Source note 92, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L196)

```text
// formats (resource formats, but if needed, with gamma taken into account) of
```

## Source note 93, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L197)

```text
// each.
```

## Source note 94, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L200)

```text
// For async pipeline stand-ins (has207/xenia-edge de8e60601): skipping a
```

## Source note 95, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L201)

```text
// draw while its pipeline compiles is only harmless for a pass redrawn every
```

## Source note 96, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L202)

```text
// frame. Records the render target the last update draws into (the first
```

## Source note 97, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L203)

```text
// bound color one, else depth) as drawn in `frame`, and returns whether it
```

## Source note 98, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L204)

```text
// was also drawn within kDrawTargetRecurringFrames before. True with no
```

## Source note 99, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L205)

```text
// render target, as nothing is kept then.
```

## Source note 100, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L208)

```text
// Whether the last update's render target is at most
```

## Source note 101, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L209)

```text
// kDrawTargetSmallPitchTiles wide (160 pixels without MSAA): generated data
```

## Source note 102, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L210)

```text
// such as impostors or lookup tables, often kept past the frame even when
```

## Source note 103, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L211)

```text
// redrawn every frame.
```

## Source note 104, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L234)

```text
// Call last in implementation-specific initialization (when things like path
```

## Source note 105, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L235)

```text
// are initialized by the implementation).
```

## Source note 106, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L237)

```text
// May be called from the destructor, or from the implementation shutdown to
```

## Source note 107, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L238)

```text
// destroy all render targets before destroying what they depend on in the
```

## Source note 108, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L239)

```text
// implementation.
```

## Source note 109, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L241)

```text
// Call last in implementation-specific shutdown, also callable from the
```

## Source note 110, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L242)

```text
// destructor.
```

## Source note 111, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L245)

```text
// For host render targets, implemented via transfer of ownership of EDRAM
```

## Source note 112, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L246)

```text
// 80x16-sample tiles between host render targets. When a range is
```

## Source note 113, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L247)

```text
// transferred, its data is copied, bit-exactly from the guest's perspective
```

## Source note 114, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L248)

```text
// (when dangerous, such as because of non-propagated NaN, primarily in the
```

## Source note 115, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L249)

```text
// float16 case, by drawing to an integer view of the render target texture),
```

## Source note 116, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L250)

```text
// from the previous host render target to the new one, by drawing rectangles
```

## Source note 117, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L251)

```text
// with a pixel shader converting the previous host render target to a guest
```

## Source note 118, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L252)

```text
// bit pattern, reinterpreting it in the new format. If depth is emulated with
```

## Source note 119, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L253)

```text
// float32, this may lead to loss of data - specifically for depth, both guest
```

## Source note 120, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L254)

```text
// format ownership and float32 ownership are tracked, and to let color data
```

## Source note 121, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L255)

```text
// overwrite depth data, loading during ownership transfer is done from
```

## Source note 122, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L256)

```text
// intersections of the current guest ownership ranges and float32 ownership
```

## Source note 123, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L257)

```text
// ranges. Ownership transfer happens when a render target is needed - based
```

## Source note 124, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L258)

```text
// on the current viewport; or, if no viewport is available, ownership of the
```

## Source note 125, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L259)

```text
// rest of the EDRAM is transferred.
```

## Source note 126, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L264)

```text
// 11
```

## Source note 127, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L265)

```text
// At 4x MSAA (2 horizontal samples), max. align(8192 * 2, 80) / 80 = 205.
```

## Source note 128, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L266)

```text
// For pitch at 64bpp, multiply by 2 (or use GetPitchTiles).
```

## Source note 129, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L267)

```text
// 19
```

## Source note 130, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L268)

```text
// 21
```

## Source note 131, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L269)

```text
// 22
```

## Source note 132, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L270)

```text
// Ignoring the blending precision and sRGB.
```

## Source note 133, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L271)

```text
// 26
```

## Source note 134, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L285)

```text
// Meaningless when pitch_tiles_at_32bpp == 0, but for comparison
```

## Source note 135, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L286)

```text
// purposes, only treat everything being 0 as a special case.
```

## Source note 136, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L326)

```text
// Exclusive ownership, plus no point in moving (only allocated via new).
```

## Source note 137, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L363)

```text
// Cutout can be specified for resolve clears - not to transfer areas that
```

## Source note 138, line 364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L364)

```text
// will be cleared to a single value anyway.
```

## Source note 139, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L389)

```text
// - 1 because the maximum is 0x1FFF / 8, not 0x2000 / 8.
```

## Source note 140, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L404)

```text
// Whether 2x MSAA is supported natively rather than through 4x.
```

## Source note 141, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L419)

```text
// If rows == 1:
```

## Source note 142, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L420)

```text
//   Row row_first span:
```

## Source note 143, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L421)

```text
//     [row_first_start, row_last_end)
```

## Source note 144, line 422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L422)

```text
// If rows > 1:
```

## Source note 145, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L423)

```text
//   Row row_first + row span:
```

## Source note 146, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L424)

```text
//     [row_first_start, row_length_used)
```

## Source note 147, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L425)

```text
//   Rows [row_first + 1, row_first + rows - 1) span:
```

## Source note 148, line 426

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L426)

```text
//     [row * pitch, row * pitch + row_length_used)
```

## Source note 149, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L427)

```text
//   Row row_first + rows - 1 span:
```

## Source note 150, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L428)

```text
//     [row * pitch, row * pitch + row_last_end)
```

## Source note 151, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L441)

```text
// Base plus offset may exceed the EDRAM tile count in case of EDRAM
```

## Source note 152, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L442)

```text
// addressing wrapping.
```

## Source note 153, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L453)

```text
// If the first and / or the last rows have the same X spans as the middle
```

## Source note 154, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L454)

```text
// part, merge them with it.
```

## Source note 155, line 490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L490)

```text
// A flattened dispatch extracted from ResolveCopyDumpRectangle.
```

## Source note 156, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L502)

```text
// Returns the height of a render target that's needed and can be created,
```

## Source note 157, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L503)

```text
// taking guest and host limits into account. EDRAM base and 32bpp/64bpp are
```

## Source note 158, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L504)

```text
// not taken into account, the same height is used for all render targets even
```

## Source note 159, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L505)

```text
// if the implementation supports mixed-size render targets, so the
```

## Source note 160, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L506)

```text
// implementation can freely disable individual render targets and let the
```

## Source note 161, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L507)

```text
// other ones use the newly available space without restarting the whole
```

## Source note 162, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L508)

```text
// render pass (on Vulkan, the actually used height is specified in
```

## Source note 163, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L509)

```text
// VkFramebuffer).
```

## Source note 164, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L515)

```text
// Whether depth buffer is encoded differently on the host, thus after
```

## Source note 165, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L516)

```text
// aliasing naively, precision may be lost - host depth must only be
```

## Source note 166, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L517)

```text
// overwritten if the new guest value is different than the current host depth
```

## Source note 167, line 518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L518)

```text
// when converted to the guest format (this catches the usual case of
```

## Source note 168, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L519)

```text
// overwriting the depth buffer for clearing it mostly). 534507D6 intro
```

## Source note 169, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L520)

```text
// cutscene, for example, has a good example of corruption that happens if
```

## Source note 170, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L521)

```text
// this is not handled - the upper 1280x384 pixels are rendered in a very
```

## Source note 171, line 522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L522)

```text
// "striped" way if the depth precision is lost (if this is made always return
```

## Source note 172, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L523)

```text
// false).
```

## Source note 173, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L540)

```text
// 3 bits for each.
```

## Source note 174, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L554)

```text
// Returns mappings between ranges within the specified tile rectangle (not
```

## Source note 175, line 555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L555)

```text
// render target texture rectangle - textures may have any pitch they need)
```

## Source note 176, line 556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L556)

```text
// from ResolveInfo::GetCopyEdramTileSpan and render targets owning them to
```

## Source note 177, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L557)

```text
// rectangles_out.
```

## Source note 178, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L566)

```text
// Sets up the needed render targets and transfers to perform a clear in a
```

## Source note 179, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L567)

```text
// resolve operation via a host render target clear. resolve_info is expected
```

## Source note 180, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L568)

```text
// to be obtained via draw_util::GetResolveInfo. Returns whether any clears
```

## Source note 181, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L569)

```text
// need to be done (false in both empty and error cases).
```

## Source note 182, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L578)

```text
// For pixel shader interlock.
```

## Source note 183, line 582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L582)

```text
// To be called by the implementation when interlocked writes to all of the
```

## Source note 184, line 583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L583)

```text
// EDRAM memory are committed with a memory barrier.
```

## Source note 185, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L593)

```text
// resolution_scale_targets (ADR-012). Phase 1 only reports which render
```

## Source note 186, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L594)

```text
// target sizes the list would scale (log_resolution_scale_targets).
```

## Source note 187, line 598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L598)

```text
// For host render targets.
```

## Source note 188, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L602)

```text
// Need to store keys, not pointers to render targets themselves, because
```

## Source note 189, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L603)

```text
// ownership transfer is also what's used to determine when to place
```

## Source note 190, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L604)

```text
// barriers with pixel shader interlock, and in this case there are no host
```

## Source note 191, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L605)

```text
// render targets.
```

## Source note 192, line 606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L606)

```text
// Render target this range is last used by.
```

## Source note 193, line 608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L608)

```text
// Host target containing the current depth bits (8:31).
```

## Source note 194, line 609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L609)

```text
// Stencil-only color writes leave it current.
```

## Source note 195, line 611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L611)

```text
// Last host-side depth render targets that used this range even if it has
```

## Source note 196, line 612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L612)

```text
// been used by a different render target since then, only used if the
```

## Source note 197, line 613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L613)

```text
// respective format has a different encoding on the host. They are tracked
```

## Source note 198, line 614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L614)

```text
// separately, overwritten if the host value converted to the guest format
```

## Source note 199, line 615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L615)

```text
// becomes out of sync with the guest value. Even if the host uses float32
```

## Source note 200, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L616)

```text
// to emulate both unorm24 and float24 (Vulkan on AMD), the unorm24 and
```

## Source note 201, line 617

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L617)

```text
// float24 render targets are tracked separately from each other, so
```

## Source note 202, line 618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L618)

```text
// switching between unorm24 and float24 for the same depth data (clearing
```

## Source note 203, line 619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L619)

```text
// of most render targets is done through unorm24 without a viewport - very
```

## Source note 204, line 620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L620)

```text
// common) is not destructive as well (f32tof24(host_f32) == guest_f24 does
```

## Source note 205, line 621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L621)

```text
// not imply f32tou24(host_f32) == guest_u24, thus aliasing float24 with
```

## Source note 206, line 622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L622)

```text
// unorm24 through the same float32 buffer will drop the precision of the
```

## Source note 207, line 623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L623)

```text
// float32 value to that of an unorm24 with a totally wrong value). If the
```

## Source note 208, line 624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L624)

```text
// range hasn't been used yet (render_target.IsEmpty() == true), these are
```

## Source note 209, line 625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L625)

```text
// empty too.
```

## Source note 210, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L651)

```text
// Last time used for something else. If it's a depth render target with
```

## Source note 211, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L652)

```text
// different host depth encoding, might have been overwritten by color,
```

## Source note 212, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L653)

```text
// or by a depth render target of a different format.
```

## Source note 213, line 658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L658)

```text
// Depth encoding is the same, but different addressing is needed.
```

## Source note 214, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L682)

```text
// Checks if changing ownership of the range to the specified render target
```

## Source note 215, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L683)

```text
// would require transferring data - primarily for barrier placement on the
```

## Source note 216, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L684)

```text
// pixel shader interlock path (where transfers do not involve copying, but
```

## Source note 217, line 685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L685)

```text
// barriers are still needed before accessing ranges written before the
```

## Source note 218, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L686)

```text
// barrier and addressed by different target-independent rasterization pixel
```

## Source note 219, line 687

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L687)

```text
// positions.
```

## Source note 220, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L693)

```text
// Updates ownership_ranges_, adds the transfers needed for the ownership
```

## Source note 221, line 694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L694)

```text
// change to transfers_append_out if it's not null. If keep_depth_bits is true
```

## Source note 222, line 695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L695)

```text
// the existing depth bits target is preserved.
```

## Source note 223, line 701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L701)

```text
// If failed to create, may contain nullptr to prevent attempting to create a
```

## Source note 224, line 702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L702)

```text
// render target twice.
```

## Source note 225, line 705

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L705)

```text
// Map of host render targets currently containing the most up-to-date version
```

## Source note 226, line 706

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L706)

```text
// of the tile. Has no gaps, unused parts are represented by empty render
```

## Source note 227, line 707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L707)

```text
// target keys.
```

## Source note 228, line 711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L711)

```text
// Render targets actually used by the draw call with the last successful
```

## Source note 229, line 712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L712)

```text
// update. 0 is depth, color starting from 1, nullptr if not bound.
```

## Source note 230, line 713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L713)

```text
// Only valid for non-pixel-shader-interlock paths.
```

## Source note 231, line 715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L715)

```text
// Render targets used by the draw call with the last successful update or
```

## Source note 232, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L716)

```text
// previous updates, unless a different or a totally new one was bound (or
```

## Source note 233, line 717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L717)

```text
// surface info was changed), to avoid unneeded render target switching (which
```

## Source note 234, line 718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L718)

```text
// is especially undesirable on tile-based GPUs) in the implementation if
```

## Source note 235, line 719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L719)

```text
// simply disabling depth / stencil test or color writes and then re-enabling
```

## Source note 236, line 720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L720)

```text
// (58410954 does this often with color). Must also be used to determine
```

## Source note 237, line 721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L721)

```text
// whether it's safe to enable depth / stencil or writing to a specific color
```

## Source note 238, line 722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L722)

```text
// render target in the pipeline for this draw call.
```

## Source note 239, line 723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L723)

```text
// Only valid for non-pixel-shader-interlock paths.
```

## Source note 240, line 725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L725)

```text
// If false, the next update must copy last_update_used_render_targets_ to
```

## Source note 241, line 726

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L726)

```text
// last_update_accumulated_render_targets_ - it's not beneficial or even
```

## Source note 242, line 727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L727)

```text
// incorrect to keep the previously bound render targets.
```

## Source note 243, line 729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L729)

```text
// The render target the last update draws into, and the last two frames
```

## Source note 244, line 730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L730)

```text
// each render target was drawn in (0 is never).
```

## Source note 245, line 734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L734)

```text
// After an update (for simplicity, even an unsuccessful update invalidates
```

## Source note 246, line 735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L735)

```text
// this), contains needed ownership transfer sources for each of the current
```

## Source note 247, line 736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L736)

```text
// render targets. They are reordered so for one source, all transfers are
```

## Source note 248, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/cache.h#L737)

```text
// consecutive in the array.
```
