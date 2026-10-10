# Window: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/window.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L34)

```text
// Transitions between these phases is sequential and looped (and >= and <=
```

## Source note 2, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L35)

```text
// can be used for openness checks, for closedness checks ! of >= and <= is
```

## Source note 3, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L36)

```text
// needed due to looping), with the exception of kDeleting that may be entered
```

## Source note 4, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L37)

```text
// from any other state (with an assertion for that not being done during
```

## Source note 5, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L38)

```text
// kOpening though as that's extremely dangerous and would require a lot of
```

## Source note 6, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L39)

```text
// handling in OpenImpl on all platforms) as the Window object may be deleted
```

## Source note 7, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L40)

```text
// externally at any moment, and the Window will have no control anymore when
```

## Source note 8, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L41)

```text
// that happens. Another exception is that the window may be closed in the
```

## Source note 9, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L42)

```text
// platform during kOpening - in this case, it will skip kOpenBeforeClosing
```

## Source note 10, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L43)

```text
// and go directly to kClosing and beyond.
```

## Source note 11, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L45)

```text
// The window hasn't been opened yet, or has been fully closed and can be
```

## Source note 12, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L46)

```text
// reopened.
```

## Source note 13, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L47)

```text
// No native window - external state updates change only the desired state,
```

## Source note 14, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L48)

```text
// don't go to the implementation immediately.
```

## Source note 15, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L49)

```text
// No actual state.
```

## Source note 16, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L50)

```text
// Listeners are not called.
```

## Source note 17, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L52)

```text
// OpenImpl is being invoked, the implementation is performing initial
```

## Source note 18, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L53)

```text
// setup.
```

## Source note 19, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L54)

```text
// External state changes are functionally near-impossible as OpenImpl
```

## Source note 20, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L55)

```text
// mostly isn't able to communicate with external Xenia code that may have
```

## Source note 21, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L56)

```text
// any effect on the Window, to avoid interference during the native window
```

## Source note 22, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L57)

```text
// setup which may be pretty complex - and also, this is the phase in which
```

## Source note 23, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L58)

```text
// the native window is being created, so there's no guarantee that the
```

## Source note 24, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L59)

```text
// native window exists throughout this phase.
```

## Source note 25, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L60)

```text
// However, it's still not strictly enforceable that OpenImpl will not cause
```

## Source note 26, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L61)

```text
// any interaction with the Window - it may happen, for instance, if
```

## Source note 27, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L62)

```text
// OpenImpl causes the OS to execute the pending functions in the
```

## Source note 28, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L63)

```text
// WindowedAppContext that might have been, for example, left over from when
```

## Source note 29, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L64)

```text
// the window was still open last time. Therefore, for the reason of state
```

## Source note 30, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L65)

```text
// consistency within OpenImpl, all external state changes are simply
```

## Source note 31, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L66)

```text
// dropped in this phase.
```

## Source note 32, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L67)

```text
// However, the desired state may be updated by the implementation during
```

## Source note 33, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L68)

```text
// OpenImpl still, but via the Update functions (if the implementation or
```

## Source note 34, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L69)

```text
// the OS, for instance, clamps the size of the window during creation, or
```

## Source note 35, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L70)

```text
// refuses to enter fullscreen).
```

## Source note 36, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L71)

```text
// Actual state is first populated during this phase, and it's readable
```

## Source note 37, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L72)

```text
// (with its level of completeness at the specific point in time) for the
```

## Source note 38, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L73)

```text
// internal purposes of the implementation.
```

## Source note 39, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L74)

```text
// Listeners are not called so the implementation can perform all the setup
```

## Source note 40, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L75)

```text
// without outer interference (the common code calls some to let the
```

## Source note 41, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L76)

```text
// listeners be aware of the initial state when the window enters kOpen
```

## Source note 42, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L77)

```text
// anyway).
```

## Source note 43, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L78)

```text
// Note: Closing may occur in the platform during kOpening - skip
```

## Source note 44, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L79)

```text
// kOpenBeforeClosing in this case while closing.
```

## Source note 45, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L81)

```text
// Fully interactive.
```

## Source note 46, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L82)

```text
// The native window exists, external state changes are applied immediately
```

## Source note 47, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L83)

```text
// (or at least immediately requested to be applied shortly after, but the
```

## Source note 48, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L84)

```text
// implementation must make sure that, for instance, if SetFullscreen is
```

## Source note 49, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L85)

```text
// successfully called, but the window will actually enter fullscreen only
```

