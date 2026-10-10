# Audio system: audio source notes

This record preserves technical and API notes moved from `include/rex/audio/audio_system.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/audio_system.h#L67)

```text
// Runs a client's guest callback once, as the worker does when the client's
```

## Source note 2, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/audio_system.h#L68)

```text
// semaphore fires. Returns false when the slot has no live callback.
```

## Source note 3, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/audio_system.h#L69)

```text
// UnregisterClient does not return while this is running for its slot.
```

## Source note 4, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/audio_system.h#L71)

```text
// Executes one guest callback on the worker thread; overridden by tests.
```

## Source note 5, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/audio_system.h#L98)

```text
// Held by DispatchClientCallback while a slot's callback runs; UnregisterClient
```

## Source note 6, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/audio_system.h#L99)

```text
// waits on it after releasing the global lock, because the callback re-enters
```

## Source note 7, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/audio_system.h#L100)

```text
// through SubmitFrame (xenia-canary#1214). Kept outside clients_, which the
```

## Source note 8, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/audio_system.h#L101)

```text
// constructor memsets (xenia-edge b0a1ea5f8).
```

## Source note 9, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/audio_system.h#L103)

```text
// Thread running each slot's callback, so an unregister from inside the
```

## Source note 10, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/audio_system.h#L104)

```text
// callback itself does not wait on its own mutex.
```

## Source note 11, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/audio_system.h#L110)

```text
// Event is always there in case we have no clients.
```
