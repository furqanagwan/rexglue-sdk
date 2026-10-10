# Gameinput test: tools source notes

This record preserves technical and API notes moved from `tests/unit/gdk/gameinput_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gameinput_test.cpp#L35)

```text
// out of range clamps
```

## Source note 2, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gameinput_test.cpp#L49)

```text
// up is positive in both
```

## Source note 3, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gameinput_test.cpp#L60)

```text
// Every GameInput button maps to a distinct XInput button.
```

## Source note 4, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gameinput_test.cpp#L84)

```text
// Wheels and sticks usually offer the gamepad kind as well.
```

## Source note 5, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gameinput_test.cpp#L113)

```text
// The capabilities carry what GameInput identified.
```

## Source note 6, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gameinput_test.cpp#L125)

```text
// ReXApp: CreateDefaultInputSystem, then AttachWindow once the runtime is set up.
```

## Source note 7, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gameinput_test.cpp#L126)

```text
// GameInput is the GDK build's default (owner decision, 2026-09-28).
```

## Source note 8, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gameinput_test.cpp#L139)

```text
// The installed runtime once wrote a callback token over the driver's vtable
```

## Source note 9, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gameinput_test.cpp#L140)

```text
// pointer during Setup (RegisterGuideButtonCallback); the next virtual call,
```

## Source note 10, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/gdk/gameinput_test.cpp#L141)

```text
// ReXApp's AttachWindow, crashed. Virtual calls go through the base here.
```
