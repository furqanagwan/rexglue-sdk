# Cache: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/texture/cache.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L83)

```text
// DEFINE_int32(
```

## Source note 2, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L84)

```text
//     draw_resolution_scale_x, 1,
```

## Source note 3, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L85)

```text
//     "Integer pixel width scale used for scaling the rendering resolution "
```

## Source note 4, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L86)

```text
//     "opaquely to the game.\n"
```

## Source note 5, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L87)

```text
//     "1, 2 and 3 may be supported, but support of anything above 1 depends on "
```

## Source note 6, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L88)

```text
//     "the device properties, such as whether it supports sparse binding / tiled "
```

## Source note 7, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L89)

```text
//     "resources, the number of virtual address bits per resource, and other "
```

## Source note 8, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L90)

```text
//     "factors.\n"
```

## Source note 9, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L91)

```text
//     "Various effects and parts of game rendering pipelines may work "
```

## Source note 10, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L92)

```text
//     "incorrectly as pixels become ambiguous from the game's perspective and "
```

## Source note 11, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L93)

```text
//     "because half-pixel offset (which normally doesn't affect coverage when "
```

## Source note 12, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L94)

```text
//     "MSAA isn't used) becomes full-pixel.",
```

## Source note 13, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L95)

```text
//     "GPU");
```

## Source note 14, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L96)

```text
// DEFINE_int32(
```

## Source note 15, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L97)

```text
//     draw_resolution_scale_y, 1,
```

## Source note 16, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L98)

```text
//     "Integer pixel width scale used for scaling the rendering resolution "
```

## Source note 17, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L99)

```text
//     "opaquely to the game.\n"
```

## Source note 18, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L100)

```text
//     "See draw_resolution_scale_x for more information.",
```

## Source note 19, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L101)

```text
//     "GPU");
```

## Source note 20, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L102)

```text
// DEFINE_uint32(
```

## Source note 21, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L103)

```text
//     texture_cache_memory_limit_soft, 384,
```

## Source note 22, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L104)

```text
//     "Maximum host texture memory usage (in megabytes) above which old textures "
```

## Source note 23, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L105)

```text
//     "will be destroyed.",
```

## Source note 24, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L106)

```text
//     "GPU");
```

## Source note 25, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L107)

```text
// DEFINE_uint32(
```

## Source note 26, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L108)

```text
//     texture_cache_memory_limit_soft_lifetime, 30,
```

## Source note 27, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L109)

```text
//     "Seconds a texture should be unused to be considered old enough to be "
```

## Source note 28, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L110)

```text
//     "deleted if texture memory usage exceeds texture_cache_memory_limit_soft.",
```

## Source note 29, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L111)

```text
//     "GPU");
```

## Source note 30, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L112)

```text
// DEFINE_uint32(
```

## Source note 31, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L113)

```text
//     texture_cache_memory_limit_hard, 768,
```

## Source note 32, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L114)

```text
//     "Maximum host texture memory usage (in megabytes) above which textures "
```

## Source note 33, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L115)

```text
//     "will be destroyed as soon as possible.",
```

## Source note 34, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L116)

```text
//     "GPU");
```

## Source note 35, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L117)

```text
// DEFINE_uint32(
```

## Source note 36, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L118)

```text
//     texture_cache_memory_limit_render_to_texture, 24,
```

## Source note 37, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L119)

```text
//     "Part of the host texture memory budget (in megabytes) that will be scaled "
```

## Source note 38, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L120)

```text
//     "by the current drawing resolution scale.\n"
```

## Source note 39, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L121)

```text
//     "If texture_cache_memory_limit_soft, for instance, is 384, and this is 24, "
```

## Source note 40, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L122)

```text
//     "it will be assumed that the game will be using roughly 24 MB of "
```

## Source note 41, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L123)

```text
//     "render-to-texture (resolve) targets and 384 - 24 = 360 MB of regular "
```

## Source note 42, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L124)

```text
//     "textures - so with 2x2 resolution scaling, the soft limit will be 360 + "
```

## Source note 43, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L125)

```text
//     "96 MB, and with 3x3, it will be 360 + 216 MB.",
```

## Source note 44, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L126)

```text
//     "GPU");
```

## Source note 45, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L131)

```text
// k8bpb
```

## Source note 46, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L133)

```text
// k16bpb
```

## Source note 47, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L135)

```text
// k32bpb
```

## Source note 48, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L137)

```text
// k64bpb
```

## Source note 49, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L139)

```text
// k128bpb
```

