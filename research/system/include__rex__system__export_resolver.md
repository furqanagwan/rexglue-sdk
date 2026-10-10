# Export resolver: system source notes

This record preserves technical and API notes moved from `include/rex/system/export_resolver.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L44)

```text
// packed like so:
```

## Source note 2, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L45)

```text
// ll...... cccccccc ........ ..bihssi
```

## Source note 3, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L49)

```text
// Export is implemented in some form and can be used.
```

## Source note 4, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L51)

```text
// Export is a stub and is probably bad.
```

## Source note 5, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L53)

```text
// Export is known to cause problems, or may not be complete.
```

## Source note 6, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L55)

```text
// Export is called *a lot*.
```

## Source note 7, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L57)

```text
// Export is important and should always be logged.
```

## Source note 8, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L59)

```text
// Export blocks the calling thread
```

## Source note 9, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L62)

```text
// Export will be logged on each call.
```

## Source note 10, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L64)

```text
// Export's result will be logged on each call.
```

## Source note 11, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L90)

```text
// Variable data. Only valid when type == kVariable.
```

## Source note 12, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L91)

```text
// This is an address in the guest memory space where the variable can
```

## Source note 13, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L92)

```text
// be found at.
```

## Source note 14, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/export_resolver.h#L96)

```text
// Function data (not used in recompiled builds, but kept for structure)
```
