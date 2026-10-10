# Rex app: core source notes

This record preserves technical and API notes moved from `include/rex/rex_app.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L45)

```text
/// Content path configuration, passed to OnConfigurePaths().
```

## Source note 2, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L46)

```text
/// All paths start with sensible defaults derived from CLI args and cvars.
```

## Source note 3, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L47)

```text
/// Subclasses may override any field before Runtime is constructed.
```

## Source note 4, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L72)

```text
/// Base class for recompiled Xbox 360 applications.
```

## Source note 5, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L74)

```text
/// OnInitialize is a thin coordinator that runs four phases in order:
```

## Source note 6, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L76)

```text
///   SetupEnvironment  -> paths, config, logging
```

## Source note 7, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L77)

```text
///   SetupPresentation -> window, graphics presentation, ImGui drawer
```

## Source note 8, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L78)

```text
///   OnFinalizePaths   -> hook for wizard-driven path resolution (sync or async)
```

## Source note 9, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L79)

```text
///   ConstructRuntime  -> Runtime, guest GPU init, XEX load, rexcrt heap
```

## Source note 10, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L80)

```text
///   LaunchModule      -> shader cache, PrepareModuleLaunch, background wait
```

## Source note 11, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L82)

```text
/// Each phase is a protected virtual; consumers override selectively without
```

## Source note 12, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L83)

```text
/// re-implementing the whole flow.
```

## Source note 13, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L85)

```text
/// Subclass skeleton:
```

## Source note 14, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L86)

```text
/// @code
```

## Source note 15, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L87)

```text
///   // src/my_app_app.h (yours to customize)
```

## Source note 16, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L88)

```text
///   class MyApp : public rex::ReXApp {
```

## Source note 17, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L89)

```text
///   public:
```

## Source note 18, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L90)

```text
///       using rex::ReXApp::ReXApp;
```

## Source note 19, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L91)

```text
///       static std::unique_ptr<rex::ui::WindowedApp> Create(
```

## Source note 20, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L92)

```text
///           rex::ui::WindowedAppContext& ctx) {
```

## Source note 21, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L93)

```text
///         return std::unique_ptr<MyApp>(new MyApp(ctx, "my_app",
```

## Source note 22, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L94)

```text
///             PPCImageConfig));
```

## Source note 23, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L96)

```text
///       // Override hooks: OnPreSetup, OnPostSetup, OnCreateDialogs,
```

## Source note 24, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L97)

```text
///       // OnConfigureFonts, OnFinalizePaths, etc.
```

## Source note 25, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L100)

```text
///   // src/main.cpp
```

## Source note 26, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L101)

```text
///   #include "generated/my_app_init.h"
```

## Source note 27, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L102)

```text
///   #include "my_app_app.h"
```

## Source note 28, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L103)

```text
///   REX_DEFINE_APP(my_app, MyApp::Create)
```

## Source note 29, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L104)

```text
/// @endcode
```

## Source note 30, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L113)

```text
// --- Virtual hooks for customization ---
```

## Source note 31, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L115)

```text
/// Called before Runtime::Setup(). Override to modify backend config.
```

## Source note 32, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L118)

```text
/// Called before Runtime::LoadXexImage(). Override to modify xex image.
```

## Source note 33, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L121)

```text
/// Called after runtime is fully initialized, before window creation.
```

## Source note 34, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L124)

```text
/// Called after ImGui drawer is created. Add custom dialogs here.
```

## Source note 35, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L127)

```text
/// Called before cleanup begins. Release custom resources here.
```

## Source note 36, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L130)

```text
/// Called after path defaults are computed, before Runtime is constructed.
```

## Source note 37, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L131)

```text
/// Override to adjust game/user/update data paths programmatically.
```

## Source note 38, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L136)

```text
/// Called after SetupPresentation returns (window and ImGui drawer are live)
```

## Source note 39, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L137)

```text
/// and before Runtime construction. Override to resolve paths from user
```

## Source note 40, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L138)

```text
/// input shown through an ImGui dialog.
```

## Source note 41, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L140)

```text
/// Return a PathConfig to continue initialization synchronously. Return
```

## Source note 42, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L141)

```text
/// std::nullopt and invoke `resume(path_config)` later (e.g. from a wizard
```

## Source note 43, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L142)

```text
/// completion handler) to continue asynchronously. `resume` must be called
```

## Source note 44, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L143)

```text
/// on the UI thread. Calling `resume` after the app has begun shutdown is
```

## Source note 45, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L144)

```text
/// a no-op.
```

## Source note 46, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L146)

```text
/// Default implementation returns `defaults` unchanged.
```

## Source note 47, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L153)

```text
/// Called from the ImGui drawer's Initialize() after the default font is
```

## Source note 48, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L154)

```text
/// registered and before the atlas is built. Override to add additional
```

## Source note 49, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L155)

```text
/// fonts via AddFontFromMemoryTTF() or similar.
```

## Source note 50, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L158)

```text
/// Called from the ImGui drawer's Initialize() after the SDK defaults have
```

## Source note 51, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L159)

```text
/// been applied. `imgui_style` is the live global ImGuiStyle: patch fields,
```

## Source note 52, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L160)

```text
/// or call ImGui::StyleColorsDark(&imgui_style) first to start from a clean
```

## Source note 53, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L161)

```text
/// slate. `ui_style` carries the per-overlay colors that ImGuiStyle cannot
```

## Source note 54, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L162)

```text
/// express (achievements, toast, console, debug, settings).
```

## Source note 55, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L168)

```text
/// Called after logging is initialized. Add log sinks here.
```

## Source note 56, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L171)

```text
/// Called once the host Gaming Runtime startup attempt is over (cvar
```

## Source note 57, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L172)

```text
/// gaming_runtime; skipped when "off"). Returning false stops the launch.
```

## Source note 58, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L173)

```text
/// The default follows the policy: "required" launches only when ready.
```

## Source note 59, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L179)

```text
/// Called after Runtime::LoadXexImage() succeeds. The XEX is loaded and
```

## Source note 60, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L180)

```text
/// mapped into guest memory but the module has not launched.
```

## Source note 61, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L181)

```text
/// Use this for data patches and recomp-specific achievement registration.
```

## Source note 62, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L184)

```text
/// Called immediately before the main guest thread is created.
```

## Source note 63, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L185)

```text
/// Everything is set up -- last chance to patch guest memory/code.
```

## Source note 64, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L188)

```text
/// Called after the main guest thread is created but before it starts
```

## Source note 65, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L189)

```text
/// executing. The thread is suspended -- attach debuggers/monitors here.
```

## Source note 66, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L192)

```text
/// Called when the main guest thread exits. The runtime is still alive.
```

## Source note 67, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L193)

```text
/// Use for cleanup that depends on runtime resources.
```

## Source note 68, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L196)

```text
/// Detached overlay mode ("bring your own renderer"). Called once from
```

## Source note 69, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L197)

```text
/// SetupPresentation when the SDK has no graphics backend
```

## Source note 70, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L198)

```text
/// (config.graphics == nullptr, typically cleared in OnPreSetup) and the app
```

## Source note 71, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L199)

```text
/// renders the guest itself. Return a unique_ptr to a ui::ImmediateDrawer
```

## Source note 72, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L200)

```text
/// subclass that creates textures and submits via your renderer. ReXApp owns
```

## Source note 73, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L201)

```text
/// the returned drawer (stored in immediate_drawer_, torn down after
```

## Source note 74, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L202)

```text
/// imgui_drawer_).
```

## Source note 75, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L204)

```text
/// Construct the drawer presenter-less. REQUIRED CONTRACT: your CreateTexture
```

## Source note 76, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L205)

```text
/// override MUST return nullptr (never crash or assert) when its GPU device
```

## Source note 77, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L206)

```text
/// is not yet available, because the SDK uploads the ImGui font atlas lazily
```

## Source note 78, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L207)

```text
/// on the first Draw and the device may only come up later (e.g. in the guest
```

## Source note 79, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L208)

```text
/// D3D device-creation hook). NOTE: ImmediateDrawer::OnEnterPresenter() /
```

## Source note 80, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L209)

```text
/// OnLeavePresenter() are NOT invoked in detached mode (the SDK never calls
```

## Source note 81, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L210)

```text
/// SetPresenter with a non-null presenter on your drawer), so perform any
```

## Source note 82, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L211)

```text
/// per-renderer GPU init lazily (on first CreateTexture/Begin), not in
```

## Source note 83, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L212)

```text
/// OnEnterPresenter. You also own present timing / vsync / letterbox in this
```

## Source note 84, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L213)

```text
/// mode.
```

## Source note 85, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L215)

```text
/// See ui::AppUIDrawContext for the per-frame draw-context handoff. Default:
```

## Source note 86, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L216)

```text
/// no overlay (SDK presenter mode; this hook is never reached).
```

## Source note 87, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L219)

```text
// --- Window event hooks (delivered on the UI thread) ---
```

## Source note 88, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L221)

```text
/// Logical (DPI-independent) client size changed.
```

## Source note 89, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L227)

```text
/// Physical pixel size changed. Use this to resize swap chains.
```

## Source note 90, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L233)

```text
/// The user asked to close the window (close button, Alt+F4). Return false
```

## Source note 91, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L234)

```text
/// to veto and close later explicitly (window()->RequestClose()) after
```

## Source note 92, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L235)

```text
/// stopping guest threads and draining renderers. Default accepts; the
```

## Source note 93, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L236)

```text
/// window then closes and the app quits via the OnClosing path.
```

## Source note 94, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L241)

```text
/// Display scale changed (window moved to a monitor with different DPI).
```

## Source note 95, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L242)

```text
/// scale is 1.0 at 96 DPI.
```

## Source note 96, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L248)

```text
/// Creates the overlay toggled by bind_achievements. Override to replace the
```

## Source note 97, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L249)

```text
/// built-in achievement UI. Returning nullptr disables the overlay.
```

## Source note 98, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L252)

```text
/// Creates the achievement notification UI. Override to replace the
```

## Source note 99, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L253)

```text
/// built-in toast renderer. Returning nullptr disables notifications.
```

## Source note 100, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L256)

```text
// --- Init phase methods (called in order from OnInitialize) ---
```

## Source note 101, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L258)

```text
/// Resolve path defaults, load config TOML, initialize logging.
```

## Source note 102, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L259)

```text
/// Populates `resolved_defaults_` with the PathConfig produced by
```

## Source note 103, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L260)

```text
/// OnConfigurePaths.
```

## Source note 104, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L264)

```text
/// Construct Runtime with the given paths, call runtime_->Setup, load the
```

## Source note 105, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L265)

```text
/// XEX image, initialize the rexcrt heap. Runs OnPostSetup at the end.
```

## Source note 106, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L268)

```text
/// Create the window, stand up graphics presentation, create the ImGui
```

## Source note 107, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L269)

```text
/// drawer, register overlay keybinds, run OnCreateDialogs.
```

## Source note 108, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L272)

```text
/// Kick off the deferred module launch: shader storage init,
```

## Source note 109, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L273)

```text
/// PrepareModuleLaunch, main thread resume, background wait.
```

## Source note 110, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L276)

```text
// --- Accessors for subclass use ---
```

## Source note 111, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L278)

```text
/// The host Gaming Runtime, or null when cvar gaming_runtime is "off".
```

## Source note 112, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L291)

```text
/// Set a callback that provides guest frame stats to the debug overlay.
```

## Source note 113, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L301)

```text
// Runs the gaming_runtime startup policy; false stops the launch.
```

## Source note 114, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L304)

```text
// Stand up the ImGui overlay stack (drawer, F3/Backtick/F4 binds, dialogs)
```

## Source note 115, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L305)

```text
// independently of how the presenter/drawer were obtained. `presenter` may be
```

## Source note 116, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L306)

```text
// null (detached mode).
```

## Source note 117, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L309)

```text
// WindowedApp overrides
```

## Source note 118, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L313)

```text
// WindowListener overrides
```

## Source note 119, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L323)

```text
// WindowInputListener overrides
```

## Source note 120, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L326)

```text
// Xbox guide (RG-GDK-041): View+Menu (Back+Start) or Home.
```

## Source note 121, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L340)

```text
// Declared before runtime_ so it outlives the guest runtime's audio, input
```

## Source note 122, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L341)

```text
// and GPU services even when OnDestroy is skipped.
```

## Source note 123, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L350)

```text
// Built-in overlays
```

## Source note 124, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L355)

```text
// self-owned on normal close
```

## Source note 125, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L356)

```text
// self-owned on normal close
```

## Source note 126, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L360)

```text
// UI-thread snapshots
```

## Source note 127, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L367)

```text
// Xbox guide. The guide deletes itself after closing, clearing guide_.
```

## Source note 128, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L379)

```text
/// The player's title update choice started the other executable; this one
```

## Source note 129, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L380)

```text
/// quits without starting the title.
```

## Source note 130, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L382)

```text
/// The guide changed the title update choice: start this title again once
```

## Source note 131, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L383)

```text
/// it has shut down, so the choice picks the executable.
```

## Source note 132, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/rex_app.h#L385)

```text
// %LOCALAPPDATA%\<name>
```
