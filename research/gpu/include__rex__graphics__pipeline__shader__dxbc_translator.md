# Dxbc translator: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/dxbc_translator.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L30)

```text
// Generates shader model 5_1 byte code (for Direct3D 12).
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L32)

```text
// IMPORTANT CONTRIBUTION NOTES:
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L34)

```text
// While DXBC may look like a flexible and high-level representation with highly
```

## Source note 4, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L35)

```text
// generalized building blocks, actually it has a lot of restrictions on operand
```

## Source note 5, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L36)

```text
// usage!
```

## Source note 6, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L40)

```text
// !!!DO NOT ADD ANYTHING FXC THAT WOULD NOT PRODUCE!!!
```

## Source note 7, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L44)

```text
// Before adding any sequence that you haven't seen in Xenia, try writing
```

## Source note 8, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L45)

```text
// equivalent code in HLSL and running it through FXC, try with /Od, try with
```

## Source note 9, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L46)

```text
// full optimization, but if you see that FXC follows a different pattern than
```

## Source note 10, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L47)

```text
// what you are expecting, do what FXC does!!!
```

## Source note 11, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L48)

```text
// SEE THE NOTES DXBC.H BEFORE WRITING ANYTHING RELATED TO DXBC!
```

## Source note 12, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L57)

```text
// Stage linkage ordering and rules (must be respected not only within the
```

## Source note 13, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L58)

```text
// DxbcShaderTranslator, but also by everything else between the VS and the
```

## Source note 14, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L59)

```text
// PS, such as geometry shaders for primitive types, and built-in pixel
```

## Source note 15, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L60)

```text
// shaders for processing the fragment depth when there's no guest pixel
```

## Source note 16, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L61)

```text
// shader):
```

## Source note 17, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L63)

```text
// Note that VS means the guest VS here - can be VS or DS on the host. RS
```

## Source note 18, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L64)

```text
// means the fixed-function rasterizer.
```

## Source note 19, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L66)

```text
// The beginning of the parameters must match between the output of the
```

## Source note 20, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L67)

```text
// producing stage and the input of the consuming stage, while the tail can be
```

## Source note 21, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L68)

```text
// stage-specific or cut off.
```

## Source note 22, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L70)

```text
// - Interpolators (TEXCOORD) - VS > GS > RS > PS, used interpolators are all
```

## Source note 23, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L71)

```text
//   unconditionally referenced in all these stages.
```

## Source note 24, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L72)

```text
// - Point coordinates (XESPRITETEXCOORD) - GS > RS > PS, must be present in
```

## Source note 25, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L73)

```text
//   none or in all, if drawing points, and PsParamGen is used.
```

## Source note 26, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L74)

```text
// - Position (SV_Position) - VS > GS > RS > PS, used in PS if actually needed
```

## Source note 27, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L75)

```text
//   for something (PsParamGen, alpha to coverage when oC0 is written, depth
```

## Source note 28, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L76)

```text
//   conversion, ROV render backend), the presence in PS depends on the usage
```

## Source note 29, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L77)

```text
//   within the PS, not on linkage, therefore it's the last in PS so it can be
```

## Source note 30, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L78)

```text
//   dropped from PS without effect on linkage.
```

## Source note 31, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L79)

```text
// - Clip distances (SV_ClipDistance) - VS > GS > RS.
```

## Source note 32, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L80)

```text
// - Cull distances (SV_CullDistance) - VS > RS or VS > GS.
```

## Source note 33, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L81)

```text
// - Vertex kill AND operator (SV_CullDistance) - VS > RS or VS > GS.
```

## Source note 34, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L82)

```text
// - Point size (XEPSIZE) - VS > GS.
```

## Source note 35, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L84)

```text
// Therefore, for the direct VS > PS path, the parameters may be the
```

## Source note 36, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L86)

```text
// - Shared between VS and PS:
```

## Source note 37, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L87)

```text
//   - Interpolators (TEXCOORD).
```

## Source note 38, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L88)

```text
//   - Position (SV_Position).
```

## Source note 39, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L89)

```text
// - VS output only:
```

## Source note 40, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L90)

```text
//   - Clip distances (SV_ClipDistance).
```

## Source note 41, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L91)

```text
//   - Cull distances (SV_CullDistance).
```

## Source note 42, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L92)

```text
//   - Vertex kill AND operator (SV_CullDistance).
```

## Source note 43, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L94)

```text
// When a GS is also used, the path between the VS and the GS is:
```

## Source note 44, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L95)

```text
// - Shared between VS and GS:
```

## Source note 45, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L96)

```text
//   - Interpolators (TEXCOORD).
```

## Source note 46, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L97)

```text
//   - Position (SV_Position).
```

## Source note 47, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L98)

```text
//   - Clip distances (SV_ClipDistance).
```

## Source note 48, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L99)

```text
//   - Cull distances (SV_CullDistance).
```

## Source note 49, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L100)

```text
//   - Vertex kill AND operator (SV_CullDistance).
```

## Source note 50, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L101)

```text
//   - Point size (XEPSIZE).
```

## Source note 51, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L103)

```text
// Then, between GS and PS, it's:
```

## Source note 52, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L104)

```text
// - Shared between GS and PS:
```

## Source note 53, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L105)

```text
//   - Interpolators (TEXCOORD).
```

## Source note 54, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L106)

```text
//   - Point coordinates (XESPRITETEXCOORD).
```

## Source note 55, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L107)

```text
//   - Position (SV_Position).
```

## Source note 56, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L108)

```text
// - GS output only:
```

## Source note 57, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L109)

```text
//   - Clip distances (SV_ClipDistance).
```

## Source note 58, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L112)

```text
// If anything in this is structure is changed in a way not compatible with
```

## Source note 59, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L113)

```text
// the previous layout, invalidate the pipeline storages by increasing this
```

## Source note 60, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L114)

```text
// version number (0xYYYYMMDD)!
```

## Source note 61, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L119)

