# Xmodule: system source notes

This record preserves technical and API notes moved from `src/system/xmodule.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmodule.cpp#L26)

```text
// Loader data (HMODULE)
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmodule.cpp#L29)

```text
// Hijack the checksum field to store our kernel object handle.
```

## Source note 3, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmodule.cpp#L37)

```text
// Destroy the loader data.
```

## Source note 4, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmodule.cpp#L61)

```text
// Grab the object from our stashed kernel handle
```

## Source note 5, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmodule.cpp#L93)

```text
// Can only save user modules at the moment, so just redirect.
```
