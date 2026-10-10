# Achievements overlay: ui source notes

This record preserves technical and API notes moved from `src/ui/overlay/achievements_overlay.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/achievements_overlay.cpp#L61)

```text
// ---- Header: summary line + progress bar -------------------------------
```

## Source note 2, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/achievements_overlay.cpp#L77)

```text
// ---- List --------------------------------------------------------------
```

## Source note 3, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/achievements_overlay.cpp#L87)

```text
// Split the draw list so the row band (channel 0) renders behind the
```

## Source note 4, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/achievements_overlay.cpp#L88)

```text
// text (channel 1); we paint the rect after measuring, then merge.
```

## Source note 5, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/achievements_overlay.cpp#L96)

```text
// Icon on the left. Locked icons are dimmed so the state reads clearly.
```

## Source note 6, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/achievements_overlay.cpp#L108)

```text
// Text block to the right of the icon.
```

## Source note 7, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/achievements_overlay.cpp#L126)

```text
// Paint the band behind unlocked rows on the lower channel.
```
