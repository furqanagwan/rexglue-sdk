# Dxil smoke test: graphics source notes

This record preserves technical and API notes moved from `tests/dxil/dxil_smoke_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L30)

```text
// The Agility SDK the build deploys to .\D3D12\ (rexglue_deploy_d3d12_redist).
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L40)

```text
// An empty compute shader, hand-assembled:
```

## Source note 3, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L41)

```text
//   OpCapability Shader
```

## Source note 4, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L42)

```text
//   OpMemoryModel Logical GLSL450
```

## Source note 5, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L43)

```text
//   OpEntryPoint GLCompute %1 "main"
```

## Source note 6, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L44)

```text
//   OpExecutionMode %1 LocalSize 1 1 1
```

## Source note 7, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L45)

```text
//   %2 = OpTypeVoid
```

## Source note 8, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L46)

```text
//   %3 = OpTypeFunction %2
```

## Source note 9, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L47)

```text
//   %1 = OpFunction %2 None %3
```

## Source note 10, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L48)

```text
//   %4 = OpLabel
```

## Source note 11, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L52)

```text
// header, bound 5
```

## Source note 12, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L53)

```text
// OpCapability Shader
```

## Source note 13, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L55)

```text
// OpEntryPoint "main"
```

## Source note 14, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L56)

```text
// OpExecutionMode LocalSize
```

## Source note 15, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L71)

```text
// A blob over caller memory, for the validator's in-place signing.
```

## Source note 16, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L120)

```text
// SPIR-V to signed DXIL, or empty.
```

## Source note 17, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L166)

```text
// Signing writes the container digest after the magic.
```

## Source note 18, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L176)

```text
// The Agility SDK, not the OS runtime, is the one loaded.
```

## Source note 19, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L214)

```text
// D3D12Provider::IsD3D12APIAvailable loads and frees D3D12.dll before the
```

## Source note 20, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/dxil/dxil_smoke_test.cpp#L215)

```text
// provider loads it for good.
```
