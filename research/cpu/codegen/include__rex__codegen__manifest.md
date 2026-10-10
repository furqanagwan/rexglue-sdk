# Manifest: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/manifest.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L24)

```text
/**
 * Codegen settings for a single binary inside a manifest. The entrypoint
 * uses an empty `guestPath`; module entries set it to the canonicalized
 * guest-visible path the host runtime resolves against.
 */
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L34)

```text
/**
 * A title update to build as its own executable ([[title_update]]): the
 * entrypoint again, with the update's XEX patches applied and its own config.
 */
```

## Source note 3, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L39)

```text
///< The title update's version (its LIVE package's)
```

## Source note 4, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L40)

```text
///< Its LIVE/CON package, or a folder of its files
```

## Source note 5, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L41)

```text
///< The entrypoint's settings with this version's own
```

## Source note 6, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L42)

```text
///< out_directory_path and includes
```

## Source note 7, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L45)

```text
/**
 * Canonicalize a module guest path: device-stripped, slashes/case normalized,
 * with `<project>/assets/` stripped when a matching project name is given.
 */
```

## Source note 8, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L51)

```text
/**
 * Parsed manifest TOML. Construct via Load(); treat as read-only after.
 */
```

## Source note 9, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L56)

```text
///< Last SDK that ran codegen on this project
```

## Source note 10, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L57)

```text
///< File this manifest was loaded from
```

## Source note 11, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L58)

```text
///< Game asset root, relative to manifestDir.
```

## Source note 12, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L59)

```text
///< Set by `rexglue init` to anchor DLL guest paths.
```

## Source note 13, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L60)

```text
///< Directory containing the manifest
```

## Source note 14, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L61)

```text
///< Entrypoint codegen settings (inline)
```

## Source note 15, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L62)

```text
///< DLL module codegen settings (inline)
```

## Source note 16, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L63)

```text
///< Title updates, each its own executable
```

## Source note 17, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L65)

```text
/**
   * Load a manifest TOML file. Returns nullopt on parse failure.
   */
```

## Source note 18, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L70)

```text
/**
   * True when `path` parses as a manifest (i.e. has a `[project]` section).
   */
```

## Source note 19, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/manifest.h#L75)

```text
/**
   * Insert or overwrite [project].sdk_version in the manifest file at `path`.
   * Preserves the rest of the file's content. Returns false on parse or write
   * failure.
   */
```
