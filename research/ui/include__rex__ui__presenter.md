# Presenter: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/presenter.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L60)

```text
// The owning presenter, or null for app-driven (detached) contexts. Backend
```

## Source note 2, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L61)

```text
// (presenter-driven) contexts always have one.
```

## Source note 3, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L64)

```text
// It's assumed that the render target size will be either equal to the size
```

## Source note 4, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L65)

```text
// of the surface, or the render target will be stretched to cover the entire
```

## Source note 5, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L66)

```text
// surface (not in the corner of the surface).
```

## Source note 6, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L71)

```text
// Presenter-driven ctor for backend (D3D12/Vulkan) contexts.
```

## Source note 7, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L77)

```text
// Presenter-less ctor for app-driven (detached) overlay contexts.
```

## Source note 8, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L84)

```text
// null for app-driven (detached) contexts
```

## Source note 9, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L89)

```text
// Renderer-agnostic base for app-driven overlay rendering when the SDK runs
```

## Source note 10, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L90)

```text
// detached (config.graphics == nullptr). The app derives from this, adds its
```

## Source note 11, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L91)

```text
// own per-frame payload (e.g. the live command target and frame/submission
```

## Source note 12, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L92)

```text
// indices), constructs it each frame, hands it to ImGuiDrawer::Draw, and its
```

## Source note 13, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L93)

```text
// ImmediateDrawer pulls the payload out in Begin via static_cast<MyCtx&>(ctx).
```

## Source note 14, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L94)

```text
// Carries no presenter.
```

## Source note 15, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L105)

```text
// R8 G8 B8 X8. The last row is not required to be padded to the stride.
```

## Source note 16, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L109)

```text
// The presenter displays up to two layers of content on a host surface:
```

## Source note 17, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L110)

```text
// - Guest output image, focusing on lowering latency and maintaining stable
```

## Source note 18, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L111)

```text
//   frame pacing, with various scaling and sharpening methods and letterboxing;
```

## Source note 19, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L112)

```text
// - Xenia's internal UI (such as the profiler and Dear ImGui).
```

## Source note 20, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L114)

```text
// The guest output image may be refreshed from any thread generating it
```

## Source note 21, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L115)

```text
// (usually the GPU emulation thread), as long as there are no multiple threads
```

## Source note 22, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L116)

```text
// doing that simultaneously (since that would functionally be a race condition
```

## Source note 23, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L117)

```text
// even if refreshing is performed in a critical section).
```

## Source note 24, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L119)

```text
// The UI overlays are managed entirely by the UI thread.
```

## Source note 25, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L121)

```text
// Painting on the host surface may occur in two places:
```

## Source note 26, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L122)

```text
// - If there are no UI overlays, painting of the guest output may be performed
```

## Source note 27, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L123)

```text
//   immediately from the thread refreshing it, to bypass the OS scheduling and
```

## Source note 28, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L124)

```text
//   event handling. This is especially important on platforms where the native
```

## Source note 29, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L125)

```text
//   surface paint event has a frame rate limit (such as the display refresh
```

## Source note 30, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L126)

```text
//   rate), and the limit may differ greatly from the guest frame rate (such as
```

## Source note 31, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L127)

```text
//   presenting a 30 or 60 FPS guest to a 144 Hz host surface).
```

## Source note 32, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L128)

```text
// - If the UI overlays (owned by the UI thread) are present, painting of both
```

## Source note 33, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L129)

```text
//   the guest output (is available) and the UI is done exclusively from the
```

## Source note 34, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L130)

```text
//   platform paint event handler. The guest output without UI overlays may also
```

## Source note 35, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L131)

```text
//   be painted from the platform paint callback in certain cases, such as when
```

## Source note 36, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L132)

```text
//   an additional paint beyond the guest's frame rate may be needed (like when
```

## Source note 37, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L133)

```text
//   resizing the window), or when painting from the thread refreshing the guest
```

## Source note 38, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L134)

```text
//   output is undesirable (for instance, if it will result in waiting for host
```

## Source note 39, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L135)

```text
//   vertical sync in that thread too early if host vertical sync can't be
```

## Source note 40, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L136)

```text
//   disabled on the platform, blocking the next frame of GPU emulation).
```

## Source note 41, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L138)

```text
// The composition of the guest and the UI is done by Xenia manually, as opposed
```

## Source note 42, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L139)

```text
// to using platform functionality such as DirectComposition, in order to have
```

## Source note 43, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L140)

```text
// more predictability of GPU queue scheduling, but primarily to be able to take
```

## Source note 44, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L141)

```text
// advantage of independent host presentation where it's available, so variable
```

## Source note 45, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L142)

```text
// refresh rate may be used where possible, and latency may be significantly
```

## Source note 46, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L143)

```text
// reduced. Also, at least on some configurations (checked on Windows 11 21H2 on
```

## Source note 47, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L144)

```text
// Nvidia GeForce GTX 1070 with driver version 472.12), when in borderless
```

## Source note 48, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L145)

```text
// fullscreen, any composition causes the DXGI Present to wait for vertical sync
```

## Source note 49, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L146)

```text
// on the GPU even if the sync interval 0 is specified.
```

## Source note 50, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L148)

```text
// An intermediate image with the size requested by the guest is used for guest
```

## Source note 51, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L149)

```text
// output in all cases. Even though it adds some GPU overhead, especially in the
```

## Source note 52, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L150)

```text
// 1:1 size case, using it solves multiple issues:
```

## Source note 53, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L151)

```text
// - Presentation may be done more often than by the guest.
```

## Source note 54, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L152)

