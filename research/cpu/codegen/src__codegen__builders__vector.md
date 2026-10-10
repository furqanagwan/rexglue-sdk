# Vector: codegen source notes

This record preserves technical and API notes moved from `src/codegen/builders/vector.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L28)

```text
// SIMD Constants Documentation
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L30)

```text
// This file uses several magic constants from Intel SSE/SSE4 intrinsics.
```

## Source note 3, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L31)

```text
// Here are the key constants and their meanings:
```

## Source note 4, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L33)

```text
// === Dot Product Masks (simde_mm_dp_ps) ===
```

## Source note 5, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L34)

```text
// The mask byte controls which elements participate in the dot product and
```

## Source note 6, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L35)

```text
// where the result is broadcast. Format: 0bAAAABBBB
```

## Source note 7, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L36)

```text
//   High nibble (AAAA): Which source elements to multiply (bit 7=x, 6=y, 5=z, 4=w)
```

## Source note 8, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L37)

```text
//   Low nibble (BBBB):  Which destination elements receive the result
```

## Source note 9, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L39)

```text
// 0xEF = 0b11101111: Dot product of elements y,z,w (bits 765 set), result to all (bits 3210 set)
```

## Source note 10, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L40)

```text
//        This computes dot(yzw) due to guest->host vector element reversal.
```

## Source note 11, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L41)

```text
// 0xFF = 0b11111111: Full 4-element dot product, result broadcast to all elements
```

## Source note 12, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L43)

```text
// === Floating-Point Sign Bit ===
```

## Source note 13, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L44)

```text
// 0x80000000: IEEE 754 sign bit mask for 32-bit float
```

## Source note 14, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L45)

```text
//             Used for negation via XOR and sign extraction
```

## Source note 15, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L47)

```text
// === IEEE 754 Single Precision Exponent ===
```

## Source note 16, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L48)

```text
// 0x7f800000: Exponent field mask (bits 23-30) for float
```

## Source note 17, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L49)

```text
// 0x7FFFFFFF: Magnitude mask (clears sign bit)
```

## Source note 18, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L50)

```text
// 0x3F800000: IEEE 754 representation of 1.0f (used for OR-ing in exponent)
```

## Source note 19, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L51)

```text
// 0x40400000: IEEE 754 representation of 3.0f (D3D NORMSHORT encoding bias)
```

## Source note 20, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L53)

```text
// === Half-Float (FP16) Conversion ===
```

## Source note 21, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L54)

```text
// 0x7C00: FP16 exponent mask
```

## Source note 22, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L55)

```text
// 0x1C000: Exponent bias adjustment for FP16->FP32 conversion
```

## Source note 23, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L56)

```text
// 0x8000: FP16 sign bit
```

## Source note 24, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L57)

```text
// 0x03FF: FP16 mantissa mask
```

## Source note 25, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L58)

```text
// 0x7FFF: FP16 positive infinity/max value
```

## Source note 26, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L60)

```text
// === Packed Integer Masks ===
```

## Source note 27, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L61)

```text
// 0x3FF: 10-bit mask for NORMPACKED32 format (10 bits per component)
```

## Source note 28, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L62)

```text
// 0xFFFFF: 20-bit mask for NORMPACKED64 format
```

## Source note 29, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L63)

```text
// 0x1F: 5-bit mask for shift amounts (shifts are mod 32)
```

## Source note 30, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L64)

```text
// 0xFF: 8-bit mask for byte values
```

## Source note 31, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L65)

```text
// 0xFFFF: 16-bit mask for halfword values
```

## Source note 32, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L67)

```text
// === D3D Color Format ===
```

## Source note 33, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L68)

```text
// 0x404000FF: D3D color packing constant (ARGB8888)
```

## Source note 34, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L72)

```text
// Vector Floating Point Arithmetic
```

## Source note 35, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L76)

```text
// Guest word 3 is host lane 0. Only NJ and SAT have defined local behavior.
```

