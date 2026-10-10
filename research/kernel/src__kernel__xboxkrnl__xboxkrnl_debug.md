# Xboxkrnl debug: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_debug.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L32)

```text
// https://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx
```

## Source note 3, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L42)

```text
// SetThreadName. FFS.
```

## Source note 4, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L43)

```text
// https://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx
```

## Source note 5, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L54)

```text
// 4D5307D6 (and its demo) has a bug where it ends up passing freed memory for
```

## Source note 6, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L55)

```text
// the name, so at the point of SetThreadName it's filled with junk.
```

## Source note 7, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L63)

```text
// Current thread.
```

## Source note 8, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L66)

```text
// Lookup thread by ID.
```

## Source note 9, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L103)

```text
// C++ exception.
```

## Source note 10, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L104)

```text
// https://blogs.msdn.com/b/oldnewthing/archive/2010/07/30/10044061.aspx
```

## Source note 11, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L105)

```text
// http://www.drdobbs.com/visual-c-exception-handling-instrumentat/184416600
```

## Source note 12, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L106)

```text
// http://www.openrce.org/articles/full_view/21
```
