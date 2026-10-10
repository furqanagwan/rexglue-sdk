# Graphics system: graphics source notes

This record preserves technical and API notes moved from `src/graphics/graphics_system.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L64)

```text
// Nvidia Optimus/AMD PowerXpress support.
```

## Source note 2, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L65)

```text
// These exports force the process to trigger the discrete GPU in multi-GPU
```

## Source note 3, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L66)

```text
// systems.
```

## Source note 4, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L67)

```text
// https://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
```

## Source note 5, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L68)

```text
// https://stackoverflow.com/questions/17458803/amd-equivalent-to-nvoptimusenablement
```

## Source note 6, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L72)

```text
// extern "C"
```

## Source note 7, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L91)

```text
// A prior SetupGuestGpu built a headless provider; backends like Vulkan
```

## Source note 8, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L92)

```text
// need swapchain support baked in at provider creation time.
```

## Source note 9, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L102)

```text
// Presenter creation must happen on the UI thread.
```

## Source note 10, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L106)

```text
// Offscreen path (e.g. capturing guest output without a window).
```

## Source note 11, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L123)

```text
// Headless path: no one set up presentation, so build a no-presentation
```

## Source note 12, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L124)

```text
// provider just for the command processor.
```

## Source note 13, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L130)

```text
// Create command processor. This will spin up a thread to process all
```

## Source note 14, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L131)

```text
// incoming ringbuffer packets.
```

## Source note 15, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L139)

```text
// Register GPU MMIO handlers
```

## Source note 16, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L140)

```text
// GPU registers are at 0x7FC80000-0x7FCFFFFF
```

## Source note 17, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L141)

```text
// base address
```

## Source note 18, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L143)

```text
// size (64KB)
```

## Source note 19, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L144)

```text
// context (GraphicsSystem*)
```

## Source note 20, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L148)

```text
// Guest vblank timer based on the configured guest video mode.
```

## Source note 21, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L159)

```text
// One vblank per interval, on time. Sleeping in whole milliseconds
```

## Source note 22, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L160)

```text
// woke only every 15.6 ms (the default Windows timer), so vblanks came
```

## Source note 23, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L161)

```text
// in bursts and gaps, and a title waiting for the next one often missed
```

## Source note 24, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L162)

```text
// a refresh (Quantum of Solace ran at ~36 fps with its 60 fps patch).
```

## Source note 25, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L163)

```text
// A high-resolution timer sleeps to just before the vblank and a short
```

## Source note 26, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L164)

```text
// yield loop covers the rest.
```

## Source note 27, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L213)

```text
// If there's no app context (thus the presenter is owned by the thread that
```

## Source note 28, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L214)

```text
// initialized the GraphicsSystem) or can't be queueing UI thread calls
```

## Source note 29, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L215)

```text
// anymore, shutdown anyway.
```

## Source note 30, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L248)

```text
// R500_D1MODE_V_COUNTER
```

## Source note 31, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L253)

```text
// interrupt status
```

## Source note 32, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L255)

```text
// AVIVO_D1MODE_VIEWPORT_SIZE
```

## Source note 33, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L256)

```text
// Maximum [width(0x0FFF), height(0x0FFF)].
```

## Source note 34, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L282)

```text
// AVIVO_D1GRPH_PRIMARY_SURFACE_ADDRESS
```

## Source note 35, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L315)

```text
// Pick a CPU, if needed. We're going to guess 2. Because.
```

## Source note 36, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L321)

```text
// REXGPU_INFO("Dispatching GPU interrupt at {:08X} w/ mode {} on cpu {}",
```

## Source note 37, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L322)

```text
//          interrupt_callback_, source, cpu);
```

## Source note 38, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L330)

```text
// Increment vblank counter (so the game sees us making progress).
```

## Source note 39, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L353)

```text
// Safe to run on any thread while the command processor is paused, no
```

## Source note 40, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/graphics_system.cpp#L354)

```text
// race condition.
```
