# Xma context test: audio source notes

This record preserves technical and API notes moved from `tests/unit/audio/xma_context_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L44)

```text
// One XMA context over guest memory, with the stream in input buffer 0.
```

## Source note 2, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L80)

```text
// Kicks the context once, as XMAEnableContext does.
```

## Source note 3, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L94)

```text
// Blocks written by one kick that started with an empty ring at offset 0.
```

## Source note 4, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L101)

```text
// --- Packet walking (pure) ---------------------------------------------------
```

## Source note 5, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L104)

```text
// Six frames leave 10 bits in the packet: the seventh frame's 15-bit header
```

## Source note 6, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L105)

```text
// runs into the next packet (xenia-edge adf56b76c).
```

## Source note 7, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L120)

```text
// routes to the split-header path
```

## Source note 8, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L136)

```text
// loop_start one bit short of the frame (xenia-edge 5dd1cdbbf).
```

## Source note 9, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L141)

```text
// Past the last frame there is nothing to resolve to.
```

## Source note 10, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L147)

```text
// Two interleaved sub-streams: A in packets 0, 1, 3; B in packet 2. Packet 1
```

## Source note 11, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L148)

```text
// only continues a frame of A and skips one packet to A's next packet
```

## Source note 12, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L149)

```text
// (xenia-edge 9d8210b32).
```

## Source note 13, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L160)

```text
// A frameless packet marked 0xFF ends the chain.
```

## Source note 14, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L163)

```text
// Running off the buffer does too.
```

## Source note 15, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L168)

```text
// --- Work() through FFmpeg ---------------------------------------------------
```

## Source note 16, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L175)

```text
// The first frame primes the start-padding realignment; each later frame
```

## Source note 17, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L176)

```text
// releases the previous one.
```

## Source note 18, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L186)

```text
// subframe_decode_count 1 hands over one block per pass, so the pass that
```

## Source note 19, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L187)

```text
// exhausts the input leaves three blocks of the last frame
```

## Source note 20, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L188)

```text
// (xenia-edge 052365bc0).
```

## Source note 21, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L204)

```text
// Eight frames decoded, seven released; dropping the split frame costs one.
```

## Source note 22, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L225)

```text
// Frames 1-4, back to 2, then 2-4: seven decodes, six frames released.
```

## Source note 23, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L244)

```text
/*stereo=*/
```

## Source note 24, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L257)

```text
/*reserved_bit=*/
```

## Source note 25, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L261)

```text
// Frame 2 fails and breaks the realignment, so frame 1 is never released and
```

## Source note 26, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L262)

```text
// frame 3 primes again: only frames 3 and 4 come out.
```

## Source note 27, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L268)

```text
// An infinite loop over one undecodable frame used to spin in Work() with
```

## Source note 28, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L269)

```text
// the context lock held (xenia-edge ade7e610b). On regression this reports
```

## Source note 29, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L270)

```text
// the timeout, then the CTest timeout ends the still-spinning process.
```

## Source note 30, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L271)

```text
/*reserved_bit=*/
```

## Source note 31, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L300)

```text
// The loop fills all 31 blocks: the write offset comes round to the read
```

## Source note 32, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L301)

```text
// offset and the full buffer is handed back as invalid.
```

## Source note 33, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L309)

```text
// One frame only primes the realignment: nothing is written, which is not a
```

## Source note 34, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L310)

```text
// full buffer (xenia-canary 09dbe2cd3).
```

## Source note 35, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L320)

```text
// NFS Carbon and Most Wanted watch for write == read (xenia-canary 09dbe2cd3).
```

## Source note 36, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L344)

```text
// 31 blocks: seven frames and three blocks of the eighth.
```

## Source note 37, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L347)

```text
// The title reads everything, hands the buffer back and stops feeding input.
```

## Source note 38, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L357)

```text
// --- Multi-stream buffers ----------------------------------------------------
```

## Source note 39, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L361)

```text
// Writes whole frames into one packet from its first data bit.
```

## Source note 40, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L381)

```text
// Three packets: the chain from packet 1 skips two, overrunning by one.
```

## Source note 41, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L403)

```text
// A 3-channel sound as 007 Legends streams it: stereo sub-stream A and mono
```

## Source note 42, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L404)

```text
// sub-stream B interleaved through both input buffers. The mono context
```

## Source note 43, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L405)

```text
// follows B from packet 1 of buffer 0 to packet 1 of buffer 1; restarting at
```

## Source note 44, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L406)

```text
// packet 0 would feed it A's stereo frames, which do not decode as mono.
```

## Source note 45, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L414)

```text
// A -> packet 2
```

## Source note 46, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L415)

```text
// B -> next buffer, 1
```

## Source note 47, line 416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L416)

```text
// A -> next buffer, 0
```

## Source note 48, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L450)

```text
// Four mono frames: the first primes the realignment.
```

## Source note 49, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L470)

```text
// The first three frames leave either 1352 payload bits or 10 header bits
```

## Source note 50, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L471)

```text
// in the first packet. Frame four continues in packet 1 of the next buffer.
```

## Source note 51, line 514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L514)

```text
// Next stream packet lies three packets beyond this buffer.
```

## Source note 52, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L519)

```text
// A single-packet refill contains only another stream. It must be skipped
```

## Source note 53, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L520)

```text
// without reading it or losing the remaining distance to this stream.
```

## Source note 54, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L554)

```text
// The guest reuses the released input for new content before failure.
```

## Source note 55, line 575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/audio/xma_context_test.cpp#L575)

```text
// The final payload is the original first buffer, not its reused memory.
```
