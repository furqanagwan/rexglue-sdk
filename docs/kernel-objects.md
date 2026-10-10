# Guest kernel objects

How a guest dispatcher object (event, semaphore, mutant, thread) is tied to
the host object that implements it, who owns it, and when the two states are
reconciled (RG-GDK-014). Code: `src/system/kernel_object.cpp`, `kernel_event.cpp`,
`kernel_semaphore.cpp`, `src/system/util/object_table.cpp`.

## The dispatch header

Every dispatcher object starts with the 16-byte `X_DISPATCH_HEADER`, big-endian
in guest memory:

| Offset | Field | Kernel use |
| --- | --- | --- |
| 0x0 | `type` | Object type: 0 notification event, 1 synchronization event, 2 mutant, 5 semaphore, 6 thread |
| 0x1–0x3 | `absolute`, `size`, `inserted` | Not used |
| 0x4 | `signal_state` | Mirrors the host state for events (0/1) and semaphores (the count) |
| 0x8 | `wait_list_flink` | Signature `REX\0` once the kernel has an object for this memory |
| 0xC | `wait_list_blink` | That object's handle |

The wait list itself is never used: host objects do the waiting, so those two
words hold the signature and handle instead.

## Two ways an object comes to exist

- **Created by the kernel** (`NtCreateEvent`, `NtCreateSemaphore`, threads):
  `CreateNative` allocates the header (plus `X_OBJECT_HEADER`) on the system
  heap, the constructor writes the type and initial state, and the memory is
  freed with the object.
- **Initialized by the guest.** The XDK inlines `KeInitializeEvent` and
  similar, so the kernel first sees such an object when the guest passes its
  address to `KeSetEvent`, `KeWaitForSingleObject`, `ObDereferenceObject` and
  so on. `GetNativeObject` then creates the host object from the header's type
  and state and records the address (`SetNativePointer`). The memory belongs to
  the guest.

## Ownership and handles

A new object has one pointer reference (the caller's `object_ref`) and one
handle in the object table, which holds a pointer reference of its own. It
lives while any handle or `object_ref` does. The table reuses the lowest free
slot, so a closed handle is usually the next one issued.

`ObReferenceObjectByHandle` takes a handle reference; `ObDereferenceObject`
releases one. For an object the guest initialized, `ObDereferenceObject` on
memory the kernel had not seen creates the object and releases its only
handle, so it dies at once and leaves the signature behind. Lookups therefore
use a stashed handle only when its object still records this address;
otherwise the memory is treated as a first use (Canary #1225, read side). Why
titles dereference such objects, and whether they should die then, is not
settled; see the ledger.

## Keeping header and host in step

The header holds what the kernel last wrote there (Canary #1227):

| Operation | Header | Host |
| --- | --- | --- |
| `Set` / `Reset` | 1 / 0, under the object's lock, before the host call | Event set / reset |
| `Pulse` | 0; returns the previous state | Event pulsed |
| Satisfied wait, synchronization event | The host state after the wait (another `Set` may have landed) | Auto-reset consumed |
| Satisfied wait, semaphore | Count − 1 | Count − 1 |
| `ReleaseSemaphore` | Count + n | Count + n |
| `SignalAndWait` | Recorded before the atomic host signal; undone if it fails | Signal and wait |
| Guest passes the header (`GetNativeObject`) | A value the kernel did not write came from the guest: the host follows it (a semaphore past its limit keeps its count and the header is corrected) | Set/reset, release or drain |

`NtQueryEvent` reads the host event without satisfying a wait
(`Event::IsSignaled`).

Tests: `kernel_tests [object_header]` (header fields, guest writes, the stale
signature, `SignalAndWait`, and concurrent release/wait and set/reset/pulse/wait
ending with header and host in agreement); `unit_tests [object_table]`.

## Limitations

- Mutants, timers and threads do not mirror their state into the header.
- A guest write is picked up only when the guest next hands the kernel the
  header; a title that polls `signal_state` inline sees kernel updates, but a
  kernel wait does not see a guest write made while it is blocked.
- Saves (`Save`/`Restore`) do not write the header.
- No title with a known header dependency (Guitar Hero 5 DLC) is available;
  the tests are synthetic.
