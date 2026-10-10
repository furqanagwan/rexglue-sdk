# Ppc codegen: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/259).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/codegen/analyze.cpp:72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/analyze.cpp#L72)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): disabled for now, causes too many false positives
  // functionPointerScan(ctx);
```

## Note 2: src/codegen/builders/control_flow.cpp:134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/control_flow.cpp#L134)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): Figure out if this actually is triggered on real hardware and what would
      // happen?
```

## Note 3: src/codegen/builders/memory.cpp:641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/memory.cpp#L641)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): vectorize
  // NOTE: accounting for the full vector reversal here
```

## Note 4: src/codegen/builders/memory.cpp:650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/memory.cpp#L650)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): vectorize
  // NOTE: accounting for the full vector reversal here
```

## Note 5: src/codegen/builders/memory.cpp:659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/memory.cpp#L659)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): vectorize
  // NOTE: accounting for the full vector reversal here
```

## Note 6: src/codegen/builders/memory.cpp:668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/memory.cpp#L668)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): vectorize
  // NOTE: accounting for the full vector reversal here
```

## Note 7: src/codegen/builders/memory.cpp:678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/memory.cpp#L678)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): vectorize
  // NOTE: accounting for the full vector reversal here
```

## Note 8: src/codegen/builders/vector.cpp:160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/vector.cpp#L160)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: see if we can use rcp safely
```

## Note 9: src/codegen/builders/vector.cpp:397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/vector.cpp#L397)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: vectorize
```

## Note 10: src/codegen/builders/vector.cpp:956

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/vector.cpp#L956)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): vectorize
```

## Note 11: src/codegen/builders/vector.cpp:964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/vector.cpp#L964)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): vectorize
```

## Note 12: src/codegen/builders/vector.cpp:1005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/vector.cpp#L1005)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): vectorize
```

## Note 13: src/codegen/builders/vector.cpp:1072

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/vector.cpp#L1072)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): vectorize
```

## Note 14: src/codegen/builders/vector.cpp:1080

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/vector.cpp#L1080)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): vectorize
```

## Note 15: src/codegen/builders/vector.cpp:1273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/vector.cpp#L1273)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): vectorize
  // NOTE: handling vector reversal here too
```

## Note 16: src/codegen/builders/vector.cpp:1492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/builders/vector.cpp#L1492)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): Vectorize
  // NOTE: handling vector reversal here too
```

## Note 17: src/codegen/function_scanner.cpp:1793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/function_scanner.cpp#L1793)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): Figure out what this voodoo does on real hardware. Its a jump target that
      // points to a null value..?
```

## Note 18: src/codegen/function_scanner.cpp:1826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/function_scanner.cpp#L1826)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): look into this more. what is the expected behavior when the processor executes
    // a null instruction.
```

## Note 19: src/codegen/phase_discover.cpp:272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/phase_discover.cpp#L272)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): THIS IS WIP AND PROB A BAD IDEA LOL LETS SEE
//=============================================================================
```

## Note 20: src/codegen/sig_scanner.cpp:28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/sig_scanner.cpp#L28)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): maybe i wanna scan other sections...
```

## Note 21: src/codegen/sig_scanner.cpp:163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/codegen/sig_scanner.cpp#L163)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): mayhaps have signatures memset, memmove, memcpy, strcmp patterns
```

## Note 22: include/rex/vec128.h:251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/vec128.h#L251)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): Figure out why clang doesn't line forward declarations of
// inline functions.
```
