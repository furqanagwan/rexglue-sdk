# Floating point: codegen source notes

This record preserves technical and API notes moved from `src/codegen/builders/floating_point.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/floating_point.cpp#L19)

```text
/**
 * Emit frD = rex::ppc::fp::<fn>(operands...) for an arithmetic instruction.
 *
 * The helpers in rex/ppc/fp.h apply PowerPC's NaN and denormal rules. A record
 * form (fadd. ...) also sets CR1 from the exceptions the operation raised.
 * `causes` classifies invalid-operation subcauses not exposed by host fenv;
 * `quiet` reports nothing raised for a single-precision denormal operand.
 */
```

## Source note 2, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/floating_point.cpp#L67)

```text
/// fctiw/fctiwz/fctid/fctidz, with CR1 for the record forms.
```

## Source note 3, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/floating_point.cpp#L79)

```text
// Sign Manipulation
```

## Source note 4, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/floating_point.cpp#L104)

```text
// Move and Conversion
```

## Source note 5, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/floating_point.cpp#L233)

```text
// Fused Multiply-Add
```

## Source note 6, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/floating_point.cpp#L285)

```text
// Reciprocal and Square Root
```
