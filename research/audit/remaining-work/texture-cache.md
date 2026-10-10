# Texture cache: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/264).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/graphics/d3d12/texture_cache.cpp:133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/texture_cache.cpp#L133)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): The DXGI_FORMAT_R8G8B8A8_U/SNORM conversion is usable for
    // the signed version, separate unsigned and signed load shaders completely
    // (as one doesn't need decompression for this format, while another does).
```

## Note 2: src/graphics/d3d12/texture_cache.cpp:141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/texture_cache.cpp#L141)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): The DXGI_FORMAT_R8G8B8A8_U/SNORM conversion is usable for
    // the signed version, separate unsigned and signed load shaders completely
    // (as one doesn't need decompression for this format, while another does).
```

## Note 3: src/graphics/d3d12/texture_cache.cpp:971

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/texture_cache.cpp#L971)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Disable filtering for texture formats not supporting it.
```

## Note 4: src/graphics/pipeline/texture/cache.cpp:892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/texture/cache.cpp#L892)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Reuse a texture with mip_page unchanged, but base_page
  // previously 0, now not 0, to save memory - common case in streaming.
```

## Note 5: src/graphics/pipeline/texture/info.cpp:322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/texture/info.cpp#L322)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): This doesn't actually make any sense. Force only one mip.
    // Offending title issues: #26, #45
```

## Note 6: include/rex/graphics/pipeline/texture/cache.h:53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/pipeline/texture/cache.h#L53)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Attach the largest LOD to existing textures with a valid
// mip_address but no base ever used yet (no base_address) to save memory
// because textures are streamed this way anyway.
```

## Note 7: include/rex/graphics/pipeline/texture/cache.h:520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/pipeline/texture/cache.h#L520)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Find out the correct contents of unused texture components.
```
