# Ppc fp: system source notes

This record preserves technical and API notes moved from `src/system/ppc_fp.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/ppc_fp.cpp#L33)

```text
// The estimate for a positive normal single: a coefficient picked by the
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/ppc_fp.cpp#L34)

```text
// exponent's parity and the top mantissa bits, then linear interpolation.
```

## Source note 3, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/ppc_fp.cpp#L56)

```text
// Indexed by exponent parity and the top 14 mantissa bits, built for
```

## Source note 4, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/ppc_fp.cpp#L57)

```text
// exponent 126 or 127; vrsqrte() corrects for the actual exponent.
```
