# Sink: core source notes

This record preserves technical and API notes moved from `include/rex/logging/sink.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L27)

```text
// e.g. "core", "gpu"
```

## Source note 2, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L28)

```text
// formatted message only (no timestamp/level prefix)
```

## Source note 3, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L31)

```text
// Thread-safe ring-buffer spdlog sink.
```

## Source note 4, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L32)

```text
// Capacity is fixed at 2048 entries; oldest entries are overwritten.
```

## Source note 5, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L37)

```text
// Copy all current entries in chronological order into `out`.
```

## Source note 6, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L38)

```text
// Safe to call from any thread (e.g. the UI/render thread).
```

## Source note 7, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L44)

```text
// Buffer not yet full - entries start at index 0.
```

## Source note 8, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L49)

```text
// Full - oldest entry is at write_pos_ (wraps around).
```

## Source note 9, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L56)

```text
// Returns true if new entries have been added since the last call
```

## Source note 10, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L57)

```text
// to CopyEntries (checked by comparing generation counter).
```

## Source note 11, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L67)

```text
// Format just the payload (no timestamp, level, or logger name).
```

## Source note 12, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L70)

```text
// Strip trailing newline spdlog adds.
```

## Source note 13, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L76)

```text
// Lock mutable_mutex_ so writes to buf_ are synchronized with
```

## Source note 14, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L77)

```text
// CopyEntries() and generation() which also lock this mutex.
```

## Source note 15, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/sink.h#L78)

```text
// (base_sink::mutex_ alone is insufficient -- CopyEntries doesn't hold it.)
```
