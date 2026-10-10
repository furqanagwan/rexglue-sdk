# Dxbc translator: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/dxbc_translator.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L35)

```text
// Notes about operands:
```

## Source note 2, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L37)

```text
// Reading and writing:
```

## Source note 3, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L38)

```text
// - r# (temporary registers) are 4-component and can be used anywhere.
```

## Source note 4, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L39)

```text
// - v# (inputs) are 4-component and read-only.
```

## Source note 5, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L40)

```text
// - o# (outputs) are 4-component and write-only.
```

## Source note 6, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L41)

```text
// - oDepth (pixel shader depth output) is 1-component and write-only.
```

## Source note 7, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L42)

```text
// - x# (indexable temporary registers) are 4-component and can be accessed
```

## Source note 8, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L43)

```text
//   either via a mov load or a mov store (and those movs are counted as
```

## Source note 9, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L44)

```text
//   ArrayInstructions in STAT, not as MovInstructions), even though the D3D11.3
```

## Source note 10, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L45)

```text
//   functional specification says x# can be used wherever r# can be used, but
```

## Source note 11, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L46)

```text
//   FXC emits only mov load/store in simple tests.
```

## Source note 12, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L49)

```text
// - Constant buffers use 3D indices in CBx[y][z] format, where x is the ID of
```

## Source note 13, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L50)

```text
//   the binding (CB#), y is the register to access within its space, z is the
```

## Source note 14, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L51)

```text
//   4-component vector to access within the register binding.
```

## Source note 15, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L52)

```text
//   For example, if the requested vector is located in the beginning of the
```

## Source note 16, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L53)

```text
//   second buffer in the descriptor array at b2, which is assigned to CB1, the
```

## Source note 17, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L54)

```text
//   index would be CB1[3][0].
```

## Source note 18, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L55)

```text
// - Resources and samplers use 2D indices, where the first dimension is the
```

## Source note 19, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L56)

```text
//   S#/T#/U# binding index, and the second is the s#/t#/u# register index
```

## Source note 20, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L57)

```text
//   within its space.
```

## Source note 21, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L78)

```text
// Don't allocate again and again for the first shader.
```

## Source note 22, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L127)

```text
// System constants always used in prologues/epilogues.
```

## Source note 23, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L185)

```text
// Xenia crashes on Intel HD Graphics 4000 with switch.
```

## Source note 24, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L192)

```text
// Guest shader registers first if they're not in x0. Depth-only pixel
```

## Source note 25, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L193)

```text
// shader is a special case of the DXBC translator usage, where there are no
```

## Source note 26, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L194)

```text
// GPRs because there's no shader to translate, and a guest shader is not
```

## Source note 27, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L195)

```text
// loaded.
```

## Source note 28, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L220)

```text
// The source is needed only once to begin building the result, so it can be
```

## Source note 29, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L221)

```text
// the same as the destination.
```

## Source note 30, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L235)

```text
// Get the scale (into temp1) and the offset (into temp2) for the piece.
```

## Source note 31, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L236)

```text
// Using `source >= threshold` comparisons because the input might have not
```

## Source note 32, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L237)

```text
// been saturated yet, and thus it may be NaN - since it will be saturated to
```

## Source note 33, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L238)

```text
// 0 later, the 0...64/255 case should be selected for it.
```

## Source note 34, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L241)

```text
// [96/255 ... 1
```

## Source note 35, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L246)

```text
// 0 ... 96/255)
```

## Source note 36, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L253)

```text
// Saturate the input, and flush NaN to 0.
```

## Source note 37, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L256)

```text
// linear = gamma * (255 * 1024) * scale + offset
```

## Source note 38, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L257)

```text
// As both 1024 and the scale are powers of 2, and 1024 * scale is not smaller
```

## Source note 39, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L258)

```text
// than 1, it's not important if it's (gamma * 255) * 1024 * scale,
```

## Source note 40, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L259)

```text
// (gamma * 255 * 1024) * scale, gamma * 255 * (1024 * scale), or
```

## Source note 41, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L260)

```text
// gamma * (255 * 1024 * scale) - or the option chosen here, as long as
```

## Source note 42, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L261)

```text
// 1024 is applied before the scale since the scale is < 1 (specifically at
```

## Source note 43, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L262)

```text
// least 1/1024), and it may make very small values denormal.
```

## Source note 44, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L266)

```text
// linear += trunc(linear * scale)
```

## Source note 45, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L270)

```text
// linear *= 1/1023
```

## Source note 46, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L278)

```text
// The source may be the same as the target, but in this case it can't also be
```

## Source note 47, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L279)

```text
// used as a temporary variable.
```

## Source note 48, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L297)

```text
// Get the scale (into temp_or_target) and the offset (into temp_non_target)
```

## Source note 49, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L298)

```text
// for the piece.
```

## Source note 50, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L301)

```text
// [128/1023 ... 1
```

## Source note 51, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L308)

```text
// 0 ... 128/1023)
```

## Source note 52, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L316)

```text
// gamma = trunc(linear * scale) * (1.0 / 255.0) + offset
```

## Source note 53, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L328)

```text
// Add the base vertex index.
```

## Source note 54, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L333)

```text
// Mask since the GPU only uses the lower 24 bits of the vertex index (tested
```

## Source note 55, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L334)

```text
// on an Adreno 200 phone). `((index & 0xFFFFFF) + offset) & 0xFFFFFF` is the
```

## Source note 56, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L335)

```text
// same as `(index + offset) & 0xFFFFFF`.
```

## Source note 57, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L338)

```text
// Clamp after offsetting.
```

## Source note 58, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L346)

```text
// Convert to float.
```

## Source note 59, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L357)

```text
// Writing the index to X of GPR 0 - either directly if not using indexable
```

## Source note 60, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L358)

```text
// registers, or via a system temporary register.
```

## Source note 61, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L369)

```text
// Check if the closing vertex of a non-indexed line loop is being processed.
```

## Source note 62, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L374)

```text
// Zero the index if processing the closing vertex of a line loop, or do
```

## Source note 63, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L375)

```text
// nothing (replace 0 with 0) if not needed.
```

## Source note 64, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L379)

```text
// Swap the vertex index's endianness.
```

