# Registers: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/registers.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L20)

```text
// Most 3D registers are the same as in the Qualcomm Adreno 200 (AMD Z430,
```

## Source note 2, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L21)

```text
// another R400 architecture family chip):
```

## Source note 3, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L23)

```text
// https://github.com/UDOOboard/Kernel_Unico/blob/master/drivers/mxc/amd-gpu/include/reg/yamato/10/yamato_registers.h
```

## Source note 4, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L24)

```text
// https://github.com/freedreno/amd-gpu/blob/master/include/reg/yamato/10/yamato_registers.h
```

## Source note 5, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L26)

```text
// https://gitlab.freedesktop.org/mesa/mesa/-/blob/main/src/freedreno/registers/adreno/a2xx.xml
```

## Source note 6, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L28)

```text
// The Adreno 200, however, has various differences in its registers (primarily
```

## Source note 7, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L29)

```text
// in the render backend, but not limited to that). Before adding the
```

## Source note 8, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L30)

```text
// definitions from the Adreno 200, see the actual values of those registers set
```

## Source note 9, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L31)

```text
// by games, and/or test them on the Xenos hardware.
```

## Source note 10, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L33)

```text
// Other useful sources are the register references for later ATI/AMD 3D chips,
```

## Source note 11, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L34)

```text
// most importantly the R600 - while it has a massive amount of differences,
```

## Source note 12, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L35)

```text
// it's the closest relative of the R400 architecture that is available on the
```

## Source note 13, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L36)

```text
// PC. Documentation for newer AMD GPUs, such as Evergreen, Northern Islands,
```

## Source note 14, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L37)

```text
// and even GCN also can provide details in some cases. The earlier ATI's
```

## Source note 15, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L38)

```text
// architecture, R3xx/R5xx, has very differently structured registers (although
```

## Source note 16, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L39)

```text
// some are still very similar), but can provide some historical context.
```

## Source note 17, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L41)

```text
// Display controller register addresses mostly match the M56 ones:
```

## Source note 18, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L42)

```text
// https://www.x.org/docs/AMD/old/RRG-216M56-03oOEM.pdf
```

## Source note 19, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L44)

```text
// All unused bits are intentionally declared as named fields for stable
```

## Source note 20, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L45)

```text
// comparisons when register values are constructed or modified by Xenia itself.
```

## Source note 21, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L47)

```text
// Only 32-bit types (uint32_t, int32_t, float or enums with uint32_t / int32_t
```

## Source note 22, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L48)

```text
// as the underlying type) are allowed in the bit fields here, as Visual C++
```

## Source note 23, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L49)

```text
// restarts packing when a field requires different alignment than the previous
```

## Source note 24, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L50)

```text
// one.
```

## Source note 25, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L73)

```text
// +0
```

## Source note 26, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L74)

```text
// +8
```

## Source note 27, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L75)

```text
// +9
```

## Source note 28, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L76)

```text
// +10
```

## Source note 29, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L77)

```text
// +11
```

## Source note 30, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L78)

```text
// +12
```

## Source note 31, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L79)

```text
// +13
```

## Source note 32, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L80)

```text
// +14
```

## Source note 33, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L81)

```text
// +15
```

## Source note 34, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L82)

```text
// +16
```

## Source note 35, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L83)

```text
// +17
```

## Source note 36, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L84)

```text
// +24
```

## Source note 37, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L85)

```text
// +25
```

## Source note 38, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L86)

```text
// +26
```

## Source note 39, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L87)

```text
// +27
```

## Source note 40, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L88)

```text
// +31
```

## Source note 41, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L97)

```text
// +0
```

## Source note 42, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L98)

```text
// +1
```

## Source note 43, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L99)

```text
// +2
```

## Source note 44, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L100)

```text
// +3
```

## Source note 45, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L101)

```text
// +4
```

## Source note 46, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L102)

```text
// +5
```

## Source note 47, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L103)

```text
// +6
```

## Source note 48, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L104)

```text
// +7
```

## Source note 49, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L105)

```text
// +10
```

## Source note 50, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L106)

```text
// +11
```

## Source note 51, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L107)

```text
// +14
```

## Source note 52, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L108)

```text
// +15
```

## Source note 53, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L109)

```text
// +16
```

## Source note 54, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L110)

```text
// +17
```

## Source note 55, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L111)

```text
// +18
```

## Source note 56, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L112)

```text
// +20
```

## Source note 57, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L113)

```text
// +24
```

## Source note 58, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L130)

```text
// GPR counts minus 1.
```

## Source note 59, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L131)

```text
// Ignore the Freedreno a2xx.xml note about the bit 7 for zero registers,
```

