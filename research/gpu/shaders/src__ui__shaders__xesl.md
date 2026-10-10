# Xesl: shaders source notes

This record preserves technical and API notes moved from `src/ui/shaders/xesl.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L13)

```text
// SHADING_LANGUAGE_GLSL/HLSL/MSL_XE 1 is expected to be defined via compiler
```

## Source note 2, line 14

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L14)

```text
// arguments.
```

## Source note 3, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L16)

```text
// Required GLSL extensions:
```

## Source note 4, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L17)

```text
// - GL_EXT_control_flow_attributes
```

## Source note 5, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L18)

```text
// - GL_EXT_samplerless_texture_functions
```

## Source note 6, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L20)

```text
// For functions, it's preferable to take the identifiers here from an existing
```

## Source note 7, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L21)

```text
// target language, such as GLSL or HLSL, add the `_xe` suffix, rename them from
```

## Source note 8, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L22)

```text
// camelCase to snake_case for consistency, and if altering (generalizing or
```

## Source note 9, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L23)

```text
// specializing usually) the functionality compared to that of the original
```

## Source note 10, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L24)

```text
// function, modify the name accordingly. The preferred name choice from all the
```

## Source note 11, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L25)

```text
// shading languages is the name that reflects the functionality the closest,
```

## Source note 12, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L26)

```text
// especially if some languages have a narrower input domain (for instance, HLSL
```

## Source note 13, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L27)

```text
// has `asuint` that can accept both `float` and `int`, while GLSL has
```

## Source note 14, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L28)

```text
// `floatBitsToUint` that accepts only `float` - there are two options here, a
```

## Source note 15, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L29)

```text
// `float_bits_to_uint_xe` alias, or `asuint_xe` overloads, but the former
```

## Source note 16, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L30)

```text
// describes the operation more precisely, so it's preferred; `lerp_xe` is
```

## Source note 17, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L31)

```text
// preferred over `mix_xe` because the former describes how exactly the mixing
```

## Source note 18, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L32)

```text
// will be performed), and / or that is the most visually consistent
```

## Source note 19, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L33)

```text
// (`float4_xe` over `vec4_xe` because it's a vector of `float`s).
```

## Source note 20, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L40)

```text
// Vectors.
```

## Source note 21, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L83)

```text
// Declarations.
```

## Source note 22, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L85)

```text
// Resource binding is very different between shading languages, so any
```

## Source note 23, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L86)

```text
// customizations are fine in it. All binding slots for all APIs, however,
```

## Source note 24, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L87)

```text
// should be explicitly specified by the shader for ease of manual lookup and
```

## Source note 25, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L88)

```text
// tweaking. They should be alphabetically ordered by the name of the target
```

## Source note 26, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L89)

```text
// shading language in the argument lists (GLSL before HLSL). For readability,
```

## Source note 27, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L90)

```text
// the `set=` and `binding=` specifiers, and register types and the `space`
```

## Source note 28, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L91)

```text
// prefix in HLSL, are exposed to the shader, even though they're redundant.
```

## Source note 29, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L93)

```text
// The `_xe_*` suffix (with context-specific suffixes, like `_xe_block`) can be
```

## Source note 30, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L94)

```text
// used to create internal derivative identifiers (such as buffer block names
```

## Source note 31, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L95)

```text
// from instance names, or separate texture and sampler from a combined
```

## Source note 32, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L96)

```text
// texture / sampler for languages not supporting the latter).
```

## Source note 33, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L98)

```text
// Non-compute shader entry point must be declared as:
```

## Source note 34, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L100)

```text
//   - Linked stage outputs.
```

## Source note 35, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L101)

```text
//   - Linked system stage outputs (like vertex position).
```

## Source note 36, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L102)

```text
//   - System stage outputs.
```

## Source note 37, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L104)

```text
//   - Linked stage inputs (vertex attributes, interpolants).
```

## Source note 38, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L105)

```text
// entry_stage_inputs_end_bindings_begin_[stage]_xe (vertex, pixel)
```

## Source note 39, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L106)

```text
//   Everything here must be separated with entry_binding_next_xe, with no
```

## Source note 40, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L107)

```text
//   leading or trailing separators.
```

## Source note 41, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L108)

```text
//   - Buffer, texture, sampler bindings.
```

## Source note 42, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L110)

```text
// (or entry_bindings_empty_end_inputs_begin_xe if there are no bindings).
```

## Source note 43, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L111)

```text
//   Everything here must be separated with entry_input_next_xe, with no leading
```

## Source note 44, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L112)

```text
//   or trailing separators.
```

## Source note 45, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L113)

```text
//   - entry_in_stage_inputs_xe if any linked stage inputs are used.
```

## Source note 46, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L114)

```text
//   - Linked system inputs (like pixel position).
```

## Source note 47, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L115)

```text
//   - System inputs.
```

## Source note 48, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L117)

```text
//   - Main function code.
```

## Source note 49, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L120)

```text
// Compute shader entry point must be declared as:
```

## Source note 50, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L121)

```text
// #define LOCAL_SIZE_X_XE ...
```

## Source note 51, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L122)

```text
// #define LOCAL_SIZE_Y_XE ...
```

## Source note 52, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L123)

```text
// #define LOCAL_SIZE_Z_XE ...
```

## Source note 53, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L125)

```text
//   Everything here must be separated with entry_binding_next_xe, with no
```

## Source note 54, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L126)

```text
//   leading or trailing separators.
```

## Source note 55, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L127)

```text
//   - Buffer, texture, sampler bindings.
```

## Source note 56, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L129)

```text
//   Everything here must be separated with entry_input_next_xe, with no leading
```

## Source note 57, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L130)

```text
//   or trailing separators.
```

## Source note 58, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L131)

```text
//   - System inputs.
```

## Source note 59, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L133)

```text
//   - Main function code.
```

## Source note 60, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L136)

```text
// Bindings are in the entry point because they are passed this way in MSL. For
```

## Source note 61, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L137)

```text
// this reason, constant and storage buffer declarations are also split into the
```

## Source note 62, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L138)

```text
// declaration itself and the binding (because blocks can't be passed as
```

## Source note 63, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L139)

```text
// function arguments in GLSL, for instance, so they must be fully declared
```

## Source note 64, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L140)

```text
// before functions referencing them in headers, for example - but in MSL, their
```

## Source note 65, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L141)

```text
// structure has to be forward-declared for this purpose, and the reference to
```

## Source note 66, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L142)

```text
// the binding should be passed to the function).
```

## Source note 67, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L144)

```text
// Note that for the stage inputs / outputs, the order must be the same as in
```

## Source note 68, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L145)

```text
// HLSL linkage. For this reason, the position and the fragment coordinate also
```

## Source note 69, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L146)

```text
// must be after the stage inputs structure in the input list.
```

## Source note 70, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L148)

```text
// Both input / output and binding names may be placed in the global scope in
```

## Source note 71, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L149)

```text
// the target language, make sure they don't collide with anything there.
```

## Source note 72, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L151)

```text
// In compute shaders, the total group size must not exceed 128 threads (unless
```

## Source note 73, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L152)

```text
// the shader is used with the appropriate conditionals), as that's the minimum
```

## Source note 74, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L153)

```text
// maxComputeWorkGroupInvocations requirement on Vulkan. 128 threads exactly is
```

## Source note 75, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L154)

```text
// the recommended group size overall, especially for shaders not using the
```

## Source note 76, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L155)

```text
// group functionality, as it's the maximum wave size supported by DXIL and
```

## Source note 77, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L156)

```text
// SPIR-V wave operations, and there are PowerVR GPUs with 128-lane waves, so
```

## Source note 78, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L157)

```text
// it provides balance between wave utilization and excess thread (and, on GPUs
```

## Source note 79, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L158)

```text
// with smaller waves, wave) count if the size of the actual work domain is not
```

## Source note 80, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L159)

```text
// aligned to the group size.
```

## Source note 81, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L161)

```text
// System outputs and inputs (declared via the respective entry_out_*_xe and
```

## Source note 82, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L162)

```text
// entry_in_*_xe):
```

## Source note 83, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L163)

```text
// - Vertex shaders:
```

## Source note 84, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L164)

```text
//   - out float4_xe out_position_xe
```

## Source note 85, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L165)

```text
//   - in uint in_vertex_id_xe
```

## Source note 86, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L166)

```text
// - Pixel shaders:
```

## Source note 87, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L167)

```text
//   - in float4_xe in_pixel_coord_xe
```

## Source note 88, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L168)

```text
//     in_pixel_coord_xe.w is 1/W if PIXEL_COORD_W_IS_INVERSE_XE, W otherwise.
```

## Source note 89, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L169)

```text
// - Compute shaders:
```

## Source note 90, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L170)

```text
//   - in uint3_xe in_group_id_xe
```

## Source note 91, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L171)

```text
//   - in uint3_xe in_local_thread_id_xe
```

## Source note 92, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L172)

```text
//   - in uint3_xe in_global_thread_id_xe
```

## Source note 93, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L173)

```text
//   - in uint in_local_thread_index_xe
```

## Source note 94, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L281)

```text
// SHADING_LANGUAGE_*_XE
```

## Source note 95, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L284)

```text
// !entry_outputs_begin_xe
```

## Source note 96, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L287)

```text
// !entry_out_position_xe
```

## Source note 97, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L290)

```text
// !entry_outputs_end_stage_inputs_begin_xe
```

## Source note 98, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L294)

```text
// !entry_in_stage_vertex_xe
```

## Source note 99, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L297)

```text
// !entry_stage_inputs_end_bindings_begin_vertex_xe
```

## Source note 100, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L300)

```text
// !entry_stage_inputs_end_bindings_begin_pixel_xe
```

## Source note 101, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L303)

```text
// !entry_bindings_begin_compute_xe
```

## Source note 102, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L306)

```text
// !entry_binding_next_xe
```

## Source note 103, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L309)

```text
// !entry_bindings_end_inputs_begin_xe
```

## Source note 104, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L312)

```text
// !entry_bindings_empty_end_inputs_begin_xe
```

## Source note 105, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L315)

```text
// !entry_bindings_end_inputs_begin_compute_xe
```

## Source note 106, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L318)

```text
// !entry_input_next_xe
```

## Source note 107, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L321)

```text
// !entry_in_stage_inputs_xe
```

## Source note 108, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L324)

```text
// !entry_in_vertex_id_xe
```

## Source note 109, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L327)

```text
// !entry_in_pixel_coord_xe
```

## Source note 110, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L330)

```text
// !entry_in_group_id_xe
```

## Source note 111, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L333)

```text
// !entry_in_local_thread_id_xe
```

## Source note 112, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L336)

```text
// !entry_in_global_thread_id_xe
```

## Source note 113, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L339)

```text
// !entry_in_local_thread_index_xe
```

## Source note 114, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L344)

```text
// !entry_code_end_xe
```

## Source note 115, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L347)

```text
// !entry_code_end_compute_xe
```

## Source note 116, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L349)

```text
// NDC_DIRECTION_Y_XE, assuming a positive viewport height, is:
```

## Source note 117, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L350)

```text
// *  1.0 if +out_position_xe.y is towards +in_pixel_coord_xe.y,
```

## Source note 118, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L351)

```text
// * -1.0 if +out_position_xe.y is towards -in_pixel_coord_xe.y.
```

## Source note 119, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L359)

```text
// GLSL requires just const for declaring a constant in the global scope.
```

## Source note 120, line 362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L362)

```text
// HLSL requires static const for declaring a constant in the global scope so
```

## Source note 121, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L363)

```text
// it doesn't go to $Globals instead.
```

## Source note 122, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L369)

```text
// SHADING_LANGUAGE_*_XE
```

## Source note 123, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L380)

```text
// Explicit offset is not supported by MSL.
```

## Source note 124, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L386)

```text
// SHADING_LANGUAGE_*_XE
```

## Source note 125, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L388)

```text
// Structures of constant and structured buffer bindings must be declared before
```

## Source note 126, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L389)

```text
// the entry point declaration.
```

## Source note 127, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L391)

```text
// Constant buffers and push constants must be manually packed as std140 (which
```

## Source note 128, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L392)

```text
// is stricter than HLSL packing) due to the GLSL requirement. This means that
```

## Source note 129, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L393)

```text
// 32x4 and 32x3 vectors must start at 16-byte alignment, 32x2 at 8-byte, and a
```

## Source note 130, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L394)

```text
// single 32-bit value can be placed immediately after a 32x3 vector (the Vulkan
```

## Source note 131, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L395)

```text
// definition of this behavior). Specifically, all alignment padding must be
```

## Source note 132, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L396)

```text
// inserted explicitly (or block_offset_member_xe must be used), as by default
```

## Source note 133, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L397)

```text
// HLSL doesn't have the alignment requirement, only the rule that elements
```

## Source note 134, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L398)

```text
// (array elements, or single non-array members) must not cross 32x4 vector
```

## Source note 135, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L399)

```text
// boundaries, so something like float|float3 or float|float2|float will be
```

## Source note 136, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L400)

```text
// packed differently in GLSL (float|pad3|float3 or float|pad|float2|float) and
```

## Source note 137, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L401)

```text
// HLSL (float|float3 or float|float2|float).
```

## Source note 138, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L403)

```text
// Constant buffer and push constant member names will be in the global scope in
```

## Source note 139, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L404)

```text
// some target languages - they must not collide with anything else there. To
```

## Source note 140, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L405)

```text
// access a constant, use constant_xe or push_const_xe.
```

## Source note 141, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L407)

```text
// Push constants, even though may be spread across multiple constant buffers in
```

## Source note 142, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L408)

```text
// the Direct3D 12 API, must be declared in a single structure in XeSL - the
```

## Source note 143, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L409)

```text
// reason is that layout qualifiers in GLSL can't be used in regular structures,
```

## Source note 144, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L410)

```text
// only in blocks, and sub-blocks can't be declared in a block, so there's no
```

## Source note 145, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L411)

```text
// way to create separate identifiers for push constant ranges in GLSL. Though
```

## Source note 146, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L412)

```text
// both GLSL and HLSL support anonymous push constants / cbuffers, MSL requires
```

## Source note 147, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L413)

```text
// a name for the buffer binding.
```

## Source note 148, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L414)

```text
// In GLSL, the offsets in the push constants are global across shader stages.
```

## Source note 149, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L415)

```text
// In HLSL, they're local to the specific root constant buffer.
```

## Source note 150, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L461)

```text
// SHADING_LANGUAGE_*_XE
```

## Source note 151, line 464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L464)

```text
// !const_buffer_binding_xe
```

## Source note 152, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L467)

```text
// !push_const_binding_xe
```

## Source note 153, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L469)

```text
// Declarations of typed storage buffers and dword buffers (_declare) must be
```

## Source note 154, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L470)

```text
// outside the entry point, but their bindings (_binding) must also be specified
```

## Source note 155, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L471)

```text
// in the entry point binding declarations.
```

## Source note 156, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L473)

```text
// An array buffer is a buffer limited to 1/2/4-component vectors of 32-bit
```

## Source note 157, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L474)

```text
// integers and floats, a typed buffer on Direct3D, but a storage buffer (as
```

## Source note 158, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L475)

```text
// opposed to a texel buffer, which has a very small minimum requirement for the
```

## Source note 159, line 476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L476)

```text
// maximum size) on Vulkan.
```

## Source note 160, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L478)

```text
// A UInt vector buffer is a buffer containing 32-bit values, but loading or
```

## Source note 161, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L479)

```text
// storing may be done for 2, 3 or 4 consecutive values that are still
```

## Source note 162, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L480)

```text
// 32-bit-aligned, and depending on the language and hardware support, access
```

## Source note 163, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L481)

```text
// of multiple elements may or may not be compiled into a single hardware
```

## Source note 164, line 482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L482)

```text
// instruction instead of separate accesses of individual elements. Each index
```

## Source note 165, line 483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L483)

```text
// value corresponds to a 32-bit element. Implementations for languages without
```

## Source note 166, line 484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L484)

```text
// native support must use functions, not macros, for adding the component
```

## Source note 167, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L485)

```text
// offset to the index to avoid evaluating the address multiple times.
```

## Source note 168, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L487)

```text
// Binding declarations.
```

## Source note 169, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L517)

```text
// Loading and storing.
```

## Source note 170, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L530)

```text
// Binding declarations.
```

## Source note 171, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L540)

```text
// Loading and storing.
```

## Source note 172, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L553)

```text
// Binding declarations.
```

## Source note 173, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L560)

```text
// Loading and storing.
```

## Source note 174, line 576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L576)

```text
// SHADING_LANGUAGE_*_XE
```

## Source note 175, line 580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L580)

```text
// !array_buffer_declare_xe
```

## Source note 176, line 584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L584)

```text
// !array_buffer_wo_declare_xe
```

## Source note 177, line 587

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L587)

```text
// !array_buffer_binding_xe
```

## Source note 178, line 590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L590)

```text
// !array_buffer_wo_binding_xe
```

## Source note 179, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L594)

```text
// !uint_vector_buffer_declare_xe
```

## Source note 180, line 597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L597)

```text
// !uint_vector_buffer_binding_xe
```

## Source note 181, line 599

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L599)

```text
// Buffer, texture, sampler and image bindings must be in the entry point
```

## Source note 182, line 600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L600)

```text
// bindings declaration.
```

## Source note 183, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L601)

```text
// - texture_xe is a separate texture.
```

## Source note 184, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L602)

```text
// - sampler_state_xe a separate sampler.
```

## Source note 185, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L603)

```text
// - sampler_xe is a combined texture / sampler where available, internally
```

## Source note 186, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L604)

```text
//   separate where not.
```

## Source note 187, line 607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L607)

```text
// Types.
```

## Source note 188, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L616)

```text
// Binding declarations.
```

## Source note 189, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L630)

```text
// Fetching and storing.
```

## Source note 190, line 660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L660)

```text
// Types.
```

## Source note 191, line 668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L668)

```text
// Binding declarations.
```

## Source note 192, line 678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L678)

```text
// Fetching and storing.
```

## Source note 193, line 698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L698)

```text
// Types.
```

## Source note 194, line 706

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L706)

```text
// Binding declarations.
```

## Source note 195, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L716)

```text
// Fetching and storing.
```

## Source note 196, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L737)

```text
// SHADING_LANGUAGE_*_XE
```

## Source note 197, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L738)

```text
// If there's no language specialization doing this already, implement combined
```

## Source note 198, line 739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L739)

```text
// textures / samplers as separate, with the `_xe_sampler` suffix for samplers.
```

## Source note 199, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L740)

```text
// The sampler types become the texture types.
```

## Source note 200, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L744)

```text
// !sampler_2d_xe
```

## Source note 201, line 754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L754)

```text
// !sampler_xe
```

## Source note 202, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L759)

```text
// !sample_comb_lod_2d_xe
```

## Source note 203, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L764)

```text
// !gather_comb_2d_r_xe
```

## Source note 204, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L769)

```text
// !gather_comb_2d_g_xe
```

## Source note 205, line 774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L774)

```text
// !gather_comb_2d_b_xe
```

## Source note 206, line 779

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L779)

```text
// !gather_comb_2d_a_xe
```

## Source note 207, line 780

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L780)

```text
// !COMBINED_TEXTURE_SAMPLER_XE
```

## Source note 208, line 782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L782)

```text
// Passing bindings to functions, and also output and input / output parameters.
```

## Source note 209, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L793)

```text
// Prototype parameters.
```

## Source note 210, line 800

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L800)

```text
// Call arguments.
```

## Source note 211, line 807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L807)

```text
// SHADING_LANGUAGE_*_XE
```

## Source note 212, line 809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L809)

```text
// Prototype parameters.
```

## Source note 213, line 812

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L812)

```text
// !param_const_buffer_xe
```

## Source note 214, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L815)

```text
// !param_next_after_const_buffer_xe
```

## Source note 215, line 818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L818)

```text
// !param_push_consts_xe
```

## Source note 216, line 821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L821)

```text
// !param_next_after_push_consts_xe
```

## Source note 217, line 824

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L824)

```text
// !param_uint_vector_buffer_xe
```

## Source note 218, line 827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L827)

```text
// !param_next_after_uint_vector_buffer_xe
```

## Source note 219, line 828

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L828)

```text
// Call arguments.
```

## Source note 220, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L831)

```text
// !pass_const_buffer_xe
```

## Source note 221, line 834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L834)

```text
// !pass_next_after_const_buffer_xe
```

## Source note 222, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L837)

```text
// !pass_push_consts_xe
```

## Source note 223, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L840)

```text
// !pass_next_after_push_consts_xe
```

## Source note 224, line 843

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L843)

```text
// !pass_uint_vector_buffer_xe
```

## Source note 225, line 846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L846)

```text
// !pass_next_after_uint_vector_buffer_xe
```

## Source note 226, line 848

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L848)

```text
// Attributes.
```

## Source note 227, line 860

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L860)

```text
// SHADING_LANGUAGE_*_XE
```

## Source note 228, line 863

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L863)

```text
// !unroll_xe
```

## Source note 229, line 866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L866)

```text
// !dont_unroll
```

## Source note 230, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L869)

```text
// !flatten_xe
```

## Source note 231, line 872

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L872)

```text
// !dont_flatten_xe
```

## Source note 232, line 874

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L874)

```text
// Function aliases.
```

## Source note 233, line 905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L905)

```text
// SHADING_LANGUAGE_*_XE
```

## Source note 234, line 913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L913)

```text
// Using functions instead of #define for implicit argument conversion.
```

## Source note 235, line 931

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L931)

```text
// Using functions instead of #define for implicit argument conversion.
```

## Source note 236, line 982

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L982)

```text
// SHADING_LANGUAGE_*_XE
```

## Source note 237, line 1001

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L1001)

```text
// Returning a unsigned integer vector. The result is undefined for zero.
```

## Source note 238, line 1027

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L1027)

```text
// GLSL findMSB finds the highest 0 for a negative value.
```

## Source note 239, line 1077

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L1077)

```text
// HLSL firstbithigh finds the highest 0 for a negative value.
```

## Source note 240, line 1153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L1153)

```text
// SHADING_LANGUAGE_*_XE
```

## Source note 241, line 1176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/ui/shaders/xesl.xesli#L1176)

```text
// SHADING_LANGUAGE_*_XE
```
