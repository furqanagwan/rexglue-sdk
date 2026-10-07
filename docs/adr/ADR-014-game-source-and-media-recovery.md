# ADR-014: Checked game sources and recoverable media I/O

Date: 2026-10-07. Status: accepted for the SDK source/I/O implementation;
console scenes are integrated; physical drive/title and interactive validation remain pending.

## Context

[SDK #154](https://github.com/furqanagwan/rexglue-sdk/issues/154) requests a
first-run ISO/disc/folder workflow. The existing runtime mounts only host
folders. Its unused XDVDFS device maps the entire image and reads directory
nodes and payloads through unchecked pointers. Removable media can invalidate
mapped pages rather than return an ordinary guest I/O error.

## Decision

Keep sources and guest VFS services in the SDK. The Guide repository owns
console XUI presentation, as required by ADR-013. First-run host controls
use the reusable Guide message-box and Active Downloads scene models before
guest construction when private assets are available, and retain an ImGui
fallback while loading or without the assets. File picking, validation and
copying stay in the SDK. The Guide takes immutable host activity snapshots;
completed copy results remain visible alongside title-update jobs.

Use positioned file reads for images and sector-aligned unbuffered reads for
explicit optical drive-letter devices. Permit only optical drives in the raw
reader. Query CD-ROM geometry; reject inaccessible media or a source without a
readable XDVDFS game partition. Do not modify drive firmware or attempt another
way of obtaining a game partition. The parser retains its existing candidate
partition offsets and bounds all headers, tables, names and payload ranges.
Directory trees reject cycles and traversal names; table traversal is iterative.
Limits are 32 MiB per directory table, 256 MiB of metadata and 256 nested
directories. Physical drive compatibility is not established by synthetic tests.

Preserve the existing mapping interface with owned read snapshots. These
buffers have no pages backed by removable media. Failed and short reads return
X_STATUS_UNEXPECTED_IO_ERROR with zero completed bytes.

New generated image configs carry the original input XEX's title ID,
XXH3-128 full-file checksum and guest-relative executable path. The checksum
is a content/build fingerprint, not authentication or a service entitlement.
TU builds fingerprint the original input, before their update is applied.
Existing generated configs keep their folder workflow; regenerate to enable
checked first-run image selection. Do not call the existing OnLoadXexImage
hook before Runtime setup: the generated path supplies preflight identity.

The selected `game_source` is an absolute folder/image/optical path, persisted
through the existing per-title config. An explicit command-line
`game_data_root` takes precedence. The runtime mounts the chosen device at
the existing game:/d: aliases without changing save/profile/cache paths.

Extraction uses the SDK reader, streams into a newly owned staging folder,
reports progress and supports cancellation between reads. It rejects Windows
filename aliases and never overwrites an existing destination. Commit with a
directory rename only after successful copying; clean only the verified owned
staging directory on failure/cancellation. OS reads already in progress can
finish before a cancellation takes effect.

Media recovery serializes failed guest I/O, keeps existing open entries, and
prompts Retry/Leave Game. Retry verifies the source XEX and directory layout,
then replaces the reader. It does not accept a different disc/repacked layout
for existing handles. UI-thread reads return errors rather than waiting on
their own UI. Shutdown cancels waiting workers before title teardown; closing
before guest construction performs cleanup so extraction can cancel.

## Validation and remaining gates

Synthetic images exercise malformed metadata, unaligned sector reads, actual
file truncation, VFS aliases, source mismatch, extraction/cancellation,
concurrent recovery, UI-thread error handling and shutdown. Generated output
tests bind the raw XEX and guest path, including TU metadata. ImGui tests cover
source validation, persistence, rejection, cancellation and recovery actions.

Keep #154 open until real-title original/TU launching, physical drive removal
and same-disc retry, painted/controller scene presentation and friendly
mismatch names meet the issue's gates. Console templates and source-progress
integration have synthetic/private scene tests, not an owner play session.
No ISO, Microsoft asset or game executable is distributed.

References: Microsoft [file buffering/alignment](https://learn.microsoft.com/en-us/windows/win32/fileio/file-buffering)
and [CD-ROM geometry](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddcdrm/ni-ntddcdrm-ioctl_cdrom_get_drive_geometry_ex).
