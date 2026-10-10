# Clock: core source notes

This record preserves technical and API notes moved from `src/core/clock.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L27)

```text
// Time scalar applied to all time operations.
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L29)

```text
// Tick frequency of guest.
```

## Source note 3, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L31)

```text
// Base FILETIME of the guest system from app start.
```

## Source note 4, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L33)

```text
// Combined time and frequency ratio between host and guest.
```

## Source note 5, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L34)

```text
// Split in numerator (first) and denominator (second).
```

## Source note 6, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L35)

```text
// Computed by RecomputeGuestTickScalar.
```

## Source note 7, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L38)

```text
// Native guest ticks.
```

## Source note 8, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L40)

```text
// Last sampled host tick count.
```

## Source note 9, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L42)

```text
// Mutex to ensure last_host_tick_count_ and last_guest_tick_count_ are in sync
```

## Source note 10, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L46)

```text
// Create a rational number with numerator (first) and denominator (second)
```

## Source note 11, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L48)

```text
// Doing it this way ensures we don't mess up our frequency scaling and
```

## Source note 12, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L49)

```text
// precisely controls the precision the guest_time_scalar_ can have.
```

## Source note 13, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L57)

```text
// Keep this a rational calculation and reduce the fraction
```

## Source note 14, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L64)

```text
// Update the guest timer for all threads.
```

## Source note 15, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L65)

```text
// Return a copy of the value so locking is reduced.
```

## Source note 16, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L70)

```text
// Nothing to update, calculate on the fly
```

## Source note 17, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L76)

```text
// Translate host tick count to guest tick count.
```

## Source note 18, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L85)

```text
// Wait until another thread has finished updating the clock.
```

## Source note 19, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L91)

```text
// Offset of the current guest system file time relative to the guest base time.
```

## Source note 20, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L99)

```text
// 100ns/10MHz resolution
```

## Source note 21, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L179)

```text
// Time is fixed to host time.
```

## Source note 22, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L183)

```text
// Query the filetime offset to calculate a new base time.
```

## Source note 23, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L213)

```text
// Absolute time.
```

## Source note 24, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/clock.cpp#L219)

```text
// Relative time.
```
