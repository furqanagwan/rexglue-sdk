# Spirv translator: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/spirv_translator.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L143)

```text
// The sample count lives in depth_stencil_mode's bits on the FSI path.
```

## Source note 2, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L156)

```text
// Vertex shader inputs.
```

## Source note 3, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L158)

```text
// Tessellation evaluation shader inputs.
```

## Source note 4, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L161)

```text
// Pixel shader inputs.
```

## Source note 5, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L166)

```text
// Barycentric interpolation inputs.
```

## Source note 6, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L268)

```text
// Past the last instruction the snapshot is the register's final value.
```

## Source note 7, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L296)

```text
// The FSI path writes only the colors the shader marked as written.
```

## Source note 8, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L380)

```text
// Common uniform buffer - system constants.
```

## Source note 9, line 490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L490)

```text
// Common uniform buffer - float constants.
```

## Source note 10, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L496)

```text
// Currently (as of October 24, 2020) makeArrayType only uses the stride
```

## Source note 11, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L497)

```text
// to check if deduplication can be done - the array stride decoration
```

## Source note 12, line 498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L498)

```text
// needs to be applied explicitly.
```

## Source note 13, line 518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L518)

```text
// Common uniform buffer - bool and loop constants.
```

## Source note 14, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L519)

```text
// Uniform buffers must have std140 packing, so using arrays of 4-component
```

## Source note 15, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L520)

```text
// vectors instead of scalar arrays because the latter would have padding to
```

## Source note 16, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L521)

```text
// 16 bytes in each element.
```

## Source note 17, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L523)

```text
// 256 bool constants.
```

## Source note 18, line 528

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L528)

```text
// 32 loop constants.
```

## Source note 19, line 552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L552)

```text
// Common uniform buffer - fetch constants (32 x 6 uints packed in std140 as
```

## Source note 20, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L553)

```text
// 4-component vectors).
```

## Source note 21, line 574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L574)

```text
// Common storage buffers - shared memory uint[], each 128 MB or larger,
```

## Source note 22, line 575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L575)

```text
// depending on what's possible on the device.
```

## Source note 23, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L578)

```text
// Storage buffers have std430 packing, no padding to 4-component vectors.
```

## Source note 24, line 614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L614)

```text
// Begin the main function.
```

## Source note 25, line 622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L622)

```text
// Load the flags system constant since it may be used in many places.
```

## Source note 26, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L631)

```text
// Begin ucode translation. Initialize everything, even without defined
```

## Source note 27, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L632)

```text
// defaults, for safety.
```

## Source note 28, line 664

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L664)

```text
// Pass stride -1 to force creation of a new type without decoration
```

## Source note 29, line 665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L665)

```text
// to avoid reusing types with ArrayStride decorations
```

## Source note 30, line 696

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L696)

```text
// Write the execution model-specific prologue with access to variables in the
```

## Source note 31, line 697

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L697)

```text
// main function.
```

## Source note 32, line 712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L712)

```text
// Run the translated guest vertex shader 3 times for the rectangle
```

## Source note 33, line 713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L713)

```text
// vertices, and store the results to build the triangle strip vertex in
```

## Source note 34, line 714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L714)

```text
// CompleteVertexOrTessEvalShaderInMain. Only reachable on hosts without
```

## Source note 35, line 715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L715)

```text
// geometry shaders (currently Metal; MoltenVK / GS-less Vulkan also land
```

## Source note 36, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L716)

```text
// here), selected by PrimitiveProcessor via kRectangleListAsTriangleStrip.
```

## Source note 37, line 753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L753)

```text
// Open the main loop.
```

## Source note 38, line 757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L757)

```text
// Added later because the body has nested control flow, but according to the
```

## Source note 39, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L759)

```text
// "The order of blocks in a function must satisfy the rule that blocks appear
```

## Source note 40, line 760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L760)

```text
//  before all blocks they dominate."
```

## Source note 41, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L765)

```text
// If no jumps, don't create a switch, but still create a loop so exece can
```

## Source note 42, line 766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L766)

```text
// break.
```

## Source note 43, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L769)

```text
// Main loop header - based on whether it's the first iteration (entered from
```

## Source note 44, line 770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L770)

```text
// the function or from the continuation), choose the program counter.
```

## Source note 45, line 774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L774)

```text
// OpPhi must be the first in the block.
```

## Source note 46, line 788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L788)

```text
// Main loop body.
```

## Source note 47, line 791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L791)

```text
// Create the program counter switch with cases for every label and for
```

## Source note 48, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L792)

```text
// label 0.
```

## Source note 49, line 799

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L799)

```text
// The default case (the merge here) must have the header as a predecessor.
```

## Source note 50, line 801

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L801)

```text
// The instruction will be inserted later, when all cases are filled.
```

## Source note 51, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L802)

```text
// Insert and enter case 0.
```

## Source note 52, line 806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L806)

```text
// Every switch case must have the OpSelectionMerge/OpSwitch block as a
```

## Source note 53, line 807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L807)

```text
// predecessor.
```

## Source note 54, line 816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L816)

```text
// Close flow control within the last switch case.
```

## Source note 55, line 819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L819)

```text
// After the final exec (if it happened to be not exece, which would already
```

## Source note 56, line 820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L820)

```text
// have a break branch), break from the switch if it exists, or from the
```

## Source note 57, line 821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L821)

```text
// loop it doesn't.
```

## Source note 58, line 826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L826)

```text
// Insert the switch instruction with all cases added as operands.
```

## Source note 59, line 829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L829)

```text
// Build the main switch merge, breaking out of the loop after falling
```

## Source note 60, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L830)

```text
// through the end or breaking from exece (only continuing if a jump -
```

## Source note 61, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L831)

```text
// from a guest loop or from jmp/call - was made).
```

## Source note 62, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L837)

```text
// Main loop continuation - choose the program counter based on the path
```

## Source note 63, line 838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L838)

```text
// taken (-1 if not from a jump as a safe fallback, which would result in
```

## Source note 64, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L839)

```text
// not hitting any switch case and reaching the final break in the body).
```

## Source note 65, line 843

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L843)

```text
// OpPhi, if added, must be the first in the block.
```

## Source note 66, line 844

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L844)

```text
// If labels were added, but not jumps (for example, due to the call
```

## Source note 67, line 845

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L845)

```text
// instruction not being implemented as of October 18, 2020), send an
```

## Source note 68, line 846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L846)

```text
// impossible program counter value (-1) to the OpPhi at the next
```

## Source note 69, line 847

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L847)

```text
// iteration.
```

## Source note 70, line 861

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L861)

```text
// Add the main loop merge block and go back to the function.
```

## Source note 71, line 868

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L868)

```text
// Store the current guest vertex shader outputs for this rectangle
```

## Source note 72, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L869)

```text
// vertex iteration.
```

## Source note 73, line 897

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L897)

```text
// Finalize memexport for this guest vertex shader execution.
```

## Source note 74, line 905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L905)

```text
// Rectangle vertex loop continuation.
```

## Source note 75, line 916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L916)

```text
// Rectangle vertex loop merge.
```

## Source note 76, line 922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L922)

```text
// Write data for the last memexport.
```

## Source note 77, line 933

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L933)

```text
// End the main function.
```

## Source note 78, line 936

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L936)

```text
// Make the main function the entry point.
```

## Source note 79, line 944

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L944)

```text
// FSI handles depth manually.
```

## Source note 80, line 949

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L949)

```text
// Truncating float24 conversion of the rasterizer's own depth rounds
```

