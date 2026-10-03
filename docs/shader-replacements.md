# Shader replacements (RG-GDK-067)

Some guest shaders misbehave on a PC GPU or when the game is upscaled: UI
lines and text that land between pixels, a viewport shifted by half a pixel, a
bloom or downsample pass that assumes the console's resolution. Microsoft's
PC backward compatibility (`VGPUDX12.dll`) ships hand-written replacements for
such shaders, named per title (`Kotor_UIVertexShader`,
`SWON_ShiftViewportPixelShader`, ...). A rexglue title can do the same: it
names a guest shader by its ucode hash and ships a host shader to use instead
of the translated one. Shaders without a replacement are translated as usual.

## Writing one

1. Find the shader. Run the title with `--dump_shaders=<folder>`. Each
   translated shader is written as `shader_<HASH>_<MOD>.<path>.bin.<vert|frag>`
   (the DXBC) and the same name without `.bin` (its disassembly), where
   `<HASH>` is the guest ucode hash, `<MOD>` the translator modification and
   `<path>` `d3d12` for vertex shaders, `d3d12_rtv` or `d3d12_rov` for pixel
   shaders. A PIX capture of the broken frame shows which draw uses it.
2. Write the replacement in HLSL (entry point `main`, shader model 5.1),
   starting from the disassembly. **Keep the translated shader's interface**:
   the same constant buffers, textures, samplers and their registers, and the
   same inputs and outputs. The translation still decides the bindings and the
   pipeline's root signature; only the code is replaced. A pixel shader can
   leave out inputs it doesn't read.
3. Name it `<HASH>[_<MOD>].<stage>.hlsl`, both in 16 hex digits, with stage
   `vs` (vertex shaders; tessellation domain variants are never replaced),
   `ps_rtv` or `ps_rov` (the two render target paths translate pixel shaders
   differently, so a replacement is for one of them). Without `_<MOD>` it
   stands in for every modification of that shader; with it, only that one,
   and it wins over the general one.
4. Put the files in the title project's `shader_replacements` folder and add
   `SHADER_REPLACEMENTS shader_replacements` to `rexglue_configure_target`.
   The build compiles each `.hlsl` with FXC (Windows SDK), copies any `.dxbc`
   of the same naming as it is, stages them in `shader_replacements\` beside
   the executable, and turns on `shader_replacements` as the title's default.

At startup the log says how many replacements were read; each one used logs
`Shader <HASH> (modification <MOD>): title replacement used`. A badly named
or non-DXBC file is skipped with a warning.

- **Opt-in by name.** The `shader_replacements` cvar (GPU, default off, needs a
  restart) is a title default set by `SHADER_REPLACEMENTS`, under the
  player's config and command line, so `--shader_replacements=false` turns them
  off to compare (ADR-009 by-name opt-in; it becomes a fix catalog entry when
  the catalog exists).
- **Not game material, if hand-written.** HLSL the title's author wrote may be
  kept in the title repository ([title repository standard](title-repo-standard.md)).
  DXBC or disassembly dumped from the game is the game's shader and stays
  local, like the shipped [shader cache](shader-cache.md).
- **After an SDK update** a changed translator can change a shader's interface
  or modification bits; check the log line for each replacement.

Tests: `tests/unit/graphics/shader_replacements_test.cpp` (names, exact and
general matching, fallback, loading) and
`tests/gpu/shader_replacement_fixture_test.cpp` (a replacement pixel shader
reaches the GPU: the draw comes out in the replacement's color).