## Source note 36, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L121)

```text
// (vA x vC) + vB, with PowerPC NaN rules (rex/ppc/fp.h).
```

## Source note 37, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L132)

```text
// -((vA x vC) - vB); a NaN result keeps its sign (rex/ppc/fp.h).
```

## Source note 38, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L160)

```text
// TODO: see if we can use rcp safely
```

## Source note 39, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L167)

```text
// The Xenon's estimate, from a table (rex/ppc/fp.h).
```

## Source note 40, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L174)

```text
// The Xenon 2^x estimate (rex/ppc/fp.h).
```

## Source note 41, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L181)

```text
// The Xenon log2 estimate (rex/ppc/fp.h).
```

## Source note 42, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L188)

```text
// Vector Dot Products
```

## Source note 43, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L192)

```text
// 3-element dot product accounting for guest->host vector element reversal
```

## Source note 44, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L193)

```text
// 0xEF = dot(yzw) with result broadcast to all elements (see constants doc)
```

## Source note 45, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L203)

```text
// 4-element dot product: 0xFF = all 4 elements, result to all (see constants doc)
```

## Source note 46, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L213)

```text
// Vector Rounding
```

## Source note 47, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L249)

```text
// Vector Integer Arithmetic
```

## Source note 48, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L292)

```text
// vaddsws: Vector Add Signed Word Saturate
```

## Source note 49, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L298)

```text
// No direct SSE intrinsic, so use overflow detection and blend
```

## Source note 50, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L302)

```text
// Overflow if: (a ^ sum) & (b ^ sum) has MSB set (signs of a,b match but sum differs)
```

## Source note 51, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L306)

```text
// Saturation value: if a positive (MSB=0), use INT32_MAX;
```

## Source note 52, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L307)

```text
// if negative, use INT32_MIN (a >> 31) gives all 1s if negative, all 0s
```

## Source note 53, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L308)

```text
// if positive XOR with 0x7FFFFFFF: negative -> 0x80000000, positive -> 0x7FFFFFFF
```

## Source note 54, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L312)

```text
// Blend: select sat_val where overflow MSB is set, else sum
```

## Source note 55, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L397)

```text
// TODO: vectorize
```

## Source note 56, line 514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L514)

```text
// Vector Average
```

## Source note 57, line 556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L556)

```text
// Vector Logical
```

## Source note 58, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L565)

```text
// vandc128: vD = vA & ~vB (simde_mm_andnot_si128 has reversed operand semantics)
```

## Source note 59, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L571)

```text
// vandc: vD = vA & ~vB (simde_mm_andnot_si128 has reversed operand semantics)
```

## Source note 60, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L605)

```text
// vnor: vD = ~(vA | vB)
```

## Source note 61, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L630)

```text
// Vector Compare
```

## Source note 62, line 635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L635)

```text
// vcmpbfp: Vector Compare Bounds Floating Point
```

## Source note 63, line 636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L636)

```text
// For each element i:
```

## Source note 64, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L637)

```text
//   bit 0 (0x80000000) = 1 if vSrcA[i] > vSrcB[i]
```

## Source note 65, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L638)

```text
//   bit 1 (0x40000000) = 1 if vSrcA[i] < -vSrcB[i]
```

## Source note 66, line 643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L643)

```text
// A NaN in either operand is out of bounds both ways (rex/ppc/fp.h).
```

## Source note 67, line 649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L649)

```text
// CR6 from vD: movemask_ps only checks bit 31, but lower-bound violations only
```

## Source note 68, line 650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L650)

```text
// set bit 30. Shift left by 1 to move bit 30 into bit 31, then OR with original
```

## Source note 69, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L651)

```text
// so movemask detects both upper and lower bound violations. vcmpbfp. sets
```

## Source note 70, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L652)

```text
// only CR6[2] (every element in bounds): 0x10 never matches, so CR6[0] stays
```

