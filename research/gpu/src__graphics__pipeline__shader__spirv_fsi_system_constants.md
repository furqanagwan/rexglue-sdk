# Spirv fsi system constants: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L37)

```text
// Per render target clamp ranges and write keep masks (two UINT32_MAX when no
```

## Source note 2, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L38)

```text
// components actually existing in the RT are written).
```

## Source note 3, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L50)

```text
// Disable depth and stencil only if an aliased color target writes bits used
```

## Source note 4, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L51)

```text
// by either test. Otherwise its keep-masked store preserves them.
```

## Source note 5, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L52)

```text
// Don't exclude fully overlapping render targets - two with the same base are
```

## Source note 6, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L53)

```text
// used in the lighting pass of 4D5307E6, picked with dynamic control flow.
```

## Source note 7, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L68)

```text
// Depth / stencil flag bits.
```

## Source note 8, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L81)

```text
// In case stencil is used without depth testing - always pass, and don't
```

## Source note 9, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L82)

```text
// modify the stored depth.
```

## Source note 10, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L90)

```text
// Hint - if not applicable to the shader, will not have effect.
```

## Source note 11, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L104)

```text
// EDRAM pitch for FSI render target writing. Align, then multiply by the
```

## Source note 12, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L105)

```text
// 32bpp tile size in dwords.
```

## Source note 13, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L115)

```text
// Per render target FSI write state.
```

## Source note 14, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L129)

```text
// Can't do float comparisons here because NaNs would result in always
```

## Source note 15, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L130)

```text
// setting the dirty flag.
```

## Source note 16, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L140)

```text
// For non-polygons, front polygon offset is used, enabled if
```

## Source note 17, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L141)

```text
// POLY_OFFSET_PARA_ENABLED is set. For polygons, front and back are separate.
```

## Source note 18, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L161)

```text
// With non-square resolution scaling, make sure the worst-case impact is
```

## Source note 19, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L162)

```text
// reverted (slope only along the scaled axis), thus max. More bias is better
```

## Source note 20, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L163)

```text
// than less bias, because less bias means Z fighting with the background is
```

## Source note 21, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_fsi_system_constants.cpp#L164)

```text
// more likely.
```
