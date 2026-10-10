# Dxbc: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/dxbc.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc.h#L34)

```text
// Resource bindings are gathered after the successful translation of any
```

## Source note 2, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc.h#L35)

```text
// modification for simplicity of translation (and they don't depend on
```

## Source note 3, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc.h#L36)

```text
// modification bits).
```

## Source note 4, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc.h#L44)

```text
// Stacked and 3D are separate TextureBindings, even for bindless for null
```

## Source note 5, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc.h#L45)

```text
// descriptor handling simplicity.
```

## Source note 6, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/dxbc.h#L49)

```text
// Safe to hash and compare with memcmp for layout hashing.
```
