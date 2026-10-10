# Chrono: core source notes

This record preserves technical and API notes moved from `include/rex/chrono/chrono.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L28)

```text
// Implementation detail: NtSystemClock template for Host/Guest time domains.
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L29)

```text
// Trick to reduce code duplication and keep all the chrono template magic
```

## Source note 3, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L30)

```text
// working.
```

## Source note 4, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L32)

```text
// boring host clock:
```

## Source note 5, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L34)

```text
// adheres to guest scaling (differrent speed, changing clock drift etc):
```

## Source note 6, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L44)

```text
// This really depends on the context the clock is used in:
```

## Source note 7, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L45)

```text
// static constexpr bool is_steady = false;
```

## Source note 8, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L48)

```text
// The delta between std::chrono::system_clock (Jan 1 1970) and NT file
```

## Source note 9, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L49)

```text
// time (Jan 1 1601), in seconds. In the spec std::chrono::system_clock's
```

## Source note 10, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L50)

```text
// epoch is undefined, but C++20 cements it as Jan 1 1970.
```

## Source note 11, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L71)

```text
// To convert XSystemClock to sys, do clock_cast<WinSystemTime>(tp) first
```

## Source note 12, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L72)

```text
// Only available for Host domain (Guest time must be converted via clock_cast)
```

## Source note 13, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L96)

```text
// QueryHostSystemTime() returns windows epoch times even on POSIX
```

## Source note 14, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L105)

```text
// Unscaled system clock which can be used for filetime <-> system_clock
```

## Source note 15, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L109)

```text
// Guest system clock, scaled
```

## Source note 16, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L125)

```text
// Consult chrono_steady_cast.h for explanation on this:
```

## Source note 17, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono.h#L148)

```text
// Consult chrono_steady_cast.h for explanation on this:
```
