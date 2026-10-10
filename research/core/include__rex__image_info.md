# Image info: core source notes

This record preserves technical and API notes moved from `include/rex/image_info.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L24)

```text
/**
 * Callback for registering recompiled modules with KernelState (multi-binary projects).
 */
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L40)

```text
/// A code patch compiled with both instruction versions. `active` is the
```

## Source note 3, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L41)

```text
/// flag the recompiled code reads; setting it switches the patch live.
```

## Source note 4, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L45)

```text
///< "patch" or "mod"
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L48)

```text
/// A cheat code the title's developers built in, for the guide's Cheats page.
```

## Source note 6, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L52)

```text
///< What it unlocks
```

## Source note 7, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L53)

```text
///< Where the game takes the code
```

## Source note 8, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L56)

```text
/// An add-on the title had in the marketplace, for the guide's Manage Game
```

## Source note 9, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L57)

```text
/// page; its name, description and art come from the built-in catalogue.
```

## Source note 10, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L59)

```text
///< marketplace media ID
```

## Source note 11, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L60)

```text
///< display name in its package, when not the catalogue's
```

## Source note 12, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L61)

```text
///< the title update version it needs; 0 for none
```

## Source note 13, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L64)

```text
/// A title update the title had ([[title_update]] in its config), for the
```

## Source note 14, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L65)

```text
/// guide's Title Updates page: optional, downloaded and installed by the player.
```

## Source note 15, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L67)

```text
///< the update's number (Xbox Unity's Version)
```

## Source note 16, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L68)

```text
///< the disc's media ID it applies to, 8 hex digits
```

## Source note 17, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L69)

```text
///< the executable version it updates (header 0x35C)
```

## Source note 18, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L70)

```text
///< package content ID, 40 hex digits (Xbox Unity's hash)
```

## Source note 19, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L71)

```text
///< package size in KB, 0 when unknown
```

## Source note 20, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L72)

```text
///< release or upload date, empty when unknown
```

## Source note 21, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L73)

```text
///< what it changes, empty when unknown
```

## Source note 22, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L76)

```text
/// PPC image layout passed from the generated config header into ReXApp.
```

## Source note 23, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L82)

```text
/// Where the function dispatch table goes; 0 for image_base + image_size.
```

## Source note 24, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L83)

```text
/// Codegen moves it when a guest DLL's image would sit there.
```

## Source note 25, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L86)

```text
///< Set by codegen when [rexcrt] has heap functions
```

## Source note 26, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L87)

```text
///< Set by codegen for multi-binary projects
```

## Source note 27, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L88)

```text
///< Set by codegen from the config flags
```

## Source note 28, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L89)

```text
/// Guest code patches compiled in, comma-separated; empty when none.
```

## Source note 29, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L91)

```text
/// Switchable patches, ended by a null name; null when codegen predates them.
```

## Source note 30, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L93)

```text
/// The title's own cheat codes, ended by a null name; null when none.
```

## Source note 31, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L95)

```text
/// The title's add-ons, ended by a null id; null when none.
```

## Source note 32, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L97)

```text
/// The title update this executable was built for; 0 for the original. A
```

## Source note 33, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L98)

```text
/// title update build applies that update's XEX patches (update:) at load.
```

## Source note 34, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L100)

```text
/// The title updates the title had, ended by a zero version; null when none.
```

## Source note 35, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L102)

```text
/// Raw source XEX identity for first-run source validation. Empty for older
```

## Source note 36, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L103)

```text
/// generated code. A TU build fingerprints its original, unpatched input XEX.
```

## Source note 37, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L107)

```text
/// The source XEX's XDBF display name, for naming it when a source holds
```

## Source note 38, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/image_info.h#L108)

```text
/// another game; empty for older generated code.
```
