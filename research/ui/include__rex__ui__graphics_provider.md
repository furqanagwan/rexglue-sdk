# Graphics provider: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/graphics_provider.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_provider.h#L23)

```text
// Factory for graphics contexts.
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_provider.h#L24)

```text
// All contexts created by the same provider will be able to share resources
```

## Source note 3, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_provider.h#L25)

```text
// according to the rules of the backing graphics API.
```

## Source note 4, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_provider.h#L46)

```text
// It's safe to reinitialize the presenter in the host GPU loss callback if it
```

## Source note 5, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_provider.h#L47)

```text
// was called from the UI thread as specified in the arguments.
```
