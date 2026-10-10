# Logical: codegen source notes

This record preserves technical and API notes moved from `src/codegen/builders/logical.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L17)

```text
// AND Operations
```

## Source note 2, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L37)

```text
// ANDI. always sets CR0
```

## Source note 3, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L46)

```text
// ANDIS. always sets CR0
```

## Source note 4, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L53)

```text
// OR Operations
```

## Source note 5, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L81)

```text
// Propagates MMIO base flag if either source register is marked MMIO
```

## Source note 6, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L82)

```text
// covers mr rD,rS which assembles as or rD,rS,rS
```

## Source note 7, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L103)

```text
// ori only sets low bits - propagate MMIO base from source
```

## Source note 8, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L121)

```text
// NOTE(tomc): don't clear flag here - oris may preserve MMIO base from source
```

## Source note 9, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L127)

```text
// XOR Operations
```

## Source note 10, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L150)

```text
// eqv: rA = ~(rS ^ rB) (XNOR - equivalent)
```

## Source note 11, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L158)

```text
// Count Leading Zeros
```

## Source note 12, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L176)

```text
// Sign Extension
```

## Source note 13, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L198)

```text
// Clear Left Word Immediate
```

## Source note 14, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L209)

```text
// Rotate Left Double Word
```

## Source note 15, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L251)

```text
// The disassembler uses rotld for rldcl with a zero mask.
```

## Source note 16, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L285)

```text
// Rotate Left Word
```

## Source note 17, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L309)

```text
// Like rlwinm but shift amount comes from register, not immediate
```

## Source note 18, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L312)

```text
// Register, not immediate
```

## Source note 19, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L334)

```text
// Shift Left
```

## Source note 20, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L354)

```text
// Shift Right Algebraic (signed)
```

## Source note 21, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L412)

```text
// Shift Right (unsigned)
```

## Source note 22, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L432)

```text
// crand: CR[crD] = CR[crA] & CR[crB]
```

## Source note 23, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L438)

```text
// crandc: CR[crD] = CR[crA] & ~CR[crB]
```

## Source note 24, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L444)

```text
// creqv: CR[crD] = ~(CR[crA] ^ CR[crB])  (XNOR)
```

## Source note 25, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L450)

```text
// crnand: CR[crD] = ~(CR[crA] & CR[crB])
```

## Source note 26, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L456)

```text
// crnor: CR[crD] = ~(CR[crA] | CR[crB])
```

## Source note 27, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L462)

```text
// cror: CR[crD] = CR[crA] | CR[crB]
```

## Source note 28, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L468)

```text
// crorc: CR[crD] = CR[crA] | ~CR[crB]
```

## Source note 29, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/logical.cpp#L474)

```text
// crxor: CR[crD] = CR[crA] ^ CR[crB]
```
