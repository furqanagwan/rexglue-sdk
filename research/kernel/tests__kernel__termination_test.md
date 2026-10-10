# Termination test: kernel source notes

This record preserves technical and API notes moved from `tests/kernel/termination_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L39)

```text
// A code range for the test's guest functions.
```

## Source note 2, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L49)

```text
// The guest thread body: block in the kernel until termination stops it.
```

## Source note 3, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L50)

```text
// start_context picks how: 0 infinite wait, 1 alertable infinite wait,
```

## Source note 4, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L51)

```text
// 2 1 ms delay, 3 alertable 5 ms delay, 4 alertable 60 s delay (only a user
```

## Source note 5, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L52)

```text
// APC can end it), 5 60 s delay (only the termination event can end it, like
```

## Source note 6, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L53)

```text
// a guest Sleep(INFINITE)).
```

## Source note 7, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L80)

```text
// Waits also wake for the contention thread; loop until terminated.
```

## Source note 8, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L81)

```text
// Termination exits the thread inside the kernel call, so this function
```

## Source note 9, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L82)

```text
// never returns; g_returned counts any that do.
```

## Source note 10, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L105)

```text
// With precise timers every kind of block ends at termination. Without
```

## Source note 11, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L106)

```text
// them a non-alertable 60 s delay (mode 5) sleeps on and is left running,
```

## Source note 12, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L107)

```text
// a documented limitation, so that mode is left out.
```

## Source note 13, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L133)

```text
// Contention: the event keeps flipping while termination runs.
```

## Source note 14, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L142)

```text
// Watchdog: TerminateTitle must return, not wait forever.
```

## Source note 15, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/termination_test.cpp#L149)

```text
// Every guest thread reached a termination point and exited.
```
