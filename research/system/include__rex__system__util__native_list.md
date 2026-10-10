# Native list: system source notes

This record preserves technical and API notes moved from `include/rex/system/util/native_list.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L20)

```text
// List is designed for storing pointers to objects in the guest heap.
```

## Source note 2, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L21)

```text
// All values in the list should be assumed to be in big endian.
```

## Source note 3, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L23)

```text
// Pass LIST_ENTRY pointers.
```

## Source note 4, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L24)

```text
// struct MYOBJ {
```

## Source note 5, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L25)

```text
//   uint32_t stuff;
```

## Source note 6, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L26)

```text
//   LIST_ENTRY list_entry; <-- pass this
```

## Source note 7, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L54)

```text
// Guest-memory linked list utilities.
```

## Source note 8, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L55)

```text
// VirtualTranslator is any type with TranslateVirtual<T*>(uint32_t)
```

## Source note 9, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L56)

```text
// and HostToGuestVirtual(void*) methods (e.g. memory::Memory*).
```

## Source note 10, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L57)

```text
// Overloads also accept a raw uint32_t guest pointer in place of the
```

## Source note 11, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L58)

```text
// translator when the caller already has the guest address.
```

## Source note 12, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L176)

```text
// Typed intrusive list built on X_LIST_ENTRY.
```

## Source note 13, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L177)

```text
// TObject is the containing struct, EntryListOffset is offsetof the
```

## Source note 14, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/native_list.h#L178)

```text
// X_LIST_ENTRY member within TObject.
```
