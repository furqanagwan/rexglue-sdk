# Shader: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/d3d12/shader.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shader.h#L37)

```text
// For owning subsystem like the pipeline cache, accessors for unique
```

## Source note 2, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shader.h#L38)

```text
// identifiers (used instead of hashes to make sure collisions can't happen)
```

## Source note 3, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shader.h#L39)

```text
// of binding layouts used by the shader, for invalidation if a shader with an
```

## Source note 4, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shader.h#L40)

```text
// incompatible layout was bound.
```

## Source note 5, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shader.h#L43)

```text
// Modifications of the same shader can be translated on different threads.
```

## Source note 6, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shader.h#L44)

```text
// The "set" function must only be called if "enter" returned true - these are
```

## Source note 7, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shader.h#L45)

```text
// set up only once.
```

## Source note 8, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shader.h#L59)

```text
// namespace rex::graphics::d3d12
```
