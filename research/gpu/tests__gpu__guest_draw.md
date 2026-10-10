# Guest draw: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/guest_draw.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L34)

```text
// Guest microcode, hand-assembled (see include/rex/graphics/format/ucode.h).
```

## Source note 2, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L35)

```text
// Control flow instructions are 48 bits, two per three dwords; ALU and fetch
```

## Source note 3, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L36)

```text
// instructions follow as three dwords each, addressed in three-dword units.
```

## Source note 4, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L38)

```text
// exec (vfetch r1, r0.x, vf0 as float4, stride 4); alloc position;
```

## Source note 5, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L39)

```text
// exec_end (max oPos, r1, r1). The vertex index is in r0.x.
```

## Source note 6, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L41)

```text
// exec 2 fetch; alloc position
```

## Source note 7, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L42)

```text
// exec_end 3 ALU; nop
```

## Source note 8, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L43)

```text
// vfetch r1.xyzw, r0.x, vf0
```

## Source note 9, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L44)

```text
// max oPos.xyzw, r1, r1
```

## Source note 10, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L47)

```text
// alloc colors; exec_end (max oC0, c0, c0).
```

## Source note 11, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L49)

```text
// alloc colors; exec_end 1 ALU
```

## Source note 12, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L50)

```text
// max oC0.xyzw, c0, c0
```

## Source note 13, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L64)

```text
// In samples, as in RB_SURFACE_INFO.
```

## Source note 14, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L69)

```text
// Depth at the left and the right edges of the region, 0 to 1 (right is
```

## Source note 15, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L70)

```text
// the left one if negative).
```

## Source note 16, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L77)

```text
// RB_COLOR_MASK bits of color target 0.
```

## Source note 17, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L79)

```text
// Of the vertex fetch constant; titles sometimes leave the wrong one.
```

## Source note 18, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L83)

```text
// Sets up drawing constant-color rectangles into a color target and a depth
```

## Source note 19, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L84)

```text
// target at EDRAM base 0, within (0, 0)-(width, height).
```

## Source note 20, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L88)

```text
// Past the region on every side: with the Direct3D 9 pixel center
```

## Source note 21, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L89)

```text
// convention, the geometry is shifted by half a pixel, which would leave
```

## Source note 22, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L90)

```text
// MSAA samples of the first row and column uncovered. The scissor clips.
```

## Source note 23, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L92)

```text
// Extrapolated to the extended edges.
```

## Source note 24, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L130)

```text
// One * source + zero * destination for color and alpha.
```

## Source note 25, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L147)

```text
// Draws (x0, y0)-(x1, y1) with the constant pixel shader output c0, clipped by
```

## Source note 26, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L148)

```text
// the window scissor, with the state from SetupDraw.
```

## Source note 27, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L165)

```text
// DrawRectFloat with an 8-bit normalized RGBA color (red in the low byte).
```

## Source note 28, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L173)

```text
// The source and destination formats of Resolve.
```

## Source note 29, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L180)

```text
// Resolves (0, 0)-(width, height) of the 32bpp color target at EDRAM base 0,
```

## Source note 30, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L181)

```text
// one sample of it with MSAA, to a 32-high k_8_8_8_8 tiled texture (or the
```

## Source note 31, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L182)

```text
// formats given).
```

## Source note 32, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L241)

```text
// Microcode encoders for hand-assembled shaders.
```

## Source note 33, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L243)

```text
// Control flow instructions, packed two per three dwords.
```

## Source note 34, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L245)

```text
// dword_1 has 16 bits.
```

## Source note 35, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L258)

```text
// ALU vector operation exporting all four components to export register
```

## Source note 36, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L259)

```text
// `dest` (32 is eA, 33 is eM0, 62 is the position), with the scalar operation
```

## Source note 37, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L260)

```text
// retaining the previous value. `sel` bits select temporary registers (1) or
```

## Source note 38, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L261)

```text
// float constants (0) for sources 1..3.
```

## Source note 39, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/guest_draw.h#L272)

```text
// Component-relative swizzle replicating X.
```
