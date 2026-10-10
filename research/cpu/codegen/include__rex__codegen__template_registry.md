# Template registry: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/template_registry.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L20)

```text
/// Exception thrown on template parse or render errors.
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L34)

```text
/// Resolves and renders inja templates by canonical ID.
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L35)

```text
/// Supports embedded defaults with optional filesystem overrides.
```

## Source note 4, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L37)

```text
/// Uses pimpl to keep inja.hpp and nlohmann/json.hpp out of this header.
```

## Source note 5, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L38)

```text
/// The render() method accepts serialized JSON (const std::string&) to avoid
```

## Source note 6, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L39)

```text
/// exposing nlohmann::json in the public API.
```

## Source note 7, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L50)

```text
/// Load overrides from a directory. Files that don't match
```

## Source note 8, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L51)

```text
/// a known canonical ID produce a warning log.
```

## Source note 9, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L54)

```text
/// Render a template by canonical ID with JSON data (as serialized string).
```

## Source note 10, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L55)

```text
/// @throws TemplateError on parse or render failure
```

## Source note 11, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L58)

```text
/// Render from raw template string (for testing). Not tied to a canonical ID.
```

## Source note 12, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L61)

```text
/// List all registered canonical IDs.
```

## Source note 13, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L69)

```text
/// SHA256 over every embedded template, ordered by ID. Fold this into any
```

## Source note 14, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L70)

```text
/// cache key built from the SDK version: that version is stable across dev
```

## Source note 15, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/template_registry.h#L71)

```text
/// builds, so a template edit alone would not otherwise invalidate it.
```
