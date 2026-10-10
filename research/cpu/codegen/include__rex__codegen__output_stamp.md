# Output stamp: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/output_stamp.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_stamp.h#L27)

```text
/// What a module's output was generated from, and what it produced.
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_stamp.h#L30)

```text
///< basenames, relative to the output directory
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_stamp.h#L32)

```text
/// nullopt when missing, unreadable, or malformed.
```

## Source note 4, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_stamp.h#L38)

```text
/// Hash everything that can change emitted output for one module. A missing
```

## Source note 5, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_stamp.h#L39)

```text
/// input contributes a "missing" marker, so a file appearing later still
```

## Source note 6, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_stamp.h#L40)

```text
/// changes the fingerprint. sdkVersion must be stable across commits
```

## Source note 7, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_stamp.h#L41)

```text
/// (floor plus channel, e.g. "0.10.0-dev").
```

## Source note 8, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_stamp.h#L49)

```text
/// Make-syntax dependency file. `target` must match the consuming build rule's
```

## Source note 9, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/output_stamp.h#L50)

```text
/// declared output byte for byte or the rule rejects the file.
```
