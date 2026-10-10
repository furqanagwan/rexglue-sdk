# Xevent: system source notes

This record preserves technical and API notes moved from `src/system/xevent.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xevent.cpp#L28)

```text
// Leave the wait list alone: it holds the stashed handle.
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xevent.cpp#L29)

```text
// Notification : Synchronization
```

## Source note 3, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xevent.cpp#L45)

```text
// EventNotificationObject (manual reset)
```

## Source note 4, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xevent.cpp#L48)

```text
// EventSynchronizationObject (auto reset)
```

## Source note 5, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xevent.cpp#L71)

```text
// The live host event; reading it doesn't satisfy a wait.
```

## Source note 6, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xevent.cpp#L84)

```text
// Held across the host Set so a waiter it releases clears the state after.
```

## Source note 7, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xevent.cpp#L93)

```text
// KePulseEvent returns the state before the pulse and leaves it reset.
```

## Source note 8, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xevent.cpp#L114)

```text
// A satisfied wait resets a synchronization event; a notification event
```

## Source note 9, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xevent.cpp#L115)

```text
// stays signaled. The callback runs after the wait returns, possibly after
```

## Source note 10, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xevent.cpp#L116)

```text
// another Set, so it records the host state rather than assuming a reset.
```

## Source note 11, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xevent.cpp#L165)

```text
// Reset the event in-case it's an auto-reset.
```
