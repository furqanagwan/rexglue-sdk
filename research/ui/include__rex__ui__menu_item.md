# Menu item: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/menu_item.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/menu_item.h#L30)

```text
// Popup menu (submenu)
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/menu_item.h#L32)

```text
// Root menu
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/menu_item.h#L33)

```text
// Menu is just a string
```

## Source note 4, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/menu_item.h#L51)

```text
// If the menu is currently attached to a Window, changes to it (such as the
```

## Source note 5, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/menu_item.h#L52)

```text
// elements and the enabled / disabled state) may be not reflected
```

## Source note 6, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/menu_item.h#L53)

```text
// immediately - call Window::CompleteMainMenuItemsUpdate when the
```

## Source note 7, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/menu_item.h#L54)

```text
// modifications are done.
```

## Source note 8, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/menu_item.h#L71)

```text
// This MenuItem may be destroyed as a result of the callback, don't do
```

## Source note 9, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/menu_item.h#L72)

```text
// anything with it after the call.
```
