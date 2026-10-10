# Dxbc translator om: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/dxbc_translator_om.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L30)

```text
// Get EDRAM offsets for the pixel:
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L31)

```text
// system_temp_rov_params_.y - for depth (absolute).
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L32)

```text
// system_temp_rov_params_.z - for 32bpp color (base-relative).
```

## Source note 4, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L33)

```text
// system_temp_rov_params_.w - for 64bpp color (base-relative).
```

## Source note 5, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L36)

```text
// For now, while we don't know the encoding of 64bpp render targets when
```

## Source note 6, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L37)

```text
// interpreted as 32bpp (no game has been seen reinterpreting between the two
```

## Source note 7, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L38)

```text
// yet), for consistency with the conventional render target logic and to have
```

## Source note 8, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L39)

```text
// the same resolve logic for both, storing 64bpp color as 40x16 samples
```

## Source note 9, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L40)

```text
// (multiplied by the resolution scale) per 1280-byte tile. It's also
```

## Source note 10, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L41)

```text
// convenient to use 40x16 granularity in the calculations here because depth
```

## Source note 11, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L42)

```text
// render targets have 40-sample halves swapped as opposed to color in each
```

## Source note 12, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L43)

```text
// tile, and reinterpretation between depth and color is common for depth /
```

## Source note 13, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L44)

```text
// stencil reloading into the EDRAM (such as in the background of the main
```

## Source note 14, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L45)

```text
// menu of 4D5307E6).
```

## Source note 15, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L47)

```text
// Convert the host pixel position to integer to system_temp_rov_params_.xy.
```

## Source note 16, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L48)

```text
// system_temp_rov_params_.x = X host pixel position as uint
```

## Source note 17, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L49)

```text
// system_temp_rov_params_.y = Y host pixel position as uint
```

## Source note 18, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L52)

```text
// Convert the position from pixels to canonical sample 0 coordinates,
```

## Source note 19, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L53)

```text
// meaning the coordinates of the pixel's sample 0 in the single sampled
```

## Source note 20, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L54)

```text
// view of the EDRAM data. The layout is described in XeEdramOffsetBytes
```

## Source note 21, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L55)

```text
// (see edram.xesli). What matters here is that the offsets of the other
```

## Source note 22, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L56)

```text
// samples from sample 0 are constant, so the sample loops just add them, and
```

## Source note 23, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L57)

```text
// that with resolution scaling the rearrangement happens at guest pixel
```

## Source note 24, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L58)

```text
// granularity.
```

## Source note 25, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L59)

```text
// system_temp_rov_params_.x = X sample 0 position
```

## Source note 26, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L60)

```text
// system_temp_rov_params_.y = Y sample 0 position
```

## Source note 27, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L77)

```text
// guest_pixel_temp.xy = guest pixel
```

## Source note 28, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L78)

```text
// guest_pixel_temp.zw = host subpixel offset
```

## Source note 29, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L91)

```text
// Check if 4x MSAA is enabled.
```

## Source note 30, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L97)

```text
// system_temp_rov_params_.z = X >> 1
```

## Source note 31, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L99)

```text
// system_temp_rov_params_.w = X & 1
```

## Source note 32, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L101)

```text
// system_temp_rov_params_.x = ((X >> 1) << 2) | (X & 1)
```

## Source note 33, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L105)

```text
// system_temp_rov_params_.z = Y >> 1
```

## Source note 34, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L107)

```text
// system_temp_rov_params_.w = Y & 1
```

## Source note 35, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L109)

```text
// system_temp_rov_params_.y = ((Y >> 1) << 2) | (Y & 1)
```

## Source note 36, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L117)

```text
// Check if 2x MSAA is enabled.
```

## Source note 37, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L123)

```text
// system_temp_rov_params_.z = X >> 1
```

## Source note 38, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L125)

```text
// system_temp_rov_params_.z = Y with bit 1 = X bit 1
```

## Source note 39, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L128)

```text
// system_temp_rov_params_.w = Y >> 1
```

## Source note 40, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L130)

```text
// system_temp_rov_params_.y = ((Y >> 1) << 2) | (X & 2) | (Y & 1)
```

## Source note 41, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L134)

```text
// system_temp_rov_params_.x = X & ~2
```

## Source note 42, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L146)

```text
// For cases of both color and depth:
```

## Source note 43, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L147)

```text
//   Get 40 x 16 x resolution scale 32bpp half-tile or 40x16 64bpp tile index
```

## Source note 44, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L148)

```text
//   to system_temp_rov_params_.zw, and put the sample index within such a
```

## Source note 45, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L149)

```text
//   region in system_temp_rov_params_.xy.
```

## Source note 46, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L150)

```text
//   Working with 40x16-sample portions for 64bpp and for swapping for depth -
```

## Source note 47, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L151)

```text
//   dividing by 40, not by 80.
```

## Source note 48, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L152)

```text
// For depth-only:
```

## Source note 49, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L153)

```text
//   Same, but for full 80x16 tiles, not 40x16 half-tiles.
```

## Source note 50, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L157)

```text
// system_temp_rov_params_.x = X sample 0 position within the half-tile or
```

## Source note 51, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L159)

```text
// system_temp_rov_params_.y = Y sample 0 position within the (half-)tile
```

## Source note 52, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L160)

```text
// system_temp_rov_params_.z = X half-tile or tile position
```

## Source note 53, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L161)

```text
// system_temp_rov_params_.w = Y tile position
```

## Source note 54, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L168)

```text
// Convert the Y sample 0 position within the half-tile or tile to the dword
```

## Source note 55, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L169)

```text
// offset of the row within a 80x16 32bpp tile or a 40x16 64bpp half-tile to
```

## Source note 56, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L170)

```text
// system_temp_rov_params_.y.
```

## Source note 57, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L171)

```text
// system_temp_rov_params_.x = X sample 0 position within the half-tile or
```

## Source note 58, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L173)

```text
// system_temp_rov_params_.y = Y sample 0 row dword offset within the
```

## Source note 59, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L174)

```text
//                             80x16-dword tile
```

## Source note 60, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L175)

```text
// system_temp_rov_params_.z = X half-tile position
```

## Source note 61, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L176)

```text
// system_temp_rov_params_.w = Y tile position
```

## Source note 62, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L183)

```text
// Depth, 32bpp color, 64bpp color are all needed.
```

## Source note 63, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L185)

```text
// X sample 0 position within in the half-tile in system_temp_rov_params_.x,
```

## Source note 64, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L186)

```text
// for 64bpp, will be used directly as sample X the within the 80x16-dword
```

## Source note 65, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L187)

```text
// region, but for 32bpp color and depth, 40x16 half-tile index within the
```

## Source note 66, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L188)

```text
// 80x16 tile - system_temp_rov_params_.z & 1 - will also be taken into
```

## Source note 67, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L189)

```text
// account when calculating the X (directly for color, flipped for depth).
```

## Source note 68, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L193)

```text
// Multiply the Y tile position by the surface tile pitch in dwords to get
```

## Source note 69, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L194)

```text
// the address of the origin of the row of tiles within a 32bpp surface in
```

## Source note 70, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L195)

```text
// dwords (later it needs to be multiplied by 2 for 64bpp).
```

## Source note 71, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L196)

```text
// system_temp_rov_params_.x = X sample 0 position within the half-tile
```

## Source note 72, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L197)

```text
// system_temp_rov_params_.y = Y sample 0 row dword offset within the
```

## Source note 73, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L198)

```text
//                             80x16-dword tile
```

## Source note 74, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L199)

```text
// system_temp_rov_params_.z = X half-tile position
```

## Source note 75, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L200)

```text
// system_temp_rov_params_.w = Y tile row dword origin in a 32bpp surface
```

## Source note 76, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L207)

```text
// Get the 32bpp tile X position within the row of tiles to
```

## Source note 77, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L208)

```text
// rov_address_temp.x.
```

## Source note 78, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L209)

```text
// system_temp_rov_params_.x = X sample 0 position within the half-tile
```

## Source note 79, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L210)

```text
// system_temp_rov_params_.y = Y sample 0 row dword offset within the
```

## Source note 80, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L211)

```text
//                             80x16-dword tile
```

## Source note 81, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L212)

```text
// system_temp_rov_params_.z = X half-tile position
```

## Source note 82, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L213)

```text
// system_temp_rov_params_.w = Y tile row dword origin in a 32bpp surface
```

## Source note 83, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L214)

```text
// rov_address_temp.x = X 32bpp tile position
```

## Source note 84, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L217)

```text
// Get the dword offset of the beginning of the row of samples within a row
```

## Source note 85, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L218)

```text
// of 32bpp 80x16 tiles to rov_address_temp.x.
```

## Source note 86, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L219)

```text
// system_temp_rov_params_.x = X sample 0 position within the half-tile
```

## Source note 87, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L220)

```text
// system_temp_rov_params_.y = Y sample 0 row dword offset within the
```

## Source note 88, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L221)

```text
//                             80x16-dword tile
```

## Source note 89, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L222)

```text
// system_temp_rov_params_.z = X half-tile position
```

## Source note 90, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L223)

```text
// system_temp_rov_params_.w = Y tile row dword origin in a 32bpp surface
```

## Source note 91, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L224)

```text
// rov_address_temp.x = dword offset of the beginning of the row of samples
```

## Source note 92, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L225)

```text
//                      within a row of 32bpp tiles
```

## Source note 93, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L229)

```text
// Get the dword offset of the beginning of the row of samples within a
```

## Source note 94, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L230)

```text
// 32bpp surface to rov_address_temp.x.
```

## Source note 95, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L231)

```text
// system_temp_rov_params_.x = X sample 0 position within the half-tile
```

## Source note 96, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L232)

```text
// system_temp_rov_params_.y = Y sample 0 row dword offset within the
```

## Source note 97, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L233)

```text
//                             80x16-dword tile
```

## Source note 98, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L234)

```text
// system_temp_rov_params_.z = X half-tile position
```

## Source note 99, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L235)

```text
// system_temp_rov_params_.w = Y tile row dword origin in a 32bpp surface
```

## Source note 100, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L236)

```text
// rov_address_temp.x = dword offset of the beginning of the row of samples
```

## Source note 101, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L237)

```text
//                      within a 32bpp surface
```

## Source note 102, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L242)

```text
// Get the dword offset of the beginning of the row of samples within a row
```

## Source note 103, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L243)

```text
// of 64bpp 80x16 tiles to system_temp_rov_params_.y (last time the
```

## Source note 104, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L244)

```text
// tile-local Y offset is needed).
```

## Source note 105, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L245)

```text
// system_temp_rov_params_.x = X sample 0 position within the half-tile
```

## Source note 106, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L246)

```text
// system_temp_rov_params_.y = dword offset of the beginning of the row of
```

## Source note 107, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L247)

```text
//                             samples within a row of 64bpp tiles
```

## Source note 108, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L248)

```text
// system_temp_rov_params_.z = X half-tile position
```

## Source note 109, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L249)

```text
// system_temp_rov_params_.w = Y tile row dword origin in a 32bpp surface
```

## Source note 110, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L250)

```text
// rov_address_temp.x = dword offset of the beginning of the row of samples
```

## Source note 111, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L251)

```text
//                      within a 32bpp surface
```

## Source note 112, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L255)

```text
// Get the dword offset of the beginning of the row of samples within a
```

## Source note 113, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L256)

```text
// 64bpp surface to system_temp_rov_params_.w (last time the Y tile row
```

## Source note 114, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L257)

```text
// offset is needed).
```

## Source note 115, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L258)

```text
// system_temp_rov_params_.x = X sample 0 position within the half-tile
```

## Source note 116, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L259)

```text
// system_temp_rov_params_.y = free
```

## Source note 117, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L260)

```text
// system_temp_rov_params_.z = X half-tile position
```

## Source note 118, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L261)

```text
// system_temp_rov_params_.w = dword offset of the beginning of the row of
```

## Source note 119, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L262)

```text
//                             samples within a 64bpp surface
```

## Source note 120, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L263)

```text
// rov_address_temp.x = dword offset of the beginning of the row of samples
```

## Source note 121, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L264)

```text
//                      within a 32bpp surface
```

## Source note 122, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L269)

```text
// Get the final offset of the sample 0 within a 64bpp surface to
```

## Source note 123, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L270)

```text
// system_temp_rov_params_.w.
```

## Source note 124, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L271)

```text
// system_temp_rov_params_.x = X sample 0 position within the half-tile
```

## Source note 125, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L272)

```text
// system_temp_rov_params_.z = X half-tile position
```

## Source note 126, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L273)

```text
// system_temp_rov_params_.w = dword sample 0 offset within a 64bpp surface
```

## Source note 127, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L274)

```text
// rov_address_temp.x = dword offset of the beginning of the row of samples
```

## Source note 128, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L275)

```text
//                      within a 32bpp surface
```

## Source note 129, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L280)

```text
// Get the half-tile index within the tile to system_temp_rov_params_.y
```

## Source note 130, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L281)

```text
// (last time the X half-tile position is needed).
```

## Source note 131, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L282)

```text
// system_temp_rov_params_.x = X sample 0 position within the half-tile
```

## Source note 132, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L283)

```text
// system_temp_rov_params_.y = half-tile index within the tile
```

## Source note 133, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L284)

```text
// system_temp_rov_params_.z = free
```

## Source note 134, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L285)

```text
// system_temp_rov_params_.w = dword sample 0 offset within a 64bpp surface
```

## Source note 135, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L286)

```text
// rov_address_temp.x = dword offset of the beginning of the row of samples
```

## Source note 136, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L287)

```text
//                      within a 32bpp surface
```

## Source note 137, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L291)

```text
// Get the X position within the 32bpp tile to system_temp_rov_params_.z
```

## Source note 138, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L292)

```text
// (last time the X position within the half-tile is needed).
```

## Source note 139, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L293)

```text
// system_temp_rov_params_.x = free
```

## Source note 140, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L294)

```text
// system_temp_rov_params_.y = half-tile index within the tile
```

## Source note 141, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L295)

```text
// system_temp_rov_params_.z = X sample 0 position within the tile
```

## Source note 142, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L296)

```text
// system_temp_rov_params_.w = dword sample 0 offset within a 64bpp surface
```

## Source note 143, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L297)

```text
// rov_address_temp.x = dword offset of the beginning of the row of samples
```

## Source note 144, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L298)

```text
//                      within a 32bpp surface
```

## Source note 145, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L303)

```text
// Get the final offset of the sample 0 within a 32bpp color surface to
```

## Source note 146, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L304)

```text
// system_temp_rov_params_.z (last time the 32bpp row offset is needed).
```

## Source note 147, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L305)

```text
// system_temp_rov_params_.y = half-tile index within the tile
```

## Source note 148, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L306)

```text
// system_temp_rov_params_.z = dword sample 0 offset within a 32bpp surface
```

## Source note 149, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L307)

```text
// system_temp_rov_params_.w = dword sample 0 offset within a 64bpp surface
```

## Source note 150, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L308)

```text
// rov_address_temp.x = free
```

## Source note 151, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L313)

```text
// Flip the 40x16 half-tiles for depth / stencil as opposed to 32bpp color -
```

## Source note 152, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L314)

```text
// get the dword offset to add for flipping to system_temp_rov_params_.y.
```

## Source note 153, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L315)

```text
// system_temp_rov_params_.y = depth half-tile flipping offset
```

## Source note 154, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L316)

