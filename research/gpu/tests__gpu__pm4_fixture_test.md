# Pm4 fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/pm4_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pm4_fixture_test.cpp#L46)

```text
// Without a swap the host-order store lands byte-reversed for the guest.
```

## Source note 2, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pm4_fixture_test.cpp#L72)

```text
// Overwrites the nested buffer's second dword only if it ran first.
```