## Source note 60, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L132)

```text
// the fields are 6-bit, not 8-bit, in yamato_registers.h, and games never
```

## Source note 61, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L133)

```text
// set the bits 7:6.
```

## Source note 62, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L134)

```text
// +0, value minus 1
```

## Source note 63, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L135)

```text
// +6
```

## Source note 64, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L136)

```text
// +8, value minus 1
```

## Source note 65, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L137)

```text
// +14
```

## Source note 66, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L138)

```text
// +16
```

## Source note 67, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L139)

```text
// +17
```

## Source note 68, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L140)

```text
// +18
```

## Source note 69, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L141)

```text
// +19
```

## Source note 70, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L142)

```text
// Interpolator output count minus 1.
```

## Source note 71, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L143)

```text
// +20, value minus 1
```

## Source note 72, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L144)

```text
// +24
```

## Source note 73, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L145)

```text
// +27
```

## Source note 74, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L146)

```text
// +31
```

## Source note 75, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L155)

```text
// +0
```

## Source note 76, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L156)

```text
// +1
```

## Source note 77, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L157)

```text
// +2
```

## Source note 78, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L158)

```text
// +4
```

## Source note 79, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L159)

```text
// Pixel shader interpolator (according to the XNA microcode validator -
```

## Source note 80, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L160)

```text
// limited to the interpolator count, 16, not the total register count of
```

## Source note 81, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L161)

```text
// 64) index to write pixel parameters to.
```

## Source note 82, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L162)

```text
// See https://portal.unifiedpatents.com/ptab/case/IPR2015-00325 Exhibit
```

## Source note 83, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L163)

```text
// 2039 R400 Sequencer Specification 2.11 (a significantly early version of
```

## Source note 84, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L164)

```text
// the specification, however) section 19.2 "Sprites/ XY screen coordinates/
```

## Source note 85, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L165)

```text
// FB information" for additional details.
```

## Source note 86, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L166)

```text
// * |XY| - position on screen (vPos - the XNA assembler translates ps_3_0
```

## Source note 87, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L167)

```text
//   vPos directly to this, so at least in Direct3D 9 pixel center mode,
```

## Source note 88, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L168)

```text
//   this contains 0, 1, 2, not 0.5, 1.5, 2.5). flto also said in the
```

## Source note 89, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L169)

```text
//   Freedreno IRC that it's .0 even in OpenGL:
```

## Source note 90, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L170)

```text
//   https://dri.freedesktop.org/~cbrill/dri-log/?channel=freedreno&date=2020-04-19
```

## Source note 91, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L171)

```text
//   According to the actual usage, in the final version of the hardware,
```

## Source note 92, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L172)

```text
//   the screen coordinates are passed to the shader directly as floats
```

## Source note 93, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L173)

```text
//   (contrary to what's written in the early 2.11 version of the sequencer
```

## Source note 94, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L174)

```text
//   specification from IPR2015-00325, where the coordinates are specified
```

## Source note 95, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L175)

```text
//   to be 2^23-biased, essentially packed as integers in the low mantissa
```

## Source note 96, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L176)

```text
//   bits of 2^23).
```

## Source note 97, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L177)

```text
//   * On Android, according to LG P705 - checked on the driver V@6.0 AU@
```

## Source note 98, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L178)

```text
//     (CL@3050818) - GL_OES_get_program_binary disassembly, gl_FragCoord.xy
```

## Source note 99, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L179)

```text
//     is |r0.xy| * c221.xy + c222.zw. Though we haven't yet been able to
```

## Source note 100, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L180)

```text
//     dump the actual constant values by exploiting a huge uniform array,
```

## Source note 101, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L181)

```text
//     but flto says c222.zw contains tile offset plus 0.5. It also appears
```

## Source note 102, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L182)

```text
//     that the multiplication by c221.xy is done to flip the direction of
```

## Source note 103, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L183)

```text
//     the Y axis in gl_FragCoord (c221.y is probably -1). According to the
```

## Source note 104, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L184)

```text
//     tests performed with triangles and point sprites, the hardware uses
```

## Source note 105, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L185)

```text
//     the top-left rasterization rule just like Direct3D (tie-breaking
```

## Source note 106, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L186)

```text
//     sample coverage towards gl_FragCoord.-x+y, while Direct3D tie-breaks
```

## Source note 107, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L187)

```text
//     towards VPOS.-x-y), and the R400 / Z430 doesn't seem to have the
```

## Source note 108, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L188)

```text
//     equivalent of R5xx's SC_EDGERULE register for configuring this).
```

## Source note 109, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L189)

```text
//     Also, both OpenGL and apparently Direct3D 9 define the point sprite V
```

