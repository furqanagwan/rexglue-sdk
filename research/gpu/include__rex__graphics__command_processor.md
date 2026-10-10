# Command processor: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/command_processor.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L53)

```text
// Occlusion queries - ZPD report mode (occlusion_query cvar).
```

## Source note 2, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L55)

```text
// Fake counter walk, no real GPU queries (fake)
```

## Source note 3, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L56)

```text
// Real queries, speculative writes biased visible (fast)
```

## Source note 4, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L57)

```text
// Fast, but replays cached zero deltas too (fast-alt)
```

## Source note 5, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L58)

```text
// Real queries, waits before writeback (strict)
```

## Source note 6, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L63)

```text
// Host query pool capacity.
```

## Source note 7, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L66)

```text
// Clock backstop for strict retire, triggered on the first failed guest wait.
```

## Source note 8, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L68)

```text
// The fast modes only need to keep queue growth in check.
```

## Source note 9, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L71)

```text
// Cap for the fast-mode cached delta map. Games reuse a small set of report
```

## Source note 10, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L72)

```text
// addresses so this should never be hit, but prevents unbounded growth if a
```

## Source note 11, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L73)

```text
// title cycles through unique addresses. Clearing the cache has no
```

## Source note 12, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L74)

```text
// correctness impact - it only removes speculative writeback hints.
```

## Source note 13, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L78)

```text
// Lock must be held when changing data in this structure.
```

## Source note 14, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L80)

```text
// Dimensions of the framebuffer textures. Should match window size.
```

## Source note 15, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L83)

```text
// Current front buffer, being drawn to the screen.
```

## Source note 16, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L85)

```text
// Current back buffer, being updated by the CP.
```

## Source note 17, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L87)

```text
// Backend data
```

## Source note 18, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L89)

```text
// Whether the back buffer is dirty and a swap is pending.
```

## Source note 19, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L129)

```text
// "Desired" is for the external thread managing the post-processing effect.
```

## Source note 20, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L132)

```text
// Implementations must not make assumptions that the front buffer will
```

## Source note 21, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L133)

```text
// necessarily be a resolve destination - it may be a texture generated by any
```

## Source note 22, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L134)

```text
// means like written to by the CPU or loaded from a file (the disclaimer
```

## Source note 23, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L135)

```text
// screen right in the beginning of 4D530AA4 is not a resolved render target,
```

## Source note 24, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L136)

```text
// for instance).
```

## Source note 25, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L140)

```text
// May be called not only from the command processor thread when the command
```

## Source note 26, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L141)

```text
// processor is paused, and the termination of this function may be explicitly
```

## Source note 27, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L142)

```text
// awaited.
```

## Source note 28, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L161)

```text
// Backend detail for a long frame's log line (frame_stats_interval), covering
```

## Source note 29, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L162)

```text
// the time since the last call. Empty when the backend does not measure.
```

## Source note 30, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L205)

```text
// Used by strict ZPD to distinguish normal in flight latency from a
```

## Source note 31, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L206)

```text
// genuinely stuck report.
```

## Source note 32, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L212)

```text
// ZPD occlusion queries, ported from xenia-canary 3d233a5b2 (PR #1218).
```

## Source note 33, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L223)

```text
// One EVENT_WRITE_ZPD. Measures the host query segments since the previous
```

## Source note 34, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L224)

```text
// report and owes the guest one write of the running counter. Reports
```

## Source note 35, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L225)

```text
// retire strictly in stream order.
```

## Source note 36, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L228)

```text
// Set by the event that ends the measurement.
```

## Source note 37, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L230)

```text
// Guest sample counts. Each segment is normalized by its own scale area
```

## Source note 38, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L231)

```text
// when it resolves.
```

## Source note 39, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L233)

```text
// Submission containing the most recently closed segment's resolve.
```

## Source note 40, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L236)

```text
// Fast modes write a guess at event time and correct it on retire.
```

## Source note 41, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L237)

```text
// The guessed delta is kept so later guesses can be re-based.
```

## Source note 42, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L241)

```text
// For strict, when a report holds the D3D sentinel.
```

