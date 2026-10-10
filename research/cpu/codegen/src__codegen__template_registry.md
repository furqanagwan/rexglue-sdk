# Template registry: codegen source notes

This record preserves technical and API notes moved from `src/codegen/template_registry.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L18)

```text
// Generated at build time by cmake/embed_templates.cmake
```

## Source note 2, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L51)

```text
// cmake_var callback: wraps a variable name in ${ }
```

## Source note 3, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L56)

```text
// hex callback: format an integer as 0x-prefixed hex
```

## Source note 4, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L64)

```text
// Resolve {% include "<id>" %} against the embedded registry. Templates
```

## Source note 5, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L65)

```text
// are embedded under canonical IDs without the .inja extension; accept
```

## Source note 6, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L66)

```text
// either form so include directives can use either.
```

## Source note 7, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L83)

```text
// Check overrides first
```

## Source note 8, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L89)

```text
// Check parsed cache
```

## Source note 9, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L95)

```text
// Look up in embedded templates
```

## Source note 10, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L101)

```text
// Parse, cache, and render
```

## Source note 11, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L109)

```text
// TemplateRegistry special members
```

## Source note 12, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L118)

```text
// TemplateRegistry public methods
```

## Source note 13, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L133)

```text
// Compute canonical ID from relative path, stripping .inja extension
```

## Source note 14, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L135)

```text
// Normalize path separators to forward slash
```

## Source note 15, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L137)

```text
// Strip .inja extension
```

## Source note 16, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L138)

```text
// strlen(".inja") == 5
```

## Source note 17, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L165)

```text
// Already wrapped
```

## Source note 18, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/template_registry.cpp#L220)

```text
// Free function: renderWithJson (internal API)
```