```text
// system_temp_rov_params_.z = dword sample 0 offset within a 32bpp surface
```

## Source note 155, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L317)

```text
// system_temp_rov_params_.w = dword sample 0 offset within a 64bpp surface
```

## Source note 156, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L321)

```text
// Flip the 40x16 half-tiles for depth / stencil as opposed to 32bpp color -
```

## Source note 157, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L322)

```text
// get the final offset of the sample 0 within a 32bpp depth / stencil
```

## Source note 158, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L323)

```text
// surface to system_temp_rov_params_.y.
```

## Source note 159, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L324)

```text
// system_temp_rov_params_.y = dword sample 0 offset within depth / stencil
```

## Source note 160, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L325)

```text
// system_temp_rov_params_.z = dword sample 0 offset within a 32bpp surface
```

## Source note 161, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L326)

```text
// system_temp_rov_params_.w = dword sample 0 offset within a 64bpp surface
```

## Source note 162, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L331)

```text
// Release rov_address_temp.
```

## Source note 163, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L334)

```text
// Simpler logic for depth-only, not involving half-tile indices (flipping
```

## Source note 164, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L335)

```text
// half-tiles via comparison).
```

## Source note 165, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L337)

```text
// Get the dword offset of the beginning of the row of samples within a row
```

## Source note 166, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L338)

```text
// of 32bpp 80x16 tiles to system_temp_rov_params_.z (last time the X tile
```

## Source note 167, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L339)

```text
// position is needed).
```

## Source note 168, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L340)

```text
// system_temp_rov_params_.x = X sample 0 position within the tile
```

## Source note 169, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L341)

```text
// system_temp_rov_params_.y = Y sample 0 row dword offset within the
```

## Source note 170, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L342)

```text
//                             80x16-dword tile
```

## Source note 171, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L343)

```text
// system_temp_rov_params_.z = dword offset of the beginning of the row of
```

## Source note 172, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L344)

```text
//                             samples within a row of 32bpp tiles
```

## Source note 173, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L345)

```text
// system_temp_rov_params_.w = Y tile position
```

## Source note 174, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L349)

```text
// Get the dword offset of the beginning of the row of samples within a
```

## Source note 175, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L350)

```text
// 32bpp surface to system_temp_rov_params_.y (last time anything Y-related
```

## Source note 176, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L351)

```text
// is needed, as well as the sample row offset within the tile row).
```

## Source note 177, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L352)

```text
// system_temp_rov_params_.x = X sample 0 position within the tile
```

## Source note 178, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L353)

```text
// system_temp_rov_params_.y = dword offset of the beginning of the row of
```

## Source note 179, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L354)

```text
//                             samples within a 32bpp surface
```

## Source note 180, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L355)

```text
// system_temp_rov_params_.z = free
```

## Source note 181, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L356)

```text
// system_temp_rov_params_.w = free
```

## Source note 182, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L363)

```text
// Add the tile-local X to the depth offset in system_temp_rov_params_.y.
```

## Source note 183, line 364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L364)

```text
// system_temp_rov_params_.x = X sample 0 position within the tile
```

## Source note 184, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L365)

```text
// system_temp_rov_params_.y = dword sample 0 offset within a 32bpp surface
```

## Source note 185, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L369)

```text
// Flip the 40x16 half-tiles for depth / stencil as opposed to 32bpp color -
```

## Source note 186, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L370)

```text
// check in which half-tile the pixel is in to system_temp_rov_params_.x.
```

## Source note 187, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L371)

```text
// system_temp_rov_params_.x = free
```

## Source note 188, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L372)

```text
// system_temp_rov_params_.y = dword sample 0 offset within a 32bpp surface
```

## Source note 189, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L373)

```text
// system_temp_rov_params_.z = 0xFFFFFFFF if in the right half-tile, 0
```

## Source note 190, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L378)

```text
// Flip the 40x16 half-tiles for depth / stencil as opposed to 32bpp color -
```

## Source note 191, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L379)

```text
// get the dword offset to add for flipping to system_temp_rov_params_.x.
```

## Source note 192, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L380)

```text
// system_temp_rov_params_.x = depth half-tile flipping offset
```

## Source note 193, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L381)

```text
// system_temp_rov_params_.y = dword sample 0 offset within a 32bpp surface
```

## Source note 194, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L385)

```text
// Flip the 40x16 half-tiles for depth / stencil as opposed to 32bpp color -
```

## Source note 195, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L386)

```text
// get the final offset of the sample 0 within a 32bpp depth / stencil
```

## Source note 196, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L387)

```text
// surface to system_temp_rov_params_.y.
```

## Source note 197, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L388)

```text
// system_temp_rov_params_.x = free
```

## Source note 198, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L389)

```text
// system_temp_rov_params_.y = dword sample 0 offset within depth / stencil
```

## Source note 199, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L395)

```text
// Add the EDRAM base for depth/stencil.
```

## Source note 200, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L396)

```text
// system_temp_rov_params_.y = non-wrapped EDRAM depth / stencil address
```

## Source note 201, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L397)

```text
// system_temp_rov_params_.z = dword sample 0 offset within a 32bpp surface if
```

## Source note 202, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L399)

```text
// system_temp_rov_params_.w = dword sample 0 offset within a 64bpp surface if
```

## Source note 203, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L406)

```text
// Wrap EDRAM addressing for depth/stencil.
```

## Source note 204, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L407)

```text
// system_temp_rov_params_.y = EDRAM depth / stencil address
```

## Source note 205, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L408)

```text
// system_temp_rov_params_.z = dword sample 0 offset within a 32bpp surface if
```

## Source note 206, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L410)

```text
// system_temp_rov_params_.w = dword sample 0 offset within a 64bpp surface if
```

## Source note 207, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L417)

```text
// Sample coverage to system_temp_rov_params_.x.
```

## Source note 208, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L420)

```text
// Using ForcedSampleCount of 4 (2 is not supported on Nvidia), so for 2x
```

## Source note 209, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L421)

```text
// MSAA, handling samples 0 and 3 (upper-left and lower-right) as 0 and 1.
```

## Source note 210, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L423)

```text
// Check if 4x MSAA is enabled.
```

## Source note 211, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L427)

```text
// Copy the 4x AA coverage to system_temp_rov_params_.x. The guest sample
```

## Source note 212, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L428)

```text
// numbering matches Direct3D 10.1+, bit 0 horizontal and bit 1 vertical,
```

## Source note 213, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L429)

```text
// just like the canonical layout where the horizontal sample bit of a 4x
```

## Source note 214, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L430)

```text
// view selects the horizontally adjacent sample column pair.
```

## Source note 215, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L433)

```text
// Handle 1 or 2 samples.
```

## Source note 216, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L436)

```text
// Extract sample 3 coverage, which will be used as sample 1.
```

## Source note 217, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L439)

```text
// Combine coverage of samples 0 (in bit 0 of vCoverage) and 3 (in bit 0 of
```

## Source note 218, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L440)

```text
// system_temp_rov_params_.x).
```

## Source note 219, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L444)

```text
// Close the 4x MSAA conditional.
```

## Source note 220, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L459)

```text
// Check whether depth/stencil is enabled.
```

## Source note 221, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L460)

```text
// temp.x = kSysFlag_ROVDepthStencil
```

## Source note 222, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L462)

```text
// Open the depth/stencil enabled conditional.
```

## Source note 223, line 463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L463)

```text
// temp.x = free
```

## Source note 224, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L472)

```text
// Convert the shader-generated depth to 24-bit, using temp.x as
```

## Source note 225, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L473)

```text
// temporary. oDepth is already written by StoreResult with saturation,
```

## Source note 226, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L474)

```text
// no need to clamp here. Adreno 200 doesn't have PA_SC_VPORT_ZMIN/ZMAX,
```

## Source note 227, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L475)

```text
// so likely there's no need to clamp to the viewport depth bounds.
```

## Source note 228, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L479)

```text
// Get the derivatives of the screen-space (but not clamped to the viewport
```

## Source note 229, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L480)

```text
// depth bounds yet - this happens after the pixel shader in Direct3D 11+;
```

## Source note 230, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L481)

```text
// also linear within the triangle - thus constant derivatives along the
```

## Source note 231, line 482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L482)

```text
// triangle) Z for calculating per-sample depth values and the slope-scaled
```

## Source note 232, line 483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L483)

```text
// polygon offset.
```

## Source note 233, line 484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L484)

```text
// We're using derivatives instead of eval_sample_index for various reasons:
```

## Source note 234, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L485)

```text
// - eval_sample_index doesn't work with SV_Position - need to use an
```

## Source note 235, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L486)

```text
//   additional interpolant.
```

## Source note 236, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L487)

```text
// - On AMD, eval_sample_index is actually implemented via calculation and
```

## Source note 237, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L488)

```text
//   scaling of derivatives of barycentric coordinates, therefore there's no
```

## Source note 238, line 489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L489)

```text
//   advantage of using it there.
```

## Source note 239, line 490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L490)

```text
// - eval_sample_index is (inconsistently, but often) one of the sources of
```

## Source note 240, line 491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L491)

```text
//   the infamous AMD shader compiler crashes when ROV is used in Xenia, in
```

## Source note 241, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L492)

```text
//   addition to shader compiler crashes on WARP.
```

## Source note 242, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L496)

```text
// temp.x = ddx(z)
```

## Source note 243, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L497)

```text
// temp.y = ddy(z)
```

## Source note 244, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L502)

```text
// For late depth / stencil testing, derivatives are calculated in the
```

## Source note 245, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L503)

```text
// beginning of the shader before any return statement is possibly
```

## Source note 246, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L504)

```text
// reached, and written to system_temp_depth_stencil_.xy.
```

## Source note 247, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L509)

```text
// Get the maximum depth slope for polygon offset.
```

## Source note 248, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L510)

```text
// https://docs.microsoft.com/en-us/windows/desktop/direct3d9/depth-bias
```

## Source note 249, line 511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L511)

```text
// temp.x if early = ddx(z)
```

## Source note 250, line 512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L512)

```text
// temp.y if early = ddy(z)
```

## Source note 251, line 513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L513)

```text
// temp.z = max(|ddx(z)|, |ddy(z)|)
```

## Source note 252, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L515)

```text
// Calculate the depth bias for the needed faceness.
```

## Source note 253, line 518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L518)

```text
// temp.x if early = ddx(z)
```

## Source note 254, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L519)

```text
// temp.y if early = ddy(z)
```

## Source note 255, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L520)

```text
// temp.z = front face polygon offset
```

## Source note 256, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L521)

```text
// temp.w = free
```

## Source note 257, line 529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L529)

```text
// temp.x if early = ddx(z)
```

## Source note 258, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L530)

```text
// temp.y if early = ddy(z)
```

## Source note 259, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L531)

```text
// temp.z = back face polygon offset
```

## Source note 260, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L532)

```text
// temp.w = free
```

## Source note 261, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L540)

```text
// Apply the post-clip and post-viewport polygon offset to the fragment's
```

## Source note 262, line 541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L541)

```text
// depth. Not clamping yet as this is at the center, which is not
```

## Source note 263, line 542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L542)

```text
// necessarily covered and not necessarily inside the bounds - derivatives
```

## Source note 264, line 543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L543)

```text
// scaled by sample positions will be added to this value, and it must be
```

## Source note 265, line 544

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L544)

```text
// linear.
```

## Source note 266, line 545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L545)

```text
// temp.x if early = ddx(z)
```

## Source note 267, line 546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L546)

```text
// temp.y if early = ddy(z)
```

## Source note 268, line 547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L547)

```text
// temp.z = biased depth in the center
```

## Source note 269, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L553)

```text
// With early depth/stencil, depth/stencil writing may be deferred to the
```

## Source note 270, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L554)

```text
// end of the shader to prevent writing in case something (like alpha test,
```

## Source note 271, line 555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L555)

```text
// which is dynamic GPU state) discards the pixel. So, write directly to the
```

## Source note 272, line 556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L556)

```text
// persistent register, system_temp_depth_stencil_, instead of a local
```

## Source note 273, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L557)

```text
// temporary register.
```

## Source note 274, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L563)

```text
// Get if the current sample is covered.
```

## Source note 275, line 564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L564)

```text
// temp.x if no oDepth and early = ddx(z)
```

## Source note 276, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L565)

```text
// temp.y if no oDepth and early = ddy(z)
```

## Source note 277, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L566)

```text
// temp.z if no oDepth = biased depth in the center
```

## Source note 278, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L567)

```text
// temp.w = coverage of the current sample
```

## Source note 279, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L570)

```text
// Check if the current sample is covered.
```

## Source note 280, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L571)

```text
// temp.x if no oDepth and early = ddx(z)
```

## Source note 281, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L572)

```text
// temp.y if no oDepth and early = ddy(z)
```

## Source note 282, line 573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L573)

```text
// temp.z if no oDepth = biased depth in the center
```

## Source note 283, line 574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L574)

```text
// temp.w = free
```

## Source note 284, line 588

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L588)

```text
// Copy the 24-bit depth common to all samples to sample_depth_stencil.
```

## Source note 285, line 589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L589)

```text
// temp.w = shader-generated 24-bit depth
```

## Source note 286, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L594)

```text
// Adreno 200 doesn't have PA_SC_VPORT_ZMIN/ZMAX, so likely there's no
```

## Source note 287, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L595)

```text
// need to clamp to the viewport depth bounds, just to 0...1 - thus only
```

## Source note 288, line 596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L596)

```text
// saturating in the end of the per-sample depth calculation.
```

## Source note 289, line 599

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L599)

```text
// First sample - off-center for MSAA, in the center without it.
```

## Source note 290, line 600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L600)

```text
// Using ForcedSampleCount 4 for both 2x and 4x MSAA because
```

## Source note 291, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L601)

```text
// ForcedSampleCount 2 is not supported on Nvidia, thus the position
```

## Source note 292, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L602)

```text
// of the top-left sample (0 in Xenia) is always that of the top-left
```

## Source note 293, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L603)

```text
// sample of host 4x MSAA.
```

## Source note 294, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L604)

```text
// Calculate the depth in the sample 0 for 2x or 4x MSAA.
```

## Source note 295, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L605)

```text
// temp.x if early = ddx(z)
```

## Source note 296, line 606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L606)

```text
// temp.y if early = ddy(z)
```

## Source note 297, line 607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L607)

```text
// temp.z = biased depth in the center
```

## Source note 298, line 608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L608)

```text
// temp.w if late = unsaturated sample 0 depth at 4x MSAA
```

## Source note 299, line 615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L615)

```text
// Choose between the sample and the center depth depending on whether
```

## Source note 300, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L616)

```text
// at least 2x MSAA is enabled and saturate.
```

## Source note 301, line 617

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L617)

```text
// temp.x if early = ddx(z)
```

## Source note 302, line 618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L618)

```text
// temp.y if early = ddy(z)
```

## Source note 303, line 619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L619)

```text
// temp.z = biased depth in the center
```

## Source note 304, line 620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L620)

```text
// temp.w if late = sample 0 depth
```

## Source note 305, line 628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L628)

```text
// - 2x MSAA: Bottom sample -> bottom-right (3) with Direct3D 11's
```

## Source note 306, line 629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L629)

```text
//   ForcedSampleCount 4.
```

## Source note 307, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L630)

```text
// - 4x MSAA: Top-right guest sample (the horizontal sample bit is
```

## Source note 308, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L631)

```text
//   bit 0) -> Direct3D 11 sample 1.
```

