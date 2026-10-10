# Host ui: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/277).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/ui/imgui_drawer.cpp:166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/ui/imgui_drawer.cpp#L166)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): disable imgui.ini saving for now,
  // imgui assumes paths are char* so we can't throw a good path at it on
  // Windows.
```

## Note 2: src/ui/imgui_drawer.cpp:501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/ui/imgui_drawer.cpp#L501)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Accept the Unicode character.
```

## Note 3: src/ui/imgui_drawer.cpp:633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/ui/imgui_drawer.cpp#L633)

Disposition: retired reminder. The upstream xenia-ui-window-demo is not an SDK application.

```text
// FIXME(Triang3l): Doesn't work in xenia-ui-window-demo.
```

## Note 4: src/ui/presenter.cpp:854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/ui/presenter.cpp#L854)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Configuration variables racing with per-game config
  // loading.
```

## Note 5: src/ui/window.cpp:155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/ui/window.cpp#L155)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Changing the Z order of an existing listener while
    // already executing the listeners may cause listeners to be called twice if
    // the Z order is lowered from one that has already been processed to one
    // below the current one. Because nested listener calls are supported, a
    // single last call index can't be associated with a listener to skip it if
    // calling twice for the same event (a "not equal to" comparison of the call
    // indices will result in the skipping being cancelled in the outer loop if
    // an inner one is done, a "greater than" comparison will cause the inner
    // loop to effectively terminate all outer ones).
```

## Note 6: include/rex/ui/window.h:363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/ui/window.h#L363)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): A resize function, primarily for snapping externally to
  // 1280x720, 1920x1080, and other 1:1 resolutions. It will need to resize the
  // window (to a desired logical size - the actual physical size is entirely
  // the feedback of the implementation) in the normal state, and possibly also
  // un-maximize (and possibly un-fullscreen) it (but this choice will possibly
  // need to be exposed to the caller). Because it's currently not needed, it's
  // not implemented to avoid platform-specific complexities regarding
  // maximization, DPI, etc.
```
