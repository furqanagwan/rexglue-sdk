# Jump table test: codegen source notes

This record preserves technical and API notes moved from `tests/unit/codegen/jump_table_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/jump_table_test.cpp#L27)

```text
// lis r9/r11,0; slwi r10,r3,2; addi r9,r9/r11,0x2000; lwzx r8,rA,rB;
```

## Source note 2, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/jump_table_test.cpp#L28)

```text
// mtctr r8; bctr; blr; blr.
```
