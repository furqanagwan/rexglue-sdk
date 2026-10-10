# Spirv to dxil compiler: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L22)

```text
// Wraps Mesa's spirv_to_dxil (NIR-based SPIR-V to DXIL) for the guest shader
```

## Source note 2, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L23)

```text
// paths that consume DXIL. Produces DXIL from the SPIR-V emitted by
```

## Source note 3, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L24)

```text
// SpirvShaderTranslator, for D3D12 directly and for Metal by way of Apple's
```

## Source note 4, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L25)

```text
// Metal Shader Converter.
```

## Source note 5, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L27)

```text
// Supports both render target cache paths. The Mesa fork lowers SPIR-V fragment
```

## Source note 6, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L28)

```text
// shader interlock to D3D12 rasterizer-ordered views, so the EDRAM ROV path
```

## Source note 7, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L29)

```text
// goes through this route as well (the EDRAM and ZPD counter UAVs become ROVs).
```

## Source note 8, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L32)

```text
// Mesa git revision of the linked library.
```

## Source note 9, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L35)

```text
// True if the DXIL signer this platform needs is available. On Windows that
```

## Source note 10, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L36)

```text
// is DXIL.dll's validator, without which every translation fails.
```

## Source note 11, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L39)

```text
// Register and space of the CBV Mesa lowers SPIR-V push constants to, which
```

## Source note 12, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L40)

```text
// a root signature must supply as root constants or a CBV. Mesa sizes that
```

## Source note 13, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L41)

```text
// CBV from the bytes the shader actually loads, rounded up to a 16-byte row.
```

## Source note 14, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L42)

```text
// Dozen's runtime data shares the space at register 0.
```

## Source note 15, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L46)

```text
// Pipeline stage of the SPIR-V module. Covers the guest vertex/pixel shaders,
```

## Source note 16, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L47)

```text
// the host primitive-expansion geometry and tessellation shaders, and the
```

## Source note 17, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L48)

```text
// render target cache's internal compute shaders.
```

## Source note 18, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L58)

```text
// Translates one SPIR-V module to signed DXIL for the given stage. When
```

## Source note 19, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L59)

```text
// lower_to_bindless is set, all descriptor-set resources are lowered to
```

## Source note 20, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L60)

```text
// SM 6.6 dynamic resource heap indexing (matching the Dozen driver), for the
```

## Source note 21, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L61)

```text
// fully bindless guest path. input_clip_size is the producer's clip distance
```

## Source note 22, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L62)

```text
// count, needed by stages that read clip inputs (geometry, tessellation) so
```

## Source note 23, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L63)

```text
// the clip / cull split matches the producer. Returns an empty vector on
```

## Source note 24, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L64)

```text
// failure and logs the cause.
```

## Source note 25, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L69)

```text
// One SPIR-V stage for TranslateLinked.
```

## Source note 26, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L76)

```text
// Translates several SPIR-V stages of one pipeline together with cross-stage
```

## Source note 27, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L77)

```text
// linking, so the inter-stage signatures match exactly as D3D12 requires (the
```

## Source note 28, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L78)

```text
// way tessellation hull and domain shaders reconcile control point counts and
```

## Source note 29, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L79)

```text
// patch constants). Stages must be in pipeline order (vertex first). Returns
```

## Source note 30, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h#L80)

```text
// one signed DXIL blob per input stage, or an empty vector on failure.
```
