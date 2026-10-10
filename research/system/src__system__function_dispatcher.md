# Function dispatcher: system source notes

This record preserves technical and API notes moved from `src/system/function_dispatcher.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/function_dispatcher.cpp#L50)

```text
// Keep the targets earlier runs recorded: each run stops at its first one.
```

## Source note 2, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/function_dispatcher.cpp#L76)

```text
/*base*/
```

## Source note 3, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/function_dispatcher.cpp#L119)

```text
// Rebind the active guest thread for cross-module callbacks.
```

## Source note 4, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/function_dispatcher.cpp#L122)

```text
// Pad out stack a bit, as some games seem to overwrite the caller by about 16 to 32b.
```

## Source note 5, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/function_dispatcher.cpp#L129)

```text
// Guest code finds its own FP mode, and the host gets its own back.
```

## Source note 6, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/function_dispatcher.cpp#L196)

```text
// Hold the global lock during interrupt dispatch.
```

## Source note 7, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/function_dispatcher.cpp#L213)

```text
// TLS ptr must be zero during interrupts. Some games check this and early-exit
```

## Source note 8, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/function_dispatcher.cpp#L214)

```text
// routines when under interrupts.
```

## Source note 9, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/function_dispatcher.cpp#L223)

```text
// Restore TLS ptr.
```

## Source note 10, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/function_dispatcher.cpp#L229)

```text
// rexglue function table management
```

## Source note 11, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/function_dispatcher.cpp#L256)

```text
// Images and tables may not overlap one another, in any pairing.
```
