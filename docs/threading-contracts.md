# Threading, timing and termination contracts

What guest code can rely on for waits, delays, APCs and title termination in
the static runtime, and what was measured (RG-GDK-015). Code:
`src/system/xthread.cpp`, `src/system/xobject.cpp`,
`src/system/kernel_state.cpp`, `src/core/threading_win.cpp`.

## Threads and generated code

- **Every guest thread is a host thread.** There is no guest scheduler; Xenia
  Edge's opt-in one (`guest_scheduler`) and its regressions (Edge #233, #234)
  are not imported. `rex::thread::Fiber` exists only for fibers the guest
  itself creates.
- **Generated code lives in the executable and is never unloaded.** A thread
  starts by looking its entry up in the function dispatcher. An address with
  no registered function logs an error and the thread does not run, rather
  than calling into freed code. `UnregisterModule` clears a module's entries.
- **There is no JIT.** No stack points, safe points or thread suspension
  (Edge #268, Canary #1025's `StepToGuestSafePoint`).

## Timeouts

Guest intervals are 100 ns ticks: negative is relative, positive an absolute
guest system time (100 ns since 1601), zero means now. The guest clock's
scalar applies (`clock_no_scaling` turns it off). A timeout never ends before
the guest asked; the host duration is rounded up.

With `guest_precise_timers = true` (the default), delays and timed waits are
measured by a per-thread high-resolution waitable timer
(`CREATE_WAITABLE_TIMER_HIGH_RESOLUTION`). It needs no change to the system
timer resolution, unlike Canary's 0.5 ms `NtSetTimerResolution` (Canary #872).
With `false`, the Windows millisecond calls are used, as before RG-GDK-015.

| Call | Precise (default) | `guest_precise_timers = false` |
| --- | --- | --- |
| `KeDelayExecutionThread`, non-zero interval | Timer, microseconds | `Sleep`/`SleepEx`, truncated to ms |
| Zero interval | Yield (below-normal priority: `Sleep(100 us)`, itself a yield) | Same |
| Timed wait on one object, or wait-any | Timer added to the wait set | `WaitFor*ObjectsEx`, truncated to ms |
| Timed wait-all, `SignalAndWait` | Truncated to ms (no room for a timer) | Same |
| Wait-any on 64 objects | Rounded up to ms (the set is full) | Truncated to ms |
| Absolute time | Honoured | Honoured (before RG-GDK-015 it asserted in Debug and returned at once) |

Measured on the development machine (Release, `kernel_tests "[.timing-report]" -s`,
median of 40, 2026-09-27):

| Requested | Precise delay | Precise wait | System delay | System wait |
| --- | --- | --- | --- | --- |
| 100 us | 530 us | 516 us | 0 (yield) | 0 (poll) |
| 500 us | 1.01 ms | 1.00 ms | 0 (yield) | 0 (poll) |
| 1 ms | 1.65 ms | 1.68 ms | 15.6 ms | 15.5 ms |
| 2 ms | 2.20 ms | 2.28 ms | 15.4 ms | 15.4 ms |
| 10 ms | 10.3 ms | 10.3 ms | 15.5 ms | 15.7 ms |
| 16 ms | 16.4 ms | 16.2 ms | 31.1 ms | 30.6 ms |
| Absolute +10 ms | 10.4 ms | — | 15.5 ms | — |

The high-resolution timer's own granularity is about 0.5 ms, so sub-ms
requests round up to it. `kernel_tests [timing]` asserts the contract: never
early, within 5 ms for 1–10 ms with precise timers, sub-ms delays yield without
them, absolute times honoured in both modes, a signaled object ends a timed
wait at once, and a user APC ends an alertable delay or wait.

Quantum of Solace (GDK Release, native backends, 90 s): the same scene
progress and CPU use in both modes, 55 and 60 CPU-seconds over the last 60 s.
The game's progress in a run depends on controller input, not the timer mode.

## APCs

A guest APC (`KeInsertQueueApc`, `NtQueueApcThread`) is queued on the target
guest thread, and a host user callback wakes that thread. It runs when the
thread is in an **alertable** wait or delay, which then returns
`X_STATUS_USER_APC`, or when the thread starts. A non-alertable wait or delay
does not deliver APCs.

## Title termination

`KernelState::TerminateTitle` (title exit, `XamLoaderTerminateTitle`,
relaunch) stops guest threads cooperatively:

1. It sets the termination flag and the termination event.
2. It wakes blocked threads by signaling every waitable object, queuing a
   user callback to each guest thread (ending alertable waits and delays), and
   through the termination event, which ends precise delays whether alertable
   or not (a guest `Sleep(INFINITE)`).
3. Each thread reaches `XThread::CheckTitleTermination` in the kernel wait or
   delay it was in, and exits there.
4. It waits up to 200 ms for them, removes guest threads from the thread map,
   clears the flag and resets the event.

Target threads are held by `object_ref` for the whole drain, and the global
lock is never dropped while iterating (the use-after-free that Canary #1025
fixes cannot occur). Threads that don't exit in time are left running, never
killed: `TerminateThread` would orphan whatever host lock they hold.

`kernel_tests [termination]` covers this: 10 rounds of 16 guest threads,
blocked in infinite, alertable and long waits and delays while another thread
flips their event, in both timer modes, with a 5 s watchdog on
`TerminateTitle` and on every thread stopping. Removing the user-callback wake
fails the legacy-mode rounds; removing the termination event fails the
precise-mode rounds.

### Unwinding

A terminated thread exits with `ExitThread` from inside the kernel call. No
host C++ destructors run on that thread's stack, and there is no exception or
unwind machinery for generated code (ADR-004). So:

- **A kernel export must not hold a host lock** when it calls a wait, delay or
  anything else that reaches `CheckTitleTermination`.
- **`object_ref`s held on that stack are not released.** The objects leak;
  this is bounded by the number of threads blocked at termination.
- **The guest stack is freed and the thread's object is signaled** (`Exit`)
  before the host thread ends.

## Limitations

- With `guest_precise_timers = false`, a non-alertable delay is not ended by
  termination and the thread is left running until its delay ends.
- Timed wait-all and `SignalAndWait` keep millisecond (system timer)
  resolution.
- Zero-time delays are unchanged. Edge #251's parking of `Sleep(0)` spinners
  stays a watch until a local title shows the cost (see the ledger).
- No module-transition test with real titles, and NFS Shift and Riddick are
  not available here.
- One machine; timer granularity on other Windows builds and CPUs is not
  measured.
