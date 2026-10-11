# Predicated tiling: window offsets in EDRAM bases

Ported from xenia-canary `e1f4a0d009` (goldislead) for #236.

## The problem

With predicated tiling a title draws the frame in tiles, moving each tile with
`PA_SC_WINDOW_OFFSET` while one depth prepass covers the whole surface.
Applying that offset through the viewport and scissor meant a later tile was
not rasterized the same way as the depth it tested against. Upstream it left
depth garbage in the bottom tile of 4D530919, 425607E5 and 5345080C.

## What changed

For a whole-tile, upward or leftward (negative) offset,
`draw_util::GetWindowOffsetTiles` returns the offset in EDRAM tiles and the
draw renders at window offset 0, with every render target and the depth
buffer's base moved by that many tiles (`AddWindowOffsetToEdramBase`, twice
the tiles for 64bpp). The viewport, scissor, draw extent estimate and the
pixel parameter generator (`param_gen_window_offset`, a system constant in
both the DXBC and SPIR-V/DXIL translators) all use the same transform.

- Guest bases are still used for aliasing and collision checks; ownership,
  transfers, dumps and ROV/FSI addressing use the moved bases.
- Host render targets are only the pitch wide, so a sideways offset stays in
  the viewport. ROV/FSI can carry both.
- A 64bpp row that lands in the next 2048-tile EDRAM addressing period gets
  its own render target (`RenderTargetKey::next_period`).
- An offset first seen kept in the viewport stays there for that surface for
  the next frame, so a title doesn't flip between the two.

`window_offset_in_edram` (default on) turns it off if tiles shift or band.

## Tests

Unit tests in `tests/unit/graphics/window_offset_edram_test.cpp` cover the
base arithmetic and wrap, which offsets move into EDRAM and which stay in the
viewport, and that the scissor stays in the tile's own space. Title checks on
the three 007 games are batched with the rest of #236.
