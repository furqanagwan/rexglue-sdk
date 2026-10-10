# Counter: core source notes

This record preserves technical and API notes moved from `src/core/perf/counter.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/perf/counter.cpp#L55)

```text
// Gauge counters are snapshotted but NOT zeroed each frame.
```

## Source note 2, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/perf/counter.cpp#L56)

```text
// Accumulators (everything else) are zeroed after snapshot.
```

## Source note 3, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/perf/counter.cpp#L58)

```text
// kFrameTimeUs       (set each frame)
```

## Source note 4, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/perf/counter.cpp#L59)

```text
// kFps               (set each frame)
```

## Source note 5, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/perf/counter.cpp#L65)

```text
// kBufferQueueDepth  (set each frame)
```

## Source note 6, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/perf/counter.cpp#L68)

```text
// kActiveThreads     (inc/dec over lifetime)
```

## Source note 7, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/perf/counter.cpp#L70)

```text
// kCriticalRegionContentions (running total)
```

## Source note 8, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/perf/counter.cpp#L78)

```text
// CSV state
```

## Source note 9, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/perf/counter.cpp#L83)

```text
// anonymous namespace
```

## Source note 10, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/perf/counter.cpp#L107)

```text
// Gauges: snapshot the current value, don't zero
```

## Source note 11, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/perf/counter.cpp#L110)

```text
// Accumulators: snapshot and zero for next frame
```

## Source note 12, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/perf/counter.cpp#L147)

```text
// Write header
```
