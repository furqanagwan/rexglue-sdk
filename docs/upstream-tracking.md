# Upstream tracking and compatibility provenance

Snapshot: 2026-09-23. These are evaluated candidates, not imported patches. A–H classifications are defined in [the investigation](investigation.md). “Unknown” regressions means none verified during this review, not proven absence. Issue/PR comments contain upstream observations; no local title outcome is inferred. See [roadmap](roadmap.md) for live ReXGlue issue links.

## Compact upstream-to-roadmap index

All implementation statuses are **investigated, not ported**. The roadmap resolves planning IDs to actual issue numbers. Closed-unmerged entries are retained as rejected/research evidence.

| ReXGlue area / upstream item | Source state | Commit (merge or PR head) | Scope/class | Regression risk | ReXGlue issue |
| --- | --- | --- | --- | --- | --- |
| [xenia-canary/xenia-canary #5](https://github.com/xenia-canary/xenia-canary/issues/5) | open | `not identified` | B/H; useful research | See scoped record below; never assume absence | RG-GDK-017 |
| [xenia-canary/xenia-canary #438](https://github.com/xenia-canary/xenia-canary/issues/438) | open | `not identified` | B/H; game-specific; useful research | See scoped record below; never assume absence | RG-GDK-018 |
| [xenia-canary/xenia-canary #600](https://github.com/xenia-canary/xenia-canary/issues/600) | open | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-019 |
| [xenia-canary/xenia-canary #608](https://github.com/xenia-canary/xenia-canary/issues/608) | open | `not identified` | B/H; regression-related; vendor | See scoped record below; never assume absence | RG-GDK-006 |
| [xenia-canary/xenia-canary #739](https://github.com/xenia-canary/xenia-canary/issues/739) | open | `not identified` | B/H; useful research | See scoped record below; never assume absence | RG-GDK-018 |
| [xenia-canary/xenia-canary #754](https://github.com/xenia-canary/xenia-canary/issues/754) | open | `not identified` | B/H; useful research | See scoped record below; never assume absence | RG-GDK-014 |
| [xenia-canary/xenia-canary #773](https://github.com/xenia-canary/xenia-canary/issues/773) | open | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-026 |
| [xenia-canary/xenia-canary #872](https://github.com/xenia-canary/xenia-canary/issues/872) | open | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-015 |
| [xenia-canary/xenia-canary #1036](https://github.com/xenia-canary/xenia-canary/issues/1036) | open | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-018 |
| [xenia-canary/xenia-canary #1093](https://github.com/xenia-canary/xenia-canary/issues/1093) | open | `not identified` | B/H; regression-related; game-specific | See scoped record below; never assume absence | RG-GDK-011 |
| [xenia-canary/xenia-canary #1134](https://github.com/xenia-canary/xenia-canary/issues/1134) | open | `not identified` | B/H; regression-related; vendor | See scoped record below; never assume absence | RG-GDK-006 |
| [xenia-canary/xenia-canary #1214](https://github.com/xenia-canary/xenia-canary/issues/1214) | open | `not identified` | B/H; useful research; regression-related | See scoped record below; never assume absence | RG-GDK-018 |
| [xenia-canary/xenia-canary #1220](https://github.com/xenia-canary/xenia-canary/issues/1220) | open | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-017 |
| [xenia-canary/xenia-canary #748](https://github.com/xenia-canary/xenia-canary/pull/748) | open PR | `a7f6514e699018674f5e3f56b437e4d9c58e7641` | B/H; useful research | See scoped record below; never assume absence | RG-GDK-018 |
| [xenia-canary/xenia-canary #844](https://github.com/xenia-canary/xenia-canary/pull/844) | open PR | `16c13ed6ca60c20e4611e804216f78f5261c99ba` | B/H; relevant but pending upstream | See scoped record below; never assume absence | RG-GDK-013 |
| [xenia-canary/xenia-canary #981](https://github.com/xenia-canary/xenia-canary/pull/981) | open PR | `555e9a4a456d2a6d80a8811486208f82095fcfe9` | B/H; relevant but pending upstream | See scoped record below; never assume absence | RG-GDK-017 |
| [xenia-canary/xenia-canary #1025](https://github.com/xenia-canary/xenia-canary/pull/1025) | open PR | `abcf2ff1bea480cb6c4cdcafd2c09350826e01d3` | B/H; relevant but pending upstream | See scoped record below; never assume absence | RG-GDK-015 |
| [xenia-canary/xenia-canary #1077](https://github.com/xenia-canary/xenia-canary/pull/1077) | open PR | `dcd2fff24243b4d2d67c2d08a10d235f04f0de80` | G/H; experimental; game-specific | See scoped record below; never assume absence | RG-GDK-012 |
| [xenia-canary/xenia-canary #1109](https://github.com/xenia-canary/xenia-canary/pull/1109) | open PR | `95f9f68817c9828ba3a28c144916d45d34d44bd1` | B/H; relevant but pending upstream | See scoped record below; never assume absence | RG-GDK-017 |
| [xenia-canary/xenia-canary #1111](https://github.com/xenia-canary/xenia-canary/pull/1111) | open PR | `78e06cafaa6429e5464786baa9e1edf252bbe582` | C/H; relevant but pending upstream; experimental; not adopted | See scoped record below; deferred to #65 | RG-GDK-010 |
| [xenia-canary/xenia-canary #1182](https://github.com/xenia-canary/xenia-canary/pull/1182) | open PR | `fa6cdaae0f58e9161e5e41ea3683f837b3b112c7` | B/H; relevant but pending upstream | See scoped record below; never assume absence | RG-GDK-004 |
| [xenia-canary/xenia-canary #1225](https://github.com/xenia-canary/xenia-canary/pull/1225) | open PR | `fe960bf66f98204940a7464ed35b50ef5b7b4cdc` | B/H; relevant but pending upstream; blocked upstream | See scoped record below; never assume absence | RG-GDK-014 |
| [xenia-canary/xenia-canary #1226](https://github.com/xenia-canary/xenia-canary/pull/1226) | open PR | `c43ea0f9c3e3f3cac600a57d9f464a38c945d808` | B/H; relevant but pending upstream | See scoped record below; never assume absence | RG-GDK-017 |
| [xenia-canary/xenia-canary #1230](https://github.com/xenia-canary/xenia-canary/pull/1230) | open PR | `ef97e8a70f4f0d0fffa2736789670f6f8164d055` | B/H; relevant but pending upstream | See scoped record below; never assume absence | RG-GDK-020 |
| [xenia-canary/xenia-canary #1016](https://github.com/xenia-canary/xenia-canary/pull/1016) | merged | `fbd620c22b44638b66a70bba80d6f30d55a10924` | C/H; useful research; relevant and merged upstream | See scoped record below; never assume absence | RG-GDK-010 |
| [xenia-canary/xenia-canary #1029](https://github.com/xenia-canary/xenia-canary/pull/1029) | closed unmerged | `a6e1a418f33efb87126ba1ffde2b0b536818170a` | B/H; useful research; rejected | See scoped record below; never assume absence | RG-GDK-018 |
| [xenia-canary/xenia-canary #1031](https://github.com/xenia-canary/xenia-canary/pull/1031) | closed unmerged | `93e3fa59b040f124f0343a80b90f2d0b53b125fc` | B/H; useful research | See scoped record below; never assume absence | RG-GDK-012 |
| [xenia-canary/xenia-canary #1038](https://github.com/xenia-canary/xenia-canary/pull/1038) | merged | `6e5b8324f4101464de0f8c2334edb03cac8826c4` | B/H; regression-related; relevant and merged upstream | See scoped record below; never assume absence | RG-GDK-018 |
| [xenia-canary/xenia-canary #1058](https://github.com/xenia-canary/xenia-canary/pull/1058) | merged | `d55670e40b1016cc36cca5111c821b3e7c9a85b8` | B/H; regression-related; behaviour kept by the #1218 port | See scoped record below | RG-GDK-010 |
| [xenia-canary/xenia-canary #1127](https://github.com/xenia-canary/xenia-canary/pull/1127) | merged | `da47dfaacfae1134b238af9083a7f3d413c6cbbe` | B/H; candidate for later port; relevant and merged upstream | See scoped record below; never assume absence | RG-GDK-005 |
| [xenia-canary/xenia-canary #1131](https://github.com/xenia-canary/xenia-canary/pull/1131) | merged | `0f2980de442341788c07b282d6fbd6dc689166de` | B/H; useful research; relevant and merged upstream | See scoped record below; never assume absence | RG-GDK-012 |
| [xenia-canary/xenia-canary #1135](https://github.com/xenia-canary/xenia-canary/pull/1135) | closed unmerged | `421498c3b38257f98efb043f438b8e28ebf951c9` | G/H; useful research; game-specific | See scoped record below; never assume absence | RG-GDK-017 |
| [xenia-canary/xenia-canary #1147](https://github.com/xenia-canary/xenia-canary/pull/1147) | merged | `7cd47947b07de30b649fb4224418a659890eab73` | B/H; useful research; relevant and merged upstream | See scoped record below; never assume absence | RG-GDK-011 |
| [xenia-canary/xenia-canary #1163](https://github.com/xenia-canary/xenia-canary/pull/1163) | merged | `437a7280cf95310d518a2f68087aab61403956ac` | C/H; candidate for later port; relevant and merged upstream | See scoped record below; never assume absence | RG-GDK-009 |
| [xenia-canary/xenia-canary #1180](https://github.com/xenia-canary/xenia-canary/pull/1180) | merged | `22708301ba76d10aae6f7d7caac8b1cac9e4a8e6` | C/H; useful research; redesign | See scoped record below; never assume absence | RG-GDK-004 |
| [xenia-canary/xenia-canary #1190](https://github.com/xenia-canary/xenia-canary/pull/1190) | merged | `3a44f20c7bc66db1da583e8a6f0ab740e31908e9` | B/H; candidate for later port; relevant and merged upstream | See scoped record below; never assume absence | RG-GDK-012 |
| [xenia-canary/xenia-canary #1195](https://github.com/xenia-canary/xenia-canary/pull/1195) | closed unmerged | `ab349b475d4d82dd2a4330b2e2eb46332006afce` | B/H; candidate for later port | See scoped record below; never assume absence | RG-GDK-011 |
| [xenia-canary/xenia-canary #1202](https://github.com/xenia-canary/xenia-canary/pull/1202) | closed unmerged | `1cc288bc71e625bd9272dafc2f1fb01259a62eb2` | B/H; useful research; rejected; regression risk | See scoped record below; never assume absence | RG-GDK-004 |
| [xenia-canary/xenia-canary #1215](https://github.com/xenia-canary/xenia-canary/pull/1215) | merged | `87c24112706d95f15f83dfec58e93923bd7ffa07` | B/H; adopted (adapted) in RG-GDK-004 | See scoped record below | RG-GDK-004 |
| [xenia-canary/xenia-canary #1216](https://github.com/xenia-canary/xenia-canary/pull/1216) | merged | `5d4dc8a88abb2965f2933286571f5bfa0b87391d` | B/H; candidate for later port; relevant and merged upstream | See scoped record below; never assume absence | RG-GDK-017 |
| [xenia-canary/xenia-canary #1218](https://github.com/xenia-canary/xenia-canary/pull/1218) | merged | `3d233a5b2e94b940825847b70c788951e364bb33` | C/H; adopted (D3D12 native-query subset) in RG-GDK-010 | See scoped record below; in-shader counters in #64 | RG-GDK-010 |
| [xenia-canary/xenia-canary #1222](https://github.com/xenia-canary/xenia-canary/pull/1222) | merged | `9da693480d0995326b81c3a14f8b1a4c226066eb` | B/H; candidate for later port; relevant and merged upstream | See scoped record below; never assume absence | RG-GDK-009 |
| [xenia-canary/xenia-canary #1227](https://github.com/xenia-canary/xenia-canary/pull/1227) | merged | `dcf2994ea1d604e841b5553b2bf941b809e36e79` | B/H; candidate for later port; relevant and merged upstream | See scoped record below; never assume absence | RG-GDK-014 |
| [xenia-canary/xenia-canary #1238](https://github.com/xenia-canary/xenia-canary/pull/1238) | merged | `0bd090dbe979bc64959efe519aa320db8e3eb467` | B/H; regression-related; relevant and merged upstream | See scoped record below; never assume absence | RG-GDK-009 |
| [xenia-canary/xenia-canary #1240](https://github.com/xenia-canary/xenia-canary/pull/1240) | merged | `89609297c7ae25dc5ba404c6a977260b806bb725` | A/B; adopted (RG-GDK-008) | See scoped record below; never assume absence | RG-GDK-008 |
| [xenia-canary/xenia-canary #1243](https://github.com/xenia-canary/xenia-canary/pull/1243) | merged | `c9c8e483b13249ba5f0060fc4b36071da6d67261` | A/B; adopted (RG-GDK-008) | See scoped record below; never assume absence | RG-GDK-008 |
| [has207/xenia-edge #38](https://github.com/has207/xenia-edge/issues/38) | open | `not identified` | B/H; candidate for later port | See scoped record below; never assume absence | RG-GDK-017 |
| [has207/xenia-edge #234](https://github.com/has207/xenia-edge/issues/234) | open | `not identified` | C/H; regression-related | See scoped record below; never assume absence | RG-GDK-015 |
| [has207/xenia-edge #268](https://github.com/has207/xenia-edge/issues/268) | open | `not identified` | D; useful research; emulator-specific | See scoped record below; never assume absence | RG-GDK-015 |
| [has207/xenia-edge #276](https://github.com/has207/xenia-edge/issues/276) | open | `not identified` | B/H; game-specific; useful research | See scoped record below; never assume absence | RG-GDK-011 |
| [has207/xenia-edge #278](https://github.com/has207/xenia-edge/issues/278) | open | `not identified` | G/H; regression-related; game-specific | See scoped record below; never assume absence | RG-GDK-012 |
| [has207/xenia-edge #280](https://github.com/has207/xenia-edge/issues/280) | open | `not identified` | B/H; game-specific; useful research | See scoped record below; never assume absence | RG-GDK-026 |
| [has207/xenia-edge #251](https://github.com/has207/xenia-edge/pull/251) | open PR | `ecee74cb8d5300bb19ebbba3b53ec6ec2cf76044` | C/H; experimental; relevant but pending upstream | See scoped record below; never assume absence | RG-GDK-015 |
| [has207/xenia-edge #107](https://github.com/has207/xenia-edge/issues/107) | closed | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-018 |
| [has207/xenia-edge #111](https://github.com/has207/xenia-edge/issues/111) | closed | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-018 |
| [has207/xenia-edge #113](https://github.com/has207/xenia-edge/issues/113) | closed | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-018 |
| [has207/xenia-edge #120](https://github.com/has207/xenia-edge/issues/120) | closed | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-018 |
| [has207/xenia-edge #127](https://github.com/has207/xenia-edge/pull/127) | merged | `397fc9284178b7626e77642c6ea24bfa69a620a8` | B/H; useful research; relevant and merged upstream | See scoped record below; never assume absence | RG-GDK-010 |
| [has207/xenia-edge #141](https://github.com/has207/xenia-edge/issues/141) | closed | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-018 |
| [has207/xenia-edge #143](https://github.com/has207/xenia-edge/pull/143) | merged | `c9a6327ad136f82920df547afc9e552424b863ac` | G/H; useful research; obsolete workaround; not adopted | See scoped record below | RG-GDK-010 |
| [has207/xenia-edge #145](https://github.com/has207/xenia-edge/pull/145) | closed unmerged | `5d31dea2343fcd60973e17bb89fe0851cca2e1fc` | G/H; experimental; rejected | See scoped record below; never assume absence | RG-GDK-010 |
| [has207/xenia-edge #160](https://github.com/has207/xenia-edge/pull/160) | merged | `aa749b4be4f49ba9818eca1028ac77fb69f9d7b8` | G/H; candidate for later port; game-specific | See scoped record below; never assume absence | RG-GDK-012 |
| [has207/xenia-edge #164](https://github.com/has207/xenia-edge/issues/164) | closed | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-018 |
| [has207/xenia-edge #194](https://github.com/has207/xenia-edge/pull/194) | closed unmerged | `9376b083bf8937a1bbc6fbff31cecc4c773a2c30` | B/H; useful research; rejected | See scoped record below; never assume absence | RG-GDK-010 |
| [has207/xenia-edge #198](https://github.com/has207/xenia-edge/issues/198) | closed | `not identified` | C/H; useful research | See scoped record below; never assume absence | RG-GDK-007 |
| [has207/xenia-edge #204](https://github.com/has207/xenia-edge/issues/204) | closed | `not identified` | B/H; useful research; vendor | See scoped record below; never assume absence | RG-GDK-006 |
| [has207/xenia-edge #207](https://github.com/has207/xenia-edge/pull/207) | closed unmerged | `551af133b2ffe8a4ab171dab9cb338b6a14d1665` | B/H; useful research | See scoped record below; never assume absence | RG-GDK-010 |
| [has207/xenia-edge #223](https://github.com/has207/xenia-edge/issues/223) | closed | `not identified` | F/H; regression-related; obsolete host path | See scoped record below; never assume absence | RG-GDK-011 |
| [has207/xenia-edge #233](https://github.com/has207/xenia-edge/issues/233) | closed | `not identified` | C/H; regression-related | See scoped record below; never assume absence | RG-GDK-015 |
| [has207/xenia-edge #235](https://github.com/has207/xenia-edge/issues/235) | closed | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-018 |
| [has207/xenia-edge #236](https://github.com/has207/xenia-edge/pull/236) | closed unmerged | `444746e4eb3d99a85f01137e0044641ec96701cb` | G/H; useful research; rejected | See scoped record below; never assume absence | RG-GDK-018 |
| [has207/xenia-edge #263](https://github.com/has207/xenia-edge/issues/263) | closed | `not identified` | B/H; regression-related | See scoped record below; never assume absence | RG-GDK-018 |
| [has207/xenia-edge #275](https://github.com/has207/xenia-edge/pull/275) | closed unmerged | `02d9ec4bddc6686f5a4c7f451faceee8f6dfe8ae` | G/H; useful research; game-specific; rejected | See scoped record below; never assume absence | RG-GDK-016 |

## Significant Canary and Edge candidates

### has207/xenia-edge #278 — Regression with depth_bias_shader_offset implementation

- Source: [https://github.com/has207/xenia-edge/issues/278](https://github.com/has207/xenia-edge/issues/278); created 2026-09-20T14:25:06Z; updated 2026-09-20T14:25:06Z; author `Slashic`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Lost Odyssey on RX 6600: depth_bias_shader_offset does not replace the old clamp successfully; do not enable globally.
- Classification: regression-related; game-specific; G/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-012**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #234 — Guest Scheduler regressions

- Source: [https://github.com/has207/xenia-edge/issues/234](https://github.com/has207/xenia-edge/issues/234); created 2026-08-21T06:35:02Z; updated 2026-09-12T12:54:02Z; author `has207`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Guest scheduler regressions and later recovery reports; runtime safepoints differ from static execution.
- Classification: regression-related; C/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-015**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #251 — [Kernel] Park host-thread guest threads that keep delaying for zero time

- Source: [https://github.com/has207/xenia-edge/pull/251](https://github.com/has207/xenia-edge/pull/251); created 2026-08-27T04:05:32Z; updated 2026-09-21T13:06:18Z; author `xenios-jp`.
- Upstream status: **pending upstream**. PR head (not adopted) commit `ecee74cb8d5300bb19ebbba3b53ec6ec2cf76044`.
- Scope / reason / applicability: Host-thread Sleep(0) parking changes guest timing; author did not test x64 or networking. Await evidence.
- Classification: experimental; relevant but pending upstream; C/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-015**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/kernel/xthread.cc`; `src/xenia/kernel/xthread.h`.
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #275 — [Kernel] Fix crash in UEFA Champions League 2006-2007 (title 45410811) from runaway audio buffer allocation

- Source: [https://github.com/has207/xenia-edge/pull/275](https://github.com/has207/xenia-edge/pull/275); created 2026-09-16T15:01:15Z; updated 2026-09-16T16:09:16Z; author `HandsleyD`.
- Upstream status: **closed unmerged**. PR head (not adopted) commit `02d9ec4bddc6686f5a4c7f451faceee8f6dfe8ae`.
- Scope / reason / applicability: Closed unmerged: title-specific 192KB allocation cap rejected. Maintainer identifies storage timing; examine 5e9eae601 instead.
- Classification: useful research; game-specific; rejected; G/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-016**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/kernel/xboxkrnl/xboxkrnl_debug.cc`; `src/xenia/kernel/xboxkrnl/xboxkrnl_memory.cc`; `src/xenia/memory.cc`; `src/xenia/memory.h`.
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #236 — [APU] Emit silence instead of stalling on XMA hard decode errors (fixes LEGO LOTR intro freeze)

- Source: [https://github.com/has207/xenia-edge/pull/236](https://github.com/has207/xenia-edge/pull/236); created 2026-08-23T19:59:55Z; updated 2026-09-07T18:49:39Z; author `Forgottenshadow89`.
- Upstream status: **closed unmerged**. PR head (not adopted) commit `444746e4eb3d99a85f01137e0044641ec96701cb`.
- Scope / reason / applicability: Closed unmerged silence substitution, dependent on FFmpeg error propagation. Maintainer preferred actual decode fix.
- Classification: useful research; rejected; G/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/apu/xma_context_new.cc`; `src/xenia/apu/xma_context_new.h`; `src/xenia/apu/xma_decoder.cc`.
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #235 — [Bug report] LEGO The Lord of the Rings: opening cutscene freezes — all XMA decoders stall on the same audio stream

- Source: [https://github.com/has207/xenia-edge/issues/235](https://github.com/has207/xenia-edge/issues/235); created 2026-08-23T15:39:18Z; updated 2026-08-23T16:24:53Z; author `Forgottenshadow89`.
- Upstream status: **closed report**. Commit not identified for this report.
- Scope / reason / applicability: LEGO LOTR intro stall motivates malformed-frame/cutscene progression tests; closure does not validate ReXGlue.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #141 — [XMA] The old & new version decoder have the BGM looping issue

- Source: [https://github.com/has207/xenia-edge/issues/141](https://github.com/has207/xenia-edge/issues/141); created 2026-04-16T07:53:55Z; updated 2026-09-06T08:13:57Z; author `lllljj1991`.
- Upstream status: **closed report**. Commit not identified for this report.
- Scope / reason / applicability: Koei audio hitches described as looping; maintainer reports newer decoder fixed it. Preserve both symptom and uncertainty.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #263 — [Regression report] SmackDown! vs RAW 2007 audio stuttering frequently

- Source: [https://github.com/has207/xenia-edge/issues/263](https://github.com/has207/xenia-edge/issues/263); created 2026-08-31T18:09:05Z; updated 2026-09-12T13:52:38Z; author `RiasatSalminSami`.
- Upstream status: **closed report**. Commit not identified for this report.
- Scope / reason / applicability: SmackDown vs RAW 2007 reporter found improvements at 67e0804; CPU/storage changes confound attribution.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #233 — [Regression] Need for Speed Shift freezes when loading races since 34357e2

- Source: [https://github.com/has207/xenia-edge/issues/233](https://github.com/has207/xenia-edge/issues/233); created 2026-08-21T05:22:45Z; updated 2026-08-21T18:44:22Z; author `kllrvet`.
- Upstream status: **closed report**. Commit not identified for this report.
- Scope / reason / applicability: NFS Shift: ccd4443 good, 34357e2 bad, guest_scheduler=false workaround.
- Classification: regression-related; C/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-015**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #160 — [GPU] FBO/ROV shader polygon offset for decal draws

- Source: [https://github.com/has207/xenia-edge/pull/160](https://github.com/has207/xenia-edge/pull/160); created 2026-05-11T07:09:35Z; updated 2026-05-29T04:19:53Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `aa749b4be4f49ba9818eca1028ac77fb69f9d7b8`.
- Scope / reason / applicability: Merged decal shader offset; comments report FH2 nearly invisible cars; #278 reports Lost Odyssey regression.
- Classification: candidate for later port; game-specific; G/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-012**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/d3d12/d3d12_command_processor.cc`; `src/xenia/gpu/d3d12/d3d12_command_processor.h`; `src/xenia/gpu/d3d12/pipeline_cache.cc`; `src/xenia/gpu/d3d12/pipeline_cache.h`; `src/xenia/gpu/draw_util.cc`; `src/xenia/gpu/draw_util.h`; `src/xenia/gpu/dxbc_shader_translator.cc`; `src/xenia/gpu/dxbc_shader_translator.h`; `src/xenia/gpu/dxbc_shader_translator_om.cc`; `src/xenia/gpu/spirv_shader_translator.cc`; `src/xenia/gpu/spirv_shader_translator.h`; `src/xenia/gpu/spirv_shader_translator_rb.cc`; `src/xenia/gpu/vulkan/vulkan_command_processor.cc`; `src/xenia/gpu/vulkan/vulkan_command_processor.h`; `src/xenia/gpu/vulkan/vulkan_pipeline_cache.cc`; `src/xenia/gpu/vulkan/vulkan_pipeline_cache.h`; `src/xenia/ui/imgui_debug_dialog.cc`; `src/xenia/ui/imgui_debug_dialog.h`.
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #198 — depth_float24_convert_in_pixel_shader not working in d3d12

- Source: [https://github.com/has207/xenia-edge/issues/198](https://github.com/has207/xenia-edge/issues/198); created 2026-07-02T13:28:56Z; updated 2026-07-08T06:46:47Z; author `has207`.
- Upstream status: **closed report**. Commit not identified for this report.
- Scope / reason / applicability: Closed report: float24 SPIR-V→DXIL translation failure in Tomb Raider Underworld, explicitly not a regression.
- Classification: useful research; C/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-007**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #204 — 45410811 - Flickering issue on my specific NVIDIA hardware

- Source: [https://github.com/has207/xenia-edge/issues/204](https://github.com/has207/xenia-edge/issues/204); created 2026-07-07T10:26:41Z; updated 2026-07-07T12:23:38Z; author `AhayriSG`.
- Upstream status: **closed report**. Commit not identified for this report.
- Scope / reason / applicability: Closed for issue-scope reasons, not a demonstrated NVIDIA fix; follows game-compatibility #120.
- Classification: useful research; vendor; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-006**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### has207/xenia-edge #223 — [Linux/AMD] Readback Resolve broken after 9792c2b

- Source: [https://github.com/has207/xenia-edge/issues/223](https://github.com/has207/xenia-edge/issues/223); created 2026-08-04T05:17:08Z; updated 2026-09-08T22:37:53Z; author `StaydMcMuffin`.
- Upstream status: **closed report**. Commit not identified for this report.
- Scope / reason / applicability: Linux/AMD Vulkan resolve report; informs readback tests, not a D3D12 driver fix.
- Classification: regression-related; obsolete host path; F/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-011**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #207 — [GPU] Add VIZ_QUERY predication

- Source: [https://github.com/has207/xenia-edge/pull/207](https://github.com/has207/xenia-edge/pull/207); created 2026-07-09T18:08:18Z; updated 2026-07-17T21:39:40Z; author `goldislead`.
- Upstream status: **closed unmerged**. PR head (not adopted) commit `551af133b2ffe8a4ab171dab9cb338b6a14d1665`.
- Scope / reason / applicability: VIZ proposal must be checked against current Canary #1111; do not infer settled predication from a closed PR.
- Classification: useful research; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-010**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/command_processor.cc`; `src/xenia/gpu/command_processor.h`; `src/xenia/gpu/d3d12/d3d12_command_processor.cc`; `src/xenia/gpu/d3d12/d3d12_command_processor.h`; `src/xenia/gpu/d3d12/d3d12_occlusion_query_pool.cc`; `src/xenia/gpu/d3d12/d3d12_occlusion_query_pool.h`; `src/xenia/gpu/d3d12/deferred_command_list.cc`; `src/xenia/gpu/d3d12/deferred_command_list.h`; `src/xenia/gpu/gpu_flags.cc`; `src/xenia/gpu/gpu_flags.h`; `src/xenia/gpu/metal/metal_command_processor.cc`; `src/xenia/gpu/metal/metal_command_processor.h`; `src/xenia/gpu/null/null_command_processor.cc`; `src/xenia/gpu/null/null_command_processor.h`; `src/xenia/gpu/packet_disassembler.cc`; `src/xenia/gpu/packet_disassembler.h`; `src/xenia/gpu/pm4_command_processor_implement.h`; `src/xenia/gpu/shader_compiler_main.cc`; `src/xenia/gpu/spirv_fsi_system_constants.cc`; `src/xenia/gpu/spirv_fsi_system_constants.h`; `src/xenia/gpu/spirv_shader_translator.cc`; `src/xenia/gpu/spirv_shader_translator.h`; `src/xenia/gpu/spirv_shader_translator_rb.cc`; `src/xenia/gpu/vulkan/deferred_command_buffer.cc`; `src/xenia/gpu/vulkan/deferred_command_buffer.h`; `src/xenia/gpu/vulkan/vulkan_command_processor.cc`; `src/xenia/gpu/vulkan/vulkan_command_processor.h`; `src/xenia/gpu/vulkan/vulkan_occlusion_query_pool.cc`; `src/xenia/gpu/vulkan/vulkan_occlusion_query_pool.h`; `src/xenia/gpu/vulkan/vulkan_pipeline_cache.cc`; `src/xenia/ui/imgui_performance_dialog.cc`; `src/xenia/ui/imgui_performance_dialog.h`; `src/xenia/ui/vulkan/functions/device_ext_conditional_rendering.inc`; `src/xenia/ui/vulkan/vulkan_device.cc`; `src/xenia/ui/vulkan/vulkan_device.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### has207/xenia-edge #268 — Overflowed stackpoints! Crash

- Source: [https://github.com/has207/xenia-edge/issues/268](https://github.com/has207/xenia-edge/issues/268); created 2026-09-10T01:34:03Z; updated 2026-09-15T14:38:37Z; author `farenthy`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Stackpoint overflow is a JIT execution symptom; retain guest exception test idea, do not import code cache.
- Classification: useful research; emulator-specific; D applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-015**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### has207/xenia-edge #38 — Maybe implement XamSwapCancel

- Source: [https://github.com/has207/xenia-edge/issues/38](https://github.com/has207/xenia-edge/issues/38); created 2025-12-01T13:51:23Z; updated 2025-12-02T00:29:27Z; author `has207`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: XamSwapCancel matters only if a static title exercises disc transitions; include module/media lifecycle research.
- Classification: candidate for later port; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-017**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1111 — [GPU] VIZ_QUERY predication

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1111](https://github.com/xenia-canary/xenia-canary/pull/1111); created 2026-07-22T22:28:10Z; updated 2026-09-22T05:27:03Z; author `goldislead`.
- Upstream status: **pending upstream** (still open at the RG-GDK-010 review, 2026-09-24). PR head (not adopted) commit `78e06cafaa6429e5464786baa9e1edf252bbe582`.
- Scope / reason / applicability: WIP VIZ predication changes query lifecycle, host predicates and ROV counters; local visibility is still faked (every VIZ query reports visible).
- Classification: relevant but pending upstream; experimental; C/H applicability. **Not adopted.** RG-GDK-010 deferred VIZ to [#65](https://github.com/furqanagwan/rexglue-sdk/issues/65), gated on #1111 settling.
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #1077 — [GPU] Clamp depth to valid value if Inf is provided

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1077](https://github.com/xenia-canary/xenia-canary/pull/1077); created 2026-07-05T20:37:26Z; updated 2026-09-21T20:50:57Z; author `Gliniak`.
- Upstream status: **pending upstream**. PR head (not adopted) commit `dcd2fff24243b4d2d67c2d08a10d235f04f0de80`.
- Scope / reason / applicability: Depth Inf clamp author explicitly requests correctness research; do not adopt globally.
- Classification: experimental; game-specific; G/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-012**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/dxbc_shader_translator_fetch.cc`.
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #1182 — [Memory] Fix large-alignment physical allocs through offset-translated heaps

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1182](https://github.com/xenia-canary/xenia-canary/pull/1182); created 2026-08-27T20:26:17Z; updated 2026-08-27T20:27:26Z; author `shempman828`.
- Upstream status: **pending upstream** (still open 2026-09-24). PR head (not adopted) commit `fa6cdaae0f58e9161e5e41ea3683f837b3b112c7`.
- Scope / reason / applicability: makes vE0000000 virtual addresses aligned (an `alignment_phase` for the parent search) instead of physical ones; title 4D5307F1 failed a 0x280000-byte 32 KB-aligned request in Canary.
- Classification: relevant but pending upstream; B/H applicability. **Watch, not adopted (RG-GDK-004, 2026-09-24).** The 4D5307F1 request succeeds here with a 32 KB-aligned physical address, because there is no host alignment check to fail. Aligning the virtual address instead would move the physical address off the requested alignment, a global change with no title evidence here.
- Tests: `Physical heap vE0000000 aligns the physical address` records the current semantics (physical address aligned, virtual address 0x1000 below it) and the 4D5307F1 request size.

### xenia-canary/xenia-canary #1225 — [Kernel] Take back the signature a dying object left in guest memory

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1225](https://github.com/xenia-canary/xenia-canary/pull/1225); created 2026-09-10T15:48:02Z; updated 2026-09-12T21:42:06Z; author `peerloomllc`.
- Upstream status: **pending upstream**. PR head (not adopted) commit `fe960bf66f98204940a7464ed35b50ef5b7b4cdc`.
- Scope / reason / applicability: Guest object signature lifetime; maintainer requests root-cause research, Guitar Hero 5 DLC reproducer.
- Classification: relevant but pending upstream; blocked upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-014**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/kernel/xobject.cc`; `src/xenia/kernel/xobject.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1226 — [VFS] Bounds check the STFS reader

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1226](https://github.com/xenia-canary/xenia-canary/pull/1226); created 2026-09-10T15:48:14Z; updated 2026-09-12T21:51:16Z; author `peerloomllc`.
- Upstream status: **pending upstream**. PR head (not adopted) commit `c43ea0f9c3e3f3cac600a57d9f464a38c945d808`.
- Scope / reason / applicability: Truncated STFS package bounds; local parser exists but package-manager APIs differ.
- Classification: relevant but pending upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-017**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/kernel/xam/xcontent/xcontent_package_container.cc`; `src/xenia/vfs/devices/xcontent_devices/stfs_container_device.cc`; `src/xenia/vfs/devices/xcontent_devices/stfs_container_device.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1214 — [APU] Lock order inversion between UnregisterClient and the audio worker

- Source: [https://github.com/xenia-canary/xenia-canary/issues/1214](https://github.com/xenia-canary/xenia-canary/issues/1214); created 2026-09-05T18:49:02Z; updated 2026-09-05T18:49:02Z; author `peerloomllc`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Lock inversion report points to Edge 8aa50e0e0. Local locking differs; audit callback lifetime instead of copying locks.
- Classification: useful research; regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #1025 — [Kernel] Fixed use-after-free on title threads termination

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1025](https://github.com/xenia-canary/xenia-canary/pull/1025); created 2026-05-24T22:48:02Z; updated 2026-08-25T20:01:45Z; author `AdrianCassar`.
- Upstream status: **pending upstream**. PR head (not adopted) commit `abcf2ff1bea480cb6c4cdcafd2c09350826e01d3`.
- Scope / reason / applicability: Thread teardown/XEX swap UAF; static module lifecycle needs independent ownership design.
- Classification: relevant but pending upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-015**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/kernel/kernel_state.cc`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #748 — Fix audio quality: Use proper rounding in float to int16 conversion

- Source: [https://github.com/xenia-canary/xenia-canary/pull/748](https://github.com/xenia-canary/xenia-canary/pull/748); created 2025-10-19T11:50:50Z; updated 2026-08-25T20:01:45Z; author `tygyh`.
- Upstream status: **pending upstream**. PR head (not adopted) commit `a7f6514e699018674f5e3f56b437e4d9c58e7641`.
- Scope / reason / applicability: Scalar float→int16 rounding PR may miss SIMD path according to review; not a general audio-quality cure.
- Classification: useful research; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/apu/xma_context.cc`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #844 — [Config] Do not overwrite base config if game specific config is loaded

- Source: [https://github.com/xenia-canary/xenia-canary/pull/844](https://github.com/xenia-canary/xenia-canary/pull/844); created 2026-01-10T19:26:33Z; updated 2026-08-25T20:01:45Z; author `Gliniak`.
- Upstream status: **pending upstream**. PR head (not adopted) commit `16c13ed6ca60c20e4611e804216f78f5261c99ba`.
- Scope / reason / applicability: Prevent title configuration contaminating global config; profile design should test transition and persistence.
- Classification: relevant but pending upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-013**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/config.cc`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #608 — native stencil value output doesn't work on non-Arc Intel gpus like iris xe

- Source: [https://github.com/xenia-canary/xenia-canary/issues/608](https://github.com/xenia-canary/xenia-canary/issues/608); created 2025-05-01T05:44:27Z; updated 2025-05-01T05:44:27Z; author `D2firegit`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Intel non-Arc RTV stencil artifacts remain an open report; native stencil toggle is not proof of support.
- Classification: regression-related; vendor; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-006**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #1093 — 5451087D - UFC Undisputed 3: fighter meshes render as black collapsed triangles (memexport stream fails when guest physical heap is near-full)

- Source: [https://github.com/xenia-canary/xenia-canary/issues/1093](https://github.com/xenia-canary/xenia-canary/issues/1093); created 2026-07-15T15:43:59Z; updated 2026-07-15T22:20:11Z; author `cozycaston`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: UFC3 memexport/heap issue, Windows RTX 4070 Ti SUPER; comments distinguish stock and created fighters and Vulkan/D3D12.
- Classification: regression-related; game-specific; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-011**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.
- RG-GDK-011 review (2026-09-24): still open upstream with no merged fix in Canary or Edge for D3D12. The proposed clamp of each memexport stream to its committed allocation (issue comment) is not adopted: unmerged, and UFC Undisputed 3 isn't available to validate it. Locally a failed memexport `RequestRange` still drops the draw with an error rather than being widened or ignored. Near-full-heap memexport fixtures are RG-GDK-011 part 2.

### xenia-canary/xenia-canary #1127 — [GPU/DXBC] Fix signed round bias breaking memexport

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1127](https://github.com/xenia-canary/xenia-canary/pull/1127); created 2026-08-02T10:47:26Z; updated 2026-08-02T16:05:24Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `da47dfaacfae1134b238af9083a7f3d413c6cbbe`.
- Scope / reason / applicability: Signed memexport rounding destination error confirmed in both local sites.
- Classification: candidate for later port; relevant and merged upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-005**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/dxbc_shader_translator_memexport.cc`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1215 — [Memory] Round the AllocRange ceiling to the page, not to the alignment

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1215](https://github.com/xenia-canary/xenia-canary/pull/1215); created 2026-09-06T01:19:39Z; updated 2026-09-07T18:30:42Z; author `peerloomllc`; ported from xenia-edge `1ad151d1`.
- Upstream status: **merged upstream**. Merge commit `87c24112706d95f15f83dfec58e93923bd7ffa07`.
- Scope / reason / applicability: `BaseHeap::AllocRange` rounded `high_address` up to the alignment, so an allocation could end above the caller's ceiling, and a ceiling near `UINT32_MAX` wrapped to zero.
- Classification: correctness; B/H applicability. **Adopted 2026-09-24 in RG-GDK-004 (adapted).**
- Adaptation: the ceiling is no longer aligned. Canary rounds `high_page_number` up to the page because its free-block search treats it as exclusive (xenia-edge `4fcb8e449`); this repository still has the older search, which treats it as the last usable page, so the local port uses the last page ending at or below `high_address` instead. The upstream formula would allow one page above the ceiling here. For windows ending one byte below an alignment boundary, allocations whose size is a multiple of the alignment land where they did before (the Far Cry 3/4 and Watch Dogs layout concern in `4fcb8e449`).
- Tests: `tests/unit/memory/heap_allocation_test.cpp` AllocRange window cases (unaligned ceiling, inclusive page ceiling, exact fit top-down/bottom-up, `UINT32_MAX` ceiling, windows too small, Canary's physical-heap case, vE0000000 4K/32K/64K). Six of the seven cases fail on the previous code; the exact-fit case passes on both.
- Far Cry 3 or an equivalent physical-heap title was not run (no title content).

### xenia-canary/xenia-canary #1202 — [Memory] Check the host alignment PhysicalHeap can actually satisfy

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1202](https://github.com/xenia-canary/xenia-canary/pull/1202); created 2026-09-02T23:06:06Z; updated 2026-09-04T04:39:16Z; author `peerloomllc`.
- Upstream status: **closed unmerged**. PR head (not adopted) commit `1cc288bc71e625bd9272dafc2f1fb01259a62eb2`.
- Scope / reason / applicability: Closed unmerged: maintainer warns the alignment proposal changes poorly understood/unreachable checks, distinguishes AllocFixed, and names Far Cry 3 as a regression control. Keep separate from merged #1215 ceiling fix.
- Classification: useful research; rejected; B/H applicability. **Not adopted (RG-GDK-004, 2026-09-24): not applicable.** `PhysicalHeap::Alloc`/`AllocRange` here have no host alignment check at all; the caller's alignment is applied to the physical address by the parent heap, which is the semantics #1202 argues for. Covered by `Physical heap vE0000000 aligns the physical address`.

### xenia-canary/xenia-canary #1243 — [GPU] Misc guest texture layout edge cases

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1243](https://github.com/xenia-canary/xenia-canary/pull/1243); created 2026-09-22T07:40:19Z; updated 2026-09-22T17:46:24Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `c9c8e483b13249ba5f0060fc4b36071da6d67261`.
- Scope / reason / applicability: Array/volume mip layout, 96bpp pitch and 3D bounds differ locally; CPU fixtures plus texture readback.
- Classification: correctness; A/B applicability. **Adopted 2026-09-24 in RG-GDK-008.**
- Adaptation and validation owner: **RG-GDK-008**.
- Source files: `src/xenia/gpu/texture_util.cc`; `src/xenia/gpu/texture_util.h`.
- Commits: `94cb5e349f` array/volume mip layout (Edge `bc6b7a020`), `21543817f2` linear 96bpp mip row pitch (Edge `19da17403`), `19f5a08556` tiled 3D address bounds (not in Edge at `94de4f676`; taken from the PR head).
- Adaptation: applied unchanged to `src/graphics/pipeline/texture/util.cpp` and `include/rex/graphics/pipeline/texture/util.h`; no texture-cache lifetime change.
- Tests: `tests/unit/graphics/texture_layout_test.cpp` (`[texture_layout]`): hand-derived D3D offsets for 2D array, 3D and packed 3D mips and linear row pitches, plus a per-texel `GetTiledOffset2D/3D` oracle that the 2D/3D bounds must contain (and match exactly for whole 32x32x4 tiles). Every case except the whole-tile tightness check fails on the pre-port code.
- Regression evidence: none known upstream at adoption.

### xenia-canary/xenia-canary a635ac64f — [GPU] Scaled resolve readback through downscale CS

- Source: xenia-canary commit `a635ac64f5ca37c0b789e8b4166b53dc673b213f` (2026-07-06, `goldislead`), present in Edge at `94de4f676`.
- Classification: correctness; A/B applicability. **Partially adopted 2026-09-24 for #58.**
- Adopted: texel size from the resolve's normalized `copy_dest_info` (`draw_util::GetResolveDownscalePixelSizeLog2`, `Resolve(..., copy_dest_info_out)`), the source window at the written extent's scaled address instead of the scaled range start, and skipping 128bpp, unaligned and out-of-range extents.
- Not adopted: the shader's group layout. Canary reads the scaled layout introduced by `0f23f0568` (2026-01-13); this repository's resolve shaders are Canary `0b2ffa314` (2025-08-20; see the shader sources record below), which writes Nx1 units. `resolve_downscale.cs.hlsl` reverses the Nx1 layout instead. Reading the group layout passes at 2x but misplaces texels at 3x.
- Local changes: the extent is limited in dwords rather than truncated to whole 32x32 tiles, so a resolve ending inside a tile reads back completely. The HLSL shifts before masking because fxc 10.1 compiles `(a & mask(n + s)) >> s` into a `ubfe` of width `n + s`, which shifted 16bpp and 32bpp texels by one unit.
- Tests: `Resolve readback keeps texel positions` and `gpu.resolve_readback_scaled_3x2`; see `docs/regression-strategy.md`.
- Follow-up: syncing the resolve and texture-load shaders to Canary's current layout needs the downscale shader to move with them.

### xenia-canary/xenia-canary 0b2ffa314 — precompiled shader sources

- Source: xenia-canary commit `0b2ffa3143` (2025-08-20, "[GPU] Change texture load cbuffer to push constants"), `src/xenia/gpu/shaders` and `src/xenia/ui/shaders/xesl.xesli`, taken from the Edge clone.
- Classification: provenance; A applicability. **Adopted 2026-09-24 for RG-GDK-009.**
- Evidence: FXC 10.1 (Windows SDK 10.0.26100.0) with Canary's `xenia-build buildshaders` arguments rebuilds all 107 checked-in `src/graphics/shaders/bytecode/d3d12_5_1` headers that have sources byte for byte. The earlier `04d5c40d0` attribution matched the resolve shaders only; its texture-load shaders differ.
- Vendored: every `src/xenia/gpu/shaders` XeSL/HLSL source except `fxaa.cs.hlsl`, `fxaa_extreme.cs.hlsl` and `fxaa.hlsli`, which need `third_party/fxaa/FXAA3_11.h`; their bytecode stays as checked in. `src/ui/shaders/bytecode` sources are not vendored.
- Tooling: `scripts/build_shaders.py` builds the bytecode with the same arguments and clang-formats it; `--check` compares with the checked-in headers and runs as CTest `shaders.bytecode_reproducible` on Windows. `resolve_downscale_cs.h` is rebuilt with these arguments instead of `/O3` and the strip flags.
- Not adopted: Canary's later shader changes, including the `0f23f0568` scaled group layout; later ports edit these sources and rebuild.

### xenia-canary/xenia-canary #1240 — [GPU] Fix tiled resolve offsets below 32bpp

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1240](https://github.com/xenia-canary/xenia-canary/pull/1240); created 2026-09-21T04:23:51Z; updated 2026-09-21T04:50:35Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `89609297c7ae25dc5ba404c6a977260b806bb725`.
- Scope / reason / applicability: Sub-32bpp tiled resolve macro phase, title 534307D5 water; general addressing candidate.
- Classification: correctness; A/B applicability. **Adopted 2026-09-24 in RG-GDK-008.**
- Adaptation and validation owner: **RG-GDK-008**.
- Source files: `src/xenia/gpu/draw_util.cc` (Edge `89609297c`).
- Adaptation: applied unchanged to `GetResolveInfo` in `src/graphics/util/draw.cpp`.
- Tests: GPU fixture `Sub-32bpp resolve keeps the macro tile phase of the base` resolves 32x32 rectangles to k_8 (phase 0, 1, 3) and k_5_6_5 (phase 0, 1) bases and checks every byte of a 16 KB allocation against `GetTiledOffset2D`. Phase 1/3 cases fail on the pre-port code (every texel misplaced).
- Title 534307D5 (Golden Axe: Beast Rider) is not available locally; no title result is claimed.
- Regression evidence: none known upstream at adoption.

### xenia-canary/xenia-canary #1238 — [GPU] Fix 2x & 4x host depth copy sample layout

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1238](https://github.com/xenia-canary/xenia-canary/pull/1238); created 2026-09-19T19:47:34Z; updated 2026-09-20T16:40:37Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `0bd090dbe979bc64959efe519aa320db8e3eb467`.
- Scope / reason / applicability: 2x/4x depth copy sample layout repairs an AMD regression after canonical EDRAM; mandatory companion for #1163.
- Classification: regression fix; B/H applicability. **Adopted 2026-09-24 in RG-GDK-009.**
- Adaptation: `host_depth_store_2xmsaa.cs.xesl` and `host_depth_store_4xmsaa.cs.xesl` pass sample coordinates through the 1x path, in `XeEdramOffsetInts` units. The 4x change produces the same stores here: the shader addresses the buffer in 16-byte units, so the thread parity bit Canary's byte-addressed version added was already dropped.
- Tests: `MSAA float24 depth keeps host precision through an alias` (2x fails in 486 of 512 pixels without the 2x change).
- AMD not available locally; the AMD regression itself is not reproduced (non-blocking, ADR-007).

### xenia-canary/xenia-canary #1163 — [GPU] One canonical EDRAM layout

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1163](https://github.com/xenia-canary/xenia-canary/pull/1163); created 2026-08-20T03:08:53Z; updated 2026-08-26T17:05:59Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `437a7280cf95310d518a2f68087aab61403956ac`.
- Scope / reason / applicability: one canonical sample layout for 1x/2x/4x views of the same EDRAM (4x4 sample blocks, sample bit 0 horizontal, 2x sample 0 top); not independently safe, adopted together with #1238 and #1222.
- Classification: correctness; C/H applicability. **Adopted 2026-09-24 in RG-GDK-009.**
- Adaptation: shaders ported onto the vendored `0b2ffa314` sources (int-addressed EDRAM buffers instead of Canary's later byte addressing): `edram.xesli` remaps pixels and samples to canonical coordinates at guest pixel granularity; `resolve.xesli` and the full resolves load each sample by address; the fast resolves keep a vectorized path for 1x sources and load per pixel for MSAA, so they bind the EDRAM as a raw buffer (`draw_util::resolve_copy_shader_info`). The D3D12 transfer and dump shader generators and the ROV output (`dxbc_translator_om.cpp`) come from Canary's diff re-based on clang-formatted sources; Canary's per-target native scale (`source_scale_native`, `native_layout`, from `74db632ab`) doesn't exist here, so the layout scale is always the draw resolution scale. Adds `dxbc::Src::kXYXY`. Vulkan/SPIR-V parts not applicable (removed backend).
- Tests: `[edram]` GPU fixtures (1x/2x/4x re-aliasing in both directions, 64bpp as 32bpp at 1x/4x); all `[gpu]` fixtures at native, 3x2 and 2x2 scale on host RT and ROV. See `docs/regression-strategy.md`.
- Not covered: MSAA resolve averaging order (`k01` now averages horizontal samples), PWL gamma blend, titles 5841125E/4D5307F1.

### xenia-canary/xenia-canary #1222 — [GPU] EDRAM bits respected for color/depth aliases

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1222](https://github.com/xenia-canary/xenia-canary/pull/1222); created 2026-09-09T10:26:39Z; updated 2026-09-10T05:31:18Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `9da693480d0995326b81c3a14f8b1a4c226066eb`.
- Scope / reason / applicability: keep depth/stencil enabled when an aliased color target writes only bits the tests don't use; title 4D530A26 (clouds and sprites through geometry), possibly other UE3.5 titles.
- Classification: compatibility/correctness; B/H applicability. **Adopted 2026-09-24 in RG-GDK-009.**
- Adaptation: `RenderTargetCache::ColorOverlapsDepthStencil`, per-range `depth_bits_target`, `IsHostDepthCurrent` and read-only aliased depth for host render targets behind the new `aliased_depth_read_only` cvar (default true, as upstream); D3D12 ROV check in `UpdateSystemConstantValues_Impl`. Canary's `scale_native` key field is not present here and is omitted.
- Tests: `Color aliasing depth keeps a read-only depth test` (without the change 640 of 640 depth-failing pixels are written, host RT and ROV).
- Title 4D530A26 is not available locally; no title result is claimed.

### xenia-canary/xenia-canary #1218 — [GPU] ZPD as a running sample counter; QueryBatch support

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1218](https://github.com/xenia-canary/xenia-canary/pull/1218); created 2026-09-07T04:36:41Z; merged 2026-09-20T16:14:05Z; author `goldislead`. Head `be167dd9358f120dfb5562ba93c440a7b5bf9e2a`, merge commit `3d233a5b2e94b940825847b70c788951e364bb33` (parent `aee0871dd`). Reviewed 2026-09-24.
- Upstream status: **merged upstream**. No follow-up regression reports found at review time.
- Scope: each EVENT_WRITE_ZPD ends the interval since the previous one and queues a snapshot of a free-running counter (conventional BEGIN/END and QueryBatch alike); reports retire in stream order; host query segments split at submissions and draw-scale changes; slots are recycled with generation checks; fast modes write a visible-biased guess and correct it on retire; strict waits only for reports holding the D3D sentinel. Also binds an empty PS to RTV draws without a PS or depth/stencil writes, which D3D otherwise drops (4541096E, 5553083B).
- Classification: correctness; C/H applicability. **Adopted in RG-GDK-010 (D3D12 native-query subset).**
- Adaptation: the local path was an older sentinel-inferring BEGIN/END pair that ended the submission at END and fell back to 1000 fake samples whenever the fence had not passed, which on a real GPU was nearly always. Replaced by `XenosZPDReport` (`include/rex/graphics/xenos_zpd_report.h`), the shared state machine in `CommandProcessor` and `D3D12ZPDQueryPool` (`src/graphics/d3d12/zpd_query_pool.cpp`). `PipelineCache::AwaitPipelineCompletion` ported for strict waits behind async pipeline creation. New `occlusion_query` cvar (`fake`/`fast`/`fast-alt`/`strict`, default `fast`); `occlusion_query_enable=false` still forces fake and `query_occlusion_fake_sample_count` (1000) is the per-interval fake delta instead of Canary's 80–100 walk. No draw-resolution-scale threshold exists locally, so segments use the texture cache scale.
- Not ported: in-shader counting for the ROV path and `occlusion_query_full_counters` (ZFail/StencilFail/Total) — the ROV path falls back to fake results at its first draw and ZFail/StencilFail stay zero; tracked in [#64](https://github.com/furqanagwan/rexglue-sdk/issues/64). Vulkan/SPIR-V parts are not applicable. `occlusion_query_saturation` (Edge #143) is not revived.
- Validation: `unit_tests [zpd]` (lane split, 32-bit wrap, scale normalization, write order) and `gpu_tests [zpd]` — conventional BEGIN/END, QueryBatch with empty intervals, depth-rejected samples, segments across submissions, reused report memory with recycled host slots (96 queries), a PS-less no-write draw, 4x MSAA, fast-mode guess then correction, and fake mode — on NVIDIA (0x10DE, driver 32.0.16.1714) at 1x and 3x2 draw resolution scale and on WARP. The PS-less case reads 0 samples on both NVIDIA and WARP without the empty-PS binding. MSAA counts host samples as Canary does; console behaviour is not verified. AMD/Intel, the ROV path and Crackdown 2 (no title content) are not run.
- Source files: `src/xenia/gpu/command_processor.cc`; `src/xenia/gpu/command_processor.h`; `src/xenia/gpu/d3d12/d3d12_command_processor.cc`; `src/xenia/gpu/d3d12/d3d12_command_processor.h`; `src/xenia/gpu/d3d12/d3d12_zpd_query_pool.cc`; `src/xenia/gpu/d3d12/d3d12_zpd_query_pool.h`; `src/xenia/gpu/d3d12/pipeline_cache.cc`; `src/xenia/gpu/d3d12/pipeline_cache.h`; `src/xenia/gpu/pm4_command_processor_implement.h`; `src/xenia/gpu/xenos_zpd_report.h` (ported); DXBC translator, `gpu_flags` full-counter cvar and all Vulkan/SPIR-V files (not ported).
- Regression evidence: none known upstream at review time; local fixtures above.

### xenia-canary/xenia-canary #1016 — [GPU] Implement ZPD occlusion queries

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1016](https://github.com/xenia-canary/xenia-canary/pull/1016); created 2026-05-16T14:59:45Z; updated 2026-05-30T17:26:26Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `fbd620c22b44638b66a70bba80d6f30d55a10924`.
- Scope / reason / applicability: Original ZPD implementation is historical context, superseded by running counters.
- Classification: useful research; relevant and merged upstream; C/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-010**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/command_processor.cc`; `src/xenia/gpu/command_processor.h`; `src/xenia/gpu/d3d12/d3d12_command_processor.cc`; `src/xenia/gpu/d3d12/d3d12_command_processor.h`; `src/xenia/gpu/d3d12/d3d12_zpd_query_pool.cc`; `src/xenia/gpu/d3d12/d3d12_zpd_query_pool.h`; `src/xenia/gpu/d3d12/deferred_command_list.cc`; `src/xenia/gpu/d3d12/deferred_command_list.h`; `src/xenia/gpu/d3d12/pipeline_cache.cc`; `src/xenia/gpu/d3d12/pipeline_cache.h`; `src/xenia/gpu/dxbc.h`; `src/xenia/gpu/dxbc_shader_translator.cc`; `src/xenia/gpu/dxbc_shader_translator.h`; `src/xenia/gpu/dxbc_shader_translator_om.cc`; `src/xenia/gpu/gpu_flags.cc`; `src/xenia/gpu/gpu_flags.h`; `src/xenia/gpu/pm4_command_processor_implement.h`; `src/xenia/gpu/spirv_shader_translator.cc`; `src/xenia/gpu/spirv_shader_translator.h`; `src/xenia/gpu/spirv_shader_translator_rb.cc`; `src/xenia/gpu/vulkan/deferred_command_buffer.cc`; `src/xenia/gpu/vulkan/deferred_command_buffer.h`; `src/xenia/gpu/vulkan/vulkan_command_processor.cc`; `src/xenia/gpu/vulkan/vulkan_command_processor.h`; `src/xenia/gpu/vulkan/vulkan_pipeline_cache.cc`; `src/xenia/gpu/vulkan/vulkan_pipeline_cache.h`; `src/xenia/gpu/vulkan/vulkan_zpd_query_pool.cc`; `src/xenia/gpu/vulkan/vulkan_zpd_query_pool.h`; `src/xenia/gpu/xenos_zpd_report.h`; `src/xenia/ui/vulkan/functions/device_1_0.inc`; `src/xenia/ui/vulkan/functions/device_1_2_ext_host_query_reset.inc`; `src/xenia/ui/vulkan/vulkan_device.cc`; `src/xenia/ui/vulkan/vulkan_device.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1058 — [GPU] Rolls back ZPD cache erasure on guest BEGIN. Only affects kFast.

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1058](https://github.com/xenia-canary/xenia-canary/pull/1058); created 2026-06-19T02:37:42Z; updated 2026-06-19T06:02:34Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `d55670e40b1016cc36cca5111c821b3e7c9a85b8`.
- Scope / reason / applicability: Fast ZPD cache-erasure rollback shows why original query port must include later corrections.
- Classification: regression-related; B/H applicability. Its behaviour is kept by the RG-GDK-010 port of #1218: the fast-mode per-address delta cache is never erased on a guest BEGIN (there is no BEGIN state any more), only capped at 1024 entries.
- Source files: `src/xenia/gpu/command_processor.cc`.
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #1190 — [GPU] Replace AC6 ground hack with scalar approximation rounding

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1190](https://github.com/xenia-canary/xenia-canary/pull/1190); created 2026-08-29T06:31:47Z; updated 2026-08-31T20:07:05Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `3a44f20c7bc66db1da583e8a6f0ab740e31908e9`.
- Scope / reason / applicability: AC6 workaround replaced with scalar approximation; numerical semantics before a title gate.
- Classification: candidate for later port; relevant and merged upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-012**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/dxbc_shader_translator.h`; `src/xenia/gpu/dxbc_shader_translator_alu.cc`; `src/xenia/gpu/dxbc_shader_translator_fetch.cc`; `src/xenia/gpu/gpu_flags.cc`; `src/xenia/gpu/gpu_flags.h`; `src/xenia/gpu/shader_interpreter.cc`; `src/xenia/gpu/shader_interpreter.h`; `src/xenia/gpu/spirv_shader_translator.h`; `src/xenia/gpu/spirv_shader_translator_alu.cc`; `src/xenia/gpu/spirv_shader_translator_fetch.cc`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1031 — [GPU] Remove ac6_ground_fix - nudge rcp up slightly instead

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1031](https://github.com/xenia-canary/xenia-canary/pull/1031); created 2026-05-26T22:42:05Z; updated 2026-09-01T09:10:47Z; author `oreyg`.
- Upstream status: **closed unmerged**. PR head (not adopted) commit `93e3fa59b040f124f0343a80b90f2d0b53b125fc`.
- Scope / reason / applicability: Earlier AC6 workaround-removal approach; status must not be conflated with merged #1190.
- Classification: useful research; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-012**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/dxbc_shader_translator.h`; `src/xenia/gpu/dxbc_shader_translator_alu.cc`; `src/xenia/gpu/dxbc_shader_translator_fetch.cc`; `src/xenia/gpu/gpu_flags.cc`; `src/xenia/gpu/gpu_flags.h`; `src/xenia/gpu/spirv_shader_translator.h`; `src/xenia/gpu/spirv_shader_translator_alu.cc`; `src/xenia/gpu/spirv_shader_translator_fetch.cc`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1180 — [Memory/GPU/Kernel] Initial XPS Support

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1180](https://github.com/xenia-canary/xenia-canary/pull/1180); created 2026-08-27T07:20:41Z; updated 2026-08-30T07:05:50Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `22708301ba76d10aae6f7d7caac8b1cac9e4a8e6`.
- Scope / reason / applicability: XPS memory/GPU/kernel support crosses ABI boundaries; no bulk subsystem replacement.
- Classification: useful research; redesign; C/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-004**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/d3d12/d3d12_command_processor.cc`; `src/xenia/gpu/dxbc_shader_translator_fetch.cc`; `src/xenia/gpu/pm4_command_processor_implement.h`; `src/xenia/gpu/shader_interpreter.cc`; `src/xenia/gpu/spirv_shader_translator_fetch.cc`; `src/xenia/gpu/vulkan/vulkan_command_processor.cc`; `src/xenia/kernel/xboxkrnl/xboxkrnl_memory.cc`; `src/xenia/memory.cc`; `src/xenia/memory.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1195 — [GPU] Publish the ring read pointer write-back every 8 packets, not once per burst

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1195](https://github.com/xenia-canary/xenia-canary/pull/1195); created 2026-08-30T04:48:12Z; updated 2026-08-30T12:49:05Z; author `peerloomllc`.
- Upstream status: **closed unmerged**. PR head (not adopted) commit `ab349b475d4d82dd2a4330b2e2eb46332006afce`.
- Scope / reason / applicability: Ring read-pointer publication cadence differs from Edge RB_BLKSZ approach; test guest-visible progress.
- Classification: candidate for later port; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-011**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/pm4_command_processor_implement.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.
- RG-GDK-011 decision (2026-09-24): not adopted; the Edge RB_BLKSZ version (29fcaeac3) was ported instead, publishing at the guest-programmed block size rather than every 8 packets.

### xenia-canary/xenia-canary #1227 — [Kernel] Reconcile the guest dispatch header on native object lookup

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1227](https://github.com/xenia-canary/xenia-canary/pull/1227); created 2026-09-10T20:22:20Z; updated 2026-09-13T20:21:27Z; author `Gliniak`.
- Upstream status: **merged upstream**. Merge commit `dcf2994ea1d604e841b5553b2bf941b809e36e79`.
- Scope / reason / applicability: Sync guest dispatcher headers and host event/semaphore state; handle-reuse and wait races require adaptation.
- Classification: candidate for later port; relevant and merged upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-014**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/kernel/xevent.cc`; `src/xenia/kernel/xevent.h`; `src/xenia/kernel/xobject.cc`; `src/xenia/kernel/xobject.h`; `src/xenia/kernel/xsemaphore.cc`; `src/xenia/kernel/xsemaphore.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1216 — [XAM] Fixed writing to packages via XamContentFlush

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1216](https://github.com/xenia-canary/xenia-canary/pull/1216); created 2026-09-06T20:19:59Z; updated 2026-09-08T18:09:50Z; author `Gliniak`.
- Upstream status: **merged upstream**. Merge commit `5d4dc8a88abb2965f2933286571f5bfa0b87391d`.
- Scope / reason / applicability: Local XamContentFlush returns success without flushing; persistence contract missing.
- Classification: candidate for later port; relevant and merged upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-017**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/kernel/xam/content_manager.cc`; `src/xenia/kernel/xam/content_manager.h`; `src/xenia/kernel/xam/xam_content.cc`; `src/xenia/kernel/xam/xcontent/xcontent_package.h`; `src/xenia/kernel/xam/xcontent/xcontent_package_container.h`; `src/xenia/kernel/xam/xcontent/xcontent_package_directory.cc`; `src/xenia/kernel/xam/xcontent/xcontent_package_directory.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1135 — [XAM] Deliver initial XMP state snapshot to new notification listeners

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1135](https://github.com/xenia-canary/xenia-canary/pull/1135); created 2026-08-04T18:31:43Z; updated 2026-08-25T22:50:53Z; author `jman9511`.
- Upstream status: **closed unmerged**. PR head (not adopted) commit `421498c3b38257f98efb043f438b8e28ebf951c9`.
- Scope / reason / applicability: Closed unmerged initial XMP notification proposal, Black Ops II; do not assume universal boot notification semantics.
- Classification: useful research; game-specific; G/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-017**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/kernel/xam/xam_notify.cc`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #981 — [XAM] Add mutex for properties vector

- Source: [https://github.com/xenia-canary/xenia-canary/pull/981](https://github.com/xenia-canary/xenia-canary/pull/981); created 2026-04-25T16:43:47Z; updated 2026-08-25T20:01:45Z; author `AdrianCassar`.
- Upstream status: **pending upstream**. PR head (not adopted) commit `555e9a4a456d2a6d80a8811486208f82095fcfe9`.
- Scope / reason / applicability: Profile properties mutex; local profile lifetime and thread-safety audit required.
- Classification: relevant but pending upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-017**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/kernel/xam/user_profile.h`; `src/xenia/kernel/xam/user_tracker.cc`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #5 — UserProfile thread-safety (or lack thereof)

- Source: [https://github.com/xenia-canary/xenia-canary/issues/5](https://github.com/xenia-canary/xenia-canary/issues/5); created 2020-01-09T18:16:36Z; updated 2020-02-23T17:12:45Z; author `emoose`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Longstanding UserProfile thread safety; test concurrent read/write and shutdown.
- Classification: useful research; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-017**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1220 — Player 2 profile save data lost after crash, but persists through normal restart (Army of Two: The 40th Day)

- Source: [https://github.com/xenia-canary/xenia-canary/issues/1220](https://github.com/xenia-canary/xenia-canary/issues/1220); created 2026-09-08T18:31:00Z; updated 2026-09-08T18:36:48Z; author `iceman24895-ui`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Army of Two player-2 profile lost after crash; crash persistence fixture, not a claimed local bug.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-017**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #1036 — Regression affecting Koei Warriors games - voice line hang/crash

- Source: [https://github.com/xenia-canary/xenia-canary/issues/1036](https://github.com/xenia-canary/xenia-canary/issues/1036); created 2026-05-31T07:54:39Z; updated 2026-06-10T03:59:39Z; author `MaNE-17`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Koei voice-line hang/crash; separate decode, pacing and callback order regressions.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #600 — Xenia freezes when no audio device is enabled or usable on the system.

- Source: [https://github.com/xenia-canary/xenia-canary/issues/600](https://github.com/xenia-canary/xenia-canary/issues/600); created 2025-04-25T08:39:21Z; updated 2026-01-28T07:02:43Z; author `hourai-branch`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: No usable audio device must not freeze title execution; audio sink recovery case.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-019**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #438 — DJ Hero 2 - Song stems other than the first one are completely broken.

- Source: [https://github.com/xenia-canary/xenia-canary/issues/438](https://github.com/xenia-canary/xenia-canary/issues/438); created 2024-11-30T03:30:58Z; updated 2024-11-30T03:30:58Z; author `portalsam1`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: DJ Hero 2 multistream XMA stems; representative decoder workload.
- Classification: game-specific; useful research; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #739 — Sound quality is low/compressed

- Source: [https://github.com/xenia-canary/xenia-canary/issues/739](https://github.com/xenia-canary/xenia-canary/issues/739); created 2025-10-11T11:26:32Z; updated 2025-10-21T06:02:35Z; author `RostovShev03`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Audio quality complaint needs PCM comparisons; scalar-only #748 may not address it.
- Classification: useful research; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #872 — [BUG] win32_high_resolution_timer when false is not honored and is instead force enabled to an extremely agressive 0.5ms

- Source: [https://github.com/xenia-canary/xenia-canary/issues/872](https://github.com/xenia-canary/xenia-canary/issues/872); created 2026-02-04T16:00:54Z; updated 2026-02-05T04:56:41Z; author `chrcoluk`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Windows timer resolution flag not honored; measure native wait/timer behavior.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-015**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #773 — [Aggregate Issue] - Regressions

- Source: [https://github.com/xenia-canary/xenia-canary/issues/773](https://github.com/xenia-canary/xenia-canary/issues/773); created 2025-11-08T23:26:10Z; updated 2026-02-15T16:31:57Z; author `The-Little-Wolf`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Aggregate regression index is an ongoing watch source, not a duplicate-all backlog.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-026**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #754 — [Aggregate Issue] - Unimplemented Kernel Functions

- Source: [https://github.com/xenia-canary/xenia-canary/issues/754](https://github.com/xenia-canary/xenia-canary/issues/754); created 2025-10-28T23:01:15Z; updated 2026-09-12T18:44:49Z; author `The-Little-Wolf`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Missing kernel exports: intersect with actual ReXGlue imports; never add success stubs just to boot.
- Classification: useful research; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-014**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1230 — [HID/SDL] controller_subtypes, and a guitar's whammy read as held down

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1230](https://github.com/xenia-canary/xenia-canary/pull/1230); created 2026-09-11T04:42:03Z; updated 2026-09-12T21:42:53Z; author `peerloomllc`.
- Upstream status: **pending upstream**. PR head (not adopted) commit `ef97e8a70f4f0d0fffa2736789670f6f8164d055`.
- Scope / reason / applicability: Guitar subtype/whammy reporting influences GameInput-to-guest mapping even though upstream patch is SDL.
- Classification: relevant but pending upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-020**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/hid/input.h`; `src/xenia/hid/sdl/sdl_input_driver.cc`; `src/xenia/hid/sdl/sdl_input_driver.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1109 — [XAM] Resolve directory-backed package payloads

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1109](https://github.com/xenia-canary/xenia-canary/pull/1109); created 2026-07-22T00:10:53Z; updated 2026-08-25T20:01:44Z; author `jaypfe`.
- Upstream status: **pending upstream**. PR head (not adopted) commit `95f9f68817c9828ba3a28c144916d45d34d44bd1`.
- Scope / reason / applicability: Directory-backed package payload lookup; local extracted content and STFS coexist.
- Classification: relevant but pending upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-017**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/kernel/xam/content_manager.cc`; `src/xenia/kernel/xam/content_manager.h`; `src/xenia/kernel/xam/xam_content.cc`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1038 — [APU] Pace audio subsystem

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1038](https://github.com/xenia-canary/xenia-canary/pull/1038); created 2026-06-02T09:59:22Z; updated 2026-07-08T17:24:33Z; author `oreyg`.
- Upstream status: **merged upstream**. Merge commit `6e5b8324f4101464de0f8c2334edb03cac8826c4`.
- Scope / reason / applicability: Audio pacing helps IdolMaster 2/Madden 06, but review reports missing audio in Shaun White Skateboarding and Way of the Samurai 3 freezes/crashes with multiple clients.
- Classification: regression-related; relevant and merged upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/apu/audio_system.cc`; `src/xenia/apu/audio_system.h`; `src/xenia/base/threading.h`; `src/xenia/base/threading_posix.cc`; `src/xenia/base/threading_win.cc`.
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #1029 — [APU] XmaDecoder: do not block in WriteRegister

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1029](https://github.com/xenia-canary/xenia-canary/pull/1029); created 2026-05-26T08:53:00Z; updated 2026-06-01T18:41:44Z; author `oreyg`.
- Upstream status: **closed unmerged**. PR head (not adopted) commit `a6e1a418f33efb87126ba1ffde2b0b536818170a`.
- Scope / reason / applicability: Closed unmerged: author withdrew nonblocking WriteRegister change pending a better case. Do not mistake closure for adoption.
- Classification: useful research; rejected; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/apu/xma_decoder.cc`.
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #1134 — d119505_canary_experimental update after error message and crash

- Source: [https://github.com/xenia-canary/xenia-canary/issues/1134](https://github.com/xenia-canary/xenia-canary/issues/1134); created 2026-08-04T17:14:17Z; updated 2026-08-05T01:50:05Z; author `stimpack7`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Windows D3D12 device loss reported on GTX 1660 SUPER driver 596.36: e45c25c good, d119505 bad; FIFA 13–19/NFS Hot Pursuit.
- Classification: regression-related; vendor; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-006**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### xenia-canary/xenia-canary #1131 — [GPU] Edge backports, part I

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1131](https://github.com/xenia-canary/xenia-canary/pull/1131); created 2026-08-03T18:14:23Z; updated 2026-08-04T08:34:43Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `0f2980de442341788c07b282d6fbd6dc689166de`.
- Scope / reason / applicability: Edge backport bundle combines Vulkan parity and shared depth behavior; split host-inappropriate pieces from D3D12 semantic candidates.
- Classification: useful research; relevant and merged upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-012**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/d3d12/d3d12_command_processor.cc`; `src/xenia/gpu/d3d12/d3d12_command_processor.h`; `src/xenia/gpu/d3d12/d3d12_texture_cache.cc`; `src/xenia/gpu/d3d12/d3d12_texture_cache.h`; `src/xenia/gpu/d3d12/pipeline_cache.cc`; `src/xenia/gpu/d3d12/pipeline_cache.h`; `src/xenia/gpu/draw_util.cc`; `src/xenia/gpu/draw_util.h`; `src/xenia/gpu/dxbc.h`; `src/xenia/gpu/dxbc_shader_translator.cc`; `src/xenia/gpu/dxbc_shader_translator.h`; `src/xenia/gpu/dxbc_shader_translator_fetch.cc`; `src/xenia/gpu/dxbc_shader_translator_om.cc`; `src/xenia/gpu/spirv_compatibility.h`; `src/xenia/gpu/spirv_shader_translator.cc`; `src/xenia/gpu/spirv_shader_translator.h`; `src/xenia/gpu/spirv_shader_translator_fetch.cc`; `src/xenia/gpu/spirv_shader_translator_rb.cc`; `src/xenia/gpu/texture_cache.cc`; `src/xenia/gpu/texture_cache.h`; `src/xenia/gpu/texture_util.cc`; `src/xenia/gpu/vulkan/vulkan_command_processor.cc`; `src/xenia/gpu/vulkan/vulkan_command_processor.h`; `src/xenia/gpu/vulkan/vulkan_pipeline_cache.cc`; `src/xenia/gpu/vulkan/vulkan_pipeline_cache.h`; `src/xenia/gpu/vulkan/vulkan_render_target_cache.cc`; `src/xenia/gpu/vulkan/vulkan_render_target_cache.h`; `src/xenia/gpu/vulkan/vulkan_texture_cache.cc`; `src/xenia/gpu/vulkan/vulkan_texture_cache.h`; `src/xenia/gpu/xenos.cc`; `src/xenia/ui/vulkan/vulkan_device.cc`; `src/xenia/ui/vulkan/vulkan_device.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### xenia-canary/xenia-canary #1147 — [GPU/Memory] Edge backports, part 2

- Source: [https://github.com/xenia-canary/xenia-canary/pull/1147](https://github.com/xenia-canary/xenia-canary/pull/1147); created 2026-08-10T06:55:59Z; updated 2026-08-18T06:32:24Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `7cd47947b07de30b649fb4224418a659890eab73`.
- Scope / reason / applicability: Edge backports include memory invalidation/read watches and DXBC counterparts; prerequisite research for memexport, not wholesale Vulkan adoption.
- Classification: useful research; relevant and merged upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-011**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/d3d12/d3d12_command_processor.cc`; `src/xenia/gpu/d3d12/d3d12_texture_cache.cc`; `src/xenia/gpu/d3d12/d3d12_texture_cache.h`; `src/xenia/gpu/dxbc_shader_translator.h`; `src/xenia/gpu/dxbc_shader_translator_fetch.cc`; `src/xenia/gpu/dxbc_shader_translator_memexport.cc`; `src/xenia/gpu/dxbc_shader_translator_om.cc`; `src/xenia/gpu/primitive_processor.cc`; `src/xenia/gpu/primitive_processor.h`; `src/xenia/gpu/render_target_cache.cc`; `src/xenia/gpu/shared_memory.cc`; `src/xenia/gpu/spirv_shader_translator.cc`; `src/xenia/gpu/spirv_shader_translator.h`; `src/xenia/gpu/spirv_shader_translator_alu.cc`; `src/xenia/gpu/spirv_shader_translator_fetch.cc`; `src/xenia/gpu/spirv_shader_translator_memexport.cc`; `src/xenia/gpu/spirv_shader_translator_rb.cc`; `src/xenia/gpu/texture_cache.cc`; `src/xenia/gpu/texture_cache.h`; `src/xenia/gpu/vulkan/vulkan_command_processor.cc`; `src/xenia/gpu/vulkan/vulkan_command_processor.h`; `src/xenia/gpu/vulkan/vulkan_pipeline_cache.cc`; `src/xenia/gpu/vulkan/vulkan_pipeline_cache.h`; `src/xenia/gpu/vulkan/vulkan_render_target_cache.cc`; `src/xenia/gpu/vulkan/vulkan_texture_cache.cc`; `src/xenia/gpu/vulkan/vulkan_texture_cache.h`; `src/xenia/gpu/xenos.h`; `src/xenia/memory.cc`; `src/xenia/memory.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### has207/xenia-edge #276 — 4E4D083D - Soulcalibur V Texture Bug

- Source: [https://github.com/has207/xenia-edge/issues/276](https://github.com/has207/xenia-edge/issues/276); created 2026-09-19T04:18:28Z; updated 2026-09-20T13:38:18Z; author `Satumariko`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Soulcalibur V color/pattern corruption; comments separate async shader artifacts from blue speckles across RTV/ROV/FBO versus FSI. No local diagnosis proved.
- Classification: game-specific; useful research; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-011**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### has207/xenia-edge #280 — 4B4E081A Otomedius Excellent background glitch

- Source: [https://github.com/has207/xenia-edge/issues/280](https://github.com/has207/xenia-edge/issues/280); created 2026-09-22T03:52:28Z; updated 2026-09-22T07:49:27Z; author `Satumariko`.
- Upstream status: **open report**. Commit not identified for this report.
- Scope / reason / applicability: Otomedius Excellent ocean background oscillation also reported in Canary; camera-matrix cause is a reporter hypothesis, not established.
- Classification: game-specific; useful research; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-026**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### has207/xenia-edge #127 — [GPU] Rewrite hardware occlusion (ZPD) implementation

- Source: [https://github.com/has207/xenia-edge/pull/127](https://github.com/has207/xenia-edge/pull/127); created 2026-03-20T04:12:53Z; updated 2026-04-05T14:15:44Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `397fc9284178b7626e77642c6ea24bfa69a620a8`.
- Scope / reason / applicability: Historical ZPD lifecycle rewrite, followed by more corrections; prefer current running-counter design review rather than this snapshot alone.
- Classification: useful research; relevant and merged upstream; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-010**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/command_processor.cc`; `src/xenia/gpu/command_processor.h`; `src/xenia/gpu/d3d12/d3d12_command_processor.cc`; `src/xenia/gpu/d3d12/d3d12_command_processor.h`; `src/xenia/gpu/d3d12/d3d12_zpd_query_pool.cc`; `src/xenia/gpu/d3d12/d3d12_zpd_query_pool.h`; `src/xenia/gpu/d3d12/pipeline_cache.cc`; `src/xenia/gpu/d3d12/pipeline_cache.h`; `src/xenia/gpu/gpu_flags.cc`; `src/xenia/gpu/gpu_flags.h`; `src/xenia/gpu/pm4_command_processor_implement.h`; `src/xenia/gpu/vulkan/vulkan_command_processor.cc`; `src/xenia/gpu/vulkan/vulkan_command_processor.h`; `src/xenia/gpu/vulkan/vulkan_pipeline_cache.cc`; `src/xenia/gpu/vulkan/vulkan_pipeline_cache.h`; `src/xenia/gpu/vulkan/vulkan_zpd_query_pool.cc`; `src/xenia/gpu/vulkan/vulkan_zpd_query_pool.h`; `src/xenia/gpu/xenos_report_controller.cc`; `src/xenia/gpu/xenos_report_controller.h`; `src/xenia/gpu/xenos_zpd_report.h`; `src/xenia/ui/config_helpers.h`; `src/xenia/ui/imgui_performance_dialog.cc`; `src/xenia/ui/imgui_performance_dialog.h`; `src/xenia/ui/vulkan/functions/device_1_2_ext_host_query_reset.inc`; `src/xenia/ui/vulkan/vulkan_device.cc`; `src/xenia/ui/vulkan/vulkan_device.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### has207/xenia-edge #143 — [GPU] Add a query sample count saturation cvar for flare tuning

- Source: [https://github.com/has207/xenia-edge/pull/143](https://github.com/has207/xenia-edge/pull/143); created 2026-04-20T00:52:28Z; updated 2026-04-21T05:06:55Z; author `goldislead`.
- Upstream status: **merged upstream**. Merge commit `c9a6327ad136f82920df547afc9e552424b863ac`.
- Scope / reason / applicability: Merged empirical sample-count saturation tuning was later removed by running-counter work; do not restore a universal 0.9 multiplier.
- Classification: useful research; obsolete workaround; G/H applicability. **Not adopted**: Canary #1218 removed `occlusion_query_saturation` and RG-GDK-010 ported #1218 without it.
- Source files: `src/xenia/gpu/gpu_flags.cc`; `src/xenia/gpu/gpu_flags.h`; `src/xenia/gpu/xenos_zpd_report.h`.
- Regression evidence: Unknown/not established for ReXGlue. Run the issue-specific regression suite and relevant vendor cases.

### has207/xenia-edge #145 — [GPU] Tune strict ZPD retirement and add optional fast ZPD path

- Source: [https://github.com/has207/xenia-edge/pull/145](https://github.com/has207/xenia-edge/pull/145); created 2026-04-23T14:02:40Z; updated 2026-04-23T15:21:34Z; author `goldislead`.
- Upstream status: **closed unmerged**. PR head (not adopted) commit `5d31dea2343fcd60973e17bb89fe0851cca2e1fc`.
- Scope / reason / applicability: Closed unmerged strict/fast tuning; proposal itself notes opt-in report trust regresses some games.
- Classification: experimental; rejected; G/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-010**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/command_processor.cc`; `src/xenia/gpu/command_processor.h`; `src/xenia/gpu/d3d12/d3d12_command_processor.cc`; `src/xenia/gpu/d3d12/d3d12_command_processor.h`; `src/xenia/gpu/gpu_flags.cc`; `src/xenia/gpu/gpu_flags.h`; `src/xenia/gpu/vulkan/vulkan_command_processor.cc`; `src/xenia/gpu/vulkan/vulkan_command_processor.h`.
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #194 — [GPU] ROV ZPD - Reduces counter atomic pressure

- Source: [https://github.com/has207/xenia-edge/pull/194](https://github.com/has207/xenia-edge/pull/194); created 2026-06-25T02:25:10Z; updated 2026-06-25T06:01:55Z; author `goldislead`.
- Upstream status: **closed unmerged**. PR head (not adopted) commit `9376b083bf8937a1bbc6fbff31cecc4c773a2c30`.
- Scope / reason / applicability: Closed unmerged ROV atomic-pressure optimization; no accepted SPIR-V counterpart established here.
- Classification: useful research; rejected; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-010**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: `src/xenia/gpu/hlsl_shader_translator.cc`.
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #164 — [Regression] Dark Souls broken audio & hangs in menu after release 8aa50e0

- Source: [https://github.com/has207/xenia-edge/issues/164](https://github.com/has207/xenia-edge/issues/164); created 2026-05-14T08:29:01Z; updated 2026-05-16T13:06:33Z; author `shinra-electric`.
- Upstream status: **closed report**. Commit not identified for this report.
- Scope / reason / applicability: Dark Souls audio/menu hangs: 3341c7a good, 8aa50e0 bad; reporter later confirms recovery. Review actual follow-up before adapting lifetime fix.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #107 — Audio regression in Shin Sangoku Musou 4 Special

- Source: [https://github.com/has207/xenia-edge/issues/107](https://github.com/has207/xenia-edge/issues/107); created 2026-02-17T13:12:06Z; updated 2026-04-16T03:49:05Z; author `QtFun`.
- Upstream status: **closed report**. Commit not identified for this report.
- Scope / reason / applicability: Shin Sangoku Musou 4 Special audio closed as fixed; comments distinguish decoder recovery from separate Koei dialogue crashes.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #111 — Midnight Club: Los Angeles audio regression

- Source: [https://github.com/has207/xenia-edge/issues/111](https://github.com/has207/xenia-edge/issues/111); created 2026-02-21T03:14:45Z; updated 2026-02-21T14:41:32Z; author `MS-64`.
- Upstream status: **closed report**. Commit not identified for this report.
- Scope / reason / applicability: Midnight Club LA audio recovery reported; SCDA still had dedicated-thread/BGM issues. Different title outcomes must remain separate.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #113 — Splinter Cell: Double Agent - Big sound regressions

- Source: [https://github.com/has207/xenia-edge/issues/113](https://github.com/has207/xenia-edge/issues/113); created 2026-02-21T19:36:27Z; updated 2026-02-22T07:51:39Z; author `TGP482`.
- Upstream status: **closed report**. Commit not identified for this report.
- Scope / reason / applicability: SCDA music/dialogue stops and scene softlock after 5376439; keep dedicated-XMA-thread settings in reproduction.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

### has207/xenia-edge #120 — 007 Legends - Audio regression

- Source: [https://github.com/has207/xenia-edge/issues/120](https://github.com/has207/xenia-edge/issues/120); created 2026-02-27T19:29:38Z; updated 2026-03-02T10:25:03Z; author `TGP482`.
- Upstream status: **closed report**. Commit not identified for this report.
- Scope / reason / applicability: 007 Legends buzzing/muting after c3d1d3d; reporter confirmed later recovery. Preserve menu and resume-game regression scenes.
- Classification: regression-related; B/H applicability. No adoption by this documentation change.
- Adaptation and validation owner: **RG-GDK-018**, whose complete issue body specifies files, tests and acceptance gates.
- Source files: Report; inspect linked commit/reproducer before implementation..
- Regression evidence: Known hazard or regression is described above and in the linked discussion; reproduce independently.

## Commit-only Edge inventory

No associated PR/issue is asserted unless linked in the notes. Commit messages and diffs are authoritative for the change, not independent proof of compatibility.

### NtOpenFile argument ABI

- Source: [has207/xenia-edge `887beea6979fc1ee8580deb755d771c61e0039ad`](https://github.com/has207/xenia-edge/commit/887beea6979fc1ee8580deb755d771c61e0039ad); 2026-09-20T00:29:06+09:00; Herman S..
- Game/scope: Dead Rising. Classification: General correctness; B.
- Reason / required adaptation / tests: Restore ShareAccess argument and forward it; test PPC r7 versus r8.
- ReXGlue issue: **RG-GDK-003**; status: investigated, not ported. PR: not identified; issue references appear in the linked roadmap body.
- Source files: `src/xenia/kernel/xboxkrnl/xboxkrnl_io.cc`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

### Storage request timing

- Source: [has207/xenia-edge `5e9eae601b16757e49eeb83ab0f4d2945809f401`](https://github.com/has207/xenia-edge/commit/5e9eae601b16757e49eeb83ab0f4d2945809f401); 2026-09-17T01:33:24+09:00; Herman S..
- Game/scope: UEFA Champions League 2006–2007 / 45410811. Classification: General compatibility hypothesis; C/G/H.
- Reason / required adaptation / tests: Replaces rejected #275 allocation cap; scheduler-dependent. Test sync/async completion and memory pressure; no global delay transplant.
- ReXGlue issue: **RG-GDK-016**; status: investigated, not ported. PR: not identified; issue references appear in the linked roadmap body.
- Source files: `src/xenia/emulator.cc`, `src/xenia/kernel/guest_scheduler.cc`, `src/xenia/kernel/guest_scheduler.h`, `src/xenia/kernel/xfile.cc`, `src/xenia/kernel/xfile.h`, `src/xenia/vfs/device.cc`, `src/xenia/vfs/device.h`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

### Charge seek only for non-contiguous read

- Source: [has207/xenia-edge `e987fd7f502bc8f0f42345b1855169a2fe7afc25`](https://github.com/has207/xenia-edge/commit/e987fd7f502bc8f0f42345b1855169a2fe7afc25); 2026-09-17T20:52:56+09:00; Herman S..
- Game/scope: Storage workloads. Classification: Regression refinement; B/H.
- Reason / required adaptation / tests: Review together with 5e9eae601; sequential reads must not pay a false seek cost.
- ReXGlue issue: **RG-GDK-016**; status: investigated, not ported. PR: not identified; issue references appear in the linked roadmap body.
- Source files: `src/xenia/kernel/xfile.cc`, `src/xenia/vfs/device.cc`, `src/xenia/vfs/device.h`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

### XMA loop frame boundary

- Source: [has207/xenia-edge `5dd1cdbbf548745a15714c158b15aad128530440`](https://github.com/has207/xenia-edge/commit/5dd1cdbbf548745a15714c158b15aad128530440); 2026-09-12T15:47:46+09:00; Herman S..
- Game/scope: Tekken Tag 2. Classification: General correctness; B/H.
- Reason / required adaptation / tests: Local XMA has different context class; test loop_start one bit early, exact starts and split packet headers.
- ReXGlue issue: **RG-GDK-018**; status: investigated, not ported. PR: not identified; issue references appear in the linked roadmap body.
- Source files: `src/xenia/apu/xma_context_new.cc`, `src/xenia/apu/xma_context_new.h`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

### XMA header across packet boundary

- Source: [has207/xenia-edge `adf56b76c434fd97876fd79ffcde65b7ff90c8e6`](https://github.com/has207/xenia-edge/commit/adf56b76c434fd97876fd79ffcde65b7ff90c8e6); 2026-09-06T16:30:48+09:00; Herman S..
- Game/scope: Split frame streams. Classification: General correctness; B/H.
- Reason / required adaptation / tests: Preserve consume accounting and ring progress; malformed and multistream fixtures.
- ReXGlue issue: **RG-GDK-018**; status: investigated, not ported. PR: not identified; issue references appear in the linked roadmap body.
- Source files: `src/xenia/apu/xma_context_new.cc`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

### Retire DXBC for SPIR-V→DXIL transfers

- Source: [has207/xenia-edge `c00e7aead23d03599c7a101f8ae96ca4bfc7fe8c`](https://github.com/has207/xenia-edge/commit/c00e7aead23d03599c7a101f8ae96ca4bfc7fe8c); 2026-08-26T02:34:29+09:00; Herman S..
- Game/scope: General D3D12. Classification: Architectural experiment; C/H.
- Reason / required adaptation / tests: Broad source removal cannot be cherry-picked into ReXGlue DXBC; vendor shader corpus required.
- ReXGlue issue: **RG-GDK-007**; status: investigated, not ported. PR: not identified; issue references appear in the linked roadmap body.
- Source files: `src/xenia/app/CMakeLists.txt`, `src/xenia/app/xenia_main.cc`, `src/xenia/gpu/CMakeLists.txt`, `src/xenia/gpu/d3d12/CMakeLists.txt`, `src/xenia/gpu/d3d12/d3d12_command_processor.cc`, `src/xenia/gpu/d3d12/d3d12_command_processor.h`, `src/xenia/gpu/d3d12/d3d12_render_target_cache.cc`, `src/xenia/gpu/d3d12/d3d12_render_target_cache.h`, `src/xenia/gpu/d3d12/d3d12_texture_cache.cc`, `src/xenia/gpu/d3d12/d3d12_texture_cache.h`, `src/xenia/gpu/d3d12/pipeline_cache.cc`, `src/xenia/gpu/dxbc.h`, `src/xenia/gpu/dxbc_shader.cc`, `src/xenia/gpu/dxbc_shader.h`, `src/xenia/gpu/dxbc_shader_translator.cc`, `src/xenia/gpu/dxbc_shader_translator.h`, `src/xenia/gpu/dxbc_shader_translator_alu.cc`, `src/xenia/gpu/dxbc_shader_translator_fetch.cc`, `src/xenia/gpu/dxbc_shader_translator_memexport.cc`, `src/xenia/gpu/dxbc_shader_translator_om.cc`, `src/xenia/gpu/metal/msl_shader.h`, `src/xenia/gpu/spirv_shader_translator_alu.cc`, `src/xenia/ui/d3d12/CMakeLists.txt`, `src/xenia/ui/d3d12/d3d12_api.h`, `src/xenia/ui/d3d12/d3d12_provider.cc`, `src/xenia/ui/d3d12/d3d12_provider.h`, `src/xenia/ui/imgui_debug_dialog.cc`, `src/xenia/ui/imgui_debug_dialog.h`, `src/xenia/ui/vulkan/CMakeLists.txt`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

### Remove Edge dxcompiler.dll dependency

- Source: [has207/xenia-edge `6e9cb7e3f6f5119aca7cf5a43c84b2abb1b78bec`](https://github.com/has207/xenia-edge/commit/6e9cb7e3f6f5119aca7cf5a43c84b2abb1b78bec); 2026-08-27T00:02:48+09:00; Herman S..
- Game/scope: General D3D12. Classification: Architecture evidence; C.
- Reason / required adaptation / tests: Do not confuse Microsoft DXC adoption with Edge current shader pipeline.
- ReXGlue issue: **RG-GDK-007**; status: investigated, not ported. PR: not identified; issue references appear in the linked roadmap body.
- Source files: `assets/locale/ar/xenia.po`, `assets/locale/bn/xenia.po`, `assets/locale/cs/xenia.po`, `assets/locale/da/xenia.po`, `assets/locale/de/xenia.po`, `assets/locale/el/xenia.po`, `assets/locale/es/xenia.po`, `assets/locale/fa/xenia.po`, `assets/locale/fi/xenia.po`, `assets/locale/fr/xenia.po`, `assets/locale/hi/xenia.po`, `assets/locale/hr/xenia.po`, `assets/locale/hu/xenia.po`, `assets/locale/id/xenia.po`, `assets/locale/it/xenia.po`, `assets/locale/ja/xenia.po`, `assets/locale/ko/xenia.po`, `assets/locale/nl/xenia.po`, `assets/locale/pl/xenia.po`, `assets/locale/pt_BR/xenia.po`, `assets/locale/ru/xenia.po`, `assets/locale/sk/xenia.po`, `assets/locale/sr/xenia.po`, `assets/locale/sv/xenia.po`, `assets/locale/ta/xenia.po`, `assets/locale/th/xenia.po`, `assets/locale/tl/xenia.po`, `assets/locale/tr/xenia.po`, `assets/locale/uk/xenia.po`, `assets/locale/ur/xenia.po`, `assets/locale/vi/xenia.po`, `assets/locale/xenia.pot`, `assets/locale/zh_CN/xenia.po`, `assets/locale/zh_TW/xenia.po`, `src/xenia/gpu/d3d12/dxc_compiler.cc`, `src/xenia/gpu/d3d12/dxc_compiler.h`, `src/xenia/gpu/d3d12/pipeline_cache.cc`, `src/xenia/gpu/d3d12/pipeline_cache.h`, `src/xenia/gpu/spirv_to_dxil_compiler.cc`, `src/xenia/gpu/spirv_to_dxil_compiler.h`, `src/xenia/ui/d3d12/d3d12_api.h`, `src/xenia/ui/d3d12/d3d12_provider.cc`, `src/xenia/ui/d3d12/d3d12_provider.h`, `src/xenia/ui/redist_installer_wx.cc`, `src/xenia/ui/redist_installer_wx.h`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

### Publish shader validity before translated flag

- Source: [has207/xenia-edge `462a1ac855d295a87f0c0fab232205eef9359d5c`](https://github.com/has207/xenia-edge/commit/462a1ac855d295a87f0c0fab232205eef9359d5c); 2026-09-18T09:26:08+09:00; Herman S..
- Game/scope: Async compilation. Classification: General correctness; B/H.
- Reason / required adaptation / tests: the local translator set `is_translated_` before `is_valid_` and before the D3D12 wrapper finished (binding layout UIDs, disassembly), while `ConfigurePipeline` and `PrepareRuntimeDescriptionForQueuedCreation` read `is_translated()` without the translation lock (double-checked locking) from the processor and creation threads. Adapted: both flags are atomics (acquire loads); the translator no longer publishes, and `PipelineCache::TranslateAnalyzedShader` calls the new `Translation::PublishTranslated()` (release) last on every exit, so a reader never sees a half-prepared translation. Edge's `TryClaimTranslation` background translation does not exist locally; translations stay serialized by `translation_request_lock_`. No deterministic test; covered by the async-compile stress fixture planned in RG-GDK-011 part 2.
- ReXGlue issue: **RG-GDK-011**; status: **ported (adapted)** in RG-GDK-011 part 1.
- Source files: `src/xenia/gpu/metal/metal_command_processor.cc`, `src/xenia/gpu/shader.h`, `src/xenia/gpu/shader_translator.cc`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

### Pin placeholder pipeline during draws

- Source: [has207/xenia-edge `fe84ec77e87739dd6d26589e35f4c5573e60d271`](https://github.com/has207/xenia-edge/commit/fe84ec77e87739dd6d26589e35f4c5573e60d271); 2026-09-11T00:08:24+09:00; Herman S..
- Game/scope: Async D3D12. Classification: Regression fix; B/H.
- Reason / required adaptation / tests: not applicable. There are no placeholder or interpreter PSOs locally: `IssueDraw` skips a draw while `GetD3D12PipelineByHandle` is null, and a pipeline's `state` only ever goes from null to the real PSO (release store after translation, acquire load at draw and at deferred-list replay), so a handle can never resolve to a different pipeline than the bindings were built for. Revisit if placeholder rendering is adopted.
- ReXGlue issue: **RG-GDK-011**; status: investigated, not applicable (no placeholders).
- Source files: `src/xenia/gpu/d3d12/d3d12_command_processor.cc`, `src/xenia/gpu/d3d12/pipeline_cache.cc`, `src/xenia/gpu/d3d12/pipeline_cache.h`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

### Ring pointer RB_BLKSZ publication

- Source: [has207/xenia-edge `29fcaeac3244bed8475b5b8b549a861d743c9c32`](https://github.com/has207/xenia-edge/commit/29fcaeac3244bed8475b5b8b549a861d743c9c32); 2026-08-30T15:50:11+09:00; Herman S..
- Game/scope: General PM4. Classification: General correctness candidate; B/H.
- Reason / required adaptation / tests: local code matched Edge's pre-fix state (write-back once per burst, `read_ptr_update_freq_` in the wrong unit). Ported into `CommandProcessor::ExecutePrimaryBuffer` (local `RingBuffer` reader) and `EnableReadPointerWriteBack`: republish every RB_BLKSZ quadwords, release fence before the store, write-back target re-read each time. Preferred over Canary #1195's fixed 8-packet cadence (closed unmerged) because it follows the guest-programmed block size. Tests: `gpu_tests [ring]` — the write-back advances to within one stride of a WAIT_REG_MEM blocked on the guest (fails without the port), and five ring lengths of bursts wrap while the fixture waits on the write-back for room.
- ReXGlue issue: **RG-GDK-011**; status: **ported** in RG-GDK-011 part 1.
- Source files: `src/xenia/gpu/command_processor.cc`, `src/xenia/gpu/pm4_command_processor_implement.h`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

### Guest scheduler starvation hack

- Source: [has207/xenia-edge `83abd43576d99ff5ef651e54272f8e95c077af76`](https://github.com/has207/xenia-edge/commit/83abd43576d99ff5ef651e54272f8e95c077af76); 2026-08-31T10:13:18+09:00; Herman S..
- Game/scope: Guest scheduler. Classification: Experimental; G/H/C.
- Reason / required adaptation / tests: Do not port to static runtime. Requires guest scheduler and measured starvation reproducer.
- ReXGlue issue: **RG-GDK-015**; status: investigated, not ported. PR: not identified; issue references appear in the linked roadmap body.
- Source files: `src/xenia/kernel/guest_scheduler.cc`, `src/xenia/kernel/guest_scheduler.h`, `src/xenia/kernel/xthread.h`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

### Case-insensitive content match

- Source: [has207/xenia-edge `16ba84808609b449778b1f00745120851697989c`](https://github.com/has207/xenia-edge/commit/16ba84808609b449778b1f00745120851697989c); 2026-08-31T12:17:58+09:00; Herman S..
- Game/scope: Content packages. Classification: General correctness candidate; B.
- Reason / required adaptation / tests: FATX lookup semantics with mixed case and collisions; preserve Windows paths and UTF-8.
- ReXGlue issue: **RG-GDK-017**; status: investigated, not ported. PR: not identified; issue references appear in the linked roadmap body.
- Source files: `src/xenia/kernel/xam/content_manager.cc`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

### Audio client lifetime/lock ordering

- Source: [has207/xenia-edge `8aa50e0e07ed659b26ea06e72c4bc21a07ad9bbb`](https://github.com/has207/xenia-edge/commit/8aa50e0e07ed659b26ea06e72c4bc21a07ad9bbb); 2026-05-13T16:14:22+09:00; Herman S..
- Game/scope: Title teardown. Classification: Regression-prone correctness; B/H.
- Reason / required adaptation / tests: Canary #1214 and Edge #164 must be reviewed together; local locks differ.
- ReXGlue issue: **RG-GDK-018**; status: investigated, not ported. PR: not identified; issue references appear in the linked roadmap body.
- Source files: `src/xenia/apu/audio_system.cc`, `src/xenia/apu/audio_system.h`.
- Known regressions: not established locally; preserve upstream follow-ups and run the mapped regression gate.

## Review process

Monthly, and before each subsystem port or release: fetch upstream refs into the controlled reference checkout; record date, SHA, merge-base and patch-equivalence comparison. Read new/updated issues and PRs, including closed-unmerged work and regressions. Search subsystem terms plus AMD/NVIDIA/Intel and title IDs. Re-check older open watches. Record explicit classification, affected titles, JIT dependencies, tests and whether a ReXGlue issue is justified. Update existing issues rather than duplicate.

Port only to the implementation fork, retaining author/license and full SHA/PR/issue provenance. Separate general corrections, driver workarounds and title profiles. Run baseline and vendor gates, record results, then merge through normal review. Never auto-merge from Xenia/Canary/Edge or make the runtime depend on the Edge checkout. Keep rejected proposals in this ledger to prevent rediscovery as apparently new fixes.

A watch issue is unblocked by a reproducible local failing fixture plus settled semantics, or by an upstream resolution that survives the same review. Merge upstream alone is not sufficient. The roadmap has one continuous-review issue; narrower pending work is attached to its owning subsystem issue instead of duplicating every upstream request.

## Reproduce source acquisition

From the controlled Edge checkout, fetch read-only references (these create only
local research refs):

```powershell
git fetch --no-tags https://github.com/has207/xenia-edge.git edge:refs/remotes/research-edge/edge
git fetch --no-tags https://github.com/xenia-canary/xenia-canary.git canary_experimental:refs/remotes/research-canary/canary_experimental
git fetch --no-tags https://github.com/xenia-project/xenia.git master:refs/remotes/research-xenia/master
gh issue list -R xenia-canary/xenia-canary --state open --limit 1000
gh pr list -R xenia-canary/xenia-canary --state open --limit 1000
gh issue list -R has207/xenia-edge --state open --limit 1000
gh pr list -R has207/xenia-edge --state open --limit 1000
```

Use `gh api --paginate` for issue comments, PR files/reviews and updated closed
items; record retrieval time and any API limit. The investigation snapshot
retrieved up to 100 comments/files per selected item; no selected comment thread
was truncated. Refresh rather than treating the snapshot as permanent upstream
status. The first-parent boundary is not necessarily a project's first original
fork; retained author dates can predate rewritten history.
