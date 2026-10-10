# Xboxkrnl video: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_video.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L37)

```text
// Display gamma type: 0 - linear, 1 - sRGB (CRT), 2 - BT.709 (HDTV), 3 - power
```

## Source note 3, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L39)

```text
// Display gamma power (used with gamma type 3)
```

## Source note 4, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L114)

```text
// https://web.archive.org/web/20150805074003/https://www.tweakoz.com/orkid/
```

## Source note 5, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L115)

```text
// http://www.tweakoz.com/orkid/dox/d3/d52/xb360init_8cpp_source.html
```

## Source note 6, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L116)

```text
// https://github.com/Free60Project/xenosfb/
```

## Source note 7, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L117)

```text
// https://github.com/Free60Project/xenosfb/blob/master/src/xe.h
```

## Source note 8, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L118)

```text
// https://github.com/gligli/libxemit
```

## Source note 9, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L119)

```text
// https://web.archive.org/web/20090428095215/https://msdn.microsoft.com/en-us/library/bb313877.aspx
```

## Source note 10, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L120)

```text
// https://web.archive.org/web/20100423054747/https://msdn.microsoft.com/en-us/library/bb313961.aspx
```

## Source note 11, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L121)

```text
// https://web.archive.org/web/20100423054747/https://msdn.microsoft.com/en-us/library/bb313878.aspx
```

## Source note 12, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L122)

```text
// https://web.archive.org/web/20090510235238/https://msdn.microsoft.com/en-us/library/bb313942.aspx
```

## Source note 13, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L123)

```text
// https://svn.dd-wrt.com/browser/src/linux/universal/linux-3.8/drivers/gpu/drm/radeon/radeon_ring.c?rev=21595
```

## Source note 14, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L124)

```text
// https://www.microsoft.com/en-za/download/details.aspx?id=5313 -- "Stripped
```

## Source note 15, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L125)

```text
// Down Direct3D: Xbox 360 Command Buffer and Resource Management"
```

## Source note 16, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L128)

```text
// 1 - sRGB.
```

## Source note 17, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L129)

```text
// 2 - TV (BT.709).
```

## Source note 18, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L130)

```text
// 3 - use the power written to *power_ptr.
```

## Source note 19, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L131)

```text
// Anything else - linear.
```

## Source note 20, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L132)

```text
// Used in D3D SetGammaRamp/SetPWLGamma to adjust the ramp for the display.
```

## Source note 21, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L138)

```text
// 0x0
```

## Source note 22, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L139)

```text
// 0x4
```

## Source note 23, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L140)

```text
// 0x8
```

## Source note 24, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L141)

```text
// 0xC
```

## Source note 25, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L146)

```text
// 0x0
```

## Source note 26, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L147)

```text
// 0x4
```

## Source note 27, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L148)

```text
// 0x8
```

## Source note 28, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L153)

```text
// 0x0
```

## Source note 29, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L154)

```text
// 0x10
```

## Source note 30, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L155)

```text
// 0x14
```

## Source note 31, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L156)

```text
// 0x18
```

## Source note 32, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L157)

```text
// 0x1C
```

## Source note 33, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L158)

```text
// 0x28
```

## Source note 34, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L159)

```text
// 0x2C
```

## Source note 35, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L164)

```text
// 0x0
```

## Source note 36, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L165)

```text
// 0x2
```

## Source note 37, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L166)

```text
// 0x4
```

## Source note 38, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L167)

```text
// 0x5
```

## Source note 39, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L168)

```text
// 0x8
```

## Source note 40, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L169)

```text
// 0x40
```

## Source note 41, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L170)

```text
// 0x42
```

## Source note 42, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L171)

```text
// 0x44
```

## Source note 43, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L172)

```text
// 0x46
```

## Source note 44, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L173)

```text
// 0x48
```

## Source note 45, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L174)

```text
// 0x4A
```

## Source note 46, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L175)

```text
// 0x4C
```

## Source note 47, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L176)

```text
// 0x50
```

## Source note 48, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L177)

```text
// 0x54
```

## Source note 49, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L178)

```text
// 0x56
```

## Source note 50, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L209)

```text
// Exposed as CVARs so the guest can observe custom display settings.
```

## Source note 51, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L244)

```text
// Often 0x40000000.
```

## Source note 52, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L246)

```text
// 0?ccf000 00000000 00000000 000000r0
```

## Source note 53, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L248)

```text
// r: 0x00000002 |     1
```

## Source note 54, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L249)

```text
// f: 0x08000000 |    27
```

## Source note 55, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L250)

```text
// c: 0x30000000 | 28-29
```

## Source note 56, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L251)

```text
// ?: 0x40000000 |    30
```

## Source note 57, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L253)

```text
// r: 1 = Resolution is 720x480 or 720x576
```

## Source note 58, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L254)

```text
// f: 1 = Texture format is k_2_10_10_10 or k_2_10_10_10_AS_16_16_16_16
```

## Source note 59, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L255)

```text
// c: Color space (0 = RGB, 1 = ?, 2 = ?)
```

## Source note 60, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L256)

```text
// ?: (always set?)
```

## Source note 61, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L262)

```text
// refresh_rate = 0, 50, 59.9, etc.
```

## Source note 62, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L268)

```text
// r3 = 0x4F810000
```

## Source note 63, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L269)

```text
// r4 = function ptr (cleanup callback?)
```

## Source note 64, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L270)

```text
// r5 = function arg
```

## Source note 65, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L271)

```text
// r6 = PFP Microcode
```

## Source note 66, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L272)

```text
// r7 = ME Microcode
```

## Source note 67, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L277)

```text
// Ignored for now.
```

## Source note 68, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L278)

