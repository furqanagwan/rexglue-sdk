# Test recompiler: tools source notes

This record preserves technical and API notes moved from `src/rexglue/commands/test_recompiler.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L90)

```text
// "ABCD12" or, as hardware captures write them, "[AB, CD, 12]".
```

## Source note 2, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L107)

```text
/* Source order is high-to-low; stored low-to-high to match runtime layout. */
```

## Source note 3, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L134)

```text
// A bracketed scalar ("f4 [3FF0000000000000]") is the register's bits.
```

## Source note 4, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L148)

```text
// Hardware captures write "0x0000000010001000"; the template adds the 0x.
```

## Source note 5, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L232)

```text
// Helper entries are emitted, but have no standalone test spec.
```

## Source note 6, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L269)

```text
// SO, OV and CA are bits 31, 30 and 29
```

## Source note 7, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L319)

```text
// Labels named one per line ("#" comments allowed), e.g. Edge's skip.txt.
```

## Source note 8, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L320)

```text
// With `with_reason`, the rest of a line after the label is kept.
```

## Source note 9, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L347)

```text
// A file's cases as ppc_table data (ppc_table_runner.h) and one TEST_CASE
```

## Source note 10, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L348)

```text
// that runs them. Each case carries its known failure cause, or nullptr.
```

## Source note 11, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L353)

```text
// Some captures already carry a suffix ("0x...ull").
```

## Source note 12, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L358)

```text
// u32[3], u32[2] in the high half; u32[1], u32[0] in the low half.
```

## Source note 13, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L437)

```text
// Output split over this many function and case files, so a large corpus
```

## Source note 14, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L438)

```text
// compiles in parallel; 1 writes ppc_test_functions.cpp and
```

## Source note 15, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L439)

```text
// ppc_test_cases.cpp as before.
```

## Source note 16, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L441)

```text
// test labels left out (captures judged wrong)
```

## Source note 17, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L442)

```text
// labels expected to fail, each with its cause
```

## Source note 18, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L443)

```text
// Cases as data run from one loop per file (ppc_table_runner.h), for a
```

## Source note 19, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L444)

```text
// corpus too large for a Catch2 test per case.
```

## Source note 20, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L531)

```text
// Each file's labels name its own functions: files reuse labels (both
```

## Source note 21, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L532)

```text
// instr_vcmpbfp.s and instr_vcmpxxfp.s have test_vcmpbfp_1).
```

## Source note 22, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L572)

```text
// Edge's skip.txt names labels without their "test_" prefix.
```

## Source note 23, line 583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L583)

```text
// Catch2 reports a known failure that passes, so a fix shows too.
```

## Source note 24, line 584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/test_recompiler.cpp#L584)

```text
// Keyed "stem/label": files reuse labels.
```
