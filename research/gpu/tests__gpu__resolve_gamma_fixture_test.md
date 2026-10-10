# Resolve gamma fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/resolve_gamma_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_gamma_fixture_test.cpp#L42)

```text
// Draws color into a kSize square render target of source_format and
```

## Source note 2, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_gamma_fixture_test.cpp#L43)

```text
// resolves it with format. Returns the center texel.
```

## Source note 3, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_gamma_fixture_test.cpp#L86)

```text
// Linear 0x80 (0.502) is 192 on the PWL curve, which decodes to 516/1023
```

## Source note 4, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_gamma_fixture_test.cpp#L87)

```text
// (8-bit 129, 10-bit 516). Raw copies of the encoded bytes give 192.
```

## Source note 5, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_gamma_fixture_test.cpp#L96)

```text
// Alpha isn't gamma encoded.
```

## Source note 6, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_gamma_fixture_test.cpp#L99)

```text
// A destination that isn't 8_8_8_8 gets the same linear values.
```

## Source note 7, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_gamma_fixture_test.cpp#L117)

```text
// 1.0 as a signed repeating fraction is 127; a raw copy would keep 255.
```

## Source note 8, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_gamma_fixture_test.cpp#L123)

```text
// An unsigned integer destination takes the value itself, clamped: 1.
```
