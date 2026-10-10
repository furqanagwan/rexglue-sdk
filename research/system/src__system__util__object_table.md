# Object table: system source notes

This record preserves technical and API notes moved from `src/system/util/object_table.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L32)

```text
// Release all objects.
```

## Source note 2, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L47)

```text
// Find a free slot.
```

## Source note 3, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L59)

```text
// Never allow 0 handles.
```

## Source note 4, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L65)

```text
// Table out of slots, expand.
```

## Source note 5, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L71)

```text
// Never allow 0 handles.
```

## Source note 6, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L86)

```text
// Zero out new entries.
```

## Source note 7, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L105)

```text
// Find a free slot.
```

## Source note 8, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L109)

```text
// Stash.
```

## Source note 9, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L117)

```text
// Retain so long as the object is in the table.
```

## Source note 10, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L140)

```text
// Release the ref that LookupObject took
```

## Source note 11, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L169)

```text
// No more references. Remove it from the table.
```

## Source note 12, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L196)

```text
// Walk the object's handles and remove this one.
```

## Source note 13, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L204)

```text
// Remove object name from mapping to prevent naming collision.
```

## Source note 14, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L211)

```text
// Release now that the object has been removed from the table.
```

## Source note 15, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L254)

```text
// Lower 2 bits are ignored.
```

## Source note 16, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L263)

```text
// Generic lookup
```

## Source note 17, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L282)

```text
// Lower 2 bits are ignored.
```

## Source note 18, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L285)

```text
// Verify slot.
```

## Source note 19, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L293)

```text
// Retain the object pointer.
```

## Source note 20, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L321)

```text
// assert_always();
```

## Source note 21, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L341)

```text
// Names are case-insensitive.
```

## Source note 22, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L350)

```text
// Names are case-insensitive.
```

## Source note 23, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L351)

```text
// Look up handle under name lock only -- do NOT hold name_mutex_ while
```

## Source note 24, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L352)

```text
// acquiring global lock (RemoveHandle takes global -> name ordering).
```

## Source note 25, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L365)

```text
// Retain under global lock via normal LookupObject path.
```

## Source note 26, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L366)

```text
// The handle may have been removed between releasing name_mutex_ and
```

## Source note 27, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L367)

```text
// acquiring global lock -- LookupObject returns nullptr in that case.
```

## Source note 28, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/util/object_table.cpp#L391)

```text
// entry.object = nullptr;
```
