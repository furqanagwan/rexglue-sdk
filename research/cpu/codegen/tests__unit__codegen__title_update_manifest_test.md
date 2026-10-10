# Title update manifest test: codegen source notes

This record preserves technical and API notes moved from `tests/unit/codegen/title_update_manifest_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/title_update_manifest_test.cpp#L24)

```text
// A project folder with a manifest and the configs it includes.
```

## Source note 2, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/title_update_manifest_test.cpp#L82)

```text
// Its own includes replace the original's: addresses differ between versions.
```

## Source note 3, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/title_update_manifest_test.cpp#L85)

```text
// The original is untouched.
```

## Source note 4, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/title_update_manifest_test.cpp#L139)

```text
// The update's sources.cmake must not replace the original's add-on list:
```

## Source note 5, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/title_update_manifest_test.cpp#L140)

```text
// each executable embeds its own version's catalogue.
```

## Source note 6, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/title_update_manifest_test.cpp#L145)

```text
// Codegen's rule produces the update's sources too, so the build orders after it.
```