## Source note 65, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L386)

```text
// 8-in-16 or one half of 8-in-32.
```

## Source note 66, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L390)

```text
// Temp = X0Z0.
```

## Source note 67, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L392)

```text
// Index = YZW0.
```

## Source note 68, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L394)

```text
// Index = Y0W0.
```

## Source note 69, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L396)

```text
// Index = YXWZ.
```

## Source note 70, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L401)

```text
// 16-in-32 or another half of 8-in-32.
```

## Source note 71, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L405)

```text
// Temp = ZW00.
```

## Source note 72, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L407)

```text
// Index = ZWXY.
```

## Source note 73, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L413)

```text
// Break register dependency.
```

## Source note 74, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L418)

```text
// Remap the index to the needed range and convert it to floating-point.
```

## Source note 75, line 422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L422)

```text
// Store to indexed GPR 0 in x0[0].
```

## Source note 76, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L431)

```text
// Zero general-purpose registers to prevent crashes when the game
```

## Source note 77, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L432)

```text
// references them after only initializing them conditionally.
```

## Source note 78, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L438)

```text
// Zero the interpolators.
```

## Source note 79, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L444)

```text
// Remember that x# are only accessible via mov load or store - use a
```

## Source note 80, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L445)

```text
// temporary variable if need to do any computations!
```

## Source note 81, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L455)

```text
// Copy the domain location to r0.xyz.
```

## Source note 82, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L456)

```text
// ZYX swizzle according to 415607E1 and 4D5307F2.
```

## Source note 83, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L462)

```text
// Copy the control point indices (already swapped and converted to
```

## Source note 84, line 463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L463)

```text
// float by the host vertex and hull shaders) to r1.xyz.
```

## Source note 85, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L477)

```text
// Copy the domain location to r0.xyz.
```

## Source note 86, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L478)

```text
// ZYX swizzle with r1.y == 0, according to the water shader in
```

## Source note 87, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L479)

```text
// 4D5307ED.
```

## Source note 88, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L485)

```text
// Copy the patch index (already swapped and converted to float by the
```

## Source note 89, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L486)

```text
// host vertex and hull shaders) to r1.x.
```

## Source note 90, line 491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L491)

```text
// Write the swizzle of the barycentric coordinates to r1.y. It
```

## Source note 91, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L492)

```text
// appears that the tessellator offloads the reordering of coordinates
```

## Source note 92, line 493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L493)

```text
// for edges to game shaders.
```

## Source note 93, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L495)

```text
// In 4D5307ED, the water shader multiplies the first control point's
```

## Source note 94, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L496)

```text
// position by r0.z, the second CP's by r0.y, and the third CP's by
```

## Source note 95, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L497)

```text
// r0.x. But before doing that it swizzles r0.xyz the following way
```

## Source note 96, line 498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L498)

```text
// depending on the value in r1.y:
```

## Source note 97, line 499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L499)

```text
// - ZXY for 1.0.
```

## Source note 98, line 500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L500)

```text
// - YZX for 2.0.
```

## Source note 99, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L501)

```text
// - XZY for 4.0.
```

## Source note 100, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L502)

```text
// - YXZ for 5.0.
```

## Source note 101, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L503)

```text
// - ZYX for 6.0.
```

## Source note 102, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L504)

```text
// Possibly, the logic here is that the value itself is the amount of
```

## Source note 103, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L505)

```text
// rotation of the swizzle to the right, and 1 << 2 is set when the
```

## Source note 104, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L506)

```text
// swizzle needs to be flipped before rotating.
```

## Source note 105, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L508)

```text
// Direct3D 12 passes the coordinates in a consistent order, so can
```

## Source note 106, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L509)

```text
// just use the identity swizzle.
```

## Source note 107, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L519)

```text
// Copy the domain location to r0.xy.
```

## Source note 108, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L524)

```text
// Control point indices according the main menu of 58410823, with
```

## Source note 109, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L525)

```text
// `cndeq r2, c255.xxxy, r1.xyzz, r0.zzzz` in the prologue of the
```

## Source note 110, line 526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L526)

```text
// shader, where c255.x is 0, and c255.y is 1.
```

## Source note 111, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L527)

```text
// r0.z for (1 - r0.x) * (1 - r0.y)
```

## Source note 112, line 528

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L528)

```text
// r1.x for r0.x * (1 - r0.y)
```

## Source note 113, line 529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L529)

```text
// r1.y for r0.x * r0.y
```

## Source note 114, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L530)

```text
// r1.z for (1 - r0.x) * r0.y
```

## Source note 115, line 548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L548)

```text
// Copy the domain location to r0.yz.
```

## Source note 116, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L549)

```text
// XY swizzle according to the ground shader in 4D5307F2.
```

## Source note 117, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L554)

```text
// Copy the patch index (already swapped and converted to float by the
```

## Source note 118, line 555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L555)

```text
// host vertex and hull shaders) to r0.x.
```

## Source note 119, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L561)

```text
// Write the swizzle of the UV coordinates to r1.x. It appears that
```

## Source note 120, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L562)

```text
// the tessellator offloads the reordering of coordinates for edges to
```

## Source note 121, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L563)

```text
// game shaders.
```

## Source note 122, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L565)

```text
// In 4D5307F2, if we assume that r0.y is U and r0.z is V, the factors
```

## Source note 123, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L566)

```text
// each control point value is multiplied by are the following:
```

## Source note 124, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L567)

```text
// - (1-u)*(1-v), u*(1-v), (1-u)*v, u*v for 0.0 (identity swizzle).
```

## Source note 125, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L568)

```text
// - u*(1-v), (1-u)*(1-v), u*v, (1-u)*v for 1.0 (YXWZ).
```

## Source note 126, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L569)

```text
// - u*v, (1-u)*v, u*(1-v), (1-u)*(1-v) for 2.0 (WZYX).
```

## Source note 127, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L570)

```text
// - (1-u)*v, u*v, (1-u)*(1-v), u*(1-v) for 3.0 (ZWXY).
```

## Source note 128, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L572)

```text
// Direct3D 12 passes the coordinates in a consistent order, so can
```

## Source note 129, line 573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L573)

```text
// just use the identity swizzle.
```

