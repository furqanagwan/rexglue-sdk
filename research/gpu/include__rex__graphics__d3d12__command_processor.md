# Command processor: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/d3d12/command_processor.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L65)

```text
// Returns the deferred drawing command list for the currently open
```

## Source note 2, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L66)

```text
// submission.
```

## Source note 3, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L74)

```text
// How DispatchResolveDownscale makes a guest texel from its host block.
```

## Source note 4, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L78)

```text
// Per byte: exact for formats of 8-bit channels (supersampling, ADR-012).
```

## Source note 5, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L82)

```text
// Downscales the scaled resolve of [address, address + length), aligned to
```

## Source note 6, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L83)

```text
// whole scaled addressing groups, into `dest` at `dest_offset`. For resolve
```

## Source note 7, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L84)

```text
// readback and for native resolves (ADR-012). Leaves a UAV barrier on `dest`
```

## Source note 8, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L85)

```text
// pending.
```

## Source note 9, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L91)

```text
// Must be called when a subsystem does something like UpdateTileMappings so
```

## Source note 10, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L92)

```text
// it can be awaited in CheckSubmissionFence(submission_current_) if it was
```

## Source note 11, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L93)

```text
// done after the latest ExecuteCommandLists + Signal.
```

## Source note 12, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L101)

```text
// Returns true if the barrier has been inserted (the new state is different).
```

## Source note 13, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L109)

```text
// Finds or creates root signature for a pipeline.
```

## Source note 14, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L113)

```text
// The fixed root signature of the SPIR-V -> DXIL guest shaders (RG-GDK-032),
```

## Source note 15, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L114)

```text
// or nullptr when that path isn't built or available.
```

## Source note 16, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L127)

```text
// Returns UINT32_MAX if no free descriptors. If the unbounded SRV range for
```

## Source note 17, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L128)

```text
// bindless resources is also used in the root signature of the draw /
```

## Source note 18, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L129)

```text
// dispatch referencing this descriptor, this must only be used to allocate
```

## Source note 19, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L130)

```text
// SRVs, otherwise it won't work on Nvidia Fermi (root signature creation will
```

## Source note 20, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L131)

```text
// fail)!
```

## Source note 21, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L134)

```text
// Request non-contiguous CBV/SRV/UAV descriptors for use only within the next
```

## Source note 22, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L135)

```text
// draw or dispatch command done for internal purposes. May change the current
```

## Source note 23, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L136)

```text
// descriptor heap. If the unbounded SRV range for bindless resources is also
```

## Source note 24, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L137)

```text
// used in the root signature of the draw / dispatch referencing these
```

## Source note 25, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L138)

```text
// descriptors, this must only be used to allocate SRVs, otherwise it won't
```

## Source note 26, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L139)

```text
// work on Nvidia Fermi (root signature creation will fail)!
```

## Source note 27, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L142)

```text
// These are needed often, so they are always allocated.
```

## Source note 28, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L144)

```text
// Both may be bound as one root parameter.
```

## Source note 29, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L149)

```text
// Both may be bound as one root parameter.
```

## Source note 30, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L154)

```text
// SPIR-V -> DXIL memexport draws also read vertices through the SRV
```

## Source note 31, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L155)

```text
// (RG-GDK-032). Bound as one table.
```

## Source note 32, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L176)

```text
// ROV occlusion query counter slots (RG-GDK-010a).
```

## Source note 33, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L182)

```text
// Beyond this point, SRVs are accessible to shaders through an unbounded
```

## Source note 34, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L183)

```text
// range - no descriptors of other types bound to shaders alongside
```

## Source note 35, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L184)

```text
// unbounded ranges - must be located beyond this point.
```

## Source note 36, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L203)

```text
// Returns a single temporary GPU-side buffer within a submission for tasks
```

## Source note 37, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L204)

```text
// like texture untiling and resolving.
```

## Source note 38, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L206)

```text
// This must be called when done with the scratch buffer, to notify the
```

## Source note 39, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L207)

```text
// command processor about the new state in case the buffer was transitioned
```

## Source note 40, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L208)

```text
// by its user.
```

## Source note 41, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L211)

```text
// Returns a pipeline with deferred creation by its handle. May return nullptr
```

