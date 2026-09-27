# Title repository standard

How a repository for recompiled games (a *title repository*) is laid out and
what its README says. One repository can hold one game or a series, like
[furqanagwan/007](https://github.com/furqanagwan/007) (Quantum of Solace,
Blood Stone, 007 Legends). The SDK stays generic: title-specific
configuration, investigation notes and evidence live in the title repository,
and fixes that help every title go to the SDK.

## Rules

- **Never commit game material.** No disc images, extracted files, XEX or
  STFS content, generated C++, builds, saves, logs, screenshots or captures of
  the game. The `.gitignore` is an allowlist (ignore `/*`, then un-ignore each
  tracked file), so new files stay private until they're deliberately added.
- **Original artwork only.** Box art, game icons and logos are the publisher's;
  use original artwork in `assets/`.
- **Identify every release exactly**, from the disc and the XEX headers, never
  from memory: the Redump name of the image, region, languages, title ID, media
  ID, executable version, disc number and title updates. Record "not yet
  identified" until the material is in hand.
- **Status claims need evidence**: a linked record (`docs/<ID>.md`) naming the
  SDK commit, the build, the hardware and what was and wasn't tested.
- **Commit identity**: the maintainer's GitHub no-reply address only, never a
  work address, as for the SDK.

## Layout

```text
README.md                 This standard's README (below)
.gitignore                Allowlist; everything else stays local
assets/
  logo.svg                Original square logo
  social-preview.svg/.png Original 1280x640 image for Settings → Social preview
configs/<title>.toml      Codegen includes for each title (function entries,
                          hooks), added to the private manifest's `includes`
docs/
  README.md               Notes for contributors
  <PREFIX>-NNN.md         One record per issue: goal, evidence, result
```

Private work (disc images, the `rexglue init` project, logs) sits beside the
repository files in the same folder, one subfolder per title, and is
ignored.

## README template

Sections in this order; drop a section only when it can't apply.

````markdown
<p align="center"><img src="assets/logo.svg" width="128" alt="<Series> logo"></p>

# <Series or title> — Xbox 360 recompilation

<One sentence: what these games are and that they're statically recompiled for
Windows PC with ReXGlue.>

> [!IMPORTANT]
> This repository contains no game files. You need your own legally obtained
> copy of each game.

## Games

| Game | Released | Disc (Redump name) | Region | Languages | Title ID | Media ID | Executable | Status |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| <Title> | <year> · <developer> | `<Redump name>` | <region> | <langs> | `<ID>` | `<ID>` | v<version>, disc <n>/<n>, TU <n or none> | <status> |

Status is one of: **Planned** (not started), **Investigating** (recompiles,
doesn't reach gameplay yet), **In-game** (reaches gameplay, not yet validated
end to end), **Playable** (validated through the game, with the limits listed).

## <Title> status

What works, what hasn't been tested and what's known broken, each with a link
to its record in `docs/`.

## Requirements

- Windows 11 x64 and a Direct3D 12 GPU (list what was tested).
- Visual Studio with LLVM Clang, CMake and Ninja, as the SDK README lists.
- ReXGlue SDK: the fork and the minimum commit.
- Optional: the Microsoft GDK edition for GDK builds.

## Build

1. Extract the disc to a private folder.
2. `rexglue init` for the executable.
3. Add `configs/<title>.toml` to the manifest's `includes`.
4. `rexglue codegen`, then configure and build against the installed SDK.
5. Run command, with the options that matter.

## Repository layout

## Issues and records

Where issues are tracked, what an issue ID looks like, and that SDK-wide fixes
go to the SDK.

## Legal

Trademarks and copyrights belong to their owners; the project isn't
affiliated with or endorsed by them.

## Credits
````

## Why

- **Allowlist `.gitignore`:** a title folder holds gigabytes of private
  material next to the few files worth sharing. An allowlist makes adding game
  material a deliberate act, not an accident.
- **Exact release identity:** recompiled code is only valid for the XEX it was
  generated from; the same title ID can cover several builds.
- **Status levels:** they keep "it boots" from reading as "it's playable".
