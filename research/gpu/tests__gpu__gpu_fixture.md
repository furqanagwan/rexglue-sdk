# Gpu fixture: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/gpu_fixture.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L26)

```text
// Drives the GPU plugin the way a title does, without a title: a Runtime with
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L27)

```text
// no image, the "xenos" plugin loaded through the plugin ABI, a primary ring
```

## Source note 3, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L28)

```text
// buffer in guest physical memory and CP_RB_WPTR writes through the MMIO path.
```

## Source note 4, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L29)

```text
// Packets are appended with Submit() and Flush() waits for a fence packet, so
```

## Source note 5, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L30)

```text
// every result read back afterwards is ordered after all submitted work.
```

## Source note 6, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L35)

```text
// Returns nullptr and sets error when the plugin or the D3D12 device can't
```

## Source note 7, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L36)

```text
// be created, so callers can skip rather than fail. cvars are applied after
```

## Source note 8, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L37)

```text
// REXGLUE_GPU_FIXTURE_CVARS, so they can also set cvars the GPU plugin
```

## Source note 9, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L38)

```text
// registers and that are only read when the GPU starts.
```

## Source note 10, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L45)

```text
// Guest physical memory, returned as a physical address as the GPU sees it.
```

## Source note 11, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L47)

```text
// Writes through the host view of physical memory, which has no access
```

## Source note 12, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L48)

```text
// watches: the GPU emulation's own view, not what a guest CPU write does.
```

## Source note 13, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L50)

```text
// Writes as the guest CPU would, through the guest virtual view the memory
```

## Source note 14, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L51)

```text
// was allocated in, so write watches on GPU-owned pages fire.
```

## Source note 15, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L55)

```text
// Appends packet dwords to the ring and moves the write pointer. Without a
```

## Source note 16, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L56)

```text
// read pointer write-back the ring must not wrap; with one, Submit waits on
```

## Source note 17, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L57)

```text
// the write-back for free space and wraps, as D3D does, and returns false if
```

## Source note 18, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L58)

```text
// the command processor stops making room.
```

## Source note 19, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L60)

```text
// Arms the CP_RB_RPTR write-back at a guest physical address, with
```

## Source note 20, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L61)

```text
// RB_BLKSZ (log2 quadwords between updates) as the guest passes it.
```

## Source note 21, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L65)

```text
// Submits a fence write and waits for the command processor to reach it.
```

## Source note 22, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L68)

```text
// Adapter, driver and capabilities that a fixture result must be recorded
```

## Source note 23, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L69)

```text
// with to be reproducible.
```

## Source note 24, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L72)

```text
// Packet builders. Memory addresses carry the endian swap mode in their low
```

## Source note 25, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L73)

```text
// two bits, as on the real command processor.
```

## Source note 26, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L85)

```text
// 8 KB quadwords = 64 KB.
```

## Source note 27, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/gpu_fixture.h#L95)

```text
// Guest virtual minus physical address for AllocPhysical allocations.
```
