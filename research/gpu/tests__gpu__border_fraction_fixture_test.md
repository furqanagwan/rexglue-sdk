# Border fraction fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/border_fraction_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 1

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/border_fraction_fixture_test.cpp#L1)

```text
// Synthetic getBCF readbacks. No title microcode or texture assets are used.
```

## Source note 2, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/border_fraction_fixture_test.cpp#L37)

```text
// Write r1 rather than an export register.
```

## Source note 3, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/border_fraction_fixture_test.cpp#L43)

```text
// tf1, r1.xyz -> r2.xyzw; explicit LOD, no anisotropy or offsets.
```

## Source note 4, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/border_fraction_fixture_test.cpp#L57)

```text
// Uniform data throughout padded tiles and mip storage makes the expected
```

## Source note 5, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/border_fraction_fixture_test.cpp#L58)

```text
// border weight independent of data layout, while exercising real texture loads.
```

## Source note 6, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/border_fraction_fixture_test.cpp#L86)

```text
// Deliberately neither forced border color. getBCF must ignore it.
```

## Source note 7, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/border_fraction_fixture_test.cpp#L118)

```text
// getBCF's YZW are zero.
```

## Source note 8, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/border_fraction_fixture_test.cpp#L149)

```text
// Same fetch constant still returns actual texels.
```
