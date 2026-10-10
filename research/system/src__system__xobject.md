# Xobject: system source notes

This record preserves technical and API notes moved from `src/system/xobject.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L18)

```text
// For TranslateAnsiStringAddress
```

## Source note 2, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L60)

```text
// Free the object creation info
```

## Source note 3, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L103)

```text
// Fake return value for api-scanner
```

## Source note 4, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L130)

```text
// Restore our pointer to our handles in the object table.
```

## Source note 5, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L191)

```text
// Absolute guest system time (100 ns units since 1601); one already
```

## Source note 6, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L192)

```text
// passed is due now.
```

## Source note 7, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L196)

```text
// Relative, or 0.
```

## Source note 8, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L200)

```text
// Truncated to whole milliseconds, as the Win32 millisecond waits take it.
```

## Source note 9, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L206)

```text
// Rounded up: a timeout never ends before the guest asked.
```

## Source note 10, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L218)

```text
// Object doesn't support waiting.
```

## Source note 11, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L242)

```text
// Or X_STATUS_ALERTED?
```

## Source note 12, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L266)

```text
// Nothing was signaled (a semaphore at its limit, a bad handle).
```

## Source note 13, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L274)

```text
// Or X_STATUS_ALERTED?
```

## Source note 14, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L301)

```text
// Wait-all has no room for a timer in the set, so only wait-any gets a
```

## Source note 15, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L302)

```text
// precise timeout.
```

## Source note 16, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L316)

```text
// Or X_STATUS_ALERTED?
```

## Source note 17, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L339)

```text
// Or X_STATUS_ALERTED?
```

## Source note 18, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L359)

```text
// Out of memory!
```

## Source note 19, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L371)

```text
// Set it up in the header.
```

## Source note 20, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L372)

```text
// Some kernel method is accessing this struct and dereferencing a member
```

## Source note 21, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L373)

```text
// @ offset 0x14
```

## Source note 22, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L383)

```text
// If hit: We've already setup the native ptr with CreateNative!
```

## Source note 23, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L388)

```text
// Memory uninitialized, so don't bother with the check.
```

## Source note 24, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L393)

```text
// Stash pointer in struct.
```

## Source note 25, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L404)

```text
// Unfortunately the XDK seems to inline some KeInitialize calls, meaning
```

## Source note 26, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L405)

```text
// we never see it and just randomly start getting passed events/timers/etc.
```

## Source note 27, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L406)

```text
// Luckily it seems like all other calls (Set/Reset/Wait/etc) are used and
```

## Source note 28, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L407)

```text
// we don't have to worry about PPC code poking the struct. Because of that,
```

## Source note 29, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L408)

```text
// we init on first use, store our handle in the struct, and dereference it
```

## Source note 30, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L409)

```text
// each time.
```

## Source note 31, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L410)

```text
// We identify this by setting wait_list_flink to a magic value. When set,
```

## Source note 32, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L411)

```text
// wait_list_blink will hold a handle to our object.
```

## Source note 33, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L423)

```text
// Already initialized.
```

## Source note 34, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L427)

```text
// An object that died leaves its signature behind, and the table hands
```

## Source note 35, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L428)

```text
// its handle to the next object, so the handle must still name an object
```

## Source note 36, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L429)

```text
// over this memory (Canary #1225, read side only; see
```

## Source note 37, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L430)

```text
// docs/upstream-tracking.md). A stale signature is a first use.
```

## Source note 38, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L439)

```text
// First use, create new.
```

## Source note 39, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L440)

```text
// https://www.nirsoft.net/kernel_struct/vista/KOBJECTS.html
```

## Source note 40, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L460)

```text
// Can't report failure to the guest at late initialization:
```

## Source note 41, line 482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L482)

```text
// Record where the object lives and stash its handle there, so lookups
```

## Source note 42, line 483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xobject.cpp#L483)

```text
// can check it and header synchronization can reach the guest state.
```