## Source note 42, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L212)

```text
// if failed to create the pipeline.
```

## Source note 43, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L217)

```text
// Sets the current cached values to external ones. This is for cache
```

## Source note 44, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L218)

```text
// invalidation primarily. A submission must be open.
```

## Source note 45, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L226)

```text
// Returns the text to display in the GPU backend name in the window title.
```

## Source note 46, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L253)

```text
// Host ticks spent this frame in the parts of command processing that can
```

## Source note 47, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L254)

```text
// stall, for TakeFrameTimingDetail.
```

## Source note 48, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L264)

```text
// Whole calls; they contain the parts above and each other.
```

## Source note 49, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L273)

```text
// Keep the size of the root signature at each stage 13 dwords or less
```

## Source note 50, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L274)

```text
// (better 12 or less) so it fits in user data on AMD. Descriptor tables are
```

## Source note 51, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L275)

```text
// 1 dword, root descriptors are 2 dwords (however, root descriptors require
```

## Source note 52, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L276)

```text
// less setup on the CPU - balance needs to be maintained).
```

## Source note 53, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L278)

```text
// CBVs are set in both bindful and bindless cases via root descriptors.
```

## Source note 54, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L280)

```text
// - Bindful resources - multiple root signatures depending on extra
```

## Source note 55, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L281)

```text
//   parameters.
```

## Source note 56, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L283)

```text
// These are always present.
```

## Source note 57, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L285)

```text
// Very frequently changed, especially for UI draws, and for models drawn in
```

## Source note 58, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L286)

```text
// multiple parts - contains vertex and texture fetch constants.
```

## Source note 59, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L287)

```text
// +2 dwords = 2 in all.
```

## Source note 60, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L288)

```text
// Quite frequently changed (for one object drawn multiple times, for
```

## Source note 61, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L289)

```text
// instance - may contain projection matrices).
```

## Source note 62, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L290)

```text
// +2 = 4 in VS.
```

## Source note 63, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L291)

```text
// Less frequently changed (per-material).
```

## Source note 64, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L292)

```text
// +2 = 4 in PS.
```

## Source note 65, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L293)

```text
// May stay the same across many draws.
```

## Source note 66, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L294)

```text
// +2 = 6 in all.
```

## Source note 67, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L295)

```text
// Pretty rarely used and rarely changed - flow control constants.
```

## Source note 68, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L296)

```text
// +2 = 8 in all.
```

## Source note 69, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L297)

```text
// Changed only when starting a new descriptor heap or when switching
```

## Source note 70, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L298)

```text
// between shared memory as SRV and UAV - shared memory byte address buffer
```

## Source note 71, line 299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L299)

```text
// (as SRV and as UAV, either may be null if not used), and, if ROV is used
```

## Source note 72, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L300)

```text
// for EDRAM, EDRAM R32_UINT UAV.
```

## Source note 73, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L301)

```text
// +1 = 9 in all.
```

## Source note 74, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L305)

```text
// Extra parameter that may or may not exist:
```

## Source note 75, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L306)

```text
// - Pixel textures (+1 = 10 in PS).
```

## Source note 76, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L307)

```text
// - Pixel samplers (+1 = 11 in PS).
```

## Source note 77, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L308)

```text
// - Vertex textures (+1 = 10 in VS).
```

## Source note 78, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L309)

```text
// - Vertex samplers (+1 = 11 in VS).
```

## Source note 79, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L313)

```text
// - Bindless resources - two global root signatures (for non-tessellated
```

## Source note 80, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L314)

```text
//   and tessellated drawing), so these are always present.
```

## Source note 81, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L316)

```text
// +2 = 2 in all.
```

## Source note 82, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L317)

```text
// +2 = 4 in VS.
```

## Source note 83, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L318)

```text
// +2 = 4 in PS.
```

## Source note 84, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L319)

```text
// Changed per-material, texture and sampler descriptor indices.
```

## Source note 85, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L320)

```text
// +2 = 6 in PS.
```

## Source note 86, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L321)

```text
// +2 = 6 in VS.
```

## Source note 87, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L322)

```text
// +2 = 8 in all.
```

## Source note 88, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L323)

