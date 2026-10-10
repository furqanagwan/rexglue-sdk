# D3d12 cpu descriptor pool: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/d3d12/d3d12_cpu_descriptor_pool.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_cpu_descriptor_pool.h#L24)

```text
// Single-descriptor pool with reference counting and unique ownership of
```

## Source note 2, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_cpu_descriptor_pool.h#L25)

```text
// allocations, safe to use in environments where the order of releasing of the
```

## Source note 3, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_cpu_descriptor_pool.h#L26)

```text
// descriptor heap and of allocated descriptors is undefined.
```

## Source note 4, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_cpu_descriptor_pool.h#L32)

```text
// shared_ptr to ensure correct release order with between render targets
```

## Source note 5, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_cpu_descriptor_pool.h#L33)

```text
// and descriptor pools.
```

## Source note 6, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_cpu_descriptor_pool.h#L36)

```text
// Owns a descriptor in the pool exclusively.
```

## Source note 7, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_cpu_descriptor_pool.h#L45)

```text
// If moving to self, don't free.
```

## Source note 8, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_cpu_descriptor_pool.h#L80)

```text
// No point in moving, created only via make_shared.
```

## Source note 9, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_cpu_descriptor_pool.h#L109)

```text
// namespace rex::ui::d3d12
```
