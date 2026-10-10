# Audio client lifetime test: audio source notes

This record preserves technical and API notes moved from `tests/unit/audio/audio_client_lifetime_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L62)

```text
// Runs in place of the guest callback.
```

## Source note 2, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L71)

```text
// Drivers are kept (marked destroyed) so late use is observable rather
```

## Source note 3, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L72)

```text
// than a crash.
```

## Source note 4, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L121)

```text
// The callback re-enters through SubmitFrame, which takes the global lock
```

## Source note 5, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L122)

```text
// UnregisterClient held while clearing the slot (xenia-canary#1214).
```

## Source note 6, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L156)

```text
// no driver: dropped, not dereferenced
```

## Source note 7, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L160)

```text
// A second unregister and an out-of-range one are rejected.
```

## Source note 8, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L181)

```text
// The slot is free again.
```

## Source note 9, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L200)

```text
// Stands in for the worker, pumping whatever slot is current.
```

## Source note 10, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L216)

```text
// Every tenth client waits until the worker has dispatched to it, so the
```

## Source note 11, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L217)

```text
// unregister below races a worker that is really running, however the
```

## Source note 12, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L218)

```text
// scheduler places the threads. The rest unregister as soon as possible.
```

## Source note 13, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/audio_client_lifetime_test.cpp#L238)

```text
// at least the waited-for clients were dispatched
```
