# Xboxkrnl io: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_io.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L40)

```text
// Low bit probably means do not queue to IO ports.
```

## Source note 3, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L45)

```text
// Count first, then status: a caller polling the status for completion
```

## Source note 4, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L46)

```text
// must never read a stale count.
```

## Source note 5, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L56)

```text
// https://processhacker.sourceforge.io/doc/ntioapi_8h.html
```

## Source note 6, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L58)

```text
// Optimization - files access will be sequential, not random.
```

## Source note 7, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L63)

```text
// Optimization - file access will be random, not sequential.
```

## Source note 8, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L74)

```text
// * must be followed by a . (*.)
```

## Source note 9, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L76)

```text
// 4D530819 has a bug in its game code where it attempts to
```

## Source note 10, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L77)

```text
// FindFirstFile() with filters of "Game:\\*_X3.rkv", "Game:\\m*_X3.rkv",
```

## Source note 11, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L78)

```text
// and "Game:\\w*_X3.rkv" and will infinite loop if the path filter is
```

## Source note 12, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L79)

```text
// allowed.
```

## Source note 13, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L87)

```text
// case '*':
```

## Source note 14, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L90)

```text
// case ':':
```

## Source note 15, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L91)

```text
// case ';':
```

## Source note 16, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L93)

```text
// case '=':
```

## Source note 17, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L95)

```text
// case '?':
```

## Source note 18, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L100)

```text
// Pattern-specific (for NtQueryDirectoryFile)
```

## Source note 19, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L108)

```text
// Pattern-specific (for NtQueryDirectoryFile)
```

## Source note 20, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L127)

```text
// note used. maybe later
```

## Source note 21, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L128)

```text
// uint64_t allocation_size = 0;  // is this correct???
```

## Source note 22, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L129)

```text
// if (allocation_size_ptr) {
```

## Source note 23, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L130)

```text
//  allocation_size = *allocation_size_ptr;
```

## Source note 24, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L134)

```text
// ..? Some games do this. This parameter is not optional.
```

## Source note 25, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L143)

```text
// Compute path, possibly attrs relative.
```

## Source note 26, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L150)

```text
// Enforce that the path is ASCII.
```

## Source note 27, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L164)

```text
// ObDosDevices names without a device prefix are relative to the running
```

## Source note 28, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L165)

```text
// title's game directory. Explicit device paths use the normal VFS path.
```

## Source note 29, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L171)

```text
// Attempt open (or create).
```

## Source note 30, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L182)

```text
// If true, desired_access SYNCHRONIZE flag must be set.
```

## Source note 31, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L187)

```text
// Handle ref is incremented, so return that.
```

## Source note 32, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L208)

```text
// The guest ABI passes ShareAccess in r7 and OpenOptions in r8 (Edge 887beea).
```

## Source note 33, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L241)

```text
// Synchronous.
```

## Source note 34, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L250)

```text
// Queue the APC callback. It must be delivered via the APC mechanism even
```

## Source note 35, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L251)

```text
// though were are completing immediately. A caller told PENDING (an
```

## Source note 36, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L252)

```text
// asynchronous handle, short of end of file) always gets it, as on NT:
```

## Source note 37, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L253)

```text
// it has no other way to learn the read finished, even when it failed.
```

## Source note 38, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L277)

```text
// Mark that we should signal the event now. We do this after
```

## Source note 39, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L278)

```text
// we have written the info out.
```

## Source note 40, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L281)

```text
// X_STATUS_PENDING if not returning immediately.
```

## Source note 41, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L282)

```text
// XFile is waitable and signalled after each async req completes.
```

## Source note 42, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L283)

```text
// reset the input event (->Reset())
```

## Source note 43, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L284)

```text
/*xeNtReadFileState* call_state = new xeNtReadFileState();
      XAsyncRequest* request = new XAsyncRequest(
      state, file,
      (XAsyncRequest::CompletionCallback)xeNtReadFileCompleted,
      call_state);*/
```

## Source note 44, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L289)

```text
// result = file->Read(buffer.guest_address(), buffer_length, byte_offset,
```

## Source note 45, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L290)

```text
//                     request);
```

## Source note 46, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L307)

```text
// Log detailed completion info for debugging async IO issues
```

## Source note 47, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L342)

```text
// Synchronous.
```

## Source note 48, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L351)

