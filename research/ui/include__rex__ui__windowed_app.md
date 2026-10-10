# Windowed app: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/windowed_app.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L30)

```text
// Interface between the platform's entry points (in the main, UI, thread that
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L31)

```text
// also runs the message loop) and the app that implements it.
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L34)

```text
// WindowedApps are expected to provide a static creation function, for
```

## Source note 4, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L35)

```text
// creating an instance of the class (which may be called before
```

## Source note 5, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L36)

```text
// initialization of platform-specific parts, should preferably be as simple
```

## Source note 6, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L37)

```text
// as possible).
```

## Source note 7, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L48)

```text
// Same as the executable (project), xenia-library-app.
```

## Source note 8, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L53)

```text
// TEMP: Replace with CVAR system
```

## Source note 9, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L54)

```text
// Called by entry point after construction, before OnInitialize()
```

## Source note 10, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L59)

```text
// TEMP: Replace with CVAR system
```

## Source note 11, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L60)

```text
// Retrieve a parsed argument by name
```

## Source note 12, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L69)

```text
// Called once before receiving other lifecycle callback invocations. Cvars
```

## Source note 13, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L70)

```text
// will be initialized with the launch arguments. Returns whether the app has
```

## Source note 14, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L71)

```text
// been initialized successfully (otherwise platform-specific code must call
```

## Source note 15, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L72)

```text
// OnDestroy and refuse to continue running the app).
```

## Source note 16, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L74)

```text
// See OnDestroy for more info.
```

## Source note 17, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L76)

```text
// For safety and convenience of referencing objects owned by the app in
```

## Source note 18, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L77)

```text
// pending functions queued in or after OnInitialize, make sure they are
```

## Source note 19, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L78)

```text
// executed before telling the app that destruction needs to happen.
```

## Source note 20, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L84)

```text
// Positional options should be initialized in the constructor if needed.
```

## Source note 21, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L85)

```text
// Cvars will not have been initialized with the arguments at the moment of
```

## Source note 22, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L86)

```text
// construction (as the result depends on construction).
```

## Source note 23, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L93)

```text
// For calling from the constructor.
```

## Source note 24, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L98)

```text
// OnDestroy entry point may be called (through InvokeOnDestroy) by the
```

## Source note 25, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L99)

```text
// platform-specific lifecycle interface at request of either the app itself
```

## Source note 26, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L100)

```text
// or the OS - thus should be possible for the lifecycle interface to call at
```

## Source note 27, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L101)

```text
// any moment (not from inside other lifecycle callbacks though). The app will
```

## Source note 28, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L102)

```text
// also be destroyed when that happens, so the destructor will also be called
```

## Source note 29, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L103)

```text
// (but this is more safe with respect to exceptions). This is only guaranteed
```

## Source note 30, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L104)

```text
// to be called if OnInitialize has already happened (successfully or not) -
```

## Source note 31, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L105)

```text
// in case of an error before initialization, the destructor may be called
```

## Source note 32, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L106)

```text
// alone as well. Context's pending functions will be executed before the
```

## Source note 33, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L107)

```text
// call, so it's safe to destroy dependencies of them here (though it may
```

## Source note 34, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L108)

```text
// still be possible to add more pending functions here depending on whether
```

## Source note 35, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L109)

```text
// the context was explicitly shut down before this is invoked).
```

## Source note 36, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L118)

```text
// TEMP: Replace with CVAR system
```

## Source note 37, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L127)

```text
// Will be deleted by the last creator registration's destructor, no
```

## Source note 38, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L128)

```text
// need for a library destructor.
```

## Source note 39, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L162)

```text
// Multiple apps in a single library.
```

## Source note 40, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L172)

```text
// Separate executables for each app.
```

## Source note 41, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app.h#L180)

```text
// Deprecated: use REX_DEFINE_APP
```
