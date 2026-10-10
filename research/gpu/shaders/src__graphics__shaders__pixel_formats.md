# Pixel formats: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/pixel_formats.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L102)

```text
// ColorFormat packing, according to the Direct3D 11.3 functional specification.
```

## Source note 2, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L108)

```text
// Signed fraction uses the positive endpoint, then keeps the destination
```

## Source note 3, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L109)

```text
// bit width.
```

## Source note 4, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L121)

```text
// Unsigned fraction, float-on-fixed, or anything unexpected: keep the
```

## Source note 5, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L122)

```text
// usual unsigned-fraction pack.
```

## Source note 6, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L237)

```text
// Treat as something (16_FLOAT).
```

## Source note 7, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L293)

```text
// Treat as 32_FLOAT.
```

## Source note 8, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L326)

```text
// Treat as 32_32_FLOAT.
```

## Source note 9, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L333)

```text
// EDRAM color format unpacking.
```

## Source note 10, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L355)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 11, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L359)

```text
// Normalize the values for the denormalized components.
```

## Source note 12, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L360)

```text
// Exponent = 1;
```

## Source note 13, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L361)

```text
// do { Exponent--; Mantissa <<= 1; } while ((Mantissa & 0x80) == 0);
```

## Source note 14, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L368)

```text
// Combine into 32-bit float bits and clear zeros.
```

## Source note 15, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L375)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 16, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L379)

```text
// Normalize the values for the denormalized components.
```

## Source note 17, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L380)

```text
// Exponent = 1;
```

## Source note 18, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L381)

```text
// do { Exponent--; Mantissa <<= 1; } while ((Mantissa & 0x80) == 0);
```

## Source note 19, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L388)

```text
// Combine into 32-bit float bits and clear zeros.
```

## Source note 20, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L396)

```text
// http://web.archive.org/web/20180826210254/https://www.students.science.uu.nl/~3220516/advancedgraphics/papers/inferred_lighting.pdf
```

## Source note 21, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L397)

```text
// "The format of the DSF buffer (two 16 bit channels) in EDRAM is fixed point
```

## Source note 22, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L398)

```text
//  with a range of -32 to 32. The corresponding texture format is fixed point
```

## Source note 23, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L399)

```text
//  with a range of 0 to 1. This requires the shader to scale the shader output
```

## Source note 24, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L400)

```text
//  of 0 to 1 to -32 to 32. To maintain 16 bit precision, the texture used for
```

## Source note 25, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L401)

```text
//  the resolve needs to be created with a custom format that has a range of -1
```

## Source note 26, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L402)

```text
//  to 1. When sampling from this texture in a shader, the results must be
```

## Source note 27, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L403)

```text
//  scaled to a 0 to 1 range."
```

## Source note 28, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L405)

```text
// Upper 16 bits are ignored by XeUnpackR16EdramX4.
```

## Source note 29, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L424)

```text
// Xenos 16-bit packed textures are RGBA, but in Direct3D 12 they are BGRA.
```

## Source note 30, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L448)

```text
// RRRRR GGGGG BBBBBB to GGGGG BBBBBB RRRRR (use RBGA swizzle when reading).
```

## Source note 31, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L460)

```text
// Also usable for BGRA8 <> RGBA8, but that's not needed for texture loading.
```

## Source note 32, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L467)

```text
// On the Xenos, it appears that the last existing component of a texture is
```

## Source note 33, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L468)

```text
// replicated into the missing components. Writing blue directly to the alpha
```

## Source note 34, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L469)

```text
// instead of 1 also makes this conversion correct for both unsigned and signed
```

## Source note 35, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L470)

```text
// data.
```

## Source note 36, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L501)

```text
// Red and blue.
```

## Source note 37, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L508)

```text
// Green. The 5 bits to be duplicated to the bottom are already at 16.
```

## Source note 38, line 511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L511)

```text
// Alpha.
```

## Source note 39, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L523)

```text
// Red and blue.
```