## Source note 50, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L86)

```text
// at the next platform event loop tick, IsFullscreen will start returning
```

## Source note 51, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L87)

```text
// true immediately).
```

## Source note 52, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L88)

```text
// The desired state can be updated as feedback from the implementation.
```

## Source note 53, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L89)

```text
// Actual state can be retrieved.
```

## Source note 54, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L90)

```text
// Listeners are called.
```

## Source note 55, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L91)

```text
// The only state in which a non-null Surface can be created (it's destroyed
```

## Source note 56, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L92)

```text
// after entering kClosing).
```

## Source note 57, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L94)

```text
// OnBeforeClose is being invoked.
```

## Source note 58, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L95)

```text
// The native window still exists, this is mostly like kOpen, but with no
```

## Source note 59, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L96)

```text
// way of creating a Surface (it's becoming destroyed in this state so the
```

## Source note 60, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L97)

```text
// native window can be destroyed safely in the next phase) or recursively
```

## Source note 61, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L98)

```text
// requesting closing - for consistency during closing within the platform,
```

## Source note 62, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L99)

```text
// state changes also behave like in kOpen.
```

## Source note 63, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L100)

```text
// Listeners are still called as normal, primarily because this is where the
```

## Source note 64, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L101)

```text
// OnClosing listener function is invoked, but reopening the window from a
```

## Source note 65, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L102)

```text
// listener is not possible for state consistency during closing.
```

## Source note 66, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L104)

```text
// OnBeforeClose has completed, but OnAfterClose hasn't been called yet for
```

## Source note 67, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L105)

```text
// the implementation to confirm that it has finished destroying the native
```

## Source note 68, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L106)

```text
// window being closed. This state exists to prevent the situation in which
```

## Source note 69, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L107)

```text
// the Window is somehow reopened in the middle of the implementation's
```

## Source note 70, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L108)

```text
// internal work in closing.
```

## Source note 71, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L109)

```text
// The implementation must detach from the native window and destroy it in
```

## Source note 72, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L110)

```text
// this phase.
```

## Source note 73, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L111)

```text
// The native window is being destroyed - external state updates change only
```

## Source note 74, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L112)

```text
// the desired state, don't go to the implementation immediately.
```

## Source note 75, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L113)

```text
// Actual state is still queryable for internal purposes of the
```

## Source note 76, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L114)

```text
// implementation.
```

## Source note 77, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L115)

```text
// Listeners are not called.
```

## Source note 78, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L117)

```text
// OnBeforeClose has completed, but the close has occurred from a listener,
```

## Source note 79, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L118)

```text
// and the call stack of listeners still hasn't been exited.
```

## Source note 80, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L119)

```text
// This state exists to prevent the situation in which the Window is being
```

## Source note 81, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L120)

```text
// closed and then reopened in the middle of the implementation's internal
```

## Source note 82, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L121)

```text
// work in event handlers. For example, let's assume putting a window (HWND)
```

## Source note 83, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L122)

```text
// in the fullscreen state requires removing window decorations
```

## Source note 84, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L123)

```text
// (SetWindowLong) and resizing the window (SetWindowPos), both being able
```

## Source note 85, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L124)

```text
// to invoke the resize handler (WM_SIZE) and thus the resize listener. In
```

## Source note 86, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L125)

```text
// this case, consider the following situation:
```

## Source note 87, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L126)

```text
// - SetWindowLong called for HWND.
```

## Source note 88, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L127)

```text
// - WM_SIZE arrives.
```

## Source note 89, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L128)

```text
// - Listener's OnResize called.
```

## Source note 90, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L129)

```text
// - Listener's OnResize does RequestClose, destroying the current HWND.
```

## Source note 91, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L130)

```text
// - Listener's OnResize does Open, creating a new HWND.
```

## Source note 92, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L131)

```text
// - SetWindowPos called for HWND, which is different now.
```

## Source note 93, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L132)

```text
// Here, SetWindowLong will be called for one native window, but then it
```

## Source note 94, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L133)

```text
// will be replaced, and SetWindowPos will be called for a different one.
```

## Source note 95, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L134)

```text
// No native window - external state updates change only the desired state,
```

## Source note 96, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L135)

```text
// don't go to the implementation immediately.
```

## Source note 97, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L136)

```text
// No actual state.
```

## Source note 98, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L137)

```text
// Listeners are not called.
```

## Source note 99, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L139)