```text
// [earlydepthstencil] - enable if alpha test and alpha to coverage are
```

## Source note 62, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L120)

```text
// disabled; ignored if anything in the shader blocks early Z writing.
```

## Source note 63, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L122)

```text
// Converting the depth to the closest 32-bit float representable exactly
```

## Source note 64, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L123)

```text
// as a 20e4 float, to support invariance in cases when the guest
```

## Source note 65, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L124)

```text
// reuploads a previously resolved depth buffer to the EDRAM, rounding
```

## Source note 66, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L125)

```text
// towards zero (which contradicts the rounding used by the Direct3D 9
```

## Source note 67, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L126)

```text
// reference rasterizer, but allows SV_DepthLessEqual to be used to allow
```

## Source note 68, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L127)

```text
// slightly coarse early Z culling; also truncating regardless of whether
```

## Source note 69, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L128)

```text
// the shader writes depth and thus always uses SV_Depth, for
```

## Source note 70, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L129)

```text
// consistency). MSAA is limited - depth must be per-sample
```

## Source note 71, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L130)

```text
// (SV_DepthLessEqual also explicitly requires sample or centroid position
```

## Source note 72, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L131)

```text
// interpolation), thus the sampler has to run at sample frequency even if
```

## Source note 73, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L132)

```text
// the device supports stencil loading and thus true non-ROV MSAA via
```

## Source note 74, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L133)

```text
// SV_StencilRef.
```

## Source note 75, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L134)

```text
// Fixed-function viewport depth bounds must be snapped to float24 for
```

## Source note 76, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L135)

```text
// clamping purposes.
```

## Source note 77, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L137)

```text
// Similar to kFloat24Truncating, but rounding to the nearest even,
```

## Source note 78, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L138)

```text
// however, always using SV_Depth rather than SV_DepthLessEqual because
```

## Source note 79, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L139)

```text
// rounding up results in a bigger value. Same viewport usage rules apply.
```

## Source note 80, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L145)

```text
// uint32_t 0.
```

## Source note 81, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L146)

```text
// Interpolators written by the vertex shader and needed by the pixel
```

## Source note 82, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L147)

```text
// shader.
```

## Source note 83, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L151)

```text
// Whether vertex killing with the "and" operator is used, and one more
```

## Source note 84, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L152)

```text
// SV_CullDistance needs to be written.
```

## Source note 85, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L155)

```text
// Dynamically indexable register count from SQ_PROGRAM_CNTL.
```

## Source note 86, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L157)

```text
// PA_CL_CLIP_CNTL::ps_ucp_mode for point primitives.
```

## Source note 87, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L159)

```text
// uint32_t 1.
```

## Source note 88, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L160)

```text
// Pipeline stage and input configuration.
```

## Source note 89, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L164)

```text
// uint32_t 0.
```

## Source note 90, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L165)

```text
// Interpolators written by the vertex shader and needed by the pixel
```

## Source note 91, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L166)

```text
// shader.
```

## Source note 92, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L169)

```text
// uint32_t 1.
```

## Source note 93, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L170)

```text
// Dynamically indexable register count from SQ_PROGRAM_CNTL.
```

## Source note 94, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L173)

```text
// If param_gen_enable is set, this must be set for point primitives, and
```

## Source note 95, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L174)

```text
// must not be set for other primitive types - enables the point sprite
```

## Source note 96, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L175)

```text
// coordinates input, and also effects the flag bits in PsParamGen.
```

## Source note 97, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L178)

```text
// Non-ROV - depth / stencil output mode.
```

## Source note 98, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L180)

```text
// For draws inside a hybrid occlusion query
```

## Source note 99, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L181)

```text
// (RTV + occlusion_query_full_counters): count the coverage before the
```

## Source note 100, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L182)

```text
// depth / stencil test into the ZPD counter's Total.
```

## Source note 101, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L199)

```text
// Constant buffer bindings in space 0.
```

## Source note 102, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L208)

```text
// Some are referenced in xenos_draw.hlsli - check it too when updating!
```

## Source note 103, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L229)

```text
// 1 to write new depth to the depth buffer, 0 to keep the old one if the
```

## Source note 104, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L230)

```text
// depth test passes.
```

## Source note 105, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L233)

```text
// If the depth / stencil test has failed, but resulted in a stencil value
```

## Source note 106, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L234)

```text
// that is different than the one currently in the depth buffer, write it
```

## Source note 107, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L235)

```text
// anyway and don't run the rest of the shader (to check if the sample may
```

## Source note 108, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L236)

```text
// be discarded some way) - use when alpha test and alpha to coverage are
```

## Source note 109, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L237)

```text
// disabled. Ignored by the shader if not applicable to it (like if it has
```

## Source note 110, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L238)

```text
// kill instructions or writes the depth output).
```

## Source note 111, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L268)

```text
// IF SYSTEM CONSTANTS ARE CHANGED OR ADDED, THE FOLLOWING MUST BE UPDATED:
```

## Source note 112, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L269)

```text
// - SystemConstants::Index enum.
```

## Source note 113, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L270)

```text
// - system_constant_rdef_.
```

## Source note 114, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L271)

```text
// - d3d12/shaders/xenos_draw.hlsli (for geometry shaders).
```

## Source note 115, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L302)

```text
// Diameter in guest screen coordinates > radius (0.5 * diameter) in the NDC
```

## Source note 116, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L303)

```text
// for the host viewport.
```

## Source note 117, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L306)

```text
// Each byte contains post-swizzle TextureSign values for each of the needed
```

## Source note 118, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L307)

```text
// components of each of the 32 used texture fetch constants.
```

## Source note 119, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L310)

```text
// Whether each texture in fetch constants is resolution-scaled.
```

## Source note 120, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L312)

```text
// Log2 of X and Y sample size. Used for alpha to mask, and for MSAA with
```

## Source note 121, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L313)

```text
// ROV, this is used for EDRAM address calculation.
```

## Source note 122, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L317)

