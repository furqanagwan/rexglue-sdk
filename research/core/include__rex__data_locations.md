# Data locations: core source notes

This record preserves technical and API notes moved from `include/rex/data_locations.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L18)

```text
// %USERPROFILE%\Saved Games (FOLDERID_SavedGames). The GDK's advice for saves
```

## Source note 2, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L19)

```text
// a title keeps itself: OneDrive does not sync it by default.
```

## Source note 3, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L22)

```text
// %LOCALAPPDATA% (FOLDERID_LocalAppData): per-user, per-machine data such as
```

## Source note 4, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L23)

```text
// caches, logs and settings.
```

## Source note 5, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L26)

```text
// Default per-title locations. Saves go under Saved Games; everything the
```

## Source note 6, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L27)

```text
// title can rebuild or that belongs to this machine goes under local app data.
```

## Source note 7, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L29)

```text
// Saved Games\<name>
```

## Source note 8, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L30)

```text
// %LOCALAPPDATA%\<name>
```

## Source note 9, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L31)

```text
// %LOCALAPPDATA%\<name>\cache
```

## Source note 10, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L32)

```text
// %LOCALAPPDATA%\<name>\logs
```

## Source note 11, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L33)

```text
// %LOCALAPPDATA%\<name>\<name>.toml
```

## Source note 12, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L40)

```text
// The game files beside the executable: `<exe_dir>\game` or `<exe_dir>`
```

## Source note 13, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L41)

```text
// itself, whichever holds `default.xex` first. Empty when neither does.
```

## Source note 14, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L44)

```text
// Result of moving a title's user data out of its old default location.
```

## Source note 15, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L46)

```text
// renamed into place; the old folder is gone
```

## Source note 16, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L47)

```text
// copied (another volume); the old folder stays
```

## Source note 17, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L48)

```text
// its cache went to the new cache location
```

## Source note 18, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L49)

```text
// why nothing was moved, if something failed
```

## Source note 19, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L52)

```text
// Moves `legacy_user` (the old Documents\<name>) to `user_data` once, when the
```

## Source note 20, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L53)

```text
// old folder exists and the new one does not. A rename is tried first; across
```

## Source note 21, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L54)

```text
// volumes (for example Documents redirected to OneDrive on another drive) the
```

## Source note 22, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L55)

```text
// data is copied and the old folder left in place. A cache folder inside it
```

## Source note 23, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L56)

```text
// moves to `cache` first; it is never copied, and goes along only with a
```

## Source note 24, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L57)

```text
// rename when it could not be moved on its own. A failed copy is removed, so the next start tries
```

## Source note 25, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/data_locations.h#L58)

```text
// again.
```
