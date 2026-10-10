# Fpscr: core source notes

This record preserves technical and API notes moved from `include/rex/platform/fpscr.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L20)

```text
// SSE3 constants are missing from simde
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L27)

```text
// simde does not handle denormal flags, so we need to implement per-arch.
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L34)

```text
// Exception mask bits (1 = exception masked/disabled)
```

## Source note 4, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L35)

```text
// IM - Invalid operation
```

## Source note 5, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L36)

```text
// DM - Denormal operand
```

## Source note 6, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L37)

```text
// ZM - Zero divide
```

## Source note 7, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L38)

```text
// OM - Overflow
```

## Source note 8, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L39)

```text
// UM - Underflow
```

## Source note 9, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L40)

```text
// PM - Precision (Inexact)
```

## Source note 10, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L49)

```text
// Set mask bits to disable exceptions
```

## Source note 11, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L59)

```text
// FZ and FZ16
```

## Source note 12, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L61)

```text
// Nearest, Zero, -Infinity, -Infinity
```

## Source note 13, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L64)

```text
// Exception enable bits (0 = exception disabled, ARM defaults to 0)
```

## Source note 14, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L65)

```text
// IOE - Invalid Operation
```

## Source note 15, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L66)

```text
// DZE - Division by Zero
```

## Source note 16, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L67)

```text
// OFE - Overflow
```

## Source note 17, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L68)

```text
// UFE - Underflow
```

## Source note 18, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L69)

```text
// IXE - Inexact
```

## Source note 19, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L70)

```text
// IDE - Input Denormal
```

## Source note 20, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/fpscr.h#L81)

```text
// Clear enable bits to disable exceptions
```