## Source note 50, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L141)

```text
// kR5G5B5A1ToB5G5R5A1
```

## Source note 51, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L143)

```text
// kR5G6B5ToB5G6R5
```

## Source note 52, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L145)

```text
// kR5G6B5ToRGBA8
```

## Source note 53, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L147)

```text
// kR5G5B6ToB5G6R5WithRBGASwizzle
```

## Source note 54, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L149)

```text
// kRGBA4ToBGRA4
```

## Source note 55, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L151)

```text
// kRGBA4ToARGB4
```

## Source note 56, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L153)

```text
// kRGBA4ToRGBA8
```

## Source note 57, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L155)

```text
// kGBGR8ToGRGB8
```

## Source note 58, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L157)

```text
// kGBGR8ToRGB8
```

## Source note 59, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L159)

```text
// kBGRG8ToRGBG8
```

## Source note 60, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L161)

```text
// kBGRG8ToRGB8
```

## Source note 61, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L163)

```text
// kR10G11B11ToRGBA16
```

## Source note 62, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L165)

```text
// kR10G11B11ToRGBA16SNorm
```

## Source note 63, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L167)

```text
// kR11G11B10ToRGBA16
```

## Source note 64, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L169)

```text
// kR11G11B10ToRGBA16SNorm
```

## Source note 65, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L171)

```text
// kR16UNormToFloat
```

## Source note 66, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L173)

```text
// kR16SNormToFloat
```

## Source note 67, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L175)

```text
// kRG16UNormToFloat
```

## Source note 68, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L177)

```text
// kRG16SNormToFloat
```

## Source note 69, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L179)

```text
// kRGBA16UNormToFloat
```

## Source note 70, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L181)

```text
// kRGBA16SNormToFloat
```

## Source note 71, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L183)

```text
// kDXT1ToRGBA8
```

## Source note 72, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L185)

```text
// kDXT3ToRGBA8
```

## Source note 73, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L187)

```text
// kDXT5ToRGBA8
```

## Source note 74, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L189)

```text
// kDXNToRG8
```

## Source note 75, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L191)

```text
// kDXT3A
```

## Source note 76, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L193)

```text
// kDXT3AAs1111ToBGRA4
```

## Source note 77, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L195)

```text
// kDXT3AAs1111ToARGB4
```

## Source note 78, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L197)

```text
// kDXT5AToR8
```

## Source note 79, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L199)

```text
// kCTX1
```

## Source note 80, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L257)

```text
// If memory usage is too high, destroy unused textures.
```

## Source note 81, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L259)

```text
// texture_cache_memory_limit_render_to_texture is assumed to be included in
```

## Source note 82, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L260)

```text
// texture_cache_memory_limit_soft and texture_cache_memory_limit_hard, at 1x,
```

## Source note 83, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L261)

```text
// so subtracting 1 from the scale.
```

## Source note 84, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L287)

```text
// The texture being destroyed might have been bound in the previous
```

## Source note 85, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L288)

```text
// submissions, and nothing has overwritten the binding yet, so completion
```

## Source note 86, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L289)

```text
// of the submission where the texture was last actually used on the GPU
```

## Source note 87, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L290)

```text
// doesn't imply that it's not bound currently. Reset bindings if
```

## Source note 88, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L291)

```text
// any texture has been destroyed.
```

## Source note 89, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L294)

```text
// Remove the texture from the map and destroy it via its unique_ptr.
```

## Source note 90, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L300)

```text
// `texture` is invalid now.
```

## Source note 91, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L315)

```text
// In case there was a failure to create something in the previous frame, make
```

## Source note 92, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L316)

```text
// sure bindings are reset so a new attempt will surely be made if the texture
```

## Source note 93, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L317)

```text
// is requested again.
```

## Source note 94, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L347)

```text
// Invalidate textures. Toggling individual textures between scaled and
```

## Source note 95, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L348)

```text
// unscaled also relies on invalidation through shared memory.
```

## Source note 96, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L360)

```text
// Whole pages only.
```

## Source note 97, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L368)

```text
// Keep the second level a superset: clear a block's bit only when the
```

## Source note 98, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L369)

```text
// block has no scaled page left.
```

## Source note 99, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L387)

```text
// Get rid of 6 and 7 values (to prevent host GPU errors if the game has
```

## Source note 100, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L388)

```text
// something broken) the simple way - by changing them to 4 (0) and 5 (1).
```

## Source note 101, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L453)

```text
// Make sure all the scaled resolve memory is resident and accessible from
```

