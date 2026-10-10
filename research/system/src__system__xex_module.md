# Xex module: system source notes

This record preserves technical and API notes moved from `src/system/xex_module.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L48)

```text
// Decrypt 16 uint8_ts from input -> output.
```

## Source note 2, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L51)

```text
// XOR with previous.
```

## Source note 3, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L53)

```text
// Set previous.
```

## Source note 4, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L75)

```text
// Match!
```

## Source note 5, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L78)

```text
// We just return the value of the optional header.
```

## Source note 6, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L79)

```text
// Assume that the output pointer points to a uint32_t.
```

## Source note 7, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L83)

```text
// Pointer to the value on the optional header.
```

## Source note 8, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L87)

```text
// Pointer to the header.
```

## Source note 9, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L117)

```text
// First: Check the xex2 export table.
```

## Source note 10, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L134)

```text
// Second: Check the PE exports.
```

## Source note 11, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L158)

```text
// No exports by name.
```

## Source note 12, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L166)

```text
// e->AddressOfX RVAs are relative to the IMAGE_EXPORT_DIRECTORY!
```

## Source note 13, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L169)

```text
// Names relative to directory
```

## Source note 14, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L172)

```text
// Table of ordinals (by name)
```

## Source note 15, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L180)

```text
// We have a match!
```

## Source note 16, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L185)

```text
// No match
```

## Source note 17, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L191)

```text
// This isn't a XEX2 patch.
```

## Source note 18, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L195)

```text
// Grab the delta descriptor and get to work.
```

## Source note 19, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L200)

```text
// Compare hash inside delta descriptor to base XEX signature
```

## Source note 20, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L232)

```text
// ? unsure what the point of this test is, kernel checks for it
```

## Source note 21, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L236)

```text
// Patch base XEX header
```

## Source note 22, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L247)

```text
// Increase xex header buffer length if needed
```

## Source note 23, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L254)

```text
// If headers_source_offset is set, copy [source_offset:source_size] to
```

## Source note 24, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L262)

```text
// If new size is smaller than original, null out the difference
```

## Source note 25, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L270)

```text
// Apply header patch...
```

## Source note 26, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L281)

```text
// Decrease xex header buffer length if needed (but only after patching)
```

## Source note 27, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L286)

```text
// Update security info context with latest security info data
```

## Source note 28, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L291)

```text
// Check if we need to alloc new memory for the patched xex
```

## Source note 29, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L314)

```text
// Header patch updated the base XEX key, need to redecrypt it
```

## Source note 30, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L319)

```text
// Decrypt the patch XEX's key using base XEX key
```

## Source note 31, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L324)

```text
// Test delta key against our decrypted keys
```

## Source note 32, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L325)

```text
// (kernel doesn't seem to check this, but it's the one use for the
```

## Source note 33, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L326)

```text
// image_key_source field I can think of...)
```

## Source note 34, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L336)

```text
// Decrypt (if needed).
```

## Source note 35, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L345)

```text
// No-op.
```

## Source note 36, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L365)

```text
// If image_source_offset is set, copy [source_offset:source_size] to
```

## Source note 37, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L376)

```text
// If new size is smaller than original, null out the difference
```

## Source note 38, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L381)

```text
// Now loop through each block and apply the delta patches inside
```

## Source note 39, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L385)

```text
// Compare block hash, if no match we probably used wrong decrypt key
```

## Source note 40, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L396)

```text
// skip block info
```

## Source note 41, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L402)

```text
// Apply delta patch
```

## Source note 42, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L415)

```text
// Decommit unused pages if new image size is smaller than original
```

## Source note 43, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L455)

```text
// Make a copy of patch data for other XEX's to use with ApplyPatch()
```

## Source note 44, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L492)

```text
// Not a patch and image doesn't have proper PE header, return 3
```

## Source note 45, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L497)

```text
// Allocate in-place the XEX memory.
```

## Source note 46, line 542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L542)

```text
// Calculate uncompressed length.
```

## Source note 47, line 555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L555)

```text
// Calculate the total size of the XEX image from its headers.
```

## Source note 48, line 558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L558)

```text
// Byteswap the bitfield manually.
```

## Source note 49, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L565)

```text
// Allocate in-place the XEX memory.
```

## Source note 50, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L577)

```text
// Quickly zero the contents.
```

## Source note 51, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L591)

```text
// Overflow.
```

## Source note 52, line 600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L600)

```text
// Decrypt 16 uint8_ts from input -> output.
```

## Source note 53, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L603)

```text
// XOR with previous.
```

## Source note 54, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L605)

```text
// Set previous.
```

## Source note 55, line 626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L626)

```text
// src -> dest:
```

## Source note 56, line 627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L627)

```text
// - decrypt (if encrypted)
```

## Source note 57, line 628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L628)

```text
// - de-block:
```

## Source note 58, line 629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L629)

```text
//    4b total size of next block in uint8_ts
```

## Source note 59, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L630)

```text
//   20b hash of entire next block (including size/hash)
```

## Source note 60, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L631)

```text
//    Nb block uint8_ts
```

## Source note 61, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L632)

```text
// - decompress block contents
```

## Source note 62, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L639)

```text
// Decrypt (if needed).
```

## Source note 63, line 646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L646)

```text
// No-op.
```

## Source note 64, line 667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L667)

```text
// De-block.
```

## Source note 65, line 675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L675)

```text
// Compare block hash, if no match we probably used wrong decrypt key
```

## Source note 66, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L684)

```text
// skip block info
```

## Source note 67, line 707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L707)

```text
// Allocate in-place the XEX memory.
```

## Source note 68, line 720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L720)

```text
// Decompress into XEX base
```

## Source note 69, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L742)

```text
// Verify DOS signature (MZ).
```

## Source note 70, line 749

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L749)

```text
// Move to the NT header offset from the DOS header.
```

## Source note 71, line 752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L752)

```text
// Verify NT signature (PE\0\0).
```

## Source note 72, line 758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L758)

```text
// Verify matches an Xbox PE.
```

## Source note 73, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L764)

```text
// Verify the expected size.
```

## Source note 74, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L769)

```text
// Verify optional header is 32bit.
```

## Source note 75, line 774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L774)

```text
// Verify subsystem.
```

## Source note 76, line 781

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L781)

```text
// Linker version - likely 8+
```

## Source note 77, line 782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L782)

```text
// Could be useful for recognizing certain patterns
```

## Source note 78, line 783

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L783)

```text
// opthdr->MajorLinkerVersion; opthdr->MinorLinkerVersion;
```

## Source note 79, line 785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L785)

```text
// Data directories of interest:
```

## Source note 80, line 786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L786)

```text
// EXPORT           IMAGE_EXPORT_DIRECTORY
```

## Source note 81, line 787

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L787)

```text
// IMPORT           IMAGE_IMPORT_DESCRIPTOR[]
```

## Source note 82, line 788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L788)

```text
// EXCEPTION        IMAGE_CE_RUNTIME_FUNCTION_ENTRY[]
```

## Source note 83, line 790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L790)

```text
// DEBUG            IMAGE_DEBUG_DIRECTORY[]
```

## Source note 84, line 791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L791)

```text
// ARCHITECTURE     /IMAGE_ARCHITECTURE_HEADER/ ----- import thunks!
```

## Source note 85, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L792)

```text
// TLS              IMAGE_TLS_DIRECTORY
```

## Source note 86, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L793)

```text
// IAT              Import Address Table ptr
```

## Source note 87, line 794

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L794)

```text
// opthdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_X].VirtualAddress / .Size
```

## Source note 88, line 796

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L796)

```text
// The macros in pe_image.h don't work with clang, for some reason.
```

## Source note 89, line 797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L797)

```text
// offsetof seems to be unable to find OptionalHeader.
```

## Source note 90, line 803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L803)

```text
// Quick scan to determine bounds of sections.
```

## Source note 91, line 811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L811)

```text
// Setup/load sections.
```

## Source note 92, line 825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L825)

```text
// Extract Exception DataDirectory (PDATA table location)
```

## Source note 93, line 826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L826)

```text
// This is the authoritative source for PDATA location, not the .pdata section header.
```

## Source note 94, line 827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L827)

```text
// The .pdata section's VirtualAddress may differ from the DataDirectory entry.
```

## Source note 95, line 828

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L828)

```text
// NOTE: PE headers are little-endian (PE spec), no byte-swap needed.
```

## Source note 96, line 832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L832)

```text
// DumpTLSDirectory(pImageBase, pNTHeader, (PIMAGE_TLS_DIRECTORY32)0);
```

## Source note 97, line 833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L833)

```text
// DumpExportsSection(pImageBase, pNTHeader);
```

## Source note 98, line 880

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L880)

```text
// Read in XEX headers
```

## Source note 99, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L884)

```text
// Read/convert XEX1/XEX2 security info to a common format
```

## Source note 100, line 889

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L889)

```text
// Try setting our base_address based on XEX_HEADER_IMAGE_BASE_ADDRESS, fall
```

## Source note 101, line 890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L890)

```text
// back to xex_security_info otherwise
```

## Source note 102, line 896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L896)

```text
// Setup debug info.
```

## Source note 103, line 902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L902)

```text
// Load in the XEX basefile
```

## Source note 104, line 903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L903)

```text
// We'll try using both XEX2 keys to see if any give a valid PE
```

## Source note 105, line 915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L915)

```text
// Note: caller will have to call LoadContinue once it's determined whether a
```

## Source note 106, line 916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L916)

```text
// patch file exists or not!
```

## Source note 107, line 921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L921)

```text
// Second part of image load
```

## Source note 108, line 922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L922)

```text
// Split from Load() so that we can patch the XEX before loading this data
```

## Source note 109, line 935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L935)

```text
// Parse any "unsafe" headers into safer variants
```

## Source note 110, line 944

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L944)

```text
// Scan and find the low/high addresses.
```

## Source note 111, line 945

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L945)

```text
// All code sections are continuous, so this should be easy.
```

## Source note 112, line 954

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L954)

```text
// Byteswap the bitfield manually.
```

## Source note 113, line 968

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L968)

```text
// NOTE(tomc): Backend notification not needed - no JIT in rexglue
```

## Source note 114, line 969

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L969)

```text
// processor_->backend()->CommitExecutableRange(low_address_, high_address_);
```

## Source note 115, line 971

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L971)

```text
// Add all imports (variables/functions).
```

## Source note 116, line 979

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L979)

```text
// Parse the string table
```

## Source note 117, line 1011

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1011)

```text
// Setup memory protection.
```

## Source note 118, line 1013

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1013)

```text
// Byteswap the bitfield manually.
```

## Source note 119, line 1032

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1032)

```text
// Populate binary introspection data
```

## Source note 120, line 1044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1044)

```text
// If this isn't a patch, just deallocate the memory occupied by the exe
```

## Source note 121, line 1058

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1058)

```text
// NOTE(tomc): import resolution is done at compile time.
```

## Source note 122, line 1059

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1059)

```text
// however, we still need to patch variable imports in guest memory
```

## Source note 123, line 1060

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1060)

```text
// since they are accessed via memory loads, not function calls.
```

## Source note 124, line 1064

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1064)

```text
// Get export resolver for variable import patching
```

## Source note 125, line 1073

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1073)

```text
// Use a map to properly pair type 0 (variable) and type 1 (thunk) records by ordinal.
```

## Source note 126, line 1074

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1074)

```text
// Import table entries alternate: type 0 has ordinal info, type 1 has thunk address.
```

## Source note 127, line 1075

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1075)

```text
// They may not come in immediate succession, so we pair by ordinal.
```

## Source note 128, line 1093

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1093)

```text
// Variable import - value_address is where the variable value is stored
```

## Source note 129, line 1096

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1096)

```text
// Patch variable imports in guest memory with the actual address
```

## Source note 130, line 1101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1101)

```text
// Write the variable address to guest memory
```

## Source note 131, line 1106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1106)

```text
// write garbage value if we don't have it implemented
```

## Source note 132, line 1114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1114)

```text
// Thunk import - thunk_address is the function pointer location
```

## Source note 133, line 1115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1115)

```text
// This is the address we need for function table registration
```

## Source note 134, line 1120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1120)

```text
// Convert map to vector (sorted by ordinal for consistent output)
```

## Source note 135, line 1143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1143)

```text
// Binary introspection implementation
```

## Source note 136, line 1148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1148)

```text
// Populate sections from existing PE sections
```

## Source note 137, line 1160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1160)

```text
// Populate symbols from import libraries
```

## Source note 138, line 1166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_module.cpp#L1166)

```text
// Thunk size: 2 ordinal words + mtctr + bctr
```
