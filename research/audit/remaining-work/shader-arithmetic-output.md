# Shader arithmetic output: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/267).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/graphics/pipeline/shader/dxbc_translator_alu.cpp:329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L329)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Not caring about NaN because no info about the
      // correct order, just using SM4 max here, which replaces them with the
      // non-NaN component (however, there's one nice thing about it is that it
      // may be compiled into max3 + max on GCN).
```

## Note 2: src/graphics/pipeline/shader/dxbc_translator_alu.cpp:964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L964)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(boma): Experimental round to zero for Volition titles (5451080D,
      // 4B4D07F6, 5451086D) that experience camera-independent, batch-boundary
      // vertex explosions with the default round-to-nearest behavior.
      // Real hardware rounding behavior needs to be verified.
      // Source: xenia-canary #1245 (3390fc219b32be4a87777ddd72217259b24dc09e).
```

## Note 3: src/graphics/pipeline/shader/dxbc_translator_memexport.cpp:270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L270)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate how input should be treated for k_8_A, k_8_B,
    // k_8_8_8_8_A.
```

## Note 4: src/graphics/pipeline/shader/dxbc_translator_memexport.cpp:464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L464)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Use extended range conversion.
```

## Note 5: src/graphics/pipeline/shader/dxbc_translator_memexport.cpp:477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L477)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Use extended range conversion.
```

## Note 6: src/graphics/pipeline/shader/dxbc_translator_memexport.cpp:492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_memexport.cpp#L492)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Use extended range conversion.
```

## Note 7: src/graphics/pipeline/shader/dxbc_translator_om.cpp:2937

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_om.cpp#L2937)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Check how alpha test works with NaN on Direct3D 9.
```

## Note 8: src/graphics/pipeline/shader/spirv_translator_alu.cpp:718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L718)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Not caring about NaN because no info about the
      // correct order, just using NMax here, which replaces them with the
      // non-NaN component (however, there's one nice thing about it is that it
      // may be compiled into max3 + max on GCN).
```

## Note 9: src/graphics/pipeline/shader/spirv_translator_alu.cpp:1280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1280)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(boma): Experimental round to zero for Volition titles (5451080D,
      // 4B4D07F6, 5451086D) that experience camera-independent, batch-boundary
      // vertex explosions with the default round-to-nearest behavior.
      // Real hardware rounding behavior needs to be verified.
```

## Note 10: src/graphics/pipeline/shader/spirv_translator_memexport.cpp:414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L414)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate how input should be treated for k_8_A, k_8_B.
```

## Note 11: src/graphics/pipeline/shader/spirv_translator_memexport.cpp:433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L433)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate how input should be treated for k_8_8_8_8_A.
```

## Note 12: src/graphics/pipeline/shader/spirv_translator_rb.cpp:430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L430)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Use OpTerminateInvocation when SPIR-V 1.6 is
        // targeted.
```

## Note 13: src/graphics/pipeline/shader/spirv_translator_rb.cpp:482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L482)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Check how alpha test works with NaN on Direct3D 9.
    // Extract the comparison function (less, equal, greater bits).
```

## Note 14: src/graphics/pipeline/shader/spirv_translator_rb.cpp:563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L563)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Promoted to SPIR-V 1.6 - don't add the extension
          // there.
```

## Note 15: src/graphics/pipeline/shader/spirv_translator_rb.cpp:569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L569)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Use OpTerminateInvocation when SPIR-V 1.6 is
          // targeted.
```

## Note 16: src/graphics/pipeline/shader/spirv_translator_rb.cpp:630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L630)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Use HelperInvocation volatile load on SPIR-V 1.6.
```

## Note 17: src/graphics/pipeline/shader/spirv_translator_rb.cpp:1136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1136)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Gamma as unorm8 check.
```
