# Intrinsics: ppc source notes

This record preserves technical and API notes moved from `include/rex/ppc/intrinsics.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L34)

```text
// Vector Load/Store Mask Tables
```

## Source note 2, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L36)

```text
// These tables are used for lvlx/lvrx (load vector left/right) and
```

## Source note 3, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L37)

```text
// stvlx/stvrx (store vector left/right) instructions.
```

## Source note 4, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L116)

```text
// SIMD Helper Functions
```

## Source note 5, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L119)

```text
// Unsigned 32-bit saturating add
```

## Source note 6, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L125)

```text
// Signed 8-bit average (rounds towards zero)
```

## Source note 7, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L132)

```text
// Signed 16-bit average
```

## Source note 8, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L139)

```text
// Signed 32-bit average
```

## Source note 9, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L146)

```text
// Convert unsigned 32-bit integers to floats
```

## Source note 10, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L158)

```text
// Permute bytes from two vectors based on control vector
```

## Source note 11, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L166)

```text
// Unsigned 8-bit compare greater than
```

## Source note 12, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L172)

```text
// Unsigned 16-bit compare greater than
```

## Source note 13, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L178)

```text
// Vector Convert To Signed Fixed-Point Word Saturate
```

## Source note 14, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L190)

```text
// Vector Convert To Unsigned Fixed-Point Word Saturate
```

## Source note 15, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L191)

```text
// Convert float to unsigned int with saturation to [0, UINT_MAX]
```

## Source note 16, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L192)

```text
// NaN -> 0, negative -> 0, > UINT_MAX -> UINT_MAX
```

## Source note 17, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L196)

```text
// UINT_MAX as float
```

## Source note 18, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L199)

```text
// Clamp to [0, UINT_MAX]
```

## Source note 19, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L203)

```text
// Convert to signed int first (will handle values up to INT_MAX correctly)
```

## Source note 20, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L204)

```text
// For values > INT_MAX, we need special handling
```

## Source note 21, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L205)

```text
// 2^31
```

## Source note 22, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L208)

```text
// For values >= 2^31, subtract 2^31 before conversion and add it back after
```

## Source note 23, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L215)

```text
// Apply saturation: NaN -> 0, overflow -> UINT_MAX
```

## Source note 24, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L225)

```text
// vmsum3fp128/vmsum4fp128: the dot product of the elements in kMask's high
```

## Source note 25, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L226)

```text
// nibble, in every element (as dpps). Hardware adds the products before
```

## Source note 26, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L227)

```text
// flushing, so a sum that flushes to zero keeps its sign; dpps flushes the
```

## Source note 27, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L228)

```text
// products first and adds them to +0.
```

## Source note 28, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L250)

```text
// Vector Shift Right
```

## Source note 29, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L258)

```text
// Vector Shift Left - shift entire 128-bit vector left by bits in low 3 bits of b
```

## Source note 30, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L260)

```text
// On hardware each byte shifts by its own count, taking the bits of the
```

## Source note 31, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L261)

```text
// next lower-addressed byte; the 128-bit shift below is the usual case where
```

## Source note 32, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L262)

```text
// all counts agree (a vspltisb count).
```

## Source note 33, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L269)

```text
// Host byte j is guest byte 15 - j, so the next guest byte is host j - 1.
```

## Source note 34, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L280)

```text
// Split into high and low 64-bit parts
```

## Source note 35, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L283)

```text
// Shift the carry from low qword to high qword position
```

## Source note 36, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L287)

```text
// ARM64 NEON implementation using vld1/vst1 for conversion
```

## Source note 37, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L291)

```text
// Store simde__m128i to memory
```

## Source note 38, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L294)

```text
// Load as NEON vector
```

## Source note 39, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L297)

```text
// vshlq_u64 accepts variable shift per lane
```

## Source note 40, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L301)

```text
// NEON vshl uses negative counts for right shifts.
```

## Source note 41, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L305)

```text
// Combine results
```

## Source note 42, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L311)

```text
// Store back to memory and reload as simde__m128i
```

## Source note 43, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L319)

```text
// Vector Shift Left by Octet - shift entire vector left by bytes in bits [121:124] of vB
```

## Source note 44, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L320)

```text
// In PPC big-endian byte 15 is at LSB position, which in x86 LE is at index 0
```

## Source note 45, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L321)

```text
// Bits 121:124 within the byte are extracted as (byte >> 3) & 0xF
```

## Source note 46, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L322)

```text
// PPC left shift = shift towards MSB (lower PPC addresses) = shift towards higher x86 addresses
```

## Source note 47, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L337)

```text
// ARM64 NEON implementation using memory for conversion
```

## Source note 48, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L350)

```text
// Vector Shift Right by Octet - shift entire vector right by bytes in bits [121:124] of vB
```

## Source note 49, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L351)

```text
// In PPC big-endian byte 15 is at LSB position, which in x86 LE is at index 0
```

## Source note 50, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L352)

```text
// Bits 121:124 within the byte are extracted as (byte >> 3) & 0xF
```

## Source note 51, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L353)

```text
// PPC right shift = shift towards LSB (higher PPC addresses) = shift towards lower x86 addresses
```

## Source note 52, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L368)

```text
// ARM64 NEON implementation using memory for conversion
```

## Source note 53, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L381)

```text
// Variable 16-bit shift left: widen to 32-bit, shift, narrow back
```

## Source note 54, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L396)

```text
// Variable 16-bit logical right shift: widen to 32-bit, shift, narrow back
```

## Source note 55, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L408)

```text
// Variable 16-bit arithmetic right shift: sign-extend to 32-bit, shift, narrow back
```

## Source note 56, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L411)

```text
// Sign-extend a: duplicate each 16-bit lane, then arithmetic shift right by 16
```

## Source note 57, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L421)

```text
// Variable 8-bit shift left: widen to 16-bit, shift, narrow back
```

## Source note 58, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L439)

```text
// Global Aliases for Generated Code
```

## Source note 59, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/intrinsics.h#L441)

```text
// Vector mask tables accessible from global scope for generated code
```
