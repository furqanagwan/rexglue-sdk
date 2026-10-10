# Utf8: core source notes

This record preserves technical and API notes moved from `include/rex/string/utf8.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string/utf8.h#L25)

```text
// UTF-8 path separator constants
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string/utf8.h#L40)

```text
// Splits the given haystack on any delimiters (needles) and returns all parts.
```

## Source note 3, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string/utf8.h#L59)

```text
// find_first_of string, case insensitive.
```

## Source note 4, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string/utf8.h#L71)

```text
// Splits the given path on any valid path separator and returns all parts.
```

## Source note 5, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string/utf8.h#L74)

```text
// Joins two path segments with the given separator.
```

## Source note 6, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string/utf8.h#L110)

```text
// Replaces all path separators with the given value and removes redundant
```

## Source note 7, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string/utf8.h#L111)

```text
// separators.
```

## Source note 8, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string/utf8.h#L119)

```text
// Find the top directory name or filename from a path.
```

## Source note 9, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string/utf8.h#L134)

```text
// Get parent path of the given directory or filename.
```

## Source note 10, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/string/utf8.h#L142)

```text
// Canonicalizes a path, removing ..'s.
```