## Source note 40, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L530)

```text
// Green.
```

## Source note 41, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L533)

```text
// Alpha.
```

## Source note 42, line 544

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L544)

```text
// Assuming the original number has only 10 bits.
```

## Source note 43, line 548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L548)

```text
// -512 and -511 are both -1.0, but with -512 the conversion will overflow.
```

## Source note 44, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L550)

```text
// Take the absolute value.
```

## Source note 45, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L553)

```text
// Expand the 9-bit absolute value to 15 bits like unorm.
```

## Source note 46, line 555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L555)

```text
// Apply the sign.
```

## Source note 47, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L560)

```text
// Assuming the original number has only 11 bits.
```

## Source note 48, line 564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L564)

```text
// -1024 and -1023 are both -1.0, but with -1024 the conversion will overflow.
```

## Source note 49, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L566)

```text
// Take the absolute value.
```

## Source note 50, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L569)

```text
// Expand the 10-bit absolute value to 15 bits like unorm.
```

## Source note 51, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L571)

```text
// Apply the sign.
```

## Source note 52, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L577)

```text
// uint4(RG0, RG1, BA0, BA1).xzyw == uint4(RG0, BA0, RG1, BA1).
```

## Source note 53, line 590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L590)

```text
// uint4(RG0, RG1, BA0, BA1).xzyw == uint4(RG0, BA0, RG1, BA1).
```

## Source note 54, line 624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L624)

```text
// Based on CFloat24 from d3dref9.dll and the 6e4 code from:
```

## Source note 55, line 625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L625)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 56, line 626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L626)

```text
// 6e4 has a different exponent bias allowing [0,512) values, 20e4 allows [0,2).
```

## Source note 57, line 627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L627)

```text
// We also can't clamp the stored value to 1 as load->store->load must be exact.
```

## Source note 58, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L630)

```text
// Keep only positive (high bit set means negative for both float and int) and
```

## Source note 59, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L631)

```text
// saturate to the maximum representable value near 2 (also dropping NaNs).
```

## Source note 60, line 645

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L645)

```text
// Normalize the values for the denormalized components.
```

## Source note 61, line 646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L646)

```text
// Exponent = 1;
```

## Source note 62, line 647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L647)

```text
// do { Exponent--; Mantissa <<= 1; } while ((Mantissa & 0x100000) == 0);
```

## Source note 63, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L653)

```text
// Combine into 32-bit float bits and clear zeros and, if needed, bias the
```

## Source note 64, line 654

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L654)

```text
// exponent.
```

## Source note 65, line 664

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L664)

```text
// Normalize the values for the denormalized components.
```

## Source note 66, line 665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L665)

```text
// Exponent = 1;
```

## Source note 67, line 666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L666)

```text
// do { Exponent--; Mantissa <<= 1; } while ((Mantissa & 0x100000) == 0);
```

## Source note 68, line 673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L673)

```text
// Combine into 32-bit float bits and clear zeros.
```

## Source note 69, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L683)

```text
// Not 1.0f / 16777215.0f as that gives an incorrect result (like for a very
```

## Source note 70, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L684)

```text
// common 0xC00000 which clears 2_10_10_10 to 0001). Division by 2^24 is just
```

## Source note 71, line 685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L685)

```text
// an exponent shift though, thus exact.
```

## Source note 72, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L686)

```text
// Division by 16777215.0f behaves this way.
```

## Source note 73, line 694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L694)

```text
// Converts endpoint BGR (first - X of the return value - in the low 16 bits,
```

## Source note 74, line 695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L695)

```text
// second - Y of the return value - in the high) of a DXT blocks to 8-bit, with
```

## Source note 75, line 696

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L696)

```text
// 2 unused bits between each component to allow for overflow when multiplying
```

## Source note 76, line 697

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L697)

```text
// by values up to 3 (so multiplication can be done for all components at once).
```

## Source note 77, line 698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L698)

```text
// Relative ordering between endpoints is preserved, so result.x > result.y
```

