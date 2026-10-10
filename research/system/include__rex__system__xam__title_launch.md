# Title launch: system source notes

This record preserves technical and API notes moved from `include/rex/system/xam/title_launch.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/title_launch.h#L17)

```text
// The outcome of a title asking XAM to launch an executable.
```

## Source note 2, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/title_launch.h#L19)

```text
// No name: return to the dashboard. There is none, so the title ends.
```

## Source note 3, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/title_launch.h#L21)

```text
// The executable this binary was compiled from, launched again.
```

## Source note 4, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/title_launch.h#L23)

```text
// Another executable. Only the compiled module exists in this binary.
```

## Source note 5, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/title_launch.h#L29)

```text
// Full guest path of the requested executable (empty for the dashboard).
```

## Source note 6, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/title_launch.h#L33)

```text
// Resolves a launch name the way XamLoaderLaunchTitle does: empty means the
```

## Source note 7, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/title_launch.h#L34)

```text
// title's own default.xex, a bare file name is taken relative to the running
```

## Source note 8, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/title_launch.h#L35)

```text
// executable's directory. Comparison with the running module ignores case.
```
