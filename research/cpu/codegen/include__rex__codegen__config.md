# Config: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/config.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L24)

```text
// For JumpTable
```

## Source note 2, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L43)

```text
// Unified function/chunk configuration
```

## Source note 3, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L44)

```text
// A "chunk" is simply a function entry with a non-zero parent field
```

## Source note 4, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L46)

```text
// Explicit size in bytes (mutually exclusive with end)
```

## Source note 5, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L47)

```text
// End address, exclusive (mutually exclusive with size)
```

## Source note 6, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L48)

```text
// Custom symbol name (empty = auto-generate sub_XXXXXXXX)
```

## Source note 7, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L49)

```text
// Parent function address (0 = standalone, non-zero = chunk)
```

## Source note 8, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L51)

```text
// Keep non-volatiles in ctx instead of localizing them. Marks an MSVC SEH
```

## Source note 9, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L52)

```text
// funclet, which reads the registers its owner left live and would see a zero
```

## Source note 10, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L53)

```text
// from a local. Callers sync their localized copies across the call site.
```

## Source note 11, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L56)

```text
// Get effective size (prefers size over end)
```

## Source note 12, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L60)

```text
// Returns true if this is a discontinuous chunk belonging to a parent function
```

## Source note 13, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L64)

```text
// One big-endian write of a code patch.
```

## Source note 14, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L67)

```text
///< Written in order starting at `address`
```

## Source note 15, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L70)

```text
// A register a switchable patch sets just before the instruction at
```

## Source note 16, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L71)

```text
// `address` runs, as a trainer's detour does: [[patch.set]] with address,
```

## Source note 17, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L72)

```text
// register ("r0".."r31"), value and, optionally, lr (only when the link
```

## Source note 18, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L73)

```text
// register holds that return address, i.e. that call was the last made).
```

## Source note 19, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L81)

```text
// A named guest code patch applied to the image before analysis (ADR-009
```

## Source note 20, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L82)

```text
// section 7). Written in the same shape as a Canary game-patches entry, so a
```

## Source note 21, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L83)

```text
// community patch copies over: [[patch]] with name, enabled and
```

## Source note 22, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L84)

```text
// [[patch.be8]] / be16 / be32 / be64 tables of address and value.
```

## Source note 23, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L88)

```text
/// Compiled with both instruction versions behind a runtime flag, so the
```

## Source note 24, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L89)

```text
/// player can switch it while the title runs; `enabled` is the default.
```

## Source note 25, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L91)

```text
/// How the guide lists a switchable patch: "patch" (fixes, frame rate) or
```

## Source note 26, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L92)

```text
/// "mod" (changes to play, such as a trainer's infinite ammo). "cheat",
```

## Source note 27, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L93)

```text
/// the earlier name for "mod", is read as "mod".
```

## Source note 28, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L96)

```text
///< Switchable patches only
```

## Source note 29, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L97)

```text
///< Config file that last defined the writes
```

## Source note 30, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L98)

```text
///< Why the entry is unusable; applying it fails
```

## Source note 31, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L101)

```text
// A cheat the title's developers built in: a code the game's own menu takes.
```

## Source note 32, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L102)

```text
// Nothing is patched; the guide's Cheats page lists them so a player need not
```

## Source note 33, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L103)

```text
// look them up. [[cheat]] with name, code, description and where.
```

## Source note 34, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L107)

```text
///< What it unlocks
```

## Source note 35, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L108)

```text
///< Where the game takes the code
```

## Source note 36, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L111)

```text
// An add-on the title had in the Xbox 360 marketplace, for the guide's Manage
```

## Source note 37, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L112)

```text
// Game page. [[dlc]] with the marketplace media ID (id), and optionally the
```

## Source note 38, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L113)

```text
// title update the add-on needs (requires_title_update, its version) and the
```

## Source note 39, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L114)

```text
// display name in its package when the catalogue's title differs (package_name).
```

## Source note 40, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L115)

```text
// `rexglue dlc-find <title ID>` prints a title's entries.
```

## Source note 41, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L119)

```text
///< 0: none
```

## Source note 42, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L122)

```text
// A title update the title had, for the guide's Title Updates page, where the
```

## Source note 43, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L123)

```text
// player can download and turn it on (an update is always optional).
```

## Source note 44, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L124)

```text
// [[title_update]] with version, media_id, base_version and content_id (Xbox
```

## Source note 45, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L125)

```text
// Unity's "hash": the package's STFS content ID), optionally size_kb, date and
```

## Source note 46, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L126)

```text
// changelog. The update runs only in a build that has its executable (a
```

## Source note 47, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L127)

