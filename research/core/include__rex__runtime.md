# Runtime: core source notes

This record preserves technical and API notes moved from `include/rex/runtime.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L33)

```text
// Forward declaration for function mapping (defined in rex/ppc/context.h)
```

## Source note 2, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L46)

```text
// Forward declarations
```

## Source note 3, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L61)

```text
/// Configuration for Runtime subsystem injection.
```

## Source note 4, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L62)

```text
/// Graphics and audio backends are provided by the caller, keeping the runtime
```

## Source note 5, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L63)

```text
/// library decoupled from concrete backend implementations.
```

## Source note 6, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L64)

```text
/// Audio uses a factory because AudioSystem requires a FunctionDispatcher* at
```

## Source note 7, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L65)

```text
/// construction time, which is only available during Setup().
```

## Source note 8, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L68)

```text
// GPU emulation plugin loaded by ReXApp when `graphics` is empty
```

## Source note 9, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L69)

```text
// (e.g. "xenos"); empty means no GPU emulation.
```

## Source note 10, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L77)

```text
/// Helper macros for populating RuntimeConfig with concrete backends.
```

## Source note 11, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L78)

```text
/// Usage:
```

## Source note 12, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L79)

```text
///   rex::RuntimeConfig config;
```

## Source note 13, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L80)

```text
///   config.graphics      = REX_GRAPHICS_BACKEND(MyCustomGraphicsSystem);
```

## Source note 14, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L81)

```text
///   config.audio_factory = REX_AUDIO_BACKEND(rex::audio::xaudio2::XAudio2AudioSystem);
```

## Source note 15, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L92)

```text
/**
 * Runtime class - the main entry point for recompiled applications.
 *
 * Owns all subsystems:
 * - Memory: Virtual address space for guest code
 * - VFS: Virtual file system
 * - KernelState: Kernel objects, threading, etc.
 */
```

## Source note 16, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L109)

```text
// Non-copyable
```

## Source note 17, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L113)

```text
// Global instance accessor - set after Setup() is called
```

## Source note 18, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L116)

```text
// Subsystem accessors
```

## Source note 19, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L124)

```text
// FunctionDispatcher for guest function dispatch and interrupt execution
```

## Source note 20, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L126)

```text
// Export resolver - used for variable import resolution in guest memory
```

## Source note 21, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L129)

```text
// Path accessors
```

## Source note 22, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L136)

```text
// Finds a metadata file or directory. An explicit metadata_root disables
```

## Source note 23, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L137)

```text
// legacy discovery; otherwise existing project layouts remain supported.
```

## Source note 24, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L143)

```text
// Set the app context for presentation (call before Setup)
```

## Source note 25, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L147)

```text
// UI accessors for dialog system
```

## Source note 26, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L153)

```text
// Setup the runtime environment
```

## Source note 27, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L154)

```text
// config.tool_mode: If true, skips GPU initialization (for analysis tools)
```

## Source note 28, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L157)

```text
// rexglue - initializes per-module function dispatch table
```

## Source note 29, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L162)

```text
// Check if running in tool mode (no GPU)
```

## Source note 30, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L167)

```text
// Load XEX image into guest memory
```

## Source note 31, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L170)

```text
// Launch XEX module and return main thread
```

## Source note 32, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L171)

```text
// Call after LoadXexImage to start execution
```

## Source note 33, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L174)

```text
// Prepare module launch: creates suspended main thread without resuming.
```

## Source note 34, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L175)

```text
// Call thread->Resume() after any pre-launch hooks.
```

## Source note 35, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L178)

```text
// Access the memory base pointer for recompiled code
```

## Source note 36, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/runtime.h#L182)

```text
// Set up VFS: mounts game_data_root as game:/d:, update_data_root as update:
```