```text
// The destructor has been called - should transition into this before doing
```

## Source note 100, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L140)

```text
// anything not only in the common, but in the implementation's destructor
```

## Source note 101, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L141)

```text
// as well. The transition must be done regardless of the previous phase as
```

## Source note 102, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L142)

```text
// there's no way the Window can stop its destruction from now on. This is
```

## Source note 103, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L143)

```text
// mostly similar to kClosedLeavingListeners, except there's no way to leave
```

## Source note 104, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L144)

```text
// this phase.
```

## Source note 105, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L150)

```text
// Temporarily revealed, hidden if not interacting with the mouse.
```

## Source note 106, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L155)

```text
// Sized from the window_width / window_height, resolution and
```

## Source note 107, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L156)

```text
// video_mode_* cvars, in that order.
```

## Source note 108, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L159)

```text
// An explicit size, ignoring the cvars.
```

## Source note 109, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L171)

```text
// kOpening - for internal use by the implementation.
```

## Source note 110, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L172)

```text
// kOpen, kOpenBeforeClosing - for both external and internal use.
```

## Source note 111, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L173)

```text
// kClosing - for internal use by the implementation.
```

## Source note 112, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L182)

```text
// `false` is returned only in case of an error while trying to perform the
```

## Source note 113, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L183)

```text
// platform window opening. If the window is already open, or just can't be
```

## Source note 114, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L184)

```text
// reopened in the current phase (as in this case it's assumed that the outer
```

## Source note 115, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L185)

```text
// will handle this situation properly and won't, for instance, leave a
```

## Source note 116, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L186)

```text
// process without windows - it will quit the application in OnBeforeClose of
```

## Source note 117, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L187)

```text
// the window closing of which was initiated before or even during opening,
```

## Source note 118, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L188)

```text
// for instance), `true` is returned. The functions of WindowListeners will be
```

## Source note 119, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L189)

```text
// called only for a newly opened platform window - and the listeners may
```

## Source note 120, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L190)

```text
// close or even destroy the window, in which case this function will still
```

## Source note 121, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L191)

```text
// return `true` to differentiate from an actual error - if it's really
```

## Source note 122, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L192)

```text
// necessary that the platform window is open after the call, check phase()
```

## Source note 123, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L193)

```text
// after calling.
```

## Source note 124, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L195)

```text
// The call may or may not close the window immediately, depending on the
```

## Source note 125, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L196)

```text
// platform (phase() may still return an open phase, and events may still be
```

## Source note 126, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L197)

```text
// sent after the call). Use phase() to check if closing has actually
```

## Source note 127, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L198)

```text
// happened immediately.
```

## Source note 128, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L200)

```text
// Don't allow external close requests during opening for state consistency
```

## Source note 129, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L201)

```text
// inside OpenImpl (if an internal close happens during OpenImpl, the
```

## Source note 130, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L202)

```text
// implementation will be aware of that at least), and don't allow closing
```

## Source note 131, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L203)

```text
// twice.
```

## Source note 132, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L208)

```text
// Must not doing anything else with *this as callbacks might have been
```

## Source note 133, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L209)

```text
// triggered during closing (if it has actually even happened), and the
```

## Source note 134, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L210)

```text
// Window might have been deleted.
```

## Source note 135, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L213)

```text
// The `public` state setters are for calling from outside.
```

## Source note 136, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L214)

```text
// The implementation must use the public getters to obtain the desired state
```

## Source note 137, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L215)

```text
// while applying, but for updating the actual state, or for overriding the
```

## Source note 138, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L216)

```text
// desired state, the `protected` On*Update functions must be used (overall
```

## Source note 139, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L217)

```text
// the On* functions are for the implementation's feedback).
```

## Source note 140, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L225)

```text
// Round trips are not guaranteed to return the same results.
```

## Source note 141, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L227)

```text
// Always rounding up to prevent zero sizes (unless the input is zero) as
```

## Source note 142, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L228)

```text
// well as gaps at the edge.
```

## Source note 143, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L239)

```text
// Rounding to the nearest mostly similar to Windows MulDiv.
```

## Source note 144, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L240)

```text
// Plus old_dpi / 2 for positive values, minus old_dpi / 2 for negative
```

## Source note 145, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L241)

```text
// values for consistent rounding for both positive and negative values (as
```

## Source note 146, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L242)

```text
// the `/` operator rounds towards zero).
```

## Source note 147, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L244)

```text
// (-3 - 1) / 3 == -1
```

