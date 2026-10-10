# Graphics system: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/graphics_system.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/graphics_system.h#L33)

```text
// Forward declarations
```

## Source note 2, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/graphics_system.h#L67)

```text
// May be called from any thread any number of times, even during recovery
```

## Source note 3, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/graphics_system.h#L68)

```text
// from a device loss.
```

## Source note 4, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/graphics_system.h#L96)

```text
// Backends build their provider here. Called lazily from either setup
```

## Source note 5, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/graphics_system.h#L97)

```text
// entry point; with_presentation is false only on headless guest-GPU paths.
```
