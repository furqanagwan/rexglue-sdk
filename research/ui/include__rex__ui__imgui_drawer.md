# Imgui drawer: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/imgui_drawer.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L45)

```text
// Per-overlay styling, patched by the consumer in OnConfigureStyle.
```

## Source note 2, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L52)

```text
// Whether Draw would render anything, so a caller that has to marshal to the
```

## Source note 3, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L53)

```text
// UI thread can skip the round trip entirely.
```

## Source note 4, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L56)

```text
// SetPresenter may be called from the destructor.
```

## Source note 5, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L76)

```text
// For now, no need for OnDpiChanged because redrawing is done continuously.
```

## Source note 6, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L103)

```text
// All currently-attached dialogs that get drawn.
```

## Source note 7, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L105)

```text
// Using an index, not an iterator, because after the erasure, the adjustment
```

## Source note 8, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L106)

```text
// must be done for the vector element indices that would be in the iterator
```

## Source note 9, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L107)

```text
// range that would be invalidated.
```

## Source note 10, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L108)

```text
// SIZE_MAX if not currently in the dialog loop.
```

## Source note 11, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L114)

```text
// Resources specific to an immediate drawer - must be destroyed before
```

## Source note 12, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L115)

```text
// detaching the presenter.
```

## Source note 13, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L118)

```text
// If there's an active pointer, the ImGui mouse is controlled by this touch.
```

## Source note 14, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L119)

```text
// If it's TouchEvent::kPointerIDNone, the ImGui mouse is controlled by the
```

## Source note 15, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L120)

```text
// mouse.
```

## Source note 16, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L122)

```text
// Whether after the next frame (since the mouse up event needs to be handled
```

## Source note 17, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L123)

```text
// with the correct mouse position still), the ImGui mouse position should be
```

## Source note 18, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L124)

```text
// reset (for instance, after releasing a touch), so it's not hovering over
```

## Source note 19, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L125)

```text
// anything.
```

## Source note 20, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L131)

```text
// ImGui's IME hook, called from EndFrame with the frame being ended.
```

## Source note 21, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L132)

```text
// ImGuiIO::WantTextInput would be a frame behind.
```

## Source note 22, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_drawer.h#L137)

```text
// Last value handed to the window, so detaching can clear it without a frame.
```
