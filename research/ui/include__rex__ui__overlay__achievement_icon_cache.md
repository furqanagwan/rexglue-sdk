# Achievement icon cache: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/overlay/achievement_icon_cache.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/achievement_icon_cache.h#L35)

```text
// Loads the achievement icon in priority order:
```

## Source note 2, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/achievement_icon_cache.h#L36)

```text
// 1. explicit metadata icon_path
```

## Source note 3, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/achievement_icon_cache.h#L37)

```text
// 2. embedded metadata icon_path
```

## Source note 4, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/achievement_icon_cache.h#L38)

```text
// 3. metadata icons/<image_id>.png
```

## Source note 5, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/achievement_icon_cache.h#L39)

```text
// 4. embedded metadata icons/<image_id>.png
```

## Source note 6, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/achievement_icon_cache.h#L40)

```text
// 5. title XDBF image <image_id> embedded in the loaded XEX
```
