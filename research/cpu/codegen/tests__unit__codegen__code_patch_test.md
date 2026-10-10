# Code patch test: codegen source notes

This record preserves technical and API notes moved from `tests/unit/codegen/code_patch_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L49)

```text
// One executable section: li r3,1 ; blr ; then padding.
```

## Source note 2, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L173)

```text
// the module's own image is untouched
```

## Source note 3, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L213)

```text
// A disabled overlapping or broken patch doesn't matter.
```

## Source note 4, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L223)

```text
// This synthetic image has no exception directory, so analysis stops in
```

## Source note 5, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L224)

```text
// registration, after the patches were applied.
```

## Source note 6, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L231)

```text
// A refused patch stops analysis before it starts.
```

## Source note 7, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L260)

```text
/*enabled=*/
```

## Source note 8, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L279)

```text
// Writing the byte already there switches nothing.
```

## Source note 9, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L291)

```text
// The second word is blr.
```

## Source note 10, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L297)

```text
// Nor turn another instruction into one.
```

## Source note 11, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L323)

```text
// the later entry wins
```

## Source note 12, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L344)

```text
// Ids are compared upper case, so the later entry replaces the first.
```

## Source note 13, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L388)

```text
// "cheat" is the earlier name for "mod"
```

## Source note 14, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L389)

```text
// A switchable patch may be a flag alone; a fixed one may not set registers.
```

## Source note 15, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L404)

```text
// An lr test needs the link register, which skip_lr drops.
```

## Source note 16, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L405)

```text
/*keeps_lr=*/
```

## Source note 17, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/code_patch_test.cpp#L406)

```text
// Sets go on instructions in code.
```
