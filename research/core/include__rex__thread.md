# Thread: core source notes

This record preserves technical and API notes moved from `include/rex/thread.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L38)

```text
// This is more like an Event with self-reset when returning from Wait()
```

## Source note 2, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L49)

```text
// Wait for the Fence to be signaled. Clears the signal on return.
```

## Source note 3, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L54)

```text
// keep local copy to minimize loads
```

## Source note 4, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L60)

```text
// We can't just clear the signal as other threads may not have read it yet
```

## Source note 5, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L61)

```text
// wait_count > 0
```

## Source note 6, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L62)

```text
// wait_count == 1
```

## Source note 7, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L63)

```text
// Last one out turn off the lights
```

## Source note 8, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L66)

```text
// Oops, another thread is still waiting, set the new count and keep the
```

## Source note 9, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L67)

```text
// signal.
```

## Source note 10, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L78)

```text
// Use the highest bit (sign bit) as the signal flag and the rest to count
```

## Source note 11, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L79)

```text
// waiting threads.
```

## Source note 12, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L83)

```text
// Returns the total number of logical processors in the host system.
```

## Source note 13, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L86)

```text
// Enables the current process to set thread affinity.
```

## Source note 14, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L87)

```text
// Must be called at startup before attempting to set thread affinity.
```

## Source note 15, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L90)

```text
// Raises the system timer resolution for this process to the finest the
```

## Source note 16, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L91)

```text
// system allows (0.5 ms on current Windows), as Xenia does at startup
```

## Source note 17, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L92)

```text
// (DrChat, 73c30d87a). Without it, Windows wakes sleeps and waits in 15.6 ms
```

## Source note 18, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L93)

```text
// steps, so a 1 ms sleep lasts 15.6 ms. Returns the resolution now in effect,
```

## Source note 19, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L94)

```text
// in 100 ns units, or 0 when it could not be queried.
```

## Source note 20, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L97)

```text
// Gets a stable thread-specific ID, but may not be. Use for informative
```

## Source note 21, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L98)

```text
// purposes only.
```

## Source note 22, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L101)

```text
// Gets a stable thread-specific ID that defaults to the same value as
```

## Source note 23, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L102)

```text
// current_thread_system_id but may be overridden.
```

## Source note 24, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L103)

```text
// Guest threads often change this to the guest thread handle.
```

## Source note 25, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L107)

```text
// Sets the current thread name.
```

## Source note 26, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L110)

```text
// Yields the current thread to the scheduler. Maybe.
```

## Source note 27, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L113)

```text
// Memory barrier (request - may be ignored).
```

## Source note 28, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L116)

```text
// Sleeps the current thread for at least as long as the given duration.
```

## Source note 29, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L126)

```text
// PreciseSleep's interrupt handle was signaled.
```

## Source note 30, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L131)

```text
// Sleeps the current thread for at least as long as the given duration.
```

## Source note 31, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L132)

```text
// The thread is put in an alertable state and may wake to dispatch user
```

## Source note 32, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L133)

```text
// callbacks. If this happens the sleep returns early with
```

## Source note 33, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L134)

```text
// SleepResult::kAlerted.
```

## Source note 34, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L137)

```text
// Sleeps on the calling thread's high-resolution waitable timer: microsecond
```

## Source note 35, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L138)

```text
// precision, independent of the system timer resolution (15.6 ms by default)
```

## Source note 36, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L139)

```text
// and without raising it for the whole system. An alertable sleep returns
```

## Source note 37, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L140)

```text
// kAlerted when a user callback ran. Falls back to Sleep/AlertableSleep if
```

## Source note 38, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L141)

```text
// the timer can't be created.
```

## Source note 39, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L142)

```text
// `interrupt`, if given, ends the sleep early with kInterrupted when it is
```

## Source note 40, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L143)

```text
// signaled (the kernel's title termination event).
```

## Source note 41, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L159)

```text
// A high-resolution timer capable of firing at millisecond-precision. All
```

## Source note 42, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L160)

```text
// timers created in this way are executed in the same thread so callbacks must
```

## Source note 43, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L161)

```text
// be kept short or else all timers will be impacted. This is a simplified
```

## Source note 44, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L162)

```text
// wrapper around QueueTimerRecurring which automatically cancels the timer on
```

## Source note 45, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L163)

```text
// destruction.
```

## Source note 46, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L178)

```text
// Creates a new repeating timer with the given period.
```

## Source note 47, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L179)

```text
// The given function will be called back as close to the given period as
```

## Source note 48, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L180)

```text
// possible.
```

## Source note 49, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L191)

```text
// Results for a WaitHandle operation.
```

## Source note 50, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L193)

```text
// The state of the specified object is signaled.
```

## Source note 51, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L194)

```text
// In a WaitAny the tuple will contain the index of the wait handle that
```

## Source note 52, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L195)

```text
// caused the wait to be satisfied.
```

## Source note 53, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L197)

```text
// The wait was ended by one or more user-mode callbacks queued to the thread.
```

## Source note 54, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L198)

```text
// This will occur when is_alertable is set true.
```

## Source note 55, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L200)

```text
// The time-out interval elapsed, and the object's state is nonsignaled.
```

## Source note 56, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L202)

```text
// The specified object is a mutex object that was not released by the thread
```

## Source note 57, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L203)

```text
// that owned the mutex object before the owning thread terminated. Ownership
```

## Source note 58, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L204)

```text
// of the mutex object is granted to the calling thread and the mutex is set
```

## Source note 59, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L205)

```text
// to nonsignaled.
```

## Source note 60, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L206)

```text
// In a WaitAny the tuple will contain the index of the wait handle that
```

## Source note 61, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L207)

```text
// caused the wait to be abandoned.
```

## Source note 62, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L209)

```text
// The function has failed.
```

## Source note 63, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L217)

```text
// Returns the native handle of the object on the host system.
```

## Source note 64, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L218)

```text
// This value is platform specific.
```

## Source note 65, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L225)

```text
// Waits until the wait handle is in the signaled state, an alert triggers and
```

## Source note 66, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L226)

```text
// a user callback is queued to the thread, or the timeout interval elapses.
```

## Source note 67, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L227)

```text
// If timeout is zero the call will return immediately instead of waiting and
```

## Source note 68, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L228)

```text
// if the timeout is max() the wait will not time out.
```

## Source note 69, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L232)

```text
// Signals one object and waits on another object as a single operation.
```

## Source note 70, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L233)

```text
// Waits until the wait handle is in the signaled state, an alert triggers and
```

## Source note 71, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L234)

```text
// a user callback is queued to the thread, or the timeout interval elapses.
```

## Source note 72, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L235)

```text
// If timeout is zero the call will return immediately instead of waiting and
```

## Source note 73, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L236)

```text
// if the timeout is max() the wait will not time out.
```

## Source note 74, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L241)

```text
// Waits until any of the objects is signaled, with a timeout measured by the
```

## Source note 75, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L242)

```text
// calling thread's high-resolution timer (see PreciseSleep) rather than the
```

## Source note 76, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L243)

```text
// system timer. With 64 handles there is no room for the timer, and the
```

## Source note 77, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L244)

```text
// timeout is rounded up to whole milliseconds instead.
```

## Source note 78, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L252)

```text
// Waits until all of the specified objects are in the signaled state, a
```

## Source note 79, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L253)

```text
// user callback is queued to the thread, or the time-out interval elapses.
```

## Source note 80, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L254)

```text
// If timeout is zero the call will return immediately instead of waiting and
```

## Source note 81, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L255)

```text
// if the timeout is max() the wait will not time out.
```

## Source note 82, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L265)

```text
// Waits until any of the specified objects are in the signaled state, a
```

## Source note 83, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L266)

```text
// user callback is queued to the thread, or the time-out interval elapses.
```

## Source note 84, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L267)

```text
// If timeout is zero the call will return immediately instead of waiting and
```

## Source note 85, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L268)

```text
// if the timeout is max() the wait will not time out.
```

## Source note 86, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L269)

```text
// The second argument of the return tuple indicates which wait handle caused
```

## Source note 87, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L270)

```text
// the wait to be satisfied or abandoned.
```

## Source note 88, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L282)

```text
// Models a Win32-like event object.
```

## Source note 89, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L283)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms682396(v=vs.85).aspx
```

