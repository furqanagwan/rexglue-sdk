# Format: system source notes

This record preserves technical and API notes moved from `include/rex/system/format.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L84)

```text
// format_double helper
```

## Source note 2, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L119)

```text
// StackArgList — reads variadic args from PPC registers/stack
```

## Source note 3, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L121)

```text
// For sprintf, _snprintf, DbgPrint, etc. where varargs follow fixed params.
```

## Source note 4, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L122)

```text
// Xbox 360 PPC has 64-bit GPRs. Variadic args in r3-r10, then stack at
```

## Source note 5, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L123)

```text
// r1+0x54 in 8-byte slots.
```

## Source note 6, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L164)

```text
// Stack arguments: 8-byte big-endian values at r1 + 0x54 + ((index - 8) * 8)
```

## Source note 7, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L179)

```text
// ArrayArgList — reads from guest va_list (8-byte-aligned array in memory)
```

## Source note 8, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L181)

```text
// For vsprintf, _vsnprintf, etc. where a va_list pointer is passed.
```

## Source note 9, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L182)

```text
// On Xbox 360, va_list is a pointer to an array of 8-byte-aligned values.
```

## Source note 10, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L203)

```text
// StringFormatData — narrow char format string I/O
```

## Source note 11, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L243)

```text
// WideStringFormatData — wide (char16_t) format string I/O
```

## Source note 12, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L280)

```text
// WideCountFormatData — counts wide output without storing
```

## Source note 13, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L317)

```text
// format_core — printf format string state machine
```

## Source note 14, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L319)

```text
// Reference: https://msdn.microsoft.com/en-us/library/56e442dc.aspx
```

## Source note 15, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L356)

```text
// the end
```

## Source note 16, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L369)

```text
// fall through
```

## Source note 17, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L372)

```text
// in any state, if c is \0, it's bad
```

## Source note 18, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L394)

```text
// reset to defaults
```

## Source note 19, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L409)

```text
// fall through, don't need to goto restart
```

## Source note 20, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L430)

```text
// fall through
```

## Source note 21, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L448)

```text
// fall through
```

## Source note 22, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L475)

```text
// fall through
```

## Source note 23, line 514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L514)

```text
// fall through
```

## Source note 24, line 677

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L677)

```text
// %n: write character count to guest memory
```

## Source note 25, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L742)

```text
// ANSI_STRING / UNICODE_STRING (not implemented)
```

## Source note 26, line 825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/format.h#L825)

```text
// right padding
```