## Source note 81, line 950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L950)

```text
// towards zero, so the output is always <= the original - announce that
```

## Source note 82, line 951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L951)

```text
// to keep coarse early-Z culling possible. Matches SV_DepthLessEqual in
```

## Source note 83, line 952

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L952)

```text
// the DXBC backend.
```

## Source note 84, line 960

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L960)

```text
// Accessing per-sample values, so interlocking just when there's common
```

## Source note 85, line 961

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L961)

```text
// coverage is enough if the device exposes that.
```

## Source note 86, line 974

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L974)

```text
// Set tessellation execution modes based on the domain shader type.
```

## Source note 87, line 977

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L977)

```text
// Tessellation domain (triangles vs quads).
```

## Source note 88, line 995

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L995)

```text
// Tessellation spacing. In SPIR-V the spacing is part of the domain
```

## Source note 89, line 996

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L996)

```text
// shader rather than the hull shader. Match the Direct3D 12 hull shader
```

## Source note 90, line 997

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L997)

```text
// partitioning - integer (equal) for discrete, fractional even for
```

## Source note 91, line 998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L998)

```text
// continuous and adaptive.
```

## Source note 92, line 1003

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1003)

```text
// Vertex ordering. Xenia does not flip the clip space Y on Vulkan
```

## Source note 93, line 1004

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1004)

```text
// (origin_bottom_left is false, so ndc_scale.y keeps the guest sign), so
```

## Source note 94, line 1005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1005)

```text
// the tessellator must wind the same way as the Direct3D 12 hull shaders,
```

## Source note 95, line 1006

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1006)

```text
// which use triangle_cw. Counter-clockwise here inverts the facing and
```

## Source note 96, line 1007

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1007)

```text
// the guest backface culling removes the whole surface.
```

## Source note 97, line 1014

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1014)

```text
// Flush to zero, similar to the real hardware, also for things like Shader
```

## Source note 98, line 1015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1015)

```text
// Model 3 multiplication emulation.
```

## Source note 99, line 1021

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1021)

```text
// Signed zero used to get VFACE from ps_param_gen, also special behavior
```

## Source note 100, line 1022

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1022)

```text
// for infinity in certain instructions (such as logarithm, reciprocal,
```

## Source note 101, line 1023

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1023)

```text
// muls_prev2).
```

## Source note 102, line 1037

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1037)

```text
// Specify the binding indices for samplers when the number of textures is
```

## Source note 103, line 1038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1038)

```text
// known, as samplers are located after images in the texture descriptor
```

## Source note 104, line 1039

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1039)

```text
// set.
```

## Source note 105, line 1071

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1071)

```text
// For a stable hash.
```

## Source note 106, line 1090

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1090)

```text
// Publish the bindings to draw-thread readers (GetGuestMesaSpirvShader)
```

## Source note 107, line 1091

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1091)

```text
// after they are fully written, so a PS translated on a creation thread is
```

## Source note 108, line 1092

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1092)

```text
// only consulted once its bindings are complete.
```

## Source note 109, line 1099

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1099)

```text
// 0 already added in the beginning.
```

## Source note 110, line 1103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1103)

```text
// Writes after a label may reach it by jumping back. Writes skipped by
```

## Source note 111, line 1104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1104)

```text
// jumping forward are already in main_interpolators_unmodified_.
```

## Source note 112, line 1110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1110)

```text
// Close flow control within the previous switch case.
```

## Source note 113, line 1114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1114)

```text
// Create the next switch case and fallthrough to it.
```

## Source note 114, line 1118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1118)

```text
// Every switch case must have the OpSelectionMerge/OpSwitch block as a
```

## Source note 115, line 1119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1119)

```text
// predecessor.
```

## Source note 116, line 1121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1121)

```text
// The previous block may have already been terminated if was exece.
```

## Source note 117, line 1123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1123)

```text
// Don't fall through directly into the next case block. An OpSwitch case
```

## Source note 118, line 1124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1124)

```text
// fall-through inside the main loop makes the NVIDIA shader compiler emit a
```

## Source note 119, line 1125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1125)

```text
// non-terminating loop. Instead re-enter the loop with this label as the
```

## Source note 120, line 1126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1126)

```text
// program counter, like an unconditional jump to it does.
```

## Source note 121, line 1141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1141)

```text
// Break out of the main switch (if exists) and the main loop.
```

## Source note 122, line 1152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1152)

```text
// loop il<idx>, L<idx> - loop with loop data il<idx>, end @ L<idx>
```

## Source note 123, line 1154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1154)

```text
// Loop control is outside execs - actually close the last exec.
```

## Source note 124, line 1160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1160)

```text
// Loop constants (member 1).
```

## Source note 125, line 1162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1162)

```text
// 4-component vector.
```

## Source note 126, line 1164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1164)

```text
// Scalar within the vector.
```

## Source note 127, line 1166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1166)

```text
// Count (unsigned) in bits 0:7 of the loop constant (struct member 1),
```

## Source note 128, line 1167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1167)

```text
// initial aL (unsigned) in 8:15.
```

## Source note 129, line 1175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1175)

```text
// Push the count to the loop count stack - move XYZ to YZW and set X to the
```

## Source note 130, line 1176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1176)

```text
// new iteration count (swizzling the way glslang does it for similar GLSL).
```

## Source note 131, line 1189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1189)

```text
// Push aL - keep the same value as in the previous loop if repeating, or the
```

## Source note 132, line 1190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1190)

```text
// new one otherwise.
```

## Source note 133, line 1212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1212)

```text
// Break (jump to the skip label) if the loop counter is 0 (since the
```

## Source note 134, line 1213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1213)

```text
// condition is checked in the end).
```

## Source note 135, line 1226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1226)

```text
// More likely to enter than to skip.
```

## Source note 136, line 1242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1242)

```text
// endloop il<idx>, L<idx> - end loop w/ data il<idx>, head @ L<idx>
```

## Source note 137, line 1244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1244)

```text
// Loop control is outside execs - actually close the last exec.
```

## Source note 138, line 1249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1249)

```text
// Subtract 1 from the loop counter (will store later).
```

## Source note 139, line 1258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1258)

```text
// Predicated break works like break if (loop_count == 0 || [!]p0).
```

## Source note 140, line 1259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1259)

```text
// Three options, due to logical operations usage (so OpLogicalNot is not
```

## Source note 141, line 1260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1260)

```text
// required):
```

## Source note 142, line 1261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1261)

```text
// - Continue if (loop_count != 0).
```

## Source note 143, line 1262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1262)

```text
// - Continue if (loop_count != 0 && p0), if breaking if !p0.
```

## Source note 144, line 1263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1263)

```text
// - Break if (loop_count == 0 || p0), if breaking if p0.
```

## Source note 145, line 1281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1281)

```text
// More likely to continue than to break.
```

## Source note 146, line 1298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1298)

```text
// Continue case.
```

## Source note 147, line 1300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1300)

```text
// Store the loop count with 1 subtracted.
```

## Source note 148, line 1304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1304)

```text
// Extract the value to add to aL (signed, in bits 16:23 of the loop
```

## Source note 149, line 1305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1305)

```text
// constant).
```

## Source note 150, line 1307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1307)

```text
// Loop constants (member 1).
```

## Source note 151, line 1309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1309)

```text
// 4-component vector.
```

## Source note 152, line 1311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1311)

```text
// Scalar within the vector.
```

## Source note 153, line 1329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1329)