```text
// - There is clear separation between pre-scaling and mid- / post-scaling
```

## Source note 55, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L153)

```text
//   operations. The gamma ramp, for instance, may be applied before scaling,
```

## Source note 56, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L154)

```text
//   with one lookup per pixel rather than four with fetch4.
```

## Source note 57, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L155)

```text
// - A simpler compute shader may be used instead of setting up the whole
```

## Source note 58, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L156)

```text
//   graphics pipeline for copying in the GPU command processor in all cases,
```

## Source note 59, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L157)

```text
//   while Direct3D 12 does not allow UAVs for swap chain buffers.
```

## Source note 60, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L159)

```text
// The presenter limits the frame rate of the UI overlay (when possible) to a
```

## Source note 61, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L160)

```text
// value that's ideally the refresh rate of the monitor containing the window if
```

## Source note 62, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L161)

```text
// the platform's paint event doesn't have an internal limiter. However, where
```

## Source note 63, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L162)

```text
// possible, the arrival of a new guest output image will interrupt the UI tick
```

## Source note 64, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L163)

```text
// wait.
```

## Source note 65, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L165)

```text
// Because the UI overlays preclude the possibility of presenting directly from
```

## Source note 66, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L166)

```text
// the thread refreshing the guest output, and on some platforms, result in the
```

## Source note 67, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L167)

```text
// frame rate limiting of paint events manifesting itself, there must be no
```

## Source note 68, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L168)

```text
// persistent UI overlays that haven't been explicitly requested by the user.
```

## Source note 69, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L169)

```text
// However, for temporary (primarily non-modal) UI elements such as various
```

## Source note 70, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L170)

```text
// timed notifications, using the Presenter should be preferred to implementing
```

## Source note 71, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L171)

```text
// them via overlaying native windows on top of the presentation surface on
```

## Source note 72, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L172)

```text
// platforms where the concept of independent presentation exists, as multiple
```

## Source note 73, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L173)

```text
// windows will result in native composition disabling it.
```

## Source note 74, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L175)

```text
// The painting connection between the Presenter and the Surface can be managed
```

## Source note 75, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L176)

```text
// only by the UI thread. However, the thread refreshing the guest output may
```

## Source note 76, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L177)

```text
// still mark the current connection as outdated and ask the UI thread (by
```

## Source note 77, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L178)

```text
// requesting painting) to try to recover - but the guest output refresh thread
```

## Source note 78, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L179)

```text
// must not try to reconnect by itself, as methods of the Surface are available
```

## Source note 79, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L180)

```text
// only to the UI thread.
```

## Source note 80, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L183)

```text
// May be actually called on the UI thread even if statically_from_ui_thread
```

## Source note 81, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L184)

```text
// is false, such as when the guest output is refreshed by the UI thread.
```

## Source note 82, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L195)

```text
// Sets whether the source actually has no more than 8 bits of precision
```

## Source note 83, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L196)

```text
// (though the image provided by the refresher may still have a higher
```

## Source note 84, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L197)

```text
// storage precision). If never called, assuming it's false.
```

## Source note 85, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L215)

```text
// AMD FidelityFX Super Resolution upsampling, Contrast Adaptive
```

## Source note 86, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L216)

```text
// Sharpening otherwise.
```

## Source note 87, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L218)

```text
// FidelityFX FSR2 selection. Uses the runtime temporal upscaler path
```

## Source note 88, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L219)

```text
// where available; currently still experimental due to limited temporal
```

## Source note 89, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L220)

```text
// inputs in the presenter path.
```

## Source note 90, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L222)

```text
// FidelityFX FSR3 selection. Uses the runtime temporal upscaler path
```

## Source note 91, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L223)

```text
// where available; currently still experimental due to limited temporal
```

## Source note 92, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L224)

```text
// inputs in the presenter path.
```

## Source note 93, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L231)

```text
// Keep current behavior and use the guest output size as-is.
```

## Source note 94, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L240)

```text
// This value is used as a lerp factor.
```

## Source note 95, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L247)

```text
// EASU (as well as CAS) is designed for scaling by factors of up to 2x2.
```

## Source note 96, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L248)

```text
// Some sensible limit for unusual cases, when the game for some reason
```

## Source note 97, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L249)

```text
// presents a very small back buffer.
```

## Source note 98, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L250)

```text
// This is enough for 480p > 960p > 1920p > 3840p > 7680p (bigger than 8K,
```

## Source note 99, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L251)

```text
// or 4320p).
```

## Source note 100, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L255)

```text
// "Values above 2.0 won't make a visible difference."
```

## Source note 101, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L256)

```text
// https://raw.githubusercontent.com/GPUOpen-Effects/FidelityFX-FSR/master/docs/FidelityFX-FSR-Overview-Integration.pdf
```

## Source note 102, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L261)

```text
// defined(REX_HAS_FIDELITYFX_SDK)
```

## Source note 103, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L263)

```text
// In the sharpness setters, min / max with a constant as the first argument
```

## Source note 104, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L264)

```text
// also drops NaNs.
```

## Source note 105, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L288)

```text
// In stops.
```

## Source note 106, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L300)

```text
// defined(REX_HAS_FIDELITYFX_SDK)
```

## Source note 107, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L302)

```text
// Very tiny effect, but highly noticeable, for instance, on the sky in the
```

## Source note 108, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L303)

```text
// 4D5307E6 main menu (prominently in Custom Games, especially with FSR -
```

## Source note 109, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L304)

```text
// banding around the clouds can be clearly seen without dithering with 8bpc
```

## Source note 110, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L305)

```text
// final host output).
```

