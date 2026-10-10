# Xaudio2 driver test: audio source notes

This record preserves technical and API notes moved from `tests/unit/audio/xaudio2_driver_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L42)

```text
// Room for more releases than AudioSystem's 64 so over-release would show.
```

## Source note 2, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L45)

```text
// Heap-allocated: a driver's frame slots are too large for the test stack.
```

## Source note 3, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L60)

```text
// Waits until the driver has released `count` frames in total.
```

## Source note 4, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L72)

```text
// Takes every pending release off the semaphore.
```

## Source note 5, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L112)

```text
// Playback paces the releases: they arrive over the frames' duration, not
```

## Source note 6, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L113)

```text
// at submission.
```

## Source note 7, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L134)

```text
// 64 frames of 5.33 ms: paced, not released at once, and not stalled.
```

## Source note 8, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L149)

```text
// Frames the dead voice held are released on the clock instead.
```

## Source note 9, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L152)

```text
// The engine is recreated straight away on the default device.
```

## Source note 10, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L263)

```text
// Either no endpoint exists, or the retry did not happen.
```

## Source note 11, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L294)

```text
// Two clients at once, as two guest render clients would have.
```

## Source note 12, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L309)

```text
// XAudio2 is the default (owner decision, 2026-09-28).
```

## Source note 13, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L315)

```text
// A config written before SDL was removed still gets audio.
```

## Source note 14, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L325)

```text
// Register a client, submit a frame from guest memory, unregister: the
```

## Source note 15, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xaudio2_driver_test.cpp#L326)

```text
// driver is created, takes the frame and is torn down with it in flight.
```
