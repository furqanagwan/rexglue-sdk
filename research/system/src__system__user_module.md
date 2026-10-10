# User module: system source notes

This record preserves technical and API notes moved from `src/system/user_module.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L54)

```text
// Resolve the file to open.
```

## Source note 2, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L65)

```text
// If the FS supports mapping, map the file in and load from that.
```

## Source note 3, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L67)

```text
// Map.
```

## Source note 4, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L73)

```text
// Load the module.
```

## Source note 5, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L78)

```text
// Open file for reading.
```

## Source note 6, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L85)

```text
// Read entire file into memory.
```

## Source note 7, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L86)

```text
// Ugh.
```

## Source note 8, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L93)

```text
// Load the module.
```

## Source note 9, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L96)

```text
// Close the file.
```

## Source note 10, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L100)

```text
// Only XEX returns X_STATUS_PENDING
```

## Source note 11, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L105)

```text
// XEX patches come from the title update the code was built for, and only
```

## Source note 12, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L106)

```text
// then: an original build must load the original image, whatever lies beside
```

## Source note 13, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L107)

```text
// it. The update holds <name>p at the module's path relative to the game
```

## Source note 14, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L108)

```text
// (data\webkit\EAWebkit.xexp), or at its root.
```

## Source note 15, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L112)

```text
// A patch is not patched itself.
```

## Source note 16, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L156)

```text
// Detect format by magic bytes
```

## Source note 17, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L170)

```text
// Create XexModule to parse and load the XEX image into guest memory
```

## Source note 18, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L179)

```text
// Continue to LoadXexContinue (returns X_STATUS_PENDING per Xenia convention)
```

## Source note 19, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L183)

```text
// Create ElfModule to parse and load the ELF image into guest memory
```

## Source note 20, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L191)

```text
// 1 MB default stack
```

## Source note 21, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L196)

```text
// ELF doesn't need LoadXexContinue
```

## Source note 22, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L203)

```text
// LoadXexContinue: finishes loading XEX after a patch has been applied (or
```

## Source note 23, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L204)

```text
// patch wasn't found)
```

## Source note 24, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L210)

```text
// If guest_xex_header is set we must have already loaded the XEX
```

## Source note 25, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L215)

```text
// Finish XexModule load (PE sections/imports/symbols...)
```

## Source note 26, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L220)

```text
// Copy the xex2 header into guest memory.
```

## Source note 27, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L228)

```text
// Cache some commonly used headers...
```

## Source note 28, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L233)

```text
// Setup the loader data entry
```

## Source note 29, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L236)

```text
// GetProcAddress will read this.
```

## Source note 30, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L249)

```text
// Quick abort.
```

## Source note 31, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L284)

```text
// No resources.
```

## Source note 32, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L291)

```text
// Found!
```

## Source note 33, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L305)

```text
// Quick die.
```

## Source note 34, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L319)

```text
// Quick die.
```

## Source note 35, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L343)

```text
// Return data stored in header value.
```

## Source note 36, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L347)

```text
// Return pointer to data stored in header value.
```

## Source note 37, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L351)

```text
// Data stored at offset to header.
```

## Source note 38, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L369)

```text
// A lot of the information stored on this class can be reconstructed at
```

## Source note 39, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L370)

```text
// runtime.
```

## Source note 40, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L379)

```text
// XModule::Save took care of this earlier...
```

## Source note 41, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/user_module.cpp#L392)

```text
// Already loaded?
```
