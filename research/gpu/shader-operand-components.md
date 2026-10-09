# Shader operand components

Which source components Xenos shader instructions read. These cases are less
obvious than the microcode fields suggest. The shader parser
(`src/graphics/pipeline/shader/translator.cpp`) and the shader interpreter
(`src/graphics/pipeline/shader/interpreter.cpp`) follow them, so the DXBC and
DXIL paths agree.

## Scalar operations beside a three-source vector operation

An ALU instruction pairs a vector and a scalar operation. A scalar operation
with one operand reads source 3. If it takes two components (`adds`, `muls`,
`maxs`, `mins` and the others marked two-component in
`src/graphics/format/ucode.cpp`), the left-hand `a` is W. The right-hand `b`
depends on the vector operation:

- If the vector operation uses one or two sources, `b` is X.
- If the vector operation uses all three sources (`mad`, `cndeq`, `cndge`,
  `cndgt`, `dp2add`), `b` is Z.

Both components go through the source 3 swizzle as usual.
`AluVectorOpcodeInfo::ScalarSecondSourceComponent` returns 2 (Z) or 0 (X).

Source: has207/xenia-edge `92ada8ebc0` ("Fix scalar ALU swizzles with
three-source vector ops", 2026-08-13). Before the fix, a `maxs` co-issued with
a `mad` read the wrong component on every path. Tests:
`tests/unit/graphics/alu_scalar_operand_test.cpp`.

## 1D texture fetches with two coordinates

`tfetch1D` and `getBCF1D` normally read one coordinate. If the source swizzle
selects different components for X, Y and Z, the shader is passing XY for a
2D fetch constant, and the fetch is translated as 2D. Otherwise Y is 0 and
the title samples the top row. 545407D4's UI shader does this.

Source: has207/xenia-edge `fbdb1f2817` ("Handle two component tfetch1D
coordinates", 2026-08-04). ReXGlue took it with the getBCF port: the parser
sets two components, and the DXBC translator
(`ProcessTextureFetchInstruction` in `dxbc_translator_fetch.cpp`) and the
SPIR-V translator (`coordinate_dimension` in `spirv_translator_fetch.cpp`)
fetch it as 2D.
