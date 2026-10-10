# Downmix: audio source notes

This record preserves technical and API notes moved from `include/rex/audio/downmix.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L15)

```text
/**
 * Weights applied when the guest's 5.1 render is folded to a stereo device.
 * Guest channel order is the XAudio default: fl fr fc lf bl br. The front
 * channels carry an implicit weight of 1.0, so `scale` alone sets the output
 * level.
 *
 * Defaults follow ITU-R BS.775 and Dolby Lo/Ro: center and surround at -3 dB,
 * LFE dropped. No published stereo downmix folds LFE, which is authored around
 * 10 dB hot by convention, so a title that wants it audible sets a weight that
 * undoes that offset rather than folding it at unity.
 */
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L30)

```text
// 1/(1+0.707)
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L33)

```text
/**
 * Weights applied when the guest's 5.1 render reaches a device with more than
 * two channels, which the output stage passes through rather than folding.
 * Same channel order and the same implicit front weight of 1.0 as StereoFold,
 * so the two structs describe one mix in two destinations.
 *
 * Defaults are unity, a passthrough, because a title whose render really is
 * 5.1 wants its own mix reproduced. A title that packs something other than an
 * LFE into the LFE slot sets `lfe` to drop or attenuate it: that slot is
 * reproduced around 10 dB hot, so full-band content placed there arrives far
 * louder than it was authored, and a downstream downmix that folds it without
 * low-passing carries the whole band into the other channels.
 */
```

## Source note 4, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L52)

```text
/// Safe to call from any thread. The output stage picks the new values up on
```

## Source note 5, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L53)

```text
/// its next device callback.
```

## Source note 6, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L60)

```text
/// Linear master gain applied to the stereo fold and to 5.1 passthrough alike.
```

## Source note 7, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L61)

```text
/// 1.0 is unity. Above unity can clip, and the output stage clamps.
```

## Source note 8, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L65)

```text
/// The gain the output stage applies: GetOutputGain() scaled by the
```

## Source note 9, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L66)

```text
/// `audio_volume` cvar (0-100, read on every call so changes apply at once).
```

## Source note 10, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L69)

```text
/// The app is constrained: its window is minimised (RG-GDK-065). Microsoft's
```

## Source note 11, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L70)

```text
/// PC backward compatibility stops a title's audio then
```

## Source note 12, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L71)

```text
/// (`disableAudioOnConstrained`); the title itself keeps running.
```

## Source note 13, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L75)

```text
/// Whether the output stage plays silence: `audio_mute`, or the app
```

## Source note 14, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/downmix.h#L76)

```text
/// constrained while `audio_mute_minimized` is on. Read on every frame.
```
