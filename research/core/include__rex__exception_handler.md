# Exception handler: core source notes

This record preserves technical and API notes moved from `include/rex/exception_handler.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L38)

```text
// ARM64 Register Definitions
```

## Source note 2, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L41)

```text
// NOTE: The order of the registers in the enumerations must match the order in
```

## Source note 3, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L42)

```text
// the string table in host_thread_context.cc, as well as remapping tables in
```

## Source note 4, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L43)

```text
// exception handler implementations.
```

## Source note 5, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L75)

```text
// FP (frame pointer).
```

## Source note 6, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L77)

```text
// LR (link register).
```

## Source note 7, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L84)

```text
// The whole 128 bits of a Vn register are also known as Qn (quadword).
```

## Source note 8, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L119)

```text
// ARM64 thread context structure members
```

## Source note 9, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L120)

```text
// Used within HostThreadContext class via #if REX_ARCH_ARM64
```

## Source note 10, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L132)

```text
// AMD64 Register Definitions
```

## Source note 11, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L137)

```text
// NOTE: The order of the registers in the enumerations must match the order in
```

## Source note 12, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L138)

```text
// the string table in host_thread_context.cc, as well as remapping tables in
```

## Source note 13, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L139)

```text
// exception handler implementations.
```

## Source note 14, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L146)

```text
// The order matches the indices in the instruction encoding, as well as the
```

## Source note 15, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L147)

```text
// Windows CONTEXT structure.
```

## Source note 16, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L184)

```text
// x86-64 thread context structure members
```

## Source note 17, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L185)

```text
// Used within HostThreadContext class via #if REX_ARCH_AMD64
```

## Source note 18, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L233)

```text
// REX_ARCH_AMD64
```

## Source note 19, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L236)

```text
// Host Register Typedef
```

## Source note 20, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L248)

```text
// Host Thread Context
```

## Source note 21, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L313)

```text
// ARM64 Load/Store Decoding (VIXL-derived)
```

## Source note 22, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L316)

```text
// AArch64 load and store decoding based on VIXL.
```

## Source note 23, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L317)

```text
// https://github.com/Linaro/vixl/blob/ae5957cd66517b3f31dbf37e9bf39db6594abfe3/src/aarch64/constants-aarch64.h
```

## Source note 24, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L320)

```text
// All rights reserved.
```

## Source note 25, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L322)

```text
// Redistribution and use in source and binary forms, with or without
```

## Source note 26, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L323)

```text
// modification, are permitted provided that the following conditions are met:
```

## Source note 27, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L326)

```text
//     this list of conditions and the following disclaimer.
```

## Source note 28, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L328)

```text
//     this list of conditions and the following disclaimer in the documentation
```

## Source note 29, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L329)

```text
//     and/or other materials provided with the distribution.
```

## Source note 30, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L330)

```text
//   * Neither the name of ARM Limited nor the names of its contributors may be
```

## Source note 31, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L331)

```text
//     used to endorse or promote products derived from this software without
```

## Source note 32, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L332)

```text
//     specific prior written permission.
```

## Source note 33, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L335)

```text
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
```

## Source note 34, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L336)

```text
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
```

## Source note 35, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L338)

```text
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
```

## Source note 36, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L339)

```text
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
```

## Source note 37, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L340)

```text
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
```

## Source note 38, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L341)

```text
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
```

## Source note 39, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L342)

```text
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
```

## Source note 40, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L343)

```text
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```

## Source note 41, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L345)

```text
// `Instruction address + literal offset` loads.
```

## Source note 42, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L346)

```text
// This includes PRFM_lit.
```

## Source note 43, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L396)

```text
// Determines if an ARM64 instruction is a load, prefetch, or store operation.
```

## Source note 44, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L397)

```text
// Returns true if the instruction is one of these, with is_store_out set to
```

## Source note 45, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L398)

```text
// indicate whether it's a store operation.
```

## Source note 46, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L402)

```text
// Exception Class
```

## Source note 47, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L433)

```text
// Returns the platform-specific thread context info.
```

## Source note 48, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L434)

```text
// Note that certain registers must be modified through Modify* proxy
```

## Source note 49, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L435)

```text
// functions rather than directly:
```

## Source note 50, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L436)

```text
// x86-64:
```

## Source note 51, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L437)

```text
// - General-purpose registers (r##, r8-r15).
```

## Source note 52, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L438)

```text
// - XMM registers.
```

## Source note 53, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L439)

```text
// AArch64:
```

## Source note 54, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L440)

```text
// - General-purpose registers (Xn), including FP and LR.
```

## Source note 55, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L441)

```text
// - SIMD and floating-point registers (Vn).
```

## Source note 56, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L444)

```text
// Returns the program counter where the exception occurred.
```

## Source note 57, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L456)

```text
// Sets the program counter where execution will resume.
```

## Source note 58, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L468)

```text
// The index is relative to X64Register::kIntRegisterFirst.
```

## Source note 59, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L496)

```text
// In case of AV, address that was read from/written to.
```

## Source note 60, line 499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L499)

```text
// In case of AV, what kind of operation caused it.
```

## Source note 61, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L519)

```text
// Exception Handler
```

## Source note 62, line 526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L526)

```text
// Installs an exception handler.
```

## Source note 63, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L527)

```text
// Handlers are called in the order they are installed.
```

## Source note 64, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/exception_handler.h#L530)

```text
// Uninstalls a previously-installed exception handler.
```
