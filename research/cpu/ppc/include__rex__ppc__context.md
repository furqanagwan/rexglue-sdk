# Context: ppc source notes

This record preserves technical and API notes moved from `include/rex/ppc/context.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L29)

```text
// Pack/Unpack Constants (NORMPACKED32 - 2:10:10:10 format)
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L40)

```text
// General Purpose Register
```

## Source note 3, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L57)

```text
// Fixed-Point Exception Register (XER)
```

## Source note 4, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L67)

```text
// Condition Register (CR) Field
```

## Source note 5, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L121)

```text
// Vector Register (128-bit)
```

## Source note 6, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L138)

```text
// Floating-Point Status and Control Register (FPSCR)
```

## Source note 7, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L149)

```text
// FPSCR bits other than RN as the guest last wrote them with mtfsf. Only RN
```

## Source note 8, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L150)

```text
// reaches the host; arithmetic status is accumulated here for mffs/mcrfs.
```

## Source note 9, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L194)

```text
// Bits the guest owns; the rest is host policy seeded by InitHost.
```

## Source note 10, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L200)

```text
// Restoring the whole word would unmask every FP exception when csr is 0.
```

## Source note 11, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L218)

```text
/// Record exception cause bits produced by a guest floating-point operation.
```

## Source note 12, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L219)

```text
/// FX is set only when an exception flag changes from zero to one; FEX and
```

## Source note 13, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L220)

```text
/// VX are summaries of their enables/cause bits.
```

## Source note 14, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L278)

```text
// Host and guest FP modes
```

## Source note 15, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L280)

```text
// Generated code runs with the guest's rounding mode and VMX flush-to-zero in
```

## Source note 16, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L281)

```text
// the host control register, and caches it in ctx.fpscr.csr. Host code
```

## Source note 17, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L282)

```text
// (kernel exports, XAM, the guide, audio) must not run in that mode, and
```

## Source note 18, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L283)

```text
// guest code entered from the host must find its cache true. Each scope
```

## Source note 19, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L284)

```text
// writes the register only when the mode differs, and restores it on exit.
```

## Source note 20, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L286)

```text
/// Host code called from guest code: round to nearest, no flush. On the way
```

## Source note 21, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L287)

```text
/// back the guest bits come from `fpscr`, which a guest callback made inside
```

## Source note 22, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L288)

```text
/// the host code may have changed.
```

## Source note 23, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L308)

```text
/// Guest code called from host code: the guest bits of `fpscr` go in, the
```

## Source note 24, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L309)

```text
/// host's exception masks stay, and the cache is made to match.
```

## Source note 25, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L336)

```text
// PPCContext Structure
```

## Source note 26, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L377)

```text
// The address lwarx/ldarx reserved; all ones when none is held.
```

## Source note 27, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L389)

```text
// VSCR saturation flag (for vector ops)
```

## Source note 28, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L390)

```text
// VSCR non-Java mode; Xenon defaults to flushing VMX denormals.
```

## Source note 29, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L392)

```text
/**
   * Last indirect call target address. Set by REX_CALL_INDIRECT_FUNC before
   * dispatch. Used by the invalid-function trap to report the faulting address.
   * Unconditional (not guarded by config flags) because ctr may be optimized
   * to a local variable via REX_CONFIG_CTR_AS_LOCAL.
   */
```

## Source note 30, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L562)

```text
//--- Non-volatile register save/restore --------
```

## Source note 31, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L563)

```text
// Layout: r14-r31 (144) | f14-f31 (144) | v14-v31 (288) | v64-v127 (1024)
```

## Source note 32, line 564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/context.h#L564)

```text
//       | cr2-cr4 (12) | fpscr (4).  Total: 1616 bytes.
```
