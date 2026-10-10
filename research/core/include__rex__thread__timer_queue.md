# Timer queue: core source notes

This record preserves technical and API notes moved from `include/rex/thread/timer_queue.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L19)

```text
// This is a platform independent implementation of a timer queue similar to
```

## Source note 2, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L20)

```text
// Windows CreateTimerQueueTimer with WT_EXECUTEINTIMERTHREAD.
```

## Source note 3, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L38)

```text
// Cancel the pending wait item. No callbacks will be running after this call.
```

## Source note 4, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L39)

```text
// The function blocks if a callback is running and returns only after the
```

## Source note 5, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L40)

```text
// callback has finished (except when called from the corresponding callback
```

## Source note 6, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L41)

```text
// itself, where it will mark the wait item for disarmament and return
```

## Source note 7, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L42)

```text
// immediately). Deadlocks are possible when a lock is held during disamament
```

## Source note 8, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L43)

```text
// and the corresponding callback is running concurrently, trying to acquire
```

## Source note 9, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L44)

```text
// said lock.
```

## Source note 10, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L51)

```text
// Waiting for the due time
```

## Source note 11, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L52)

```text
// Callback is being executed
```

## Source note 12, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L53)

```text
// Callback is being executed and disarmed itself
```

## Source note 13, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L54)

```text
// Disarmed, waiting for destruction
```

## Source note 14, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L62)

```text
// zero if not recurring
```

## Source note 15, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L70)

```text
// Callback is first executed at due, then again repeatedly after interval
```

## Source note 16, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L71)

```text
// passes (unless interval == 0). The first callback will be scheduled at
```

## Source note 17, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/timer_queue.h#L72)

```text
// `max(now() - interval, due)` to mitigate callback flooding.
```
