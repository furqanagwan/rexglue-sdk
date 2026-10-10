# Launch settings: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/overlay/launch_settings.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/launch_settings.h#L13)

```text
// Host-neutral navigation state. Axes are -1..1, with positive Y pointing up.
```

## Source note 2, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/launch_settings.h#L23)

```text
// Shared ImGui navigation for host menus. Release before disposing the reader.
```

## Source note 3, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/launch_settings.h#L28)

```text
// Self-owned dialog, like ShowMessageBox. Its completion callback runs only
```

## Source note 4, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/launch_settings.h#L29)

```text
// after Play/Exit; destroying it during app shutdown does not launch a title.
```
