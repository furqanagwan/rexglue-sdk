# Content persistence (RG-GDK-017)

How guest saves and other XAM content reach the host disk, and what the flush
calls promise. RG-GDK-017 is delivered in parts; this page grows with them.

| Part | Scope | Status |
| --- | --- | --- |
| 1 | `XamContentFlush`, `NtFlushBuffersFile`, durable content headers | Done |
| 2 | STFS container bounds (Canary #1226), mixed-case paths | Open |
| 3 | Concurrent profiles, crash persistence for several users (Canary #981, #5, #1220) | Open |
| 4 | Notification masks and order, compiled-module relaunch, XMP initial state (Canary #1135, closed unmerged) | Open |

## Package model

A content package is a host directory,
`<content root>/<xuid>/<title id>/<content type>/<file name>/`, mounted at the
guest root name (`save:`) through a host path device. Its metadata sits beside
it in `<content root>/<xuid>/<title id>/Headers/<content type>/<file name>.header`
(`XCONTENT_AGGREGATE_DATA`, then the license mask when there is one).

Guest file writes go straight to host files through Win32 `WriteFile` on
unbuffered handles. Nothing is held back in the process, so a crash of the
title does not lose writes that already returned. Only the OS cache stands
between them and the disk.

## Flush contract (part 1)

- `XamContentFlush(root, overlapped)`: every open guest file under `root` is
  flushed to the disk (`FlushFileBuffers`), and the package header is written
  if it is missing, for content created by a run that stopped before
  `XamContentCreate` wrote it. Success means both happened. A root that is not
  open returns `ERROR_FILE_NOT_FOUND`, as `XamContentClose` does. A file the
  host fails to flush returns `ERROR_WRITE_FAULT`. With an overlapped, every
  result is delivered through it, failures included, so a title waiting on it
  is released.
- `NtFlushBuffersFile(handle)`: flushes that file.
  `STATUS_INVALID_HANDLE` for an unknown handle, `STATUS_UNEXPECTED_IO_ERROR`
  when the host flush fails.
- Header writes (create, flush, install) write a sibling `.tmp`, flush it and
  rename it over the header. A crash leaves the old header or the new one,
  never a torn one.

Canary #1216 is the source (merged). Canary rewrites the header of its own
directory-package class on flush; the adaptation above fits ReXGlue's plain
directories. The return code for an unknown root is not verified against
console behavior; Canary returns `STATUS_INVALID_PARAMETER` there without
completing the overlapped.

## Tests

`kernel_tests [content]` runs an image-less `Runtime` and gives each case its
own content root:

- a flushed save reads back, under either casing of the root name;
- flushing a root that isn't open fails;
- a file whose flush fails is reported and clears once it is closed;
- flush restores a missing header;
- a torn header and a stray `.tmp` are replaced whole;
- a child process creates a save, flushes it and is killed with
  `TerminateProcess`, and the parent lists it with its metadata and reads its
  data back through a new content manager.

## Limitations

- The crash test kills the process, not the machine. Writes in the OS cache
  survive that even without a flush, so the test proves the save and its
  header are complete after a crash and a restart, not that the flush was
  needed. Power loss is not simulated.
- The atomic header write is checked by its outcome (no torn header or
  leftover temporary), not by interrupting it midway.
- No title was run.
