# Xfile: system source notes

This record preserves technical and API notes moved from `src/system/xfile.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L61)

```text
// Only queries in the current directory are supported for now.
```

## Source note 2, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L66)

```text
// Always restart the search?
```

## Source note 3, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L109)

```text
// A new request clears the file's event (NT notification event).
```

## Source note 4, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L121)

```text
// Read from current position.
```

## Source note 5, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L127)

```text
// Zero length means success for a valid file object according to Windows
```

## Source note 6, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L128)

```text
// tests.
```

## Source note 7, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L133)

```text
// Games often read directly to texture/vertex buffer memory - in this
```

## Source note 8, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L134)

```text
// case, invalidation notifications must be sent. However, having any
```

## Source note 9, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L135)

```text
// memory callbacks in the range will result in STATUS_ACCESS_VIOLATION at
```

## Source note 10, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L136)

```text
// least on Windows, without anything being read or any callbacks being
```

## Source note 11, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L137)

```text
// triggered. So for physical memory, host protection must be bypassed,
```

## Source note 12, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L138)

```text
// and invalidation callbacks must be triggered manually (it's also wrong
```

## Source note 13, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L139)

```text
// to trigger invalidation callbacks before reading in this case, because
```

## Source note 14, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L140)

```text
// during the read, the guest may still access the data around the buffer
```

## Source note 15, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L141)

```text
// that is located in the same host pages as the buffer's start and end,
```

## Source note 16, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L142)

```text
// on the GPU - and that must not trigger a race condition).
```

## Source note 17, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L213)

```text
// segments points to an array of buffer pointers of type
```

## Source note 18, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L214)

```text
// "FILE_SEGMENT_ELEMENT", but they can just be treated as normal pointers
```

## Source note 19, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xfile.cpp#L267)

```text
// Write from current position.
```
