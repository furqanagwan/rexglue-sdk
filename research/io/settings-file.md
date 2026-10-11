# Settings file strings

`SaveConfig` (`src/core/cvar.cpp`) writes string settings as escaped TOML
basic strings, so a Windows path is saved as `"C:\\Users\\..."`.

Through 0.1.0-alpha.3 the strings were written unescaped. A saved game source
such as `game_source = "C:\Users\..."` holds `\U`, which TOML reads as a
Unicode escape, so the whole file failed to parse. The next launch then:

- had no settings at all;
- showed the game picker again;
- saved the new choice the same way.

Every setting except the game source was lost on each launch. This was found
in a Blood Stone play session on 2026-10-11, where `log_level = "warn"`
disappeared and the picker came back.

`LoadConfig` repairs those files. When a file does not parse, each
`name = "..."` line whose value holds a backslash (and no `'`) is read as a
literal string `'...'` and the file is parsed again. The next save writes it
escaped. A value with both a backslash and a `'` is not repaired.

The parse error is logged before logging starts, so it never reaches the log
file; only the console sees it.

Tests: `cvar SaveConfig writes Windows paths that load again` and
`cvar LoadConfig reads a file saved with unescaped Windows paths`
(`tests/unit/core/cvar_test.cpp`). Both fail on the old code.