```text
// If alpha to mask is disabled, the entire alpha_to_mask value must be 0.
```

## Source note 123, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L318)

```text
// If alpha to mask is enabled, bits 0:7 are sample offsets, and bit 8 must
```

## Source note 124, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L319)

```text
// be 1.
```

## Source note 125, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L323)

```text
// ZPD counter slot for ROV draws (RG-GDK-010a); UINT32_MAX when no
```

## Source note 126, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L324)

```text
// occlusion query is open, which the shader treats as "don't count".
```

## Source note 127, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L344)

```text
// In stencil function/operations (they match the layout of the
```

## Source note 128, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L345)

```text
// function/operations in RB_DEPTHCONTROL):
```

## Source note 129, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L346)

```text
// 0:2 - comparison function (bit 0 - less, bit 1 - equal, bit 2 - greater).
```

## Source note 130, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L347)

```text
// 3:5 - fail operation.
```

## Source note 131, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L348)

```text
// 6:8 - pass operation.
```

## Source note 132, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L349)

```text
// 9:11 - depth fail operation.
```

## Source note 133, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L372)

```text
// RT format combined with RenderTargetCache::kPSIColorFormatFlag values
```

## Source note 134, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L373)

```text
// (pass via RenderTargetCache::AddPSIColorFormatFlags).
```

## Source note 135, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L376)

```text
// Format info - values to clamp the color to before blending or storing.
```

## Source note 136, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L377)

```text
// Low color, low alpha, high color, high alpha.
```

## Source note 137, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L380)

```text
// Format info - mask to apply to the old packed RT data, and to apply as
```

## Source note 138, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L381)

```text
// inverted to the new packed data, before storing (more or less the inverse
```

## Source note 139, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L382)

```text
// of the write mask packed like render target channels). This can be used
```

## Source note 140, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L383)

```text
// to bypass unpacking if blending is not used. If 0 and not blending,
```

## Source note 141, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L384)

```text
// reading the old data from the EDRAM buffer is not required.
```

## Source note 142, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L387)

```text
// Render target blending options - RB_BLENDCONTROL, with only the relevant
```

## Source note 143, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L388)

```text
// options (factors and operations - AND 0x1FFF1FFF). If 0x00010001
```

## Source note 144, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L389)

```text
// (1 * src + 0 * dst), blending is disabled for the render target.
```

## Source note 145, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L392)

```text
// The constant blend factor for the respective modes.
```

## Source note 146, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L395)

```text
// Packed fixed texture conversion (see texture_util::GetIntegerScaleBits).
```

## Source note 147, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L396)

```text
// Every component occupies 6 bits in bits 0:23
```

## Source note 148, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L397)

```text
//   bits 0:3 = component_bits - 1
```

## Source note 149, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L398)

```text
//   bits 4:5 = xenos::TextureSign
```

## Source note 150, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L399)

```text
// bit 24 = normalized num_format
```

## Source note 151, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L400)

```text
// bit 26 = point sampled fetch constant
```

## Source note 152, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L401)

```text
// Zero means no conversion.
```

## Source note 153, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L465)

```text
// Shader resource view binding spaces.
```

## Source note 154, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L467)

```text
// SRVMainSpaceRegister t# layout.
```

## Source note 155, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L474)

```text
// Shader resource view bindings in SRVSpace::kMain.
```

## Source note 156, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L480)

```text
// 192 textures at most because there are 32 fetch constants, and textures can
```

## Source note 157, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L481)

```text
// be 2D array, 3D or cube, and also signed and unsigned.
```

## Source note 158, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L486)

```text
// Temporary for WriteResourceDefinition.
```

## Source note 159, line 490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L490)

```text
// Stacked and 3D are separate TextureBindings, even for bindless for null
```

## Source note 160, line 491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L491)

```text
// descriptor handling simplicity.
```

## Source note 161, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L497)

```text
// Arbitrary limit - there can't be more than 2048 in a shader-visible
```

## Source note 162, line 498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L498)

```text
// descriptor heap, though some older hardware (tier 1 resource binding -
```

## Source note 163, line 499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L499)

```text
// Nvidia Fermi) doesn't support more than 16 samplers bound at once (we can't
```

## Source note 164, line 500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L500)

```text
// really do anything if a game uses more than 16), but just to have some
```

## Source note 165, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L501)

```text
// limit so sampler count can easily be packed into 32-bit map keys (for
```

## Source note 166, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L502)

```text
// instance, for root signatures). But shaders can specify overrides for
```

## Source note 167, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L503)

```text
// filtering modes, and the number of possible combinations is huge - let's
```

## Source note 168, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L504)

```text
// limit it to something sane.
```

## Source note 169, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L519)

```text
// Unordered access view bindings in space 0.
```

## Source note 170, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L533)

```text
// Creates a special pixel shader without color outputs - this resets the
```

## Source note 171, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L534)

```text
// state of the translator.
```

## Source note 172, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L535)

```text
// `viz_survey` (ROV): marks the ZPass lane of the counter slot instead of
```

## Source note 173, line 536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L536)

```text
// counting, for VIZ surveys, which only need zero or not (xenia-canary
```

## Source note 174, line 537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L537)

```text
// #1111).
```

## Source note 175, line 544

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L544)

```text
// Common functions useful not only for the translator, but also for render
```

## Source note 176, line 545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L545)

```text
// target reinterpretation.
```

## Source note 177, line 547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L547)

```text
// Converts the color value externally clamped to [0, 31.875] to 7e3 floating
```

## Source note 178, line 548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L548)

```text
// point, with zeros in bits 10:31, rounding to the nearest even. Source and
```

## Source note 179, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L549)

```text
// destination may be the same, temporary must be different than both.
```

## Source note 180, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L554)

```text
// Same as PreClampedFloat32To7e3, but clamps the input to [0, 31.875].
```

## Source note 181, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L559)

```text
// Converts the 7e3 number in bits [f10_shift, f10_shift + 10) to a 32-bit
```