## Source note 78, line 699

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L699)

```text
// (color0 > color1) and result.x <= result.y (color0 <= color1) can be used for
```

## Source note 79, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L700)

```text
// choosing the DXT1 mode.
```

## Source note 80, line 702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L702)

```text
// Converting 5:6:5 to 8:8:8 similar to how Compressonator does that.
```

## Source note 81, line 703

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L703)

```text
// https://github.com/GPUOpen-Tools/compressonator/blob/master/CMP_CompressonatorLib/DXTC/Codec_DXTC_RGBA.cpp#L340
```

## Source note 82, line 705

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L705)

```text
// Blue in 0:4 and 16:20 - to 3:7.
```

## Source note 83, line 707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L707)

```text
// Green in 5:10 and 21:26 - to 12:17.
```

## Source note 84, line 710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L710)

```text
// Red in 11:15 and 27:31 - to 23:27.
```

## Source note 85, line 713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L713)

```text
// Apply the lower bit replication to give full dynamic range.
```

## Source note 86, line 714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L714)

```text
// Blue and red.
```

## Source note 87, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L716)

```text
// Green.
```

## Source note 88, line 721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L721)

```text
// Sorts the color indices of a DXT3/DXT5 or a DXT1 opaque block so they can be
```

## Source note 89, line 722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L722)

```text
// used as the weights for the second endpoint, from 0 to 3. To get the weights
```

## Source note 90, line 723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L723)

```text
// for the first endpoint, apply bitwise NOT to the result.
```

## Source note 91, line 725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L725)

```text
// Initially 00 = 3:0, 01 = 0:3, 10 = 2:1, 11 = 1:2.
```

## Source note 92, line 726

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L726)

```text
// Swap bits. 00 = 3:0, 01 = 2:1, 10 = 0:3, 11 = 1:2.
```

## Source note 93, line 728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L728)

```text
// Swap 10 and 11. 00 = 3:0, 01 = 2:1, 10 = 1:2, 11 = 0:3.
```

## Source note 94, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L738)

```text
// Get the RGB colors of one row of a DXT opaque block. Endpoint colors can be
```

## Source note 95, line 739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L739)

```text
// obtained using XeDXTColorEndpointsToBGR8In10 (8 bits with 2 bits of free
```

## Source note 96, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L740)

```text
// space between each), weights can be obtained using XeDXTHighColorWeights.
```

## Source note 97, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L741)

```text
// Alpha is set to 0 in the result. Weights must be shifted right by 8 * row
```

## Source note 98, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L742)

```text
// index before calling.
```

## Source note 99, line 753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L753)

```text
// Sort the color indices of four transparent DXT1 blocks so bits of them can be
```

## Source note 100, line 754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L754)

```text
// used as endpoint weights (lower bit for the low endpoint, upper bit for the
```

## Source note 101, line 755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L755)

```text
// high endpoint, and both bits for 1/2 of each, AND of those bits can be used
```

## Source note 102, line 756

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L756)

```text
// as the right shift amount for mixing the two colors in the punchthrough
```

## Source note 103, line 757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L757)

```text
// mode). Zero for the punchthrough alpha texels.
```

## Source note 104, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L759)

```text
// Initially 00 = 1:0, 01 = 0:1, 10 = 1:1, 11 = 0:0.
```

## Source note 105, line 760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L760)

```text
// 00 = 0:0, 01 = 1:1, 10 = 0:1, 11 = 1:0.
```

## Source note 106, line 762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L762)

```text
// 00 = 0:0, 01 = 1:0, 10 = 0:1, 11 = 1:1.
```

## Source note 107, line 766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L766)

```text
// Gets the RGBA colors of one row of a DXT1 punchthrough block. Endpoint colors
```

## Source note 108, line 767

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L767)

```text
// can be obtained using XeDXTColorEndpointsToBGR8In10 (8 bits with 2 bits of
```

## Source note 109, line 768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L768)

```text
// free space between each), weights can be obtained using XeDXT1TransWeights
```

