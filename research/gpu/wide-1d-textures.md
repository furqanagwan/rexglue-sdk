# Wide 1D textures

Xenos 1D textures can be up to 2^24 texels wide (`kTexture1DMaxWidth`).
Direct3D 12 2D textures stop at 16,384 texels, and ReXGlue stores 1D textures
as 2D arrays, so anything wider than 8,192 texels used to be dropped with "1D
texture is too wide". Titles that use them for lookup tables (5345084D's
decision trees, 555308CE) then read black.

## How it works

- **Texture cache** (`src/graphics/pipeline/texture/cache.cpp`): a 1D fetch
  constant wider than 8,192 texels becomes a 2D texture of 8,192-texel rows
  (`texture_util::GetWide1DTextureLayout`), with no mips and a row pitch of
  8,192 texels. 1D textures are always linear, so the rows are contiguous in
  guest memory.
- **Row cap**: at most `kTexture1DWideMaxRows` (128) rows are made. Some
  titles declare widths far larger than the data behind them. 5345084D's
  786,432-texel table needs 96 rows.
- **Shaders**: a 1D fetch checks at runtime whether its fetch constant is 1D
  and wider than 8,192 texels. If so, it turns the texel coordinate (from the
  original operand, not the normalized one, which loses precision at widths
  near 2^24) into a column and a row, and samples the row's centre. The DXBC
  translator does this in `EmitWide1DTextureCoordinates`, and the SPIR-V
  translator inline in `spirv_translator_fetch.cpp`.
- **Promoted fetches**: a `tfetch1D` whose source swizzle gives XY (see
  [shader operand components](shader-operand-components.md)) is fetched as
  2D, but its fetch constant can still be 1D. Its size is then picked at
  runtime from the 1D or 2D fields, and a wide 1D constant still takes the
  row mapping. Such fetches don't snap to texel centres for point sampling,
  matching Edge, because the snap would overwrite the row.
- **Gradients**: unchanged. Wide textures have no mips, so their LOD doesn't
  matter.

## Source

has207/xenia-edge `947075f880` ("Implement wide 1D texture support",
2026-08-04), `7cd47947b0` ("Select promoted tfetch1D layouts at runtime",
2026-08-18) and `6260a87b85` ("Fix fetching from wide 1D textures at large
coordinates", 2026-10-03, which also raised the row cap to 128). Not taken:
Edge's change to two gradient components and ignoring register gradients for
1D fetches. Its final code zeroes the Y gradient anyway, and the register
gradient change would alter ordinary 1D fetches.

## Tests

- `tests/gpu/wide_1d_texture_fixture_test.cpp`: a 20,000-texel texture with
  a different value in each row, sampled at row edges by a plain and a
  promoted `tfetch1D`, on DXBC and under `gpu.dxil_parity`; and an 8,192-texel
  texture fetched as before. Without the texture cache change, all 14 wide
  samples fail.
- `tests/unit/graphics/texture_layout_test.cpp`: the row mapping, the row cap
  and the guest layout of a wide texture.
