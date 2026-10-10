# Object table test: kernel source notes

This record preserves technical and API notes moved from `tests/unit/kernel/object_table_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 1

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L1)

```text
/**
 * Unit tests for kernel object system (XObject and ObjectTable)
 *
 * Tests handle management, reference counting, and name mapping.
 */
```

## Source note 2, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L18)

```text
// Test Fixtures and Helpers
```

## Source note 3, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L21)

```text
// Minimal XObject subclass for testing
```

## Source note 4, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L28)

```text
// Track destructor calls for leak detection
```

## Source note 5, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L35)

```text
// Reset destructor count before each test
```

## Source note 6, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L40)

```text
// Initialize logging once
```

## Source note 7, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L50)

```text
// object_ref Smart Pointer Tests
```

## Source note 8, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L67)

```text
// Object starts with ref count of 1 from constructor
```

## Source note 9, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L75)

```text
// Destructor should release, destroying object
```

## Source note 10, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L88)

```text
// Copy - should retain
```

## Source note 11, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L90)

```text
// Still alive
```

## Source note 12, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L92)

```text
// ref2 destroyed, but ref1 still holds
```

## Source note 13, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L95)

```text
// Both refs destroyed
```

## Source note 14, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L109)

```text
// Moved from
```

## Source note 15, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L126)

```text
// Copy assign
```

## Source note 16, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L175)

```text
// Not destroyed
```

## Source note 17, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L177)

```text
// Clean up manually
```

## Source note 18, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L187)

```text
// obj has ref count 1
```

## Source note 19, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L190)

```text
// Should retain, ref count now 2
```

## Source note 20, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L193)

```text
// ref destroyed, ref count back to 1
```

## Source note 21, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L196)

```text
// Final release
```

## Source note 22, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L201)

```text
// ObjectTable Handle Allocation Tests
```

## Source note 23, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L216)

```text
// 0xF8000000
```

## Source note 24, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L218)

```text
// Handle should be in object's handle list
```

## Source note 25, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L234)

```text
// First handle should be slot 1: kHandleBase + (1 << 2) = 0xF8000004
```

## Source note 26, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L257)

```text
// Handles increment by 4 (slot << 2)
```

## Source note 27, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L265)

```text
// ObjectTable Handle Lookup Tests
```

## Source note 28, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L302)

```text
// ObjectTable Handle Reference Counting Tests
```

## Source note 29, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L317)

```text
// Need two releases to remove
```

## Source note 30, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L322)

```text
// This should remove it
```

## Source note 31, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L340)

```text
// Handle should be gone
```

## Source note 32, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L369)

```text
// Both handles refer to same object
```

## Source note 33, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L375)

```text
// Object should have both handles
```

## Source note 34, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L382)

```text
// ObjectTable Handle Release Tests
```

## Source note 35, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L394)

```text
// ReleaseHandle decrements ref count; at 0 it removes the handle
```

## Source note 36, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L409)

```text
// Keep alive after table releases
```

## Source note 37, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L423)

```text
// ObjectTable Name Mapping Tests
```

## Source note 38, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L470)

```text
// Different case should still collide
```

## Source note 39, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L508)

```text
// ObjectTable Reset and Bulk Operations
```

## Source note 40, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L524)

```text
// Objects have ref count 2: 1 from new, 1 from AddHandle's Retain
```

## Source note 41, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L525)

```text
// Release our initial ref so table owns them exclusively
```

## Source note 42, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L534)

```text
// Now Reset's Release brings ref count from 1 to 0, destroying them
```

## Source note 43, line 555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L555)

```text
// TODO: Tests requiring kernel integration
```

## Source note 44, line 558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L558)

```text
// TODO: Test handle 0xFFFFFFFF (CurrentProcess) - requires full KernelState
```

## Source note 45, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L559)

```text
// TODO: Test handle 0xFFFFFFFE (CurrentThread) - requires XThread integration
```

## Source note 46, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L560)

```text
// TODO: Test GetObjectsByType<T>() with real typed objects
```

## Source note 47, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L561)

```text
// TODO: Test GetObjectByName with existing object - requires kernel_state for RetainHandle
```

## Source note 48, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/kernel/object_table_test.cpp#L562)

```text
// TODO: Test case-insensitive name lookup via GetObjectByName
```
