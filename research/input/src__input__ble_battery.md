# Ble battery: input source notes

This record preserves technical and API notes moved from `src/input/ble_battery.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/ble_battery.h#L19)

```text
// Pads paired over Bluetooth LE (Xbox Wireless over BLE, ROG Raikiri II and
```

## Source note 2, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/ble_battery.h#L20)

```text
// the like) reach XInput through xinputhid, which reports no battery, and
```

## Source note 3, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/ble_battery.h#L21)

```text
// GameInput, which reports them wired. Their GATT Battery Service (0x180F,
```

## Source note 4, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/ble_battery.h#L22)

```text
// Battery Level 0x2A19) has the level. A device read can
```

## Source note 5, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/ble_battery.h#L23)

```text
// take a 15 s timeout when the pad sleeps, so reads run on a worker thread and
```

## Source note 6, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/ble_battery.h#L24)

```text
// callers get the last level read. The worker is detached at destruction, so
```

## Source note 7, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/ble_battery.h#L25)

```text
// exit never waits on a read.
```

## Source note 8, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/ble_battery.h#L34)

```text
/// The last level read for the connected BLE device with this USB vendor
```

## Source note 9, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/ble_battery.h#L35)

```text
/// and product ID, or -1 while none is known. The first call for an ID
```

## Source note 10, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/ble_battery.h#L36)

```text
/// starts reading it.
```

## Source note 11, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/input/ble_battery.h#L45)

```text
// (vendor << 16 | product) to percent, -1 until read.
```
