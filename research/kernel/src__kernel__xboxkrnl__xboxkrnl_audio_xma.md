# Xboxkrnl audio xma: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L33)

```text
// See audio_system.cc for implementation details.
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L35)

```text
// XMA details:
```

## Source note 4, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L36)

```text
// https://devel.nuclex.org/external/svn/directx/trunk/include/xma2defs.h
```

## Source note 5, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L37)

```text
// https://github.com/gdawg/fsbext/blob/master/src/xma_header.h
```

## Source note 6, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L39)

```text
// XMA is undocumented, but the methods are pretty simple.
```

## Source note 7, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L40)

```text
// Games do this sequence to decode (now):
```

## Source note 8, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L41)

```text
//   (not sure we are setting buffer validity/offsets right)
```

## Source note 9, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L42)

```text
// d> XMACreateContext(20656800)
```

## Source note 10, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L43)

```text
// d> XMAIsInputBuffer0Valid(000103E0)
```

## Source note 11, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L44)

```text
// d> XMAIsInputBuffer1Valid(000103E0)
```

## Source note 12, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L45)

```text
// d> XMADisableContext(000103E0, 0)
```

## Source note 13, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L46)

```text
// d> XMABlockWhileInUse(000103E0)
```

## Source note 14, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L47)

```text
// d> XMAInitializeContext(000103E0, 20008810)
```

## Source note 15, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L48)

```text
// d> XMASetOutputBufferValid(000103E0)
```

## Source note 16, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L49)

```text
// d> XMASetInputBuffer0Valid(000103E0)
```

## Source note 17, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L50)

```text
// d> XMAEnableContext(000103E0)
```

## Source note 18, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L51)

```text
// d> XMAGetOutputBufferWriteOffset(000103E0)
```

## Source note 19, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L52)

```text
// d> XMAGetOutputBufferReadOffset(000103E0)
```

## Source note 20, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L53)

```text
// d> XMAIsOutputBufferValid(000103E0)
```

## Source note 21, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L54)

```text
// d> XMAGetOutputBufferReadOffset(000103E0)
```

## Source note 22, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L55)

```text
// d> XMAGetOutputBufferWriteOffset(000103E0)
```

## Source note 23, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L56)

```text
// d> XMAIsInputBuffer0Valid(000103E0)
```

## Source note 24, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L57)

```text
// d> XMAIsInputBuffer1Valid(000103E0)
```

## Source note 25, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L58)

```text
// d> XMAIsInputBuffer0Valid(000103E0)
```

## Source note 26, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L59)

```text
// d> XMAIsInputBuffer1Valid(000103E0)
```

## Source note 27, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L60)

```text
// d> XMAReleaseContext(000103E0)
```

## Source note 28, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L62)

```text
// XAudio2 uses XMA under the covers, and seems to map with the same
```

## Source note 29, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L63)

```text
// restrictions of frame/subframe/etc:
```

## Source note 30, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L64)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.xaudio2.xaudio2_buffer(v=vs.85).aspx
```

## Source note 31, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L126)

```text
// Input buffers may be null (buffer 1 in 415607D4).
```

## Source note 32, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L127)

```text
// Convert to host endianness.
```

## Source note 33, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L133)

```text
// Xenia-specific safety check.
```

## Source note 34, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L176)

```text
// context.work_buffer = context_init->work_buffer;  // ?
```

## Source note 35, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L226)

```text
// Xenia-specific safety check.
```

## Source note 36, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_audio_xma.cpp#L260)

```text
// Xenia-specific safety check.
```
