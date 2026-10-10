# Xam user: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xam/xam_user.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L56)

```text
// maybe online profile?
```

## Source note 3, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L60)

```text
// maybe offline profile?
```

## Source note 4, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L85)

```text
// maybe zero?
```

## Source note 5, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L150)

```text
// https://github.com/oukiar/freestyledash/blob/master/Freestyle/Tools/Generic/xboxtools.cpp
```

## Source note 6, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L167)

```text
// probably flags
```

## Source note 7, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L169)

```text
// must have at least 1 to 32 settings
```

## Source note 8, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L174)

```text
// buffer size pointer must be valid
```

## Source note 9, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L179)

```text
// if buffer size is non-zero, buffer pointer must be valid
```

## Source note 10, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L214)

```text
// Title ID = 0 means us.
```

## Source note 11, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L215)

```text
// 0xfffe07d1 = profile?
```

## Source note 12, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L218)

```text
// Only support user 0.
```

## Source note 13, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L229)

```text
// First call asks for size (fill buffer_size_ptr).
```

## Source note 14, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L230)

```text
// Second call asks for buffer contents with that size.
```

## Source note 15, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L312)

```text
// Only support user 0.
```

## Source note 16, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L321)

```text
// Update and save settings.
```

## Source note 17, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L344)

```text
// Copy provided data
```

## Source note 18, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L348)

```text
// Data pointer was NULL, so just fill with zeroes
```

## Source note 19, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L374)

```text
// checking all users?
```

## Source note 20, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L385)

```text
// If we deny everything, games should hopefully not try to do stuff.
```

## Source note 21, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L395)

```text
// No restrictions?
```

## Source note 22, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L406)

```text
// Some games have special case paths for 3F that differ from the failure
```

## Source note 23, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L407)

```text
// path, so my guess is that's 'don't care'.
```

## Source note 24, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L435)

```text
/* 6 appears to be Gold */
```

## Source note 25, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L451)

```text
// No friends!
```

## Source note 26, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L456)

```text
// Only support user 0.
```

## Source note 27, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L457)

```text
// if user is local -> X_ERROR_NOT_LOGGED_ON
```

## Source note 28, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L478)

```text
// Mask values vary. Probably matching user types? Local/remote?
```

## Source note 29, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L480)

```text
// To fix game modes that display a 4 profile signin UI (even if playing
```

## Source note 30, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L481)

```text
// alone):
```

## Source note 31, line 484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L484)

```text
// Games seem to sit and loop until we trigger this notification:
```

## Source note 32, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L485)

```text
// XN_SYS_UI (off)
```

## Source note 33, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L525)

```text
// Enumeration starts at the title's offset: titles page through their
```

## Source note 34, line 526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L526)

```text
// achievements with one enumerator per page (Canary 603355ae5b).
```

## Source note 35, line 624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L624)

```text
// ACHIEVED | ACHIEVED_ONLINE flags the game checks to consider an achievement earned.
```

## Source note 36, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L639)

```text
// Prefer the runtime store (populated from TOML or XDBF at boot) so that
```

## Source note 37, line 640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_user.cpp#L640)

```text
// dev-edited labels/descriptions are visible to the game's own queries.
```