## Source note 148, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L245)

```text
// (-2 - 1) / 3 == -1
```

## Source note 149, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L246)

```text
// (-1 - 1) / 3 == 0
```

## Source note 150, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L248)

```text
// (0 + 1) / 3 == 0
```

## Source note 151, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L249)

```text
// (1 + 1) / 3 == 0
```

## Source note 152, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L250)

```text
// (2 + 1) / 3 == 1
```

## Source note 153, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L261)

```text
// The desired logical size of the window when it's not maximized, regardless
```

## Source note 154, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L262)

```text
// of the current state of the window (maximized, fullscreen, etc.)
```

## Source note 155, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L263)

```text
// The implementation may update it, for instance, to clamp it, or when the
```

## Source note 156, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L264)

```text
// user resizes a non-maximized window.
```

## Source note 157, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L271)

```text
// 0 width or height may be returned even in case of an open window with a
```

## Source note 158, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L272)

```text
// valid non-zero-area surface depending on the platform.
```

## Source note 159, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L286)

```text
// Desired state stored by the common Window, modifiable both externally and
```

## Source note 160, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L287)

```text
// by the implementation (including from SetFullscreen itself).
```

## Source note 161, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L295)

```text
// Desired state stored by the common Window, externally modifiable, read-only
```

## Source note 162, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L296)

```text
// in the implementation.
```

## Source note 163, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L300)

```text
// Desired state stored in a platform-dependent way in the implementation,
```

## Source note 164, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L301)

```text
// externally modifiable, read-only by the implementation unless from the
```

## Source note 165, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L302)

```text
// LoadAndApplyIcon implementation. The icon is in Windows .ico format.
```

## Source note 166, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L303)

```text
// Provide null buffer and / or zero size to reset the icon.
```

## Source note 167, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L307)

```text
/// Returns the platform-native window handle (HWND on Windows), or nullptr.
```

## Source note 168, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L308)

```text
/// Valid after Open() returns successfully.
```

## Source note 169, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L311)

```text
// Desired state stored by the common Window, externally modifiable, read-only
```

## Source note 170, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L312)

```text
// in the implementation.
```

## Source note 171, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L317)

```text
// Desired state stored by the common Window, externally modifiable, read-only
```

## Source note 172, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L318)

```text
// in the implementation.
```

## Source note 173, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L323)

```text
// Locks the pointer and switches motion events to relative deltas
```

## Source note 174, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L324)

```text
// (MouseEvent::dx/dy), for mouse look. Returns whether it took.
```

## Source note 175, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L329)

```text
// Fallback when relative mode isn't available. Returns false, leaving the
```

## Source note 176, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L330)

```text
// outputs untouched, unless the pointer verifiably reached the center.
```

## Source note 177, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L337)

```text
// Desired state stored by the common Window, externally modifiable, read-only
```

## Source note 178, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L338)

```text
// in the implementation. Whether the window is an active text input field for
```

## Source note 179, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L339)

```text
// the OS input method. Leaving it on for the session pulls in IME candidate
```

## Source note 180, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L340)

```text
// windows and the on screen keyboard during button-only gameplay.
```

## Source note 181, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L344)

```text
// Desired state stored by the common Window, externally modifiable, read-only
```

## Source note 182, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L345)

```text
// in the implementation.
```

## Source note 183, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L347)

```text
// Setting this to kAutoHidden from any _other_ visibility should hide the
```

## Source note 184, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L348)

```text
// cursor immediately - for instance, if the external code wants to auto-hide
```

## Source note 185, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L349)

```text
// the cursor in fullscreen, to allow going into the fullscreen mode to hide
```

## Source note 186, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L350)

```text
// the cursor instantly.
```

## Source note 187, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L354)

```text
// Idle time before kAutoHidden hides the cursor. Takes effect the next time
```

## Source note 188, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L355)

```text
// the auto-hide timer is armed (the next mouse motion).
```

## Source note 189, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L359)

```text
// May be applied in a delayed way or dropped at all, HasFocus will not
```

## Source note 190, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L360)

```text
// necessarily be true immediately.
```

## Source note 191, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L365)

```text
// Request repainting of the surface. Can be called from non-UI threads as
```

## Source note 192, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L366)

```text
// long as they know the Surface exists and isn't in the middle of being
```

## Source note 193, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L367)

```text
// changed to another (the synchronization of this fact between the UI thread
```

## Source note 194, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L368)

```text
// and the caller thread must be done externally through OnSurfaceChanged).
```

