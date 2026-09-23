# Initial Windows D3D12 regression baseline

This file records issue [RG-GDK-001](https://github.com/furqanagwan/rexglue-sdk/issues/1)
on the implementation branch rooted at `main`. The broader modernization roadmap
is being reviewed separately. [Baseline capture](baseline-capture.md) describes
the recorder, private run and exact limitations.

The first representative title is 007: Quantum of Solace (`415607FF`, media
`06DD88A0`). It compiles to a native executable, but initial boot fails before
a game log or screenshot. This is a **failing title result**, not a working or
partially working result. Gameplay, saves, audio, input and graphics have not
been assessed. No other title is selected until this one has a reproducible
boot scene. Synthetic unit and PPC tests remain part of every baseline.

| Workload | Owner | Current result | Evidence / next step |
| --- | --- | --- | --- |
| SDK unit and PPC tests | SDK maintainers | Debug/Release results in baseline capture | Preserve test logs and four explicit skips |
| Quantum of Solace boot | Furqan Agwan / SDK maintainers | Failing, `0xC000001D` | Private run manifest; locate generated `ud2` cause |
| Quantum of Solace gameplay/save/audio/input | Furqan Agwan / SDK maintainers | Not run | Requires boot and controlled repeatable scene |
| D3D12 NVIDIA | Furqan Agwan / SDK maintainers | Not run | Requires a scene reaching GPU initialization; record adapter/path/driver, log and screenshot |
| AMD and Intel GPU | External future coverage | Untested, non-blocking | User has no usable test access; do not claim compatibility |
| April 2026 GDK deployment | SDK maintainers | Not run | The ordinary Windows preset is not GDK validation |

For future changes, preserve the first result, rerun the same scene and compare
module/generated-code hashes, config, selected GPU path, logs and images. Use
disposable saves for failure tests. A compile pass cannot upgrade a title or
vendor result. Missing hardware results are marked untested; per the user's
decision, AMD and Intel GPU coverage does not block local completion.

The known generated branch from `0x824A287C` to `0x821C1BF8` emits `REX_FATAL`.
The observed boot crash is an illegal instruction at a different generated code
offset; its cause is still unknown. Keep these as separate investigation items.