## Source note 309, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L632)

```text
// Check if 4x MSAA is used.
```

## Source note 310, line 636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L636)

```text
// 4x MSAA.
```

## Source note 311, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L637)

```text
// temp.x if early = ddx(z)
```

## Source note 312, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L638)

```text
// temp.y if early = ddy(z)
```

## Source note 313, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L639)

```text
// temp.z = biased depth in the center
```

## Source note 314, line 640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L640)

```text
// temp.w if late = saturated sample 1 depth at 4x MSAA
```

## Source note 315, line 648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L648)

```text
// 2x MSAA as ForcedSampleCount 4 on the host.
```

## Source note 316, line 649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L649)

```text
// temp.x if early = ddx(z)
```

## Source note 317, line 650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L650)

```text
// temp.y if early = ddy(z)
```

## Source note 318, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L651)

```text
// temp.z = biased depth in the center
```

## Source note 319, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L652)

```text
// temp.w if late = saturated sample 1 depth at 2x MSAA
```

## Source note 320, line 662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L662)

```text
// Guest samples 2 and 3, bottom left and bottom right with the
```

## Source note 321, line 663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L663)

```text
// vertical sample bit being bit 1, map to Direct3D 11 samples 2
```

## Source note 322, line 664

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L664)

```text
// and 3.
```

## Source note 323, line 665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L665)

```text
// temp.x if early = ddx(z)
```

## Source note 324, line 666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L666)

```text
// temp.y if early = ddy(z)
```

## Source note 325, line 667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L667)

```text
// temp.z = biased depth in the center
```

## Source note 326, line 668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L668)

```text
// temp.w if late = saturated sample 2 or 3 depth
```

## Source note 327, line 677

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L677)

```text
// Convert the sample's depth to 24-bit, using sample_temp.x as a
```

## Source note 328, line 678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L678)

```text
// temporary.
```

## Source note 329, line 679

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L679)

```text
// temp.x if early = ddx(z)
```

## Source note 330, line 680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L680)

```text
// temp.y if early = ddy(z)
```

## Source note 331, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L681)

```text
// temp.z = biased depth in the center
```

## Source note 332, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L682)

```text
// temp.w if late = sample's 24-bit Z
```

## Source note 333, line 689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L689)

```text
// Load the old depth/stencil value.
```

## Source note 334, line 690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L690)

```text
// sample_temp.x = old depth/stencil
```

## Source note 335, line 698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L698)

```text
// Depth test.
```

## Source note 336, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L700)

```text
// Extract the old depth part to sample_depth_stencil.
```

## Source note 337, line 701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L701)

```text
// sample_temp.x = old depth/stencil
```

## Source note 338, line 702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L702)

```text
// sample_temp.y = old depth
```

## Source note 339, line 704

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L704)

```text
// Get the difference between the new and the old depth, > 0 - greater,
```

## Source note 340, line 705

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L705)

```text
// == 0 - equal, < 0 - less.
```

## Source note 341, line 706

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L706)

```text
// sample_temp.x = old depth/stencil
```

## Source note 342, line 707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L707)

```text
// sample_temp.y = old depth
```

## Source note 343, line 708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L708)

```text
// sample_temp.z = depth difference
```

## Source note 344, line 710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L710)

```text
// Check if the depth is "less" or "greater or equal".
```

## Source note 345, line 711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L711)

```text
// sample_temp.x = old depth/stencil
```

## Source note 346, line 712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L712)

```text
// sample_temp.y = old depth
```

## Source note 347, line 713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L713)

```text
// sample_temp.z = depth difference
```

## Source note 348, line 714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L714)

```text
// sample_temp.w = depth difference less than 0
```

## Source note 349, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L716)

```text
// Choose the passed depth function bits for "less" or for "greater".
```

## Source note 350, line 717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L717)

```text
// sample_temp.x = old depth/stencil
```

## Source note 351, line 718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L718)

```text
// sample_temp.y = old depth
```

## Source note 352, line 719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L719)

```text
// sample_temp.z = depth difference
```

## Source note 353, line 720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L720)

```text
// sample_temp.w = depth function passed bits for "less" or "greater"
```

## Source note 354, line 723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L723)

```text
// Do the "equal" testing.
```

## Source note 355, line 724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L724)

```text
// sample_temp.x = old depth/stencil
```

## Source note 356, line 725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L725)

```text
// sample_temp.y = old depth
```

## Source note 357, line 726

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L726)

```text
// sample_temp.z = depth function passed bits
```

## Source note 358, line 727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L727)

```text
// sample_temp.w = free
```

## Source note 359, line 730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L730)

```text
// Mask the resulting bits with the ones that should pass.
```

## Source note 360, line 731

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L731)

```text
// sample_temp.x = old depth/stencil
```

## Source note 361, line 732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L732)

```text
// sample_temp.y = old depth
```

## Source note 362, line 733

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L733)

```text
// sample_temp.z = masked depth function passed bits
```

## Source note 363, line 735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L735)

```text
// Check if depth test has passed.
```

## Source note 364, line 736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L736)

```text
// sample_temp.x = old depth/stencil
```

## Source note 365, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L737)

```text
// sample_temp.y = old depth
```

## Source note 366, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L738)

```text
// sample_temp.z = free
```

## Source note 367, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L741)

```text
// Extract the depth write flag.
```

## Source note 368, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L742)

```text
// sample_temp.x = old depth/stencil
```

## Source note 369, line 743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L743)

```text
// sample_temp.y = old depth
```

## Source note 370, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L744)

```text
// sample_temp.z = depth write mask
```

## Source note 371, line 747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L747)

```text
// If depth writing is disabled, don't change the depth.
```

## Source note 372, line 748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L748)

```text
// temp.x if no oDepth and early = ddx(z)
```

## Source note 373, line 749

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L749)

```text
// temp.y if no oDepth and early = ddy(z)
```

## Source note 374, line 750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L750)

```text
// temp.z if no oDepth = biased depth in the center
```

## Source note 375, line 751

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L751)

```text
// temp.w if late = resulting sample depth after the depth test
```

## Source note 376, line 752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L752)

```text
// sample_temp.x = old depth/stencil
```

## Source note 377, line 753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L753)

```text
// sample_temp.y = free
```

## Source note 378, line 754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L754)

```text
// sample_temp.z = free
```

## Source note 379, line 758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L758)

```text
// Depth test has failed.
```

## Source note 380, line 762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L762)

```text
// Remember for the ZFail ZPD counter. Stencil is tested after this and
```

## Source note 381, line 763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L763)

```text
// may move the sample to StencilFail instead.
```

## Source note 382, line 768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L768)

```text
// Exclude the bit from the covered sample mask.
```

## Source note 383, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L769)

```text
// sample_temp.x = old depth/stencil
```

## Source note 384, line 770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L770)

```text
// sample_temp.y = old depth
```

## Source note 385, line 776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L776)

```text
// Create packed depth/stencil, with the stencil value unchanged at this
```

## Source note 386, line 777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L777)

```text
// point.
```

## Source note 387, line 778

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L778)

```text
// temp.x if no oDepth and early = ddx(z)
```

## Source note 388, line 779

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L779)

```text
// temp.y if no oDepth and early = ddy(z)
```

## Source note 389, line 780

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L780)

```text
// temp.z if no oDepth = biased depth in the center
```

## Source note 390, line 781

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L781)

```text
// temp.w if late = resulting sample depth, current resulting stencil
```

## Source note 391, line 782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L782)

```text
// sample_temp.x = old depth/stencil
```

## Source note 392, line 786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L786)

```text
// Stencil test.
```

## Source note 393, line 788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L788)

```text
// Extract the stencil test bit.
```

## Source note 394, line 789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L789)

```text
// sample_temp.x = old depth/stencil
```

## Source note 395, line 790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L790)

```text
// sample_temp.y = stencil test enabled
```

## Source note 396, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L792)

```text
// Check if stencil test is enabled.
```

## Source note 397, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L793)

```text
// sample_temp.x = old depth/stencil
```

## Source note 398, line 794

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L794)

```text
// sample_temp.y = free
```

## Source note 399, line 797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L797)

```text
// Check the current face to get the reference and apply the read mask.
```

## Source note 400, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L802)

```text
// Go to the back face.
```

## Source note 401, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L810)

```text
// Read-mask the stencil reference.
```

## Source note 402, line 811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L811)

```text
// sample_temp.x = old depth/stencil
```

## Source note 403, line 812

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L812)

```text
// sample_temp.y = read-masked stencil reference
```

## Source note 404, line 819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L819)

```text
// Read-mask the old stencil value (also dropping the depth bits).
```

## Source note 405, line 820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L820)

```text
// sample_temp.x = old depth/stencil
```

## Source note 406, line 821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L821)

```text
// sample_temp.y = read-masked stencil reference
```

## Source note 407, line 822

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L822)

```text
// sample_temp.z = read-masked old stencil
```

## Source note 408, line 825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L825)

```text
// Close the face check.
```

## Source note 409, line 827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L827)

```text
// Get the difference between the stencil reference and the old stencil,
```

## Source note 410, line 828

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L828)

```text
// > 0 - greater, == 0 - equal, < 0 - less.
```

## Source note 411, line 829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L829)

```text
// sample_temp.x = old depth/stencil
```

## Source note 412, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L830)

```text
// sample_temp.y = stencil difference
```

## Source note 413, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L831)

```text
// sample_temp.z = free
```

## Source note 414, line 833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L833)

```text
// Check if the stencil is "less" or "greater or equal".
```

## Source note 415, line 834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L834)

```text
// sample_temp.x = old depth/stencil
```

## Source note 416, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L835)

```text
// sample_temp.y = stencil difference
```

## Source note 417, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L836)

```text
// sample_temp.z = stencil difference less than 0
```

## Source note 418, line 838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L838)

```text
// Choose the passed depth function bits for "less" or for "greater".
```

## Source note 419, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L839)

```text
// sample_temp.x = old depth/stencil
```

## Source note 420, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L840)

```text
// sample_temp.y = stencil difference
```

## Source note 421, line 841

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L841)

```text
// sample_temp.z = stencil function passed bits for "less" or "greater"
```

## Source note 422, line 845

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L845)

```text
// Do the "equal" testing.
```

## Source note 423, line 846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L846)

```text
// sample_temp.x = old depth/stencil
```

## Source note 424, line 847

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L847)

```text
// sample_temp.y = stencil function passed bits
```

## Source note 425, line 848

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L848)

```text
// sample_temp.z = free
```

## Source note 426, line 851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L851)

```text
// Get the comparison function and the operations for the current face.
```

## Source note 427, line 852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L852)

```text
// sample_temp.x = old depth/stencil
```

## Source note 428, line 853

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L853)

```text
// sample_temp.y = stencil function passed bits
```

## Source note 429, line 854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L854)

```text
// sample_temp.z = stencil function and operations
```

## Source note 430, line 864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L864)

```text
// Mask the resulting bits with the ones that should pass (the comparison
```

## Source note 431, line 865

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L865)

```text
// function is in the low 3 bits of the constant, and only ANDing 3-bit
```

## Source note 432, line 866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L866)

```text
// values with it, so safe not to UBFE the function).
```

## Source note 433, line 867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L867)

```text
// sample_temp.x = old depth/stencil
```

## Source note 434, line 868

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L868)

```text
// sample_temp.y = stencil test result
```

## Source note 435, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L869)

```text
// sample_temp.z = stencil function and operations
```

## Source note 436, line 871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L871)

```text
// Handle passing and failure of the stencil test, to choose the operation
```

## Source note 437, line 872

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L872)

```text
// and to discard the sample.
```

## Source note 438, line 873

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L873)

```text
// sample_temp.x = old depth/stencil
```

## Source note 439, line 874

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L874)

```text
// sample_temp.y = free
```

## Source note 440, line 875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L875)

```text
// sample_temp.z = stencil function and operations
```

## Source note 441, line 878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L878)

```text
// Check if depth test has passed for this sample (the sample will only
```

## Source note 442, line 879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L879)

```text
// be processed if it's covered, so the only thing that could unset the
```

## Source note 443, line 880

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L880)

```text
// bit at this point that matters is the depth test).
```

## Source note 444, line 881

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L881)

```text
// sample_temp.x = old depth/stencil
```

## Source note 445, line 882

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L882)

```text
// sample_temp.y = depth test result
```

## Source note 446, line 883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L883)

```text
// sample_temp.z = stencil function and operations
```

## Source note 447, line 886

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L886)

```text
// Choose the bit offset of the stencil operation.
```

## Source note 448, line 887

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L887)

```text
// sample_temp.x = old depth/stencil
```

## Source note 449, line 888

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L888)

```text
// sample_temp.y = sample operation offset
```

## Source note 450, line 889

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L889)

```text
// sample_temp.z = stencil function and operations
```

## Source note 451, line 891

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L891)

```text
// Extract the stencil operation.
```

## Source note 452, line 892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L892)

```text
// sample_temp.x = old depth/stencil
```

## Source note 453, line 893

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L893)

```text
// sample_temp.y = stencil operation
```

## Source note 454, line 894

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L894)

```text
// sample_temp.z = free
```

## Source note 455, line 897

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L897)

```text
// Stencil test has failed.
```

## Source note 456, line 900

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L900)

```text
// Extract the stencil fail operation.
```

## Source note 457, line 901

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L901)

```text
// sample_temp.x = old depth/stencil
```

## Source note 458, line 902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L902)

```text
// sample_temp.y = stencil operation
```

## Source note 459, line 903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L903)

```text
// sample_temp.z = free
```

## Source note 460, line 906

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L906)

```text
// Stencil failure takes precedence over depth failure.
```

## Source note 461, line 914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L914)

```text
// Exclude the bit from the covered sample mask.
```

## Source note 462, line 915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L915)

```text
// sample_temp.x = old depth/stencil
```

## Source note 463, line 916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L916)

```text
// sample_temp.y = stencil operation
```

## Source note 464, line 921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L921)

```text
// Close the stencil pass check.
```

## Source note 465, line 924

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L924)

```text
// Open the stencil operation switch for writing the new stencil (not
```

## Source note 466, line 925

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L925)

```text
// caring about bits 8:31).
```

## Source note 467, line 926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L926)

```text
// sample_temp.x = old depth/stencil
```

## Source note 468, line 927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L927)

```text
// sample_temp.y = will contain unmasked new stencil in 0:7 and junk above
```

## Source note 469, line 930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L930)

```text
// Zero.
```

## Source note 470, line 934

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L934)

```text
// Replace.
```

## Source note 471, line 946

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L946)

```text
// Increment and clamp.
```

## Source note 472, line 949

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L949)

```text
// Clear the upper bits for saturation.
```

## Source note 473, line 951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L951)

```text
// Increment.
```

## Source note 474, line 953

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L953)

```text
// Clamp.
```

## Source note 475, line 957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L957)

```text
// Decrement and clamp.
```

## Source note 476, line 960

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L960)

```text
// Clear the upper bits for saturation.
```

## Source note 477, line 962

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L962)

```text
// Increment.
```

## Source note 478, line 964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L964)

```text
// Clamp.
```

## Source note 479, line 968

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L968)

```text
// Invert.
```

## Source note 480, line 972

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L972)

```text
// Increment and wrap.
```

## Source note 481, line 976

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L976)

```text
// Decrement and wrap.
```

## Source note 482, line 980

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L980)

```text
// Keep.
```