## Source note 195, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L381)

```text
// The receiver, which must never be instantiated in the Window object itself
```

## Source note 196, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L382)

```text
// (rather, usually it should be created as a local variable, because only
```

## Source note 197, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L383)

```text
// LIFO-ordered creation and deletion of these is supported), that allows
```

## Source note 198, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L384)

```text
// deletion of the Window from within an event handler (which may invoke a
```

## Source note 199, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L385)

```text
// WindowListener, and window listeners are allowed to destroy windows; also
```

## Source note 200, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L386)

```text
// they may execute, for instance, the functions requested to be executed in
```

## Source note 201, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L387)

```text
// the UI thread in the WindowedAppContext, which are also allowed to destroy
```

## Source note 202, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L388)

```text
// windows - because if the former wasn't allowed, the latter would be
```

## Source note 203, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L389)

```text
// required to destroy windows as a result of UI interaction) to be caught by
```

## Source note 204, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L390)

```text
// functions inside the Window in order to stop interacting with `*this` and
```

## Source note 205, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L391)

```text
// returning after this happens.
```

## Source note 206, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L392)

```text
// Note that the receivers are signaled in the *end* of the destruction of the
```

## Source note 207, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L393)

```text
// common Window, when truly nothing can be done with it anymore, so it's safe
```

## Source note 208, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L394)

```text
// to assume that right after the creation of the WindowDestructionReceiver,
```

## Source note 209, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L395)

```text
// it will still be in an unsignaled state even if it's used somewhere in the
```

## Source note 210, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L396)

```text
// destructor. The reason is that the users of the WindowDestructionReceiver
```

## Source note 211, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L397)

```text
// are expected to stop accessing the Window *immediately* once
```

## Source note 212, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L398)

```text
// IsWindowDestroyed becomes `true`, and to leave it in a potentially
```

## Source note 213, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L399)

```text
// indeterminate state - but the code executed subsequently in the destructor
```

## Source note 214, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L400)

```text
// may still use that state meaningfully.
```

## Source note 215, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L411)

```text
// If the window is not null, removal from the stack must happen
```

## Source note 216, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L412)

```text
// regardless of `phase_ == Phase::kDeleting`, because the window
```

## Source note 217, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L413)

```text
// destructor iterates the receivers after EnterDestructor(), and if the
```

## Source note 218, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L414)

```text
// receiver is not removed in this case, the destructor will do
```

## Source note 219, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L415)

```text
// use-after-free.
```

## Source note 220, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L417)

```text
// Only LIFO order is supported (normally through RAII).
```

## Source note 221, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L425)

```text
// Helper functions for common usages of the receiver. Unlike
```

## Source note 222, line 426

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L426)

```text
// IsWindowDestroyed, these, however, may return false immediately on
```

## Source note 223, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L427)

```text
// creation.
```

## Source note 224, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L428)

```text
// Primarily for the implementation (most importantly its native event
```

## Source note 225, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L429)

```text
// handler), to stop interacting with the native window given that it was
```

## Source note 226, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L430)

```text
// possible before the function call it's guarded with.
```

## Source note 227, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L432)

```text
// For guarding Apply* calls if one state setter needs to make multiple of
```

## Source note 228, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L433)

```text
// them (or just detecting if it's okay to call Apply*).
```

## Source note 229, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L442)

```text
// The Window must set window_ to nullptr in its destructor.
```

## Source note 230, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L448)

```text
// Like in the Windows Media Player.
```

## Source note 231, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L449)

```text
// A more modern Windows example, Movies & TV in Windows 11 21H2, has 5000,
```

## Source note 232, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L450)

```text
// but it's too long especially for highly dynamic games.
```

## Source note 233, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L451)

```text
// Implementations may use different values according to the platform's UX
```

## Source note 234, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L452)

```text
// conventions.
```

## Source note 235, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L458)

```text
// If implementation-specific destruction happens, should be called in the
```

## Source note 236, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L459)

```text
// beginning of the implementation's destructor so the implementation can
```

## Source note 237, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L460)

```text
// destroy the platform window without doing something unsafe in destruction.
```

## Source note 238, line 463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L463)

```text
// Disconnect from the surface before destroying the window behind it.
```

## Source note 239, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L467)

```text
// For an open window, the implementation should return the current DPI for
```

## Source note 240, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L468)

```text
// the window. For a non-open one, it should be the closest approximation,
```

## Source note 241, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L469)

