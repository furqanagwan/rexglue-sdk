# Xenos MSAA sample positions

Ported from xenia-canary `cc4981a465` (goldislead) for #236.

## Positions

Xenos places MSAA samples differently from the Direct3D 10 standard pattern,
in 1/16-pixel units:

| Samples | Xenos | D3D10 standard |
| --- | --- | --- |
| 2x | (-4, 4), (4, -4) | (4, 4), (-4, -4) |
| 4x | (-2, -2), (2, 2), (-6, 6), (6, -6) | (-2, -6), (6, -2), (-6, 2), (2, 6) |

Tiled MSAA titles such as 4D5307D5 resolve sample 0 of depth and test against
it again; Unreal Engine 3 offsets the viewport to line that sample up with
non-MSAA depth. With the host's standard positions the retest missed and the
shading disappeared.

## What ReXGlue does

- **ROV (DXBC) and FSI (SPIR-V/DXIL):** always. Coverage comes from the host
  sample nearest each Xenos position (4x swaps host samples 1 and 3; 2x drawn
  as 4x takes host samples 2 and 1), and depth is extrapolated to the Xenos
  positions. With programmable sample positions the ROV path also sets them.
- **Host render targets:** only with `xenos_sample_positions` (off by
  default, as upstream) and a device with programmable sample positions
  (`D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_1` or higher). Depth clears,
  transfers and render target transitions then use the same positions, and
  multisampled depth is decompressed (`ResolveSubresourceRegion`,
  `D3D12_RESOLVE_MODE_DECOMPRESS`) before a shader reads it.
- **Resolution scaling:** only the whole-pixel part of a viewport offset that
  lands on a Xenos sample is scaled; the sample offset stays in host pixels,
  because programmed positions don't scale.

NVIDIA and AMD default to host render targets with the setting off, so their
default rendering is unchanged; Intel defaults to ROV.

## Tests

Unit tests in `tests/unit/graphics/xenos_sample_positions_test.cpp` cover the
host sample order for each mode and the scaled viewport offset. The GPU
fixture suite passed 59/59 under `render_target_path_d3d12=rov` and under
`xenos_sample_positions=true` on an RTX 5080 (positions tier 2). Title checks
on the three 007 games are batched with the rest of #236.
