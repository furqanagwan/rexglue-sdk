# Info: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/texture/info.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L27)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/cc308051(v=vs.85).aspx
```

## Source note 2, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L28)

```text
// a2xx_sq_surfaceformat
```

## Source note 3, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L42)

```text
// we treat 1D textures as 2D
```

## Source note 4, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L83)

```text
// We've gotten this far and mip_address is zero, assume no extra mips.
```

## Source note 5, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L159)

```text
// Short-circuit. Mip 0 is always stored in base_address.
```

## Source note 6, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L170)

```text
// Short-circuit. There is no mip data.
```

## Source note 7, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L194)

```text
// Walk forward to find the address of the mip.
```

## Source note 8, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L200)

```text
// We've reached the point where the mips are packed into a single tile.
```

## Source note 9, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L206)

```text
// Now, check if the mip is packed at an offset.
```

## Source note 10, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L215)

```text
// Tile size is 32x32, and once textures go <=16 they are packed into a
```

## Source note 11, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L216)

```text
// single tile together. The math here is insane. Most sourced
```

## Source note 12, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L217)

```text
// from graph paper and looking at dds dumps.
```

## Source note 13, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L218)

```text
//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
```

## Source note 14, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L219)

```text
// 0         +.4x4.+ +.....8x8.....+ +............16x16............+
```

## Source note 15, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L220)

```text
// 1         +.4x4.+ +.....8x8.....+ +............16x16............+
```

## Source note 16, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L221)

```text
// 2         +.4x4.+ +.....8x8.....+ +............16x16............+
```

## Source note 17, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L222)

```text
// 3         +.4x4.+ +.....8x8.....+ +............16x16............+
```

## Source note 18, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L223)

```text
// 4 x               +.....8x8.....+ +............16x16............+
```

## Source note 19, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L224)

```text
// 5                 +.....8x8.....+ +............16x16............+
```

## Source note 20, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L225)

```text
// 6                 +.....8x8.....+ +............16x16............+
```

## Source note 21, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L226)

```text
// 7                 +.....8x8.....+ +............16x16............+
```

## Source note 22, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L227)

```text
// 8 2x2                             +............16x16............+
```

## Source note 23, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L228)

```text
// 9 2x2                             +............16x16............+
```

## Source note 24, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L229)

```text
// 0                                 +............16x16............+
```

## Source note 25, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L231)

```text
// This only works for square textures, or textures that are some non-pot
```

## Source note 26, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L232)

```text
// <= square. As soon as the aspect ratio goes weird, the textures start to
```

## Source note 27, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L233)

```text
// stretch across tiles.
```

## Source note 28, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L235)

```text
// The 2x2 and 1x1 squares are packed in their specific positions because
```

## Source note 29, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L236)

```text
// each square is the size of at least one block (which is 4x4 pixels max)
```

## Source note 30, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L238)

```text
// if (tile_aligned(w) > tile_aligned(h)) {
```

## Source note 31, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L239)

```text
//   // wider than tall, so packed horizontally
```

## Source note 32, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L240)

```text
// } else if (tile_aligned(w) < tile_aligned(h)) {
```

## Source note 33, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L241)

```text
//   // taller than wide, so packed vertically
```

## Source note 34, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L242)

```text
// } else {
```

## Source note 35, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L245)

```text
// It's important to use logical sizes here, as the input sizes will be
```

## Source note 36, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L246)

```text
// for the entire packed tile set, not the actual texture.
```

## Source note 37, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L247)

```text
// The minimum dimension is what matters most: if either width or height
```

## Source note 38, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L248)

```text
// is <= 16 this mode kicks in.
```

## Source note 39, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L253)

```text
// Too big, not packed.
```

## Source note 40, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L259)

```text
// Find the block offset of the mip.
```

## Source note 41, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L262)

```text
// Wider than tall. Laid out vertically.
```

## Source note 42, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L266)

```text
// Taller than wide. Laid out horizontally.
```

## Source note 43, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L272)

```text
// Wider than tall. Laid out vertically.
```

## Source note 44, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L276)

```text
// Taller than wide. Laid out horizontally.
```

## Source note 45, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L311)

```text
// There is a base mip level.
```

## Source note 46, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L317)

```text
// Sort circuit. Only one mip.
```

## Source note 47, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L327)

```text
// Mip data is actually at base address?
```

## Source note 48, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L331)

```text
// Nothing needs to be done.
```

## Source note 49, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L333)

```text
// WTF?
```

## Source note 50, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L351)

```text
// Walk forward to find the address of the mip.
```

## Source note 51, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/info.cpp#L357)

```text
// We've reached the point where the mips are packed into a single tile.
```