```text
// such as the last DPI from an existing window, the system DPI, or just the
```

## Source note 242, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L470)

```text
// medium DPI (0 returned from it will also be treated as medium DPI).
```

## Source note 243, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L473)

```text
// Deletion of the window may (and must) not happen in OpenImpl, the listeners
```

## Source note 244, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L474)

```text
// are deferred, so there's no need to use WindowDestructionReceiver in it.
```

## Source note 245, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L475)

```text
// In case of failure, the implementation must not leave itself in an
```

## Source note 246, line 476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L476)

```text
// indeterminate state, so another attempt to open the window can be made.
```

## Source note 247, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L477)

```text
// The implementation must apply the following desired state if it needs it,
```

## Source note 248, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L478)

```text
// directly (not via Set* methods as they will be dropped during OpenImpl
```

## Source note 249, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L479)

```text
// since the window is not fully open yet):
```

## Source note 250, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L480)

```text
// - Title (GetTitle()).
```

## Source note 251, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L481)

```text
// - Icon (from the last LoadAndApplyIcon call).
```

## Source note 252, line 482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L482)

```text
// - Main menu (GetMainMenu()) and its enablement.
```

## Source note 253, line 483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L483)

```text
// - Desired logical size (GetDesiredLogicalWidth() / Height(), taking into
```

## Source note 254, line 484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L484)

```text
//   account that the main menu, during the initial opening, should not be
```

## Source note 255, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L485)

```text
//   included in this size - it specifies the client area that painting will
```

## Source note 256, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L486)

```text
//   be done to), within the capabilities of the platform (may be clamped by
```

## Source note 257, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L487)

```text
//   the OS, for instance - in this case, OnDesiredLogicalSizeUpdate may be
```

## Source note 258, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L488)

```text
//   called from within OpenImpl to store the clamped size for later).
```

## Source note 259, line 489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L489)

```text
// - Fullscreen (GetFullscreen()) - however, if possible, the calculations
```

## Source note 260, line 490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L490)

```text
//   that would normally be done for a non-fullscreen window in OpenImpl
```

## Source note 261, line 491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L491)

```text
//   should also be done if entering fullscreen, including the menu-related
```

## Source note 262, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L492)

```text
//   ones - first, the usual windowed geometry calculations should be done,
```

## Source note 263, line 493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L493)

```text
//   and then fullscreen should be entered; but preferably still entering
```

## Source note 264, line 494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L494)

```text
//   fullscreen before actually showing a visible window to the user for a
```

## Source note 265, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L495)

```text
//   seamless transition.
```

## Source note 266, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L496)

```text
// - Mouse capture (IsMouseCaptureRequested()).
```

## Source note 267, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L497)

```text
// - Cursor visibility (GetCursorVisibility()).
```

## Source note 268, line 498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L498)

```text
// Also, as a result of the OpenImpl call, these function should be called
```

## Source note 269, line 499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L499)

```text
// (immediately from within OpenImpl directly or indirectly through the native
```

## Source note 270, line 500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L500)

```text
// event handling, or shortly after during the UI main loop) to provide the
```

## Source note 271, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L501)

```text
// initial actual state to the common Window code so it returns the correct
```

## Source note 272, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L503)

```text
// - OnActualSizeUpdate, at least if the window isn't opened as not yet
```

## Source note 273, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L504)

```text
//   visible on screen (otherwise the size will be assumed to be 0x0 until the
```

## Source note 274, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L505)

```text
//   next size update caused by something likely requiring user interaction).
```

## Source note 275, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L506)

```text
// - OnFocusUpdate, at least if the focus has been obtained (otherwise the
```

## Source note 276, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L507)

```text
//   window will be assumed to be not in focus until it goes into the focus
```

## Source note 277, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L508)

```text
//   again).
```

## Source note 278, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L509)

```text
// Also, if some of the desired state that may be updated by the
```

## Source note 279, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L510)

```text
// implementation could not be applied (such as the fullscreen mode), and
```

## Source note 280, line 511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L511)

```text
// certain values of the implementation state are either normally
```

## Source note 281, line 512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L512)

```text
// differentiated within the implementation or are just meaningful considering
```

## Source note 282, line 513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L513)

```text
// the platform's defaults (for instance, the platform inherently supports
```

## Source note 283, line 514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L514)

```text
// only fullscreen, possibly doesn't have a concept of windows at all), it's
```

## Source note 284, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L515)

```text
// recommended to call the appropriate On*Update functions to update the
```

