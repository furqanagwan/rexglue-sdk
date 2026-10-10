# Gaming runtime test: system source notes

This record preserves technical and API notes moved from `tests/unit/system/gaming_runtime_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/gaming_runtime_test.cpp#L42)

```text
// While `blocked`, initialize waits until Release(): a stalled runtime.
```

## Source note 2, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/gaming_runtime_test.cpp#L55)

```text
// Captures a shared_ptr: a timed-out call outlives the test's GamingRuntime.
```

## Source note 3, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/gaming_runtime_test.cpp#L94)

```text
// Initializing again while ready does not call the runtime again.
```

## Source note 4, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/gaming_runtime_test.cpp#L106)

```text
// The destructor balances the second initialization.
```

## Source note 5, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/gaming_runtime_test.cpp#L159)

```text
// ERROR_FILE_NOT_FOUND, passed through unchanged
```

## Source note 6, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/gaming_runtime_test.cpp#L164)

```text
// The same code without a config path is not blamed on a config file.
```

## Source note 7, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/gaming_runtime_test.cpp#L179)

```text
// No second call is made into a runtime that has not returned.
```

## Source note 8, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/gaming_runtime_test.cpp#L186)

```text
// The next attempt starts fresh once the stalled call is over.
```

## Source note 9, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/gaming_runtime_test.cpp#L201)

```text
// The GamingRuntime is gone before the call returns.
```
