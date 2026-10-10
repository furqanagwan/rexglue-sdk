# Scaling list: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/render_target/scaling_list.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/scaling_list.h#L18)

```text
/// A title's list of render target sizes to upscale, in the syntax of
```

## Source note 2, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/scaling_list.h#L19)

```text
/// Microsoft's backward compatibility launch arguments: space-separated
```

## Source note 3, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/scaling_list.h#L20)

```text
/// `WxH`, 0 meaning any (`720x0 844x0 0x240`). A size matches an entry when
```

## Source note 4, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/scaling_list.h#L21)

```text
/// every non-zero dimension of the entry is equal. `none` matches nothing:
```

## Source note 5, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/scaling_list.h#L22)

```text
/// every resolve at the guest's size (with resolve_downscale_average, full
```

## Source note 6, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/scaling_list.h#L23)

```text
/// supersampling).
```

## Source note 7, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/scaling_list.h#L31)

```text
/// Parses `text`; false (and an empty list) if any entry is malformed or
```

## Source note 8, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/scaling_list.h#L32)

```text
/// `0x0`, with the bad entry in `error_out`.
```

## Source note 9, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/scaling_list.h#L35)

```text
/// Whether a render target of this size is upscaled. An empty list scales
```

## Source note 10, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/render_target/scaling_list.h#L36)

```text
/// everything (the behaviour without a list); `none` nothing.
```
