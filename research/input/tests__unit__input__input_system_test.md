# Input system test: input source notes

This record preserves technical and API notes moved from `tests/unit/input/input_system_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L48)

```text
// Exercise the no-driver branch without depending on attached hardware.
```

## Source note 2, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L65)

```text
/// One pad per id, reporting a standard pad's capabilities and recording the
```

## Source note 3, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L66)

```text
/// last vibration it was sent.
```

## Source note 4, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L170)

```text
/// Restores a double cvar when the test ends.
```

## Source note 5, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L193)

```text
// 0.12 of a standard pad's range is about XInput's own 7849.
```

## Source note 6, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L195)

```text
// Upstream compared against the signed projection and let these through.
```

## Source note 7, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L199)

```text
// Past it, the stick is untouched.
```

## Source note 8, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L202)

```text
// Off, or out of range: leave the stick alone.
```

## Source note 9, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L205)

```text
// A device reporting no range gets no deadzone.
```

## Source note 10, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L232)

```text
// Still a success: the pad is there, it just does not buzz.
```

## Source note 11, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L236)

```text
// The guest's own request is not rewritten.
```

## Source note 12, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L239)

```text
// Toggling silences a running motor at once.
```

## Source note 13, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L254)

```text
// The guest sees an untouched pad; the dialog still reads the real one.
```

## Source note 14, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L260)

```text
// A is pressed to dismiss, and still held as the dialog closes.
```

## Source note 15, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L264)

```text
// Other buttons pressed meanwhile get through.
```

## Source note 16, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L267)

```text
// A counts again once released and pressed anew.
```

## Source note 17, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L283)

```text
// An unmatched remove does not unbalance the count.
```

## Source note 18, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L296)

```text
// Ones the guest never polled for are spent when the dialog closes.
```

## Source note 19, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L328)

```text
// The driver cannot tell.
```

## Source note 20, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/input/input_system_test.cpp#L337)

```text
// No pad for user 1, and none for user 0 once it is unplugged.
```