## Source note 182, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L560)

```text
// float. Two temporaries must be different, but one can be the same as the
```

## Source note 183, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L561)

```text
// source. The destination may be anything writable.
```

## Source note 184, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L566)

```text
// Converts the depth value externally clamped to the representable [0, 2)
```

## Source note 185, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L567)

```text
// range to 20e4 floating point, with zeros in bits 24:31, rounding to the
```

## Source note 186, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L568)

```text
// nearest even or towards zero. Source and destination may be the same,
```

## Source note 187, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L569)

```text
// temporary must be different than both. If remap_from_0_to_0_5 is true, it's
```

## Source note 188, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L570)

```text
// assumed that 0...1 is pre-remapped to 0...0.5 in the input.
```

## Source note 189, line 576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L576)

```text
// Converts the 20e4 number in bits [f24_shift, f24_shift + 10) to a 32-bit
```

## Source note 190, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L577)

```text
// float. Two temporaries must be different, but one can be the same as the
```

## Source note 191, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L578)

```text
// source. The destination may be anything writable. If remap_to_0_to_0_5 is
```

## Source note 192, line 579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L579)

```text
// true, 0...1 in float24 will be remaped to 0...0.5 in float32.
```

## Source note 193, line 585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L585)

```text
// Converts one scalar from piecewise linear gamma to linear. The target may
```

## Source note 194, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L586)

```text
// be the same as the source, the temporary variables must be different. If
```

## Source note 195, line 587

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L587)

```text
// the source is not pre-saturated, saturation will be done internally.
```

## Source note 196, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L593)

```text
// Converts one scalar, which must be saturated before calling this function,
```

## Source note 197, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L594)

```text
// from linear to piecewise linear gamma. The target may be the same as either
```

## Source note 198, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L595)

```text
// the source or as temp_or_target, but not as both (and temp_or_target may
```

## Source note 199, line 596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L596)

```text
// not be the same as the source). temp_non_target must be different.
```

## Source note 200, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L632)

```text
// IF ANY OF THESE ARE CHANGED, WriteInputSignature and WriteOutputSignature
```

## Source note 201, line 633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L633)

```text
// MUST BE UPDATED!
```

## Source note 202, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L637)

```text
// GetSystemConstantSrc + MarkSystemConstantUsed is for special cases of
```

## Source note 203, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L638)

```text
// building the source unconditionally - in general, LoadSystemConstant must
```

## Source note 204, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L639)

```text
// be used instead.
```

## Source note 205, line 643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L643)

```text
// Offset should be offsetof(SystemConstants, field). Swizzle values are
```

## Source note 206, line 644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L644)

```text
// relative to the first component in the vector according to offsetof - to
```

## Source note 207, line 645

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L645)

```text
// request a scalar, use XXXX swizzle, and if it's at +4 in its 16-byte
```

## Source note 208, line 646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L646)

```text
// vector, it will be turned into YYYY, and so on. The swizzle may include
```

## Source note 209, line 647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L647)

```text
// out-of-bounds components of the vector for simplicity of use, assuming they
```

## Source note 210, line 648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L648)

```text
// will be dropped anyway later.
```

## Source note 211, line 694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L694)

```text
// Whether to use switch-case rather than if (pc >= label) for control flow.
```

## Source note 212, line 697

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L697)

```text
// Allocates new consecutive r# registers for internal use and returns the
```

## Source note 213, line 698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L698)

```text
// index of the first.
```

## Source note 214, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L700)

```text
// Frees the last allocated internal r# registers for later reuse.
```

## Source note 215, line 703

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L703)

```text
// ExportToMemory modifies the values of eA/eM# for simplicity, call only
```

## Source note 216, line 704

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L704)

```text
// before starting a new export or ending the invocation or making it
```

## Source note 217, line 705

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L705)

```text
// inactive.
```

## Source note 218, line 713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L713)

```text
// See system_temp_depth_stencil_ documentation for explanation of cases.
```

## Source note 219, line 715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L715)

```text
// Needed for all cases (early, late, late with oDepth).
```

## Source note 220, line 719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L719)

```text
// With host render targets, the depth format may be float24, in this
```

## Source note 221, line 720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L720)

```text
// case, need to multiply it by 0.5 since 0...1 of the guest is stored as
```

## Source note 222, line 721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L721)

```text
// 0...0.5 on the host, and also to convert it.
```

## Source note 223, line 722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L722)

```text
// With ROV, need to store it to write later.
```

## Source note 224, line 727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L727)

```text
// Whether the current non-ROV pixel shader should convert the depth to 20e4.
```

## Source note 225, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L737)

```text
// Whether it's possible and worth skipping running the translated shader for
```

## Source note 226, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L738)

```text
// 2x2 quads.
```

## Source note 227, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L744)

```text
// Converts the pre-clamped depth value to 24-bit (storing the result in bits
```

## Source note 228, line 745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L745)

```text
// 0:23 and zeros in 24:31, not creating room for stencil - since this may be
```

## Source note 229, line 746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L746)

```text
// involved in comparisons) according to the format specified in the system
```

## Source note 230, line 747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L747)

```text
// constants. Source and destination may be the same, temporary must be
```

## Source note 231, line 748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L748)

```text
// different than both.
```

## Source note 232, line 752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L752)

```text
// Does all the related to depth / stencil, including or not including
```

## Source note 233, line 753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L753)

```text
// writing based on whether it's late, or on whether it's safe to do it early.
```

## Source note 234, line 754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L754)

```text
// Updates system_temp_rov_params_ result and coverage if allowed and safe,
```

## Source note 235, line 755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L755)

```text
// updates system_temp_depth_stencil_, and if early and the coverage is empty
```

## Source note 236, line 756

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L756)

```text
// for all pixels in the 2x2 quad and safe to return early (stencil is
```

## Source note 237, line 757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L757)

```text
// unchanged or known that it's safe not to await kills/alphatest/AtoC),
```

