# Ring fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/ring_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L26)

```text
// A NOP packet of `dwords` dwords in total.
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L32)

```text
// WAIT_REG_MEM until the big-endian dword at `address` equals `value`.
```

## Source note 3, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L39)

```text
// Poll interval; 0x100 per millisecond slept.
```

## Source note 4, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L56)

```text
// has207/xenia-edge 29fcaeac3: the guest frees ring space by polling the read
```

## Source note 5, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L57)

```text
// pointer write-back. Published only at the end of a burst, a burst that waits
```

## Source note 6, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L58)

```text
// on the guest partway through never hands back the space it already consumed.
```

## Source note 7, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L65)

```text
// RB_BLKSZ 2: every 4 quadwords, 8 dwords.
```

## Source note 8, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L80)

```text
// While the command processor sits in the WAIT_REG_MEM, the guest must see
```

## Source note 9, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L81)

```text
// everything before it consumed, to within one RB_BLKSZ stride.
```

## Source note 10, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L92)

```text
// The end of every burst publishes the exact position.
```

## Source note 11, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L102)

```text
// The usual RB_BLKSZ 6: every 128 dwords.
```

## Source note 12, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L107)

```text
// Bursts of 3/4 of the ring, each a run of NOPs ending in a MEM_WRITE of its
```

## Source note 13, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L108)

```text
// sequence number, five ring lengths in total. Each Submit waits on the
```

## Source note 14, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/ring_fixture_test.cpp#L109)

```text
// write-back for room and wraps the write pointer, as D3D does.
```
