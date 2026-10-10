# Stfs container test: filesystem source notes

This record preserves technical and API notes moved from `tests/unit/filesystem/stfs_container_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L34)

```text
// 0x971A, rounded to 0xA000
```

## Source note 2, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L35)

```text
// level 0 table for blocks 0-169
```

## Source note 3, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L38)

```text
// Block b (< 170) of a read-only STFS sits after the table: 0xA000 + (b+1) * 4K.
```

## Source note 4, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L53)

```text
// A package with one file, `name`, of `data` bytes in consecutive blocks
```

## Source note 5, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L54)

```text
// starting at block 1.
```

## Source note 6, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L72)

```text
// file table
```

## Source note 7, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L166)

```text
// second data block mostly missing
```

## Source note 8, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L174)

```text
// Block 1 claims its successor is block 200, whose hash table would lie far
```

## Source note 9, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L175)

```text
// past the end of the file (xenia-canary #1226 crash shape).
```

## Source note 10, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L183)

```text
// Block 1 and the out-of-package block 200 were recorded; reading stops at
```

## Source note 11, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L184)

```text
// the end of the file instead of misplacing data.
```

## Source note 12, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L207)

```text
// entry 0 is a file
```

## Source note 13, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L213)

```text
// 40 chars
```

## Source note 14, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L243)

```text
// Single-file SVOD: the media magic at 0xD000 (block 0), root directory at
```

## Source note 15, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L244)

```text
// block 2 (0xE000). Node 0 links right to node 8, which links to itself.
```

## Source note 16, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L245)

```text
// reaches past the 0x12000 XSF probe
```

## Source note 17, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/filesystem/stfs_container_test.cpp#L262)

```text
// name length
```
