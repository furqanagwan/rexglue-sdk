# Instruction: codegen source notes

This record preserves technical and API notes moved from `src/codegen/ppc/instruction.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L25)

```text
/**
 * PowerPC instruction with decoded fields
 *
 * Uses union-based decoding for efficient field access.
 * Includes semantic information for future recompilation support.
 */
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L32)

```text
// Guest address of instruction
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L33)

```text
// Raw instruction encoding (big-endian)
```

## Source note 4, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L38)

```text
// Format-specific field unions
```

## Source note 5, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L41)

```text
/**
   * Format I - Unconditional Branch (b, ba, bl, bla)
   * Fields: LI (24-bit), AA (1-bit), LK (1-bit)
   */
```

## Source note 6, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L46)

```text
// Branch offset (bits 6-29)
```

## Source note 7, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L47)

```text
// Absolute address flag (bit 30)
```

## Source note 8, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L48)

```text
// Link flag (bit 31)
```

## Source note 9, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L49)

```text
// Primary opcode (bits 0-5)
```

## Source note 10, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L51)

```text
// Get sign-extended branch target offset
```

## Source note 11, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L53)

```text
// Sign-extend 24-bit to 32-bit, then multiply by 4
```

## Source note 12, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L54)

```text
// Sign extend and * 4
```

## Source note 13, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L59)

```text
/**
   * Format B - Conditional Branch (bc, bca, bcl, bcla)
   * Fields: BO (5-bit), BI (5-bit), BD (14-bit), AA (1-bit), LK (1-bit)
   */
```

## Source note 14, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L64)

```text
// Branch displacement (bits 16-29)
```

## Source note 15, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L65)

```text
// Absolute address flag (bit 30)
```

## Source note 16, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L66)

```text
// Link flag (bit 31)
```

## Source note 17, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L67)

```text
// Condition register bit (bits 11-15)
```

## Source note 18, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L68)

```text
// Branch options (bits 6-10)
```

## Source note 19, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L69)

```text
// Primary opcode (bits 0-5)
```

## Source note 20, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L71)

```text
// Get sign-extended branch target offset
```

## Source note 21, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L73)

```text
// Sign-extend 14-bit to 32-bit, then multiply by 4
```

## Source note 22, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L74)

```text
// Sign extend and * 4
```

## Source note 23, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L79)

```text
/**
   * Format D - Immediate operations (load, store, addi, etc.)
   * Fields: RT/RS (5-bit), RA (5-bit), d/SIMM/UIMM (16-bit)
   */
```

## Source note 24, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L84)

```text
// Immediate value (bits 16-31)
```

## Source note 25, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L85)

```text
// Register A (bits 11-15)
```

## Source note 26, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L86)

```text
// Register T/S (bits 6-10)
```

## Source note 27, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L87)

```text
// Primary opcode (bits 0-5)
```

## Source note 28, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L89)

```text
// Signed immediate
```

## Source note 29, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L91)

```text
// Sign-extend 16-bit
```

## Source note 30, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L94)

```text
// Unsigned immediate
```

## Source note 31, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L97)

```text
// Register S (store instructions use this field)
```

## Source note 32, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L101)

```text
/**
   * Format DS - Double-word operations (ld, std)
   * Fields: RT/RS (5-bit), RA (5-bit), DS (14-bit), XO (2-bit)
   */
```

## Source note 33, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L106)

```text
// Extended opcode (bits 30-31)
```

## Source note 34, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L107)

```text
// Displacement (bits 16-29, multiple of 4)
```

## Source note 35, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L108)

```text
// Register A (bits 11-15)
```

## Source note 36, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L109)

```text
// Register T/S (bits 6-10)
```

## Source note 37, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L110)

```text
// Primary opcode (bits 0-5)
```

## Source note 38, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L112)

```text
// Get sign-extended displacement (multiple of 4)
```

## Source note 39, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L114)

```text
// Sign-extend and * 4
```

## Source note 40, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L120)

```text
/**
   * Format X - General register operations (logical, shifts, loads/stores)
   * Fields: RT/RS (5-bit), RA (5-bit), RB (5-bit), XO (10-bit), Rc (1-bit)
   */
