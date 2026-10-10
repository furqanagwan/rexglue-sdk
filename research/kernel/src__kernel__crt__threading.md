# Threading: kernel source notes

This record preserves technical and API notes moved from `src/kernel/crt/threading.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L36)

```text
/// get KTHREAD and PCR pointers from the current thread's context.
```

## Source note 2, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L53)

```text
/// update KTHREAD/PCR/ctx stack pointers
```

## Source note 3, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L66)

```text
// FiberEntryPoint -- host fiber entry for CreateFiber fibers
```

## Source note 4, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L81)

```text
// Read fiber_data (lpParameter) from guest context buffer
```

## Source note 5, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L85)

```text
// Call the fiber function
```

## Source note 6, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L88)

```text
// Fiber returned (shouldn't per XDK) -- safe fallback
```

## Source note 7, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L97)

```text
/// Helper for ConvertFiberToThread logic, shared by ConvertFiberToThread_entry
```

## Source note 8, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L98)

```text
/// and DeleteFiber_entry (self-delete case).
```

## Source note 9, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L116)

```text
// Must null main_fiber_ AFTER Destroy() above to avoid double-free
```

## Source note 10, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L117)

```text
// in ~XThread, which also calls main_fiber_->Destroy() if non-null.
```

## Source note 11, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L127)

```text
// XAPI Fiber Function Implementations
```

## Source note 12, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L140)

```text
// Allocate guest fiber context buffer
```

## Source note 13, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L149)

```text
// Populate from current KTHREAD stack state
```

## Source note 14, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L158)

```text
// Reuse existing host fiber from XThread::Execute() if available;
```

## Source note 15, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L159)

```text
// otherwise create one (should not happen in normal flow).
```

## Source note 16, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L187)

```text
// Determine guest stack size
```

## Source note 17, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L190)

```text
// 64KB default
```

## Source note 18, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L191)

```text
// page-align
```

## Source note 19, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L193)

```text
// 16KB minimum
```

## Source note 20, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L195)

```text
// Allocate guest kernel stack (for PPC stack variables via ctx.r1).
```

## Source note 21, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L196)

```text
// guest_stack_size is already page-aligned.
```

## Source note 22, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L212)

```text
// Zero the initial 80-byte frame
```

## Source note 23, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L215)

```text
// Resolve start address to host function pointer
```

## Source note 24, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L218)

```text
// Allocate guest fiber context buffer
```

## Source note 25, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L231)

```text
// = alloc_base initially
```

## Source note 26, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L235)

```text
// Create host fiber
```

## Source note 27, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L245)

```text
// FiberEntryPoint takes ownership
```

## Source note 28, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L263)

```text
// Self-delete: ConvertFiberToThread + ExitThread
```

## Source note 29, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L268)

```text
// does not return
```

## Source note 30, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L294)

```text
// Validate target
```

## Source note 31, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L301)

```text
// Save outgoing fiber's non-volatile registers and SP
```

## Source note 32, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L309)

```text
// Set target as active
```

## Source note 33, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L312)

```text
// Restore target's non-volatile registers and guest stack state
```

## Source note 34, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L327)

```text
// Host fiber switch -- suspends here, resumes when switched back
```

## Source note 35, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L329)

```text
// Resumed: non-volatile regs and stack state already restored by the fiber that switched back.
```

## Source note 36, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/threading.cpp#L335)

```text
// REXCRT_EXPORT wiring
```