```text
// Queue the APC callback. It must be delivered via the APC mechanism even
```

## Source note 49, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L352)

```text
// though were are completing immediately. An asynchronous handle is
```

## Source note 50, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L353)

```text
// always told PENDING, and then always gets its APC; a synchronous one
```

## Source note 51, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L354)

```text
// only when the read succeeded, as for NtReadFile.
```

## Source note 52, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L367)

```text
// Mark that we should signal the event now. We do this after
```

## Source note 53, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L368)

```text
// we have written the info out.
```

## Source note 54, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L371)

```text
// X_STATUS_PENDING if not returning immediately.
```

## Source note 55, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L372)

```text
// XFile is waitable and signalled after each async req completes.
```

## Source note 56, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L373)

```text
// reset the input event (->Reset())
```

## Source note 57, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L374)

```text
/*xeNtReadFileState* call_state = new xeNtReadFileState();
      XAsyncRequest* request = new XAsyncRequest(
      state, file,
      (XAsyncRequest::CompletionCallback)xeNtReadFileCompleted,
      call_state);*/
```

## Source note 58, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L379)

```text
// result = file->Read(buffer.guest_address(), buffer_length, byte_offset,
```

## Source note 59, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L380)

```text
//                     request);
```

## Source note 60, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L405)

```text
// Grab event to signal.
```

## Source note 61, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L412)

```text
// Grab file.
```

## Source note 62, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L418)

```text
// Execute write.
```

## Source note 63, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L421)

```text
// Synchronous request.
```

## Source note 64, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L431)

```text
// Queue the APC callback. It must be delivered via the APC mechanism even
```

## Source note 65, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L432)

```text
// though were are completing immediately.
```

## Source note 66, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L433)

```text
// Low bit probably means do not queue to IO ports.
```

## Source note 67, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L446)

```text
// Mark that we should signal the event now. We do this after
```

## Source note 68, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L447)

```text
// we have written the info out.
```

## Source note 69, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L450)

```text
// X_STATUS_PENDING if not returning immediately.
```

## Source note 70, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L497)

```text
// Dequeues a packet from the completion port.
```

## Source note 71, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L501)

```text
// uint32_t info = 0;
```

## Source note 72, line 546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L546)

```text
// Enforce that the path is ASCII.
```

## Source note 73, line 551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L551)

```text
// Resolve the file using the virtual file system.
```

## Source note 74, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L554)

```text
// Found.
```

## Source note 75, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L586)

```text
// Enforce that the path is ASCII.
```

## Source note 76, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L592)

```text
// X_FILE_DIRECTORY_INFORMATION dir_info = {0};
```

## Source note 77, line 629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L629)

```text
// https://docs.microsoft.com/en-us/windows/win32/devnotes/ntopensymboliclinkobject
```

## Source note 78, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L637)

```text
// case insensitive
```

## Source note 79, line 643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L643)

```text
// Enforce that the path is ASCII.
```

## Source note 80, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L653)

```text
// Strip the full qualifier
```

## Source note 81, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L669)

```text
// https://docs.microsoft.com/en-us/windows/win32/devnotes/ntquerysymboliclinkobject
```

## Source note 82, line 689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L689)

```text
// unk_0 = 0
```

## Source note 83, line 690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L690)

```text
// unk_1 looks like a count? in what units? 256 is a common value
```

## Source note 84, line 698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L698)

```text
// Called by XMountUtilityDrive cache-mounting code
```

## Source note 85, line 699

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L699)

```text
// (checks if the returned values look valid, values below seem to pass the
```

## Source note 86, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L700)

```text
// checks)
```

## Source note 87, line 730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L730)

```text
// Called from XMountUtilityDrive XAM-task code
```

## Source note 88, line 731

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L731)

```text
// That code tries writing things to a pointer at out_struct+0x18
```

## Source note 89, line 732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L732)

```text
// We'll alloc some scratch space for it so it doesn't cause any exceptions
```

## Source note 90, line 734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L734)

```text
// 0x24 is guessed size from accesses to out_struct - likely incorrect
```

## Source note 91, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L740)

```text
// XMountUtilityDrive writes some kind of header here
```

## Source note 92, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L741)

```text
// 0x1000 bytes should be enough to store it
```

## Source note 93, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L769)

```text
// if (out_device) *out_device = 0;
```
