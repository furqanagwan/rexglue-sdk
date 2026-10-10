# Debug markers: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/debug_markers.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L20)

```text
// PIX event blobs for ID3D12GraphicsCommandList and ID3D12CommandQueue
```

## Source note 2, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L21)

```text
// BeginEvent/SetMarker, encoded as WinPixEventRuntime's pix3.h does for GPU
```

## Source note 3, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L22)

```text
// markers (PIX_USE_GPU_MARKERS_V2, microsoft/PixEvents b0caa73, MIT:
```

## Source note 4, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L23)

```text
// PIXEventsCommon.h, PIXEvents.h, pix3_win.h). The GPU blob is written by the
```

## Source note 5, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L24)

```text
// header alone, so it needs neither pix3.h nor WinPixEventRuntime.dll. EndEvent
```

## Source note 6, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L25)

```text
// takes no blob.
```

## Source note 7, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L27)

```text
// Layout, in 64-bit words: the event info, the color, the context (the
```

## Source note 8, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L28)

```text
// command list or queue) and the label, eight ANSI characters per word, low
```

## Source note 9, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L29)

```text
// byte first, zero-terminated.
```

## Source note 10, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L32)

```text
// WINPIX_EVENT_PIX3BLOB_V2: the metadata argument of BeginEvent/SetMarker.
```

## Source note 11, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L40)

```text
// Event info word fields.
```

## Source note 12, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L41)

```text
// Bits 0-6, event size in words.
```

## Source note 13, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L42)

```text
// Bits 7-11.
```

## Source note 14, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L43)

```text
// Bits 12-19.
```

## Source note 15, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L44)

```text
// Metadata bits.
```

## Source note 16, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L49)

```text
// An opaque 0xAARRGGBB color, as PIX_COLOR makes it.
```

## Source note 17, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L54)

```text
// Words for a label of at most kMaxLabelLength characters.
```

## Source note 18, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L58)

```text
// Writes the blob of a begin event or a marker to `words`; returns its size
```

## Source note 19, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L59)

```text
// in bytes. A longer label is cut to kMaxLabelLength characters.
```

## Source note 20, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L63)

```text
// With the terminator.
```

## Source note 21, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L70)

```text
// Little-endian words: characters in order, low byte first.
```

## Source note 22, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L77)

```text
// Tracks the open debug marker regions of the command list being recorded.
```

## Source note 23, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L79)

```text
// PIX and the D3D12 debug layer expect every BeginEvent in a command list to
```

## Source note 24, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L80)

```text
// be ended in the same command list, but a region opened for a draw or a swap
```

## Source note 25, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L81)

```text
// can outlive the submission: the command processor may end the submission in
```

## Source note 26, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L82)

```text
// the middle of the region (the swap submits before presenting, and a fence
```

## Source note 27, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L83)

```text
// wait can submit early). CloseAll ends the open regions with the command
```

## Source note 28, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L84)

```text
// list, and End then ignores regions whose command list is already closed, so
```

## Source note 29, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L85)

```text
// they are never ended twice or in the wrong command list.
```

## Source note 30, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L88)

```text
// Opens a region; pass the returned token to End.
```

## Source note 31, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L94)

```text
// Returns whether the region's EndEvent has to be recorded: false if the
```

## Source note 32, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L95)

```text
// command list it was opened in has been closed by CloseAll.
```

## Source note 33, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L104)

```text
// Closes the command list: returns how many EndEvents to record for regions
```

## Source note 34, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/debug_markers.h#L105)

```text
// still open, and detaches those regions from their End calls.
```
