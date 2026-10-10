# Timer queue: core source notes

This record preserves technical and API notes moved from `src/core/timer_queue.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L49)

```text
// Kick dispatch thread to check stop token
```

## Source note 2, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L55)

```text
// std::jthread auto-joins on destruction
```

## Source note 3, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L69)

```text
// Consume new wait items and add them to sorted wait queue
```

## Source note 4, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L74)

```text
// Check for timeout
```

## Source note 5, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L89)

```text
// Check wait queue, invoke callbacks and reschedule
```

## Source note 6, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L95)

```text
// Ensure that it isn't disarmed
```

## Source note 7, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L99)

```text
// Possibility to dispatch to a thread pool here
```

## Source note 8, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L106)

```text
// Item is recurring and didn't self-disarm during callback:
```

## Source note 9, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L116)

```text
// Specifically, kInCallback is illegal here
```

## Source note 10, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L129)

```text
// Mitigate callback flooding
```

## Source note 11, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L142)

```text
// This ring buffer will be used to introduce timers queued by the public API
```

## Source note 12, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L149)

```text
// This is a _sorted_ (ascending due_) list of active timers managed by a
```

## Source note 13, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L150)

```text
// dedicated thread
```

## Source note 14, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L160)

```text
// Special case for calling from a callback itself
```

## Source note 15, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L165)

```text
// If we are self disarming from the callback set this special state and
```

## Source note 16, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L169)

```text
// Normal case can handle the rest
```

## Source note 17, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L173)

```text
// Classes which hold WaitItems will often call Disarm() to cancel them during
```

## Source note 18, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L174)

```text
// destruction. This may lead to race conditions when the dispatch thread
```

## Source note 19, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L175)

```text
// executes a callback which accesses memory that is freed simultaneously due
```

## Source note 20, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L176)

```text
// to this. Therefore, we need to guarantee that no callbacks will be running
```

## Source note 21, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L177)

```text
// once Disarm() has returned.
```

## Source note 22, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/timer_queue.cpp#L183)

```text
// Wait for callback to complete - dispatch thread will notify
```
