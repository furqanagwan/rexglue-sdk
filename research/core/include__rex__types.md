# Types: core source notes

This record preserves technical and API notes moved from `include/rex/types.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L26)

```text
// Check for mixed endian
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L32)

```text
/// Byte-swap a value of any trivially copyable type (1, 2, 4, or 8 bytes).
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L33)

```text
/// Uses std::bit_cast for safe type punning and std::byteswap for the swap.
```

## Source note 4, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L41)

```text
// Convert to unsigned integer of same size, byteswap, convert back
```

## Source note 5, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L50)

```text
// Type alias for value() in MappedPtr
```

## Source note 6, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L83)

```text
// ++a
```

## Source note 7, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L87)

```text
// a++
```

## Source note 8, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L91)

```text
// --a
```

## Source note 9, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L95)

```text
// a--
```

## Source note 10, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L106)

```text
// Big-Endian Type Detection
```

## Source note 11, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L119)

```text
// Basic Integer Types
```

## Source note 12, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L139)

```text
// Memory Address Types
```

## Source note 13, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L142)

```text
// Xbox 360 guest address (32-bit)
```

## Source note 14, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L143)

```text
// Host native address (64-bit on x64)
```

## Source note 15, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L146)

```text
// Big-Endian Type Aliases (using rex::be<T>)
```

## Source note 16, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L149)

```text
// No byte-swapping needed for single bytes
```

## Source note 17, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L163)

```text
// MappedPtr - Wraps host pointer with guest address tracking
```

## Source note 18, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L228)

```text
// MappedPtr<void> Specialization
```

## Source note 19, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L281)

```text
// MappedPtr<char> Specialization (strings)
```

## Source note 20, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L323)

```text
// MappedPtr<char16_t> Specialization (wide strings)
```

## Source note 21, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L365)

```text
// MappedPtr Type Traits
```

## Source note 22, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L385)

```text
// Global Namespace Exports
```

## Source note 23, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/types.h#L418)

```text
// Legacy compat alias for ppc_ptr_t<T>
```
