# Xfile: system source notes

This record preserves technical and API notes moved from `include/rex/system/xfile.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L28)

```text
// https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/ns-ntifs-_file_directory_information
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L32)

```text
// 0x0
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L33)

```text
// 0x4
```

## Source note 4, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L34)

```text
// 0x8
```

## Source note 5, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L35)

```text
// 0x10
```

## Source note 6, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L36)

```text
// 0x18
```

## Source note 7, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L37)

```text
// 0x20
```

## Source note 8, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L38)

```text
// 0x28 size in bytes
```

## Source note 9, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L39)

```text
// 0x30
```

## Source note 10, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L40)

```text
// 0x38 X_FILE_ATTRIBUTES
```

## Source note 11, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L41)

```text
// 0x3C
```

## Source note 12, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L42)

```text
// 0x40
```

## Source note 13, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L90)

```text
// Don't do within the global critical region because invalidation callbacks
```

## Source note 14, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L91)

```text
// may be triggered (as per the usual rule of not doing I/O within the global
```

## Source note 15, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xfile.h#L92)

```text
// critical region).
```
