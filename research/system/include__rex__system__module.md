# Module: system source notes

This record preserves technical and API notes moved from `include/rex/system/module.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/module.h#L39)

```text
// Binary introspection interface (virtual with defaults for backwards compat)
```

## Source note 2, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/module.h#L45)

```text
// Exception DataDirectory accessors (for PDATA table)
```

## Source note 3, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/module.h#L46)

```text
// These return the correct PDATA location from the PE Optional Header.
```

## Source note 4, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/module.h#L51)

```text
// Check if address is in an executable section
```

## Source note 5, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/module.h#L54)

```text
// Section access - default implementations return empty
```

## Source note 6, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/module.h#L59)

```text
// Symbol access - default implementations return empty
```

## Source note 7, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/module.h#L65)

```text
// Symbol manipulation helpers (for external symbol loading, e.g., from map files)
```

## Source note 8, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/module.h#L73)

```text
// Storage for binary introspection (populated by derived classes)
```