## Source note 110, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L190)

```text
//     coordinate to be 0 in the top, and 1 in the bottom (but OpenGL
```

## Source note 111, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L191)

```text
//     gl_FragCoord.y is towards the top, while Direct3D 9's VPOS.y is
```

## Source note 112, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L192)

```text
//     towards the bottom), gl_PointCoord.y is |PsParamGen.w| directly, and
```

## Source note 113, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L193)

```text
//     the R400 / Z430 doesn't appear to have an equivalent of R6xx's
```

## Source note 114, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L194)

```text
//     SPI_INTERP_CONTROL_0::PNT_SPRITE_TOP_1 for toggling the direction.
```

## Source note 115, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L195)

```text
//     So, it looks like the internal screen coordinates in the official
```

## Source note 116, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L196)

```text
//     OpenGL ES 2.0 driver are still top-to-bottom like in Direct3D, but
```

## Source note 117, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L197)

```text
//     gl_FragCoord.y is flipped in the shader code so it's bottom-to-top
```

## Source note 118, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L198)

```text
//     as OpenGL specifies.
```

## Source note 119, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L199)

```text
//     https://docs.microsoft.com/en-us/windows/win32/direct3d9/point-sprites
```

## Source note 120, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L200)

```text
// * |ZW| - UV within a point sprite, [0, 1]. In OpenGL ES 2.0, this is
```

## Source note 121, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L201)

```text
//   interpreted directly as gl_PointCoord, with the directions matching the
```

## Source note 122, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L202)

```text
//   OpenGL ES 2.0 specification - 0 in the top (towards +gl_FragCoord.y in
```

## Source note 123, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L203)

```text
//   OpenGL ES bottom-to-top screen coordinates - but towards -PsParamGen.y
```

## Source note 124, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L204)

```text
//   likely, see the explanation of gl_FragCoord.xy above), 1 in the bottom
```

## Source note 125, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L205)

```text
//   (towards -gl_FragCoord.y, or +PsParamGen.y likely). The point sprite
```

## Source note 126, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L206)

```text
//   coordinates are exposed differently on the Xbox 360 and the PC
```

## Source note 127, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L207)

```text
//   Direct3D 9 - the Xbox 360 passes the whole PsParamGen register via the
```

## Source note 128, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L208)

```text
//   SPRITETEXCOORD input semantic directly (unlike on the PC, where point
```

## Source note 129, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L209)

```text
//   sprite coordinates are written to XY of TEXCOORD0), and shaders should
```

## Source note 130, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L210)

```text
//   take abs(SPRITETEXCOORD.zw) explicitly.
```

## Source note 131, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L211)

```text
//   https://shawnhargreaves.com/blog/point-sprites-on-xbox.html
```

## Source note 132, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L212)

```text
//   4D5307F1 has snowflake point sprites with an asymmetric texture.
```

## Source note 133, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L213)

```text
//   * For non-point primitives, according to LG P705, this may be the IJ
```

## Source note 134, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L214)

```text
//     barycentric coordinates, however, it's not yet known how intentional,
```

## Source note 135, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L215)

```text
//     well-defined and reliable this behavior is, and whether any game uses
```

## Source note 136, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L216)

```text
//     it on purpose. Also, the mapping between the vertex indices and the
```

## Source note 137, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L217)

```text
//     order of these coordinates seems to vary possibly depending on the
```

## Source note 138, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L218)

```text
//     positions of the vertices relative to each other even when the
```

## Source note 139, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L219)

```text
//     winding order stays the same. It's also unknown what effect the
```

## Source note 140, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L220)

```text
//     provoking vertex convention has on the order.
```

## Source note 141, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L222)

```text
// +8
```

## Source note 142, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L223)

```text
// +16
```

## Source note 143, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L224)

```text
// +17
```

## Source note 144, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L225)

```text
// +18
```

## Source note 145, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L226)

```text
// +19
```

## Source note 146, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L235)

```text
// +0
```

## Source note 147, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L236)

```text
// SampleLocation bits - 0 for centroid, 1 for center, if
```

## Source note 148, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L237)

```text
// SQ_CONTEXT_MISC::sc_sample_cntl is kCentroidsAndCenters.
```

## Source note 149, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L238)

```text
// +16
```

## Source note 150, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L247)

```text
// +0
```

## Source note 151, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L248)

```text
// +9
```

## Source note 152, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L249)

```text
// Vec4 count minus one.
```

## Source note 153, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L250)

```text
// +12, value minus 1
```

## Source note 154, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L251)

```text
// +21
```

## Source note 155, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L257)

```text
// Same as SQ_VS_CONST.
```

