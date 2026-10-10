# Fp test: ppc source notes

This record preserves technical and API notes moved from `tests/unit/ppc/fp_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 1

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L1)

```text
/**
 * Tests for the PowerPC floating-point rules in rex/ppc/fp.h that the PPC
 * corpus doesn't cover (RG-GDK-055). The corpus covers the arithmetic.
 */
```

## Source note 2, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L44)

```text
// Single SNaN 0x7F800001 widens to 0x7FF0000020000000, quiet bit clear.
```

## Source note 3, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L47)

```text
// A quiet NaN stays quiet, and ordinary values convert as before.
```

## Source note 4, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L126)

```text
// 1 + 2 is exact: nothing raised.
```

## Source note 5, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L129)

```text
// 0.1 + 0.2 is inexact: FX alone.
```

## Source note 6, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L132)

```text
// inf - inf is invalid: FX and VX, and the default QNaN.
```

## Source note 7, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L145)

```text
// Inexact is sticky and sets FX when the cause flag first changes.
```

## Source note 8, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L154)

```text
// An invalid operation records its PowerPC subcause and invalid summary.
```

## Source note 9, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L166)

```text
// An enabled invalid exception leaves the result fields unchanged.
```

## Source note 10, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L173)

```text
// FEX reflects the corresponding enable and clears when the enabled cause is cleared.
```

## Source note 11, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L263)

```text
// Guest code with VMX flush on and rounding toward zero calls an export.
```

## Source note 12, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L273)

```text
// The export calls back into guest code, which switches to rounding
```

## Source note 13, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L274)

```text
// down.
```

## Source note 14, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/ppc/fp_test.cpp#L281)

```text
// Back in guest code: the callback's rounding mode, and the cache agrees.
```
