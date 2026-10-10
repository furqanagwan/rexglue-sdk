# Immediate drawer: ui source notes

This record preserves technical and API notes moved from `src/ui/immediate_drawer.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/immediate_drawer.cpp#L27)

```text
// Changing the presenter while drawing would make the state inconsistent.
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/immediate_drawer.cpp#L40)

```text
// App-driven contexts carry no presenter; presenter-driven backend contexts
```

## Source note 3, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/immediate_drawer.cpp#L41)

```text
// must match the drawer's presenter. presenter_or_null() is safe for both.
```

## Source note 4, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/immediate_drawer.cpp#L44)

```text
// In case of non-positive values (or NaNs) - use render target coordinates
```

## Source note 5, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/immediate_drawer.cpp#L45)

```text
// according to the contract of the function, and also for safety because
```

## Source note 6, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/immediate_drawer.cpp#L46)

```text
// there will be division by the coordinate space size in several places.
```

## Source note 7, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/immediate_drawer.cpp#L73)

```text
// Scale to render target coordinates, drop NaNs, and clamp to the render
```

## Source note 8, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/immediate_drawer.cpp#L74)

```text
// target size, below which the values are representable as 16p8 fixed-point.
```

## Source note 9, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/immediate_drawer.cpp#L81)

```text
// Also make sure the size is non-negative.
```

## Source note 10, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/immediate_drawer.cpp#L86)

```text
// Top-left - include .5 (0.128 treated as 0 covered, 0.129 as 0 not covered).
```

## Source note 11, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/immediate_drawer.cpp#L89)

```text
// Bottom-right - exclude .5.
```
