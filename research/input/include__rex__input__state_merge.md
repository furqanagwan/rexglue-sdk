# State merge: input source notes

This record preserves technical and API notes moved from `include/rex/input/state_merge.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L24)

```text
/// Folds src into dst: buttons OR, triggers max, stick axes larger magnitude,
```

## Source note 2, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L25)

```text
/// packet number newest.
```

## Source note 3, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L30)

```text
/// A stick's {x, y} range as its device's capabilities report it (0xFFFF on
```

## Source note 4, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L31)

```text
/// every standard pad).
```

## Source note 5, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L34)

```text
/// Zeroes each axis inside `percentage` of the range, scaled along the stick's
```

## Source note 6, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L35)

```text
/// angle so a diagonal is not held to a larger push than a cardinal one. The
```

## Source note 7, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L36)

```text
/// scale matches Xenia Canary's deadzone cvars, so 0.12 of a standard pad is
```

## Source note 8, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L37)

```text
/// about XInput's own 7849. 0 or 1 and above leave the stick alone.
```

## Source note 9, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L41)

```text
/// Tracks which device most recently produced real input, per guest user, so
```

## Source note 10, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L42)

```text
/// button glyphs follow the pad in the player's hands.
```

## Source note 11, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L45)

```text
/// Neutral gamepads never take over, so stick drift on an idle pad cannot
```

## Source note 12, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L46)

```text
/// steal the slot.
```

## Source note 13, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/input/state_merge.h#L53)

```text
// Zero-initialized, which is DeviceId::kInvalid.
```
