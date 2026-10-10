# D3d12 presenter: ui source notes

This record preserves technical and API notes moved from `src/ui/d3d12/d3d12_presenter.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L38)

```text
// Generated with `xb buildshaders`.
```

## Source note 2, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L55)

```text
// Await completion of the usage of everything before destroying anything.
```

## Source note 3, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L56)

```text
// From most likely the latest to most likely the earliest to be signaled, so
```

## Source note 4, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L57)

```text
// just one sleep will likely be needed.
```

## Source note 5, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L177)

```text
// The presenter path doesn't currently provide accurate temporal inputs,
```

## Source note 6, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L178)

```text
// so run in reset mode each frame to avoid history artifacts.
```

## Source note 7, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L214)

```text
// Incremented the reference count of the guest output resource - safe to
```

## Source note 8, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L215)

```text
// leave the consumer critical section now.
```

## Source note 9, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L232)

```text
// Create zeroed not to leak data in the row padding.
```

## Source note 10, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L288)

```text
// Make sure that if any work is submitted, any `return` will cause an await
```

## Source note 11, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L289)

```text
// before releasing the command allocator / list and the resource the RAII
```

## Source note 12, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L290)

```text
// way in the destruction of the submission tracker - so create after the
```

## Source note 13, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L291)

```text
// objects referenced in the submission - but don't submit anything if
```

## Source note 14, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L292)

```text
// failed to initialize the fence.
```

## Source note 15, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L331)

```text
// Unmapping will be done implicitly when the resource goes out of scope and
```

## Source note 16, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L332)

```text
// gets destroyed.
```

## Source note 17, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L347)

```text
// ConnectOrReconnectPaintingToSurfaceFromUIThread may be called only for the
```

## Source note 18, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L348)

```text
// surface of the current swap chain or when the old swap chain has already
```

## Source note 19, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L349)

```text
// been destroyed, if the surface is the same, try resizing.
```

## Source note 20, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L357)

```text
// Using the current swap_chain_allows_tearing_ value that's consistent with
```

## Source note 21, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L358)

```text
// the creation of the swap chain because ResizeBuffers can't toggle the
```

## Source note 22, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L359)

```text
// tearing flag.
```

## Source note 23, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L382)

```text
// Failed to resize, retry creating from scratch.
```

## Source note 24, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L388)

```text
// Create a new swap chain.
```

## Source note 25, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L399)

```text
// DXGI_SCALING_STRETCH may cause the content to "shake" while resizing,
```

## Source note 26, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L400)

```text
// with relayout done for the guest output twice visually rather than once,
```

## Source note 27, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L401)

```text
// and the UI becoming stretched and then jumping to normal. If it's
```

## Source note 28, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L402)

```text
// possible to cover the entire surface without stretching, don't stretch.
```

## Source note 29, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L403)

```text
// After resizing, the presenter repaints as soon as possible anyway, so
```

## Source note 30, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L412)

```text
// Allow tearing in borderless fullscreen to support variable refresh
```

## Source note 31, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L413)

```text
// rate.
```

## Source note 32, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L428)

```text
// Disable automatic Alt+Enter handling - DXGI fullscreen doesn't
```

## Source note 33, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L429)

```text
// support ALLOW_TEARING, and the window implementation provides
```

## Source note 34, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L430)

```text
// borderless fullscreen anyway with better state tracking.
```

## Source note 35, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L447)

```text
// From now on, in case of any failure, DestroySwapChain must be called
```

## Source note 36, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L448)

```text
// before returning.
```

## Source note 37, line 466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L466)

```text
// Create the RTV descriptors.
```

## Source note 38, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L501)

```text
// Main target painting has its own reference to the textures for reading
```

## Source note 39, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L502)

```text
// in its own submission tracker timeline, safe to release here.
```

## Source note 40, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L533)

```text
// Even if the refresher has returned false, it still might have submitted
```

## Source note 41, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L534)

```text
// some commands referencing the resource. It's better to put an excessive
```

## Source note 42, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L535)

```text
// signal and wait slightly longer, for nothing important, while shutting down
```

## Source note 43, line 536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L536)

```text
// than to destroy the resource while it's still in use.
```

## Source note 44, line 558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L558)

```text
// Begin the command list with the command allocator not currently potentially
```

## Source note 45, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L559)

```text
// used on the GPU.
```

## Source note 46, line 574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L574)

```text
// Obtain the RTV heap and the back buffer.
```

## Source note 47, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L586)

```text
// Draw the guest output.
```

## Source note 48, line 598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L598)

```text
// Incremented the reference count of the guest output resource - safe to
```

## Source note 49, line 599

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L599)

```text
// leave the consumer critical section now as everything here either will be
```

## Source note 50, line 600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L600)

```text
// using the new reference or is exclusively owned by main target painting
```

## Source note 51, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L601)

```text
// (and multiple threads can't paint the main target at the same time).
```

## Source note 52, line 610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L610)

```text
// Check if all guest output paint effects are supported by the
```

## Source note 53, line 611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L611)

```text
// implementation.
```

## Source note 54, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L630)

```text
// Store the main target reference to the guest output texture so it's not
```

## Source note 55, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L631)

```text
// destroyed while it's still potentially in use by main target painting
```

## Source note 56, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L632)

```text
// queued on the GPU.
```

## Source note 57, line 635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L635)

```text
// Try to find the existing reference to the same texture, or an already
```

## Source note 58, line 636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L636)

```text
// released (or a taken, but never actually used) slot.
```

## Source note 59, line 650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L650)

```text
// New texture - store the reference and create the descriptors.
```

## Source note 60, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L652)

```text
// Replace the earliest used reference.
```

## Source note 61, line 662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L662)

```text
// Await the completion of the usage of the old guest output
```

## Source note 62, line 663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L663)

```text
// resource and its SRV descriptors.
```

## Source note 63, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L670)

```text
// The actual submission index will be set if the texture is actually
```

## Source note 64, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L671)

```text
// used, not dropped due to some error.
```

## Source note 65, line 674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L674)

```text
// Create the SRV descriptor of the new texture.
```

## Source note 66, line 691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L691)

```text
// Make sure intermediate textures of the needed size are available, and
```

## Source note 67, line 692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L692)

```text
// unneeded intermediate textures are destroyed.
```

## Source note 68, line 708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L708)

```text
// Need to replace immediately as a new texture with the requested
```

## Source note 69, line 709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L709)

```text
// size is needed.
```

## Source note 70, line 715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L715)

```text
// Resource.
```

## Source note 71, line 736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L736)

```text
// Don't display the guest output, and don't try to create more
```

## Source note 72, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L737)

```text
// intermediate textures (only destroy them).
```

## Source note 73, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L742)

```text
// SRV.
```

## Source note 74, line 757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L757)

```text
// RTV.
```

## Source note 75, line 768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L768)

```text
// Was previously needed, but not anymore - destroy when possible.
```

## Source note 76, line 788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L788)

```text
// This effect loop must not be aborted so the states of the resources
```

## Source note 77, line 789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L789)

```text
// involved are consistent.
```

## Source note 78, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L839)

```text
// If this is not the first effect, the transition has been done at
```

## Source note 79, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L840)

```text
// the end of the previous effect in a single command.
```

## Source note 80, line 938

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L938)

```text
// +Y is -V.
```

## Source note 81, line 999

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L999)

```text
// Clear the letterbox around the guest output if the guest output
```

## Source note 82, line 1000

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1000)

```text
// doesn't cover the entire back buffer.
```

## Source note 83, line 1028

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1028)

```text
// Transition the newly written intermediate image to SRV for use as
```

## Source note 84, line 1029

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1029)

```text
// the source in the next effect.
```

## Source note 85, line 1040

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1040)

```text
// Merge the current destination > next source transition with the
```

## Source note 86, line 1041

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1041)

```text
// acquisition of the destination for the next effect.
```

## Source note 87, line 1043

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1043)

```text
// The next effect won't be the last - transition the next
```

## Source note 88, line 1044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1044)

```text
// intermediate destination to its write state.
```

## Source note 89, line 1059

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1059)

```text
// The next effect draws to the back buffer - merge into one
```

## Source note 90, line 1060

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1060)

```text
// ResourceBarrier command.
```

## Source note 91, line 1082

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1082)

```text
// Release main target guest output texture references that aren't needed
```

## Source note 92, line 1083

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1083)

```text
// anymore (this is done after various potential guest-output-related main
```

## Source note 93, line 1084

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1084)

```text
// target submission tracker waits so the completed submission value is the
```

## Source note 94, line 1085

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1085)

```text
// most actual).
```

## Source note 95, line 1099

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1099)

```text
// If no guest output has been drawn, the transitioned of the back buffer to
```

## Source note 96, line 1100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1100)

```text
// RTV hasn't been done yet, and it's needed to clear it, and optionally to
```

## Source note 97, line 1101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1101)

```text
// draw the UI.
```

## Source note 98, line 1120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1120)

```text
// Draw the UI.
```

## Source note 99, line 1132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1132)

```text
// End drawing to the back buffer.
```

## Source note 100, line 1142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1142)

```text
// Execute and present.
```

## Source note 101, line 1150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1150)

```text
// Present as soon as possible, without waiting for vsync (the host refresh
```

## Source note 102, line 1151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1151)

```text
// rate may be something like 144 Hz, which is not a multiple of the common
```

## Source note 103, line 1152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1152)

```text
// 30 Hz or 60 Hz guest refresh rate), and allowing dropping outdated queued
```

## Source note 104, line 1153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1153)

```text
// frames for lower latency. Also, if possible, allowing tearing to use
```

## Source note 105, line 1154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1154)

```text
// variable refresh rate in borderless fullscreen (note that if DXGI
```

## Source note 106, line 1155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1155)

```text
// fullscreen is ever used in, the allow tearing flag must not be passed in
```

## Source note 107, line 1156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1156)

```text
// fullscreen, but DXGI fullscreen is largely unneeded with the flip
```

## Source note 108, line 1157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1157)

```text
// presentation model used in Direct3D 12).
```

## Source note 109, line 1161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1161)

```text
// Even if presentation has failed, work might have been enqueued anyway
```

## Source note 110, line 1162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1162)

```text
// internally before the failure according to Jesse Natalie from the DirectX
```

## Source note 111, line 1163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1163)

```text
// Discord server.
```

## Source note 112, line 1176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1176)

```text
// Check if DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING is supported.
```

## Source note 113, line 1190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1190)

```text
// Initialize static guest output painting objects.
```

## Source note 114, line 1192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1192)

```text
// Guest output painting root signatures.
```

## Source note 115, line 1193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1193)

```text
// One (texture) for bilinear, two (texture and constants) for AMD FidelityFX
```

## Source note 116, line 1194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1194)

```text
// CAS and FSR.
```

## Source note 117, line 1197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1197)

```text
// Source texture.
```

## Source note 118, line 1214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1214)

```text
// Rectangle.
```

## Source note 119, line 1226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1226)

```text
// Pixel shader constants.
```

## Source note 120, line 1235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1235)

```text
// Bilinear sampler.
```

## Source note 121, line 1257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1257)

```text
// Bilinear filtering (needs the sampler).
```

## Source note 122, line 1273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1273)

```text
// EASU (needs the sampler).
```

## Source note 123, line 1288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1288)

```text
// RCAS and CAS don't need the sampler.
```

## Source note 124, line 1290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1290)

```text
// RCAS.
```

## Source note 125, line 1305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1305)

```text
// CAS, sharpening only.
```

## Source note 126, line 1320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1320)

```text
// CAS, resampling.
```

## Source note 127, line 1335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1335)

```text
// defined(REX_HAS_FIDELITYFX_SDK)
```

## Source note 128, line 1337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1337)

```text
// Guest output painting pipelines.
```

## Source note 129, line 1409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1409)

```text
// Not supported by this implementation.
```

## Source note 130, line 1442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1442)

```text
// Initialize connection-independent parts of the painting context.
```

## Source note 131, line 1446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1446)

```text
// Paint submission trackers.
```

## Source note 132, line 1452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1452)

```text
// Paint command allocators and command list.
```

## Source note 133, line 1471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1471)

```text
// Command lists are created in an open state.
```

## Source note 134, line 1474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1474)

```text
// RTV descriptor heap.
```

## Source note 135, line 1489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1489)

```text
// CBV/SRV/UAV descriptor heap.
```

## Source note 136, line 1515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_presenter.cpp#L1515)

```text
// namespace rex::ui::d3d12
```
