# Opcode: codegen source notes

This record preserves technical and API notes moved from `src/codegen/ppc/opcode.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L18)

```text
/**
 * PowerPC instruction formats
 */
```

## Source note 2, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L23)

```text
// Branch (LI, AA, LK)
```

## Source note 3, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L24)

```text
// Conditional branch (BO, BI, BD, AA, LK)
```

## Source note 4, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L25)

```text
// Immediate (RT, RA, d/SIMM/UIMM)
```

## Source note 5, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L26)

```text
// Double-word store (RT, RA, DS, XO)
```

## Source note 6, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L27)

```text
// General purpose (RT, RA, RB, XO, Rc)
```

## Source note 7, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L28)

```text
// Branch to LR/CTR (BO, BI, XO, LK)
```

## Source note 8, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L29)

```text
// Move to/from SPR (RT, SPR, XO)
```

## Source note 9, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L30)

```text
// Arithmetic with OE (RT, RA, RB, OE, XO, Rc)
```

## Source note 10, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L31)

```text
// Rotate/mask (RS, RA, RB, MB, ME, Rc)
```

## Source note 11, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L32)

```text
// Rotate double-word (RS, RA, sh, mb, XO, Rc)
```

## Source note 12, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L33)

```text
// Floating-point arithmetic (FRT, FRA, FRB, FRC, XO, Rc)
```

## Source note 13, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L34)

```text
// Vector with record bit (VRT, VRA, VRB, Rc, XO)
```

## Source note 14, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L37)

```text
/**
 * PowerPC opcodes
 * Covers essential control flow, ALU, memory, and special register operations
 */
