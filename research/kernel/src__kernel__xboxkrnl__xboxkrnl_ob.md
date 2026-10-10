# Xboxkrnl ob: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_ob.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L33)

```text
// r3 = ptr to info?
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L34)

```text
//   +0 = -4
```

## Source note 4, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L35)

```text
//   +4 = name ptr
```

## Source note 5, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L36)

```text
//   +8 = 0
```

## Source note 6, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L37)

```text
// r4 = ExEventObjectType | ExSemaphoreObjectType | ExTimerObjectType
```

## Source note 7, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L38)

```text
// r5 = 0
```

## Source note 8, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L39)

```text
// r6 = out_ptr (handle?)
```

## Source note 9, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L65)

```text
// Retain the handle. Will be released in NtClose.
```

## Source note 10, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L77)

```text
// Retain the object. Will be released in ObDereferenceObject.
```

## Source note 11, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L89)

```text
// Handle pseudo-handles.
```

## Source note 12, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L92)

```text
// CurrentThread pseudo-handle.
```

## Source note 13, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L108)

```text
// Type check using real KernelGuestGlobals addresses.
```

## Source note 14, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L136)

```text
// Caller takes the reference.
```

## Source note 15, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L137)

```text
// It's released in ObDereferenceObject.
```

## Source note 16, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L159)

```text
// Check if a dummy value from ObReferenceObjectByHandle.
```

## Source note 17, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L181)

```text
// Strip the full qualifier
```

## Source note 18, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L201)

```text
// NOTE: new_handle_ptr can be zero to just close a handle.
```

## Source note 19, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L202)

```text
// NOTE: this function seems to be used to get the current thread handle
```

## Source note 20, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L203)

```text
//       (passed handle=-2).
```

## Source note 21, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L204)

```text
// This function actually just creates a new handle to the same object.
```

## Source note 22, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L205)

```text
// Most games use it to get real handles to the current thread or whatever.
```

## Source note 23, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L214)

```text
/* DUPLICATE_CLOSE_SOURCE */
```

## Source note 24, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_ob.cpp#L215)

```text
// Always close the source object.
```
