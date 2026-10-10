# Context: audio source notes

This record preserves technical and API notes moved from `include/rex/audio/xma/context.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L23)

```text
// XMA audio format:
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L24)

```text
// From research, XMA appears to be based on WMA Pro with
```

## Source note 3, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L25)

```text
// a few (very slight) modifications.
```

## Source note 4, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L26)

```text
// XMA2 is fully backwards-compatible with XMA1.
```

## Source note 5, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L28)

```text
// Helpful resources:
```

## Source note 6, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L29)

```text
// https://github.com/koolkdev/libertyv/blob/master/libav_wrapper/xma2dec.c
```

## Source note 7, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L30)

```text
// https://hcs64.com/mboard/forum.php?showthread=14818
```

## Source note 8, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L31)

```text
// https://github.com/hrydgard/minidx9/blob/master/Include/xma2defs.h
```

## Source note 9, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L33)

```text
// Forward declarations
```

## Source note 10, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L42)

```text
// This is stored in guest space in big-endian order.
```

## Source note 11, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L43)

```text
// We load and swap the whole thing to splat here so that we can
```

## Source note 12, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L44)

```text
// use bitfields.
```

## Source note 13, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L45)

```text
// This could be important:
```

## Source note 14, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L46)

```text
// https://www.fmod.org/questions/question/forum-15859
```

## Source note 15, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L47)

```text
// Appears to be dumped in order (for the most part)
```

## Source note 16, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L50)

```text
// DWORD 0
```

## Source note 17, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L51)

```text
// XMASetInputBuffer0, number of
```

## Source note 18, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L52)

```text
// 2KB packets. Max 4095 packets.
```

## Source note 19, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L53)

```text
// These packets form a block.
```

## Source note 20, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L54)

```text
// +12bit, XMASetLoopData NumLoops
```

## Source note 21, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L55)

```text
// +20bit, XMAIsInputBuffer0Valid
```

## Source note 22, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L56)

```text
// +21bit, XMAIsInputBuffer1Valid
```

## Source note 23, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L57)

```text
// +22bit SizeWrite 256byte blocks
```

## Source note 24, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L58)

```text
// +27bit
```

## Source note 25, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L60)

```text
// AKA OffsetWrite
```

## Source note 26, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L62)

```text
// DWORD 1
```

## Source note 27, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L63)

```text
// XMASetInputBuffer1, number of
```

## Source note 28, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L64)

```text
// 2KB packets. Max 4095 packets.
```

## Source note 29, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L65)

```text
// These packets form a block.
```

## Source note 30, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L66)

```text
// +12bit, XMAPlaybackSetLoop
```

## Source note 31, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L67)

```text
// dwLoopSubframeEnd: last loop frame
```

## Source note 32, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L68)

```text
// plays subframes 0..end
```

## Source note 33, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L69)

```text
// +14bit
```

## Source note 34, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L70)

```text
// +17bit, XMAPlaybackSetLoop
```

## Source note 35, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L71)

```text
// dwLoopSubframeSkip: subframes to
```

## Source note 36, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L72)

```text
// discard at loop start; 4 = whole
```

## Source note 37, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L73)

```text
// warm-up frame (frame-aligned loops)
```

## Source note 38, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L74)

```text
// +20bit
```

## Source note 39, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L75)

```text
// +24bit, extra output buffer blocks
```

## Source note 40, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L76)

```text
// reserved per decoded frame
```

## Source note 41, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L77)

```text
// +27bit enum of sample rates
```

## Source note 42, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L78)

```text
// +29bit
```

## Source note 43, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L79)

```text
// +30bit
```

## Source note 44, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L80)

```text
// +31bit, XMAIsOutputBufferValid
```

## Source note 45, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L82)

```text
// DWORD 2
```

## Source note 46, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L87)

```text
// DWORD 3
```

## Source note 47, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L88)

```text
// XMASetLoopData LoopStartOffset
```

## Source note 48, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L89)

```text
// frame offset in bits
```

## Source note 49, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L93)

```text
// DWORD 4
```

## Source note 50, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L94)

```text
// XMASetLoopData LoopEndOffset
```

## Source note 51, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L95)

```text
// frame offset in bits
```

