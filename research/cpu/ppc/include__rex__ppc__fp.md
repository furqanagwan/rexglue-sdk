# Fp: ppc source notes

This record preserves technical and API notes moved from `include/rex/ppc/fp.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L37)

```text
// Scalar classification
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L40)

```text
/// PowerPC's default QNaN is positive; x86's is negative.
```

## Source note 3, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L74)

```text
/// A NaN result is the first NaN operand, quieted with its sign kept, or the
```

## Source note 4, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L75)

```text
/// default QNaN when the operation itself was invalid.
```

## Source note 5, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L90)

```text
/// Single-precision arithmetic answers the default QNaN when every operand is
```

## Source note 6, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L91)

```text
/// finite and one is a denormalized double. Divide and square root don't.
```

## Source note 7, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L92)

```text
/// It sits on every single-precision op, so the hot path is one subtract and
```

## Source note 8, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L93)

```text
/// compare per operand (a zero wraps to the top and never reads as
```

## Source note 9, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L94)

```text
/// denormal), with the finite check only once one hits (as xenia-edge
```

## Source note 10, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L95)

```text
/// 078a07b53 does).
```

## Source note 11, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L110)

```text
// Scalar arithmetic
```

## Source note 12, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L112)

```text
// The host result is kept unless it is a NaN, which costs one compare.
```

## Source note 13, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L135)

```text
// Multiply-add takes frA, frC, frB, but a NaN is chosen in A, B, C order. The
```

## Source note 14, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L136)

```text
// negated forms leave a NaN result's sign alone.
```

## Source note 15, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L154)

```text
// The single-precision forms keep the host result unless it is a NaN or an
```

## Source note 16, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L155)

```text
// operand is a denormalized double; both are rare, so one unlikely branch
```

## Source note 17, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L156)

```text
// covers them and the exact answer is worked out out of line.
```

## Source note 18, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L163)

```text
// r is the multiply-add result (negated for the negated forms).
```

## Source note 19, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L190)

```text
// A denormalized operand keeps the double quotient and root, unrounded.
```

## Source note 20, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L216)

```text
/// frsqrte: the Xenon's estimate, 5 bits from a 16-entry table indexed by the
```

## Source note 21, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L217)

```text
/// exponent's parity and the top 3 mantissa bits (xenia-edge's frsqrte helper).
```

## Source note 22, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L223)

```text
// +-0 -> +-inf
```

## Source note 23, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L228)

```text
// NaN, quieted
```

## Source note 24, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L229)

```text
// -inf
```

## Source note 25, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L235)

```text
// denormal: normalise
```

## Source note 26, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L245)

```text
/// The vrsqrtefp table (src/system/ppc_fp.cpp).
```

## Source note 27, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L248)

```text
/// vrsqrtefp on one element, with VSCR[NJ] set (denormals as zero).
```

## Source note 28, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L251)

```text
// positive normal
```

## Source note 29, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L254)

```text
// NaN, quieted
```

## Source note 30, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L256)

```text
// +inf
```

## Source note 31, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L258)

```text
// +-0 and denormals -> +-inf
```

## Source note 32, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L259)

```text
// negative: the default QNaN
```

## Source note 33, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L262)

```text
/// fctiw/fctiwz: a NaN or too-negative value gives the sign-extended most
```

## Source note 34, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L263)

```text
/// negative word, a too-positive one the most positive.
```

## Source note 35, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L275)

```text
/// fctid/fctidz: as to_int32, on a doubleword.
```

## Source note 36, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L287)

```text
/// lfs: widening a single never quiets it on PowerPC, where the host convert
```

## Source note 37, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L288)

```text
/// sets a signalling NaN's quiet bit.
```

## Source note 38, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L298)

```text
/// stfs: as load_single, narrowing.
```

## Source note 39, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L309)

```text
// Record forms (fadd. ...): CR1 is FX, FEX, VX, OX
```

## Source note 40, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L311)

```text
// FX summarises every exception the instruction raised, VX the invalid ones
```

## Source note 41, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L312)

```text
// and OX overflow. FEX needs the exception enables, which nothing sets. The
```

## Source note 42, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L313)

```text
// host status flags supply what the arithmetic raised; `invalid` adds what
```

## Source note 43, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L314)

```text
// the host doesn't report (a signalling operand it quieted, or 0 x inf with a
```

## Source note 44, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L315)

```text
// quiet NaN addend). The flags are read per instruction rather than kept
```

## Source note 45, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L316)

```text
// sticky in the FPSCR.
```

## Source note 46, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L326)

```text
/// Compare operands and record the invalid causes specified by fcmpu/fcmpo.
```

## Source note 47, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L338)

```text
// Compare updates FPCC, but preserves C, FR, and FI. An ordered compare
```

## Source note 48, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L339)

```text
// that raises an enabled invalid exception still reports unordered FPCC.
```

## Source note 49, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L348)

```text
/// Return the PowerPC FPRF encoding for a floating-point result.
```

## Source note 50, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L433)

```text
/// x86 skips the invalid signal for 0 x inf when the addend is a quiet NaN.
```

## Source note 51, line 498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L498)

```text
/// Return the sign of exact-result minus rounded-result. This uses an
```

