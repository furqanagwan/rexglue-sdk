# Function table layout test: codegen source notes

This record preserves technical and API notes moved from `tests/unit/codegen/function_table_layout_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/function_table_layout_test.cpp#L27)

```text
// FIFA Street: the launcher (1.75 MiB at 82000000) and its game DLL at
```

## Source note 2, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/function_table_layout_test.cpp#L28)

```text
// 82300000; the launcher's table after its image would cross the DLL.
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/function_table_layout_test.cpp#L35)

```text
// The DLL's own table still follows its image.
```

## Source note 4, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/function_table_layout_test.cpp#L37)

```text
// The launcher's goes past every image, on a 64 KiB boundary, and the two
```

## Source note 5, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/function_table_layout_test.cpp#L38)

```text
// tables do not overlap.
```

## Source note 6, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/function_table_layout_test.cpp#L42)

```text
// Nothing lands on an image.
```
