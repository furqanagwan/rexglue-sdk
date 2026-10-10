# User profile: system source notes

This record preserves technical and API notes moved from `src/system/xam/user_profile.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L33)

```text
// A 360 gamertag: up to 15 characters (XUSER_NAME_SIZE 16, with the null).
```

## Source note 2, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L36)

```text
// The gamertag of the Xbox account signed in to Windows. The Xbox app's sign-in
```

## Source note 3, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L37)

```text
// keeps it in HKCU\Software\Microsoft\XboxLive (Gamertag, the classic form);
```

## Source note 4, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L38)

```text
// this is not a documented interface, so it is read only and may be missing.
```

## Source note 5, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L39)

```text
// XUserGetGamertag needs a Store package identity and a registered title, which
```

## Source note 6, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L40)

```text
// a recompiled title does not have (E_GAMEUSER_NO_PACKAGE_IDENTITY).
```

## Source note 7, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L65)

```text
// the lead byte of the character cut short
```

## Source note 8, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L74)

```text
// 58410A1F checks the user XUID against a mask of 0x00C0000000000000 (3<<54),
```

## Source note 9, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L75)

```text
// if non-zero, it prevents the user from playing the game.
```

## Source note 10, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L76)

```text
// "You do not have permissions to perform this operation."
```

## Source note 11, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L80)

```text
// https://cs.rin.ru/forum/viewtopic.php?f=38&t=60668&hilit=gfwl+live&start=195
```

## Source note 12, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L81)

```text
// https://github.com/arkem/py360/blob/master/py360/constants.py
```

## Source note 13, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L110)

```text
// Preferred color 1
```

## Source note 14, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L112)

```text
// Preferred color 2
```

## Source note 15, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L133)

```text
// If we set this, games will try to get it.
```

## Source note 16, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L137)

```text
// XPROFILE_TITLE_SPECIFIC1
```

## Source note 17, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L139)

```text
// XPROFILE_TITLE_SPECIFIC2
```

## Source note 18, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L141)

```text
// XPROFILE_TITLE_SPECIFIC3
```

## Source note 19, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L149)

```text
// Written by a title, it is now that title's copy, saved or not. The
```

## Source note 20, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L150)

```text
// defaults added before a kernel exists belong to no title.
```

## Source note 21, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L159)

```text
// A reader still holding the previous setting keeps it alive. Read the id
```

## Source note 22, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L160)

```text
// first: the right side of the assignment is evaluated (and moved) first.
```

## Source note 23, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L173)

```text
// If what we have loaded in memory isn't for the title that is running right
```

## Source note 24, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L174)

```text
// now, load that title's copy from disk.
```

## Source note 25, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L184)

```text
// Title-specific settings are binary. A fresh object each time: readers of
```

## Source note 26, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L185)

```text
// the previous one are unaffected, and a title with no saved copy gets an
```

## Source note 27, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L186)

```text
// unset setting instead of the previous title's value.
```

## Source note 28, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L221)

```text
// Title-specific settings are save data too: written whole and flushed.
```

## Source note 29, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L229)

```text
// Unsupported for now.  Other settings aren't per-game and need to be
```

## Source note 30, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/user_profile.cpp#L230)

```text
// stored some other way.
```