```text
// manifest [[title_update]]).
```

## Source note 48, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L138)

```text
// Section info for analysis output
```

## Source note 49, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L143)

```text
// "rx", "rw", "r" etc.
```

## Source note 50, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L146)

```text
// Function entry for analysis output
```

## Source note 51, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L150)

```text
// optional, defaults to "sub_XXXXXXXX"
```

## Source note 52, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L154)

```text
// === Required user-provided fields ===
```

## Source note 53, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L155)

```text
///< Project name for output files
```

## Source note 54, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L156)

```text
///< Path to XEX/ELF file
```

## Source note 55, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L157)

```text
///< Output directory for generated code
```

## Source note 56, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L158)

```text
///< Optional custom template directory for overrides
```

## Source note 57, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L160)

```text
/// Every TOML that fed this config, in load order. LoadFromTable() gets a
```

## Source note 58, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L161)

```text
/// parsed table, so a manifest-embedded entry omits the manifest itself.
```

## Source note 59, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L164)

```text
// === Code generation options (optional) ===
```

## Source note 60, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L173)

```text
///< Generate SEH exception handler wrappers
```

## Source note 61, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L175)

```text
// === Analysis tuning (optional) ===
```

## Source note 62, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L176)

```text
///< Max bytes to extend function for jump table targets
```

## Source note 63, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L177)

```text
///< Consecutive invalid instructions to mark as data region
```

## Source note 64, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L178)

```text
///< 1MB - warn if function exceeds this size
```

## Source note 65, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L180)

```text
// Optional override for DLL module flag. If unset, the orchestrator infers
```

## Source note 66, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L181)

```text
// from the module's position in the manifest (entrypoint = false, modules = true).
```

## Source note 67, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L184)

```text
/// The title update this executable is built for (a manifest
```

## Source note 68, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L185)

```text
/// [[title_update]]); 0 for the original. Compiled into PPCImageInfo.
```

## Source note 69, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L188)

```text
// === Manual overrides ===
```

## Source note 70, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L189)

```text
///< Function/chunk configuration
```

## Source note 71, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L192)

```text
/// Guest code patches in definition order, keyed by name: a later file with
```

## Source note 72, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L193)

```text
/// the same name replaces the writes it lists and the enabled flag it sets.
```

## Source note 73, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L195)

```text
/// The title's own cheat codes, in definition order, keyed by name.
```

## Source note 74, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L197)

```text
/// The title's add-ons, in definition order, keyed by id.
```

## Source note 75, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L199)

```text
/// The title's updates, in definition order, keyed by version.
```

## Source note 76, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L203)

```text
// Analysis-only guard for the recognized CRT's optional setjmp hook.
```

## Source note 77, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L206)

```text
// === rexcrt: CRT function address overrides ===
```

## Source note 78, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L207)

```text
// Maps function name -> guest address (e.g. "CreateFileA" -> 0x8248B780)
```

## Source note 79, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L208)

```text
// Parsed from [rexcrt] TOML table. Codegen generates rexcrt_<Name> entries.
```

## Source note 80, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L211)

```text
// === User hints (merged with analysis results in AnalysisState) ===
```

## Source note 81, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L212)

```text
///< addr -> size
```

## Source note 82, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L214)

```text
///< bctr addresses that are vtable/computed calls
```

## Source note 83, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L215)

```text
///< Additional exception handler addresses
```

## Source note 84, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L217)

```text
/**
   * Load configuration from a TOML file.
   *
   * Supports an optional `includes` array for layered config. Paths in
   * `includes` resolve relative to the including file's directory.  Merge
   * semantics: scalars last-wins, keyed tables additive (same key = last
   * wins), arrays-of-tables deduplicated by primary key, sets additive.
   *
   * @param configFilePath Path to the TOML config file
   * @return true on success, false on error (parse failure, circular
   *         include, depth exceeded)
   */
```

## Source note 85, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L231)

```text
/**
   * Load configuration from an in-memory TOML table (e.g. an inline binary
   * entry inside a manifest). Includes referenced from the table resolve
   * relative to `base_dir`. Same merge semantics as Load().
   */
```

## Source note 86, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L238)

```text
/// Validation result containing warnings and errors.
```

## Source note 87, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L240)

```text
///< true if no errors (warnings OK)
```

## Source note 88, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L241)

```text
///< Non-fatal issues
```

## Source note 89, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L242)

```text
///< Fatal issues that block codegen
```

## Source note 90, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/config.h#L247)

```text
/**
   * Validate the loaded configuration.
   * Checks address alignment, required fields, and sanity constraints.
   * @return ValidationResult with warnings and errors
   */
```
