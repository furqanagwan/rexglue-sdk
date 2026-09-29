# RG-GDK-040: Legends XMA sub-streams across input buffers

Issue: [#124](https://github.com/furqanagwan/rexglue-sdk/issues/124).
Investigation: 2026-09-29, SDK baseline `1e9a019`.

## Cause and evidence

007 Legends' three-channel sounds interleave a stereo sub-stream and a mono
sub-stream. A packet header's skip count identifies the next packet belonging
to that sub-stream. Crossing an input-buffer boundary must retain the packet
index remainder. Restarting at packet zero can switch channels mid-stream.

The eight private XMAD captures from the diagnostic sessions contain the same repeated audio
segment, not eight distinct assets. They all show the same distinction:

| Selected chain in input buffer 1 | Decode as mono | Decode as stereo |
| --- | --- | --- |
| Start packet 0, 10 packets | 3 frames accepted, 81 rejected | 84 accepted, 0 rejected |
| Start packet 1, 5 packets | 84 accepted, 0 rejected | 0 accepted, 84 rejected |

The preceding 15-packet buffer's mono skip chain continues at packet **1** of
the next buffer. The failing contexts are mono but restart at bit offset 32,
packet **0**. This explains both reserved-bit and coefficient-count errors with
valid input bytes. These counts were reproduced with both the original investigation probe
and the maintained `xma_probe` tool using the unchanged SDK FFmpeg pin
`0604b464c7cb4ebc94940cf1f324a3b26b87717c`.

The faulty reset and next-packet lookup also exist in the parent of timer change
`c85c98a`. The arithmetic defect predates that change; timing could expose it,
but no same-scene timing A/B or audible-quality claim is made here.

## Fix

Carry the skip-chain remainder through input-buffer swaps and split-frame
lookahead. Distinguish "no frame found" from a legitimate frame at bit 32.
Retain the remainder while awaiting refill, including a short refill containing
no packets of this sub-stream. Preserve the existing decoder, loop, output-ring
and explicit decode-failure behavior; do not substitute silence.

The optional failure diagnostic writes the local context at the failing frame,
valid input buffers and an owned snapshot of the previous buffer. It copies the
previous input before invalidating it, only when dumping is enabled, so later
guest reuse cannot change that historical snapshot. File errors are reported.

## Diagnostic tools

Launch the title with `--xma_dump_dir=C:/private/xma-captures`. Dumping is off by
default. Captures include game audio and must remain private. One capture per
failing stream is written; this is not a full continuous recording.

```powershell
python scripts/xma_dump.py C:/private/xma-captures/xma_000_ctx07.bin
cmake --build --preset win-amd64-release --target xma_probe
out/win-amd64/Release/xma_probe.exe C:/private/xma-captures/xma_000_ctx07.bin 1 0
out/win-amd64/Release/xma_probe.exe C:/private/xma-captures/xma_000_ctx07.bin 1 1
```

The probe takes a buffer index (0/1 for inputs, 2 for the previous snapshot)
and a starting packet. It follows that chain and tests both channel modes with
the capture's sample rate. It reports rejected frames and incomplete tails,
without playing or writing PCM. Exit zero means the probe ran, not that both
modes decoded or that a title is compatible. It cannot reconstruct missing
buffers or decoder history before the capture. The optional target is not
installed and adds no dependency to title builds.

XMAD layout: four-byte `XMAD`, the 64-byte big-endian guest context, then two or
three buffers, each prefixed by a four-byte little-endian byte length. Zero
length means unavailable. Each nonempty buffer contains whole 2048-byte packets.
The third buffer is an optional previous-input snapshot; its pointers may no
longer describe live guest memory. The parser accepts the original two-buffer captures.

## Validation

- Debug, Release and GDK Release `[xma]`: 20 cases, 214,122 assertions, passing. Tests use
  synthetic mono/stereo frames decoded by real FFmpeg over guest memory.
- New cases cover immediate/delayed refill, split payloads and split headers in
  both buffer directions, short refills, and diagnostic snapshot ownership.
- Restoring the old reset/lookahead behavior makes the two stream-transition
  tests fail: 7 failed assertions. The source was restored and the suite passed.
- Four synthetic XMAD parser tests cover legacy/current layouts, truncation,
  oversized/misaligned lengths and extra buffers (`audio.xma_dump_format`).
- Full Debug suite: 1,964 tests discovered, no failures, four pre-existing
  BitStream write tests skipped. GDK Release rebuilt/installed; Legends rebuilt
  against that runtime. Full Release and title-run results are pending.
  Private logs and probe results are retained under ignored `out/rg040`.

The original issue reports errors after about two minutes of Legends gameplay.
A boot/menu soak does not satisfy that scene's acceptance gate. Audible impact
is unconfirmed. This is an audio change; no new GPU-vendor claim is made.

## Upstream comparison

Read-only Edge `12e3b4223dd4c2e41d57ea4b4477546affe4ce10` retains the
cross-buffer target calculation from Canary [PR #983](https://github.com/xenia-canary/xenia-canary/pull/983),
merged 2026-05-14 as `b575c684187d6a77a91cb8ff3297173326206a58`
(head `c77d274464a971b8c47ad53527ee43f694a2433d`). Its
`GetPacketHandle` subtracts the previous buffer's packet count before accessing
the next buffer. This local change adapts that behavior to the existing context
without transplanting the decoder. Classification B: shared compatibility fix.

The PR describes AC6 cinematic audio gaps and reports improved AC6/Afro Samurai
audio, with no obvious regression in the listed spot checks. It also lists
unresolved audio problems in other titles; those reports are not local passes.
Later Edge fixes for split headers, frameless skip chains, loops and draining
remain covered by the [existing audit and tests](xma-audit.md).
Edge [PR #236](https://github.com/has207/xenia-edge/pull/236) was closed unmerged:
its owner preferred fixing decode over emitting silence. That fallback is not
adopted. No full Edge emulator or alternate FFmpeg build has been run on these
captures; the comparison here is source-level packet routing and decoding with
the SDK's pinned codec.
