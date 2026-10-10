# Domain shader registers

A guest vertex shader drawn with tessellation runs as a domain shader. The
translators write the tessellator's outputs into the guest's temporary
registers before the guest code runs:

- `r0`: the domain location, and the first control point index or the patch
  index, depending on the patch type.
- `r1`: the other three control point indices (quad, control-point indexed),
  the patch index (triangle, patch indexed), or the swizzle indicator.

Upstream Xenia asserts that a domain shader has at least two registers. The
titles it was written against (4D5307F2's ground and water shaders, 58410823's
main menu) all use `r1`. The translators already handle a shader that only uses
`r0`: they write `r1` only when the shader has it. The register count is the
highest register the shader addresses plus one, so a valid domain shader that
only reads its domain location has one register, and the assertion stopped
Debug builds on it (`gpu_tests`' tessellated quad patch, whose shader reads only
`r0.yz`).

The assertions were removed in both translators, and the SPIR-V translator's
quad control-point-indexed path now writes `r1` only when the shader has it, as
the DXBC translator's does. Before that it wrote past the end of the register
array for a one-register shader. Shaders with two or more registers translate as
before.
