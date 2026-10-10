# Spirv builtin geometry shader: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h#L21)

```text
// Built-in geometry shader variants for guest primitive types that need host
```

## Source note 2, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h#L22)

```text
// expansion (the Xbox 360 has no geometry shaders). The values match the
```

## Source note 3, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h#L23)

```text
// per-backend PipelineGeometryShader enums so a backend key can be cast in.
```

## Source note 4, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h#L29)

```text
// Line list or strip expanded to quads 1 guest pixel wide, for
```

## Source note 5, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h#L30)

```text
// resolution-scaled draws (host lines are always 1 host pixel wide).
```

## Source note 6, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h#L34)

```text
// Builds the SPIR-V for a built-in primitive-expansion geometry shader, shared
```

## Source note 7, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h#L35)

```text
// by the Vulkan backend (used directly) and the D3D12 backend (fed through
```

## Source note 8, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h#L36)

```text
// spirv_to_dxil). The shader reads the SpirvShaderTranslator vertex output
```

## Source note 9, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h#L37)

```text
// signature and SystemConstants layout, so it pairs with that translator's
```

## Source note 10, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h#L38)

```text
// vertex and pixel shaders on either backend. Returns the SPIR-V words.
```
