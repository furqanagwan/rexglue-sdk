# Fiber: core source notes

This record preserves technical and API notes moved from `include/rex/thread/fiber.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/fiber.h#L19)

```text
/// Host OS fiber primitive.
```

## Source note 2, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/fiber.h#L20)

```text
/// Each guest fiber gets one Fiber. Switching preserves the entire C++ call
```

## Source note 3, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/fiber.h#L21)

```text
/// stack, so mid-function resume works without any LR lookup.
```

## Source note 4, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/fiber.h#L23)

```text
/// Convert the calling thread into a fiber.
```

## Source note 5, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/fiber.h#L24)

```text
/// Must be called once on a thread before any SwitchTo.
```

## Source note 6, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/fiber.h#L25)

```text
/// Returns a handle for the thread's current execution context.
```

## Source note 7, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/fiber.h#L28)

```text
/// Create a new fiber with its own host stack.
```

## Source note 8, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/fiber.h#L29)

```text
/// entry(arg) is called when the fiber is first switched to.
```

## Source note 9, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/fiber.h#L32)

```text
/// Suspend the current fiber and resume target.
```

## Source note 10, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/fiber.h#L33)

```text
/// Returns when another fiber calls SwitchTo back to this one.
```

## Source note 11, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/fiber.h#L36)

```text
/// Destroy this fiber. Must not be called while it is executing.
```

## Source note 12, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/fiber.h#L39)

```text
/// Returns the fiber currently executing on this thread, or nullptr.
```
