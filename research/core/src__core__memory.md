# Memory: core source notes

This record preserves technical and API notes moved from `src/core/memory.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L39)

```text
// This works around a GCC bug
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L40)

```text
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=100801
```

## Source note 3, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L65)

```text
// handle residual elements
```

## Source note 4, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L83)

```text
// handle residual elements
```

## Source note 5, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L104)

```text
// handle residual elements
```

## Source note 6, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L122)

```text
// handle residual elements
```

## Source note 7, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L143)

```text
// handle residual elements
```

## Source note 8, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L161)

```text
// handle residual elements
```

## Source note 9, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L176)

```text
// handle residual elements
```

## Source note 10, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L191)

```text
// handle residual elements
```

## Source note 11, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L198)

```text
// Although NEON offers vector rev instructions (like vrev32q_u8), they are
```

## Source note 12, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L199)

```text
// slower in benchmarks. Also, using uint8x16xN_t wasn't any faster in the
```

## Source note 13, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L200)

```text
// benchmarks, hence we use just use one SIMD register to minimize residual
```

## Source note 14, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L201)

```text
// processing.
```

## Source note 15, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L220)

```text
// These pointer increments will be combined with the load/stores (ldr/str)
```

## Source note 16, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L221)

```text
// into single instructions (at least by clang)
```

## Source note 17, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory.cpp#L314)

```text
// Generic routines.
```
