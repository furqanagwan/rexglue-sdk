# Kernel fixture: kernel source notes

This record preserves technical and API notes moved from `tests/kernel/kernel_fixture.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/kernel_fixture.h#L104)

```text
// Opens `path` inside mounted root `root_name` for writing, as the guest's
```

## Source note 2, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/kernel_fixture.h#L105)

```text
// NtCreateFile would, and wraps it in a kernel file object.
```

## Source note 3, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/kernel_fixture.h#L131)

```text
// A file whose host flush fails, standing in for a disk that rejects it.
```
