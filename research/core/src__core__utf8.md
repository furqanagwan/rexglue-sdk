# Utf8: core source notes

This record preserves technical and API notes moved from `src/core/utf8.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L294)

```text
// not enough room in target for search
```

## Source note 2, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L333)

```text
// not enough room in target for search
```

## Source note 3, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L371)

```text
// not enough room in target for search
```

## Source note 4, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L396)

```text
// not enough room in target for search
```

## Source note 5, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L423)

```text
// not enough room in target for search
```

## Source note 6, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L450)

```text
// not enough room in target for search
```

## Source note 7, line 512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L512)

```text
// Swap all separators to new_sep.
```

## Source note 8, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L525)

```text
// Begins with a separator
```

## Source note 9, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L571)

```text
// skip trailing separators at the end of the path
```

## Source note 10, line 574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L574)

```text
// path is all separators, name is empty
```

## Source note 11, line 580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L580)

```text
// update end so it is before any trailing separators
```

## Source note 12, line 583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L583)

```text
// skip non-separators
```

## Source note 13, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L591)

```text
// if the iterator is on a separator, advance
```

## Source note 14, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L638)

```text
// skip trailing separators at the end of the path
```

## Source note 15, line 646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L646)

```text
// skip non-separators
```

## Source note 16, line 649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L649)

```text
// there are no separators, base path is empty
```

## Source note 17, line 655

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L655)

```text
// Save position of the separator we just found
```

## Source note 18, line 658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L658)

```text
// skip trailing separators at the end of the base path
```

## Source note 19, line 661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L661)

```text
// base path is all separators, base path is empty
```

## Source note 20, line 667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L667)

```text
// If we stopped at a colon (drive letter like "D:"), include the root separator
```

## Source note 21, line 668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L668)

```text
// This ensures "D:\file.txt" returns "D:\" not "D:"
```

## Source note 22, line 689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L689)

```text
// Potential marker for current directory.
```

## Source note 23, line 692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/utf8.cpp#L692)

```text
// Ensure we don't override the device name.
```
