# Memexport fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/memexport_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L34)

```text
// vfetch r1 from vf0 by the vertex index in r0.x; oPos = r1; then
```

## Source note 2, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L35)

```text
//   mad eA, r0.xxxx, c1, c2   (c1 = 0, 1, 0, 0 - the index into eA.y)
```

## Source note 3, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L36)

```text
//   max eM0, c3, c3           (the exported value)
```

## Source note 4, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L37)

```text
// so every vertex exports c3 to stream c2 at its own index.
```

## Source note 5, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L43)

```text
// 3: vfetch r1.xyzw, r0.x, vf0 (as in the shared vertex shader).
```

## Source note 6, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L45)

```text
// 4: max oPos, r1, r1.
```

## Source note 7, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L48)

```text
// 5: mad eA, r0.xxxx, c1, c2.
```

## Source note 8, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L51)

```text
// 6: max eM0, c3, c3.
```

## Source note 9, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L60)

```text
// The stream constant for `index_count` k_32_32_32_32_FLOAT elements at
```

## Source note 10, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L61)

```text
// `address`, big-endian as the guest reads it back.
```

## Source note 11, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L80)

```text
// Deterministic: the exported data is read
```

## Source note 12, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L81)

```text
// back after the draw, not a frame later.
```

## Source note 13, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L85)

```text
// A 16x8 rectangle drawn without a pixel shader, exporting `value` for each of
```

## Source note 14, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L86)

```text
// its four vertices to `stream`.
```

## Source note 15, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L101)

```text
// Samples drawn by one 16x8 rectangle from the vertices at `vertices`, counted
```

## Source note 16, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L102)

```text
// with a strict occlusion query.
```

## Source note 17, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L135)

```text
// Rectangle vertices in the layout the shared vertex shader fetches: x, y, z,
```

## Source note 18, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L136)

```text
// w per vertex, triangle strip order.
```

## Source note 19, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L159)

```text
// GPU write, CPU read.
```

## Source note 20, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L170)

```text
// CPU write over the GPU-written pages, then GPU reuse as vertex data: the
```

## Source note 21, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L171)

```text
// draw must see the CPU's rectangle, not the exported values (which would be
```

## Source note 22, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L172)

```text
// a degenerate triangle strip at one point).
```

## Source note 23, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L173)

```text
// Control: the same vertices from memory the GPU never wrote.
```

## Source note 24, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L189)

```text
// Starts in the last page of the 512 MB and runs 16 KB past its end.
```

## Source note 25, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L193)

```text
// The command processor carries on: a valid export after it lands.
```

## Source note 26, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L209)

```text
// As in 5451087D (xenia-canary #1093): the stream's index count describes
```

## Source note 27, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L210)

```text
// far more than the allocation its base is in, so it runs into pages that
```

## Source note 28, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L211)

```text
// aren't allocated.
```

## Source note 29, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L217)

```text
// Whatever the policy for the unallocated tail, the allocated head is
```

## Source note 30, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L218)

```text
// written and the command processor is still running.
```

## Source note 31, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L227)

```text
// Translation on the creation threads racing first use and cache hits on the
```

## Source note 32, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L228)

```text
// processor thread (has207/xenia-edge 462a1ac85), then teardown with creation
```

## Source note 33, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L229)

```text
// still in flight. Each round loads unseen pixel shaders; the draws without a
```

## Source note 34, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L230)

```text
// pixel shader translate the shared vertex shader on the processor thread
```

## Source note 35, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L231)

```text
// while a creation thread may be translating it for a pipeline.
```

## Source note 36, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L243)

```text
// max oC0, c#, c# - a distinct pixel shader per constant.
```

## Source note 37, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L250)

```text
// Same vertex shader, no pixel shader: translated synchronously.
```

## Source note 38, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/memexport_fixture_test.cpp#L254)

```text
// Only the first rounds wait; the last tears down with creation queued.
```
