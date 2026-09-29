# Guest code patches

A title's codegen config can change guest instructions before they are
recompiled. This is how a community patch, such as one from Xenia Canary's
[game-patches](https://github.com/xenia-canary/game-patches) repository,
reaches a recompiled title. It follows
[ADR-009](adr/ADR-009-title-compatibility-profiles.md) section 7: code changes
live in the codegen config and are compiled in, never applied at runtime.

## Format

The entry has the same shape as a Canary `.patch.toml` entry, so one can be
copied across:

```toml
[[patch]]
name = "Unlock FPS"
enabled = false            # Canary's is_enabled is accepted too; default true
[[patch.be32]]
address = 0x8229B808
value = 0x60000000         # nop
[[patch.be8]]
address = 0x820F2283
value = 0x01
```

- `be8`, `be16`, `be32` and `be64` write a big-endian value of that width.
- Patches are keyed by `name`. A later file with the same name replaces the
  writes it lists and the `enabled` flag it sets. A title config can therefore
  ship a patch switched off, and a small file that includes it turns it on:

  ```toml
  includes = ["title.toml"]
  [[patch]]
  name = "Unlock FPS"
  enabled = true
  ```

## Rules

- **Code only.** Every write must lie inside one executable section. The
  running title loads the original image into guest memory, so a patch to
  data would never be seen; codegen refuses it.
- **Checked before anything is written.** A malformed enabled patch, one that
  reaches outside the code, or two enabled patches writing the same byte stop
  codegen with an error naming the patch. Disabled patches are not checked.
- **Applied first.** Patches are written into codegen's copy of the image
  before instructions are decoded, so discovery, analysis and the generated
  C++ all see the patched code. The XEX on disk is never changed.
- **Recorded.** Codegen logs each patch as applied or disabled. The names are
  compiled into the title (`PPCImageInfo::code_patches`) and logged at startup
  as `Guest code patches compiled in: ...`. Changing a patch changes the config,
  which regenerates the code.

A patch is title-specific behavior (ADR-005). It belongs in the title's own
repository and config, never in the SDK. Record where it came from, its author
and any known problems next to it, as Canary does.

## Tests

`unit_tests [codegen][patch]`: widths and byte order, Canary's `is_enabled`,
bad entries, an including file switching a patch on, writes into code only,
refusals for data, out-of-image and past-the-section writes, overlaps, and
patching before decoding.
