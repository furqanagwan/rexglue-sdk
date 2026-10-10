# Packet disassembler: graphics source notes

This record preserves technical and API notes moved from `src/graphics/packet_disassembler.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L113)

```text
// initialize CP's micro-engine
```

## Source note 2, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L119)

```text
// skip N 32-bit words to get to the next packet
```

## Source note 3, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L120)

```text
// No-op, ignore some data.
```

## Source note 4, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L126)

```text
// generate interrupt from the command stream
```

## Source note 5, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L132)

```text
// graphics_system_->DispatchInterruptCallback(1, n);
```

## Source note 6, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L138)

```text
// Xenia-specific VdSwap hook.
```

## Source note 7, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L139)

```text
// VdSwap will post this to tell us we need to swap the screen/fire an
```

## Source note 8, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L140)

```text
// interrupt.
```

## Source note 9, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L141)

```text
// 63 words here, but only the first has any data.
```

## Source note 10, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L149)

```text
// indirect buffer dispatch
```

## Source note 11, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L157)

```text
// wait until a register or memory location is a specific value
```

## Source note 12, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L168)

```text
// register read/modify/write
```

## Source note 13, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L169)

```text
// ? (used during shader upload and edram setup)
```

## Source note 14, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L178)

```text
// conditional write to memory or register
```

## Source note 15, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L190)

```text
// generate an event that creates a write to memory when completed
```

## Source note 16, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L197)

```text
// generate a VS|PS_done event
```

## Source note 17, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L206)

```text
// generate a screen extent event
```

## Source note 18, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L214)

```text
// initiate fetch of index buffer and draw
```

## Source note 19, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L215)

```text
// dword0 = viz query info
```

## Source note 20, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L224)

```text
// Indexed draw.
```

## Source note 21, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L232)

```text
// Auto draw.
```

## Source note 22, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L234)

```text
// Unknown source select.
```

## Source note 23, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L240)

```text
// draw using supplied indices in packet
```

## Source note 24, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L247)

```text
// 'SrcSel=AutoIndex'
```

## Source note 25, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L254)

```text
// load constant into chip and to memory
```

## Source note 26, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L255)

```text
// PM4_REG(reg) ((0x4 << 16) | (GSL_HAL_SUBBLOCK_OFFSET(reg)))
```

## Source note 27, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L256)

```text
//                                     reg - 0x2000
```

## Source note 28, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L302)

```text
// load constants from memory
```

## Source note 29, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L333)

```text
// Hrm, ?
```

## Source note 30, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L334)

```text
// memory::load_and_swap<uint32_t>(membase_ + GpuToCpu(address + n * 4));
```

## Source note 31, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L352)

```text
// load sequencer instruction memory (pointer-based)
```

## Source note 32, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L365)

```text
// load sequencer instruction memory (code embedded in packet)
```

## Source note 33, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L378)

```text
// selective invalidation of state pointers
```

## Source note 34, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L388)

```text
// bin_mask_ = (bin_mask_ & 0xFFFFFFFF00000000ull) | value;
```

## Source note 35, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L396)

```text
// bin_mask_ =
```

## Source note 36, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L397)

```text
//  (bin_mask_ & 0xFFFFFFFFull) | (static_cast<uint64_t>(value) << 32);
```

## Source note 37, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L404)

```text
// bin_select_ = (bin_select_ & 0xFFFFFFFF00000000ull) | value;
```

## Source note 38, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L412)

```text
// bin_select_ =
```

## Source note 39, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L413)

```text
//  (bin_select_ & 0xFFFFFFFFull) | (static_cast<uint64_t>(value) <<
```

## Source note 40, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L414)

```text
//  32);
```

## Source note 41, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L418)

```text
// Ignored packets - useful if breaking on the default handler below.
```

## Source note 42, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L419)

```text
// 0xC0015000 usually 2 words, 0xFFFFFFFF / 0x00000000
```

## Source note 43, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/packet_disassembler.cpp#L424)

```text
// 0xC0015100 usually 2 words, 0xFFFFFFFF / 0xFFFFFFFF
```
