# Window listener: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/window_listener.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_listener.h#L18)

```text
// Virtual interfaces for types that want to listen for Window events.
```

## Source note 2, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_listener.h#L19)

```text
// Use Window::Add[Input]Listener and Window::Remove[Input]Listener to manage
```

## Source note 3, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_listener.h#L20)

```text
// active listeners.
```

## Source note 4, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_listener.h#L26)

```text
// OnOpened will be followed by various initial setup listeners.
```

## Source note 5, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_listener.h#L30)

```text
// Called when the user asks to close the window (close button, Alt+F4).
```

## Source note 6, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_listener.h#L31)

```text
// Return false to veto: the window stays open and the vetoing party is
```

## Source note 7, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_listener.h#L32)

```text
// expected to close it explicitly later (Window::RequestClose) once it is
```

## Source note 8, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/window_listener.h#L33)

```text
// safe (renderers drained, guest threads stopped). Default accepts.
```
