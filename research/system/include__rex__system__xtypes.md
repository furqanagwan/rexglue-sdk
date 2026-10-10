# Xtypes: system source notes

This record preserves technical and API notes moved from `include/rex/system/xtypes.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L18)

```text
// be<T>
```

## Source note 2, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L25)

```text
// NT_STATUS (STATUS_*)
```

## Source note 3, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L26)

```text
// https://msdn.microsoft.com/en-us/library/cc704588.aspx
```

## Source note 4, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L77)

```text
// Win32 error codes (ERROR_*)
```

## Source note 5, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L78)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx
```

## Source note 6, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L106)

```text
// HRESULT codes
```

## Source note 7, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L122)

```text
// MEM_*, used by NtAllocateVirtualMemory
```

## Source note 8, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L135)

```text
// from Valve SDK
```

## Source note 9, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L138)

```text
// PAGE_*, used by NtAllocateVirtualMemory
```

## Source note 10, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L153)

```text
// Sockets/networking
```

## Source note 11, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L157)

```text
// https://docs.microsoft.com/en-us/windows/win32/api/ntdef/ns-ntdef-list_entry
```

## Source note 12, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L159)

```text
// next entry / head
```

## Source note 13, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L160)

```text
// previous entry / head
```

## Source note 14, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L165)

```text
// 0x0 pointer to next entry
```

## Source note 15, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L169)

```text
// https://www.nirsoft.net/kernel_struct/vista/SLIST_HEADER.html
```

## Source note 16, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L171)

```text
// 0x0
```

## Source note 17, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L172)

```text
// 0x4
```

## Source note 18, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L173)

```text
// 0x6
```

## Source note 19, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L182)

```text
// Typed guest pointer - holds a guest address but provides type documentation.
```

## Source note 20, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xtypes.h#L183)

```text
// Implicitly converts to/from uint32_t via the be<uint32_t> member.
```
