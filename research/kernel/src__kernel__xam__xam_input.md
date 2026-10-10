# Xam input: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xam/xam_input.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L42)

```text
// Do we need to do anything?
```

## Source note 2, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L49)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xinputgetcapabilities(v=vs.85).aspx
```

## Source note 3, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L58)

```text
// Ignore any query for other types of devices.
```

## Source note 4, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L64)

```text
// Always pin user to 0.
```

## Source note 5, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L79)

```text
// Ignore any query for other types of devices.
```

## Source note 6, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L85)

```text
// Always pin user to 0.
```

## Source note 7, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L89)

```text
// Unused in this implementation
```

## Source note 8, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L94)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xinputgetstate(v=vs.85).aspx
```

## Source note 9, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L96)

```text
// Games call this with a NULL state ptr, probably as a query.
```

## Source note 10, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L104)

```text
// Ignore any query for other types of devices.
```

## Source note 11, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L110)

```text
// Always pin user to 0.
```

## Source note 12, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L118)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xinputsetstate(v=vs.85).aspx
```

## Source note 13, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L126)

```text
// Always pin user to 0.
```

## Source note 14, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L130)

```text
// Unused in this implementation
```

## Source note 15, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L135)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xinputgetkeystroke(v=vs.85).aspx
```

## Source note 16, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L137)

```text
// https://github.com/CodeAsm/ffplay360/blob/master/Common/AtgXime.cpp
```

## Source note 17, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L138)

```text
// user index = index or XUSER_INDEX_ANY
```

## Source note 18, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L139)

```text
// flags = XINPUT_FLAG_GAMEPAD (| _ANYUSER | _ANYDEVICE)
```

## Source note 19, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L146)

```text
// Ignore any query for other types of devices.
```

## Source note 20, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L152)

```text
// Always pin user to 0.
```

## Source note 21, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L160)

```text
// Same as non-ex, just takes a pointer to user index.
```

## Source note 22, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L168)

```text
// Ignore any query for other types of devices.
```

## Source note 23, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L174)

```text
// Always pin user to 0.
```

## Source note 24, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L180)

```text
// An X_RESULT: X_ERROR_EMPTY is positive, so XSUCCEEDED would accept it.
```

## Source note 25, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L188)

```text
// Games check the result - usually with some masking.
```

## Source note 26, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L189)

```text
// If this function fails they assume zero, so let's fail AND
```

## Source note 27, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_input.cpp#L190)

```text
// set zero just to be safe.
```
