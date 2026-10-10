# Zpd fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/zpd_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L31)

```text
// D3D's pending marker, written big-endian to ZPass_A of the END report
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L32)

```text
// before the event and polled until the GPU overwrites it.
```

## Source note 3, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L37)

```text
// Otherwise draws are dropped while their pipelines compile.
```

## Source note 4, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L42)

```text
// One sample counter report, as D3D reserves it.
```

## Source note 5, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L49)

```text
// EVENT_WRITE_ZPD at report. D3D marks the report it will wait on (the END of
```

## Source note 6, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L50)

```text
// a conventional query) with the pending sentinel first.
```

## Source note 7, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L83)

```text
// The ROV render target path, where the pixel shaders count samples. WARP's
```

## Source note 8, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L84)

```text
// ROV draws don't complete, and some adapters have no ROVs, so those skip.
```

## Source note 9, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L99)

```text
// Waits for the command processor to write the awaited report back. Reports
```

## Source note 10, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L100)

```text
// retire in stream order, so every earlier one is final too.
```

## Source note 11, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L115)

```text
// The guest's END - BEGIN, in 32-bit arithmetic as D3D does it.
```

## Source note 12, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L129)

```text
// Drawn outside any query; must not be counted.
```

## Source note 13, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L140)

```text
// Host queries count ZPass only: Total is ZPass and nothing fails.
```

## Source note 14, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L157)

```text
// Issue, draw, Issue, Issue, draw, draw, Issue: N intervals from N + 1
```

## Source note 15, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L158)

```text
// snapshots of one running counter.
```

## Source note 16, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L181)

```text
// Color after the depth buffer in EDRAM rather than aliasing it.
```

## Source note 17, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L196)

```text
// Behind the depth buffer everywhere: fully occluded.
```

## Source note 18, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L201)

```text
// In front, over a quarter of the target.
```

## Source note 19, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L224)

```text
// The command processor goes idle and submits, closing the host query; the
```

## Source note 20, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L225)

```text
// next draw opens a new segment for the same report.
```

## Source note 21, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L243)

```text
// The same two reports for every query, as titles reuse query objects; the
```

## Source note 22, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L244)

```text
// host slots of each round are released and handed out again in the next.
```

## Source note 23, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L265)

```text
// No color writes and no depth/stencil writes: the draw has no pixel shader
```

## Source note 24, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L266)

```text
// and writes nothing, as occlusion-only proxies do (4541096E, 5553083B).
```

## Source note 25, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L296)

```text
// Host samples, as Canary reports them; not verified against a console.
```

## Source note 26, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L313)

```text
// Written at the event without waiting: never the sentinel, never occluded.
```

## Source note 27, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L317)

```text
// Later submissions retire the report and write the real count over the
```

## Source note 28, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L318)

```text
// guess. Draws after the last event don't belong to the measured interval.
```

## Source note 29, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L343)

```text
// query_occlusion_fake_sample_count, whatever was drawn.
```

## Source note 30, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L363)

```text
// Before RG-GDK-010a, ROV reported query_occlusion_fake_sample_count here.
```

## Source note 31, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L404)

```text
// Without full counters the failures are not counted.
```

## Source note 32, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L431)

```text
// Behind everywhere: every sample fails depth.
```

## Source note 33, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L436)

```text
// Behind as well, and the stencil test never passes: a sample failing both
```

## Source note 34, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L437)

```text
// counts once, as a stencil failure.
```

## Source note 35, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L445)

```text
// In front, no stencil: passes.
```

## Source note 36, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L487)

```text
// Each query releases its slot at resolve, and the next one takes it back.
```

## Source note 37, line 513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L513)

```text
// The same host sample count as the host render target path.
```

## Source note 38, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L519)

```text
// Host render targets with occlusion_query_full_counters: queries around depth
```

## Source note 39, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L520)

```text
// or stencil tested draws without depth writes are hybrid, with ZPass from the
```

## Source note 40, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L521)

```text
// D3D12 query and Total counted in the pixel shaders (xenia-canary PR #1218).
```

## Source note 41, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L540)

```text
// A 32x32 depth buffer at z 0.5, and options for tested draws without depth
```

## Source note 42, line 541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L541)

```text
// writes.
```

## Source note 43, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L572)

```text
// Behind everywhere: every sample fails depth.
```

## Source note 44, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L577)

```text
// Behind, and the stencil test never passes. Host render targets can't
```

## Source note 45, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L578)

```text
// tell stencil from depth failures, so both are ZFail.
```

## Source note 46, line 585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L585)

```text
// In front: passes.
```

## Source note 47, line 617

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L617)

```text
// No color writes: an occlusion-only proxy drawn without a pixel shader, so
```

## Source note 48, line 618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L618)

```text
// the counting depth-only shader stands in for it.
```

## Source note 49, line 650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L650)

```text
// A depth-writing draw keeps early depth rejection and only counts ZPass:
```

## Source note 50, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L651)

```text
// half of it is in front.
```

## Source note 51, line 657

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/zpd_fixture_test.cpp#L657)

```text
// Then, in the same interval, a hybrid draw behind the untouched half.
```