```text
// Jump back to the beginning of the loop body.
```

## Source note 154, line 1335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1335)

```text
// Break case.
```

## Source note 155, line 1337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1337)

```text
// Pop the current loop off the loop counter and the relative address stacks -
```

## Source note 156, line 1338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1338)

```text
// move YZW to XYZ and set W to 0.
```

## Source note 157, line 1355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1355)

```text
// Now going to fall through to the next control flow instruction.
```

## Source note 158, line 1359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1359)

```text
// Treat like exec, merge with execs if possible, since it's an if too.
```

## Source note 159, line 1370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1370)

```text
// UpdateExecConditionals may not necessarily close the instruction-level
```

## Source note 160, line 1371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1371)

```text
// predicate check (it's not necessary if the execs are merged), but here the
```

## Source note 161, line 1372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1372)

```text
// instruction itself is on the control flow level, so the predicate check is
```

## Source note 162, line 1373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1373)

```text
// on the control flow level too.
```

## Source note 163, line 1377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1377)

```text
// Unreachable for some reason.
```

## Source note 164, line 1395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1395)

```text
// Reset which eM# elements have been written.
```

## Source note 165, line 1397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1397)

```text
// Break dependencies from the previous memexport.
```

## Source note 166, line 1407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1407)

```text
// Initialize eA to an invalid address.
```

## Source note 167, line 1436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1436)

```text
// param_gen_interpolator is already 4 bits, no need for an interpolator count
```

## Source note 168, line 1437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1437)

```text
// safety check.
```

## Source note 169, line 1485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1485)

```text
// Set the point size to a negative value to tell the point sprite expansion
```

## Source note 170, line 1486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1486)

```text
// that it should use the default point size if the vertex shader does not
```

## Source note 171, line 1487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1487)

```text
// override it.
```

## Source note 172, line 1489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1489)

```text
// The edge flag is ignored.
```

## Source note 173, line 1491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1491)

```text
// Don't kill by default (zero bits 0:30).
```

## Source note 174, line 1497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1497)

```text
// Zero general-purpose registers to prevent crashes when the game references
```

## Source note 175, line 1498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1498)

```text
// them after only initializing them conditionally.
```

## Source note 176, line 1507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1507)

```text
// Zero the interpolators.
```

## Source note 177, line 1529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1529)

```text
// Create the inputs.
```

## Source note 178, line 1531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1531)

```text
// Per-control-point index input from the hull shader, mirroring the control
```

## Source note 179, line 1532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1532)

```text
// point input read by the Direct3D 12 domain shader. The hull shader has
```

## Source note 180, line 1533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1533)

```text
// already applied the endian swap, the vertex index offset, the low 24-bit
```

## Source note 181, line 1534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1534)

```text
// wrap and the min/max clamp, so this is the index the guest expects rather
```

## Source note 182, line 1535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1535)

```text
// than the raw gl_PrimitiveID. The array size matches the hull shader's
```

## Source note 183, line 1536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1536)

```text
// output control point count for the domain type.
```

## Source note 184, line 1546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1546)

```text
// Patch-indexed (and line) domains output a single control point.
```

## Source note 185, line 1557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1557)

```text
// Tessellation coordinates (barycentric coordinates for the tessellated
```

## Source note 186, line 1558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1558)

```text
// vertex within the patch).
```

## Source note 187, line 1574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1574)

```text
// Create the interpolator outputs.
```

## Source note 188, line 1596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1596)

```text
// Create the point coordinates output.
```

## Source note 189, line 1605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1605)

```text
// Create the point size output. Not using gl_PointSize from gl_PerVertex
```

## Source note 190, line 1606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1606)

```text
// not to rely on the shaderTessellationAndGeometryPointSize feature, and
```

## Source note 191, line 1607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1607)

```text
// also because the value written to gl_PointSize must be greater than
```

## Source note 192, line 1608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1608)

```text
// zero.
```

## Source note 193, line 1618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1618)

```text
// Create the gl_PerVertex output for used system outputs.
```

## Source note 194, line 1623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1623)

```text
// Only allocate ClipDistance/CullDistance arrays when user clip planes are
```

## Source note 195, line 1624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1624)

```text
// actually enabled (count > 0).
```

## Source note 196, line 1633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1633)

```text
// Vertex kill with the "and" operator writes a dedicated cull distance after
```

## Source note 197, line 1634

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1634)

```text
// the user clip plane cull distances.
```

## Source note 198, line 1659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1659)

```text
// Decorate clip/cull arrays only if allocated.
```

## Source note 199, line 1686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1686)

```text
// The edge flag isn't used for any purpose by the translator.
```

## Source note 200, line 1689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1689)

```text
// Set the point size to a negative value to tell the point sprite expansion
```

## Source note 201, line 1690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1690)

```text
// that it should use the default point size if the vertex shader does not
```

## Source note 202, line 1691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1691)

```text
// override it.
```

## Source note 203, line 1693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1693)

```text
// The edge flag is ignored.
```

## Source note 204, line 1695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1695)

```text
// Don't kill by default (zero bits 0:30).
```

## Source note 205, line 1707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1707)

```text
// Check if memory export should be allowed for this host vertex of the guest
```

## Source note 206, line 1708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1708)

```text
// primitive to make sure export is done only once for each guest vertex.
```

## Source note 207, line 1712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1712)

```text
// Run memory export for all 3 guest rectangle vertices only in one host
```

## Source note 208, line 1713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1713)

```text
// invocation (when emitting strip vertex 0).
```

## Source note 209, line 1724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1724)

```text
// Only for one host vertex for the point.
```

## Source note 210, line 1745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1745)

```text
// Expanded strip vertex index in [0, 3].
```

## Source note 211, line 1775

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1775)

```text
// Load the 3 guest rectangle vertex indices. For DMA draws, indices are
```

## Source note 212, line 1776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1776)

```text
// fetched from guest memory and endian-swapped, same as in the point list
```

## Source note 213, line 1777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1777)

```text
// fallback path.
```

## Source note 214, line 1872

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1872)

```text
// Load the vertex index or the tessellation parameters.
```

## Source note 215, line 1875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1875)

```text
// Tessellation evaluation shader (domain shader).
```

## Source note 216, line 1876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1876)

```text
// Copy barycentric coordinates (gl_TessCoord) to r0 with appropriate
```

## Source note 217, line 1877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1877)

```text
// swizzle based on the domain type.
```

## Source note 218, line 1885

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1885)

```text
// Triangle domain: gl_TessCoord.xyz -> r0.zyx
```

## Source note 219, line 1886

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1886)

```text
// ZYX swizzle according to 415607E1 and 4D5307F2.
```

## Source note 220, line 1888

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1888)

```text
// z -> r0.x
```

## Source note 221, line 1889

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1889)

```text
// y -> r0.y
```

## Source note 222, line 1890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1890)

```text
// x -> r0.z
```

## Source note 223, line 1893

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1893)

```text
// Store to r0.xyz
```

## Source note 224, line 1898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1898)

```text
// Build float4 from swizzled xyz and w=1.0
```

## Source note 225, line 1912

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1912)

```text
// Quad domain CP-indexed, matching the Direct3D 12 domain shader:
```

## Source note 226, line 1913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1913)

```text
// r0.xy = domain location, r0.z = control point index 0,
```

## Source note 227, line 1914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1914)

```text
// r1.xyz = control point indices 1, 2, 3 (already endian swapped and
```

## Source note 228, line 1915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1915)

```text
// converted to float by the host vertex and hull shaders).
```

