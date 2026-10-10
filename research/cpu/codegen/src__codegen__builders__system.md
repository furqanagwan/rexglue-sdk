# System: codegen source notes

This record preserves technical and API notes moved from `src/codegen/builders/system.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L18)

```text
// No-ops and Sync Operations
```

## Source note 2, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L22)

```text
// Canonical PPC no-op (ori 0,0,0)
```

## Source note 3, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L28)

```text
// Xenon-specific debug breakpoint, no effect in recompiled code
```

## Source note 4, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L34)

```text
// Memory barrier, x86 has strong ordering so this is a no-op
```

## Source note 5, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L40)

```text
// Generated code does not fetch or execute guest instructions dynamically.
```

## Source note 6, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L46)

```text
// Instruction cache invalidation has no effect on static native code.
```

## Source note 7, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L52)

```text
// Lightweight memory barrier, x86 has strong ordering so this is a no-op
```

## Source note 8, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L58)

```text
// Enforce in-order execution of I/O, x86 has strong ordering so this is a no-op
```

## Source note 9, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L64)

```text
// Xenon-specific 16-cycle delay hint, no effect in recompiled code
```

## Source note 10, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L70)

```text
// Xenon-specific cache control thread priority low, no effect in recompiled code
```

## Source note 11, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L76)

```text
// Xenon-specific cache control thread priority medium, no effect in recompiled code
```

## Source note 12, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L82)

```text
// Xenon-specific cache control thread priority high, no effect in recompiled code
```

## Source note 13, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L88)

```text
// Trap Instructions
```

## Source note 14, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L89)

```text
// PPC trap instructions are assertion/debug checks. The TO field (bits 21-25)
```

## Source note 15, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L90)

```text
// is a 5-bit mask specifying which conditions trigger: signed lt/gt, eq,
```

## Source note 16, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L91)

```text
// unsigned lt/gt. We extract TO directly from the instruction word so that
```

## Source note 17, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L92)

```text
// both generic (tw TO,rA,rB) and simplified (tweq rA,rB) forms work with
```

## Source note 18, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L93)

```text
// the same builder.
```

## Source note 19, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L110)

```text
// twi 31, r0, <imm> is an unconditional trap with service code in the immediate
```

## Source note 20, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L141)

```text
// Cache Operations
```

## Source note 21, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L145)

```text
// Hint instruction, access violation callback handlers take care of this on write
```

## Source note 22, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L151)

```text
// Hint instruction, prefetch has no semantic effect
```

## Source note 23, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L157)

```text
// Hint instruction, prefetch-for-store has no semantic effect
```

## Source note 24, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L163)

```text
// Xenon has 128-byte cache blocks for both dcbz and dcbzl.
```

## Source note 25, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L173)

```text
// Compute EA, align to 128-byte cache line, apply physical offset
```

## Source note 26, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L183)

```text
// Hint instruction, access violation callback handlers take care of this on write
```

## Source note 27, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L189)

```text
// Move Register
```

## Source note 28, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L196)

```text
// Propagates MMIO base flag from source to destination register
```

## Source note 29, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L206)

```text
// Move Register Field
```

## Source note 30, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L210)

```text
// Trivally copy one Control Register Field to another:
```

## Source note 31, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L217)

```text
// Only exception flags are cleared; rounding, enables and result flags survive.
```

## Source note 32, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L218)

```text
// In particular, clearing a field must not reset RN through guest_bits, which
```

## Source note 33, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L219)

```text
// intentionally excludes the host-backed rounding bits.
```

## Source note 34, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L232)

```text
// Move From Special Registers
```

## Source note 35, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L256)

```text
// FXM is a one-hot mask: bit 7 = CR0, bit 6 = CR1, ..., bit 0 = CR7
```

## Source note 36, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L280)

```text
// Memory barrier for MSR read
```

## Source note 37, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L282)

```text
// Check global lock and return appropriate value
```

## Source note 38, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L283)

```text
// Returns 0x8000 if unlocked (interrupts enabled), 0 if locked
```

## Source note 39, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L295)

```text
// Xbox 360 timebase runs at 50 MHz (guest tick frequency)
```

## Source note 40, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L296)

```text
// Using REX_QUERY_TIMEBASE() macro provides properly scaled timing from the runtime
```

## Source note 41, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L302)

```text
// Upper 32 bits of timebase
```

## Source note 42, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L308)

```text
// Move To Special Registers
```

## Source note 43, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L348)

```text
// Memory barrier for MSR write
```

## Source note 44, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L350)

```text
// Preserve the modeled MSR mask, but change the interrupt lock only when
```

## Source note 45, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L351)

```text
// EE changes. Register identity cannot identify an interrupt transition:
```

## Source note 46, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L352)

```text
// ordinary mtmsr writes and nested save/restore pairs use arbitrary GPRs.
```

## Source note 47, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/system.cpp#L391)

```text
// Clear Left Double Word Immediate
```
