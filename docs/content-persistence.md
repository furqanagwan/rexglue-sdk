# Content persistence (RG-GDK-017)

How guest saves and other XAM content reach the host disk, and what the flush
calls promise. RG-GDK-017 is delivered in parts; this page grows with them.

| Part | Scope | Status |
| --- | --- | --- |
| 1 | `XamContentFlush`, `NtFlushBuffersFile`, durable content headers | Done |
| 2 | STFS container bounds (Canary #1226), mixed-case paths | Done |
| 3 | Profile setting concurrency and durability, close commits content (Canary #981, #5, #1220) | Done |
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

## Close and profile settings (part 3)

- `XamContentClose` flushes the root, as `XamContentFlush` does, before it
  releases the package: closing content commits it on the console. A save a
  title closes without flushing therefore survives a system crash, not only a
  process crash (Canary #1220 reports the loss after a PC crash). The package
  is closed even if the flush fails, and the failure is returned.
- Profile settings are shared objects behind a lock. A guest thread that read
  a setting keeps it alive while another thread writes the same setting
  (Canary #5, and #981, which locks Canary's `UserTracker`; ReXGlue has no
  tracker). Before, the writer destroyed the object the reader was using.
- Title-specific settings (`XPROFILE_TITLE_SPECIFIC1`-`3`) are saved through
  the same flushed-temporary-and-rename write as content headers, and a failed
  save is logged instead of writing to a null file. Loading a title with no
  saved copy gives it an unset setting; before, the previous title's value
  stayed.
- `KernelState::title_id()` is 0 with no title loaded instead of asserting.

ReXGlue has one signed-in profile (`KernelState::user_profile()`), so the
two-user split-screen case in Canary #1220 and #981's per-user contexts have no
local counterpart yet. Multi-user profiles are recorded as a gap, not claimed.

## STFS and SVOD packages (part 2)

Installed content (`ContentManager::InstallContent`) and disc packages are read
by `StfsContainerDevice`. Their headers, tables and chains come from the file,
so a damaged or incomplete package is input to be rejected, not an invariant
to assert:

- A package whose metadata `content_size` describes more data than the file
  holds is refused at mount and named (Canary #1226). Zero means unknown, and
  such packages go through the checks below.
- A block chain stops where the hash table for the next block is not in the
  file. The file keeps the blocks found, and reads end at the last byte the file
  really holds, instead of placing later blocks at the wrong offset.
- A file-table chain that leaves the package, an entry whose parent index
  points past the entries read so far or at a file, and an SVOD directory node
  that repeats or nests more than 1024 deep all refuse the package. So does an
  SVOD node in a data file that does not exist.
- Names are clamped to the 40-byte name field.
- A folder is scanned for a package without mapping files shorter than the
  4-byte magic.

Path lookup inside a package ignores case. When two entries differ only by
case, the first in the file table is the one found.

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

`kernel_tests [profile]` and the close case in `[content]` cover a held setting
outliving its replacement (the setting records its own destruction), 2000
writes against four reader threads, a title-specific setting saved whole and
read back by a new profile, no leak into a title without a saved copy, and
close flushing (header restored, flush failure returned, package closed).
Keeping the previous title's value, or closing without a flush, each fails its
test.

`unit_tests [stfs],[svod]` builds packages in memory: a read-only STFS with one
hash table, a file-table block and data blocks, and a single-file SVOD. Each
malformed case damages one field or cuts the file short. Run against the
previous reader, 7 of the 13 fail. The other six pass on both readers: they pin
behavior that was already right (valid reads, case-insensitive lookup,
truncation handling).

## Limitations

- The crash test kills the process, not the machine. Writes in the OS cache
  survive that even without a flush, so the test proves the save and its
  header are complete after a crash and a restart, not that the flush was
  needed. Power loss is not simulated.
- The atomic header write is checked by its outcome (no torn header or
  leftover temporary), not by interrupting it midway.
- No title was run.
