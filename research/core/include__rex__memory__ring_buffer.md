# Ring buffer: core source notes

This record preserves technical and API notes moved from `include/rex/memory/ring_buffer.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/ring_buffer.h#L24)

```text
// Use uint32_t instead of size_t to eliminate REX prefix on x86-64
```

## Source note 2, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/ring_buffer.h#L25)

```text
// instructions in this hot class.
```

## Source note 3, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/ring_buffer.h#L127)

```text
// Fast path for GPU command processor - the hottest path.
```

## Source note 4, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/ring_buffer.h#L128)

```text
// Direct load bypasses generic Read() + memcpy.
```

## Source note 5, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/ring_buffer.h#L129)

```text
// Uses == (not >=) for wrap check: capacity must be a multiple of 4,
```

## Source note 6, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/ring_buffer.h#L130)

```text
// so next_read_offset can only land exactly at capacity, never past it.
```