## Source note 43, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L242)

```text
// Only these are worth blocking a wait for.
```

## Source note 44, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L252)

```text
// Host query segment open for the ZPD report and/or VIZ ID currently being
```

## Source note 45, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L253)

```text
// measured. Both read the same resolve (xenia-canary #1111).
```

## Source note 46, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L256)

```text
// The segment's draws count Total in the pixel shaders (hybrid query).
```

## Source note 47, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L260)

```text
// The segment counts for the current report.
```

## Source note 48, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L262)

```text
// The VIZ ID the segment measures, if any.
```

## Source note 49, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L264)

```text
// The segment holds VIZ survey draws, which no report counts.
```

## Source note 50, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L273)

```text
// Backend acquires a pool slot, records BeginQuery, tracks it internally.
```

## Source note 51, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L277)

```text
// Backend records EndQuery, queues a resolve for the active slot and the
```

## Source note 52, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L278)

```text
// VIZ predicate if there's a VIZ consumer. report_handle is invalid without
```

## Source note 53, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L279)

```text
// a report consumer.
```

## Source note 54, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L284)

```text
// Backend drains completed resolves and calls OnZPDQueryResolved and
```

## Source note 55, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L285)

```text
// OnVIZQueryResolved for each.
```

## Source note 56, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L287)

```text
// Backend waits for all pending segments of report_handle to resolve.
```

## Source note 57, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L292)

```text
// Queues the current interval at report_address and starts the next one.
```

## Source note 58, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L294)

```text
// Opens a new host query segment when CanOpenZPDQuery is true.
```

## Source note 59, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L296)

```text
// Closes the current segment at a submission boundary. The report stays
```

## Source note 60, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L297)

```text
// open and a new segment will open at the next opportunity.
```

## Source note 61, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L303)

```text
// Splits the open segment when the draw scale or hybrid Total counting
```

## Source note 62, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L304)

```text
// changes, so each segment normalizes with one scale and counts one way, and
```

## Source note 63, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L305)

```text
// when the VIZ ID or survey state changes. Also opens a pending segment, once
```

## Source note 64, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L306)

```text
// per draw.
```

## Source note 65, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L309)

```text
// VIZ_QUERY has the scan converter track 64 query IDs. An ID is visible when
```

## Source note 66, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L310)

```text
// its geometry is still potentially visible after hi-Z. Without any
```

## Source note 67, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L311)

```text
// hierarchical state, answers come from the survey's query segment instead.
```

## Source note 68, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L312)

```text
// Draws carrying a VIZ token then get predicated on the GPU. Anything
```

## Source note 69, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L313)

```text
// unmeasured, for whatever reason, stays visible (xenia-canary #1111).
```

## Source note 70, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L320)

```text
// Survey reached the backend during this generation.
```

## Source note 71, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L322)

```text
// OR of the resolved segments for this generation.
```

## Source note 72, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L324)

```text
// Something went wrong while measuring; this doesn't mean not-visible.
```

## Source note 73, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L327)

```text
// The backend has a survey result ready to use for predication.
```

## Source note 74, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L329)

```text
// Once the predicate no longer covers the full unresolved query, later
```

## Source note 75, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L330)

```text
// segments can't make it exact again.
```

## Source note 76, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L334)

```text
// Surveys ride the query segments as a consumer, see ActiveZPDSegment.
```

## Source note 77, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L337)

```text
// Backend calls this for every draw under an active ID. Measured only if it
```

## Source note 78, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L338)

```text
// ran inside a segment carrying the ID.
```

## Source note 79, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L340)

```text
// Backend reports a resolved segment here.
```

## Source note 80, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L342)

```text
// Whether a draw with a VIZ token runs. If it does, viz_draw_predicate_ is
```

## Source note 81, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L343)

```text
// set when the backend has to predicate it. Memexport and copy draws pass
```

## Source note 82, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L344)

```text
// through untouched, since a cull or a predicate would lose their side
```

## Source note 83, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L345)

```text
// effects.
```

## Source note 84, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L347)

