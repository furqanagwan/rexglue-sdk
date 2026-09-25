# XMA packet/loop and audio callback lifetime audit (RG-GDK-018)

Audit date 2026-09-25, against `main` at `8186b9f`. It compares
`src/audio/xma_context.cpp` (decode, consume, `StoreContextMerged`) and
`src/audio/audio_system.cpp` with has207/xenia-edge `edge` at `5dd1cdbbf`,
which carries Canary's `XmaContextNew` plus Edge's later fixes. ReXGlue's
context came from the same source (the AC6 ReXGlue context that Canary imported
as `b575c6841`), so most upstream changes apply line for line.

## Adopted

| Upstream | What it fixes | Local change | Test (`unit_tests`) |
| --- | --- | --- | --- |
| Edge `adf56b76c` | A frame whose 15-bit header crosses the packet end was not counted, so the frame was skipped (XMA1 packets; XMA2 headers hid it) | Counted with size 0, which routes it to the split-header path | "XMA packet walk counts a frame whose header crosses the packet end", "XMA split frame headers decode every frame for XMA1 and XMA2 packets" |
| Edge `5dd1cdbbf` | `loop_start` one bit before a frame boundary sent the loop through the split-header path and ended the stream (Tekken Tag 2) | `GetPacketInfo` reports the first frame at or after an offset; `Decode` adopts it on a loop restart | "XMA packet walk resolves an offset to the next frame boundary", "XMA loop_start one bit before a frame loops like an exact loop_start" |
| Edge `9d8210b32` | The next-packet search stepped onto other sub-streams' packets (LEGO cutscene freezes) | Follows a frameless packet's own skip count | "XMA next-packet search follows the sub-stream skip chain" |
| Edge `052365bc0` | The work loop left the current frame half delivered when the input ran out (NBA Live 06 deadlock) | Keeps consuming until the frame is out | "XMA work drains the current frame after the input runs out" |
| Edge `ade7e610b` | The work loop could spin with the context lock held when a pass made no progress | Stops on a pass that moved nothing; adapted so a buffer swap or priming the start-padding carry counts as progress | "XMA work returns when a looping frame keeps failing", "XMA single-frame loop keeps producing audio" |
| Canary `7e98ae6de`, `09dbe2cd3`, `505697f98` | Output invalidation: invalidate only a full ring, reset write to read when starved of input (NFS Carbon/MW), invalidate an empty ring after a consume-only pass (565507E4) | Same rules at the end of `Work()` and in the consume-only path | "XMA output stays valid when a kick releases nothing", "XMA kick starved of input resets write to read", "XMA consume-only kick drains the frame left by a full buffer" |
| Edge `8aa50e0e0` + `b0a1ea5f8`, Canary #1214 | `UnregisterClient` destroyed the driver and freed the callback argument while the worker could still be running the guest callback; a late `SubmitFrame` dereferenced a null driver | Per-client callback mutex (outside the `memset` client array); unregister clears the slot under the global lock, waits for the callback without it, then destroys and frees; slot stays reserved until teardown ends; self-unregister from the callback skips the wait; late or invalid submits and unregisters are dropped | `[audio][lifetime]` (4 cases) |

Each fix was checked by disabling it and rebuilding: its tests fail (the
no-progress guard's test reports a timeout and then hangs until the CTest
timeout ends it).

Decoder errors stay observable: a frame FFmpeg rejects, or returns no audio
for, increments `XmaContext::decode_failure_count()` and logs a warning at
1, 2, 4, 8, … failures. It is not replaced with silence. The frame's samples
are missing from the output and the start-padding realignment re-primes
("XMA decode failures are counted and not filled with silence").

## Not adopted

| Upstream | Reason |
| --- | --- |
| Edge PR #236 (emit silence on hard decode errors) | Closed without merging; conceals errors, which the issue rules out |
| Canary PR #748 (rounding in float→int16) | Open; it only changes the scalar fallback in `ConvertFrame`, which x64 builds do not compile (the SSE path already rounds through `_mm_cvtps_epi32`). Not a fix for decode problems |
| Edge `e25bfd824` (signal kick completion on disable) | No local kicker waits: kicks decode inline (local `29eaa8a`) and `WaitForWorkDone` has no callers |
| Edge `1fae8f43a` (decode on the kicking thread) | Already equivalent (local `29eaa8a`) |
| Edge `c26d93763`, `7887efa69` (tick semaphore or submit silence for dead clients) | After the lifetime change an unregistered slot has no driver or callback, so there is nothing to keep alive; late frames are dropped |
| Edge `GetPacketHandle` cross-buffer next-packet lookup (from `b575c6841`'s later Edge form) | Larger restructuring; local `Decode` already moves to the other buffer's first frame on a swap. Revisit with a two-buffer fixture if a title needs it |
| Edge `6e5b8324f` (pace audio subsystem) | Output pacing belongs to the XAudio2 output work, RG-GDK-019 |

## FFmpeg pin

- ReXGlue: `thirdparty/FFmpeg` = wmarti/FFmpeg `0604b464c7`
  (`xenia-ffmpeg-canary-full`, 2026-02-11). Its `wmaprodec.c` xmaframes decoder
  dates from `244cc2f281` (2020-06-28) and has no flush callback.
- Edge: has207/FFmpeg `c4f44071ad` (`xmaframes`, 2026-08-25, "fix xmaframes
  error handling and add a flush callback"), on a much newer FFmpeg base
  (GitHub compare: 21,546 commits ahead, 163 behind ours). Its branch also
  changes first-frame skipping (`d980192e17`) and exposes encoder delay
  (`d1963569c9`).
- Not changed here. ReXGlue compensates for the old decoder in its own code:
  it reopens the codec instead of flushing (`ResetDecoderState`) and realigns
  the 192-sample start padding (`kDecoderStartPadding`). Moving the pin changes
  that sample numbering, so it needs its own change with PCM comparisons. The
  synthetic frames in `tests/unit/audio/xma_context_test.cpp` decode on the
  current pin.

## Test fixtures

The Work()-level tests build streams in memory: silent WMA Pro frames (no
coefficients, sized with subframe fill bits) laid through 2048-byte XMA packets,
decoded by the real FFmpeg decoder over real guest memory. They cover split
headers, frameless packets, loop_start one bit early and exact, output ring
wrap, stereo, decode failures, and consume-only draining. Because the frames are
silent, sample continuity is checked by block accounting, not waveform content.

## Limitations

- No title workload was run. Koei (Canary #1036), Tekken Tag 2, LEGO LOTR,
  Splinter Cell: Double Agent and 007 Legends have no recompiled fixture on this
  machine (007 Legends exists only as a disc image). Their upstream scenes stay
  unchecked locally.
- A guest that unregisters its client while holding a guest lock that its own
  render callback needs would now wait for that callback, and so would deadlock.
  Upstream has not reported this with the same design; a title that does it
  needs a profile or a timeout.
- A pending frame drained by a kick that starts with no valid input is dropped
  by the starved-input rule, as in Canary and Edge.
- Multi-buffer (input buffer 0 → 1) transitions are exercised only through the
  existing swap paths, not a dedicated two-buffer fixture.
