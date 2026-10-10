# Library art: tools source notes

This record preserves technical and API notes moved from `src/rexglue/commands/library_art.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L19)

```text
/// An image in premultiplied BGRA, 8 bits a channel, rows top down.
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L29)

```text
/// Decodes a PNG, JPEG or any format Windows Imaging Component reads.
```

## Source note 3, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L31)

```text
/// Encodes `image` as a PNG (straight alpha, as PNG stores it).
```

## Source note 4, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L33)

```text
/// A Windows ICO at 16, 24, 32, 48, 64, 128 and 256 pixels (PNG at 256,
```

## Source note 5, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L34)

```text
/// bitmap frames below 256 for native Shell extraction).
```

## Source note 6, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L35)

```text
/// Uses title art directly, preserving alpha, independently of library tiles.
```

## Source note 7, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L37)

```text
/// `image` scaled to `width` x `height` with high-quality cubic filtering.
```

## Source note 8, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L40)

```text
/// The orb and XBOX 360 wordmark the tile's strip shows, shaped from the
```

## Source note 9, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L41)

```text
/// system update's `splash_360.png` (xam shared resources) without its trade
```

## Source note 10, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L42)

```text
/// mark signs, and coloured as the Store's tiles colour them: the white orb
```

## Source note 11, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L43)

```text
/// with a green X, XBOX dark green, 360 grey.
```

## Source note 12, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L45)

```text
// turned a quarter left as the strip shows it; transparent outside the disc
```

## Source note 13, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L46)

```text
// left to right
```

## Source note 14, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L50)

```text
/// The square tile the Xbox PC app shows for an Xbox 360 backward-compatible
```

## Source note 15, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L51)

```text
/// game, `size` pixels across (laid out from the Store's 1080 x 1080 tiles):
```

## Source note 16, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L52)

```text
/// a white strip down the left 17.5% with the green swooshes at its top, the
```

## Source note 17, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L53)

```text
/// wordmark reading upwards and the orb at its foot, and `cover` filling the
```

## Source note 18, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L54)

```text
/// rest, scaled to cover it and centred. `crop_top` (0 to 1) is cut from the
```

## Source note 19, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L55)

```text
/// top of `cover` first: the 360 marketplace's box art carries the console's
```

## Source note 20, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L56)

```text
/// banner there. Without `strip_art` the strip has the swooshes only.
```

## Source note 21, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/library_art.h#L59)

```text
/// `image` scaled to cover `width` x `height` and centred, for the splash.
```