## Source note 238, line 758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L758)

```text
// returns from the shader.
```

## Source note 239, line 760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L760)

```text
// Adds the depth/stencil outcomes in system_temp_rov_params_ to the open
```

## Source note 240, line 761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L761)

```text
// ZPD query's counter slot: ZPass from the surviving coverage, and, with
```

## Source note 241, line 762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L762)

```text
// occlusion_query_full_counters, ZFail and StencilFail from bits 12:19.
```

## Source note 242, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L764)

```text
// Adds the coverage before the depth / stencil test to the Total counter of
```

## Source note 243, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L765)

```text
// the active ZPD counter slot (RTV hybrid queries).
```

## Source note 244, line 767

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L767)

```text
// Unpacks a 32bpp or a 64bpp color in packed_temp.packed_temp_components to
```

## Source note 245, line 768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L768)

```text
// color_temp, using 2 temporary VGPRs.
```

## Source note 246, line 772

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L772)

```text
// Packs a float32x4 color value to 32bpp or a 64bpp in color_temp to
```

## Source note 247, line 773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L773)

```text
// packed_temp.packed_temp_components, using 2 temporary VGPR. color_temp and
```

## Source note 248, line 774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L774)

```text
// packed_temp may be the same if packed_temp_components is 0. If the format
```

## Source note 249, line 775

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L775)

```text
// is 32bpp, will still write the high part to break register dependency.
```

## Source note 250, line 779

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L779)

```text
// Emits a sequence of `case` labels for color blend factors, generating the
```

## Source note 251, line 780

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L780)

```text
// factor from src_temp.rgb and dst_temp.rgb to factor_temp.rgb. factor_temp
```

## Source note 252, line 781

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L781)

```text
// can be the same as src_temp or dst_temp.
```

## Source note 253, line 783

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L783)

```text
// Emits a sequence of `case` labels for alpha blend factors, generating the
```

## Source note 254, line 784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L784)

```text
// factor from src_temp.a and dst_temp.a to factor_temp.factor_component.
```

## Source note 255, line 785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L785)

```text
// factor_temp can be the same as src_temp or dst_temp.
```

## Source note 256, line 789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L789)

```text
// Writing the prologue.
```

## Source note 257, line 790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L790)

```text
// Applies the offset to vertex or tessellation patch indices in the source
```

## Source note 258, line 791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L791)

```text
// components, restricts them to the minimum and the maximum index values, and
```

## Source note 259, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L792)

```text
// converts them to floating-point. The destination may be the same as the
```

## Source note 260, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L793)

```text
// source.
```

## Source note 261, line 803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L803)

```text
// For RTV, adds the sample to coverage_temp.coverage_temp_component if it
```

## Source note 262, line 804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L804)

```text
// passes alpha to mask (or, if initialize == true (for the first sample
```

## Source note 263, line 805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L805)

```text
// tested), overwrites the output to initialize it).
```

## Source note 264, line 806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L806)

```text
// For ROV, masks the sample away from coverage_temp.coverage_temp_component
```

## Source note 265, line 807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L807)

```text
// if it doesn't pass alpha to mask.
```

## Source note 266, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L808)

```text
// threshold_offset and temp.temp_component can be the same if needed.
```

## Source note 267, line 814

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L814)

```text
// Performs alpha to coverage if necessary, for RTV, writing to oMask, and for
```

## Source note 268, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L815)

```text
// ROV, updating the low (coverage) bits of system_temp_rov_params_.x. Done
```

## Source note 269, line 816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L816)

```text
// manually even for RTV to maintain the guest dithering pattern and because
```

## Source note 270, line 817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L817)

```text
// alpha can be exponent-biased. Also narrows the ZPD coverage temp by the
```

## Source note 271, line 818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L818)

```text
// alpha to coverage mask.
```

## Source note 272, line 827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L827)

```text
// Writes the original instruction disassembly in the output DXBC if enabled,
```

## Source note 273, line 828

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L828)

```text
// as shader messages, from instruction_disassembly_buffer_.
```

## Source note 274, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L831)

```text
// Converts a shader translator source operand to a DXBC emitter operand, or
```

## Source note 275, line 832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L832)

```text
// returns a zero literal operand if it's not going to be referenced. This may
```

## Source note 276, line 833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L833)

```text
// allocate a temporary register and emit instructions if the operand can't be
```

## Source note 277, line 834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L834)

```text
// used directly with most DXBC instructions (like, if it's an indexable GPR),
```

## Source note 278, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L835)

```text
// in this case, temp_pushed_out will be set to true, and PopSystemTemp must
```

## Source note 279, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L836)

```text
// be done when the operand is not needed anymore.
```

## Source note 280, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L839)

```text
// Writes the specified source (src must be usable as a vector `mov` source,
```

## Source note 281, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L840)

```text
// including to x#) to an instruction storage target.
```

## Source note 282, line 841

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L841)

```text
// can_store_memexport_address is for safety, to allow only proper MADs with a
```

## Source note 283, line 842

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L842)

```text
// stream constant to write to eA.
```

## Source note 284, line 846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L846)

```text
// The nesting of `if` instructions is the following:
```

## Source note 285, line 847

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L847)

```text
// - pc checks (labels).
```

## Source note 286, line 848

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L848)

```text
// - exec predicate/bool constant check.
```

## Source note 287, line 849

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L849)

```text
// - Instruction-level predicate checks.
```

## Source note 288, line 850

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L850)

```text
// As an optimization, where possible, the DXBC translator tries to merge
```

## Source note 289, line 851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L851)

```text
// multiple execs into one, not creating endif/if doing nothing, if the
```

## Source note 290, line 852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L852)

```text
// execution condition is the same. This can't be done across labels
```

## Source note 291, line 853

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L853)

```text
// (obviously) and in case `setp` is done in a predicated exec - in this case,
```

## Source note 292, line 854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L854)

```text
// the predicate value in the current exec may not match the predicate value
```

## Source note 293, line 855

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L855)

