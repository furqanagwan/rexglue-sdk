# Achievement manager: system source notes

This record preserves technical and API notes moved from `include/rex/system/achievement_manager.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievement_manager.h#L47)

```text
// Adds a new achievement or overrides an existing achievement with the same
```

## Source note 2, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievement_manager.h#L48)

```text
// ID. Intended for startup hooks so recomp-specific metadata can layer over
```

## Source note 3, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievement_manager.h#L49)

```text
// extracted title metadata.
```

## Source note 4, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievement_manager.h#L54)

```text
// Loads and merges [[achievements]] entries from an editable TOML file.
```

## Source note 5, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievement_manager.h#L60)

```text
// Unlock persistence and presentation are separate by default. Pass kShow
```

## Source note 6, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievement_manager.h#L61)

```text
// for a convenience notification, or call ShowAchievementNotification()
```

## Source note 7, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievement_manager.h#L62)

```text
// explicitly when title-specific timing is required.
```