## Source note 110, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L769)

```text
// and must be shifted right by 8 * row index before calling.
```

## Source note 111, line 776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L776)

```text
// Whether the texel is (RGB0+RGB1)/2 - divide the weighted sum by 2 (shift
```

## Source note 112, line 777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L777)

```text
// right by 1) if it is.
```

## Source note 113, line 781

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L781)

```text
// Whether the texel is opaque.
```

## Source note 114, line 791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L791)

```text
// Converts one row of four DXT3 alpha blocks to 16 packed R8 texels, useful for
```

## Source note 115, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L792)

```text
// converting DXT3A. Only 16 bits of alpha half-blocks are used. Alpha is from
```

## Source note 116, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L793)

```text
// word 0 for rows 0 and 1, from word 1 for rows 2 and 3, must be shifted right
```

## Source note 117, line 794

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L794)

```text
// by 16 * (row index & 1) before calling.
```

## Source note 118, line 796

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L796)

```text
// (alphas & 0xFu) | ((alphas & 0xFu) << 4u) |
```

## Source note 119, line 797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L797)

```text
// ((alphas & 0xF0u) << (8u - 4u)) | ((alphas & 0xF0u) << (12u - 4u)) |
```

## Source note 120, line 798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L798)

```text
// ((alphas & 0xF00u) << (16u - 8u)) | ((alphas & 0xF00u) << (20u - 8u)) |
```

## Source note 121, line 799

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L799)

```text
// ((alphas & 0xF000u) << (24u - 12u)) | ((alphas & 0xF000u) << (28u - 12u))
```

## Source note 122, line 806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L806)

```text
// Only 16 bits of half-blocks are used. X contains pixels 0123, Y - 4567 (in
```

## Source note 123, line 807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L807)

```text
// the image, halfblocks.y is halfblocks.x + 8).
```

## Source note 124, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L808)

```text
// In the row, X contains pixels 01, Y - 23, Z - 45, W - 67.
```

## Source note 125, line 809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L809)

```text
// Assuming alpha in LSB and red in MSB, because it's consistent with how
```

## Source note 126, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L810)

```text
// DXT1/DXT3/DXT5 color components and CTX1 X/Y are ordered in:
```

## Source note 127, line 811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L811)

```text
// http://fileadmin.cs.lth.se/cs/Personal/Michael_Doggett/talks/unc-xenos-doggett.pdf
```

## Source note 128, line 812

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L812)

```text
// (LSB on the right, MSB on the left.)
```

## Source note 129, line 833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L833)

```text
// Only 16 bits of half-blocks are used. X contains pixels 0123, Y - 4567 (in
```

## Source note 130, line 834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L834)

```text
// the image, halfblocks.y is halfblocks.x + 8).
```

## Source note 131, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L835)

```text
// In the row, X contains pixels 01, Y - 23, Z - 45, W - 67.
```

## Source note 132, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L836)

```text
// Assuming alpha in LSB and red in MSB, because it's consistent with how
```

## Source note 133, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L837)

```text
// DXT1/DXT3/DXT5 color components and CTX1 X/Y are ordered in:
```

## Source note 134, line 838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L838)

```text
// http://fileadmin.cs.lth.se/cs/Personal/Michael_Doggett/talks/unc-xenos-doggett.pdf
```

## Source note 135, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L839)

```text
// (LSB on the right, MSB on the left.)
```

## Source note 136, line 859

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L859)

```text
// & 0x249249 = bits 0 of 24 bits of DXT5 alpha codes.
```

## Source note 137, line 860

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L860)

```text
// & 0x492492 = bits 1 of 24 bits of DXT5 alpha codes.
```

## Source note 138, line 861

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L861)

```text
// & 0x924924 = bits 2 of 24 bits of DXT5 alpha codes.
```

## Source note 139, line 863

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L863)

```text
// Sorts half (24 bits) of the codes of a DXT5 alpha block so they can be used
```

