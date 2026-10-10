# Runtime: system source notes

This record preserves technical and API notes moved from `src/system/runtime.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L23)

```text
// SEH exception support
```

## Source note 2, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L45)

```text
// As Xenia Canary does (mount_cache, on since 2024-08-31): EA's titles copy
```

## Source note 3, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L46)

```text
// their streaming archives to the utility partition and read them from there;
```

## Source note 4, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L47)

```text
// without it NHL Legacy Edition read D:\(null)\cacherender.big and drew its
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L48)

```text
// matches black (RG-GDK-069).
```

## Source note 6, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L57)

```text
// Names the recompiled guest function a fatal guest access violation came
```

## Source note 7, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L58)

```text
// from, with the faulting thread's guest LR and stack pointer. The host
```

## Source note 8, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L59)

```text
// module and offset let the PC be symbolized later.
```

## Source note 9, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L89)

```text
// Static instance for global access
```

## Source note 10, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L154)

```text
// Initialize SEH exception support for hardware exception handling
```

## Source note 11, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L157)

```text
// Initialize clock
```

## Source note 12, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L162)

```text
// Enable threading affinity configuration
```

## Source note 13, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L167)

```text
// Create memory system first
```

## Source note 14, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L181)

```text
// Create virtual file system
```

## Source note 15, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L184)

```text
// Create kernel state - this sets the global singleton
```

## Source note 16, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L187)

```text
// Initialize input from injected config
```

## Source note 17, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L202)

```text
// HLE kernel modules and apps.
```

## Source note 18, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L207)

```text
// Initialize the APU (Audio Processing Unit) from injected config
```

## Source note 19, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L222)

```text
// Set up VFS: game_data_root as game:/d:, update_data_root as update:
```

## Source note 20, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L227)

```text
// Skip GPU initialization in tool mode (for analysis tools like codegen)
```

## Source note 21, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L234)

```text
// Initialize GPU from injected config
```

## Source note 22, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L263)

```text
/*is_entrypoint=*/
```

## Source note 23, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L360)

```text
// Mount game_data_root as \Device\Harddisk0\Partition1
```

## Source note 24, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L380)

```text
// Register symbolic links for game: and D:
```

## Source note 25, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L385)

```text
// Mount update_data_root as update:\ if provided: a folder of the title
```

## Source note 26, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L386)

```text
// update's files, or its LIVE/CON package as it was downloaded.
```

## Source note 27, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L410)

```text
// Setup NullDevice for raw HDD partition accesses
```

## Source note 28, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L411)

```text
// Cache/STFC code baked into games tries reading/writing to these
```

## Source note 29, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L412)

```text
// Using a NullDevice returns success to all IO requests, allowing games
```

## Source note 30, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L413)

```text
// to believe cache/raw disk was accessed successfully.
```

## Source note 31, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L414)

```text
// NOTE: Must be registered AFTER Partition1 so Partition1 requests don't
```

## Source note 32, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L415)

```text
// go to NullDevice (VFS resolves devices in registration order)
```

## Source note 33, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L424)

```text
// The utility partitions as host folders under the cache root (Canary's
```

## Source note 34, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/runtime.cpp#L425)

```text
// mount_cache): cache0: and cache1: first, since cache: is their prefix.
```
