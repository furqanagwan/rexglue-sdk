# Imgui drawer: ui source notes

This record preserves technical and API notes moved from `src/ui/imgui_drawer.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L30)

```text
// File: 'ProggyTiny.ttf' (35656 bytes)
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L31)

```text
// Exported using binary_to_compressed_c.cpp
```

## Source note 3, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L120)

```text
// Check if already added.
```

## Source note 4, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L125)

```text
// First dialog added. !IsDrawingDialogs() is also checked because in a
```

## Source note 5, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L126)

```text
// situation of removing the only dialog, then adding a dialog, from within
```

## Source note 6, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L127)

```text
// a dialog's Draw function, re-registering the ImGuiDrawer may result in
```

## Source note 7, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L128)

```text
// ImGui being drawn multiple times in the current frame.
```

## Source note 8, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L144)

```text
// Actualize the next dialog index after the erasure from the vector.
```

## Source note 9, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L155)

```text
// Setup ImGui internal state.
```

## Source note 10, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L156)

```text
// This will give us state we can swap to the ImGui globals when in use.
```

## Source note 11, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L167)

```text
// Draws honour each command's VtxOffset, so a draw list may pass 65536
```

## Source note 12, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L168)

```text
// vertices with 16-bit indices (the Xbox guide's gradients do).
```

## Source note 13, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L171)

```text
// Setup the font glyphs.
```

## Source note 14, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L177)

```text
// Basic Latin + Latin Supplement
```

## Source note 15, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L183)

```text
// https://github.com/Koruri/kibitaki looks really good, but is 1.5MiB.
```

## Source note 16, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L270)

```text
// Function keys
```

## Source note 17, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L292)

```text
// OEM keys
```

## Source note 18, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L367)

```text
// Eagerly upload the font atlas only when a presenter is attached (SDK mode).
```

## Source note 19, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L368)

```text
// In detached mode (presenter_ == nullptr) the app's renderer device may not
```

## Source note 20, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L369)

```text
// exist yet at SetupPresentation, so defer to the idempotent Draw-time
```

## Source note 21, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L370)

```text
// SetupFontTexture().
```

## Source note 22, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L377)

```text
// Drawing is initiated by the presenter (SDK mode), or by the app in detached
```

## Source note 23, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L378)

```text
// mode (config.graphics == nullptr), where there is no presenter.
```

## Source note 24, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L380)

```text
// A drawer target has been attached, but an immediate drawer hasn't yet.
```

## Source note 25, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L384)

```text
// In detached mode the app's immediate drawer (and the renderer device
```

## Source note 26, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L385)

```text
// backing it) may only become usable on the first frame, after the guest
```

## Source note 27, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L386)

```text
// creates its D3D device. Upload the font atlas lazily and idempotently;
```

## Source note 28, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L387)

```text
// SetupFontTexture early-returns once font_texture_ is set.
```

## Source note 29, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L402)

```text
// For safety as Dear ImGui doesn't allow non-positive DeltaTime. Using the
```

## Source note 30, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L403)

```text
// same default value as in the official samples.
```

## Source note 31, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L432)

```text
// Detaching is deferred if the last dialog is removed during drawing, perform
```

## Source note 32, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L433)

```text
// it now if needed.
```

## Source note 33, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L437)

```text
// Repaint (and handle input) continuously if still active. In detached mode
```

## Source note 34, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L438)

```text
// there is no presenter; the app drives repaint via its own present loop.
```

## Source note 35, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L520)

```text
// Ignored.
```

## Source note 36, line 552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L552)

```text
// Ignored.
```

## Source note 37, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L577)

```text
// The latest pointer needs to be controlling the ImGui mouse.
```

## Source note 38, line 579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L579)

```text
// Switching from the mouse to touch input.
```

## Source note 39, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L595)

```text
// Make sure that after a touch, the ImGui mouse isn't hovering over
```

## Source note 40, line 596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L596)

```text
// anything.
```

## Source note 41, line 657

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L657)

```text
// Nothing needs to be done regarding CaptureMouse and ReleaseMouse - all
```

## Source note 42, line 658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L658)

```text
// buttons as well as mouse capture have been released when switching to
```

## Source note 43, line 659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L659)

```text
// touch input, the mouse is never captured during touch input, and now
```

## Source note 44, line 660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L660)

```text
// resetting to no buttons down (therefore not capturing).
```

## Source note 45, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L681)

```text
// Window text input is changed on the UI thread only, and in detached mode Draw is not.
```

## Source note 46, line 687

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L687)

```text
// IsDrawingDialogs() is also checked because in a situation of removing the
```

## Source note 47, line 688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L688)

```text
// only dialog, then adding a dialog, from within a dialog's Draw function,
```

## Source note 48, line 689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L689)

```text
// re-registering the ImGuiDrawer may result in ImGui being drawn multiple
```

## Source note 49, line 690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L690)

```text
// times in the current frame.
```

## Source note 50, line 694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L694)

```text
// Detaching stops Draw, so there is no later frame to notice that the
```

## Source note 51, line 695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L695)

```text
// removed dialog took a focused InputText with it.
```

## Source note 52, line 701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L701)

```text
// Clear all input since no input will be received anymore, and when the
```

## Source note 53, line 702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L702)

```text
// drawer becomes active again, it'd have an outdated input state otherwise
```

## Source note 54, line 703

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L703)

```text
// which will be persistent until new events actualize individual input
```

## Source note 55, line 704

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/imgui_drawer.cpp#L704)

```text
// properties.
```
