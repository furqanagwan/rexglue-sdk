# Vtable scanner: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/vtable_scanner.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L24)

```text
// RTTI Structures (MSVC-based, Xbox 360)
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L27)

```text
// Type descriptor - contains mangled class name
```

## Source note 3, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L29)

```text
// Always points to type_info vtable
```

## Source note 4, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L30)

```text
// Runtime use, always 0 in image
```

## Source note 5, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L31)

```text
// char name[];         // Mangled name: ".?AVClassName@@"
```

## Source note 6, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L34)

```text
// Complete Object Locator - links vtable to type info
```

## Source note 7, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L36)

```text
// Always 0 for 32-bit
```

## Source note 8, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L37)

```text
// Offset of this vtable in complete class
```

## Source note 9, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L38)

```text
// Constructor displacement offset
```

## Source note 10, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L39)

```text
// Pointer to TypeDescriptor
```

## Source note 11, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L40)

```text
// Pointer to class hierarchy descriptor
```

## Source note 12, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L44)

```text
// VTableInfo - Result of vtable scanning
```

## Source note 13, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L48)

```text
// Address of vtable[0]
```

## Source note 14, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L49)

```text
// RTTI Complete Object Locator address
```

## Source note 15, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L50)

```text
// Demangled class name (optional)
```

## Source note 16, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L51)

```text
// Function addresses in vtable
```

## Source note 17, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L55)

```text
// VTableScanner - RTTI-based vtable discovery
```

## Source note 18, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L62)

```text
// Scan for all vtables via RTTI traversal
```

## Source note 19, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L68)

```text
// Find all Complete Object Locators in .rdata
```

## Source note 20, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L71)

```text
// Find the vtable that references a given COL (COL is at vtable[-1])
```

## Source note 21, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L74)

```text
// Read all function slots from a vtable (until non-executable address)
```

## Source note 22, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L77)

```text
// Extract class name from type descriptor
```

## Source note 23, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L80)

```text
// Check if an address points to executable code
```

## Source note 24, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L83)

```text
// Read a dword from the binary
```

## Source note 25, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/vtable_scanner.h#L86)

```text
// Read a string from the binary
```