## Source note 130, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L591)

```text
// Load the EDRAM addresses and the coverage.
```

## Source note 131, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L595)

```text
// Do early 2x2 quad rejection if it's safe.
```

## Source note 132, line 599

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L599)

```text
// Get the derivatives of the screen-space (but not clamped to the
```

## Source note 133, line 600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L600)

```text
// viewport depth bounds yet - this happens after the pixel shader in
```

## Source note 134, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L601)

```text
// Direct3D 11+; also linear within the triangle - thus constant
```

## Source note 135, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L602)

```text
// derivatives along the triangle) Z for calculating per-sample depth
```

## Source note 136, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L603)

```text
// values and the slope-scaled polygon offset to
```

## Source note 137, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L604)

```text
// system_temp_depth_stencil_ before any return statement is possibly
```

## Source note 138, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L605)

```text
// reached.
```

## Source note 139, line 615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L615)

```text
// If not translating anything, we only need the depth.
```

## Source note 140, line 623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L623)

```text
// param_gen_interpolator is already 4 bits, no need for an interpolator count
```

## Source note 141, line 624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L624)

```text
// safety check.
```

## Source note 142, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L631)

```text
// Zero general-purpose registers to prevent crashes when the game
```

## Source note 143, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L632)

```text
// references them after only initializing them conditionally, and copy
```

## Source note 144, line 633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L633)

```text
// interpolants to GPRs.
```

## Source note 145, line 646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L646)

```text
// Write the pixel parameters to the specified interpolator register
```

## Source note 146, line 647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L647)

```text
// (PsParamGen). The negate modified in DXBC flips the sign bit, so it can be
```

## Source note 147, line 648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L648)

```text
// used to write the flags.
```

## Source note 148, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L652)

```text
// X - pixel X .0 in the magnitude, is back-facing in the sign bit.
```

## Source note 149, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L653)

```text
// Y - pixel Y .0 in the magnitude, is point in the sign bit.
```

## Source note 150, line 654

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L654)

```text
// Pixel position.
```

## Source note 151, line 655

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L655)

```text
// Get the XY address of the current host pixel as float (no matter whether
```

## Source note 152, line 656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L656)

```text
// the position is pixel-rate or sample-rate also due to float24 depth
```

## Source note 153, line 657

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L657)

```text
// conversion requirements, it will be rounded the same). Rounding down, and
```

## Source note 154, line 658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L658)

```text
// taking the absolute value (because the sign bit of X stores the
```

## Source note 155, line 659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L659)

```text
// faceness), so in case the host GPU for some reason has quads used for
```

## Source note 156, line 660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L660)

```text
// derivative calculation at odd locations, the left and top edges will have
```

## Source note 157, line 661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L661)

```text
// correct derivative magnitude and LODs.
```

## Source note 158, line 667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L667)

```text
// Revert resolution scale - after truncating, so if the pixel position
```

## Source note 159, line 668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L668)

```text
// is passed to tfetch (assuming the game doesn't round it by itself),
```

## Source note 160, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L669)

```text
// it will be sampled with higher resolution too.
```

## Source note 161, line 675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L675)

```text
// A point - always front-facing (the upper bit of X is 0), not a line
```

## Source note 162, line 676

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L676)

```text
// (the upper bit of Z is 0).
```

## Source note 163, line 677

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L677)

```text
// Take the absolute value of the position and apply the point flag.
```

## Source note 164, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L682)

```text
// ZW - point sprite coordinates.
```

## Source note 165, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L683)

```text
// Saturate to avoid negative point coordinates if the center of the pixel
```

## Source note 166, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L684)

```text
// is not covered, and extrapolation is done.
```

## Source note 167, line 689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L689)

```text
// Take the absolute value of the position and apply the point flag.
```

## Source note 168, line 691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L691)

```text
// Faceness.
```

## Source note 169, line 692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L692)

```text
// Check if faceness applies to the current primitive type.
```

## Source note 170, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L693)

```text
// Using Z as a temporary (not written yet).
```

## Source note 171, line 698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L698)

```text
// Negate modifier flips the sign bit even for 0 - set it to minus for
```

## Source note 172, line 699

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L699)

```text
// backfaces.
```

## Source note 173, line 707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L707)

```text
// No point coordinates.
```

## Source note 174, line 708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L708)

```text
// Z - is line in the sign bit.
```

## Source note 175, line 709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L709)

```text
// W - nothing.
```

## Source note 176, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L716)

```text
// With dynamic register addressing, write the PsParamGen to the GPR.
```

## Source note 177, line 719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L719)

```text
// Release param_gen_temp.
```

## Source note 178, line 725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L725)

```text
// Make sure memexport is done only once for a guest pixel.
```

## Source note 179, line 734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L734)

```text
// Only do memexport for one host pixel in a guest pixel - prefer the
```

## Source note 180, line 735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L735)

```text
// host pixel closer to the center of the guest pixel, but one that's
```

## Source note 181, line 736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L736)

```text
// covered with the half-pixel offset according to the top-left rule (1
```

## Source note 182, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L737)

```text
// for 2x because 0 isn't covered with the half-pixel offset, 1 for 3x
```

## Source note 183, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L738)

```text
// because it's the center and is covered with the half-pixel offset too).
```

## Source note 184, line 755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L755)

```text
// Release memexport_condition_temp.
```

## Source note 185, line 758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L758)

```text
// With sample-rate shading (with float24 conversion), only do memexport
```

## Source note 186, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L759)

```text
// from one sample (as the shader is invoked multiple times for a pixel),
```

## Source note 187, line 760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L760)

```text
// if SV_SampleIndex == firstbit_lo(SV_Coverage). For zero coverage,
```

## Source note 188, line 761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L761)

```text
// firstbit_lo returns 0xFFFFFFFF.
```

## Source note 189, line 770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L770)

```text
// Release memexport_condition_temp.
```

## Source note 190, line 777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L777)

```text
// Set up the input and output registers.
```

## Source note 191, line 783

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L783)

```text
// Interpolators.
```

## Source note 192, line 788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L788)

```text
// Position.
```

## Source note 193, line 791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L791)

```text
// Clip and cull distances.
```

## Source note 194, line 798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L798)

