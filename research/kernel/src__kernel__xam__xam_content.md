# Xam content: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xam/xam_content.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L33)

```text
// Each bit in the mask represents a granted license. Available licenses
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L34)

```text
// seems to vary from game to game, but most appear to use bit 0 to indicate
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L35)

```text
// if the game is purchased or not.
```

## Source note 4, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L51)

```text
// Result of buffer_ptr is sent to RtlInitAnsiString.
```

## Source note 5, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L52)

```text
// buffer_size is usually 260 (max path).
```

## Source note 6, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L53)

```text
// Games expect zero if resolve was successful.
```

## Source note 7, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L59)

```text
// https://github.com/MrColdbird/gameservice/blob/master/ContentManager.cpp
```

## Source note 8, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L60)

```text
// https://github.com/LestaD/SourceEngine2007/blob/master/se2007/engine/xboxsystem.cpp#L499
```

## Source note 9, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L87)

```text
// Enumerate user-specific content
```

## Source note 10, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L95)

```text
// Also enumerate common content (xuid=0)
```

## Source note 11, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L149)

```text
// Fail if exists.
```

## Source note 12, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L157)

```text
// Overwrite existing, if any.
```

## Source note 13, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L158)

```text
// Close any existing mount under this root name first.
```

## Source note 14, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L159)

```text
// Games may reuse the same root without explicitly closing.
```

## Source note 15, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L169)

```text
// Open only if exists.
```

## Source note 16, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L177)

```text
// Create if needed.
```

## Source note 17, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L185)

```text
// Fail if doesn't exist, if does exist delete and recreate.
```

## Source note 18, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L264)

```text
// Success means the root's written files are durable on the host and its
```

## Source note 19, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L265)

```text
// header exists (adapted from xenia-canary #1216, which rewrites its header
```

## Source note 20, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L266)

```text
// file). Failures are reported through the overlapped too, so a title
```

## Source note 21, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L267)

```text
// waiting on it is released.
```

## Source note 22, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L278)

```text
// Closes a previously opened root from XamContentCreate*.
```

## Source note 23, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L301)

```text
// User always creates saves.
```

## Source note 24, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L332)

```text
// Get thumbnail (if it exists).
```

## Source note 25, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L340)

```text
// Write data, if we were given a pointer.
```

## Source note 26, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L341)

```text
// This may have just been a size query.
```

## Source note 27, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L344)

```text
// Dest buffer too small.
```

## Source note 28, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L347)

```text
// Copy data.
```

## Source note 29, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L367)

```text
// Buffer is PNG data.
```

## Source note 30, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L396)

```text
// INFO: Analysis of xam.xex shows that "internal" functions are wrappers with
```

## Source note 31, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_content.cpp#L397)

```text
// 0xFE as user_index
```
