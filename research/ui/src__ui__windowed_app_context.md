# Windowed app context: ui source notes

This record preserves technical and API notes moved from `src/ui/windowed_app_context.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L22)

```text
// The UI thread is responsible for managing the lifetime of the context.
```

## Source note 2, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L25)

```text
// It's okay to destroy the context from a platform's internal UI loop
```

## Source note 3, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L26)

```text
// callback, primarily on platforms where the loop is run by the OS itself,
```

## Source note 4, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L27)

```text
// and the context can't be created and destroyed in a RAII way, rather, it's
```

## Source note 5, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L28)

```text
// created in an initialization handler and destroyed in a shutdown handler
```

## Source note 6, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L29)

```text
// called by the OS. However, destruction must not be done from within the
```

## Source note 7, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L30)

```text
// queued functions - as in this case, the pending function container, the
```

## Source note 8, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L31)

```text
// mutex, will be accessed after having been destroyed already.
```

## Source note 9, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L33)

```text
// Make sure CallInUIThreadDeferred doesn't call
```

## Source note 10, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L34)

```text
// NotifyUILoopOfPendingFunctions, which is virtual.
```

## Source note 11, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L36)

```text
// Make sure the final ExecutePendingFunctionsFromUIThread doesn't call
```

## Source note 12, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L37)

```text
// PlatformQuitFromUIThread, which is virtual.
```

## Source note 13, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L40)

```text
// Platform-specific quit is expected to be performed by the subclass (the
```

## Source note 14, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L41)

```text
// order of it vs. the final ExecutePendingFunctionsFromUIThread shouldn't
```

## Source note 15, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L42)

```text
// matter anymore, the implementation may assume that no pending functions
```

## Source note 16, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L43)

```text
// will be requested for execution specifically via the platform-specific
```

## Source note 17, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L44)

```text
// loop, as there should be no more references to the context in other
```

## Source note 18, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L45)

```text
// threads), can't call the virtual PlatformQuitFromUIThread anymore.
```

## Source note 19, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L53)

```text
// Will not be called as the loop will not be executed anymore.
```

## Source note 20, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L58)

```text
// Notify unconditionally, even if currently running pending functions. It's
```

## Source note 21, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L59)

```text
// possible for pending functions themselves to run inner platform message
```

## Source note 22, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L60)

```text
// loops, such as when displaying dialogs - in this case, the notification is
```

## Source note 23, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L61)

```text
// needed to run the new function from such an inner loop. A modal loop can be
```

## Source note 24, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L62)

```text
// started even in leftovers happening during the quit, where there's still
```

## Source note 25, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L63)

```text
// opportunity for enqueueing and executing new pending functions - so only
```

## Source note 26, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L64)

```text
// checking if called in the destructor (it's safe to check this without
```

## Source note 27, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L65)

```text
// locking a mutex as it's assumed that if the object is already being
```

## Source note 28, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L66)

```text
// destroyed, no other threads can have references to it - any access would
```

## Source note 29, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L67)

```text
// result in a race condition anyway) as the subclass has already been
```

## Source note 30, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L68)

```text
// destroyed. Having pending_functions_mutex_ unlocked also means that
```

## Source note 31, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L69)

```text
// NotifyUILoopOfPendingFunctions may be done while the UI thread is calling
```

## Source note 32, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L70)

```text
// or has already called PlatformQuitFromUIThread - but it's better than
```

## Source note 33, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L71)

```text
// keeping pending_functions_mutex_ locked as NotifyUILoopOfPendingFunctions
```

## Source note 34, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L72)

```text
// may be implemented as pushing to a fixed-size pipe, in which case it will
```

## Source note 35, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L73)

```text
// have to wait until free space is available, but if the UI thread tries to
```

## Source note 36, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L74)

```text
// lock the mutex afterwards to execute pending functions (and encouters
```

## Source note 37, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L75)

```text
// contention), nothing will be able to receive from the pipe anymore and thus
```

## Source note 38, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L76)

```text
// free the space, causing a deadlock.
```

## Source note 39, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L85)

```text
// The intention is just to make sure the code is executed in the UI thread,
```

## Source note 40, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L86)

```text
// don't defer execution if no need to.
```

## Source note 41, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L95)

```text
// Prevent deadlock if called from the UI thread.
```

## Source note 42, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L113)

```text
// Make sure PlatformQuitFromUIThread is called only once, not from nested
```

## Source note 43, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L114)

```text
// pending function execution during the quit - otherwise it will be called
```

## Source note 44, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L115)

```text
// when it's still possible to add new pending functions. This isn't as wrong
```

## Source note 45, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L116)

```text
// as calling PlatformQuitFromUIThread from the destructor, but still a part
```

## Source note 46, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L117)

```text
// of the contract for simplicity.
```

## Source note 47, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L119)

```text
// Executing pending function unconditionally because it's the contract of
```

## Source note 48, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L120)

```text
// this method that functions are executed immediately.
```

## Source note 49, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L123)

```text
// Potentially calling QuitFromUIThread from inside a pending function (in
```

## Source note 50, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L124)

```text
// the worst and dangerous case, from a pending function executed in the
```

## Source note 51, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L125)

```text
// destructor - and PlatformQuitFromUIThread is virtual).
```

## Source note 52, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L128)

```text
// Call the platform-specific shutdown while letting it assume that no new
```

## Source note 53, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L129)

```text
// functions will be queued anymore (but NotifyUILoopOfPendingFunctions may
```

## Source note 54, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L130)

```text
// still be called after PlatformQuitFromUIThread as the two are not
```

## Source note 55, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L131)

```text
// interlocked). This is different than the order in the destruction, but
```

## Source note 56, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L132)

```text
// there this assumption is ensured by the expectation that there should be no
```

## Source note 57, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L133)

```text
// more references to the context in other threads that would allow queueing
```

## Source note 58, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L134)

```text
// new functions with calling NotifyUILoopOfPendingFunctions.
```

## Source note 59, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L142)

```text
// Removing the function from the queue before executing it, as the function
```

## Source note 60, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L143)

```text
// itself may call ExecutePendingFunctionsFromUIThread - if it's kept, the
```

## Source note 61, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L144)

```text
// inner loop will try to execute it again, resulting in potentially endless
```

## Source note 62, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L145)

```text
// recursion, and even if it's terminated, each level will be trying to
```

## Source note 63, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L146)

```text
// remove the same function from the queue - instead, actually removing
```

## Source note 64, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L147)

```text
// other functions, or even beyond the end of the queue.
```

## Source note 65, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L150)

```text
// Call the function with the lock released as it may take an indefinitely
```

## Source note 66, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L151)

```text
// long time to execute if it opens some dialog (possibly with its own
```

## Source note 67, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L152)

```text
// platform message loop), and in that case, without unlocking, no other
```

## Source note 68, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L153)

```text
// thread would be able to add new pending functions (which would result in
```

## Source note 69, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L154)

```text
// unintended waits for user input). This also allows using std::mutex
```

## Source note 70, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L155)

```text
// instead of std::recursive_mutex.
```

## Source note 71, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L161)

```text
// Atomically with completion of the pending functions loop, disallow adding
```

## Source note 72, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L162)

```text
// new functions after executing the existing ones - it was possible to
```

## Source note 73, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L163)

```text
// enqueue new functions from the leftover ones as there still was
```

## Source note 74, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L164)

```text
// opportunity to call them, so it wasn't necessary to disallow adding
```

## Source note 75, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L165)

```text
// before executing, but now new functions will potentially never be
```

## Source note 76, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L166)

```text
// executed. This is done even if this is just an inner pending functions
```

## Source note 77, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L167)

```text
// execution and there's still potential possibility of adding and executing
```

## Source note 78, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L168)

```text
// new functions in the outer loops - for simplicity and consistency (so
```

## Source note 79, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L169)

```text
// QuitFromUIThread's behavior doesn't depend as much on the location of the
```

## Source note 80, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L170)

```text
// call - inside a pending function or from some system callback of the
```

## Source note 81, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L171)

```text
// window), assuming after a PlatformQuitFromUIThread call, it's not
```

## Source note 82, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context.cpp#L172)

```text
// possible to add new pending functions anymore.
```