## Source note 285, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L516)

```text
// desired state to the actual one.
```

## Source note 286, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L520)

```text
// Apply* are called only if CanApplyState() is true (unless the function
```

## Source note 287, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L521)

```text
// should do more than just applying, such as also updating the desired state
```

## Source note 288, line 522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L522)

```text
// in a platform-dependent way - see each individual function).
```

## Source note 289, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L523)

```text
// ApplyNew* means that the value has actually been changed to something
```

## Source note 290, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L524)

```text
// different than it was previously.
```

## Source note 291, line 529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L529)

```text
// can_apply_state_in_current_phase whether the window is in a life cycle
```

## Source note 292, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L530)

```text
// phase that would normally accept Apply calls (the native window surely
```

## Source note 293, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L531)

```text
// exists), since this function may be called in closed states too to update
```

## Source note 294, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L532)

```text
// the desired icon (since it's stored in the implementation) - the
```

## Source note 295, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L533)

```text
// implementation may, however, ignore it and use a more granular check of the
```

## Source note 296, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L534)

```text
// existence of the native window and the safety of updating the icon for
```

## Source note 297, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L535)

```text
// better internal state consistency. The icon is in Windows .ico format. If
```

## Source note 298, line 536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L536)

```text
// the buffer is null or the size is 0, the icon should be reset to the
```

## Source note 299, line 537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L537)

```text
// default one. Returns whether the icon has been updated successfully.
```

## Source note 300, line 545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L545)

```text
// May be called to add, replace or remove the main menu.
```

## Source note 301, line 547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L547)

```text
// If there's main menu, and state can be applied, will be called to make the
```

## Source note 302, line 548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L548)

```text
// implementation's state consistent with the new state of the MenuItems of
```

## Source note 303, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L549)

```text
// the main menu after changes have been made to them.
```

## Source note 304, line 551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L551)

```text
// Will be called even if capturing while the mouse is already assumed to be
```

## Source note 305, line 552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L552)

```text
// captured, in case something has released it in the OS.
```

## Source note 306, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L559)

```text
// If state can be applied, this is called to request bringing the window into
```

## Source note 307, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L560)

```text
// focus (and once that's done by the OS, update the actual focus state). Does
```

## Source note 308, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L561)

```text
// nothing otherwise (focus can't be requested before the window is open, a
```

## Source note 309, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L562)

```text
// closed window is always assumed to be not in focus).
```

## Source note 310, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L567)

```text
// If new_surface_potentially_exists is false, creation of the new surface for
```

## Source note 311, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L568)

```text
// the window won't be updated, and it may be called from the destructor (via
```

## Source note 312, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L569)

```text
// EnterDestructor to destroy the surface before destroying what it depends
```

## Source note 313, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L570)

```text
// on) as no virtual functions (including CreateSurface) will be called.
```

## Source note 314, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L571)

```text
// This function is nonvirtual itself for this reason as well.
```

## Source note 315, line 573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L573)

```text
// Called only for an open window.
```

## Source note 316, line 575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L575)

```text
// Called only if the Surface exists.
```

## Source note 317, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L578)

```text
// Will also disconnect the surface if needed.
```

## Source note 318, line 582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L582)

```text
// Asks all listeners whether a user-initiated close may proceed. Returns
```

## Source note 319, line 583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L583)

```text
// false if any listener vetoed or the window was destroyed from a callback.
```

## Source note 320, line 589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L589)

```text
// These functions may usually also be called as part of the opening process
```

## Source note 321, line 590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L590)

```text
// from within OpenImpl (directly or through the platform event handler
```

## Source note 322, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L591)

```text
// invoked during it) to actualize the state for the newly createad window,
```

## Source note 323, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L592)

```text
// especially if it's different than the desired one.
```

## Source note 324, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L595)

```text
// For calling when the platform changes something in the non-maximized,
```

## Source note 325, line 596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L596)

```text
// non-fullscreen size of the window.
```

## Source note 326, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L602)

```text
// If the size of the client area is the same as the currently assumed one
```

## Source note 327, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L603)

```text
// (the desired / last size for a newly opened / reopened window, the last
```

## Source note 328, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L604)

```text
// actual size for an already open window), does nothing and returns false.
```

## Source note 329, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L605)

```text
// Otherwise, updates the size, notifies what depends on the size about the
```

## Source note 330, line 606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L606)

```text
// change, and returns true. Not storing the new size in the UISetupEvent
```

