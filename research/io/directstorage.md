# DirectStorage: defer

**Decision (2026-10-09, issue #42 / RG-GDK-029): don't adopt DirectStorage.**
The three 007 games spend about 0.1% of their time waiting on file reads,
and no single read blocked for more than 10 ms. DirectStorage speeds up large
batches of reads and GPU decompression. These games read through the Xbox 360
kernel one request at a time and decompress on their own CPU threads, so it
has nothing to accelerate. Revisit if a game is measured spending real time
blocked on reads.

## How it was measured

`file_read_stats_interval=5` (in `src/system/file_read_statistics.cpp`) times
every guest read in `XFile::Read` and `XFile::ReadScatter`, including waiting
for the file's lock. Every 5 seconds it logs the reads, bytes, time blocked
and a size histogram. Guest reads are synchronous, so time blocked is time
the calling guest thread could not run.

Each game ran once for 90 seconds from launch with no input, on a fresh
profile, Release build, GDK 260404, NVIDIA RTX 5080 Laptop, game files
extracted on the internal NVMe drive. The runs went through boot, logos,
menus or intro, and the first level load.

## Results

| Game | Reads | Data | Time blocked | Share of run | Longest read |
| --- | --- | --- | --- | --- | --- |
| Quantum of Solace | 1,857 | 276 MiB | 96 ms | 0.12% | 6.1 ms |
| Blood Stone | 1,978 | 262 MiB | 92 ms | 0.11% | 9.5 ms |
| 007 Legends | 6,571 | 180 MiB | 122 ms | 0.14% | 9.6 ms |

The busiest 5-second window in each game:

| Game | Window |
| --- | --- |
| Quantum of Solace | 1,015 reads, 126 MiB, 40 ms blocked (0.8%) |
| Blood Stone | 405 reads, 57 MiB, 17 ms blocked (0.3%) |
| 007 Legends | 1,884 reads, 61 MiB, 38 ms blocked (0.6%) |

Read sizes (≤4 KiB / ≤64 KiB / ≤1 MiB / larger):

| Game | ≤4 KiB | ≤64 KiB | ≤1 MiB | Larger |
| --- | --- | --- | --- | --- |
| Quantum of Solace | 32 | 74 | 1,746 | 5 |
| Blood Stone | 19 | 306 | 1,650 | 3 |
| 007 Legends | 4,233 | 1,707 | 617 | 14 |

Quantum of Solace and Blood Stone stream in 64 KiB–1 MiB pieces. Legends makes
many small reads, but each still finishes in well under a millisecond.

## Limits

- The files had been read earlier the same day, so Windows' file cache
  probably held them. A cold-cache run (after clearing the standby list) was
  not done. Even uncached, 276 MiB from an NVMe drive at about 3 GB/s is
  roughly 0.1 s in total over a 90-second run.
- A hard drive or network share would be slower; that's not a supported
  setup to optimise for.
- Disc-image (ISO) sources go through the same `XFile` path but were not
  measured separately.
- Issue #16 (storage completion timing for a UEFA title) is unrelated: it
  is about when completions are reported, not how fast data arrives.

Raw logs were kept locally only and removed after these numbers were taken.
