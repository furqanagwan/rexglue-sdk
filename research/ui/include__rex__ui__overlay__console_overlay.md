# Console overlay: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/overlay/console_overlay.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/console_overlay.h#L44)

```text
// 0 = initialize to default fraction on first draw
```

## Source note 2, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/console_overlay.h#L47)

```text
// Console-only output (command feedback). Kept out of the log sink/files, but
```

## Source note 3, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/console_overlay.h#L48)

```text
// tagged with the sink generation at the moment it was produced so it can be
```

## Source note 4, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/console_overlay.h#L49)

```text
// interleaved chronologically with the captured log lines at draw time.
```

## Source note 5, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/console_overlay.h#L52)

```text
// sink generation when produced
```

## Source note 6, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/console_overlay.h#L56)

```text
// sink snapshot, refreshed when generation changes
```

## Source note 7, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/console_overlay.h#L60)

```text
// index into spdlog level enum; 0 = trace
```

## Source note 8, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/console_overlay.h#L62)

```text
// category -> enabled
```

## Source note 9, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/console_overlay.h#L64)

```text
// Command input
```

## Source note 10, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/console_overlay.h#L70)

```text
// Autocomplete over cvar/command names.
```

## Source note 11, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/overlay/console_overlay.h#L72)

```text
// selected popup item, -1 = none highlighted
```
