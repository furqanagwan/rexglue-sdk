# Xenos zpd report: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/xenos_zpd_report.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L23)

```text
// One EVENT_WRITE_ZPD occlusion query sample counter report.
```

## Source note 2, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L25)

```text
// Z-Pass Done (ZPD) reports are a headache to emulate for a few reasons:
```

## Source note 3, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L27)

```text
// 1. D3D has two ZPD occlusion query APIs, and some titles use both.
```

## Source note 4, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L28)

```text
//    - A conventional query brackets a draw interval within BEGIN and END calls
```

## Source note 5, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L29)

```text
//      then reads the result back with GetData.
```

## Source note 6, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L30)

```text
//    - QueryBatch writes a cumulative counter snapshot for every Issue call.
```

## Source note 7, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L31)

```text
//      Lock readies the snapshot and results are gotten by subtracting adjacent
```

## Source note 8, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L32)

```text
//      slots. So N intervals need N + 1 reports:
```

## Source note 9, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L33)

```text
//        Issue, draw_A, Issue, draw_B, Issue
```

## Source note 10, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L35)

```text
// 2. Xenos doesn't have a hardware counter for each query. EVENT_WRITE_ZPD
```

## Source note 11, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L36)

```text
//    writes the counters to RB_SAMPLE_COUNT_ADDR, and D3D subtracts the BEGIN
```

## Source note 12, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L37)

```text
//    report from the END report in software to get the sample counts. So we
```

## Source note 13, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L38)

```text
//    have to track every interval between writes, including ones that aren't
```

## Source note 14, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L39)

```text
//    bracketed by BEGIN and END.
```

## Source note 15, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L41)

```text
// 3. Each report contains four counters, each with A and B lanes:
```

## Source note 16, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L42)

```text
//    - ZFail: samples that fail depth
```

## Source note 17, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L43)

```text
//    - ZPass: samples that pass depth
```

## Source note 18, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L44)

```text
//    - StencilFail: samples that fail stencil
```

## Source note 19, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L45)

```text
//    - Total: ZFail + ZPass + StencilFail
```

## Source note 20, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L47)

```text
//    D3D sums A and B. The exact meaning of the A/B lane split still isn't
```

## Source note 21, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L48)

```text
//    known. But for every 50 titles that merely ask for the summed ZPass,
```

## Source note 22, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L49)

```text
//    there's one example like 425307EC that masks each lane to 24 bits before
```

## Source note 23, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L50)

```text
//    summing, so we need to evenly split the counts. Samples rejected by hi-Z
```

## Source note 24, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L51)

```text
//    or hi-stencil aren't included in ZFail or StencilFail respectively.
```

## Source note 25, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L53)

```text
// Host occlusion queries can only count ZPass. Canary's in-shader counting of
```

## Source note 26, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L54)

```text
// the other counters (occlusion_query_full_counters and the ROV counter path)
```

## Source note 27, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L55)

```text
// isn't ported yet, so ZFail and StencilFail stay zero and Total equals ZPass.
```

## Source note 28, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L57)

```text
// Lanes of a host counter slot (four uint32 per open query), written by the
```

## Source note 29, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L58)

```text
// ROV pixel shaders.
```

## Source note 30, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L82)

```text
// Native host occlusion query. ZPass only.
```

## Source note 31, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L83)

```text
// A counter slot read back from the host. Total is not stored separately:
```

## Source note 32, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L84)

```text
// it is always the sum of the other three.
```

## Source note 33, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L93)

```text
// Hybrid RTV query: ZPass from the native query, Total from the pixel
```

## Source note 34, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L94)

```text
// shaders (coverage entering the depth / stencil test). The rejected rest
```

## Source note 35, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L95)

```text
// is ZFail: host render targets cannot tell it from StencilFail.
```

## Source note 36, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L109)

```text
// Divides host counts by the draw scale area, rounding to nearest.
```

## Source note 37, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L123)

```text
// Writes the report to guest memory, each counter split across the A and B
```

## Source note 38, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L124)

```text
// lanes. Low 32 bits only, the hardware counters wrap and so do we.
```

## Source note 39, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L125)

```text
// GetData (usually) wakes on the ZPass lanes and QueryBatch Lock on ZPass_A
```

## Source note 40, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos_zpd_report.h#L126)

```text
// or StencilFail_B, so those four are written last, in one copy.
```