## Source note 483, line 985

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L985)

```text
// Close the new stencil switch.
```

## Source note 484, line 988

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L988)

```text
// Select the stencil write mask for the face.
```

## Source note 485, line 989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L989)

```text
// sample_temp.x = old depth/stencil
```

## Source note 486, line 990

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L990)

```text
// sample_temp.y = unmasked new stencil in 0:7 and junk above
```

## Source note 487, line 991

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L991)

```text
// sample_temp.z = stencil write mask
```

## Source note 488, line 1001

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1001)

```text
// Apply the write mask to the new stencil, also dropping the upper 24
```

## Source note 489, line 1002

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1002)

```text
// bits.
```

## Source note 490, line 1003

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1003)

```text
// sample_temp.x = old depth/stencil
```

## Source note 491, line 1004

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1004)

```text
// sample_temp.y = masked new stencil
```

## Source note 492, line 1005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1005)

```text
// sample_temp.z = stencil write mask
```

## Source note 493, line 1007

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1007)

```text
// Invert the write mask for keeping the old stencil and the depth bits.
```

## Source note 494, line 1008

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1008)

```text
// sample_temp.x = old depth/stencil
```

## Source note 495, line 1009

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1009)

```text
// sample_temp.y = masked new stencil
```

## Source note 496, line 1010

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1010)

```text
// sample_temp.z = inverted stencil write mask
```

## Source note 497, line 1012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1012)

```text
// Remove the bits that will be replaced from the combined depth/stencil
```

## Source note 498, line 1013

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1013)

```text
// before inserting their new values.
```

## Source note 499, line 1014

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1014)

```text
// sample_temp.x = old depth/stencil
```

## Source note 500, line 1015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1015)

```text
// sample_temp.y = masked new stencil
```

## Source note 501, line 1016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1016)

```text
// sample_temp.z = free
```

## Source note 502, line 1017

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1017)

```text
// temp.x if no oDepth and early = ddx(z)
```

## Source note 503, line 1018

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1018)

```text
// temp.y if no oDepth and early = ddy(z)
```

## Source note 504, line 1019

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1019)

```text
// temp.z if no oDepth = biased depth in the center
```

## Source note 505, line 1020

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1020)

```text
// temp.w if late = resulting sample depth, inverse-write-masked old
```

## Source note 506, line 1023

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1023)

```text
// Merge the old and the new stencil.
```

## Source note 507, line 1024

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1024)

```text
// temp.x if no oDepth and early = ddx(z)
```

## Source note 508, line 1025

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1025)

```text
// temp.y if no oDepth and early = ddy(z)
```

## Source note 509, line 1026

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1026)

```text
// temp.z if no oDepth = biased depth in the center
```

## Source note 510, line 1027

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1027)

```text
// temp.w if late = resulting sample depth/stencil
```

## Source note 511, line 1028

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1028)

```text
// sample_temp.x = old depth/stencil
```

## Source note 512, line 1029

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1029)

```text
// sample_temp.y = free
```

## Source note 513, line 1032

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1032)

```text
// Close the stencil test check.
```

## Source note 514, line 1035

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1035)

```text
// Check if the depth/stencil has failed not to modify the depth if it has.
```

## Source note 515, line 1036

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1036)

```text
// sample_temp.x = old depth/stencil
```

## Source note 516, line 1037

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1037)

```text
// sample_temp.y = whether depth/stencil has passed for this sample
```

## Source note 517, line 1040

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1040)

```text
// If the depth/stencil test has failed, don't change the depth.
```

## Source note 518, line 1041

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1041)

```text
// sample_temp.x = old depth/stencil
```

## Source note 519, line 1042

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1042)

```text
// sample_temp.y = free
```

## Source note 520, line 1045

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1045)

```text
// Copy the new stencil over the old depth.
```

## Source note 521, line 1046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1046)

```text
// temp.x if no oDepth and early = ddx(z)
```

## Source note 522, line 1047

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1047)

```text
// temp.y if no oDepth and early = ddy(z)
```

## Source note 523, line 1048

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1048)

```text
// temp.z if no oDepth = biased depth in the center
```

## Source note 524, line 1049

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1049)

```text
// temp.w if late = resulting sample depth/stencil
```

## Source note 525, line 1053

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1053)

```text
// Close the depth/stencil passing check.
```

## Source note 526, line 1055

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1055)

```text
// Check if the new depth/stencil is different, and thus needs to be
```

## Source note 527, line 1056

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1056)

```text
// written.
```

## Source note 528, line 1057

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1057)

```text
// sample_temp.x = old depth/stencil
```

## Source note 529, line 1060

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1060)

```text
// Set the sample bit in bits 4:7 of system_temp_rov_params_.x - always
```

## Source note 530, line 1061

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1061)

```text
// need to write late in this shader, as it may do something like
```

## Source note 531, line 1062

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1062)

```text
// explicitly killing pixels.
```

## Source note 532, line 1067

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1067)

```text
// Check if need to write.
```

## Source note 533, line 1068

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1068)

```text
// sample_temp.x = free
```

## Source note 534, line 1072

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1072)

```text
// Get if early depth/stencil write is enabled.
```

## Source note 535, line 1073

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1073)

```text
// sample_temp.x = whether early depth/stencil write is enabled
```

## Source note 536, line 1076

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1076)

```text
// Check if need to write early.
```

## Source note 537, line 1077

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1077)

```text
// sample_temp.x = free
```

## Source note 538, line 1080

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1080)

```text
// Write the new depth/stencil.
```

## Source note 539, line 1088

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1088)

```text
// Need to still run the shader to know whether to write the
```

## Source note 540, line 1089

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1089)

```text
// depth/stencil value.
```

## Source note 541, line 1091

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1091)

```text
// Set the sample bit in bits 4:7 of system_temp_rov_params_.x if need
```

## Source note 542, line 1092

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1092)

```text
// to write later (after checking if the sample is not discarded by a
```

## Source note 543, line 1093

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1093)

```text
// kill instruction, alphatest or alpha-to-coverage).
```

## Source note 544, line 1097

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1097)

```text
// Close the early depth/stencil check.
```

## Source note 545, line 1101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1101)

```text
// Close the write check.
```

## Source note 546, line 1105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1105)

```text
// Release sample_temp.
```

## Source note 547, line 1108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1108)

```text
// Close the sample conditional.
```

## Source note 548, line 1111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1111)

```text
// Go to the next sample. The canonical layout puts the samples of a
```

## Source note 549, line 1112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1112)

```text
// pixel at +0, +(2*scale_x), +(2*scale_y rows) and +(2*scale_x +
```

## Source note 550, line 1113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1113)

```text
// 2*scale_y rows) dwords. So the deltas after each sample are
```

## Source note 551, line 1114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1114)

```text
// +(2*scale_x), +(2*scale_y rows - 2*scale_x), +(2*scale_x), and after
```

## Source note 552, line 1115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1115)

```text
// the last sample -(2*scale_x + 2*scale_y rows) to restore the sample 0
```

## Source note 553, line 1116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1116)

```text
// address.
```

## Source note 554, line 1137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1137)

```text
// Failed samples are counted here: with early depth/stencil, a quad
```

## Source note 555, line 1138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1138)

```text
// with no coverage left returns before the end of the shader.
```

## Source note 556, line 1142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1142)

```text
// Check if safe to discard the whole 2x2 quad early, without running the
```

## Source note 557, line 1143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1143)

```text
// translated pixel shader, by checking if coverage is 0 in all pixels in
```

## Source note 558, line 1144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1144)

```text
// the quad and if there are no samples which failed the depth test, but
```

## Source note 559, line 1145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1145)

```text
// where stencil was modified and needs to be written in the end. Must
```

## Source note 560, line 1146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1146)

```text
// reject at 2x2 quad granularity because texture fetches need derivatives.
```

## Source note 561, line 1148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1148)

```text
// temp.x = coverage | deferred depth/stencil write
```

## Source note 562, line 1151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1151)

```text
// temp.x = 1.0 if any sample is covered or potentially needs stencil write
```

## Source note 563, line 1152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1152)

```text
// in the end of the shader in the current pixel
```

## Source note 564, line 1155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1155)

```text
// temp.x = 1.0 if any sample is covered or potentially needs stencil write
```

## Source note 565, line 1156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1156)

```text
// in the end of the shader in the current pixel
```

## Source note 566, line 1157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1157)

```text
// temp.y = non-zero if anything is covered in the pixel across X
```

## Source note 567, line 1159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1159)

```text
// temp.x = 1.0 if anything is covered in the current half of the quad
```

## Source note 568, line 1160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1160)

```text
// temp.y = free
```

## Source note 569, line 1163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1163)

```text
// temp.x = 1.0 if anything is covered in the current half of the quad
```

## Source note 570, line 1164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1164)

```text
// temp.y = non-zero if anything is covered in the two pixels across Y
```

## Source note 571, line 1166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1166)

```text
// temp.x = 1.0 if anything is covered in the current whole quad
```

## Source note 572, line 1167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1167)

```text
// temp.y = free
```

## Source note 573, line 1170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1170)

```text
// End the shader if nothing is covered in the 2x2 quad after early
```

## Source note 574, line 1171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1171)

```text
// depth/stencil.
```

## Source note 575, line 1172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1172)

```text
// temp.x = free
```

## Source note 576, line 1176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1176)

```text
// Close the large depth/stencil conditional.
```

## Source note 577, line 1179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1179)

```text
// Release temp.
```

## Source note 578, line 1195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1195)

```text
// Break register dependencies and initialize if there are not enough
```

## Source note 579, line 1196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1196)

```text
// components. The rest of the function will write at least RG (k_32_FLOAT and
```

## Source note 580, line 1197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1197)

```text
// k_32_32_FLOAT handled with the same default label), and if packed_temp is
```

## Source note 581, line 1198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1198)

```text
// the same as color_temp, the packed color won't be touched.
```

## Source note 582, line 1201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1201)

```text
// Choose the packing based on the render target's format.
```

## Source note 583, line 1208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1208)

```text
// k_8_8_8_8
```

## Source note 584, line 1209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1209)

```text
// k_8_8_8_8_GAMMA
```

## Source note 585, line 1215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1215)

```text
// Unpack the components.
```

## Source note 586, line 1218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1218)

```text
// Convert from fixed-point.
```

## Source note 587, line 1220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1220)

```text
// Normalize.
```

## Source note 588, line 1232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1232)

```text
// k_2_10_10_10
```

## Source note 589, line 1233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1233)

```text
// k_2_10_10_10_AS_10_10_10_10
```

## Source note 590, line 1240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1240)

```text
// Unpack the components.
```

## Source note 591, line 1243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1243)

```text
// Convert from fixed-point.
```

## Source note 592, line 1245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1245)

```text
// Normalize.
```

## Source note 593, line 1252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1252)

```text
// k_2_10_10_10_FLOAT
```

## Source note 594, line 1253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1253)

```text
// k_2_10_10_10_FLOAT_AS_16_16_16_16
```

## Source note 595, line 1254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1254)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 596, line 1261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1261)

```text
// Unpack the alpha.
```

## Source note 597, line 1264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1264)

```text
// Convert the alpha from fixed-point.
```

## Source note 598, line 1266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1266)

```text
// Normalize the alpha.
```

## Source note 599, line 1269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1269)

```text
// Process the components in reverse order because color_temp.r stores the
```

## Source note 600, line 1270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1270)

```text
// packed color which shouldn't be touched until G and B are converted if
```

## Source note 601, line 1271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1271)

```text
// packed_temp and color_temp are the same.
```

## Source note 602, line 1280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1280)

```text
// k_16_16
```

## Source note 603, line 1281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1281)

```text
// k_16_16_16_16 (64bpp)
```

## Source note 604, line 1288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1288)

```text
// Unpack the components.
```

## Source note 605, line 1291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1291)

```text
// Convert from fixed-point.
```

## Source note 606, line 1293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1293)

```text
// Normalize.
```

## Source note 607, line 1299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1299)

```text
// k_16_16_FLOAT
```

## Source note 608, line 1300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1300)

```text
// k_16_16_16_16_FLOAT (64bpp)
```

## Source note 609, line 1307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1307)

```text
// Unpack the components.
```

## Source note 610, line 1310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1310)

```text
// Convert from 16-bit float.
```

## Source note 611, line 1316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1316)

```text
// Assume k_32_FLOAT or k_32_32_FLOAT for the rest.
```

## Source note 612, line 1331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1331)

```text
// Packing normalized formats according to the Direct3D 11.3 functional
```

## Source note 613, line 1332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1332)

```text
// specification, but assuming clamping was done by the caller.
```

## Source note 614, line 1343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1343)

```text
// Break register dependency after 32bpp cases.
```

## Source note 615, line 1346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1346)

```text
// Choose the packing based on the render target's format.
```

## Source note 616, line 1353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1353)

```text
// k_8_8_8_8
```

## Source note 617, line 1354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1354)

```text
// k_8_8_8_8_GAMMA
```

## Source note 618, line 1364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1364)

```text
// Denormalize and add 0.5 for rounding.
```

## Source note 619, line 1367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1367)

```text
// Denormalize and add 0.5 for rounding.
```

## Source note 620, line 1371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1371)

```text
// Convert to fixed-point.
```

## Source note 621, line 1373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1373)

```text
// Pack the upper components.
```

## Source note 622, line 1383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1383)

```text
// k_2_10_10_10
```

## Source note 623, line 1384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1384)

```text
// k_2_10_10_10_AS_10_10_10_10
```

## Source note 624, line 1391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1391)

```text
// Denormalize and convert to fixed-point.
```

## Source note 625, line 1395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1395)

```text
// Pack the upper components.
```

## Source note 626, line 1404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1404)

```text
// k_2_10_10_10_FLOAT
```

## Source note 627, line 1405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1405)

```text
// k_2_10_10_10_FLOAT_AS_16_16_16_16
```

## Source note 628, line 1406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1406)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 629, line 1413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1413)

```text
// Convert red directly to the destination, which may be the same as the
```

## Source note 630, line 1414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1414)

```text
// source, but PreClampedFloat32To7e3 allows that.
```

## Source note 631, line 1418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1418)

```text
// Convert green and blue to a temporary register and insert them into the
```

## Source note 632, line 1419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1419)

```text
// result.
```

## Source note 633, line 1424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1424)

```text
// Denormalize the alpha and convert it to fixed-point.
```

## Source note 634, line 1428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1428)

```text
// Pack the alpha.
```

## Source note 635, line 1434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1434)

```text
// k_16_16
```

## Source note 636, line 1435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1435)

```text
// k_16_16_16_16 (64bpp)
```

## Source note 637, line 1442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1442)

```text
// Denormalize and convert to fixed-point, making 0.5 with the proper sign
```

## Source note 638, line 1443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1443)

```text
// in temp2.
```

## Source note 639, line 1450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1450)

```text
// Convert to fixed-point.
```

## Source note 640, line 1452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1452)

```text
// Pack green or alpha.
```

## Source note 641, line 1462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1462)

```text
// k_16_16_FLOAT
```

## Source note 642, line 1463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1463)

```text
// k_16_16_16_16_FLOAT (64bpp)
```

## Source note 643, line 1472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1472)

```text
// Convert to 16-bit float.
```

## Source note 644, line 1474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1474)

```text
// Pack green or alpha.
```

## Source note 645, line 1484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1484)

```text
// Assume k_32_FLOAT or k_32_32_FLOAT for the rest.
```

