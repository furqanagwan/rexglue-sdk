# Texture load ctx1.cs: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/texture_load_ctx1.cs.xesl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L13)

```text
// http://fileadmin.cs.lth.se/cs/Personal/Michael_Doggett/talks/unc-xenos-doggett.pdf
```

## Source note 2, line 14

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L14)

```text
// CXT1 is like DXT3/5 color, but 2-component and with 8:8 endpoints rather than
```

## Source note 3, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L15)

```text
// 5:6:5.
```

## Source note 4, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L17)

```text
// Dword 1:
```

## Source note 5, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L20)

```text
// (R is in the higher bits, according to how this format is used in 4D5307E6).
```

## Source note 6, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L21)

```text
// Dword 2:
```

## Source note 7, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L22)

```text
// AA BB CC DD
```

## Source note 8, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L23)

```text
// EE FF GG HH
```

## Source note 9, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L24)

```text
// II JJ KK LL
```

## Source note 10, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L25)

```text
// MM NN OO PP
```

## Source note 11, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L41)

```text
// 1 thread = 4 CTX1 blocks to 16x4 R8G8 texels.
```

## Source note 12, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L61)

```text
// Odd 2 blocks = even 2 blocks + 32 bytes when tiled.
```

## Source note 13, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L64)

```text
// Two blocks.
```

## Source note 14, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L68)

```text
// Unpack the endpoints as 0x00g000r0 0x00G000R0 0x00g100r1 0x00G100R1 so
```

## Source note 15, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_ctx1.cs.xesl#L69)

```text
// they can be multiplied by their weights allowing overflow.
```
