# Tessellation fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/tessellation_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/tessellation_fixture_test.cpp#L50)

```text
// alloc position; exec_end (mad oPos, r0.yzxx, c0, c1): the domain location
```

## Source note 2, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/tessellation_fixture_test.cpp#L51)

```text
// (u, v) in r0.yz scaled by c0 and offset by c1, w from c1.w. The patch index
```

## Source note 3, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/tessellation_fixture_test.cpp#L52)

```text
// in r0.x is 0 here, so it zeroes z and w before the offset.
```

## Source note 4, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/tessellation_fixture_test.cpp#L56)

```text
// Component-relative: x from y, y from z, z and w from x.
```

## Source note 5, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/tessellation_fixture_test.cpp#L64)

```text
// Fills the target black, then draws one tessellated quad patch in white and
```

## Source note 6, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/tessellation_fixture_test.cpp#L65)

```text
// returns the resolved texels.
```

## Source note 7, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/tessellation_fixture_test.cpp#L95)

```text
// Factors of 1 (the guest adds 1): one quad over the whole domain.
```

## Source note 8, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/tessellation_fixture_test.cpp#L134)

```text
// White inside the patch, the black fill outside, away from the edges.
```
