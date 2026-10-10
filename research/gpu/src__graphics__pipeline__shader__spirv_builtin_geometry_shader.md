# Spirv builtin geometry shader: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L43)

```text
// Point to a strip of 2 triangles.
```

## Source note 2, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L50)

```text
// Triangle to a strip of 2 triangles.
```

## Source note 3, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L57)

```text
// 4 vertices passed via a line list with adjacency to a strip of 2
```

## Source note 4, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L58)

```text
// triangles.
```

## Source note 5, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L65)

```text
// Line (of a list or a strip) to a strip of 2 triangles.
```

## Source note 6, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L97)

```text
// Match the vertex and pixel shaders' float controls. NaN preservation most
```

## Source note 7, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L98)

```text
// importantly keeps the NaN-position primitive discard below (used for the
```

## Source note 8, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L99)

```text
// vertex kill "or" operator and degenerate rectangles) from being folded
```

## Source note 9, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L100)

```text
// away. The execution modes are added once the entry point exists.
```

## Source note 10, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L134)

```text
// System constants.
```

## Source note 11, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L135)

```text
// For points (lines only need point_screen_diameter_to_ndc_radius, as the
```

## Source note 12, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L136)

```text
// NDC size of a guest pixel):
```

## Source note 13, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L137)

```text
// - float2 point_constant_diameter
```

## Source note 14, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L138)

```text
// - float2 point_screen_diameter_to_ndc_radius
```

## Source note 15, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L173)

```text
// SPIR-V 1.4+ lists every global the entry point references in its
```

## Source note 16, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L174)

```text
// interface, not just inputs and outputs.
```

## Source note 17, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L180)

```text
// Inputs and outputs - matching glslang order, in gl_PerVertex gl_in[],
```

## Source note 18, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L181)

```text
// user-defined outputs, user-defined inputs, out gl_PerVertex.
```

## Source note 19, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L186)

```text
// in gl_PerVertex gl_in[].
```

## Source note 20, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L187)

```text
// gl_Position.
```

## Source note 21, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L193)

```text
// gl_ClipDistance.
```

## Source note 22, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L202)

```text
// gl_CullDistance.
```

## Source note 23, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L208)

```text
// Structure and array.
```

## Source note 24, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L237)

```text
// Interpolators outputs.
```

## Source note 25, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L250)

```text
// Point coordinate output.
```

## Source note 26, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L263)

```text
// Interpolator inputs.
```

## Source note 27, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L276)

```text
// Point size input.
```

## Source note 28, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L288)

```text
// out gl_PerVertex.
```

## Source note 29, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L289)

```text
// gl_Position.
```

## Source note 30, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L295)

```text
// gl_ClipDistance.
```

## Source note 31, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L304)

```text
// Structure.
```

## Source note 32, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L323)

```text
// Begin the main function.
```

## Source note 33, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L349)

```text
// Note that after every OpEmitVertex, all output variables are undefined.
```

## Source note 34, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L351)

```text
// Discard the whole primitive if any vertex has a NaN position (may also be
```

## Source note 35, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L352)

```text
// set to NaN for emulation of vertex killing with the OR operator).
```

## Source note 36, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L385)

```text
// Cull the whole primitive if any cull distance for all vertices in the
```

## Source note 37, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L386)

```text
// primitive is < 0.
```

## Source note 38, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L437)

```text
// Expand the point sprite, with left-to-right, top-to-bottom UVs.
```

## Source note 39, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L443)

```text
// Load the point diameter in guest pixels.
```

## Source note 40, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L457)

```text
// The vertex shader's header writes -1.0 to point_size by default, so
```

## Source note 41, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L458)

```text
// any non-negative value means that it was overwritten by the
```

## Source note 42, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L459)

```text
// translated vertex shader, and needs to be used instead of the
```

## Source note 43, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L460)

```text
// constant size. The per-vertex diameter is already clamped in the
```

## Source note 44, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L461)

```text
// vertex shader (combined with making it non-negative).
```

## Source note 45, line 463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L463)

```text
// 0 is the input primitive vertex index.
```

## Source note 46, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L478)

