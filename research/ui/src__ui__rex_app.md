# Rex app: ui source notes

This record preserves technical and API notes moved from `src/ui/rex_app.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L106)

```text
// Physical controllers only; this reader ends with its host dialog.
```

## Source note 2, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L151)

```text
// The height in pixels of the display the window is on, in its current
```

## Source note 3, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L152)

```text
// mode (not scaled by the desktop's DPI setting); 0 when unknown.
```

## Source note 4, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L167)

```text
// The draw resolution scale that fills the display: titles draw at 720p,
```

## Source note 5, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L168)

```text
// so 3 for 2160p, 2 for 1440p and 1080p, 1 below.
```

## Source note 6, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L173)

```text
// Shows the title as the console would: its name from the XDBF string table,
```

## Source note 7, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L174)

```text
// in the user's language when it has one, and its dashboard icon. Leaves the
```

## Source note 8, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L175)

```text
// window as it is when the executable has no XDBF resource.
```

## Source note 9, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L176)

```text
// The title's own XDBF name, in the user's language when it has one.
```

## Source note 10, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L209)

```text
// --- ReXApp ---
```

## Source note 11, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L236)

```text
// The console's own popup (xam notify.xur) from the system update, with the
```

## Source note 12, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L237)

```text
// SDK toast when there is none.
```

## Source note 13, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L261)

```text
// This process's arguments after argv[0], without the title update ones: a
```

## Source note 14, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L262)

```text
// restart must take the saved choice, and only a hand-over is marked.
```

## Source note 15, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L297)

```text
// Starts `executable` with this process's arguments. A hand-over is marked so
```

## Source note 16, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L298)

```text
// the new one never hands back.
```

## Source note 17, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L337)

```text
// Async: consumer will invoke resume when ready. OnInitialize returns
```

## Source note 18, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L338)

```text
// true so the event loop keeps pumping (wizard dialogs render).
```

## Source note 19, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L396)

```text
// This reader is for the host menu, with no synthetic guest controllers.
```

## Source note 20, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L397)

```text
// Its lifetime ends with the dialog, before runtime input is constructed.
```

## Source note 21, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L403)

```text
// Leave the current ImGui draw before constructing the guest runtime.
```

## Source note 22, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L433)

```text
/*force=*/
```

## Source note 23, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L439)

```text
// Where an Xbox PC game keeps its files (docs/data-locations.md): saves
```

## Source note 24, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L440)

```text
// under Saved Games, caches, logs and settings under local app data.
```

## Source note 25, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L444)

```text
// Game data: cvar override, or the game files beside the executable
```

## Source note 26, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L453)

```text
// User data: cvar override, or Saved Games\<name>
```

## Source note 27, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L462)

```text
// Update data: cvar override, or empty (opt-in)
```

## Source note 28, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L469)

```text
// Cache: cvar override, or local app data. With an explicit user data
```

## Source note 29, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L470)

```text
// folder and no cache override, the cache stays inside it as before.
```

## Source note 30, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L487)

```text
// Settings: a <name>.toml beside the executable still wins (development
```

## Source note 31, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L488)

```text
// builds and existing projects); otherwise the per-user one.
```

## Source note 32, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L504)

```text
// The title's own defaults (rexglue_configure_target CVAR_DEFAULTS,
```

## Source note 33, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L505)

```text
// "name=value|..."), under the config file and command line.
```

## Source note 34, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L517)

```text
// Load config FIRST so log cvars have final values
```

## Source note 35, line 529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L529)

```text
// Each run is one file now (no rotation), so the directory is bounded
```

## Source note 36, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L530)

```text
// instead: the 100 MiB the old 5 MiB x 20 rotation allowed. Titles can
```

## Source note 37, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L531)

```text
// change it, or turn it off with 0, in OnConfigureLogging.
```

## Source note 38, line 548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L548)

```text
// Title updates are optional (docs/title-updates.md): the player's choice in
```

## Source note 39, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L549)

```text
// the guide (title_update) picks the executable, and the original is always
```

## Source note 40, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L550)

```text
// the fallback. An update build given --update_data_root runs as asked.
```

## Source note 41, line 580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L580)

```text
// Earlier builds kept user data in Documents\<name>, which OneDrive syncs.
```

## Source note 42, line 599

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L599)

```text
// Already raised by the entry point; asking again reports it for the log.
```

## Source note 43, line 677

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L677)

```text
// Window and ImGui drawer already exist from SetupPresentation; publish them
```

## Source note 44, line 678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L678)

```text
// to the runtime before Setup so hooks and native rendering see them.
```

## Source note 45, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L686)

```text
// Draw at the display's resolution unless the player chose one in the
```

## Source note 46, line 687

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L687)

```text
// guide (Preferences > Resolution) or on the command line. Not saved: it
```

## Source note 47, line 688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L688)

```text
// follows the display from run to run.
```

## Source note 48, line 726

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L726)

```text
// Mirrors the game:\ / d:\ -> game_data_root mapping in Runtime::SetupVfs.
```

## Source note 49, line 763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L763)

```text
// A title update build runs that update's code, so it loads the executable
```

## Source note 50, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L764)

```text
// patched by the same update (update_data_root, mounted at update:).
```

## Source note 51, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L792)

```text
// Patches the player can switch in the guide: as they left them.
```

## Source note 52, line 868

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L868)

```text
// Legacy/custom hosts without a pinned source fingerprint retain ordinary
```

## Source note 53, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L869)

```text
// read errors; they cannot certify replacement media is the same disc.
```

## Source note 54, line 945

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L945)

```text
// Fatal by design: no silent headless fallback.
```

## Source note 55, line 962

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L962)

```text
// Create window
```

## Source note 56, line 969

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L969)

```text
// The project name until the title's own name and icon are known at launch.
```

## Source note 57, line 970

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L970)

```text
// The SDK build stamp is in the log and the debug overlay.
```

## Source note 58, line 1017

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1017)

```text
// SDK mode: the emulated-Xenos presenter drives the overlays.
```

## Source note 59, line 1029

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1029)

```text
// Detached mode: the app brings its own renderer and drives its own paint
```

## Source note 60, line 1030

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1030)

```text
// loop. ReXApp owns the returned drawer via immediate_drawer_.
```

## Source note 61, line 1033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1033)

```text
/*presenter=*/
```

## Source note 62, line 1034

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1034)

```text
// No window_->SetPresenter, no drawer SetPresenter: the app owns the
```

## Source note 63, line 1035

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1035)

```text
// surface and the present cadence.
```

## Source note 64, line 1057

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1057)

```text
// presenter is nullptr in detached mode; ImGuiDrawer tolerates that and the
```

## Source note 65, line 1058

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1058)

```text
// gated eager font upload in SetImmediateDrawer is skipped (font uploads
```

## Source note 66, line 1059

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1059)

```text
// lazily on the first Draw instead).
```

## Source note 67, line 1096

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1096)

```text
// Consume buttons held while selecting a source or using a host menu.
```

## Source note 68, line 1102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1102)

```text
// Register the achievement notification callback now that the runtime and
```

## Source note 69, line 1103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1103)

```text
// KernelState are guaranteed to exist. Done here (not OnCreateDialogs)
```

## Source note 70, line 1104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1104)

```text
// because KernelState is null during SetupPresentation.
```

## Source note 71, line 1185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1185)

```text
// Hard-exit rather than run subsystem teardown, which can deadlock on a host
```

## Source note 72, line 1186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1186)

```text
// lock still held by a straggler TerminateTitle left running. Flush (not
```

## Source note 73, line 1187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1187)

```text
// ShutdownLogging, which frees loggers a straggler may still use); the OS
```

## Source note 74, line 1188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1188)

```text
// reclaims the rest.
```

## Source note 75, line 1249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1249)

```text
// Notify subclass before cleanup
```

## Source note 76, line 1254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1254)

```text
// Unregister overlay keybinds before destroying dialogs
```

## Source note 77, line 1260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1260)

```text
// ImGui cleanup (reverse of setup)
```

## Source note 78, line 1282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1282)

```text
// immediate_drawer_ was already unlinked from imgui_drawer_ above. Detach it
```

## Source note 79, line 1283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1283)

```text
// from its presenter so SDK mode runs OnLeavePresenter() before disposal; in
```

## Source note 80, line 1284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1284)

```text
// detached mode the drawer never had a presenter, so SetPresenter(nullptr) is
```

## Source note 81, line 1285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1285)

```text
// a no-op.
```

## Source note 82, line 1294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1294)

```text
// Window/runtime cleanup
```

## Source note 83, line 1307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1307)

```text
// Last: the guest runtime's audio, input and GPU services are gone.
```

## Source note 84, line 1310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1310)

```text
// The guide changed the title update choice; the new process picks the
```

## Source note 85, line 1311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1311)

```text
// executable for it.
```

## Source note 86, line 1312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1312)

```text
/*hand_off=*/
```

## Source note 87, line 1323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1323)

```text
// --- Xbox guide (RG-GDK-041) ---
```

## Source note 88, line 1331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1331)

```text
// XamShowKeyboardUI shows the console's own keyboard from the same files
```

## Source note 89, line 1332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1332)

```text
// (RG-GDK-059); the ImGui dialog while they load or without them.
```

## Source note 90, line 1360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1360)

```text
// Reading the system update decompresses XAM; keep it off the UI thread.
```

## Source note 91, line 1368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1368)

```text
// The guide the title build embedded comes first, unless a system update
```

## Source note 92, line 1369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1369)

```text
// was named explicitly.
```

## Source note 93, line 1423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1423)

```text
// Polling a missing XInput pad is slow; only read connected users.
```

## Source note 94, line 1448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1448)

```text
// detaches from the ImGui drawer and releases guest input
```

## Source note 95, line 1475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/rex_app.cpp#L1475)

```text
// Still loading, or no system update: say which, once.
```
