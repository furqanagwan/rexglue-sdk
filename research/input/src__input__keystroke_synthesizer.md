# Keystroke synthesizer: input source notes

This record preserves technical and API notes moved from `src/input/keystroke_synthesizer.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/keystroke_synthesizer.cpp#L23)

```text
// The order of this list is also the order in which events are sent if
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/keystroke_synthesizer.cpp#L24)

```text
// multiple buttons change at once.
```

## Source note 3, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/keystroke_synthesizer.cpp#L26)

```text
// 00 - True buttons from xinput button field
```

## Source note 4, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/keystroke_synthesizer.cpp#L37)

```text
/* Guide has no VK */
```

## Source note 5, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/keystroke_synthesizer.cpp#L38)

```text
/* Unknown */
```

## Source note 6, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/keystroke_synthesizer.cpp#L43)

```text
// 16 - Fake buttons generated from analog inputs
```

## Source note 7, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/keystroke_synthesizer.cpp#L46)

```text
// 18
```

## Source note 8, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/keystroke_synthesizer.cpp#L55)

```text
// 26
```

## Source note 9, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/keystroke_synthesizer.cpp#L99)

```text
// First clear buttons with up events, to match XInput when a stick moves
```

## Source note 10, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/keystroke_synthesizer.cpp#L100)

```text
// between directions: THUMB_UPLEFT goes up before THUMB_LEFT goes down.
```