```text
// Point size.
```

## Source note 195, line 805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L805)

```text
// Interpolators.
```

## Source note 196, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L810)

```text
// Point coordinates.
```

## Source note 197, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L815)

```text
// Position.
```

## Source note 198, line 818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L818)

```text
// System inputs.
```

## Source note 199, line 823

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L823)

```text
// Allocate global system temporary registers that may also be used in the
```

## Source note 200, line 824

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L824)

```text
// epilogue.
```

## Source note 201, line 828

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L828)

```text
// Set the point size to a negative value to tell the geometry shader that
```

## Source note 202, line 829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L829)

```text
// it should use the default point size if the vertex shader does not
```

## Source note 203, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L830)

```text
// override it.
```

## Source note 204, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L835)

```text
// Will be initialized unconditionally.
```

## Source note 205, line 841

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L841)

```text
// X holds the guest oDepth - make sure it's always initialized because
```

## Source note 206, line 842

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L842)

```text
// assumptions can't be made about the integrity of the guest code.
```

## Source note 207, line 847

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L847)

```text
// XYZW hold per-sample depth / stencil after the early test - written
```

## Source note 208, line 848

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L848)

```text
// conditionally based on the coverage, ensure registers are
```

## Source note 209, line 849

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L849)

```text
// initialized unconditionally for safety.
```

## Source note 210, line 852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L852)

```text
// XY hold Z gradients, written unconditionally in the beginning.
```

## Source note 211, line 866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L866)

```text
// Allocate temporary registers for memexport.
```

## Source note 212, line 870

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L870)

```text
// Initialize the memexport conditional to whether the shared memory is
```

## Source note 213, line 871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L871)

```text
// currently bound as UAV (to 0 or UINT32_MAX). It can be made narrower
```

## Source note 214, line 872

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L872)

```text
// later.
```

## Source note 215, line 886

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L886)

```text
// Allocate system temporary variables for the translated code. Since access
```

## Source note 216, line 887

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L887)

```text
// depends on the guest code (thus no guarantees), initialize everything
```

## Source note 217, line 888

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L888)

```text
// now (except for pv, it's an internal temporary variable, not accessible
```

## Source note 218, line 889

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L889)

```text
// by the guest).
```

## Source note 219, line 898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L898)

```text
// Write stage-specific prologue.
```

## Source note 220, line 905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L905)

```text
// If not translating anything, don't start the main loop.
```

## Source note 221, line 910

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L910)

```text
// Start the main loop (for jumping to labels by setting pc and continuing).
```

## Source note 222, line 912

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L912)

```text
// Switch and the first label (pc == 0).
```

## Source note 223, line 928

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L928)

```text
// Check if the shader already returns W, not 1/W, and if it doesn't, turn 1/W
```

## Source note 224, line 929

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L929)

```text
// into W. Using div rather than relaxed-precision rcp for safety.
```

## Source note 225, line 936

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L936)

```text
// Check if the shader returns XY/W rather than XY, and if it does, revert
```

## Source note 226, line 937

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L937)

```text
// that.
```

## Source note 227, line 944

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L944)

```text
// Check if the shader returns Z/W rather than Z, and if it does, revert that.
```

## Source note 228, line 956

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L956)

```text
// Clip against user clip planes.
```

## Source note 229, line 971

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L971)

```text
// Apply scale for guest to host viewport and clip space conversion. Also, if
```

## Source note 230, line 972

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L972)

```text
// the vertex shader is multipass, the NDC scale constant can be used to set
```

## Source note 231, line 973

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L973)

```text
// position to NaN to kill all primitives.
```

## Source note 232, line 978

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L978)

```text
// Apply offset (multiplied by W) used for the same purposes.
```

## Source note 233, line 985

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L985)

```text
// Kill the primitive if needed - check if the shader wants to kill (bits
```

## Source note 234, line 986

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L986)

```text
// 0:30 of the vertex kill register are not zero - using `and`, not abs or
```

## Source note 235, line 987

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L987)

```text
// especially 0.0f comparison, to avoid potential denormal flushing).
```

## Source note 236, line 996

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L996)

```text
// AND operator - write an SV_CullDistance.
```

## Source note 237, line 1007

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1007)

```text
// OR operator - set the position to NaN.
```

## Source note 238, line 1015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1015)

```text
// Write the position to the output.
```

## Source note 239, line 1018

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1018)

```text
// Write the point size.
```

## Source note 240, line 1024

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1024)

```text
// Release temp.
```

## Source note 241, line 1030

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1030)

```text
// Close the last exec, there's nothing to merge it with anymore, and we're
```

## Source note 242, line 1031

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1031)

```text
// closing upper-level flow control blocks.
```

## Source note 243, line 1033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1033)

```text
// Close the last label and the switch.
```

## Source note 244, line 1040

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1040)

```text
// End the main loop.
```

## Source note 245, line 1044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1044)

```text
// Release the following system temporary values so epilogue can reuse them:
```

## Source note 246, line 1045

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1045)

```text
// - system_temp_result_.
```

## Source note 247, line 1046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1046)

```text
// - system_temp_ps_pc_p0_a0_.
```

## Source note 248, line 1047

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1047)

```text
// - system_temp_aL_.
```

## Source note 249, line 1048

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1048)

```text
// - system_temp_loop_count_.
```

## Source note 250, line 1049

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1049)

```text
// - system_temp_grad_h_lod_.
```

## Source note 251, line 1050

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1050)

```text
// - system_temp_grad_v_vfetch_address_.
```

## Source note 252, line 1056

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1056)

```text
// Write data for the last memexport.
```

## Source note 253, line 1059

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1059)

```text
// Release memexport temporary registers:
```

## Source note 254, line 1060

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1060)

```text
// - system_temp_memexport_enabled_and_eM_written_.
```

## Source note 255, line 1061

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1061)

```text
// - system_temp_memexport_address_.
```

## Source note 256, line 1062

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1062)

```text
// - system_temps_memexport_data_.
```

## Source note 257, line 1066

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1066)

```text
// Write stage-specific epilogue.
```

## Source note 258, line 1073

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1073)

```text
// Return from `main`.
```

## Source note 259, line 1077

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1077)

