# Code emitter: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/code_emitter.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L21)

```text
// Forward declarations
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L24)

```text
/**
 * @brief CSR (Control/Status Register) state for FPU denormal handling.
 *
 * Tracks MXCSR configuration:
 * - Unknown: Initial or after function call
 * - Fpu: Denormals preserved (scalar FP)
 * - Vmx: Denormals flushed (vector FP)
 */
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L33)

```text
// Need to check/set on next FP instruction
```

## Source note 4, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L34)

```text
// Flush mode disabled (scalar FP)
```

## Source note 5, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L35)

```text
// Flush mode enabled (vector FP)
```

## Source note 6, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L38)

```text
/**
 * @brief Abstract interface for C++ code emission.
 *
 * Provides indentation management, formatted output, and CSR state tracking.
 * Implementations can write to strings, files, or streams.
 *
 * Example:
 * @code
 * StringEmitter emit;
 * emit.line("void foo() {{");
 * emit.indent();
 * emit.line("int x = {};", 42);
 * emit.dedent();
 * emit.line("}}");
 * @endcode
 */
```

## Source note 7, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L62)

```text
/// Increase indentation level
```

## Source note 8, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L65)

```text
/// Decrease indentation level
```

## Source note 9, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L68)

```text
/// Get current indentation string
```

## Source note 10, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L75)

```text
/// Write raw string (no indentation, no newline)
```

## Source note 11, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L78)

```text
/// Write formatted line with indentation and newline
```

## Source note 12, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L86)

```text
/// Write empty line
```

## Source note 13, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L89)

```text
/// Write comment line
```

## Source note 14, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L98)

```text
// CSR State Management
```

## Source note 15, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L101)

```text
/// Get current CSR state
```

## Source note 16, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L104)

```text
/// Set CSR state (called when mode is established)
```

## Source note 17, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L107)

```text
/// Ensure CSR is in required state, emitting code if needed
```

## Source note 18, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L110)

```text
/// Reset CSR state to Unknown (call after function calls)
```

## Source note 19, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L117)

```text
/**
 * @brief CodeEmitter that writes to a string buffer.
 *
 * Useful for tests and building function bodies before output.
 */
```

## Source note 20, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L141)

```text
/// Get the accumulated output
```

## Source note 21, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L144)

```text
/// Clear the buffer
```

## Source note 22, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_emitter.h#L147)

```text
/// Move the buffer out
```
