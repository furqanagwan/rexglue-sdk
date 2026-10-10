# Menu item: ui source notes

This record preserves technical and API notes moved from `src/ui/menu_item.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/menu_item.cpp#L33)

```text
// No native menu backend with SDL windowing; the plain item still carries
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/menu_item.cpp#L34)

```text
// text/hotkey/callback state for callers that walk the tree themselves.
```

## Source note 3, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/menu_item.cpp#L79)

```text
// Note that this MenuItem might have been destroyed by the callback.
```

## Source note 4, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/menu_item.cpp#L80)

```text
// Must not do anything with *this in this function from now on.
```
