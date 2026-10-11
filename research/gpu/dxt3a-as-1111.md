# k_DXT3A_AS_1_1_1_1 and resolve copy command 2

Ported from xenia-edge `ac37478be6` and `7347cd12ef` (knuckleslee) for #236.

## Bit order

Each pixel of a `k_DXT3A_AS_1_1_1_1` texture is a 4-bit DXT3A alpha value
whose bits are four 1-bit components: red in bit 0, green in bit 1, blue in
bit 2, alpha in bit 3. Xenia had assumed the opposite (alpha in the low bit,
by analogy with DXT colour ordering). 5345084D proves the order: it builds
Kinect masks in this format with resolves, samples them as
`k_DXT3A_AS_1_1_1_1`, and reads the same memory as `k_16_16_16_16` in a vertex
shader that culls empty rectangles by testing bit 0 of each 4-bit group. With
the reversed order every rectangle was culled. 4D53085B (lighting on the
beams near the start of the first mission) still needs a visual check.

## Copy command 2 (`kConvertTo1111`)

`RB_COPY_CONTROL.copy_command = 2` resolves a `k_8_8_8_8` (or gamma)
render target into `k_DXT3A_AS_1_1_1_1`. For each source component, the
masked value (`RB_COPY_MASK`) is compared with the same byte of
`RB_COPY_REF` using the 3-bit function for that component in
`RB_COPY_FUNC` (bits 0, 4, 8 and 12), and the result becomes that
component's bit. Destination coordinates are in 4x4 blocks of 8 bytes.

Not handled: depth sources, other source formats, array destinations and
sample averaging (logged and skipped). With resolution scaling the copy is
skipped and the clears still run; Edge has the same limitation outside its
fully native resolves. None of the three 007 titles uses copy command 2:
their logs never reported it as unsupported.

## Tests

`gpu_tests` `Copy command 2 packs one bit per component into
k_DXT3A_AS_1_1_1_1, red in bit 0` clears a target, resolves it with
Never/Always/Equal/NotEqual functions and checks each block at its tiled
address (red only gives 0x1 per pixel, alpha only 0x8). Under
`gpu.resolve_readback_scaled_3x2` it checks the destination is left alone.