## Source note 71, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L653)

```text
// clear.
```

## Source note 72, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L792)

```text
// Vector Conversion
```

## Source note 73, line 841

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L841)

```text
// Vector Convert To Unsigned Fixed-Point Word Saturate
```

## Source note 74, line 854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L854)

```text
// Vector Merge
```

## Source note 75, line 888

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L888)

```text
// Vector Permute
```

## Source note 76, line 902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L902)

```text
// NOTE: accounting for full vector reversal here
```

## Source note 77, line 927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L927)

```text
// Vector Shift
```

## Source note 78, line 956

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L956)

```text
// TODO(tomc): vectorize
```

## Source note 79, line 964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L964)

```text
// TODO(tomc): vectorize
```

## Source note 80, line 977

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L977)

```text
// Rotate each byte left by the low 3 bits of the matching byte of vB.
```

## Source note 81, line 1005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1005)

```text
// TODO(tomc): vectorize
```

## Source note 82, line 1016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1016)

```text
// Vector Shift Left (128-bit) - shift entire vector left by bits specified in low 3 bits of vB
```

## Source note 83, line 1026

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1026)

```text
// Vector Shift Left by Octet - shift entire vector left by bytes specified in bits 121:124 of vB
```

## Source note 84, line 1036

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1036)

```text
// Vector Shift Right by Octet - shift entire vector right by bytes specified in bits 121:124 of
```

## Source note 85, line 1072

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1072)

```text
// TODO(tomc): vectorize
```

## Source note 86, line 1080

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1080)

```text
// TODO(tomc): vectorize
```

## Source note 87, line 1088

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1088)

```text
// Vector Splat
```

## Source note 88, line 1092

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1092)

```text
// NOTE: accounting for full vector reversal here
```

## Source note 89, line 1103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1103)

```text
// NOTE: accounting for full vector reversal here
```

## Source note 90, line 1115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1115)

```text
// Sign-extend 5-bit immediate to 8-bit
```

## Source note 91, line 1123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1123)

```text
// Sign-extend 5-bit immediate to 32-bit
```

## Source note 92, line 1131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1131)

```text
// Sign-extend 5-bit immediate to 16-bit
```

## Source note 93, line 1139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1139)

```text
// NOTE: accounting for full vector reversal here
```

## Source note 94, line 1150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1150)

```text
// Vector Pack
```

## Source note 95, line 1164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1164)

```text
// Vector Pack Unsigned Halfword Unsigned Modulo - pack low 8 bits from each halfword
```

## Source note 96, line 1176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1176)

```text
// Vector Pack Unsigned Halfword Unsigned Saturate
```

## Source note 97, line 1177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1177)

```text
// NOTE(tomc): _mm_packus_epi16 treats inputs as signed, so we need custom saturation for
```

## Source note 98, line 1178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1178)

```text
// unsigned. Unsigned halfwords >= 0x8000 would be interpreted as negative and clamped to 0
```

## Source note 99, line 1179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1179)

```text
// instead of 0xFF.
```

## Source note 100, line 1180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1180)

```text
// vD can alias vA/vB, so pack into vTemp first.
```

## Source note 101, line 1192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1192)

```text
// Vector Pack Unsigned Word Unsigned Modulo - pack low 16 bits from each word
```

## Source note 102, line 1205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1205)

```text
// Vector Pack Unsigned Word Unsigned Saturate
```

## Source note 103, line 1207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1207)

```text
// NOTE(tomc): _mm_packus_epi32 treats inputs as signed, so we need custom saturation for unsigned
```

## Source note 104, line 1208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1208)

```text
// Saturate each u32 to [0, 0xFFFF], then pack to u16
```

## Source note 105, line 1209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1209)

```text
// vD can alias vA/vB, so pack into vTemp first.
```

## Source note 106, line 1222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1222)

```text
// Vector Pack Signed Halfword Signed Saturate
```

