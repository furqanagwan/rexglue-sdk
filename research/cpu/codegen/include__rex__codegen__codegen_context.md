# Codegen context: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/codegen_context.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L37)

```text
// Forward declarations
```

## Source note 2, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L43)

```text
/**
 * Analysis state holding binary-derived data and analysis results.
 * This data is populated during analysis and should not be mutated after.
 * Separates analysis state from user-provided config.
 */
```

## Source note 3, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L49)

```text
// Binary-derived (set once from BinaryView)
```

## Source note 4, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L50)

```text
///< "xex" or "elf"
```

## Source note 5, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L51)

```text
///< Image base address
```

## Source note 6, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L52)

```text
///< Entry point address
```

## Source note 7, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L53)

```text
///< Total image size
```

## Source note 8, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L55)

```text
// Analysis results
```

## Source note 9, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L56)

```text
///< Sections from binary
```

## Source note 10, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L57)

```text
///< Discovered functions
```

## Source note 11, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L58)

```text
///< Chunk lookup
```

## Source note 12, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L60)

```text
// Auto-detected ABI helpers (0 = not found)
```

## Source note 13, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L70)

```text
// Merged results (user hints + analysis-detected)
```

## Source note 14, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L71)

```text
///< addr -> size
```

## Source note 15, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L72)

```text
///< bctr addresses
```

## Source note 16, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L73)

```text
///< Handler addresses
```

## Source note 17, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L74)

```text
///< EH-discovered function addresses
```

## Source note 18, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L77)

```text
/**
 * Unified context for the entire codegen pipeline.
 *
 * This class owns all the core data structures used throughout analysis
 * and code generation. It replaces the previous scattered ownership where
 * Recompiler owned some data and AnalysisContext owned other data.
 *
 * Single source of truth for:
 * - Binary data (BinaryView)
 * - Function graph (all functions including imports)
 * - Configuration
 * - Analysis errors
 * - Scan artifacts
 */
```

## Source note 19, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L93)

```text
// === FACTORY ===
```

## Source note 20, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L94)

```text
/**
   * Create a CodegenContext from config file path and Runtime.
   *
   * This is the primary way to create a context. It:
   * 1. Loads configuration from the TOML file
   * 2. Loads the XEX via Runtime
   * 3. Creates BinaryView from the loaded module
   *
   * @param configPath Path to the TOML config file
   * @param runtime Runtime instance (must be set up with correct content_root)
   * @return CodegenContext on success, error on failure
   */
```

## Source note 21, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L108)

```text
/**
   * Create a CodegenContext from pre-loaded binary and config.
   * Primarily for testing where binary is loaded differently.
   *
   * @param binary Pre-loaded BinaryView (moved into context)
   * @param config Pre-loaded RecompilerConfig (moved into context)
   */
```

## Source note 22, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L117)

```text
// Non-copyable, movable
```

## Source note 23, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L124)

```text
// === OWNED DATA (single source of truth) ===
```

## Source note 24, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L125)

```text
///< All functions (including imports)
```

## Source note 25, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L126)

```text
///< Accumulated errors
```

## Source note 26, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L128)

```text
/// Scan phase artifacts (passed to Discover for scanner setup)
```

## Source note 27, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L130)

```text
///< Null-delimited code regions
```

## Source note 28, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L132)

```text
// address -> size
```

## Source note 29, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L135)

```text
// === ACCESSORS ===
```

## Source note 30, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L139)

```text
/// Access the decoded binary (must call initDecoded() first)
```

## Source note 31, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L143)

```text
/// Initialize DecodedBinary after context is in final location
```

## Source note 32, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L144)

```text
/// Call this once after Create() before accessing decoded()
```

## Source note 33, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L168)

```text
/// The function dispatch table's guest address (0: image base + size).
```

## Source note 34, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L172)

```text
/// Names of the guest code patches applied to this module's image.
```

## Source note 35, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L176)

```text
/// Patches compiled with both instruction versions, switched at run time.
```

## Source note 36, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L183)

```text
///< Binary data + sections (owned)
```

## Source note 37, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L184)

```text
///< User configuration (owned)
```

## Source note 38, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L185)

```text
///< Analysis state (populated during analysis)
```

## Source note 39, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L186)

```text
///< Decoded instructions (created via initDecoded())
```

## Source note 40, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L187)

```text
///< For runtime resolution (borrowed)
```

## Source note 41, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L188)

```text
///< Directory containing config file (for relative paths)
```

## Source note 42, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L190)

```text
///< True if this module is a DLL (shared library output)
```

## Source note 43, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L191)

```text
///< True if the project has DLL modules (multi-binary)
```

## Source note 44, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L192)

```text
///< Dispatch table address; 0 for image base + size
```

## Source note 45, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/codegen_context.h#L194)

```text
///< Code patches applied before analysis
```