## Source note 140, line 864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L864)

```text
// as weights for the second endpoint, from 0 to 7, in alpha0 > alpha1 mode.
```

## Source note 141, line 866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L866)

```text
// Initially 000 - first endpoint, 001 - second endpoint, 010 and above -
```

## Source note 142, line 867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L867)

```text
// weights from 6:1 to 1:6. Need to make 001 111, and subtract 1 from 010 and
```

## Source note 143, line 868

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L868)

```text
// above.
```

## Source note 144, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L869)

```text
// Whether the bits are 000 (the first endpoint only).
```

## Source note 145, line 872

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L872)

```text
// Whether the bits are 001 (the second endpoint only).
```

## Source note 146, line 875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L875)

```text
// Change 000 to 001 so subtracting 1 will result in 0 (and there will never
```

## Source note 147, line 876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L876)

```text
// be overflow), subtract 1, and if the code was originally 001 (the second
```

## Source note 148, line 877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L877)

```text
// endpoint only), make it 111.
```

## Source note 149, line 882

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L882)

```text
// Sorts half (24 bits) of the codes of a DXT5 alpha block so they can be used
```

## Source note 150, line 883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L883)

```text
// as weights for the second endpoint, from 0 to 5, in alpha0 <= alpha1 mode,
```

## Source note 151, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L884)

```text
// except for 110 and 111 which represent 0 and 1 constants.
```

## Source note 152, line 887

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L887)

```text
// 000 - first endpoint.
```

## Source note 153, line 888

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L888)

```text
// 001 - second endpoint.
```

## Source note 154, line 889

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L889)

```text
// 010 - 4:1.
```

## Source note 155, line 890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L890)

```text
// 011 - 3:2.
```

## Source note 156, line 891

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L891)

```text
// 100 - 2:3.
```

## Source note 157, line 892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L892)

```text
// 101 - 1:4.
```

## Source note 158, line 893

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L893)

```text
// 110 - constant 0.
```

## Source note 159, line 894

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L894)

```text
// 111 - constant 1.
```

## Source note 160, line 895

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L895)

```text
// Create 3-bit masks (111 or 000) of whether the codes represent 0 or 1
```

## Source note 161, line 896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L896)

```text
// constants to keep them 110 and 111 later.
```

## Source note 162, line 899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L899)

```text
// Store the codes for the constants (110 or 111), or 0 if not a constant.
```

## Source note 163, line 902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L902)

```text
// Need to make 001 101, and subtract 1 from 010 and above (constants will be
```

## Source note 164, line 903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L903)

```text
// handled separately later).
```

## Source note 165, line 904

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L904)

```text
// Whether the bits are 000 (the first endpoint only).
```

## Source note 166, line 907

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L907)

```text
// Whether the bits are 001 (the second endpoint only).
```

## Source note 167, line 910

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L910)

```text
// Change 000 to 001 so subtracting 1 will result in 0 (and there will never
```

## Source note 168, line 911

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L911)

```text
// be overflow), subtract 1, and if the code was originally 001 (the second
```

## Source note 169, line 912

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L912)

```text
// endpoint only), make it 101.
```

## Source note 170, line 915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L915)

```text
// Make constants 110 and 111 again (they are 101 and 110 now).
```

## Source note 171, line 919

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L919)

```text
// Sorts half (24 bits) of the codes of a DXT5 alpha block so they can be used
```

## Source note 172, line 920

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L920)

```text
// as weights for XeDXT5RowToA8.
```

## Source note 173, line 926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L926)

```text
// Get alphas of a DXT5 alpha row in alpha0 > alpha1 mode. Endpoint alphas are
```

## Source note 174, line 927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L927)

```text
// in bits 0:7 and 8:15 of the first dword, weights can be obtained using
```

## Source note 175, line 928

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L928)

```text
// XeDXT5High8StepAlphaWeights and must be shifted right by 12 * (row index & 1)
```

## Source note 176, line 929

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L929)

```text
// before calling.
```