## Source note 111, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L310)

```text
// Tools, rather than the emulator itself, must not allow overscan cutoff
```

## Source note 112, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L311)

```text
// and must use the kBilinear effect as the image must be as close to the
```

## Source note 113, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L312)

```text
// original front buffer as possible.
```

## Source note 114, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L330)

```text
// For calling from the Window for the Presenter attached to it.
```

## Source note 115, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L331)

```text
// May be called from the destructor of the presenter through the window.
```

## Source note 116, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L336)

```text
// For calling from the platform paint event handler. Refreshes the surface
```

## Source note 117, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L337)

```text
// connection if needed, and also paints if possible and if needed (if there
```

## Source note 118, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L338)

```text
// are no UI overlays, and the guest output is presented directly from the
```

## Source note 119, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L339)

```text
// thread refreshing it, the paint may be skipped unless there has been an
```

## Source note 120, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L340)

```text
// explicit request previously or force_paint is true). If painting happens,
```

## Source note 121, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L341)

```text
// both the guest output and the UI overlays (if any are active) are drawn.
```

## Source note 122, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L342)

```text
// The background / letterbox of the painted context will be black - windows
```

## Source note 123, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L343)

```text
// should preferably have a black background before a Presenter is attached to
```

## Source note 124, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L344)

```text
// them too.
```

## Source note 125, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L347)

```text
// Pass 0 as width or height to disable guest output until the next refresh
```

## Source note 126, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L348)

```text
// with an actual size. The display aspect ratio may be specified like 16:9 or
```

## Source note 127, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L349)

```text
// like 1280:720, both are accepted, for simplicity, the guest display size
```

## Source note 128, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L350)

```text
// may just be passed. The callback will receive a backend-specific context,
```

## Source note 129, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L351)

```text
// and will not be called in case of an error such as the wrong size, or if
```

## Source note 130, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L352)

```text
// guest output is disabled. Returns whether the callback was called and it
```

## Source note 131, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L353)

```text
// returned true. The callback must submit all updating work to the host GPU
```

## Source note 132, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L354)

```text
// before successfully returning, and also signal all the GPU synchronization
```

## Source note 133, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L355)

```text
// primitives required by the GuestOutputRefreshContext implementation.
```

## Source note 134, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L359)

```text
// The implementation must be callable from any thread, including from
```

## Source note 135, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L360)

```text
// multiple at the same time, and it should acquire the latest guest output
```

## Source note 136, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L361)

```text
// image via ConsumeGuestOutput.
```

## Source note 137, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L366)

```text
// For simplicity, may be called repeatedly even if no changes have been made.
```

## Source note 138, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L372)

```text
// Requests (re)painting with the UI if there's UI to draw.
```

## Source note 139, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L379)

```text
// Refused for internal reasons or a host API side failure, but still may
```

## Source note 140, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L380)

```text
// try to present without resetting the graphics provider in the future.
```

## Source note 141, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L388)

```text
// Redrawing not necessary, nothing changed. Must not be returned for a new
```

## Source note 142, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L389)

```text
// connection (when was previously disconnected from the surface).
```

## Source note 143, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L399)

```text
// At least any value being 0 here means the guest output is disabled for
```

## Source note 144, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L400)

```text
// this frame.
```

## Source note 145, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L403)

```text
// Guest display aspect ratio numerator and denominator (both 16:9 and
```

## Source note 146, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L404)

```text
// 1280:720 kinds of values are accepted).
```

## Source note 147, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L444)

```text
// Dithering is never performed in intermediate passes because it may be
```

## Source note 148, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L445)

```text
// interpreted as features by the subsequent passes.
```

## Source note 149, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L454)

```text
// The result of any other effect can be stretched with bilinear
```

## Source note 150, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L455)

```text
// filtering to the final resolution.
```

## Source note 151, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L472)

```text
// The longest path is kFsrMaxUpscalingPassesMax + optionally RCAS +
```

## Source note 152, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L473)

```text
// optionally bilinear, when upscaling by more than
```

## Source note 153, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L474)

```text
// 2^kFsrMaxUpscalingPassesMax along any direction.
```

## Source note 154, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L475)

```text
// Non-FSR paths are either only bilinear, only CAS, or (when upscaling by
```

## Source note 155, line 476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L476)

```text
// more than 2 along any direction) CAS followed by bilinear.
```

## Source note 156, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L480)

```text
// Bilinear-only path: at most 1 effect.
```

## Source note 157, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L485)

```text
// Letterbox on up to 4 sides.
```

## Source note 158, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L497)

```text
// If 0, don't display the guest output.
```

## Source note 159, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L502)

```text
// Offset of the rectangle for final drawing to the host window with
```

## Source note 160, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L503)

```text
// letterboxing.
```

## Source note 161, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L507)

```text
// If there is guest output (effect_count is not 0), contains the letterbox
```

## Source note 162, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L508)

```text
// rectangles around the guest output.
```

## Source note 163, line 551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L551)

```text
// CasSetup const1.x.
```

## Source note 164, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L568)

```text
// Input size / output size.
```

## Source note 165, line 585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L585)

```text
// No output offset because the EASU pass is always done to an intermediate
```

## Source note 166, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L586)

```text
// framebuffer.
```

## Source note 167, line 606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L606)

```text
// FsrRcasCon const0.x.
```

## Source note 168, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L616)

```text
// defined(REX_HAS_FIDELITYFX_SDK)
```

## Source note 169, line 621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L621)

```text
// Must be called by the implementation's initialization, before the presenter
```

## Source note 170, line 622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L622)

