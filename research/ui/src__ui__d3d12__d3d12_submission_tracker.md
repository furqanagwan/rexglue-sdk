# D3d12 submission tracker: ui source notes

This record preserves technical and API notes moved from `src/ui/d3d12/d3d12_submission_tracker.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L26)

```text
// Continue where the tracker was left at the last shutdown.
```

## Source note 2, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L50)

```text
// Not fully initialized yet or already shut down.
```

## Source note 3, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L53)

```text
// The tracker itself can't give a submission index for a submission that
```

## Source note 4, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L54)

```text
// hasn't even started being recorded yet, the client has provided a
```

## Source note 5, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L55)

```text
// completely invalid value or has done overly optimistic math if such an
```

## Source note 6, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L56)

```text
// index has been obtained somehow.
```

## Source note 7, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L58)

```text
// Waiting for the current submission is fine if there was a refusal to
```

## Source note 8, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L59)

```text
// submit, and the submission index wasn't incremented, but still need to
```

## Source note 9, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L60)

```text
// release objects referenced in the dropped submission (while shutting down,
```

## Source note 10, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L61)

```text
// for instance - in this case, waiting for the last successful submission,
```

## Source note 11, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L62)

```text
// which could have also referenced the objects from the new submission - we
```

## Source note 12, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L63)

```text
// can't know since the client has already overwritten its last usage index,
```

## Source note 13, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L64)

```text
// would correctly ensure that GPU usage of the objects is not pending).
```

## Source note 14, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L65)

```text
// Waiting for successful submissions, but failed signals, will result in a
```

## Source note 15, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L66)

```text
// true race condition, however, but waiting for the closest successful signal
```

## Source note 16, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L67)

```text
// is the best approximation - also retrying to signal in this case.
```

## Source note 17, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L89)

```text
// Make sure the first signal on the new queue won't happen before the last
```

## Source note 18, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L90)

```text
// signal, if pending, on the old one, as that would result first in too
```

## Source note 19, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L91)

```text
// early submission completion indication, and then in rewinding.
```

## Source note 20, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_submission_tracker.cpp#L118)

```text
// namespace rex::ui::d3d12
```
