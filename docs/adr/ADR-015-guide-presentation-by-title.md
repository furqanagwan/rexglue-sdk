# ADR-015: Guide presentation is selected by the title host

Date: 2026-10-07. Status: implemented; painted fidelity and original Xbox execution remain unvalidated.

## Context

The owner requires the existing Xbox 360 Guide for 360 recompilations and the
Microsoft backward-compatibility Guide for original Xbox games. Previously,
`GuideAssets` preferred emulator scenes whenever they were present, and a global
BC Flash path replaced the asset source for every title. Asset availability is
not a title-platform identifier.

## Decision

`rexglue_configure_target` accepts `GUIDE_PRESENTATION xbox360` (default) or
`GUIDE_PRESENTATION original-xbox`. The host compiles its selected presentation
into `rex_app.cpp` and passes the typed `GuidePresentation` through both embedded
and external asset loading. A config file or external asset override does not
change that selection. The standalone Guide's full adapter defaults to Xbox 360.

Xbox 360 builds embed only `REXGLUE_SYSTEM_UPDATE`, ignoring a configured BC Flash
path. Original Xbox presentation requires `REXGLUE_GUIDE_FLASH`; it can combine
that source with a console update for supplementary resources. Its emulator
scenes are required: missing scenes report an error rather than silently
substituting the other Guide. Existing 360 navigation, timelines and scenes
remain in place. The experimental host launch menu remains opt-in.

The same local host services may be exposed through either presentation.
Original Xbox presentation uses the owner's actual BC scenes; this does not
establish complete service or visual parity with Microsoft.

## Execution boundary

Presentation selection does not select or create an original Xbox CPU backend.
The SDK executes statically generated Xbox 360 PPC modules (ADR-004). Supporting
original Xbox XBE/x86 titles through a XeFu-like compatibility layer requires
its own execution design, module/import inventory, independently usable
implementation and title regression evidence. Microsoft's installed native DLLs
and service identities are reference material, not reusable SDK dependencies.
No original Xbox title launch is claimed by this change.

## Validation

Private-asset tests check the default and explicit 360 scenes, explicit BC
scenes, rejection of a console update in original Xbox mode and absence of an
automatic emulator fallback. Existing BC tab/timeline and message-box tests opt
into their intended presentation. Installed-consumer tests check target selection,
asset source precedence and invalid/missing configuration. Painted, controller,
service and representative original Xbox execution gates remain open.
