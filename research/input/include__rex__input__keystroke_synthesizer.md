# Keystroke synthesizer: input source notes

This record preserves technical and API notes moved from `include/rex/input/keystroke_synthesizer.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L22)

```text
// Turns successive gamepad states into XInputGetKeystroke events: one event
```

## Source note 2, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L23)

```text
// per call, key-ups before key-downs, analog triggers and stick directions as
```

## Source note 3, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L24)

```text
// virtual buttons, and key repeat for the last button pressed. Keep one per
```

## Source note 4, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L25)

```text
// physical pad so it survives guest user reassignment.
```

## Source note 5, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L33)

```text
// `active` false reports every button released, so focus loss produces
```

## Source note 6, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L34)

```text
// key-ups and regaining focus produces key-downs. `now_ms` is guest uptime.
```

## Source note 7, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L35)

```text
// Returns X_ERROR_SUCCESS with an event, or X_ERROR_EMPTY. user_index is
```

## Source note 8, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L36)

```text
// left zero; InputSystem stamps the guest user.
```

## Source note 9, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L40)

```text
// Analog inputs past their thresholds as virtual buttons 16-33.
```

## Source note 10, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L45)

```text
// no buttons pressed or repeating has ended
```

## Source note 11, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L46)

```text
// a button is held and the delay is awaited
```

## Source note 12, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L47)

```text
// actively repeating at a rate
```

## Source note 13, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/keystroke_synthesizer.h#L52)

```text
// The button pressed last, and when its down or repeat event was sent.
```