```text
// Release system_temp_position_ and
```

## Source note 260, line 1078

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1078)

```text
// system_temp_point_size_edge_flag_kill_vertex_.
```

## Source note 261, line 1081

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1081)

```text
// Release system_temps_color_.
```

## Source note 262, line 1089

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1089)

```text
// Release system_temp_depth_stencil_.
```

## Source note 263, line 1093

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1093)

```text
// Release system_temp_rov_params_.
```

## Source note 264, line 1100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1100)

```text
// Because of shader_object_.resize(), pointers can't be kept persistently
```

## Source note 265, line 1101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1101)

```text
// here! Resizing also zeroes the memory.
```

## Source note 266, line 1103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1103)

```text
// Write the code epilogue.
```

## Source note 267, line 1108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1108)

```text
// 6 or 7 blobs - RDEF, ISGN, optionally PCSG, OSGN, SHEX, SFI0, STAT.
```

## Source note 268, line 1109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1109)

```text
// Whether SFI0 is needed at this point is not known, always writing it.
```

## Source note 269, line 1111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1111)

```text
// Allocate space for the header and the blob offsets.
```

## Source note 270, line 1118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1118)

```text
// Resource definition.
```

## Source note 271, line 1131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1131)

```text
// Input signature.
```

## Source note 272, line 1144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1144)

```text
// Patch constant signature.
```

## Source note 273, line 1159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1159)

```text
// Output signature.
```

## Source note 274, line 1172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1172)

```text
// Shader program.
```

## Source note 275, line 1185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1185)

```text
// Shader feature info.
```

## Source note 276, line 1200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1200)

```text
// Statistics.
```

## Source note 277, line 1215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1215)

```text
// Header.
```

## Source note 278, line 1246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1246)

```text
// For a stable hash.
```

## Source note 279, line 1276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1276)

```text
// Trim leading spaces and trailing new line.
```

## Source note 280, line 1318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1318)

```text
// Load x#[#] to r# because x#[#] can be used only with mov.
```

## Source note 281, line 1363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1363)

```text
// Swizzle, skipping unneeded components similar to how FXC skips components,
```

## Source note 282, line 1364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1364)

```text
// by replacing them with the leftmost used one.
```

## Source note 283, line 1384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1384)

```text
// Get the destination address and type.
```

## Source note 284, line 1437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1437)

```text
// Mark that the eM# has been written to and needs to be exported.
```

## Source note 285, line 1448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1448)

```text
// For ROV output, mark that the color has been written to.
```

## Source note 286, line 1449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1449)

```text
// According to:
```

## Source note 287, line 1450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1450)

```text
// https://docs.microsoft.com/en-us/windows/desktop/direct3dhlsl/dx9-graphics-reference-asm-ps-registers-output-color
```

## Source note 288, line 1451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1451)

```text
// if a color target hasn't been written to - including due to flow
```

## Source note 289, line 1452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1452)

```text
// control - the render target must not be modified (the unwritten
```

## Source note 290, line 1453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1453)

```text
// components of a written target are undefined, not sure if this
```

## Source note 291, line 1454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1454)

```text
// behavior is respected on the real GPU, but the ROV code currently
```

## Source note 292, line 1455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1455)

```text
// doesn't preserve unmodified components).
```

## Source note 293, line 1462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1462)

```text
// Writes X to scalar oDepth or to X of system_temp_depth_stencil_, no
```

## Source note 294, line 1463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1463)

```text
// additional swizzling needed.
```

## Source note 295, line 1471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1471)

```text
// Depth outside [0, 1] is not safe for use with the ROV code, with
```

## Source note 296, line 1472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1472)

```text
// 20e4-as-32 conversion and with 0...1 to 0...0.5 float24 remapping.
```

## Source note 297, line 1473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1473)

```text
// Though 20e4 float depth can store values between 1 and 2, it's a very
```

## Source note 298, line 1474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1474)

```text
// unusual case. Direct3D 10+ SV_Depth, however, can accept any values,
```

## Source note 299, line 1475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1475)

```text
// including specials, when the depth buffer is floating-point.
```

## Source note 300, line 1483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1483)

```text
// Write.
```

## Source note 301, line 1510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1510)

```text
// Make the point size non-negative as negative is used to indicate that the
```

## Source note 302, line 1511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1511)

```text
// default size must be used, and also clamp it to the bounds the way the R400
```

## Source note 303, line 1512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1512)

```text
// (Adreno 200, to be more precise) hardware clamps it (functionally like a
```

## Source note 304, line 1513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1513)

```text
// signed 32-bit integer, -NaN and -Infinity...-0 to the minimum, +NaN to the
```

## Source note 305, line 1514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1514)

```text
// maximum).
```

## Source note 306, line 1532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1532)

```text
// Check if we can merge the new exec with the previous one, or the jump with
```

## Source note 307, line 1533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1533)

```text
// the previous exec. The instruction-level predicate check is also merged in
```

## Source note 308, line 1534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1534)

```text
// this case.
```

## Source note 309, line 1537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1537)

```text
// Can merge conditional with conditional, as long as the bool constant and
```

## Source note 310, line 1538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1538)

```text
// the expected values are the same.
```

## Source note 311, line 1544

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1544)

```text
// Can merge predicated with predicated if the conditions are the same and
```

## Source note 312, line 1545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1545)

```text
// the previous exec hasn't modified the predicate register.
```

## Source note 313, line 1551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1551)

```text
// Can merge unconditional with unconditional.
```

## Source note 314, line 1558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1558)

```text
// Emit the disassembly for the exec/jump merged with the previous one.
```

## Source note 315, line 1565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1565)

```text
// Emit the disassembly for the new exec/jump.
```

## Source note 316, line 1570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1570)

```text
// Check the bool constant value.
```

## Source note 317, line 1579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1579)

```text
// Open the new `if`.
```

## Source note 318, line 1581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1581)

```text
// Release bool_constant_test_temp.
```

## Source note 319, line 1593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1593)

```text
// Within the exec - instruction-level predicate check.
```

## Source note 320, line 1595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1595)

```text
// Exec level.
```

## Source note 321, line 1601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1601)

```text
// Nothing relies on the predicate value being unchanged now.
```