```text
// in the next exec.
```

## Source note 294, line 856

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L856)

```text
// Instruction-level predicate checks are also merged, and until a `setp` is
```

## Source note 295, line 857

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L857)

```text
// done, if the instruction has the same predicate condition as the exec it is
```

## Source note 296, line 858

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L858)

```text
// in, no instruction-level predicate `if` is created as well. One exception
```

## Source note 297, line 859

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L859)

```text
// to the usual way of instruction-level predicate handling is made for
```

## Source note 298, line 860

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L860)

```text
// instructions involving derivative computation, such as texture fetches with
```

## Source note 299, line 861

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L861)

```text
// computed LOD. The part involving derivatives is executed disregarding the
```

## Source note 300, line 862

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L862)

```text
// predication, but the result storing is predicated (this is handled in
```

## Source note 301, line 863

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L863)

```text
// texture fetch instruction implementation):
```

## Source note 302, line 864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L864)

```text
// https://docs.microsoft.com/en-us/windows/desktop/direct3dhlsl/dx9-graphics-reference-asm-ps-registers-output-color
```

## Source note 303, line 866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L866)

```text
// Updates the current flow control condition (to be called in the beginning
```

## Source note 304, line 867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L867)

```text
// of exec and in jumps), closing the previous conditionals if needed.
```

## Source note 305, line 868

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L868)

```text
// However, if the condition is not different, the instruction-level predicate
```

## Source note 306, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L869)

```text
// `if` also won't be closed - this must be checked separately if needed (for
```

## Source note 307, line 870

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L870)

```text
// example, in jumps). Also emits the last disassembly written to
```

## Source note 308, line 871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L871)

```text
// instruction_disassembly_buffer_ after closing the previous conditional and
```

## Source note 309, line 872

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L872)

```text
// before opening a new one.
```

## Source note 310, line 875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L875)

```text
// Closes `if`s opened by exec and instructions within them (but not by
```

## Source note 311, line 876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L876)

```text
// labels) and updates the state accordingly.
```

## Source note 312, line 878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L878)

```text
// Opens or reopens the predicate check conditional for the instruction, and
```

## Source note 313, line 879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L879)

```text
// emits the last disassembly written to instruction_disassembly_buffer_ after
```

## Source note 314, line 880

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L880)

```text
// closing the previous predicate conditional and before opening a new one.
```

## Source note 315, line 881

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L881)

```text
// This should be called before processing a non-control-flow instruction.
```

## Source note 316, line 883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L883)

```text
// Closes the instruction-level predicate `if` if it's open, useful if a flow
```

## Source note 317, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L884)

```text
// control instruction needs to do some code which needs to respect the exec's
```

## Source note 318, line 885

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L885)

```text
// conditional, but can't itself be predicated.
```

## Source note 319, line 895

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L895)

```text
// Returns the number of texture SRV and sampler offsets that need to be
```

## Source note 320, line 896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L896)

```text
// passed via a constant buffer to the shader.
```

## Source note 321, line 900

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L900)

```text
// Marks fetch constants as used by the DXBC shader and returns dxbc::Src
```

## Source note 322, line 901

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L901)

```text
// for the words 01 (pair 0), 23 (pair 1) or 45 (pair 2) of the texture fetch
```

## Source note 323, line 902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L902)

```text
// constant.
```

## Source note 324, line 923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L923)

```text
// Reduces finite host approximations to a chosen mantissa width
```

## Source note 325, line 924

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L924)

```text
// (xenia-canary #1190, opt-in through gpu_scalar_approximation_rounding).
```

## Source note 326, line 925

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L925)

```text
// The console's exact precision and rounding still aren't known.
```

## Source note 327, line 927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L927)

```text
// Reciprocal and reciprocal square root, as DIV (and SQRT) when the
```

## Source note 328, line 928

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L928)

```text
// rounding is enabled so the host's own approximate RCP/RSQ isn't rounded
```

## Source note 329, line 929

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L929)

```text
// twice, otherwise the host approximations.
```

## Source note 330, line 942

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L942)

```text
// Executable instructions - generated during translation.
```

## Source note 331, line 944

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L944)

```text
// Complete shader object, with all the needed blobs and dcl_ instructions -
```

## Source note 332, line 945

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L945)

```text
// generated in the end of translation.
```

## Source note 333, line 948

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L948)

```text
// Optional Direct3D features used by the shader.
```

## Source note 334, line 950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L950)

```text
// The statistics blob.
```

## Source note 335, line 953

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L953)

```text
// Assembler for shader_code_ and statistics_ (must be placed after them for
```

## Source note 336, line 954

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L954)

```text
// correct initialization order).
```

## Source note 337, line 956

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L956)

```text
// Assembler for shader_object_ and statistics_, for declarations before the
```

## Source note 338, line 957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L957)

```text
// shader code that depend on info gathered during translation (must be placed
```

## Source note 339, line 958

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L958)

```text
// after them for correct initialization order).
```

## Source note 340, line 961

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L961)

```text
// Buffer for instruction disassembly comments.
```

## Source note 341, line 964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L964)

```text
// Whether to write comments with the original Xenos instructions to the
```

## Source note 342, line 965

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L965)

```text
// output.
```

## Source note 343, line 968

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L968)

```text
// Vendor ID of the GPU manufacturer, for toggling unsupported features.
```

## Source note 344, line 971

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L971)

```text
// Whether textures and samplers should be bindless.
```

## Source note 345, line 974

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L974)

```text
// Whether the output merger should be emulated in pixel shaders.
```

## Source note 346, line 977

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L977)

```text
// Whether ROV shaders also count ZFail and StencilFail
```

## Source note 347, line 978

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L978)

```text
// (occlusion_query_full_counters).
```

## Source note 348, line 981

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L981)

```text
// Whether with RTV-based output-merger, k_8_8_8_8_GAMMA render targets are
```

## Source note 349, line 982

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L982)

