# Xsocket: system source notes

This record preserves technical and API notes moved from `include/rex/system/xsocket.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L43)

```text
// Always big-endian!
```

## Source note 2, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L46)

```text
// sin_zero is defined as __pad on Android, so prefixed here.
```

## Source note 3, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L50)

```text
// Xenia native sockaddr_in
```

## Source note 4, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L66)

```text
// sin_zero is defined as __pad on Android, so prefixed here.
```

## Source note 5, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L87)

```text
// LIVE Voice and Data Protocol
```

## Source note 6, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L88)

```text
// https://blog.csdn.net/baozi3026/article/details/4277227
```

## Source note 7, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L89)

```text
// Format: [cbGameData][GameData(encrypted)][VoiceData(unencrypted)]
```

## Source note 8, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L119)

```text
// These values are in network byte order.
```

## Source note 9, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L127)

```text
// Queue a packet into our internal buffer.
```

## Source note 10, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L134)

```text
// Address family
```

## Source note 11, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L135)

```text
// Type (DGRAM/Stream/etc)
```

## Source note 12, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L136)

```text
// Protocol (TCP/UDP/etc)
```

## Source note 13, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L137)

```text
// Secure socket (encryption enabled)
```

## Source note 14, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xsocket.h#L139)

```text
// Explicitly bound to an IP address?
```
