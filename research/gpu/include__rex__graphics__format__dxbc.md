# Dxbc: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/format/dxbc.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L25)

```text
// Utilities for generating shader model 5_1 byte code (for Direct3D 12).
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L27)

```text
// This file contains only parts of DXBC used by Xenia currently or previously,
```

## Source note 3, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L28)

```text
// not all of DXBC. If an operation, operand, blob or something else is needed
```

## Source note 4, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L29)

```text
// for Xenia, but is not here, add it (after reproducing it with FXC to see what
```

## Source note 5, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L30)

```text
// dependencies - such as STAT fields being modified - and encoding specifics it
```

## Source note 6, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L31)

```text
// has).
```

## Source note 7, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L33)

```text
// IMPORTANT CONTRIBUTION NOTES:
```

## Source note 8, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L35)

```text
// While DXBC may look like a flexible and high-level representation with highly
```

## Source note 9, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L36)

```text
// generalized building blocks, actually it has a lot of restrictions on operand
```

## Source note 10, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L37)

```text
// usage!
```

## Source note 11, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L41)

```text
// !!!DO NOT ADD ANYTHING FXC THAT WOULD NOT PRODUCE!!!
```

## Source note 12, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L45)

```text
// Before adding any sequence that you haven't seen in Xenia, try writing
```

## Source note 13, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L46)

```text
// equivalent code in HLSL and running it through FXC, try with /Od, try with
```

## Source note 14, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L47)

```text
// full optimization, but if you see that FXC follows a different pattern than
```

## Source note 15, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L48)

```text
// what you are expecting, do what FXC does!!!
```

## Source note 16, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L49)

```text
// Most important limitations:
```

## Source note 17, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L50)

```text
// - Absolute, negate and saturate are only supported by instructions that
```

## Source note 18, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L51)

```text
//   explicitly support them. See MSDN pages of the specific instructions you
```

## Source note 19, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L52)

```text
//   want to use with modifiers:
```

## Source note 20, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L53)

```text
//   https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx9-graphics-reference-asm
```

## Source note 21, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L54)

```text
// - Component selection in the general case (ALU instructions - things like
```

## Source note 22, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L55)

```text
//   resource access and flow control mostly explicitly need a specific
```

## Source note 23, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L56)

```text
//   component selection mode defined in the specification of the instruction):
```

## Source note 24, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L57)

```text
//   - 0-component - for operand types with no data (samplers, labels).
```

## Source note 25, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L58)

```text
//   - 1-component - for scalar destination operand types, and for scalar source
```

## Source note 26, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L59)

```text
//     operand types when the destination vector has 1 component masked
```

## Source note 27, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L60)

```text
//     (including scalar immediates).
```

## Source note 28, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L61)

```text
//   - Mask - for vector destination operand types.
```

## Source note 29, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L62)

```text
//   - Swizzle - for both vector and scalar (replicated in this case) source
```

## Source note 30, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L63)

```text
//     operand types, when the destination vector has 2 or more components
```

## Source note 31, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L64)

```text
//     masked. Immediates in this case have XYZW swizzle.
```

## Source note 32, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L65)

```text
//   - Select 1 - for vector source operand types, when the destination has 1
```

## Source note 33, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L66)

```text
//     component masked or is of a scalar type.
```

## Source note 34, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L67)

```text
// - Input operands (v#) can be used only as sources, output operands (o#) can
```

## Source note 35, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L68)

```text
//   be used only as destinations.
```

## Source note 36, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L69)

```text
// - Indexable temporaries (x#) can only be used as a destination or a source
```

## Source note 37, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L70)

```text
//   operand (but not both at once) of a mov instruction - a load/store pattern
```

## Source note 38, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L71)

```text
//   here. Also, movs involving x# are counted as ArrayInstructions rather than
```

## Source note 39, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L72)

```text
//   MovInstructions in STAT. The other operand can be anything that most other
```

## Source note 40, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L73)

```text
//   instructions accept, but it still must be a mov with x# on one side.
```

## Source note 41, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L74)

```text
// !NOTE!: The D3D11.3 Functional Specification on Microsoft's GitHub profile,
```

## Source note 42, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L75)

```text
// as of March 27th, 2020, is NOT a reliable reference, even though it contains
```

## Source note 43, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L76)

```text
// many DXBC details! There are multiple places where it clearly contradicts
```

## Source note 44, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L77)

```text
// what FXC does, even when targeting old shader models like 4_0:
```

## Source note 45, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L78)

```text
// - The limit of 1 immediate or constant buffer source operand per instruction
```

## Source note 46, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L79)

```text
//   is totally ignored by FXC - in simple tests, it can emit an instruction
```

## Source note 47, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L80)

```text
//   with two constant buffer sources, or one constant buffer source and one
```

## Source note 48, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L81)

```text
//   immediate, or a multiply-add with two immediate operands.
```

## Source note 49, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L82)

```text
// - It says x# can be used wherever r# can be used - in synthetic tests, FXC
```

## Source note 50, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L83)

```text
//   always accesses x# in a load/store way via mov.
```

## Source note 51, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L84)

```text
// - It says x# can be used for indexing, including nested indexing of x# (one
```

## Source note 52, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L85)

```text
//   level deep), however, FXC moves the inner index operand to r# first in this
```

## Source note 53, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L86)

```text
//   case.
```

## Source note 54, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L88)

```text
// For bytecode structure, see d3d12TokenizedProgramFormat.hpp from the Windows
```

## Source note 55, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L89)

```text
// Driver Kit, and DXILConv from DirectX Shader Compiler.
```

## Source note 56, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L91)

```text
// Avoid using uninitialized register components - such as registers written to
```

## Source note 57, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L92)

```text
// in "if" and not in "else", but then used outside unconditionally or with a
```

## Source note 58, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L93)

```text
// different condition (or even with the same condition, but in a different "if"
```

## Source note 59, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L94)

```text
// block). This will cause crashes on AMD drivers, and will also limit
```

## Source note 60, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L95)

```text
// optimization possibilities as this may result in false dependencies. Always
```

## Source note 61, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L96)

```text
// mov l(0, 0, 0, 0) to such components before potential branching -
```

## Source note 62, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L97)

```text
// PushSystemTemp accepts a zero mask for this purpose.
```

## Source note 63, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L99)

```text
// Clamping of non-negative values must be done first to the lower bound (using
```

## Source note 64, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L100)

```text
// max), then to the upper bound (using min), to match the saturate modifier
```

## Source note 65, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L101)

```text
// behavior, which results in 0 for NaN.
```

## Source note 66, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L103)

```text
// Sources (apart from reverse engineering of compiled shaders):
```

## Source note 67, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L104)

```text
// - Hash:
```

## Source note 68, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L105)

```text
//   - DXBCChecksum from GPUOpen-Archive/common-src-ShaderUtils
```

## Source note 69, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L106)

```text
// - RDEF:
```

## Source note 70, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L107)

```text
//   - d3d12shader.h from the Windows SDK
```

## Source note 71, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L108)

```text
//   - D3D10ShaderObject.h from GPUOpen-Archive/common-src-ShaderUtils
```

## Source note 72, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L109)

```text
// - ISGN, PCSG, OSGN:
```

## Source note 73, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L110)

```text
//   - d3d12shader.h from the Windows SDK
```

## Source note 74, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L111)

```text
//   - DxbcSignatures.h from DXILConv
```

## Source note 75, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L112)

```text
// - SHEX:
```

## Source note 76, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L113)

```text
//   - d3d12TokenizedProgramFormat.hpp from the Windows Driver Kit
```

## Source note 77, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L114)

```text
// - SFI0:
```

## Source note 78, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L115)

```text
//   - DXBCUtils.h from the D3D12 Translation Layer
```

## Source note 79, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L116)

```text
// - STAT:
```

## Source note 80, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L117)

```text
//   - D3D10ShaderObject.h fromGPUOpen-Archive/common-src-ShaderUtils
```

## Source note 81, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L118)

```text
//   - d3dcompiler_parse_stat from Wine
```

## Source note 82, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L119)

```text
//   - d3d12shader.h from the Windows SDK
```

## Source note 83, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L120)

```text
// Note that d3d12shader.h contains structures for use with Direct3D reflection
```

## Source note 84, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L121)

```text
// interfaces, not the DXBC containers themselves. They may have fields removed,
```

## Source note 85, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L122)

```text
// reordered or added.
```

## Source note 86, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L124)

```text
// Pointers in RDEF and signatures are offsets from the start of the blob (not
```

## Source note 87, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L125)

```text
// including the FourCC and the size), 0 pointer is considered null when
```

## Source note 88, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L126)

```text
// applicable.
```

## Source note 89, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L128)

```text
// Even if DXIL emission is added to Xenia, it's still desirable to keep the
```

## Source note 90, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L129)

```text
// DXBC emitter as a usable option (unless supporting it becomes excessively
```

## Source note 91, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L130)

```text
// burdensome) - apart from much worse readability of the resulting DXIL code,
```

## Source note 92, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L131)

```text
// the UWP GPU driver on the Xbox One also doesn't support DXIL.
```

## Source note 93, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L144)

```text
// Of the entire DXBC container including this header, with this set to 0
```

## Source note 94, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L145)

```text
// before hashing. Calculate using CalculateDXBCChecksum from
```

## Source note 95, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L146)

```text
// GPUOpen-Archive/common-src-ShaderUtils.
```

## Source note 96, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L157)

```text
// Followed by uint32_t[blob_count] offsets from the start of the container in
```

## Source note 97, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L158)

```text
// bytes to the start of each blob's header.
```

## Source note 98, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L164)

```text
// In order of appearance in a container.
```

## Source note 99, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L181)

```text
// Appends a string to a DWORD stream, returns the DWORD-aligned length.
```

## Source note 100, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L188)

```text
// Don't leave uninitialized data, and make sure multiple uses of the
```

## Source note 101, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L189)

```text
// assembler with the same input give the same DXBC for driver shader caching.
```

## Source note 102, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L195)

```text
// Returns the length of a string as if it was appended to a DWORD stream, in
```

## Source note 103, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L196)

```text
// bytes.
```

## Source note 104, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L201)

```text
// D3DCOMPILE subset
```

## Source note 105, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L203)

```text
// NoPreshader and PreferFlowControl are set by default for shader model 5_1.
```

## Source note 106, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L211)

```text
// D3D_SHADER_VARIABLE_CLASS
```

## Source note 107, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L223)

```text
// D3D_SHADER_VARIABLE_TYPE subset
```

## Source note 108, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L230)

```text
// D3D_SHADER_VARIABLE_FLAGS
```

## Source note 109, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L238)

```text
// D3D_SHADER_CBUFFER_FLAGS
```

## Source note 110, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L243)

```text
// D3D_CBUFFER_TYPE
```

## Source note 111, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L251)

```text
// D3D_SHADER_INPUT_TYPE
```

## Source note 112, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L267)

```text
// D3D_RESOURCE_RETURN_TYPE / D3D10_SB_RESOURCE_RETURN_TYPE
```

## Source note 113, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L280)

```text
// D3D12_SRV_DIMENSION / D3D12_UAV_DIMENSION
```

## Source note 114, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L303)

```text
// D3D_SHADER_INPUT_FLAGS
```

## Source note 115, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L305)

```text
// For constant buffers, UserPacked is set if it was declared as `cbuffer`
```

## Source note 116, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L306)

```text
// rather than `ConstantBuffer<T>` (not dynamically indexable; though
```

## Source note 117, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L307)

```text
// non-uniform dynamic indexing of constant buffers also didn't work on AMD
```

## Source note 118, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L308)

```text
// drivers in 2018) - not to be confused with kRdefCbufferFlagUserPacked,
```

## Source note 119, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L309)

```text
// which is set in a different case.
```

## Source note 120, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L312)

```text
// Texture and typed buffer component count minus 1.
```

## Source note 121, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L328)

```text
// D3D12_SHADER_TYPE_DESC with some differences.
```

## Source note 122, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L332)

```text
// Matrix rows, 1 for other numeric, 0 if not applicable.
```

## Source note 123, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L334)

```text
// Vector and matrix columns, 1 for other numerics, 0 if not applicable.
```

## Source note 124, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L336)

```text
// 0 if not an array, except for structures which have 1.
```

## Source note 125, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L338)

```text
// 0 if not a structure.
```

## Source note 126, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L340)

```text
// Null if not a structure.
```

## Source note 127, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L342)

```text
// Zero.
```

## Source note 128, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L344)

```text
// uint is called dword when it's scalar (but uint vectors are still uintN).
```

## Source note 129, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L356)

```text
// D3D12_SHADER_VARIABLE_DESC with some differences.
```

## Source note 130, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L357)

```text
// Used for constants in constant buffers primarily.
```

## Source note 131, line 362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L362)

```text
// RdefVariableFlags.
```

## Source note 132, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L366)

```text
// UINT32_MAX if no textures used.
```

## Source note 133, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L368)

```text
// Number of texture slots possibly used, 0 if no textures used.
```

## Source note 134, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L370)

```text
// UINT32_MAX if no textures used.
```

## Source note 135, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L372)

```text
// Number of sampler slots possibly used, 0 if no textures used.
```

## Source note 136, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L377)

```text
// Sorted by ID.
```

## Source note 137, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L382)

```text
// 16-byte-aligned.
```

## Source note 138, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L385)

```text
// RdefCbufferFlags.
```

## Source note 139, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L390)

```text
// D3D12_SHADER_INPUT_BIND_DESC with some differences.
```

## Source note 140, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L391)

```text
// Placed in samplers, SRVs, UAVs, CBVs order, sorted by ID.
```

## Source note 141, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L397)

```text
// 0 for multisampled textures (the sample count is specified in the SRV
```

## Source note 142, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L398)

```text
// descriptor), constant buffers, ByteAddressBuffers and samplers.
```

## Source note 143, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L399)

```text
// UINT32_MAX for single-sampled textures and typed buffers.
```

## Source note 144, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L402)

```text
// 0 for unbounded.
```

## Source note 145, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L404)

```text
// RdefInputFlags.
```

## Source note 146, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L406)

```text
// Bind point space and ID added in shader model 5_1.
```

## Source note 147, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L414)

```text
// RD11 in Shader Model 5_0 shaders.
```

## Source note 148, line 416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L416)

```text
// RD11 with reversed nibbles in Shader Model 5_0 shaders.
```

## Source note 149, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L424)

```text
// CompileFlags.
```

## Source note 150, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L434)

```text
// Zero.
```

## Source note 151, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L447)

```text
// D3D_NAME subset
```

## Source note 152, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L462)

```text
// D3D_REGISTER_COMPONENT_TYPE
```

## Source note 153, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L470)

```text
// D3D_MIN_PRECISION
```

## Source note 154, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L481)

```text
// D3D10_INTERNALSHADER_PARAMETER
```

## Source note 155, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L485)

```text
// kUndefined for pixel shader outputs - inferred from the component type and
```

## Source note 156, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L486)

```text
// what is used in the shader.
```

## Source note 157, line 489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L489)

```text
// o#/v# when there's linkage, SV_Target index or UINT32_MAX in pixel shader
```

## Source note 158, line 490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L490)

```text
// output.
```

## Source note 159, line 494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L494)

```text
// For an output signature.
```

## Source note 160, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L496)

```text
// For an input signature.
```

## Source note 161, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L502)

```text
// D3D11_INTERNALSHADER_PARAMETER_FOR_GS
```

## Source note 162, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L503)

```text
// Extends SignatureParameter, see it for more information.
```

## Source note 163, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L505)

```text
// Stream index (parameters must appear in non-decreasing stream order).
```

## Source note 164, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L520)

```text
// D3D11_INTERNALSHADER_PARAMETER_11_1
```

## Source note 165, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L521)

```text
// Extends SignatureParameterForGS, see it for more information.
```

## Source note 166, line 538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L538)

```text
// D3D10_INTERNALSHADER_SIGNATURE
```

## Source note 167, line 541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L541)

```text
// If the signature is empty, this still points after the header.
```

## Source note 168, line 547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L547)

```text
// Low 32 bits.
```

## Source note 169, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L566)

```text
// UINT64 originally, but aligned to 4 rather than 8.
```

## Source note 170, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L571)

```text
// D3D11_SB_TESSELLATOR_DOMAIN
```

## Source note 171, line 579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L579)

```text
// D3D10_SB_PRIMITIVE_TOPOLOGY
```

## Source note 172, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L593)

```text
// D3D10_SB_PRIMITIVE
```

## Source note 173, line 635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L635)

```text
// The STAT blob (based on Wine d3dcompiler_parse_stat).
```

## Source note 174, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L637)

```text
// Not increased by declarations and labels.
```

## Source note 175, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L638)

```text
// +0
```

## Source note 176, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L639)

```text
// +4
```

## Source note 177, line 640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L640)

```text
// Unknown in Wine.
```

## Source note 178, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L641)

```text
// +8
```

## Source note 179, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L642)

```text
// Only inputs and outputs, not CBVs, SRVs, UAVs and samplers.
```

## Source note 180, line 643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L643)

```text
// +C
```

## Source note 181, line 644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L644)

```text
// +10
```

## Source note 182, line 645

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L645)

```text
// +14
```

## Source note 183, line 646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L646)

```text
// +18
```

## Source note 184, line 647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L647)

```text
// endif, ret.
```

## Source note 185, line 648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L648)

```text
// +1C
```

## Source note 186, line 649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L649)

```text
// if (but not else).
```

## Source note 187, line 650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L650)

```text
// +20
```

## Source note 188, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L651)

```text
// Unknown in Wine.
```

## Source note 189, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L652)

```text
// +24
```

## Source note 190, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L653)

```text
// +28
```

## Source note 191, line 654

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L654)

```text
// +2C
```

## Source note 192, line 655

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L655)

```text
// +30
```

## Source note 193, line 656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L656)

```text
// +34
```

## Source note 194, line 657

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L657)

```text
// +38
```

## Source note 195, line 658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L658)

```text
// +3C
```

## Source note 196, line 659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L659)

```text
// +40
```

## Source note 197, line 660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L660)

```text
// +44
```

## Source note 198, line 661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L661)

```text
// +48
```

## Source note 199, line 662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L662)

```text
// Not including indexable temp load/store.
```

## Source note 200, line 663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L663)

```text
// +4C
```

## Source note 201, line 664

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L664)

```text
// Unknown in Wine.
```

## Source note 202, line 665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L665)

```text
// +50
```

## Source note 203, line 666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L666)

```text
// +54
```

## Source note 204, line 667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L667)

```text
// Unknown in Wine.
```

## Source note 205, line 668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L668)

```text
// +58
```

## Source note 206, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L669)

```text
// +5C
```

## Source note 207, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L670)

```text
// +60
```

## Source note 208, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L671)

```text
// +64
```

## Source note 209, line 672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L672)

```text
// +68
```

## Source note 210, line 673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L673)

```text
// Unknown in Wine, but confirmed by testing.
```

## Source note 211, line 674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L674)

```text
// +6C
```

## Source note 212, line 675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L675)

```text
// +70
```

## Source note 213, line 676

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L676)

```text
// +74
```

## Source note 214, line 677

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L677)

```text
// +78
```

## Source note 215, line 678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L678)

```text
// +7C
```

## Source note 216, line 679

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L679)

```text
// +80
```

## Source note 217, line 680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L680)

```text
// +84
```

## Source note 218, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L681)

```text
// Unknown in Wine.
```

## Source note 219, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L682)

```text
// +88
```

## Source note 220, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L683)

```text
// Unknown in Wine.
```

## Source note 221, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L684)

```text
// +8C
```

## Source note 222, line 685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L685)

```text
// Unknown in Wine, but confirmed by testing.
```

## Source note 223, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L686)

```text
// +90
```

## Source note 224, line 690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L690)

```text
// A shader blob begins with a version token and the shader length in dwords
```

## Source note 225, line 691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L691)

```text
// (including the version token and the length token itself).
```

## Source note 226, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L693)

```text
// D3D10_SB_TOKENIZED_PROGRAM_TYPE
```

## Source note 227, line 708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L708)

```text
// D3D10_SB_CUSTOMDATA_CLASS
```

## Source note 228, line 718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L718)

```text
// D3D10_SB_OPERAND_TYPE subset
```

## Source note 229, line 723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L723)

```text
// Only usable as destination or source (but not both) in mov (and it
```

## Source note 230, line 724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L724)

```text
// becomes an array instruction this way).
```

## Source note 231, line 747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L747)

```text
// D3D10_SB_OPERAND_NUM_COMPONENTS
```

## Source note 232, line 749

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L749)

```text
// D3D10_SB_OPERAND_0_COMPONENT
```

## Source note 233, line 750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L750)

```text
// D3D10_SB_OPERAND_1_COMPONENT
```

## Source note 234, line 751

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L751)

```text
// D3D10_SB_OPERAND_4_COMPONENT
```

## Source note 235, line 775

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L775)

```text
// D3D10_SB_OPERAND_4_COMPONENT_SELECTION_MODE
```

## Source note 236, line 783

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L783)

```text
// D3D10_SB_OPERAND_INDEX_REPRESENTATION
```

## Source note 237, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L793)

```text
// UINT32_MAX if absolute. Lower 2 bits are the component index, upper bits
```

## Source note 238, line 794

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L794)

```text
// are the temp register index. Applicable to indexable temps, inputs,
```

## Source note 239, line 795

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L795)

```text
// outputs except for pixel shaders, constant buffers and bindings.
```

## Source note 240, line 798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L798)

```text
// Implicit constructor.
```

## Source note 241, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L815)

```text
// Encode selecting one component from absolute-indexed r#.
```

## Source note 242, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L884)

```text
// D3D10_SB_EXTENDED_OPERAND_TYPE
```

## Source note 243, line 890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L890)

```text
// D3D10_SB_OPERAND_MODIFIER
```

## Source note 244, line 899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L899)

```text
// Ignored for 0-component and 1-component operand types.
```

## Source note 245, line 900

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L900)

```text
// For 4-component operand types, if the write mask is 0, it's treated as
```

## Source note 246, line 901

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L901)

```text
// 0-component.
```

## Source note 247, line 904

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L904)

```text
// Input destinations (v*) are for use only in declarations. Vector input
```

## Source note 248, line 905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L905)

```text
// declarations use read masks instead of swizzle (resource declarations still
```

## Source note 249, line 906

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L906)

```text
// use swizzle when they're vector, however).
```

## Source note 250, line 1023

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1023)

```text
// Ignored for 0-component and 1-component operand types.
```

## Source note 251, line 1027

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1027)

```text
// Only valid for OperandType::kImmediate32.
```

## Source note 252, line 1038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1038)

```text
// For creating instances for use in declarations.
```

## Source note 253, line 1218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1218)

```text
// Clear swizzle of unused components to a used value to avoid
```

## Source note 254, line 1219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1219)

```text
// referencing potentially uninitialized register components.
```

## Source note 255, line 1256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1256)

```text
// D3D10_SB_GLOBAL_FLAGS_MASK
```

## Source note 256, line 1258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1258)

```text
// Permit the driver to reorder arithmetic operations for optimization.
```

## Source note 257, line 1262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1262)

```text
// Enable RAW and structured buffers in non-CS 4.x shaders. Not needed on 5.x.
```

## Source note 258, line 1264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1264)

```text
// Direct3D 11.1.
```

## Source note 259, line 1265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1265)

```text
// Skip optimizations of shader IL when translating to native code.
```

## Source note 260, line 1268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1268)

```text
// Enable 11.1 double-precision floating-point instruction extensions. Not
```

## Source note 261, line 1269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1269)

```text
// needed on 5.1.
```

## Source note 262, line 1271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1271)

```text
// Enable 11.1 non-double instruction extensions. Not needed on 5.1.
```

## Source note 263, line 1273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1273)

```text
// Direct3D 12.
```

## Source note 264, line 1277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1277)

```text
// D3D10_SB_SAMPLER_MODE
```

## Source note 265, line 1284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1284)

```text
// D3D10_SB_CONSTANT_BUFFER_ACCESS_PATTERN
```

## Source note 266, line 1290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1290)

```text
// D3D10_SB_INTERPOLATION_MODE
```

## Source note 267, line 1302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1302)

```text
// D3D10_SB_RESOURCE_DIMENSION
```

## Source note 268, line 1319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1319)

```text
// D3D11_SB_RESOURCE_FLAGS_MASK
```

## Source note 269, line 1326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1326)

```text
// D3D10_SB_OPCODE_TYPE subset
```

## Source note 270, line 1454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1454)

```text
// D3D10_SB_EXTENDED_OPCODE_TYPE
```

## Source note 271, line 1486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1486)

```text
// Even if a texture or a typed buffer has less than 4 components, it has the
```

## Source note 272, line 1487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1487)

```text
// same return type specified for all 4 in its dcl instruction.
```

## Source note 273, line 1492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1492)

```text
// Assembler appending to the shader program code vector.
```

## Source note 274, line 1654

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1654)

```text
// The label is source, not destination, for simplicity, to unify it will
```

## Source note 275, line 1655

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1655)

```text
// call/callc (in DXBC it's just a zero-component label operand).
```

## Source note 276, line 1660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1660)

```text
// Doesn't count towards stat_.instruction_count.
```

## Source note 277, line 1730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1730)

```text
// Returns a pointer for writing the custom data to.
```

## Source note 278, line 1737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1737)

```text
// Different opcode encoding (no size).
```

## Source note 279, line 1740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1740)

```text
// Don't leave uninitialized data, and make sure multiple uses of the
```

## Source note 280, line 1741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1741)

```text
// assembler with the same input give the same DXBC for driver shader
```

## Source note 281, line 1742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1742)

```text
// caching.
```

## Source note 282, line 1834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1834)

```text
// If the address is 1-component, the derivatives are 1-component, if the
```

## Source note 283, line 1835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1835)

```text
// address is 4-component, the derivatives are 4-component.
```

## Source note 284, line 1926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1926)

```text
// The order of constant buffer declarations in a shader indicates their
```

## Source note 285, line 1927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1927)

```text
// relative priority from highest to lowest (hint to driver).
```

## Source note 286, line 1948

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1948)

```text
// In geometry shaders, only kPointList, kLineStrip and kTriangleStrip are
```

## Source note 287, line 1949

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1949)

```text
// allowed.
```

## Source note 288, line 1954

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1954)

```text
// In geometry shaders, only kPoint, kLine, kTriangle, kLineWithAdjacency and
```

## Source note 289, line 1955

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1955)

```text
// kTriangleWithAdjacency are allowed.
```

## Source note 290, line 1960

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L1960)

```text
// Returns the index of the count written in the code_ vector.
```

## Source note 291, line 2002

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2002)

```text
// Constant interpolation mode is set in FXC output at least for
```

## Source note 292, line 2003

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2003)

```text
// SV_IsFrontFace, despite the comment in d3d12TokenizedProgramFormat.hpp
```

## Source note 293, line 2004

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2004)

```text
// saying bits 11:23 are ignored.
```

## Source note 294, line 2035

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2035)

```text
// Returns the index of the count written in the code_ vector.
```

## Source note 295, line 2051

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2051)

```text
// flags are GlobalFlags.
```

## Source note 296, line 2086

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2086)

```text
// Don't use emit_then_cut_stream - crashes AMD Software: Adrenalin Edition
```

## Source note 297, line 2087

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2087)

```text
// 23.3.2 shader compiler on RDNA 3 if used conditionally.
```

## Source note 298, line 2176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2176)

```text
// Possible flags are kUAVFlagGloballyCoherentAccess and
```

## Source note 299, line 2177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2177)

```text
// kUAVFlagRasterizerOrderedAccess.
```

## Source note 300, line 2189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2189)

```text
// Possible flags are kUAVFlagGloballyCoherentAccess and
```

## Source note 301, line 2190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2190)

```text
// kUAVFlagRasterizerOrderedAccess.
```

## Source note 302, line 2222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2222)

```text
// Typed UAV writes don't support write masking.
```

## Source note 303, line 2236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2236)

```text
// For Load, FXC emits code for writing to any component of the destination,
```

## Source note 304, line 2237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2237)

```text
// with xxxx swizzle of the source SRV/UAV.
```

## Source note 305, line 2238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2238)

```text
// For Load2/Load3/Load4, it's xy/xyz/xyzw write mask and xyxx/xyzx/xyzw
```

## Source note 306, line 2239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2239)

```text
// swizzle.
```

## Source note 307, line 2399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/format/dxbc.h#L2399)

```text
// Atomic operations require a 0-component memory destination.
```