```text
// is used for anything.
```

## Source note 171, line 625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L625)

```text
// ConnectOrReconnect and Disconnect are callable only by the UI thread and
```

## Source note 172, line 626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L626)

```text
// only when it has access to painting (PaintMode is not
```

## Source note 173, line 627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L627)

```text
// kGuestOutputThreadImmediately).
```

## Source note 174, line 628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L628)

```text
// Called only for a non-zero-area surface potentially supporting painting via
```

## Source note 175, line 629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L629)

```text
// the presenter. In case of a failure, internally no resources referencing
```

## Source note 176, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L630)

```text
// the surface must be held by the implementation anymore - the implementation
```

## Source note 177, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L631)

```text
// must be left in the same state as after
```

## Source note 178, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L632)

```text
// DisconnectPaintingFromSurfaceFromUIThreadImpl. If the call is successful,
```

## Source note 179, line 633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L633)

```text
// the implementation must write to is_vsync_implicit_out whether the
```

## Source note 180, line 634

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L634)

```text
// connection will now have vertical sync forced by the host window system,
```

## Source note 181, line 635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L635)

```text
// which may cause undesirable waits on the CPU when beginning or ending
```

## Source note 182, line 636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L636)

```text
// frames.
```

## Source note 183, line 640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L640)

```text
// Releases resources referencing the surface in the implementation if they
```

## Source note 184, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L641)

```text
// are held by it. Call through DisconnectPaintingFromSurfaceFromUIThread to
```

## Source note 185, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L642)

```text
// ensure the implementation is only called while the connection is active.
```

## Source note 186, line 645

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L645)

```text
// The returned lock interlocks multiple consumers (but not the producer and
```

## Source note 187, line 646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L646)

```text
// the consumer) and must be held while accessing implementation-specific
```

## Source note 188, line 647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L647)

```text
// objects that depend on the image or its index in the mailbox (unless there
```

## Source note 189, line 648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L648)

```text
// are other locking mechanisms involved for the resources, such as reference
```

## Source note 190, line 649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L649)

```text
// counting for the guest output images, which doesn't have to be atomic
```

## Source note 191, line 650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L650)

```text
// though for the reason described later in this paragraph, or assumptions
```

## Source note 192, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L651)

```text
// like of main target painting being possible only in at most one thread at
```

## Source note 193, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L652)

```text
// once). While this lock is held, the currently acquired image index can't be
```

## Source note 194, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L653)

```text
// changed (by other consumers advancing the acquired image index to the new
```

## Source note 195, line 654

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L654)

```text
// ready image index), so the image with the index given by this function
```

## Source note 196, line 655

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L655)

```text
// can't be released and be made writable or given to a different consumer
```

## Source note 197, line 656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L656)

```text
// (thus it's owned exclusively by the consumer who has called this function).
```

## Source note 198, line 657

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L657)

```text
// The properties are returned by copy rather than returning a pointer to them
```

## Source note 199, line 658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L658)

```text
// or asking the consumer to pull them for the current mailbox index, so there
```

## Source note 200, line 659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L659)

```text
// are less things to take into consideration while leaving the guest output
```

## Source note 201, line 660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L660)

```text
// consumer critical section earlier (as if a pointer was returned, the data
```

## Source note 202, line 661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L661)

```text
// behind it could be overwritten at any time after leaving the consumer
```

## Source note 203, line 662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L662)

```text
// critical section) if the implementation has its own synchronization
```

## Source note 204, line 663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L663)

```text
// mechanisms that allow for doing so as described earlier. Returns UINT32_MAX
```

## Source note 205, line 664

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L664)

```text
// as the mailbox index if the image is inactive (if it's active, it has
```

## Source note 206, line 665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L665)

```text
// proper properties though).
```

## Source note 207, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L669)

```text
// The properties are passed explicitly, not taken from the current acquired
```

## Source note 208, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L670)

```text
// image, so it can be called for a copy of the acquired image's properties
```

## Source note 209, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L671)

```text
// outside the consumer lock if the implementation has its own synchronization
```

## Source note 210, line 672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L672)

```text
// (like reference counting for the guest output images) that makes it
```

## Source note 211, line 673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L673)

```text
// possible to leave the consumer critical section earlier. Also, the guest
```

## Source note 212, line 674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L674)

```text
// output paint configuration is passed explicitly too so calling this
```

## Source note 213, line 675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L675)

```text
// function multiple times is safer.
```

## Source note 214, line 680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L680)

```text
// is_8bpc_out_ref is where to write whether the source actually has no more
```

## Source note 215, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L681)

```text
// than 8 bits of precision per channel (though the image provided by the
```

## Source note 216, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L682)

```text
// refresher may still have a higher storage precision) - if not written, it
```

## Source note 217, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L683)

```text
// will be assumed to be false.
```

## Source note 218, line 688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L688)

```text
// For guest output capturing (for debugging use thus - shouldn't be adding
```

## Source note 219, line 689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L689)

```text
// any noise like dithering that's not present in the original image),
```

## Source note 220, line 690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L690)

```text
// converting a 10bpc RGB pixel to 8bpc that can be stored in common image
```

## Source note 221, line 691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L691)

```text
// formats.
```

## Source note 222, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L693)

```text
// Conversion almost according to the Direct3D 10+ rules (unorm > float >
```

## Source note 223, line 694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L694)

```text
// unorm), but with one multiplication rather than separate division and
```

## Source note 224, line 695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L695)

```text
// multiplication - the results are the same for unorm10 to unorm8.
```

## Source note 225, line 708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L708)

```text
// Paints and presents the guest output if available (or just solid black
```

