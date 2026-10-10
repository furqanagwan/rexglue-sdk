# Mapped memory win: core source notes

This record preserves technical and API notes moved from `src/core/mapped_memory_win.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/mapped_memory_win.cpp#L34)

```text
// CreateFile returns INVALID_HANDLE_VALUE in case of failure.
```

## Source note 2, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/mapped_memory_win.cpp#L36)

```text
// CreateFileMapping returns nullptr in case of failure.
```

## Source note 3, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/mapped_memory_win.cpp#L272)

```text
// If specified, ensure the allocation occurs in the lower 32-bit address
```

## Source note 4, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/mapped_memory_win.cpp#L273)

```text
// space.
```

## Source note 5, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/mapped_memory_win.cpp#L286)

```text
// VirtualAlloc2FromApp and MapViewOfFile3FromApp were added in
```

## Source note 6, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/mapped_memory_win.cpp#L287)

```text
// 10.0.17134.0.
```

## Source note 7, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/mapped_memory_win.cpp#L288)

```text
// https://docs.microsoft.com/en-us/uwp/win32-and-com/win32-apis
```
