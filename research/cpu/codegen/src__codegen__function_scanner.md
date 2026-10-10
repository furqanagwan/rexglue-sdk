# Function scanner: codegen source notes

This record preserves technical and API notes moved from `src/codegen/function_scanner.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L35)

```text
// Import PPC types
```

## Source note 2, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L48)

```text
// Address Translation
```

## Source note 3, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L61)

```text
// Helper: Detect function prologue pattern
```

## Source note 4, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L72)

```text
// Check for mflr
```

## Source note 5, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L77)

```text
// Check for mfspr lr (SPR 8)
```

## Source note 6, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L82)

```text
// Check for stack frame allocation: stwu r1, -X(r1)
```

## Source note 7, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L91)

```text
// Helper: Detect function epilogue pattern
```

## Source note 8, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L103)

```text
// Check for blr
```

## Source note 9, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L108)

```text
// Check for mtlr
```

## Source note 10, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L113)

```text
// Check for stack restore: lwz r1, 0(r1)
```

## Source note 11, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L122)

```text
// Helper: Detect save/restore helper functions via byte pattern matching
```

## Source note 12, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L131)

```text
// Check single-instruction patterns (4 bytes each)
```

## Source note 13, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L132)

```text
// ld r14, -0x98(r1)
```

## Source note 14, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L133)

```text
// std r14, -0x98(r1)
```

## Source note 15, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L134)

```text
// lfd f14, -0x90(r12)
```

## Source note 16, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L135)

```text
// stfd f14, -0x90(r12)
```

## Source note 17, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L142)

```text
// Check two-instruction patterns (8 bytes each)
```

## Source note 18, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L143)

```text
// Pattern: li r11, -0x120 (0x3960fee0) + lvx/stvx
```

## Source note 19, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L144)

```text
// li r11, -0x120
```

## Source note 20, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L148)

```text
// lvx v14, r11, r12
```

## Source note 21, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L149)

```text
// stvx v14, r11, r12
```

## Source note 22, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L156)

```text
// Pattern: li r11, -0x400 (0x3960fc00) + lvx128/stvx128
```

## Source note 23, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L157)

```text
// li r11, -0x400
```

## Source note 24, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L161)

```text
// lvx128 v64, r11, r12
```

## Source note 25, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L162)

```text
// stvx128 v64, r11, r12
```

## Source note 26, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L173)

```text
// Jump Table Pattern Detection
```

## Source note 27, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L175)

```text
// Xbox 360 compilers emit 4 distinct jump table patterns (maybe more?):
```

## Source note 28, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L177)

```text
// 1. ABSOLUTE: lwzx loads full 32-bit target addresses
```

## Source note 29, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L178)

```text
//    lis rT, table@ha; addi rT, rT, table@l; rlwinm rI, rIdx, 2; lwzx rT, rI, rT; mtctr; bctr
```

## Source note 30, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L180)

```text
// 2. COMPUTED: lbzx loads byte offset, shifted and added to base
```

## Source note 31, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L181)

```text
//    lis rT, table@ha; addi rT, rT, table@l; lbzx rO, rIdx, rT; rlwinm rO, rO, shift;
```

## Source note 32, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L182)

```text
//    lis rB, base@ha; addi rB, rB, base@l; add rT, rB, rO; mtctr; bctr
```

## Source note 33, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L184)

```text
// 3. BYTEOFFSET: lbzx loads byte offset, added directly to base
```

## Source note 34, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L185)

```text
//    lis rT, table@ha; addi rT, rT, table@l; lbzx rO, rIdx, rT;
```

## Source note 35, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L186)

```text
//    lis rB, base@ha; addi rB, rB, base@l; add rT, rB, rO; mtctr; bctr
```

## Source note 36, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L188)

```text
// 4. SHORTOFFSET: lhzx loads 16-bit offset, added to base
```

## Source note 37, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L189)

```text
//    lis rT, table@ha; addi rT, rT, table@l; rlwinm rI, rIdx, 1; lhzx rO, rI, rT;
```

## Source note 38, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L190)

```text
//    lis rB, base@ha; addi rB, rB, base@l; add rT, rB, rO; mtctr; bctr
```

## Source note 39, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L195)

```text
// Jump table type - internal use only during detection
```

## Source note 40, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L196)

```text
// Determines how target addresses are stored/computed in the binary
```

## Source note 41, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L198)

```text
// lwzx - table contains full 32-bit target addresses
```

## Source note 42, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L199)

```text
// lbzx + rlwinm + add - byte offset shifted and added to base
```

## Source note 43, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L200)

```text
// lbzx + add - byte offset added directly to base
```

## Source note 44, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L201)

```text
// lhzx + add - 16-bit offset added to base
```

## Source note 45, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L204)

```text
// Helper struct for tracking pattern match state
```

## Source note 46, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L207)

```text
// Register moved to CTR
```

## Source note 47, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L208)

```text
// Register holding table address
```

## Source note 48, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L209)

```text
// Register holding base address (offset types)
```

## Source note 49, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L210)

```text
// Register holding original switch index
```

## Source note 50, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L211)

```text
// Register holding loaded offset
```

## Source note 51, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L212)

```text
// Shift amount for COMPUTED type
```

## Source note 52, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L218)

```text
// Pattern matching state
```

## Source note 53, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L220)

```text
// For offset-based types
```

## Source note 54, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L221)

```text
// lwzx/lbzx/lhzx
```

## Source note 55, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L222)

```text
// rlwinm for shift
```

## Source note 56, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L228)

```text
// For @ha/@l pairs, addi uses signed immediate, so we need addition with sign extension
```

## Source note 57, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L233)

```text
// Scan backward for CMPLWI bounds check and conditional branch
```

## Source note 58, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L242)

```text
// Helper: Scan for bounds check (CMPLWI + BGT/BLE)
```

## Source note 59, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L250)

```text
// CR field from conditional branch
```

## Source note 60, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L267)

```text
// Look for conditional branch (bc, bca, bcl, bcla, bclr, bclrl)
```

## Source note 61, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L268)

```text
// bgt/ble/bgtlr/blelr are simplified mnemonics for bc with specific BO/BI
```

## Source note 62, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L275)

```text
// Check if this could be a bounds check branch (bgt or ble pattern)
```

## Source note 63, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L276)

```text
// BO[4] (bit 0) = 0 means test CR bit
```

## Source note 64, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L277)

```text
// BI[0:1] = condition bit within CR field (GT=1, LT=0, EQ=2, SO=3)
```

## Source note 65, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L280)

```text
// Check for branches that test the GT bit (BI mod 4 == 1)
```

## Source note 66, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L281)

```text
// bgt: BO=12 (01100), tests CR[GT]=true
```

## Source note 67, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L282)

```text
// ble: BO=4 (00100), tests CR[GT]=false (i.e., not greater = less or equal)
```

## Source note 68, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L283)

```text
// Tests GT bit
```

## Source note 69, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L284)

```text
// Extract CR field (bits 2-4 of BI)
```

## Source note 70, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L287)

```text
// Extract default target if branch has target
```

## Source note 71, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L295)

```text
// Look for rlwinm that sets the index register with a mask
```

## Source note 72, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L296)

```text
// clrlwi rD, rS, n = rlwinm rD, rS, 0, n, 31
```

## Source note 73, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L297)

```text
// This bounds the value to 2^(32-n) - 1 entries
```

## Source note 74, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L303)

```text
// clrlwi pattern: SH=0, ME=31, MB > 0
```

## Source note 75, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L304)

```text
// The mask clears leftmost MB bits, so max value = 2^(32-MB) - 1
```

## Source note 76, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L305)

```text
// Entry count = max value + 1 = 2^(32-MB)
```

## Source note 77, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L312)

```text
// Only accept if count is reasonable (2-256 entries)
```

## Source note 78, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L317)

```text
// Implicit bounds are definitive
```

## Source note 79, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L322)

```text
// Look for cmpli or cmpi (cmplwi/cmpwi - unsigned/signed bounds check)
```

## Source note 80, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L324)

```text
// cmpli format: cmpli BF, L, RA, UIMM
```

## Source note 81, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L325)

```text
// BF (bits 23-25): CR field
```

## Source note 82, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L326)

```text
// L (bit 21): 0=32-bit, 1=64-bit
```

## Source note 83, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L327)

```text
// RA (bits 16-20): Register to compare
```

## Source note 84, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L328)

```text
// UIMM (bits 0-15): Immediate value
```

## Source note 85, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L330)

```text
// BF is top 3 bits of RT field for compare instructions
```

## Source note 86, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L332)

```text
// Register being compared
```

## Source note 87, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L333)

```text
// Immediate value (max index)
```

## Source note 88, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L335)

```text
// Prefer register match, accept CR-only match as fallback
```

## Source note 89, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L339)

```text
// CRITICAL: Reject very small immediates (0 or 1) even if register matches
```

## Source note 90, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L340)

```text
// These are likely unrelated comparisons (checking for zero/null, boolean tests)
```

## Source note 91, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L341)

```text
// A real switch table bounds check would have immediate >= 2 (at least 3 cases)
```

## Source note 92, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L349)

```text
// Only accept if register matches, or if CR matches AND immediate is reasonable
```

## Source note 93, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L351)

```text
// cmpli compares against max, so count = max + 1
```

## Source note 94, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L355)

```text
// If register matches, we found the best match - done
```

## Source note 95, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L358)

```text
// If only CR matches, continue scanning for a better (register) match
```

## Source note 96, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L367)

```text
// Helper: Read table entries based on type
```

## Source note 97, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L374)

```text
// entry_count comes from bounds check analysis - use it exactly if available
```

## Source note 98, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L375)

```text
// If no bounds check was found (entry_count == 0), read until we hit invalid entries
```

## Source note 99, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L376)

```text
// Loop terminates via goto done when invalid memory is hit
```

## Source note 100, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L382)

```text
// Read 32-bit address directly (big-endian)
```

## Source note 101, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L391)

```text
// Read byte, shift, add to base
```

## Source note 102, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L401)

```text
// Read byte, add directly to base
```

## Source note 103, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L411)

```text
// Read 16-bit value (big-endian), add to base
```

## Source note 104, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L421)

```text
// PPC instructions must be 4-byte aligned
```

## Source note 105, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L425)

```text
// Validate target (stop on null or invalid for absolute type)
```

## Source note 106, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L429)

```text
// Validate target is in EXECUTABLE section (not just mapped memory)
```

## Source note 107, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L430)

```text
// This prevents false positives from data tables containing addresses
```

## Source note 108, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L432)

```text
// For absolute tables, non-executable target means wrong table address
```

## Source note 109, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L435)

```text
// Skip non-executable entries in offset tables (might be default/error cases)
```

## Source note 110, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L445)

```text
// anonymous namespace
```

## Source note 111, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L448)

```text
// Helper: Check if instruction indicates a function boundary
```

## Source note 112, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L450)

```text
// Returns true if the instruction at 'code' indicates we've crossed into
```

## Source note 113, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L451)

```text
// a different function (either previous function's terminator or current
```

## Source note 114, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L452)

```text
// function's prologue).
```

## Source note 115, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L454)

```text
// Zero padding between functions
```

## Source note 116, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L460)

```text
// blr - previous function's return
```

## Source note 117, line 466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L466)

```text
// bctr/bctrl - indirect branch/call via CTR
```

## Source note 118, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L472)

```text
// Unconditional branch 'b' (tail call to named function)
```

## Source note 119, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L478)

```text
// mflr - function prologue (saving link register)
```

## Source note 120, line 484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L484)

```text
// stw rX, offset(r1) where offset is negative - stack frame setup
```

## Source note 121, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L485)

```text
// This catches "stwu r1, -N(r1)" which is a common prologue
```

## Source note 122, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L487)

```text
// stwu r1, -N(r1) is stack frame allocation
```

## Source note 123, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L492)

```text
// nop (ori r0,r0,0 = 0x60000000) - often used as padding
```

## Source note 124, line 493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L493)

```text
// But nops can appear mid-function too, so only treat consecutive nops as boundary
```

## Source note 125, line 494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L494)

```text
// For now, don't treat single nop as boundary
```

## Source note 126, line 500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L500)

```text
// Helper: Detect jump table pattern at bctr instruction
```

## Source note 127, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L503)

```text
// Skip detection if this address has a manually-specified switch table
```

## Source note 128, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L506)

```text
// Will be handled by the pre-loaded config
```

## Source note 129, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L515)

```text
// Backward scan to match pattern
```

## Source note 130, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L525)

```text
// Read as big-endian (PPC is big-endian)
```

## Source note 131, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L530)

```text
// Stop at function boundaries - but allow continuing past bctr if we're still
```

## Source note 132, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L531)

```text
// looking for lis (handles adjacent switch tables sharing setup code)
```

## Source note 133, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L533)

```text
// If we found load but not lis, and this is bctr, continue scanning
```

## Source note 134, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L534)

```text
// (adjacent switch tables may share the same lis setup)
```

## Source note 135, line 542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L542)

```text
// Step 1: Find mtctr rX
```

## Source note 136, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L554)

```text
// Step 2a: Find add rT, rBase, rOffset (for offset-based types)
```

## Source note 137, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L557)

```text
// Store both RA and RB - we'll determine which is base/offset later
```

## Source note 138, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L568)

```text
// Step 2b: Find lwzx (ABSOLUTE type) - only if no add found
```

## Source note 139, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L569)

```text
// lwzx RT, RA, RB: RT = mem[RA + RB]
```

## Source note 140, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L570)

```text
// Note: RA and RB can be in either order (table/index or index/table)
```

## Source note 141, line 574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L574)

```text
// Initially assume RA=table, RB=index (will verify/swap later)
```

## Source note 142, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L586)

```text
// For offset-based types: find the load instruction
```

## Source note 143, line 588

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L588)

```text
// lbzx for COMPUTED or BYTEOFFSET
```

## Source note 144, line 589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L589)

```text
// lbzx RT, RA, RB: RT = *(RA + RB)
```

## Source note 145, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L591)

```text
// Initially assume RA=table, RB=index
```

## Source note 146, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L595)

```text
// Only set type if we haven't already found a shift (which means kComputed)
```

## Source note 147, line 597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L597)

```text
// Default when no shift
```

## Source note 148, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L605)

```text
// lhzx for SHORTOFFSET
```

## Source note 149, line 618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L618)

```text
// Step 3: Find rlwinm for shift (COMPUTED type or index scaling)
```

## Source note 150, line 620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L620)

```text
// Check if this is scaling the index (for ABSOLUTE, SHORT, or offset-based types)
```

## Source note 151, line 621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L621)

```text
// Must check BEFORE offset shift to handle SHORTOFFSET with scaled index
```

## Source note 152, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L630)

```text
// Check if this is shifting the offset (COMPUTED type)
```

## Source note 153, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L631)

```text
// Only set COMPUTED type if we haven't already identified as SHORTOFFSET
```

## Source note 154, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L632)

```text
// (SHORTOFFSET uses rlwinm for index scaling, not offset shifting)
```

## Source note 155, line 646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L646)

```text
// Step 4: Find lis/addi pairs for table address (and base for register reuse case)
```

## Source note 156, line 647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L647)

```text
// Also check if we need to swap table_reg/index_reg (RA/RB ambiguity)
```

## Source note 157, line 649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L649)

```text
// Check for register reuse: same register used for both table and base (offset-based types)
```

## Source note 158, line 650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L650)

```text
// In this case, backward scan finds BASE first (closer to bctr), then TABLE
```

## Source note 159, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L653)

```text
// Check for lis matching table_reg
```

## Source note 160, line 656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L656)

```text
// Register reuse: first lis = BASE, second lis = TABLE
```

## Source note 161, line 678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L678)

```text
// Check if lis matches index_reg - means we guessed wrong, need to swap
```

## Source note 162, line 689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L689)

```text
// Check for addi/ori matching table_reg
```

## Source note 163, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L693)

```text
// Register reuse: first addi = BASE, second addi = TABLE
```

## Source note 164, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L716)

```text
// Check if addi matches index_reg - means we guessed wrong, need to swap
```

## Source note 165, line 729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L729)

```text
// Step 5: Find lis/addi pairs for base address (offset-based types)
```

## Source note 166, line 730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L730)

```text
// Also handle RA/RB ambiguity for add instruction
```

## Source note 167, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L740)

```text
// Check if lis matches offset_reg - means we guessed wrong
```

## Source note 168, line 758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L758)

```text
// Check if addi matches offset_reg - means we guessed wrong
```

## Source note 169, line 770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L770)

```text
// Check if we have a complete pattern
```

## Source note 170, line 776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L776)

```text
// Pattern complete
```

## Source note 171, line 780

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L780)

```text
// Verify minimum required pattern elements
```

## Source note 172, line 786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L786)

```text
// Only report error if we found indexed load AND lis/addi for the table address.
```

## Source note 173, line 787

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L787)

```text
// If we found load but NO lis, it's a vtable/indirect call (runtime pointer), not a switch
```

## Source note 174, line 788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L788)

```text
// table.
```

## Source note 175, line 796

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L796)

```text
// Load but no lis = vtable/indirect call with runtime pointer, not a switch table
```

## Source note 176, line 803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L803)

```text
// For offset-based types, require base address
```

## Source note 177, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L810)

```text
// Validate table address
```

## Source note 178, line 821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L821)

```text
// Scan for bounds check (CMPLWI)
```

## Source note 179, line 826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L826)

```text
// Read table entries
```

## Source note 180, line 829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L829)

```text
// Require at least 2 entries
```

## Source note 181, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L835)

```text
// Build result
```

## Source note 182, line 846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L846)

```text
// Block-Based Discovery
```

## Source note 183, line 854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L854)

```text
// Track all instruction addresses scanned (prevents overlap between blocks)
```

## Source note 184, line 857

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L857)

```text
// DFS block stack - tracks blocks being processed
```

## Source note 185, line 858

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L858)

```text
// this allows projection carry-forward on continuous blocks
```

## Source note 186, line 861

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L861)

```text
// Start with entry block
```

## Source note 187, line 865

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L865)

```text
// No limit
```

## Source note 188, line 868

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L868)

```text
// Safety limit
```

## Source note 189, line 871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L871)

```text
// Get current block from stack (by reference for in-place modification)
```

## Source note 190, line 874

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L874)

```text
// Only check for duplicates if this is a FRESH block (not partially scanned)
```

## Source note 191, line 875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L875)

```text
// When block.end > block.base, we're continuing to process an existing block
```

## Source note 192, line 877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L877)

```text
// Fresh block - check if already scanned by another block
```

## Source note 193, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L884)

```text
// Validate alignment
```

## Source note 194, line 891

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L891)

```text
// Calculate current position in block
```

## Source note 195, line 892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L892)

```text
// end tracks where we are (exclusive becomes next addr)
```

## Source note 196, line 894

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L894)

```text
// Fresh block - start scanning from base
```

## Source note 197, line 897

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L897)

```text
// Check projection limit BEFORE processing instruction
```

## Source note 198, line 898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L898)

```text
// if block.size >= projectedSize, block is done
```

## Source note 199, line 903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L903)

```text
// Block done - save and pop
```

## Source note 200, line 909

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L909)

```text
// Check if this address was already scanned by another block (overlap prevention)
```

## Source note 201, line 910

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L910)

```text
// This catches cases where a fall-through block tries to scan into territory
```

## Source note 202, line 911

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L911)

```text
// already covered by another block (e.g., shared epilogue code)
```

## Source note 203, line 913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L913)

```text
// Block ends here - don't include the already-scanned instruction
```

## Source note 204, line 915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L915)

```text
// Record the overlap address as a successor so codegen emits a goto
```

## Source note 205, line 924

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L924)

```text
// CRITICAL: Check if we've hit another function's entry point
```

## Source note 206, line 925

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L925)

```text
// This enforces the authority system - PDATA/config entries cannot be consumed
```

## Source note 207, line 929

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L929)

```text
// Block has content - save it
```

## Source note 208, line 930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L930)

```text
// Don't include this instruction
```

## Source note 209, line 934

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L934)

```text
// Either way, pop this block - we can't continue into another function
```

## Source note 210, line 939

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L939)

```text
// Fetch instruction
```

## Source note 211, line 951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L951)

```text
// Null instruction ends block
```

## Source note 212, line 953

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L953)

```text
// Don't include the null
```

## Source note 213, line 960

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L960)

```text
// Include this instruction in block
```

## Source note 214, line 962

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L962)

```text
// Mark this address as scanned
```

## Source note 215, line 966

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L966)

```text
// Check for blr (return)
```

## Source note 216, line 974

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L974)

```text
// Check for bctr (indirect branch)
```

## Source note 217, line 979

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L979)

```text
// Add all jump table targets as successors
```

## Source note 218, line 988

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L988)

```text
// Push jump table targets onto stack (if any)
```

## Source note 219, line 1003

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1003)

```text
// Check for unconditional branch (b/ba)
```

## Source note 220, line 1009

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1009)

```text
// Check known_callables_ FIRST (gathered before discovery)
```

## Source note 221, line 1012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1012)

```text
// Backward branch to unknown = probably tail call
```

## Source note 222, line 1017

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1017)

```text
// Large forward branch (>1MB) = probably tail call to shared code
```

## Source note 223, line 1018

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1018)

```text
// No legitimate internal branch spans more than 1MB
```

## Source note 224, line 1023

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1023)

```text
// Check if target is a known callable (function or import)
```

## Source note 225, line 1028

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1028)

```text
// CRITICAL: Check code region boundary
```

## Source note 226, line 1029

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1029)

```text
// If target is in a different region (and not a configured chunk),
```

## Source note 227, line 1030

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1030)

```text
// it MUST be a tail call - prevents mega-merges across null boundaries
```

## Source note 228, line 1037

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1037)

```text
// CRITICAL: Check if target looks like a function entry (has prologue)
```

## Source note 229, line 1038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1038)

```text
// If branching to a prologue, it's definitely a tail call to another function
```

## Source note 230, line 1052

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1052)

```text
// Carry projection forward if branch is continuous
```

## Source note 231, line 1061

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1061)

```text
// IMPORTANT: Save and pop current block FIRST, before push_back
```

## Source note 232, line 1062

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1062)

```text
// push_back can reallocate the vector, invalidating 'block' reference
```

## Source note 233, line 1067

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1067)

```text
// Now safe to push new block
```

## Source note 234, line 1082

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1082)

```text
// Check for function call (bl) - doesn't end block
```

## Source note 235, line 1085

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1085)

```text
// Continue to next instruction (block.end already updated)
```

## Source note 236, line 1089

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1089)

```text
// Check for conditional return (bclr/bclrl with conditional BO)
```

## Source note 237, line 1090

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1090)

```text
// These return to LR if condition is met, otherwise fall through
```

## Source note 238, line 1091

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1091)

```text
// Examples: blelr, bgtlr, bnelr, beqlr, etc.
```

## Source note 239, line 1093

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1093)

```text
// is_return() only matches unconditional blr
```

## Source note 240, line 1098

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1098)

```text
// Pop current block BEFORE pushing fall-through
```

## Source note 241, line 1100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1100)

```text
// Push fall-through block onto stack
```

## Source note 242, line 1111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1111)

```text
// Check for conditional branch (bc, bca, etc.)
```

## Source note 243, line 1116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1116)

```text
// Block ends at conditional branch
```

## Source note 244, line 1122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1122)

```text
// Push true-case first, then false-case
```

## Source note 245, line 1123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1123)

```text
// False-case (fall-through) gets projectedSize = distance to true-case
```

## Source note 246, line 1124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1124)

```text
// This prevents fall-through from growing past the branch target
```

## Source note 247, line 1126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1126)

```text
// Check if target is internal to function (at or after entry point)
```

## Source note 248, line 1129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1129)

```text
// Push true-case block (branch target) - no projection
```

## Source note 249, line 1134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1134)

```text
// No limit on true-case
```

## Source note 250, line 1138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1138)

```text
// Push false-case block (fall-through) WITH projection
```

## Source note 251, line 1144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1144)

```text
// Project size: distance from fall-through to branch target
```

## Source note 252, line 1145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1145)

```text
// This prevents fall-through from consuming code past the branch target
```

## Source note 253, line 1159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1159)

```text
// Regular instruction - continue to next (block.end already updated)
```

## Source note 254, line 1166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1166)

```text
// Sort blocks by address for deterministic output and easier diffing
```

## Source note 255, line 1174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1174)

```text
// Code Region Boundary Checking
```

## Source note 256, line 1191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1191)

```text
// Check if target is a configured chunk of the current function
```

## Source note 257, line 1192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1192)

```text
// Chunks can cross region boundaries by design
```

## Source note 258, line 1197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1197)

```text
// Find regions for both addresses
```

## Source note 259, line 1201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1201)

```text
// If target is in a different region (or no region), it's a tail call
```

## Source note 260, line 1212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1212)

```text
// Block Discovery
```

## Source note 261, line 1218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1218)

```text
// Helper: Check if instruction is prologue pattern
```

## Source note 262, line 1226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1226)

```text
// mflr is really mfspr with SPR=8
```

## Source note 263, line 1229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1229)

```text
// stwu r1, -X(r1) - stack frame setup
```

## Source note 264, line 1237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1237)

```text
// Helper: Check if block should stop at this instruction
```

## Source note 265, line 1244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1244)

```text
// NULL padding ends block (but NOT unknown instructions - those get emitted as comments)
```

## Source note 266, line 1249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1249)

```text
// Note: kUnknown opcodes (like 64-bit rotate instructions) are NOT terminators.
```

## Source note 267, line 1250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1250)

```text
// They should be included in the block and emitted as comments during codegen.
```

## Source note 268, line 1252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1252)

```text
// Check for terminators
```

## Source note 269, line 1256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1256)

```text
// bcctr (indirect branch via CTR)
```

## Source note 270, line 1258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1258)

```text
// bcctrl is a call. An unconditional bcctr (bctr, BO == 20) is a terminator,
```

## Source note 271, line 1259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1259)

```text
// but a conditional bcctr (e.g. bnectr/beqctr) falls through to the next
```

## Source note 272, line 1260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1260)

```text
// instruction when its condition is not met, so it does not end the block.
```

## Source note 273, line 1264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1264)

```text
// Unconditional branch
```

## Source note 274, line 1268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1268)

```text
// Branch outside region is terminator
```

## Source note 275, line 1271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1271)

```text
// Branch to known function is tail call (terminator)
```

## Source note 276, line 1275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1275)

```text
// Unconditional branch always terminates block
```

## Source note 277, line 1282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1282)

```text
// Helper: Detect bounds check for jump table
```

## Source note 278, line 1290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1290)

```text
// Use funcStart as lower bound to avoid scanning into other functions
```

## Source note 279, line 1304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1304)

```text
// Stop at unconditional terminators - scanning past basic block boundaries
```

## Source note 280, line 1305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1305)

```text
// risks finding unrelated comparisons on the index register
```

## Source note 281, line 1311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1311)

```text
// Look for cmpli/cmpi followed by conditional branch
```

## Source note 282, line 1313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1313)

```text
// cmpli crX, L, rA, UIMM
```

## Source note 283, line 1327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1327)

```text
// cmpi crX, L, rA, SIMM
```

## Source note 284, line 1340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1340)

```text
// Look for clrlwi (rlwinm rA, rS, 0, MB, 31) which masks bits
```

## Source note 285, line 1341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1341)

```text
// MB must be > 0 to actually mask something; MB=0 is a no-op
```

## Source note 286, line 1344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1344)

```text
// Masked to (32 - MB) bits, max value is 2^(32-MB) - 1
```

## Source note 287, line 1360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1360)

```text
// anonymous namespace
```

## Source note 288, line 1363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1363)

```text
// Jump Table Detection
```

## Source note 289, line 1373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1373)

```text
// State for backward scan
```

## Source note 290, line 1377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1377)

```text
// Pending address parts (order of lis/addi varies in backward scan)
```

## Source note 291, line 1378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1378)

```text
// Note: addi uses sign-extended addition, ori uses OR
```

## Source note 292, line 1385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1385)

```text
// Helper to combine lis high bits with addi/ori low bits
```

## Source note 293, line 1388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1388)

```text
// addi: sign-extend lo and add
```

## Source note 294, line 1391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1391)

```text
// ori: zero-extend and OR
```

## Source note 295, line 1396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1396)

```text
// Current reg being traced (0xFF = stop tracing)
```

## Source note 296, line 1397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1397)

```text
// Last valid indexReg for scanForBounds/output
```

## Source note 297, line 1398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1398)

```text
// The other lwzx operand if RB is a static table base.
```

## Source note 298, line 1402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1402)

```text
// Backward scan from bctr
```

## Source note 299, line 1413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1413)

```text
// Stop at unconditional terminators (but NOT conditional branches - they're often bounds
```

## Source note 300, line 1414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1414)

```text
// checks)
```

## Source note 301, line 1418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1418)

```text
// Find mtctr rX
```

## Source note 302, line 1421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1421)

```text
// mtctr is mtspr 9, rS
```

## Source note 303, line 1428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1428)

```text
// After mtctr, look for load into ctrSourceReg
```

## Source note 304, line 1430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1430)

```text
// lwzx rD, rA, rB - indexed word load (ABSOLUTE table)
```

## Source note 305, line 1432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1432)

```text
// Tentatively treat RA as the table base and RB as the index;
```

## Source note 306, line 1433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1433)

```text
// the operands may be reversed.
```

## Source note 307, line 1444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1444)

```text
// lbzx rD, rA, rB - indexed byte load (BYTE/COMPUTED table)
```

## Source note 308, line 1446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1446)

```text
// Don't overwrite kComputed (set by rlwinm for shifted byte tables)
```

## Source note 309, line 1458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1458)

```text
// lhzx rD, rA, rB - indexed halfword load (SHORTOFFSET table)
```

## Source note 310, line 1460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1460)

```text
// Don't overwrite kComputed
```

## Source note 311, line 1472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1472)

```text
// add rD, rA, rB - combining base with offset
```

## Source note 312, line 1473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1473)

```text
// Pattern: rD = base + offset, where one operand is base, other is from table
```

## Source note 313, line 1475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1475)

```text
// If RA == rD (e.g., r12 = r12 + r0), then RB has the table offset
```

## Source note 314, line 1476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1476)

```text
// If RA != rD (e.g., r12 = r11 + r0), follow RA for the chain
```

## Source note 315, line 1478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1478)

```text
// Pattern: r12 = r12 + r0 --> r0 came from table load
```

## Source note 316, line 1481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1481)

```text
// Follow RA
```

## Source note 317, line 1489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1489)

```text
// rlwinm - shift for computed offset (slwi is rlwinm simplified)
```

## Source note 318, line 1501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1501)

```text
// Log unhandled instructions in the chain (potential issue)
```

## Source note 319, line 1508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1508)

```text
// After load: trace back indexReg through LEFT SHIFT (slwi) instructions only
```

## Source note 320, line 1509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1509)

```text
// slwi rA, rS, n is rlwinm rA, rS, n, 0, 31-n (MB=0, ME=31-SH)
```

## Source note 321, line 1510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1510)

```text
// This scales the index for table lookup (e.g., slwi r0, r31, 1 for halfword table)
```

## Source note 322, line 1511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1511)

```text
// DON'T trace back through extrwi/other rlwinm variants - those transform the value
```

## Source note 323, line 1512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1512)

```text
// NOTE: SH must be > 0 for a real shift; SH=0 is just a move/no-op (clrlwi r,r,0)
```

## Source note 324, line 1513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1513)

```text
// IMPORTANT: Stop tracing if another instruction writes to indexReg (breaks the chain)
```

## Source note 325, line 1514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1514)

```text
// PPC indexed loads are commutative in RA/RB. If an address-building
```

## Source note 326, line 1515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1515)

```text
// instruction overwrites the tentative RB index, the scaled index may be
```

## Source note 327, line 1516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1516)

```text
// in RA instead. Only accept a proper slwi of that alternate operand.
```

## Source note 328, line 1526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1526)

```text
// Check if this instruction writes to indexReg
```

## Source note 329, line 1530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1530)

```text
// Check common instruction forms that write to a register
```

## Source note 330, line 1535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1535)

```text
// X-form shift instructions: destination is RA (bits 11-15)
```

## Source note 331, line 1543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1543)

```text
// X-form load instructions: destination is RT (bits 6-10)
```

## Source note 332, line 1547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1547)

```text
// X-form logical instructions: destination is RA (bits 11-15), NOT RT
```

## Source note 333, line 1548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1548)

```text
// (RT is RS/source for these instructions)
```

## Source note 334, line 1551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1551)

```text
// XO-form instructions (add, subf)
```

## Source note 335, line 1558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1558)

```text
// Check for slwi pattern: if it matches, trace back; otherwise stop tracing
```

## Source note 336, line 1563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1563)

```text
// Check for slwi pattern: SH>0, MB=0, ME=31-SH
```

## Source note 337, line 1571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1571)

```text
// Non-slwi rlwinm writes to indexReg, stop tracing
```

## Source note 338, line 1576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1576)

```text
// Mark as invalid to stop further tracing
```

## Source note 339, line 1579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1579)

```text
// Another instruction writes to indexReg, stop tracing
```

## Source note 340, line 1587

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1587)

```text
// Mark as invalid to stop further tracing
```

## Source note 341, line 1592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1592)

```text
// Find lis/addi pairs for table and base addresses
```

## Source note 342, line 1593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1593)

```text
// When scanning backward for byte offset tables:
```

## Source note 343, line 1594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1594)

```text
// - BEFORE foundLoad (between mtctr and lbzx): baseAddr
```

## Source note 344, line 1595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1595)

```text
// - AFTER foundLoad (before lbzx in forward order): tableAddr
```

## Source note 345, line 1596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1596)

```text
// For absolute tables (lwzx), there's only tableAddr (after foundLoad)
```

## Source note 346, line 1598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1598)

```text
// lis rD, HI
```

## Source note 347, line 1605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1605)

```text
// After load: this is tableAddr (only capture first complete address)
```

## Source note 348, line 1613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1613)

```text
// Once tableAddr is set, ignore further lis instructions
```

## Source note 349, line 1615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1615)

```text
// Before load (between mtctr and load): this is baseAddr
```

## Source note 350, line 1622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1622)

```text
// Once baseAddr is set, ignore further lis instructions
```

## Source note 351, line 1626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1626)

```text
// addi rD, rA, LO (ori also possible)
```

## Source note 352, line 1634

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1634)

```text
// After load: this is tableAddr (only capture first complete address)
```

## Source note 353, line 1649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1649)

```text
// tableAddr has only high bits, add low bits
```

## Source note 354, line 1654

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1654)

```text
// Once tableAddr is fully set, ignore further addi instructions
```

## Source note 355, line 1656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1656)

```text
// Before load: this is baseAddr
```

## Source note 356, line 1675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1675)

```text
// Once baseAddr is fully set, ignore further addi instructions
```

## Source note 357, line 1693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1693)

```text
// For offset-based tables, we need a base address
```

## Source note 358, line 1695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1695)

```text
// Fallback to region start
```

## Source note 359, line 1698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1698)

```text
// Find bounds
```

## Source note 360, line 1700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1700)

```text
// If bounds not found (e.g., state machine pattern with forward bounds check),
```

## Source note 361, line 1701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1701)

```text
// use max entries and let the validation loop determine actual table size
```

## Source note 362, line 1704

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1704)

```text
// Read table entries
```

## Source note 363, line 1757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1757)

```text
// A zero can be an internal gap rather than the end of an absolute
```

## Source note 364, line 1758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1758)

```text
// table. Keep its case only if a nearby entry resolves to executable
```

## Source note 365, line 1759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1759)

```text
// code; otherwise stop before reading unrelated data after the table.
```

## Source note 366, line 1780

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1780)

```text
// PPC instructions must be 4-byte aligned
```

## Source note 367, line 1790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1790)

```text
// Validate target is within code region - jump table targets help DEFINE function extent
```

## Source note 368, line 1791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1791)

```text
// Don't constrain by funcEnd since that's just PDATA which may not include out-of-line code
```

## Source note 369, line 1793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1793)

```text
// TODO(tomc): Figure out what this voodoo does on real hardware. Its a jump target that
```

## Source note 370, line 1794

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1794)

```text
// points to a null value..?
```

## Source note 371, line 1805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1805)

```text
// End of valid entries
```

## Source note 372, line 1815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1815)

```text
// Target must be >= function start (can't jump backward past entry point)
```

## Source note 373, line 1825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1825)

```text
// Validate target points to valid code, not null padding
```

## Source note 374, line 1826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1826)

```text
// TODO(tomc): look into this more. what is the expected behavior when the processor executes
```

## Source note 375, line 1827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1827)

```text
// a null instruction.
```

## Source note 376, line 1834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1834)

```text
// sentinel, handled in codegen as __builtin_trap()
```

## Source note 377, line 1855

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1855)

```text
// Block Discovery
```

## Source note 378, line 1867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1867)

```text
// Function extent - use pdataSize when available
```

## Source note 379, line 1874

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1874)

```text
// Helper to check if address is within function bounds
```

## Source note 380, line 1879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1879)

```text
// Start with entry point
```

## Source note 381, line 1892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1892)

```text
// Linear scan until terminator
```

## Source note 382, line 1905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1905)

```text
// Mark as visited
```

## Source note 383, line 1908

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1908)

```text
// Collect instruction pointer
```

## Source note 384, line 1911

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1911)

```text
// Handle branches
```

## Source note 385, line 1915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1915)

```text
// Helper: check if target is internal to this function
```

## Source note 386, line 1916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1916)

```text
// Uses funcEnd (from pdataSize or region) defined at top of function
```

## Source note 387, line 1918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1918)

```text
// Must be within function bounds
```

## Source note 388, line 1922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1922)

```text
// Must not be a known function entry (except our own entry point)
```

## Source note 389, line 1930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1930)

```text
// bl - function call
```

## Source note 390, line 1932

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1932)

```text
// All bl instructions need to be recorded as unresolved branches
```

## Source note 391, line 1933

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1933)

```text
// so they can be resolved to CallEdges during merge phase
```

## Source note 392, line 1936

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1936)

```text
// Track as external call for function discovery
```

## Source note 393, line 1941

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1941)

```text
// Calls don't terminate block, fall through
```

## Source note 394, line 1943

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1943)

```text
// blr - end of function path
```

## Source note 395, line 1947

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1947)

```text
// Conditional bcctr (e.g. bnectr/beqctr): branches to CTR when the
```

## Source note 396, line 1948

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1948)

```text
// condition is met, otherwise falls through to the next instruction.
```

## Source note 397, line 1949

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1949)

```text
// Record the fall-through and continue the linear scan (mirrors the
```

## Source note 398, line 1950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1950)

```text
// conditional-branch case below) so the rest of the function is not
```

## Source note 399, line 1951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1951)

```text
// dropped. The CTR target is indirect and has no static label.
```

## Source note 400, line 1960

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1960)

```text
// Do not break: continue scanning the fall-through path.
```

## Source note 401, line 1962

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1962)

```text
// Unconditional bctr - prefer a manually configured table, then try
```

## Source note 402, line 1963

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1963)

```text
// automatic detection. Manual tables are authoritative because they
```

## Source note 403, line 1964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1964)

```text
// are commonly needed when the compiler emits a table without an
```

## Source note 404, line 1965

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1965)

```text
// adjacent bounds check.
```

## Source note 405, line 1989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1989)

```text
// sentinel from null-padding detection
```

## Source note 406, line 1991

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1991)

```text
// A jump table target may tail-dispatch to another known
```

## Source note 407, line 1992

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1992)

```text
// function; don't import that function's blocks into this one
```

## Source note 408, line 1993

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1993)

```text
// (mirrors isInternalTarget's treatment of regular branches,
```

## Source note 409, line 1994

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1994)

```text
// and now also applies to auto-detected table targets, not
```

## Source note 410, line 1995

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1995)

```text
// just manual ones).
```

## Source note 411, line 1998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1998)

```text
// A manually configured table is authoritative, so a drop
```

## Source note 412, line 1999

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L1999)

```text
// here likely means the target was mis-registered as a
```

## Source note 413, line 2000

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2000)

```text
// function entry elsewhere. Warn so it's diagnosable
```

## Source note 414, line 2001

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2001)

```text
// instead of silently discarding a user-provided target.
```

## Source note 415, line 2015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2015)

```text
// Internal jump table targets are part of this function. Extend
```

## Source note 416, line 2016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2016)

```text
// funcEnd for out-of-line case blocks within the code region.
```

## Source note 417, line 2018

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2018)

```text
// Extend to include this target
```

## Source note 418, line 2030

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2030)

```text
// Conditional branch - follow both paths
```

## Source note 419, line 2038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2038)

```text
// External conditional branch (or conditional tail call to known function)
```

## Source note 420, line 2041

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2041)

```text
// CRITICAL: Fall-through also needs a label
```

## Source note 421, line 2051

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2051)

```text
// Unconditional branch
```

## Source note 422, line 2054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2054)

```text
// Internal unconditional branch (includes backward branches)
```

## Source note 423, line 2061

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2061)

```text
// Tail call to external
```

## Source note 424, line 2071

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2071)

```text
// Check for block terminator (null, prologue of next function, etc.)
```

## Source note 425, line 2081

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2081)

```text
// Log why loop exited if not due to terminator
```

## Source note 426, line 2087

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2087)

```text
// Finalize block size if not set
```

## Source note 427, line 2097

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2097)

```text
// Sort blocks by address
```

## Source note 428, line 2101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_scanner.cpp#L2101)

```text
// Remove duplicate instructions (in case of overlapping scans)
```
