# Codegen writer test: codegen source notes

This record preserves technical and API notes moved from `tests/unit/codegen/codegen_writer_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/codegen_writer_test.cpp#L40)

```text
// Big-endian `blr` (0x4E800020), one instruction per test function.
```

## Source note 2, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/codegen_writer_test.cpp#L50)

```text
/// Whole-file contents, for asserting on emitted text.
```

## Source note 3, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/codegen_writer_test.cpp#L56)

```text
/// Fake module, context with a sealed function per `blr`, scratch output tree.
```

## Source note 4, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/codegen_writer_test.cpp#L220)

```text
// Touches init.h, init.cpp, register.cpp and one recomp file, not sources.cmake.
```

## Source note 5, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/codegen_writer_test.cpp#L279)

```text
// A call may precede its own definition, so being defined here is no excuse.
```