```text
// stored as 8-bit with shader-side gamma conversion.
```

## Source note 350, line 985

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L985)

```text
// Whether 2x MSAA is emulated using real 2x MSAA rather than two samples of
```

## Source note 351, line 986

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L986)

```text
// 4x MSAA.
```

## Source note 352, line 989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L989)

```text
// Guest pixel host width / height.
```

## Source note 353, line 993

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L993)

```text
// Is currently writing the empty depth-only pixel shader, for
```

## Source note 354, line 994

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L994)

```text
// CompleteTranslation.
```

## Source note 355, line 998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L998)

```text
// Data types used in constants buffers. Listed in dependency order.
```

## Source note 356, line 1007

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1007)

```text
// Render target clamping ranges.
```

## Source note 357, line 1009

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1009)

```text
// User clip planes.
```

## Source note 358, line 1011

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1011)

```text
// Float constants - size written dynamically.
```

## Source note 359, line 1013

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1013)

```text
// Bool constants, texture signedness, front/back stencil, render target
```

## Source note 360, line 1014

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1014)

```text
// keep masks.
```

## Source note 361, line 1016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1016)

```text
// Loop constants.
```

## Source note 362, line 1018

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1018)

```text
// Fetch constants.
```

## Source note 363, line 1020

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1020)

```text
// Descriptor indices - size written dynamically.
```

## Source note 364, line 1028

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1028)

```text
// Name ignored for arrays.
```

## Source note 365, line 1041

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1041)

```text
// Number of constant buffer bindings used in this shader - also used for
```

## Source note 366, line 1042

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1042)

```text
// generation of indices of constant buffers that are optional.
```

## Source note 367, line 1057

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1057)

```text
// Mask of system constants (1 << SystemConstants::Index) used in the shader,
```

## Source note 368, line 1058

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1058)

```text
// so the remaining ones can be marked as unused in RDEF.
```

## Source note 369, line 1063

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1063)

```text
// Clip and cull distances must be tightly packed in Direct3D.
```

## Source note 370, line 1064

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1064)

```text
// Up to 6 SV_ClipDistances or SV_CullDistances depending on
```

## Source note 371, line 1065

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1065)

```text
// user_clip_plane_cull, then one SV_CullDistance if vertex_kill_and is used.
```

## Source note 372, line 1071

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1071)

```text
// nointerpolation inputs. SV_IsFrontFace (X) is for non-point PsParamGen,
```

## Source note 373, line 1072

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1072)

```text
// SV_SampleIndex (Y) is for memexport when sample-rate shading is otherwise
```

## Source note 374, line 1073

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1073)

```text
// needed anyway due to depth conversion.
```

## Source note 375, line 1076

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1076)

```text
// Mask of domain location actually used in the domain shader.
```

## Source note 376, line 1078

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1078)

```text
// Whether kInRegisterDSControlPointIndex has been used in the shader.
```

## Source note 377, line 1080

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1080)

```text
// Mask of the pixel/sample position actually used in the pixel shader.
```

## Source note 378, line 1082

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1082)

```text
// Whether the faceness has been used in the pixel shader.
```

## Source note 379, line 1085

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1085)

```text
// Number of currently allocated Xenia internal r# registers.
```

## Source note 380, line 1087

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1087)

```text
// Total maximum number of temporary registers ever used during this
```

## Source note 381, line 1088

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1088)

```text
// translation (for the declaration).
```

## Source note 382, line 1091

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1091)

```text
// Position in vertex shaders (because viewport and W transformations can be
```

## Source note 383, line 1092

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1092)

```text
// applied in the end of the shader).
```

## Source note 384, line 1094

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1094)

```text
// Special exports in vertex shaders.
```

## Source note 385, line 1096

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1096)

```text
// ROV only - 4 persistent VGPRs when writing to color targets, 2 VGPRs when
```

## Source note 386, line 1098

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1098)

```text
// X - Bit masks:
```

## Source note 387, line 1099

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1099)

```text
// 0:3 - Per-sample coverage at the current stage of the shader's execution.
```

## Source note 388, line 1100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1100)

```text
//       Affected by things like SV_Coverage, early or late depth / stencil
```

## Source note 389, line 1101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1101)

```text
//       (always resets bits for failing, no matter if need to defer writing),
```

## Source note 390, line 1102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1102)

```text
//       alpha to coverage.
```

## Source note 391, line 1103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1103)

```text
// 4:7 - Depth write deferred mask - when early depth / stencil resulted in a
```

## Source note 392, line 1104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1104)

```text
//       different value for the sample (like different stencil if the test
```

## Source note 393, line 1105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1105)

```text
//       failed), but can't write it before running the shader because it's
```

## Source note 394, line 1106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1106)

```text
//       not known if the sample will be discarded by the shader, alphatest or
```

## Source note 395, line 1107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1107)

```text
//       AtoC.
```

## Source note 396, line 1108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1108)

```text
// Early depth / stencil rejection of the pixel is possible when both 0:3 and
```

## Source note 397, line 1109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1109)

```text
// 4:7 are zero.
```

## Source note 398, line 1110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1110)

```text
// 8:11 - Whether color buffers have been written to, if not written on the
```

## Source note 399, line 1111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1111)

```text
//        taken execution path, don't export according to Direct3D 9 register
```

## Source note 400, line 1112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1112)

```text
//        documentation (some games rely on this behavior).
```

## Source note 401, line 1113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1113)

```text
// Bits 12:19 are only set with zpd_full_counters_ (occlusion queries):
```

## Source note 402, line 1114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1114)

```text
// 12:15 - Samples that passed stencil and failed depth.
```

## Source note 403, line 1115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1115)

```text
// 16:19 - Samples that failed stencil.
```

## Source note 404, line 1116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1116)

```text
// Y - Absolute resolution-scaled EDRAM offset for depth / stencil, in dwords,
```

## Source note 405, line 1117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1117)

```text
//     before and during depth testing. During color writing, when the depth /
```

