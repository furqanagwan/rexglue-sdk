# Spirv builder: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/spirv_builder.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builder.cpp#L137)

```text
// Make the blocks, but only put the then-block into the function, the
```

## Source note 2, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builder.cpp#L138)

```text
// else-block and merge-block will be added later, in order, after earlier
```

## Source note 3, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builder.cpp#L139)

```text
// code is emitted.
```

## Source note 4, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builder.cpp#L144)

```text
// Save the current block, so that we can add in the flow control split when
```

## Source note 5, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builder.cpp#L145)

```text
// makeEndIf is called.
```

## Source note 6, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builder.cpp#L162)

```text
// Close out the "then" by having it jump to the mergeBlock.
```

## Source note 7, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builder.cpp#L167)

```text
// Make the first else block and add it to the function.
```

## Source note 8, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builder.cpp#L171)

```text
// Start building the else block.
```

## Source note 9, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builder.cpp#L185)

```text
// Jump to the merge block.
```

## Source note 10, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builder.cpp#L190)

```text
// Go back to the headerBlock and make the flow control split.
```

## Source note 11, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_builder.cpp#L209)

```text
// Add the merge block to the function.
```