## Source note 52, line 499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L499)

```text
/// error-free residual for addition and fused multiply-add to avoid comparing
```

## Source note 53, line 500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L500)

```text
/// only the already-rounded host result.
```

## Source note 54, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L540)

```text
/// Execute a scalar floating-point instruction, record its sticky FPSCR state,
```

## Source note 55, line 541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L541)

```text
/// and optionally update CR1 for the record form.
```

## Source note 56, line 558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L558)

```text
// FR is architecturally undefined for overflow; FI still reports the
```

## Source note 57, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L559)

```text
// overflowed, inexact result.
```

## Source note 58, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L570)

```text
/// Runs `op` on the operands with the host status flags cleared and sets CR1
```

## Source note 59, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L571)

```text
/// from what it raised. The operands and result go through volatiles so the
```

## Source note 60, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L572)

```text
/// arithmetic stays between the flag calls. `quiet` reports nothing raised
```

## Source note 61, line 573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L573)

```text
/// (a single-precision denormal operand).
```

## Source note 62, line 600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L600)

```text
/// Convert a signed guest integer to double and track its rounding fields.
```

## Source note 63, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L616)

```text
/// Convert to an integer and accumulate the guest FPSCR exception state.
```

## Source note 64, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L638)

```text
/// Execute fres/frsqrte and accumulate the exception state defined by the
```

## Source note 65, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L639)

```text
/// operand. These estimate instructions do not report inexact, and FR/FI are
```

## Source note 66, line 640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L640)

```text
/// architecturally undefined for them, so both are left unchanged. FPRF takes
```

## Source note 67, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L641)

```text
/// the result class (single precision for fres) unless an enabled invalid or
```

## Source note 68, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L642)

```text
/// zero-divide exception suppresses the result.
```

## Source note 69, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L653)

```text
// |x| > 2^126 makes 1/x tiny in single precision.
```

## Source note 70, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L669)

```text
// Vector (VMX) NaN rules
```

## Source note 71, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L671)

```text
// A NaN element is the first NaN operand element, quieted, or the positive
```

## Source note 72, line 672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L672)

```text
// default QNaN (x86 makes it negative). Results without a NaN element return
```

## Source note 73, line 673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L673)

```text
// after one compare.
```

## Source note 74, line 696

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L696)

```text
/// Replaces r's NaN elements; `negate` flips the sign of the others.
```

## Source note 75, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L716)

```text
/// Replaces the elements where a or b is a NaN (min and max return the other
```

## Source note 76, line 717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L717)

```text
/// operand there, so the result can't be tested).
```

## Source note 77, line 732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L732)

```text
/// VMX flushes a denormal element to zero, keeping its sign. The host's
```

## Source note 78, line 733

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L733)

```text
/// denormals-are-zero mode does so for arithmetic but not for min and max,
```

## Source note 79, line 734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L734)

```text
/// which return the operand's own bits.
```

## Source note 80, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L744)

```text
// Fused multiply-add. vmaddfp and vnmsubfp round once, so a separate multiply
```

## Source note 81, line 745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L745)

```text
// and add can be an ulp out, or lose the sign of a product that flushes to
```

## Source note 82, line 746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L746)

```text
// zero. FMA3 does it in one instruction where the CPU has it (checked once);
```

## Source note 83, line 747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L747)

```text
// otherwise the elements go through double, where the product is exact.
```

## Source note 84, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L759)

```text
// Inline assembly rather than a target("fma") function, which can't be
```

## Source note 85, line 760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L760)

```text
// inlined into the SSE4.1 title code. VEX.128 clears the upper halves, so
```

## Source note 86, line 761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L761)

```text
// mixing it with the legacy SSE code costs no transition.
```

## Source note 87, line 774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L774)

```text
/// a x c + b (or - b), rounded once to single.
```

## Source note 88, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L802)

```text
/// vmaddfp: A x C + B, NaN in A, B, C order.
```

## Source note 89, line 806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L806)

```text
/// vnmsubfp: -(A x C - B), a NaN element not negated.
```

## Source note 90, line 811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L811)

```text
/// vmaxfp/vminfp: denormals flushed, +0 above -0, and a NaN element quieted.
```

## Source note 91, line 827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L827)

```text
/// vrsqrtefp on each element.
```

## Source note 92, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L836)

```text
// vexptefp and vlogefp: minimax polynomials snapped onto the guest's 2^-11
```

## Source note 93, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L837)

```text
// estimate grid, which keeps 2^0 == 1 and log2(2^n) == n exact (xenia-edge
```

## Source note 94, line 838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L838)

```text
// fb225d975 coefficients).
```

## Source note 95, line 857

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L857)

```text
/// vexptefp: 2^x estimate.
```

## Source note 96, line 867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L867)

```text
// Out-of-range and non-finite inputs never reach the estimator.
```

## Source note 97, line 876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L876)

```text
/// vlogefp: log2(x) estimate.
```

## Source note 98, line 894

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L894)

```text
// Zero and denormals reach the estimator as zero: -inf.
```

## Source note 99, line 903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/fp.h#L903)

```text
/// vcmpbfp: bit 31 when a > b, bit 30 when a < -b, both for a NaN element.
```
