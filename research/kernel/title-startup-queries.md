# Title startup queries

Legends, Blood Stone and Quantum of Solace logged warnings every run for calls
the SDK answered on purpose. These were missing-file probes, a content package
path, a cache partition format and the system link version status. The answers
are unchanged or now real, and only failures that need a look are warnings.

Seen in the 0.1.0-alpha.3 smoke runs (SDK `503bfcc`, 180 s each).

## Missing-file probes

`NtCreateFile` (`src/kernel/xboxkrnl/xboxkrnl_io.cpp`) logs "not found"
(`X_STATUS_NO_SUCH_FILE`, `X_STATUS_OBJECT_NAME_NOT_FOUND`) at debug level.
Other failures stay warnings.

- Quantum of Solace opens `D:\<language>\code_post_gfx.ff` for 13 languages.
  The disc only has the ones it ships.
- Blood Stone opens `game:\gamedata\xt\loc\` and two `pre_credits` folders that
  are not in its data (the game ships `pre_credits_2_new`).

Both games carry on. The status code is the one Xenia returns; what the console
kernel returns for a missing folder versus a missing file is not checked.

## XamContentResolve

`src/kernel/xam/xam_content.cpp`, path from `ResolveContentPackageDevicePath`
(`src/system/xam/content_manager.cpp`). It is ported from xenia-canary
`canary_experimental` at `c9c8e483` (`xeXamContentResolve`). The audit clone is
shallow, so the commit that first added it is not recorded.

The path is `<device root><XUID>\<title ID>\<content type>\<file name>`:

| Device ID | Root |
| --- | --- |
| 1 (hard drive) | `\Device\Harddisk0\Partition1\Content\` |
| 2 (disc) | `D:\content\` |
| other | `X_ERROR_INVALID_PARAMETER` |

The XUID is the signed-in player's for saved games and zero for everything
else. A root name is rejected, as upstream does. The overlapped form completes
deferred.

Legends (`sub_827BD810`) resolves a package, then opens it with `NtOpenFile`
(read, non-directory) and keeps the handle. ReXGlue stores packages as host
folders, not STFS files, so the open fails as it would on a console without
that package. Before this change the resolve itself failed with
`X_ERROR_NOT_FOUND`. Which package Legends asks for is not known.

## IoDismountVolumeByFileHandle

Legends writes an `XTAF` header to a cache partition with `NtWriteFile` and
then dismounts the volume, so the kernel mounts it again on the next open. The
SDK's cache partitions are host folders or a null device, with no mounted
state to drop. The call checks the handle (`X_STATUS_INVALID_HANDLE` if it is
not a file) and succeeds.

## XFileFsDeviceInformation

`NtQueryVolumeInformationFile` (`src/kernel/xboxkrnl/xboxkrnl_io_info.cpp`)
reports `FILE_DEVICE_UNKNOWN` with no characteristics, as Xenia does. Titles
compare it with `FILE_DEVICE_EHSTOR` (USB storage), and no ReXGlue volume is
USB storage. The console's value for its hard drive and disc is not known, so
the answer is unchanged and no longer logged.

## XNetGetBroadcastVersionStatus

`NetDll_XNetGetBroadcastVersionStatus(caller, reset)` in
`src/kernel/xam/xam_net.cpp` returns 0. This means no system link broadcast
from an older or newer version of the title has been seen, which is true
without system link. It was a generic stub that also returned 0, but logged a
warning.

## Tests

`tests/kernel/title_startup_queries_test.cpp` covers:

- the package paths;
- the XUID rule;
- truncation, rejected root names and unknown devices;
- dismount with a bad handle and with an open file;
- the version status.
