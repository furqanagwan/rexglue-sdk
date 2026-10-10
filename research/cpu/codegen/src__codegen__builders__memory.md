# Memory: codegen source notes

This record preserves technical and API notes moved from `src/codegen/builders/memory.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L18)

```text
// Load Immediate (not really memory operations, but L* category)
```

## Source note 2, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L43)

```text
// Byte Loads
```

## Source note 3, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L67)

```text
// Halfword Loads
```

## Source note 4, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L101)

```text
// Load Halfword Algebraic with Update: sign-extend then update rA
```

## Source note 5, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L110)

```text
// Load Halfword Algebraic with Update Indexed: EA = rA + rB; rD = EXTS(MEM16(EA)); rA = EA
```

## Source note 6, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L119)

```text
// Load Halfword Byte-Reverse Indexed
```

## Source note 7, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L129)

```text
// Word Loads
```

## Source note 8, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L138)

```text
// Load Word Algebraic with Update Indexed: EA = rA + rB; rD = EXTS(MEM32(EA)); rA = EA
```

## Source note 9, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L157)

```text
// Snapshot the address before loads, including when RA is a destination.
```

## Source note 10, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L195)

```text
// Doubleword Loads
```

## Source note 11, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L209)

```text
// Load Doubleword Byte-Reverse Indexed
```

## Source note 12, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L228)

```text
// Atomic Load and Reserve
```

## Source note 13, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L242)

```text
// Floating Point Loads
```

## Source note 14, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L286)

```text
// Load Floating-point Double with Update
```

## Source note 15, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L296)

```text
// Load Floating-point Double with Update Indexed
```

## Source note 16, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L306)

```text
// Load Floating-point Single with Update (convert to double)
```

## Source note 17, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L318)

```text
// Load Floating-point Single with Update Indexed (convert to double)
```

## Source note 18, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L330)

```text
// Byte Stores
```

## Source note 19, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L354)

```text
// Halfword Stores
```

## Source note 20, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L387)

```text
// Word Stores
```

## Source note 21, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L411)

```text
// EA = (rA == 0 ? 0 : r[rA]) + EXTS(d); store r[rS]..r[31] at EA, EA+4, ...
```

## Source note 22, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L435)

```text
// Atomic Store Conditional
```

## Source note 23, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L449)

```text
// Doubleword Stores
```

## Source note 24, line 463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L463)

```text
// Store Doubleword Byte-Reverse Indexed
```

## Source note 25, line 483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L483)

```text
// Floating Point Stores
```

## Source note 26, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L506)

```text
// Store Floating-point Double with Update Indexed: EA = rA + rB; MEM(EA) = FRS; rA = EA
```

## Source note 27, line 547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L547)

```text
// Store Floating-point Double with Update
```

## Source note 28, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L557)

```text
// Store Floating-point Single with Update (convert double to float first)
```

## Source note 29, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L569)

```text
// Store Floating-point Single with Update Indexed
```

## Source note 30, line 582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L582)

```text
// Vector Loads (will be more comprehensive in vector.cpp)
```

## Source note 31, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L586)

```text
// NOTE(tomc): for endian swapping, we reverse the whole vector instead of individual elements.
```

## Source note 32, line 587

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L587)

```text
// this is accounted for in every instruction (eg. dp3 sums yzw instead of xyz)
```

## Source note 33, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L637)

```text
// Vector Stores
```

## Source note 34, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L641)

```text
// TODO(tomc): vectorize
```

## Source note 35, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L642)

```text
// NOTE: accounting for the full vector reversal here
```

## Source note 36, line 650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L650)

```text
// TODO(tomc): vectorize
```

## Source note 37, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L651)

```text
// NOTE: accounting for the full vector reversal here
```

## Source note 38, line 659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L659)

```text
// TODO(tomc): vectorize
```

## Source note 39, line 660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L660)

```text
// NOTE: accounting for the full vector reversal here
```

## Source note 40, line 668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L668)

```text
// TODO(tomc): vectorize
```

## Source note 41, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L669)

```text
// NOTE: accounting for the full vector reversal here
```

## Source note 42, line 678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L678)

```text
// TODO(tomc): vectorize
```

## Source note 43, line 679

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/memory.cpp#L679)

```text
// NOTE: accounting for the full vector reversal here
```
