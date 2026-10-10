# Spirv compatibility: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/spirv_compatibility.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L20)

```text
// Backward compatibility for Op codes - old style was spv::OpXXX, new is
```

## Source note 2, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L21)

```text
// spv::Op::OpXXX We provide the old style as direct aliases in the spv
```

## Source note 3, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L23)

```text
// Op code compatibility macros
```

## Source note 4, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L313)

```text
// Direct aliases for Op codes in the main spv namespace
```

## Source note 5, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L314)

```text
// This allows code like spv::OpFAdd to work without qualification
```

## Source note 6, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L316)

```text
// Inject old-style OpXXX names into spv namespace
```

## Source note 7, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L318)

```text
// Backward compatibility for Decoration names
```

## Source note 8, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L319)

```text
// Only include decorations that actually exist
```

## Source note 9, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L346)

```text
// Backward compatibility for ImageOperands
```

## Source note 10, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L352)

```text
// Backward compatibility for StorageClass
```

## Source note 11, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L359)

```text
// Backward compatibility for SelectionControl
```

## Source note 12, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L363)

```text
// Backward compatibility for Capability
```

## Source note 13, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L380)

```text
// Backward compatibility for AddressingModel
```

## Source note 14, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L383)

```text
// Backward compatibility for MemoryModel
```

## Source note 15, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L386)

```text
// Backward compatibility for SourceLanguage
```

## Source note 16, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L389)

```text
// Backward compatibility for ExecutionModel
```

## Source note 17, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L396)

```text
// Backward compatibility for ExecutionMode
```

## Source note 18, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L424)

```text
// Backward compatibility for Decoration
```

## Source note 19, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L435)

```text
// Backward compatibility for LoopControl
```

## Source note 20, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L438)

```text
// Backward compatibility for StorageClass (additional)
```

## Source note 21, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L442)

```text
// Backward compatibility for Dim
```

## Source note 22, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L447)

```text
// Backward compatibility for ImageFormat
```

## Source note 23, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L450)

```text
// Backward compatibility for OpDemoteToHelperInvocationEXT
```

## Source note 24, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L456)

```text
// Backward compatibility for Scope
```

## Source note 25, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_compatibility.h#L459)

```text
// Fragment barycentric BuiltIn values
```
