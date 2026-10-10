# Function: ppc source notes

This record preserves technical and API notes moved from `include/rex/ppc/function.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L36)

```text
// Global PPC Function Registry (for runtime ordinal lookup)
```

## Source note 2, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L38)

```text
// Populated by static constructors from XAM_EXPORT / XBOXKRNL_EXPORT macros.
```

## Source note 3, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L62)

```text
// Type Traits (additional, types.h has is_be_type)
```

## Source note 4, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L65)

```text
// Function argument helpers
```

## Source note 5, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L78)

```text
// Concepts for Type Constraints
```

## Source note 6, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L90)

```text
// A "plain" type: not a pointer, not be<T>, not MappedPtr
```

## Source note 7, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L100)

```text
// Argument Translator
```

## Source note 8, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L104)

```text
// Get integer argument value from register or stack
```

## Source note 9, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L129)

```text
// Stack arguments at r1 + 0x54 + ((arg - 8) * 8)
```

## Source note 10, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L134)

```text
// Get float/double argument value from FPR
```

## Source note 11, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L170)

```text
// Set integer argument value
```

## Source note 12, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L203)

```text
// Stack-passed arguments (mirrors GetIntegerArgumentValue layout)
```

## Source note 13, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L208)

```text
// Set float/double argument value
```

## Source note 14, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L256)

```text
// Get typed value (be<T> types)
```

## Source note 15, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L264)

```text
// Get typed value (MappedPtr<T>)
```

## Source note 16, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L277)

```text
// Get typed value (non-pointer, non-be<T>, non-MappedPtr)
```

## Source note 17, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L287)

```text
// Get typed value (pointer - translates guest address to host pointer)
```

## Source note 18, line 299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L299)

```text
// Set typed value
```

## Source note 19, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L317)

```text
// Argument Gathering
```

## Source note 20, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L321)

```text
// 0 = integer, 1 = float
```

## Source note 21, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L322)

```text
// Position in integer or float argument list
```

## Source note 22, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L325)

```text
// Helper to detect precise types
```

## Source note 23, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L331)

```text
// Type-only gather helper - doesn't require constexpr-constructible types
```

## Source note 24, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L353)

```text
// Helper to extract args tuple types and call GatherFunctionArgumentsFromTypes
```

## Source note 25, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L370)

```text
// Argument Translation
```

## Source note 26, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L401)

```text
// Host To PPC Function Wrapper
```

## Source note 27, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L403)

```text
// Calls a native C++ function with arguments extracted from PPC context
```

## Source note 28, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L411)

```text
// The export runs in the host's FP mode, not the guest's (RG-GDK-056).
```

## Source note 29, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L419)

```text
// Memory barrier to ensure compiler doesn't reorder
```

## Source note 30, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L438)

```text
// PPC To Host Function Wrapper
```

## Source note 31, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L440)

```text
// Calls a PPC function from host code with proper context setup
```

## Source note 32, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L468)

```text
// PPC64 minimum frame: linkage + param save
```

## Source note 33, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ppc/function.h#L501)

```text
/// Maximum size of the loaded image name buffer (255 chars + NUL).
```
