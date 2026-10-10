# Image decode: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/image_decode.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/image_decode.h#L17)

```text
// Decodes a PNG (or any stb-supported image) byte buffer to tightly-packed
```

## Source note 2, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/image_decode.h#L18)

```text
// R8G8B8A8 pixels. Returns an empty vector on failure; on success fills
```

## Source note 3, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/image_decode.h#L19)

```text
// out_width/out_height and returns width*height*4 bytes.
```
