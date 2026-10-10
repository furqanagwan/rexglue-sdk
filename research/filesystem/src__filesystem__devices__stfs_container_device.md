# Stfs container device: filesystem source notes

This record preserves technical and API notes moved from `src/filesystem/devices/stfs_container_device.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L71)

```text
// Resolve a valid STFS file if a directory is given.
```

## Source note 2, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L82)

```text
// Open the data file(s)
```

## Source note 3, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L103)

```text
// Map the file containing the STFS Header and read it.
```

## Source note 4, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L120)

```text
// If the STFS package is a single file, the header is self contained and
```

## Source note 5, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L121)

```text
// we don't need to map any extra files.
```

## Source note 6, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L122)

```text
// NOTE: data_file_count is 0 for STFS and 1 for SVOD
```

## Source note 7, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L123)

```text
// The metadata records how much data the package holds; an incomplete copy
```

## Source note 8, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L124)

```text
// or download is refused here, named, instead of failing later mid-read
```

## Source note 9, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L125)

```text
// (xenia-canary #1226). Some packages leave the field at zero.
```

## Source note 10, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L149)

```text
// If the STFS package is multi-file, it is an SVOD system. We need to map
```

## Source note 11, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L150)

```text
// the files in the .data folder and can discard the header.
```

## Source note 12, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L159)

```text
// Ensure data fragment files are sorted
```

## Source note 13, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L184)

```text
// no need to seek back, any reads from this file will seek first anyway
```

## Source note 14, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L205)

```text
// The filesystem will have stripped our prefix off already, so the path will
```

## Source note 15, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L206)

```text
// be in the form:
```

## Source note 16, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L207)

```text
// some\PATH.foo
```

## Source note 17, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L213)

```text
// Check size of the file is enough to store an STFS header
```

## Source note 18, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L222)

```text
// Read header & check signature
```

## Source note 19, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L228)

```text
// Unexpected format.
```

## Source note 20, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L232)

```text
// Pre-calculate some values used in block number calculations
```

## Source note 21, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L246)

```text
// SVOD Systems can have different layouts. The root block is
```

## Source note 22, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L247)

```text
// denoted by the magic "MICROSOFT*XBOX*MEDIA" and is always in
```

## Source note 23, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L248)

```text
// the first "actual" data fragment of the system.
```

## Source note 24, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L255)

```text
// Check for EDGF layout
```

## Source note 25, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L257)

```text
// The STFS header has specified that this SVOD system uses the EGDF layout.
```

## Source note 26, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L258)

```text
// We can expect the magic block to be located immediately after the hash
```

## Source note 27, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L259)

```text
// blocks. We also offset block address calculation by 0x1000 by shifting
```

## Source note 28, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L260)

```text
// block indices by +0x2.
```

## Source note 29, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L283)

```text
// If the SVOD's magic block is at 0x12000, it is likely using an XSF
```

## Source note 30, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L284)

```text
// layout. This is usually due to converting the game using a third-party
```

## Source note 31, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L285)

```text
// tool, as most of them use a nulled XSF as a template.
```

## Source note 32, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L290)

```text
// Check for XSF Header
```

## Source note 33, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L313)

```text
// If the SVOD's magic block is at 0xD000, it most likely means that it
```

## Source note 34, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L314)

```text
// is a single-file system. The STFS Header is 0xB000 bytes , and the
```

## Source note 35, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L315)

```text
// remaining 0x2000 is from hash tables. In most cases, these will be
```

## Source note 36, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L316)

```text
// STFS, not SVOD.
```

## Source note 37, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L321)

```text
// Check for single file system
```

## Source note 38, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L338)

```text
// Parse the root directory
```

## Source note 39, line 364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L364)

```text
// Traverse all child entries
```

## Source note 40, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L372)

```text
// The tree comes from the package; a cycle or an absurd depth is damage.
```

## Source note 41, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L380)

```text
// For games with a large amount of files, the ordinal offset can overrun
```

## Source note 42, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L381)

```text
// the current block and potentially hit a hash block.
```

## Source note 43, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L386)

```text
// Calculate the file & address of the block
```

## Source note 44, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L391)

```text
// Read directory entry
```

## Source note 45, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L425)

```text
// Read the left node
```

## Source note 46, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L433)

```text
// Read file & address of block's data
```

## Source note 47, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L437)

```text
// Create the entry
```

## Source note 48, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L438)

```text
// NOTE: SVOD entries don't have timestamps for individual files, which can
```

## Source note 49, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L439)

```text
//       cause issues when decrypting games. Using the root entry's timestamp
```

## Source note 50, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L440)

```text
//       solves this issues.
```

## Source note 51, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L443)

```text
// Entry is a directory
```

## Source note 52, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L453)

```text
// If length is greater than 0, traverse the directory's children
```

## Source note 53, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L460)

```text
// Entry is a file
```

## Source note 54, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L471)

```text
// Fill in all block records, sector by sector.
```

## Source note 55, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L488)

```text
// Consecutive, so append to last entry.
```

## Source note 56, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L503)

```text
// Read the right node.
```

## Source note 57, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L516)

```text
// SVOD Systems use hash blocks for integrity checks. These hash blocks
```

## Source note 58, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L517)

```text
// cause blocks to be discontinuous in memory, and must be accounted for.
```

## Source note 59, line 518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L518)

```text
//  - Each data block is 0x800 bytes in length
```

## Source note 60, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L519)

```text
//  - Every group of 0x198 data blocks is preceded a Level0 hash table.
```

## Source note 61, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L520)

```text
//    Level0 tables contain 0xCC hashes, each representing two data blocks.
```

## Source note 62, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L521)

```text
//    The total size of each Level0 hash table is 0x1000 bytes in length.
```

## Source note 63, line 522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L522)

```text
//  - Every 0xA1C4 Level0 hash tables is preceded by a Level1 hash table.
```

## Source note 64, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L523)

```text
//    Level1 tables contain 0xCB hashes, each representing two Level0 hashes.
```

## Source note 65, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L524)

```text
//    The total size of each Level1 hash table is 0x1000 bytes in length.
```

## Source note 66, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L525)

```text
//  - Files are split into fragments of 0xA290000 bytes in length,
```

## Source note 67, line 526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L526)

```text
//    consisting of 0x14388 data blocks, 0xCB Level0 hash tables, and 0x1
```

## Source note 68, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L527)

```text
//    Level1 hash table.
```

## Source note 69, line 537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L537)

```text
// Resolve the true block address and file index
```

## Source note 70, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L540)

```text
// EGDF has an 0x1000 byte offset, which is two blocks
```

## Source note 71, line 548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L548)

```text
// Calculate offset caused by Level0 Hash Tables
```

## Source note 72, line 552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L552)

```text
// Calculate offset caused by Level1 Hash Tables
```

## Source note 73, line 556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L556)

```text
// For single-file SVOD layouts, include the size of the header in the offset.
```

## Source note 74, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L563)

```text
// If the offset causes the block address to overrun the file, round it.
```

## Source note 75, line 583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L583)

```text
// Load all listings.
```

## Source note 76, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L602)

```text
// Done.
```

## Source note 77, line 613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L613)

```text
// An index from the package itself; a damaged table must not read
```

## Source note 78, line 614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L614)

```text
// past the entries seen so far.
```

## Source note 79, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L641)

```text
// Fill in all block records.
```

## Source note 80, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L642)

```text
// It's easier to do this now and just look them up later, at the cost
```

## Source note 81, line 643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L643)

```text
// of some memory. Nasty chain walk.
```

## Source note 82, line 648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L648)

```text
// Each step consumes a block of the entry's length, so even a looping
```

## Source note 83, line 649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L649)

```text
// chain ends.
```

## Source note 84, line 657

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L657)

```text
// The hash table this block needs is not in the file (a truncated
```

## Source note 85, line 658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L658)

```text
// package); keep what was found (xenia-canary #1226).
```

## Source note 86, line 665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L665)

```text
// Malformed packages are reported, not asserted: they are input.
```

## Source note 87, line 674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L674)

```text
// Check that the number of blocks retrieved from hash entries matches
```

## Source note 88, line 675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L675)

```text
// the block count read from the file entry
```

## Source note 89, line 707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L707)

```text
// For every level there is a hash table
```

## Source note 90, line 708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L708)

```text
// Level 0: hash table of next 170 blocks
```

## Source note 91, line 709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L709)

```text
// Level 1: hash table of next 170 hash tables
```

## Source note 92, line 710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L710)

```text
// Level 2: hash table of next 170 level 1 hash tables
```

## Source note 93, line 711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L711)

```text
// And so on...
```

## Source note 94, line 753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L753)

```text
// Level 2 is always at blockStep1
```

## Source note 95, line 768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L768)

```text
// Offset for selecting the secondary hash block, in packages that have them
```

## Source note 96, line 773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L773)

```text
// If this is read_only_format then it doesn't contain secondary blocks, no
```

## Source note 97, line 774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L774)

```text
// need to check upper hash levels
```

## Source note 98, line 778

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L778)

```text
// Not a read-only package, need to check each levels active index flag to
```

## Source note 99, line 779

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L779)

```text
// see if we need to use secondary block or not
```

## Source note 100, line 781

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L781)

```text
// Check level1 table if package has it
```

## Source note 101, line 786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L786)

```text
// Check level2 table if package has it
```

## Source note 102, line 842

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L842)

```text
// Files shorter than the magic, or unreadable, are simply not packages.
```

## Source note 103, line 855

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L855)

```text
// Scan through folders until a file with magic is found
```

## Source note 104, line 873

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L873)

```text
// Try to read the file's magic
```

## Source note 105, line 887

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_device.cpp#L887)

```text
// Could not find a suitable container file
```
