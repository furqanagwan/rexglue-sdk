# Test support: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/test_support.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/test_support.h#L23)

```text
/**
 * @brief Lightweight Module for loading raw binary test data
 *
 * TestModule provides the Module interface needed by FunctionScanner and
 * Recompiler without requiring a full Runtime/FunctionDispatcher setup. It accepts
 * raw binary data by reference (caller owns the buffer).
 *
 * Usage:
 *   std::vector<uint8_t> data = load_binary_file(...);
 *   TestModule module;
 *   module.Load(0x82010000, data.data(), data.size());
 *   recompiler.module_ = &module;
 */
```

## Source note 2, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/test_support.h#L41)

```text
/**
   * @brief Load binary data for analysis
   * @param base_address Guest virtual address where code is loaded
   * @param data Pointer to binary data (caller owns, must outlive TestModule usage)
   * @param size Size of binary data in bytes
   */
```

## Source note 3, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/test_support.h#L49)

```text
// Module interface overrides
```

## Source note 4, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/test_support.h#L66)

```text
/**
 * @brief Analyze a test binary using map symbols as function entry points.
 *
 * Filters symbols to test_ prefixed entries, adds them as functions to
 * ctx.graph with single blocks, then scans for bl instructions and
 * registers call edges.
 *
 * @param ctx         Codegen context whose graph will be populated
 * @param testName    Stem name used for function naming (e.g. "addi")
 * @param symbols     Address-to-name map from parse_map_file()
 * @param baseAddress Base address the binary was linked at
 * @param data        Pointer to raw binary data
 * @param dataSize    Size of binary data in bytes
 */
```
