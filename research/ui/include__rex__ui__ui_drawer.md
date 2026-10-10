# Ui drawer: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/ui_drawer.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_drawer.h#L22)

```text
// No preparation or finishing callbacks because drawers may register or
```

## Source note 2, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_drawer.h#L23)

```text
// unregister each other, so between the loops the list may be different.
```

## Source note 3, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_drawer.h#L25)

```text
// The draw function may register or unregister drawers (and depending on the
```

## Source note 4, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_drawer.h#L26)

```text
// Z order the changes may or may not effect immediately). However, they must
```

## Source note 5, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_drawer.h#L27)

```text
// not perform any lifetime management of the presenter and of its connection
```

## Source note 6, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_drawer.h#L28)

```text
// to the surface. Ideally drawing should not be changing any state at all,
```

## Source note 7, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_drawer.h#L29)

```text
// however, in Dear ImGui, input is handled directly during drawing - any
```

## Source note 8, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_drawer.h#L30)

```text
// quitting or resizing, if done in the UI, must be deferred via something
```

## Source note 9, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_drawer.h#L31)

```text
// like WindowedAppContext::CallInUIThreadDeferred.
```