## Source note 226, line 709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L709)

```text
// color), and if requested, the UI on top of it.
```

## Source note 227, line 711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L711)

```text
// May be called from the non-UI thread, but only to paint the guest output
```

## Source note 228, line 712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L712)

```text
// (no UI drawing, with execute_ui_drawers disabled).
```

## Source note 229, line 714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L714)

```text
// Call via PaintAndPresent.
```

## Source note 230, line 717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L717)

```text
// For calling from the painting implementations if requested.
```

## Source note 231, line 722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L722)

```text
// Don't paint at all.
```

## Source note 232, line 723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L723)

```text
// Painting lifecycle is accessible only by the UI thread.
```

## Source note 233, line 724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L724)

```text
// window_->RequestPaint() must not be called in this mode at all regardless
```

## Source note 234, line 725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L725)

```text
// of whether the Window object exists because the Window object in this
```

## Source note 235, line 726

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L726)

```text
// case may correspond to a window without a paintable Surface (in a closed
```

## Source note 236, line 727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L727)

```text
// state, or in the middle of a surface change), and non-UI threads (such as
```

## Source note 237, line 728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L728)

```text
// the guest output thread) may result in a race condition internally inside
```

## Source note 238, line 729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L729)

```text
// Window::RequestPaint during the access to the Window's state, such as the
```

## Source note 239, line 730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L730)

```text
// availability of the Surface that can handle the paint (therefore, if
```

## Source note 240, line 731

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L731)

```text
// there's no Surface, this is the only valid mode).
```

## Source note 241, line 733

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L733)

```text
// Guest output refreshing notifies the `window_`, which must be valid and
```

## Source note 242, line 734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L734)

```text
// safe to call RequestPaint for, that painting should be done in the UI
```

## Source note 243, line 735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L735)

```text
// thread (including the UI if needed). Painting is possible, and painting
```

## Source note 244, line 736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L736)

```text
// lifecycle is accessible, only by the UI thread.
```

## Source note 245, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L738)

```text
// Paint immediately in the guest output thread for lower latency. The
```

## Source note 246, line 739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L739)

```text
// `window_`, however, may be notified that the surface painting connection
```

## Source note 247, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L740)

```text
// has become outdated (via RequestPaint, as in this case the UI thread will
```

## Source note 248, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L741)

```text
// need to repaint as sooner as possible after reconnecting anyway), and
```

## Source note 249, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L742)

```text
// change the surface connection state accordingly (only to
```

## Source note 250, line 743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L743)

```text
// kConnectedOutdated).
```

## Source note 251, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L744)

```text
// Painting is possible only by the guest output thread, lifecycle
```

## Source note 252, line 745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L745)

```text
// management cannot be done from the UI thread until it takes over.
```

## Source note 253, line 750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L750)

```text
// No surface at all, or couldn't connect with the current state of the
```

## Source note 254, line 751

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L751)

```text
// surface (such as because the surface was zero-sized because the window
```

## Source note 255, line 752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L752)

```text
// was minimized, for example). Or, the connection has become outdated, and
```

## Source note 256, line 753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L753)

```text
// the attempt to reconnect at kRetryConnectingSoon has failed. Try to
```

## Source note 257, line 754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L754)

```text
// reconnect if anything changes in the state of the surface, such as its
```

## Source note 258, line 755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L755)

```text
// size.
```

## Source note 259, line 757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L757)

```text
// Can't connect to the current existing surface (the surface has been lost
```

## Source note 260, line 758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L758)

```text
// or it's completely incompatible). No point in retrying connecting until
```

## Source note 261, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L759)

```text
// the surface is replaced.
```

## Source note 262, line 761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L761)

```text
// Everything is fine, can paint. The connection might have become
```

## Source note 263, line 762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L762)

```text
// suboptimal though, and haven't tried refreshing yet, but still usable for
```

## Source note 264, line 763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L763)

```text
// painting nonetheless.
```

## Source note 265, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L765)

```text
// The implementation still holds resources associated with the connection,
```

## Source note 266, line 766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L766)

```text
// but presentation has reported that it has become outdated, try
```

## Source note 267, line 767

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L767)

```text
// reconnecting as soon as possible (at the next paint attempt, requesting
```

## Source note 268, line 768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L768)

```text
// it if needed). This is the only state that the guest output thread may
```

## Source note 269, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L769)

```text
// transition the connection to (from kConnectedPaintable only) if it has
```

## Source note 270, line 770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L770)

```text
// access to painting (the paint mode is kGuestOutputThreadImmediately).
```

## Source note 271, line 789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L789)

```text
// Based on conditions like whether UI needs to be drawn and whether vertical
```

## Source note 272, line 790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L790)

```text
// sync is implicit - see the implementation for the requirements.
```

## Source note 273, line 791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L791)

```text
// is_paintable is an explicit parameter because this function may be called
```

## Source note 274, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L792)

```text
// in two scenarios:
```

## Source note 275, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L793)

```text
// - After connection updates - painting connection is owned by the UI thread,
```

## Source note 276, line 794

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L794)

```text
//   so the actual state can be obtained and passed here so kNone can be
```

## Source note 277, line 795

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L795)

```text
//   returned.
```

## Source note 278, line 796

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L796)

```text
// - When merely toggling something local to the UI thread - only to toggle
```

## Source note 279, line 797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L797)

```text
//   between the two threads, but not to switch from or to kNone (make sure
```

## Source note 280, line 798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L798)

```text
//   it's not kNone before calling), pass `true` in this case.
```

## Source note 281, line 801

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L801)

