# Dxbc translator memexport: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/dxbc_translator_memexport.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L30)

```text
// Check if memory export is allowed in this invocation.
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L33)

```text
// Check if the address with the correct sign and exponent was written, and
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L34)

```text
// that the index doesn't overflow the mantissa bits.
```

## Source note 4, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L47)

```text
// Release address_check_temp.
```

## Source note 5, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L54)

```text
// Swap red and blue components if needed.
```

## Source note 6, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L60)

```text
// Release red_blue_swap_temp.
```

## Source note 7, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L70)

```text
// Close the red/blue swap conditional.
```

## Source note 8, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L76)

```text
// Extract the color format and the numeric format.
```

## Source note 9, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L77)

```text
// temp.x = color format.
```

## Source note 10, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L78)

```text
// temp.y = numeric format is signed.
```

## Source note 11, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L79)

```text
// temp.z = numeric format is integer.
```

## Source note 12, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L83)

```text
// Perform format packing.
```

## Source note 13, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L84)

```text
// After the switch, temp.x must contain log2 of the number of bytes in an
```

## Source note 14, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L85)

```text
// element, of UINT32_MAX if the format is unknown.
```

## Source note 15, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L103)

```text
// Release is_nan_temp.
```

## Source note 16, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L107)

```text
// The result will be in eM#.x. The widths must be without holes (R, RG,
```

## Source note 17, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L108)

```text
// RGB, RGBA), and expecting the widths to add up to the size of the stored
```

## Source note 18, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L109)

```text
// texel (8, 16 or 32 bits), as the unused upper bits will contain junk from
```

## Source note 19, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L110)

```text
// the sign extension of X if the number is signed.
```

## Source note 20, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L119)

```text
// Only formats for which max + 0.5 can be represented exactly.
```

## Source note 21, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L127)

```text
// Will be packing components into eM#.x starting from green, assume red
```

## Source note 22, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L128)

```text
// will already be there after the conversion.
```

## Source note 23, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L135)

```text
// Signed.
```

## Source note 24, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L138)

```text
// Signed integer.
```

## Source note 25, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L158)

```text
// Signed normalized.
```

## Source note 26, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L181)

```text
// Add plus/minus 0.5 before truncating according to the Direct3D format
```

## Source note 27, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L182)

```text
// conversion rules, and convert to signed integers.
```

## Source note 28, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L193)

```text
// Release round_bias_temp.
```

## Source note 29, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L198)

```text
// Unsigned.
```

## Source note 30, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L201)

```text
// Unsigned integer.
```

## Source note 31, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L217)

```text
// Unsigned normalized.
```

## Source note 32, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L231)

```text
// Saturate.
```

## Source note 33, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L240)

```text
// Add 0.5 before truncating according to the Direct3D format conversion
```

## Source note 34, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L241)

```text
// rules, and convert to unsigned integers.
```

## Source note 35, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L252)

```text
// Pack into 32 bits.
```

## Source note 36, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L367)

```text
// Signed.
```

## Source note 37, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L370)

```text
// Signed integer.
```

## Source note 38, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L381)

```text
// Signed normalized.
```

## Source note 39, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L393)

```text
// Add plus/minus 0.5 before truncating according to the Direct3D format
```

## Source note 40, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L394)

```text
// conversion rules, and convert to signed integers.
```

## Source note 41, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L405)

```text
// Release round_bias_temp.
```

## Source note 42, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L410)

```text
// Unsigned.
```

## Source note 43, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L413)

```text
// Unsigned integer.
```

## Source note 44, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L424)

```text
// Unsigned normalized.
```

## Source note 45, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L429)

```text
// Saturate.
```

## Source note 46, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L436)

```text
// Add 0.5 before truncating according to the Direct3D format conversion
```

## Source note 47, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L437)

```text
// rules, and convert to unsigned integers.
```

## Source note 48, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L448)

```text
// Pack.
```

## Source note 49, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L503)

```text
// Already in eM#.
```

## Source note 50, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L510)

```text
// Already in eM#.
```

## Source note 51, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L517)

```text
// Already in eM#.
```

## Source note 52, line 526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L526)

```text
// Close the color format switch.
```

## Source note 53, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L531)

```text
// Only temp.x is used currently (for the element size log2).
```

## Source note 54, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L533)

```text
// Do endian swap, using temp.y for the endianness value, and temp.z as a
```

## Source note 55, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L534)

```text
// temporary value.
```

## Source note 56, line 538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L538)

```text
// Extract endianness into temp.y.
```

## Source note 57, line 542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L542)

