# Spirv builder: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/spirv_builder.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L26)

```text
// SpvBuilder with extra helpers.
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L33)

```text
// When true, createNoContraction* helpers emit plain operations.
```

## Source note 3, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L37)

```text
// Decorate every float arithmetic result with NoContraction.
```

## Source note 4, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L51)

```text
// Make public rather than protected.
```

## Source note 5, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L54)

```text
// Backward compatibility wrapper for createBranch
```

## Source note 6, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L57)

```text
// Backward compatibility wrapper for makeFunctionEntry
```

## Source note 7, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L58)

```text
// For shaders, we use LinkageType::Max which means no linkage decoration
```

## Source note 8, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L63)

```text
// LinkageType::Max means no linkage decoration will be added (correct for
```

## Source note 9, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L64)

```text
// shader entry points)
```

## Source note 10, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L69)

```text
// Hide base class createAccessChain to workaround the way
```

## Source note 11, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L70)

```text
// glslang 11.6.0+ uses internal accessChain state instead of parameters.
```

## Source note 12, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L73)

```text
// glslang 11.6.0+ uses the accessChain member
```

## Source note 13, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L74)

```text
// in getResultingAccessChainType() but doesn't populate it from the
```

## Source note 14, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L75)

```text
// parameters. We need to set it up correctly before calling the parent.
```

## Source note 15, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L84)

```text
// Clear the state again to avoid affecting subsequent operations
```

## Source note 16, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L104)

```text
// Makes a constant of a float scalar or vector value_type with all
```

## Source note 17, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L105)

```text
// components set to value.
```

## Source note 18, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L108)

```text
// Helper to use for building nested control flow with if-then-else with
```

## Source note 19, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L109)

```text
// additions over SpvBuilder::If.
```

## Source note 20, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L124)

```text
// If there's no then/else block that branches to the merge block, the phi
```

## Source note 21, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L125)

```text
// parent is the header block - this simplifies then-only usage.
```

## Source note 22, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L162)

```text
// Simpler and more flexible (such as multiple cases pointing to the same
```

## Source note 23, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L163)

```text
// block) compared to makeSwitch.
```

## Source note 24, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L175)

```text
// If there's no default block that branches to the merge block, the phi
```

## Source note 25, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L176)

```text
// parent is the header block - this simplifies case-only usage.
```

## Source note 26, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_builder.h#L207)

```text
// Defined in the .cc since the spv enum shim is not visible in headers.
```
