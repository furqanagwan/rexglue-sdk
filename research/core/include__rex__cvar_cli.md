# Cvar cli: core source notes

This record preserves technical and API notes moved from `include/rex/cvar_cli.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/cvar_cli.h#L25)

```text
/**
 * Adds a "--<name>" option for every registered flag to `app`. Boolean flags
 * also gain a "--no-<name>" form. Values go through the same validation as
 * SetFlagByName and are recorded as Source::kCommandLine.
 *
 * Call after all cvars have registered and before parsing. Set
 * `app.fallthrough()` beforehand if the tool uses subcommands and should accept
 * overrides spelled after the subcommand name.
 */
```
