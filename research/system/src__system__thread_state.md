# Thread state: system source notes

This record preserves technical and API notes moved from `src/system/thread_state.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/thread_state.cpp#L28)

```text
// System thread. Assign the system thread ID with a high bit
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/thread_state.cpp#L29)

```text
// set so people know what's up.
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/thread_state.cpp#L34)

```text
// Set initial registers
```

## Source note 4, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/thread_state.cpp#L35)

```text
// Stack pointer
```

## Source note 5, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/thread_state.cpp#L36)

```text
// PCR address
```

## Source note 6, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/thread_state.cpp#L38)

```text
// Note(tomc): the rexglue abi passes memory base via 'base' parameter to each function call,
```

## Source note 7, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/thread_state.cpp#L39)

```text
// so we don't need to store it in the context like JIT did.
```
