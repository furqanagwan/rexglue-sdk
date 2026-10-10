# Code patches: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/code_patches.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L23)

```text
/**
 * Writes every enabled `[[patch]]` into the image, before instructions are
 * decoded, so the generated C++ is built from the patched code.
 *
 * Only executable sections can be patched: the runtime loads the original
 * image into guest memory, so a data patch would never reach the running
 * title. A disabled patch is skipped. Nothing is written, and an error names
 * the patch, when an enabled patch is malformed, reaches outside the code
 * sections, or overlaps another enabled patch.
 *
 * @return The names of the applied patches, in definition order.
 */
```

## Source note 2, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L35)

```text
/// Writes the enabled, non-switchable patches into codegen's copy of the
```

## Source note 3, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L36)

```text
/// image. Returns their names.
```

## Source note 4, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L40)

```text
/// A switchable patch as the title's patch table lists it.
```

## Source note 5, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L43)

```text
///< Its state when the title starts
```

## Source note 6, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L49)

```text
///< By guest address
```

## Source note 7, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L50)

```text
///< By the guest address they run before
```

## Source note 8, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L53)

```text
/// Checks the switchable patches and works out, per instruction word, the
```

## Source note 9, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L54)

```text
/// original and patched versions. They are not written into the image, so
```

## Source note 10, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L55)

```text
/// analysis sees the original code. Every write must stay in code, and
```

## Source note 11, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L56)

```text
/// neither version of a word may be a branch, call, trap or system call:
```

## Source note 12, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L57)

```text
/// switching one of those would change the control flow analysis found.
```

## Source note 13, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L58)

```text
/// A patch's register sets must be at word addresses in code, and one keyed
```

## Source note 14, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/code_patches.h#L59)

```text
/// on lr needs the link register kept (not skip_lr).
```
