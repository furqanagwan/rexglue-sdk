# D3d12 provider test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/d3d12_provider_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/d3d12_provider_test.cpp#L24)

```text
// Adapter selection is read once at creation, so each case sets it and
```

## Source note 2, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/d3d12_provider_test.cpp#L25)

```text
// restores the default afterwards.
```
