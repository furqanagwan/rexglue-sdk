# Xboxkrnl crypt: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_crypt.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L45)

```text
// 0x0
```

## Source note 3, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L46)

```text
// 0x100
```

## Source note 4, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L47)

```text
// 0x101
```

## Source note 5, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L52)

```text
// Setup RC4 state
```

## Source note 6, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L68)

```text
// Crypt data
```

## Source note 7, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L89)

```text
// 0x0
```

## Source note 8, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L90)

```text
// 0x4
```

## Source note 9, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L91)

```text
// 0x18
```

## Source note 10, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L191)

```text
// 0x0
```

## Source note 11, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L192)

```text
// 0x4
```

## Source note 12, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L193)

```text
// 0x24
```

## Source note 13, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L237)

```text
// Byteswaps each 8 bytes
```

## Source note 14, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L244)

```text
// size of modulus in 8 byte units
```

## Source note 15, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L248)

```text
// followed by modulus, followed by any private-key data
```

## Source note 16, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L254)

```text
// 0 indicates failure (but not a BOOL return value)
```

## Source note 17, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L257)

```text
// Convert XECRYPT blob into BCrypt format
```

## Source note 18, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L268)

```text
// Copy in exponent/modulus, luckily these are BE inside BCrypt blob
```

## Source note 19, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L272)

```text
// ...except modulus needs to be reversed in 64-bit chunks for BCrypt to make
```

## Source note 20, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L273)

```text
// use of it properly for some reason
```

## Source note 21, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L307)

```text
// Byteswap & reverse the input into output, as BCrypt wants MSB first
```

## Source note 22, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L313)

```text
// BCryptDecrypt only works with private keys, fortunately BCryptEncrypt
```

## Source note 23, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L314)

```text
// performs the right actions needed for us to decrypt the input
```

## Source note 24, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L324)

```text
// Reverse data & byteswap again so data is as game expects
```

## Source note 25, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L340)

```text
// BOOL return value
```

## Source note 26, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L352)

```text
// Sets bit 0 to make the parity odd
```

## Source note 27, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L365)

```text
// Store our DES state into the state.
```

## Source note 28, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L388)

```text
// DES can only do 8-byte chunks at a time!
```

## Source note 29, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L407)

```text
// 0x0
```

## Source note 30, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L408)

```text
// 0xB0
```

## Source note 31, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L418)

```text
// Decryption key schedule not needed by openluopworld/aes_128, but generated
```

## Source note 32, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L419)

```text
// to fill the context structure properly.
```

## Source note 33, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L421)

```text
// Inverse MixColumns.
```

## Source note 34, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L506)

```text
// In case inp == out.
```

## Source note 35, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L531)

```text
// Setup HMAC key
```

## Source note 36, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L532)

```text
// If > block size, use its hash
```

## Source note 37, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L577)

```text
// Retail key 0x19
```

## Source note 38, line 606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L606)

```text
// Deobscure key
```

## Source note 39, line 613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L613)

```text
// Run CBC using deobscured key
```

## Source note 40, line 622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L622)

```text
// Based on HvxKeysObscureKey
```

## Source note 41, line 623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L623)

```text
// Seems to encrypt input with per-console KEY_OBFUSCATION_KEY (key 0x18)
```

## Source note 42, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L642)

```text
// Deobscure key
```

## Source note 43, line 662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L662)

```text
// Success (signature valid)
```