```text
// +2 = 10 in all.
```

## Source note 89, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L324)

```text
// Changed only when switching between shared memory as SRV and UAV - shared
```

## Source note 90, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L325)

```text
// memory byte address buffer (as SRV and as UAV, either may be null if not
```

## Source note 91, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L326)

```text
// used).
```

## Source note 92, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L327)

```text
// +1 = 11 in all.
```

## Source note 93, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L328)

```text
// Unbounded sampler descriptor table - changed in case of overflow.
```

## Source note 94, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L329)

```text
// +1 = 12 in all.
```

## Source note 95, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L330)

```text
// Unbounded SRV/UAV descriptor table - never changed.
```

## Source note 96, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L331)

```text
// +1 = 13 in all.
```

## Source note 97, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L336)

```text
// The fixed root signature of the SPIR-V -> DXIL guest shaders (xenia-edge's
```

## Source note 98, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L337)

```text
// Mesa layout): constant buffers in space1, shared memory in space0 t0/u0,
```

## Source note 99, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L338)

```text
// the ZPD counter and EDRAM at u1/u2, runtime data in space31, and texture /
```

## Source note 100, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L339)

```text
// sampler heap index buffers for the bindless lowering.
```

## Source note 101, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L367)

```text
// Gets the indices of optional root parameters. Returns the total parameter
```

## Source note 102, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L368)

```text
// count.
```

## Source note 103, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L373)

```text
// BeginSubmission and EndSubmission may be called at any time. If there's an
```

## Source note 104, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L374)

```text
// open non-frame submission, BeginSubmission(true) will promote it to a
```

## Source note 105, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L375)

```text
// frame. EndSubmission(true) will close the frame no matter whether the
```

## Source note 106, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L376)

```text
// submission has already been closed.
```

## Source note 107, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L377)

```text
// Submission (ExecuteCommandLists) boundaries are implicit full UAV and
```

## Source note 108, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L378)

```text
// aliasing barriers, and also result in common resource state promotion and
```

## Source note 109, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L379)

```text
// decay.
```

## Source note 110, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L381)

```text
// Rechecks submission number and reclaims per-submission resources. Pass 0 as
```

## Source note 111, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L382)

```text
// the submission to await to simply check status, or pass submission_current_
```

## Source note 112, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L383)

```text
// to wait for all queue operations to be completed.
```

## Source note 113, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L385)

```text
// If is_guest_command is true, a new full frame - with full cleanup of
```

## Source note 114, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L386)

```text
// resources and, if needed, starting capturing - is opened if pending (as
```

## Source note 115, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L387)

```text
// opposed to simply resuming after mid-frame synchronization). Returns
```

## Source note 116, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L388)

```text
// whether a submission is open currently and the device is not removed.
```

## Source note 117, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L390)

```text
// If is_swap is true, a full frame is closed - with, if needed, cache
```

## Source note 118, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L391)

```text
// clearing and stopping capturing. Returns whether the submission was done
```

## Source note 119, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L392)

```text
// successfully, if it has failed, leaves it open.
```

## Source note 120, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L394)

```text
// Checks if ending a submission right now would not cause potentially more
```

## Source note 121, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L395)

```text
// delay than it would reduce by making the GPU start working earlier - such
```

## Source note 122, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L396)

```text
// as when there are unfinished graphics pipeline creation requests that would
```

## Source note 123, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L397)

```text
// need to be fulfilled before actually submitting the command list.
```

## Source note 124, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L406)

```text
// Opens a debug marker region for PIX and RenderDoc when markers are
```

## Source note 125, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L407)

```text
// enabled; returns the token for PopDebugMarker. Colors are 0xAARRGGBB.
```

## Source note 126, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L412)

```text
// A debug marker region until the end of the scope, or until the submission
```

## Source note 127, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L413)

```text
// ends if that comes first.
```

## Source note 128, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L427)

```text
// Need to await submission completion before calling.
```

## Source note 129, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L430)

```text
// Request descriptors and automatically rebind the descriptor heap on the
```

## Source note 130, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L431)

```text
// draw command list. Refer to D3D12DescriptorHeapPool::Request for partial /
```

## Source note 131, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L432)

