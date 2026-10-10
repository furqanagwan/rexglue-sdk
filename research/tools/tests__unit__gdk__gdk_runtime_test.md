# Gdk runtime test: tools source notes

This record preserves technical and API notes moved from `tests/unit/gdk/gdk_runtime_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 9

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gdk_runtime_test.cpp#L9)

```text
// SDK headers first, then the GDK, as a title would: both must coexist with
```

## Source note 2, line 10

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gdk_runtime_test.cpp#L10)

```text
// the SDK's NOMINMAX/WIN32_LEAN_AND_MEAN Windows configuration.
```

## Source note 3, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gdk_runtime_test.cpp#L17)

```text
// The GDK headers need the Windows headers first; the SDK headers above do
```

## Source note 4, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gdk_runtime_test.cpp#L18)

```text
// not include them.
```

## Source note 5, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gdk_runtime_test.cpp#L50)

```text
// The command runs inside rexruntime's cvar dispatch, so the exception
```

## Source note 6, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gdk_runtime_test.cpp#L51)

```text
// crosses the DLL boundary on its way back to the test.
```
