# Graphics: system source notes

This record preserves technical and API notes moved from `include/rex/system/interfaces/graphics.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L19)

```text
// Forward declarations
```

## Source note 2, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L38)

```text
// Build the provider + presenter. Safe to call standalone (without a
```

## Source note 3, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L39)

```text
// Runtime) to stand up a window + ImGui for an installer. Idempotent.
```

## Source note 4, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L40)

```text
// Must be called before SetupGuestGpu if presentation is desired: some
```

## Source note 5, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L41)

```text
// backends (e.g. Vulkan) bake swapchain support into the provider, and
```

## Source note 6, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L42)

```text
// a headless provider from SetupGuestGpu cannot be upgraded in place.
```

## Source note 7, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L45)

```text
// Wire the GPU into the guest address space: MMIO, command processor,
```

## Source note 8, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L46)

```text
// vsync worker. Needs the Runtime's dispatcher + kernel state. If
```

## Source note 9, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L47)

```text
// SetupPresentation has not been called, a headless provider is built.
```

## Source note 10, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L53)

```text
// --- Optional capabilities, default no-op -------------------------------
```

## Source note 11, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L55)

```text
// Host presentation objects for ReXApp's overlay wiring; custom systems may
```

## Source note 12, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L56)

```text
// leave these null.
```

## Source note 13, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L60)

```text
// Guest GPU services reached from the xboxkrnl Vd* exports.
```

## Source note 14, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L74)

```text
// Persistent shader/pipeline storage under the cache root. Default: none.
```

## Source note 15, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/interfaces/graphics.h#L82)

```text
// One-shot convenience for callers that don't care about the split.
```
