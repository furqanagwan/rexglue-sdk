# Shader replacement fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/shader_replacement_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/shader_replacement_fixture_test.cpp#L31)

```text
// The ucode hash the command processor gives kPixelShader: XXH3 of the
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/shader_replacement_fixture_test.cpp#L32)

```text
// dwords as the guest stores them, big-endian.
```

## Source note 3, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/shader_replacement_fixture_test.cpp#L43)

```text
// Draws an 8x8 rectangle of `color` with kPixelShader, resolves it, and reads
```

## Source note 4, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/shader_replacement_fixture_test.cpp#L44)

```text
// the first texel; false if the fixture can't run.
```

## Source note 5, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/shader_replacement_fixture_test.cpp#L53)

```text
// Otherwise draws are dropped while their pipelines compile.
```

## Source note 6, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/shader_replacement_fixture_test.cpp#L84)

```text
// The replacement draws magenta whatever the guest asks for.
```

## Source note 7, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/shader_replacement_fixture_test.cpp#L87)

```text
// The fixtures' cvars outlive them.
```
