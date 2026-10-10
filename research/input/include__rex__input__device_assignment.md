# Device assignment: input source notes

This record preserves technical and API notes moved from `include/rex/input/device_assignment.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device_assignment.h#L24)

```text
/// Devices arrive sorted by ordinal.
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device_assignment.h#L27)

```text
/// An empty result means the guest sees X_ERROR_DEVICE_NOT_CONNECTED.
```

## Source note 3, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device_assignment.h#L31)

```text
/// Device ordinal N feeds guest user N. Synthetic devices feed user 0.
```

## Source note 4, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device_assignment.h#L41)

```text
/// Every device feeds guest user 0. Users 1 and up report not connected. For
```

## Source note 5, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/device_assignment.h#L42)

```text
/// single-player titles that only ever poll user 0.
```
