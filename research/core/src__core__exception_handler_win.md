# Exception handler win: core source notes

This record preserves technical and API notes moved from `src/core/exception_handler_win.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L22)

```text
// Handle of the added VectoredExceptionHandler.
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L24)

```text
// Handle of the added VectoredContinueHandler.
```

## Source note 3, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L27)

```text
// This can be as large as needed, but isn't often needed.
```

## Source note 4, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L28)

```text
// As we will be sometimes firing many exceptions we want to avoid having to
```

## Source note 5, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L29)

```text
// scan the table too much or invoke many custom handlers.
```

## Source note 6, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L32)

```text
// All custom handlers, left-aligned and null terminated.
```

## Source note 7, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L33)

```text
// Executed in order.
```

## Source note 8, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L37)

```text
// Visual Studio SetThreadName.
```

## Source note 9, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L50)

```text
// https://msdn.microsoft.com/en-us/library/ms679331(v=vs.85).aspx
```

## Source note 10, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L51)

```text
// https://msdn.microsoft.com/en-us/library/aa363082(v=vs.85).aspx
```

## Source note 11, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L75)

```text
// Unknown/unhandled type.
```

## Source note 12, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L79)

```text
// The handlers (MMIO, the GPU's register writes) are host code, but the
```

## Source note 13, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L80)

```text
// faulting thread may be in the guest's rounding and flush mode. Continuing
```

## Source note 14, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L81)

```text
// restores the context record's own control register.
```

## Source note 15, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler_win.cpp#L97)

```text
// Exception handled.
```
