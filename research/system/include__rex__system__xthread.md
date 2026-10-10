# Xthread: system source notes

This record preserves technical and API notes moved from `include/rex/system/xthread.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L57)

```text
// https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/ntos/ke/kthread_state.htm
```

## Source note 2, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L96)

```text
// KAPC is 0x28(40) bytes? (what's passed to ExAllocatePoolWithTag)
```

## Source note 3, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L97)

```text
// This is 4b shorter than NT - looks like the reserved dword at +4 is gone.
```

## Source note 4, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L98)

```text
// NOTE: stored in guest memory.
```

## Source note 5, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L99)

```text
// +0
```

## Source note 6, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L100)

```text
// +2
```

## Source note 7, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L101)

```text
// +3
```

## Source note 8, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L102)

```text
// +4
```

## Source note 9, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L103)

```text
// +8
```

## Source note 10, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L104)

```text
// +16
```

## Source note 11, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L105)

```text
// +20
```

## Source note 12, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L106)

```text
// +24
```

## Source note 13, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L107)

```text
// +28
```

## Source note 14, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L108)

```text
// +32
```

## Source note 15, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L109)

```text
// +36
```

## Source note 16, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L113)

```text
/// Guest fiber context buffer layout.
```

## Source note 17, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L115)

```text
// 0x00  lpParameter
```

## Source note 18, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L116)

```text
// 0x04  KTHREAD.stack_alloc_base (0xD0)
```

## Source note 19, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L117)

```text
// 0x08  KTHREAD.stack_base (0x5C), PCR.stack_base_ptr
```

## Source note 20, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L118)

```text
// 0x0C  KTHREAD.stack_limit (0x60), PCR.stack_end_ptr
```

## Source note 21, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L119)

```text
// 0x10  padding
```

## Source note 22, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L120)

```text
// 0x1C  saved LR (zeroed, unused by host)
```

## Source note 23, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L121)

```text
// 0x20  padding
```

## Source note 24, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L122)

```text
// 0x30  saved r1
```

## Source note 25, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L123)

```text
// non-volatile PPCContext register save area
```

## Source note 26, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L133)

```text
// 0x0
```

## Source note 27, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L134)

```text
// 0x8
```

## Source note 28, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L135)

```text
// 0xC
```

## Source note 29, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L136)

```text
// 0x10
```

## Source note 30, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L137)

```text
// 0x14
```

## Source note 31, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L138)

```text
// 0x16
```

## Source note 32, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L143)

```text
// 0x0
```

## Source note 33, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L144)

```text
// 0x4
```

## Source note 34, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L145)

```text
// 0x8
```

## Source note 35, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L146)

```text
// 0xC
```

## Source note 36, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L147)

```text
// 0xD
```

## Source note 37, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L148)

```text
// 0x10
```

## Source note 38, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L149)

```text
// 0x14
```

## Source note 39, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L150)

```text
// 0x18
```

## Source note 40, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L151)

```text
// 0x1C
```

## Source note 41, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L152)

```text
// 0x20
```

## Source note 42, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L153)

```text
// 0x24
```

## Source note 43, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L154)

```text
// 0x30
```

## Source note 44, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L155)

```text
// 0x34
```

## Source note 45, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L156)

```text
// 0x38
```

## Source note 46, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L157)

```text
// 0x3C
```

## Source note 47, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L158)

```text
// 0x40
```

## Source note 48, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L159)

```text
// 0x44
```

## Source note 49, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L160)

```text
// 0x48
```

## Source note 50, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L161)

```text
// 0x50
```

## Source note 51, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L162)

```text
// 0x54
```

## Source note 52, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L163)

```text
// 0x58
```

## Source note 53, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L164)

```text
// 0x5C
```

## Source note 54, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L165)

```text
// 0x60
```

## Source note 55, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L166)

```text
// 0x64
```

## Source note 56, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L167)

```text
// 0x68
```

## Source note 57, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L168)

```text
// 0x168
```

## Source note 58, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L169)

```text
// 0x184
```

## Source note 59, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L170)

```text
// 0x18C
```

## Source note 60, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L173)

```text
// Processor Control Region
```

## Source note 61, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L175)

```text
// 0x0
```

## Source note 62, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L176)

```text
// 0x4
```

## Source note 63, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L178)

```text
// 0x8
```

## Source note 64, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L180)

```text
// 0x8
```

## Source note 65, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L181)

```text
// 0x9
```

## Source note 66, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L184)

```text
// 0xA
```

## Source note 67, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L185)

```text
// 0xC
```

## Source note 68, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L186)

```text
// 0xD
```

## Source note 69, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L187)

```text
// 0xE
```

## Source note 70, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L188)

```text
// 0xF
```

## Source note 71, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L189)

```text
// 0x10
```

## Source note 72, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L190)

```text
// 0x14
```

## Source note 73, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L191)

```text
// 0x18
```

## Source note 74, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L192)

```text
// 0x19
```

## Source note 75, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L193)

```text
// 0x1A
```

## Source note 76, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L194)

```text
// 0x1B
```

## Source note 77, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L195)

```text
// 0x1C
```

## Source note 78, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L196)

```text
// 0x20
```

## Source note 79, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L197)

```text
// 0x30
```

## Source note 80, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L199)

```text
// 0x38
```

## Source note 81, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L200)

```text
// 0x38
```

## Source note 82, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L202)

```text
// 0x40
```

## Source note 83, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L203)

```text
// 0x5C
```

## Source note 84, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L204)

```text
// 0x60
```

## Source note 85, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L205)

```text
// 0x6C
```

## Source note 86, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L206)

```text
// 0x70 Stack base address (high addr)
```

## Source note 87, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L207)

```text
// 0x74 Stack end (low addr)
```

## Source note 88, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L208)

```text
// 0x78
```

## Source note 89, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L209)

```text
// 0x7C
```

## Source note 90, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L210)

```text
// 0x80
```

## Source note 91, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L211)

```text
// 0x100
```

## Source note 92, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L212)

```text
// 0x2A8
```

## Source note 93, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L213)

```text
// 0x2AC
```

## Source note 94, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L217)

```text
// 0x0
```

## Source note 95, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L218)

```text
// 0x10
```

## Source note 96, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L219)

```text
// 0x14
```

## Source note 97, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L220)

```text
// 0x18
```

## Source note 98, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L221)

```text
// 0x40
```

## Source note 99, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L222)

```text
// 0x58
```

## Source note 100, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L223)

```text
// 0x5C
```

## Source note 101, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L224)

```text
// 0x60
```

## Source note 102, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L225)

```text
// 0x64
```

## Source note 103, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L226)

```text
// 0x68
```

## Source note 104, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L227)

```text
// 0x6C
```

## Source note 105, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L228)

```text
// 0x6D
```

## Source note 106, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L229)

```text
// 0x6F
```

## Source note 107, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L230)

```text
// 0x70
```

## Source note 108, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L231)

```text
// 0x71
```

## Source note 109, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L232)

```text
// 0x72 (same as process_type below)
```

## Source note 110, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L233)

```text
// 0x73 (referenced most frequently)
```

## Source note 111, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L234)

```text
// apc_mode determines which list an apc goes into
```

## Source note 112, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L235)

```text
// 0x74
```

## Source note 113, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L236)

```text
// 0x84
```

## Source note 114, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L237)

```text
// 0x88
```

## Source note 115, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L238)

```text
// 0x89
```

## Source note 116, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L239)

```text
// 0x8A
```

## Source note 117, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L240)

```text
// 0x8B
```

## Source note 118, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L241)

```text
// 0x8C
```

## Source note 119, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L242)

```text
// 0x90
```

## Source note 120, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L243)

```text
// 0x94
```

## Source note 121, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L244)

```text
// 0x9C
```

## Source note 122, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L245)

```text
// 0xA0
```

## Source note 123, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L246)

```text
// 0xA4
```

## Source note 124, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L247)

```text
// 0xA5
```

## Source note 125, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L248)

```text
// 0xB0
```

## Source note 126, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L249)

```text
// 0xB4
```

## Source note 127, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L250)

```text
// 0xB8
```

## Source note 128, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L251)

```text
// 0xB9
```

## Source note 129, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L252)

```text
// 0xBA
```

## Source note 130, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L253)

```text
// 0xBB
```

## Source note 131, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L254)

```text
// 0xBC
```

## Source note 132, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L255)

```text
// 0xBD
```

## Source note 133, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L256)

```text
// 0xBE
```

## Source note 134, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L257)

```text
// 0xBF
```

## Source note 135, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L258)

```text
// 0xC0
```

## Source note 136, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L259)

```text
// 0xC4
```

## Source note 137, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L260)

```text
// 0xC8
```

## Source note 138, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L261)

```text
// 0xC9
```

## Source note 139, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L262)

```text
// 0xCA
```

## Source note 140, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L263)

```text
// 0xCB
```

## Source note 141, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L264)

```text
// 0xCC
```

## Source note 142, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L265)

```text
// 0xD0
```

## Source note 143, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L266)

```text
// 0xD4
```

## Source note 144, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L267)

```text
// 0xFC
```

## Source note 145, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L268)

```text
// 0x110
```

## Source note 146, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L269)

```text
// 0x118
```

## Source note 147, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L270)

```text
// 0x11C
```

## Source note 148, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L271)

```text
// 0x124
```

## Source note 149, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L272)

```text
// 0x128
```

## Source note 150, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L273)

```text
// 0x12C
```

## Source note 151, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L274)

```text
// 0x130
```

## Source note 152, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L275)

```text
// 0x138
```

## Source note 153, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L276)

```text
// 0x140
```

## Source note 154, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L277)

```text
// 0x144
```

## Source note 155, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L278)

```text
// 0x14C
```

## Source note 156, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L279)

```text
// 0x150
```

## Source note 157, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L280)

```text
// 0x154
```

## Source note 158, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L281)

```text
// 0x15C
```

## Source note 159, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L282)

```text
// 0x160
```

## Source note 160, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L283)

```text
// 0x164
```

## Source note 161, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L284)

```text
// 0x168
```

## Source note 162, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L285)

```text
// 0x16C
```

## Source note 163, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L286)

```text
// 0x170
```

## Source note 164, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L287)

```text
// 0x17C
```

## Source note 165, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L288)

```text
// 0x180
```

## Source note 166, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L320)

```text
// If the title is terminating and this is a running guest thread, self-exits
```

## Source note 167, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L321)

```text
// via Exit(0) and DOES NOT RETURN. Called from the kernel wait primitives.
```

## Source note 168, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L330)

```text
// True if the thread is created by the guest app.
```

## Source note 169, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L336)

```text
// The guest stack: [stack_limit, stack_base), with a guard page each side.
```

## Source note 170, line 364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L364)

```text
// Xbox thread IDs:
```

## Source note 171, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L365)

```text
// 0 - core 0, thread 0 - user
```

## Source note 172, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L366)

```text
// 1 - core 0, thread 1 - user
```

## Source note 173, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L367)

```text
// 2 - core 1, thread 0 - sometimes xcontent
```

## Source note 174, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L368)

```text
// 3 - core 1, thread 1 - user
```

## Source note 175, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L369)

```text
// 4 - core 2, thread 0 - xaudio
```

## Source note 176, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L370)

```text
// 5 - core 2, thread 1 - user
```

## Source note 177, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L389)

```text
// Internal - do not use.
```

## Source note 178, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L414)

```text
// Stack alloc base
```

## Source note 179, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L415)

```text
// Stack alloc size
```

## Source note 180, line 416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L416)

```text
// High address
```

## Source note 181, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L417)

```text
// Low address
```

## Source note 182, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L419)

```text
// Entry-point thread
```

## Source note 183, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L420)

```text
// Atomic: written by the thread itself in Exit/Terminate, read cross-thread by
```

## Source note 184, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xthread.h#L421)

```text
// KernelState::TerminateTitle's cooperative drain.
```
