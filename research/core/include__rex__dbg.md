# Dbg: core source notes

This record preserves technical and API notes moved from `include/rex/dbg.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L22)

```text
// Returns true if a debugger is attached to this process.
```

## Source note 2, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L23)

```text
// The state may change at any time (attach after launch, etc), so do not
```

## Source note 3, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L24)

```text
// cache this value. Determining if the debugger is attached is expensive,
```

## Source note 4, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L25)

```text
// though, so avoid calling it frequently.
```

## Source note 5, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L28)

```text
// Breaks into the debugger if it is attached.
```

## Source note 6, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L29)

```text
// If no debugger is present, a signal will be raised.
```

## Source note 7, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L36)

```text
// Prints a message to the attached debugger.
```

## Source note 8, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L37)

```text
// This bypasses the normal logging mechanism. If no debugger is attached it's
```

## Source note 9, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L38)

```text
// likely to no-op.
```

## Source note 10, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L50)

```text
// CPU profiling zones
```

## Source note 11, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L56)

```text
// GPU profiling stubs -- backend code uses TracyVkZone/TracyD3D12Zone directly.
```

## Source note 12, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L60)

```text
// Thread profiling
```

## Source note 13, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L68)

```text
// Fiber profiling
```

## Source note 14, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L85)

```text
// Counter profiling -- plot to Tracy
```

## Source note 15, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L92)

```text
// !REXGLUE_ENABLE_PROFILING
```

## Source note 16, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L94)

```text
// CPU profiling stubs
```

## Source note 17, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L98)

```text
// GPU profiling stubs
```

## Source note 18, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L102)

```text
// Thread profiling stubs
```

## Source note 19, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L106)

```text
// Fiber profiling stubs
```

## Source note 20, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/dbg.h#L110)

```text
// Counter profiling stubs
```
