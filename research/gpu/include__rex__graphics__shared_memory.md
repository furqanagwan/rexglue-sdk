# Shared memory: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/shared_memory.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L23)

```text
// Manages memory for unconverted textures, resolve targets, vertex and index
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L24)

```text
// buffers that can be accessed from shaders with Xenon physical addresses, with
```

## Source note 3, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L25)

```text
// system page size granularity.
```

## Source note 4, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L32)

```text
// Call in the implementation-specific ClearCache.
```

## Source note 5, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L41)

```text
// Registers a callback invoked when something is invalidated in the GPU
```

## Source note 6, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L42)

```text
// memory copy by the CPU or (if triggered explicitly - such as by a resolve)
```

## Source note 7, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L43)

```text
// by the GPU. It will be fired for writes to pages previously requested, but
```

## Source note 8, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L44)

```text
// may also be fired regardless of whether it was used by GPU emulation - for
```

## Source note 9, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L45)

```text
// example, if the game changes protection level of a memory range containing
```

## Source note 10, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L46)

```text
// the watched range.
```

## Source note 11, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L48)

```text
// The callback is called within the global critical region.
```

## Source note 12, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L55)

```text
// Registers a callback invoked when the specified memory range is invalidated
```

## Source note 13, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L56)

```text
// in the GPU memory copy by the CPU or (if triggered explicitly - such as by
```

## Source note 14, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L57)

```text
// a resolve) by the GPU. It will be fired for writes to pages previously
```

## Source note 15, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L58)

```text
// requested, but may also be fired regardless of whether it was used by GPU
```

## Source note 16, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L59)

```text
// emulation - for example, if the game changes protection level of a memory
```

## Source note 17, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L60)

```text
// range containing the watched range.
```

## Source note 18, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L62)

```text
// Generally the context is the subsystem pointer (for example, the texture
```

## Source note 19, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L63)

```text
// cache), the data is the object (such as a texture), and the argument is
```

## Source note 20, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L64)

```text
// additional subsystem/object-specific data (such as whether the range
```

## Source note 21, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L65)

```text
// belongs to the base mip level or to the rest of the mips).
```

## Source note 22, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L67)

```text
// Called with the global critical region locked. Do NOT watch or unwatch
```

## Source note 23, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L68)

```text
// ranges from within it! The watch for the callback is cancelled after the
```

## Source note 24, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L69)

```text
// callback - the handle becomes invalid.
```

## Source note 25, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L73)

```text
// Unregisters previously registered watched memory range.
```

## Source note 26, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L76)

```text
// Checks if the range has been updated, uploads new data if needed and
```

## Source note 27, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L77)

```text
// ensures the host GPU memory backing the range are resident. Returns true if
```

## Source note 28, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L78)

```text
// the range has been fully updated and is usable.
```

## Source note 29, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L82)

```text
// Marks the range and, if not exact_range, potentially its surroundings
```

## Source note 30, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L83)

```text
// (to up to the first GPU-written page, as an access violation exception
```

## Source note 31, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L84)

```text
// count optimization) as modified by the CPU, also invalidating GPU-written
```

## Source note 32, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L85)

```text
// pages directly in the range.
```

## Source note 33, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L89)

```text
// Marks the range as containing GPU-generated data (such as resolves),
```

## Source note 34, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L90)

```text
// triggering modification callbacks, making it valid (so pages are not
```

## Source note 35, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L91)

```text
// copied from the main memory until they're modified by the CPU) and
```

## Source note 36, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L92)

```text
// protecting it. Before writing anything from the GPU side, RequestRange must
```

## Source note 37, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L93)

```text
// be called, to make sure, if the GPU writes don't overwrite *everything* in
```

## Source note 38, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L94)

```text
// the pages they touch, the CPU data is properly loaded to the unmodified
```

## Source note 39, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L95)

```text
// regions in those pages.
```

## Source note 40, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L100)

```text
// Call in implementation-specific initialization.
```

## Source note 41, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L103)

```text
// Call last in implementation-specific shutdown, also callable from the
```

## Source note 42, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L104)

```text
// destructor.
```

## Source note 43, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L107)

```text
// Sparse allocations are 4 MB, so not too many of them are allocated, but
```

## Source note 44, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L108)

```text
// also not to waste too much memory for padding (with 16 MB there's too
```

## Source note 45, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L109)

```text
// much).
```

## Source note 46, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L121)

```text
// Allocations in the host buffer are aligned the same way as in the guest
```

## Source note 47, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L122)

```text
// physical memory (for instance, if an allocation is 64 KB, it can represent
```

## Source note 48, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L123)

```text
// 0-64 KB, 64-128 KB, 128-192 KB in the guest memory, and so on, but not
```

## Source note 49, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L124)

```text
// something like 16-80 KB. This is assumed by the rules for texture data
```

## Source note 50, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L125)

```text
// access in the texture cache.
```

## Source note 51, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L129)

```text
// Mark the memory range as updated and protect it.
```

## Source note 52, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L132)

```text
// Uploads a range of host pages - only called if host GPU sparse memory
```

## Source note 53, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L133)

```text
// allocation succeeded if needed. While uploading, MakeRangeValid must be
```

## Source note 54, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L134)

```text
// called for each successfully uploaded range as early as possible, before
```

## Source note 55, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L135)

```text
// the memcpy, to make sure invalidation that happened during the CPU -> GPU
```

## Source note 56, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L136)

```text
// memcpy isn't missed (upload_page_ranges is in pages because of this -
```

## Source note 57, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L137)

```text
// MakeRangeValid has page granularity). upload_page_ranges are sorted in
```

## Source note 58, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L138)

```text
// ascending address order, so front and back can be used to determine the
```

## Source note 59, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L139)

```text
// overall bounds of pages to be uploaded.
```

## Source note 60, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L146)

```text
// Log2 of invalidation granularity (the system page size, but the dependency
```

## Source note 61, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L147)

```text
// on it is not hard - the access callback takes a range as an argument, and
```

## Source note 62, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L148)

```text
// touched pages of the buffer of this size will be invalidated).
```

## Source note 63, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L160)

```text
// Ranges that need to be uploaded, generated by GetRangesToUpload (a
```

## Source note 64, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L161)

```text
// persistently allocated vector).
```

## Source note 65, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L164)

```text
// Mutex between the guest memory subsystem and the command processor, to be
```

## Source note 66, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L165)

```text
// locked when checking or updating validity of pages/ranges and when firing
```

## Source note 67, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L166)

```text
// watches.
```

## Source note 68, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L170)

```text
// Things below should be fully protected by global_critical_region.
```

## Source note 69, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L173)

```text
// Pages whose contents in the buffer are in sync with guest memory.
```

## Source note 70, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L175)

```text
// Subset of valid pages containing data written by the GPU.
```

## Source note 71, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L188)

```text
// Watched range placed by other GPU subsystems.
```

## Source note 72, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L203)

```text
// Node for faster checking of watches when pages have been written to - all
```

## Source note 73, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L204)

```text
// 512 MB are split into smaller equally sized buckets, and then ranges are
```

## Source note 74, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L205)

```text
// linearly checked.
```

## Source note 75, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L210)

```text
// Link to another node of this watched range in the next bucket.
```

## Source note 76, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L212)

```text
// Links to nodes belonging to other watched ranges in the bucket.
```

## Source note 77, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L222)

```text
// Allocation from pools - taking new WatchRanges and WatchNodes from the free
```

## Source note 78, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L223)

```text
// list, and if there are none, creating a pool if the current one is fully
```

## Source note 79, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L224)

```text
// used, and linearly allocating from the current pool.
```

## Source note 80, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L233)

```text
// Triggers the watches (global and per-range), removing triggered range
```

## Source note 81, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L234)

```text
// watches.
```

## Source note 82, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L236)

```text
// Unlinks and frees the range and its nodes. Call this in the global critical
```

## Source note 83, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/shared_memory.h#L237)

```text
// region.
```
