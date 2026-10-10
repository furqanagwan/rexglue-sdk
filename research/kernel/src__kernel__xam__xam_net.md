# Xam net: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xam/xam_net.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L32)

```text
// NOTE: must be included last as it expects windows.h to already be included.
```

## Source note 3, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L42)

```text
// https://github.com/G91/TitanOffLine/blob/1e692d9bb9dfac386d08045ccdadf4ae3227bb5e/xkelib/xam/xamNet.h
```

## Source note 4, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L52)

```text
// https://github.com/pmrowla/hl2sdk-csgo/blob/master/common/xbox/xboxstubs.h
```

## Source note 5, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L54)

```text
// FYI: IN_ADDR should be in network-byte order.
```

## Source note 6, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L55)

```text
// IP address (zero if not static/DHCP)
```

## Source note 7, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L56)

```text
// Online IP address (zero if not online)
```

## Source note 8, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L57)

```text
// Online port
```

## Source note 9, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L58)

```text
// Ethernet MAC address
```

## Source note 10, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L59)

```text
// Online identification
```

## Source note 11, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L114)

```text
// must be named to avoid GCC error
```

## Source note 12, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L126)

```text
// Maybe? Depends on type.
```

## Source note 13, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L145)

```text
// Maybe? Depends on type.
```

## Source note 14, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L155)

```text
// https://github.com/joolswills/mameox/blob/master/MAMEoX/Sources/xbox_Network.cpp#L136
```

## Source note 15, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L182)

```text
/*
  if (!xam->xnet()) {
    auto xnet = new XNet(REX_KERNEL_STATE());
    xnet->Initialize();

    xam->set_xnet(xnet);
  }
  */
```

## Source note 16, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L196)

```text
// auto xnet = xam->xnet();
```

## Source note 17, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L197)

```text
// xam->set_xnet(nullptr);
```

## Source note 18, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L220)

```text
// For now, constant values.
```

## Source note 19, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L221)

```text
// This makes replicating things easier.
```

## Source note 20, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L242)

```text
// Some games (5841099F) want this value round-tripped - they'll compare if
```

## Source note 21, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L243)

```text
// it changes and bugcheck if it does.
```

## Source note 22, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L249)

```text
/*
  auto xam = REX_KERNEL_STATE()->GetKernelModule<XamModule>("xam.xex");
  if (!xam->xnet()) {
    auto xnet = new XNet(REX_KERNEL_STATE());
    xnet->Initialize();

    xam->set_xnet(xnet);
  }
  */
```

## Source note 23, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L263)

```text
// This does nothing. Xenia needs WSA running.
```

## Source note 24, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L277)

```text
// auto evt = REX_KERNEL_OBJECTS()->LookupObject<XEvent>(
```

## Source note 25, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L278)

```text
//    overlapped_ptr->event_handle);
```

## Source note 26, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L280)

```text
// if (evt) {
```

## Source note 27, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L281)

```text
//  //evt->Set(0, false);
```

## Source note 28, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L285)

```text
// we're not going to be receiving packets any time soon
```

## Source note 29, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L286)

```text
// return error so we don't wait on that - Cancerous
```

## Source note 30, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L290)

```text
// If the socket is a VDP socket, buffer 0 is the game data length, and buffer 1
```

## Source note 31, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L291)

```text
// is the unencrypted game data.
```

## Source note 32, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L306)

```text
// Our sockets implementation doesn't support multiple buffers, so we need
```

## Source note 33, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L307)

```text
// to combine the buffers the game has given us!
```

## Source note 34, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L387)

```text
// Address acquisition is not yet complete
```

## Source note 35, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L389)

```text
// XNet is uninitialized or no debugger found
```

## Source note 36, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L391)

```text
// Host has ethernet address (no IP address)
```

## Source note 37, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L393)

```text
// Host has statically assigned IP address
```

## Source note 38, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L395)

```text
// Host has DHCP assigned IP address
```

## Source note 39, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L397)

```text
// Host has PPPoE assigned IP address
```

## Source note 40, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L399)

```text
// Host has one or more gateways configured
```

## Source note 41, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L401)

```text
// Host has one or more DNS servers configured
```

## Source note 42, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L403)

```text
// Host is currently connected to online service
```

## Source note 43, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L405)

```text
// Network configuration requires troubleshooting
```

## Source note 44, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L410)

```text
// Just return a loopback address atm.
```

## Source note 45, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L425)

```text
// XNET_GET_XNADDR_NONE causes caller to gracefully return.
```

## Source note 46, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L430)

```text
// Tell the caller we're not signed in to live (non-zero ret)
```

## Source note 47, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L439)

```text
// This converts a XNet address to an IN_ADDR. The IN_ADDR is used for
```

## Source note 48, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L440)

```text
// subsequent socket calls (like a handle to a XNet address)
```

## Source note 49, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L446)

```text
// Does the reverse of the above.
```

## Source note 50, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L453)

```text
// https://www.google.com/patents/WO2008112448A1?cl=en
```

## Source note 51, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L454)

```text
// Reserves a port for use by system link
```

## Source note 52, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L459)

```text
// https://github.com/ILOVEPIE/Cxbx-Reloaded/blob/master/src/CxbxKrnl/EmuXOnline.h#L39
```

## Source note 53, line 476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L476)

```text
// non-zero = error
```

## Source note 54, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L496)

```text
// Set pqos as some games will try accessing it despite non-successful result
```

## Source note 55, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L530)

```text
// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-inet_addr#return-value
```

## Source note 56, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L531)

```text
// Based on console research it seems like x360 uses old version of inet_addr
```

## Source note 57, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L532)

```text
// In case of empty string it return 0 instead of -1
```

## Source note 58, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_net.cpp#L716)

```text
// Convert from Xenia -> native
```
