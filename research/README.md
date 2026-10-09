# Research

The code has no comments: names say what it does. Knowledge the code cannot
say lives here instead. That includes how the Xbox 360 hardware behaves, why
a workaround exists, where a piece of code came from, and what was measured.

Each folder covers one area. Each file is one topic, named for the topic
(`edram-tiling.md`, not `notes-3.md`).

| Folder | Covers |
| --- | --- |
| [audit](audit/) | Codebase health reviews and the cleanup plan |
| [cpu](cpu/) | PowerPC instructions, FPSCR, recompiler behavior |
| [gpu](gpu/) | Xenos, EDRAM, shaders, Direct3D 12 |
| [language](language/) | Language and toolchain decisions |
| [releases](releases/) | Versioning, releases and the updater |

## Writing a note

- Start with the conclusion in one or two sentences.
- Say what code it explains, with the path (`src/graphics/d3d12/...`).
- Cite sources: hardware tests, upstream commits, Microsoft docs.
- Say what is unknown or untested.
- When code changes, update the note in the same pull request.

Older records still live in [docs](../docs/README.md); move a topic here
when you next touch it.