## Source note 322, line 1615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1615)

```text
// Already in the needed instruction-level `if`.
```

## Source note 323, line 1622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1622)

```text
// Emit the disassembly before opening (or not opening) the new conditional.
```

## Source note 324, line 1625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1625)

```text
// If the instruction predicate condition is the same as the exec predicate
```

## Source note 325, line 1626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1626)

```text
// condition, no need to open a check. However, if there was a `setp` prior
```

## Source note 326, line 1627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1627)

```text
// to this instruction, the predicate value now may be different than it was
```

## Source note 327, line 1628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1628)

```text
// in the beginning of the exec.
```

## Source note 328, line 1653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1653)

```text
// 0 already added in the beginning.
```

## Source note 329, line 1656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1656)

```text
// Close flow control on the deeper levels below - prevent attempts to merge
```

## Source note 330, line 1657

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1657)

```text
// execs across labels.
```

## Source note 331, line 1660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1660)

```text
// Fallthrough to the label from the previous one on the next iteration if
```

## Source note 332, line 1661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1661)

```text
// no `continue` was done. Can't simply fallthrough because in DXBC, a
```

## Source note 333, line 1662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1662)

```text
// non-empty switch case must end with a break.
```

## Source note 334, line 1664

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1664)

```text
// Close the previous label.
```

## Source note 335, line 1666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1666)

```text
// Go to the next label.
```

## Source note 336, line 1669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1669)

```text
// Close the previous label.
```

## Source note 337, line 1671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1671)

```text
// if (pc <= cf_index)
```

## Source note 338, line 1676

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1676)

```text
// Release test_temp.
```

## Source note 339, line 1691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1691)

```text
// Break out of the main loop.
```

## Source note 340, line 1694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1694)

```text
// Write an invalid value to pc.
```

## Source note 341, line 1696

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1696)

```text
// Go to the next iteration, where switch cases won't be reached.
```

## Source note 342, line 1705

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1705)

```text
// loop il<idx>, L<idx> - loop with loop data il<idx>, end @ L<idx>
```

## Source note 343, line 1707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1707)

```text
// Loop control is outside execs - actually close the last exec.
```

## Source note 344, line 1716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1716)

```text
// Count (unsigned) in bits 0:7 of the loop constant, initial aL (unsigned) in
```

## Source note 345, line 1717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1717)

```text
// 8:15. Starting from vector 2 because of bool constants.
```

## Source note 346, line 1730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1730)

```text
// Skip the loop without pushing if the count is zero from the beginning.
```

## Source note 347, line 1735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1735)

```text
// Push the count to the loop count stack - move XYZ to YZW and set X to the
```

## Source note 348, line 1736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1736)

```text
// new loop count.
```

## Source note 349, line 1742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1742)

```text
// Release loop_count_temp.
```

## Source note 350, line 1746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1746)

```text
// Push aL - keep the same value as in the previous loop if repeating, or the
```

## Source note 351, line 1747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1747)

```text
// new one otherwise.
```

## Source note 352, line 1757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1757)

```text
// endloop il<idx>, L<idx> - end loop w/ data il<idx>, head @ L<idx>
```

## Source note 353, line 1759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1759)

```text
// Loop control is outside execs - actually close the last exec.
```

## Source note 354, line 1768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1768)

```text
// Subtract 1 from the loop counter.
```

## Source note 355, line 1773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1773)

```text
// if (loop_count.x == 0 || [!]p0)
```

## Source note 356, line 1776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1776)

```text
// If p0 is non-zero, set the test value to 0 (since if_z is used,
```

## Source note 357, line 1777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1777)

```text
// otherwise check if the loop counter is zero).
```

## Source note 358, line 1782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1782)

```text
// If p0 is zero, set the test value to 0 (since if_z is used, otherwise
```

## Source note 359, line 1783

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1783)

```text
// check if the loop counter is zero).
```

## Source note 360, line 1789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1789)

```text
// Release break_case_temp.
```

## Source note 361, line 1792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1792)

```text
// if (loop_count.x == 0)
```

## Source note 362, line 1796

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1796)

```text
// Break case.
```

## Source note 363, line 1797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1797)

```text
// Pop the current loop off the loop counter and the relative address
```

## Source note 364, line 1798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1798)

```text
// stacks - move YZW to XYZ and set W to 0.
```

## Source note 365, line 1804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1804)

```text
// Now going to fall through to the next exec (no need to jump).
```

## Source note 366, line 1808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1808)

```text
// Continue case.
```

## Source note 367, line 1810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1810)

```text
// Extract the value to add to aL (signed, in bits 16:23 of the loop
```

## Source note 368, line 1811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1811)

```text
// constant). Starting from vector 2 because of bool constants.
```

## Source note 369, line 1820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1820)

```text
// Add the needed value to aL.
```

## Source note 370, line 1824

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1824)

```text
// Release aL_add_temp.
```

## Source note 371, line 1826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1826)

```text
// Jump back to the beginning of the loop body.
```

## Source note 372, line 1838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1838)

```text
// Treat like exec, merge with execs if possible, since it's an if too.
```

## Source note 373, line 1849

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1849)

```text
// UpdateExecConditionalsAndEmitDisassembly may not necessarily close the
```

## Source note 374, line 1850

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1850)

```text
// instruction-level predicate check (it's not necessary if the execs are
```

## Source note 375, line 1851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1851)

```text
// merged), but here the instruction itself is on the flow control level, so
```

## Source note 376, line 1852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1852)

```text
// the predicate check is on the flow control level too.
```

## Source note 377, line 1874

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1874)

```text
// Reset which eM# elements have been written.
```

## Source note 378, line 1877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1877)

```text
// Break dependencies from the previous memexport.
```

## Source note 379, line 1887

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1887)

```text
// Initialize eA to an invalid address.
```

## Source note 380, line 1897

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1897)

```text
// kFloat2
```

## Source note 381, line 1900

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1900)

```text
// kFloat3
```

## Source note 382, line 1903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1903)

```text
// kFloat4
```

## Source note 383, line 1909

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1909)

```text
// kUint2
```

## Source note 384, line 1912

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1912)

```text
// kUint4
```

## Source note 385, line 1915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1915)