```text
// Callable only by the UI thread and only when it has access to painting
```

## Source note 282, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L802)

```text
// (PaintMode is not kGuestOutputThreadImmediately).
```

## Source note 283, line 803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L803)

```text
// This can be called to a surface after having not been connected to any (in
```

## Source note 284, line 804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L804)

```text
// this case, surface_paint_connection_state_ must be
```

## Source note 285, line 805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L805)

```text
// kUnconnectedRetryAtStateChange, not kUnconnectedNoUsableSurface, otherwise
```

## Source note 286, line 806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L806)

```text
// the call will be dropped), or to handle surface state changes such as
```

## Source note 287, line 807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L807)

```text
// resizing. However, this must not be called to change directly from one
```

## Source note 288, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L808)

```text
// surface to another - need to disconnect prior to that, because the
```

## Source note 289, line 809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L809)

```text
// implementation may assume that the surface is still the same, and may try
```

## Source note 290, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L810)

```text
// to, for instance, resize the buffers for the existing surface.
```

## Source note 291, line 813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L813)

```text
// Callable only by the UI thread and only when it has access to painting
```

## Source note 292, line 814

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L814)

```text
// (PaintMode is not kGuestOutputThreadImmediately).
```

## Source note 293, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L815)

```text
// See DisconnectPaintingFromSurfaceFromUIThreadImpl for more information.
```

## Source note 294, line 818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L818)

```text
// Can be called from any thread if an existing window_ safe to RequestPaint
```

## Source note 295, line 819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L819)

```text
// (not closed) is available in it, so doesn't check the surface painting
```

## Source note 296, line 820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L820)

```text
// connection state. Returns whether the window_->RequestPaint() call has been
```

## Source note 297, line 821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L821)

```text
// made.
```

## Source note 298, line 824

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L824)

```text
// Platform-specific function refreshing the monitor the current window
```

## Source note 299, line 825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L825)

```text
// surface is on, through the Surface or its Window. A reference to the
```

## Source note 300, line 826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L826)

```text
// monitor is held only when a Surface is available, so it's automatically
```

## Source note 301, line 827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L827)

```text
// dropped when the Window loses its Surface when it's being closed (but the
```

## Source note 302, line 828

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L828)

```text
// Window object keeps being attached to the Presenter), for instance.
```

## Source note 303, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L830)

```text
// Platform-specific function returning whether the surface the presenter is
```

## Source note 304, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L831)

```text
// currently attached it is actually visible on any monitor. UI thread
```

## Source note 305, line 832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L832)

```text
// painting may be dropped if this returns false - need to request painting if
```

## Source note 306, line 833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L833)

```text
// the surface appears on a monitor again. May be using the state cached at
```

## Source note 307, line 834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L834)

```text
// window / surface state changes, not the actual state from the platform.
```

## Source note 308, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L837)

```text
// Calls PaintAndPresentImpl and does post-paint checks that are safe to do on
```

## Source note 309, line 838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L838)

```text
// both the UI thread and the guest output thread. See the information about
```

## Source note 310, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L839)

```text
// PaintAndPresentImpl for details.
```

## Source note 311, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L840)

```text
// A kPresentedSuboptimal result is returned as is, but the connection may or
```

## Source note 312, line 841

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L841)

```text
// may not be made outdated if that happens - though if it's
```

## Source note 313, line 842

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L842)

```text
// kPresentedSuboptimal rather than kNotPresentedConnectionOutdated, the image
```

## Source note 314, line 843

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L843)

```text
// has been successfully sent to the OS presentation at least.
```

## Source note 315, line 849

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L849)

```text
// UI drawing should be done, and painting needs to be possible (coarsely
```

## Source note 316, line 850

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L850)

```text
// checking because the actual connection state, including outdated, may be
```

## Source note 317, line 851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L851)

```text
// currently unavailable from the UI thread).
```

## Source note 318, line 852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L852)

```text
// There's no need to limit the frame rate manually if there is vertical
```

## Source note 319, line 853

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L853)

```text
// sync in the presentation already as that might result in inconsistent
```

## Source note 320, line 854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L854)

```text
// frame pacing and potentially skipped vertical sync intervals.
```

## Source note 321, line 860

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L860)

```text
// May be called from any thread.
```

## Source note 322, line 863

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L863)

```text
// Must be called only in the end of entry points - reinitialization of the
```

## Source note 323, line 864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L864)

```text
// presenter may be done by the handler if it was called from the UI thread
```

## Source note 324, line 865

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L865)

```text
// (even if the UI thread argument is false - such as when the guest output is
```

## Source note 325, line 866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L866)

```text
// refreshed on the UI thread).
```

## Source note 326, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L869)

```text
// May be accessed by the guest output thread if the paint mode is not kNone,
```

## Source note 327, line 870

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L870)

```text
// to request painting (for kUIThreadOnRequest) or reconnection (for
```

## Source note 328, line 871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L871)

```text
// kGuestOutputThreadImmediately) in the UI thread. Set the paint mode to
```

## Source note 329, line 872

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L872)

```text
// kNone before modifying (that naturally has to be done anyway by
```

## Source note 330, line 873

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L873)

```text
// disconnecting painting).
```

## Source note 331, line 876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L876)

```text
// The surface of the `window_` the presenter is currently attached to.
```

## Source note 332, line 879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L879)

```text
// Mutex protecting paint_mode_ (and, in the guest output thread, objects
```

## Source note 333, line 880

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L880)

```text
// related to painting themselves).
```

## Source note 334, line 882

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L882)

```text
// The UI thread (as the mode is modifiable only by it) can use it as
```