## Source note 646, line 1499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1499)

```text
// kOne.
```

## Source note 647, line 1548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1548)

```text
// Factors involving the constant.
```

## Source note 648, line 1585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1585)

```text
// kZero default.
```

## Source note 649, line 1597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1597)

```text
// kOne, kSrcAlphaSaturate.
```

## Source note 650, line 1603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1603)

```text
// kSrcColor, kSrcAlpha.
```

## Source note 651, line 1611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1611)

```text
// kOneMinusSrcColor, kOneMinusSrcAlpha.
```

## Source note 652, line 1617

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1617)

```text
// kDstColor, kDstAlpha.
```

## Source note 653, line 1625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1625)

```text
// kOneMinusDstColor, kOneMinusDstAlpha.
```

## Source note 654, line 1631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1631)

```text
// Factors involving the constant.
```

## Source note 655, line 1633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1633)

```text
// kConstantColor, kConstantAlpha.
```

## Source note 656, line 1641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1641)

```text
// kOneMinusConstantColor, kOneMinusConstantAlpha.
```

## Source note 657, line 1649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1649)

```text
// kZero default.
```

## Source note 658, line 1667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1667)

```text
// Apply the exponent bias after alpha to coverage because it needs the
```

## Source note 659, line 1668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1668)

```text
// unbiased alpha from the shader.
```

## Source note 660, line 1674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1674)

```text
// Convert to gamma space - this is incorrect, since it must be done after
```

## Source note 661, line 1675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1675)

```text
// blending on the Xbox 360, but this is just one of many blending issues
```

## Source note 662, line 1676

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1676)

```text
// in the RTV path.
```

## Source note 663, line 1680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1680)

```text
// Saturate before the gamma conversion.
```

## Source note 664, line 1688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1688)

```text
// Copy the color from a readable temp register to an output register.
```

## Source note 665, line 1691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1691)

```text
// Release gamma_temp.
```

## Source note 666, line 1700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1700)

```text
// If not converting, but the shader writes depth explicitly, for float24,
```

## Source note 667, line 1701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1701)

```text
// need to scale it from guest 0...1 to host 0...0.5 to support
```

## Source note 668, line 1702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1702)

```text
// reinterpretation round trips as viewport scaling doesn't apply to
```

## Source note 669, line 1703

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1703)

```text
// oDepth.
```

## Source note 670, line 1710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1710)

```text
// Write the depth from the temporary to the system depth output.
```

## Source note 671, line 1718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1718)

```text
// The depth is already written to system_temp_depth_stencil_.x and clamped
```

## Source note 672, line 1719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1719)

```text
// to 0...1 with NaNs dropped (saturating in StoreResult); yzw are free.
```

## Source note 673, line 1722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1722)

```text
// Need a temporary variable; remap the sample's depth input from host
```

## Source note 674, line 1723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1723)

```text
// 0...0.5 back to guest 0...1 for conversion purposes to it and saturate it
```

## Source note 675, line 1724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1724)

```text
// (in Direct3D 11, depth is clamped to the viewport bounds after the pixel
```

## Source note 676, line 1725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1725)

```text
// shader, and SV_Position.z contains the unclamped depth, which may be
```

## Source note 677, line 1726

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1726)

```text
// outside the viewport's depth range if it's biased); though it will be
```

## Source note 678, line 1727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1727)

```text
// clamped to the viewport bounds anyway, but to be able to make the
```

## Source note 679, line 1728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1728)

```text
// assumption of it being clamped while working with the bit representation.
```

## Source note 680, line 1742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1742)

```text
// Simplified conversion, always less than or equal to the original value -
```

## Source note 681, line 1743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1743)

```text
// just drop the lower bits.
```

## Source note 682, line 1744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1744)

```text
// The float32 exponent bias is 127.
```

## Source note 683, line 1745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1745)

```text
// After saturating, the exponent range is -127...0.
```

## Source note 684, line 1746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1746)

```text
// The smallest normalized 20e4 exponent is -14 - should drop 3 mantissa
```

## Source note 685, line 1747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1747)

```text
// bits at -14 or above.
```

## Source note 686, line 1748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1748)

```text
// The smallest denormalized 20e4 number is -34 - should drop 23 mantissa
```

## Source note 687, line 1749

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1749)

```text
// bits at -34.
```

## Source note 688, line 1750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1750)

```text
// Anything smaller than 2^-34 becomes 0.
```

## Source note 689, line 1752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1752)

```text
// Check if the number is representable as a float24 after truncation - the
```

## Source note 690, line 1753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1753)

```text
// exponent is at least -34.
```

## Source note 691, line 1757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1757)

```text
// Extract the biased float32 exponent to temp.y.
```

## Source note 692, line 1758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1758)

```text
// temp.y = 113+ at exponent -14+.
```

## Source note 693, line 1759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1759)

```text
// temp.y = 93 at exponent -34.
```

## Source note 694, line 1761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1761)

```text
// Convert exponent to the unclamped number of bits to truncate.
```

## Source note 695, line 1762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1762)

```text
// 116 - 113 = 3.
```

## Source note 696, line 1763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1763)

```text
// 116 - 93 = 23.
```

## Source note 697, line 1764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1764)

```text
// temp.y = 3+ at exponent -14+.
```

## Source note 698, line 1765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1765)

```text
// temp.y = 23 at exponent -34.
```

## Source note 699, line 1767

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1767)

```text
// Clamp the truncated bit count to drop 3 bits of any normal number.
```

## Source note 700, line 1768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1768)

```text
// Exponents below -34 are handled separately.
```

## Source note 701, line 1769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1769)

```text
// temp.y = 3 at exponent -14.
```

## Source note 702, line 1770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1770)

```text
// temp.y = 23 at exponent -34.
```

## Source note 703, line 1772

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1772)

```text
// Truncate the mantissa - fill the low bits with zeros.
```

## Source note 704, line 1773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1773)

```text
// temp.x = result in 0...1 range
```

## Source note 705, line 1775

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1775)

```text
// Remap from guest 0...1 to host 0...0.5.
```

## Source note 706, line 1778

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1778)

```text
// The number is not representable as float24 after truncation - zero.
```

## Source note 707, line 1781

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1781)

```text
// Close the non-zero result check.
```

## Source note 708, line 1784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1784)

```text
// Properly convert to 20e4, with rounding to the nearest even (the bias was
```

## Source note 709, line 1785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1785)

```text
// pre-applied by multiplying by 2), then convert back restoring the bias.
```

## Source note 710, line 1791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1791)

```text
// Release temp.
```

## Source note 711, line 1802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1802)

```text
// Calculate the threshold.
```

## Source note 712, line 1805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1805)

```text
// Check if alpha of oC0 is at or greater than the threshold (handling NaN
```

## Source note 713, line 1806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1806)

```text
// according to the Direct3D 11.3 functional specification, as not covered).
```

## Source note 714, line 1812

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1812)

```text
// Keep all bits in but the ones that need to be removed in case of failure.
```

## Source note 715, line 1813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1813)

```text
// For ROV, the test must effect not only the coverage bits, but also the
```

## Source note 716, line 1814

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1814)

```text
// deferred depth/stencil write bits since the coverage is zeroed for
```

## Source note 717, line 1815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1815)

```text
// samples that have failed the depth/stencil test, but stencil may still
```

## Source note 718, line 1816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1816)

```text
// require writing - but if the sample is discarded by alpha to coverage, it
```

## Source note 719, line 1817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1817)

```text
// must not be written at all.
```

## Source note 720, line 1819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1819)

```text
// Clear the coverage for samples that have failed the test.
```

## Source note 721, line 1823

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1823)

```text
// First sample tested - initialize.
```

## Source note 722, line 1827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1827)

```text
// Not first sample tested - add.
```

## Source note 723, line 1835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1835)

```text
// Check if alpha to coverage can be done at all in this shader.
```

## Source note 724, line 1841

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1841)

```text
// Initialize the output coverage for the case if alpha to mask is not
```

## Source note 725, line 1842

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1842)

```text
// enabled - it needs to be written on every execution path.
```

## Source note 726, line 1846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1846)

```text
// Check if alpha to coverage is enabled.
```

## Source note 727, line 1856

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1856)

```text
// Get the dithering threshold offset index for the pixel, Y - low bit of
```

## Source note 728, line 1857

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1857)

```text
// offset index, X - high bit, and extract the offset and convert it to
```

## Source note 729, line 1858

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1858)

```text
// floating-point. With resolution scaling, still using host pixels, to
```

## Source note 730, line 1859

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1859)

```text
// preserve the idea of dithering.
```

## Source note 731, line 1860

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1860)

```text
// temp.x = alpha to coverage offset as float 0.0...3.0.
```

## Source note 732, line 1870

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1870)

```text
// Write the result to temp.z for RTV or to system_temp_rov_params_.x for ROV.
```

## Source note 733, line 1871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1871)

```text
// temp.x = alpha to coverage offset as float 0.0...3.0.
```

## Source note 734, line 1872

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1872)

```text
// temp.z = without ROV, accumulated coverage.
```

## Source note 735, line 1876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1876)

```text
// Check if MSAA is enabled.
```

## Source note 736, line 1880

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1880)

```text
// Check if MSAA is 4x or 2x.
```

## Source note 737, line 1884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1884)

```text
// 4x MSAA.
```

## Source note 738, line 1885

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1885)

```text
// Sample 0 must be checked first - CompletePixelShader_AlphaToMaskSample
```

## Source note 739, line 1886

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1886)

```text
// initializes the result for sample index 0.
```

## Source note 740, line 1895

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1895)

```text
// 2x MSAA.
```

## Source note 741, line 1896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1896)

```text
// With ROV, using guest sample indices.
```

## Source note 742, line 1897

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1897)

```text
// Without ROV:
```

## Source note 743, line 1898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1898)

```text
// - Native 2x: top (0 in Xenia) is 1 in D3D10.1+, bottom (1 in Xenia) is 0.
```

## Source note 744, line 1899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1899)

```text
// - 2x as 4x: top is 0, bottom is 3.
```

## Source note 745, line 1907

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1907)

```text
// Close the 4x check.
```

## Source note 746, line 1910

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1910)

```text
// MSAA is disabled.
```

## Source note 747, line 1914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1914)

```text
// Close the 2x/4x check.
```

## Source note 748, line 1917

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1917)

```text
// Check if any sample is still covered and return to avoid unneeded work (the
```

## Source note 749, line 1918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1918)

```text
// driver's shader compiler may place return after a discard, but it will
```

## Source note 750, line 1919

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1919)

```text
// likely not place one during SV_Coverage assignment - that's what the AMD
```

## Source note 751, line 1920

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1920)

```text
// compiler does, at least). Then, if needed, write the coverage value.
```

## Source note 752, line 1922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1922)

```text
// The mask includes both 0:3 and 4:7 parts because there may be samples
```

## Source note 753, line 1923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1923)

```text
// which passed alpha to coverage, but not stencil test, and the stencil
```

## Source note 754, line 1924

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1924)

```text
// buffer needs to be modified - in this case, samples would be dropped in
```

## Source note 755, line 1925

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1925)

```text
// 0:3, but not in 4:7).
```

## Source note 756, line 1939

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1939)

```text
// Release temp.
```

## Source note 757, line 1942

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1942)

```text
// Close the alpha to coverage check.
```

## Source note 758, line 1966

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1966)

```text
// UINT32_MAX: no occlusion query is open for this draw.
```

## Source note 759, line 1970

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1970)

```text
// The counter UAV is raw, so address it in bytes: four uint32 lanes per
```

## Source note 760, line 1971

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1971)

```text
// slot.
```

## Source note 761, line 1988

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1988)

```text
// A VIZ survey's consumer only needs zero or not, so a plain store of 1
```

## Source note 762, line 1989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L1989)

```text
// replaces the atomic add.
```

## Source note 763, line 2005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2005)

```text
// Bits 0:3 are the surviving coverage; 4:7 are deferred depth/stencil
```

## Source note 764, line 2006

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2006)

```text
// writes and don't count.
```

## Source note 765, line 2033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2033)

```text
// Do late depth/stencil test (which includes writing) if needed or deferred
```

## Source note 766, line 2034

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2034)

```text
// depth writing.
```

## Source note 767, line 2036

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2036)

```text
// Write modified depth/stencil.
```

## Source note 768, line 2038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2038)

```text
// Get if need to write to temp.x.
```

## Source note 769, line 2039

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2039)

```text
// temp.x = whether the depth sample needs to be written.
```

## Source note 770, line 2042

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2042)

```text
// Check if need to write.
```

## Source note 771, line 2043

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2043)

```text
// temp.x = free.
```

## Source note 772, line 2046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2046)

```text
// Write the new depth/stencil.
```

## Source note 773, line 2054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2054)

```text
// Close the write check.
```

## Source note 774, line 2056

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2056)

```text
// Go to the next sample, with the same deltas as in the depth sample
```

## Source note 775, line 2057

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2057)

```text
// loop above, just without restoring the sample 0 address at the end.
```

## Source note 776, line 2071

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2071)

```text
// system_temp_rov_params_.y (the depth / stencil sample address) is not
```

## Source note 777, line 2072

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2072)

```text
// needed anymore, can be used for color writing.
```

## Source note 778, line 2077

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2077)

```text
// Check if any sample is still covered after depth testing and writing,
```

## Source note 779, line 2078

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2078)

```text
// skip color writing completely in this case.
```

## Source note 780, line 2079

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2079)

```text
// temp.x = whether any sample is still covered.
```

## Source note 781, line 2082

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2082)

```text
// temp.x = free.
```

## Source note 782, line 2086

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2086)

```text
// Write color values.
```

## Source note 783, line 2095

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2095)

```text
// This includes a swizzle to choose XY for even render targets or ZW for
```

## Source note 784, line 2096

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2096)

```text
// odd ones - use SelectFromSwizzled and SwizzleSwizzled.
```

## Source note 785, line 2101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2101)

```text
// Check if color writing is disabled - special keep mask constant case,
```

## Source note 786, line 2102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2102)

```text
// both 32bpp parts are forced UINT32_MAX, but also check whether the shader
```

## Source note 787, line 2103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2103)

```text
// has written anything to this target at all.
```

## Source note 788, line 2105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2105)

```text
// Combine both parts of the keep mask to check if both are 0xFFFFFFFF.
```

## Source note 789, line 2106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2106)

```text
// temp.x = whether all bits need to be kept.
```

## Source note 790, line 2108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2108)

```text
// Flip the bits so both UINT32_MAX would result in 0 - not writing.
```

## Source note 791, line 2109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2109)

```text
// temp.x = whether any bits need to be written.
```

## Source note 792, line 2111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2111)

```text
// Get the bits that will be used for checking wherther the render target
```

## Source note 793, line 2112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2112)

```text
// has been written to on the taken execution path - if the write mask is
```

## Source note 794, line 2113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2113)

```text
// empty, AND zero with the test bit to always get zero.
```

## Source note 795, line 2114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2114)

```text
// temp.x = bits for checking whether the render target has been written to.
```

## Source note 796, line 2117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2117)

```text
// Check if the render target was written to on the execution path.
```

## Source note 797, line 2118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2118)

```text
// temp.x = whether anything was written and needs to be stored.
```

## Source note 798, line 2120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2120)

```text
// Check if need to write anything to the render target.
```

## Source note 799, line 2121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2121)

```text
// temp.x = free.
```

## Source note 800, line 2124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2124)

