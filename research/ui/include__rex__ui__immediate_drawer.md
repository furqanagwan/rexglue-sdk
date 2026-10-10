# Immediate drawer: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/immediate_drawer.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L20)

```text
// Describes the filter applied when sampling textures.
```

## Source note 2, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L26)

```text
// Simple texture compatible with the immediate renderer.
```

## Source note 3, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L31)

```text
// Texture width, in pixels.
```

## Source note 4, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L33)

```text
// Texture height, in pixels.
```

## Source note 5, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L40)

```text
// Describes the primitive type used by a draw call.
```

## Source note 6, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L46)

```text
// Simple vertex used by the immediate mode drawer.
```

## Source note 7, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L47)

```text
// To avoid translations, this matches both imgui and elemental-forms vertices:
```

## Source note 8, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L56)

```text
// All parameters required to draw an immediate-mode batch of vertices.
```

## Source note 9, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L58)

```text
// Vertices to draw.
```

## Source note 10, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L62)

```text
// Optional index buffer indices.
```

## Source note 11, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L68)

```text
// Primitive type the vertices/indices represent.
```

## Source note 12, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L70)

```text
// Total number of elements to draw.
```

## Source note 13, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L72)

```text
// Starting offset in the index buffer.
```

## Source note 14, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L74)

```text
// Base vertex of elements, if using an index buffer.
```

## Source note 15, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L77)

```text
// Texture used when drawing, or nullptr if color only.
```

## Source note 16, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L80)

```text
// True to enable scissoring using the region defined by scissor_rect.
```

## Source note 17, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L82)

```text
// Scissoring region in the coordinate space (if right < left or bottom < top,
```

## Source note 18, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L83)

```text
// not drawing).
```

## Source note 19, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L99)

```text
// Creates a new texture with the given attributes and R8G8B8A8 data.
```

## Source note 20, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L105)

```text
// Begins drawing in immediate mode using the given projection matrix. The
```

## Source note 21, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L106)

```text
// presenter that is currently attached to the immediate drawer, as the
```

## Source note 22, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L107)

```text
// implementation may hold presenter-specific information such as UI
```

## Source note 23, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L108)

```text
// submission indices. Pass 0 or a negative value as the coordinate space
```

## Source note 24, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L109)

```text
// width or height to use raw render target pixel coordinates (or this will
```

## Source note 25, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L110)

```text
// just be used as a safe fallback when with a non-zero-sized surface the
```

## Source note 26, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L111)

```text
// coordinate space size becomes zero somehow).
```

## Source note 27, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L114)

```text
// Starts a draw batch.
```

## Source note 28, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L116)

```text
// Draws one set of a batch.
```

## Source note 29, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L118)

```text
// Ends a draw batch.
```

## Source note 30, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L120)

```text
// Ends drawing in immediate mode and flushes contents.
```

## Source note 31, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L130)

```text
// Available between Begin and End.
```

## Source note 32, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L135)

```text
// Converts and clamps the scissor in the immediate draw to render target
```

## Source note 33, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L136)

```text
// coordinates. Returns whether the scissor contains any render target pixels
```

## Source note 34, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/immediate_drawer.h#L137)

```text
// (but a valid scissor is written even if false is returned).
```
