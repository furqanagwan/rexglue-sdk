# Windowed app context: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/windowed_app_context.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L24)

```text
// Context for inputs provided by the entry point and interacting with the
```

## Source note 2, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L25)

```text
// platform's UI loop, to be implemented by platforms.
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L32)

```text
// The thread where the object is created will be assumed to be the UI thread,
```

## Source note 4, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L33)

```text
// for the purpose of being able to perform CallInUIThreadSynchronous before
```

## Source note 5, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L34)

```text
// running the loop.
```

## Source note 6, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L37)

```text
// CallInUIThreadDeferred and CallInUIThread are fire and forget - will be
```

## Source note 7, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L38)

```text
// executed at some point the future when the UI thread is running the loop
```

## Source note 8, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L39)

```text
// and is not busy doing other things.
```

## Source note 9, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L40)

```text
// Therefore, references to objects in the function may outlive the owners of
```

## Source note 10, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L41)

```text
// those objects, so use-after-free is very easy to create if not being
```

## Source note 11, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L42)

```text
// careful enough.
```

## Source note 12, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L43)

```text
// There are two solutions to this issue:
```

## Source note 13, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L44)

```text
// - Signaling a fence in the function, awaiting it before destroying objects
```

## Source note 14, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L45)

```text
//   referenced by the function (works for shutdown from non-UI threads, or
```

## Source note 15, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L46)

```text
//   for CallInUIThread, but not CallInUIThreadDeferred, in the UI thread).
```

## Source note 16, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L47)

```text
// - Calling ExecutePendingFunctionsFromUIThread in the UI thread before
```

## Source note 17, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L48)

```text
//   destroying objects referenced by the function (works for shutdown from
```

## Source note 18, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L49)

```text
//   the UI thread, though CallInUIThreadSynchronous doing
```

## Source note 19, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L50)

```text
//   ExecutePendingFunctionsFromUIThread is also an option for shutdown from
```

## Source note 20, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L51)

```text
//   any thread).
```

## Source note 21, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L52)

```text
// (These are not required if all the called function is doing is triggering a
```

## Source note 22, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L53)

```text
// quit with the context pointer captured by value, as the only object
```

## Source note 23, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L54)

```text
// involved will be the context itself, with a pointer that is valid until
```

## Source note 24, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L55)

```text
// it's destroyed - the most late location of the pending function execution
```

## Source note 25, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L56)

```text
// possible.)
```

## Source note 26, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L57)

```text
// Returning true if the function has been enqueued (it will be called at some
```

## Source note 27, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L58)

```text
// point, at worst, before exiting the loop) or called immediately, false if
```

## Source note 28, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L59)

```text
// it was dropped (if calling after exiting the loop).
```

## Source note 29, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L60)

```text
// It's okay to enqueue functions from queued functions already being
```

## Source note 30, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L61)

```text
// executed. As execution may be happening during the destruction of the
```

## Source note 31, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L62)

```text
// context as well, in this case, CallInUIThreadDeferred must make sure it
```

## Source note 32, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L63)

```text
// doesn't call anything virtual in the destructor.
```

## Source note 33, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L65)

```text
// Enqueues the function regardless of the current thread. Won't necessarily
```

## Source note 34, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L66)

```text
// be executed directly from the platform main loop as
```

## Source note 35, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L67)

```text
// ExecutePendingFunctionsFromUIThread may be called anywhere (for instance,
```

## Source note 36, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L68)

```text
// to await pending functions before destroying what they are referencing).
```

## Source note 37, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L70)

```text
// Executes the function immediately if already in the UI thread, enqueues it
```

## Source note 38, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L71)

```text
// otherwise.
```

## Source note 39, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L74)

```text
// It's okay to call this function from the queued functions themselves (such
```

## Source note 40, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L75)

```text
// as in the case of waiting for a pending async CallInUIThreadDeferred
```

## Source note 41, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L76)

```text
// described above - the wait may be done inside a CallInUIThreadSynchronous
```

## Source note 42, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L77)

```text
// function safely).
```

## Source note 43, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L80)

```text
// If on the target platform, the program itself is supposed to run the UI
```

## Source note 44, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L81)

```text
// loop, this may be checked before doing blocking message waits as an
```

## Source note 45, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L82)

```text
// additional safety measure beyond what PlatformQuitFromUIThread guarantees,
```

## Source note 46, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L83)

```text
// and if true, the loop should be terminated (pending function will already
```

## Source note 47, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L84)

```text
// have been executed). This doesn't imply that pending functions have been
```

## Source note 48, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L85)

```text
// executed in all contexts, however - they can be executing from quitting
```

## Source note 49, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L86)

```text
// itself (in the worst case, in the destructor where virtual methods can't be
```

## Source note 50, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L87)

```text
// called), and in this case, this will be returning true.
```

## Source note 51, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L93)

```text
// Immediately disallows adding new pending UI functions, executes the already
```

## Source note 52, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L94)

```text
// queued ones, and makes sure that the UI loop is aware that it was asked to
```

## Source note 53, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L95)

```text
// stop running. This must not destroy the context or the app directly - the
```

## Source note 54, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L96)

```text
// actual app shutdown will be initiated at some point outside the scope of
```

## Source note 55, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L97)

```text
// app's callbacks. May call virtual functions - invoke
```

## Source note 56, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L98)

```text
// ExecutePendingFunctionsFromUIThread(true) in the destructor instead, and
```

## Source note 57, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L99)

```text
// use the platform-specific destructor to invoke the needed
```

## Source note 58, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L100)

```text
// PlatformQuitFromUIThread logic (it should be safe, in case of destruction,
```

## Source note 59, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L101)

```text
// to perform platform-specific quit request logic before the common part -
```

## Source note 60, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L102)

```text
// NotifyUILoopOfPendingFunctions won't be called after the platform-specific
```

## Source note 61, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L103)

```text
// quit request logic in this case anyway as destruction expects that there
```

## Source note 62, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L104)

```text
// are no references to the object in other threads). Safe to call from within
```

## Source note 63, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L105)

```text
// pending functions - requesting quit from non-UI threads is possible via
```

## Source note 64, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L106)

```text
// methods like CallInUIThreadSynchronous. For deferred, rather than
```

## Source note 65, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L107)

```text
// immediate, quitting from the UI thread, CallInUIThreadDeferred may be used
```

## Source note 66, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L108)

```text
// (but the context pointer should be captured by value not to require
```

## Source note 67, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L109)

```text
// explicit completion forcing in case the storage of the pointer is lost
```

## Source note 68, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L110)

```text
// before the function is called).
```

## Source note 69, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L112)

```text
// Callable from any thread. This is a special case where a completely
```

## Source note 70, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L113)

```text
// fire-and-forget CallInUIThreadDeferred is safe, as the function only
```

## Source note 71, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L114)

```text
// references nonvirtual functions of the context itself, and will be called
```

## Source note 72, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L115)

```text
// at most from the destructor. No need to return the result - it doesn't
```

## Source note 73, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L116)

```text
// matter if has quit already or not, as that's the intention anyway.
```

## Source note 74, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L124)

```text
// Can be called from any thread (including the UI thread) to ask the OS to
```

## Source note 75, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L125)

```text
// run an iteration of the UI loop (with or without processing internal UI
```

## Source note 76, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L126)

```text
// messages, this is platform-dependent) so pending functions will be executed
```

## Source note 77, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L127)

```text
// at some point. pending_functions_mutex_ will not be locked when this is
```

## Source note 78, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L128)

```text
// called (to make sure that, for example, the caller, waiting for space in
```

## Source note 79, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L129)

```text
// the OS's message queue, such as in case of a Linux pipe, won't be blocking
```

## Source note 80, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L130)

```text
// the UI thread that has started executing pending messages while pumping
```

## Source note 81, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L131)

```text
// that pipe, resulting in a deadlock) - implementations don't directly see
```

## Source note 82, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L132)

```text
// anything protected by it anyway, and a spurious notification shouldn't be
```

## Source note 83, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L133)

```text
// causing any damage, this is similar to how condition variables can be
```

## Source note 84, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L134)

```text
// signaled outside the critical section (signaling inside the critical
```

## Source note 85, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L135)

```text
// section may also cause contention if the thread waiting is woken up quickly
```

## Source note 86, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L136)

```text
// enough). This, however, means that NotifyUILoopOfPendingFunctions may be
```

## Source note 87, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L137)

```text
// called in a non-UI thread after the final pending message processing
```

## Source note 88, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L138)

```text
// followed by PlatformQuitFromUIThread in the UI thread - so it can still be
```

## Source note 89, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L139)

```text
// called after a quit.
```

## Source note 90, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L142)

```text
// Called when requesting a quit in the UI thread to tell the platform that
```

## Source note 91, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L143)

```text
// the UI loop needs to be terminated. The pending function queue is assumed
```

## Source note 92, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L144)

```text
// to be empty before this is called, and no new pending functions can be
```

## Source note 93, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L145)

```text
// added (but NotifyUILoopOfPendingFunctions may still be called as it's not
```

## Source note 94, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L146)

```text
// mutually exclusive with PlatformQuitFromUIThread - if this matters, the
```

## Source note 95, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L147)

```text
// platform implementation itself should be resolving this case).
```

## Source note 96, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L153)

```text
// May be called with is_final == true from the destructor - must not call
```

## Source note 97, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L154)

```text
// anything virtual in this case.
```

## Source note 98, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L157)

```text
// Accessible by the UI thread.
```

## Source note 99, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L161)

```text
// Synchronizes producers with each other and with the consumer, as well as
```

## Source note 100, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L162)

```text
// all of them with the pending_functions_accepted_ variable which indicates
```

## Source note 101, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L163)

```text
// whether shutdown has not been performed yet, as after the shutdown, no new
```

## Source note 102, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L164)

```text
// functions will be executed anymore, therefore no new function should be
```

## Source note 103, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L165)

```text
// queued, as it will never be called (thus CallInUIThreadSynchronous for it
```

## Source note 104, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L166)

```text
// will never return, for instance).
```

## Source note 105, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L169)

```text
// Protected by pending_functions_mutex_, writable by the UI thread, readable
```

## Source note 106, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L170)

```text
// by any thread. Must be set to false before exiting the main platform loop,
```

## Source note 107, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L171)

```text
// but before that, all pending functions must be executed no matter what, as
```

## Source note 108, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L172)

```text
// they may need to signal fences currently being awaited (like the
```

## Source note 109, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context.h#L173)

```text
// CallInUIThreadSynchronous fence).
```
