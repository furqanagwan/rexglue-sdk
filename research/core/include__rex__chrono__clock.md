# Clock: core source notes

This record preserves technical and API notes moved from `include/rex/chrono/clock.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L24)

```text
// Raw clock source requires platform-specific implementation
```

## Source note 2, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L25)

```text
// Disable for now - use platform clock functions instead
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L33)

```text
// Host ticks-per-second. Generally QueryHostTickFrequency should be used.
```

## Source note 4, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L34)

```text
// Either from platform suplied time source or from hardware directly.
```

## Source note 5, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L39)

```text
// Host tick count. Generally QueryHostTickCount() should be used.
```

## Source note 6, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L45)

```text
// Queries the host tick frequency.
```

## Source note 7, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L47)

```text
// Queries the current host tick count.
```

## Source note 8, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L49)

```text
// Host time, in FILETIME format.
```

## Source note 9, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L51)

```text
// Queries the milliseconds since the host began.
```

## Source note 10, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L54)

```text
// Guest time scalar.
```

## Source note 11, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L56)

```text
// Sets the guest time scalar, adjusting tick and wall clock speed.
```

## Source note 12, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L57)

```text
// Ex: 1x=normal, 2x=double speed, 1/2x=half speed.
```

## Source note 13, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L59)

```text
// Get the tick ration between host and guest including time scaling if set.
```

## Source note 14, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L61)

```text
// Guest ticks-per-second.
```

## Source note 15, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L63)

```text
// Sets the guest ticks-per-second.
```

## Source note 16, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L65)

```text
// Time based used for the guest system time.
```

## Source note 17, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L67)

```text
// Sets the guest time base, used for computing the system time.
```

## Source note 18, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L68)

```text
// By default this is the current system time.
```

## Source note 19, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L71)

```text
// Queries the current guest tick count, accounting for frequency adjustment
```

## Source note 20, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L72)

```text
// and scaling.
```

## Source note 21, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L74)

```text
// Queries the guest time, in FILETIME format, accounting for scaling.
```

## Source note 22, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L76)

```text
// Queries the milliseconds since the guest began, accounting for scaling.
```

## Source note 23, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L79)

```text
// Sets the system time of the guest.
```

## Source note 24, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L82)

```text
// Scales a time duration in milliseconds, from guest time.
```

## Source note 25, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L84)

```text
// Scales a time duration in 100ns ticks like FILETIME, from guest time.
```

## Source note 26, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/clock.h#L86)

```text
// Scales a time duration represented as a timeval, from guest time.
```