## Source note 156, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L261)

```text
// +0
```

## Source note 157, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L262)

```text
// +9
```

## Source note 158, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L263)

```text
// Vec4 count minus one.
```

## Source note 159, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L264)

```text
// +12, value minus 1
```

## Source note 160, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L265)

```text
// +21
```

## Source note 161, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L271)

```text
/*******************************************************************************
 __   _____ ___ _____ _____  __
 \ \ / / __| _ \_   _| __\ \/ /
  \ V /| _||   / | | | _| >  <
   \_/ |___|_|_\ |_| |___/_/\_\

   ___ ___  ___  _   _ ___ ___ ___     _   _  _ ___
  / __| _ \/ _ \| | | | _ \ __| _ \   /_\ | \| |   \
 | (_ |   / (_) | |_| |  _/ _||   /  / _ \| .` | |) |
  \___|_|_\\___/ \___/|_| |___|_|_\ /_/ \_\_|\_|___/

  _____ ___ ___ ___ ___ _    _      _ _____ ___  ___
 |_   _| __/ __/ __| __| |  | |    /_\_   _/ _ \| _ \
   | | | _|\__ \__ \ _|| |__| |__ / _ \| || (_) |   /
   |_| |___|___/___/___|____|____/_/ \_\_| \___/|_|_\