## Source note 102, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L454)

```text
// the shader, including any possible padding that hasn't yet been touched
```

## Source note 103, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L455)

```text
// by an actual resolve, but is still included in the texture size, so the
```

## Source note 104, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L456)

```text
// GPU won't be trying to access unmapped memory.
```

## Source note 105, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L472)

```text
// Mark the ranges as uploaded and watch them. This is needed for scaled
```

## Source note 106, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L473)

```text
// resolves as well to detect when the CPU wants to reuse the memory for a
```

## Source note 107, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L474)

```text
// regular texture or a vertex buffer, and thus the scaled resolve version is
```

## Source note 108, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L475)

```text
// not up to date anymore.
```

## Source note 109, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L486)

```text
// A texture has become outdated - make sure whether textures are outdated
```

## Source note 110, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L487)

```text
// is rechecked in this draw and in subsequent ones to reload the new data
```

## Source note 111, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L488)

```text
// if needed.
```

## Source note 112, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L492)

```text
// Update the texture keys and the textures.
```

## Source note 113, line 539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L539)

```text
// Check if need to load the unsigned and the signed versions of the texture
```

## Source note 114, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L540)

```text
// (if the format is emulated with different host bit representations for
```

## Source note 115, line 541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L541)

```text
// signed and unsigned - otherwise only the unsigned one is loaded).
```

## Source note 116, line 555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L555)

```text
// Can reuse previously loaded unsigned/signed versions if the key is the
```

## Source note 117, line 556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L556)

```text
// same and the texture was previously bound as unsigned/signed
```

## Source note 118, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L557)

```text
// respectively (checking the previous values of signedness rather than
```

## Source note 119, line 558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L558)

```text
// binding.texture != nullptr and binding.texture_signed != nullptr also
```

## Source note 120, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L559)

```text
// prevents repeated attempts to load the texture if it has failed to
```

## Source note 121, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L560)

```text
// load).
```

## Source note 122, line 580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L580)

```text
// Same resource for both unsigned and signed, but descriptor formats may
```

## Source note 123, line 581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L581)

```text
// be different.
```

## Source note 124, line 666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L666)

```text
// The texture must be in the recent usage list. Place it in front now because
```

## Source note 125, line 667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L667)

```text
// after creation, the texture will likely be used immediately, and it should
```

## Source note 126, line 668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L668)

```text
// not be destroyed immediately after creation if dropping of old textures is
```

## Source note 127, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L669)

```text
// performed somehow. The list is maintained by the Texture, not the
```

## Source note 128, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L670)

```text
// TextureCache itself (unlike the `textures_` container).
```

## Source note 129, line 689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L689)

```text
// Never try to upload data that doesn't exist.
```

## Source note 130, line 745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L745)

```text
// This is called very frequently, don't relink unless needed for caching.
```

## Source note 131, line 752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L752)

```text
// Already the most recently used.
```

## Source note 132, line 797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L797)

```text
// Check if the texture is a scaled resolve texture.
```

## Source note 133, line 864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L864)

```text
// If the host can't support the full texture extent, first try using the
```

## Source note 134, line 865

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L865)

```text
// unscaled version of a scaled resolve texture, then fall back to the first
```

## Source note 135, line 866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L866)

```text
// stored mip level only.
```

## Source note 136, line 891

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L891)

```text
// Try to find an existing texture.
```

## Source note 137, line 898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L898)

```text
// Create the texture and add it to the map.
```

## Source note 138, line 935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L935)

```text
// Reset the key and the signedness.
```

## Source note 139, line 969

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L969)

```text
// No texture data at all.
```

## Source note 140, line 1060

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L1060)

```text
// Two-level check for faster rejection since resolve targets are usually
```

## Source note 141, line 1061

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L1061)

```text
// placed in relatively small and localized memory portions (confirmed by
```

## Source note 142, line 1062

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L1062)

```text
// testing - pretty much all times the deeper level was entered, the texture
```

## Source note 143, line 1063

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L1063)

```text
// was a resolve target).
```

## Source note 144, line 1111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L1111)

```text
// Resolves themselves do exactly the opposite of what this should do.
```

## Source note 145, line 1114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L1114)

```text
// Mark scaled resolve ranges as non-scaled. Textures themselves will be
```

## Source note 146, line 1115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L1115)

```text
// invalidated by their shared memory watches.
```

## Source note 147, line 1125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/cache.cpp#L1125)

```text
// Pre-mask to only process blocks within the write range.
```
