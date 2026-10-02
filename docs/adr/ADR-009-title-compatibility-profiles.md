# ADR-009: Title compatibility profiles — a fix catalog and per-title profiles, no database

Status: **Accepted design; implementation deferred until a title needs it** (RG-GDK-013). Date: 2026-09-27. First step 2026-10-02 (RG-GDK-069): titles can set cvar defaults by name, `rexglue_configure_target(<target> CVAR_DEFAULTS "name=value" ...)`, applied with `rex::cvar::SetTitleDefault` beneath the config file, environment and command line; NHL Legacy Edition uses it for `render_target_path_d3d12=rov`. The fix catalog itself is still to come. Implements the mechanism ADR-005 left pending; ADR-005's policy is unchanged.

## Context

Xenia Canary and Edge adapt to individual games with per-title config files
and hash-filtered patch lists. Three problems show up there:

- **The same workaround is copied into many title configs** and never becomes
  a general fix, even when it is one.
- **Title settings leak into global settings.** Canary PR
  [#844](https://github.com/xenia-canary/xenia-canary/pull/844) (open, head
  `16c13ed6`) exists because saving the config while a game-specific config is
  loaded writes the game's values into the base config.
- **A profile can match the wrong executable**, and a runtime byte patch does
  not change code that was already compiled.

ReXGlue differs from those emulators in ways that make the problem smaller:

- **Each recompiled title is its own project and executable.** There is no
  shared emulator binary that has to recognise thousands of games at startup.
- **Guest code patches already happen before code generation.** Mid-asm hooks,
  function overrides and jump-table hints live in the title's codegen config.
  The codegen stamp fingerprints the XEX and every config input, so a changed
  input regenerates the C++.
- **Runtime behaviour is already selected by cvars** with a source ranking
  (default < config < environment < command line < runtime).

Inventory, 2026-09-27:

| Source | Title-specific runtime overrides needed |
| --- | --- |
| Quantum of Solace (the only local title), 79 recorded runs, standard and GDK native builds | **None.** It runs on SDK defaults. Its only title setting is build-time (`GPU_PLUGINS xenos`). |
| SDK source (`src/`) | **None.** There are no title-ID branches. |
| Pre-codegen patches | Title codegen config, bound by the codegen fingerprint |

The cvar layer also has a leak of the same kind as #844 today: `SaveConfig`
(used by the settings overlay) writes every non-default value, whatever its
source. So a `--gpu_plugin=xenos` given on the command line ends up in the
user's config file.

## Decision

### 1. No compatibility database

The SDK ships no central list of titles. A title's profile lives in that
title's project, next to its codegen config, and is compiled into its
executable. A database would only earn its cost for a shared binary running
unknown games, and ReXGlue does not have one.

### 2. Fixes live in an SDK catalog; profiles only refer to them

Every behaviour a title can opt into is a **fix**: a named entry in one SDK
catalog (an X-macro list, `fixes.inc` in a new `rex/compat` include
directory when implemented). Each entry has:

