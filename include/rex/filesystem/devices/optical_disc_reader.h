// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#pragma once
#include <rex/filesystem.h>

namespace rex::filesystem {
// Only explicit drive-letter optical paths (\\.\D:), never physical disks.
bool IsOpticalDiscPath(const std::filesystem::path& path);
std::unique_ptr<FileHandle> OpenOpticalDisc(const std::filesystem::path& path, size_t* size);
// The underlying reader requires sector-aligned offsets, lengths and buffers.
// Injection lets synthetic tests enforce the same contract as unbuffered I/O.
std::unique_ptr<FileHandle> MakeSectorAlignedDiscReader(std::unique_ptr<FileHandle> reader,
                                                        size_t sector_size, size_t size);
}  // namespace rex::filesystem