## Source note 331, line 607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L607)

```text
// because a resize listener may request another resize, in which case it will
```

## Source note 332, line 608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L608)

```text
// be outdated - listeners must query the new physical size from the window
```

## Source note 333, line 609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L609)

```text
// explicitly.
```

## Source note 334, line 615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L615)

```text
// Pass true as force_paint in case the platform can't retain the image from
```

## Source note 335, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L616)

```text
// the previous paint so it won't be skipped if there are no content updates.
```

## Source note 336, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L637)

```text
// To support nested listener calls, in case a listener does some
```

## Source note 337, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L638)

```text
// interaction with the window that results in more events being triggered
```

## Source note 338, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L639)

```text
// (such as calling Windows API functions that return a result from a
```

## Source note 339, line 640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L640)

```text
// message handled by a window, rather that simply enqueueing the message).
```

## Source note 340, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L642)

```text
// Using indices, not iterators, because after the erasure, the adjustment
```

## Source note 341, line 643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L643)

```text
// must be done for the vector element indices that would be in the iterator
```

## Source note 342, line 644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L644)

```text
// range that would be invalidated.
```

## Source note 343, line 656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L656)

```text
// To support nested listener calls.
```

## Source note 344, line 658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L658)

```text
// Reverse iterator because input handlers with a higher Z order index may
```

## Source note 345, line 659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L659)

```text
// correspond to what's displayed on top of what has a lower Z order index,
```

## Source note 346, line 660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L660)

```text
// so what's higher may consum the event.
```

## Source note 347, line 665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L665)

```text
// If the window is closed, the platform native window is either being
```

## Source note 348, line 666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L666)

```text
// destroyed, or doesn't exist anymore, and thus it's in a non-interactive
```

## Source note 349, line 667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L667)

```text
// state.
```

## Source note 350, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L671)

```text
// In kOpening, OpenImpl itself pulls the desired state itself and applies
```

## Source note 351, line 672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L672)

```text
// it, the Apply* functions can't be called and are unsafe to call because
```

## Source note 352, line 673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L673)

```text
// the implementation is an incomplete state, with the platform window
```

## Source note 353, line 674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L674)

```text
// potentially not existing. In kOpenBeforeClosing, as the native window
```

## Source note 354, line 675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L675)

```text
// still hasn't been destroyed and it can receive new state, still allowing
```

## Source note 355, line 676

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L676)

```text
// applying new state for more consistency between the desired and the
```

## Source note 356, line 677

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L677)

```text
// actual state during the final listener invocation.
```

## Source note 357, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L684)

```text
// The listeners may delete the Window - check the destruction receiver after
```

## Source note 358, line 685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L685)

```text
// calling and stop doing anything accessing *this if that happens.
```

## Source note 359, line 692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L692)

```text
// If opening, surface creation is deferred until all the initial setup has
```

## Source note 360, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L693)

```text
// completed. Destruction of the surface is also a part of the closing
```

## Source note 361, line 694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L694)

```text
// process in OnBeforeClose.
```

## Source note 362, line 706

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L706)

```text
// All currently-attached listeners that get event notifications.
```

## Source note 363, line 708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L708)

```text
// Ordered by the Z order, and then by the time of addition (but executed in
```

## Source note 364, line 709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L709)

```text
// reverse order).
```

## Source note 365, line 710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L710)

```text
// Note: All the iteration logic involving this Z ordering must be the same as
```

## Source note 366, line 711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L711)

```text
// in drawing (in the UI drawers in the Presenter), but in reverse.
```

## Source note 367, line 713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L713)

```text
// Linked list-based stacks of the contexts of the listener iterations
```

## Source note 368, line 714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L714)

```text
// currently being done, usually allocated on the stack.
```

## Source note 369, line 720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L720)

```text
// Set by the implementation via OnActualSizeUpdate (from OpenImpl or from the
```

## Source note 370, line 721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L721)

```text
// platform resize handler).
```

## Source note 371, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L744)

```text
// Whether currently in InPaint to prevent recursive painting in case it's
```

## Source note 372, line 745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L745)

```text
// triggered somehow from within painting again, because painting is much more
```

## Source note 373, line 746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L746)

```text
// complex than just a small state update, and recursive painting is
```

## Source note 374, line 747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L747)

```text
// completely unsupported by the Presenter.
```

## Source note 375, line 749

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window.h#L749)

```text
// A paint arrived during painting and must be requested again afterwards.
```
