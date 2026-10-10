# Analyze: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/analyze.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/analyze.h#L20)

```text
/**
 * Build and validate the complete FunctionGraph.
 *
 * This function consolidates all analysis phases:
 * - Register: imports, helpers, PDATA functions, config functions
 * - Scan: code regions (null boundaries), data regions
 * - Discover: function blocks, calls, jump tables (iterative to fixed point)
 * - VTable: discover functions via RTTI vtables
 * - GapFill: claim orphaned code regions
 * - Merge: resolve all jumps, seal functions
 * - Validate: verify all calls resolve
 *
 * @param ctx CodegenContext with binary and config loaded
 * @return Success if graph is valid, error otherwise
 */
```