| Field | Meaning |
| --- | --- |
| `name` | Stable identifier, e.g. `readback_resolve_full` |
| `kind` | `title`, `driver` or `experimental` (ADR-005's categories) |
| `effect` | cvar values it sets, or a code switch read with `rex::compat::IsActive(Fix::k...)` |
| `lifecycle` | `init` (only at startup) or `live` |
| `provenance` | Upstream PR/issue/commit, or the local reproduction |
| `test` | The test that shows the fix and would fail without it |
| `owner`, `review` | Who owns it and when to revisit or remove it |

- **Code never branches on a title ID.** It asks whether a fix is active.
- **A fix is written, reviewed and tested once.** Every title that needs it
  refers to it by name, so the fifth title to need a fix adds one line, not a
  fifth copy.
- **Driver fixes are selected by adapter**, never by title. They key on the
  DXGI vendor, device and driver version already logged at startup (for
  example the Intel non-Arc stencil path, Canary #608).

### 3. A profile binds to exact modules and lists fixes

A profile is TOML in the title project (`<title>_compat.toml`). It is checked
against [compat-profile.schema.json](../compat-profile.schema.json) and the
fix catalog at build time, then embedded in the executable. Nothing extra is
deployed, so `makepkg` packages it with the title and it can't be separated
from the build it was tested with.

```toml
schema_version = 1

[[module]]
title_id = "415607FF"
xex_sha256 = "…"                # the exact default.xex this build was generated from
version = "1.0"                 # informational
fixes = ["readback_resolve_full"]

[fix.readback_resolve_full]     # why this title needs it
evidence = "baseline run rg0xx-qos-…; resolve readback test …"
added = "2026-09-27"
```

- **Binding.** A module's profile applies only when the running module's title
  ID **and** XEX SHA-256 both match. Otherwise nothing from the profile
  applies, and the mismatch is reported (fail closed). A title update or a
  different disc revision is a different module and needs its own entry.
- **Other modules.** A static project contains all of its modules, so each
  module has its own entry. When `XamLoaderLaunchTitle` switches module, the
  profile is evaluated again. A fix with `lifecycle = "init"` cannot change
  after startup: it applies to the entry module only, and a switch that would
  change it is logged as needing a restart, not applied halfway.

### 4. Precedence, and what is saved

Profile values become a new cvar source between the compiled default and the
user's config:

`default < profile < config file < environment < command line < runtime`

The user always wins: a value the user sets is used and logged as
overriding the profile. `SaveConfig` writes only values whose source is
`config` or `runtime`. Profile, environment and command-line values are never
saved, which rules out the #844 leak and also fixes the command-line leak
above.

### 5. Conflicts are build errors

- **Two fixes in one profile setting the same cvar to different values**:
  `rexglue` rejects the profile at build time.
- **An unknown fix name or key**: build error.
- **A fix whose effect changes in a new SDK**: the catalog entry is versioned,
  and the build reports profiles that refer to an older version.

### 6. Promotion and demotion

A fix is expected to leave the catalog:

| Stage | Applies to | Moves on when |
| --- | --- | --- |
| `title` or `experimental` | Titles whose profile lists it | It is confirmed on 2–3 unrelated titles **and** the root cause is understood |
| Default on | Every title; a profile can opt out with `disable = ["name"]` | The regression baseline (ADR-006) shows no title got worse |
| Removed | Everyone, as ordinary correct behaviour | It matches console behaviour |

Demotion is the same in reverse. A fix that breaks a title is disabled in that
title's profile, and the regression record says why. Each promotion or
demotion is a PR that updates the catalog entry and `docs/upstream-tracking.md`.

### 7. Pre-codegen patches stay separate

Guest code changes (mid-asm hooks, function overrides, instruction or data
hints, and `[[patch]]` byte patches of code, see [code patches](../code-patches.md))
stay in the codegen config. They are not in the profile, because a
runtime layer cannot change compiled C++. The codegen fingerprint already binds
them to the XEX. Runtime byte patches of guest code are not supported at all
(ADR-004).

### 8. Debugging with Windows and GDK tools

| Where | What it shows |
| --- | --- |
| Log, at startup and on a module switch | One line per module: title ID, XEX hash, profile matched or why not. One line per fix: active, disabled, overridden by the user, or needs a restart. |
| `--compat_report` | Prints that table and exits |
| TraceLogging (Windows SDK, no dependency) | Provider `ReXGlue.Compat`, events `ProfileEvaluated` and `FixState`. Record with WPR, read in WPA or PIX timing captures alongside CPU and GPU data. |
| PIX GPU captures | A queue marker `Compat: <fixes>` on the first submission (RG-GDK-028 markers), so a capture says which fixes were active |
| Crash and bug reports | The log's startup lines above precede everything else |

**Kill switches:**

- `--compat_profile=off` turns off the whole profile.
- `--compat_disable=a,b` turns off listed fixes.
- `--compat_enable=a` tries a fix on a title that does not list it. The run is
  logged as experimental.

`MicrosoftGame.config` is not used for profiles. Its schema is fixed, and its
identity is the PC package's, not the Xbox 360 module's.

## Design examples (the issue's required cases)

| Case | Outcome |
| --- | --- |
| Profile with an unknown fix or key | `rexglue` rejects it at build time; the title does not build |
| Right title ID, different XEX hash (title update, other disc) | Profile not applied; logged `profile 415607FF: xex hash mismatch, running on defaults`; a TraceLogging `ProfileEvaluated` event carries both hashes |
| `fix a` and `fix b` both set `readback_resolve`, to different values | Build error naming both fixes |
| Profile sets `readback_resolve=full`, the user's config sets `fast` | `fast` is used; logged `readback_resolve_full: overridden by user config` |
| Settings overlay saves while a profile is active | Only `config` and `runtime` values are written; the profile's values never reach the user's config |
| Title switches module; the new module's profile has an `init` fix the old one lacked | Not applied; logged as needing a restart; `live` fixes switch over |
| `--compat_profile=off` | Every fix inactive; the report shows the profile as disabled by the command line |
| A fix is promoted to default on | Its catalog entry changes; profiles listing it get a build note that the entry is redundant; titles that opted out keep opting out |

## Negative test plan (for the implementation)

Each rule gets a test that fails if the rule is broken:

1. **Isolation.** A synthetic profile for title A; run modules of title A and
   title B in one test. B's cvars and fix states must equal the defaults
   exactly.
2. **Hash binding.** Same title ID, one byte changed in the module: nothing is
   applied and the mismatch is reported.
3. **No persistence.** Apply a profile, change an unrelated setting, and call
   `SaveConfig`. The file must contain only that setting. The same test covers
   command-line and environment values, which is today's leak.
4. **Precedence.** For each higher source, a user value beats the profile and
   is reported as an override.
5. **Build-time rejection.** Unknown fix, unknown key, conflicting fixes, and
   an unsupported `schema_version` each fail `rexglue` validation with a named
   error.
6. **Disable and removal.** `--compat_profile=off` and `--compat_disable`
   leave no fix active. Removing a fix from the catalog makes every profile
   that lists it fail to build, so a removal is never silent.
7. **Module switch.** `init` fixes do not change after startup; `live` fixes
   follow the module.
8. **No title branches.** A source check fails the build when `src/` compares
   against a title-ID literal outside the compat module.

## Rejected alternatives

- **A central title database in the SDK** (Canary's `game-patches` style). It
  couples every title to every other title's entries, needs lookups for
  titles a static executable never runs, and invites copying.
- **Per-title cvar files loaded at runtime** (Canary/Edge `config/<title>.toml`).
  These are the source of the #844 leak. They can go missing or not match the
  build, and there is no catalog to promote from.
- **Heuristic auto-detection** ("enable when a title behaves like X"). It
  silently changes titles nobody tested, which ADR-005 forbids.
- **Runtime byte patches of guest code.** They don't reach the generated C++
  (ADR-004); code changes belong in the codegen config.
- **Profiles in `MicrosoftGame.config`.** Its schema is fixed and validated by
  `makepkg`, and it describes the PC package, not the guest module.

## Implementation gate

Implementation starts when the first title needs a runtime override that
cannot be a general fix. That needs a local reproduction and a failing test.
Until then:

- **The catalog is empty**, and nothing loads profiles.
- **The `SaveConfig` persistence rule (§4) is the exception, and is done**
  (2026-09-27). Each cvar records the value to save: the config file's value
  (kept even when the command line overrides it for a run) or a runtime
  change. Config keys for cvars that never registered are kept too. Tests:
  `unit_tests [cvar][save]`.
- **The schema is published** as [compat-profile.schema.json](../compat-profile.schema.json)
  and checked by `scripts/tests`.

## Validation and follow-up

RG-GDK-013 (this design), ADR-004, ADR-005, ADR-006. Pending upstream
reference: Canary #844.
