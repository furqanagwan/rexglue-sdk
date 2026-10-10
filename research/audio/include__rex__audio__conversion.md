# Conversion: audio source notes

This record preserves technical and API notes moved from `include/rex/audio/conversion.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L28)

```text
// The gain pass below walks the output four floats at a time, and its weight
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L29)

```text
// table assumes 6 channels divide evenly into those windows.
```

## Source note 3, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L50)

```text
// Second pass rather than fusing into the shuffle above, which stores as integers.
```

## Source note 4, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L51)

```text
// 6 KB per 5.33 ms frame, so skipping it at unity gain is not worth the asymmetry.
```

## Source note 5, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L53)

```text
// Six interleaved channels across four-float windows repeat every 12 floats,
```

## Source note 6, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L54)

```text
// so three weight vectors cover every alignment the loop ever sees. The
```

## Source note 7, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L55)

```text
// assert above makes the sample count even, which makes the float count a
```

## Source note 8, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L56)

```text
// multiple of 12, so the cycle closes with no tail to handle.
```

## Source note 9, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L86)

```text
// load 4 samples from 6 channels each
```

## Source note 10, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L93)

```text
// byte swap
```

## Source note 11, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L101)

```text
// Center and LFE land on both sides.
```

## Source note 12, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L129)

```text
// Default 5.1 channel mapping is fl, fr, fc, lf, bl, br
```

## Source note 13, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L130)

```text
// https://docs.microsoft.com/en-us/windows/win32/xaudio2/xaudio2-default-channel-mapping
```

## Source note 14, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/conversion.h#L139)

```text
// Center and LFE land on both sides.
```
