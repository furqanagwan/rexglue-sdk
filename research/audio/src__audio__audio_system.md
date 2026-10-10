# Audio system: audio source notes

This record preserves technical and API notes moved from `src/audio/audio_system.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L31)

```text
// As with normal Microsoft, there are like twelve different ways to access
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L32)

```text
// the audio APIs. Early games use XMA*() methods almost exclusively to touch
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L33)

```text
// decoders. Later games use XAudio*() and direct memory writes to the XMA
```

## Source note 4, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L34)

```text
// structures (as opposed to the XMA* calls), meaning that we have to support
```

## Source note 5, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L35)

```text
// both.
```

## Source note 6, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L37)

```text
// For ease of implementation, most audio related processing is handled in
```

## Source note 7, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L38)

```text
// AudioSystem, and the functions here call off to it.
```

## Source note 8, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L39)

```text
// The XMA*() functions just manipulate the audio system in the guest context
```

## Source note 9, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L40)

```text
// and let the normal AudioSystem handling take it, to prevent duplicate
```

## Source note 10, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L41)

```text
// implementations. They can be found in xboxkrnl_audio_xma.cc
```

## Source note 11, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L100)

```text
// Initialize driver and ringbuffer.
```

## Source note 12, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L103)

```text
// Main run loop.
```

## Source note 13, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L106)

```text
// These handles signify the number of submitted samples. Once we reach
```

## Source note 14, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L107)

```text
// 64 samples, we wait until our audio backend releases a semaphore
```

## Source note 15, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L108)

```text
// (signaling a sample has finished playing)
```

## Source note 16, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L123)

```text
// Shutdown event signaled.
```

## Source note 17, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L132)

```text
// Number of clients pumped
```

## Source note 18, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L162)

```text
// Adapted from xenia-edge 8aa50e0e0 (per-client callback mutex): the slot is
```

## Source note 19, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L163)

```text
// read under the callback mutex, so once UnregisterClient has cleared it and
```

## Source note 20, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L164)

```text
// waited here, no callback can still be using its driver or argument.
```

## Source note 21, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L210)

```text
// Shut down XMA decoder first - its worker can stall in FFmpeg
```

## Source note 22, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L218)

```text
// The worker may be stuck inside a guest callback that is itself blocked on
```

## Source note 23, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L219)

```text
// guest objects (e.g. KeWaitForMultipleObjects), so terminating is the last
```

## Source note 24, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L220)

```text
// resort. Give it a chance to unwind first: TerminateThread abandons any
```

## Source note 25, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L221)

```text
// lock the thread holds, including the CRT heap lock.
```

## Source note 26, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L233)

```text
// Destroy all active client drivers (closes their output voices, stopping
```

## Source note 27, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L234)

```text
// callback threads) before the semaphores they reference are destroyed.
```

## Source note 28, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L291)

```text
// A callback finishing after its client was unregistered still submits;
```

## Source note 29, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L292)

```text
// there is no driver left to take the frame.
```

## Source note 30, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L307)

```text
// Clear the slot under the global lock, then wait for an in-flight callback
```

## Source note 31, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L308)

```text
// without it: the callback takes the global lock in SubmitFrame, so waiting
```

## Source note 32, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L309)

```text
// while holding it deadlocks (xenia-canary#1214, xenia-edge 8aa50e0e0).
```

## Source note 33, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L310)

```text
// The slot stays in_use until teardown finishes, so RegisterClient cannot
```

## Source note 34, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L311)

```text
// hand it out while the old driver can still release its semaphore.
```

## Source note 35, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L332)

```text
// The guest callback still running on this thread holds the argument
```

## Source note 36, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L333)

```text
// pointer; leak the 4-byte cell rather than free it under it.
```

## Source note 37, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L340)

```text
// Drain the semaphore of its count.
```

## Source note 38, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L355)

```text
// Count the number of used clients first.
```

## Source note 39, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L356)

```text
// Any gaps should be handled gracefully.
```

## Source note 40, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L393)

```text
// Reset the semaphore and recreate the driver ourselves.
```

## Source note 41, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/audio_system.cpp#L431)

```text
// Kind of a hack, but it works.
```