```

## Source note 41, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L125)

```text
// Record bit (bit 31)
```

## Source note 42, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L126)

```text
// Extended opcode (bits 21-30)
```

## Source note 43, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L127)

```text
// Register B (bits 16-20)
```

## Source note 44, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L128)

```text
// Register A (bits 11-15)
```

## Source note 45, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L129)

```text
// Register T/S (bits 6-10)
```

## Source note 46, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L130)

```text
// Primary opcode (bits 0-5)
```

## Source note 47, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L135)

```text
/**
   * Format XL - Branch to LR/CTR (bclr, bcctr)
   * Fields: BO (5-bit), BI (5-bit), XO (10-bit), LK (1-bit)
   */
```

## Source note 48, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L140)

```text
// Link bit (bit 31)
```

## Source note 49, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L141)

```text
// Extended opcode (bits 21-30)
```

## Source note 50, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L142)

```text
// Unused (bits 16-20)
```

## Source note 51, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L143)

```text
// Condition register bit (bits 11-15)
```

## Source note 52, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L144)

```text
// Branch options (bits 6-10)
```

## Source note 53, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L145)

```text
// Primary opcode (bits 0-5)
```

## Source note 54, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L148)

```text
/**
   * Format XFX - SPR access (mfspr, mtspr)
   * Fields: RT/RS (5-bit), SPR (10-bit), XO (10-bit)
   */
```

## Source note 55, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L153)

```text
// Unused (bit 31)
```

## Source note 56, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L154)

```text
// Extended opcode (bits 21-30)
```

## Source note 57, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L155)

```text
// SPR number (bits 11-20, encoded split)
```

## Source note 58, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L156)

```text
// Register T/S (bits 6-10)
```

## Source note 59, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L157)

```text
// Primary opcode (bits 0-5)
```

## Source note 60, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L159)

```text
// Get actual SPR number (bits are swapped in encoding)
```

## Source note 61, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L169)

```text
/**
   * Format XO - Arithmetic with overflow (add, sub, mul, div)
   * Fields: RT (5-bit), RA (5-bit), RB (5-bit), OE (1-bit), XO (9-bit), Rc (1-bit)
   */
```

## Source note 62, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L174)

```text
// Record bit (bit 31)
```

## Source note 63, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L175)

```text
// Extended opcode (bits 22-30)
```

## Source note 64, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L176)

```text
// Overflow enable (bit 21)
```

## Source note 65, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L177)

```text
// Register B (bits 16-20)
```

## Source note 66, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L178)

```text
// Register A (bits 11-15)
```

## Source note 67, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L179)

```text
// Register T (bits 6-10)
```

## Source note 68, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L180)

```text
// Primary opcode (bits 0-5)
```

## Source note 69, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L183)

```text
/**
   * Format M - Rotate and mask (rlwinm, rlwnm)
   * Fields: RS (5-bit), RA (5-bit), SH/RB (5-bit), MB (5-bit), ME (5-bit), Rc (1-bit)
   */
```

## Source note 70, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L188)

```text
// Record bit (bit 31)
```

## Source note 71, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L189)

```text
// Mask end (bits 26-30)
```

## Source note 72, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L190)

```text
// Mask begin (bits 21-25)
```

## Source note 73, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L191)

```text
// Shift amount (bits 16-20)
```

## Source note 74, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L192)

```text
// Register A (bits 11-15)
```

## Source note 75, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L193)

```text
// Register S (bits 6-10)
```

## Source note 76, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L194)

```text
// Primary opcode (bits 0-5)
```

## Source note 77, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L196)

```text
// For rlwnm
```

## Source note 78, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L199)

```text
/**
   * Format MD - Rotate double-word (64-bit)
   * Fields: RS (5-bit), RA (5-bit), sh (6-bit), mb (6-bit), XO (3-bit), Rc (1-bit)
   */
