# Disasm: codegen source notes

This record preserves technical and API notes moved from `src/codegen/ppc/disasm.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/disasm.h#L20)

```text
// Low-level Disassembler Engine (binutils wrapper)
```

## Source note 2, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/disasm.h#L22)

```text
// Decodes raw bytes into ppc_insn struct using GNU binutils
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/ppc/disasm.h#L32)

```text
/**
   * Disassemble a single instruction
   * @return Number of bytes decoded
   */
```