## Source note 229, line 1918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1918)

```text
// Load control point index 0.
```

## Source note 230, line 1925

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1925)

```text
// Store r0 = (domain.x, domain.y, control point index 0, 0).
```

## Source note 231, line 1937

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1937)

```text
// Store r1.xyz = control point indices 1, 2, 3.
```

## Source note 232, line 1955

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1955)

```text
// Quad domain patch-indexed: gl_TessCoord.xy -> r0.yz,
```

## Source note 233, line 1956

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1956)

```text
// patch index -> r0.x, r0.w = 1
```

## Source note 234, line 1957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1957)

```text
// XY swizzle according to the ground shader in 4D5307F2.
```

## Source note 235, line 1959

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1959)

```text
// x -> r0.y
```

## Source note 236, line 1960

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1960)

```text
// y -> r0.z
```

## Source note 237, line 1963

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1963)

```text
// Read the patch index from control point 0 (already endian swapped,
```

## Source note 238, line 1964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1964)

```text
// offset, wrapped and clamped by the host vertex and hull shaders),
```

## Source note 239, line 1965

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1965)

```text
// matching the Direct3D 12 domain shader, rather than using the raw
```

## Source note 240, line 1966

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1966)

```text
// gl_PrimitiveID.
```

## Source note 241, line 1973

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1973)

```text
// Store to r0: x = patch index, yz = tess coord, w = 1
```

## Source note 242, line 1987

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L1987)

```text
// Also set r1.x = 0.0f (swizzle indicator for identity swizzle).
```

## Source note 243, line 2000

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2000)

```text
// Line domain tessellation is not yet implemented.
```

## Source note 244, line 2011

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2011)

```text
// For triangle patch-indexed mode, store patch index to r1.x and
```

## Source note 245, line 2012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2012)

```text
// swizzle indicator (0.0f) to r1.y.
```

## Source note 246, line 2015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2015)

```text
// Read the patch index from control point 0 (already endian swapped,
```

## Source note 247, line 2016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2016)

```text
// offset, wrapped and clamped by the host vertex and hull shaders),
```

## Source note 248, line 2017

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2017)

```text
// matching the Direct3D 12 domain shader, rather than using the raw
```

## Source note 249, line 2018

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2018)

```text
// gl_PrimitiveID.
```

## Source note 250, line 2025

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2025)

```text
// Store patch index to r1.x
```

## Source note 251, line 2032

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2032)

```text
// Store swizzle indicator (0.0f = identity) to r1.y
```

## Source note 252, line 2033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2033)

```text
// According to D3D12 implementation and comments in
```

## Source note 253, line 2034

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2034)

```text
// adaptive_triangle.hs.glsl, r1.y == 0 means identity swizzle.
```

## Source note 254, line 2042

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2042)

```text
// Store the three control point indices (already endian swapped and
```

## Source note 255, line 2043

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2043)

```text
// converted to float by the host vertex and hull shaders) to r1.xyz,
```

## Source note 256, line 2044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2044)

```text
// matching the Direct3D 12 domain shader.
```

## Source note 257, line 2071

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2071)

```text
// For rectangle list VS expansion, the translated guest shader is
```

## Source note 258, line 2072

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2072)

```text
// executed 3 times in an outer loop, and r0.x is written there.
```

## Source note 259, line 2075

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2075)

```text
// Load the point index, autogenerated or indirectly from the index
```

## Source note 260, line 2076

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2076)

```text
// buffer.
```

## Source note 261, line 2077

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2077)

```text
// Extract the primitive index from the two-triangle strip vertex index.
```

## Source note 262, line 2083

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2083)

```text
// Check if the index needs to be loaded from the index buffer.
```

## Source note 263, line 2096

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2096)

```text
// Check if the index is 32-bit.
```

## Source note 264, line 2103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2103)

```text
// Calculate the vertex index address in the shared memory.
```

## Source note 265, line 2117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2117)

```text
// Load the 32 bits containing the whole vertex index or two 16-bit
```

## Source note 266, line 2118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2118)

```text
// vertex indices.
```

## Source note 267, line 2124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2124)

```text
// Extract the 16-bit index from the loaded 32 bits if needed.
```

## Source note 268, line 2134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2134)

```text
// Endian-swap the loaded index.
```

## Source note 269, line 2145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2145)

```text
// Select between the loaded index and the original index from Vulkan.
```

## Source note 270, line 2153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2153)

```text
// Check if the full 32-bit index needs to be loaded indirectly.
```

## Source note 271, line 2166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2166)

```text
// Load the 32-bit index.
```

## Source note 272, line 2185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2185)

```text
// Select between the loaded index and the original index from Vulkan.
```

## Source note 273, line 2187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2187)

```text
// Clamp only the indirection index position used for shared-memory
```

## Source note 274, line 2188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2188)

```text
// loads. For regular indexed draws, input_vertex_index is already the
```

## Source note 275, line 2189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2189)

```text
// fetched vertex index value and must not be bounded by index count.
```

## Source note 276, line 2195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2195)

```text
// Endian-swap the index.
```

## Source note 277, line 2205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2205)

```text
// Convert the index to a signed integer.
```

## Source note 278, line 2207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2207)

```text
// Add the base to the index.
```

## Source note 279, line 2258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2258)

```text
// Choose the diagonal to build the strip from (matching the geometry shader
```

## Source note 280, line 2259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2259)

```text
// path using host-converted clip-space XY).
```

## Source note 281, line 2385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2385)

```text
// Build and write the final guest position for this strip vertex.
```

## Source note 282, line 2405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2405)

```text
// Build and write the final guest interpolators for this strip vertex.
```

## Source note 283, line 2431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2431)

```text
// Check if the shader already returns W, not 1/W, and if it doesn't, turn 1/W
```

## Source note 284, line 2432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2432)

```text
// into W.
```

## Source note 285, line 2447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2447)

```text
// Open a scope since position_xy and position_z won't be synchronized anymore
```

## Source note 286, line 2448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2448)

```text
// after position_xyz is built and modified later.
```

## Source note 287, line 2450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2450)

```text
// Check if the shader returns XY/W rather than XY, and if it does, revert
```

## Source note 288, line 2451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2451)

```text
// that.
```

## Source note 289, line 2470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2470)

```text
// Check if the shader returns Z/W rather than Z, and if it does, revert
```

## Source note 290, line 2471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2471)

```text
// that.
```

## Source note 291, line 2484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2484)

```text
// Build XYZ of the position with W format handled.
```

## Source note 292, line 2495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2495)

```text
// Compute user clip/cull distances BEFORE NDC transform.
```

## Source note 293, line 2496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2496)

```text
// Clip planes must operate on the original clip-space position.
```

## Source note 294, line 2499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2499)

```text
// Reconstruct the original clip-space position (x, y, z, w) for dot
```

## Source note 295, line 2500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2500)

```text
// product. Use the untransformed position_xyz and corrected position_w.
```

## Source note 296, line 2511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2511)

```text
// Determine which member index to use based on whether we're using
```

## Source note 297, line 2512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2512)

```text
// ClipDistance or CullDistance.
```

## Source note 298, line 2518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2518)

```text
// Compute distance to each enabled user clip plane via dot product.
```

## Source note 299, line 2520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2520)

```text
// Load user clip plane from the system constants buffer.
```

## Source note 300, line 2523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2523)

```text
// Array index
```

## Source note 301, line 2529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2529)

```text
// Compute dot product: distance = dot(clip_space_position, clip_plane).
```

