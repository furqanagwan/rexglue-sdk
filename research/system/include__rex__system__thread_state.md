# Thread state: system source notes

This record preserves technical and API notes moved from `include/rex/system/thread_state.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/thread_state.h#L23)

```text
// rexglue constructor - takes Memory directly, no Processor needed (maybe add later)
```

## Source note 2, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/thread_state.h#L42)

```text
// NOTE: must be 64b aligned for SSE ops.
```

## Source note 3, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/thread_state.h#L47)

```text
// Thread-safe accessors for current thread's PPC context and kernel state.
```

## Source note 4, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/thread_state.h#L48)

```text
// Require ThreadState::Bind() to have been called on the current thread.
```

## Source note 5, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/thread_state.h#L57)

```text
// Forward declaration in correct namespace
```
