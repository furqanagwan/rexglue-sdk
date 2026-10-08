# ADR-016: Required PC GDK; Helix is a future validation target

Date: 2026-10-07. Status: accepted owner direction; implementation and validation
are recorded in the release evidence. Supersedes ADR-001's optional GDK build
policy, not its Windows-only destination or guest compatibility boundaries.

## Decision

ReXGlue is a Windows x64 / April 2026 PC GDK 260404 / D3D12 static Xbox 360
recompilation SDK. The supported SDK and installed-consumer builds require the
pinned GDK. `REXGLUE_USE_GDK=OFF` fails with migration guidance. The canonical
preset is `win-amd64-gdk`; the old `win-amd64` spelling resolves to the same
GDK build/install directories. Existing GDK-free artifacts are historical
baselines, not a separately maintained supported configuration.

Native Win32 presentation, XAudio2, GameInput and the existing XInput adapter
remain. XInput provides compatible pads, including Bluetooth LE devices that
GameInput does not enumerate; it does not imply a GDK-free SDK. Retained
compile-time fallback branches may be removed separately after their gates;
this change does not remove compatibility behavior to make a build pass.
The standalone Xbox Guide scene library keeps its narrow host interfaces and
does not gain a dependency on the entire SDK or on GDK APIs it does not use.

No SDL, Linux, macOS or Vulkan runtime support is introduced. SPIR-V remains
shader IR only. ARM64 research gates stay open; hardware architecture is not
inferred from a product codename. Gaming Runtime startup policy and Xbox Live
identity/services remain separate, explicit contracts; requiring the build
toolchain does not manufacture service access or title compatibility.

## Helix boundary

Microsoft says Project Helix is designed to play Xbox console and PC games,
with developer alpha hardware planned for 2027. That makes the Windows/GDK
architecture a relevant preparation target, not a proven Helix deployment.
Actual hardware, platform SDK requirements and deployment/certification tests
must be available and passed before support is claimed. Source:
[Xbox's GDC statement](https://news.xbox.com/en-us/2026/03/11/project-helix-building-next-generation-of-xbox/).

## Verification

Configure defaults and the compatibility alias against 260404; reject explicit
GDK OFF, a missing root and a differing edition. Build Debug and Release;
discover and run the affected unit/PPC cases, including installed-runtime cases
locally. Validate an installed consumer against its own GDK root. Hosted CI is
a software build/test gate and explicitly excludes installed-runtime cases;
it cannot replace local deployment, GPU, title or save tests. Record known
Debug GPU failures rather than hiding them or switching shader defaults.

Microsoft's documented
[payload extraction](https://learn.microsoft.com/en-us/gaming/gdk/docs/gdk-dev/console-dev/usingwithoutinstall/extract-setup-payload?view=gdk-2604)
supports obtaining headers/libraries without full installation. The public
[2604 Update 4 release](https://github.com/microsoft/GDK/releases/tag/April-2026-Update-4-v2604.4.7897)
is pinned in the CI setup script by SHA-256; its contents are not committed or
included in SDK release artifacts.
