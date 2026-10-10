# Phase validate: codegen source notes

This record preserves technical and API notes moved from `src/codegen/phase_validate.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L33)

```text
// Validate all calls resolve
```

## Source note 2, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L47)

```text
// A config boundary is an assertion the binary cannot make for itself, so one
```

## Source note 3, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L48)

```text
// the graph contradicts has to say so: otherwise the author sees a full rebuild
```

## Source note 4, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L49)

```text
// change nothing and has no way to tell why. Reported, never fatal. A PDATA
```

## Source note 5, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L50)

```text
// entry inside a config extent is the normal MSVC layout for a function with an
```

## Source note 6, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L51)

```text
// SEH funclet, so only discovery carving an entry point out of a declared range
```

## Source note 7, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L52)

```text
// is worth a warning.
```

## Source note 8, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L71)

```text
// The declared size, not node->size(): discover() grows a node to cover its
```

## Source note 9, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L72)

```text
// blocks, and only what the author wrote is a boundary claim.
```

## Source note 10, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L127)

```text
// Check if target is within this function's blocks
```

## Source note 11, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L133)

```text
// Check if target is within this function's overall bounds
```

## Source note 12, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L134)

```text
// (handles cases where blocks don't cover all owned addresses)
```

## Source note 13, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L140)

```text
// Check if target is another function's entry point
```

## Source note 14, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L145)

```text
// Check if target is an import
```

## Source note 15, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L150)

```text
// Check if target is inside any other function's blocks
```

## Source note 16, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L151)

```text
// (handles cross-function internal branches due to gap-fill merging)
```

## Source note 17, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L155)

```text
// Target is inside another function - treat as internal to that function
```

## Source note 18, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L156)

```text
// This can happen when gap-fill created overlapping regions
```

## Source note 19, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L162)

```text
// Target is not in any function - this is an error that must stop the build
```

## Source note 20, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L172)

```text
// Check if target is inside another function - this is a special case
```

## Source note 21, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L173)

```text
// where code branches to another function's internal address
```

## Source note 22, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L176)

```text
// Target is not in any function - this is an error (call the cops)
```

## Source note 23, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L181)

```text
// If target is inside another function, it will be handled as a tail call
```

## Source note 24, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L182)

```text
// to that function's internal label during code generation
```

## Source note 25, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_validate.cpp#L207)

```text
// anonymous namespace
```