## Source note 107, line 1233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1233)

```text
// Vector Pack Signed Word Signed Saturate
```

## Source note 108, line 1244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1244)

```text
// Vector Pack Signed Word Unsigned Saturate
```

## Source note 109, line 1254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1254)

```text
// Guest pixels are ARGB8888 and the packed result is A1R5G5B5.
```

## Source note 110, line 1255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1255)

```text
// Snapshot both inputs so vD may alias either source register.
```

## Source note 111, line 1273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1273)

```text
// TODO(tomc): vectorize
```

## Source note 112, line 1274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1274)

```text
// NOTE: handling vector reversal here too
```

## Source note 113, line 1277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1277)

```text
// D3D color
```

## Source note 114, line 1282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1282)

```text
// Pack the 4 floats to D3DCOLOR
```

## Source note 115, line 1286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1286)

```text
// Use !(x >= 3.0f) instead of (x < 3.0f) to properly clamp NaN to minimum
```

## Source note 116, line 1296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1296)

```text
// Handle mask operand:
```

## Source note 117, line 1297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1297)

```text
// mask=1: Write result to word[shift]
```

## Source note 118, line 1298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1298)

```text
// mask=2: Write result to word[shift], clear word[shift+1] to 0
```

## Source note 119, line 1299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1299)

```text
// mask=3: Same as mask=2, but for shift=3 only clear word[0] (don't write result)
```

## Source note 120, line 1301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1301)

```text
// Special case: mask=3, shift=3 - only clear word 0
```

## Source note 121, line 1304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1304)

```text
// Write result to word[shift]
```

## Source note 122, line 1306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1306)

```text
// For mask=2 or mask=3, also clear the adjacent word
```

## Source note 123, line 1314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1314)

```text
// NORMSHORT2 - pack 2 floats (in 3.0+X form) to 2 signed shorts
```

## Source note 124, line 1316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1316)

```text
// Extract signed 16-bit values from floats and pack into one 32-bit word
```

## Source note 125, line 1317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1317)

```text
// floats are in form: 3.0f + X (stored as integer add to 3.0f representation 0x40400000)
```

## Source note 126, line 1318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1318)

```text
// We need to saturate to signed 16-bit range [-32767, 32767] (NOT -32768, based on tests)
```

## Source note 127, line 1319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1319)

```text
// NOTE: Guest element 0 is at array index 3, element 1 is at index 2 (reversed for host)
```

## Source note 128, line 1320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1320)

```text
// Element 0 (index 3) goes to HIGH word, element 1 (index 2) goes to LOW word
```

## Source note 129, line 1325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1325)

```text
// element 0 to high word
```

## Source note 130, line 1330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1330)

```text
// element 1 to low word
```

## Source note 131, line 1336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1336)

```text
// NORMPACKED32 - pack 4 floats (in 3.0+X form) to 2:10:10:10 format (w:x:y:z)
```

## Source note 132, line 1338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1338)

```text
// Format: 2 bits for w (element 3), 10 bits each for x, y, z (elements 0, 1, 2)
```

## Source note 133, line 1339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1339)

```text
// Input floats are in 3.0+X form where X is the integer to pack
```

## Source note 134, line 1340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1340)

```text
// Algorithm: saturate float to range, then mask low bits to extract X
```

## Source note 135, line 1341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1341)

```text
// Constants kPack2101010_* are defined in ppc/context.h
```

## Source note 136, line 1344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1344)

```text
// Pack x (10 bits, position 0-9) - Guest element 0 is at index 3
```

## Source note 137, line 1352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1352)

```text
// Pack y (10 bits, position 10-19) - Guest element 1 is at index 2
```

## Source note 138, line 1360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1360)

```text
// Pack z (10 bits, position 20-29) - Guest element 2 is at index 1
```

## Source note 139, line 1368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1368)

```text
// Pack w (2 bits, position 30-31) - Guest element 3 is at index 0
```

