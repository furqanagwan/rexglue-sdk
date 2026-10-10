# D3d12 descriptor heap pool: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L20)

```text
// Submission index is the fence value or a value derived from it (if reclaiming
```

## Source note 2, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L21)

```text
// less often than once per fence value, for instance).
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L35)

```text
// Because all descriptors for a single draw call must be in the same heap,
```

## Source note 4, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L36)

```text
// sometimes all descriptors, rather than only the modified portion of it,
```

## Source note 5, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L37)

```text
// needs to be written.
```

## Source note 6, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L39)

```text
// This may happen if there's not enough free space even for a partial update
```

## Source note 7, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L40)

```text
// in the current heap, or if the heap which contains the unchanged part of
```

## Source note 8, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L41)

```text
// the descriptors is outdated.
```

## Source note 9, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L43)

```text
// If something uses this pool to do partial updates, it must let this
```

## Source note 10, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L44)

```text
// function determine whether a partial update is possible. For this purpose,
```

## Source note 11, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L45)

```text
// this function returns the heap reset index - and it must be called with its
```

## Source note 12, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L46)

```text
// previous return value for the set of descriptors it's updating.
```

## Source note 13, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L48)

```text
// If this function returns a value that is the same as previous_heap_index, a
```

## Source note 14, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L49)

```text
// partial update needs to be done - and space for count_for_partial_update is
```

## Source note 15, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L50)

```text
// allocated.
```

## Source note 16, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L52)

```text
// If it's different, all descriptors must be written again - and space for
```

## Source note 17, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L53)

```text
// count_for_full_update is allocated.
```

## Source note 18, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L55)

```text
// If kHeapIndexInvalid is returned, there was an error.
```

## Source note 19, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L57)

```text
// This MUST be called even if there's nothing to write in a partial update
```

## Source note 20, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L58)

```text
// (with count_for_partial_update being 0), because a full update may still be
```

## Source note 21, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L59)

```text
// required.
```

## Source note 22, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L64)

```text
// The current heap, for binding and actually writing - may be called only
```

## Source note 23, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L65)

```text
// after a successful request because before a request, the heap may not exist
```

## Source note 24, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L66)

```text
// yet.
```

## Source note 25, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L88)

```text
// A list of heap with free space, with the first buffer being the one
```

## Source note 26, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L89)

```text
// currently being filled.
```

## Source note 27, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L92)

```text
// A list of full heaps that can be reclaimed when the GPU doesn't use them
```

## Source note 28, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L93)

```text
// anymore.
```

## Source note 29, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L96)

```text
// Monotonically increased when a new request is going to a different
```

## Source note 30, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L97)

```text
// ID3D12DescriptorHeap than the one that may be bound currently. See Request
```

## Source note 31, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L98)

```text
// for more information.
```

## Source note 32, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_descriptor_heap_pool.h#L103)

```text
// namespace rex::ui::d3d12
```
