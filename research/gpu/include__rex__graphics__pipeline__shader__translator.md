# Translator: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/translator.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L32)

```text
/*dynamic_addressable_register_count*/
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L33)

```text
/*host_vertex_shader_type*/
```

## Source note 3, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L38)

```text
/*dynamic_addressable_register_count*/
```

## Source note 4, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L42)

```text
// AnalyzeUcode must be done on the shader before translating!
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L48)

```text
// Resets translator state before beginning translation.
```

## Source note 6, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L51)

```text
// Shader and modification currently being translated.
```

## Source note 7, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L55)

```text
// Register count from SQ_PROGRAM_CNTL, stored by the implementation in its
```

## Source note 8, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L56)

```text
// modification bits.
```

## Source note 9, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L59)

```text
// True if the current shader is a vertex shader.
```

## Source note 10, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L61)

```text
// True if the current shader is a pixel shader.
```

## Source note 11, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L64)

```text
// Whether a texture fetch derives its LOD from gradients (implicit or
```

## Source note 12, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L65)

```text
// register) rather than an explicit LOD (xenia-edge).
```

## Source note 13, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L71)

```text
// Temporary register count, accessible via static and dynamic addressing.
```

## Source note 14, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L74)

```text
// Emits a translation error that will be passed back in the result.
```

## Source note 15, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L77)

```text
// Handles the start of translation.
```

## Source note 16, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L78)

```text
// At this point the vertex and texture bindings have been gathered.
```

## Source note 17, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L81)

```text
// Handles the end of translation when all ucode has been processed.
```

## Source note 18, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L82)

```text
// Returns the translated shader binary.
```

## Source note 19, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L85)

```text
// Handles post-translation tasks when the shader has been fully translated.
```

## Source note 20, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L87)

```text
// Sets the host disassembly on a shader.
```

## Source note 21, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L92)

```text
// Pre-process a control-flow instruction before anything else.
```

## Source note 22, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L94)

```text
/*instrs*/
```

## Source note 23, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L96)

```text
// Handles translation for control flow label addresses.
```

## Source note 24, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L97)

```text
// This is triggered once for each label required (due to control flow
```

## Source note 25, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L98)

```text
// operations) before any of the instructions within the target exec.
```

## Source note 26, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L99)

```text
/*cf_index*/
```

## Source note 27, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L101)

```text
// Handles translation for control flow nop instructions.
```

## Source note 28, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L102)

```text
/*cf_index*/
```

## Source note 29, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L103)

```text
// Handles the start of a control flow instruction at the given address.
```

## Source note 30, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L104)

```text
/*cf_index*/
```

## Source note 31, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L105)

```text
// Handles the end of a control flow instruction that began at the given
```

## Source note 32, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L106)

```text
// address.
```

## Source note 33, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L107)

```text
/*cf_index*/
```

## Source note 34, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L108)

```text
// Handles translation for control flow exec instructions prior to their
```

## Source note 35, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L109)

```text
// contained ALU/fetch instructions.
```

## Source note 36, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L110)

```text
/*instr*/
```

## Source note 37, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L111)

```text
// Handles translation for control flow exec instructions after their
```

## Source note 38, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L112)

```text
// contained ALU/fetch instructions.
```

## Source note 39, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L113)

```text
/*instr*/
```

## Source note 40, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L114)

```text
// Handles translation for loop start instructions.
```

## Source note 41, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L115)

```text
/*instr*/
```

## Source note 42, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L116)

```text
// Handles translation for loop end instructions.
```

## Source note 43, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L117)

```text
/*instr*/
```

## Source note 44, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L118)

```text
// Handles translation for function call instructions.
```

## Source note 45, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L119)

```text
/*instr*/
```

## Source note 46, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L120)

```text
// Handles translation for function return instructions.
```

## Source note 47, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L121)

```text
/*instr*/
```

## Source note 48, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L122)

```text
// Handles translation for jump instructions.
```

## Source note 49, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L123)

```text
/*instr*/
```

## Source note 50, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L124)

```text
// Handles translation for alloc instructions. Memory exports for eM#
```

## Source note 51, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L125)

```text
// indicated by export_eM must be performed, regardless of the alloc type.
```

## Source note 52, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L126)

```text
/*instr*/
```

## Source note 53, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L127)

```text
/*export_eM*/
```

## Source note 54, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L129)

```text
// Handles translation for vertex fetch instructions.
```

## Source note 55, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L130)

```text
/*instr*/
```

## Source note 56, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L131)

```text
// Handles translation for texture fetch instructions.
```

## Source note 57, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L132)

```text
/*instr*/
```

## Source note 58, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L133)

```text
// Handles translation for ALU instructions.
```

## Source note 59, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L134)

```text
// memexport_eM_potentially_written_before needs to be handled by `kill`
```

## Source note 60, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L135)

```text
// instruction to make sure memory exports for the eM# writes earlier in
```

## Source note 61, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L136)

```text
// previous execs and the current exec are done before the invocation becomes
```

## Source note 62, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L137)

```text
// inactive.
```

## Source note 63, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L138)

```text
/*instr*/
```

## Source note 64, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L139)

```text
/*memexport_eM_potentially_written_before*/
```

## Source note 65, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L145)

```text
// Current shader and modification being translated.
```

## Source note 66, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L148)

```text
// Accumulated translation errors.
```

## Source note 67, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L151)

```text
// Temporary register count, accessible via static and dynamic addressing.
```

## Source note 68, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L154)

```text
// Current control flow dword index.
```

## Source note 69, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/translator.h#L157)

```text
// Kept for supporting vfetch_mini.
```
