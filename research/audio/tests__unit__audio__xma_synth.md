# Xma synth: audio source notes

This record preserves technical and API notes moved from `tests/unit/audio/xma_synth.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L31)

```text
// A WMA Pro frame as FFmpeg's xmaframes decoder parses it (flags 0x10d6):
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L32)

```text
// length prefix, one full-length subframe per channel, no coefficients, so it
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L33)

```text
// decodes to silence. Subframe fill bits pad it to size_bits. reserved_bit set
```

## Source note 4, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L34)

```text
// makes FFmpeg reject it.
```

## Source note 5, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L41)

```text
// frame length
```

## Source note 6, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L42)

```text
// tile header: fixed layout, one 512-sample subframe
```

## Source note 7, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L44)

```text
// no postproc transform
```

## Source note 8, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L46)

```text
// drc gain
```

## Source note 9, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L47)

```text
// no start/end skip
```

## Source note 10, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L48)

```text
// subframe extended header: fill bits follow
```

## Source note 11, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L49)

```text
//   explicit fill length
```

## Source note 12, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L50)

```text
//   15-bit length field
```

## Source note 13, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L55)

```text
// channel transform present bit
```

## Source note 14, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L56)

```text
// pair: no transform
```

## Source note 15, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L58)

```text
// no coefficients per channel
```

## Source note 16, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L59)

```text
// the bit before the trailer
```

## Source note 17, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L67)

```text
// absolute bit offsets in the buffer
```

## Source note 18, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L76)

```text
// first_frame_bit 0 marks a packet in which no frame starts.
```

## Source note 19, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_synth.h#L84)

```text
// Lays frames end to end through the data area of packet_count packets.
```
