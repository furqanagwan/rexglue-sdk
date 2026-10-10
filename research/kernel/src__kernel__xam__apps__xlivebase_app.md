# Xlivebase app: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xam/apps/xlivebase_app.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xlivebase_app.cpp#L26)

```text
// http://mb.mirage.org/bugzilla/xliveless/main.c
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xlivebase_app.cpp#L30)

```text
// NOTE: buffer_length may be zero or valid.
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xlivebase_app.cpp#L34)

```text
// Called on startup, seems to just return a bool in the buffer.
```

## Source note 4, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xlivebase_app.cpp#L47)

```text
// Occurs if title calls XOnlineGetServiceInfo, expects dwServiceId
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xlivebase_app.cpp#L48)

```text
// and pServiceInfo. pServiceInfo should contain pointer to
```

## Source note 6, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xlivebase_app.cpp#L49)

```text
// XONLINE_SERVICE_INFO structure.
```

## Source note 7, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xlivebase_app.cpp#L54)

```text
// 0x00058004 is called right before this.
```

## Source note 8, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xlivebase_app.cpp#L55)

```text
// We should create a XamEnumerate-able empty list here, but I'm not
```

## Source note 9, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xlivebase_app.cpp#L56)

```text
// sure of the format.
```

## Source note 10, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xlivebase_app.cpp#L57)

```text
// buffer_length seems to be the same ptr sent to 0x00058004.
```

## Source note 11, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xlivebase_app.cpp#L70)

```text
// Required to be successful for 4D530910 to detect signed-in profile
```

## Source note 12, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/apps/xlivebase_app.cpp#L71)

```text
// Doesn't seem to set anything in the given buffer, probably only takes
```