```text
// Games seem to call an Initialize/Shutdown pair to query info, then
```

## Source note 69, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L279)

```text
// re-initialize.
```

## Source note 70, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L283)

```text
// Games compare for < 0x10 and do VdInitializeEDRAM, else other
```

## Source note 71, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L284)

```text
// (retrain/etc).
```

## Source note 72, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L289)

```text
// Ignored, as it really doesn't matter.
```

## Source note 73, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L294)

```text
// callback takes 2 params
```

## Source note 74, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L295)

```text
// r3 = bool 0/1 - 0 is normal interrupt, 1 is some acquire/lock mumble
```

## Source note 75, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L296)

```text
// r4 = user_data (r4 of VdSetGraphicsInterruptCallback)
```

## Source note 76, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L307)

```text
// r3 = result of MmGetPhysicalAddress
```

## Source note 77, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L308)

```text
// r4 = log2(size)
```

## Source note 78, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L309)

```text
// Buffer pointers are from MmAllocatePhysicalMemory with WRITE_COMBINE.
```

## Source note 79, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L320)

```text
// r4 = log2(block size), 6, usually --- <=19
```

## Source note 80, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L337)

```text
// r3 = 0x2B10(d3d?) + 8
```

## Source note 81, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L341)

```text
// r3
```

## Source note 82, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L342)

```text
// r4 = 19
```

## Source note 83, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L343)

```text
// no op?
```

## Source note 84, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L346)

```text
// ((uint16_t)y << 16) | (uint16_t)x
```

## Source note 85, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L347)

```text
// ((uint16_t)h << 16) | (uint16_t)w
```

## Source note 86, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L348)

```text
// ((uint16_t)y << 16) | (uint16_t)x
```

## Source note 87, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L349)

```text
// ((uint16_t)h << 16) | (uint16_t)w
```

## Source note 88, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L350)

```text
// ((uint16_t)h << 16) | (uint16_t)w
```

## Source note 89, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L351)

```text
// 7?
```

## Source note 90, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L353)

```text
// 7?
```

## Source note 91, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L356)

```text
// Points to the first 80000000h where the memcpy
```

## Source note 92, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L357)

```text
// sources from.
```

## Source note 93, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L358)

```text
// Count in words.
```

## Source note 94, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L360)

```text
// We could fake the commands here, but I'm not sure the game checks for
```

## Source note 95, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L361)

```text
// anything but success (non-zero ret).
```

## Source note 96, line 362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L362)

```text
// For now, we just fill it with NOPs.
```

## Source note 97, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L389)

```text
// BOOL return value
```

## Source note 98, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L394)

```text
// unk1_ptr needs to be populated with a pointer passed to
```

## Source note 99, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L395)

```text
// MmFreePhysicalMemory(1, *unk1_ptr).
```

## Source note 100, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L415)

```text
// ptr into primary ringbuffer
```

## Source note 101, line 416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L416)

```text
// frontbuffer Direct3D 9 texture header fetch
```

## Source note 102, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L417)

```text
// system writeback ptr
```

## Source note 103, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L418)

```text
// buffer from VdGetSystemCommandBuffer
```

## Source note 104, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L419)

```text
// from VdGetSystemCommandBuffer (0xBEEF0001)
```

## Source note 105, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L420)

```text
// ptr to frontbuffer address
```

## Source note 106, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L423)

```text
// All of these parameters are REQUIRED.
```

## Source note 107, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L437)

```text
// The fetch constant passed is not a true GPU fetch constant, but rather, the
```

## Source note 108, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L438)

```text
// fetch constant stored in the Direct3D 9 texture header, which contains the
```

## Source note 109, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L439)

```text
// address in one of the virtual mappings of the physical memory rather than
```

## Source note 110, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L440)

```text
// the physical address itself. We're emulating swapping in the GPU subsystem,
```

## Source note 111, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L441)

```text
// which works with GPU memory addresses (physical addresses directly) from
```

## Source note 112, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L442)

```text
// proper fetch constants like ones used to bind textures to shaders, not CPU
```

## Source note 113, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L443)

```text
// MMU addresses, so translation from virtual to physical is needed.
```

## Source note 114, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L450)

```text
// Xenia-specific safety check.
```

## Source note 115, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L461)

```text
// RGB(0)
```

## Source note 116, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L465)

```text
// The caller seems to reserve 64 words (256b) in the primary ringbuffer
```

## Source note 117, line 466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L466)

```text
// for this method to do what it needs. We just zero them out and send a
```

## Source note 118, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L467)

```text
// token value. It'd be nice to figure out what this is really doing so
```

## Source note 119, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L468)

```text
// that we could simulate it, though due to TCR I bet all games need to
```

## Source note 120, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L469)

```text
// use this method.
```

## Source note 121, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L475)

```text
// Write in the GPU texture fetch.
```

## Source note 122, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L492)

```text
// Fill the rest of the buffer with NOP packets.
```

## Source note 123, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L502)

```text
// VdGlobalDevice (4b)
```

## Source note 124, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L503)

```text
// Pointer to a global D3D device. Games only seem to set this, so we don't
```

## Source note 125, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L504)

```text
// have to do anything. We may want to read it back later, though.
```

## Source note 126, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L509)

```text
// VdGlobalXamDevice (4b)
```

## Source note 127, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L510)

```text
// Pointer to the XAM D3D device, which we don't have.
```

## Source note 128, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L515)

```text
// VdGpuClockInMHz (4b)
```

## Source note 129, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L516)

```text
// GPU clock. Xenos is 500MHz. Hope nothing is relying on this timing...
```

## Source note 130, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L521)

```text
// VdHSIOCalibrationLock (28b)
```

## Source note 131, line 522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L522)

```text
// CriticalSection.
```
