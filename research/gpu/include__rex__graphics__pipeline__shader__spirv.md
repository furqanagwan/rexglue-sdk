# Spirv: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/spirv.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv.h#L38)

```text
// Resource bindings are gathered after the successful translation of any
```

## Source note 2, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv.h#L39)

```text
// modification for simplicity of translation (and they don't depend on
```

## Source note 3, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv.h#L40)

```text
// modification bits).
```

## Source note 4, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv.h#L44)

```text
// Stacked and 3D are separate TextureBindings.
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv.h#L48)

```text
// Safe to hash and compare with memcmp for layout hashing.
```

## Source note 6, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv.h#L60)

```text
// getBCF samples with the border color forced to forced_border_color.
```

## Source note 7, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv.h#L68)

```text
// True once a translation has gathered the resource bindings above. Set with
```

## Source note 8, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv.h#L69)

```text
// release ordering after the binding vectors are filled (which may happen on
```

## Source note 9, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv.h#L70)

```text
// a pipeline creation thread), so a draw-thread reader that sees this true
```

## Source note 10, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv.h#L71)

```text
// (acquire) is guaranteed the bindings are fully written and immutable.
```
