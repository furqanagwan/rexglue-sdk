# Draw: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/util/draw.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L30)

```text
// For patch primitive types, the major mode is always explicit, so just
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L31)

```text
// checking if VGT_OUTPUT_PATH_CNTL::path_select is kTessellationEnable is
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L32)

```text
// enough.
```

## Source note 4, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L53)

```text
// Polygonal primitive types (not including points and lines) are rasterized as
```

## Source note 5, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L54)

```text
// triangles, have front and back faces, and also support face culling and fill
```

## Source note 6, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L55)

```text
// modes (polymode_front_ptype, polymode_back_ptype). Other primitive types are
```

## Source note 7, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L56)

```text
// always "front" (but don't support front face and back face culling, according
```

## Source note 8, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L57)

```text
// to OpenGL and Vulkan specifications - even if glCullFace is
```

## Source note 9, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L58)

```text
// GL_FRONT_AND_BACK, points and lines are still drawn), and may in some cases
```

## Source note 10, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L59)

```text
// use the "para" registers instead of "front" or "back" (for "parallelogram" -
```

## Source note 11, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L60)

```text
// like poly_offset_para_enable).
```

## Source note 12, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L65)

```text
// For patch primitive types, the major mode is always explicit, so just
```

## Source note 13, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L66)

```text
// checking if VGT_OUTPUT_PATH_CNTL::path_select is kTessellationEnable is
```

## Source note 14, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L67)

```text
// enough.
```

## Source note 15, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L92)

```text
// Whether with the current state, any samples to rasterize (for any reason, not
```

## Source note 16, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L93)

```text
// only to write something to a render target, but also to do sample counting or
```

## Source note 17, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L94)

```text
// pixel shader memexport) can be generated. Finally dropping draw calls can
```

## Source note 18, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L95)

```text
// only be done if the vertex shader doesn't memexport. Checks mostly special
```

## Source note 19, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L96)

```text
// cases (for both the guest and usual host implementations), not everything
```

## Source note 20, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L97)

```text
// like whether viewport / scissor are empty (until this truly matters in any
```

## Source note 21, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L98)

```text
// game, of course).
```

## Source note 22, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L101)

```text
// VIZ_QUERY survey geometry, killed after hi-Z on real hardware. Drawn only to
```

## Source note 23, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L102)

```text
// count coverage for its ID: no pixel shader, no color, no depth or stencil
```

## Source note 24, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L103)

```text
// writes (xenia-canary #1111).
```

## Source note 25, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L106)

```text
// Direct3D 10.1+ standard sample positions, also used in Vulkan, for
```

## Source note 26, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L107)

```text
// calculations related to host MSAA, in 1/16th of a pixel.
```

## Source note 27, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L113)

```text
// Direct3D 9 and Xenos constant polygon offset is an absolute floating-point
```

## Source note 28, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L114)

```text
// value.
```

## Source note 29, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L115)

```text
// It's possibly treated just as an absolute offset by the Xenos too - the
```

## Source note 30, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L116)

```text
// PA_SU_POLY_OFFSET_DB_FMT_CNTL::POLY_OFFSET_DB_IS_FLOAT_FMT switch was added
```

## Source note 31, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L117)

```text
// later in the R6xx, though this needs verification.
```

## Source note 32, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L118)

```text
// 5454082B, for example, for float24, sets the bias to 0.000002 - or slightly
```

## Source note 33, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L119)

```text
// above 2^-19.
```

## Source note 34, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L120)

```text
// The total polygon offset formula specified by Direct3D 9 is:
```

## Source note 35, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L121)

```text
// `offset = slope * slope factor + constant offset`
```

## Source note 36, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L123)

```text
// Direct3D 10, Metal, OpenGL and Vulkan, however, take the constant polygon
```

## Source note 37, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L124)

```text
// offset factor as a relative value, with the formula being:
```

## Source note 38, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L125)