## Source note 90, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L286)

```text
// Creates a manual-reset event object, which requires the use of the
```

## Source note 91, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L287)

```text
// Reset() function to set the event state to nonsignaled.
```

## Source note 92, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L288)

```text
// If initial_state is true the event will start in the signaled state.
```

## Source note 93, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L291)

```text
// Creates an auto-reset event object, and system automatically resets the
```

## Source note 94, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L292)

```text
// event state to nonsignaled after a single waiting thread has been released.
```

## Source note 95, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L293)

```text
// If initial_state is true the event will start in the signaled state.
```

## Source note 96, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L296)

```text
// Sets the specified event object to the signaled state.
```

## Source note 97, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L297)

```text
// If this is a manual reset event the event stays signaled until Reset() is
```

## Source note 98, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L298)

```text
// called. If this is an auto reset event until exactly one wait is satisfied.
```

## Source note 99, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L301)

```text
// Sets the specified event object to the nonsignaled state.
```

## Source note 100, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L302)

```text
// Resetting an event that is already reset has no effect.
```

## Source note 101, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L305)

```text
// Sets the specified event object to the signaled state and then resets it to
```

## Source note 102, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L306)

```text
// the nonsignaled state after releasing the appropriate number of waiting
```

## Source note 103, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L307)

```text
// threads.
```

