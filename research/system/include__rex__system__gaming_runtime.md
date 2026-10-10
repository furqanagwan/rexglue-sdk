# Gaming runtime: system source notes

This record preserves technical and API notes moved from `include/rex/system/gaming_runtime.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L38)

```text
// The SDK was built without the GDK.
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L40)

```text
// xgameruntime.dll (Gaming Services) is not installed or is incomplete.
```

## Source note 3, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L42)

```text
// The installed runtime does not support the GDK edition the title uses.
```

## Source note 4, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L44)

```text
// MicrosoftGame.config is malformed or disagrees with the package or with an
```

## Source note 5, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L45)

```text
// earlier initialization in this process.
```

## Source note 6, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L55)

```text
// The initialize HRESULT; 0 when the call did not return (timeout) or was
```

## Source note 7, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L56)

```text
// never made (unavailable).
```

## Source note 8, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L58)

```text
// A diagnostic for logs and error dialogs: what failed and what to do.
```

## Source note 9, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L64)

```text
// Maps an XGameRuntimeInitialize* HRESULT to a state (kReady on success).
```

## Source note 10, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L67)

```text
// The diagnostic for a failed (or successful) initialize HRESULT.
```

## Source note 11, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L70)

```text
// What a title does with the runtime at startup (cvar gaming_runtime).
```

## Source note 12, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L72)

```text
// never initialize it
```

## Source note 13, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L73)

```text
// initialize it when the SDK has the GDK; launch whatever happens
```

## Source note 14, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L74)

```text
// launch only when it is ready
```

## Source note 15, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L79)

```text
// Whether the title may start after `result` under `policy`.
```

## Source note 16, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L82)

```text
// The calls GamingRuntime makes. Tests substitute fakes; titles use
```

## Source note 17, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L83)

```text
// SystemGamingRuntimeHooks().
```

## Source note 18, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L85)

```text
// Initializes the runtime. An empty config_path means XGameRuntimeInitialize;
```

## Source note 19, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L86)

```text
// otherwise XGameRuntimeInitializeWithOptions with that MicrosoftGame.config.
```

## Source note 20, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L91)

```text
// The real XGameRuntime calls, or empty hooks in a build without the GDK.
```

## Source note 21, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L106)

```text
// Initializes the runtime, waiting at most `timeout`. Returns the current
```

## Source note 22, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L107)

```text
// result without calling again when already ready. A new attempt is refused
```

## Source note 23, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L108)

```text
// (kTimedOut) while an earlier timed-out call is still inside the runtime.
```

## Source note 24, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L112)

```text
// Balances a successful Initialize; otherwise does nothing. Call it after
```

## Source note 25, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/gaming_runtime.h#L113)

```text
// everything that uses the runtime has shut down.
```
