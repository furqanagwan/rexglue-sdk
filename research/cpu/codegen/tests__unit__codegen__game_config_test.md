# Game config test: codegen source notes

This record preserves technical and API notes moved from `tests/unit/codegen/game_config_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/game_config_test.cpp#L129)

```text
// 'A' is not allowed
```

## Source note 2, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/game_config_test.cpp#L151)

```text
// 24 bpp plus alpha, as the Store validator requires.
```

## Source note 3, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/game_config_test.cpp#L160)

```text
// A flat color compresses: under a tenth of the raw RGBA size plus the
```

## Source note 4, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/game_config_test.cpp#L161)

```text
// fixed PNG overhead (the 1920x1080 splash is about 20 KB, not 8 MB).
```
