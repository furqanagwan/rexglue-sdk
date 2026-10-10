# Chrono test: core source notes

This record preserves technical and API notes moved from `tests/unit/core/chrono_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L23)

```text
// Known FILETIME constants
```

## Source note 2, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L26)

```text
// All values are 100-nanosecond intervals since 1601-01-01 00:00:00 UTC.
```

## Source note 3, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L27)

```text
// 1601-01-01
```

## Source note 4, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L28)

```text
// 1970-01-01
```

## Source note 5, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L29)

```text
// 2000-01-01
```

## Source note 6, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L30)

```text
// 2000-02-29
```

## Source note 7, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L31)

```text
// 2020-12-30 12:00:12.345
```

## Source note 8, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L32)

```text
// 2021-01-01
```

## Source note 9, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L35)

```text
// Section 1: Epoch Constant Validation
```

## Source note 10, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L39)

```text
// 369 years from 1601 to 1970, with 89 leap days
```

## Source note 11, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L42)

```text
// unix_epoch_delta() computes dynamically from date types
```

## Source note 12, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L43)

```text
// The delta should be negative (1601 is before 1970)
```

## Source note 13, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L49)

```text
// Section 2: FILETIME Round-Trip
```

## Source note 14, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L62)

```text
// ~year 9999
```

## Source note 15, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L76)

```text
// Section 3: to_sys / from_sys with Known Values
```

## Source note 16, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L84)

```text
// system_clock epoch is 1970-01-01, so time_since_epoch should be zero
```

## Source note 17, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L91)

```text
// 2000-01-01 is 10957 days after 1970-01-01 (including leap days)
```

## Source note 18, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L97)

```text
// 2021-01-01 is 18628 days after 1970-01-01
```

## Source note 19, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L103)

```text
// Use values aligned to system_clock precision (whole seconds)
```

## Source note 20, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L114)

```text
// Section 4: Calendar Decomposition (mirrors RtlTimeToTimeFields)
```

## Source note 21, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L117)

```text
// Helper struct matching the fields extracted in RtlTimeToTimeFields_entry
```

## Source note 22, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L122)

```text
// c_encoding: 0=Sun..6=Sat
```

## Source note 23, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L129)

```text
// Decompose a FILETIME exactly as RtlTimeToTimeFields_entry does
```

## Source note 24, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L221)

```text
// Section 5: Calendar Recomposition (mirrors RtlTimeFieldsToTime)
```

## Source note 25, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L224)

```text
// Recompose fields to FILETIME exactly as RtlTimeFieldsToTime_entry does
```

## Source note 26, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L258)

```text
// Feb 30 - never valid
```

## Source note 27, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L262)

```text
// Month 13 - invalid month
```

## Source note 28, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L266)

```text
// Day 0 - invalid day
```

## Source note 29, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L270)

```text
// Feb 29 in non-leap year
```

## Source note 30, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L274)

```text
// Feb 29 in leap year - valid
```

## Source note 31, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L278)

```text
// Century non-leap: 1900 is not a leap year
```

## Source note 32, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L282)

```text
// 400-year leap: 2000 is a leap year (already checked above, but explicit)
```

## Source note 33, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L296)

```text
// Section 6: Weekday c_encoding Edge Cases
```

## Source note 34, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L302)

```text
// Verify the full range of c_encoding values using known days
```

## Source note 35, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L303)

```text
// 2000-01-02 is Sunday (0)
```

## Source note 36, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L305)

```text
// 1601-01-01 is Monday (1)
```

## Source note 37, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L307)

```text
// 2000-02-29 is Tuesday (2)
```

## Source note 38, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L309)

```text
// 2020-12-30 is Wednesday (3)
```

## Source note 39, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L311)

```text
// 1970-01-01 is Thursday (4)
```

## Source note 40, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L313)

```text
// 2021-01-01 is Friday (5)
```

## Source note 41, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/chrono_test.cpp#L315)

```text
// 2000-01-01 is Saturday (6)
```
