# Guest path: system source notes

This record preserves technical and API notes moved from `src/system/guest_path.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/guest_path.cpp#L22)

```text
// Manifest / config consumers expect POSIX-style guest paths: forward
```

## Source note 2, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/guest_path.cpp#L23)

```text
// slashes, no device prefix, lowercase. The runtime VFS tolerates either
```

## Source note 3, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/guest_path.cpp#L24)

```text
// separator, so converting backslashes here keeps writers (TOML) happy.
```
