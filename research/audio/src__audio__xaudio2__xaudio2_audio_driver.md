# Xaudio2 audio driver: audio source notes

This record preserves technical and API notes moved from `src/audio/xaudio2/xaudio2_audio_driver.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L36)

```text
// KSDATAFORMAT_SUBTYPE_IEEE_FLOAT, spelled out so no GUID library is needed.
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L40)

```text
// Guest channel order fl fr fc lf bl br is the 5.1 speaker mask's bit order.
```

## Source note 3, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L108)

```text
// XAudio2 needs COM in the MTA. The service thread holds an MTA scope for
```

## Source note 4, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L109)

```text
// the driver's lifetime, which also makes guest threads that submit frames
```

## Source note 5, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L110)

```text
// implicitly MTA (https://devblogs.microsoft.com/oldnewthing/?p=4613).
```

## Source note 6, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L148)

```text
// More frames in flight than AudioSystem ever queues. Keep the one
```

## Source note 7, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L149)

```text
// release per frame so the client cannot stall.
```

## Source note 8, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L162)

```text
// Same conversion and mix controls as the SDL output, applied per frame.
```

## Source note 9, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L177)

```text
// The device may have changed while this frame was converted; a frame mixed
```

## Source note 10, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L178)

```text
// for another channel count is paced instead of played.
```

## Source note 11, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L188)

```text
// Start the stall watchdog's clock.
```

## Source note 12, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L250)

```text
// Buffers of a torn-down engine were already moved to the paced queue.
```

## Source note 13, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L297)

```text
// A dead voice never ends its buffers; release them on the clock instead.
```

## Source note 14, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L352)

```text
// Default device, channels and rate: the default device ID selects the
```

## Source note 15, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L353)

```text
// virtual audio client, which follows default-device changes itself, and
```

## Source note 16, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L354)

```text
// not forcing a rate lets it switch to a 44.1 kHz endpoint. A chosen
```

## Source note 17, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L355)

```text
// endpoint that is gone falls back to the default.
```

## Source note 18, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L380)

```text
// A mono or stereo endpoint gets the stereo fold; anything
```

## Source note 19, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L381)

```text
// wider gets 5.1 and XAudio2 maps it onto the endpoint's layout.
```

## Source note 20, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L432)

```text
// An orderly teardown, not a loss: same bookkeeping without counting it.
```

## Source note 21, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L444)

```text
// Callbacks may still be running; they take mutex_, so none of this may
```

## Source note 22, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L445)

```text
// happen under it. Stopping the engine first ends in-flight callbacks before
```

## Source note 23, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L446)

```text
// the voices go (xenia-edge 9371e73d9).
```

## Source note 24, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L470)

```text
// Initialize() reports once the first device attempt is done, so a caller
```

## Source note 25, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L471)

```text
// sees has_device() settled.
```

## Source note 26, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L506)

```text
// Recreate straight away: the loss is often a device switch the virtual
```

## Source note 27, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L507)

```text
// client could not follow, and the new default is already there.
```

## Source note 28, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L533)

```text
// Never spin: a deadline already past still yields the lock for a moment.
```

## Source note 29, line 542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xaudio2/xaudio2_audio_driver.cpp#L542)

```text
// namespace rex::audio::xaudio2
```
