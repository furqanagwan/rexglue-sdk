# Xtimer: system source notes

This record preserves technical and API notes moved from `src/system/xtimer.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xtimer.cpp#L44)

```text
// Caller is checking for STATUS_TIMER_RESUME_IGNORED.
```

## Source note 2, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xtimer.cpp#L52)

```text
// Any timer implementation uses absolute times eventually, convert as early
```

## Source note 3, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xtimer.cpp#L53)

```text
// as possible for increased accuracy
```

## Source note 4, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xtimer.cpp#L60)

```text
// Stash routine for callback.
```

## Source note 5, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xtimer.cpp#L65)

```text
// This callback will only be issued when the timer is fired.
```

## Source note 6, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xtimer.cpp#L69)

```text
// Queue APC to call back routine with (arg, low, high).
```

## Source note 7, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xtimer.cpp#L70)

```text
// It'll be executed on the thread that requested the timer.
```
