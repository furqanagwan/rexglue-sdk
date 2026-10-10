# Codegen: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/codegen.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen.h#L26)

```text
/**
 * Pipeline orchestrator for code generation.
 *
 * Usage:
 *   auto pipeline = CodegenPipeline::Create(configPath);
 *   if (!pipeline) { handle error }
 *   auto result = pipeline->Run();
 */
```

## Source note 2, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen.h#L38)

```text
// Non-copyable, movable
```

## Source note 3, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen.h#L44)

```text
/**
   * Create pipeline from config file path.
   * Loads XEX, creates Runtime and CodegenContext.
   *
   * @param configPath Path to TOML config file
   * @return Pipeline on success, error on failure
   */
```