```

## Source note 79, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L204)

```text
// Record bit (bit 31)
```

## Source note 80, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L205)

```text
// Extended opcode (bits 27-30, includes sh bit 5)
```

## Source note 81, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L206)

```text
// Mask begin (bits 21-26, includes bit 5)
```

## Source note 82, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L207)

```text
// Shift amount (bits 16-20, includes bit 30)
```

## Source note 83, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L208)

```text
// Register A (bits 11-15)
```

## Source note 84, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L209)

```text
// Register S (bits 6-10)
```

## Source note 85, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L210)

```text
// Primary opcode (bits 0-5)
```

## Source note 86, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L213)

```text
/**
   * Format A - Floating-point arithmetic (fmadd, fmul, etc.)
   * Fields: FRT (5-bit), FRA (5-bit), FRB (5-bit), FRC (5-bit), XO (5-bit), Rc (1-bit)
   */
```

## Source note 87, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L218)

```text
// Record bit (bit 31)
```

## Source note 88, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L219)

```text
// Extended opcode (bits 26-30)
```

## Source note 89, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L220)

```text
// FPR C (bits 21-25)
```

## Source note 90, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L221)

```text
// FPR B (bits 16-20)
```

## Source note 91, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L222)

```text
// FPR A (bits 11-15)
```

## Source note 92, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L223)

```text
// FPR T (target, bits 6-10)
```

## Source note 93, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L224)

```text
// Primary opcode (bits 0-5)
```

## Source note 94, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L227)

```text
/**
   * Format VA - Vector 4-operand (vperm, vmaddfp, etc.)
   * Fields: VRT (5-bit), VRA (5-bit), VRB (5-bit), VRC (5-bit), XO (6-bit)
   */
```

## Source note 95, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L232)

```text
// Extended opcode (bits 26-31)
```

## Source note 96, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L233)

```text
// Vector register C (bits 21-25)
```

## Source note 97, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L234)

```text
// Vector register B (bits 16-20)
```

## Source note 98, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L235)

```text
// Vector register A (bits 11-15)
```

## Source note 99, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L236)

```text
// Vector register T (bits 6-10)
```

## Source note 100, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L237)

```text
// Primary opcode (bits 0-5)
```

## Source note 101, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L239)

```text
// Alias for VD (destination)
```

## Source note 102, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L243)

```text
/**
   * Format VX - Vector 3-operand/2-operand (vaddfp, vand, etc.)
   * Fields: VRT (5-bit), VRA (5-bit), VRB (5-bit), XO (11-bit)
   */
```

## Source note 103, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L248)

```text
// Extended opcode (bits 21-31)
```

## Source note 104, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L249)

```text
// Vector register B (bits 16-20)
```

## Source note 105, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L250)

```text
// Vector register A (bits 11-15)
```

## Source note 106, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L251)

```text
// Vector register T (bits 6-10)
```

## Source note 107, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L252)

```text
// Primary opcode (bits 0-5)
```

## Source note 108, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L254)

```text
// Alias for immediate in some instructions (UIMM in VRA field)
```

## Source note 109, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L256)

```text
// Sign extend 5-bit
```

## Source note 110, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L260)

```text
/**
   * Format VXR - Vector with record bit (vcmp instructions)
   * Fields: VRT (5-bit), VRA (5-bit), VRB (5-bit), Rc (1-bit), XO (10-bit)
   */
```

## Source note 111, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L265)

```text
// Extended opcode (bits 21-30)
```

## Source note 112, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L266)

```text
// Record bit (bit 31, sets CR6)
```

## Source note 113, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L267)

```text
// Vector register B (bits 16-20)
```

## Source note 114, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L268)

```text
// Vector register A (bits 11-15)
```

## Source note 115, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L269)

```text
// Vector register T (bits 6-10)
```

## Source note 116, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L270)

```text
// Primary opcode (bits 0-5)
```

## Source note 117, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L275)

```text
/**
   * Format VMX128 - Xbox 360 extended vector format
   * Uses different register encoding for 128 vector registers
   */
