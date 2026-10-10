# D3d12 presenter: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/d3d12/d3d12_presenter.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L54)

```text
// The format used internally by Windows composition.
```

## Source note 2, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L57)

```text
// The callback must use the main direct queue of the provider.
```

## Source note 3, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L63)

```text
// kGuestOutputFormat, supports UAV. The initial state in the callback is
```

## Source note 4, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L64)

```text
// kGuestOutputInternalState, and the callback must also transition it back
```

## Source note 5, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L65)

```text
// to kGuestOutputInternalState before finishing.
```

## Source note 6, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L178)

```text
// Swap chain buffers - updated when creating the swap chain
```

## Source note 7, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L179)

```text
// (connection-specific).
```

## Source note 8, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L182)

```text
// Intermediate textures - the last usage is
```

## Source note 9, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L183)

```text
// guest_output_intermediate_texture_paint_last_usage_.
```

## Source note 10, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L190)

```text
// Guest output textures - indices are the same as in
```

## Source note 11, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L191)

```text
// guest_output_resource_paint_refs, and the last usage is tied to them.
```

## Source note 12, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L194)

```text
// Intermediate textures - the last usage is
```

## Source note 13, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L195)

```text
// guest_output_intermediate_texture_paint_last_usage_.
```

## Source note 14, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L202)

```text
// Presentation engine usage.
```

## Source note 15, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L204)

```text
// Paint (render target) usage. While the presentation fence is signaled
```

## Source note 16, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L205)

```text
// on the same queue, and presentation happens after painting, awaiting
```

## Source note 17, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L206)

```text
// anyway for safety just to make less assumptions in the architecture.
```

## Source note 18, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L212)

```text
// Connection-independent.
```

## Source note 19, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L214)

```text
// Signaled before presenting.
```

## Source note 20, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L216)

```text
// Signaled after presenting.
```

## Source note 21, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L223)

```text
// Descriptor heaps for views of the current resources related to the guest
```

## Source note 22, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L224)

```text
// output and to painting, updated either during painting or during
```

## Source note 23, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L225)

```text
// connection lifetime management if outdated after awaiting usage
```

## Source note 24, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L226)

```text
// completion.
```

## Source note 25, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L227)

```text
// RTV heap.
```

## Source note 26, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L229)

```text
// Shader-visible CBV/SRV/UAV heap.
```

## Source note 27, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L232)

```text
// Refreshed and cleaned up during guest output painting. The first is the
```

## Source note 28, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L233)

```text
// paint submission index in which the guest output texture (and its
```

## Source note 29, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L234)

```text
// descriptors) was last used, the second is the reference to the texture,
```

## Source note 30, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L235)

```text
// which may be null. The indices are not mailbox indices here, rather, if
```

## Source note 31, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L236)

```text
// the reference is not in this array yet, the most outdated reference, if
```

## Source note 32, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L237)

```text
// needed, is replaced with the new one, awaiting the completion of the last
```

## Source note 33, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L238)

```text
// paint usage.
```

## Source note 34, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L242)

```text
// Current intermediate textures for guest output painting, refreshed when
```

## Source note 35, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L243)

```text
// painting guest output. While not in use, they are in
```

## Source note 36, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L244)

```text
// D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE.
```

## Source note 37, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L249)

```text
// Connection-specific.
```

## Source note 38, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L278)

```text
// Whether DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING is supported by DXGI (depends in
```

## Source note 39, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L279)

```text
// particular on the Windows 10 version and hardware support), primarily for
```

## Source note 40, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L280)

```text
// variable refresh rate support.
```

## Source note 41, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L283)

```text
// Static objects for guest output presentation, used only when painting the
```

## Source note 42, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L284)

```text
// main target (can be destroyed only after awaiting main target usage
```

## Source note 43, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L285)

```text
// completion).
```

## Source note 44, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L293)

```text
// The first is the refresher submission tracker fence value at which the
```

## Source note 45, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L294)

```text
// guest output texture was last refreshed, the second is the reference to the
```

## Source note 46, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L295)

```text
// texture, which may be null. The indices are the mailbox indices.
```

## Source note 47, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L298)

```text
// The guest output resources are protected by two submission trackers - the
```

## Source note 48, line 299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L299)

```text
// refresher ones (for writing to them via the guest_output_resources_
```

## Source note 49, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L300)

```text
// references) and the paint one (for presenting it via the
```

## Source note 50, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L301)

```text
// paint_context_.guest_output_resource_paint_refs references taken from
```

## Source note 51, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L302)

```text
// guest_output_resources_).
```

## Source note 52, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L305)

```text
// UI submission tracker with the submission index that can be given to UI
```

## Source note 53, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L306)

```text
// drawers (accessible from the UI thread only, at any time).
```

## Source note 54, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L309)

```text
// Accessible only by painting and by surface connection lifetime management
```

## Source note 55, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L310)

```text
// (ConnectOrReconnectPaintingToSurfaceFromUIThread,
```

## Source note 56, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L311)

```text
// DisconnectPaintingFromSurfaceFromUIThreadImpl) by the thread doing it, as
```

## Source note 57, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L312)

```text
// well as by presenter initialization and shutdown.
```

## Source note 58, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/d3d12/d3d12_presenter.h#L325)

```text
// namespace rex::ui::d3d12
```
