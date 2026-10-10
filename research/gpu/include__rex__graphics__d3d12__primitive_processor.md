# Primitive processor: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/d3d12/primitive_processor.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/primitive_processor.h#L67)

```text
// Temporary buffer copied in the beginning of the first submission for
```

## Source note 2, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/primitive_processor.h#L68)

```text
// uploading to builtin_index_buffer_, destroyed when the submission when it
```

## Source note 3, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/primitive_processor.h#L69)

```text
// was uploaded is completed.
```

## Source note 4, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/primitive_processor.h#L71)

```text
// UINT64_MAX means not uploaded yet and needs uploading in the first
```

## Source note 5, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/primitive_processor.h#L72)

```text
// submission (if the upload buffer exists at all).
```

## Source note 6, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/primitive_processor.h#L76)

```text
// Indexed by the backend handles.
```

## Source note 7, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/primitive_processor.h#L80)

```text
// namespace rex::graphics::d3d12
```
