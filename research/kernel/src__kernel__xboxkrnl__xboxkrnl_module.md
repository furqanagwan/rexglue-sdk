# Xboxkrnl module: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_module.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L60)

```text
// Register video variable exports (VdGlobalDevice, VdGpuClockInMHz, etc.)
```

## Source note 3, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L63)

```text
// KeDebugMonitorData (?*)
```

## Source note 4, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L64)

```text
// Set to a valid value when a remote debugger is attached.
```

## Source note 5, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L65)

```text
// Offset 0x18 is a 4b pointer to a handler function that seems to take two
```

## Source note 6, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L66)

```text
// arguments. If we wanted to see what would happen we could fake that.
```

## Source note 7, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L82)

```text
// KeCertMonitorData (?*)
```

## Source note 8, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L83)

```text
// Always set to zero, ignored.
```

## Source note 9, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L99)

```text
// XboxHardwareInfo (XboxHardwareInfo_t, 16b)
```

## Source note 10, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L100)

```text
// flags       cpu#  ?     ?     ?     ?           ?       ?
```

## Source note 11, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L101)

```text
// 0x00000000, 0x06, 0x00, 0x00, 0x00, 0x00000000, 0x0000, 0x0000
```

## Source note 12, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L102)

```text
// Games seem to check if bit 26 (0x20) is set, which at least for xbox1
```

## Source note 13, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L103)

```text
// was whether an HDD was present. Not sure what the other flags are.
```

## Source note 14, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L105)

```text
// aomega08 says the value is 0x02000817, bit 27: debug mode on.
```

## Source note 15, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L106)

```text
// When that is set, though, allocs crash in weird ways.
```

## Source note 16, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L108)

```text
// From kernel dissasembly, after storage is initialized
```

## Source note 17, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L109)

```text
// XboxHardwareInfo flags is set with flag 5 (0x20).
```

## Source note 18, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L114)

```text
// cpu count
```

## Source note 19, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L115)

```text
// Remaining 11b are zeroes?
```

## Source note 20, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L117)

```text
// ExConsoleGameRegion, probably same values as keyvault region uses?
```

## Source note 21, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L118)

```text
// Just return all 0xFF, should satisfy anything that checks it
```

## Source note 22, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L124)

```text
// XexExecutableModuleHandle (?**)
```

## Source note 23, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L125)

```text
// Games try to dereference this to get a pointer to some module struct.
```

## Source note 24, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L126)

```text
// So far it seems like it's just in loader code, and only used to look up
```

## Source note 25, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L127)

```text
// the XexHeaderBase for use by RtlImageXexHeaderField.
```

## Source note 26, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L128)

```text
// We fake it so that the address passed to that looks legit.
```

## Source note 27, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L129)

```text
// 0x80100FFC <- pointer to structure
```

## Source note 28, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L130)

```text
// 0x80101000 <- our module structure
```

## Source note 29, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L131)

```text
// 0x80101058 <- pointer to xex header
```

## Source note 30, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L132)

```text
// 0x80101100 <- xex header base
```

## Source note 31, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L136)

```text
// ExLoadedImageName (char*)
```

## Source note 32, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L137)

```text
// The full path to loaded image/xex including its name.
```

## Source note 33, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L138)

```text
// Used usually in custom dashboards (Aurora)
```

## Source note 34, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L139)

```text
// Todo(Gliniak): Confirm that official kernel always allocate space for this
```

## Source note 35, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L140)

```text
// variable.
```

## Source note 36, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L144)

```text
// ExLoadedCommandLine (char*)
```

## Source note 37, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L145)

```text
// The name of the xex. Not sure this is ever really used on real devices.
```

## Source note 38, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L146)

```text
// Perhaps it's how swap disc/etc data is sent?
```

## Source note 39, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L147)

```text
// Always set to "default.xex" (with quotes) for now.
```

## Source note 40, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L161)

```text
// XboxKrnlVersion (8b)
```

## Source note 41, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L162)

```text
// Kernel version, looks like 2b.2b.2b.2b.
```

## Source note 42, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L163)

```text
// I've only seen games check >=, so we just fake something here.
```

## Source note 43, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L173)

```text
// KeTimeStampBundle (24b)
```

## Source note 44, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L174)

```text
// This must be updated during execution, at 1ms intevals.
```

## Source note 45, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L175)

```text
// We setup a system timer here to do that.
```

## Source note 46, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L190)

```text
// Wire kernel object type variables to KernelGuestGlobals.
```

## Source note 47, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L191)

```text
// KernelGuestGlobals is allocated in KernelState ctor, which runs before this.
```

## Source note 48, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L233)

```text
// Build the export table used for resolution.
```