```text
// Change 8-in-64 and 8-in-128 to 8-in-32.
```

## Source note 58, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L561)

```text
// 8-in-16 or one half of 8-in-32.
```

## Source note 59, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L571)

```text
// Temp = X0Z0.
```

## Source note 60, line 573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L573)

```text
// eM = YZW0.
```

## Source note 61, line 575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L575)

```text
// eM = Y0W0.
```

## Source note 62, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L577)

```text
// eM = YXWZ.
```

## Source note 63, line 583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L583)

```text
// 16-in-32 or another half of 8-in-32.
```

## Source note 64, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L593)

```text
// Temp = ZW00.
```

## Source note 65, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L595)

```text
// eM = ZWXY.
```

## Source note 66, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L601)

```text
// Release swap_temp.
```

## Source note 67, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L605)

```text
// Extract the base index to temp.y and the index upper bound to temp.z.
```

## Source note 68, line 612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L612)

```text
// Check if eM0 isn't out of bounds via temp.w - if it is, eM1...4 also are
```

## Source note 69, line 613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L613)

```text
// (the base index can't be negative).
```

## Source note 70, line 617

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L617)

```text
// Extract the base address to temp.w as bytes (30 lower bits to 30 upper bits
```

## Source note 71, line 618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L618)

```text
// with 0 below).
```

## Source note 72, line 627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L627)

```text
// Get eM1...4 indices and check if they're in bounds.
```

## Source note 73, line 636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L636)

```text
// Check if eM1...4 were actually written by the invocation and merge the
```

## Source note 74, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L637)

```text
// result with store_eM14_temp.
```

## Source note 75, line 643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L643)

```text
// Release eM14_written_temp.
```

## Source note 76, line 645

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L645)

```text
// Convert eM1...4 indices to global byte addresses.
```

## Source note 77, line 650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L650)

```text
// Convert eM0 index to a global byte address if it's needed.
```

## Source note 78, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L653)

```text
// base_address_src and index_count_src are deallocated at this point (even
```

## Source note 79, line 654

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L654)

```text
// if eM0 isn't potentially written), temp.zw are now free.
```

## Source note 80, line 655

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L655)

```text
// Extract if eM0 was actually written by the invocation to temp.z.
```

## Source note 81, line 661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L661)

```text
// Write depending on the element size.
```

## Source note 82, line 662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L662)

```text
// No switch case will be entered for an unknown format (UINT32_MAX size
```

## Source note 83, line 663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L663)

```text
// written), so writing won't be attempted for it.
```

## Source note 84, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L671)

```text
// 8bpp, 16bpp.
```

## Source note 85, line 680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L680)

```text
// sub_dword_temp.x = eM0 offset in the dword (8 << (byte_address & 3))
```

## Source note 86, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L681)

```text
// (assuming a little-endian host).
```

## Source note 87, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L684)

```text
// Keep only the dword part of the address.
```

## Source note 88, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L686)

```text
// Erase the bits that will be replaced with eM0 via sub_dword_temp.y.
```

## Source note 89, line 692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L692)

```text
// Add the eM0 bits via sub_dword_temp.y.
```

## Source note 90, line 701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L701)

```text
// sub_dword_temp = eM# offset in the dword (8 << (byte_address & 3))
```

## Source note 91, line 702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L702)

```text
// (assuming a little-endian host).
```

## Source note 92, line 705

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L705)

```text
// Keep only the dword part of the address.
```

## Source note 93, line 713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L713)

```text
// Erase the bits that will be replaced with eM# via
```

## Source note 94, line 714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L714)

```text
// sub_dword_data_temp.x.
```

## Source note 95, line 720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L720)

```text
// Add the eM# bits via sub_dword_temp.y.
```

## Source note 96, line 729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L729)

```text
// Release sub_dword_data_temp.
```

## Source note 97, line 732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L732)

```text
// Release sub_dword_temp.
```

## Source note 98, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L737)

```text
// 32bpp, 64bpp, 128bpp.
```

## Source note 99, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L740)

```text
// Store (0b0001), Store2 (0b0011), Store4 (0b1111).
```

## Source note 100, line 760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L760)

```text
// Close the element size switch.
```

## Source note 101, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L764)

```text
// Release eM14_address_temp and store_eM14_temp.
```

## Source note 102, line 768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L768)

```text
// Close the eM0 bounds check.
```

## Source note 103, line 771

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L771)

```text
// Release temp.
```

## Source note 104, line 774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L774)

```text
// Close the address correctness conditional.
```

## Source note 105, line 777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L777)

```text
// Close the memory export allowed conditional.
```
