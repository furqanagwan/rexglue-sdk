# Xinput input driver: input source notes

This record preserves technical and API notes moved from `src/input/xinput/xinput_input_driver.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L33)

```text
// XInput has four fixed native slots, so the slot index rides inside the handle
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L34)

```text
// and the per-slot bookkeeping below stays keyed by it.
```

## Source note 3, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L48)

```text
// Querying an empty slot costs milliseconds, so back off after a miss.
```

## Source note 4, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L69)

```text
// xinput1_4.dll ordinal 108: the capabilities with the pad's USB IDs.
```

## Source note 5, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L80)

```text
// XInput's four battery levels as percentages, matching the guide's four
```

## Source note 6, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L81)

```text
// icons (rex::ui::XboxGuide maps them back).
```

## Source note 7, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L134)

```text
// Support guide button with XInput using XInputGetStateEx
```

## Source note 8, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L135)

```text
// https://source.winehq.org/git/wine.git/?a=commit;h=de3591ca9803add117fbacb8abe9b335e2e44977
```

## Source note 9, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L138)

```text
// Required.
```

## Source note 10, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L145)

```text
// Not required.
```

## Source note 11, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L150)

```text
// Only fail when we don't have the bare essentials;
```

## Source note 12, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L189)

```text
// In supplement mode, per USB ID, the slots the other driver already serves.
```

## Source note 13, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L274)

```text
// Added padding in case we are using XInputGetStateEx
```

## Source note 14, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L280)

```text
// If the guide button is enabled use XInputGetStateEx, otherwise use the
```

## Source note 15, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L281)

```text
// default XInputGetState.
```

## Source note 16, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L327)

```text
// We may want to filter flags before sending to native.
```

## Source note 17, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L328)

```text
// flags is reserved on desktop.
```

## Source note 18, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L334)

```text
// XInputGetKeystroke on Windows has a bug where it will return
```

## Source note 19, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L335)

```text
// ERROR_SUCCESS (0) even if the device is not connected:
```

## Source note 20, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L336)

```text
// https://stackoverflow.com/questions/23669238/xinputgetkeystroke-returning-error-success-while-controller-is-unplugged
```

## Source note 21, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L338)

```text
// So we first check if the device is connected via XInputGetCapabilities, so
```

## Source note 22, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L339)

```text
// we are not passing back an uninitialized X_INPUT_KEYSTROKE structure.
```

## Source note 23, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L359)

```text
// X_ERROR_EMPTY if no new keys
```

## Source note 24, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L360)

```text
// X_ERROR_DEVICE_NOT_CONNECTED if no device
```

## Source note 25, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L361)

```text
// X_ERROR_SUCCESS if key
```

## Source note 26, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/xinput/xinput_input_driver.cpp#L390)

```text
// xinputhid (Bluetooth) reports no battery; the pad's GATT service does.
```