```text
// full update explanation. Doesn't work when bindless descriptors are used.
```

## Source note 132, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L456)

```text
// System constants in SpirvShaderTranslator's layout, constant buffers and
```

## Source note 133, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L457)

```text
// bindless index buffers for a SPIR-V -> DXIL draw (xenia-edge
```

## Source note 134, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L458)

```text
// UpdateBindingsMesa, host render target path).
```

## Source note 135, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L472)

```text
// Returns a buffer for reading GPU data back to the CPU. Assuming
```

## Source note 136, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L473)

```text
// synchronizing immediately after use. Always in COPY_DEST state.
```

## Source note 137, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L505)

```text
// ZPD occlusion queries (CommandProcessor backend hooks).
```

## Source note 138, line 514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L514)

```text
// The 64 VIZ predicates (one uint64 each) SetPredication reads.
```

## Source note 139, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L532)

```text
// Values of submission_fence_.
```

## Source note 140, line 537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L537)

```text
// For awaiting non-submission queue operations such as UpdateTileMappings in
```

## Source note 141, line 538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L538)

```text
// AwaitAllQueueOperationsCompletion when they're queued after the latest
```

## Source note 142, line 539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L539)

```text
// ExecuteCommandLists + Signal, thus won't be awaited by just awaiting the
```

## Source note 143, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L540)

```text
// submission.
```

## Source note 144, line 546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L546)

```text
// Guest frame index, since some transient resources can be reused across
```

## Source note 145, line 547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L547)

```text
// submissions. Values updated in the beginning of a frame.
```

## Source note 146, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L550)

```text
// Submission indices of frames that have already been submitted.
```

## Source note 147, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L569)

```text
// d3d12_capture_frame: begins or ends a programmatic capture (PIX) at the
```

## Source note 148, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L570)

```text
// guest frame boundary it's called at.
```

## Source note 149, line 575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L575)

```text
// Viewport info caching - avoids redundant GetHostViewportInfo recalculation
```

## Source note 150, line 576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L576)

```text
// when viewport-affecting register state hasn't changed between draws.
```

## Source note 151, line 584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L584)

```text
// XSCALE, XOFFSET, YSCALE, YOFFSET, ZSCALE, ZOFFSET
```

## Source note 152, line 585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L585)

```text
// packed: convert_z_to_float24, full_float24, ps_writes_depth
```

## Source note 153, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L592)

```text
// Should bindless textures and samplers be used - many times faster
```

## Source note 154, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L593)

```text
// UpdateBindings than bindful (that becomes a significant bottleneck with
```

## Source note 155, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L594)

```text
// bindful - mainly because of CopyDescriptorsSimple, which takes the majority
```

## Source note 156, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L595)

```text
// of UpdateBindings time, and that's outside the emulator's control even).
```

## Source note 157, line 607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L607)

```text
// Currently bound descriptor heap - updated by RequestViewBindfulDescriptors.
```

## Source note 158, line 609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L609)

```text
// Rationale: textures have 4 KB alignment in guest memory, and there can be
```

## Source note 159, line 610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L610)

```text
// 512 MB / 4 KB in total of them at most, and multiply by 3 for different
```

## Source note 160, line 611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L611)

```text
// swizzles, signedness, and multiple host textures for one guest texture, and
```

## Source note 161, line 612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L612)

```text
// transient descriptors. Though in reality there will be a lot fewer of
```

## Source note 162, line 613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L613)

```text
// course, this is just a "safe" value. The limit is 1000000 for resource
```

## Source note 163, line 614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L614)

```text
// binding tier 2.
```

## Source note 164, line 622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L622)

```text
// <Descriptor index, submission where requested>, sorted by the submission
```

## Source note 165, line 623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L623)

```text
// number.
```

## Source note 166, line 626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L626)

```text
// Direct3D 12 only allows shader-visible heaps with no more than 2048
```

## Source note 167, line 627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L627)

```text
// samplers (due to Nvidia addressing). However, there's also possibly a weird
```

## Source note 168, line 628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L628)

```text
// bug in the Nvidia driver (tested on 440.97 and earlier on Windows 10 1803)
```

## Source note 169, line 629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L629)

