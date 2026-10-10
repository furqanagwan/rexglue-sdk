# Display mode: ui source notes

This record preserves technical and API notes moved from `src/ui/display_mode.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/display_mode.h#L25)

```text
// The mode to switch to for a requested size, following SDL's
```

## Source note 2, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/display_mode.h#L26)

```text
// SDL_GetClosestFullscreenDisplayMode so both windows agree: the exact size
```

## Source note 3, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/display_mode.h#L27)

```text
// if the display has it, otherwise the smallest mode covering it, otherwise
```

## Source note 4, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/display_mode.h#L28)

```text
// the largest mode. Among modes of that size, the preferred refresh rate (the
```

## Source note 5, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/display_mode.h#L29)

```text
// desktop's), or the highest one. Only the deepest colour modes are
```

## Source note 6, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/display_mode.h#L30)

```text
// considered. Empty when there are no modes.
```