```text
// Backend waits for the submission holding a VIZ segment's resolve.
```

## Source note 85, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L349)

```text
// The backend stages a survey's result into its predicate buffer while the
```

## Source note 86, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L350)

```text
// generation can still use it, and arms or blocks the ID accordingly.
```

## Source note 87, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L366)

```text
// Whether the draw being issued runs under an armed predicate.
```

## Source note 88, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L380)

```text
// Called by backends when a host query resolve completes.
```

## Source note 89, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L381)

```text
// Accumulates the normalized sample counts into the report.
```

## Source note 90, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L384)

```text
// Queued or current report, nullptr once retired. Handles are issued in
```

## Source note 91, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L385)

```text
// order, so the queue is indexed by the front handle.
```

## Source note 92, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L387)

```text
// Handles a strict report the guest is waiting on while the ring is empty.
```

## Source note 93, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L389)

```text
// Called from PrepareForWait and submission boundaries so retired reports
```

## Source note 94, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L390)

```text
// reach the guest before it loops again. Fast modes give up on a stuck front
```

## Source note 95, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L391)

```text
// report after kFastZPDRetireDeadlineMs.
```

## Source note 96, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L393)

```text
// Guest writeback.
```

## Source note 97, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L446)

```text
// "Actual" is for the command processor thread, to be read by the
```

## Source note 98, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L447)

```text
// implementations.
```

## Source note 99, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L450)

```text
// Shared readback resolve mode with backend legacy-flag alias support.
```

## Source note 100, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L452)

```text
// Shared memexport readback enable state with backend legacy-flag override support.
```

## Source note 101, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L465)

```text
// MicroEngine binary from PM4_ME_INIT
```

## Source note 102, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L480)

```text
// Some titles submit writes beyond the emulated register file range in PM4
```

## Source note 103, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L481)

```text
// packets. Preserve these values so dependent packet logic can still observe
```

## Source note 104, line 482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L482)

```text
// them instead of dropping the write entirely.
```

## Source note 105, line 493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L493)

```text
// By default (such as for tools), post-processing is disabled.
```

## Source note 106, line 494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L494)

```text
// "Desired" is for the external thread managing the post-processing effect.
```

## Source note 107, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L501)

```text
// The report the next event will end. No handle means nothing is measuring.
```

## Source note 108, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L504)

```text
// OpenZPDQuery is running (a nested open would double-book the slot).
```

## Source note 109, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L506)

```text
// The 64 slots of PA_SC_VIZ_QUERY_STATUS_0/1.
```

## Source note 110, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L508)

```text
// Predicate for the draw being issued, set by PM4.
```

## Source note 111, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L510)

```text
// Segments with an unresolved VIZ consumer.
```

## Source note 112, line 512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L512)

```text
// Reports owed to the guest, in stream order.
```

## Source note 113, line 514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L514)

```text
// Strict reports containing the D3D sentinel the guest polls.
```

## Source note 114, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L517)

```text
// frame_stats_interval: time between guest swaps.
```

## Source note 115, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L520)

```text
// Host ticks this frame spent waiting for guest commands, and in
```

## Source note 116, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L521)

```text
// WAIT_REG_MEM, to attribute long frames to the guest or to this thread.
```

## Source note 117, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L525)

```text
// The retired counter advances as intervals retire. The speculative counter
```

## Source note 118, line 526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L526)

```text
// tracks the latest queued report so fast modes can monotonically write
```

## Source note 119, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L527)

```text
// increasing values at EVENT_WRITE_ZPD, using each report's last retired
```

## Source note 120, line 528

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L528)

```text
// delta as its next speculative prediction.
```

## Source note 121, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L535)

```text
// Uptime in ms when the current retire backstop was armed.
```

## Source note 122, line 538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L538)

```text
// Set by the backend when resolution scale changes.
```

## Source note 123, line 542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L542)

```text
// Scale area for the segment being closed.
```

## Source note 124, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L549)

```text
// Set by backend command processors to their legacy memexport readback cvar
```

## Source note 125, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/command_processor.h#L550)

```text
// name (for explicit-override compatibility).
```
