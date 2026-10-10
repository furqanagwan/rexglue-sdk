# Hash: core source notes

This record preserves technical and API notes moved from `include/rex/hash.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hash.h#L19)

```text
// Enable inline implementations and advanced API (XXH3)
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hash.h#L24)

```text
// Can't use XXH_X86DISPATCH because XXH is calculated on multiple threads,
```

## Source note 3, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hash.h#L25)

```text
// while the dispatch writes the result (multiple pointers without any
```

## Source note 4, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hash.h#L26)

```text
// synchronization) to XXH_g_dispatch at the first call.
```

## Source note 5, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hash.h#L32)

```text
// For use in unordered_sets and unordered_maps (primarily multisets and
```

## Source note 6, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hash.h#L33)

```text
// multimaps, with manual collision resolution), where the hash is calculated
```

## Source note 7, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hash.h#L34)

```text
// externally (for instance, as XXH3), possibly requiring context data rather
```

## Source note 8, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hash.h#L35)

```text
// than a pure function to calculate the hash
```

## Source note 9, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hash.h#L48)

```text
/// 128-bit XXH3 digest as a 32-character lowercase hex string. For fingerprints
```

## Source note 10, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hash.h#L49)

```text
/// and cache keys, not for anything security bearing.
```

## Source note 11, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hash.h#L52)

```text
/// Same digest over a file's contents, streamed in chunks. Empty string when
```

## Source note 12, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/hash.h#L53)

```text
/// the file cannot be opened.
```
