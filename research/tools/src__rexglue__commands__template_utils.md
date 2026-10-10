# Template utils: tools source notes

This record preserves technical and API notes moved from `src/rexglue/commands/template_utils.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/template_utils.h#L65)

```text
// `original` keeps the letters' case but joins words with one underscore:
```

## Source note 2, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/template_utils.h#L66)

```text
// it names files and CMake targets and is a C++ identifier in
```

## Source note 3, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/template_utils.h#L67)

```text
// REX_DEFINE_APP. That is also exactly what earlier versions wrote for a
```

## Source note 4, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/template_utils.h#L68)

```text
// lowercase name, so an existing project's manifest name ("my_game") still
```

## Source note 5, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/template_utils.h#L69)

```text
// regenerates rexglue.cmake pointing at its own files. Upstream dropped the
```

## Source note 6, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/rexglue/commands/template_utils.h#L70)

```text
// separators ("mygame"), which would break those projects.
```
