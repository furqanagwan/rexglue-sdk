# Xam debug: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xam/xam_debug.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_debug.cpp#L22)

```text
// OutputDebugStringA - ANSI debug string output
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_debug.cpp#L29)

```text
// OutputDebugStringW - Unicode debug string output
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_debug.cpp#L32)

```text
// Convert char16_t to UTF-8 for logging (simple ASCII fallback)
```

## Source note 4, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_debug.cpp#L40)

```text
// Non-ASCII fallback
```

## Source note 5, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_debug.cpp#L47)

```text
// RtlOutputDebugString - Same as OutputDebugStringA
```

## Source note 6, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_debug.cpp#L54)

```text
// RtlDebugTrace - Debug trace output
```

## Source note 7, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_debug.cpp#L65)

```text
// Hook registrations
```
