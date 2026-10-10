# Timer resolution test: core source notes

This record preserves technical and API notes moved from `tests/unit/core/timer_resolution_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/timer_resolution_test.cpp#L19)

```text
// 1 ms or finer (Windows reports 0.5 ms)
```

## Source note 2, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/timer_resolution_test.cpp#L21)

```text
// Without it, each of these took 15.6 ms.
```