## Source note 104, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L310)

```text
// Returns whether the event is signaled, without satisfying a wait (an
```

## Source note 105, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L311)

```text
// auto-reset event stays signaled).
```

## Source note 106, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L315)

```text
// Models a Win32-like semaphore object.
```

## Source note 107, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L316)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms682438(v=vs.85).aspx
```

## Source note 108, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L319)

```text
// Creates a new semaphore object.
```

## Source note 109, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L320)

```text
// The initial_count must be greater than or equal to zero and less than or
```

## Source note 110, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L321)

```text
// equal to maximum_count. The state of a semaphore is signaled when its count
```

## Source note 111, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L322)

```text
// is greater than zero and nonsignaled when it is zero. The count is
```

## Source note 112, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L323)

```text
// decreased by one whenever a wait function releases a thread that was
```

## Source note 113, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L324)

```text
// waiting for the semaphore. The count is increased  by a specified amount by
```

## Source note 114, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L325)

```text
// calling the Release() function.
```

## Source note 115, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L328)

```text
// Increases the count of the specified semaphore object by a specified
```

## Source note 116, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L329)

```text
// amount.
```

## Source note 117, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L330)

```text
// release_count must be greater than zero.
```

## Source note 118, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L331)

```text
// Returns false if adding release_count would set the semaphore over the
```

## Source note 119, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L332)

```text
// initially specified maximum_count.
```

## Source note 120, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L336)

```text
// Models a Win32-like mutant (mutex) object.
```

## Source note 121, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L337)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms682411(v=vs.85).aspx
```

## Source note 122, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L340)

```text
// Creates a new mutant object, initially owned by the calling thread if
```

## Source note 123, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L341)

```text
// specified.
```

## Source note 124, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L344)

```text
// Releases ownership of the specified mutex object.
```

## Source note 125, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L345)

```text
// Returns false if the calling thread does not own the mutant object.
```

## Source note 126, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L349)

```text
// Models a Win32-like timer object.
```

