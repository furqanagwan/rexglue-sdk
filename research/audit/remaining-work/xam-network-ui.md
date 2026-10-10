# Xam network ui: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/270).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/kernel/xam/xam_net.cpp:199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_net.cpp#L199)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Shut down and delete.
  // delete xnet;
```

## Note 2: src/kernel/xam/xam_net.cpp:231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_net.cpp#L231)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): abstraction layer needed.
```

## Note 3: src/kernel/xam/xam_net.cpp:328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_net.cpp#L328)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Instantly complete overlapped
```

## Note 4: src/kernel/xam/xam_net.cpp:421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_net.cpp#L421)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): A proper mac address.
  // RakNet's 360 version appears to depend on abEnet to create "random" 64-bit
  // numbers. A zero value will cause RakPeer::Startup to fail. This causes
  // 58411436 to crash on startup.
  // The 360-specific code is scrubbed from the RakNet repo, but there's still
  // traces of what it's doing which match the game code.
  // https://github.com/facebookarchive/RakNet/blob/master/Source/RakPeer.cpp#L382
  // https://github.com/facebookarchive/RakNet/blob/master/Source/RakPeer.cpp#L4527
  // https://github.com/facebookarchive/RakNet/blob/master/Source/RakPeer.cpp#L4467
  // "Mac address is a poor solution because you can't have multiple connections
  // from the same system"
```

## Note 5: src/kernel/xam/xam_net.cpp:464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_net.cpp#L464)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME: Arguments may not be correct.
```

## Note 6: src/kernel/xam/xam_net.cpp:490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_net.cpp#L490)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): actually implement this
```

## Note 7: src/kernel/xam/xam_net.cpp:583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_net.cpp#L583)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Absolutely delete this object. It is no longer valid after calling
  // closesocket.
```

## Note 8: src/kernel/xam/xam_net.cpp:633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_net.cpp#L633)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO
```

## Note 9: src/kernel/xam/xam_net.cpp:819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_net.cpp#L819)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): modify ret to be what's actually copied to the guest fd_sets?
```

## Note 10: src/kernel/xam/xam_net.cpp:862

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_net.cpp#L862)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Better way of getting the error code
```

## Note 11: src/kernel/xam/xam_nui.cpp:46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_nui.cpp#L46)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): Implement imgui stuff
  // const Runtime* emulator = REX_KERNEL_STATE()->emulator();
  // ui::Window* display_window = emulator->display_window();
  // ui::ImGuiDrawer* imgui_drawer = emulator->imgui_drawer();
  // if (display_window && imgui_drawer) {
  //  rex::thread::Fence fence;
  //  if (display_window->app_context().CallInUIThreadSynchronous([&]() {
  //        rex::ui::ImGuiDialog::ShowMessageBox(
  //            imgui_drawer, "NUI Troubleshooter",
  //            "The game has indicated there is a problem with NUI (Kinect).")
  //            ->Then(&fence);
  //      })) {
  //    ++xam_dialogs_shown_;
  //    fence.Wait();
  //    --xam_dialogs_shown_;
  //  }
  //}
```

## Note 12: src/kernel/xam/xam_ui.cpp:43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_ui.cpp#L43)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): This is all one giant WIP that seems to work better than the
// previous immediate synchronous completion of dialogs.
//
// The deferred execution of dialog handling is done in such a way that there is
// a pre-, peri- (completion), and post- callback steps.
//
// pre();
// result = completion();
// CompleteOverlapped(result);
// post();
//
// There are games that are batshit insane enough to wait for the X_OVERLAPPED
// to be completed (ie not X_ERROR_PENDING) before creating a listener to
// receive a notification, which is why we have distinct pre- and post- steps.
//
// We deliberately delay the XN_SYS_UI = false notification to give games time
// to create a listener (if they're insane enough do this).
```

## Note 13: src/kernel/xam/xam_ui.cpp:189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_ui.cpp#L189)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): do something with extended_error/length?
```

## Note 14: src/kernel/xam/xam_ui.cpp:236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_ui.cpp#L236)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): do something with extended_error/length?
```

## Note 15: src/kernel/xam/xam_ui.cpp:318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_ui.cpp#L318)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): default title based on flags?
```

## Note 16: src/kernel/xam/xam_ui.cpp:342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_ui.cpp#L342)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): setup icon states.
```

## Note 17: src/kernel/xam/xam_ui.cpp:710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_ui.cpp#L710)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): cleaner exit.
```

## Note 18: src/kernel/xam/xam_ui.cpp:723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_ui.cpp#L723)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): implement properly
```

## Note 19: src/system/xsocket.cpp:79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xsocket.cpp#L79)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: WSAGetLastError()
```

## Note 20: src/system/xsocket.cpp:94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xsocket.cpp#L94)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Get last error
```

## Note 21: src/system/xsocket.cpp:165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xsocket.cpp#L165)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(DrChat): Enable when I commit XNet
  /*
  {
    std::lock_guard<std::mutex> lock(incoming_packet_mutex_);
    if (incoming_packets_.size()) {
      packet* pkt = (packet*)incoming_packets_.front();
      int data_len = pkt->data_len;
      std::memcpy(buf, pkt->data, std::min((uint32_t)pkt->data_len, buf_len));

      from->sin_family = 2;
      from->sin_addr = pkt->src_ip;
      from->sin_port = pkt->src_port;

      incoming_packets_.pop();
      uint8_t* pkt_ui8 = (uint8_t*)pkt;
      delete[] pkt_ui8;

      return data_len;
    }
  }
  */
```

## Note 22: src/system/xsocket.cpp:213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xsocket.cpp#L213)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(DrChat): Enable when I commit XNet.
  /*
  auto xam = kernel_state()->GetKernelModule<xam::XamModule>("xam.xex");
  auto xnet = xam->xnet();
  if (xnet) {
    xnet->SendPacket(this, to, buf, buf_len);
  }
  */
```

## Note 23: src/system/xsocket.cpp:244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xsocket.cpp#L244)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Limit on number of incoming packets?
```
