# User profile: system source notes

This record preserves technical and API notes moved from `include/rex/system/xam/user_profile.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L35)

```text
// UserProfile::Setting::Type. Appears to be 8-in-32 field, and the upper 24
```

## Source note 2, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L36)

```text
// are not always zeroed by the game.
```

## Source note 3, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L114)

```text
// Whether loaded_title_id names the title this value belongs to; the
```

## Source note 4, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L115)

```text
// defaults a profile starts with belong to none.
```

## Source note 5, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L119)

```text
// Settings are owned through the base; derived ones hold vectors.
```

## Source note 6, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L227)

```text
/* local | online profile? */
```

## Source note 7, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L231)

```text
// Adds or replaces a setting; a title-specific one is also saved to disk.
```

## Source note 8, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L232)

```text
// Returns false if that save failed (the setting is still replaced).
```

## Source note 9, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L234)

```text
// The setting, kept alive while the caller holds it even if another thread
```

## Source note 10, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L235)

```text
// replaces it (xenia-canary #5, #981). Null if unknown.
```

## Source note 11, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L241)

```text
// Guest threads read and write settings concurrently.
```

## Source note 12, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L246)

```text
// With settings_mutex_ held.
```

## Source note 13, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/user_profile.h#L255)

```text
// fmt formatter for UserProfile::Setting::Type
```
