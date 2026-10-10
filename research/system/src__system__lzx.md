# Lzx: system source notes

This record preserves technical and API notes moved from `src/system/lzx.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/lzx.cpp#L117)

```text
// zero the window and then copy window_data to the end of it
```

## Source note 2, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/lzx.cpp#L155)

```text
// 0 byte patches need us to remove 4 byte from next
```

## Source note 3, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/lzx.cpp#L156)

```text
// patch addr because of patch_data field
```

## Source note 4, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/lzx.cpp#L161)

```text
// fill with 0
```

## Source note 5, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/lzx.cpp#L164)

```text
// copy from old -> new
```

## Source note 6, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/lzx.cpp#L168)

```text
// delta patch
```

## Source note 7, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/lzx.cpp#L169)

```text
// -4 because of patch_data field
```