```text
// that caused the sampler with index 2047 not to work if a heap with 8 or
```

## Source note 170, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L630)

```text
// less samplers also exists - in case of Xenia, it's the immediate drawer's
```

## Source note 171, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L631)

```text
// sampler heap.
```

## Source note 172, line 640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L640)

```text
// Currently the sampler heap is used only for texture cache samplers, so
```

## Source note 173, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L641)

```text
// individual samplers are never freed, and using a simple linear allocator
```

## Source note 174, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L642)

```text
// inside the current heap without a free list.
```

## Source note 175, line 644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L644)

```text
// <Heap, overflow submission number>, if total sampler count used so far
```

## Source note 176, line 645

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L645)

```text
// exceeds kSamplerHeapSize, and the heap has been switched (this is not a
```

## Source note 177, line 646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L646)

```text
// totally impossible situation considering Direct3D 9 has sampler parameter
```

## Source note 178, line 647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L647)

```text
// state instead of sampler objects, and having one "unimportant" parameter
```

## Source note 179, line 648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L648)

```text
// changed may result in doubling of sampler count). Sorted by the submission
```

## Source note 180, line 649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L649)

```text
// number (so checking if the first can be reused is enough).
```

## Source note 181, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L651)

```text
// D3D12TextureCache::SamplerParameters::value -> indices within the current
```

## Source note 182, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L652)

```text
// bindless sampler heap.
```

## Source note 183, line 655

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L655)

```text
// Root signatures for different descriptor counts.
```

## Source note 184, line 667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L667)

```text
// Bytes 0x0...0x3FF - 256-entry gamma ramp table with B10G10R10X2 data (read
```

## Source note 185, line 668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L668)

```text
// as R10G10B10X2 with swizzle).
```

## Source note 186, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L669)

```text
// Bytes 0x400...0x9FF - 128-entry PWL R16G16 gamma ramp (R - base, G - delta,
```

## Source note 187, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L670)

```text
// low 6 bits of each are zero, 3 elements per entry).
```

## Source note 188, line 673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L673)

```text
// Upload buffer for an image that is the same as gamma_ramp_, but with
```

## Source note 189, line 674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L674)

```text
// kQueueFrames array layers.
```

## Source note 190, line 731

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L731)

```text
// PWL gamma ramp can result in values with more precision than 10bpc. Though
```

## Source note 191, line 732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L732)

```text
// those sub-10bpc bits don't have any noticeable visual effect, so normally
```

## Source note 192, line 733

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L733)

```text
// R10G10B10A2_UNORM is enough. But what's the most important is that for the
```

## Source note 193, line 734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L734)

```text
// original FXAA shader, the luma needs to be written to the alpha channel.
```

## Source note 194, line 735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L735)

```text
// For simplicity (to avoid modifying the FXAA shader and adding more texture
```

## Source note 195, line 736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L736)

```text
// fetches into it), and for the highest quality (preserving all 13 bits that
```

## Source note 196, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L737)

```text
// may be generated by applying the PWL gamma ramp with an increment of 2^3,
```

## Source note 197, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L738)

```text
// and also leaving some space for the result of applying fractional weights
```

## Source note 198, line 739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L739)

```text
// to calculate the luma), using R16G16B16A16_UNORM instead of
```

## Source note 199, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L740)

```text
// R10G10B10X2_UNORM with a separate alpha texture.
```

## Source note 200, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L742)

```text
// Kept in NON_PIXEL_SHADER_RESOURCE state.
```

## Source note 201, line 746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L746)

```text
// Unsubmitted barrier batch.
```

## Source note 202, line 749

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L749)

```text
// <Submission where requested, resource>, sorted by the submission number.
```

## Source note 203, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L764)

```text
// Host query segment currently recording in the open submission.
```

## Source note 204, line 767

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L767)

```text
// Closed segments whose ResolveQueryData is in, or will be in, the given
```

## Source note 205, line 768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L768)

```text
// submission. Retired in submission order once the fence passes.
```

## Source note 206, line 775

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L775)

```text
// Read from the ROV counter slot rather than the occlusion query.
```

## Source note 207, line 777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L777)

```text
// Hybrid RTV query: the occlusion query for ZPass, the slot for Total.
```

