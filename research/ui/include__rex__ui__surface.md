# Surface: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/surface.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L20)

```text
// Represents a surface that presenting can be performed to.
```

## Source note 2, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L21)

```text
// Surface methods can be called only from the UI thread.
```

## Source note 3, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L26)

```text
// Within one platform, the more preferable surface types are earlier in
```

## Source note 4, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L27)

```text
// this enumeration, so rex::bit_scan_forward can be used to try creating
```

## Source note 5, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L28)

```text
// surfaces of all types supported by both the graphics provider and the
```

## Source note 6, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L29)

```text
// window.
```

## Source note 7, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L30)

```text
// Android.
```

## Source note 8, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L32)

```text
// GNU/Linux. Wayland first: xcb is only reachable through XWayland there.
```

## Source note 9, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L35)

```text
// Windows.
```

## Source note 10, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L37)

```text
// macOS — CAMetalLayer presented via MoltenVK (VK_EXT_metal_surface).
```

## Source note 11, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L55)

```text
// Returns the up-to-date size (and true), or zeros (and false) if not ready
```

## Source note 12, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L56)

```text
// to open a presentation connection yet. The size preferably should be
```

## Source note 13, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L57)

```text
// exactly the dimensions of the surface in physical pixels of the display
```

## Source note 14, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L58)

```text
// (without stretching performed by the platform's composition), but even if
```

## Source note 15, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L59)

```text
// stretching happens, it is required that surface pixels have 1:1 aspect
```

## Source note 16, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L60)

```text
// ratio relatively to the physical display.
```

## Source note 17, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L62)

```text
// If any dimension is 0 (like, resized completely to zero in one direction,
```

## Source note 18, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L63)

```text
// but not in another), the surface is zero-area - don't try to present to
```

## Source note 19, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L64)

```text
// it.
```

## Source note 20, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L79)

```text
// Returns the up-to-date size in physical pixels (and true), or zeros (and
```

## Source note 21, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/surface.h#L80)

```text
// optionally false) if not ready to open a presentation connection yet.
```
