# Chrono steady cast: core source notes

This record preserves technical and API notes moved from `include/rex/chrono/chrono_steady_cast.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L18)

```text
// This is in a separate header because casting to and from steady time points
```

## Source note 2, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L19)

```text
// usually doesn't make sense and is imprecise. However, NT uses the FileTime
```

## Source note 3, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L20)

```text
// epoch as a steady clock in waits. In such cases, include this header and use
```

## Source note 4, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L21)

```text
// clock_cast<>().
```

## Source note 5, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L25)

```text
// This conveniently works only for Host time domain because Guest needs
```

## Source note 6, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L26)

```text
// additional scaling. Convert XSystemClock to WinSystemClock first if
```

## Source note 7, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L27)

```text
// necessary.
```

## Source note 8, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L30)

```text
// using NtSystemClock_ = ::rex::chrono::internal::NtSystemClock<domain_>;
```

## Source note 9, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L37)

```text
// Since there is no known epoch for steady_clock and even if, since it can
```

## Source note 10, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L38)

```text
// progress differently than other common clocks (e.g. stopping when the
```

## Source note 11, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L39)

```text
// computer is suspended), we need to use now() which introduces
```

## Source note 12, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L40)

```text
// imprecision.
```

## Source note 13, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L41)

```text
// Memory fences to keep the clock fetches close together to
```

## Source note 14, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L42)

```text
// minimize drift. This pattern was benchmarked to give the lowest
```

## Source note 15, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L43)

```text
// conversion error: error = sty_tpoint -
```

## Source note 16, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/chrono/chrono_steady_cast.h#L44)

```text
// clock_cast<sty>(clock_cast<nt>(sty_tpoint));
```