```text
// Apply the exponent bias after alpha to coverage because it needs the
```

## Source note 801, line 2125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2125)

```text
// unbiased alpha from the shader.
```

## Source note 802, line 2135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2135)

```text
// Load whether the render target is 64bpp to system_temp_rov_params_.y to
```

## Source note 803, line 2136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2136)

```text
// get the needed relative sample address.
```

## Source note 804, line 2139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2139)

```text
// Choose the relative sample address for the render target to
```

## Source note 805, line 2140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2140)

```text
// system_temp_rov_params_.y.
```

## Source note 806, line 2145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2145)

```text
// Add the EDRAM base of the render target to system_temp_rov_params_.y.
```

## Source note 807, line 2152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2152)

```text
// Wrap EDRAM addressing for the color render target to get the final sample
```

## Source note 808, line 2153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2153)

```text
// address in the EDRAM to system_temp_rov_params_.y.
```

## Source note 809, line 2165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2165)

```text
// Get if not blending to pack the color once for all 4 samples.
```

## Source note 810, line 2166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2166)

```text
// temp.x = whether blending is disabled.
```

## Source note 811, line 2168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2168)

```text
// Check if not blending.
```

## Source note 812, line 2169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2169)

```text
// temp.x = free.
```

## Source note 813, line 2172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2172)

```text
// Clamp the color to the render target's representable range - will be
```

## Source note 814, line 2173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2173)

```text
// packed.
```

## Source note 815, line 2178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2178)

```text
// Pack the color once if blending.
```

## Source note 816, line 2179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2179)

```text
// temp.xy = packed color.
```

## Source note 817, line 2182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2182)

```text
// Blending is enabled.
```

## Source note 818, line 2185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2185)

```text
// Get if the blending source color is fixed-point for clamping if it is.
```

## Source note 819, line 2186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2186)

```text
// temp.x = whether color is fixed-point.
```

## Source note 820, line 2189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2189)

```text
// Check if the blending source color is fixed-point and needs clamping.
```

## Source note 821, line 2190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2190)

```text
// temp.x = free.
```

## Source note 822, line 2193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2193)

```text
// Clamp the blending source color if needed.
```

## Source note 823, line 2199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2199)

```text
// Close the fixed-point color check.
```

## Source note 824, line 2202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2202)

```text
// Get if the blending source alpha is fixed-point for clamping if it is.
```

## Source note 825, line 2203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2203)

```text
// temp.x = whether alpha is fixed-point.
```

## Source note 826, line 2206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2206)

```text
// Check if the blending source alpha is fixed-point and needs clamping.
```

## Source note 827, line 2207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2207)

```text
// temp.x = free.
```

## Source note 828, line 2210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2210)

```text
// Clamp the blending source alpha if needed.
```

## Source note 829, line 2218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2218)

```text
// Close the fixed-point alpha check.
```

## Source note 830, line 2220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2220)

```text
// Break register dependency in the color sample raster operation.
```

## Source note 831, line 2221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2221)

```text
// temp.xy = 0 instead of packed color.
```

## Source note 832, line 2226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2226)

```text
// Blend, mask and write all samples.
```

## Source note 833, line 2228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2228)

```text
// Get if the sample is covered.
```

## Source note 834, line 2229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2229)

```text
// temp.z = whether the sample is covered.
```

## Source note 835, line 2233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2233)

```text
// Check if the sample is covered.
```

## Source note 836, line 2234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2234)

```text
// temp.z = free.
```

## Source note 837, line 2237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2237)

```text
// Only temp.xy are used at this point (containing the packed color from
```

## Source note 838, line 2238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2238)

```text
// the shader if not blending).
```

## Source note 839, line 2241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2241)

```text
// Color sample raster operation.
```

## Source note 840, line 2245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2245)

```text
// Checking if color loading must be done - if any component needs to be
```

## Source note 841, line 2246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2246)

```text
// kept or if blending is enabled.
```

## Source note 842, line 2249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2249)

```text
// Get if need to keep any components to temp.z.
```

## Source note 843, line 2250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2250)

```text
// temp.z = whether any components must be kept (OR of keep masks).
```

## Source note 844, line 2253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2253)

```text
// Blending isn't done if it's 1 * source + 0 * destination. But since the
```

## Source note 845, line 2254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2254)

```text
// previous color also needs to be loaded if any original components need
```

## Source note 846, line 2255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2255)

```text
// to be kept, force the blend control to something with blending in this
```

## Source note 847, line 2256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2256)

```text
// case in temp.z.
```

## Source note 848, line 2257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2257)

```text
// temp.z = blending mode used to check if need to load.
```

## Source note 849, line 2259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2259)

```text
// Get if the blend control register requires loading the color to temp.z.
```

## Source note 850, line 2260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2260)

```text
// temp.z = whether need to load the color.
```

## Source note 851, line 2262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2262)

```text
// Check if need to do something with the previous color.
```

## Source note 852, line 2263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2263)

```text
// temp.z = free.
```

## Source note 853, line 2267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2267)

```text
// Loading the previous color to temp.zw.
```

## Source note 854, line 2270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2270)

```text
// Load the 32bpp color, or the lower 32 bits of the 64bpp color, to
```

## Source note 855, line 2271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2271)

```text
// temp.z.
```

## Source note 856, line 2272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2272)

```text
// temp.z = 32-bit packed color or lower 32 bits of the packed color.
```

## Source note 857, line 2279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2279)

```text
// Get if the format is 64bpp to temp.w.
```

## Source note 858, line 2280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2280)

```text
// temp.w = whether the render target is 64bpp.
```

## Source note 859, line 2283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2283)

```text
// Check if the format is 64bpp.
```

## Source note 860, line 2284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2284)

```text
// temp.w = free.
```

## Source note 861, line 2287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2287)

```text
// Get the address of the upper 32 bits of the color to temp.w.
```

## Source note 862, line 2288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2288)

```text
// temp.w = address of the upper 32 bits of the packed color.
```

## Source note 863, line 2291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2291)

```text
// Load the upper 32 bits of the 64bpp color to temp.w.
```

## Source note 864, line 2292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2292)

```text
// temp.zw = packed destination color/alpha.
```

## Source note 865, line 2300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2300)

```text
// The color is 32bpp.
```

## Source note 866, line 2303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2303)

```text
// Break register dependency in temp.w if the color is 32bpp.
```

## Source note 867, line 2304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2304)

```text
// temp.zw = packed destination color/alpha.
```

## Source note 868, line 2307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2307)

```text
// Close the color format check.
```

## Source note 869, line 2316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2316)

```text
// Get if blending is enabled to color_temp.x.
```

## Source note 870, line 2317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2317)

```text
// color_temp.x = whether blending is enabled.
```

## Source note 871, line 2320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2320)

```text
// Check if need to blend.
```

## Source note 872, line 2321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2321)

```text
// color_temp.x = free.
```

## Source note 873, line 2324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2324)

```text
// Now, when blending is enabled, temp.xy are used as scratch since
```

## Source note 874, line 2325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2325)

```text
// the color is packed after blending.
```

## Source note 875, line 2327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2327)

```text
// Unpack the destination color to color_temp, using temp.xy as temps.
```

## Source note 876, line 2328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2328)

```text
// The destination color never needs clamping because out-of-range
```

## Source note 877, line 2329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2329)

```text
// values can't be loaded.
```

## Source note 878, line 2330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2330)

```text
// color_temp.xyzw = destination color/alpha.
```

## Source note 879, line 2334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2334)

```text
// Color blending.
```

## Source note 880, line 2337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2337)

```text
// Extract the color min/max bit to temp.x.
```

## Source note 881, line 2338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2338)

```text
// temp.x = whether min/max should be used for color.
```

## Source note 882, line 2340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2340)

```text
// Check if need to do blend the color with factors.
```

## Source note 883, line 2341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2341)

```text
// temp.x = free.
```

## Source note 884, line 2348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2348)

```text
// Extract the source color factor to temp.x.
```

## Source note 885, line 2349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2349)

```text
// temp.x = source color factor index.
```

## Source note 886, line 2351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2351)

```text
// Check if the source color factor is not zero - if it is, the
```

## Source note 887, line 2352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2352)

```text
// source must be ignored completely, and Infinity and NaN in it
```

## Source note 888, line 2353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2353)

```text
// shouldn't affect blending.
```

## Source note 889, line 2356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2356)

```text
// Open the switch for choosing the source color blend factor.
```

## Source note 890, line 2357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2357)

```text
// temp.x = free.
```

## Source note 891, line 2359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2359)

```text
// Write the source color factor to blend_src_temp.xyz.
```

## Source note 892, line 2360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2360)

```text
// blend_src_temp.xyz = unclamped source color factor.
```

## Source note 893, line 2362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2362)

```text
// Close the source color factor switch.
```

## Source note 894, line 2364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2364)

```text
// Get if the render target color is fixed-point and the source
```

## Source note 895, line 2365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2365)

```text
// color factor needs clamping to temp.x.
```

## Source note 896, line 2366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2366)

```text
// temp.x = whether color is fixed-point.
```

## Source note 897, line 2369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2369)

```text
// Check if the source color factor needs clamping.
```

## Source note 898, line 2372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2372)

```text
// Clamp the source color factor in blend_src_temp.xyz.
```

## Source note 899, line 2373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2373)

```text
// blend_src_temp.xyz = source color factor.
```

## Source note 900, line 2377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2377)

```text
// Close the source color factor clamping check.
```

## Source note 901, line 2379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2379)

```text
// Apply the factor to the source color.
```

## Source note 902, line 2380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2380)

```text
// blend_src_temp.xyz = unclamped source color part without
```

## Source note 903, line 2381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2381)

```text
//                      addition sign.
```

## Source note 904, line 2384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2384)

```text
// Check if the source color part needs clamping after the
```

## Source note 905, line 2385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2385)

```text
// multiplication.
```

## Source note 906, line 2386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2386)

```text
// temp.x = free.
```

## Source note 907, line 2389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2389)

```text
// Clamp the source color part.
```

## Source note 908, line 2390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2390)

```text
// blend_src_temp.xyz = source color part without addition sign.
```

## Source note 909, line 2394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2394)

```text
// Close the source color part clamping check.
```

## Source note 910, line 2396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2396)

```text
// Extract the source color sign to temp.x.
```

## Source note 911, line 2397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2397)

```text
// temp.x = source color sign as zero for 1 and non-zero for -1.
```

## Source note 912, line 2399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2399)

```text
// Apply the source color sign.
```

## Source note 913, line 2400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2400)

```text
// blend_src_temp.xyz = source color part.
```

## Source note 914, line 2401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2401)

```text
// temp.x = free.
```

## Source note 915, line 2405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2405)

```text
// The source color factor is zero.
```

## Source note 916, line 2408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2408)

```text
// Write zero to the source color part.
```

## Source note 917, line 2409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2409)

```text
// blend_src_temp.xyz = source color part.
```

## Source note 918, line 2410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2410)

```text
// temp.x = free.
```

## Source note 919, line 2413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2413)

```text
// Close the source color factor zero check.
```

## Source note 920, line 2416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2416)

```text
// Extract the destination color factor to temp.x.
```

## Source note 921, line 2417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2417)

```text
// temp.x = destination color factor index.
```

## Source note 922, line 2419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2419)

```text
// Check if the destination color factor is not zero.
```

## Source note 923, line 2424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2424)

```text
// Open the switch for choosing the destination color blend
```

## Source note 924, line 2425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2425)

```text
// factor.
```

## Source note 925, line 2426

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2426)

```text
// temp.x = free.
```

## Source note 926, line 2428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2428)

```text
// Write the destination color factor to
```

## Source note 927, line 2429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2429)

```text
// blend_dest_factor_temp.xyz.
```

## Source note 928, line 2430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2430)

```text
// blend_dest_factor_temp.xyz = unclamped destination color
```

## Source note 929, line 2431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2431)

```text
//                              factor.
```

## Source note 930, line 2434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2434)

```text
// Close the destination color factor switch.
```

## Source note 931, line 2436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2436)

```text
// Get if the render target color is fixed-point and the
```

## Source note 932, line 2437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2437)

```text
// destination color factor needs clamping to temp.x.
```

## Source note 933, line 2438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2438)

```text
// temp.x = whether color is fixed-point.
```

## Source note 934, line 2441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2441)

```text
// Check if the destination color factor needs clamping.
```

## Source note 935, line 2444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2444)

```text
// Clamp the destination color factor in
```

## Source note 936, line 2445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2445)

```text
// blend_dest_factor_temp.xyz.
```

## Source note 937, line 2446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2446)

```text
// blend_dest_factor_temp.xyz = destination color factor.
```

## Source note 938, line 2452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2452)

```text
// Close the destination color factor clamping check.
```

## Source note 939, line 2454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2454)

```text
// Apply the factor to the destination color in color_temp.xyz.
```

## Source note 940, line 2455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2455)

```text
// color_temp.xyz = unclamped destination color part without
```

## Source note 941, line 2456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2456)

```text
//                  addition sign.
```

## Source note 942, line 2457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2457)

```text
// blend_dest_temp.xyz = free.
```

## Source note 943, line 2459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2459)

```text
// Release blend_dest_factor_temp.
```

## Source note 944, line 2461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2461)

```text
// Check if the destination color part needs clamping after the
```

## Source note 945, line 2462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2462)

```text
// multiplication.
```

## Source note 946, line 2463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2463)

```text
// temp.x = free.
```

## Source note 947, line 2466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2466)

```text
// Clamp the destination color part.
```

## Source note 948, line 2467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2467)

```text
// color_temp.xyz = destination color part without addition
```

## Source note 949, line 2468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2468)

```text
// sign.
```

## Source note 950, line 2472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2472)

```text
// Close the destination color part clamping check.
```

## Source note 951, line 2474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2474)

```text
// Extract the destination color sign to temp.x.
```

## Source note 952, line 2475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2475)

```text
// temp.x = destination color sign as zero for 1 and non-zero for
```

## Source note 953, line 2476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2476)

```text
//          -1.
```

## Source note 954, line 2478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2478)

```text
// Select the sign for destination multiply-add as 1.0 or -1.0 to
```

## Source note 955, line 2479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2479)

```text
// temp.x.
```

## Source note 956, line 2480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2480)

```text
// temp.x = destination color sign as float.
```

## Source note 957, line 2482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2482)

```text
// Perform color blending to color_temp.xyz.
```

## Source note 958, line 2483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2483)

```text
// color_temp.xyz = unclamped blended color.
```

## Source note 959, line 2484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2484)

```text
// blend_src_temp.xyz = free.
```

## Source note 960, line 2485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2485)

```text
// temp.x = free.
```

## Source note 961, line 2488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2488)

```text
// The destination color factor is zero.
```

## Source note 962, line 2491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2491)

```text
// Write the source color part without applying the destination
```

## Source note 963, line 2492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2492)

```text
// color.
```

## Source note 964, line 2493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2493)

```text
// color_temp.xyz = unclamped blended color.
```

## Source note 965, line 2494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2494)

```text
// blend_src_temp.xyz = free.
```

## Source note 966, line 2495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2495)

```text
// temp.x = free.
```

## Source note 967, line 2498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2498)

```text
// Close the destination color factor zero check.
```

## Source note 968, line 2501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2501)

```text
// Release blend_src_temp.
```

## Source note 969, line 2504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2504)

```text
// Clamp the color in color_temp.xyz before packing.
```

