# Fiber test: core source notes

This record preserves technical and API notes moved from `tests/unit/core/fiber_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/fiber_test.cpp#L17)

```text
// Globals - fiber entry functions cannot capture closures.
```

## Source note 2, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/fiber_test.cpp#L22)

```text
// first resume
```

## Source note 3, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/fiber_test.cpp#L24)

```text
// second resume
```

## Source note 4, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/fiber_test.cpp#L35)

```text
// fiber ran, switched back
```

## Source note 5, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/fiber_test.cpp#L37)

```text
// fiber resumed, ran again, switched back
```

## Source note 6, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/fiber_test.cpp#L39)

```text
// NOTE: Cleanup is not exception-safe. If a REQUIRE above fires, Catch2
```

## Source note 7, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/fiber_test.cpp#L40)

```text
// throws and these Destroy() calls are skipped, leaking the host fiber
```

## Source note 8, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/fiber_test.cpp#L41)

```text
// handles. Acceptable for a test-only scenario; fix if spurious failures occur.
```