```text
// `offset = slope * slope factor +
```

## Source note 39, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L126)

```text
//           maximum resolvable difference * constant factor`
```

## Source note 40, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L127)

```text
// where the maximum resolvable difference is:
```

## Source note 41, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L128)

```text
// - For a fixed-point depth buffer, the minimum representable non-zero value in
```

## Source note 42, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L129)

```text
//   the depth buffer, that is 1 / (2^24 - 1) for unorm24 (on Vulkan though it's
```

## Source note 43, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L130)

```text
//   allowed to be up to 2 / 2^24 in this case).
```

## Source note 44, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L131)

```text
// - For a floating-point depth buffer, it's:
```

## Source note 45, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L132)

```text
//   2 ^ (exponent of the maximum Z in the primitive - the number of explicitly
```

## Source note 46, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L133)

```text
//        stored mantissa bits)
```

## Source note 47, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L134)

```text
//   (23 explicitly stored bits for float32 - and 20 explicitly stored bits for
```

## Source note 48, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L135)

```text
//    float24).
```

## Source note 49, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L137)

```text
// While the polygon offset is a fixed-function feature in the pipeline, and the
```

## Source note 50, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L138)

```text
// formula can't be toggled between absolute and relative, it's important that
```

## Source note 51, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L139)

```text
// Xenia translates the guest absolute depth bias into the host relative depth
```

## Source note 52, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L140)

```text
// bias in a way that the values that separate coplanar geometry on the guest
```

## Source note 53, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L141)

```text
// qualitatively also still correctly separate them on the host.
```

## Source note 54, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L143)

```text
// It also should be taken into account that on Xenia, float32 depth values may
```

## Source note 55, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L144)

```text
// be snapped to float24 directly in the translated pixel shaders (to prevent
```

## Source note 56, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L145)

```text
// data loss if after reuploading a depth buffer to the EDRAM there's no way to
```

## Source note 57, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L146)

```text
// recover the full-precision value, that results in the inability to perform
```

## Source note 58, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L147)

```text
// more rendering passes for the same geometry), and not only to the nearest
```

## Source note 59, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L148)

```text
// value, but also just truncating them (so in case of data loss, the "greater
```

## Source note 60, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L149)

```text
// or equal" depth test function still works).
```

## Source note 61, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L151)

```text
// Because of this, the depth bias may be lost if Xenia translates it into a too
```

## Source note 62, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L152)

```text
// small value, and the conversion of the depth is done in the pixel shader.
```

## Source note 63, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L153)

```text
// Specifically, Xenia should not simply convert a value that separates coplanar
```

## Source note 64, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L154)

```text
// primitives as float24 just into something that still separates them as
```

## Source note 65, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L155)

```text
// float32. Essentially, if conversion to float24 is done in the pixel shader,
```

## Source note 66, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L156)

```text
// Xenia should make sure the polygon offset on the host is calculated as if the
```

## Source note 67, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L157)

```text
// host had float24 depth too, not float32.
```

## Source note 68, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L159)

```text
// Applies to both native host unorm24, and unorm24 emulated as host float32.
```

## Source note 69, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L160)

```text
// For native unorm24, this is exactly the inverse of the minimum representable
```

## Source note 70, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L161)

```text
// non-zero value.
```

## Source note 71, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L162)

```text
// For unorm24 emulated as float32, the minimum representable non-zero value for
```

## Source note 72, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L163)

```text
// a primitive in the [0.5, 1) range (the worst case that forward depth reaches
```

## Source note 73, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L164)

```text
// very quickly, at nearly `2 * near clipping plane distance`) is 2 ^ (-1 - 23),
```

## Source note 74, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L165)

```text
// or 2^-24, and this factor is almost 2^24.
```

## Source note 75, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L168)

```text
// For a host floating-point depth buffer, the integer value of the depth bias
```

## Source note 76, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L169)

```text
// is roughly how many ULPs primitives should be separated by.
```

## Source note 77, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L171)

```text
// Float24, however, has 3 mantissa bits fewer than float32 - so one float24 ULP
```

## Source note 78, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L172)

```text
// corresponds to 8 float32 ULPs - which means each conceptual "layer" of the
```

## Source note 79, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L173)

```text
// guest value should correspond to a polygon offset of 8. So, after the guest
```

## Source note 80, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L174)

```text
// absolute value is converted to "layers", it should be multiplied by 8 before
```

## Source note 81, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L175)

```text
// being used on the host with a float32 depth buffer.
```

## Source note 82, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L177)

```text
// The scale for converting the guest absolute depth bias to the "layers" needs
```

## Source note 83, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L178)

```text
// to be determined for the worst case - specifically, the [0.5, 1) range (1 is
```

## Source note 84, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L179)

```text
// a single value, so there's no need to take it into consideration). In this
```

## Source note 85, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L180)

```text
// range, Z values have the exponent of -1. Therefore, for float24, the absolute
```

## Source note 86, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L181)

```text
// offset is obtained from the "layer index" in this range as (disregarding the
```

## Source note 87, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L182)

```text
// slope term):
```

## Source note 88, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L183)

```text
// offset = 2 ^ (-1 - 20) * constant factor
```

## Source note 89, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L184)

```text
// Thus, to obtain the constant factor from the absolute offset in the range
```

## Source note 90, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L185)

```text
// with the lowest absolute precision, the offset needs to be multiplied by
```

## Source note 91, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L186)

```text
// 2^21.
```

## Source note 92, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L188)

```text
// Finally, the 0...0.5 range may be used on the host to represent the 0...1
```

## Source note 93, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L189)

```text
// guest depth range to be able to copy all possible encodings, which are
```

## Source note 94, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L190)

```text
// [0, 2), via a [0, 1] depth output variable, during EDRAM contents
```

## Source note 95, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L191)

```text
// reinterpretation. This is done by scaling the viewport depth bounds by 0.5.
```

## Source note 96, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L192)

```text
// However, there's no need to do anything to handle this scenario in the
```

## Source note 97, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L193)

```text
// polygon offset - it's calculated after applying the viewport transformation,
```

## Source note 98, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L194)

```text
// and the maximum Z value in the primitive will have an exponent lowered by 1,
```

## Source note 99, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L195)

```text
// thus the result will also have an exponent lowered by 1 - exactly what's
```

## Source note 100, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L196)

```text
// needed for remapping 0...1 to 0...0.5.
```

## Source note 101, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L202)

```text
// Using `ceil` because more offset is better, especially if flooring would
```

## Source note 102, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L203)

```text
// result in 0 - conceptually, if the offset is used at all, primitives need
```

## Source note 103, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L204)

```text
// to be separated in the depth buffer.
```

## Source note 104, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L208)

```text
// For float24, the conversion may be done in the translated pixel shaders,
```

## Source note 105, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L209)

```text
// including via truncation rather than rounding to the nearest. So, making
```

## Source note 106, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L210)

```text
// the integer bias always in the increments of 2^3 (2 ^ the difference in the
```

## Source note 107, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L211)

```text
// mantissa bit count between float32 and float24), and because of that, doing
```

## Source note 108, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L212)

```text
// `ceil` before changing the units from float24 ULPs to float32 ULPs.
```

## Source note 109, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L219)

```text
// For hosts not supporting separate front and back polygon offsets, returns the
```

## Source note 110, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L220)

```text
// polygon offset for the face which likely needs the offset the most (and that
```

## Source note 111, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L221)

```text
// will not be culled). The values returned will have the units of the original
```

## Source note 112, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L222)

```text
// registers (the scale is for 1/16 subpixels, multiply by
```

## Source note 113, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L223)

```text
// xenos::kPolygonOffsetScaleSubpixelUnit outside if the value for pixels is
```

## Source note 114, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L224)

```text
// needed).
```

## Source note 115, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L234)

```text
// Whether the pixel shader can be disabled on the host to speed up depth
```

## Source note 116, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L235)

```text
// pre-passes and shadowmaps. The shader must have its ucode analyzed. If
```

## Source note 117, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L236)

```text
// IsRasterizationPotentiallyDone, this shouldn't be called, and assumed false
```

## Source note 118, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L237)

```text
// instead. Helps reject the pixel shader in some cases - memexport draws in
```

## Source note 119, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L238)

```text
// 4D5307E6, and also most of some 1-point draws not covering anything done for
```

## Source note 120, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L239)

```text
// some reason in different games with a leftover pixel shader from the previous
```

## Source note 121, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L240)

```text
// draw, but with SQ_PROGRAM_CNTL destroyed, reducing the number of
```

## Source note 122, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L241)

```text
// unpredictable unneeded translations of random shaders with different host
```

## Source note 123, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L242)

```text
// modification bits, such as register count and depth format-related.
```

## Source note 124, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L243)

```text
// include_memory_export may be set to false to evaluate whether the pixel
```

## Source note 125, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L244)

```text
// shader has any side effects other than memexport.
```

## Source note 126, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L249)

```text
// Offset from render target UV = 0 to +UV.
```

## Source note 127, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L250)

```text
// For simplicity of cropping to the maximum size on the host; to match the
```

## Source note 128, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L251)

```text
// Direct3D 12 clipping / scissoring behavior with a fractional viewport, to
```

## Source note 129, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L252)

```text
// floor(TopLeftXY) ... floor(TopLeftXY + WidthHeight), on the real AMD, Intel
```

## Source note 130, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L253)

```text
// and Nvidia hardware (not WARP); as well as to hide the differences between
```

## Source note 131, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L254)

```text
// 0 and 8+ viewportSubPixelBits on Vulkan, and to prevent any numerical error
```

## Source note 132, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L255)

```text
// in bound checking in host APIs, viewport bounds are returned as integers.
```

## Source note 133, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L256)

```text
// Also they're returned as non-negative, also to make it easier to crop (so
```

## Source note 134, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L257)

```text
// Vulkan maxViewportDimensions and viewportBoundsRange don't have to be
```

## Source note 135, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L258)

```text
// handled separately - maxViewportDimensions is greater than or equal to the
```

## Source note 136, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L259)

```text
// largest framebuffer image size, so it's safe, and viewportBoundsRange is
```

## Source note 137, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L260)

```text
// always bigger than maxViewportDimensions. All fractional offsetting,
```

## Source note 138, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L261)

```text
// including the half-pixel offset, and cropping are handled via ndc_scale and
```

## Source note 139, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L262)

```text
// ndc_offset.
```

## Source note 140, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L264)

```text
// Extent can be zero for an empty viewport - host APIs not supporting empty
```

## Source note 141, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L265)

```text
// viewports need to use an empty scissor rectangle.
```

## Source note 142, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L269)

```text
// The scale is applied before the offset (like using multiply-add).
```

## Source note 143, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L273)

```text
// Converts the guest viewport (or fakes one if drawing without a viewport) to
```

## Source note 144, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L274)

```text
// a viewport, plus values to multiply-add the returned position by, usable on
```

## Source note 145, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L275)

```text
// host graphics APIs such as Direct3D 11+ and Vulkan, also forcing it to the
```

## Source note 146, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L276)

```text
// Direct3D clip space with 0...W Z rather than -W...W.
```

## Source note 147, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L285)

```text
// Offset from render target UV = 0 to +UV.
```

## Source note 148, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L287)

```text
// Extent can be zero.
```

## Source note 149, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L292)

```text
// Returns the color component write mask for the draw command taking into
```

## Source note 150, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L293)

```text
// account which color targets are written to by the pixel shader, as well as
```

## Source note 151, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L294)

```text
// components that don't exist in the formats of the render targets (render
```

## Source note 152, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L295)

```text
// targets with only non-existent components written are skipped, but
```

## Source note 153, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L296)

```text
// non-existent components are forced to written if some existing components of
```

## Source note 154, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L297)

```text
// the render target are actually used to make sure the host driver doesn't try
```

## Source note 155, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L298)

```text
// to take a slow path involving reading and mixing if there are any disabled
```

## Source note 156, line 299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L299)

```text
// components even if they don't actually exist).
```

## Source note 157, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L303)

```text
// Never an identity conversion - can always write conditional move instructions
```

## Source note 158, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L304)

```text
// to shaders that will be no-ops for conversion from guest to host samples.
```

## Source note 159, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L305)

```text
// While we don't know the exact guest sample pattern, due to the way
```

## Source note 160, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L306)

```text
// multisampled render targets are stored in the memory (like 1x2 single-sampled
```

## Source note 161, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L307)

```text
// pixels with 2x MSAA, or like 2x2 single-sampled pixels with 4x), assuming
```

## Source note 162, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L308)

```text
// that the sample 0 is the top sample, and the sample 1 is the bottom one.
```

## Source note 163, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L313)

```text
// On Direct3D 10.1 with native 2x MSAA, the top-left sample is 1, and the
```

## Source note 164, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L314)

```text
// bottom-right sample is 0.
```

## Source note 165, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L317)

```text
// When native 2x MSAA is not supported, using the top-left (0) and the
```

## Source note 166, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L318)

```text
// bottom-right (3) samples of the guaranteed 4x MSAA.
```

## Source note 167, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L330)

```text
// Gathers memory ranges involved in memexports in the shader with the float
```

## Source note 168, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L331)

```text
// constants from the registers, adding them to ranges_out.
```

## Source note 169, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L335)

```text
// To avoid passing values that the shader won't understand (even though
```

## Source note 170, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L336)

```text
// Direct3D 9 shouldn't pass them anyway).
```

## Source note 171, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L340)

```text
// Packed structures are small and can be passed to the shaders in root/push
```

## Source note 172, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L341)

```text
// constants.
```

## Source note 173, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L346)

```text
// With 32bpp/64bpp taken into account.
```

## Source note 174, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L350)

```text
// With offset to the region that edram_offset_x/y_div_8 are relative to.
```

## Source note 175, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L354)

```text
// Whether to fill the half-pixel offset gap on the left and the top sides
```

## Source note 176, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L355)

```text
// of the resolve region with the contents of the first surely covered
```

## Source note 177, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L356)

```text
// column / row with resolution scaling.
```

## Source note 178, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L365)

```text
// In pixels relatively to the origin of the EDRAM base tile.
```

## Source note 179, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L366)

```text
// 0...9 for 0...72.
```

## Source note 180, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L368)

```text
// 0...1 for 0...8.
```

## Source note 181, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L371)

```text
// In pixels.
```

## Source note 182, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L372)

```text
// May be zero if the original rectangle was somehow specified in a
```

## Source note 183, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L373)

```text
// totally broken way - in this case, the resolve must be dropped.
```

## Source note 184, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L376)

```text
// 1 to 7.
```

## Source note 185, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L383)

```text
// Returns tiles actually covered by a resolve area. Row length used is width of
```

## Source note 186, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L384)

```text
// the area in tiles, but the pitch between rows is edram_info.pitch_tiles.
```

## Source note 187, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L392)

```text
// 0...16384/32.
```

## Source note 188, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L398)

```text
// Up to the maximum period of the texture tiled address function (128x128
```

## Source note 189, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L399)

```text
// for 2D 1bpb).
```

## Source note 190, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L408)

```text
// For backends with Shader Model 5-like compute, host shaders to use to perform
```

## Source note 191, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L409)

```text
// copying in resolve operations.
```

## Source note 192, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L427)

```text
// Debug name of the pipeline state object with this shader.
```

## Source note 193, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L429)

```text
// Whether the EDRAM source needs be bound as a raw buffer (ByteAddressBuffer
```

## Source note 194, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L430)

```text
// in Direct3D) since it can load different numbers of 32-bit values at once
```

## Source note 195, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L431)

```text
// on some hardware. If the host API doesn't support raw buffers, a typed
```

## Source note 196, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L432)

```text
// buffer with source_bpe_log2-byte elements needs to be used instead.
```

## Source note 197, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L434)

```text
// Log2 of bytes per element of the type of the EDRAM buffer bound to the
```

## Source note 198, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L435)

```text
// shader (at least 2).
```

## Source note 199, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L437)

```text
// Log2 of bytes per element of the type of the destination buffer bound to
```

## Source note 200, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L438)

```text
// the shader (at least 2 because of the 128 megatexel minimum requirement on
```

## Source note 201, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L439)

```text
// Direct3D 10+ - D3D12_REQ_BUFFER_RESOURCE_TEXEL_COUNT_2_TO_EXP - that
```

## Source note 202, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L440)

```text
// prevents binding the entire shared memory buffer with smaller element
```

## Source note 203, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L441)

```text
// sizes).
```

## Source note 204, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L443)

```text
// Log2 of number of pixels in a single thread group along X and Y. 64 threads
```

## Source note 205, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L444)

```text
// per group preferred (GCN lane count).
```

## Source note 206, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L451)

```text
// When the destination base is not needed (not binding the entire shared
```

## Source note 207, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L452)

```text
// memory buffer - with resoluion scaling, for instance), only the
```

## Source note 208, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L453)

```text
// DestRelative part may be passed to the shader to use less constants.
```

## Source note 209, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L465)

```text
// rt_specific is different for color and depth, the rest is the same and can
```

## Source note 210, line 466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L466)

```text
// be preserved in the root bindings when going from depth to color.
```

## Source note 211, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L478)

```text
// depth_edram_info / depth_original_base and color_edram_info /
```

## Source note 212, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L479)

```text
// color_original_base are set up if copying or clearing color and depth
```

## Source note 213, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L480)

```text
// respectively, according to RB_COPY_CONTROL.
```

## Source note 214, line 483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L483)

```text
// Original bases, without adjustment to a 160x32 region for packed offsets,
```

## Source note 215, line 484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L484)

```text
// for locating host render targets to perform clears if host render targets
```

## Source note 216, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L485)

```text
// are used for EDRAM emulation - the same as the base that the render target
```

## Source note 217, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L486)

```text
// will likely be used for drawing next, to prevent unneeded tile ownership
```

## Source note 218, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L487)

```text
// transfers between clears and first usage if clearing a subregion.
```

## Source note 219, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L492)

```text
// Like coordinate_info.width_div_8, but not needed for shaders.
```

## Source note 220, line 493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L493)

```text
// In pixels.
```

## Source note 221, line 494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L494)

```text
// May be zero if the original rectangle was somehow specified in a totally
```

## Source note 222, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L495)

```text
// broken way - in this case, the resolve must be dropped.
```

## Source note 223, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L501)

```text
// The address of the texture or the location within the texture that
```

## Source note 224, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L502)

```text
// copy_dest_coordinate_info.offset_x/y_div_8 - the origin of the copy
```

## Source note 225, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L503)

```text
// destination - is relative to.
```

## Source note 226, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L505)

```text
// Memory range that will potentially be modified by copying to the texture.
```

## Source note 227, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L506)

```text
// copy_dest_extent_length may be zero if something is wrong with the
```

## Source note 228, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L507)

```text
// destination, in this case, clearing may still be done, but copying must be
```

## Source note 229, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L508)

```text
// dropped.
```

## Source note 230, line 512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L512)

```text
// The clear shaders always write to a uint4 view of EDRAM.
```

## Source note 231, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L521)

```text
// See GetResolveEdramTileSpan documentation for explanation.
```

## Source note 232, line 552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L552)

```text
// Not doing -32...32 to -1...1 clamping here as a hack for k_16_16 and
```

## Source note 233, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L553)

```text
// k_16_16_16_16 blending emulation when using host render targets as it
```

## Source note 234, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L554)

```text
// would be inconsistent with the usual way of clearing with a depth quad.
```

## Source note 235, line 564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L564)

```text
// 8 guest MSAA samples per invocation.
```

## Source note 236, line 581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L581)

```text
// Returns false if there was an error obtaining the info making it totally
```

## Source note 237, line 582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L582)

```text
// invalid. fixed_rg[ba]16_truncated_to_minus_1_to_1 is false if 16_16[_16_16]
```

## Source note 238, line 583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L583)

```text
// color render target formats are properly emulated as -32...32, true if
```

## Source note 239, line 584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L584)

```text
// emulated as snorm, with range limited to -1...1, but with correct blending
```

## Source note 240, line 585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L585)

```text
// within that range.
```

## Source note 241, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L591)

```text
// Returns log2 of the copy destination texel size in bytes from a resolve's
```

## Source note 242, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L592)

```text
// copy_dest_info (format already normalized by GetResolveInfo) - the same
```

## Source note 243, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/util/draw.h#L593)

```text
// derivation GetResolveInfo used for the destination extent.
```
