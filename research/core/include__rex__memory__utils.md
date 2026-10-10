# Utils: core source notes

This record preserves technical and API notes moved from `include/rex/memory/utils.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L29)

```text
// For variable declarations (not return values or `this` pointer).
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L30)

```text
// Not propagated.
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L33)

```text
// Aliasing-safe bit reinterpretation.
```

## Source note 4, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L34)

```text
// For more complex cases such as non-trivially-copyable types, write copying
```

## Source note 5, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L35)

```text
// code respecting the requirements for them externally instead of using these
```

## Source note 6, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L36)

```text
// functions.
```

## Source note 7, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L53)

```text
// Returns the native page size of the system, in bytes.
```

## Source note 8, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L54)

```text
// This should be ~4KiB.
```

## Source note 9, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L57)

```text
// Returns the allocation granularity of the system, in bytes.
```

## Source note 10, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L58)

```text
// This is likely 64KiB.
```

## Source note 11, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L80)

```text
// Whether the host allows the pages to be allocated or mapped with
```

## Source note 12, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L81)

```text
// PageAccess::kExecuteReadWrite - if not, separate mappings backed by the same
```

## Source note 13, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L82)

```text
// memory-mapped file must be used to write to executable pages.
```

## Source note 14, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L85)

```text
// Whether PageAccess::kExecuteReadWrite is a supported and preferred way of
```

## Source note 15, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L86)

```text
// writing executable memory, useful for simulating how Xenia would work without
```

## Source note 16, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L87)

```text
// writable executable memory on a system with it.
```

## Source note 17, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L90)

```text
// Allocates a block of memory at the given page-aligned base address.
```

## Source note 18, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L91)

```text
// Fails if the memory is not available.
```

## Source note 19, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L92)

```text
// Specify nullptr for base_address to leave it up to the system.
```

## Source note 20, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L96)

```text
// Deallocates and/or releases the given block of memory.
```

## Source note 21, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L97)

```text
// When releasing memory length must be zero, as all pages in the region are
```

## Source note 22, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L98)

```text
// released.
```

## Source note 23, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L101)

```text
// Sets the access rights for the given block of memory and returns the previous
```

## Source note 24, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L102)

```text
// access rights. Both base_address and length will be adjusted to page_size().
```

## Source note 25, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L106)

```text
// Queries a region of pages to get the access rights. This will modify the
```

## Source note 26, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L107)

```text
// length parameter to the length of pages with the same consecutive access
```

## Source note 27, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L108)

```text
// rights. The length will start from the first byte of the first page of
```

## Source note 28, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L109)

```text
// the region.
```

## Source note 29, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L112)

```text
// Allocates a block of memory for a type with the given alignment.
```

## Source note 30, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L113)

```text
// The memory must be freed with AlignedFree.
```

## Source note 31, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L119)

```text
// Frees memory previously allocated with AlignedAlloc.
```

## Source note 32, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L125)

```text
// Opaque file mapping handle.
```

## Source note 33, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L126)

```text
// On Windows this holds a HANDLE (void*), on POSIX a file descriptor (int).
```

## Source note 34, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L127)

```text
// We use intptr_t to hold either without platform guards.
```

## Source note 35, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L199)

```text
/// Load a value of type T from arbitrary memory (handles unaligned access).
```

## Source note 36, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L208)

```text
/// Load a value of type T from memory and byte-swap it.
```

## Source note 37, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L214)

```text
// String specializations need custom logic
```

## Source note 38, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L240)

```text
/// Store a value of type T to arbitrary memory (handles unaligned access).
```

## Source note 39, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L247)

```text
/// Store a byte-swapped value of type T to memory.
```

## Source note 40, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L253)

```text
// String specializations need custom logic
```

## Source note 41, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L277)

```text
// Get FourCC in host byte order
```

## Source note 42, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L278)

```text
// make_fourcc('a', 'b', 'c', 'd') == 0x61626364
```

## Source note 43, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L284)

```text
// Get FourCC in host byte order
```

## Source note 44, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L285)

```text
// This overload requires fourcc.length() == 4
```

## Source note 45, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/memory/utils.h#L286)

```text
// make_fourcc("abcd") == 'abcd' == 0x61626364 for most compilers
```
