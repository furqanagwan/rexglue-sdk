# Stream test: core source notes

This record preserves technical and API notes moved from `tests/unit/core/stream_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 1

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L1)

```text
/**
 * Unit tests for stream utilities (BitStream, ByteStream)
 *
 * Tests bit-level and byte-level stream operations.
 */
```

## Source note 2, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L18)

```text
// ByteStream Basic Tests
```

## Source note 3, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L60)

```text
// ByteStream Read/Write Tests
```

## Source note 4, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L76)

```text
// Read it back
```

## Source note 5, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L89)

```text
// Write various types
```

## Source note 6, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L97)

```text
// Read them back
```

## Source note 7, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L158)

```text
// BitStream Basic Tests
```

## Source note 8, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L192)

```text
// BitStream Peek/Read Tests
```

## Source note 9, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L196)

```text
// Buffer with known pattern: 0xAB = 10101011
```

## Source note 10, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L201)

```text
// No advance
```

## Source note 11, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L204)

```text
// Same value
```

## Source note 12, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L219)

```text
// Big-endian data: reading first byte should give 0xAB
```

## Source note 13, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L232)

```text
// Reading 16 bits from big-endian: 0xABCD
```

## Source note 14, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L245)

```text
// 0xAB = 10101011, 0xCD = 11001101
```

## Source note 15, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L249)

```text
// Read 4 bits: should be 1010 = 0xA
```

## Source note 16, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L252)

```text
// Read 4 bits: should be 1011 = 0xB
```

## Source note 17, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L255)

```text
// Read 8 bits: should be 0xCD
```

## Source note 18, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L260)

```text
// 0xAB = 10101011
```

## Source note 19, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L264)

```text
// Read bits one at a time from MSB
```

## Source note 20, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L265)

```text
// 1
```

## Source note 21, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L266)

```text
// 0
```

## Source note 22, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L267)

```text
// 1
```

## Source note 23, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L268)

```text
// 0
```

## Source note 24, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L269)

```text
// 1
```

## Source note 25, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L270)

```text
// 0
```

## Source note 26, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L271)

```text
// 1
```

## Source note 27, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L272)

```text
// 1
```

## Source note 28, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L276)

```text
// Read bits that span byte boundaries
```

## Source note 29, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L280)

```text
// Now at bit 4
```

## Source note 30, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L282)

```text
// Read 8 bits crossing the boundary: last 4 of 0xFF + first 4 of 0x00
```

## Source note 31, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L283)

```text
// 0xFF = 11111111, last 4 = 1111
```

## Source note 32, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L284)

```text
// 0x00 = 00000000, first 4 = 0000
```

## Source note 33, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L285)

```text
// Combined: 11110000 = 0xF0
```

## Source note 34, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L290)

```text
// BitStream Write Tests
```

## Source note 35, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L291)

```text
// NOTE: BitStream::Write is marked "TODO: This is totally not tested!" in source.
```

## Source note 36, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L292)

```text
// It has a bug: doesn't byte-swap when storing, but Read expects big-endian.
```

## Source note 37, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L293)

```text
// These tests are skipped until Write is fixed.
```

## Source note 38, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L327)

```text
// Write 4 bits, then 4 more
```

## Source note 39, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L328)

```text
// 1010
```

## Source note 40, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L329)

```text
// 1011
```

## Source note 41, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L342)

```text
// Clear middle 4 bits
```

## Source note 42, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L345)

```text
// First 4 bits should still be 1111, next 4 should be 0000
```

## Source note 43, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L351)

```text
// BitStream Edge Cases
```

## Source note 44, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L359)

```text
// No advance
```

## Source note 45, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L366)

```text
// 57 bits of all 1s = 0x1FFFFFFFFFFFFFF
```

## Source note 46, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/stream_test.cpp#L373)

```text
// 64 bits = 8 bytes
```
