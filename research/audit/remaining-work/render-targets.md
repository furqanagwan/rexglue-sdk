# Render targets: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/263).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/graphics/d3d12/render_target_cache.cpp:189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/render_target_cache.cpp#L189)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Make ROV the default when it's optimized better (for
    // instance, using static shader modifications to pass render target
    // parameters).
```

## Note 2: src/graphics/d3d12/render_target_cache.cpp:1088

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/render_target_cache.cpp#L1088)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Check if this draw call modifies color or depth /
      // stencil, at least coarsely, to prevent useless barriers.
```

## Note 3: src/graphics/d3d12/render_target_cache.cpp:1481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/render_target_cache.cpp#L1481)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Check if NaN propagation defined in the D3D11.3
    // specification can be relied on for 32-bit float render targets.
```

## Note 4: src/graphics/d3d12/render_target_cache.cpp:3641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/render_target_cache.cpp#L3641)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Pipeline state name debug names (lots of variables - but
  // not very important since everything can be derived from the bindings and
  // outputs in a debugger).
```

## Note 5: src/graphics/d3d12/render_target_cache.cpp:4136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/render_target_cache.cpp#L4136)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Reduce scissor to the smallest transfer region for
        // more tiling friendliness.
```

## Note 6: src/graphics/pipeline/render_target/cache.cpp:139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/render_target/cache.cpp#L139)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Use the extended-range encoding in all implementations.
```

## Note 7: src/graphics/pipeline/render_target/cache.cpp:568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/render_target/cache.cpp#L568)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): If really needed for some game on some device, clamp
      // the pitch and generate multiple ranges (each for every row of tiles)
      // with gaps for padding. Very few PowerVR GPUs have 4096, not 8192, as
      // the limit, though with 8192 (on Mali) the actual limit for Xenia is
      // 8160 because tile padding is stored - but 8192 should be extremely rare
      // anyway.
```

## Note 8: src/graphics/pipeline/render_target/cache.cpp:1206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/render_target/cache.cpp#L1206)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): If really needed for some game on some device, clamp the
    // pitch the same way as explained in the comment in Update.
```

## Note 9: include/rex/graphics/d3d12/render_target_cache.h:252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/d3d12/render_target_cache.h#L252)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): With bindless resources, persistently store them in the
    // heap.
```

## Note 10: include/rex/graphics/d3d12/render_target_cache.h:430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/d3d12/render_target_cache.h#L430)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): See if it may be better to sort by the source in the
      // first place, especially when reading the same data multiple times (like
      // to write the stencil bits after depth) for better read locality.
      // Sort by the shader key primarily to reduce pipeline state (context)
      // switches.
```

## Note 11: include/rex/graphics/pipeline/render_target/cache.h:570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/pipeline/render_target/cache.h#L570)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Try to defer clears until the first draw in the next pass
  // (if it uses one or both render targets being cleared) for tile-based GPUs.
```

## Note 12: include/rex/graphics/pipeline/render_target/cache.h:709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/pipeline/render_target/cache.h#L709)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Pool allocator (or a custom red-black tree with one even),
  // since standard containers use dynamic allocation for elements, though
  // changes to this throughout a frame are pretty rare.
```
