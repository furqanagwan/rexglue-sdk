# Vtable scanner: codegen source notes

This record preserves technical and API notes moved from `src/codegen/vtable_scanner.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L27)

```text
// Step 1: Find all Complete Object Locators
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L31)

```text
// Step 2: For each COL, find its vtable and read slots
```

## Source note 3, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L62)

```text
// Scan .rdata section for COL patterns
```

## Source note 4, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L73)

```text
// COL is 20 bytes, need room for it
```

## Source note 5, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L78)

```text
// Scan for COL pattern: signature=0, valid type descriptor pointer
```

## Source note 6, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L85)

```text
// COL signature must be 0 for 32-bit MSVC RTTI
```

## Source note 7, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L90)

```text
// Type descriptor must point to valid memory
```

## Source note 8, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L96)

```text
// Check if type descriptor has ".?AV" mangling prefix
```

## Source note 9, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L112)

```text
// The vtable pointer to COL is stored at vtable[-1]
```

## Source note 10, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L113)

```text
// So we need to find a dword in .rdata that contains colAddr,
```

## Source note 11, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L114)

```text
// and the vtable starts at that address + 4
```

## Source note 12, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L129)

```text
// Found reference to COL - vtable starts at next dword
```

## Source note 13, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L146)

```text
// Can't read memory
```

## Source note 14, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L151)

```text
// Termination: null pointer
```

## Source note 15, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L156)

```text
// Termination: not executable address
```

## Source note 16, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L161)

```text
// Termination: not 4-byte aligned (PPC requirement)
```

## Source note 17, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L174)

```text
// pTypeDescriptor offset
```

## Source note 18, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L179)

```text
// Class name is at typeDescriptor + 8
```

## Source note 19, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/vtable_scanner.cpp#L182)

```text
// Simple demangling: ".?AVClassName@@" -> "ClassName"
```
