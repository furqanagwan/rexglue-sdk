# Xobject: system source notes

This record preserves technical and API notes moved from `include/rex/system/xobject.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L42)

```text
// https://www.nirsoft.net/kernel_struct/vista/DISPATCHER_HEADER.html
```

## Source note 2, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L71)

```text
// https://www.nirsoft.net/kernel_struct/vista/OBJECT_HEADER.html
```

## Source note 3, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L86)

```text
// -0x8 POBJECT_TYPE
```

## Source note 4, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L87)

```text
// -0x4
```

## Source note 5, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L89)

```text
// Object lives after this header.
```

## Source note 6, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L90)

```text
// (There's actually a body field here which is the object itself)
```

## Source note 7, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L93)

```text
// https://www.nirsoft.net/kernel_struct/vista/OBJECT_CREATE_INFORMATION.html
```

## Source note 8, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L95)

```text
// 0x0
```

## Source note 9, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L96)

```text
// 0x4
```

## Source note 10, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L97)

```text
// 0x8
```

## Source note 11, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L98)

```text
// 0xC
```

## Source note 12, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L99)

```text
// 0x10
```

## Source note 13, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L100)

```text
// 0x14
```

## Source note 14, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L101)

```text
// 0x18
```

## Source note 15, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L102)

```text
// 0x1C
```

## Source note 16, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L103)

```text
// 0x20
```

## Source note 17, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L105)

```text
// Security QoS here (SECURITY_QUALITY_OF_SERVICE) too!
```

## Source note 18, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L109)

```text
// 0x0
```

## Source note 19, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L110)

```text
// 0x4
```

## Source note 20, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L111)

```text
// 0x8
```

## Source note 21, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L112)

```text
// 0xC
```

## Source note 22, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L113)

```text
// 0x10
```

## Source note 23, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L114)

```text
// 0x14 probably offset from ntobject to keobject
```

## Source note 24, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L115)

```text
// 0x18
```

## Source note 25, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L120)

```text
// 45410806 needs proper handle value for certain calculations
```

## Source note 26, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L121)

```text
// It gets handle value from TLS (without base handle value is 0x88)
```

## Source note 27, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L122)

```text
// and substract 0xF8000088. Without base we're receiving wrong address
```

## Source note 28, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L123)

```text
// Instead of receiving address that starts with 0x82... we're receiving
```

## Source note 29, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L124)

```text
// one with 0x8A... which causes crash
```

## Source note 30, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L154)

```text
// Returns the primary handle of this object.
```

## Source note 31, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L157)

```text
// Returns all associated handles with this object.
```

## Source note 32, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L164)

```text
// Has this object been created for use by the host?
```

## Source note 33, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L165)

```text
// Host objects are persisted through reloads/etc.
```

## Source note 34, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L180)

```text
// Called by the object table, under its lock, when the guest has closed the
```

## Source note 35, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L181)

```text
// object's last handle, before the table drops its own reference. Objects
```

## Source note 36, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L182)

```text
// that the kernel also keeps a reference to release it here.
```

## Source note 37, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L192)

```text
// Reference()
```

## Source note 38, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L193)

```text
// Dereference()
```

## Source note 39, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L215)

```text
// Called on successful wait.
```

## Source note 40, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L217)

```text
// SignalAndWait signals through the host handle: BeginSignal records the
```

## Source note 41, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L218)

```text
// signal before it, as Set/Release would, so a waiter it releases updates
```

## Source note 42, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L219)

```text
// the state after; CancelSignal undoes it when the host signal failed.
```

## Source note 43, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L222)

```text
// Called when the guest hands the kernel this object's dispatch header, the
```

## Source note 44, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L223)

```text
// only point where a write the guest made to it directly (an inlined
```

## Source note 45, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L224)

```text
// KeInitialize over a live object) can be picked up. Canary #1227.
```

## Source note 46, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L228)

```text
// Creates the kernel object for guest code to use. Typically not needed.
```

## Source note 47, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L237)

```text
// Stash native pointer into X_DISPATCH_HEADER
```

## Source note 48, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L243)

```text
// Guest timeouts are 100 ns ticks: negative is relative, positive an
```

## Source note 49, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L244)

```text
// absolute guest system time, 0 is now.
```

## Source note 50, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L247)

```text
// The host duration of a guest timeout, scaled by the guest clock and
```

## Source note 51, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L248)

```text
// rounded up to microseconds.
```

## Source note 52, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L253)

```text
// Host objects are persisted through resets/etc.
```

## Source note 53, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L261)

```text
// May be zero length.
```

## Source note 54, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L263)

```text
// Guest pointer for kernel object. Remember: X_OBJECT_HEADER precedes this
```

## Source note 55, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L264)

```text
// if we allocated it!
```

## Source note 56, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L281)

```text
// Assumes retained on call.
```

## Source note 57, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L352)

```text
// Explicit nullptr comparison to avoid C++20 synthesized operator ambiguity
```

## Source note 58, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xobject.h#L402)

```text
// fmt formatter for XObject::Type - format as underlying uint32_t
```
