# Mmio handler: system source notes

This record preserves technical and API notes moved from `src/system/mmio_handler.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L40)

```text
// There can be only one handler at a time.
```

## Source note 2, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L50)

```text
// Install exception handler for memory coherence (SharedMemory write tracking).
```

## Source note 3, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L51)

```text
// Note: MMIO operations are handled at the recompiler level via REX_MM_LOAD/STORE
```

## Source note 4, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L52)

```text
// macros that call CheckLoad/CheckStore directly.
```

## Source note 5, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L129)

```text
// Current byte decode index.
```

## Source note 6, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L136)

```text
// MOVBE m32, r32 (store)
```

## Source note 7, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L137)

```text
// https://web.archive.org/web/20170629091435/https://www.tptp.cc/mirrors/siyobik.info/instruction/MOVBE.html
```

## Source note 8, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L138)

```text
// 44 0f 38 f1 a4 02 00     movbe  DWORD PTR [rdx+rax*1+0x0],r12d
```

## Source note 9, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L139)

```text
// 42 0f 38 f1 8c 22 00     movbe  DWORD PTR [rdx+r12*1+0x0],ecx
```

## Source note 10, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L140)

```text
// 0f 38 f1 8c 02 00 00     movbe  DWORD PTR [rdx + rax * 1 + 0x0], ecx
```

## Source note 11, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L145)

```text
// MOVBE r32, m32 (load)
```

## Source note 12, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L146)

```text
// https://web.archive.org/web/20170629091435/https://www.tptp.cc/mirrors/siyobik.info/instruction/MOVBE.html
```

## Source note 13, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L147)

```text
// 44 0f 38 f0 a4 02 00     movbe  r12d,DWORD PTR [rdx+rax*1+0x0]
```

## Source note 14, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L148)

```text
// 42 0f 38 f0 8c 22 00     movbe  ecx,DWORD PTR [rdx+r12*1+0x0]
```

## Source note 15, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L149)

```text
// 46 0f 38 f0 a4 22 00     movbe  r12d,DWORD PTR [rdx+r12*1+0x0]
```

## Source note 16, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L150)

```text
// 0f 38 f0 8c 02 00 00     movbe  ecx,DWORD PTR [rdx+rax*1+0x0]
```

## Source note 17, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L151)

```text
// 0F 38 F0 1C 02           movbe  ebx,dword ptr [rdx+rax]
```

## Source note 18, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L156)

```text
// MOV m32, r32 (store)
```

## Source note 19, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L157)

```text
// https://web.archive.org/web/20170629072136/https://www.tptp.cc/mirrors/siyobik.info/instruction/MOV.html
```

## Source note 20, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L158)

```text
// 44 89 24 02              mov  DWORD PTR[rdx + rax * 1], r12d
```

## Source note 21, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L159)

```text
// 42 89 0c 22              mov  DWORD PTR[rdx + r12 * 1], ecx
```

## Source note 22, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L160)

```text
// 89 0c 02                 mov  DWORD PTR[rdx + rax * 1], ecx
```

## Source note 23, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L165)

```text
// MOV r32, m32 (load)
```

## Source note 24, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L166)

```text
// https://web.archive.org/web/20170629072136/https://www.tptp.cc/mirrors/siyobik.info/instruction/MOV.html
```

## Source note 25, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L167)

```text
// 44 8b 24 02              mov  r12d, DWORD PTR[rdx + rax * 1]
```

## Source note 26, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L168)

```text
// 42 8b 0c 22              mov  ecx, DWORD PTR[rdx + r12 * 1]
```

## Source note 27, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L169)

```text
// 46 8b 24 22              mov  r12d, DWORD PTR[rdx + r12 * 1]
```

## Source note 28, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L170)

```text
// 8b 0c 02                 mov  ecx, DWORD PTR[rdx + rax * 1]
```

## Source note 29, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L175)

```text
// MOV m32, simm32
```

## Source note 30, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L176)

```text
// https://web.archive.org/web/20161017042413/https://www.asmpedia.org/index.php?title=MOV
```

## Source note 31, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L177)

```text
// C7 04 02 02 00 00 00     mov  dword ptr [rdx+rax],2
```

## Source note 32, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L191)

```text
// http://www.sandpile.org/x86/opc_rm.htm
```

## Source note 33, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L192)

```text
// http://www.sandpile.org/x86/opc_sib.htm
```

## Source note 34, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L211)

```text
// RIP-relative not supported.
```

## Source note 35, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L229)

```text
// No index.
```

## Source note 36, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L239)

```text
// Alternate rbp-relative addressing not supported.
```

## Source note 37, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L271)

```text
// Literal loading (PC-relative) is not handled.
```

## Source note 38, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L274)

```text
// Not a load or a store instruction.
```

## Source note 39, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L279)

```text
// Handling MMIO only for single 32-bit values, not for pairs.
```

## Source note 40, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L305)

```text
// `Rt` field (load / store register).
```

## Source note 41, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L308)

```text
// Zero constant rather than a register read.
```

## Source note 42, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L314)

```text
// The base is Xn (for 0...30) or SP (for 31).
```

## Source note 43, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L315)

```text
// `Rn` field (first source register).
```

## Source note 44, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L321)

```text
// LDR|STR Wt|St, [Xn|SP{, #pimm}]
```

## Source note 45, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L378)

```text
// Data Execution Prevention or something else uninteresting.
```

## Source note 46, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L384)

```text
// Quick kill anything outside our mapping.
```

## Source note 47, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L389)

```text
// Access violations are pretty rare, so we can do a linear search here.
```

## Source note 48, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L390)

```text
// Only check if in the virtual range, as we only support virtual ranges.
```

## Source note 49, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L398)

```text
// Address is within the range of this mapping.
```

## Source note 50, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L405)

```text
// Recheck if the pages are still protected (race condition - another thread
```

## Source note 51, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L406)

```text
// clears the watch we just hit).
```

## Source note 52, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L407)

```text
// Do this under the lock so we don't introduce another race condition.
```

## Source note 53, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L414)

```text
// Another thread has cleared this watch. Abort.
```

## Source note 54, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L417)

```text
// The address is not found within any range, so either a write watch or an
```

## Source note 55, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L418)

```text
// actual access violation.
```

## Source note 56, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L443)

```text
// Preserve the base address with the pre- or the post-index offset to write
```

## Source note 57, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L444)

```text
// it after writing the result (since the base address register and the
```

## Source note 58, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L445)

```text
// register to load to may be the same, in which case it should receive the
```

## Source note 59, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L446)

```text
// original base address with the offset).
```

## Source note 60, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L457)

```text
// REX_ARCH_ARM64
```

## Source note 61, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L461)

```text
// Load of a memory value - read from range, swap, and store in the
```

## Source note 62, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L462)

```text
// register.
```

## Source note 63, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L465)

```text
// We swap only if it's not a movbe, as otherwise we are swapping twice.
```

## Source note 64, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L479)

```text
// Register write is ignored for X31.
```

## Source note 65, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L485)

```text
// Store of a register value - read register, swap, write to range.
```

## Source note 66, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L507)

```text
// We swap only if it's not a movbe, as otherwise we are swapping twice.
```

## Source note 67, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L515)

```text
// Write the base address with the pre- or the post-index offset, overwriting
```

## Source note 68, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L516)

```text
// the register to load to if it's the same.
```

## Source note 69, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L525)

```text
// REX_ARCH_ARM64
```

## Source note 70, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/mmio_handler.cpp#L527)

```text
// Advance RIP to the next instruction so that we resume properly.
```