*******************************************************************************/
```

## Source note 162, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L292)

```text
// +0
```

## Source note 163, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L293)

```text
// +24
```

## Source note 164, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L294)

```text
// +30
```

## Source note 165, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L301)

```text
// Has differences from the Adreno 200.
```

## Source note 166, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L303)

```text
// +0
```

## Source note 167, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L304)

```text
// +6
```

## Source note 168, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L305)

```text
// Adreno 200 replaced this with FACENESS_CULL_SELECT possibly due to the
```

## Source note 169, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L306)

```text
// removal of tessellation, but on the Xenos this is MAJOR_MODE like on the
```

## Source note 170, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L307)

```text
// R600, it's set to the explicit mode mainly for tessellated draws in games
```

## Source note 171, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L308)

```text
// (because VGT_OUTPUT_PATH_CNTL where tessellation is enabled is ignored in
```

## Source note 172, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L309)

```text
// the implicit major mode).
```

## Source note 173, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L310)

```text
// +8
```

## Source note 174, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L311)

```text
// +10
```

## Source note 175, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L312)

```text
// +11
```

## Source note 176, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L313)

```text
// +12
```

## Source note 177, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L314)

```text
// +13
```

## Source note 178, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L315)

```text
// +16
```

## Source note 179, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L321)

```text
// Unlike on R6xx (but closer to R5xx), and according to the Adreno 200 header,
```

## Source note 180, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L322)

```text
// the registers related to the vertex index are 24-bit. Vertex indices are
```

## Source note 181, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L323)

```text
// unsigned, and only the lower 24 bits of them are actually used by the GPU -
```

## Source note 182, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L324)

```text
// this has been verified on an Adreno 200 phone (LG Optimus L7) on OpenGL ES
```

## Source note 183, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L325)

```text
// using a GL_UNSIGNED_INT element array buffer with junk in the upper 8 bits
```

## Source note 184, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L326)

```text
// that had no effect on drawing.
```

## Source note 185, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L328)

```text
// The order of operations is primitive reset index checking -> offsetting ->
```

## Source note 186, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L329)

```text
// clamping.
```

## Source note 187, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L334)

```text
// The upper 8 bits of the value from the index buffer are confirmed to be
```

## Source note 188, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L335)

```text
// ignored. So, though this specifically is untested (because
```

## Source note 189, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L336)

```text
// GL_PRIMITIVE_RESTART_FIXED_INDEX was added only in OpenGL ES 3.0, though
```

## Source note 190, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L337)

```text
// it behaves conceptually close to our expectations anyway - uses the
```

## Source note 191, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L338)

```text
// 0xFFFFFFFF restart index while GL_MAX_ELEMENT_INDEX may be 0xFFFFFF),
```

## Source note 192, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L339)

```text
// the restart index check likely only involves the lower 24 bit of the
```

## Source note 193, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L340)

```text
// vertex index - therefore, if reset_indx is 0xFFFFFF, likely 0xFFFFFF,
```

## Source note 194, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L341)

```text
// 0x1FFFFFF, 0xFFFFFFFF all cause primitive reset.
```

## Source note 195, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L342)

```text
// +0
```

## Source note 196, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L343)

```text
// +24
```

## Source note 197, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L352)

```text
// Unlike R5xx's VAP_INDEX_OFFSET, which is signed 25-bit, this is 24-bit -
```

## Source note 198, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L353)

```text
// and signedness doesn't matter as index calculations are done in 24-bit
```

## Source note 199, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L354)

```text
// integers, and ((0xFFFFFE + 3) & 0xFFFFFF) == 1 anyway, just like
```

## Source note 200, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L355)

```text
// ((0xFFFFFFFE + 3) & 0xFFFFFF) == 1 if we treated it as signed by
```

## Source note 201, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L356)

```text
// sign-extending on the host. Direct3D 9 just writes BaseVertexIndex as a
```

## Source note 202, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L357)

```text
// signed int32 to the entire register, but the upper 8 bits are ignored
```

## Source note 203, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L358)

```text
// anyway, and that has no effect on offsets that fit in 24 bits.
```

## Source note 204, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L359)

```text
// +0
```

## Source note 205, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L360)

```text
// +24
```

## Source note 206, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L369)

```text
// +0
```

## Source note 207, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L370)

```text
// +24
```

## Source note 208, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L379)

```text
// Usually 0xFFFF or 0xFFFFFF.
```

## Source note 209, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L380)

```text
// +0
```

## Source note 210, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L381)

```text
// +24
```

## Source note 211, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L390)

```text
// +0
```

## Source note 212, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L391)

```text
// +2
```

## Source note 213, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L400)

```text
// +0
```

## Source note 214, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L401)

```text
// +2
```

## Source note 215, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L407)

```text
/*******************************************************************************
  ___ ___ ___ __  __ ___ _____ _____   _____
 | _ \ _ \_ _|  \/  |_ _|_   _|_ _\ \ / / __|
 |  _/   /| || |\/| || |  | |  | | \ V /| _|
 |_| |_|_\___|_|  |_|___| |_| |___| \_/ |___|

    _   ___ ___ ___ __  __ ___ _    ___ ___
   /_\ / __/ __| __|  \/  | _ ) |  | __| _ \
  / _ \\__ \__ \ _|| |\/| | _ \ |__| _||   /
 /_/ \_\___/___/___|_|  |_|___/____|___|_|_\

*******************************************************************************/
```

## Source note 216, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L423)

```text
// For per-vertex size specification, radius (1/2 size), 12.4 fixed point.
```

## Source note 217, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L424)

```text
// +0
```

## Source note 218, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L425)

```text
// +16
```

## Source note 219, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L434)

```text
// 1/2 width or height, 12.4 fixed point.
```

## Source note 220, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L435)

```text
// +0
```

## Source note 221, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L436)

```text
// +16
```

## Source note 222, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L442)

```text
// Setup Unit / Scanline Converter mode cntl
```

## Source note 223, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L446)

```text
// +0
```

## Source note 224, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L447)

```text
// +1
```

## Source note 225, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L448)

```text
// 0 - front is CCW, 1 - front is CW.
```

## Source note 226, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L449)

```text
// +2
```

## Source note 227, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L450)

```text
// 4541096E uses poly_mode 2 for triangles, which is "reserved" on R6xx and
```

## Source note 228, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L451)

```text
// not defined on Adreno 2xx, but polymode_front/back_ptype are 0 (points)
```

## Source note 229, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L452)

```text
// in this case in 4541096E, which should not be respected for non-kDualMode
```

## Source note 230, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L453)

```text
// as the title wants to draw filled triangles.
```

## Source note 231, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L454)

```text
// +3
```

## Source note 232, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L455)

```text
// +5
```

## Source note 233, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L456)

```text
// +8
```

## Source note 234, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L457)

```text
// +11
```

## Source note 235, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L458)

```text
// +12
```

## Source note 236, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L459)

```text
// +13
```

## Source note 237, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L460)

```text
// +14
```

## Source note 238, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L461)

```text
// +15
```

## Source note 239, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L462)

```text
// +16
```

## Source note 240, line 463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L463)

```text
// LINE_STIPPLE_ENABLE was added on Adreno.
```

## Source note 241, line 464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L464)

```text
// +17
```

## Source note 242, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L465)

```text
// +19
```

## Source note 243, line 466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L466)

```text
// +20
```

## Source note 244, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L467)

```text
// +21
```

## Source note 245, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L468)

```text
// +22
```

## Source note 246, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L469)

```text
// +23
```

## Source note 247, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L470)

```text
// +24
```

## Source note 248, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L471)

```text
// WAIT_RB_IDLE_ALL_TRI and WAIT_RB_IDLE_FIRST_TRI_NEW_STATE were added on
```

## Source note 249, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L472)

```text
// Adreno.
```

## Source note 250, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L473)

```text
// +25
```

## Source note 251, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L479)

```text
// Setup Unit Vertex Control
```

## Source note 252, line 483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L483)

```text
// +0
```

## Source note 253, line 484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L484)

```text
// +1
```

## Source note 254, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L485)

```text
// +3
```

## Source note 255, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L486)

```text
// +6
```

## Source note 256, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L495)

```text
// +0
```

## Source note 257, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L496)

```text
// +20
```

## Source note 258, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L497)

```text
// +31
```

## Source note 259, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L503)

```text
// Scanline converter viz query, used by D3D for gpu side conditional rendering
```

## Source note 260, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L507)

```text
// the visibility of draws should be evaluated
```

## Source note 261, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L508)

```text
// +0
```

## Source note 262, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L509)

```text
// +1
```

## Source note 263, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L510)

```text
// discard geometry after test (but use for testing)
```

## Source note 264, line 511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L511)

```text
// +7
```

## Source note 265, line 512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L512)

```text
// not used with d3d
```

## Source note 266, line 513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L513)

```text
// +8
```

## Source note 267, line 514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L514)

```text
// +9
```

## Source note 268, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L520)

```text
// Clipper clip control
```

## Source note 269, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L524)

```text
// Like on the Adreno 200, but with user clip planes from R3xx (used in
```

## Source note 270, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L525)

```text
// 4D5307E6 for the hanging lamp on Last Resort).
```

## Source note 271, line 526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L526)

```text
// +0
```

## Source note 272, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L527)

```text
// +1
```

## Source note 273, line 528

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L528)

```text
// +2
```

## Source note 274, line 529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L529)

```text
// +3
```

## Source note 275, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L530)

```text
// +4
```

## Source note 276, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L531)

```text
// +5
```

## Source note 277, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L532)

```text
// +6
```

## Source note 278, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L533)

```text
// +14
```

## Source note 279, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L534)

```text
// +16
```

## Source note 280, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L535)

```text
// +17
```

## Source note 281, line 536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L536)

```text
// +18
```

## Source note 282, line 537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L537)

```text
// +19
```

## Source note 283, line 538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L538)

```text
// +20
```

## Source note 284, line 539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L539)

```text
// +21
```

## Source note 285, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L540)

```text
// +22
```

## Source note 286, line 541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L541)

```text
// +23
```

## Source note 287, line 542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L542)

```text
// +24
```

## Source note 288, line 543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L543)

```text
// +25
```

## Source note 289, line 552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L552)

```text
// Viewport transform engine control
```

## Source note 290, line 556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L556)

```text
// +0
```

## Source note 291, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L557)

```text
// +1
```

## Source note 292, line 558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L558)

```text
// +2
```

## Source note 293, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L559)

```text
// +3
```

## Source note 294, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L560)

```text
// +4
```

## Source note 295, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L561)

```text
// +5
```

## Source note 296, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L562)

```text
// +6
```

## Source note 297, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L563)

```text
// +8
```

## Source note 298, line 564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L564)

```text
// +9
```

## Source note 299, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L565)

```text
// +10
```

## Source note 300, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L566)

```text
// +11
```

## Source note 301, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L567)

```text
// +12
```

## Source note 302, line 576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L576)

```text
// +0
```

## Source note 303, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L577)

```text
// +15
```

## Source note 304, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L578)

```text
// +16
```

## Source note 305, line 579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L579)

```text
// +31
```

## Source note 306, line 588

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L588)

```text
// +0
```

## Source note 307, line 589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L589)

```text
// +15
```

## Source note 308, line 590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L590)

```text
// +16
```

## Source note 309, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L591)

```text
// +31
```

## Source note 310, line 600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L600)

```text
// +0
```

## Source note 311, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L601)

```text
// +15
```

## Source note 312, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L602)

```text
// +16
```

## Source note 313, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L603)

```text
// +31
```

## Source note 314, line 612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L612)

```text
// +0
```

## Source note 315, line 613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L613)

```text
// +14
```

## Source note 316, line 614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L614)

```text
// +16
```

## Source note 317, line 615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L615)

```text
// +30
```

## Source note 318, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L616)

```text
// +31
```

## Source note 319, line 625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L625)

```text
// +0
```

## Source note 320, line 626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L626)

```text
// +14
```

## Source note 321, line 627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L627)

```text
// +16
```

## Source note 322, line 628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L628)

```text
// +30
```

## Source note 323, line 650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L650)

```text
// +0
```

## Source note 324, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L651)

```text
// +3
```

## Source note 325, line 660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L660)

```text
// +0 in pixels.
```

## Source note 326, line 661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L661)

```text
// +14
```

## Source note 327, line 662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L662)

```text
// +16
```

## Source note 328, line 663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L663)

```text
// +18
```

## Source note 329, line 672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L672)

```text
// +0
```

## Source note 330, line 673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L673)

```text
// +3
```

## Source note 331, line 674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L674)

```text
// +4
```

## Source note 332, line 675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L675)

```text
// Everything in between was added on Adreno.
```

## Source note 333, line 676

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L676)

```text
// +5
```

## Source note 334, line 678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L678)

```text
// +24
```

## Source note 335, line 679

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L679)

```text
// +26
```

## Source note 336, line 680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L680)

```text
// +28
```

## Source note 337, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L681)

```text
// +30
```

## Source note 338, line 690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L690)

```text
// The original R400 structure has 12-bit color_base, however the Xenos has
```

## Source note 339, line 691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L691)

```text
// periodic 11-bit EDRAM tile addressing, so this field was split in Xenia
```

## Source note 340, line 692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L692)

```text
// for convenience and to avoid mistakes.
```

## Source note 341, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L693)

```text
// +0 in tiles.
```

## Source note 342, line 694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L694)

```text
// +11
```

## Source note 343, line 695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L695)

```text
// +12
```

## Source note 344, line 696

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L696)

```text
// +16
```

## Source note 345, line 697

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L697)

```text
// +20
```

## Source note 346, line 698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L698)

```text
// +26
```

## Source note 347, line 701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L701)

```text
// RB_COLOR[1-3]_INFO also use this format.
```

## Source note 348, line 709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L709)

```text
// +0
```

## Source note 349, line 710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L710)

```text
// +1
```

## Source note 350, line 711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L711)

```text
// +2
```

## Source note 351, line 712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L712)

```text
// +3
```

## Source note 352, line 713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L713)

```text
// +4
```

## Source note 353, line 714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L714)

```text
// +5
```

## Source note 354, line 715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L715)

```text
// +6
```

## Source note 355, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L716)

```text
// +7
```

## Source note 356, line 717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L717)

```text
// +8
```

## Source note 357, line 718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L718)

```text
// +9
```

## Source note 358, line 719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L719)

```text
// +10
```

## Source note 359, line 720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L720)

```text
// +11
```

## Source note 360, line 721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L721)

```text
// +12
```

## Source note 361, line 722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L722)

```text
// +13
```

## Source note 362, line 723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L723)

```text
// +14
```

## Source note 363, line 724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L724)

```text
// +15
```

## Source note 364, line 725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L725)

```text
// +16
```

## Source note 365, line 734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L734)

```text
// +0
```

## Source note 366, line 735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L735)

```text
// +5
```

## Source note 367, line 736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L736)

```text
// +8
```

## Source note 368, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L737)

```text
// +13
```

## Source note 369, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L738)

```text
// +16
```

## Source note 370, line 739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L739)

```text
// +21
```

## Source note 371, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L740)

```text
// +24
```

## Source note 372, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L741)

```text
// BLEND_FORCE_ENABLE and BLEND_FORCE were added on Adreno.
```

## Source note 373, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L742)

```text
// +29
```

## Source note 374, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L744)

```text
// RB_BLENDCONTROL[0-3] use this format.
```

## Source note 375, line 753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L753)

```text
// +0
```

## Source note 376, line 754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L754)

```text
// +1
```

## Source note 377, line 755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L755)

```text
// +2
```

## Source note 378, line 756

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L756)

```text
// EARLY_Z_ENABLE was added on Adreno, never set by Xbox 360 games.
```

## Source note 379, line 757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L757)

```text
// +3
```

## Source note 380, line 758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L758)

```text
// +4
```

## Source note 381, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L759)

```text
// +7
```

## Source note 382, line 760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L760)

```text
// +8
```

## Source note 383, line 761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L761)

```text
// +11
```

## Source note 384, line 762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L762)

```text
// +14
```

## Source note 385, line 763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L763)

```text
// +17
```

## Source note 386, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L764)

```text
// +20
```

## Source note 387, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L765)

```text
// +23
```

## Source note 388, line 766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L766)

```text
// +26
```

## Source note 389, line 767

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L767)

```text
// +29
```

## Source note 390, line 776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L776)

```text
// +0
```

## Source note 391, line 777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L777)

```text
// +1
```

## Source note 392, line 778

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L778)

```text
// +2
```

## Source note 393, line 787

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L787)

```text
// +0
```

## Source note 394, line 788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L788)

```text
// +8
```

## Source note 395, line 789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L789)

```text
// +16
```

## Source note 396, line 790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L790)

```text
// +24
```

## Source note 397, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L793)

```text
// RB_STENCILREFMASK_BF also uses this format.
```

## Source note 398, line 800

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L800)

```text
// The original R400 structure has 12-bit depth_base, however the Xenos has
```

## Source note 399, line 801

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L801)

```text
// periodic 11-bit EDRAM tile addressing, so this field was split in Xenia
```

## Source note 400, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L802)

```text
// for convenience and to avoid mistakes.
```

## Source note 401, line 803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L803)

```text
// +0 in tiles.
```

## Source note 402, line 804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L804)

```text
// +11
```

## Source note 403, line 805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L805)

```text
// +12
```

## Source note 404, line 806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L806)

```text
// +16
```

## Source note 405, line 807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L807)

```text
// +17
```

## Source note 406, line 813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L813)

```text
// Copy registers are very different than on Adreno.
```

## Source note 407, line 818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L818)

```text
// +0 Depth is 4.
```

## Source note 408, line 819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L819)

```text
// +3
```

## Source note 409, line 820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L820)

```text
// +4
```

## Source note 410, line 821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L821)

```text
// +7
```

## Source note 411, line 822

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L822)

```text
// +8
```

## Source note 412, line 823

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L823)

```text
// +9
```

## Source note 413, line 824

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L824)

```text
// +10
```

## Source note 414, line 825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L825)

```text
// +20
```

## Source note 415, line 826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L826)

```text
// +22
```

## Source note 416, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L835)

```text
// +0
```

## Source note 417, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L836)

```text
// +3
```

## Source note 418, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L837)

```text
// +4
```

## Source note 419, line 838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L838)

```text
// +7
```

## Source note 420, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L839)

```text
// +13
```

## Source note 421, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L840)

```text
// +16
```

## Source note 422, line 841

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L841)

```text
// +22
```

## Source note 423, line 842

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L842)

```text
// +24
```

## Source note 424, line 843

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L843)

```text
// +25
```

## Source note 425, line 852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L852)

```text
// +0
```

## Source note 426, line 853

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L853)

```text
// +14
```

## Source note 427, line 854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L854)

```text
// +16
```

## Source note 428, line 855

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L855)

```text
// +30
```

## Source note 429, line 861

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L861)

```text
/*******************************************************************************
  ___ ___ ___ ___ _      ___   __
 |   \_ _/ __| _ \ |    /_\ \ / /
 | |) | |\__ \  _/ |__ / _ \ V /
 |___/___|___/_| |____/_/ \_\_|

   ___ ___  _  _ _____ ___  ___  _    _    ___ ___
  / __/ _ \| \| |_   _| _ \/ _ \| |  | |  | __| _ \
 | (_| (_) | .` | | | |   / (_) | |__| |__| _||   /
  \___\___/|_|\_| |_| |_|_\\___/|____|____|___|_|_\

*******************************************************************************/
```

## Source note 430, line 877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L877)

```text
// Unlike in the M56 documentation, for the 256-table entry, this is the
```

## Source note 431, line 878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L878)

```text
// absolute index, without the lower or upper 10 bits selection in the
```

## Source note 432, line 879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L879)

```text
// bit 0. For PWL, the bit 7 is ignored.
```

## Source note 433, line 880

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L880)

```text
// +0
```

## Source note 434, line 881

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L881)

```text
// +8
```

## Source note 435, line 890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L890)

```text
// +0, bits 0:5 are hardwired to zero
```

## Source note 436, line 891

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L891)

```text
// +16
```

## Source note 437, line 900

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L900)

```text
// See the M56 DC_LUTA_CONTROL for information about the way these should be
```

## Source note 438, line 901

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L901)

```text
// interpreted (`output = base + (multiplier * delta) / 2^increment`, where
```

## Source note 439, line 902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L902)

```text
// the increment is the value specified in DC_LUTA_CONTROL for the specific
```

## Source note 440, line 903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L903)

```text
// color channel, the base is 7 bits of the front buffer value above
```

## Source note 441, line 904

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L904)

```text
// `increment` bits, the multiplier is the lower `increment` bits of it; the
```

## Source note 442, line 905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L905)

```text
// increment is nonzero, otherwise the 256-entry table should be used
```

## Source note 443, line 906

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L906)

```text
// instead).
```

## Source note 444, line 907

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L907)

```text
// +0, bits 0:5 are hardwired to zero
```

## Source note 445, line 908

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L908)

```text
// +16, bits 0:5 are hardwired to zero
```

## Source note 446, line 917

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L917)

```text
// +0
```

## Source note 447, line 918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L918)

```text
// +10
```

## Source note 448, line 919

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L919)

```text
// +20
```

## Source note 449, line 920

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/registers.h#L920)

```text
// +30
```
