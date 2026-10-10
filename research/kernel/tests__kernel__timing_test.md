# Timing test: kernel source notes

This record preserves technical and API notes moved from `tests/kernel/timing_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L57)

```text
// A thread object for KeDelayExecutionThread's path; Delay needs no host
```

## Source note 2, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L58)

```text
// thread of its own.
```

## Source note 3, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L95)

```text
// Prints the table in docs/threading-contracts.md:
```

## Source note 4, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L96)

```text
//   kernel_tests "[.timing-report]" -s
```

## Source note 5, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L118)

```text
// The contract: a delay or timed wait never ends before the guest asked, and
```

## Source note 6, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L119)

```text
// with precise timers ends within a few milliseconds of it (the Windows
```

## Source note 7, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L120)

```text
// system timer alone rounds up to 15.6 ms steps). Loose upper bounds keep a
```

## Source note 8, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L121)

```text
// busy machine from failing the test; the report above has the real numbers.
```

## Source note 9, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L134)

```text
// Sub-millisecond delays sleep instead of yielding.
```

## Source note 10, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L142)

```text
// Before RG-GDK-015 an absolute time asserted in Debug and returned at once.
```

## Source note 11, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L144)

```text
// The guest clock's own granularity.
```

## Source note 12, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L146)

```text
// A time already passed is a zero delay.
```

## Source note 13, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L154)

```text
// Sub-millisecond delays truncate to a zero delay, a yield.
```

## Source note 14, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L156)

```text
// Whole milliseconds are never early.
```

## Source note 15, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L164)

```text
// 1 s.
```

## Source note 16, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/timing_test.cpp#L184)

```text
// 2 s.
```
