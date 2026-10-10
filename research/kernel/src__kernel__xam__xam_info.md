# Xam info: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xam/xam_info.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L41)

```text
// Empty stub schema binary.
```

## Source note 2, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L59)

```text
// return pointer to the schema ptr/schema size struct
```

## Source note 3, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L116)

```text
// On an actual xbox these funcs would return a locator to xam.xex resources,
```

## Source note 4, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L117)

```text
// but for Xenia we can return a locator to the resources as local files. (big
```

## Source note 5, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L118)

```text
// thanks to MS for letting XamBuildResourceLocator return local file
```

## Source note 6, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L119)

```text
// locators!)
```

## Source note 7, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L121)

```text
// If you're running an app that'll need them, make sure to extract xam.xex
```

## Source note 8, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L122)

```text
// resources with xextool ("xextool -d . xam.xex") and add a .xzp extension.
```

## Source note 9, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L129)

```text
// see notes inside XamBuildGamercardResourceLocator above
```

## Source note 10, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L144)

```text
// eh, just picking one. If we go too low we may break new games, but
```

## Source note 11, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L145)

```text
// this value seems to be used for conditionally loading symbols and if
```

## Source note 12, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L146)

```text
// we pretend to be old we have less to worry with implementing.
```

## Source note 13, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L147)

```text
// 0x200A3200
```

## Source note 14, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L148)

```text
// 0x20096B00
```

## Source note 15, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L156)

```text
// Real XAM reads XCONFIG_USER_AUDIO_FLAGS; so does this (Edge xam_info.cc).
```

## Source note 16, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L163)

```text
// Not sure what the values are for this, but 6 is VGA.
```

## Source note 17, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L164)

```text
// Other likely values are 3/4/8 for HDMI or something.
```

## Source note 18, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L165)

```text
// Games seem to use this as a PAL check - if the result is not 3/4/6/8
```

## Source note 19, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L166)

```text
// they explode with errors if not in PAL mode.
```

## Source note 20, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L184)

```text
// NOTE(tomc): Switched this up to get title ID from executable module instead of runtime
```

## Source note 21, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L185)

```text
// (emulator)
```

## Source note 22, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L251)

```text
// A statically compiled binary holds one title module and cannot load
```

## Source note 23, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L252)

```text
// another executable, so every launch ends the running title; say which kind
```

## Source note 24, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L253)

```text
// it was instead of ending silently (RG-GDK-017; see docs/content-persistence.md).
```

## Source note 25, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L276)

```text
// This function does not return.
```

## Source note 26, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L281)

```text
// This function does not return.
```

## Source note 27, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L288)

```text
// Allocate from the heap. Not sure why XAM does this specially, perhaps
```

## Source note 28, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L289)

```text
// it keeps stuff in a separate heap?
```

## Source note 29, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L303)

```text
/* guess */
```

## Source note 30, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L308)

```text
// 0 = tray open, 1 = tray closed with disc
```

## Source note 31, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L315)

```text
// Stub for multi-disc games. Single-disc games (like Blue Dragon's reblue test)
```

## Source note 32, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_info.cpp#L316)

```text
// don't need this, but the game may look it up dynamically via XexGetProcedureAddress.
```