## Source note 970, line 2505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2505)

```text
// color_temp.xyz = blended color.
```

## Source note 971, line 2509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2509)

```text
// Need to do min/max for color.
```

## Source note 972, line 2512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2512)

```text
// Extract the color min (0) or max (1) bit to temp.x
```

## Source note 973, line 2513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2513)

```text
// temp.x = whether min or max should be used for color.
```

## Source note 974, line 2515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2515)

```text
// Check if need to do min or max for color.
```

## Source note 975, line 2516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2516)

```text
// temp.x = free.
```

## Source note 976, line 2519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2519)

```text
// Choose max of the colors without applying the factors to
```

## Source note 977, line 2520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2520)

```text
// color_temp.xyz.
```

## Source note 978, line 2521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2521)

```text
// color_temp.xyz = blended color.
```

## Source note 979, line 2524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2524)

```text
// Need to do min.
```

## Source note 980, line 2527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2527)

```text
// Choose min of the colors without applying the factors to
```

## Source note 981, line 2528

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2528)

```text
// color_temp.xyz.
```

## Source note 982, line 2529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2529)

```text
// color_temp.xyz = blended color.
```

## Source note 983, line 2532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2532)

```text
// Close the min or max check.
```

## Source note 984, line 2535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2535)

```text
// Close the color factor blending or min/max check.
```

## Source note 985, line 2539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2539)

```text
// Alpha blending.
```

## Source note 986, line 2542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2542)

```text
// Extract the alpha min/max bit to temp.x.
```

## Source note 987, line 2543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2543)

```text
// temp.x = whether min/max should be used for alpha.
```

## Source note 988, line 2545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2545)

```text
// Check if need to do blend the color with factors.
```

## Source note 989, line 2546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2546)

```text
// temp.x = free.
```

## Source note 990, line 2549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2549)

```text
// Extract the source alpha factor to temp.x.
```

## Source note 991, line 2550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2550)

```text
// temp.x = source alpha factor index.
```

## Source note 992, line 2552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2552)

```text
// Check if the source alpha factor is not zero.
```

## Source note 993, line 2555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2555)

```text
// Open the switch for choosing the source alpha blend factor.
```

## Source note 994, line 2556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2556)

```text
// temp.x = free.
```

## Source note 995, line 2558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2558)

```text
// Write the source alpha factor to temp.x.
```

## Source note 996, line 2559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2559)

```text
// temp.x = unclamped source alpha factor.
```

## Source note 997, line 2561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2561)

```text
// Close the source alpha factor switch.
```

## Source note 998, line 2563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2563)

```text
// Get if the render target alpha is fixed-point and the source
```

## Source note 999, line 2564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2564)

```text
// alpha factor needs clamping to temp.y.
```

## Source note 1000, line 2565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2565)

```text
// temp.y = whether alpha is fixed-point.
```

## Source note 1001, line 2568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2568)

```text
// Check if the source alpha factor needs clamping.
```

## Source note 1002, line 2571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2571)

```text
// Clamp the source alpha factor in temp.x.
```

## Source note 1003, line 2572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2572)

```text
// temp.x = source alpha factor.
```

## Source note 1004, line 2576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2576)

```text
// Close the source alpha factor clamping check.
```

## Source note 1005, line 2578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2578)

```text
// Apply the factor to the source alpha.
```

## Source note 1006, line 2579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2579)

```text
// temp.x = unclamped source alpha part without addition sign.
```

## Source note 1007, line 2582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2582)

```text
// Check if the source alpha part needs clamping after the
```

## Source note 1008, line 2583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2583)

```text
// multiplication.
```

## Source note 1009, line 2584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2584)

```text
// temp.y = free.
```

## Source note 1010, line 2587

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2587)

```text
// Clamp the source alpha part.
```

## Source note 1011, line 2588

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2588)

```text
// temp.x = source alpha part without addition sign.
```

## Source note 1012, line 2592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2592)

```text
// Close the source alpha part clamping check.
```

## Source note 1013, line 2594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2594)

```text
// Extract the source alpha sign to temp.y.
```

## Source note 1014, line 2595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2595)

```text
// temp.y = source alpha sign as zero for 1 and non-zero for -1.
```

## Source note 1015, line 2597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2597)

```text
// Apply the source alpha sign.
```

## Source note 1016, line 2598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2598)

```text
// temp.x = source alpha part.
```

## Source note 1017, line 2601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2601)

```text
// The source alpha factor is zero.
```

## Source note 1018, line 2604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2604)

```text
// Write zero to the source alpha part.
```

## Source note 1019, line 2605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2605)

```text
// temp.x = source alpha part.
```

## Source note 1020, line 2608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2608)

```text
// Close the source alpha factor zero check.
```

## Source note 1021, line 2611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2611)

```text
// Extract the destination alpha factor to temp.y.
```

## Source note 1022, line 2612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2612)

```text
// temp.y = destination alpha factor index.
```

## Source note 1023, line 2614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2614)

```text
// Check if the destination alpha factor is not zero.
```

## Source note 1024, line 2617

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2617)

```text
// Open the switch for choosing the destination alpha blend
```

## Source note 1025, line 2618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2618)

```text
// factor.
```

## Source note 1026, line 2619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2619)

```text
// temp.y = free.
```

## Source note 1027, line 2621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2621)

```text
// Write the destination alpha factor to temp.y.
```

## Source note 1028, line 2622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2622)

```text
// temp.y = unclamped destination alpha factor.
```

## Source note 1029, line 2624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2624)

```text
// Close the destination alpha factor switch.
```

## Source note 1030, line 2626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2626)

```text
// Get if the render target alpha is fixed-point and the
```

## Source note 1031, line 2627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2627)

```text
// destination alpha factor needs clamping.
```

## Source note 1032, line 2628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2628)

```text
// alpha_is_fixed_temp.x = whether alpha is fixed-point.
```

## Source note 1033, line 2632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2632)

```text
// Check if the destination alpha factor needs clamping.
```

## Source note 1034, line 2635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2635)

```text
// Clamp the destination alpha factor in temp.y.
```

## Source note 1035, line 2636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2636)

```text
// temp.y = destination alpha factor.
```

## Source note 1036, line 2640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2640)

```text
// Close the destination alpha factor clamping check.
```

## Source note 1037, line 2642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2642)

```text
// Apply the factor to the destination alpha in color_temp.w.
```

## Source note 1038, line 2643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2643)

```text
// color_temp.w = unclamped destination alpha part without
```

## Source note 1039, line 2644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2644)

```text
//                addition sign.
```

## Source note 1040, line 2646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2646)

```text
// Check if the destination alpha part needs clamping after the
```

## Source note 1041, line 2647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2647)

```text
// multiplication.
```

## Source note 1042, line 2648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2648)

```text
// alpha_is_fixed_temp.x = free.
```

## Source note 1043, line 2650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2650)

```text
// Release alpha_is_fixed_temp.
```

## Source note 1044, line 2653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2653)

```text
// Clamp the destination alpha part.
```

## Source note 1045, line 2654

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2654)

```text
// color_temp.w = destination alpha part without addition sign.
```

## Source note 1046, line 2658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2658)

```text
// Close the destination alpha factor clamping check.
```

## Source note 1047, line 2660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2660)

```text
// Extract the destination alpha sign to temp.y.
```

## Source note 1048, line 2661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2661)

```text
// temp.y = destination alpha sign as zero for 1 and non-zero for
```

## Source note 1049, line 2662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2662)

```text
//          -1.
```

## Source note 1050, line 2664

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2664)

```text
// Select the sign for destination multiply-add as 1.0 or -1.0 to
```

## Source note 1051, line 2665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2665)

```text
// temp.y.
```

## Source note 1052, line 2666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2666)

```text
// temp.y = destination alpha sign as float.
```

## Source note 1053, line 2668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2668)

```text
// Perform alpha blending to color_temp.w.
```

## Source note 1054, line 2669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2669)

```text
// color_temp.w = unclamped blended alpha.
```

## Source note 1055, line 2670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2670)

```text
// temp.xy = free.
```

## Source note 1056, line 2673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2673)

```text
// The destination alpha factor is zero.
```

## Source note 1057, line 2676

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2676)

```text
// Write the source alpha part without applying the destination
```

## Source note 1058, line 2677

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2677)

```text
// alpha.
```

## Source note 1059, line 2678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2678)

```text
// color_temp.w = unclamped blended alpha.
```

## Source note 1060, line 2679

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2679)

```text
// temp.xy = free.
```

## Source note 1061, line 2682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2682)

```text
// Close the destination alpha factor zero check.
```

## Source note 1062, line 2685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2685)

```text
// Clamp the alpha in color_temp.w before packing.
```

## Source note 1063, line 2686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2686)

```text
// color_temp.w = blended alpha.
```

## Source note 1064, line 2690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2690)

```text
// Need to do min/max for alpha.
```

## Source note 1065, line 2693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2693)

```text
// Extract the alpha min (0) or max (1) bit to temp.x.
```

## Source note 1066, line 2694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2694)

```text
// temp.x = whether min or max should be used for alpha.
```

## Source note 1067, line 2696

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2696)

```text
// Check if need to do min or max for alpha.
```

## Source note 1068, line 2697

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2697)

```text
// temp.x = free.
```

## Source note 1069, line 2700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2700)

```text
// Choose max of the alphas without applying the factors to
```

## Source note 1070, line 2701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2701)

```text
// color_temp.w.
```

## Source note 1071, line 2702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2702)

```text
// color_temp.w = blended alpha.
```

## Source note 1072, line 2706

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2706)

```text
// Need to do min.
```

## Source note 1073, line 2709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2709)

```text
// Choose min of the alphas without applying the factors to
```

## Source note 1074, line 2710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2710)

```text
// color_temp.w.
```

## Source note 1075, line 2711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2711)

```text
// color_temp.w = blended alpha.
```

## Source note 1076, line 2715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2715)

```text
// Close the min or max check.
```

## Source note 1077, line 2718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2718)

```text
// Close the alpha factor blending or min/max check.
```

## Source note 1078, line 2721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2721)

```text
// Pack the new color/alpha to temp.xy.
```

## Source note 1079, line 2722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2722)

```text
// temp.xy = packed new color/alpha.
```

## Source note 1080, line 2725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2725)

```text
// Release color_pack_temp.
```

## Source note 1081, line 2728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2728)

```text
// Close the blending check.
```

## Source note 1082, line 2732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2732)

```text
// Write mask application
```

## Source note 1083, line 2735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2735)

```text
// Apply the keep mask to the previous packed color/alpha in temp.zw.
```

## Source note 1084, line 2736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2736)

```text
// temp.zw = masked packed old color/alpha.
```

## Source note 1085, line 2739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2739)

```text
// Invert the keep mask into color_temp.xy.
```

## Source note 1086, line 2740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2740)

```text
// color_temp.xy = inverted keep mask (write mask).
```

## Source note 1087, line 2742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2742)

```text
// Release color_temp.
```

## Source note 1088, line 2744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2744)

```text
// Apply the write mask to the new color/alpha in temp.xy.
```

## Source note 1089, line 2745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2745)

```text
// temp.xy = masked packed new color/alpha.
```

## Source note 1090, line 2747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2747)

```text
// Combine the masked colors into temp.xy.
```

## Source note 1091, line 2748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2748)

```text
// temp.xy = packed resulting color/alpha.
```

## Source note 1092, line 2749

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2749)

```text
// temp.zw = free.
```

## Source note 1093, line 2752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2752)

```text
// Close the previous color load check.
```

## Source note 1094, line 2756

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2756)

```text
// Writing the color
```

## Source note 1095, line 2759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2759)

```text
// Store the 32bpp color or the lower 32 bits of the 64bpp color.
```

## Source note 1096, line 2765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2765)

```text
// Get if the format is 64bpp to temp.z.
```

## Source note 1097, line 2766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2766)

```text
// temp.z = whether the render target is 64bpp.
```

## Source note 1098, line 2769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2769)

```text
// Check if the format is 64bpp.
```

## Source note 1099, line 2770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2770)

```text
// temp.z = free.
```

## Source note 1100, line 2773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2773)

```text
// Get the address of the upper 32 bits of the color to temp.z (can't
```

## Source note 1101, line 2774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2774)

```text
// use temp.x because components when not blending, packing is done once
```

## Source note 1102, line 2775

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2775)

```text
// for all samples, so it has to be preserved).
```

## Source note 1103, line 2778

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2778)

```text
// Store the upper 32 bits of the 64bpp color.
```

## Source note 1104, line 2785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2785)

```text
// Close the 64bpp conditional.
```

## Source note 1105, line 2789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2789)

```text
// End of color sample raster operation.
```

## Source note 1106, line 2792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2792)

```text
// Close the sample covered check.
```

## Source note 1107, line 2795

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2795)

```text
// Go to the next sample, the same walk as in the depth sample loop,
```

## Source note 1108, line 2796

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2796)

```text
// except the deltas are in sample columns here and a 64bpp sample
```

## Source note 1109, line 2797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2797)

```text
// column is 2 dwords wide, while a row is 80*scale_x dwords either way.
```

## Source note 1110, line 2798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2798)

```text
// No need to do this for the last sample as for the next render target,
```

## Source note 1111, line 2799

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2799)

```text
// the address will be recalculated.
```

## Source note 1112, line 2804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2804)

```text
// temp.z = whether the render target is 64bpp.
```

## Source note 1113, line 2807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2807)

```text
// temp.z = offset from the current sample to the next.
```

## Source note 1114, line 2813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2813)

```text
// temp.z = free.
```

## Source note 1115, line 2819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2819)

```text
// Close the render target write check.
```

## Source note 1116, line 2823

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2823)

```text
// Release temp.
```

## Source note 1117, line 2828

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2828)

```text
// Adapted from xenia-canary 3d233a5b2e94b940825847b70c788951e364bb33
```

## Source note 1118, line 2829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2829)

```text
// (PR #1218): hybrid RTV queries take ZPass from the native query and count
```

## Source note 1119, line 2830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2830)

```text
// the coverage entering the depth / stencil test here, as Total.
```

## Source note 1120, line 2847

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2847)

```text
// UINT32_MAX means no ZPD segment is open for this draw.
```

## Source note 1121, line 2851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2851)

```text
// Total is the slot's first counter.
```

## Source note 1122, line 2856

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2856)

```text
// Every sample-frequency invocation gets the pixel's full primitive
```

## Source note 1123, line 2857

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2857)

```text
// coverage (D3D11.3 16.3.2). To count it once, only the first covered
```

## Source note 1124, line 2858

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2858)

```text
// sample adds it, as memexport does.
```

## Source note 1125, line 2879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2879)

```text
// The ZPD Total counter takes the coverage entering the shader, narrowed by
```

## Source note 1126, line 2880

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2880)

```text
// everything that drops samples before the depth / stencil test.
```

## Source note 1127, line 2888

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2888)

```text
// The depth-only shader only needs to do the depth test and to write the
```

## Source note 1128, line 2889

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2889)

```text
// depth to the ROV, or, for a hybrid occlusion query on RTV, to count the
```

## Source note 1129, line 2890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2890)

```text
// coverage and convert the depth.
```

## Source note 1130, line 2907

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2907)

```text
// Check if the render target 0 was written to on the execution path.
```

## Source note 1131, line 2912

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2912)

```text
// Release rt_0_written_temp.
```

## Source note 1132, line 2916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2916)

```text
// Alpha test.
```