```

## Source note 15, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L44)

```text
// Branch instructions (essential for control flow)
```

## Source note 16, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L46)

```text
// Branch absolute
```

## Source note 17, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L47)

```text
// Branch and link
```

## Source note 18, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L48)

```text
// Branch and link absolute
```

## Source note 19, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L49)

```text
// Branch conditional
```

## Source note 20, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L50)

```text
// Branch conditional absolute
```

## Source note 21, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L51)

```text
// Branch conditional and link
```

## Source note 22, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L52)

```text
// Branch conditional and link absolute
```

## Source note 23, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L53)

```text
// Branch conditional to link register
```

## Source note 24, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L54)

```text
// Branch conditional to link register and link
```

## Source note 25, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L55)

```text
// Branch conditional to count register
```

## Source note 26, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L56)

```text
// Branch conditional to count register and link
```

## Source note 27, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L58)

```text
// Load instructions (byte, half-word, word, double-word)
```

## Source note 28, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L59)

```text
// Load byte and zero
```

## Source note 29, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L60)

```text
// Load byte and zero with update
```

## Source note 30, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L61)

```text
// Load byte and zero indexed
```

## Source note 31, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L62)

```text
// Load half-word and zero
```

## Source note 32, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L63)

```text
// Load half-word and zero with update
```

## Source note 33, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L64)

```text
// Load half-word and zero indexed
```

## Source note 34, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L65)

```text
// Load half-word algebraic
```

## Source note 35, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L66)

```text
// Load half-word algebraic indexed
```

## Source note 36, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L67)

```text
// Load word and zero
```

## Source note 37, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L68)

```text
// Load word and zero with update
```

## Source note 38, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L69)

```text
// Load word and zero indexed
```

## Source note 39, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L70)

```text
// Load double-word
```

## Source note 40, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L71)

```text
// Load double-word with update
```

## Source note 41, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L72)

```text
// Load double-word indexed
```

## Source note 42, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L74)

```text
// Store instructions
```

## Source note 43, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L75)

```text
// Store byte
```

## Source note 44, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L76)

```text
// Store byte with update
```

## Source note 45, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L77)

```text
// Store byte indexed
```

## Source note 46, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L78)

```text
// Store half-word
```

## Source note 47, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L79)

```text
// Store half-word with update
```

## Source note 48, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L80)

```text
// Store half-word indexed
```

## Source note 49, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L81)

```text
// Store word
```

## Source note 50, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L82)

```text
// Store word with update
```

## Source note 51, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L83)

```text
// Store word indexed
```

## Source note 52, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L84)

```text
// Store double-word
```

## Source note 53, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L85)

```text
// Store double-word with update
```

## Source note 54, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L86)

```text
// Store double-word indexed
```

## Source note 55, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L88)

```text
// Integer arithmetic/logical
```

## Source note 56, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L90)

```text
// Add immediate
```

## Source note 57, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L91)

```text
// Add immediate shifted
```

## Source note 58, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L92)

```text
// Add immediate carrying
```

## Source note 59, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L93)

```text
// Add immediate carrying and record
```

## Source note 60, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L94)

```text
// Subtract from
```

## Source note 61, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L95)

```text
// Subtract from immediate carrying
```

## Source note 62, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L97)

```text
// OR immediate
```

## Source note 63, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L98)

```text
// OR immediate shifted
```

## Source note 64, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L99)

```text
// XOR immediate
```

## Source note 65, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L100)

```text
// XOR immediate shifted
```

## Source note 66, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L101)

```text
// AND immediate (note: andi. in assembly)
```

## Source note 67, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L102)

```text
// AND immediate shifted
```

## Source note 68, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L103)

```text
// Multiply low immediate
```

## Source note 69, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L105)

```text
// Multiply/divide
```

## Source note 70, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L106)

```text
// Multiply low word
```

## Source note 71, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L107)

```text
// Multiply high word (signed)
```

## Source note 72, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L108)

```text
// Multiply high word (unsigned)
```

## Source note 73, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L109)

```text
// Divide word (signed)
```

## Source note 74, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L110)

```text
// Divide word (unsigned)
```

## Source note 75, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L112)

```text
// Logical operations
```

## Source note 76, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L113)

```text
// AND (note: and in assembly)
```

## Source note 77, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L118)

```text
// AND with complement
```

## Source note 78, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L119)

```text
// OR with complement
```

## Source note 79, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L120)

```text
// Equivalent (XNOR)
```

## Source note 80, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L122)

```text
// Shifts and rotates
```

## Source note 81, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L123)

```text
// Shift left word
```

## Source note 82, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L124)

```text
// Shift right word
```

## Source note 83, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L125)

```text
// Shift right algebraic word
```

## Source note 84, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L126)

```text
// Shift right algebraic word immediate
```

## Source note 85, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L127)

```text
// Rotate left word immediate then AND with mask
```

## Source note 86, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L128)

```text
// Rotate left word then AND with mask
```

## Source note 87, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L129)

```text
// Count leading zeros word
```

## Source note 88, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L131)

```text
// Sign/zero extension
```

## Source note 89, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L132)

```text
// Extend sign byte
```

## Source note 90, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L133)

```text
// Extend sign halfword
```

## Source note 91, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L137)

```text
// Compare immediate
```

## Source note 92, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L138)

```text
// Compare logical
```

## Source note 93, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L139)

```text
// Compare logical immediate
```

## Source note 94, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L141)

```text
// Special purpose register access
```

## Source note 95, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L142)

```text
// Move from special purpose register
```

## Source note 96, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L143)

```text
// Move to special purpose register
```

## Source note 97, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L144)

```text
// Move from condition register
```

## Source note 98, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L145)

```text
// Move to condition register
```

## Source note 99, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L147)

```text
// Move to/from count/link registers (simplified mnemonics)
```

## Source note 100, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L148)

```text
// Move from link register (mfspr simplified)
```

## Source note 101, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L149)

```text
// Move to link register (mtspr simplified)
```

## Source note 102, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L150)

```text
// Move from count register (mfspr simplified)
```

## Source note 103, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L151)

```text
// Move to count register (mtspr simplified)
```

## Source note 104, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L155)

```text
// Instruction synchronize
```

## Source note 105, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L157)

```text
// System call
```

## Source note 106, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L158)

```text
// System call
```

## Source note 107, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L161)

```text
// Trap word
```

## Source note 108, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L162)

```text
// Trap word immediate
```

## Source note 109, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L164)

```text
// Move register (simplified)
```

## Source note 110, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L165)

```text
// Move register (or rA, rS, rS)
```

## Source note 111, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L167)

```text
// No-op
```

## Source note 112, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L168)

```text
// No operation (ori 0, 0, 0)
```

## Source note 113, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L170)

```text
// Load immediate (simplified)
```

## Source note 114, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L171)

```text
// Load immediate (addi rD, 0, value)
```

## Source note 115, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L172)

```text
// Load immediate shifted (addis rD, 0, value)
```

## Source note 116, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L175)

```text
// Floating-Point Instructions
```

## Source note 117, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L178)

```text
// Floating-point load/store
```

## Source note 118, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L179)

```text
// Load floating-point single
```

## Source note 119, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L180)

```text
// Load floating-point single with update
```

## Source note 120, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L181)

```text
// Load floating-point single indexed
```

## Source note 121, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L182)

```text
// Load floating-point double
```

## Source note 122, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L183)

```text
// Load floating-point double with update
```

## Source note 123, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L184)

```text
// Load floating-point double indexed
```

## Source note 124, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L185)

```text
// Store floating-point single
```

## Source note 125, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L186)

```text
// Store floating-point single with update
```

## Source note 126, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L187)

```text
// Store floating-point single indexed
```

## Source note 127, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L188)

```text
// Store floating-point double
```

## Source note 128, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L189)

```text
// Store floating-point double with update
```

## Source note 129, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L190)

```text
// Store floating-point double indexed
```

## Source note 130, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L192)

```text
// Floating-point arithmetic
```

## Source note 131, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L193)

```text
// Floating add (double)
```

## Source note 132, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L194)

```text
// Floating add single
```

## Source note 133, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L195)

```text
// Floating subtract (double)
```

## Source note 134, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L196)

```text
// Floating subtract single
```

## Source note 135, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L197)

```text
// Floating multiply (double)
```

## Source note 136, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L198)

```text
// Floating multiply single
```

## Source note 137, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L199)

```text
// Floating divide (double)
```

## Source note 138, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L200)

```text
// Floating divide single
```

## Source note 139, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L201)

```text
// Floating square root (double)
```

## Source note 140, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L202)

```text
// Floating square root single
```

## Source note 141, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L203)

```text
// Floating reciprocal estimate
```

## Source note 142, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L204)

```text
// Floating reciprocal estimate single
```

## Source note 143, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L205)

```text
// Floating reciprocal square root estimate
```

## Source note 144, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L206)

```text
// Floating reciprocal square root estimate single
```

## Source note 145, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L208)

```text
// Floating-point multiply-add
```

## Source note 146, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L209)

```text
// Floating multiply-add (double)
```

## Source note 147, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L210)

```text
// Floating multiply-add single
```

## Source note 148, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L211)

```text
// Floating multiply-subtract (double)
```

## Source note 149, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L212)

```text
// Floating multiply-subtract single
```

## Source note 150, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L213)

```text
// Floating negative multiply-add (double)
```

## Source note 151, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L214)

```text
// Floating negative multiply-add single
```

## Source note 152, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L215)

```text
// Floating negative multiply-subtract (double)
```

## Source note 153, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L216)

```text
// Floating negative multiply-subtract single
```

## Source note 154, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L218)

```text
// Floating-point rounding/conversion
```

## Source note 155, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L219)

```text
// Floating round to single precision
```

## Source note 156, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L220)

```text
// Floating convert to integer word
```

## Source note 157, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L221)

```text
// Floating convert to integer word with round toward zero
```

## Source note 158, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L222)

```text
// Floating convert from integer doubleword
```

## Source note 159, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L223)

```text
// Floating convert to integer doubleword
```

## Source note 160, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L224)

```text
// Floating convert to integer doubleword with round toward zero
```

## Source note 161, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L226)

```text
// Floating-point move/misc
```

## Source note 162, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L227)

```text
// Floating move register
```

## Source note 163, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L228)

```text
// Floating absolute value
```

## Source note 164, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L229)

```text
// Floating negative absolute value
```

## Source note 165, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L230)

```text
// Floating negate
```

## Source note 166, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L231)

```text
// Floating select
```

## Source note 167, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L233)

```text
// Floating-point compare
```

## Source note 168, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L234)

```text
// Floating compare unordered
```

## Source note 169, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L235)

```text
// Floating compare ordered
```

## Source note 170, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L237)

```text
// Floating-point status/control
```

## Source note 171, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L238)

```text
// Move from FPSCR
```

## Source note 172, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L239)

```text
// Move to FPSCR fields
```

## Source note 173, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L240)

```text
// Move to FPSCR field immediate
```

## Source note 174, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L241)

```text
// Move to FPSCR bit 0
```

## Source note 175, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L242)

```text
// Move to FPSCR bit 1
```

## Source note 176, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L245)

```text
// VMX/VMX128 Vector Instructions (Xbox 360)
```

## Source note 177, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L248)

```text
// Vector load/store (standard VMX)
```

## Source note 178, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L249)

```text
// Load vector indexed
```

## Source note 179, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L250)

```text
// Load vector indexed LRU
```

## Source note 180, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L251)

```text
// Store vector indexed
```

## Source note 181, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L252)

```text
// Store vector indexed LRU
```

## Source note 182, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L253)

```text
// Load vector left indexed
```

## Source note 183, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L254)

```text
// Load vector right indexed
```

## Source note 184, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L255)

```text
// Store vector left indexed
```

## Source note 185, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L256)

```text
// Store vector right indexed
```

## Source note 186, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L257)

```text
// Load vector for shift left
```

## Source note 187, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L258)

```text
// Load vector for shift right
```

## Source note 188, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L260)

```text
// Vector load/store (VMX128 extended - 128 registers)
```

## Source note 189, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L261)

```text
// Load vector indexed (128-reg)
```

## Source note 190, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L262)

```text
// Store vector indexed (128-reg)
```

## Source note 191, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L263)

```text
// Load vector left indexed (128-reg)
```

## Source note 192, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L264)

```text
// Load vector right indexed (128-reg)
```

## Source note 193, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L265)

```text
// Store vector left indexed (128-reg)
```

## Source note 194, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L266)

```text
// Store vector right indexed (128-reg)
```

## Source note 195, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L267)

```text
// Load vector left indexed LRU (128-reg)
```

## Source note 196, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L268)

```text
// Load vector right indexed LRU (128-reg)
```

## Source note 197, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L269)

```text
// Store vector left indexed LRU (128-reg)
```

## Source note 198, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L270)

```text
// Store vector right indexed LRU (128-reg)
```

## Source note 199, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L271)

```text
// Load vector for shift left (128-reg)
```

## Source note 200, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L272)

```text
// Load vector for shift right (128-reg)
```

## Source note 201, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L273)

```text
// Load vector element word indexed (128-reg)
```

## Source note 202, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L274)

```text
// Load vector indexed LRU (128-reg)
```

## Source note 203, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L275)

```text
// Store vector element word indexed (128-reg)
```

## Source note 204, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L276)

```text
// Store vector indexed LRU (128-reg)
```

## Source note 205, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L277)

```text
// Vector shift left double by octet immediate (128-reg)
```

## Source note 206, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L279)

```text
// Vector floating-point arithmetic
```

## Source note 207, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L280)

```text
// Vector add floating-point
```

## Source note 208, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L281)

```text
// Vector subtract floating-point
```

## Source note 209, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L282)

```text
// Vector multiply-add floating-point
```

## Source note 210, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L283)

```text
// Vector negative multiply-subtract floating-point
```

## Source note 211, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L284)

```text
// Vector multiply floating-point (128-reg)
```

## Source note 212, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L285)

```text
// Vector reciprocal square root estimate floating-point
```

## Source note 213, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L286)

```text
// Vector reciprocal estimate floating-point
```

## Source note 214, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L287)

```text
// Vector log2 estimate floating-point
```

## Source note 215, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L288)

```text
// Vector 2^x estimate floating-point
```

## Source note 216, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L289)

```text
// Vector maximum floating-point
```

## Source note 217, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L290)

```text
// Vector minimum floating-point
```

## Source note 218, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L292)

```text
// VMX128 floating-point arithmetic (Xbox 360 specific)
```

## Source note 219, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L293)

```text
// Vector add floating-point (128-reg)
```

## Source note 220, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L294)

```text
// Vector subtract floating-point (128-reg)
```

## Source note 221, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L295)

```text
// Vector multiply-add floating-point (128-reg)
```

## Source note 222, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L296)

```text
// Vector multiply-add floating-point (C variant, 128-reg)
```

## Source note 223, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L297)

```text
// Vector negative multiply-subtract floating-point (128-reg)
```

## Source note 224, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L298)

```text
// Vector maximum floating-point (128-reg)
```

## Source note 225, line 299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L299)

```text
// Vector minimum floating-point (128-reg)
```

## Source note 226, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L300)

```text
// Vector reciprocal estimate floating-point (128-reg)
```

## Source note 227, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L301)

```text
// Vector reciprocal square root estimate floating-point (128-reg)
```

## Source note 228, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L302)

```text
// Vector 2^x estimate floating-point (128-reg)
```

## Source note 229, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L303)

```text
// Vector log2 estimate floating-point (128-reg)
```

## Source note 230, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L305)

```text
// VMX128 dot product instructions (Xbox 360 specific)
```

## Source note 231, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L306)

```text
// Vector 3-element dot product (128-reg)
```

## Source note 232, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L307)

```text
// Vector 4-element dot product (128-reg)
```

## Source note 233, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L308)

```text
// Vector multiply-sum 3-element (128-reg)
```

## Source note 234, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L309)

```text
// Vector multiply-sum 4-element (128-reg)
```

## Source note 235, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L311)

```text
// Vector integer arithmetic
```

## Source note 236, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L312)

```text
// Vector add unsigned byte modulo
```

## Source note 237, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L313)

```text
// Vector add unsigned halfword modulo
```

## Source note 238, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L314)

```text
// Vector add unsigned word modulo
```

## Source note 239, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L315)

```text
// Vector subtract unsigned byte modulo
```

## Source note 240, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L316)

```text
// Vector subtract unsigned halfword modulo
```

## Source note 241, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L317)

```text
// Vector subtract unsigned word modulo
```

## Source note 242, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L318)

```text
// Vector multiply odd unsigned byte
```

## Source note 243, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L319)

```text
// Vector multiply odd unsigned halfword
```

## Source note 244, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L320)

```text
// Vector multiply odd unsigned word
```

## Source note 245, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L321)

```text
// Vector multiply even unsigned byte
```

## Source note 246, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L322)

```text
// Vector multiply even unsigned halfword
```

## Source note 247, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L323)

```text
// Vector multiply even unsigned word
```

## Source note 248, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L324)

```text
// Vector average unsigned byte
```

## Source note 249, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L325)

```text
// Vector average unsigned halfword
```

## Source note 250, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L326)

```text
// Vector average unsigned word
```

## Source note 251, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L328)

```text
// Vector logical
```

## Source note 252, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L329)

```text
// Vector AND
```

## Source note 253, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L330)

```text
// Vector AND with complement
```

## Source note 254, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L331)

```text
// Vector OR
```

## Source note 255, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L332)

```text
// Vector OR with complement (VMX128)
```

## Source note 256, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L333)

```text
// Vector XOR
```

## Source note 257, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L334)

```text
// Vector NOR
```

## Source note 258, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L335)

```text
// Vector select
```

## Source note 259, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L337)

```text
// VMX128 logical (Xbox 360 specific)
```

## Source note 260, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L338)

```text
// Vector AND (128-reg)
```

## Source note 261, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L339)

```text
// Vector AND with complement (128-reg)
```

## Source note 262, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L340)

```text
// Vector OR (128-reg)
```

## Source note 263, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L341)

```text
// Vector XOR (128-reg)
```

## Source note 264, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L342)

```text
// Vector NOR (128-reg)
```

## Source note 265, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L343)

```text
// Vector select (128-reg)
```

## Source note 266, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L344)

```text
// Vector shift left by octet (128-reg)
```

## Source note 267, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L345)

```text
// Vector shift right by octet (128-reg)
```

## Source note 268, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L347)

```text
// Vector compare floating-point
```

## Source note 269, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L348)

```text
// Vector compare equal-to floating-point
```

## Source note 270, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L349)

```text
// Vector compare greater-than-or-equal floating-point
```

## Source note 271, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L350)

```text
// Vector compare greater-than floating-point
```

## Source note 272, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L351)

```text
// Vector compare bounds floating-point
```

## Source note 273, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L352)

```text
// Vector compare equal-to floating-point (Rc=1)
```

## Source note 274, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L353)

```text
// Vector compare greater-than-or-equal floating-point (Rc=1)
```

## Source note 275, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L354)

```text
// Vector compare greater-than floating-point (Rc=1)
```

## Source note 276, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L356)

```text
// Vector compare integer
```

## Source note 277, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L357)

```text
// Vector compare equal unsigned byte
```

## Source note 278, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L358)

```text
// Vector compare equal unsigned halfword
```

## Source note 279, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L359)

```text
// Vector compare equal unsigned word
```

## Source note 280, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L360)

```text
// Vector compare greater-than unsigned byte
```

## Source note 281, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L361)

```text
// Vector compare greater-than unsigned halfword
```

## Source note 282, line 362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L362)

```text
// Vector compare greater-than unsigned word
```

## Source note 283, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L363)

```text
// Vector compare greater-than signed byte
```

## Source note 284, line 364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L364)

```text
// Vector compare greater-than signed halfword
```

## Source note 285, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L365)

```text
// Vector compare greater-than signed word
```

## Source note 286, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L367)

```text
// VMX128 compare (Xbox 360 specific)
```

## Source note 287, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L368)

```text
// Vector compare equal-to floating-point (128-reg)
```

## Source note 288, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L369)

```text
// Vector compare greater-than-or-equal floating-point (128-reg)
```

## Source note 289, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L370)

```text
// Vector compare greater-than floating-point (128-reg)
```

## Source note 290, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L371)

```text
// Vector compare bounds floating-point (128-reg)
```

## Source note 291, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L372)

```text
// Vector compare equal unsigned word (128-reg)
```

## Source note 292, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L374)

```text
// Vector permute/merge
```

## Source note 293, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L375)

```text
// Vector permute
```

## Source note 294, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L376)

```text
// Vector permute (128-reg)
```

## Source note 295, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L377)

```text
// Vector merge high byte
```

## Source note 296, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L378)

```text
// Vector merge high halfword
```

## Source note 297, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L379)

```text
// Vector merge high word
```

## Source note 298, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L380)

```text
// Vector merge low byte
```

## Source note 299, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L381)

```text
// Vector merge low halfword
```

## Source note 300, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L382)

```text
// Vector merge low word
```

## Source note 301, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L384)

```text
// VMX128 merge (Xbox 360 specific)
```

## Source note 302, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L385)

```text
// Vector merge high word (128-reg)
```

## Source note 303, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L386)

```text
// Vector merge low word (128-reg)
```

## Source note 304, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L387)

```text
// Vector permute word immediate (128-reg)
```

## Source note 305, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L389)

```text
// Vector pack/unpack
```

## Source note 306, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L390)

```text
// Vector pack unsigned halfword unsigned modulo
```

## Source note 307, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L391)

```text
// Vector pack unsigned word unsigned modulo
```

## Source note 308, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L392)

```text
// Vector pack unsigned halfword unsigned saturate
```

## Source note 309, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L393)

```text
// Vector pack unsigned word unsigned saturate
```

## Source note 310, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L394)

```text
// Vector pack signed halfword unsigned saturate
```

## Source note 311, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L395)

```text
// Vector pack signed word unsigned saturate
```

## Source note 312, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L396)

```text
// Vector pack signed halfword signed saturate
```

## Source note 313, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L397)

```text
// Vector pack signed word signed saturate
```

## Source note 314, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L398)

```text
// Vector unpack high signed byte
```

## Source note 315, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L399)

```text
// Vector unpack high signed halfword
```

## Source note 316, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L400)

```text
// Vector unpack low signed byte
```

## Source note 317, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L401)

```text
// Vector unpack low signed halfword
```

## Source note 318, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L403)

```text
// VMX128 pack (Xbox 360 specific)
```

## Source note 319, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L404)

```text
// Vector pack signed halfword signed saturate (128-reg)
```

## Source note 320, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L405)

```text
// Vector pack signed halfword unsigned saturate (128-reg)
```

## Source note 321, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L406)

```text
// Vector pack signed word signed saturate (128-reg)
```

## Source note 322, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L407)

```text
// Vector pack signed word unsigned saturate (128-reg)
```

## Source note 323, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L408)

```text
// Vector pack unsigned halfword unsigned modulo (128-reg)
```

## Source note 324, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L409)

```text
// Vector pack unsigned halfword unsigned saturate (128-reg)
```

## Source note 325, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L410)

```text
// Vector pack unsigned word unsigned modulo (128-reg)
```

## Source note 326, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L411)

```text
// Vector pack unsigned word unsigned saturate (128-reg)
```

## Source note 327, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L412)

```text
// Vector unpack high signed byte (128-reg)
```

## Source note 328, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L413)

```text
// Vector unpack low signed byte (128-reg)
```

## Source note 329, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L415)

```text
// Vector splat
```

## Source note 330, line 416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L416)

```text
// Vector splat byte
```

## Source note 331, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L417)

```text
// Vector splat halfword
```

## Source note 332, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L418)

```text
// Vector splat word
```

## Source note 333, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L419)

```text
// Vector splat immediate signed byte
```

## Source note 334, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L420)

```text
// Vector splat immediate signed halfword
```

## Source note 335, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L421)

```text
// Vector splat immediate signed word
```

## Source note 336, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L423)

```text
// VMX128 splat (Xbox 360 specific)
```

## Source note 337, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L424)

```text
// Vector splat word (128-reg)
```

## Source note 338, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L425)

```text
// Vector splat immediate signed word (128-reg)
```

## Source note 339, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L427)

```text
// Vector shift/rotate
```

## Source note 340, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L428)

```text
// Vector shift left byte
```

## Source note 341, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L429)

```text
// Vector shift left halfword
```

## Source note 342, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L430)

```text
// Vector shift left word
```

## Source note 343, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L431)

```text
// Vector shift right byte
```

## Source note 344, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L432)

```text
// Vector shift right halfword
```

## Source note 345, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L433)

```text
// Vector shift right word
```

## Source note 346, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L434)

```text
// Vector shift right algebraic byte
```

## Source note 347, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L435)

```text
// Vector shift right algebraic halfword
```

## Source note 348, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L436)

```text
// Vector shift right algebraic word
```

## Source note 349, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L437)

```text
// Vector rotate left byte
```

## Source note 350, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L438)

```text
// Vector rotate left halfword
```

## Source note 351, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L439)

```text
// Vector rotate left word
```

## Source note 352, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L440)

```text
// Vector shift left (128-bit)
```

## Source note 353, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L441)

```text
// Vector shift right (128-bit)
```

## Source note 354, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L442)

```text
// Vector shift left by octet
```

## Source note 355, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L443)

```text
// Vector shift right by octet
```

## Source note 356, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L445)

```text
// Vector conversion
```

## Source note 357, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L446)

```text
// Vector convert from unsigned fixed-point word
```

## Source note 358, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L447)

```text
// Vector convert from signed fixed-point word
```

## Source note 359, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L448)

```text
// Vector convert to unsigned fixed-point word saturate
```

## Source note 360, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L449)

```text
// Vector convert to signed fixed-point word saturate
```

## Source note 361, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L450)

```text
// Vector round to floating-point integer nearest
```

## Source note 362, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L451)

```text
// Vector round to floating-point integer toward zero
```

## Source note 363, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L452)

```text
// Vector round to floating-point integer toward +infinity
```

## Source note 364, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L453)

```text
// Vector round to floating-point integer toward -infinity
```

## Source note 365, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L455)

```text
// VMX128 conversion (Xbox 360 specific)
```

## Source note 366, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L456)

```text
// Vector convert from FP to signed fixed-point word saturate (128-reg)
```

## Source note 367, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L457)

```text
// Vector convert from FP to unsigned fixed-point word saturate (128-reg)
```

## Source note 368, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L458)

```text
// Vector convert from signed fixed-point word to FP (128-reg)
```

## Source note 369, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L459)

```text
// Vector convert from unsigned fixed-point word to FP (128-reg)
```

## Source note 370, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L460)

```text
// Vector round to FP integer toward -infinity (128-reg)
```

## Source note 371, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L461)

```text
// Vector round to FP integer nearest (128-reg)
```

## Source note 372, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L462)

```text
// Vector round to FP integer toward +infinity (128-reg)
```

## Source note 373, line 463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L463)

```text
// Vector round to FP integer toward zero (128-reg)
```

## Source note 374, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L465)

```text
// VMX128 move/misc
```

## Source note 375, line 466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L466)

```text
// Vector merge odd word (128-reg)
```

## Source note 376, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L467)

```text
// Vector merge even word (128-reg)
```

## Source note 377, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L468)

```text
// Vector rotate left word (128-reg)
```

## Source note 378, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L469)

```text
// Vector shift left word (128-reg)
```

## Source note 379, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L470)

```text
// Vector shift right word (128-reg)
```

## Source note 380, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L471)

```text
// Vector shift right algebraic word (128-reg)
```

## Source note 381, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L472)

```text
// Vector unpack D3D format (128-reg)
```

## Source note 382, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L473)

```text
// Vector pack D3D format (128-reg)
```

## Source note 383, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L474)

```text
// Vector rotate left immediate and mask insert (128-reg)
```

## Source note 384, line 476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L476)

```text
// Vector status/control
```

## Source note 385, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L477)

```text
// Move from vector status and control register
```

## Source note 386, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L478)

```text
// Move to vector status and control register
```

## Source note 387, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L481)

```text
/**
 * Opcode groups for classification
 */
