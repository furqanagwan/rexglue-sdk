# Pipeline cache: graphics source notes

This record preserves technical and API notes moved from `src/graphics/d3d12/pipeline_cache.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L80)

```text
// Generated with `xb buildshaders`.
```

## Source note 2, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L99)

```text
// Generated from shaders/spirv by glslang at build time.
```

## Source note 3, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L170)

```text
// Initialize the command processor thread DXIL objects.
```

## Source note 4, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L195)

```text
// Pick some reasonable amount if couldn't determine the number of cores.
```

## Source note 5, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L198)

```text
// Initialize creation thread synchronization data even if not using creation
```

## Source note 6, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L199)

```text
// threads because they may be used anyway to create pipelines from the
```

## Source note 7, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L200)

```text
// storage.
```

## Source note 8, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L219)

```text
// These compile during gameplay, three quarters of the cores at once; at
```

## Source note 9, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L220)

```text
// normal priority they preempt the command processor and the guest,
```

## Source note 10, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L221)

```text
// which the title sees as a long frame (RG-GDK-038). The draw is skipped
```

## Source note 11, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L222)

```text
// or awaited either way, so creation losing the CPU costs nothing.
```

## Source note 12, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L262)

```text
// Shut down all threads, before destroying the pipelines since they may be
```

## Source note 13, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L263)

```text
// creating them.
```

## Source note 14, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L277)

```text
// Shut down the persistent shader / pipeline storage.
```

## Source note 15, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L280)

```text
// Destroy all pipelines.
```

## Source note 16, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L292)

```text
// Destroy all shaders.
```

## Source note 17, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L305)

```text
// Shut down shader translation.
```

## Source note 18, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L316)

```text
// For files that can be moved between different hosts.
```

## Source note 19, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L317)

```text
// Host PSO blobs - if ever added - should be stored in shaders/local/ (they
```

## Source note 20, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L318)

```text
// currently aren't used because because they may be not very practical -
```

## Source note 21, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L319)

```text
// would need to invalidate them every commit likely, and additional I/O
```

## Source note 22, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L320)

```text
// cost - though D3D's internal validation would possibly be enough to ensure
```

## Source note 23, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L321)

```text
// they are up to date).
```

## Source note 24, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L336)

```text
// Initialize the pipeline storage stream - read pipeline descriptions and
```

## Source note 25, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L337)

```text
// collect used shader modifications to translate.
```

## Source note 26, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L339)

```text
// <Shader hash, modification bits>.
```

## Source note 27, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L344)

```text
// Full ZPD counters change every ROV pixel shader.
```

## Source note 28, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L346)

```text
// The cache shipped with the title seeds this PC's first (RG-GDK-064).
```

## Source note 29, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L389)

```text
// 'XEPS'.
```

## Source note 30, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L391)

```text
// 'DXRO' or 'DXRT'.
```

## Source note 31, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L423)

```text
// Validate file integrity, stop and truncate the stream if data is
```

## Source note 32, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L424)

```text
// corrupted.
```

## Source note 33, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L449)

```text
// Pick some reasonable amount if couldn't determine the number of cores.
```

## Source note 34, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L453)

```text
// Initialize the Xenos shader storage stream.
```

## Source note 35, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L481)

```text
// 'XESH'.
```

## Source note 36, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L488)

```text
// Load and translate shaders written by previous Xenia executions until the
```

## Source note 37, line 489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L489)

```text
// end of the file or until a corrupted one is detected.
```

## Source note 38, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L495)

```text
// Threads overlapping file reading.
```

## Source note 39, line 512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L512)

```text
// If needed and possible, create objects needed for DXIL conversion and
```

## Source note 40, line 513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L513)

```text
// disassembly on this thread.
```

## Source note 41, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L540)

```text
// Translate each needed modification on this thread after performing
```

## Source note 42, line 541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L541)

```text
// modification-independent analysis of the whole shader.
```

## Source note 43, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L550)

```text
// Only try (and delete in case of failure) if it's a new translation.
```

## Source note 44, line 551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L551)

```text
// If it's a shader previously encountered in the game, translation of
```

## Source note 45, line 552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L552)

```text
// which has failed, and the shader storage is loaded later, keep it
```

## Source note 46, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L553)

```text
// this way not to try to translate it again.
```

## Source note 47, line 590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L590)

```text
// Validation failed.
```

## Source note 48, line 597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L597)

```text
// Appeared twice in this file for some reason - skip, otherwise race
```

## Source note 49, line 598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L598)

```text
// condition will be caused by translating twice in parallel.
```

## Source note 50, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L601)

```text
// Loaded from the current storage - don't write again.
```

## Source note 51, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L603)

```text
// Create new threads if the currently existing threads can't keep up
```

## Source note 52, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L604)

```text
// with file reading, but not more than the number of logical processors
```

## Source note 53, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L605)

```text
// minus one.
```

## Source note 54, line 619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L619)

```text
// Request ucode information gathering and translation of all the needed
```

## Source note 55, line 620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L620)

```text
// shaders.
```

## Source note 56, line 659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L659)

```text
// Create the pipelines.
```

## Source note 57, line 663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L663)

```text
// Launch additional creation threads to use all cores to create
```

## Source note 58, line 664

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L664)

```text
// pipelines faster. Will also be using the main thread, so minus 1.
```

## Source note 59, line 781

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L781)

```text
// Submit the pipeline for creation to any available thread.
```

## Source note 60, line 801

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L801)

```text
// Assuming the queue is empty because of
```

## Source note 61, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L802)

```text
// CreateQueuedPipelinesOnProcessorThread.
```

## Source note 62, line 811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L811)

```text
// Cleanup so additional threads can be created later again.
```

## Source note 63, line 814

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L814)

```text
// If the invocation is blocking, all the shader storage
```

## Source note 64, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L815)

```text
// initialization is expected to be done before proceeding, to avoid
```

## Source note 65, line 816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L816)

```text
// latency in the command processor after the invocation.
```

## Source note 66, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L836)

```text
// If any pipeline descriptions were corrupted (or the whole file has excess
```

## Source note 67, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L837)

```text
// bytes in the end), truncate to the last valid pipeline description.
```

## Source note 68, line 854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L854)

```text
// Start the storage writing thread.
```

## Source note 69, line 911

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L911)

```text
// Await creation of all queued pipelines.
```

## Source note 70, line 915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L915)

```text
// Assuming the creation queue is already empty (because the processor
```

## Source note 71, line 916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L916)

```text
// thread also worked on creating the leftover pipelines), so only check
```

## Source note 72, line 917

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L917)

```text
// if there are threads with pipelines currently being created.
```

## Source note 73, line 937

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L937)

```text
// Not started: create it here rather than wait for the queue before it.
```

## Source note 74, line 946

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L946)

```text
// A creation thread has it.
```

## Source note 75, line 991

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L991)

```text
// Hash the input memory and lookup the shader.
```

## Source note 76, line 1000

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1000)

```text
// Shader has been previously loaded.
```

## Source note 77, line 1003

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1003)

```text
// Always create the shader and stash it away.
```

## Source note 78, line 1004

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1004)

```text
// We need to track it even if it fails translation so we know not to try
```

## Source note 79, line 1005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1005)

```text
// again.
```

## Source note 80, line 1109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1109)

```text
// Ensure shaders are translated - needed now for GetCurrentStateDescription.
```

## Source note 81, line 1110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1110)

```text
// Edge flags are not supported yet (because polygon primitives are not).
```

## Source note 82, line 1116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1116)

```text
// Ucode analysis is always needed on the main thread (for modification and
```

## Source note 83, line 1117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1117)

```text
// hash computation). Translation can be deferred to background threads when
```

## Source note 84, line 1118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1118)

```text
// async compilation is enabled.
```

## Source note 85, line 1144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1144)

```text
// Translation attempted previously, but not valid.
```

## Source note 86, line 1191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1191)

```text
// Find an existing pipeline in the cache.
```

## Source note 87, line 1223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1223)

```text
// Submit the pipeline for creation to any available thread.
```

## Source note 88, line 1259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1259)

```text
// Perform translation.
```

## Source note 89, line 1260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1260)

```text
// If this fails the shader will be marked as invalid and ignored later.
```

## Source note 90, line 1267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1267)

```text
// A title's replacement stands in for the translated code, keeping the
```

## Source note 91, line 1268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1268)

```text
// translation's bindings (RG-GDK-067). Domain shaders are not replaced.
```

## Source note 92, line 1324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1324)

```text
// Set up texture and sampler binding layouts.
```

## Source note 93, line 1351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1351)

```text
// Obtain the unique IDs of binding layouts if there are any texture
```

## Source note 94, line 1352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1352)

```text
// bindings or bindless samplers, for invalidation in the command processor.
```

## Source note 95, line 1354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1354)

```text
// Use sampler count for the bindful case because it's the only thing that
```

## Source note 96, line 1355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1355)

```text
// must be the same for layouts to be compatible in this case
```

## Source note 97, line 1356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1356)

```text
// (instruction-specified parameters are used as overrides for actual
```

## Source note 98, line 1357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1357)

```text
// samplers).
```

## Source note 99, line 1433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1433)

```text
// Disassemble the shader for dumping.
```

## Source note 100, line 1442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1442)

```text
// Dump shader files if desired.
```

## Source note 101, line 1451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1451)

```text
// Last: other threads read the translation without the translation lock as
```

## Source note 102, line 1452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1452)

```text
// soon as is_translated() is true.
```

## Source note 103, line 1464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1464)

```text
// Translated shaders needed at least for the root signature, unless in
```

## Source note 104, line 1465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1465)

```text
// placeholder mode (async compilation) where both VS and PS translation
```

## Source note 105, line 1466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1466)

```text
// may be deferred to background threads.
```

## Source note 106, line 1476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1476)

```text
// Initialize all unused fields to zero for comparison/hashing.
```

## Source note 107, line 1485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1485)

```text
// In Direct3D, rasterization (along with pixel counting) is disabled by
```

## Source note 108, line 1486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1486)

```text
// disabling the pixel shader and depth / stencil. However, if rasterization
```

## Source note 109, line 1487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1487)

```text
// should be disabled, the pixel shader must be disabled externally, to ensure
```

## Source note 110, line 1488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1488)

```text
// things like texture binding layout is correct for the shader actually being
```

## Source note 111, line 1489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1489)

```text
// used (don't replace anything here).
```

## Source note 112, line 1500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1500)

```text
// Root signature.
```

## Source note 113, line 1510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1510)

```text
// Vertex shader.
```

## Source note 114, line 1515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1515)

```text
// Index buffer strip cut value.
```

## Source note 115, line 1525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1525)

```text
// Host vertex shader type and primitive topology.
```

## Source note 116, line 1537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1537)

```text
// Quads are emulated as line lists with adjacency.
```

## Source note 117, line 1560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1560)

```text
// Host lines are 1 host pixel wide; a guest line covers 1 guest pixel
```

## Source note 118, line 1561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1561)

```text
// (has207/xenia-edge 7d0a45263).
```

## Source note 119, line 1582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1582)

```text
// The rest doesn't matter when rasterization is disabled (thus no writing to
```

## Source note 120, line 1583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1583)

```text
// anywhere from post-geometry stages and no samples are counted).
```

## Source note 121, line 1589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1589)

```text
// Pixel shader.
```

## Source note 122, line 1596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1596)

```text
// Rasterizer state.
```

## Source note 123, line 1597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1597)

```text
// Because Direct3D 12 doesn't support per-side fill mode and depth bias, the
```

## Source note 124, line 1598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1598)

```text
// values to use depends on the current culling state.
```

## Source note 125, line 1599

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1599)

```text
// If front faces are culled, use the ones for back faces.
```

## Source note 126, line 1600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1600)

```text
// If back faces are culled, it's the other way around.
```

## Source note 127, line 1601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1601)

```text
// If culling is not enabled, assume the developer wanted to draw things in a
```

## Source note 128, line 1602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1602)

```text
// more special way - so if one side is wireframe or has a depth bias, then
```

## Source note 129, line 1603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1603)

```text
// that's intentional (if both sides have a depth bias, the one for the front
```

## Source note 130, line 1604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1604)

```text
// faces is used, though it's unlikely that they will ever be different -
```

## Source note 131, line 1605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1605)

```text
// SetRenderState sets the same offset for both sides).
```

## Source note 132, line 1606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1606)

```text
// Points fill mode (0) also isn't supported in Direct3D 12, but assume the
```

## Source note 133, line 1607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1607)

```text
// developer didn't want to fill the whole primitive and use wireframe (like
```

## Source note 134, line 1608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1608)

```text
// Xenos fill mode 1).
```

## Source note 135, line 1609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1609)

```text
// Here we also assume that only one side is culled - if two sides are culled,
```

## Source note 136, line 1610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1610)

```text
// rasterization will be disabled externally, or the draw call will be dropped
```

## Source note 137, line 1611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1611)

```text
// early if the vertex shader doesn't export to memory.
```

## Source note 138, line 1618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1618)

```text
// The case when both faces are culled should be handled by disabling
```

## Source note 139, line 1619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1619)

```text
// rasterization.
```

## Source note 140, line 1627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1627)

```text
// With ROV, the depth bias is applied in the pixel shader because
```

## Source note 141, line 1628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1628)

```text
// per-sample depth is needed for MSAA.
```

## Source note 142, line 1630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1630)

```text
// Front faces aren't culled.
```

## Source note 143, line 1631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1631)

```text
// Direct3D 12, unfortunately, doesn't support point fill mode.
```

## Source note 144, line 1637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1637)

```text
// Back faces aren't culled.
```

## Source note 145, line 1646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1646)

```text
// Filled front faces only, without culling.
```

## Source note 146, line 1667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1667)

```text
// Depth/stencil. No stencil, always passing depth test and no depth writing
```

## Source note 147, line 1668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1668)

```text
// means depth disabled.
```

## Source note 148, line 1680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1680)

```text
// Per-face masks not supported by Direct3D 12, choose the back face
```

## Source note 149, line 1681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1681)

```text
// ones only if drawing only back faces.
```

## Source note 150, line 1707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1707)

```text
// If not binding the DSV, ignore the format in the hash.
```

## Source note 151, line 1718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1718)

```text
// Render targets and blending state. 32 because of 0x1F mask, for safety
```

## Source note 152, line 1719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1719)

```text
// (all unknown to zero).
```

## Source note 153, line 1721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1721)

```text
/*  0 */
```

## Source note 154, line 1722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1722)

```text
/*  1 */
```

## Source note 155, line 1723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1723)

```text
/*  2 */
```

## Source note 156, line 1724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1724)

```text
/*  3 */
```

## Source note 157, line 1725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1725)

```text
/*  4 */
```

## Source note 158, line 1726

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1726)

```text
/*  5 */
```

## Source note 159, line 1727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1727)

```text
/*  6 */
```

## Source note 160, line 1728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1728)

```text
/*  7 */
```

## Source note 161, line 1729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1729)

```text
/*  8 */
```

## Source note 162, line 1730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1730)

```text
/*  9 */
```

## Source note 163, line 1731

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1731)

```text
/* 10 */
```

## Source note 164, line 1732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1732)

```text
/* 11 */
```

## Source note 165, line 1734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1734)

```text
/* 12 */
```

## Source note 166, line 1736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1736)

```text
/* 13 */
```

## Source note 167, line 1738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1738)

```text
/* 14 */
```

## Source note 168, line 1740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1740)

```text
/* 15 */
```

## Source note 169, line 1741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1741)

```text
/* 16 */
```

## Source note 170, line 1743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1743)

```text
// Like kBlendFactorMap, but with color modes changed to alpha. Some
```

## Source note 171, line 1744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1744)

```text
// pipelines aren't created in 545407E0 because a color mode is used for
```

## Source note 172, line 1745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1745)

```text
// alpha.
```

## Source note 173, line 1747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1747)

```text
/*  0 */
```

## Source note 174, line 1748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1748)

```text
/*  1 */
```

## Source note 175, line 1749

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1749)

```text
/*  2 */
```

## Source note 176, line 1750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1750)

```text
/*  3 */
```

## Source note 177, line 1751

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1751)

```text
/*  4 */
```

## Source note 178, line 1752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1752)

```text
/*  5 */
```

## Source note 179, line 1753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1753)

```text
/*  6 */
```

## Source note 180, line 1754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1754)

```text
/*  7 */
```

## Source note 181, line 1755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1755)

```text
/*  8 */
```

## Source note 182, line 1756

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1756)

```text
/*  9 */
```

## Source note 183, line 1757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1757)

```text
/* 10 */
```

## Source note 184, line 1758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1758)

```text
/* 11 */
```

## Source note 185, line 1759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1759)

```text
/* 12 */
```

## Source note 186, line 1761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1761)

```text
/* 13 */
```

## Source note 187, line 1763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1763)

```text
/* 14 */
```

## Source note 188, line 1765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1765)

```text
/* 15 */
```

## Source note 189, line 1766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1766)

```text
/* 16 */
```

## Source note 190, line 1768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1768)

```text
// While it's okay to specify fewer render targets in the pipeline state
```

## Source note 191, line 1769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1769)

```text
// (even fewer than written by the shader) than actually bound to the
```

## Source note 192, line 1770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1770)

```text
// command list (though this kind of truncation may only happen at the end -
```

## Source note 193, line 1771

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1771)

```text
// DXGI_FORMAT_UNKNOWN *requires* a null RTV descriptor to be bound), not
```

## Source note 194, line 1772

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1772)

```text
// doing that because sample counts of all render targets bound via
```

## Source note 195, line 1773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1773)

```text
// OMSetRenderTargets, even those beyond NumRenderTargets, apparently must
```

## Source note 196, line 1774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1774)

```text
// have their sample count matching the one set in the pipeline - however if
```

## Source note 197, line 1775

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1775)

```text
// we set NumRenderTargets to 0 and also disable depth / stencil, the sample
```

## Source note 198, line 1776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1776)

```text
// count must be set to 1 - while the command list may still have
```

## Source note 199, line 1777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1777)

```text
// multisampled render targets bound (happens in 4D5307E6 main menu).
```

## Source note 200, line 1811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1811)

```text
// 2 is not supported in ForcedSampleCount on Nvidia.
```

## Source note 201, line 1817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1817)

```text
// Direct3D 12 requires the sample count to be 1 when no color or depth /
```

## Source note 202, line 1818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1818)

```text
// stencil render targets are bound.
```

## Source note 203, line 1864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1864)

```text
// RDEF, ISGN, OSG5, SHEX, STAT.
```

## Source note 204, line 1867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1867)

```text
// Allocate space for the container header and the blob offsets.
```

## Source note 205, line 1876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1876)

```text
// Resource definition
```

## Source note 206, line 1881

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1881)

```text
// Not needed, as the next operation done is resize, to allocate the space for
```

## Source note 207, line 1882

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1882)

```text
// both the blob header and the resource definition header.
```

## Source note 208, line 1883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1883)

```text
// shader_out.resize(rdef_position_dwords);
```

## Source note 209, line 1885

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1885)

```text
// RDEF header - the actual definitions will be written if needed.
```

## Source note 210, line 1887

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1887)

```text
// Generator name.
```

## Source note 211, line 1896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1896)

```text
// Generator name is right after the header.
```

## Source note 212, line 1906

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1906)

```text
// Need point parameters from the system constants (lines only use the NDC
```

## Source note 213, line 1907

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1907)

```text
// size of a guest pixel).
```

## Source note 214, line 1909

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1909)

```text
// Constant types - float2 only.
```

## Source note 215, line 1910

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1910)

```text
// Names.
```

## Source note 216, line 1914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1914)

```text
// Types.
```

## Source note 217, line 1930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1930)

```text
// - float2 xe_point_constant_diameter
```

## Source note 218, line 1931

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1931)

```text
// - float2 xe_point_screen_diameter_to_ndc_radius
```

## Source note 219, line 1937

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1937)

```text
// Names.
```

## Source note 220, line 1943

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1943)

```text
// Constants.
```

## Source note 221, line 1952

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1952)

```text
// float2 xe_point_constant_diameter
```

## Source note 222, line 1970

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1970)

```text
// float2 xe_point_screen_diameter_to_ndc_radius
```

## Source note 223, line 1990

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1990)

```text
// Constant buffers - xe_system_cbuffer only.
```

## Source note 224, line 1992

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1992)

```text
// Names.
```

## Source note 225, line 1996

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L1996)

```text
// Constant buffers.
```

## Source note 226, line 2031

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2031)

```text
// Bindings - xe_system_cbuffer only.
```

## Source note 227, line 2046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2046)

```text
// Pointers in the header.
```

## Source note 228, line 2069

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2069)

```text
// Input signature
```

## Source note 229, line 2072

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2072)

```text
// Clip and cull distances are tightly packed together into registers, but
```

## Source note 230, line 2073

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2073)

```text
// have separate signature parameters with each being a vec4-aligned window.
```

## Source note 231, line 2080

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2080)

```text
// Interpolators, position, clip and cull distances (parameters containing
```

## Source note 232, line 2081

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2081)

```text
// only clip or cull distances, and also one parameter containing both if
```

## Source note 233, line 2082

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2082)

```text
// present), point size.
```

## Source note 234, line 2088

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2088)

```text
// Reserve space for the header and the parameters.
```

## Source note 235, line 2094

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2094)

```text
// Names (after the parameters).
```

## Source note 236, line 2115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2115)

```text
// Header and parameters.
```

## Source note 237, line 2121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2121)

```text
// Header.
```

## Source note 238, line 2127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2127)

```text
// Parameters.
```

## Source note 239, line 2133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2133)

```text
// Interpolators (TEXCOORD#).
```

## Source note 240, line 2148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2148)

```text
// Position (SV_Position).
```

## Source note 241, line 2159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2159)

```text
// Clip and cull distances (SV_ClipDistance#, SV_CullDistance#).
```

## Source note 242, line 2195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2195)

```text
// Point size (XEPSIZE).
```

## Source note 243, line 2221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2221)

```text
// Output signature
```

## Source note 244, line 2224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2224)

```text
// Interpolators, point coordinates, position, clip distances.
```

## Source note 245, line 2228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2228)

```text
// Reserve space for the header and the parameters.
```

## Source note 246, line 2235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2235)

```text
// Names (after the parameters).
```

## Source note 247, line 2252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2252)

```text
// Header and parameters.
```

## Source note 248, line 2258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2258)

```text
// Header.
```

## Source note 249, line 2264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2264)

```text
// Parameters.
```

## Source note 250, line 2270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2270)

```text
// Interpolators (TEXCOORD#).
```

## Source note 251, line 2284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2284)

```text
// Point coordinates (XESPRITETEXCOORD).
```

## Source note 252, line 2297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2297)

```text
// Position (SV_Position).
```

## Source note 253, line 2307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2307)

```text
// Clip distances (SV_ClipDistance#).
```

## Source note 254, line 2338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2338)

```text
// Shader program
```

## Source note 255, line 2346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2346)

```text
// Reserve space for the length token.
```

## Source note 256, line 2369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2369)

```text
// Point to a strip of 2 triangles.
```

## Source note 257, line 2376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2376)

```text
// Triangle to a strip of 2 triangles.
```

## Source note 258, line 2383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2383)

```text
// 4 vertices passed via kLineWithAdjacency to a strip of 2 triangles.
```

## Source note 259, line 2390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2390)

```text
// Line (of a list or a strip) to a strip of 2 triangles.
```

## Source note 260, line 2406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2406)

```text
// Clip and cull plane declarations are separate in FXC-generated code even
```

## Source note 261, line 2407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2407)

```text
// for a single register.
```

## Source note 262, line 2432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2432)

```text
// At least 1 temporary register needed to discard primitives with NaN
```

## Source note 263, line 2433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2433)

```text
// position.
```

## Source note 264, line 2460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2460)

```text
// Note that after every emit, all o# become initialized and must be written
```

## Source note 265, line 2461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2461)

```text
// to again.
```

## Source note 266, line 2462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2462)

```text
// Also, FXC generates only movs (from statically or dynamically indexed
```

## Source note 267, line 2463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2463)

```text
// v[#][#], from r#, or from a literal) to o# for some reason.
```

## Source note 268, line 2464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2464)

```text
// emit_then_cut_stream must not be used - it crashes the shader compiler of
```

## Source note 269, line 2465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2465)

```text
// AMD Software: Adrenalin Edition 23.3.2 on RDNA 3 if it's conditional (after
```

## Source note 270, line 2466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2466)

```text
// a `retc` or inside an `if`), and it doesn't seem to be generated by FXC or
```

## Source note 271, line 2467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2467)

```text
// DXC at all.
```

## Source note 272, line 2469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2469)

```text
// Discard the whole primitive if any vertex has a NaN position (may also be
```

## Source note 273, line 2470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2470)

```text
// set to NaN for emulation of vertex killing with the OR operator).
```

## Source note 274, line 2480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2480)

```text
// Cull the whole primitive if any cull distance for all vertices in the
```

## Source note 275, line 2481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2481)

```text
// primitive is < 0.
```

## Source note 276, line 2482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2482)

```text
// For point lists with ps_ucp_mode 3, user cull plane distances are
```

## Source note 277, line 2483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2483)

```text
// calculated per expanded vertex later.
```

## Source note 278, line 2507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2507)

```text
// Expand the point sprite, with left-to-right, top-to-bottom UVs.
```

## Source note 279, line 2516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2516)

```text
// The vertex shader's header writes -1.0 to point_size by default, so
```

## Source note 280, line 2517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2517)

```text
// any non-negative value means that it was overwritten by the
```

## Source note 281, line 2518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2518)

```text
// translated vertex shader, and needs to be used instead of the
```

## Source note 282, line 2519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2519)

```text
// constant size. The per-vertex diameter is already clamped in the
```

## Source note 283, line 2520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2520)

```text
// vertex shader (combined with making it non-negative).
```

## Source note 284, line 2527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2527)

```text
// 4D5307F1 has zero-size snowflakes, drop them quicker, and also drop
```

## Source note 285, line 2528

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2528)

```text
// points with a constant size of zero since point lists may also be used
```

## Source note 286, line 2529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2529)

```text
// as just "compute" with memexport.
```

## Source note 287, line 2530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2530)

```text
// XY may contain the point size with the per-vertex override applied, use
```

## Source note 288, line 2531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2531)

```text
// Z as temporary.
```

## Source note 289, line 2536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2536)

```text
// Transform the diameter in the guest screen coordinates to radius in the
```

## Source note 290, line 2537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2537)

```text
// normalized device coordinates, and then to the clip space by
```

## Source note 291, line 2538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2538)

```text
// multiplying by W.
```

## Source note 292, line 2617

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2617)

```text
// Same interpolators for the entire sprite.
```

## Source note 293, line 2622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2622)

```text
// Top-left, top-right, bottom-left, bottom-right order (chosen
```

## Source note 294, line 2623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2623)

```text
// arbitrarily, simply based on clockwise meaning front with
```

## Source note 295, line 2624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2624)

```text
// FrontCounterClockwise = FALSE, but faceness is ignored for
```

## Source note 296, line 2625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2625)

```text
// non-polygon primitive types).
```

## Source note 297, line 2626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2626)

```text
// Bottom is -Y in Direct3D NDC, +V in point sprite coordinates.
```

## Source note 298, line 2631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2631)

```text
// FXC generates only `mov`s for o#, use temporary registers (r0.zw, as
```

## Source note 299, line 2632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2632)

```text
// r0.xy already used for the point size) for calculations.
```

## Source note 300, line 2643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2643)

```text
// Convert host clip space back to guest clip space before applying
```

## Source note 301, line 2644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2644)

```text
// user clip planes.
```

## Source note 302, line 2698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2698)

```text
// Construct a strip with the fourth vertex generated by mirroring a
```

## Source note 303, line 2699

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2699)

```text
// vertex across the longest edge (the diagonal).
```

## Source note 304, line 2701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2701)

```text
// Possible options:
```

## Source note 305, line 2703

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2703)

```text
// 0---1
```

## Source note 306, line 2705

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2705)

```text
// | / |  - 12 is the longest edge, strip 0123 (most commonly used)
```

## Source note 307, line 2706

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2706)

```text
// |/  |    v3 = v0 + (v1 - v0) + (v2 - v0), or v3 = -v0 + v1 + v2
```

## Source note 308, line 2707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2707)

```text
// 2--[3]
```

## Source note 309, line 2709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2709)

```text
// 1---2
```

## Source note 310, line 2711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2711)

```text
// | / |  - 20 is the longest edge, strip 1203
```

## Source note 311, line 2713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2713)

```text
// 0--[3]
```

## Source note 312, line 2715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2715)

```text
// 2---0
```

## Source note 313, line 2717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2717)

```text
// | / |  - 01 is the longest edge, strip 2013
```

## Source note 314, line 2719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2719)

```text
// 1--[3]
```

## Source note 315, line 2721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2721)

```text
// Input vertices are implicitly indexable, dcl_indexRange is not needed
```

## Source note 316, line 2722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2722)

```text
// for the first dimension of a v[#][#] index.
```

## Source note 317, line 2724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2724)

```text
// Get squares of edge lengths into r0.xyz to choose the longest edge.
```

## Source note 318, line 2725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2725)

```text
// r0.x = ||12||^2
```

## Source note 319, line 2729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2729)

```text
// r0.y = ||20||^2
```

## Source note 320, line 2733

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2733)

```text
// r0.z = ||01||^2
```

## Source note 321, line 2738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2738)

```text
// Find the longest edge, and select the strip vertex indices into r0.xyz.
```

## Source note 322, line 2739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2739)

```text
// r0.w = 12 > 20
```

## Source note 323, line 2742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2742)

```text
// r0.x = 12 > 01
```

## Source note 324, line 2745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2745)

```text
// r0.x = 12 > 20 && 12 > 01
```

## Source note 325, line 2750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2750)

```text
// 12 is the longest edge, the first triangle in the strip is 012.
```

## Source note 326, line 2755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2755)

```text
// r0.x = 20 > 01
```

## Source note 327, line 2758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2758)

```text
// If 20 is the longest edge, the first triangle in the strip is 120.
```

## Source note 328, line 2759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2759)

```text
// Otherwise, it's 201.
```

## Source note 329, line 2765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2765)

```text
// Emit the triangle in the strip that consists of the original vertices.
```

## Source note 330, line 2787

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2787)

```text
// Construct the fourth vertex using r1 as temporary storage, including
```

## Source note 331, line 2788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2788)

```text
// for the final operation as FXC generates only `mov`s for o#.
```

## Source note 332, line 2823

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2823)

```text
// Build the triangle strip from the original quad vertices in the
```

## Source note 333, line 2824

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2824)

```text
// 0, 1, 3, 2 order (like specified for GL_QUAD_STRIP).
```

## Source note 334, line 2850

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2850)

```text
// Host lines are rasterized 1 host pixel wide, but a guest line covers
```

## Source note 335, line 2851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2851)

```text
// 1 guest pixel, draw_resolution_scale host pixels. Expand the segment
```

## Source note 336, line 2852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2852)

```text
// into a quad 1 guest pixel wide centered on the line, each end keeping
```

## Source note 337, line 2853

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2853)

```text
// its own attributes (has207/xenia-edge 7d0a45263).
```

## Source note 338, line 2855

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2855)

```text
// The NDC radius of a 1 guest pixel diameter: half a guest pixel.
```

## Source note 339, line 2868

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2868)

```text
// The ends in half guest pixels (NDC over half a guest pixel's NDC
```

## Source note 340, line 2869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2869)

```text
// size), so the direction is in screen space whatever the aspect:
```

## Source note 341, line 2870

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2870)

```text
// r1.xy for the first, r2.xy for the second.
```

## Source note 342, line 2876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2876)

```text
// r2.xy = direction.
```

## Source note 343, line 2878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2878)

```text
// Drop zero-length (and NaN) lines: nothing to expand, and no normal.
```

## Source note 344, line 2883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2883)

```text
// Unit normal (-dy, dx), then half a guest pixel along it in the NDC:
```

## Source note 345, line 2884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2884)

```text
// r2.xy.
```

## Source note 346, line 2899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2899)

```text
// The offset in the clip space is the NDC offset times W.
```

## Source note 347, line 2923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2923)

```text
// Write the actual number of temporary registers used.
```

## Source note 348, line 2926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2926)

```text
// Write the shader program length in dwords.
```

## Source note 349, line 2957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L2957)

```text
// Container header
```

## Source note 350, line 3001

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3001)

```text
// Root signature.
```

## Source note 351, line 3004

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3004)

```text
// Index buffer strip cut value.
```

## Source note 352, line 3017

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3017)

```text
// Primitive topology, vertex, hull, domain and geometry shaders.
```

## Source note 353, line 3019

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3019)

```text
// SPIR-V -> DXIL (RG-GDK-032): every stage, helper pixel shaders included,
```

## Source note 354, line 3020

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3020)

```text
// is DXIL (a pipeline can't mix DXBC and DXIL).
```

## Source note 355, line 3025

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3025)

```text
// The guest shader is the domain shader, linked with the host vertex
```

## Source note 356, line 3026

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3026)

```text
// and hull shaders.
```

## Source note 357, line 3168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3168)

```text
// Fallback vertex shaders are not needed on Direct3D 12.
```

## Source note 358, line 3192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3192)

```text
// Pixel shader.
```

## Source note 359, line 3194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3194)

```text
// Set above.
```

## Source note 360, line 3205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3205)

```text
// Hybrid occlusion query draw without a guest pixel shader: the coverage
```

## Source note 361, line 3206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3206)

```text
// still has to be counted (xenia-canary PR #1218).
```

## Source note 362, line 3218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3218)

```text
// VIZ surveys only mark the ZPass counter.
```

## Source note 363, line 3237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3237)

```text
// Bind an empty PS to force rasterization.
```

## Source note 364, line 3238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3238)

```text
// D3D drops PS-less draws without depth/stencil writes, breaking
```

## Source note 365, line 3239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3239)

```text
// occlusion queries (4541096E, 5553083B). From xenia-canary PR #1218.
```

## Source note 366, line 3245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3245)

```text
// Geometry shader.
```

## Source note 367, line 3252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3252)

```text
// Rasterizer state.
```

## Source note 368, line 3272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3272)

```text
// With non-square resolution scaling, make sure the worst-case impact is
```

## Source note 369, line 3273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3273)

```text
// reverted (slope only along the scaled axis), thus max. More bias is better
```

## Source note 370, line 3274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3274)

```text
// than less bias, because less bias means Z fighting with the background is
```

## Source note 371, line 3275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3275)

```text
// more likely.
```

## Source note 372, line 3283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3283)

```text
// Only 1, 4, 8 and (not on all GPUs) 16 are allowed, using sample 0 as 0
```

## Source note 373, line 3284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3284)

```text
// and 3 as 1 for 2x instead (not exactly the same sample positions, but
```

## Source note 374, line 3285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3285)

```text
// still top-left and bottom-right - however, this can be adjusted with
```

## Source note 375, line 3286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3286)

```text
// programmable sample positions).
```

## Source note 376, line 3295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3295)

```text
// Sample mask and description.
```

## Source note 377, line 3306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3306)

```text
// Using sample 0 as 0 and 3 as 1 for 2x instead (not exactly the same
```

## Source note 378, line 3307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3307)

```text
// sample positions, but still top-left and bottom-right - however, this
```

## Source note 379, line 3308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3308)

```text
// can be adjusted with programmable sample positions).
```

## Source note 380, line 3317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3317)

```text
// Depth/stencil.
```

## Source note 381, line 3322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3322)

```text
// Comparison functions are the same in Direct3D 12 but plus one (minus
```

## Source note 382, line 3323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3323)

```text
// one, bit 0 for less, bit 1 for equal, bit 2 for greater).
```

## Source note 383, line 3331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3331)

```text
// Stencil operations are the same in Direct3D 12 too but plus one.
```

## Source note 384, line 3354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3354)

```text
// Render targets and blending.
```

## Source note 385, line 3365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3365)

```text
// 8 entries for safety since 3 bits from the guest are passed directly.
```

## Source note 386, line 3373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3373)

```text
// Null RTV descriptors can be used for slots with DXGI_FORMAT_UNKNOWN
```

## Source note 387, line 3374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3374)

```text
// in the pipeline state.
```

## Source note 388, line 3402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3402)

```text
// Disable rasterization if needed (parameter combinations that make no
```

## Source note 389, line 3403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3403)

```text
// difference when rasterization is disabled have already been handled in
```

## Source note 390, line 3404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3404)

```text
// GetCurrentStateDescription) the way it's disabled in Direct3D by design
```

## Source note 391, line 3405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3405)

```text
// (disabling a pixel shader and depth / stencil).
```

## Source note 392, line 3414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3414)

```text
// Create the D3D12 pipeline state object.
```

## Source note 393, line 3426

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3426)

```text
// With the debug layer (d3d12_debug), its reasons.
```

## Source note 394, line 3458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3458)

```text
// Don't leak anything in unused bits.
```

## Source note 395, line 3517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3517)

```text
// Need to swap because the hash is calculated for the shader with guest
```

## Source note 396, line 3518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3518)

```text
// endianness.
```

## Source note 397, line 3603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3603)

```text
// Check if need to shut down or set the completion event and dequeue the
```

## Source note 398, line 3604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3604)

```text
// pipeline if there is any.
```

## Source note 399, line 3609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3609)

```text
// Last pipeline in the queue created - signal the event if requested.
```

## Source note 400, line 3619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3619)

```text
// Take the pipeline from the queue and increment the busy thread count
```

## Source note 401, line 3620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3620)

```text
// until the pipeline is created - other threads must be able to dequeue
```

## Source note 402, line 3621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3621)

```text
// requests, but can't set the completion event until the pipelines are
```

## Source note 403, line 3622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3622)

```text
// fully created (rather than just started creating).
```

## Source note 404, line 3626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3626)

```text
// Created by an AwaitPipeline already.
```

## Source note 405, line 3641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3641)

```text
// Pipeline created - the thread is not busy anymore, safe to set the
```

## Source note 406, line 3642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3642)

```text
// completion event if needed (at the next iteration, or in some other
```

## Source note 407, line 3643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3643)

```text
// thread).
```

## Source note 408, line 3680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3680)

```text
// As xenia-edge's D3D12 pipeline cache configures it for Mesa spirv_to_dxil.
```

## Source note 409, line 3681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3681)

```text
/*all=*/
```

## Source note 410, line 3682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3682)

```text
// Pixel (not sample) interlock: D3D12's rasterizer-ordered views.
```

## Source note 411, line 3684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3684)

```text
// Manual barycentric interpolation through SV_Barycentrics.
```

## Source note 412, line 3692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3692)

```text
/*native_2x_msaa_no_attachments=*/
```

## Source note 413, line 3694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3694)

```text
/*precise_interpolation=*/
```

## Source note 414, line 3748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3748)

```text
// An empty entry is a cached failure.
```

## Source note 415, line 3752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3752)

```text
// The conversion is the expensive step, outside the lock; two threads
```

## Source note 416, line 3753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3753)

```text
// converting the same shader keep the first result.
```

## Source note 417, line 3760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3760)

```text
/*lower_to_bindless=*/
```

## Source note 418, line 3776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3776)

```text
// The SPIR-V host tessellation vertex and hull shaders for a tessellation mode
```

## Source note 419, line 3777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3777)

```text
// and domain, as the DXBC ones are chosen in CreateD3D12Pipeline
```

## Source note 420, line 3778

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3778)

```text
// (has207/xenia-edge GetMesaTessHostSpirv). False for an invalid combination.
```

## Source note 421, line 3790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3790)

```text
// The edge factors come through the index buffer.
```

## Source note 422, line 3858

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3858)

```text
// The domain shader's modification holds the domain and the mode.
```

## Source note 423, line 3871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3871)

```text
/*lower_to_bindless=*/
```

## Source note 424, line 3878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3878)

```text
// Once per domain shader and modification, as xenia-edge logs it.
```

## Source note 425, line 3904

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3904)

```text
/*lower_to_bindless=*/
```

## Source note 426, line 3907

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3907)

```text
// Depth and stencil are in the EDRAM buffer, so without a guest pixel
```

## Source note 427, line 3908

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3908)

```text
// shader one still has to run the in-shader depth / stencil test.
```

## Source note 428, line 3958

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3958)

```text
// VIZ surveys only mark the ZPass counter.
```

## Source note 429, line 3968

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3968)

```text
// As the DXBC path: float24 depth converted in the shader, else an empty
```

## Source note 430, line 3969

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L3969)

```text
// shader so D3D doesn't drop a draw writing nothing (occlusion queries).
```

## Source note 431, line 4001

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4001)

```text
// The same SPIR-V version and float controls as the guest shaders, so the
```

## Source note 432, line 4002

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4002)

```text
// stages link.
```

## Source note 433, line 4012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4012)

```text
/*lower_to_bindless=*/
```

## Source note 434, line 4026

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4026)

```text
// Vertex shaders, and domain shaders with the host tessellation stages; the
```

## Source note 435, line 4027

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4027)

```text
// *AsTriangleStrip fallbacks are Vulkan-only.
```

## Source note 436, line 4039

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4039)

```text
// A title's replacement shaders are DXBC: their draws stay on that path.
```

## Source note 437, line 4059

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4059)

```text
/*ps_param_gen_used=*/
```

## Source note 438, line 4064

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4064)

```text
/*apply_polygon_offset_in_shader=*/
```

## Source note 439, line 4071

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4071)

```text
// SPIR-V here for the draw's bindings; DXIL when the pipeline is created.
```

## Source note 440, line 4079

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4079)

```text
// The fixed function state as for DXBC, then the DXIL shaders.
```

## Source note 441, line 4086

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4086)

```text
/*for_placeholder=*/
```

## Source note 442, line 4107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4107)

```text
// Selects the EDRAM depth-only pixel shader for the guest sample count,
```

## Source note 443, line 4108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4108)

```text
// which host_msaa_samples doesn't keep (2x is drawn as 4x).
```

## Source note 444, line 4125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4125)

```text
// The SPIR-V is ready, so creation needs no guest translation: on the
```

## Source note 445, line 4126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4126)

```text
// creation threads with async_shader_compilation, as DXBC pipelines are,
```

## Source note 446, line 4127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4127)

```text
// else here.
```

## Source note 447, line 4158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4158)

```text
// Still being created on a creation thread: IssueDraw skips or awaits it.
```

## Source note 448, line 4171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4171)

```text
// The guest shaders go to the shader storage as the DXBC path's translated
```

## Source note 449, line 4172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4172)

```text
// ones do; DXIL draws may never translate them to DXBC.
```

## Source note 450, line 4268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/pipeline_cache.cpp#L4268)

```text
// namespace rex::graphics::d3d12
```