```text
// kFloat4Array4
```

## Source note 386, line 1918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1918)

```text
// kFloat4Array6
```

## Source note 387, line 1921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1921)

```text
// kFloat4ConstantArray - float constants - size written dynamically.
```

## Source note 388, line 1924

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1924)

```text
// kUint4Array2
```

## Source note 389, line 1927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1927)

```text
// kUint4Array8
```

## Source note 390, line 1930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1930)

```text
// kUint4Array48
```

## Source note 391, line 1933

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1933)

```text
// kUint4DescriptorIndexArray - bindless descriptor indices - size
```

## Source note 392, line 1935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1935)

```text
// dynamically.
```

## Source note 393, line 1995

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1995)

```text
// Because of shader_object_.resize(), pointers can't be kept persistently
```

## Source note 394, line 1996

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L1996)

```text
// here! Resizing also zeroes the memory.
```

## Source note 395, line 2004

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2004)

```text
// Allocate space for the header, will fill when all pointers and counts are
```

## Source note 396, line 2005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2005)

```text
// known.
```

## Source note 397, line 2007

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2007)

```text
// Generator name.
```

## Source note 398, line 2011

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2011)

```text
// Constant types
```

## Source note 399, line 2014

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2014)

```text
// Type names.
```

## Source note 400, line 2020

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2020)

```text
// Array - use the name of the element type.
```

## Source note 401, line 2028

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2028)

```text
// Types.
```

## Source note 402, line 2044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2044)

```text
// Declaring a 0-sized array may not be safe, so write something valid
```

## Source note 403, line 2045

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2045)

```text
// even if they aren't used.
```

## Source note 404, line 2063

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2063)

```text
// Names.
```

## Source note 405, line 2092

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2092)

```text
// System constants.
```

## Source note 406, line 2118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2118)

```text
// Float constants.
```

## Source note 407, line 2135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2135)

```text
// Bool and loop constants.
```

## Source note 408, line 2167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2167)

```text
// Fetch constants.
```

## Source note 409, line 2183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2183)

```text
// Bindless description indices.
```

## Source note 410, line 2203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2203)

```text
// Constant buffers
```

## Source note 411, line 2206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2206)

```text
// Names.
```

## Source note 412, line 2229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2229)

```text
// All the constant buffers, sorted by their binding index.
```

## Source note 413, line 2280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2280)

```text
// Bindings, in s#, t#, u#, cb# order
```

## Source note 414, line 2283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2283)

```text
// Names, except for constant buffers because their names are written already.
```

## Source note 415, line 2337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2337)

```text
// Samplers.
```

## Source note 416, line 2346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2346)

```text
// Bindless sampler heap.
```

## Source note 417, line 2350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2350)

```text
// Bindful samplers.
```

## Source note 418, line 2365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2365)

```text
// Shader resource views, sorted by binding index.
```

## Source note 419, line 2376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2376)

```text
// Shared memory (when memexport isn't used in the pipeline).
```

## Source note 420, line 2385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2385)

```text
// Bindful texture or bindless textures.
```

## Source note 421, line 2391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2391)

```text
// Bindless texture heap.
```

## Source note 422, line 2407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2407)

```text
// Bindful texture.
```

## Source note 423, line 2432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2432)

```text
// Unordered access views, sorted by binding index.
```

## Source note 424, line 2444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2444)

```text
// Shared memory (when memexport is used in the pipeline).
```

## Source note 425, line 2451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2451)

```text
// EDRAM R32_UINT buffer.
```

## Source note 426, line 2459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2459)

```text
// ZPD counter slots, raw.
```

## Source note 427, line 2471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2471)

```text
// Constant buffers.
```

## Source note 428, line 2482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2482)

```text
// Like `cbuffer`, don't need `ConstantBuffer<T>` properties.
```

## Source note 429, line 2533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2533)

```text
// Generator name placed directly after the header.
```

## Source note 430, line 2541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2541)

```text
// Because of shader_object_.resize(), pointers can't be kept persistently
```

## Source note 431, line 2542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2542)

```text
// here! Resizing also zeroes the memory.
```

## Source note 432, line 2544

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2544)

```text
// Reserve space for the header.
```

## Source note 433, line 2550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2550)

```text
// Unswapped vertex index (SV_VertexID).
```

## Source note 434, line 2564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2564)

```text
// Semantic names.
```

## Source note 435, line 2573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2573)

```text
// Control point indices, byte-swapped, biased according to the base index
```

## Source note 436, line 2574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2574)

```text
// and converted to float by the host vertex and hull shaders
```

## Source note 437, line 2575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2575)

```text
// (XEVERTEXID).
```

## Source note 438, line 2588

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2588)

```text
// Semantic names.
```

## Source note 439, line 2597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2597)

```text
// Intepolators (TEXCOORD#).
```

## Source note 440, line 2621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2621)

```text
// Point coordinates for PsParamGen (XESPRITETEXCOORD).
```

## Source note 441, line 2636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2636)

```text
// Pixel position (SV_Position).
```

## Source note 442, line 2650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2650)

```text
// Is front face (SV_IsFrontFace).
```

## Source note 443, line 2664

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2664)

```text
// Sample index (SV_SampleIndex) for safe memexport and ZPD Total counting
```

## Source note 444, line 2665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2665)

```text
// with sample-rate shading.
```

## Source note 445, line 2683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2683)

```text
// Semantic names.
```

## Source note 446, line 2721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2721)

```text
// Header.
```

## Source note 447, line 2731

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2731)

```text
// Because of shader_object_.resize(), pointers can't be kept persistently
```

## Source note 448, line 2732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2732)

```text
// here! Resizing also zeroes the memory.
```

## Source note 449, line 2734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2734)

```text
// Reserve space for the header.
```

## Source note 450, line 2739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2739)

```text
// FXC always compiles with SV_TessFactor and SV_InsideTessFactor input, so
```

## Source note 451, line 2740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2740)

```text
// this is required even if not referenced (HS and DS have very strict
```

## Source note 452, line 2741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2741)

```text
// linkage, by the way, everything that HS outputs must be listed in DS
```

## Source note 453, line 2742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2742)

```text
// inputs).
```

## Source note 454, line 2770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2770)