## Source note 302, line 2533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2533)

```text
// Store to gl_ClipDistance[i] or gl_CullDistance[i].
```

## Source note 303, line 2543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2543)

```text
// Apply the NDC scale and offset for guest to host viewport transformation.
```

## Source note 304, line 2563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2563)

```text
// Apply vertex killing requested via the kill flag (oPts.z) - bits 0:30 of
```

## Source note 305, line 2564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2564)

```text
// the value being non-zero kills. Done after the NDC transform since the kill
```

## Source note 306, line 2565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2565)

```text
// cull distance is just a flag and the position is about to be written.
```

## Source note 307, line 2569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2569)

```text
// Z vector component.
```

## Source note 308, line 2575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2575)

```text
// Test the integer bits 0:30 rather than comparing the float to avoid
```

## Source note 309, line 2576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2576)

```text
// denormal flushing affecting the result (matching the Direct3D 12 path).
```

## Source note 310, line 2584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2584)

```text
// "and" operator - write -1 to the dedicated cull distance when killed
```

## Source note 311, line 2585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2585)

```text
// (the primitive is culled only if it's negative for all the vertices).
```

## Source note 312, line 2598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2598)

```text
// "or" operator - setting the position W to NaN kills the whole primitive
```

## Source note 313, line 2599

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2599)

```text
// if any of its vertices requests the kill.
```

## Source note 314, line 2608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2608)

```text
// Write the point size.
```

## Source note 315, line 2614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2614)

```text
// X vector component.
```

## Source note 316, line 2621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2621)

```text
// Not statically overridden - write a negative value.
```

## Source note 317, line 2627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2627)

```text
// Expand the point sprite.
```

## Source note 318, line 2630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2630)

```text
// Top-left, bottom-left, top-right, bottom-right order (chosen arbitrarily,
```

## Source note 319, line 2631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2631)

```text
// simply based on counterclockwise meaning front with
```

## Source note 320, line 2632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2632)

```text
// frontFace = VkFrontFace(0), but faceness is ignored for non-polygon
```

## Source note 321, line 2633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2633)

```text
// primitive types).
```

## Source note 322, line 2649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2649)

```text
// Load the point diameter in guest pixels, with the override from the
```

## Source note 323, line 2650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2650)

```text
// vertex shader if provided.
```

## Source note 324, line 2665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2665)

```text
// The vertex shader's header writes -1.0 to point_size by default, so any
```

## Source note 325, line 2666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2666)

```text
// non-negative value means that it was overwritten by the translated
```

## Source note 326, line 2667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2667)

```text
// vertex shader, and needs to be used instead of the constant size. The
```

## Source note 327, line 2668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2668)

```text
// per-vertex diameter has already been clamped earlier in translation
```

## Source note 328, line 2669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2669)

```text
// (combined with making it non-negative).
```

## Source note 329, line 2679

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2679)

```text
// Transform the diameter in the guest screen coordinates to radius in the
```

## Source note 330, line 2680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2680)

```text
// normalized device coordinates.
```

## Source note 331, line 2690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2690)

```text
// Transform the radius from the normalized device coordinates to the clip
```

## Source note 332, line 2691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2691)

```text
// space.
```

## Source note 333, line 2695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2695)

```text
// Expand the point sprite in the direction for the current host vertex.
```

## Source note 334, line 2706

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2706)

```text
// Store the position.
```

## Source note 335, line 2709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2709)

```text
// Bypass the `getNumTypeConstituents(typeId) == (int)constituents.size()`
```

## Source note 336, line 2710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2710)

```text
// assertion in createCompositeConstruct, OpCompositeConstruct can
```

## Source note 337, line 2711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2711)

```text
// construct vectors not only from scalars, but also from other vectors.
```

## Source note 338, line 2723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2723)

```text
// Write the point coordinates.
```

## Source note 339, line 2732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2732)

```text
// Store the position converted to the host.
```

## Source note 340, line 2735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2735)

```text
// Bypass the `getNumTypeConstituents(typeId) == (int)constituents.size()`
```

## Source note 341, line 2736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2736)

```text
// assertion in createCompositeConstruct, OpCompositeConstruct can
```

## Source note 342, line 2737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2737)

```text
// construct vectors not only from scalars, but also from other vectors.
```

## Source note 343, line 2755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2755)

```text
// EDRAM buffer uint[].
```

## Source note 344, line 2758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2758)

```text
// Storage buffers have std430 packing, no padding to 4-component vectors.
```

## Source note 345, line 2782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2782)

```text
// ZPD counter buffer uint[], for FSI and hybrid queries.
```

## Source note 346, line 2813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2813)

```text
// Interpolator inputs.
```

## Source note 347, line 2814

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2814)

```text
// When fragment_shader_barycentric is enabled, create per-vertex
```

## Source note 348, line 2815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2815)

```text
// interpolator arrays (float4[3]) with PerVertexKHR decoration for manual
```

## Source note 349, line 2816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2816)

```text
// barycentric interpolation. This works around Nvidia driver differences
```

## Source note 350, line 2817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2817)

```text
// in hardware interpolation that can cause noise artifacts in games that
```

## Source note 351, line 2818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2818)

```text
// do exact equality comparisons in shaders (e.g., Perfect Dark, Tenchu Z).
```

## Source note 352, line 2819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2819)

```text
// Skip barycentric for point primitives - barycentric coordinates are only
```

## Source note 353, line 2820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2820)

```text
// meaningful for triangles.
```

## Source note 354, line 2825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2825)

```text
// Add extension and capability for barycentric interpolation.
```

## Source note 355, line 2829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2829)

```text
// Create gl_BaryCoordKHR builtin input (float3).
```

## Source note 356, line 2836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2836)

```text
// Create per-vertex interpolator inputs as float4[3] arrays with
```

## Source note 357, line 2837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2837)

```text
// PerVertexKHR decoration.
```

## Source note 358, line 2851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2851)

```text
// Note: Centroid decoration is not applicable with PerVertexKHR since
```

## Source note 359, line 2852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2852)

```text
// we're doing manual interpolation.
```

## Source note 360, line 2857

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2857)

```text
// Standard hardware interpolation path.
```

## Source note 361, line 2876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2876)

```text
// Point coordinate input.
```

## Source note 362, line 2889

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2889)

```text
// Fragment coordinates.
```

## Source note 363, line 2890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2890)

```text
// FSI: Always needed for EDRAM offset calculation and depth derivatives.
```

## Source note 364, line 2891

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2891)

```text
// param_gen: Needed for PsParamGen calculation.
```

## Source note 365, line 2892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2892)

```text
// FBO alpha-to-coverage: Needed for dithering pattern, but only when
```

## Source note 366, line 2893

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2893)

```text
// alpha-to-coverage can actually run (no early fragment tests).
```

## Source note 367, line 2894

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2894)

```text
// FBO float24 in-PS conversion of the rasterizer's depth: reads
```

## Source note 368, line 2895

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2895)

```text
// gl_FragCoord.z
```

## Source note 369, line 2896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2896)

```text
// - and must do so per-sample for MSAA antialiasing of intersections.
```

## Source note 370, line 2908

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2908)

```text
// Per the Vulkan spec, a Sample-decorated fragment input forces
```

## Source note 371, line 2909

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2909)

```text
// per-sample shader invocation - no explicit sampleShadingEnable needed.
```

## Source note 372, line 2916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2916)

```text
// Is front facing.
```

## Source note 373, line 2926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2926)

