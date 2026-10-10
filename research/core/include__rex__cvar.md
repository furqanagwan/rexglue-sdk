# Cvar: core source notes

This record preserves technical and API notes moved from `include/rex/cvar.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L119)

```text
// Initialization API
```

## Source note 2, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L128)

```text
// As SaveConfig, reporting a write/flush failure to interactive callers.
```

## Source note 3, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L132)

```text
// Flag Registry
```

## Source note 4, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L137)

```text
// Lifecycle: when can this flag be modified?
```

## Source note 5, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L139)

```text
// Can only be set during initialization (before FinalizeInit)
```

## Source note 6, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L140)

```text
// Can be changed at runtime with immediate effect
```

## Source note 7, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L141)

```text
// Can be changed, but only takes effect after restart
```

## Source note 8, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L144)

```text
// Where a flag's current value came from, in ascending priority. A source
```

## Source note 9, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L145)

```text
// never overwrites a value a higher-priority source already set.
```

## Source note 10, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L147)

```text
// Compiled-in default
```

## Source note 11, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L148)

```text
// TOML config file
```

## Source note 12, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L149)

```text
// REX_* environment variable
```

## Source note 13, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L150)

```text
// --flag on the command line
```

## Source note 14, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L151)

```text
// SetFlagByName from the console, settings UI, or code
```

## Source note 15, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L154)

```text
// Validation constraints
```

## Source note 16, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L178)

```text
// What SaveConfig writes for this flag: the config file's value (even when a
```

## Source note 17, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L179)

```text
// higher source overrides it for this run), replaced by a runtime change.
```

## Source note 18, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L180)

```text
// Environment and command-line values are for one run and never saved.
```

## Source note 19, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L186)

```text
/**
 * Returns the registered entry's index, or nullopt if the name was already
 * registered (logged at ERROR).
 */
```

## Source note 20, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L192)

```text
/**
 * Removes a flag from the registry. Used by `FlagRegistrar`'s destructor so
 * that DLL unload tears down the lambdas captured in each FlagEntry.
 */
```

## Source note 21, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L200)

```text
// A title's own default for a flag (rexglue_configure_target CVAR_DEFAULTS):
```

## Source note 22, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L201)

```text
// replaces the compiled-in default, so the config file, environment, command
```

## Source note 23, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L202)

```text
// line and runtime changes still win and SaveConfig does not write it. False
```

## Source note 24, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L203)

```text
// when the flag is unknown or the value is rejected.
```

## Source note 25, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L206)

```text
// Applies a value parsed off the command line. Returns false only when the
```

## Source note 26, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L207)

```text
// value is rejected (unparseable, or outside the flag's constraints); a value
```

## Source note 27, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L208)

```text
// skipped because a higher-priority source already won returns true.
```

## Source note 28, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L213)

```text
// Which source last wrote this flag. Returns Source::kDefault for unknown names.
```

## Source note 29, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L216)

```text
// Invoke a registered command by name, passing the raw argument text.
```

## Source note 30, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L217)

```text
// Returns false if `name` is not registered or is not a FlagType::Command.
```

## Source note 31, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L220)

```text
// Typed registry query. Cross-DLL access path that does not require linking
```

## Source note 32, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L221)

```text
// the DLL where the cvar is defined. Slower than REXCVAR_GET (string parse +
```

## Source note 33, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L222)

```text
// hash lookup), so prefer REXCVAR_GET when the defining DLL is already on the
```

## Source note 34, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L223)

```text
// link line. Returns a value-initialized T when the cvar is missing or its
```

## Source note 35, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L224)

```text
// stored string fails to parse.
```

## Source note 36, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L256)

```text
/// Callback invoked when a CVAR value changes
```

## Source note 37, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L257)

```text
/// @param name The CVAR name
```

## Source note 38, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L258)

```text
/// @param new_value The new value as a string
```

## Source note 39, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L261)

```text
/// Register a callback to be invoked when a specific CVAR changes
```

## Source note 40, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L264)

```text
/// Unregister all callbacks for a specific CVAR
```

## Source note 41, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L267)

```text
/**
 * RAII handle for a registered flag. Destructor unregisters by name; on
 * duplicate-name registration `owned_name_` is empty so chain methods and
 * the destructor become no-ops and the original owner's entry is untouched.
 */
```

## Source note 42, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L273)

```text
// empty when registration was rejected
```

## Source note 43, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L292)

```text
// Chain methods mutate the registered entry by name lookup.
```

## Source note 44, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L324)

```text
// Non-copyable (prevent double registration)
```

## Source note 45, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L345)

```text
// CVar Macros
```

## Source note 46, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L348)

```text
// Declare a cvar (use in headers and TUs that need to read it).
```

## Source note 47, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L349)

```text
// The accessor function returns a reference to the cvar's storage. Storage
```

## Source note 48, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L350)

```text
// lives as a static-local inside whichever DLL contains the matching
```

## Source note 49, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L351)

```text
// REXCVAR_DEFINE_*. Cross-DLL access goes through the import lib.
```

## Source note 50, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L354)

```text
// Get a cvar value
```

## Source note 51, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L357)

```text
// Set a cvar value
```

## Source note 52, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L360)

```text
// Cross-module typed query that goes through the cvar registry by name.
```

## Source note 53, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L361)

```text
// Use this when the defining DLL is not on the consumer's link line (e.g.,
```

## Source note 54, line 362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L362)

```text
// across one-way subsystem dependencies where adding the reverse link would
```

## Source note 55, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L363)

```text
// create a cycle). Slower than REXCVAR_GET; prefer REXCVAR_GET when possible.
```

## Source note 56, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L366)

```text
// Define cvars (use in one .cpp file per cvar)
```

## Source note 57, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L367)

```text
// The FlagRegistrar registers the flag in its destructor, allowing method chaining.
```

## Source note 58, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L557)

```text
// Define an argument-taking command. `callback` is convertible to
```

## Source note 59, line 558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L558)

```text
// std::function<void(std::string_view args)>; the console passes the text
```

## Source note 60, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar.h#L559)

```text
// after the command name as `args`.
```