## Source note 406, line 1118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1118)

```text
//     stencil address is not needed anymore, current color sample address.
```

## Source note 407, line 1119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1119)

```text
// Z - Base-relative resolution-scaled EDRAM offset for 32bpp color data, in
```

## Source note 408, line 1120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1120)

```text
//     dwords.
```

## Source note 409, line 1121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1121)

```text
// W - Base-relative resolution-scaled EDRAM offset for 64bpp color data, in
```

## Source note 410, line 1122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1122)

```text
//     dwords.
```

## Source note 411, line 1124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1124)

```text
// Different purposes:
```

## Source note 412, line 1125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1125)

```text
// - When writing to oDepth: X also used to hold the depth written by the
```

## Source note 413, line 1126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1126)

```text
//   shader, which, for host render targets, if the depth buffer is float24,
```

## Source note 414, line 1127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1127)

```text
//   needs to be remapped from guest 0...1 to host 0...0.5 and, if needed,
```

## Source note 415, line 1128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1128)

```text
//   converted to float24 precision; and for ROV, needs to be written in the
```

## Source note 416, line 1129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1129)

```text
//   end of the shader.
```

## Source note 417, line 1130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1130)

```text
// - When not writing to oDepth, but using ROV:
```

## Source note 418, line 1131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1131)

```text
//   - ROV_IsDepthStencilEarly: New per-sample depth / stencil values,
```

## Source note 419, line 1132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1132)

```text
//     generated during early depth / stencil test (actual writing checks
```

## Source note 420, line 1133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1133)

```text
//     the remaining coverage bits).
```

## Source note 421, line 1134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1134)

```text
//   - Not ROV_IsDepthStencilEarly: Z gradients in .xy taken in the beginning
```

## Source note 422, line 1135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1135)

```text
//     of the shader before any return statement is possibly reached.
```

## Source note 423, line 1137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1137)

```text
// Up to 4 color outputs in pixel shaders (needs to be readable, because of
```

## Source note 424, line 1138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1138)

```text
// alpha test, alpha to coverage, exponent bias, gamma, and also for ROV
```

## Source note 425, line 1139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1139)

```text
// writing).
```

## Source note 426, line 1142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1142)

```text
// Memory export temporary registers are allocated if the shader writes any
```

## Source note 427, line 1143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1143)

```text
// eM# (current_shader().memexport_eM_written() != 0).
```

## Source note 428, line 1144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1144)

```text
// X - whether memexport is enabled for this invocation.
```

## Source note 429, line 1145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1145)

```text
// Y - which eM# elements have been written so far by the invocation since the
```

## Source note 430, line 1146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1146)

```text
//     last memory write.
```

## Source note 431, line 1148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1148)

```text
// eA.
```

## Source note 432, line 1150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1150)

```text
// eM#.
```

## Source note 433, line 1153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1153)

```text
// Vector ALU or fetch result / scratch (since Xenos write masks can contain
```

## Source note 434, line 1154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1154)

```text
// swizzles).
```

## Source note 435, line 1156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1156)

```text
// Temporary register ID for previous scalar result, program counter,
```

## Source note 436, line 1157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1157)

```text
// predicate and absolute address register.
```

## Source note 437, line 1159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1159)

```text
// Loop index stack - .x is the active loop, shifted right to .yzw on push.
```

## Source note 438, line 1161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1161)

```text
// Loop counter stack, .x is the active loop. Represents number of times
```

## Source note 439, line 1162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1162)

```text
// remaining to loop.
```

## Source note 440, line 1164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1164)

```text
// Explicitly set texture gradients and LOD.
```

## Source note 441, line 1166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1166)

```text
// .w stores `base + index * stride` in bytes from the last vfetch_full as it
```

## Source note 442, line 1167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1167)

```text
// may be needed by vfetch_mini.
```

## Source note 443, line 1170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1170)

```text
// The bool constant number containing the condition for the currently
```

## Source note 444, line 1171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1171)

```text
// processed exec (or the last - unless a label has reset this), or
```

## Source note 445, line 1172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1172)

```text
// kCfExecBoolConstantNone if it's not checked.
```

## Source note 446, line 1175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1175)

```text
// The expected bool constant value in the current exec if
```

## Source note 447, line 1176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1176)

```text
// cf_exec_bool_constant_ is not kCfExecBoolConstantNone.
```

## Source note 448, line 1178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1178)

```text
// Whether the currently processed exec is executed if a predicate is
```

## Source note 449, line 1179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1179)

```text
// set/unset.
```

## Source note 450, line 1181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1181)

```text
// The expected predicated condition if cf_exec_predicated_ is true.
```

## Source note 451, line 1183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1183)

```text
// Whether an `if` for instruction-level predicate check is currently open.
```

## Source note 452, line 1185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1185)

```text
// The expected predicate condition for the current or the last instruction if
```

## Source note 453, line 1186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1186)

```text
// cf_exec_instruction_predicated_ is true.
```

## Source note 454, line 1188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1188)

```text
// Whether there was a `setp` in the current exec before the current
```

## Source note 455, line 1189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1189)

```text
// instruction, thus instruction-level predicate value can be different than
```

## Source note 456, line 1190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1190)

```text
// the exec-level predicate value, and can't merge two execs with the same
```

## Source note 457, line 1191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1191)

```text
// predicate condition anymore.
```

## Source note 458, line 1194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1194)

```text
// Number of SRV resources used in this shader - also used for generation of
```

## Source note 459, line 1195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1195)

```text
// indices of SRV resources that are optional.
```

## Source note 460, line 1202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1202)

```text
// The first binding is at t[SRVMainRegister::kBindfulTexturesStart] of space
```

## Source note 461, line 1203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1203)

```text
// SRVSpace::kMain.
```

## Source note 462, line 1207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1207)

```text
// Number of UAV resources used in this shader - also used for generation of
```

## Source note 463, line 1208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc_translator.h#L1208)

```text
// indices of UAV resources that are optional.
```