## Source note 335, line 883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L883)

```text
// "barriers", like:
```

## Source note 336, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L884)

```text
// 1) If needed, lock and disable guest output thread access to painting.
```

## Source note 337, line 885

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L885)

```text
// 2) Interact with the painting connection.
```

## Source note 338, line 886

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L886)

```text
// 3) If needed, lock and re-enable guest output thread access to the
```

## Source note 339, line 887

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L887)

```text
//    painting.
```

## Source note 340, line 889

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L889)

```text
// On the other hand, the guest output thread _must_ hold it all the time it's
```

## Source note 341, line 890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L890)

```text
// painting, to ensure the mode stays the same while it's painting.
```

## Source note 342, line 892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L892)

```text
// UI thread: writable, guest output thread: read-only.
```

## Source note 343, line 895

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L895)

```text
// These fields can be accessed _exclusively_ by either the UI thread or the
```

## Source note 344, line 896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L896)

```text
// guest output thread, depending on paint_mode_.
```

## Source note 345, line 897

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L897)

```text
// If it's kGuestOutputThreadImmediately, they can be accessed _only_ by the
```

## Source note 346, line 898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L898)

```text
// guest output thread (though the UI thread can still read, but not modify,
```

## Source note 347, line 899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L899)

```text
// fields that are writable by the UI thread and readadable by both).
```

## Source note 348, line 900

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L900)

```text
// Otherwise, they can be accessed _only_ by the UI thread.
```

## Source note 349, line 901

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L901)

```text
// The connection state may be changed from the guest output thread, but only
```

## Source note 350, line 902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L902)

```text
// from kConnectedPaintable to kConnectedOutdated.
```

## Source note 351, line 905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L905)

```text
// If the surface connection was optimal at the last paint attempt, but now
```

## Source note 352, line 906

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L906)

```text
// has become suboptimal, need to try to reconnect. But only in this case - if
```

## Source note 353, line 907

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L907)

```text
// the connection has been suboptimal from the very beginning don't try to
```

## Source note 354, line 908

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L908)

```text
// reconnect every frame.
```

## Source note 355, line 911

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L911)

```text
// Modifiable only by the UI thread (therefore can be accessed by the UI
```

## Source note 356, line 912

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L912)

```text
// thread regardless of the paint mode) while (re)connecting painting to the
```

## Source note 357, line 913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L913)

```text
// surface.
```

## Source note 358, line 915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L915)

```text
// Modifiable only by the UI thread, can be read by the thread that's
```

## Source note 359, line 916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L916)

```text
// painting.
```

## Source note 360, line 920

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L920)

```text
// Can be set by both the UI thread and the guest output thread before doing
```

## Source note 361, line 921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L921)

```text
// window_->RequestPaint() - whether an extra painting (preceded by
```

## Source note 362, line 922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L922)

```text
// reconnection if needed, and painting) was requested, primarily after some
```

## Source note 363, line 923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L923)

```text
// state change that may effect the surface painting connection, resulting in
```

## Source note 364, line 924

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L924)

```text
// the need to refresh it as soon as possible.
```

## Source note 365, line 926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L926)

```text
// Relaxed memory order is enough, everything that may influence painting is
```

## Source note 366, line 927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L927)

```text
// either local to the UI thread or protected with barriers elsewhere.
```

## Source note 367, line 929

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L929)

```text
// There's no need to bother about resetting this variable when losing
```

## Source note 368, line 930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L930)

```text
// connection as the next successful reconnection should be followed by a
```

## Source note 369, line 931

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L931)

```text
// repaint request anyway.
```

## Source note 370, line 935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L935)

```text
// UI thread: writable, guest output thread: read-only.
```

## Source note 371, line 938

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L938)

```text
// Single-producer-multiple-consumers (lock-free SPSC + consumer lock) mailbox
```

## Source note 372, line 939

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L939)

```text
// for presenting of the most up-to-date guest output image without long
```

## Source note 373, line 940

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L940)

```text
// interlocking between guest output refreshing and painting.
```

## Source note 374, line 942

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L942)

```text
// The "acquired" image (in bits 0:1) is the one that is currently being read,
```

## Source note 375, line 943

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L943)

```text
// or was last read, by a consumer of the guest output. The index of it can be
```

## Source note 376, line 944

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L944)

```text
// modified only by the consumer and stays the same while it's processing the
```

## Source note 377, line 945

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L945)

```text
// image.
```

## Source note 378, line 946

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L946)

```text
// The "ready" image (in bits 2:3) is the most up-to-date image that the
```

## Source note 379, line 947

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L947)

```text
// refresher has completely written, and a consumer may acquire it. It may be
```

## Source note 380, line 948

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L948)

```text
// == acquired if there has been no refresh since the last acquisition.
```

## Source note 381, line 949

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L949)

```text
// These two images can be accessed by painting in parallel, in an unordered
```

## Source note 382, line 950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L950)

```text
// way, with guest output refreshing.
```

## Source note 383, line 952

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L952)

```text
// The "writable" image is different than both "acquired" and "ready" and is
```

## Source note 384, line 953

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L953)

```text
// accessible only by the guest output refreshing - it's the image that the
```

## Source note 385, line 954

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L954)

```text
// refresher may write to.
```

## Source note 386, line 956

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L956)

```text
// The guest output images may be consumed by two operations - painting, and
```

## Source note 387, line 957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L957)

```text
// capturing to a CPU-side buffer. These two usually never happen in parallel
```

## Source note 388, line 958

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L958)

```text
// in reality though, as they're usually not even needed both at once in the
```

