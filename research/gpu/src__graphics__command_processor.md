# Command processor: graphics source notes

This record preserves technical and API notes moved from `src/graphics/command_processor.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L83)

```text
// "fast" by default, as Canary (since 2025-12-04) and Edge read back by
```

## Source note 2, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L84)

```text
// default: without it, titles that read render-to-texture results on the CPU
```

## Source note 3, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L85)

```text
// see stale memory (Blood Stone computes its exposure from one and turns white).
```

## Source note 4, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L174)

```text
// Initialize the gamma ramps to their default (linear) values - taken from
```

## Source note 5, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L175)

```text
// what games set when starting with the sRGB (return value 1)
```

## Source note 6, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L176)

```text
// VdGetCurrentDisplayGamma.
```

## Source note 7, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L271)

```text
// We've run out of commands to execute.
```

## Source note 8, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L272)

```text
// We spin here waiting for new ones, as the overhead of waiting on our
```

## Source note 9, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L273)

```text
// event is too high.
```

## Source note 10, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L278)

```text
// If we spin around too much, revert to a "low-power" state.
```

## Source note 11, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L283)

```text
// Strict ZPD may still owe the guest a report it's spinning on with
```

## Source note 12, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L284)

```text
// nothing left in the ring.
```

## Source note 13, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L303)

```text
// Execute. Note that we handle wraparound transparently.
```

## Source note 14, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L306)

```text
// ExecutePrimaryBuffer republishes this every read_ptr_update_freq_ dwords
```

## Source note 15, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L307)

```text
// as it drains, this is the final position for the burst.
```

## Source note 16, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L385)

```text
// CP_RB_RPTR_ADDR Ring Buffer Read Pointer Address 0x70C
```

## Source note 17, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L386)

```text
// ptr = RB_RPTR_ADDR, pointer to write back the address to.
```

## Source note 18, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L388)

```text
// CP_RB_CNTL Ring Buffer Control 0x704
```

## Source note 19, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L389)

```text
// block_size = RB_BLKSZ, log2 of the number of quadwords read between
```

## Source note 20, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L390)

```text
// updates of the read pointer. Kept in dwords, the unit read_ptr_index_ and
```

## Source note 21, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L391)

```text
// the write-back use. Usually 6, so 128 dwords.
```

## Source note 22, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L421)

```text
// Volatile for the WAIT_REG_MEM loop.
```

## Source note 23, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L427)

```text
// Scratch register writeback.
```

## Source note 24, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L431)

```text
// Enabled - write to address.
```

## Source note 25, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L438)

```text
// If this is a COHER register, set the dirty flag.
```

## Source note 26, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L439)

```text
// This will block the command processor the next time it WAIT_REG_MEMs
```

## Source note 27, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L440)

```text
// and allow us to synchronize the memory.
```

## Source note 28, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L446)

```text
// Reset the sequential read / write component index (see the M56
```

## Source note 29, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L447)

```text
// DC_LUT_SEQ_COLOR documentation).
```

## Source note 30, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L452)

```text
// Should be in the 256-entry table writing mode.
```

## Source note 31, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L455)

```text
// DC_LUT_SEQ_COLOR is in the red, green, blue order, but the write
```

## Source note 32, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L456)

```text
// enable mask is blue, green, red.
```

## Source note 33, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L462)

```text
// Bits 0:5 are hardwired to zero.
```

## Source note 34, line 489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L489)

```text
// Should be in the PWL writing mode.
```

## Source note 35, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L492)

```text
// Bit 7 of the index is ignored for PWL.
```

## Source note 36, line 494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L494)

```text
// DC_LUT_PWL_DATA is likely in the red, green, blue order because
```

## Source note 37, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L495)

```text
// DC_LUT_SEQ_COLOR is, but the write enable mask is blue, green, red.
```

## Source note 38, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L502)

```text
// Bits 0:5 are hardwired to zero.
```

## Source note 39, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L521)

```text
// Should be in the 256-entry table writing mode.
```

## Source note 40, line 633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L633)

```text
// Status host often has 0x01000000 or 0x03000000.
```

## Source note 41, line 634

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L634)

```text
// This is likely toggling VC (vertex cache) or TC (texture cache).
```

## Source note 42, line 635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L635)

```text
// Or, it also has a direction in here maybe - there is probably
```

## Source note 43, line 636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L636)

```text
// some way to check for dest coherency (what all the COHER_DEST_BASE_*
```

## Source note 44, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L637)

```text
// registers are for).
```

## Source note 45, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L638)

```text
// Best docs I've found on this are here:
```

## Source note 46, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L639)

```text
// https://web.archive.org/web/20160711162346/https://amd-dev.wpengine.netdna-cdn.com/wordpress/media/2013/10/R6xx_R7xx_3D.pdf
```

## Source note 47, line 640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L640)

```text
// https://cgit.freedesktop.org/xorg/driver/xf86-video-radeonhd/tree/src/r6xx_accel.c?id=3f8b6eccd9dba116cc4801e7f80ce21a879c67d2#n454
```

## Source note 48, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L642)

```text
// Volatile because this may be called from the WAIT_REG_MEM loop.
```

## Source note 49, line 665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L665)

```text
// Mark coherent.
```

## Source note 50, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L683)

```text
// Execute commands!
```

## Source note 51, line 688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L688)

```text
// The guest polls the read pointer write-back to see how much ring space it
```

## Source note 52, line 689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L689)

```text
// has, and hardware advances it as the ring drains. Publishing only once the
```

## Source note 53, line 690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L690)

```text
// burst ends leaves the guest waiting on work already done - and with a
```

## Source note 54, line 691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L691)

```text
// WAIT_REG_MEM partway through the burst waiting on the guest in turn,
```

## Source note 55, line 692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L692)

```text
// neither side progresses. So republish every RB_BLKSZ dwords on the way
```

## Source note 56, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L693)

```text
// through (has207/xenia-edge 29fcaeac3). A zero stride means the guest never
```

## Source note 57, line 694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L694)

```text
// armed the write-back.
```

## Source note 58, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L700)

```text
// This probably should be fatal - but we're going to continue anyways.
```

## Source note 59, line 706

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L706)

```text
// remaining only grows back if a malformed packet ran the read offset past
```

## Source note 60, line 707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L707)

```text
// the end of the burst, and then there is nothing honest to publish.
```

## Source note 61, line 710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L710)

```text
// Re-read the target, the guest can re-point or disable the write-back
```

## Source note 62, line 711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L711)

```text
// from its own thread while this drains.
```

## Source note 63, line 714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L714)

```text
// Publishing the read pointer hands that ring space back, so it has to
```

## Source note 64, line 715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L715)

```text
// land after the reads of it.
```

## Source note 65, line 732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L732)

```text
// Execute commands!
```

## Source note 66, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L737)

```text
// Return up a level if we encounter a bad packet.
```

## Source note 67, line 746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L746)

```text
// Execute commands!
```

## Source note 68, line 785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L785)

```text
// Type-0 packet.
```

## Source note 69, line 786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L786)

```text
// Write count registers in sequence to the registers starting at
```

## Source note 70, line 787

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L787)

```text
// (base_index << 2).
```

## Source note 71, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L808)

```text
// Type-1 packet.
```

## Source note 72, line 809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L809)

```text
// Contains two registers of data. Type-0 should be more common.
```

## Source note 73, line 820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L820)

```text
// Type-2 packet.
```

## Source note 74, line 821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L821)

```text
// No-op. Do nothing.
```

## Source note 75, line 826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L826)

```text
// Type-3 packet.
```

## Source note 76, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L837)

```text
// & 1 == predicate - when set, we do bin check to see if we should execute
```

## Source note 77, line 838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L838)

```text
// the packet. Only type 3 packets are affected.
```

## Source note 78, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L839)

```text
// We also skip predicated swaps, as they are never valid (probably?).
```

## Source note 79, line 972

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L972)

```text
// This opcode is used by 5454084E while going / being ingame.
```

## Source note 80, line 994

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L994)

```text
// initialize CP's micro-engine
```

## Source note 81, line 1005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1005)

```text
// skip N 32-bit words to get to the next packet
```

## Source note 82, line 1006

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1006)

```text
// No-op, ignore some data.
```

## Source note 83, line 1015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1015)

```text
// generate interrupt from the command stream
```

## Source note 84, line 1052

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1052)

```text
// A long frame spent mostly waiting for guest commands was the game's own
```

## Source note 85, line 1053

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1053)

```text
// CPU work; one spent busy here was command processing (pipelines,
```

## Source note 86, line 1054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1054)

```text
// uploads, resolves) or a guest wait on the GPU.
```

## Source note 87, line 1075

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1075)

```text
// Xenia-specific VdSwap hook.
```

## Source note 88, line 1076

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1076)

```text
// VdSwap will post this to tell us we need to swap the screen/fire an
```

## Source note 89, line 1077

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1077)

```text
// interrupt.
```

## Source note 90, line 1078

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1078)

```text
// 63 words here, but only the first has any data.
```

## Source note 91, line 1095

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1095)

```text
// indirect buffer dispatch
```

## Source note 92, line 1108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1108)

```text
// wait until a register or memory location is a specific value
```

## Source note 93, line 1134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1134)

```text
// Never.
```

## Source note 94, line 1137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1137)

```text
// Less than reference.
```

## Source note 95, line 1140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1140)

```text
// Less than or equal to reference.
```

## Source note 96, line 1143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1143)

```text
// Equal to reference.
```

## Source note 97, line 1146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1146)

```text
// Not equal to reference.
```

## Source note 98, line 1149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1149)

```text
// Greater than or equal to reference.
```

## Source note 99, line 1152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1152)

```text
// Greater than reference.
```

## Source note 100, line 1160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1160)

```text
// Wait.
```

## Source note 101, line 1164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1164)

```text
// User wants it fast and dangerous.
```

## Source note 102, line 1173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1173)

```text
// Short-circuited exit.
```

## Source note 103, line 1188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1188)

```text
// register read/modify/write
```

## Source note 104, line 1189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1189)

```text
// ? (used during shader upload and edram setup)
```

## Source note 105, line 1195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1195)

```text
// & reg
```

## Source note 106, line 1198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1198)

```text
// & imm
```

## Source note 107, line 1202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1202)

```text
// | reg
```

## Source note 108, line 1205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1205)

```text
// | imm
```

## Source note 109, line 1214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1214)

```text
// Copy Register to Memory (?)
```

## Source note 110, line 1215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1215)

```text
// Count is 2, assuming a Register Addr and a Memory Addr.
```

## Source note 111, line 1248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1248)

```text
// conditional write to memory or register
```

## Source note 112, line 1257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1257)

```text
// Memory.
```

## Source note 113, line 1263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1263)

```text
// Register.
```

## Source note 114, line 1268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1268)

```text
// Never.
```

## Source note 115, line 1271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1271)

```text
// Less than reference.
```

## Source note 116, line 1274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1274)

```text
// Less than or equal to reference.
```

## Source note 117, line 1277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1277)

```text
// Equal to reference.
```

## Source note 118, line 1280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1280)

```text
// Not equal to reference.
```

## Source note 119, line 1283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1283)

```text
// Greater than or equal to reference.
```

## Source note 120, line 1286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1286)

```text
// Greater than reference.
```

## Source note 121, line 1294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1294)

```text
// Write.
```

## Source note 122, line 1296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1296)

```text
// Memory.
```

## Source note 123, line 1302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1302)

```text
// Register.
```

## Source note 124, line 1311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1311)

```text
// generate an event that creates a write to memory when completed
```

## Source note 125, line 1313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1313)

```text
// Writeback initiator.
```

## Source note 126, line 1316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1316)

```text
// Just an event flag? Where does this write?
```

## Source note 127, line 1318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1318)

```text
// Write to an address.
```

## Source note 128, line 1327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1327)

```text
// generate a VS|PS_done event
```

## Source note 129, line 1332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1332)

```text
// Writeback initiator.
```

## Source note 130, line 1336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1336)

```text
// Write counter (GPU vblank counter?).
```

## Source note 131, line 1339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1339)

```text
// Write value.
```

## Source note 132, line 1351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1351)

```text
// generate a screen extent event
```

## Source note 133, line 1354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1354)

```text
// Writeback initiator.
```

## Source note 134, line 1359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1359)

```text
// Let us hope we can fake this.
```

## Source note 135, line 1360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1360)

```text
// This callback tells the driver the xy coordinates affected by a previous
```

## Source note 136, line 1361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1361)

```text
// drawcall.
```

## Source note 137, line 1362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1362)

```text
// https://www.google.com/patents/US20060055701
```

## Source note 138, line 1364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1364)

```text
// min x
```

## Source note 139, line 1365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1365)

```text
// max x
```

## Source note 140, line 1366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1366)

```text
// min y
```

## Source note 141, line 1367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1367)

```text
// max y
```

## Source note 142, line 1368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1368)

```text
// min z
```

## Source note 143, line 1369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1369)

```text
// max z
```

## Source note 144, line 1381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1381)

```text
// Writeback initiator.
```

## Source note 145, line 1385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1385)

```text
// RB_SAMPLE_COUNT_CTL is unused by real hardware.
```

## Source note 146, line 1391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1391)

```text
// Z-Pass Done (ZPD) facilitates all D3D occlusion queries.
```

## Source note 147, line 1392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1392)

```text
// D3D fills the counters (usually ZPass_A + ZPass_B, but some 2005-2006 D3D
```

## Source note 148, line 1393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1393)

```text
// versions use ZFail_A + ZFail_B, and sometimes even both counters' B
```

## Source note 149, line 1394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1394)

```text
// fields are kept zero) with a swapped 0xFFFFFEED sentinel while counting.
```

## Source note 150, line 1395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1395)

```text
// Rather than trying to infer BEGIN and END here, each event is treated as
```

## Source note 151, line 1396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1396)

```text
// a snapshot of a free-running sample counter.
```

## Source note 152, line 1397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1397)

```text
// VIZ_QUERY is a coarse hi-Z visibility test, not strictly an OQ.
```

## Source note 153, line 1402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1402)

```text
// Fake mode, or host queries unavailable. Every interval reports the same
```

## Source note 154, line 1403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1403)

```text
// number of passing samples, so D3D's END - BEGIN is the fake count.
```

## Source note 155, line 1414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1414)

```text
// viz_query_condition is the VIZ token. Bit 8 makes the draw conditional on
```

## Source note 156, line 1415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1415)

```text
// the ID's visibility in bits 0:5, from an earlier PM4_VIZ_QUERY.
```

## Source note 157, line 1433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1433)

```text
// Indexed draw.
```

## Source note 158, line 1436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1436)

```text
// Two separate bounds checks so if there's only one missing register
```

## Source note 159, line 1437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1437)

```text
// value out of two, one uint32_t will be skipped in the command buffer,
```

## Source note 160, line 1438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1438)

```text
// not two.
```

## Source note 161, line 1460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1460)

```text
// The base address must already be word-aligned according to the R6xx
```

## Source note 162, line 1461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1461)

```text
// documentation, but for safety.
```

## Source note 163, line 1477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1477)

```text
// Auto draw.
```

## Source note 164, line 1482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1482)

```text
// Invalid source selection.
```

## Source note 165, line 1488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1488)

```text
// Skip to the next command, for example, if there are immediate indexes that
```

## Source note 166, line 1489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1489)

```text
// we don't support yet.
```

## Source note 167, line 1493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1493)

```text
// A consumer draw whose survey is still outstanding runs under the
```

## Source note 168, line 1494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1494)

```text
// backend's predicate instead of blocking. Surveys themselves are ordinary
```

## Source note 169, line 1495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1495)

```text
// draws here (draw_util::IsVIZSurveyDraw).
```

## Source note 170, line 1521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1521)

```text
// If read the packed correctly, but merely couldn't execute it (because of,
```

## Source note 171, line 1522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1522)

```text
// for instance, features not supported by the host), don't terminate command
```

## Source note 172, line 1523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1523)

```text
// buffer processing as that would leave rendering in a way more inconsistent
```

## Source note 173, line 1524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1524)

```text
// state than just a single dropped draw command.
```

## Source note 174, line 1530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1530)

```text
// "initiate fetch of index buffer and draw"
```

## Source note 175, line 1531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1531)

```text
// Generally used by Xbox 360 Direct3D 9 for kDMA and kAutoIndex sources.
```

## Source note 176, line 1532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1532)

```text
// With a viz query token as the first one.
```

## Source note 177, line 1547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1547)

```text
// "draw using supplied indices in packet"
```

## Source note 178, line 1548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1548)

```text
// Generally used by Xbox 360 Direct3D 9 for kAutoIndex source.
```

## Source note 179, line 1549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1549)

```text
// No viz query token.
```

## Source note 180, line 1555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1555)

```text
// load constant into chip and to memory
```

## Source note 181, line 1556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1556)

```text
// PM4_REG(reg) ((0x4 << 16) | (GSL_HAL_SUBBLOCK_OFFSET(reg)))
```

## Source note 182, line 1557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1557)

```text
//                                     reg - 0x2000
```

## Source note 183, line 1596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1596)

```text
// load constants from memory
```

## Source note 184, line 1640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1640)

```text
// load sequencer instruction memory (pointer-based)
```

## Source note 185, line 1669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1669)

```text
// load sequencer instruction memory (code embedded in packet)
```

## Source note 186, line 1698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1698)

```text
// selective invalidation of state pointers
```

## Source note 187, line 1699

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1699)

```text
/*uint32_t mask =*/
```

## Source note 188, line 1700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1700)

```text
// driver_->InvalidateState(mask);
```

## Source note 189, line 1706

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1706)

```text
// https://www.google.com/patents/US20050195186
```

## Source note 190, line 1707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1707)

```text
// VIZ_QUERY is Xenos' GPU-side conditional rendering. It's not an occlusion
```

## Source note 191, line 1708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1708)

```text
// query like EVENT_WRITE_ZPD: there are no sample counts for the guest and no
```

## Source note 192, line 1709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1709)

```text
// buffer the CPU reads. The scan converter tracks 64 IDs; geometry between
```

## Source note 193, line 1710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1710)

```text
// BEGIN and END updates one of them, and later draw packets carrying the ID
```

## Source note 194, line 1711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1711)

```text
// are discarded when it saw nothing. As an approximation, host occlusion
```

## Source note 195, line 1712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1712)

```text
// queries (or the ROV counter) measure the survey, any passing sample means
```

## Source note 196, line 1713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1713)

```text
// visible, and the consumers run under D3D12 predication (xenia-canary
```

## Source note 197, line 1714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1714)

```text
// #1111).
```

## Source note 198, line 1731

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1731)

```text
// Read back as visible, as before; the predicate decides the draws.
```

## Source note 199, line 1766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1766)

```text
// No survey draw ever reached the backend: a real not-visible.
```

## Source note 200, line 1770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1770)

```text
// Fallbacks are visible, whatever pending segments say.
```

## Source note 201, line 1806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1806)

```text
// Retire the answer once the query is closed and every segment resolved.
```

## Source note 202, line 1821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1821)

```text
// Pick up resolves that already completed.
```

## Source note 203, line 1825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1825)

```text
// The predicate stands in for the answer only while it covers the whole
```

## Source note 204, line 1826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1826)

```text
// query, so not after a fallback or with a segment still open on the ID.
```

## Source note 205, line 1832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1832)

```text
// Don't wait on an open query.
```

## Source note 206, line 1834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1834)

```text
// Segments resolve in submission order, so the newest is the answer.
```

## Source note 207, line 1843

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1843)

```text
// Only culled or predicated draws pay for the memexport and copy checks.
```

## Source note 208, line 1844

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1844)

```text
// Any unanalyzed memexport shader might export.
```

## Source note 209, line 1858

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1858)

```text
// Only called by EVENT_WRITE_ZPD. This closes the query interval since the last
```

## Source note 210, line 1859

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1859)

```text
// event and queues its counter snapshot.
```

## Source note 211, line 1868

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1868)

```text
// See EVENT_WRITE_ZPD for additional information on the pending sentinel.
```

## Source note 212, line 1874

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1874)

```text
// Fast modes write a guess now and correct it when the real delta lands.
```

## Source note 213, line 1875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1875)

```text
// Unknown still means visible. Replaying the last real delta for the same
```

## Source note 214, line 1876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1876)

```text
// report is usually a better guess than one fake sample. fast-alt is the
```

## Source note 215, line 1877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1877)

```text
// same as fast, but can replay zeroes, which often improves correctness
```

## Source note 216, line 1878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1878)

```text
// (545107FC, 454108D4, 4D5307D2), but stale zeroes tend to break occlusion
```

## Source note 217, line 1879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1879)

```text
// culling tests, resulting in popping primitives (4D5308AB, 4D530805).
```

## Source note 218, line 1895

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1895)

```text
// The next report's segment opens at its first draw.
```

## Source note 219, line 1896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1896)

```text
// Report runs without draws between them never use any pool slots.
```

## Source note 220, line 1920

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1920)

```text
// Fall back to fake results for the rest of the session.
```

## Source note 221, line 1930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1930)

```text
// Frees any slots from completed submissions before asking for new ones.
```

## Source note 222, line 1938

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1938)

```text
// Fast modes favor forward progress over accuracy. Report at least one
```

## Source note 223, line 1939

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1939)

```text
// passing sample instead of waiting for a slot to become available.
```

## Source note 224, line 1953

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1953)

```text
// A deferred segment opens at the next opportunity with these consumers.
```

## Source note 225, line 1966

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1966)

```text
// Closes the active host segment without ending the report or the VIZ ID.
```

## Source note 226, line 1967

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1967)

```text
// BeginQuery/EndQuery can't cross D3D12 command list boundaries. The result
```

## Source note 227, line 1968

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1968)

```text
// accumulates across all pieces.
```

## Source note 228, line 1988

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1988)

```text
// The segment is lost but its draws ran, so the query stays visible.
```

## Source note 229, line 1992

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1992)

```text
// The report resumes at the next opportunity if this segment counted for
```

## Source note 230, line 1993

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L1993)

```text
// it, or if it was still waiting for one around a survey.
```

## Source note 231, line 2004

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L2004)

```text
// Surveys are killed after hi-Z on hardware, so no report counts them.
```

## Source note 232, line 2012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L2012)

```text
// Close the segment and start a fresh one for this draw when the draw scale
```

## Source note 233, line 2013

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L2013)

```text
// or hybrid Total counting changed in the middle of a report, when a report
```

## Source note 234, line 2014

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L2014)

```text
// would share a segment with surveys, or when a new ID would inherit earlier
```

## Source note 235, line 2015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L2015)

```text
// draws. Later draws without the ID only err towards visible.
```

## Source note 236, line 2083

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L2083)

```text
// Draw-less queries still can't be written until the reports ahead resolve.
```

## Source note 237, line 2107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L2107)

```text
// Keep what resolved, with a floor of one so culling doesn't flash occluded.
```

## Source note 238, line 2121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/command_processor.cpp#L2121)

```text
// A stuck front report would block everything behind it.
```