## Source note 208, line 779

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L779)

```text
// The VIZ ID the segment measured, if any.
```

## Source note 209, line 786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L786)

```text
// The open query counts in the ROV shaders rather than a D3D12 query.
```

## Source note 210, line 788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L788)

```text
// The open query is a hybrid one: a D3D12 occlusion query for ZPass, and
```

## Source note 211, line 789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L789)

```text
// the pixel shaders counting Total into its slot.
```

## Source note 212, line 791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L791)

```text
// Host render targets with occlusion_query_full_counters: queries around
```

## Source note 213, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L792)

```text
// depth / stencil tested draws without depth writes also count Total
```

## Source note 214, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L793)

```text
// (xenia-canary PR #1218).
```

## Source note 215, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L802)

```text
// The current fixed-function drawing state.
```

## Source note 216, line 812

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L812)

```text
// Currently bound pipeline, either a graphics pipeline from the pipeline
```

## Source note 217, line 813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L813)

```text
// cache (with potentially deferred creation - current_external_pipeline_ is
```

## Source note 218, line 814

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L814)

```text
// nullptr in this case) or a non-Xenos graphics or compute pipeline
```

## Source note 219, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L815)

```text
// (current_guest_pipeline_ is nullptr in this case).
```

## Source note 220, line 819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L819)

```text
// Currently bound graphics root signature.
```

## Source note 221, line 821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L821)

```text
// Extra parameters which may or may not be present.
```

## Source note 222, line 823

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L823)

```text
// Whether root parameters are up to date - reset if a new signature is bound.
```

## Source note 223, line 826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L826)

```text
// System shader constants.
```

## Source note 224, line 829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L829)

```text
// Float constant usage masks of the last draw call.
```

## Source note 225, line 833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L833)

```text
// Constant buffer bindings.
```

## Source note 226, line 845

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L845)

```text
// The SPIR-V -> DXIL path's own (its system constants have another layout,
```

## Source note 227, line 846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L846)

```text
// and draws switch between the paths).
```

## Source note 228, line 857

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L857)

```text
// Whether the latest shared memory and EDRAM buffer binding contains the
```

## Source note 229, line 858

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L858)

```text
// shared memory UAV rather than the SRV.
```

## Source note 230, line 859

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L859)

```text
// Separate descriptor tables for the SRV and the UAV, even though only one is
```

## Source note 231, line 860

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L860)

```text
// accessed dynamically in the shaders, are used to prevent a validation
```

## Source note 232, line 861

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L861)

```text
// message about missing resource states in PIX.
```

## Source note 233, line 864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L864)

```text
// Pages with the descriptors currently used for handling Xenos draw calls.
```

## Source note 234, line 868

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L868)

```text
// Whether the last used texture sampler bindings have been written to the
```

## Source note 235, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L869)

```text
// current view descriptor heap.
```

## Source note 236, line 874

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L874)

```text
// Layout UIDs and last texture and sampler bindings written to the current
```

## Source note 237, line 875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L875)

```text
// descriptor heaps (for bindful) or descriptor index constant buffer (for
```

## Source note 238, line 876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L876)

```text
// bindless) with the last used descriptor layout. Valid only when:
```

## Source note 239, line 877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L877)

```text
// - For bindful, when bindful_#_written_#_ is true.
```

## Source note 240, line 878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L878)

```text
// - For bindless, when cbuffer_binding_descriptor_indices_#_.up_to_date is
```

## Source note 241, line 879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L879)

```text
//   true.
```

## Source note 242, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L884)

```text
// Size of these should be ignored when checking whether these are up to date,
```

## Source note 243, line 885

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L885)

```text
// layout UID should be checked first (they will be different for different
```

## Source note 244, line 886

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L886)

```text
// binding counts).
```

## Source note 245, line 894

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L894)

```text
// Latest bindful descriptor handles used for handling Xenos draw calls.
```

## Source note 246, line 902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L902)

```text
// Current primitive topology.
```

## Source note 247, line 905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L905)

```text
// Temporary storage for memexport stream constants used in the draw.
```

## Source note 248, line 909

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/command_processor.h#L909)

```text
// namespace rex::graphics::d3d12
```