## Source note 389, line 959

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L959)

```text
// same app within Xenia, so there's no need to create any
```

## Source note 390, line 960

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L960)

```text
// complex lock-free synchronization between the two, but still, the situation
```

## Source note 391, line 961

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L961)

```text
// when multiple consumers want the guest output image at the same is
```

## Source note 392, line 962

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L962)

```text
// perfectly valid (unlike for producers, because even with a producer lock
```

## Source note 393, line 963

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L963)

```text
// that would still be a race condition since the two refreshes themselves
```

## Source note 394, line 964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L964)

```text
// will be done in an undefined order) - so, a sufficient synchronization
```

## Source note 395, line 965

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L965)

```text
// mechanism is used to make sure multiple consumers can acquire images
```

## Source note 396, line 966

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L966)

```text
// without interfering with each other.
```

## Source note 397, line 967

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L967)

```text
// While this is held, paint_mode_mutex_ must not be locked (the lock order is
```

## Source note 398, line 968

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L968)

```text
// the reverse when painting in the guest output thread - painting is done
```

## Source note 399, line 969

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L969)

```text
// with paint_mode_mutex_ held in this case, and guest output consumption
```

## Source note 400, line 970

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L970)

```text
// happens as part of painting.
```

## Source note 401, line 974

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L974)

```text
// Accessible only by refreshing, whether the last refresh contained an image
```

## Source note 402, line 975

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L975)

```text
// rather than being blank.
```

## Source note 403, line 978

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L978)

```text
// Ordered by the Z order, and then by the time of addition.
```

## Source note 404, line 979

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L979)

```text
// Note: All the iteration logic involving this Z ordering must be the same as
```

## Source note 405, line 980

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L980)

```text
// in input handling (in the input listeners in the Window), but in reverse.
```

## Source note 406, line 988

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L988)

```text
// Whether currently running the logic of PaintFromUIThread, so certain
```

## Source note 407, line 989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L989)

```text
// actions (such as changing the paint mode, requesting a redraw) must be
```

## Source note 408, line 990

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L990)

```text
// deferred and be handled by the tail of PaintFromUIThread for consistency
```

## Source note 409, line 991

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L991)

```text
// with what PaintFromUIThread does internally.
```

## Source note 410, line 996

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L996)

```text
// Platform-specific, but implementation-agnostic parts, primarily for
```

## Source note 411, line 997

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L997)

```text
// limiting of the frame rate of the UI to avoid drawing the UI at extreme
```

## Source note 412, line 998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L998)

```text
// frame rates wasting the CPU and the GPU resources and starving everything
```

## Source note 413, line 999

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L999)

```text
// else. The waits performed here must be interruptible by guest output
```

## Source note 414, line 1000

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1000)

```text
// presentation requests to prevent adding arbitrary amounts of latency to it.
```

## Source note 415, line 1001

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1001)

```text
// On Android and GTK, this is not needed, the frame rate of draw events is
```

## Source note 416, line 1002

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1002)

```text
// limited to the display refresh rate internally.
```

## Source note 417, line 1011

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1011)

```text
// Accessible only from the UI thread, to avoid updating monitor-dependent
```

## Source note 418, line 1012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1012)

```text
// information such as the DXGI output if the monitor hasn't actually been
```

## Source note 419, line 1013

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1013)

```text
// changed in the current state change (such as window positioning changes).
```

## Source note 420, line 1016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1016)

```text
// Requiring the lowest version of DXGI for IDXGIOutput::WaitForVBlank, which
```

## Source note 421, line 1017

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1017)

```text
// is available even on Windows Vista, but for IDXGIFactory1::IsCurrent,
```

## Source note 422, line 1018

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1018)

```text
// DXGI 1.1 is needed (available starting from Windows 7; also mixing DXGI 1.0
```

## Source note 423, line 1019

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1019)

```text
// and 1.1+ in the Direct3D 12 code is not supported, see CreateDXGIFactory on
```

## Source note 424, line 1020

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1020)

```text
// MSDN). The factory is created when it's needed, and may be released and
```

## Source note 425, line 1021

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1021)

```text
// recreated when it's not current anymore and that becomes relevant.
```

## Source note 426, line 1024

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1024)

```text
// Accessible only from the UI thread, though the value is taken from the
```

## Source note 427, line 1025

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1025)

```text
// tick-mutex-protected variable.
```

## Source note 428, line 1030

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1030)

```text
// If output is null or shutdown is true, the signal may not be sent, either
```

## Source note 429, line 1031

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1031)

```text
// don't limit the frame rate in this case (an exceptional situation, such as
```

## Source note 430, line 1032

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1032)

```text
// a failure to find the output in DXGI), or don't draw at all if the window
```

## Source note 431, line 1033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1033)

```text
// was removed from a connected monitor.
```

## Source note 432, line 1035

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1035)

```text
// To avoid allocating processing resources to the thread when nothing needs
```

## Source note 433, line 1036

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1036)

```text
// the ticks (not drawing the UI), the thread waits for vertical blanking
```

## Source note 434, line 1037

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1037)

```text
// intervals only when the UI drawing ticks are needed, and sleeping waiting
```

## Source note 435, line 1038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1038)

```text
// for the control condition variable signals otherwise. Modifiable only from
```

## Source note 436, line 1039

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1039)

```text
// the UI thread, so readable by it without locking the mutex.
```

## Source note 437, line 1041

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1041)

```text
// The shutdown flag is modifiable only from the UI thread.
```

## Source note 438, line 1046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/presenter.h#L1046)

```text
// May be signaled by guest output refreshing.
```
