# Interpreter: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/interpreter.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L41)

```text
// Scalar approximation results, reduced when gpu_scalar_approximation_rounding
```

## Source note 2, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L42)

```text
// is enabled, as the translated shaders do.
```

## Source note 3, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L50)

```text
// For more consistency between invocations in case of a malformed shader.
```

## Source note 4, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L123)

```text
// Not supporting texture fetching (very complex).
```

## Source note 5, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L216)

```text
// No stack depth assertion - skipping the return is a well-defined
```

## Source note 6, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L217)

```text
// behavior for `return` outside a function call.
```

## Source note 7, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L285)

```text
// Vector operation.
```

## Source note 8, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L336)

```text
// Direct3D 9 behavior (0 or denormal * anything = +0).
```

## Source note 9, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L394)

```text
// Direct3D 9 behavior (0 or denormal * anything = +0).
```

## Source note 10, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L395)

```text
// Doing the addition rather than conditional assignment even for zero
```

## Source note 11, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L396)

```text
// operands because +0 + -0 must be +0.
```

## Source note 12, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L425)

```text
// Direct3D 9 behavior (0 or denormal * anything = +0).
```

## Source note 13, line 426

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L426)

```text
// Doing the addition even for zero operands because +0 + -0 must be
```

## Source note 14, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L427)

```text
// +0.
```

## Source note 15, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L437)

```text
// Direct3D 9 behavior (0 or denormal * anything = +0).
```

## Source note 16, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L438)

```text
// Doing the addition even for zero operands because +0 + -0 must be
```

## Source note 17, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L439)

```text
// +0.
```

## Source note 18, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L447)

```text
// Doing the addition even for zero operands because +0 + -0 must be +0.
```

## Source note 19, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L450)

```text
// Direct3D 9 behavior (0 or denormal * anything = +0).
```

## Source note 20, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L459)

```text
// Operand [0] is .z_xy.
```

## Source note 21, line 464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L464)

```text
// Result is T coordinate, S coordinate, 2 * major axis, face ID.
```

## Source note 22, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L533)

```text
// Not implementing pixel kill currently, the interpreter is currently
```

## Source note 23, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L534)

```text
// used only for vertex shaders.
```

## Source note 24, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L566)

```text
// Direct3D 9 behavior (0 or denormal * anything = +0).
```

## Source note 25, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L593)

```text
// Scalar operation.
```

## Source note 26, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L602)

```text
// r#/c#.w or r#/c#.wx.
```

## Source note 27, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L630)

```text
// c#.w.
```

## Source note 28, line 634

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L634)

```text
// r#.x.
```

## Source note 29, line 661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L661)

```text
// Direct3D 9 behavior (0 or denormal * anything = +0).
```

## Source note 30, line 668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L668)

```text
// Direct3D 9 behavior (0 or denormal * anything = +0).
```

## Source note 31, line 674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L674)

```text
// Step back if the float multiply rounded away from zero.
```

## Source note 32, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L683)

```text
// Direct3D 9 behavior (0 or denormal * anything = +0).
```

## Source note 33, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L693)

```text
// Direct3D 9 behavior (0 or denormal * anything = +0).
```

## Source note 34, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L836)

```text
// Not implementing pixel kill currently, the interpreter is currently used
```

## Source note 35, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L837)

```text
// only for vertex shaders.
```

## Source note 36, line 947

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L947)

```text
// ucode::FetchDestinationSwizzle::k0 or the invalid swizzle 6.
```

## Source note 37, line 965

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L965)

```text
// Get the part of the address that depends on vfetch_full data.
```

## Source note 38, line 1078

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L1078)

```text
// No need to clamp to -1 if signed - the smallest value will be
```

## Source note 39, line 1079

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/interpreter.cpp#L1079)

```text
// -2^23 / 2^23 due to rounding.
```
