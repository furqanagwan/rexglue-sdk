# Spirv fsi system constants: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L24)

```text
// Fills the fragment shader interlock (EDRAM ROP) subset of the SPIR-V system
```

## Source note 2, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L25)

```text
// constants from the register file: the FSI-specific flag bits, the EDRAM tile
```

## Source note 3, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L26)

```text
// pitch / render target / depth base / stencil / blend / polygon offset
```

## Source note 4, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L27)

```text
// constants and the ZPD counter index. Shared by the Vulkan and the D3D12
```

## Source note 5, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L28)

```text
// (Mesa spirv_to_dxil) command processors so the single EDRAM ROP encoding is
```

## Source note 6, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L29)

```text
// not duplicated. Only call when the render target cache is in its pixel shader
```

## Source note 7, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L30)

```text
// interlock path.
```

## Source note 8, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L32)

```text
// flags is the in-progress system constant flags word. The FSI flag bits are
```

## Source note 9, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L33)

```text
// OR'd into it (the caller owns the base bits and the final assignment). dirty
```

## Source note 10, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L34)

```text
// is OR'd with true when any written constant changed, for the Vulkan caller's
```

## Source note 11, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L35)

```text
// constant buffer invalidation. The D3D12 caller ignores it.
```

## Source note 12, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L36)

```text
// zpd_fsi_counter_index is computed per backend (UINT32_MAX to disable) and
```

## Source note 13, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_fsi_system_constants.h#L37)

```text
// passed in.
```