## Source note 140, line 1381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1381)

```text
// FLOAT16_2 - pack 2 floats to 2 float16s
```

## Source note 141, line 1383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1383)

```text
// Pack 2 elements into 32 bits (1 word)
```

## Source note 142, line 1384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1384)

```text
// Guest element 0 goes to high 16 bits, element 1 to low 16 bits
```

## Source note 143, line 1385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1385)

```text
// Output u16 index = (1-i) + 2*shift for element i
```

## Source note 144, line 1387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1387)

```text
// Guest element i is at host array index 3-i
```

## Source note 145, line 1389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1389)

```text
// Output reversed: elem 0 to high, elem 1 to low
```

## Source note 146, line 1409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1409)

```text
// NORMSHORT4 - pack 4 floats (in 3.0+X form) to 4 signed shorts
```

## Source note 147, line 1411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1411)

```text
// Pack 4 elements into 64 bits (2 words)
```

## Source note 148, line 1412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1412)

```text
// Guest element 0 goes to highest 16-bit position, element 3 to lowest
```

## Source note 149, line 1413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1413)

```text
// Output u16 index = (3-i) + 2*shift for element i
```

## Source note 150, line 1415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1415)

```text
// Guest element i is at host array index 3-i
```

## Source note 151, line 1416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1416)

```text
// Output also reversed
```

## Source note 152, line 1427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1427)

```text
// float16_4
```

## Source note 153, line 1429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1429)

```text
// Pack 4 elements into 64 bits (4 x 16-bit floats)
```

## Source note 154, line 1430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1430)

```text
// Guest element 0 goes to highest 16-bit position, element 3 to lowest
```

## Source note 155, line 1431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1431)

```text
// Output u16 index = (3-i) + 2*shift for element i
```

## Source note 156, line 1432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1432)

```text
// Packs 2 and 3 place the 64 bits alike except at shift 3 (Xenia's
```

## Source note 157, line 1433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1433)

```text
// vpkd3d128 permute masks).
```

## Source note 158, line 1438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1438)

```text
// Guest element i is at host array index 3-i
```

## Source note 159, line 1439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1439)

```text
// Output also reversed
```

## Source note 160, line 1459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1459)

```text
// NORMPACKED64 - pack 4 floats to 4:20:20:20 format
```

## Source note 161, line 1461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1461)

```text
// Format: 4 bits for w, 20 bits each for x, y, z (packed into 64 bits)
```

## Source note 162, line 1463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1463)

```text
// Pack x (20 bits, position 0-19)
```

## Source note 163, line 1466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1466)

```text
// Pack y (20 bits, position 20-39)
```

## Source note 164, line 1469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1469)

```text
// Pack z (20 bits, position 40-59)
```

## Source note 165, line 1472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1472)

```text
// Pack w (4 bits, position 60-63)
```

## Source note 166, line 1488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1488)

```text
// Vector Unpack
```

## Source note 167, line 1492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1492)

```text
// TODO(tomc): Vectorize
```

## Source note 168, line 1493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1493)

```text
// NOTE: handling vector reversal here too
```

## Source note 169, line 1495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1495)

```text
// D3D color
```

## Source note 170, line 1504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1504)

```text
// NORMSHORT2 - unpack 2 shorts to floats (3.0+X form)
```

## Source note 171, line 1515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1515)

```text
// NORMPACKED32 - unpack 2:10:10:10 to floats
```

## Source note 172, line 1517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1517)

```text
// Format: w(2 bits):z(10 bits):y(10 bits):x(10 bits) in Guest element 3 (host s32[0])
```

## Source note 173, line 1518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1518)

```text
// x, y, z --> 3.0+X form (signed 10-bit), w --> 1.0+w form
```

## Source note 174, line 1519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1519)

```text
// Output: x --> Guest element 0 (host u32[3]), y --> Guest element 1 (host u32[2]),
```