```

## Source note 388, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L485)

```text
// General ALU/logical
```

## Source note 389, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L486)

```text
// Branch/control flow
```

## Source note 390, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L487)

```text
// Load/store
```

## Source note 391, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L488)

```text
// SPR access
```

## Source note 392, line 490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L490)

```text
// System call/trap
```

## Source note 393, line 491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L491)

```text
// Floating-point
```

## Source note 394, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L492)

```text
// VMX/VMX128 vector
```

## Source note 395, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L495)

```text
/**
 * Check if opcode is a branch instruction
 * Used for basic block boundary detection
 */
```

## Source note 396, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L519)

```text
/**
 * Check if opcode is an unconditional branch (always taken)
 * Used for control flow analysis
 */
```

## Source note 397, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L535)

```text
/**
 * Check if opcode terminates a basic block (branch or return)
 * Used for control flow analysis
 */
```

## Source note 398, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L553)

```text
// System call
```

## Source note 399, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L554)

```text
// Trap word
```

## Source note 400, line 555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L555)

```text
// Trap word immediate
```

## Source note 401, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L562)

```text
/**
 * Opcode information structure
 */
```

## Source note 402, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L570)

```text
// Bits 0-5
```

## Source note 403, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L571)

```text
// Bits 21-30 (or other extended field)
```

## Source note 404, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L572)

```text
// True if uses extended opcode
```

## Source note 405, line 575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L575)

```text
/**
 * Lookup opcode from instruction code
 * @param code Raw 32-bit instruction (big-endian)
 * @return Opcode enum value
 */
```

## Source note 406, line 582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/opcode.h#L582)

```text
/**
 * Get opcode information
 * @param opcode Opcode enum value
 * @return Opcode information structure
 */
```