## Source note 127, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L350)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms687012(v=vs.85).aspx
```

## Source note 128, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L353)

```text
// Make vtable entries for both so we can defer conversions and only do them
```

## Source note 129, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L354)

```text
// if really necessary (let the calling code what clock it prefers). Windows
```

## Source note 130, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L355)

```text
// kernel sync primitives will work with WinSystemClock while our own
```

## Source note 131, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L356)

```text
// implementation works with steady_clock.
```

## Source note 132, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L360)

```text
// Creates a timer whose state remains signaled until SetOnce() or
```

## Source note 133, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L361)

```text
// SetRepeating() is called to establish a new due time.
```

## Source note 134, line 364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L364)

```text
// Creates a timer whose state remains signaled until a thread completes a
```

## Source note 135, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L365)

```text
// wait operation on the timer object.
```

## Source note 136, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L368)

```text
// Activates the specified waitable timer. When the due time arrives, the
```

## Source note 137, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L369)

```text
// timer is signaled and the thread that set the timer calls the optional
```

## Source note 138, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L370)

```text
// completion routine.
```

## Source note 139, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L371)

```text
// Returns true on success.
```

## Source note 140, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L379)

```text
// Activates the specified waitable timer. When the due time arrives, the
```

## Source note 141, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L380)

```text
// timer is signaled and the thread that set the timer calls the optional
```

## Source note 142, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L381)

```text
// completion routine. A periodic timer automatically reactivates each time
```

## Source note 143, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L382)

```text
// the period elapses, until the timer is canceled or reset.
```

## Source note 144, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L383)

```text
// Returns true on success.
```

## Source note 145, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L392)

```text
// Stops the timer before it can be set to the signaled state and cancels
```

## Source note 146, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L393)

```text
// outstanding callbacks. Threads performing a wait operation on the timer
```

## Source note 147, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L394)

```text
// remain waiting until they time out or the timer is reactivated and its
```

## Source note 148, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L395)

```text
// state is set to signaled. If the timer is already in the signaled state, it
```

## Source note 149, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L396)

```text
// remains in that state.
```

## Source note 150, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L397)

```text
// Returns true on success.
```

## Source note 151, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L409)

```text
// Models a Win32-like thread object.
```

## Source note 152, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L410)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms682453(v=vs.85).aspx
```

## Source note 153, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L419)

```text
// Creates a thread with the given parameters and calls the start routine from
```

## Source note 154, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L420)

```text
// within that thread.
```

## Source note 155, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L425)

```text
// Ends the calling thread.
```

## Source note 156, line 426

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L426)

```text
// No destructors are called, and this function does not return.
```

## Source note 157, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L427)

```text
// The state of the thread object becomes signaled, releasing any other
```

## Source note 158, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L428)

```text
// threads that had been waiting for the thread to terminate.
```

## Source note 159, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L431)

```text
// Returns the ID of the thread.
```

## Source note 160, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L434)

```text
// Returns the current name of the thread, if previously specified.
```

## Source note 161, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L437)

```text
// Sets the name of the thread, used in debugging and logging.
```

## Source note 162, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L440)

```text
// Returns the current priority value for the thread.
```

## Source note 163, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L443)

```text
// Sets the priority value for the thread. This value, together with the
```

## Source note 164, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L444)

```text
// priority class of the thread's process, determines the thread's base
```

## Source note 165, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L445)

```text
// priority level. ThreadPriority contains useful constants.
```

## Source note 166, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L448)

```text
// Returns the current processor affinity mask for the thread.
```

## Source note 167, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L451)

```text
// Sets a processor affinity mask for the thread.
```

## Source note 168, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L452)

```text
// A thread affinity mask is a bit vector in which each bit represents a
```

## Source note 169, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L453)

```text
// logical processor that a thread is allowed to run on. A thread affinity
```

## Source note 170, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L454)

```text
// mask must be a subset of the process affinity mask for the containing
```

## Source note 171, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L455)

```text
// process of a thread.
```

## Source note 172, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L458)

```text
// Adds a user-mode asynchronous procedure call request to the thread queue.
```

## Source note 173, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L459)

```text
// When a user-mode APC is queued, the thread is not directed to call the APC
```

## Source note 174, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L460)

```text
// function unless it is in an alertable state. After the thread is in an
```

## Source note 175, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L461)

```text
// alertable state, the thread handles all pending APCs in first in, first out
```

## Source note 176, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L462)

```text
// (FIFO) order, and the wait operation returns WaitResult::kUserCallback.
```

## Source note 177, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L465)

```text
// Decrements a thread's suspend count. When the suspend count is decremented
```

## Source note 178, line 466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L466)

```text
// to zero, the execution of the thread is resumed.
```

## Source note 179, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L469)

```text
// Suspends the specified thread.
```

## Source note 180, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L472)

```text
// Terminates the thread.
```

## Source note 181, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L473)

```text
// No destructors are called, and this function does not return.
```

## Source note 182, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L474)

```text
// The state of the thread object becomes signaled, releasing any other
```

## Source note 183, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread.h#L475)

```text
// threads that had been waiting for the thread to terminate.
```
