# Xsocket: system source notes

This record preserves technical and API notes moved from `src/system/xsocket.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsocket.cpp#L18)

```text
// #include <rex/system/xnet.h>
```

## Source note 2, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsocket.cpp#L22)

```text
// Standard socket types used by Xbox API emulation
```

## Source note 3, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsocket.cpp#L44)

```text
// VDP is a layer on top of UDP.
```

## Source note 4, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsocket.cpp#L72)

```text
// Disable socket encryption
```

## Source note 5, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsocket.cpp#L142)

```text
// Create a kernel object to represent the new socket, and copy parameters
```

## Source note 6, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsocket.cpp#L143)

```text
// over.
```

## Source note 7, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsocket.cpp#L162)

```text
// Pop from secure packets first
```

## Source note 8, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsocket.cpp#L170)

```text
// BE <- BE
```

## Source note 9, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsocket.cpp#L188)

```text
// Send 2 copies of the packet: One to XNet (for network security) and an
```

## Source note 10, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsocket.cpp#L189)

```text
// unencrypted copy for other Xenia hosts.
```
