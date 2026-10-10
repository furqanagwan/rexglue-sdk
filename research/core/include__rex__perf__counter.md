# Counter: core source notes

This record preserves technical and API notes moved from `include/rex/perf/counter.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L52)

```text
// sentinel -- must be last
```

## Source note 2, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L55)

```text
// Returns human-readable name for a counter (e.g. "frame_time_us")
```

## Source note 3, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L58)

```text
// Set a counter to an absolute value
```

## Source note 4, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L61)

```text
// Atomically add to a counter
```

## Source note 5, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L64)

```text
// Read a counter's current live value
```

## Source note 6, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L67)

```text
// Snapshot current values into the read buffer and zero the live counters.
```

## Source note 7, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L68)

```text
// Called once per frame by Profiler::Flip().
```

## Source note 8, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L71)

```text
// Read a counter from the last-frame snapshot (stable between frames).
```

## Source note 9, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L74)

```text
// Initialize the counter system (zeroes everything). Safe to call multiple times.
```

## Source note 10, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L77)

```text
// CSV logging
```

## Source note 11, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L82)

```text
// Profiler -- coordinates Tracy frame marks and counter snapshots.
```

## Source note 12, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L83)

```text
// Moved here from rex::debug to consolidate all perf code under rex::perf.
```

## Source note 13, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L135)

```text
// Perf counter macros -- compile to no-ops when counters are disabled.
```

## Source note 14, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L138)

```text
// Generic helpers for easily adding new counters
```

## Source note 15, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/perf/counter.h#L143)

```text
// Purpose-specific macros so callsites stay clean
```
