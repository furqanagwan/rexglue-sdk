---
name: Compatibility regression
about: Previously working behavior changed relative to a recorded baseline
title: "[Regression] "
labels: regression
---

## Regression category
Functional / rendering / performance / stability / compatibility / vendor / GDK / build

## Last known good / first known bad
Commit SHAs, build IDs, or explicitly unknown. Include suspected source change.

## Affected subsystem and game/test
Title ID, module hash/TU, generated title project and SDK commits. No game binaries.

## Environment and vendor validation
Windows/GDK/compiler versions, CPU, GPU model/vendor/driver, D3D12 capabilities,
selected path, config/profiles. AMD / NVIDIA / Intel: pass, fail, blocked or not-run.

## Reproduction
Exact steps, scene/input sequence, expected and observed result, frequency.

## Evidence
Logs, baseline/candidate screenshots, PCM, performance runs, PIX/DRED when relevant.
Redact personal paths and accounts; link private captures appropriately.

## Upstream references
Issue/PR/commit and reported scope. State whether reproduced in ReXGlue.

## Workaround
Known safe workaround, its scope, or none known.

## Acceptance criteria
Specific regression test and unchanged control cases required to close this issue.