```text
// 4D5307F1 has zero-size snowflakes, drop them quicker, and also drop
```

## Source note 47, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L479)

```text
// points with a constant size of zero since point lists may also be used
```

## Source note 48, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L480)

```text
// as just "compute" with memexport.
```

## Source note 49, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L508)

```text
// Transform the diameter in the guest screen coordinates to radius in the
```

## Source note 50, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L509)

```text
// normalized device coordinates, and then to the clip space by
```

## Source note 51, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L510)

```text
// multiplying by W.
```

## Source note 52, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L527)

```text
// 0 is the input primitive vertex index.
```

## Source note 53, line 539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L539)

```text
// Load the inputs for the guest point.
```

## Source note 54, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L540)

```text
// Interpolators.
```

## Source note 55, line 543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L543)

```text
// 0 is the input primitive vertex index.
```

## Source note 56, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L550)

```text
// Positions.
```

## Source note 57, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L562)

```text
// Clip distances.
```

## Source note 58, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L566)

```text
// 0 is the input primitive vertex index.
```

## Source note 59, line 575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L575)

```text
// Same interpolators for the entire sprite.
```

## Source note 60, line 579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L579)

```text
// Top-left, bottom-left, top-right, bottom-right order (chosen
```

## Source note 61, line 580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L580)

```text
// arbitrarily, simply based on counterclockwise meaning front with
```

## Source note 62, line 581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L581)

```text
// frontFace = VkFrontFace(0), but faceness is ignored for non-polygon
```

## Source note 63, line 582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L582)

```text
// primitive types).
```

## Source note 64, line 585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L585)

```text
// Point coordinates.
```

## Source note 65, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L593)

```text
// Position.
```

## Source note 66, line 606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L606)

```text
// Clip distances.
```

## Source note 67, line 615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L615)

```text
// Emit the vertex.
```

## Source note 68, line 622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L622)

```text
// Construct a strip with the fourth vertex generated by mirroring a
```

## Source note 69, line 623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L623)

```text
// vertex across the longest edge (the diagonal).
```

## Source note 70, line 625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L625)

```text
// Possible options:
```

## Source note 71, line 627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L627)

```text
// 0---1
```

## Source note 72, line 629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L629)

```text
// | / |  - 12 is the longest edge, strip 0123 (most commonly used)
```

## Source note 73, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L630)

```text
// |/  |    v3 = v0 + (v1 - v0) + (v2 - v0), or v3 = -v0 + v1 + v2
```

## Source note 74, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L631)

```text
// 2--[3]
```

## Source note 75, line 633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L633)

```text
// 1---2
```

## Source note 76, line 635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L635)

```text
// | / |  - 20 is the longest edge, strip 1203
```

## Source note 77, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L637)

```text
// 0--[3]
```

## Source note 78, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L639)

```text
// 2---0
```

## Source note 79, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L641)

```text
// | / |  - 01 is the longest edge, strip 2013
```

## Source note 80, line 643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L643)

```text
// 1--[3]
```

## Source note 81, line 650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L650)

```text
// Get squares of edge lengths to choose the longest edge.
```

## Source note 82, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L651)

```text
// [0] - 12, [1] - 20, [2] - 01.
```

## Source note 83, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L681)

```text
// Choose the index of the first vertex in the strip based on which edge
```

## Source note 84, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L682)

```text
// is the longest, and calculate the indices of the other vertices.
```

## Source note 85, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L684)

```text
// If 12 > 20 && 12 > 01, then 12 is the longest edge, and the strip is
```

## Source note 86, line 685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L685)

```text
// 0123. Otherwise, if 20 > 01, then 20 is the longest, and the strip is
```

## Source note 87, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L686)

```text
// 1203, but if not, 01 is the longest, and the strip is 2013.
```

## Source note 88, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L700)

```text
// vertex_indices[i] = (vertex_indices[0] + i) % 3
```

## Source note 89, line 711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L711)

```text
// Initialize the point coordinates output for safety if this shader type
```

## Source note 90, line 712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L712)

```text
// is used with has_point_coordinates for some reason.
```

## Source note 91, line 722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L722)