## Source note 1133, line 2917

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2917)

```text
// X - mask, then masked result (SGPR for loading, VGPR for masking).
```

## Source note 1134, line 2918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2918)

```text
// Y - operation result (SGPR for mask operations, VGPR for alpha
```

## Source note 1135, line 2919

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2919)

```text
//     operations).
```

## Source note 1136, line 2920

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2920)

```text
// Z - fuzzy diff (alpha - reference), used when fuzzy epsilon is enabled.
```

## Source note 1137, line 2928

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2928)

```text
// Extract the comparison mask to check if the test needs to be done at all.
```

## Source note 1138, line 2929

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2929)

```text
// Don't care about flow control being somewhat dynamic - early Z is forced
```

## Source note 1139, line 2930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2930)

```text
// using a special version of the shader anyway.
```

## Source note 1140, line 2933

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2933)

```text
// Compare the mask to ALWAYS to check if the test shouldn't be done (will
```

## Source note 1141, line 2934

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2934)

```text
// pass even for NaNs, though the expected behavior in this case hasn't been
```

## Source note 1142, line 2935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2935)

```text
// checked, but let's assume this means "always", not "less, equal or
```

## Source note 1143, line 2936

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2936)

```text
// greater".
```

## Source note 1144, line 2940

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2940)

```text
// Don't do the test if the mode is "always".
```

## Source note 1145, line 2943

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2943)

```text
// Do the test.
```

## Source note 1146, line 2948

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2948)

```text
// Epsilon for fuzzy alpha checks (prevents flickering on NVIDIA GPUs).
```

## Source note 1147, line 2950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2950)

```text
// Handle "not equal" specially (specifically as "not equal" so it's true
```

## Source note 1148, line 2951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2951)

```text
// for NaN, not "less or greater" which is false for NaN).
```

## Source note 1149, line 2958

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2958)

```text
// Check if distance to desired value is less than epsilon (false for
```

## Source note 1150, line 2959

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2959)

```text
// NaN) and write the negated result.
```

## Source note 1151, line 2969

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2969)

```text
// Less than.
```

## Source note 1152, line 2974

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2974)

```text
// "Equals" to.
```

## Source note 1153, line 2979

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2979)

```text
// Greater than.
```

## Source note 1154, line 2985

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2985)

```text
// Less than.
```

## Source note 1155, line 2989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2989)

```text
// Equals to.
```

## Source note 1156, line 2993

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2993)

```text
// Greater than.
```

## Source note 1157, line 2999

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2999)

```text
// Close the "not equal" check.
```

## Source note 1158, line 3001

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3001)

```text
// Discard the pixel if it has failed the test.
```

## Source note 1159, line 3008

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3008)

```text
// Close the "not always" check.
```

## Source note 1160, line 3010

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3010)

```text
// Release alpha_test_temp.
```

## Source note 1161, line 3013

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3013)

```text
// Discard samples with alpha to coverage.
```

## Source note 1162, line 3017

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3017)

```text
// Close the render target 0 written check.
```

## Source note 1163, line 3027

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3027)

```text
// Write the values to the render targets. Not applying the exponent bias yet
```

## Source note 1164, line 3028

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3028)

```text
// because the original 0 to 1 alpha value is needed for alpha to coverage,
```

## Source note 1165, line 3029

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3029)

```text
// which is done differently for ROV and RTV/DSV.
```

## Source note 1166, line 3044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3044)

```text
// Source and destination may be the same.
```

## Source note 1167, line 3051

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3051)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 1168, line 3052

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3052)

```text
// Assuming the color is already clamped to [0, 31.875].
```

## Source note 1169, line 3054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3054)

```text
// Check if the number is too small to be represented as normalized 7e3.
```

## Source note 1170, line 3055

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3055)

```text
// temp = f32 < 2^-2
```

## Source note 1171, line 3057

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3057)

```text
// Handle denormalized numbers separately.
```

## Source note 1172, line 3060

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3060)

```text
// temp = f32 >> 23
```

## Source note 1173, line 3062

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3062)

```text
// temp = 125 - (f32 >> 23)
```

## Source note 1174, line 3064

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3064)

```text
// Don't allow the shift to overflow, since in DXBC the lower 5 bits of the
```

## Source note 1175, line 3065

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3065)

```text
// shift amount are used.
```

## Source note 1176, line 3066

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3066)

```text
// temp = min(125 - (f32 >> 23), 24)
```

## Source note 1177, line 3068

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3068)

```text
// biased_f32 = (f32 & 0x7FFFFF) | 0x800000
```

## Source note 1178, line 3070

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3070)

```text
// biased_f32 = ((f32 & 0x7FFFFF) | 0x800000) >> min(125 - (f32 >> 23), 24)
```

## Source note 1179, line 3073

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3073)

```text
// Not denormalized?
```

## Source note 1180, line 3076

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3076)

```text
// Bias the exponent.
```

## Source note 1181, line 3077

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3077)

```text
// biased_f32 = f32 + (-124 << 23)
```

## Source note 1182, line 3078

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3078)

```text
// (left shift of a negative value is undefined behavior)
```

## Source note 1183, line 3081

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3081)

```text
// Close the denormal check.
```

## Source note 1184, line 3083

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3083)

```text
// Build the 7e3 number.
```

## Source note 1185, line 3084

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3084)

```text
// temp = (biased_f32 >> 16) & 1
```

## Source note 1186, line 3086

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3086)

```text
// f10 = biased_f32 + 0x7FFF
```

## Source note 1187, line 3088

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3088)

```text
// f10 = biased_f32 + 0x7FFF + ((biased_f32 >> 16) & 1)
```

## Source note 1188, line 3090

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3090)

```text
// f24 = ((biased_f32 + 0x7FFF + ((biased_f32 >> 16) & 1)) >> 16) & 0x3FF
```

## Source note 1189, line 3098

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3098)

```text
// Source and destination might be the same or different, just like in
```

## Source note 1190, line 3099

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3099)

```text
// PreClampedFloat32To7e3 - clamp to the destination and use it as source.
```

## Source note 1191, line 3115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3115)

```text
// Source may be the same as temp1 or temp2.
```

## Source note 1192, line 3121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3121)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 1193, line 3124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3124)

```text
// Unpack the exponent before the mantissa if that doesn't overwrite the
```

## Source note 1194, line 3125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3125)

```text
// source.
```

## Source note 1195, line 3129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3129)

```text
// Unpack the mantissa.
```

## Source note 1196, line 3133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3133)

```text
// Unpack the exponent after the mantissa if doing that before the mantissa
```

## Source note 1197, line 3134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3134)

```text
// would overwrite the source.
```

## Source note 1198, line 3138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3138)

```text
// Check if the number is denormalized.
```

## Source note 1199, line 3141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3141)

```text
// Check if the number is non-zero (if the mantissa isn't zero - the
```

## Source note 1200, line 3142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3142)

```text
// exponent is known to be zero at this point).
```

## Source note 1201, line 3145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3145)

```text
// Normalize the mantissa.
```

## Source note 1202, line 3146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3146)

```text
// Note that HLSL firstbithigh(x) is compiled to DXBC like:
```

## Source note 1203, line 3147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3147)

```text
// `x ? 31 - firstbit_hi(x) : -1`
```

## Source note 1204, line 3148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3148)

```text
// (returns the index from the LSB, not the MSB, but -1 for zero too).
```

## Source note 1205, line 3149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3149)

```text
// exponent = firstbit_hi(mantissa)
```

## Source note 1206, line 3151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3151)

```text
// exponent = 7 - firstbithigh(mantissa)
```

## Source note 1207, line 3153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3153)

```text
// exponent = 7 - (31 - firstbit_hi(mantissa))
```

## Source note 1208, line 3155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3155)

```text
// mantissa = mantissa << (7 - firstbithigh(mantissa))
```

## Source note 1209, line 3156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3156)

```text
// AND 0x7F not needed after this - BFI will do it.
```

## Source note 1210, line 3158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3158)

```text
// Get the normalized exponent.
```

## Source note 1211, line 3159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3159)

```text
// exponent = 1 - (7 - firstbithigh(mantissa))
```

## Source note 1212, line 3162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3162)

```text
// The number is zero.
```

## Source note 1213, line 3165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3165)

```text
// Set the unbiased exponent to -124 for zero - 124 will be added later,
```

## Source note 1214, line 3166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3166)

```text
// resulting in zero float32.
```

## Source note 1215, line 3169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3169)

```text
// Close the non-zero check.
```

## Source note 1216, line 3172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3172)

```text
// Close the denormal check.
```

## Source note 1217, line 3174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3174)

```text
// Bias the exponent and move it to the correct location in f32.
```

## Source note 1218, line 3176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3176)

```text
// Combine the mantissa and the exponent.
```

## Source note 1219, line 3188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3188)

```text
// Source and destination may be the same.
```

## Source note 1220, line 3195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3195)

```text
// CFloat24 from d3dref9.dll +
```

## Source note 1221, line 3196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3196)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 1222, line 3197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3197)

```text
// Assuming the depth is already clamped to [0, 2) (in all places, the depth
```

## Source note 1223, line 3198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3198)

```text
// is written with the saturate flag set).
```

## Source note 1224, line 3202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3202)

```text
// Check if the number is too small to be represented as normalized 20e4.
```

## Source note 1225, line 3203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3203)

```text
// temp = f32 < 2^-14
```

## Source note 1226, line 3205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3205)

```text
// Handle denormalized numbers separately.
```

## Source note 1227, line 3208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3208)

```text
// temp = f32 >> 23
```

## Source note 1228, line 3210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3210)

```text
// temp = 113 - (f32 >> 23)
```

## Source note 1229, line 3212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3212)

```text
// Don't allow the shift to overflow, since in DXBC the lower 5 bits of the
```

## Source note 1230, line 3213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3213)

```text
// shift amount are used (otherwise 0 becomes 8).
```

## Source note 1231, line 3214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3214)

```text
// temp = min(113 - (f32 >> 23), 24)
```

## Source note 1232, line 3216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3216)

```text
// biased_f32 = (f32 & 0x7FFFFF) | 0x800000
```

## Source note 1233, line 3218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3218)

```text
// biased_f32 = ((f32 & 0x7FFFFF) | 0x800000) >> min(113 - (f32 >> 23), 24)
```

## Source note 1234, line 3221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3221)

```text
// Not denormalized?
```

## Source note 1235, line 3224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3224)

```text
// Bias the exponent.
```

## Source note 1236, line 3225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3225)

```text
// biased_f32 = f32 + (-112 << 23)
```

## Source note 1237, line 3226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3226)

```text
// (left shift of a negative value is undefined behavior)
```

## Source note 1238, line 3229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3229)

```text
// Close the denormal check.
```

## Source note 1239, line 3231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3231)

```text
// Build the 20e4 number.
```

## Source note 1240, line 3233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3233)

```text
// temp = (biased_f32 >> 3) & 1
```

## Source note 1241, line 3235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3235)

```text
// f24 = biased_f32 + 3
```

## Source note 1242, line 3237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3237)

```text
// f24 = biased_f32 + 3 + ((biased_f32 >> 3) & 1)
```

## Source note 1243, line 3240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3240)

```text
// For rounding to the nearest even:
```

## Source note 1244, line 3241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3241)

```text
// f24 = ((biased_f32 + 3 + ((biased_f32 >> 3) & 1)) >> 3) & 0xFFFFFF
```

## Source note 1245, line 3242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3242)

```text
// For rounding towards zero:
```

## Source note 1246, line 3243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3243)

```text
// f24 = (biased_f32 >> 3) & 0xFFFFFF
```

## Source note 1247, line 3254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3254)

```text
// Source may be the same as temp1 or temp2.
```

## Source note 1248, line 3260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3260)

```text
// CFloat24 from d3dref9.dll +
```

## Source note 1249, line 3261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3261)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 1250, line 3266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3266)

```text
// Unpack the exponent before the mantissa if that doesn't overwrite the
```

## Source note 1251, line 3267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3267)

```text
// source.
```

## Source note 1252, line 3271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3271)

```text
// Unpack the mantissa.
```

## Source note 1253, line 3275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3275)

```text
// Unpack the exponent after the mantissa if doing that before the mantissa
```

## Source note 1254, line 3276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3276)

```text
// would overwrite the source.
```

## Source note 1255, line 3280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3280)

```text
// Check if the number is denormalized.
```

## Source note 1256, line 3283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3283)

```text
// Check if the number is non-zero (if the mantissa isn't zero - the
```

## Source note 1257, line 3284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3284)

```text
// exponent is known to be zero at this point).
```

## Source note 1258, line 3287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3287)

```text
// Normalize the mantissa.
```

## Source note 1259, line 3288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3288)

```text
// Note that HLSL firstbithigh(x) is compiled to DXBC like:
```

## Source note 1260, line 3289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3289)

```text
// `x ? 31 - firstbit_hi(x) : -1`
```

## Source note 1261, line 3290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3290)

```text
// (returns the index from the LSB, not the MSB, but -1 for zero too).
```

## Source note 1262, line 3291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3291)

```text
// exponent = firstbit_hi(mantissa)
```

## Source note 1263, line 3293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3293)

```text
// exponent = 20 - firstbithigh(mantissa)
```

## Source note 1264, line 3295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3295)

```text
// exponent = 20 - (31 - firstbit_hi(mantissa))
```

## Source note 1265, line 3297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3297)

```text
// mantissa = mantissa << (20 - firstbithigh(mantissa))
```

## Source note 1266, line 3298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3298)

```text
// AND 0xFFFFF not needed after this - BFI will do it.
```

## Source note 1267, line 3300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3300)

```text
// Get the normalized exponent.
```

## Source note 1268, line 3301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3301)

```text
// exponent = 1 - (20 - firstbithigh(mantissa))
```

## Source note 1269, line 3304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3304)

```text
// The number is zero.
```

## Source note 1270, line 3307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3307)

```text
// Set the unbiased exponent to -112 for zero - 112 will be added later
```

## Source note 1271, line 3308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3308)

```text
// (taking the range remap bias into account), resulting in zero float32.
```

## Source note 1272, line 3311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3311)

```text
// Close the non-zero check.
```

## Source note 1273, line 3314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3314)

```text
// Close the denormal check.
```

## Source note 1274, line 3316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3316)

```text
// Bias the exponent and move it to the correct location in f32, and also
```

## Source note 1275, line 3317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3317)

```text
// remap from guest 0...1 to host 0...0.5 if needed.
```

## Source note 1276, line 3320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3320)

```text
// Combine the mantissa and the exponent.
```

## Source note 1277, line 3328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3328)

```text
// Source and destination may be the same.
```

## Source note 1278, line 3332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3332)

```text
// Convert according to the format.
```

## Source note 1279, line 3335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3335)

```text
// 20e4 conversion.
```

## Source note 1280, line 3341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3341)

```text
// Unorm24 conversion.
```

## Source note 1281, line 3346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3346)

```text
// Round to the nearest even integer. This seems to be the correct way:
```

## Source note 1282, line 3347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3347)

```text
// rounding towards zero gives 0xFF instead of 0x100 in clear shaders in,
```

## Source note 1283, line 3348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3348)

```text
// for instance, 4D5307E6, but other clear shaders in it are also broken if
```

## Source note 1284, line 3349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3349)

```text
// 0.5 is added before ftou instead of round_ne.
```

## Source note 1285, line 3351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L3351)

```text
// Convert to fixed-point.
```
