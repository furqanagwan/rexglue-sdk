# Function dispatcher test: system source notes

This record preserves technical and API notes moved from `tests/unit/system/function_dispatcher_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/function_dispatcher_test.cpp#L63)

```text
// caller_address=0 is reserved for host-initiated allocations that have no
```

## Source note 2, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/function_dispatcher_test.cpp#L64)

```text
// guest caller (the entrypoint wiring its own __imp__* exports during
```

## Source note 3, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/function_dispatcher_test.cpp#L65)

```text
// setup). It must land in the entrypoint module's pool.
```

## Source note 4, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/function_dispatcher_test.cpp#L75)

```text
/*is_entrypoint=*/
```

## Source note 5, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/function_dispatcher_test.cpp#L109)

```text
// A non-zero caller_address that doesn't fall inside any module is a bug
```

## Source note 6, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/function_dispatcher_test.cpp#L110)

```text
// in the caller: the right answer is to refuse, not to silently route the
```

## Source note 7, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/function_dispatcher_test.cpp#L111)

```text
// thunk to the entrypoint pool.
```

## Source note 8, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/function_dispatcher_test.cpp#L164)

```text
// Re-init must succeed: UnregisterModule destroys the per-module table so the
```

## Source note 9, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/function_dispatcher_test.cpp#L165)

```text
// same code range can be reloaded without tripping the overlap check.
```

## Source note 10, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/function_dispatcher_test.cpp#L288)

```text
// Distinct bodies, so identical-code folding can't merge them.
```
