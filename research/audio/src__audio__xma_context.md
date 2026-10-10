# Xma context: audio source notes

This record preserves technical and API notes moved from `src/audio/xma_context.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L38)

```text
// extern "C"
```

## Source note 2, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L44)

```text
// Credits for most of this code goes to:
```

## Source note 3, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L45)

```text
// https://github.com/koolkdev/libertyv/blob/master/libav_wrapper/xma2dec.c
```

## Source note 4, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L71)

```text
// Allocate ffmpeg stuff:
```

## Source note 5, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L76)

```text
// find the XMA2 audio decoder
```

## Source note 6, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L89)

```text
// Initialize these to 0. They'll actually be set later.
```

## Source note 7, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L99)

```text
// FYI: We're purposely not opening the codec here. That is done later.
```

## Source note 8, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L138)

```text
// Consume-only context: no input, just drain remaining subframes.
```

## Source note 9, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L145)

```text
// xenia-canary 7e98ae6de (fixes a 565507E4 boot hardlock).
```

## Source note 10, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L153)

```text
// Minimum free blocks needed before attempting a decode.
```

## Source note 11, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L154)

```text
// Use subframe_decode_count (clamped to 1) instead of full frame size.
```

## Source note 12, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L173)

```text
// Don't abandon a partially consumed frame: Consume() hands over at most
```

## Source note 13, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L174)

```text
// subframe_decode_count blocks per pass, so the pass that exhausts the
```

## Source note 14, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L175)

```text
// input usually strands the rest. is_enabled_ is already clear and only
```

## Source note 15, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L176)

```text
// XMAEnableContext sets it again, so a title polling for that remainder
```

## Source note 16, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L177)

```text
// would never kick (xenia-edge 052365bc0).
```

## Source note 17, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L183)

```text
// A pass that neither moved the input nor produced a frame cannot make
```

## Source note 18, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L184)

```text
// progress on a later pass either; stop rather than spin under the lock.
```

## Source note 19, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L185)

```text
// Only checked when nothing was pending, since a drain-only pass leaves the
```

## Source note 20, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L186)

```text
// offset unchanged by design (xenia-edge ade7e610b). Priming the carry is
```

## Source note 21, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L187)

```text
// progress: a one-frame loop decodes at an unchanged offset.
```

## Source note 22, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L199)

```text
// Starved of input: NFS Carbon and Most Wanted use write == read as their
```

## Source note 23, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L200)

```text
// stall detector (xenia-canary 09dbe2cd3).
```

## Source note 24, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L205)

```text
// Invalidate only a full buffer: read == write also means nothing was
```

## Source note 25, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L206)

```text
// written, which is not a reason to hand it back (xenia-canary 09dbe2cd3,
```

## Source note 26, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L207)

```text
// 505697f98).
```

## Source note 27, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L255)

```text
// A freed or re-initialized context is a new logical stream, so the previous
```

## Source note 28, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L256)

```text
// wave's MDCT overlap-add tail must not survive into frame 0 of the next one.
```

## Source note 29, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L257)

```text
// avcodec_flush_buffers() cannot drop it: ff_xmaframes_decoder declares no
```

## Source note 30, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L258)

```text
// flush callback, so the call never reaches the code clearing channel[].out.
```

## Source note 31, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L259)

```text
// Invalidating the cached format makes PrepareDecoder reopen the codec on the
```

## Source note 32, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L260)

```text
// next decode, which does discard the history.
```

## Source note 33, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L306)

```text
// Decode moves this on to the first frame that starts in the packet.
```

## Source note 34, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L378)

```text
// The skip chain continues into the next buffer at the index by which it
```

## Source note 35, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L379)

```text
// overruns this one (see FindStreamFrame).
```

## Source note 36, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L414)

```text
// No frame starts in this packet: it only continues a frame split across
```

## Source note 37, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L415)

```text
// the boundary. In a buffer interleaving several sub-streams the next
```

## Source note 38, line 416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L416)

```text
// sequential packet belongs to another stream, so follow this packet's own
```

## Source note 39, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L417)

```text
// skip count to stay on this one (xenia-edge 9d8210b32).
```

## Source note 40, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L425)

```text
// A multi-stream sound interleaves its sub-streams through every buffer, and
```

## Source note 41, line 426

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L426)

```text
// a stream's first packet in the next buffer is where its skip chain overruns
```

## Source note 42, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L427)

```text
// this one. In 007 Legends' 3-channel sounds the mono stream continues at
```

## Source note 43, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L428)

```text
// packet 1 of the next buffer and the stereo stream at packet 0.
```

## Source note 44, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L461)

```text
// BitStream only reads; it takes a mutable pointer for its writers.
```

## Source note 45, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L465)

```text
// Report the first frame starting at or after frame_offset, so a loop_start
```

## Source note 46, line 466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L466)

```text
// that is not on a frame boundary can be resolved (xenia-edge 5dd1cdbbf).
```

## Source note 47, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L488)

```text
// This frame's 15-bit header runs into the next packet, so its size is
```

## Source note 48, line 489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L489)

```text
// not readable yet. Count it anyway, or the caller takes the previous
```

## Source note 49, line 490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L490)

```text
// frame for the packet's last and skips straight past this one. Size 0
```

## Source note 50, line 491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L491)

```text
// sends it to the split-header path (xenia-edge adf56b76c).
```

## Source note 51, line 680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L680)

```text
// "XMAD", the guest context as stored (big endian), then each input buffer
```

## Source note 52, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L681)

```text
// as a little-endian byte count and its bytes.
```

## Source note 53, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L693)

```text
// Work has not committed its local context yet. Dump the actual failure
```

## Source note 54, line 694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L694)

```text
// position, rather than the stale guest copy from before this kick.
```

## Source note 55, line 699

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L699)

```text
// The third is the buffer the stream left last, if any.
```

## Source note 56, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L744)

```text
// Loop-end frame: decode it here (output limited to loop_subframe_end),
```

## Source note 57, line 745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L745)

```text
// jump to loop_start afterwards in the next-offset step.
```

## Source note 58, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L764)

```text
// A skip chain may pass over an entire short refill. Keep its remainder
```

## Source note 59, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L765)

```text
// instead of asserting on the carried packet index when that refill arrives.
```

## Source note 60, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L792)

```text
// Full packet skip (0xFF) -- no new frames begin in this packet.
```

## Source note 61, line 807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L807)

```text
// Games can write loop_start one bit short of the frame boundary. Left
```

## Source note 62, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L808)

```text
// unaligned, no frame matches, the split-header path reads a size out of
```

## Source note 63, line 809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L809)

```text
// frame payload and FFmpeg rejects the packet (xenia-edge 5dd1cdbbf).
```

## Source note 64, line 821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L821)

```text
// Frame header split across packet boundary.
```

## Source note 65, line 883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L883)

```text
// Reopening the codec restarts its output; the carried tail belongs to the
```

## Source note 66, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L884)

```text
// old stream.
```

## Source note 67, line 893

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L893)

```text
// Realign the decoder's output onto the bitstream's sample numbering: the
```

## Source note 68, line 894

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L894)

```text
// samples of the frame just decoded run from kDecoderStartPadding into this
```

## Source note 69, line 895

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L895)

```text
// block and finish in the head of the next one.
```

## Source note 70, line 899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L899)

```text
// Loop end: limit output to subframes 0..loop_subframe_end.
```

## Source note 71, line 903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L903)

```text
// Loop start: skip leading subframes per loop_subframe_skip. skip == 4
```

## Source note 72, line 904

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L904)

```text
// means the whole frame is a warm-up frame (frame-aligned loop start):
```

## Source note 73, line 905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L905)

```text
// decode seeds the codec state, output is fully discarded.
```

## Source note 74, line 926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L926)

```text
// A dropped frame breaks the carry's adjacency; re-prime rather than splice
```

## Source note 75, line 927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L927)

```text
// two blocks that are not neighbors. The frame is not replaced with
```

## Source note 76, line 928

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L928)

```text
// silence: the failure stays visible in the output and in the count.
```

## Source note 77, line 941

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L941)

```text
// Compute where to go next.
```

## Source note 78, line 961

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L961)

```text
// Not filled yet; the read offset already names the packet to start at.
```

## Source note 79, line 968

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L968)

```text
// No frame of this stream starts in the new buffer either.
```

## Source note 80, line 978

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L978)

```text
// Loop through every sample, convert and drop it into the output array.
```

## Source note 81, line 979

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L979)

```text
// If more than one channel, we need to interleave the samples from each
```

## Source note 82, line 980

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L980)

```text
// channel next to each other. Always saturate because FFmpeg output is
```

## Source note 83, line 981

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L981)

```text
// not limited to [-1, 1] (for example 1.095 as seen in 5454082B).
```

## Source note 84, line 985

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L985)

```text
// For testing of vectorized versions, stereo audio is common in 4D5307E6,
```

## Source note 85, line 986

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L986)

```text
// since the first menu frame; the intro cutscene also has more than 2
```

## Source note 86, line 987

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L987)

```text
// channels.
```

## Source note 87, line 996

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L996)

```text
// Load 8 samples, 4 for each channel.
```

## Source note 88, line 999

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L999)

```text
// Rescale.
```

## Source note 89, line 1002

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1002)

```text
// Cast to int32.
```

## Source note 90, line 1005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1005)

```text
// Saturated cast and pack to int16.
```

## Source note 91, line 1007

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1007)

```text
// Interleave channels and byte swap.
```

## Source note 92, line 1009

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1009)

```text
// Store, as [out + i * 4] movdqu.
```

## Source note 93, line 1015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1015)

```text
// Load 8 samples, as [in_channel_0 + i * 4] and
```

## Source note 94, line 1016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1016)

```text
// [in_channel_0 + i * 4 + 16] movups.
```

## Source note 95, line 1019

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1019)

```text
// Rescale.
```

## Source note 96, line 1022

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1022)

```text
// Cast to int32.
```

## Source note 97, line 1025

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1025)

```text
// Saturated cast and pack to int16.
```

## Source note 98, line 1027

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1027)

```text
// Byte swap.
```

## Source note 99, line 1029

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1029)

```text
// Store, as [out + i * 2] movdqu.
```

## Source note 100, line 1037

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1037)

```text
// Select the appropriate array based on the current channel.
```

## Source note 101, line 1040

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1040)

```text
// Raw samples sometimes aren't within [-1, 1]
```

## Source note 102, line 1043

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_context.cpp#L1043)

```text
// Convert the sample and output it in big endian.
```