```

## Source note 118, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L280)

```text
// Extended opcode (variable position)
```

## Source note 119, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L281)

```text
// Vector register C (bits 21-25), extended
```

## Source note 120, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L282)

```text
// Vector register B (bits 16-20), extended
```

## Source note 121, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L283)

```text
// Vector register A (bits 11-15), extended
```

## Source note 122, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L284)

```text
// Vector register T (bits 6-10), extended
```

## Source note 123, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L285)

```text
// Primary opcode (bits 0-5)
```

## Source note 124, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L287)

```text
// Get full 7-bit register numbers (0-127)
```

## Source note 125, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L291)

```text
// Union to access different formats
```

## Source note 126, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L303)

```text
// Floating-point A-form
```

## Source note 127, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L304)

```text
// Vector A-form (4 operands)
```

## Source note 128, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L305)

```text
// Vector X-form (3 operands)
```

## Source note 129, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L306)

```text
// Vector X-form with record bit
```

## Source note 130, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L307)

```text
// Xbox 360 VMX128 extended
```

## Source note 131, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L308)

```text
// Raw 32-bit value for direct access
```

## Source note 132, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L312)

```text
// Branch offset extraction using XOR-subtract sign extension
```

## Source note 133, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L315)

```text
/**
   * Get I-form branch offset (26-bit LI field, sign-extended, * 4)
   * For b, ba, bl, bla instructions
   * Uses XOR-subtract technique for reliable sign extension
   */
```

## Source note 134, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L321)

```text
// LI is bits 6-29 (24 bits), but stored with implicit 00 suffix
```

## Source note 135, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L322)

```text
// Mask 0x3FFFFFC extracts bits 2-25 (which is LI * 4)
```

## Source note 136, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L323)

```text
// XOR-subtract with sign bit 0x2000000 for 26-bit sign extension
```

## Source note 137, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L327)

```text
/**
   * Get B-form branch offset (14-bit BD field, sign-extended, * 4)
   * For bc, bca, bcl, bcla instructions
   * Uses XOR-subtract technique for reliable sign extension
   */
```

## Source note 138, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L333)

```text
// BD is bits 16-29 (14 bits), but stored with implicit 00 suffix
```

## Source note 139, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L334)

```text
// Mask 0xFFFC extracts bits 2-15 (which is BD * 4)
```

## Source note 140, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L335)

```text
// XOR-subtract with sign bit 0x8000 for 16-bit sign extension
```

## Source note 141, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L339)

```text
// Pre-computed branch target (if applicable)
```

## Source note 142, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L343)

```text
// Helper methods
```

## Source note 143, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L346)

```text
/**
   * Check if this is a branch instruction
   */
```

## Source note 144, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L351)

```text
/**
   * Check if this is a function call (branch with link)
   */
```

## Source note 145, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L356)

```text
/**
   * Check if this is a return instruction (blr)
   */
```

## Source note 146, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L361)

```text
/**
   * Check if this is an indirect branch (bcctr, bclr)
   */
```

## Source note 147, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L366)

```text
/**
   * Check if this is a record-form instruction (sets CR0).
   * Checks the Rc bit based on the instruction format.
   */
```

## Source note 148, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L372)

```text
/**
   * Check if this is a conditional branch
   * Returns false for unconditional branches (BO=20)
   */
```

## Source note 149, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L378)

```text
/**
   * Get register numbers that this instruction reads from
   */
```

## Source note 150, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L383)

```text
/**
   * Get register numbers that this instruction writes to
   */
```

## Source note 151, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L388)

```text
/**
   * Disassemble instruction to string
   */
```

## Source note 152, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L394)

```text
// Semantic information (for future HIR translation)
```

## Source note 153, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L398)

```text
// GPR registers read
```

## Source note 154, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L399)

```text
// GPR registers written
```

## Source note 155, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L406)

```text
// Condition register
```

## Source note 156, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L413)

```text
/**
   * Get semantic information (computed on demand)
   */
```

## Source note 157, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L419)

```text
/**
 * Decode instruction from raw code
 * @param address Guest address of instruction
 * @param code Raw 32-bit instruction code (host byte order)
 * @return Decoded instruction structure
 */
```

## Source note 158, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L427)

```text
/**
 * PowerPC disassembler to string converter
 *
 * Converts instructions to GNU objdump-style assembly text.
 * Examples:
 *   bl 0x82001234
 *   addi r3, r1, 100
 *   stw r4, 0x20(r1)
 */
```

## Source note 159, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L438)

```text
/**
   * Disassemble a single instruction
   * @param instr Decoded instruction
   * @return Assembly text string
   */
```

## Source note 160, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L446)

```text
// Format helpers
```

## Source note 161, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/instruction.h#L452)

```text
// Instruction-specific formatters
```