```text
// Sample mask input.
```

## Source note 374, line 2928

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2928)

```text
// SampleMask depends on SampleRateShading in some SPIR-V revisions.
```

## Source note 375, line 2940

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2940)

```text
// Framebuffer color attachment outputs (FBO path only).
```

## Source note 376, line 2941

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2941)

```text
// For FBO, we create Output variables here and Function-scoped variables
```

## Source note 377, line 2942

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2942)

```text
// in StartFragmentShaderInMain. The Function-scoped variables are used
```

## Source note 378, line 2943

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2943)

```text
// throughout the shader (so we can read them for alpha test), and copied
```

## Source note 379, line 2944

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2944)

```text
// to the Output variables at the end.
```

## Source note 380, line 2953

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2953)

```text
// Only create outputs for color targets that are both written by the
```

## Source note 381, line 2954

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2954)

```text
// shader and actually bound in the render pass.
```

## Source note 382, line 2967

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2967)

```text
// Make invariant as pixel shaders may be used for various precise
```

## Source note 383, line 2968

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2968)

```text
// computations.
```

## Source note 384, line 2975

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2975)

```text
// FBO fragment depth output. Used for guest oDepth, float24 conversion, and
```

## Source note 385, line 2976

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2976)

```text
// the narrow host RT decal path. FSI manages depth in EDRAM instead.
```

## Source note 386, line 2988

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2988)

```text
// Sample mask output for alpha-to-coverage.
```

## Source note 387, line 2989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2989)

```text
// Only needed for non-FSI mode. FSI uses main_fsi_sample_mask_ instead.
```

## Source note 388, line 2992

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L2992)

```text
// gl_SampleMask is an array of int in SPIR-V.
```

## Source note 389, line 3004

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3004)

```text
// The ZPD Total counter tracks coverage entering the shader until all
```

## Source note 390, line 3005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3005)

```text
// pre-depth/stencil tests finish dropping samples.
```

## Source note 391, line 3025

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3025)

```text
// Set up pixel killing from within the translated shader without affecting
```

## Source note 392, line 3026

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3026)

```text
// the control flow (unlike with OpKill), similarly to how pixel killing works
```

## Source note 393, line 3027

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3027)

```text
// on the Xenos, and also keeping a single critical section exit and return
```

## Source note 394, line 3028

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3028)

```text
// for safety across different Vulkan implementations with fragment shader
```

## Source note 395, line 3029

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3029)

```text
// interlock.
```

## Source note 396, line 3039

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3039)

```text
// For killing with fragment shader interlock when demotion is supported,
```

## Source note 397, line 3040

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3040)

```text
// using OpIsHelperInvocationEXT to avoid allocating a variable in addition
```

## Source note 398, line 3041

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3041)

```text
// to the execution mask GPUs naturally have.
```

## Source note 399, line 3044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3044)

```text
// Initialize color output variables as Function-scoped for both FSI and FBO.
```

## Source note 400, line 3045

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3045)

```text
// For FBO, this allows reading the color values back (e.g., for alpha test),
```

## Source note 401, line 3046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3046)

```text
// which isn't possible with Output storage class. The values are copied to
```

## Source note 402, line 3047

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3047)

```text
// the actual Output variables at the end of the shader for FBO.
```

## Source note 403, line 3066

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3066)

```text
// Color write tracking for both FSI and FBO paths.
```

## Source note 404, line 3067

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3067)

```text
// This is used to conditionally skip alpha test / alpha-to-coverage if
```

## Source note 405, line 3068

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3068)

```text
// render target 0 wasn't written on the execution path.
```

## Source note 406, line 3074

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3074)

```text
// Staging variable for guest oDepth writes.
```

## Source note 407, line 3075

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3075)

```text
// Created whenever the shader uses oDepth:
```

## Source note 408, line 3076

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3076)

```text
//   * FSI reads it during its EDRAM depth write inside the interlock.
```

## Source note 409, line 3077

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3077)

```text
//   * FBO copies it to gl_FragDepth at the end of the shader.
```

## Source note 410, line 3085

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3085)

```text
// The decal path needs the original triangle depth slope, not the slope of
```

## Source note 411, line 3086

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3086)

```text
// whichever lanes survive guest control flow or kill.
```

## Source note 412, line 3107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3107)

```text
// Failed samples never reach the end of an early-tested shader, so
```

## Source note 413, line 3108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3108)

```text
// they're counted here before the quad can be discarded.
```

## Source note 414, line 3112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3112)

```text
// Skip the rest of the shader if the whole quad (due to derivatives) has
```

## Source note 415, line 3113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3113)

```text
// failed the depth / stencil test, and there are no depth and stencil
```

## Source note 416, line 3114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3114)

```text
// values to conditionally write after running the shader to check if
```

## Source note 417, line 3115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3115)

```text
// samples don't additionally need to be discarded.
```

## Source note 418, line 3120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3120)

```text
// Query the horizontally adjacent pixel.
```

## Source note 419, line 3130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3130)

```text
// Query the vertically adjacent pair of pixels.
```

## Source note 420, line 3157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3157)

```text
// Zero general-purpose registers to prevent crashes when the game
```

## Source note 421, line 3158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3158)

```text
// references them after only initializing them conditionally, and copy
```

## Source note 422, line 3159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3159)

```text
// interpolants to GPRs.
```

## Source note 423, line 3162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3162)

```text
// When barycentric interpolation is enabled, manually compute interpolated
```

## Source note 424, line 3163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3163)

```text
// values using barycentric coordinates to avoid Nvidia driver interpolation
```

## Source note 425, line 3164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3164)

```text
// differences. Skip for point primitives since barycentric coordinates are
```

## Source note 426, line 3165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3165)

```text
// only meaningful for triangles.
```

## Source note 427, line 3170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3170)

```text
// Barycentric weights splatted to float4 for interpolation.
```

## Source note 428, line 3171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3171)

```text
// Using only bary.y and bary.z since we anchor on v0 (bary.x = 1 - y - z).
```

## Source note 429, line 3175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3175)

```text
// Load barycentric coordinates once for all interpolators.
```

## Source note 430, line 3178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3178)

```text
// Extract and smear bary.y and bary.z to float4 for vectorized ops.
```

## Source note 431, line 3179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3179)

```text
// We don't need bary.x since we use v0 as anchor (AMD-style interpolation).
```

## Source note 432, line 3196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3196)

```text
// The Xenos samples a pixel once, at its center. With resolution scaling, the
```

## Source note 433, line 3197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3197)

```text
// host pixels are up to (scale - 1) / (2 * scale) guest pixels away from it,
```

## Source note 434, line 3198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3198)

```text
// which with a coordinate bias the guest was fine with, such as the quarter
```

## Source note 435, line 3199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3199)

```text
// texel in 43430814's GPU animation passes, makes point sampled fetches read
```

## Source note 436, line 3200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3200)

```text
// the neighbor texel. Over at most (scale - 1) / 2 host pixels, interpolants
```

## Source note 437, line 3201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3201)

```text
// are close enough to affine for the derivatives to give their value at the
```

## Source note 438, line 3202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3202)

```text
// guest pixel center.
```

## Source note 439, line 3220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3220)

```text
// (floor(position / scale) + 0.5) * scale - position.
```

## Source note 440, line 3246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3246)

```text
// AMD-style barycentric interpolation using v0 as anchor.
```

## Source note 441, line 3247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3247)

```text
// This matches real AMD GPU hardware (V_INTERP_P1_F32/V_INTERP_P2_F32):
```