```text
// Emit the triangle in the strip that consists of the original vertices.
```

## Source note 92, line 725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L725)

```text
// Interpolators.
```

## Source note 93, line 735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L735)

```text
// Point coordinates.
```

## Source note 94, line 739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L739)

```text
// Position.
```

## Source note 95, line 751

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L751)

```text
// Clip distances.
```

## Source note 96, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L765)

```text
// Emit the vertex.
```

## Source note 97, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L769)

```text
// Construct the fourth vertex.
```

## Source note 98, line 770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L770)

```text
// Interpolators.
```

## Source note 99, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L793)

```text
// Point coordinates.
```

## Source note 100, line 797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L797)

```text
// Position.
```

## Source note 101, line 822

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L822)

```text
// Clip distances.
```

## Source note 102, line 852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L852)

```text
// Emit the vertex.
```

## Source note 103, line 858

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L858)

```text
// Initialize the point coordinates output for safety if this shader type
```

## Source note 104, line 859

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L859)

```text
// is used with has_point_coordinates for some reason.
```

## Source note 105, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L869)

```text
// Build the triangle strip from the original quad vertices in the
```

## Source note 106, line 870

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L870)

```text
// 0, 1, 3, 2 order (like specified for GL_QUAD_STRIP).
```

## Source note 107, line 874

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L874)

```text
// Interpolators.
```

## Source note 108, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L884)

```text
// Point coordinates.
```

## Source note 109, line 888

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L888)

```text
// Position.
```

## Source note 110, line 900

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L900)

```text
// Clip distances.
```

## Source note 111, line 914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L914)

```text
// Emit the vertex.
```

## Source note 112, line 921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L921)

```text
// Host lines are rasterized 1 host pixel wide, but a guest line covers 1
```

## Source note 113, line 922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L922)

```text
// guest pixel, which is draw_resolution_scale host pixels. Expand the
```

## Source note 114, line 923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L923)

```text
// segment into a quad 1 guest pixel wide centered on the line, each end
```

## Source note 115, line 924

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L924)

```text
// keeping its own attributes.
```

## Source note 116, line 931

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L931)

```text
// Half of a guest pixel in the NDC along each axis - the constant is the
```

## Source note 117, line 932

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L932)

```text
// NDC radius of a 1 guest pixel diameter.
```

## Source note 118, line 947

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L947)

```text
// Load the positions, and get the vertices in half guest pixel units
```

## Source note 119, line 948

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L948)

```text
// (NDC divided by the NDC size of half a guest pixel) so the direction
```

## Source note 120, line 949

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L949)

```text
// is measured in screen space regardless of the viewport aspect.
```

## Source note 121, line 975

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L975)

```text
// Direction of the line in screen space.
```

## Source note 122, line 987

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L987)

```text
// Drop zero-length lines (also NaN-safe), there's nothing to expand and
```

## Source note 123, line 988

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L988)

```text
// the normal would be undefined.
```

## Source note 124, line 1012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1012)

```text
// Unit normal in screen space, then half a guest pixel along it in the
```

## Source note 125, line 1013

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1013)

```text
// NDC (back to the per-axis NDC size of half a guest pixel).
```

## Source note 126, line 1027

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1027)

```text
// Initialize the point coordinates output for safety if this shader type
```

## Source note 127, line 1028

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1028)

```text
// is used with has_point_coordinates for some reason.
```

## Source note 128, line 1037

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1037)

```text
// Emit the strip: both sides of the first vertex, then of the second.
```

## Source note 129, line 1042

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1042)

```text
// Interpolators.
```

## Source note 130, line 1052

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1052)

```text
// Point coordinates.
```

## Source note 131, line 1056

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1056)

```text
// Position - the NDC offset is transformed to the clip space by
```

## Source note 132, line 1057

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1057)

```text
// multiplying by W.
```

## Source note 133, line 1075

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1075)

```text
// Clip distances.
```

## Source note 134, line 1089

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1089)

```text
// Emit the vertex.
```

## Source note 135, line 1099

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1099)

```text
// End the main function.
```

## Source note 136, line 1102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L1102)

```text
// Serialize the shader code.
```
