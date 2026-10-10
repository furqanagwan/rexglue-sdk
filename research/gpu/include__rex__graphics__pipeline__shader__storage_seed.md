# Storage seed: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/storage_seed.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L19)

```text
/// The shape of a persistent shader storage file (the "shareable" files the
```

## Source note 2, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L20)

```text
/// pipeline cache keeps per title): a header, then records that each start
```

## Source note 3, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L21)

```text
/// with the 64-bit XXH3 hash of the bytes they cover, which is also the
```

## Source note 4, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L22)

```text
/// record's identity.
```

## Source note 5, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L24)

```text
/// The header a file of the running SDK's version starts with.
```

## Source note 6, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L26)

```text
/// Fixed-size records (pipeline descriptions, `.xpso`): the record's size;
```

## Source note 7, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L27)

```text
/// the hash covers the rest of it. 0: shader records (`.xsh`), a 12-byte
```

## Source note 8, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L28)

```text
/// head (the hash, then a 32-bit field whose low 31 bits are the ucode's
```

## Source note 9, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L29)

```text
/// dword count) and the ucode, which the hash covers.
```

## Source note 10, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L34)

```text
// nothing shipped for this file
```

## Source note 11, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L35)

```text
// shipped for another SDK version or damaged: ignored
```

## Source note 12, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L36)

```text
// the player had none (or another version's): shipped copy used
```

## Source note 13, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L37)

```text
// shipped records the player lacked appended
```

## Source note 14, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L38)

```text
// the player has every shipped record
```

## Source note 15, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L39)

```text
// the player's file could not be written
```

## Source note 16, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L44)

```text
// records copied or appended
```

## Source note 17, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L48)

```text
/// Brings the shipped storage file `shipped` into the player's `user` file,
```

## Source note 18, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L49)

```text
/// before the pipeline cache opens it: a player without one (or with another
```

## Source note 19, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L50)

```text
/// version's) gets the shipped file; otherwise the shipped records the player
```

## Source note 20, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L51)

```text
/// lacks are appended after the player's valid records. Damaged tails stop
```

## Source note 21, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L52)

```text
/// reading, as the pipeline cache's own loading does. The file is rewritten
```

## Source note 22, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L53)

```text
/// beside and moved into place, so a failure leaves the player's file as it
```

## Source note 23, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/storage_seed.h#L54)

```text
/// was.
```