## Source note 442, line 3248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3248)

```text
//   result = v0 + (v1 - v0) * bary.y + (v2 - v0) * bary.z
```

## Source note 443, line 3250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3250)

```text
// Since bary.x + bary.y + bary.z = 1, this is equivalent to:
```

## Source note 444, line 3251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3251)

```text
//   result = v0 * bary.x + v1 * bary.y + v2 * bary.z
```

## Source note 445, line 3253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3253)

```text
// When v0 = v1 = v2 = V:
```

## Source note 446, line 3254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3254)

```text
//   (v1 - v0) = 0, (v2 - v0) = 0, result = v0 = V (exact)
```

## Source note 447, line 3256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3256)

```text
// This avoids floating-point precision issues that cause noise
```

## Source note 448, line 3257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3257)

```text
// artifacts on Nvidia GPUs when games do exact equality comparisons.
```

## Source note 449, line 3260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3260)

```text
// Load per-vertex values (vertex 0, 1, 2).
```

## Source note 450, line 3280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3280)

```text
// Compute deltas from v0 (anchor vertex).
```

## Source note 451, line 3284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3284)

```text
// Compute: v0 + d1*bary.y + d2*bary.z
```

## Source note 452, line 3290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3290)

```text
// Standard hardware interpolation path.
```

## Source note 453, line 3320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3320)

```text
// The beginning of the shader may be jumped back to.
```

## Source note 454, line 3324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3324)

```text
// Pixel parameters.
```

## Source note 455, line 3327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3327)

```text
// Rounding the position down, and taking the absolute value, so in case the
```

## Source note 456, line 3328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3328)

```text
// host GPU for some reason has quads used for derivative calculation at odd
```

## Source note 457, line 3329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3329)

```text
// locations, the left and top edges will have correct derivative magnitude
```

## Source note 458, line 3330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3330)

```text
// and LODs.
```

## Source note 459, line 3331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3331)

```text
// Assuming that if PsParamGen is needed at all, param_gen_point is always
```

## Source note 460, line 3332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3332)

```text
// set for point primitives, and is always disabled for other primitive
```

## Source note 461, line 3333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3333)

```text
// types.
```

## Source note 462, line 3334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3334)

```text
// OpFNegate requires sign bit flipping even for 0.0 (in this case, the
```

## Source note 463, line 3335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3335)

```text
// first column or row of pixels) only since SPIR-V 1.5 revision 2 (not the
```

## Source note 464, line 3336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3336)

```text
// base 1.5).
```

## Source note 465, line 3339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3339)

```text
// X - pixel X .0 in the magnitude, is back-facing in the sign bit.
```

## Source note 466, line 3351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3351)

```text
// Apply resolution scale inversion after truncating.
```

## Source note 467, line 3377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3377)

```text
// Y - pixel Y .0 in the magnitude, is point in the sign bit.
```

## Source note 468, line 3388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3388)

```text
// Apply resolution scale inversion after truncating.
```

## Source note 469, line 3401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3401)

```text
// Z - point S in the magnitude, is line in the sign bit.
```

## Source note 470, line 3402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3402)

```text
// W - point T in the magnitude.
```

## Source note 471, line 3406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3406)

```text
// Saturate to avoid negative point coordinates if the center of the pixel
```

## Source note 472, line 3407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3407)

```text
// is not covered, and extrapolation is done.
```

## Source note 473, line 3427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3427)

```text
// Store the pixel parameters.
```

## Source note 474, line 3444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3444)

```text
// Check if we can merge the new exec with the previous one, or the jump with
```

## Source note 475, line 3445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3445)

```text
// the previous exec. The instruction-level predicate check is also merged in
```

## Source note 476, line 3446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3446)

```text
// this case.
```

## Source note 477, line 3448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3448)

```text
// Can merge conditional with conditional, as long as the bool constant and
```

## Source note 478, line 3449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3449)

```text
// the expected values are the same.
```

## Source note 479, line 3455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3455)

```text
// Can merge predicated with predicated if the conditions are the same and
```

## Source note 480, line 3456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3456)

```text
// the previous exec hasn't modified the predicate register.
```

## Source note 481, line 3463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3463)

```text
// Can merge unconditional with unconditional.
```

## Source note 482, line 3480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3480)

```text
// Bool constants (member 0).
```

## Source note 483, line 3482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3482)

```text
// 128-bit vector.
```

## Source note 484, line 3484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3484)

```text
// 32-bit scalar of a 128-bit vector.
```

## Source note 485, line 3523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3523)

```text
// Already in the needed instruction-level conditional.
```

## Source note 486, line 3529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3529)

```text
// If the instruction predicate condition is the same as the exec predicate
```

## Source note 487, line 3530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3530)

```text
// condition, no need to open a check. However, if there was a `setp` prior
```

## Source note 488, line 3531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3531)

```text
// to this instruction, the predicate value now may be different than it was
```

## Source note 489, line 3532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3532)

```text
// in the beginning of the exec.
```

## Source note 490, line 3566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3566)

```text
// Within the exec - instruction-level predicate check.
```

## Source note 491, line 3568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3568)

```text
// Exec level.
```

## Source note 492, line 3578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3578)

```text
// Nothing relies on the predicate value being unchanged now.
```

## Source note 493, line 3605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3605)

```text
// Load X component.
```

## Source note 494, line 3619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3619)

```text
// a0 and aL are whatever the guest put there, so clamp to the array. Direct3D
```

## Source note 495, line 3620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3620)

```text
// 12 binds the float constants as a root CBV, which carries no size to bound
```

## Source note 496, line 3621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3621)

```text
// the read, unlike a Vulkan uniform buffer under robust buffer access.
```

## Source note 497, line 3641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3641)

```text
// Array element.
```

## Source note 498, line 3649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3649)

```text
// The first and the only structure member.
```

## Source note 499, line 3651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3651)

```text
// Array element.
```

## Source note 500, line 3764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3764)

```text
// Must call GetStorageAddressingIndex first because of
```

## Source note 501, line 3765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3765)

```text
// id_vector_temp_util_ usage in it.
```

## Source note 502, line 3769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3769)

```text
// Array element.
```

## Source note 503, line 3777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3777)

```text
// Unused interpolators are spv::NoResult in input_output_interpolators_.
```

## Source note 504, line 3806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3806)

```text
// spv::NoResult if memory export usage is unsupported or invalid.
```

## Source note 505, line 3810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3810)

```text
// spv::NoResult if memory export usage is unsupported or invalid.
```

## Source note 506, line 3813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3813)

```text
// Mark that the eM# has been written to and needs to be exported.
```

## Source note 507, line 3824

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3824)

```text
// oDepth is scalar. The FBO path copies it to gl_FragDepth (in
```

## Source note 508, line 3825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3825)

```text
// CompleteFragmentShader_DSV_DepthTo24Bit), while FSI writes it to a
```

## Source note 509, line 3826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3826)

```text
// depth variable consumed by FSI_DepthStencilTest.
```

## Source note 510, line 3832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3832)

```text
// Depth outside [0, 1] needs to be clamped for safety, similar to D3D12.
```

## Source note 511, line 3833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3833)

```text
// Though 20e4 float depth can store values between 1 and 2, it's a very
```

## Source note 512, line 3834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3834)

```text
// unusual case. In Vulkan, gl_FragDepth can accept any values when the
```

## Source note 513, line 3835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3835)

```text
// depth buffer is floating-point, but we clamp for consistency.
```

