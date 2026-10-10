# Console overlay: ui source notes

This record preserves technical and API notes moved from `src/ui/overlay/console_overlay.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L36)

```text
// New category discovered - enable by default.
```

## Source note 2, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L62)

```text
// Complete the command/cvar name only (the first token). Once a space is
```

## Source note 3, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L63)

```text
// typed the user is editing arguments, so close the popup.
```

## Source note 4, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L96)

```text
// Longest common prefix of all candidates.
```

## Source note 5, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L117)

```text
// When the completion popup is open, arrows move the selection.
```

## Source note 6, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L127)

```text
// Otherwise: command history.
```

## Source note 7, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L150)

```text
// Tag with the current sink generation so the draw pass can interleave this
```

## Source note 8, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L151)

```text
// console-local line chronologically with the captured log entries.
```

## Source note 9, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L157)

```text
// Trim whitespace.
```

## Source note 10, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L165)

```text
// Record in history.
```

## Source note 11, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L186)

```text
// Split on first space into name + args.
```

## Source note 12, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L199)

```text
// Command dispatch takes priority over get/set. Echo before invoking so the
```

## Source note 13, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L200)

```text
// "> cmd" line is tagged with an earlier generation than any log lines the
```

## Source note 14, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L201)

```text
// command emits, keeping it just above its own output.
```

## Source note 15, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L210)

```text
// No args: treat as "get" - show current value.
```

## Source note 16, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L220)

```text
// Has args, non-command: set.
```

## Source note 17, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L232)

```text
// Snapshot the sink only when it has new data (copying up to kCapacity
```

## Source note 18, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L233)

```text
// entries every frame would be wasteful). Console-local command feedback
```

## Source note 19, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L234)

```text
// lives in local_entries_ and is merged in at draw time below, so it appears
```

## Source note 20, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L235)

```text
// the frame after it is produced regardless of whether the sink advanced -
```

## Source note 21, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L236)

```text
// otherwise a command that emits no log line (help, cvar get/set, the command
```

## Source note 22, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L237)

```text
// echo) would not stream until some unrelated log bumped the generation.
```

## Source note 23, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L264)

```text
// Drag handle along the top edge to resize the console vertically.
```

## Source note 24, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L271)

```text
// --- Filter bar ---
```

## Source note 25, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L287)

```text
// --- Log area ---
```

## Source note 26, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L294)

```text
// Level filter.
```

## Source note 27, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L297)

```text
// Category filter. The "console" pseudo-category is always shown.
```

## Source note 28, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L312)

```text
// Merge the sink snapshot with the console-local feedback by generation so
```

## Source note 29, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L313)

```text
// command output blends in chronologically instead of piling up at the bottom.
```

## Source note 30, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L314)

```text
// entries_[i] has absolute generation base_gen + i (the sink increments its
```

## Source note 31, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L315)

```text
// counter once per captured line); a local line tagged seq belongs after every
```

## Source note 32, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L316)

```text
// sink line with generation <= seq. Locals are drawn every frame regardless of
```

## Source note 33, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L317)

```text
// whether the sink advanced, so feedback appears the frame after it is issued.
```

## Source note 34, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L336)

```text
// --- Command input ---
```

## Source note 35, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L354)

```text
// Close the completion popup whenever the input loses keyboard focus, so it
```

## Source note 36, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L355)

```text
// does not linger after the user clicks or tabs away from the input.
```

## Source note 37, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/overlay/console_overlay.cpp#L377)

```text
// Anchor the bottom edge to the input's top edge and grow upward.
```