## Source note 175, line 1520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1520)

```text
//         z --> Guest element 2 (host u32[1]), w --> Guest element 3 (host u32[0])
```

## Source note 176, line 1523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1523)

```text
// x (bits 0-9) - sign extend from 10 bits --> Guest element 0 (host u32[3])
```

## Source note 177, line 1528

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1528)

```text
// y (bits 10-19) - sign extend from 10 bits --> Guest element 1 (host u32[2])
```

## Source note 178, line 1532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1532)

```text
// z (bits 20-29) - sign extend from 10 bits --> Guest element 2 (host u32[1])
```

## Source note 179, line 1536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1536)

```text
// w (bits 30-31) - 2 bits, convert to 1.0+w form --> Guest element 3 (host u32[0])
```

## Source note 180, line 1542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1542)

```text
// FLOAT16_2 - unpack 2 float16 to floats
```

## Source note 181, line 1546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1546)

```text
// Unpack 2 float16s from u16[0,1] to elements 0,1 (stored at u32[3,2])
```

## Source note 182, line 1547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1547)

```text
// Element 0 (at u32[3]) from u16[1] (high), element 1 (at u32[2]) from u16[0] (low)
```

## Source note 183, line 1549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1549)

```text
// Read from u16[1], u16[0]
```

## Source note 184, line 1550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1550)

```text
// Write to u32[3], u32[2]
```

## Source note 185, line 1552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1552)

```text
// Extract sign, exponent, mantissa
```

## Source note 186, line 1557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1557)

```text
// Handle zero/denorm case
```

## Source note 187, line 1567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1567)

```text
// NORMSHORT4 - unpack 4 shorts to floats (3.0+X form)
```

## Source note 188, line 1569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1569)

```text
// Unpack 4 shorts from Guest elements 2-3 (host u16[0-3]) to 4 floats
```

## Source note 189, line 1570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1570)

```text
// Guest element order is reversed in host arrays
```

## Source note 190, line 1572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1572)

```text
// Read from u16 indices 3, 2, 1, 0 (guest shorts 0, 1, 2, 3)
```

## Source note 191, line 1573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1573)

```text
// Write to f32 indices 3, 2, 1, 0 (Guest elements 0, 1, 2, 3)
```

## Source note 192, line 1581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1581)

```text
// FLOAT16_4 - unpack 4 float16 to floats
```

## Source note 193, line 1585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1585)

```text
// Unpack 4 float16s from Guest elements 2-3 (host u16[0-3]) to elements 0-3
```

## Source note 194, line 1586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1586)

```text
// Guest element order is reversed in host arrays
```

## Source note 195, line 1588

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1588)

```text
// Read from u16 indices 3, 2, 1, 0 (guest shorts 0, 1, 2, 3)
```

## Source note 196, line 1589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1589)

```text
// Write to u32 indices 3, 2, 1, 0 (Guest elements 0, 1, 2, 3)
```

## Source note 197, line 1591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1591)

```text
// Extract sign, exponent, mantissa and convert to float32
```

## Source note 198, line 1596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1596)

```text
// Handle zero/denorm case
```

## Source note 199, line 1604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1604)

```text
// NORMPACKED64 - unpack 4:20:20:20 to floats
```

## Source note 200, line 1608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1608)

```text
// Format: w(4 bits):z(20 bits):y(20 bits):x(20 bits) in 64 bits
```

## Source note 201, line 1609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1609)

```text
// x, y, z --> floats, w --> float
```

## Source note 202, line 1611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1611)

```text
// x (bits 0-19) - sign extend from 20 bits
```

## Source note 203, line 1614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1614)

```text
// y (bits 20-39) - sign extend from 20 bits
```

## Source note 204, line 1617

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1617)

```text
// z (bits 40-59) - sign extend from 20 bits
```

## Source note 205, line 1620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/vector.cpp#L1620)

```text
// w (bits 60-63) - 4 bits
```
