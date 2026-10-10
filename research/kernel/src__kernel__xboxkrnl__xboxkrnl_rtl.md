# Xboxkrnl rtl: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_rtl.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L37)

```text
// https://msdn.microsoft.com/en-us/library/ff561778
```

## Source note 3, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L42)

```text
// Note that the return value is the number of bytes that match, so it's best
```

## Source note 4, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L43)

```text
// we just do this ourselves vs. using memcmp.
```

## Source note 5, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L44)

```text
// On Windows we could use the builtin function.
```

## Source note 6, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L56)

```text
// https://msdn.microsoft.com/en-us/library/ff552123
```

## Source note 7, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L58)

```text
// Return 0 if source/length not aligned
```

## Source note 8, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L74)

```text
// https://msdn.microsoft.com/en-us/library/ff552263
```

## Source note 9, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L76)

```text
// NOTE: length must be % 4, so we can work on uint32s.
```

## Source note 10, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L130)

```text
// https://msdn.microsoft.com/en-us/library/ff561918
```

## Source note 11, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L144)

```text
// https://msdn.microsoft.com/en-us/library/ff561899
```

## Source note 12, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L153)

```text
// https://msdn.microsoft.com/en-us/library/ff561934
```

## Source note 13, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L164)

```text
// https://msdn.microsoft.com/en-us/library/ff561903
```

## Source note 14, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L204)

```text
// https://msdn.microsoft.com/en-us/library/ff562969
```

## Source note 15, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L208)

```text
// _Inout_  PANSI_STRING DestinationString,
```

## Source note 16, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L209)

```text
// _In_     PCUNICODE_STRING SourceString,
```

## Source note 17, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L210)

```text
// _In_     BOOLEAN AllocateDestinationString
```

## Source note 18, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L230)

```text
// Too large - we just write what we can.
```

## Source note 19, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L236)

```text
// \0
```

## Source note 20, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L241)

```text
// https://msdn.microsoft.com/en-us/library/ff553113
```

## Source note 21, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L259)

```text
// https://msdn.microsoft.com/en-us/library/ff553261
```

## Source note 22, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L276)

```text
// https://undocumented.ntinternals.net/UserMode/Undocumented%20Functions/Executable%20Images/RtlImageNtHeader.html
```

## Source note 23, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L282)

```text
// Little-endian! no swapping!
```

## Source note 24, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L286)

```text
// 'MZ'
```

## Source note 25, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L293)

```text
// 'PE'
```

## Source note 26, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L301)

```text
// VS acts weird going from u32 -> enum
```

## Source note 27, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L308)

```text
// Unfortunately the Windows RTL_CRITICAL_SECTION object is bigger than the one
```

## Source note 28, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L309)

```text
// on the 360 (32b vs. 28b). This means that we can't do in-place splatting of
```

## Source note 29, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L310)

```text
// the critical sections. Also, the 360 never calls RtlDeleteCriticalSection
```

## Source note 30, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L311)

```text
// so we can't clean up the native handles.
```

## Source note 31, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L313)

```text
// Because of this, we reimplement it poorly. Hooray.
```

## Source note 32, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L314)

```text
// We have 28b to work with so we need to be careful. We map our struct directly
```

## Source note 33, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L315)

```text
// into guest memory, as it should be opaque and so long as our size is right
```

## Source note 34, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L316)

```text
// the user code will never know.
```

## Source note 35, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L319)

```text
// https://web.archive.org/web/20161214022602/https://msdn.microsoft.com/en-us/magazine/cc164040.aspx
```

## Source note 36, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L321)

```text
// https://github.com/reactos/reactos/blob/master/sdk/lib/rtl/critical.c
```

## Source note 37, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L323)

```text
// This structure tries to match the one on the 360 as best I can figure out.
```

## Source note 38, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L324)

```text
// Unfortunately some games have the critical sections pre-initialized in
```

## Source note 39, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L325)

```text
// their embedded data and InitializeCriticalSection will never be called.
```

## Source note 40, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L329)

```text
// 0x10 -1 -> 0 on first lock
```

## Source note 41, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L330)

```text
// 0x14  0 -> 1 on first lock
```

## Source note 42, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L331)

```text
// 0x18 PKTHREAD 0 unless locked
```

## Source note 43, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L337)

```text
// EventSynchronizationObject (auto reset)
```

## Source note 44, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L338)

```text
// spin count div 256
```

## Source note 45, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L352)

```text
// Spin count is rounded up to 256 intervals then packed in.
```

## Source note 46, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L353)

```text
// uint32_t spin_count_div_256 = (uint32_t)floor(spin_count / 256.0f + 0.5f);
```

## Source note 47, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L359)

```text
// EventSynchronizationObject (auto reset)
```

## Source note 48, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L379)

```text
// We already own the lock.
```

## Source note 49, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L385)

```text
// Spin loop
```

## Source note 50, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L388)

```text
// Acquired.
```

## Source note 51, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L396)

```text
// Create a full waiter.
```

## Source note 52, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L409)

```text
// Able to steal the lock right away.
```

## Source note 53, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L414)

```text
// Already own the lock.
```

## Source note 54, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L420)

```text
// Failed to acquire lock.
```

## Source note 55, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L427)

```text
// Drop recursion count - if it isn't zero we still have the lock.
```

## Source note 56, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L436)

```text
// Not owned - unlock!
```

## Source note 57, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L439)

```text
// There were waiters - wake one of them.
```

## Source note 58, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L456)

```text
// https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-rtltimetotimefields
```

## Source note 59, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L458)

```text
// Use host clock because we don't want scaling to be applied, just conversion
```

## Source note 60, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L475)

```text
// https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-rtltimefieldstotime
```
