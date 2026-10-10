# Arithmetic: codegen source notes

This record preserves technical and API notes moved from `src/codegen/builders/arithmetic.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L73)

```text
// addme: rD = rA + CA - 1 (which is rA + CA + 0xFFFFFFFFFFFFFFFF)
```

## Source note 2, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L85)

```text
// addc: rD = rA + rB, CA = carry out
```

## Source note 3, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L97)

```text
// PPC division instructions do NOT trap on divide-by-zero - they produce undefined results.
```

## Source note 4, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L98)

```text
// We generate safe division that returns 0 when the divisor is zero.
```

## Source note 5, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L101)

```text
// divd rD,rA,rB: rD = rA / rB (64-bit signed)
```

## Source note 6, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L102)

```text
// Safe division: return 0 if divisor is zero or INT64_MIN / -1 (UB in C)
```

## Source note 7, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L114)

```text
// divdu rD,rA,rB: rD = rA / rB (64-bit unsigned)
```

## Source note 8, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L115)

```text
// Safe division: return 0 if divisor is zero
```

## Source note 9, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L125)

```text
// divw rD,rA,rB: rD = rA / rB (32-bit signed)
```

## Source note 10, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L126)

```text
// Safe division: return 0 if divisor is zero or INT32_MIN / -1 (UB in C)
```

## Source note 11, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L139)

```text
// divwu rD,rA,rB: rD = rA / rB (32-bit unsigned)
```

## Source note 12, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L140)

```text
// Safe division: return 0 if divisor is zero
```

## Source note 13, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L169)

```text
// Use unsigned multiplication to avoid signed overflow UB (PPC wraps on overflow)
```

## Source note 14, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L177)

```text
// Use unsigned multiplication to avoid signed overflow UB (PPC wraps on overflow)
```

## Source note 15, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L192)

```text
// mulhd: rD = high 64 bits of (rA * rB) (signed)
```

## Source note 16, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L202)

```text
// mulhdu: rD = high 64 bits of (rA * rB) (unsigned)
```

## Source note 17, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L216)

```text
// Use unsigned negation to avoid signed overflow UB when negating INT64_MIN
```

## Source note 18, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L264)

```text
// subfze: rD = ~rA + CA (subtract from zero extended)
```

## Source note 19, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L275)

```text
// subfme: rD = ~rA + CA - 1 (subtract from minus one extended)
```

## Source note 20, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L288)

```text
// Overflow-enable (OE) forms: XER[OV] for the result, XER[SO] sticky
```

## Source note 21, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L290)

```text
// OV is worked out from the operands before the base instruction runs (its
```

## Source note 22, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L291)

```text
// result may overwrite a source), so the base instruction's record form sees
```

## Source note 23, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L292)

```text
// the updated SO in CR0. Additions and subtractions judge overflow on 64
```

## Source note 24, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L293)

```text
// bits, as has207/xenia-edge 10da45ea4 does: SO is sticky, so a false
```

## Source note 25, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L294)

```text
// positive from a 32-bit view would never clear.
```

## Source note 26, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L298)

```text
// Sets OV to `ov`, a C++ expression over `a`, `b` and `r` (64-bit unsigned).
```

## Source note 27, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L310)

```text
// The shared record helper compares the low word; OE doubleword forms must
```

## Source note 28, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L311)

```text
// compare the full result. Emit after the base builder to replace CR0.
```

## Source note 29, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L319)

```text
// a + b (+ carry_in): overflow when both addends' signs differ from the sum's.
```

## Source note 30, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L354)

```text
// subf rD,rA,rB is rB + ~rA + 1.
```

## Source note 31, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L377)

```text
// The product of the low words overflows when it doesn't fit 32 signed bits.
```

## Source note 32, line 422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/arithmetic.cpp#L422)

```text
// CR field = XER[SO, OV, CA, 0]; those XER bits are cleared.
```
