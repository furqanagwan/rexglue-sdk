# Notify test: kernel source notes

This record preserves technical and API notes moved from `tests/kernel/notify_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/notify_test.cpp#L28)

```text
// Notification ids pack mask_index:6, version:9 and local_id:16.
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/notify_test.cpp#L33)

```text
// Mask bit 0 is left out: the kernel sends its startup notifications to the
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/notify_test.cpp#L34)

```text
// first listener with that bit, which only the dedicated case below creates.
```

## Source note 4, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/notify_test.cpp#L55)

```text
/*max_version=*/
```

## Source note 5, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/notify_test.cpp#L58)

```text
// other mask bit
```

## Source note 6, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/notify_test.cpp#L59)

```text
// newer than max_version
```

## Source note 7, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/notify_test.cpp#L60)

```text
// exactly max_version
```

## Source note 8, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/notify_test.cpp#L78)

```text
// the first b
```

## Source note 9, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/notify_test.cpp#L91)

```text
// XCloseHandle on the listener: the kernel stops holding and feeding it.
```

## Source note 10, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/notify_test.cpp#L102)

```text
// XN_SYS_UI on/off, XN_SYS_SIGNINCHANGED x2, input device changed/config x2 each.
```
