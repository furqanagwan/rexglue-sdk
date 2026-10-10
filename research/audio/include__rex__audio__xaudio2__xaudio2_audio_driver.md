# Xaudio2 audio driver: audio source notes

This record preserves technical and API notes moved from `include/rex/audio/xaudio2/xaudio2_audio_driver.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L43)

```text
// Guest frames: 6 channels (fl fr fc lf bl br) of 256 big-endian float
```

## Source note 2, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L44)

```text
// samples each, one channel after another, at 48 kHz.
```

## Source note 3, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L49)

```text
// AudioSystem queues at most this many frames per client.
```

## Source note 4, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L55)

```text
// Every engine creation fails, as on a machine with no audio endpoint.
```

## Source note 5, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L57)

```text
// How often to try again for a device while there is none.
```

## Source note 6, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L59)

```text
// Buffers queued with no OnBufferEnd for this long mean the device is gone
```

## Source note 7, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L60)

```text
// even if XAudio2 never reported it.
```

## Source note 8, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L62)

```text
// The Windows endpoint ID to play through; empty follows the default.
```

## Source note 9, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L70)

```text
// Starts the service thread and tries for a device. Succeeds without one
```

## Source note 10, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L71)

```text
// (frames are then paced by the clock); fails only if COM cannot start.
```

## Source note 11, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L74)

```text
// SubmitFrame on a host pointer to a guest-format frame.
```

## Source note 12, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L76)

```text
// Stops the service thread and releases the engine. Frames still queued are
```

## Source note 13, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L77)

```text
// not released: the client is going away.
```

## Source note 14, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L80)

```text
// A device is open and taking frames.
```

## Source note 15, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L82)

```text
// Channels submitted to the device: 2 (stereo fold) or 6 (5.1).
```

## Source note 16, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L84)

```text
// Moves the output to another Windows endpoint (empty: the default); the
```

## Source note 17, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L85)

```text
// service thread reopens the engine on it.
```

## Source note 18, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L87)

```text
// The endpoint the open engine plays through: empty for the default, and
```

## Source note 19, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L88)

```text
// for a chosen endpoint that could not be opened.
```

## Source note 20, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L90)

```text
// Engines opened so far.
```

## Source note 21, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L92)

```text
// Device losses handled so far (critical errors and stalls).
```

## Source note 22, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L94)

```text
// Semaphore releases so far.
```

## Source note 23, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L97)

```text
// Test hooks: take the device-loss path as if XAudio2 reported a critical
```

## Source note 24, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L98)

```text
// error, and switch simulated device absence on or off.
```

## Source note 25, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L101)

```text
// Stops the source voice without telling the driver, so buffers stop
```

## Source note 26, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L102)

```text
// finishing and only the stall watchdog notices.
```

## Source note 27, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L122)

```text
// With mutex_ held.
```

## Source note 28, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L125)

```text
// A null reason is an orderly teardown: nothing is logged.
```

## Source note 29, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L149)

```text
// Owned by the service thread; used by SubmitGuestFrame only while
```

## Source note 30, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L150)

```text
// engine_live_ is set, under mutex_.
```

## Source note 31, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xaudio2/xaudio2_audio_driver.h#L167)

```text
// namespace rex::audio::xaudio2
```