## Source note 177, line 942

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L942)

```text
// Version of XeDXT58StepRowToA8 that returns values packed in low 8 bits of
```

## Source note 178, line 943

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L943)

```text
// 16-bit parts, for DXN decompression.
```

## Source note 179, line 956

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L956)

```text
// Get alphas of a DXT5 alpha row in alpha0 <= alpha1 mode. Endpoint alphas are
```

## Source note 180, line 957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L957)

```text
// in bits 0:7 and 8:15 of the first dword, weights can be obtained using
```

## Source note 181, line 958

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L958)

```text
// XeDXT5High6StepAlphaWeights and must be shifted right by 12 * (row index & 1)
```

## Source note 182, line 959

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L959)

```text
// before calling.
```

## Source note 183, line 961

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L961)

```text
// Make a mask for whether the weights are constants.
```

## Source note 184, line 964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L964)

```text
// Get the weights for the first endpoint and remove constant from the
```

## Source note 185, line 965

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L965)

```text
// interpolation (set weights of the endpoints to 0 for them). First need to
```

## Source note 186, line 966

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L966)

```text
// zero the weights of the second endpoint so 6 or 7 won't be subtracted from
```

## Source note 187, line 967

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L967)

```text
// 5 while getting the weights of the first endpoint.
```

## Source note 188, line 970

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L970)

```text
// Interpolate.
```

## Source note 189, line 979

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L979)

```text
// Get the constant values as 1 bit per pixel separated by 7 bits.
```

## Source note 190, line 985

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L985)

```text
// Add constant 1 where needed.
```

## Source note 191, line 989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L989)

```text
// Version of XeDXT56StepRowToA8 that returns values packed in low 8 bits of
```

## Source note 192, line 990

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L990)

```text
// 16-bit parts, for DXN decompression.
```

## Source note 193, line 992

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L992)

```text
// Make a mask for whether the weights are constants.
```

## Source note 194, line 995

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L995)

```text
// Get the weights for the first endpoint and remove constant from the
```

## Source note 195, line 996

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L996)

```text
// interpolation (set weights of the endpoints to 0 for them). First need to
```

## Source note 196, line 997

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L997)

```text
// zero the weights of the second endpoint so 6 or 7 won't be subtracted from
```

## Source note 197, line 998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L998)

```text
// 5 while getting the weights of the first endpoint.
```

## Source note 198, line 1001

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1001)

```text
// Interpolate.
```

## Source note 199, line 1010

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1010)

```text
// Get the constant values as 1 bit per pixel separated by 7 bits.
```

## Source note 200, line 1016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1016)

```text
// Add constant 1 where needed.
```

## Source note 201, line 1020

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1020)

```text
// Get alphas of a DXT5 alpha row. Endpoint alphas are in bits 0:7 and 8:15 of
```

## Source note 202, line 1021

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1021)

```text
// the first dword, weights can be obtained using XeDXT5HighAlphaWeights and
```

## Source note 203, line 1022

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1022)

```text
// must be shifted right by 12 * (row index & 1) before calling.
```

## Source note 204, line 1028

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1028)

```text
// Version of XeDXT5RowToA8 that returns values packed in low 8 bits of 16-bit
```

## Source note 205, line 1029

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1029)

```text
// parts, for DXN decompression.
```

## Source note 206, line 1035

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1035)

```text
// Converts one row of two CTX1 blocks to R8G8. Endpoints of block 0 in XY and
```

## Source note 207, line 1036

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1036)

```text
// of block 1 in ZW must be unpacked from 0xRRGGrrgg to 0x00gg00rr 0x00GG00RR so
```

## Source note 208, line 1037

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1037)

```text
// they can be multiplied by weights with room for overflow. Weights can be
```

## Source note 209, line 1038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1038)

```text
// obtained using XeDXTHighColorWeights and must be shifted right by 8 * row
```

## Source note 210, line 1039

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/pixel_formats.xesli#L1039)

```text
// index before calling.
```