## Source note 52, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L99)

```text
// DWORD 5
```

## Source note 53, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L100)

```text
// physical address
```

## Source note 54, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L101)

```text
// DWORD 6
```

## Source note 55, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L102)

```text
// physical address
```

## Source note 56, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L103)

```text
// DWORD 7
```

## Source note 57, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L104)

```text
// physical address
```

## Source note 58, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L105)

```text
// DWORD 8
```

## Source note 59, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L106)

```text
// PtrOverlapAdd(?)
```

## Source note 60, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L108)

```text
// DWORD 9
```

## Source note 61, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L109)

```text
// +0bit, XMAGetOutputBufferReadOffset AKA WriteBufferOffsetRead
```

## Source note 62, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L112)

```text
// +30bit
```

## Source note 63, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L113)

```text
// +31bit
```

## Source note 64, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L115)

```text
// DWORD 10-15
```

## Source note 65, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L116)

```text
// reserved?
```

## Source note 66, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L157)

```text
// XMA2WAVEFORMATEX
```

## Source note 67, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L168)

```text
// First frame starting at or after the requested offset.
```

## Source note 68, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L197)

```text
// The bitstream declares a start padding that the hardware discards. FFmpeg's
```

## Source note 69, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L198)

```text
// xmaframes decoder parses that field and drops it on the floor
```

## Source note 70, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L199)

```text
// (wmaprodec.c decode_frame, "start skip"), emitting the padding as ordinary
```

## Source note 71, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L200)

```text
// output, so its sample numbering runs this far ahead of the numbering the
```

## Source note 72, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L201)

```text
// guest's loop offsets use. Measured at 192 on every wave checked. Left
```

## Source note 73, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L202)

```text
// uncorrected it costs each loop wrap its final 192 samples.
```

## Source note 74, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L225)

```text
// Frames FFmpeg rejected or returned no audio for since Setup.
```

## Source note 75, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L235)

```text
// Walks the frames of one 2048-byte packet and describes the one at
```

## Source note 76, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L236)

```text
// frame_offset (bits from the packet start).
```

## Source note 77, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L238)

```text
// Bit offset in buffer of the next frame start of this sub-stream at or after
```

## Source note 78, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L239)

```text
// packet next_packet_index, or kBitsPerPacketHeader when the buffer has none.
```

## Source note 79, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L240)

```text
// When the skip chain runs past the buffer, next_buffer_packet receives the
```

## Source note 80, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L241)

```text
// packet index where it continues in the other input buffer (0 otherwise).
```

## Source note 81, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L258)

```text
// Moves to the other input buffer, reading from its packet start_packet.
```

## Source note 82, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L260)

```text
// GetNextPacketReadOffset, returning 0 when no frame of the stream starts.
```

## Source note 83, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L282)

```text
// Logs the stream's configuration once, on its first undecodable frame, and
```

## Source note 84, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L283)

```text
// with xma_dump_dir set saves the context and input buffers there.
```

## Source note 85, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L301)

```text
// Set on the first failed frame of a stream; cleared with the decoder state.
```

## Source note 86, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L304)

```text
// Diagnostic-only copy taken before invalidating guest input. The guest may
```

## Source note 87, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L305)

```text
// reuse or free an invalid buffer before a later decode failure.
```

## Source note 88, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L308)

```text
// ffmpeg structures
```

## Source note 89, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L314)

```text
// Packet data buffer (two packets worth for split frame handling)
```

## Source note 90, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L316)

```text
// First byte contains bit offset information
```

## Source note 91, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L318)

```text
// Conversion buffer for up to 2-channel frame
```

## Source note 92, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L320)

```text
// Freshly decoded block, before start-padding realignment
```

## Source note 93, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L322)

```text
// Tail of the previous decoded block, awaiting the next block's padding head
```

## Source note 94, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L325)

```text
// Output buffer tracking
```

## Source note 95, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L329)

```text
// Loop subframe precision state
```

## Source note 96, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L333)

```text
// Start-padding realignment state. Attributes belong to the frame whose
```

## Source note 97, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L334)

```text
// samples are still being assembled, so they land one decode after the frame
```

## Source note 98, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/audio/xma/context.h#L335)

```text
// they describe.
```