## Source note 514, line 3836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3836)

```text
// Clamp the depth value to [0, 1] if not already saturated.
```

## Source note 515, line 3844

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3844)

```text
// All storage targets should be handled above.
```

## Source note 516, line 3855

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3855)

```text
// The instruction processing function decided that nothing useful needs to
```

## Source note 517, line 3856

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3856)

```text
// be stored for some reason, however, some components still need to be
```

## Source note 518, line 3857

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3857)

```text
// written on the guest side - fill them with zeros.
```

## Source note 519, line 3866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3866)

```text
// Apply the saturation modifier to the result.
```

## Source note 520, line 3873

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3873)

```text
// The value contains either result.GetUsedResultComponents() in a condensed
```

## Source note 521, line 3874

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3874)

```text
// way, or a scalar to be replicated. Decompress them to create a mapping from
```

## Source note 522, line 3875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3875)

```text
// guest result components to the ones in the value vector.
```

## Source note 523, line 3889

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3889)

```text
// Get swizzled mapping of non-constant components to the components of
```

## Source note 524, line 3890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3890)

```text
// `value`.
```

## Source note 525, line 3911

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3911)

```text
// All components are overwritten - no need to load the original value.
```

## Source note 526, line 3912

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3912)

```text
// Possible cases:
```

## Source note 527, line 3913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3913)

```text
// * Non-constants only.
```

## Source note 528, line 3914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3914)

```text
//   * Vector target.
```

## Source note 529, line 3915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3915)

```text
//     * Vector source.
```

## Source note 530, line 3916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3916)

```text
//       * Identity swizzle - store directly.
```

## Source note 531, line 3917

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3917)

```text
//       * Non-identity swizzle - shuffle.
```

## Source note 532, line 3918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3918)

```text
//     * Scalar source - smear.
```

## Source note 533, line 3919

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3919)

```text
//   * Scalar target.
```

## Source note 534, line 3920

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3920)

```text
//     * Vector source - extract.
```

## Source note 535, line 3921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3921)

```text
//     * Scalar source - store directly.
```

## Source note 536, line 3922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3922)

```text
// * Constants only.
```

## Source note 537, line 3923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3923)

```text
//   * Vector target - make composite constant.
```

## Source note 538, line 3924

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3924)

```text
//   * Scalar target - store directly.
```

## Source note 539, line 3925

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3925)

```text
// * Mixed non-constants and constants (only for vector targets - scalar
```

## Source note 540, line 3926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3926)

```text
//   targets fully covered by the previous cases).
```

## Source note 541, line 3927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3927)

```text
//   * Vector source - shuffle with {0, 1} also applying swizzle.
```

## Source note 542, line 3928

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3928)

```text
//   * Scalar source - construct composite.
```

## Source note 543, line 3932

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3932)

```text
// Non-constants only - vector target, vector source.
```

## Source note 544, line 3948

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3948)

```text
// Non-constants only - vector target, scalar source.
```

## Source note 545, line 3953

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3953)

```text
// Non-constants only - scalar target, vector source.
```

## Source note 546, line 3957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3957)

```text
// Non-constants only - scalar target, scalar source.
```

## Source note 547, line 3963

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3963)

```text
// Constants only - vector target.
```

## Source note 548, line 3971

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3971)

```text
// Constants only - scalar target.
```

## Source note 549, line 3977

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3977)

```text
// Mixed non-constants and constants - vector source.
```

## Source note 550, line 3990

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L3990)

```text
// Mixed non-constants and constants - scalar source.
```

## Source note 551, line 4004

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4004)

```text
// Only certain components are overwritten.
```

## Source note 552, line 4005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4005)

```text
// Scalar targets are always overwritten fully, can't reach this case for
```

## Source note 553, line 4006

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4006)

```text
// them.
```

## Source note 554, line 4009

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4009)

```text
// Two steps:
```

## Source note 555, line 4010

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4010)

```text
// 1) Insert constants by shuffling (first so dependency chain of step 2 is
```

## Source note 556, line 4011

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4011)

```text
//    simpler if constants are written first).
```

## Source note 557, line 4012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4012)

```text
// 2) Insert value components - via shuffling for vector source, via
```

## Source note 558, line 4013

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4013)

```text
//    composite inserts for scalar value.
```

## Source note 559, line 4053

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4053)

```text
// Make the point size non-negative as negative is used to indicate that the
```

## Source note 560, line 4054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4054)

```text
// default size must be used, and also clamp it to the bounds the way the
```

## Source note 561, line 4055

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4055)

```text
// R400 (Adreno 200, to be more precise) hardware clamps it (functionally
```

## Source note 562, line 4056

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4056)

```text
// like a signed 32-bit integer, -NaN and -Infinity...-0 to the minimum,
```

## Source note 563, line 4057

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4057)

```text
// +NaN to the maximum).
```

## Source note 564, line 4114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4114)

```text
// 8-in-16 or one half of 8-in-32 (doing 8-in-16 swap).
```

## Source note 565, line 4140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4140)

```text
// 16-in-32 or another half of 8-in-32 (doing 16-in-32 swap).
```

## Source note 566, line 4161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4161)

```text
// Change 8-in-64 and 8-in-128 to 8-in-32, and then swap within 32 bits.
```

## Source note 567, line 4205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4205)

```text
// Single binding - load directly.
```

## Source note 568, line 4207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4207)

```text
// The only SSBO struct member.
```

## Source note 569, line 4215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4215)

```text
// The memory is split into multiple bindings - check which binding to load
```

## Source note 570, line 4216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4216)

```text
// from. 29 is log2(512 MB), but addressing in dwords (4 B). Not indexing the
```

## Source note 571, line 4217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4217)

```text
// array with the variable itself because it needs non-uniform storage buffer
```

## Source note 572, line 4218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4218)

```text
// indexing.
```

## Source note 573, line 4231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4231)

```text
// Zero if out of bounds.
```

## Source note 574, line 4241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4241)

```text
// The only SSBO struct member.
```

## Source note 575, line 4275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4275)

```text
// Don't touch the other bits in the buffer, just modify the needed bits
```

## Source note 576, line 4276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4276)

```text
// in the most up to date uint32 at the address.
```

## Source note 577, line 4292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4292)

```text
// Single binding - store directly.
```

## Source note 578, line 4294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4294)

```text
// The only SSBO struct member.
```

## Source note 579, line 4301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4301)

```text
// The memory is split into multiple bindings - check which binding to store
```

## Source note 580, line 4302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4302)

```text
// to. 29 is log2(512 MB), but addressing in dwords (4 B). Not indexing the
```

## Source note 581, line 4303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4303)

```text
// array with the variable itself because it needs non-uniform storage buffer
```

## Source note 582, line 4304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4304)

```text
// indexing.
```

## Source note 583, line 4321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4321)

```text
// The only SSBO struct member.
```

## Source note 584, line 4349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4349)

```text
// Saturate, flushing NaN to 0.
```

## Source note 585, line 4386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4386)

```text
// linear = gamma * (255.0f * 1024.0f) * scale + offset
```

## Source note 586, line 4395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4395)

```text
// linear += trunc(linear * scale)
```

## Source note 587, line 4401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4401)

```text
// linear *= 1.0f / 1023.0f
```

## Source note 588, line 4422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4422)

```text
// Saturate, flushing NaN to 0.
```

## Source note 589, line 4459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator.cpp#L4459)

```text
// gamma = trunc(linear * scale) * (1.0f / 255.0f) + offset
```