```text
// Edge tessellation factors (SV_TessFactor).
```

## Source note 455, line 2782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2782)

```text
// Not using any of these, just assigning consecutive registers.
```

## Source note 456, line 2788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2788)

```text
// Inside tessellation factors (SV_InsideTessFactor).
```

## Source note 457, line 2800

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2800)

```text
// Not using any of these, just assigning consecutive registers.
```

## Source note 458, line 2806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2806)

```text
// Semantic names.
```

## Source note 459, line 2825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2825)

```text
// Header.
```

## Source note 460, line 2834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2834)

```text
// Because of shader_object_.resize(), pointers can't be kept persistently
```

## Source note 461, line 2835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2835)

```text
// here! Resizing also zeroes the memory.
```

## Source note 462, line 2837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2837)

```text
// Reserve space for the header.
```

## Source note 463, line 2845

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2845)

```text
// Intepolators (TEXCOORD#).
```

## Source note 464, line 2862

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2862)

```text
// Position (SV_Position).
```

## Source note 465, line 2875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2875)

```text
// Clip (SV_ClipDistance) and cull (SV_CullDistance) distances.
```

## Source note 466, line 2923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2923)

```text
// Point size (XEPSIZE). Always used because reset to -1.
```

## Source note 467, line 2938

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2938)

```text
// Semantic names.
```

## Source note 468, line 2989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L2989)

```text
// Color render targets (SV_Target#).
```

## Source note 469, line 3012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3012)

```text
// Coverage output for alpha to mask (SV_Coverage).
```

## Source note 470, line 3026

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3026)

```text
// Depth (SV_Depth or SV_DepthLessEqual).
```

## Source note 471, line 3040

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3040)

```text
// Semantic names.
```

## Source note 472, line 3080

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3080)

```text
// Header.
```

## Source note 473, line 3101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3101)

```text
// Reserve space for the length token.
```

## Source note 474, line 3135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3135)

```text
// Don't allow refactoring when converting to native code to maintain position
```

## Source note 475, line 3136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3136)

```text
// invariance (needed even in pixel shaders for oDepth invariance).
```

## Source note 476, line 3141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3141)

```text
// Constant buffers, from most frequenly accessed to least frequently accessed
```

## Source note 477, line 3142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3142)

```text
// (the order is a hint to the driver according to the DXBC header).
```

## Source note 478, line 3181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3181)

```text
// Samplers.
```

## Source note 479, line 3184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3184)

```text
// Bindless sampler heap.
```

## Source note 480, line 3187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3187)

```text
// Bindful samplers.
```

## Source note 481, line 3195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3195)

```text
// Shader resource views, sorted by binding index.
```

## Source note 482, line 3198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3198)

```text
// Shared memory ByteAddressBuffer.
```

## Source note 483, line 3204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3204)

```text
// Texture or texture heap.
```

## Source note 484, line 3209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3209)

```text
// Bindless texture heap.
```

## Source note 485, line 3224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3224)

```text
// Bindful texture.
```

## Source note 486, line 3253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3253)

```text
// Unordered access views, sorted by binding index.
```

## Source note 487, line 3256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3256)

```text
// Shared memory RWByteAddressBuffer.
```

## Source note 488, line 3264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3264)

```text
// EDRAM buffer R32_UINT rasterizer-ordered view.
```

## Source note 489, line 3272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3272)

```text
// ZPD counter slots, raw, added to atomically.
```

## Source note 490, line 3281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3281)

```text
// Inputs and outputs.
```

## Source note 491, line 3285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3285)

```text
// Domain location input.
```

## Source note 492, line 3294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3294)

```text
// Unswapped vertex index input (only X component).
```

## Source note 493, line 3298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3298)

```text
// Interpolator output.
```

## Source note 494, line 3303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3303)

```text
// Position output.
```

## Source note 495, line 3305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3305)

```text
// Clip and cull distance outputs.
```

## Source note 496, line 3327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3327)

```text
// Point size output.
```

## Source note 497, line 3334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3334)

```text
// Interpolator input.
```

## Source note 498, line 3351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3351)

```text
// Point coordinates input.
```

## Source note 499, line 3356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3356)

```text
// Position input (XY needed for ps_param_gen, Z needed for non-ROV
```

## Source note 500, line 3357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3357)

```text
// float24 conversion; the ROV depth code calculates the depth the from
```

## Source note 501, line 3358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3358)

```text
// clip space Z and W with pull-mode per-sample interpolation instead).
```

## Source note 502, line 3359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3359)

```text
// At the cost of possibility of MSAA with pixel-rate shading, need
```

## Source note 503, line 3360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3360)

```text
// per-sample depth - otherwise intersections cannot be antialiased, and
```

## Source note 504, line 3361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3361)

```text
// with SV_DepthLessEqual, per-sample (or centroid, but this isn't
```

## Source note 505, line 3362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3362)

```text
// applicable here) position is mandatory. However, with depth output, on
```

## Source note 506, line 3363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3363)

```text
// the guest, there's only one depth value for the whole pixel.
```

## Source note 507, line 3373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3373)

```text
// Sample-rate shading can't be done with UAV-only rendering (sample-rate
```

## Source note 508, line 3374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3374)

```text
// shading is only needed for float24 depth conversion when using a float32
```

## Source note 509, line 3375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3375)

```text
// host depth buffer).
```

## Source note 510, line 3380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3380)

```text
// Is front face, sample index.
```

## Source note 511, line 3386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3386)

```text
// Sample coverage input.
```

## Source note 512, line 3390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3390)

```text
// Color output.
```

## Source note 513, line 3397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3397)

```text
// Coverage output for alpha to mask.
```

## Source note 514, line 3401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3401)

```text
// Depth output.
```

## Source note 515, line 3413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3413)

```text
// Temporary registers - guest general-purpose registers if not using dynamic
```

## Source note 516, line 3414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3414)

```text
// indexing and Xenia internal registers.
```

## Source note 517, line 3422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3422)

```text
// General-purpose registers if using dynamic indexing (x0).
```

## Source note 518, line 3428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3428)

```text
// Write the translated shader code.
```

## Source note 519, line 3436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator.cpp#L3436)

```text
// Write the length.
```
