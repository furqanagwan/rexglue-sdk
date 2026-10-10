# Settings overlay: ui source notes

This record preserves technical and API notes moved from `src/ui/overlay/settings_overlay.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L159)

```text
/*io*/
```

## Source note 2, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L162)

```text
// Collect sorted unique category paths.
```

## Source note 3, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L168)

```text
// Build tree: for each category path like "Input/Keybinds/Controller",
```

## Source note 4, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L169)

```text
// also register the parent paths "Input" and "Input/Keybinds" as nodes.
```

## Source note 5, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L172)

```text
// leaf segment (e.g. "Controller")
```

## Source note 6, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L209)

```text
// Search bar at the top (full width).
```

## Source note 7, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L220)

```text
// Recursive lambda to draw the category tree.
```

## Source note 8, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L225)

```text
// Leaf node - selectable
```

## Source note 9, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L235)

```text
// Parent node with children - use tree node
```

## Source note 10, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L238)

```text
// Can be selected as well as expanded
```

## Source note 11, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L253)

```text
// Root node named after the config file
```

## Source note 12, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L271)

```text
// Helper: check if a CVAR's category matches the selected category.
```

## Source note 13, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L272)

```text
// Exact match or prefix match (e.g. selecting "Input" shows all "Input/*").
```

## Source note 14, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L275)

```text
// Root selected - show all
```

## Source note 15, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L286)

```text
// Helper: check if a category is a keybind category.
```

## Source note 16, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L294)

```text
// Filter by category (unless searching).
```

## Source note 17, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L300)

```text
// Search matches name or description (case-insensitive substring).
```

## Source note 18, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L324)

```text
// Use description as display label if available, otherwise CVAR name
```

## Source note 19, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L329)

```text
// Grey out controller keybinds when MnK mode is disabled
```

## Source note 20, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L335)

```text
// Show description as label (e.g. "A button"), not the raw CVAR name
```

## Source note 21, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L383)

```text
// Conflict detection
```

## Source note 22, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L402)

```text
// Skip the generic name + lifecycle badge rendering for keybinds
```

## Source note 23, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L410)

```text
// Non-keybind CVARs: colored label on left, value widget on right
```

## Source note 24, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/settings_overlay.cpp#L503)

```text
// Bottom bar: Save button.
```
