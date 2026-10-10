# D3d12 submission tracker: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/d3d12/d3d12_submission_tracker.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L18)

```text
// GPU > CPU fence wrapper, safely handling cases when the fence has not been
```

## Source note 2, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L19)

```text
// initialized yet or has already been shut down, dropped submissions, and also
```

## Source note 3, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L20)

```text
// transfers between queues so signals stay ordered.
```

## Source note 4, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L22)

```text
// The current submission index can be associated with the usage of objects to
```

## Source note 5, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L23)

```text
// release them when the GPU isn't potentially referencing them anymore, and
```

## Source note 6, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L24)

```text
// should be incremented only
```

## Source note 7, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L26)

```text
// 0 can be used as a "never referenced" submission index.
```

## Source note 8, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L28)

```text
// The submission index timeline survives Shutdown / Initialize, so submission
```

## Source note 9, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L29)

```text
// indices can be given to clients that are not aware of the lifetime of the
```

## Source note 10, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L30)

```text
// tracker.
```

## Source note 11, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L38)

```text
// The queue may be null if it's going to be set dynamically. Will also take a
```

## Source note 12, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L39)

```text
// reference to the queue.
```

## Source note 13, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L43)

```text
// Will perform an ownership transfer if the queue is different than the
```

## Source note 14, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L44)

```text
// current one, and take a reference to the queue.
```

## Source note 15, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L48)

```text
// May be lower than a value awaited by AwaitSubmissionCompletion if it
```

## Source note 16, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L49)

```text
// returned false.
```

## Source note 17, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L51)

```text
// If shut down already or haven't fully initialized yet, don't care, for
```

## Source note 18, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L52)

```text
// simplicity of external code, as any downloads are unlikely in this case,
```

## Source note 19, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L53)

```text
// but destruction can be simplified.
```

## Source note 20, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L57)

```text
// Returns whether the expected GPU signal has actually been reached (rather
```

## Source note 21, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L58)

```text
// than some fallback condition) for cases when stronger completeness
```

## Source note 22, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L59)

```text
// guarantees as needed (when downloading, as opposed to just destroying).
```

## Source note 23, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L60)

```text
// If false is returned, it's also not guaranteed that GetCompletedSubmission
```

## Source note 24, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L61)

```text
// will return a value >= submission_index.
```

## Source note 25, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L67)

```text
// Call after a successful ExecuteCommandList. Unconditionally increments the
```

## Source note 26, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L68)

```text
// current submission index, and tries to enqueue the fence signal. Returns
```

## Source note 27, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L69)

```text
// true if enqueued successfully, but even if not, waiting for submissions
```

## Source note 28, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L70)

```text
// without a successfully enqueued signal is handled in the tracker in a way
```

## Source note 29, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L71)

```text
// that it won't be infinite, so there's no need for clients to revert updates
```

## Source note 30, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L72)

```text
// to submission indices associated with GPU usage of objects.
```

## Source note 31, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L74)

```text
// If NextSubmission has failed, but it's important that the signal is
```

## Source note 32, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L75)

```text
// enqueued, can be used to retry enqueueing the signal.
```

## Source note 33, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_submission_tracker.h#L86)

```text
// namespace rex::ui::d3d12
```
