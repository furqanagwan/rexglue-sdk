# Guest path: system source notes

This record preserves technical and API notes moved from `include/rex/system/guest_path.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/guest_path.h#L20)

```text
/**
 * Normalize a guest path to the canonical form used as a key for runtime
 * lookups: device prefix stripped, separators canonicalized to forward
 * slashes, redundant `..` segments resolved, leading slashes removed,
 * and ASCII lowercased. Codegen-side canonicalization
 * (rex::codegen::CanonicalizeModuleGuestPath) layers a project-scoped prefix
 * strip on top of this; both must agree on this base form for runtime
 * lookups to find the registered module.
 */
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/guest_path.h#L31)

```text
/**
 * Whether normalized `path` names `module_path` (normalized, relative to the
 * game root) through a device path: it ends with `/module_path`. Modules
 * loaded by a bare name are joined to the executable's device path
 * (\Device\Harddisk0\Partition1\...), which NormalizeGuestPath keeps.
 */
```

## Source note 3, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/guest_path.h#L39)

```text
/// Return an unqualified ObDosDevices name suitable for opening relative to
```

## Source note 4, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/guest_path.h#L40)

```text
/// the title directory. A trailing separator names the directory itself.
```
