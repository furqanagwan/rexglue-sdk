# Elf module: system source notes

This record preserves technical and API notes moved from `src/system/elf_module.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L20)

```text
/*kernel_state*/
```

## Source note 2, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L25)

```text
// ELF structures
```

## Source note 3, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L69)

```text
// Not an ELF file!
```

## Source note 4, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L73)

```text
// 32bit
```

## Source note 5, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L75)

```text
/* ET_EXEC */
```

## Source note 6, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L76)

```text
// Not executable (shared objects not supported yet)
```

## Source note 7, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L81)

```text
/* EM_PPC */
```

## Source note 8, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L82)

```text
// Not a PPC ELF!
```

## Source note 9, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L90)

```text
// Parse LOAD program headers and load into memory.
```

## Source note 10, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L101)

```text
// Entry point virtual address
```

## Source note 11, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L104)

```text
// Copy the ELF header
```

## Source note 12, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L111)

```text
// Calculate base address and image size from loaded segments
```

## Source note 13, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L116)

```text
/* PT_LOAD */
```

## Source note 14, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L116)

```text
/* PT_DYNAMIC */
```

## Source note 15, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L117)

```text
// Track address range
```

## Source note 16, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L123)

```text
// Allocate and copy into memory.
```

## Source note 17, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L124)

```text
// Base address @ 0x80000000
```

## Source note 18, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L148)

```text
// crack: No JIT backend to notify about executable code
```

## Source note 19, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L149)

```text
// In JIT mode this would be: processor_->backend()->CommitExecutableRange(...)
```

## Source note 20, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L155)

```text
// Set base address and image size
```

## Source note 21, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/elf_module.cpp#L167)

```text
// crack: Memory allocated for ELF segments remains - no deallocation
```
