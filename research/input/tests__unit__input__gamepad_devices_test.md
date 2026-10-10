# Gamepad devices test: input source notes

This record preserves technical and API notes moved from `tests/unit/input/gamepad_devices_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/gamepad_devices_test.cpp#L32)

```text
// The GameInput driver with GameInput replaced by test calls: host devices
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/gamepad_devices_test.cpp#L33)

```text
// are addresses of HostPad objects, and rumble sent to them is recorded.
```

## Source note 3, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/gamepad_devices_test.cpp#L107)

```text
// Buttons user `user` sees, or nullopt when nothing is connected there.
```

## Source note 4, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/gamepad_devices_test.cpp#L157)

```text
// no phantom input from the removed pad
```

## Source note 5, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/gamepad_devices_test.cpp#L182)

```text
// unchanged reading
```

## Source note 6, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/gamepad_devices_test.cpp#L184)

```text
// two host updates between polls count once
```

## Source note 7, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/gamepad_devices_test.cpp#L187)

```text
// focus loss is a change
```

## Source note 8, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/gamepad_devices_test.cpp#L189)

```text
// input while unfocused is not seen
```

## Source note 9, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/gamepad_devices_test.cpp#L228)

```text
// A request while unfocused is remembered, not played.
```

## Source note 10, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/gamepad_devices_test.cpp#L251)

```text
// A focus cycle replays only what the guest asked of the new connection.
```

## Source note 11, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/gamepad_devices_test.cpp#L305)

```text
// No motors: XInput reports zero speeds.
```
